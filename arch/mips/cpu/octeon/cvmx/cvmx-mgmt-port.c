/***********************license start***************
 * Copyright (c) 2003-2015  Cavium Inc. (support@cavium.com). All rights
 * reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.

 *   * Neither the name of Cavium Inc. nor the names of
 *     its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.

 * This Software, including technical data, may be subject to U.S. export  control
 * laws, including the U.S. Export Administration Act and its  associated
 * regulations, and may be subject to export or import  regulations in other
 * countries.

 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
 * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 * THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY REPRESENTATION OR
 * DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT DEFECTS, AND CAVIUM
 * SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES OF TITLE,
 * MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF
 * VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK ARISING OUT OF USE OR
 * PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 ***********************license end**************************************/

/**
 * @file
 *
 * Support functions for managing the MII management port
 *
 * <hr>$Revision: 169278 $<hr>
 */
#include "cvmx.h"
#include "cvmx-bootmem.h"
#include "cvmx-spinlock.h"
#include "cvmx-mdio.h"
#include "cvmx-mgmt-port.h"
#include "cvmx-sysinfo.h"
#include "cvmx-error.h"
#include "cvmx-helper-cfg.h"
#include "cvmx-helper-bgx.h"
#include "octeon-feature.h"

/**
 * Format of the TX/RX ring buffer entries
 */
typedef union {
	uint64_t u64;
	struct {
		uint64_t reserved_62_63:2;
		uint64_t len:14;	/* Length of the buffer/packet in bytes */
		uint64_t tstamp:1;	/* For TX, signals that the packet should be timestamped */
		uint64_t code:7;	/* The RX error code */
		uint64_t addr:40;	/* Physical address of the buffer */
	} s;
	struct cn78xx_tx_ring_entry {
		uint64_t len:14;	/* Length of the buffer/packet in bytes */
		uint64_t tstamp:1;	/* For TX, signals that the packet should be timestamped */
		uint64_t reserved_48_42:7;
		uint64_t addr:42;	/* Physical address of the buffer */
	} cn78xx_tx;
	struct cn78xx_rx_ring_entry {
		uint64_t len:14;	/* Length of the buffer/packet in bytes */
		uint64_t code:6;	/* The RX error code */
		uint64_t reserved_43_42:2;
		uint64_t addr:42;	/* Physical address of the buffer */
	} cn78xx_rx;
} cvmx_mgmt_port_ring_entry_t;

/**
 * Per port state required for each mgmt port
 */
typedef struct {
	cvmx_spinlock_t lock;	/* Used for exclusive access to this structure */
	int tx_write_index;	/* Where the next TX will write in the tx_ring and tx_buffers */
	int rx_read_index;	/* Where the next RX will be in the rx_ring and rx_buffers */
	int port;		/* Port to use.  (This is the 'fake' IPD port number */
	uint64_t mac;		/* Our MAC address */
	cvmx_mgmt_port_ring_entry_t tx_ring[CVMX_MGMT_PORT_NUM_TX_BUFFERS];
	cvmx_mgmt_port_ring_entry_t rx_ring[CVMX_MGMT_PORT_NUM_RX_BUFFERS];
	char tx_buffers[CVMX_MGMT_PORT_NUM_TX_BUFFERS][CVMX_MGMT_PORT_TX_BUFFER_SIZE];
	char rx_buffers[CVMX_MGMT_PORT_NUM_RX_BUFFERS][CVMX_MGMT_PORT_RX_BUFFER_SIZE];
	cvmx_mgmt_port_mode_t mode;	/* Mode of the interface */
} cvmx_mgmt_port_state_t;

/**
 * Pointers to each mgmt port's state
 */
CVMX_SHARED cvmx_mgmt_port_state_t *cvmx_mgmt_port_state_ptr = NULL;

/**
 * Return the number of management ports supported by this chip
 *
 * @return Number of ports
 */
int __cvmx_mgmt_port_num_ports(void)
{
	if (OCTEON_IS_MODEL(OCTEON_CN56XX) || OCTEON_IS_MODEL(OCTEON_CN68XX))
		return 1;
	else if (OCTEON_IS_MODEL(OCTEON_CN52XX)
		 || OCTEON_IS_MODEL(OCTEON_CN6XXX)
		 || OCTEON_IS_MODEL(OCTEON_CN78XX)
		 || OCTEON_IS_MODEL(OCTEON_CN73XX)
		 || OCTEON_IS_MODEL(OCTEON_CNF75XX))
		return 2;
	else
		return 0;
}

/**
 * Called to initialize a management port for use. Multiple calls
 * to this function across applications is safe.
 *
 * @param port   Port to initialize
 *
 * @return CVMX_MGMT_PORT_SUCCESS or an error code
 */
