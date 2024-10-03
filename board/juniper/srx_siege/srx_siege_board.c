/*
 * Copyright (c) 2007-2015, Juniper Networks, Inc.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <asm/mipsregs.h>
#include <asm/arch/octeon_boot.h>
#include <asm/arch/octeon_board_common.h>
#include <asm/arch/octeon_fdt.h>
#include <asm/arch/lib_octeon_shared.h>
/* added for srx380 */
#include <asm/arch/octeon_qlm.h>
#include <asm/arch/lib_octeon.h>
#include <asm/arch/cvmx-helper-jtag.h>
#include <asm/gpio.h>
#include <asm/arch/cvmx-pcie.h>
#include <asm/arch/cvmx-qlm.h>
#include <asm/arch/cvmx.h>
#include <asm/arch/cvmx-mdio.h>
#include <asm/arch/cvmx-agl.h>
#include <asm/arch/cvmx-agl-defs.h>
#include <i2c.h>
#include <pca953x.h>
#include <watchdog_cpu.h>
#include <spi_flash.h>
#include "../common/juniper_board_common.h"
#include "srx_siege_board.h"
#include <platform_srx_siege.h>
#include <tpm.h>

DECLARE_GLOBAL_DATA_PTR;

/* defined in cmd_sf.c */
extern int spi_flash_update(struct spi_flash *flash, u32 offset,
		size_t len, const char *buf);
int siege_tpm_init(void);
void board_configure_qlms_airbus(void);
extern void cvm_oct_configure_rgmii_speed(struct eth_device *dev);

/* defined in start.S */
extern const char uboot_api_ver_string[];

static struct spi_flash *siege_spi_flash = NULL;
int   ethact_init = 0;

uint16_t board_type_2_memory_type(uint16_t type)
{
    if (IS_PLATFORM_AIRBUS(type)) {
        return I2C_ID_MEMORY_MODEL_AIRBUS;
    } else {
        return I2C_ID_MEMORY_MODEL_SIEGE;
    }
}


int is_valid_board_type(uint16_t type)
{
    return (IS_PLATFORM_SIEGE(type) || IS_PLATFORM_AIRBUS(type));
}

void board_net_preinit(void)
{
	mdelay(120);
}

int board_early_init_f(void)
{
    return 0;
}

/**
 * Modify the device tree to remove all unused interface types.
 */
int siege_board_fixup_fdt(void)
{
    char fdt_key[32];
    enum cvmx_qlm_mode mode;

    mode = cvmx_qlm_get_mode(0);
    switch (mode) {
    case CVMX_QLM_MODE_SGMII_SGMII:
        strcpy(fdt_key, "0,sgmii-sgmii");
        break;
    case CVMX_QLM_MODE_SGMII_QSGMII:
        strcpy(fdt_key, "0,sgmii-qsgmii");
        break;
    case CVMX_QLM_MODE_SGMII_DISABLED:
        strcpy(fdt_key, "0,sgmii-none");
        break;
    case CVMX_QLM_MODE_QSGMII_SGMII:
        strcpy(fdt_key, "0,qsgmii-sgmii");
        break;
    case CVMX_QLM_MODE_QSGMII_QSGMII:
        strcpy(fdt_key, "0,qsgmii-qsgmii");
        break;
    case CVMX_QLM_MODE_RXAUI_1X2:
        strcpy(fdt_key, "0,xaui");
        break;
    case CVMX_QLM_MODE_DISABLED:
        strcpy(fdt_key, "0,none");
        break;
    default:
        strcpy(fdt_key, "0,none");
        break;
    }
    octeon_fdt_patch(working_fdt, fdt_key, NULL);

    mode = cvmx_qlm_get_dlm_mode(2, 0);
    switch (mode) {
    case CVMX_QLM_MODE_SATA_2X1:
        strcpy(fdt_key, "2,sata");
        break;
    default:
        strcpy(fdt_key, "2,none");
    }
    octeon_fdt_patch(working_fdt, fdt_key, NULL);

    return 0;
}

static void kill_fdt_phy(void *fdt, int offset, void *arg)
{
	int len, phy_offset;
	const fdt32_t *php;
	uint32_t phandle;

	php = fdt_getprop(fdt, offset, "phy-handle", &len);
	if (php && len == sizeof(*php)) {
		phandle = fdt32_to_cpu(*php);
		fdt_nop_property(fdt, offset, "phy-handle");
		phy_offset = fdt_node_offset_by_phandle(fdt, phandle);
		if (phy_offset > 0)
			fdt_nop_node(fdt, phy_offset);
	}
}

/*
 * parse_env_var:	Parse the environment variable ("bgx_for_mix%d") to
 *			extract the lmac it is set to.
 *
 *  index:		Index of environment variable to parse.
 *			environment variable.
 *  env_bgx:		Updated with the bgx of the lmac in the environment
 *			variable.
 *  env_lmac:		Updated with the index of lmac in the environment
 *			variable.
 *
 *  returns:		Zero on success, error otherwise.
 */
static int parse_env_var(int index, int *env_bgx, int *env_lmac)
{
	char	env_var[20];
	ulong	xipd_port;

	sprintf(env_var, "bgx_for_mix%d", index);
	if ((xipd_port = getenv_ulong(env_var, 0, 0xffff)) != 0xffff) {
		int xiface;
		struct cvmx_xiface xi;
		struct cvmx_xport xp;

		/*
		 * The environemt variable is set to the xipd port. Convert the
		 * xipd port to numa node, bgx, and lmac.
		 */
		xiface = cvmx_helper_get_interface_num(xipd_port);
		xi = cvmx_helper_xiface_to_node_interface(xiface);
		xp = cvmx_helper_ipd_port_to_xport(xipd_port);
		*env_bgx = xi.interface;
		*env_lmac = cvmx_helper_get_interface_index_num(xp.port);
		return 0;
	}

	return -1;
}

/*
 * get_lmac_fdt_node:	Search the device tree for the node corresponding to
 *			a given bgx lmac.
 *
 *  fdt:		Pointer to flat device tree
 *  search_node:	Numa node of the lmac to search for.
 *  search_bgx:		Bgx of the lmac to search for.
 *  search_lmac:	Lmac index to search for.
 *  compat:		Compatible string to search for.

 *  returns:		The device tree node of the lmac if found,
 *			or -1 otherwise.
 */