cvmx_mgmt_port_result_t cvmx_mgmt_port_initialize(int port)
{
	char *alloc_name = "cvmx_mgmt_port";
	cvmx_mixx_oring1_t oring1;
	cvmx_mixx_ctl_t mix_ctl;
	int node = 0;
	int port_num;

	if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
		node = (port >> 12) & 0xf;
		port_num = port & 0xfff;
		port = (port >> 4) & 0x1;
	} else
		port_num = CVMX_HELPER_BOARD_MGMT_IPD_PORT + port;

	if ((port < 0) || (port >= __cvmx_mgmt_port_num_ports()))
		return CVMX_MGMT_PORT_INVALID_PARAM;

	cvmx_mgmt_port_state_ptr = cvmx_bootmem_alloc_named_flags(CVMX_MGMT_PORT_NUM_PORTS * sizeof(cvmx_mgmt_port_state_t), 128, alloc_name, CVMX_BOOTMEM_FLAG_END_ALLOC);
	if (cvmx_mgmt_port_state_ptr) {
		memset(cvmx_mgmt_port_state_ptr, 0, CVMX_MGMT_PORT_NUM_PORTS * sizeof(cvmx_mgmt_port_state_t));
	} else {
		const cvmx_bootmem_named_block_desc_t *block_desc = cvmx_bootmem_find_named_block(alloc_name);
		if (block_desc)
			cvmx_mgmt_port_state_ptr = cvmx_phys_to_ptr(block_desc->base_addr);
		else {
			cvmx_dprintf("ERROR: cvmx_mgmt_port_initialize: Unable to get named block %s on MIX%d.\n", alloc_name, port);
			return CVMX_MGMT_PORT_NO_MEMORY;
		}
	}

	/* Reset the MIX block if the previous user had a different TX ring size, or if
	 ** we allocated a new (and blank) state structure. */
	mix_ctl.u64 = cvmx_read_csr_node(node, CVMX_MIXX_CTL(port));
	if (!mix_ctl.s.reset) {
		uint64_t osize;
		oring1.u64 = cvmx_read_csr_node(node, CVMX_MIXX_ORING1(port));
		if (OCTEON_IS_MODEL(OCTEON_CN78XX)
		    || OCTEON_IS_MODEL(OCTEON_CN73XX)
		    || OCTEON_IS_MODEL(OCTEON_CNF75XX))
			osize = oring1.cn78xx.osize;
		else
			osize = oring1.cn68xx.osize;
		if (osize != CVMX_MGMT_PORT_NUM_TX_BUFFERS || cvmx_mgmt_port_state_ptr[port].tx_ring[0].u64 == 0) {
			mix_ctl.u64 = cvmx_read_csr_node(node, CVMX_MIXX_CTL(port));
			mix_ctl.s.en = 0;
			cvmx_write_csr_node(node, CVMX_MIXX_CTL(port), mix_ctl.u64);
			do {
				mix_ctl.u64 = cvmx_read_csr_node(node, CVMX_MIXX_CTL(port));
			} while (mix_ctl.s.busy);
			mix_ctl.s.reset = 1;
			cvmx_write_csr_node(node, CVMX_MIXX_CTL(port), mix_ctl.u64);
			cvmx_read_csr_node(node, CVMX_MIXX_CTL(port));
			memset(cvmx_mgmt_port_state_ptr + port, 0, sizeof(cvmx_mgmt_port_state_t));
		}
	}

	if (cvmx_mgmt_port_state_ptr[port].tx_ring[0].u64 == 0) {
		cvmx_mgmt_port_state_t *state = cvmx_mgmt_port_state_ptr + port;
		int i;
		cvmx_mixx_bist_t mix_bist;
		cvmx_mixx_oring1_t oring1;
		cvmx_mixx_iring1_t iring1;
		cvmx_agl_prtx_ctl_t agl_prtx_ctl;

		/* Make sure BIST passed */
		mix_bist.u64 = cvmx_read_csr_node(node, CVMX_MIXX_BIST(port));
		if (mix_bist.u64)
			cvmx_dprintf("WARNING: cvmx_mgmt_port_initialize: Managment port MIX failed BIST (0x%016llx) on MIX%d\n", CAST64(mix_bist.u64), port);

		if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
			cvmx_bgxx_cmr_global_config_t cmr_global_config;
			cvmx_bgxx_cmr_bist_status_t bist_status;
			int interface = ((port_num >> 8) & 0xf) - 8;

			bist_status.u64 = cvmx_read_csr_node(node, CVMX_BGXX_CMR_BIST_STATUS(interface));
			if (bist_status.s.status != 0)
				cvmx_dprintf("WARNING: cvmx_mgmt_port_initialize: BGX(%d)_CMR failed BIST for MIX%d\n", interface, port);

			/* When MIXx is reset, GBX_CMRx must be reset too */
			if (mix_ctl.s.reset) {
				cmr_global_config.u64 = cvmx_read_csr_node(node,
							    CVMX_BGXX_CMR_GLOBAL_CONFIG(interface));
				if (port)
					cmr_global_config.s.cmr_mix1_reset = 1;
				else
					cmr_global_config.s.cmr_mix0_reset = 1;
				cvmx_write_csr_node(node, CVMX_BGXX_CMR_GLOBAL_CONFIG(interface),
					cmr_global_config.u64);
			}
		} else {
			cvmx_agl_gmx_bist_t agl_gmx_bist;
			agl_gmx_bist.u64 = cvmx_read_csr(CVMX_AGL_GMX_BIST);
			if (agl_gmx_bist.u64)
				cvmx_dprintf("WARNING: cvmx_mgmt_port_initialize: Managment port AGL failed BIST (0x%016llx) on MIX%d\n", CAST64(agl_gmx_bist.u64), port);
		}

		/* Clear all state information */
		memset(state, 0, sizeof(*state));

		/* Take the control logic out of reset */
		mix_ctl.u64 = cvmx_read_csr_node(node, CVMX_MIXX_CTL(port));
		mix_ctl.s.reset = 0;
		cvmx_write_csr_node(node, CVMX_MIXX_CTL(port), mix_ctl.u64);

		/* Read until reset == 0.  Timeout should never happen... */
		if (CVMX_WAIT_FOR_FIELD64_NODE(node, CVMX_MIXX_CTL(port), cvmx_mixx_ctl_t, reset, ==, 0, 300000000)) {
			cvmx_dprintf("ERROR: cvmx_mgmt_port_initialize: Timeout waiting for MIX(%d) reset.\n", port);
			return CVMX_MGMT_PORT_INIT_ERROR;
		}

		/* Set the PHY address and mode of the interface (RGMII/MII mode). */
		if (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_SIM) {
			state->port = -1;
			state->mode = CVMX_MGMT_PORT_MII_MODE;
		} else {
			int phy_addr;

			if (state->mode == CVMX_MGMT_PORT_NONE) {
				phy_addr = cvmx_helper_board_get_mii_address((node<<12) | port_num);
				/* Change the mode to MII, when phy is not present (BGX is in mac mode). */
			if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
				int intf = (port_num >> 8) - 8;
				if (!cvmx_helper_get_port_phy_present(intf, port)) {
					state->mode = CVMX_MGMT_PORT_MII_MODE;
						goto done;
				}
			}
			if (phy_addr != -1) {
				cvmx_mdio_phy_reg_status_t phy_status;
				/* Read PHY status register to find the mode of the interface. */
				phy_status.u16 = cvmx_mdio_read((phy_addr >> 8) | (node << 2),
							phy_addr & 0xff, CVMX_MDIO_PHY_REG_STATUS);
				if (phy_status.s.capable_extended_status == 0)	// MII mode
					state->mode = CVMX_MGMT_PORT_MII_MODE;
				else if (!OCTEON_IS_OCTEON1PLUS()
					 && phy_status.s.capable_extended_status)	// RGMII mode
					state->mode = CVMX_MGMT_PORT_RGMII_MODE;
				else
					state->mode = CVMX_MGMT_PORT_NONE;
			} else {
				cvmx_dprintf("ERROR: cvmx_mgmt_port_initialize: Not able to read the PHY on MIX%d\n", port);
				return CVMX_MGMT_PORT_INVALID_PARAM;
			}
			}
done:
			if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX))
				/* Include node information to the port_num */
				state->port = (node << 12) | port_num;
			else
				state->port = port_num;
		}

		/* All interfaces should be configured in same mode */
		for (i = 0; i < __cvmx_mgmt_port_num_ports(); i++) {
			if (i != port && cvmx_mgmt_port_state_ptr[i].mode != CVMX_MGMT_PORT_NONE && cvmx_mgmt_port_state_ptr[i].mode != state->mode) {
				cvmx_dprintf("ERROR: cvmx_mgmt_port_initialize: All ports in MIX interface are not configured in same mode.\n \
	Port %d is configured as %d\n \
	And Port %d is configured as %d\n", port, state->mode, i, cvmx_mgmt_port_state_ptr[i].mode);
				return CVMX_MGMT_PORT_INVALID_PARAM;
			}
		}

		/* Create a default MAC address */
		state->mac = 0x000000dead000000ull;
		state->mac += 0xffffff & CAST64(state);

		/* Setup the TX ring */
		for (i = 0; i < CVMX_MGMT_PORT_NUM_TX_BUFFERS; i++) {
			if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
				state->tx_ring[i].cn78xx_tx.len = CVMX_MGMT_PORT_TX_BUFFER_SIZE;
				state->tx_ring[i].cn78xx_tx.addr = cvmx_ptr_to_phys(state->tx_buffers[i]);
			} else {
				state->tx_ring[i].s.len = CVMX_MGMT_PORT_TX_BUFFER_SIZE;
				state->tx_ring[i].s.addr = cvmx_ptr_to_phys(state->tx_buffers[i]);
			}
		}

		/* Tell the HW where the TX ring is */
		oring1.u64 = 0;
		if (OCTEON_IS_MODEL(OCTEON_CN78XX)
		    || OCTEON_IS_MODEL(OCTEON_CN73XX)
		    || OCTEON_IS_MODEL(OCTEON_CNF75XX)) {
			oring1.cn78xx.obase = cvmx_ptr_to_phys(state->tx_ring) >> 3;
			oring1.cn78xx.osize = CVMX_MGMT_PORT_NUM_TX_BUFFERS;
		} else {
			oring1.cn68xx.obase = cvmx_ptr_to_phys(state->tx_ring) >> 3;
			oring1.cn68xx.osize = CVMX_MGMT_PORT_NUM_TX_BUFFERS;
		}
		CVMX_SYNCWS;
		cvmx_write_csr_node(node, CVMX_MIXX_ORING1(port), oring1.u64);

		/* Setup the RX ring */
		for (i = 0; i < CVMX_MGMT_PORT_NUM_RX_BUFFERS; i++) {
			/* This size is -8 due to an errata for CN56XX pass 1 */
			if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
				state->rx_ring[i].cn78xx_rx.len = CVMX_MGMT_PORT_RX_BUFFER_SIZE - 8;
				state->rx_ring[i].cn78xx_rx.addr = cvmx_ptr_to_phys(state->rx_buffers[i]);
			} else {
				state->rx_ring[i].s.len = CVMX_MGMT_PORT_RX_BUFFER_SIZE - 8;
				state->rx_ring[i].s.addr = cvmx_ptr_to_phys(state->rx_buffers[i]);
			}
		}

		/* Tell the HW where the RX ring is */
		iring1.u64 = 0;
		if (OCTEON_IS_MODEL(OCTEON_CN78XX)
		    || OCTEON_IS_MODEL(OCTEON_CN73XX)
		    || OCTEON_IS_MODEL(OCTEON_CNF75XX)) {
			iring1.cn78xx.ibase = cvmx_ptr_to_phys(state->rx_ring) >> 3;
			iring1.cn78xx.isize = CVMX_MGMT_PORT_NUM_RX_BUFFERS;
		} else {
			iring1.cn68xx.ibase = cvmx_ptr_to_phys(state->rx_ring) >> 3;
			iring1.cn68xx.isize = CVMX_MGMT_PORT_NUM_RX_BUFFERS;
		}
		CVMX_SYNCWS;
		cvmx_write_csr_node(node, CVMX_MIXX_IRING1(port), iring1.u64);
		cvmx_write_csr_node(node, CVMX_MIXX_IRING2(port), CVMX_MGMT_PORT_NUM_RX_BUFFERS);

		/* Disable the external input/output */
		cvmx_mgmt_port_disable(port);

		/* Set the MAC address filtering up */
		cvmx_mgmt_port_set_mac(port, state->mac);

		/* Set the default max size to an MTU of 1500 with L2 and VLAN */
		cvmx_mgmt_port_set_max_packet_size(port, 1518);

		/* Enable the port HW. Packets are not allowed until cvmx_mgmt_port_enable() is called */
		mix_ctl.u64 = 0;
		mix_ctl.s.crc_strip = 1;	/* Strip the ending CRC */
		mix_ctl.s.en = 1;	/* Enable the port */
		mix_ctl.s.nbtarb = 0;	/* Arbitration mode */
		mix_ctl.s.mrq_hwm = 1;	/* MII CB-request FIFO programmable high watermark */
		cvmx_write_csr_node(node, CVMX_MIXX_CTL(port), mix_ctl.u64);

		/* Configure BGX */
		if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
			cvmx_bgxx_cmr_global_config_t cmr_global_config;
			int index = (state->port >> 4) & 0xf;
			int interface = ((state->port >> 8) & 0xf) - 8;
			int xiface = cvmx_helper_node_interface_to_xiface(node, interface);
			int xipd_port = cvmx_helper_get_ipd_port(xiface, index);

			/* Clear CMR_MIXx_RESET */
			cmr_global_config.u64 = cvmx_read_csr_node(node,
							CVMX_BGXX_CMR_GLOBAL_CONFIG(interface));
			if (port)
				cmr_global_config.s.cmr_mix1_reset = 0;
			else
				cmr_global_config.s.cmr_mix0_reset = 0;
			cvmx_write_csr_node(node, CVMX_BGXX_CMR_GLOBAL_CONFIG(interface),
				cmr_global_config.u64);

			__cvmx_helper_bgx_port_init(xipd_port, 1);
		}

		/* Select the mode of operation for the interface. */
		if (OCTEON_IS_MODEL(OCTEON_CN6XXX)) {
			agl_prtx_ctl.u64 = cvmx_read_csr(CVMX_AGL_PRTX_CTL(port));

			if (state->mode == CVMX_MGMT_PORT_RGMII_MODE)
				agl_prtx_ctl.s.mode = 0;
			else if (state->mode == CVMX_MGMT_PORT_MII_MODE)
				agl_prtx_ctl.s.mode = 1;
			else {
				cvmx_dprintf("ERROR: cvmx_mgmt_port_initialize: Invalid mode for MIX(%d)\n", port);
				return CVMX_MGMT_PORT_INVALID_PARAM;
			}

			cvmx_write_csr(CVMX_AGL_PRTX_CTL(port), agl_prtx_ctl.u64);
		}

		/* Initialize the physical layer. */
		if (OCTEON_IS_MODEL(OCTEON_CN6XXX)) {
			/* MII clocks counts are based on the 125Mhz reference, so our
			   delays need to be scaled to match the core clock rate. The
			   "+1" is to make sure rounding always waits a little too
			   long. */
			uint64_t clock_scale = cvmx_clock_get_rate(CVMX_CLOCK_CORE) / 125000000 + 1;

			/* Take the DLL and clock tree out of reset */
			agl_prtx_ctl.u64 = cvmx_read_csr(CVMX_AGL_PRTX_CTL(port));
			agl_prtx_ctl.s.clkrst = 0;
			if (state->mode == CVMX_MGMT_PORT_RGMII_MODE)	// RGMII Initialization
			{
				agl_prtx_ctl.s.dllrst = 0;
				agl_prtx_ctl.s.clktx_byp = 0;
			}
			cvmx_write_csr(CVMX_AGL_PRTX_CTL(port), agl_prtx_ctl.u64);
			cvmx_read_csr(CVMX_AGL_PRTX_CTL(port));	/* Force write out before wait */

			/* Wait for the DLL to lock.  External 125 MHz reference clock must be stable at this point. */
			cvmx_wait(256 * clock_scale);

			/* The rest of the config is common between RGMII/MII */

			/* Enable the interface */
			agl_prtx_ctl.u64 = cvmx_read_csr(CVMX_AGL_PRTX_CTL(port));
			agl_prtx_ctl.s.enable = 1;
			cvmx_write_csr(CVMX_AGL_PRTX_CTL(port), agl_prtx_ctl.u64);

			/* Read the value back to force the previous write */
			agl_prtx_ctl.u64 = cvmx_read_csr(CVMX_AGL_PRTX_CTL(port));

			/* Enable the componsation controller */
			agl_prtx_ctl.s.comp = 1;
			agl_prtx_ctl.s.drv_byp = 0;
			cvmx_write_csr(CVMX_AGL_PRTX_CTL(port), agl_prtx_ctl.u64);
			cvmx_read_csr(CVMX_AGL_PRTX_CTL(port));	/* Force write out before wait */
			cvmx_wait(1024 * clock_scale);	// for componsation state to lock.

			/*
			 * If the IFG1/IFG2 fields were wide enough, the workaround
			 * would be to double the programmed AGL_GMX_TX_IFG[IFG2,IFG1]
			 * values. But they aren't.
			 *
			 * Instead, the recommended workaround is to use these values
			 * in 10 or 100 RGMII mode:
			 *    AGL_GM_TX_IFG[IFG1]=14
			 *    AGL_GM_TX_IFG[IFG2]=10
			 *
			 * Some models have 2 mgmt ports, and AGL_GMX_TX_IFG settings
			 * apply to both the ports, applying the workaround to
			 * all 10/100/1000 Mbytes speeds.
			 */
			cvmx_write_csr(CVMX_AGL_GMX_TX_IFG, 0xae);
		} else if (OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X) || OCTEON_IS_MODEL(OCTEON_CN52XX_PASS1_X)) {
			/* Force compensation values, as they are not determined properly by HW */
			cvmx_agl_gmx_drv_ctl_t drv_ctl;

			drv_ctl.u64 = cvmx_read_csr(CVMX_AGL_GMX_DRV_CTL);
			if (port) {
				drv_ctl.s.byp_en1 = 1;
				drv_ctl.s.nctl1 = 6;
				drv_ctl.s.pctl1 = 6;
			} else {
				drv_ctl.s.byp_en = 1;
				drv_ctl.s.nctl = 6;
				drv_ctl.s.pctl = 6;
			}
			cvmx_write_csr(CVMX_AGL_GMX_DRV_CTL, drv_ctl.u64);
		}
	}
	if (!octeon_has_feature(OCTEON_FEATURE_BGX_MIX))
		cvmx_error_enable_group(CVMX_ERROR_GROUP_MGMT_PORT, port);
	return CVMX_MGMT_PORT_SUCCESS;
}