static int get_lmac_fdt_node(const void *fdt, int search_node, int search_bgx,
			     int search_lmac, const char *compat)
{
	int		node;
	const fdt32_t	*reg;
	u64		addr;
	int		fdt_node = -1;
	int		fdt_bgx = -1;
	int		fdt_lmac = -1;
	int		len;
	int		parent;

	/* Iterate through all bgx ports */
	node = -1;
	while ((node = fdt_node_offset_by_compatible((void *)fdt, node,
						     compat)) >= 0) {
		/* Get the node and bgx from the physical address */
		if (((parent = fdt_parent_offset(fdt, node)) < 0) ||
		    !(reg = fdt_getprop(fdt, parent, "reg", &len)))
			continue;

		addr = fdt_translate_address((void *)fdt, parent, reg);
		fdt_node = (addr >> 36) & 0x7;
		fdt_bgx = (addr >> 24) & 0xf;

		/* Get the lmac index from the reg property */
		if ((reg = fdt_getprop(fdt, node, "reg", &len)))
			fdt_lmac = *reg;

		/* Check for a match */
		if (search_node == fdt_node && search_bgx == fdt_bgx &&
		    search_lmac == fdt_lmac)
			return node;
	}

	return -1;
}

/*
 * get_mix_fdt_node:	Search the device tree for the node corresponding to
 *			a given mix.
 *
 *  fdt:		Pointer to flat device tree
 *  search_node:	Mix numa node to search for.
 *  search_index:	Mix index to search for.
 *
 *  returns:		The device tree node of the lmac if found,
 *			or -1 otherwise.
 */
static int get_mix_fdt_node(const void *fdt, int search_node, int search_index)
{
	int		node;

	/* Iterate through all the mix fdt nodes */
	node = -1;
	while ((node = fdt_node_offset_by_compatible((void *)fdt, node,
					"cavium,octeon-7890-mix")) >= 0) {
		int		parent;
		int		len;
		const char	*name;
		int		mix_numa_node;
		const fdt32_t	*reg;
		int		mix_index = -1;
		u64		addr;

		/* Get the numa node of the mix from the parent node name */
		if (((parent = fdt_parent_offset(fdt, node)) < 0) ||
		    ((name = fdt_get_name(fdt, parent, &len)) == NULL) ||
		    ((name = strchr(name, '@')) == NULL))
			continue;

		name++;
		mix_numa_node = simple_strtol(name, NULL, 0) ? 1 : 0;

		/* Get the mix index from the reg property */
		if ((reg = fdt_getprop(fdt, node, "reg", &len))) {
			addr = fdt_translate_address((void *)fdt, parent, reg);
			mix_index = (addr >> 11) & 1;
		}

		/* Check for a match */
		if (mix_numa_node == search_node && mix_index == search_index)
			return node;
	}

	return -1;
}

/*
 * fdt_fix_mix:		Fix the mix nodes in the device tree. Only the mix nodes
 *			configured by the user will be preserved. All other mix
 *			nodes will be trimmed.
 *
 *  fdt:		Pointer to flat device tree
 *
 *  returns:		Zero on success, error otherwise.
 */
#define MAX_MIX_ENV_VARS 4
static int fdt_fix_mix(const void *fdt)
{
	int	node;
	int	next_node;
	int	len;
	int	i;

	/* Parse all the mix port environment variables */
	for (i = 0; i < MAX_MIX_ENV_VARS; i++) {
		int	env_node = 0;
		int	env_bgx = -1;
		int	env_lmac = -1;
		int	lmac_fdt_node = -1;
		int	mix_fdt_node = -1;
		int	lmac_phandle;
		char	*compat;

		/* Get the lmac for this environment variable */
		if (parse_env_var(i, &env_bgx, &env_lmac))
			continue;

		/* Get the fdt node for this lmac and add a phandle to it */
		compat = "cavium,octeon-7890-bgx-port";
		if ((lmac_fdt_node = get_lmac_fdt_node(fdt, env_node, env_bgx,
						       env_lmac, compat)) < 0) {
			/* Must check for the xcv compatible string too */
			compat = "cavium,octeon-7360-xcv";
			if ((lmac_fdt_node = get_lmac_fdt_node(fdt, env_node,
							       env_bgx,
							       env_lmac,
							       compat)) < 0) {
				printf("WARNING: Failed to get lmac fdt node "
				       "for %d%d%d\n", env_node, env_bgx,
				       env_lmac);
			continue;
			}
		}

		lmac_phandle = fdt_alloc_phandle((void *)fdt);
		fdt_set_phandle((void *)fdt, lmac_fdt_node, lmac_phandle);

		/* Get the fdt mix node corresponding to this lmac */
		if ((mix_fdt_node = get_mix_fdt_node(fdt, env_node,
						     env_lmac)) < 0)
			continue;

		/* Point the mix to the lmac */
		fdt_getprop(fdt, mix_fdt_node, "cavium,mac-handle", &len);
		fdt_setprop_inplace((void *)fdt, mix_fdt_node,
				    "cavium,mac-handle", &lmac_phandle, len);
	}

	/* Trim unused mix'es from the device tree */
	for (node = fdt_next_node(fdt, -1, NULL); node >= 0;
	     node = next_node) {
		const char	*compat;
		const fdt32_t	*reg;

		next_node = fdt_next_node(fdt, node, NULL);

		if ((compat = fdt_getprop(fdt, node, "compatible", &len))) {
			if (strcmp(compat, "cavium,octeon-7890-mix"))
				continue;

			if ((reg = fdt_getprop(fdt, node,
					       "cavium,mac-handle", &len))) {
				if (*reg == 0xffff)
					fdt_nop_node((void *)fdt, node);
			}
		}
	}

	return 0;
}

int no_phy[8] = {0, 0, 0, 0, 0, 0, 0, 0};
void airbus_fixup_xcv(void)
{
	unsigned long bgx = getenv_ulong("bgx_for_rgmii", 10, (unsigned long)-1);
	char fdt_key[16];
	int i;

	debug("%s: BGX %d\n", __func__, (int)bgx);

	for (i = 0; i < 3; i++) {
		snprintf(fdt_key, sizeof(fdt_key),
			 bgx == i ? "%d,xcv" : "%d,not-xcv", i);
		debug("%s: trimming bgx %lu with key %s\n",
		      __func__, bgx, fdt_key);

		octeon_fdt_patch_rename((void *)gd->fdt_blob, fdt_key,
					"cavium,xcv-trim", true, NULL, NULL);
	}
}