/**
 * Shutdown a management port. This currently disables packet IO
 * but leaves all hardware and buffers. Another application can then
 * call initialize() without redoing the hardware setup.
 *
 * @param port   Management port
 *
 * @return CVMX_MGMT_PORT_SUCCESS or an error code
 */
cvmx_mgmt_port_result_t cvmx_mgmt_port_shutdown(int port)
{
	cvmx_mixx_ctl_t mix_ctl;
	cvmx_mgmt_port_state_t *state;
	int node = 0;

	if ((port < 0) || (port >= __cvmx_mgmt_port_num_ports()))
		return CVMX_MGMT_PORT_INVALID_PARAM;

	if (!octeon_has_feature(OCTEON_FEATURE_BGX_MIX))
		cvmx_error_disable_group(CVMX_ERROR_GROUP_MGMT_PORT, port);

	/* Stop packets from comming in */
	cvmx_mgmt_port_disable(port);
	state = cvmx_mgmt_port_state_ptr + port;

	if (state->port == 0)
		return CVMX_MGMT_PORT_INVALID_PARAM;

	if (cvmx_sysinfo_get()->board_type != CVMX_BOARD_TYPE_SIM)
		node = (state->port >> 12) & 0xf;

	if (cvmx_sysinfo_get()->board_type != CVMX_BOARD_TYPE_SIM) {
		/* Disable and reset MIX port */
		mix_ctl.u64 = cvmx_read_csr_node(node, CVMX_MIXX_CTL(port));
		mix_ctl.s.en = 0;
		cvmx_write_csr_node(node, CVMX_MIXX_CTL(port), mix_ctl.u64);
		do {
			mix_ctl.u64 = cvmx_read_csr_node(node, CVMX_MIXX_CTL(port));
		} while (mix_ctl.s.busy);

		mix_ctl.s.reset = 1;
		cvmx_write_csr_node(node, CVMX_MIXX_CTL(port), mix_ctl.u64);
		cvmx_read_csr_node(node, CVMX_MIXX_CTL(port));
	}

	if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
		cvmx_bgxx_cmr_global_config_t cmr_global_config;
		cvmx_bgxx_cmrx_config_t cmr_config;
		cvmx_bgxx_cmrx_rx_adr_ctl_t rx_adr_ctl;
		int index = (state->port >> 4) & 0xf;
		int interface = ((state->port >> 8) & 0xf) - 8;

		cmr_global_config.u64 = cvmx_read_csr_node(node,
						CVMX_BGXX_CMR_GLOBAL_CONFIG(interface));
		if (port)
			cmr_global_config.s.cmr_mix1_reset = 1;
		else
			cmr_global_config.s.cmr_mix0_reset = 1;
		cvmx_write_csr_node(node, CVMX_BGXX_CMR_GLOBAL_CONFIG(interface),
			cmr_global_config.u64);

		/* Reset MAC filtering, CAM entry */
		cvmx_write_csr_node(node, CVMX_BGXX_CMR_RX_ADRX_CAM(index*8,interface), 0);
		rx_adr_ctl.u64 = 0;
		rx_adr_ctl.s.bcst_accept = 1;
		cvmx_write_csr_node(node, CVMX_BGXX_CMRX_RX_ADR_CTL(index, interface), rx_adr_ctl.u64);

		/* Disable MIX binding */
		cmr_config.u64 = cvmx_read_csr_node(node, CVMX_BGXX_CMRX_CONFIG(index, interface));
		cmr_config.s.data_pkt_tx_en = 0;
		cmr_config.s.data_pkt_rx_en = 0;
		cvmx_write_csr_node(node, CVMX_BGXX_CMRX_CONFIG(index, interface), cmr_config.u64);

		cmr_config.u64 = cvmx_read_csr_node(node, CVMX_BGXX_CMRX_CONFIG(index, interface));
		cmr_config.s.mix_en = 0;
		cvmx_write_csr_node(node, CVMX_BGXX_CMRX_CONFIG(index, interface), cmr_config.u64);
	}

	/* We don't free any memory so the next intialize can reuse the HW setup */
	return CVMX_MGMT_PORT_SUCCESS;
}

/**
 * Enable packet IO on a management port
 *
 * @param port   Management port
 *
 * @return CVMX_MGMT_PORT_SUCCESS or an error code
 */
cvmx_mgmt_port_result_t cvmx_mgmt_port_enable(int port)
{
	cvmx_mgmt_port_state_t *state;

	if ((port < 0) || (port >= __cvmx_mgmt_port_num_ports()))
		return CVMX_MGMT_PORT_INVALID_PARAM;

	state = cvmx_mgmt_port_state_ptr + port;

	cvmx_spinlock_lock(&state->lock);

	if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
		cvmx_bgxx_cmrx_config_t cmr_config;
		int ipd_port = state->port;
		int index = (ipd_port >> 4) & 0xf;
		int interface = ((ipd_port >> 8) & 0xf) - 8;
		int node = (state->port >> 12) & 0xf;

		cmr_config.u64 = cvmx_read_csr_node(node, CVMX_BGXX_CMRX_CONFIG(index, interface));
		cmr_config.s.mix_en = 1;
		cvmx_write_csr_node(node, CVMX_BGXX_CMRX_CONFIG(index, interface), cmr_config.u64);
		cmr_config.u64 = cvmx_read_csr_node(node, CVMX_BGXX_CMRX_CONFIG(index, interface));
		cmr_config.s.enable = 1;
		cmr_config.s.data_pkt_tx_en = 1;
		cmr_config.s.data_pkt_rx_en = 1;
		cvmx_write_csr_node(node, CVMX_BGXX_CMRX_CONFIG(index, interface), cmr_config.u64);

	} else
		cvmx_agl_enable(port);

	/* Configure the port duplex and enables */
	cvmx_mgmt_port_link_set(port, cvmx_mgmt_port_link_get(port));

	cvmx_spinlock_unlock(&state->lock);
	return CVMX_MGMT_PORT_SUCCESS;
}

/**
 * Disable packet IO on a management port
 *
 * @param port   Management port
 *
 * @return CVMX_MGMT_PORT_SUCCESS or an error code
 */