/* QLM0 - QLM6 */
void airbus_fixup_fdt(void)
{
	int qlm;
	int speed = 0;

	for (qlm = 0; qlm < 7; qlm++) {
		enum cvmx_qlm_mode mode;
		char fdt_key[16];
		const char *type_str = "none";
		mode = cvmx_qlm_get_mode(qlm);
		switch (mode) {
		case CVMX_QLM_MODE_SGMII:
		case CVMX_QLM_MODE_RGMII_SGMII:
		case CVMX_QLM_MODE_RGMII_SGMII_1X1:
			type_str = "sgmii";
			break;
		case CVMX_QLM_MODE_XAUI:
		case CVMX_QLM_MODE_RGMII_XAUI:
			speed = (cvmx_qlm_get_gbaud_mhz(qlm) * 8 / 10) * 4;
			if (speed == 10000)
				type_str = "xaui";
			else
				type_str = "dxaui";
			break;
		case CVMX_QLM_MODE_RXAUI:
		case CVMX_QLM_MODE_RGMII_RXAUI:
			type_str = "rxaui";
			break;
		case CVMX_QLM_MODE_XLAUI:
		case CVMX_QLM_MODE_RGMII_XLAUI:
			type_str = "xlaui";
			break;
		case CVMX_QLM_MODE_XFI:
		case CVMX_QLM_MODE_RGMII_XFI:
		case CVMX_QLM_MODE_RGMII_XFI_1X1:
			type_str = "xfi";
			break;
		case CVMX_QLM_MODE_10G_KR:
		case CVMX_QLM_MODE_RGMII_10G_KR:
			type_str = "10G_KR";
			break;
		case CVMX_QLM_MODE_40G_KR4:
		case CVMX_QLM_MODE_RGMII_40G_KR4:
			type_str = "40G_KR4";
			break;
		case CVMX_QLM_MODE_SATA_2X1:
			type_str = "sata";
			break;
		case CVMX_QLM_MODE_SGMII_2X1:
		case CVMX_QLM_MODE_XFI_1X2:
		case CVMX_QLM_MODE_10G_KR_1X2:
		case CVMX_QLM_MODE_RXAUI_1X2:
		case CVMX_QLM_MODE_MIXED: // special for DLM5 & DLM6
		{
			cvmx_bgxx_cmrx_config_t cmr_config;
			cvmx_bgxx_spux_br_pmd_control_t pmd_control;
			int mux = cvmx_qlm_mux_interface(2);
			if (mux == 2) {   // only dlm6
				cmr_config.u64 = cvmx_read_csr(
						CVMX_BGXX_CMRX_CONFIG(2, 2));
				pmd_control.u64 = cvmx_read_csr(
						CVMX_BGXX_SPUX_BR_PMD_CONTROL(2, 2));
			} else {
				if (qlm == 5) {
					cmr_config.u64 = cvmx_read_csr(
							CVMX_BGXX_CMRX_CONFIG(0, 2));
					pmd_control.u64 = cvmx_read_csr(
							CVMX_BGXX_SPUX_BR_PMD_CONTROL(0, 2));
				} else {
					cmr_config.u64 = cvmx_read_csr(
							CVMX_BGXX_CMRX_CONFIG(2, 2));
					pmd_control.u64 = cvmx_read_csr(
							CVMX_BGXX_SPUX_BR_PMD_CONTROL(2, 2));
				}
			}
			switch (cmr_config.s.lmac_type) {
			case 0:
				type_str = "sgmii";
				break;
			case 1:
				type_str = "xaui";
				break;
			case 2:
				type_str = "rxaui";
				break;
			case 3:
				if (pmd_control.s.train_en)
					type_str = "10G_KR";
				else
					type_str = "xfi";
				break;
			case 4:
				if (pmd_control.s.train_en)
					type_str = "40G_KR4";
				else
					type_str = "xlaui";
				break;
			default:
				type_str = "none";
				break;
			}
			break;
		}
		default:
			type_str = "none";
			break;
		}
		sprintf(fdt_key, "%d,%s", qlm, type_str);
		debug("Patching qlm %d for %s for mode %d%s\n",
		      qlm, fdt_key, mode, no_phy[qlm] ? ", removing PHY" : "");
		octeon_fdt_patch_rename((void *)gd->fdt_blob, fdt_key, NULL,
					true, no_phy[qlm] ? kill_fdt_phy : NULL, NULL);
	}
}

int board_fixup_fdt(void)
{
    switch (gd->arch.board_desc.board_type) {
    CASE_ALL_JSRX_SIEGE_MODELS 
        siege_board_fixup_fdt();
        return 0;
    default:
        break;
    }
    /* for airbus */
	airbus_fixup_fdt();
	airbus_fixup_xcv();

	/* Fix the mix ports */
	fdt_fix_mix(gd->fdt_blob);

	return 0;
}

static void
board_configure_qlms_siege(void)
{
    /* Turn on USB ports */
    gpio_direction_output(1, 1);
    /* Overcurrent flag */
    gpio_direction_input(3);

    /* Take PHYs out of reset */
    gpio_direction_output(9, 1);
    mdelay(10);

    /* Configure QLMs */
    /* JUNIPER start */
    switch (gd->arch.board_desc.board_type) {
    CASE_ALL_JSRX_SWORD_MODELS
        octeon_configure_qlm(0, 2500, CVMX_QLM_MODE_SGMII_SGMII, 0, 0, 0, 1);
        octeon_configure_qlm(1, 5000, CVMX_QLM_MODE_PCIE_2X1, 1, 1, 1, 1);
        /* change input = 1, they use it at new sdk, instead of clk_sel,
         * because cvmx_write_csr(CVMX_GSERX_DLMX_REFCLK_SEL(qlm, 0), ref_clk_input);
         * */
        octeon_configure_qlm(2, 5000, CVMX_QLM_MODE_SATA_2X1, 1, 0, 0, 1);
        break;

    CASE_ALL_JSRX_TRIDENT_MODELS
        octeon_configure_qlm(0, 3125, CVMX_QLM_MODE_RXAUI, 0 ,0, 2, 2);
        octeon_configure_qlm(1, 5000, CVMX_QLM_MODE_PCIE_2X1, 1, 1, 1, 1);
        /* change input = 1, they use it at new sdk, instead of clk_sel,
         * because cvmx_write_csr(CVMX_GSERX_DLMX_REFCLK_SEL(qlm, 0), ref_clk_input);
         * */
        octeon_configure_qlm(2, 5000, CVMX_QLM_MODE_SATA_2X1, 1, 0, 0, 1);
        break;

    default:
        break;
    }
}