cvmx_mgmt_port_result_t cvmx_mgmt_port_disable(int port)
{
	cvmx_mgmt_port_state_t *state;

	if ((port < 0) || (port >= __cvmx_mgmt_port_num_ports()))
		return CVMX_MGMT_PORT_INVALID_PARAM;

	state = cvmx_mgmt_port_state_ptr + port;
	cvmx_spinlock_lock(&state->lock);

	if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
		cvmx_bgxx_cmrx_config_t cmr_config;
		int ipd_port = state->port;
		int index = (ipd_port >> 4) & 0xf;
		int interface = ((ipd_port >> 8) & 0xf) - 8;
		int node = (state->port >> 12) & 0xf;

		cmr_config.u64 = cvmx_read_csr_node(node, CVMX_BGXX_CMRX_CONFIG(index, interface));
		cmr_config.s.data_pkt_tx_en = 0;
		cmr_config.s.data_pkt_rx_en = 0;
		cvmx_write_csr_node(node, CVMX_BGXX_CMRX_CONFIG(index, interface), cmr_config.u64);
	} else {
		cvmx_agl_gmx_prtx_cfg_t agl_gmx_prtx;
		agl_gmx_prtx.u64 = cvmx_read_csr(CVMX_AGL_GMX_PRTX_CFG(port));
		agl_gmx_prtx.s.en = 0;
		cvmx_write_csr(CVMX_AGL_GMX_PRTX_CFG(port), agl_gmx_prtx.u64);
	}

	cvmx_spinlock_unlock(&state->lock);
	return CVMX_MGMT_PORT_SUCCESS;
}

/**
 * Send a packet out the management port. The packet is copied so
 * the input buffer isn't used after this call.
 *
 * @param port       Management port
 * @param packet_len Length of the packet to send. It does not include the final CRC
 * @param buffer     Packet data
 *
 * @return CVMX_MGMT_PORT_SUCCESS or an error code
 */
cvmx_mgmt_port_result_t cvmx_mgmt_port_send(int port, int packet_len, void *buffer)
{
	cvmx_mgmt_port_state_t *state;
	cvmx_mixx_oring2_t mix_oring2;
	int node = 0;

	if ((port < 0) || (port >= __cvmx_mgmt_port_num_ports()))
		return CVMX_MGMT_PORT_INVALID_PARAM;

	/* Max sure the packet size is valid */
	if ((packet_len < 1) || (packet_len > CVMX_MGMT_PORT_TX_BUFFER_SIZE))
		return CVMX_MGMT_PORT_INVALID_PARAM;

	if (buffer == NULL)
		return CVMX_MGMT_PORT_INVALID_PARAM;

	state = cvmx_mgmt_port_state_ptr + port;
	if (cvmx_sysinfo_get()->board_type != CVMX_BOARD_TYPE_SIM)
		node = (state->port >> 12) & 0xf;

	cvmx_spinlock_lock(&state->lock);

	mix_oring2.u64 = cvmx_read_csr_node(node, CVMX_MIXX_ORING2(port));
	if (mix_oring2.s.odbell >= CVMX_MGMT_PORT_NUM_TX_BUFFERS - 1) {
		/* No room for another packet */
		cvmx_spinlock_unlock(&state->lock);
		return CVMX_MGMT_PORT_NO_MEMORY;
	} else {
		/* Copy the packet into the output buffer */
		memcpy(state->tx_buffers[state->tx_write_index], buffer, packet_len);
		/* Insert the source MAC */
		memcpy(state->tx_buffers[state->tx_write_index] + 6, ((char *)&state->mac) + 2, 6);
		if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
			/* Update the TX ring buffer entry size */
			state->tx_ring[state->tx_write_index].cn78xx_tx.len = packet_len;
			/* This code doesn't support TX timestamps */
			state->tx_ring[state->tx_write_index].cn78xx_tx.tstamp = 0;
		} else {
			/* Update the TX ring buffer entry size */
			state->tx_ring[state->tx_write_index].s.len = packet_len;
			/* This code doesn't support TX timestamps */
			state->tx_ring[state->tx_write_index].s.tstamp = 0;
		}
		/* Increment our TX index */
		state->tx_write_index = (state->tx_write_index + 1) % CVMX_MGMT_PORT_NUM_TX_BUFFERS;
		/* Ring the doorbell, sending the packet */
		CVMX_SYNCWS;
		mix_oring2.u64 = cvmx_read_csr_node(node, CVMX_MIXX_ORING2(port));
		mix_oring2.s.odbell = 1;
		cvmx_write_csr_node(node, CVMX_MIXX_ORING2(port), mix_oring2.u64);
		if (cvmx_read_csr_node(node, CVMX_MIXX_ORCNT(port)))
			cvmx_write_csr_node(node, CVMX_MIXX_ORCNT(port), cvmx_read_csr(CVMX_MIXX_ORCNT(port)));

		cvmx_spinlock_unlock(&state->lock);
		return CVMX_MGMT_PORT_SUCCESS;
	}
}

/**
 * Receive a packet from the management port.
 *
 * @param port       Management port
 * @param buffer_len Size of the buffer to receive the packet into
 * @param buffer     Buffer to receive the packet into
 *
 * @return The size of the packet, or a negative erorr code on failure. Zero
 *         means that no packets were available.
 */