void board_configure_qlms(void)
{
    switch (gd->arch.board_desc.board_type) {
    CASE_ALL_JSRX_SWORD_MODELS
    CASE_ALL_JSRX_TRIDENT_MODELS
        board_configure_qlms_siege();
        break;

    CASE_ALL_JSRX_AIRBUS_MODELS
        board_configure_qlms_airbus();
        break;

    default:
        break;
    }
}

int checkboard(void)
{
    return 0;
}

int early_board_init(void)
{
    int cpu_ref = DEFAULT_CPU_REF_FREQUENCY_MHZ;
    uint32_t cpu_id;


    /* JUNIPER */
    cpu_id = cvmx_get_proc_id();

    /* Turn off power to USB ports */
    if ((cpu_id & 0xff00) == 0x9600) {
        gpio_direction_output(2, 0);
        gpio_direction_output(3, 0);
    }

    if ((cpu_id & 0xff00) == 0x9600) {
        if (cvmx_read_csr(CVMX_MIO_FUS_PDF) & (0x1ULL << 32)) { /* 71 family */
            octeon_board_get_descriptor(I2C_ID_JSRXNLE_SRX340_CHASSIS, 1, 0);
        } else {  /* 70 family */
            octeon_board_get_descriptor(I2C_ID_JSRXNLE_SRX300_CHASSIS, 1, 0);
        }
        /* Populate global data from eeprom */
        octeon_board_get_clock_info(SRX_SIEGE_DEF_DRAM_FREQ);
        gd->arch.ddr_ref_hertz = (DEFAULT_CPU_REF_FREQUENCY_MHZ * 1000 * 1000ull);

    } else if ((cpu_id & 0xff00) == 0x9700) { /* 0x97 = CN73XX */
        octeon_board_get_descriptor(I2C_ID_JSRXNLE_SRX380_POE_AC_CHASSIS, 1, 0);
        /* Populate global data from eeprom */
        octeon_board_get_clock_info(SRX_AIRBUS_DEF_DRAM_FREQ);
    } else {
        octeon_board_get_descriptor(I2C_ID_JSRXNLE_SRX300_CHASSIS, 1, 0);
        /* Populate global data from eeprom */
        octeon_board_get_clock_info(SRX_SIEGE_DEF_DRAM_FREQ);
    }

    /* Even though the CPU ref freq is stored in the clock descriptor, we
     * don't read it here.  The MCU reads it and configures the clock, and
     * we read how the clock is actually configured.
     * The bootloader does not need to read the clock descriptor tuple for
     * normal operation on rev 2 and later boards.
     */
    octeon_board_get_mac_addr();

    if ((cpu_id & 0xff00) == 0x9600) {
        /* Read CPU clock multiplier */
        gd->cpu_clk = octeon_get_cpu_multiplier() * cpu_ref * 1000000;
    }

    /* bootbus init early than this */
    cpld_board_reset();

    /* stage3 in memory 0x1000000 (by stage2 bootstage3) now */
    /* switch_spi to primary to access env loader ushell */
    cpld_switch_spi(0);

    cpld_set_led_status_amber();

	return 0;
}

void board_net_postinit(void)
{
	/*
     * Try to initialize networking so Vitesse PHYs work for user
	 * programs.
	 */
	eth_init(gd->bd);
}


void srx_siege_boot_bus_init(void)
{
    cvmx_mio_boot_reg_cfgx_t reg_cfg;

    /* Setup region 1 for CPLD */
    reg_cfg.u64 = 0;
    reg_cfg.s.en = 1;
    reg_cfg.s.ale = 1;

    /* Mask to put physical address in boot bus window */
    reg_cfg.s.base = ((SIEGE_LOCAL_BUS_REGION_1_BASE >> 16) & 0x1fff);

    cvmx_write_csr(CVMX_MIO_BOOT_REG_CFGX(1), reg_cfg.u64);
}

void srx_airbus_boot_bus_init(void)
{
    /*
     *  cvmx_mio_boot_reg_cfgx_t reg_cfg;
     *  cvmx_mio_boot_reg_timx_t reg_tim;
     */
    uint8_t node = cvmx_get_node_num();

    /*
     * write64 0x1180000000040 0xc3fc0103105142
     * write64 0x1180000000048 0xfd7fc400020d041
     * write64 0x1180000000050 0xfffffffffffffff
     * write64 0x1180000000058 0xfffffffffffffff
     * write64 0x1180000000060 0xfffffffffffffff
     * write64 0x1180000000068 0xfffffffffffffff
     * write64 0x1180000000070 0xfffffffffffffff
     * write64 0x1180000000078 0xfffffffffffffff
     */
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_TIMX(0), 0x0c3fc0103105142);
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_TIMX(1), 0xfd7fc400020d041);
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_TIMX(2), 0xfffffffffffffff);
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_TIMX(3), 0xfffffffffffffff);
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_TIMX(4), 0xfffffffffffffff);
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_TIMX(5), 0xfffffffffffffff);
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_TIMX(6), 0xfffffffffffffff);
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_TIMX(7), 0xfffffffffffffff);

#if 0

    /*
     * write64 0x1180000000000 0x300a0bf1f40
     * write64 0x1180000000008 0x3e0a0001d02
     * write64 0x1180000000010 0x300a0001d04
     * write64 0x1180000000018 0x300a0001d05
     * write64 0x1180000000020 0x300a0001d03
     * write64 0x1180000000028 0x300a0001d06
     * write64 0x1180000000030 0x30020000000
     * write64 0x1180000000038 0x30020000000
     */
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_CFGX(0), 0x0300a0bf1f40);
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_CFGX(1), 0x03e0a0001d02);
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_CFGX(2), 0x0300a0001d04);
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_CFGX(3), 0x0300a0001d05);
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_CFGX(4), 0x0300a0001d03);
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_CFGX(5), 0x0300a0001d06);
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_CFGX(6), 0x030020000000);
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_REG_CFGX(7), 0x030020000000);
    /*
     * write64 0x11800000000b8 0x404
     */
    cvmx_write_csr_node(node, CVMX_MIO_BOOT_COMP,        0x000000000404);