int cvmx_mgmt_port_receive(int port, int buffer_len, void *buffer)
{
	cvmx_mixx_ircnt_t mix_ircnt;
	cvmx_mgmt_port_state_t *state;
	int result;
	int node = 0;

	if ((port < 0) || (port >= __cvmx_mgmt_port_num_ports()))
		return CVMX_MGMT_PORT_INVALID_PARAM;

	/* Max sure the buffer size is valid */
	if (buffer_len < 1)
		return CVMX_MGMT_PORT_INVALID_PARAM;

	if (buffer == NULL)
		return CVMX_MGMT_PORT_INVALID_PARAM;

	state = cvmx_mgmt_port_state_ptr + port;
	if (cvmx_sysinfo_get()->board_type != CVMX_BOARD_TYPE_SIM)
		node = (state->port >> 12) & 0xf;

	cvmx_spinlock_lock(&state->lock);

	/* Find out how many RX packets are pending */
	mix_ircnt.u64 = cvmx_read_csr_node(node, CVMX_MIXX_IRCNT(port));
	if (mix_ircnt.s.ircnt) {
		void *source = state->rx_buffers[state->rx_read_index];
		uint64_t *zero_check = source;
		int code;
		/* CN56XX pass 1 has an errata where packets might start 8 bytes
		   into the buffer instead of at their correct lcoation. If the
		   first 8 bytes is zero we assume this has happened */
		if (OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X) && (*zero_check == 0))
			source += 8;
		/* Start off with zero bytes received */
		result = 0;
		/* While the completion code signals more data, copy the buffers
		   into the user's data */
		if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX))
			code = state->rx_ring[state->rx_read_index].cn78xx_rx.code;
		else
			code = state->rx_ring[state->rx_read_index].s.code;
		while (code == 16) {
			/* Only copy what will fit in the user's buffer */
			int length;
			if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX))
				length = state->rx_ring[state->rx_read_index].cn78xx_rx.len;
			else
				length = state->rx_ring[state->rx_read_index].s.len;
			if (length > buffer_len)
				length = buffer_len;
			memcpy(buffer, source, length);
			/* Reduce the size of the buffer to the remaining space. If we run
			   out we will signal an error when the code 15 buffer doesn't fit */
			buffer += length;
			buffer_len -= length;
			result += length;
			/* Update this buffer for reuse in future receives. This size is
			   -8 due to an errata for CN56XX pass 1 */
			if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
				state->rx_ring[state->rx_read_index].cn78xx_rx.code = 0;
				state->rx_ring[state->rx_read_index].cn78xx_rx.len = CVMX_MGMT_PORT_RX_BUFFER_SIZE;
			} else {
				state->rx_ring[state->rx_read_index].s.code = 0;
				state->rx_ring[state->rx_read_index].s.len = CVMX_MGMT_PORT_RX_BUFFER_SIZE - 8;
			}
			state->rx_read_index = (state->rx_read_index + 1) % CVMX_MGMT_PORT_NUM_RX_BUFFERS;
			/* Zero the beginning of the buffer for use by the errata check */
			*zero_check = 0;
			CVMX_SYNCWS;
			/* Increment the number of RX buffers */
			cvmx_write_csr_node(node, CVMX_MIXX_IRING2(port), 1);
			source = state->rx_buffers[state->rx_read_index];
			zero_check = source;
			if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX))
				code = state->rx_ring[state->rx_read_index].cn78xx_rx.code;
			else
				code = state->rx_ring[state->rx_read_index].s.code;
		}

		if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX))
			code = state->rx_ring[state->rx_read_index].cn78xx_rx.code;
		else
			code = state->rx_ring[state->rx_read_index].s.code;
		/* Check for the final good completion code */
		if (code == 15) {
			int length;

			if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX))
				length = state->rx_ring[state->rx_read_index].cn78xx_rx.len;
			else
				length = state->rx_ring[state->rx_read_index].s.len;
			if (buffer_len >= length) {
				memcpy(buffer, source, length);
				result += length;
			} else {
				/* Not enough room for the packet */
				cvmx_dprintf("ERROR: cvmx_mgmt_port_receive: Packet (%d) larger than supplied buffer (%d)\n", state->rx_ring[state->rx_read_index].s.len,
					     buffer_len);
				result = CVMX_MGMT_PORT_NO_MEMORY;
			}
		} else {
			cvmx_dprintf("ERROR: cvmx_mgmt_port_receive: Receive error code %d. Packet dropped(Len %d), \n",
				     state->rx_ring[state->rx_read_index].s.code, state->rx_ring[state->rx_read_index].s.len + result);
			result = -code;

			/* Check to see if we need to change the duplex. */
			cvmx_mgmt_port_link_set(port, cvmx_mgmt_port_link_get(port));
		}

		/* Clean out the ring buffer entry. This size is -8 due to an errata
		   for CN56XX pass 1 */
		if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
			state->rx_ring[state->rx_read_index].cn78xx_rx.code = 0;
			state->rx_ring[state->rx_read_index].cn78xx_rx.len = CVMX_MGMT_PORT_RX_BUFFER_SIZE;
		} else {
			state->rx_ring[state->rx_read_index].s.code = 0;
			state->rx_ring[state->rx_read_index].s.len = CVMX_MGMT_PORT_RX_BUFFER_SIZE - 8;
		}
		state->rx_read_index = (state->rx_read_index + 1) % CVMX_MGMT_PORT_NUM_RX_BUFFERS;
		/* Zero the beginning of the buffer for use by the errata check */
		*zero_check = 0;
		CVMX_SYNCWS;
		/* Increment the number of RX buffers */
		cvmx_write_csr_node(node, CVMX_MIXX_IRING2(port), 1);
		/* Decrement the pending RX count */
		cvmx_write_csr_node(node, CVMX_MIXX_IRCNT(port), 1);
	} else {
		/* No packets available */
		result = 0;
	}
	cvmx_spinlock_unlock(&state->lock);
	return result;
}

/**
 * Set the MAC address for a management port
 *
 * @param port   Management port
 * @param mac    New MAC address. The lower 6 bytes are used.
 *
 * @return CVMX_MGMT_PORT_SUCCESS or an error code
 */
cvmx_mgmt_port_result_t cvmx_mgmt_port_set_mac(int port, uint64_t mac)
{
	cvmx_mgmt_port_state_t *state;

	if ((port < 0) || (port >= __cvmx_mgmt_port_num_ports()))
		return CVMX_MGMT_PORT_INVALID_PARAM;

	state = cvmx_mgmt_port_state_ptr + port;

	cvmx_spinlock_lock(&state->lock);

	if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX))
		cvmx_helper_bgx_set_mac((state->port), 1, 0, mac);
	else {
		cvmx_agl_gmx_rxx_adr_ctl_t agl_gmx_rxx_adr_ctl;
		agl_gmx_rxx_adr_ctl.u64 = 0;
		agl_gmx_rxx_adr_ctl.s.cam_mode = 1;	/* Only accept matching MAC addresses */
		agl_gmx_rxx_adr_ctl.s.mcst = 0;	/* Drop multicast */
		agl_gmx_rxx_adr_ctl.s.bcst = 1;	/* Allow broadcast */
		cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CTL(port), agl_gmx_rxx_adr_ctl.u64);

		/* Only using one of the CAMs */
		cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM0(port), (mac >> 40) & 0xff);
		cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM1(port), (mac >> 32) & 0xff);
		cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM2(port), (mac >> 24) & 0xff);
		cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM3(port), (mac >> 16) & 0xff);
		cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM4(port), (mac >> 8) & 0xff);
		cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM5(port), (mac >> 0) & 0xff);
		cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM_EN(port), 1);
	}

	state->mac = mac;

	cvmx_spinlock_unlock(&state->lock);
	return CVMX_MGMT_PORT_SUCCESS;
}