#endif

    cvmx_mio_boot_reg_cfgx_t reg_cfg;

    /* Setup region 1 for CPLD */
    reg_cfg.u64 = 0;
    reg_cfg.s.en = 1;
    reg_cfg.s.ale = 1;

    /* Mask to put physical address in boot bus window */
    reg_cfg.s.base = ((SIEGE_LOCAL_BUS_REGION_1_BASE >> 16) & 0x1fff);

    cvmx_write_csr(CVMX_MIO_BOOT_REG_CFGX(1), reg_cfg.u64);
}



static struct spi_flash *
board_get_spi_flash (void)
{
    unsigned int bus = CONFIG_SF_DEFAULT_BUS;
    unsigned int cs = CONFIG_SF_DEFAULT_CS;
    unsigned int speed = CONFIG_SF_DEFAULT_SPEED;
    unsigned int mode = CONFIG_SF_DEFAULT_MODE;

    if (siege_spi_flash) return siege_spi_flash;

    siege_spi_flash = spi_flash_probe(bus, cs,
            speed, mode);
    if (!siege_spi_flash) {
        printf("\nWARNING: spi probe failed.\n");
        return NULL;
    }
    return siege_spi_flash;
}

/* common tool functions */
int
board_spi_flash_read(u32 offset,
                     size_t len,
                     void *buf,
                     uint32_t is_backup)
{
    struct spi_flash *flash = board_get_spi_flash();
    if (!flash)
        return -1;

    cpld_switch_spi(is_backup);
    return spi_flash_read(flash, offset, len, buf);
}

int
board_spi_flash_write (uint32_t mem_addr,
        uint32_t flash_start,
        uint32_t size,
        uint32_t is_backup)
{
    struct spi_flash *flash = board_get_spi_flash();
    if (!flash)
        return -1;

    cpld_switch_spi(is_backup);

    if (spi_flash_write(flash, flash_start,
                size, (void *)mem_addr)) {
        printf("Writing to flash failed\n");
        return -1;
    }

    return 0;
}

int
board_spi_flash_erase (uint32_t flash_start,
                        uint32_t size,
                        uint32_t is_backup)
{
    struct spi_flash *flash = board_get_spi_flash();
    if (!flash)
        return -1;

    cpld_switch_spi(is_backup);

    if (spi_flash_erase(flash, flash_start, size)) {
        printf("erase flash failed\n");
        return -1;
    }

    return 0;
}

int
board_spi_flash_update (uint32_t offset,
                        uint32_t len,
                        const char *buf,
                        uint32_t is_backup)
{
    struct spi_flash *flash = board_get_spi_flash();
    if (!flash)
        return -1;

    cpld_switch_spi(is_backup);

    return spi_flash_update(flash, offset, len, buf);
}

void
boot_variables_setup()
{
    char temp[64];
    setenv("boot.ver", uboot_api_ver_string);

    /* the boot flash offsets are 32bit values */
    sprintf(temp, "0x%08x ", CFG_SPI_FLASH_USHELL_START);
    setenv("boot.upgrade.ushell", temp);
    sprintf(temp, "0x%08x ", CFG_SPI_FLASH_LOADER_P1_START);
    setenv("boot.upgrade.loader_p1", temp);

    sprintf(temp, "0x%08x ", CFG_SPI_FLASH_LOADER_P2_START);
    setenv("boot.upgrade.loader_p2", temp);

    sprintf(temp, "0x%08x ", CFG_SPI_FLASH_UBOOT_START);
    setenv("boot.upgrade.uboot", temp);

    sprintf(temp, "0x%08x ", CFG_SPI_FLASH_UBOOT_START);
    setenv("boot.upgrade.uboot.secondary", temp);

    sprintf(temp, "0x%08x ", CONFIG_ENV_OFFSET);
    setenv("boot.env.start", temp);

    sprintf(temp, "0x%08x ", CFG_UBOOT_SIZE);
    setenv("boot.upgrade.uboot.maxsize", temp);

    sprintf(temp, "0x%08x ", CONFIG_BOOTSEQ_OFFSET);
    setenv("boot.btsq.start", temp);

    sprintf(temp, "0x%08x ", CONFIG_BOOTSEQ_SECT_SIZE);
    setenv("boot.btsq.len", temp);

    /* loader use this */
    setenv("disk.install", "disk1");

    if ((getenv("loaddev")) == NULL) {
        sprintf(temp, "%s ", "disk0:");
        setenv("loaddev", temp);
    }

    sprintf(temp, "0x%08x", CONFIG_ENV_SIZE);
    setenv("boot.env.size", temp);

    /*
     * Offsets of CRC header and the data on which
     * CRC is calculated.
     */
    sprintf(temp, "0x%08x ", IMG_HEADER_OFFSET);
    setenv("boot.upgrade.uboot.hdr", temp);

    sprintf(temp, "0x%08x ", IMG_DATA_OFFSET);
    setenv("boot.upgrade.uboot.data", temp);

    sprintf(temp, "0x%08x ", CFG_LOADER_HDR_OFFSET);
    setenv("boot.upgrade.loader.hdr", temp);

    sprintf(temp, "0x%08x ", CFG_LOADER_DATA_OFFSET);
    setenv("boot.upgrade.loader.data", temp);

    sprintf(temp, "0x%08x", gd->arch.board_desc.board_type);
    setenv("board_id", temp);

    setenv("rootpath", "/");

    /*
     * If bootcmd is not present in env, set to default
     * otherwise, system will stop at u-boot prompt.
     */
    setenv("bootcmd", "sf probe; sf read 0x100000 0x200000 0xfffc0; \
sf read 0x1fffc0 0x400000 0x100000; bootelf 0x100000");

    if (IS_PLATFORM_AIRBUS(gd->arch.board_desc.board_type)) {
        setenv("bgx_for_rgmii", "2");
    }

    /*
     * Initialize the bootsequencing code after
     * all variables are defined
     */
    srx_siege_bootseq_init();
}