/**
 * Get the MAC address for a management port
 *
 * @param port   Management port
 *
 * @return MAC address
 */
uint64_t cvmx_mgmt_port_get_mac(int port)
{
	if ((port < 0) || (port >= __cvmx_mgmt_port_num_ports()))
		return CVMX_MGMT_PORT_INVALID_PARAM;

	return cvmx_mgmt_port_state_ptr[port].mac;
}

/**
 * Set the multicast list.
 *
 * @param port   Management port
 * @param flags  Interface flags
 *
 * @return
 */
void cvmx_mgmt_port_set_multicast_list(int port, int flags)
{
	cvmx_mgmt_port_state_t *state;
	cvmx_agl_gmx_rxx_adr_ctl_t agl_gmx_rxx_adr_ctl;

	if ((port < 0) || (port >= __cvmx_mgmt_port_num_ports()))
		return;

	state = cvmx_mgmt_port_state_ptr + port;

	cvmx_spinlock_lock(&state->lock);

	agl_gmx_rxx_adr_ctl.u64 = cvmx_read_csr(CVMX_AGL_GMX_RXX_ADR_CTL(port));

	/* Allow broadcast MAC addresses */
	if (!agl_gmx_rxx_adr_ctl.s.bcst)
		agl_gmx_rxx_adr_ctl.s.bcst = 1;

	if ((flags & CVMX_IFF_ALLMULTI) || (flags & CVMX_IFF_PROMISC))
		agl_gmx_rxx_adr_ctl.s.mcst = 2;	/* Force accept multicast packets */
	else
		agl_gmx_rxx_adr_ctl.s.mcst = 1;	/* Force reject multicast packets */

	if (flags & CVMX_IFF_PROMISC)
		agl_gmx_rxx_adr_ctl.s.cam_mode = 0;	/* Reject matches if promisc. Since CAM is shut off, should accept everything */
	else
		agl_gmx_rxx_adr_ctl.s.cam_mode = 1;	/* Filter packets based on the CAM */

	cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CTL(port), agl_gmx_rxx_adr_ctl.u64);

	if (flags & CVMX_IFF_PROMISC)
		cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM_EN(port), 0);
	else
		cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM_EN(port), 1);

	cvmx_spinlock_unlock(&state->lock);
}

/**
 * Set the maximum packet allowed in. Size is specified
 * including L2 but without FCS. A normal MTU would corespond
 * to 1514 assuming the standard 14 byte L2 header.
 *
 * @param port   Management port
 * @param size_without_fcs
 *               Size in bytes without FCS
 */
void cvmx_mgmt_port_set_max_packet_size(int port, int size_without_fcs)
{
	cvmx_mgmt_port_state_t *state;

	if ((port < 0) || (port >= __cvmx_mgmt_port_num_ports()))
		return;

	state = cvmx_mgmt_port_state_ptr + port;

	cvmx_spinlock_lock(&state->lock);
	if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
		int index = (state->port >> 4) & 0xf;
		int interface = ((state->port >> 8) & 0xf) - 8;
		int node = (state->port >> 12) & 0xf;
		cvmx_write_csr_node(node, CVMX_BGXX_GMP_GMI_RXX_JABBER(index, interface),
			(size_without_fcs + 4 + 7) & 0xfff8);
	} else {
		cvmx_write_csr(CVMX_AGL_GMX_RXX_FRM_MAX(port), size_without_fcs);
		cvmx_write_csr(CVMX_AGL_GMX_RXX_JABBER(port), (size_without_fcs + 7) & 0xfff8);
	}
	cvmx_spinlock_unlock(&state->lock);
}

/**
 * Return the link state of an RGMII/MII port as returned by
 * auto negotiation. The result of this function may not match
 * Octeon's link config if auto negotiation has changed since
 * the last call to cvmx_mgmt_port_link_set().
 *
 * @param port     The RGMII/MII interface port to query
 *
 * @return Link state
 */
cvmx_helper_link_info_t cvmx_mgmt_port_link_get(int port)
{
	cvmx_mgmt_port_state_t *state;
	cvmx_helper_link_info_t result;

	state = cvmx_mgmt_port_state_ptr + port;
	result.u64 = 0;

	if (port > __cvmx_mgmt_port_num_ports()) {
		cvmx_dprintf("WARNING: Invalid port %d\n", port);
		return result;
	}

	if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
		int xiface = cvmx_helper_get_interface_num(state->port);
		cvmx_helper_interface_mode_t mode;
		mode = cvmx_helper_interface_get_mode(xiface);

		if (mode == CVMX_HELPER_INTERFACE_MODE_SGMII)
			return __cvmx_helper_bgx_sgmii_link_get(state->port);
		else
			return __cvmx_helper_bgx_xaui_link_get(state->port);
	} else
		return cvmx_agl_link_get(state->port);
}

/**
 * Configure RGMII/MII port for the specified link state. This
 * function does not influence auto negotiation at the PHY level.
 *
 * @param port      RGMII/MII interface port
 * @param link_info The new link state
 *
 * @return Zero on success, negative on failure
 */
int cvmx_mgmt_port_link_set(int port, cvmx_helper_link_info_t link_info)
{
	cvmx_mgmt_port_state_t *state;

	state = cvmx_mgmt_port_state_ptr + port;
	if (octeon_has_feature(OCTEON_FEATURE_BGX_MIX)) {
		int xiface = cvmx_helper_get_interface_num(state->port);
		cvmx_helper_interface_mode_t mode;
		mode = cvmx_helper_interface_get_mode(xiface);

		if (mode == CVMX_HELPER_INTERFACE_MODE_SGMII)
			return __cvmx_helper_bgx_sgmii_link_set(state->port, link_info);
		else
			return __cvmx_helper_bgx_xaui_link_set(state->port, link_info);
	} else
		return cvmx_agl_link_set(port, link_info);
}