void
late_ethsetup (void)
{
    char* s;
	union cvmx_agl_prtx_ctl agl_prtx_ctl;

    switch (gd->arch.board_desc.board_type)
    {
        CASE_ALL_JSRX_SWORD_MODELS
            setenv("ethact","octeth0");
            break;
        CASE_ALL_JSRX_TRIDENT_MODELS
            /* configure trident rgmii phy bcm54616s, phy addr 0x1 */
            cvmx_mdio_write(0, 1, 0x1c, 0xb4ae);  /* led2 ,left, stand for muticolor2 */
            cvmx_mdio_write(0, 1, 0x1c, 0xb8ea);  /* led3 ,right, stand for muticolor1 */
            cvmx_mdio_write(0, 1, 0x17, 0x0f04);  /* access the expand reg4 */
            cvmx_mdio_write(0, 1, 0x15, 0x0189);  /* muticolor2,link, muticolor1, activity led */
            cvmx_mdio_write(0, 1, 0x1c, 0x8e00);  /* enable GTX CLK/delay at phy */

            cvmx_mdio_write(0, 1, 0x18, 0xf0e7);  /* PHY Tx: delay, Rx: bypass*/

            agl_prtx_ctl.u64 = cvmx_read_csr(CVMX_AGL_PRTX_CTL(0));
            agl_prtx_ctl.s.clkrst = 0;
            agl_prtx_ctl.s.dllrst = 0;

            agl_prtx_ctl.s.refclk_sel = 0;
            agl_prtx_ctl.s.clkrx_set = 0;

            agl_prtx_ctl.s.clktx_byp = 1;
            agl_prtx_ctl.s.clkrx_byp = 0;

            cvmx_write_csr(CVMX_AGL_PRTX_CTL(0), agl_prtx_ctl.u64);

            setenv("ethact","octrgmii0");
            break;

        CASE_ALL_JSRX_AIRBUS_MODELS
#if 0 
            /* configure rx bypass at phy */
            cvmx_mdio_write(0, 1, 0x1c, 0xb4ae);  /* led2 ,left, stand for muticolor2 */
            cvmx_mdio_write(0, 1, 0x1c, 0xb8ea);  /* led3 ,right, stand for muticolor1 */
            cvmx_mdio_write(0, 1, 0x17, 0x0f04);  /* access the expand reg4 */
            cvmx_mdio_write(0, 1, 0x15, 0x0189);  /* muticolor2,link, muticolor1, activity led */
            cvmx_mdio_write(0, 1, 0x1c, 0x8e00);  /* enable GTX CLK/delay at phy */

            cvmx_mdio_write(0, 1, 0x18, 0xf0e7);  /* PHY Tx: delay, Rx: bypass*/
#endif

            setenv("ethact","octrgmii0");
            break;

        default:
            return;
    }

    /*
     * if disable ushell is set, means debug ushell,
     * need to initialize eth manually
     */
    if ((s = getenv("disable_ushell")) != NULL
            && (*s != '0')) {
        uart_debug("##### disable ushell by env \n");
        return;
    }

    ethact_init = 1;
#ifdef CONFIG_NET_MULTI
    eth_set_current();

    if (IS_PLATFORM_AIRBUS(gd->arch.board_desc.board_type)) {
        cvm_oct_configure_rgmii_speed(eth_current);
    }
#endif
    return;
}

int recover_primary(void)
{
    int ret;
    void *buf = CONFIG_BOOT_IMAGE_VERIFY_ADDR;

    if (board_spi_flash_read(CFG_SPI_FLASH_UBOOT_START,
                CFG_UBOOT_SIZE, buf, 1)) {
        printf("Could not read SPI flash to find uboot\n");
        return -1;
    }

    ret = board_spi_flash_update(CFG_SPI_FLASH_UBOOT_START,
            CFG_UBOOT_SIZE, buf, 0);

    return ret;
}

int early_board_init_r(void)
{
    switch (gd->arch.board_desc.board_type) {
    CASE_ALL_JSRX_AIRBUS_MODELS
        setenv( "qlm2_mode", "xaui");
        setenv( "qlm3_mode", "xaui");
        setenv( "qlm4_mode", "sata");
        setenv( "qlm5_mode", "pcie");
        setenv( "qlm6_mode", "sgmii");
        setenv( "pcie5_mode", "rc");
        setenv( "pcie5_gen", "1");
        setenv( "pcie5_lanes", "2");
        setenv( "bgx_for_rgmii", "2");
        setenv( "bgx_for_mix0", "0xa00");

        break;
    default:
        break;
    }
	return 0;
}

int
late_board_init (void)
{
    int res = 0;

    boot_variables_setup();
    /* setboot finish will clear the bootsector flag */

    if (cpld_is_boot_from_backup()) {
        cpld_set_bootfinish();
        printf("WARNING: Running from backup u-boot\n");
        setenv("boot.current", "secondary");
        res = recover_primary();
        if (res < 0) {
            printf("WARNING: Failed to auto-recover primary U-Boot.\n"
                    "Please recover it manually as soon as possible.\n");
        } else if (res == 0) {
            printf("Recovered primary U-Boot from secondary, please upgrade it"
                    " to the latest version.\n");
        }
    } else {
        setenv("boot.current", "primary");
    }

    late_ethsetup();
    cpld_usb_enable();

    RELOAD_WATCHDOG(ENABLE_WATCHDOG);

    cpld_set_fan_speed(50);

    /* switch to primary spi-flash to read loader */
    cpld_switch_spi(0);
    siege_tpm_init();
    cpld_set_bootfinish();
    /* need to enable usb before check MBR at eUSB */
    usb_disk_scan(0);

	return 0;
}

/* we can have only 3 major revision digits */
#define IS_VALID_VERSION_STRING(str) (str[1] == '.' \
                      || str[2] == '.'  \
                      || str[3] == '.' ? 1 : 0)

#define MAX_VERSION_STR_LEN 7

uint32_t
get_uboot_version (void)
{
    uint32_t idx = 0;
    int8_t mjr_digits[4];
    uint32_t major = 0, minor = 0;

    char *ver_string = uboot_api_ver_string;

    if (!IS_VALID_VERSION_STRING(ver_string)) {
        return 0;
    }

    for (idx = 0; idx < MAX_VERSION_STR_LEN; idx++) {
        if (ver_string[idx] == '.') {
            mjr_digits[idx] = '\0';
            break;
        }
        mjr_digits[idx] = ver_string[idx];
    }

    idx++;

    major = simple_strtoul(mjr_digits, NULL, 10);
    minor = simple_strtoul(&ver_string[idx], NULL, 10);

    if (major >= 0 && major <= 255
            && minor >= 0 && minor <= 255) {
        return ((major << 16) | minor);
    }

    return 0;
}

/*
 * Board specific interface probe func
 * interface index and types for Octeon:
 * 0: (RXAUI/sgmii/etc)
 * 2: (NPI)
 * 3: (LOOP)
 * 4: (AGL)
*/
int
__cvmx_helper_board_interface_probe(int x_interface, int supported_ports)
{
    struct cvmx_xiface xi = cvmx_helper_xiface_to_node_interface(x_interface);
    int iface = xi.interface;
    int rc = 0;

    switch (gd->arch.board_desc.board_type) {
    CASE_ALL_JSRX_SWORD_MODELS
        if (iface == 0)
            rc = 1;
        break;

    CASE_ALL_JSRX_TRIDENT_MODELS
        if (iface == 4)
            rc = 1;
        break;

    CASE_ALL_JSRX_AIRBUS_MODELS
        /*  (interface)0->QLM2, 1->QLM3, 2->DLM5 && DLM6 */
        if (iface == 2)
            rc = 1;
        break;

    default:
        break;
    }

    mark_debug("%s, interface 0x%x, iface %d, supported_ports %d, rc %d \r\n",
               __func__, x_interface, iface, supported_ports, rc);

    return rc;
}



void board_configure_qlms_airbus(void)
{
	int qlm;
	char env_var[16];
	int speed[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int mode[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
	int pcie_rc[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int pcie_gen[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int ref_clock_sel[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int ref_clock_input[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int rbgx, rqlm;

	octeon_init_qlm(0);

	gpio_direction_output(27, 0);	/* Put RGMII PHY in reset */

#if defined(CONFIG_OCTEON_MCU_PROBE) && defined(BOARD_MCU_TWSI_ADDR)
	if (octeon_mcu_probe(0) != -1) {
		return 0;
	}
#endif
	rbgx = 2; /*getenv_ulong("bgx_for_rgmii", 10, (unsigned long)-1);*/
	switch(rbgx) {
	case 0:
		rqlm = 2;
		break;
	case 1:
		rqlm = 3;
		break;
	case 2:
		rqlm = 5;
		break;
	default:
		rqlm = -1;
		break;
	}

	for (qlm = 0; qlm < 7; qlm++) {
		const char *mode_str;
		char spd_env[16];

		mode[qlm] = CVMX_QLM_MODE_DISABLED;
		sprintf(env_var, "qlm%d_mode", qlm);

        if (qlm == 6) {
            mode_str = "sgmii";
        } else {
            mode_str = getenv(env_var);
        }
		if (!mode_str)
			continue;

		if (qlm == 4 &&
		    mode[4] != -1 &&
		    mode[4] != CVMX_QLM_MODE_SATA_2X1) {
			printf("Error: DLM 4 can only be configured for SATA\n");
			continue;
		}

		if (strstr(mode_str, ",no_phy"))
			no_phy[qlm] = 1;

		if (!strncmp(mode_str, "sgmii", 5)) {
			bool rgmii = false;
			speed[qlm] = 1250;
			if (rqlm == qlm && qlm < 5) {
				mode[qlm] = CVMX_QLM_MODE_RGMII_SGMII;
				rgmii = true;
			} else if (qlm == 6 || qlm == 5) {
				if (rqlm == qlm && qlm == 5) {
					mode[qlm] = CVMX_QLM_MODE_RGMII_SGMII_1X1;
					rgmii = true;
				} else if (rqlm == 5 && qlm == 6
					   && mode[5] != CVMX_QLM_MODE_RGMII_SGMII_1X1) {
					mode[qlm] = CVMX_QLM_MODE_RGMII_SGMII_2X1;
					rgmii = true;
				} else {
					mode[qlm] = CVMX_QLM_MODE_SGMII_2X1;
				}
			} else {
				mode[qlm] = CVMX_QLM_MODE_SGMII;
			}
			ref_clock_sel[qlm] = 2;
			if (qlm == 5 || qlm == 6)
				ref_clock_input[qlm] = 0;
			if (no_phy[qlm]) {
				int i;
				int start = 0, stop = 2;
				rbgx = 0;
				switch (qlm) {
				case 3:
					rbgx = 1;
				case 2:
					for (i = 0; i < 4; i++) {
						printf("Ignoring PHY for interface: %d, port: %d\n",
						       rbgx, i);
						cvmx_helper_set_port_force_link_up(rbgx, i, true);
					}
					break;
				case 6:
					start = 2;
					stop = 4;
				case 5:

					for (i = start; i < stop; i++) {
						printf("Ignoring PHY for interface: %d, port: %d\n",
						       2, i);
						cvmx_helper_set_port_force_link_up(2, i, true);
					}
					break;
				default:
					printf("SGMII not supported for QLM/DLM %d\n",
					       qlm);
					break;
				}
			}
			printf("QLM %d: SGMII%s\n", qlm, rgmii ? ", RGMII" : "");
		} else if (!strncmp(mode_str, "xaui", 4)) {
			speed[qlm] = 3125;
			mode[qlm] = CVMX_QLM_MODE_XAUI;
			ref_clock_sel[qlm] = 2;
			if (qlm == 5 || qlm == 6)
				ref_clock_input[qlm] = 0;
			printf("QLM %d: XAUI\n", qlm);
		} else if (!strncmp(mode_str, "dxaui", 5)) {
			speed[qlm] = 6250;
			mode[qlm] = CVMX_QLM_MODE_XAUI;
			ref_clock_sel[qlm] = 2;
			if (qlm == 5 || qlm == 6)
				ref_clock_input[qlm] = 0;
			printf("QLM %d: DXAUI\n", qlm);
		} else if (!strncmp(mode_str, "rxaui", 5)) {
			bool rgmii = false;
			speed[qlm] = 6250;
			if (qlm == 5 || qlm == 6) {
				if (rqlm == qlm && qlm == 5) {
					mode[qlm] = CVMX_QLM_MODE_RGMII_RXAUI;
					rgmii = true;
				} else {
					mode[qlm] = CVMX_QLM_MODE_RXAUI_1X2;
				}
			} else {
				mode[qlm] = CVMX_QLM_MODE_RXAUI;
			}
			ref_clock_sel[qlm] = 2;
			if (qlm == 5 || qlm == 6)
				ref_clock_input[qlm] = 0;
			printf("QLM %d: RXAUI%s\n", qlm, rgmii ? ", rgmii" : "");
		} else if (!strncmp(mode_str, "xlaui", 5)) {
			speed[qlm] = 103125;
			mode[qlm] = CVMX_QLM_MODE_XLAUI;
			ref_clock_sel[qlm] = 2;
			if (qlm == 5 || qlm == 6)
				ref_clock_input[qlm] = 0;
			sprintf(spd_env, "qlm%d_speed", qlm);
			if (getenv(spd_env)) {
				int spd = getenv_ulong(spd_env, 0, 8);
				if (spd)
					speed[qlm] = spd;
				else
					speed[qlm] = 103125;
			}
			printf("QLM %d: XLAUI\n", qlm);
		} else if (!strncmp(mode_str, "xfi", 3)) {
			bool rgmii = false;
			speed[qlm] = 103125;
			if (rqlm == qlm) {
				mode[qlm] = CVMX_QLM_MODE_RGMII_XFI;
				rgmii = true;
			} else if (qlm == 5 || qlm == 6) {
				mode[qlm] = CVMX_QLM_MODE_XFI_1X2;
			} else {
				mode[qlm] = CVMX_QLM_MODE_XFI;
			}
			ref_clock_sel[qlm] = 2;
			if (qlm == 5 || qlm == 6)
				ref_clock_input[qlm] = 2; // use QLMC_REF_CLK1
			printf("QLM %d: XFI%s\n", qlm, rgmii ? ", RGMII" : "");
		} else if (!strncmp(mode_str, "10G_KR", 6)) {
			speed[qlm] = 103125;
			if (rqlm == qlm && qlm == 5)
				mode[qlm] = CVMX_QLM_MODE_RGMII_10G_KR;
			else if (qlm == 5 || qlm == 6)
				mode[qlm] = CVMX_QLM_MODE_10G_KR_1X2;
			else
				mode[qlm] = CVMX_QLM_MODE_10G_KR;
			ref_clock_sel[qlm] = 2;
			if (qlm == 5 || qlm == 6)
				ref_clock_input[qlm] = 2; // use QLMC_REF_CLK1
			printf("QLM %d: 10G_KR\n", qlm);
		} else if (!strncmp(mode_str, "40G_KR4", 7)) {
			speed[qlm] = 103125;
			mode[qlm] = CVMX_QLM_MODE_40G_KR4;
			ref_clock_sel[qlm] = 2;
			if (qlm == 5 || qlm == 6)
				ref_clock_input[qlm] = 2; // use QLMC_REF_CLK1
			printf("QLM %d: 40G_KR4\n", qlm);
		} else if (!strcmp(mode_str, "pcie")) {
			char *pmode;
			int lanes = 0;
			sprintf(env_var, "pcie%d_mode", qlm);
			pmode = getenv(env_var);
			if (pmode && !strcmp(pmode, "ep"))
				pcie_rc[qlm] = 0;
			else
				pcie_rc[qlm] = 1;
			sprintf(env_var, "pcie%d_gen", qlm);
			pcie_gen[qlm] = getenv_ulong(env_var, 0, 3);
			sprintf(env_var, "pcie%d_lanes", qlm);
			lanes = getenv_ulong(env_var, 0, 8);
			if (lanes == 8)
				mode[qlm] = CVMX_QLM_MODE_PCIE_1X8;
			else if (qlm == 5 || qlm == 6) {
				if (lanes != 2)
					printf("QLM%d: Invalid lanes selected, defaulting to 2 lanes\n", qlm);
				mode[qlm] = CVMX_QLM_MODE_PCIE_1X2;
				ref_clock_input[qlm] = 1; // use QLMC_REF_CLK0
			} else
				mode[qlm] = CVMX_QLM_MODE_PCIE;
			ref_clock_sel[qlm] = 0;
			printf("QLM %d: PCIe gen%d %s, x%d lanes\n", qlm, pcie_gen[qlm] + 1,
				pcie_rc[qlm] ? "root complex" : "endpoint", lanes);
		} else if (!strcmp(mode_str, "sata")) {
			mode[qlm] = CVMX_QLM_MODE_SATA_2X1;
			ref_clock_sel[qlm] = 0;
			ref_clock_input[qlm] = 1;
			sprintf(spd_env, "qlm%d_speed", qlm);
			if (getenv(spd_env)) {
				int spd = getenv_ulong(spd_env, 0, 8);
				if ((spd == 1500) || (spd == 3000) || (spd == 3000))
					speed[qlm] = spd;
				else
					speed[qlm] = 6000;
			} else
			speed[qlm] = 6000;
		} else {
			printf("QLM %d: disabled\n", qlm);
		}
	}

    /* SATA at DLM4 */
    mode[4] = CVMX_QLM_MODE_SATA_2X1;
    ref_clock_sel[4] = 0;
    ref_clock_input[4] = 0;

    /* pcie DLM5 */
    mode[5] = CVMX_QLM_MODE_PCIE_1X2;
    pcie_rc[5] = 1;
    pcie_gen[5] = 1; /* param4 : 0 = GEN1, 1 = GEN2, 2 = GEN3, we use gen2 , default is 3 */
    ref_clock_sel[5] = 0;

	for (qlm = 0; qlm < 7; qlm++) {
		int rc;
		if (mode[qlm] == -1)
			continue;

        /* for airbus, all DLM/QLM use externel reference clock */
        ref_clock_input[qlm] = 0;

		debug("Configuring qlm%d with speed(%d), mode(%d), RC(%d), Gen(%d), REF_CLK(%d), CLK_SOURCE(%d)\n",
		      qlm, speed[qlm], mode[qlm], pcie_rc[qlm],
		      pcie_gen[qlm] + 1, ref_clock_sel[qlm], ref_clock_input[qlm]);
		rc = octeon_configure_qlm(qlm, speed[qlm], mode[qlm],
					  pcie_rc[qlm], pcie_gen[qlm],
					  ref_clock_sel[qlm],
					  ref_clock_input[qlm]);

		if (speed[qlm] == 6250)
			octeon_qlm_tune_v3(0, qlm, speed[qlm], 0xa, 0xa0, -1, -1);
		else if (speed[qlm] == 103125)
			octeon_qlm_tune_v3(0, qlm, speed[qlm], 0xd, 0xd0, -1, -1);

        /* tune sata for SRX380 */
        if (qlm == 4) {
            /* external ssd */
            octeon_qlm_tune_per_lane_v3(0, 4, speed[qlm], 0, 7, -1, 3, -1, -1);

            /* internal ssd */
            octeon_qlm_tune_per_lane_v3(0, 4, speed[qlm], 1, 6, -1, 3, -1, -1);
        } 

		if (qlm == 4 && rc != 0)
			/* There is a bug with SATA with 73xx.  Until it's fixed
			 * we need to strip it from the device tree.
			 */
			octeon_fdt_patch_rename((void *)gd->fdt_blob, "4,none",
						NULL, true, NULL, NULL);
	}
}

