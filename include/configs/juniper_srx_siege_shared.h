
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
#ifndef __JUNIPER_SRX_SIEGE_SHARED_H__
#define __JUNIPER_SRX_SIEGE_SHARED_H__


#define I2C_ID_SRX550M_CHASSIS                   0x058E  /* SRX550M Chassis */

#define I2C_ID_JSRXNLE_SRX300_BASE_PIC                  0x0680  /* SRX300 base PIC */
#define I2C_ID_JSRXNLE_SRX320_BASE_PIC                  0x0681  /* SRX320 base PIC */
#define I2C_ID_JSRXNLE_SRX340_BASE_PIC                  0x0682  /* SRX340 base PIC */

#define I2C_ID_JSRXNLE_SRX300_BASE_COMBO_FPC         0x0780  /* SRX300 baseboard FPC */
#define I2C_ID_JSRXNLE_SRX320_BASE_COMBO_FPC         0x0781  /* SRX320 baseboard FPC */
#define I2C_ID_JSRXNLE_SRX340_BASE_COMBO_FPC         0x0782  /* SRX340 baseboard FPC */

#define JUNIPER_SIEGE_TECHMOSA_125_32BITS_1333_WITHOUT_ECC_SPD_CL10 \
0x92, 0x12, 0x0B, 0x00, 0x04, 0x21, 0x00, 0x09, 0x02, 0x11, 0x01, 0x08, 0x0C, 0x00, 0x3E, 0x00 , \
0x69, 0x78, 0x69, 0x30, 0x69, 0x11, 0x20, 0x89, 0x20, 0x08, 0x3C, 0x3C, 0x00, 0xF0, 0x83, 0x05 , \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 , \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x01 , \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 , \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 , \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 , \
0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x96, 0xB1 , \
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 , \
0x20, 0x20, 0x00, 0x00, 0x83, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00 , \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 , \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 , \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 , \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 , \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 , \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00

#define JUNIPER_SRX_SIEGE_4GB_DRAM_SOCKET_CONFIGURATION0 \
	{{0x0, 0x0}, {juniper_srx_siege_4gb_spd_values, NULL}}

#define JUNIPER_SRX_SIEGE_BOARD_EEPROM_TWSI_ADDR	(0x53)
#define JUNIPER_SRX_AIRBUS_BOARD_EEPROM_TWSI_ADDR	(0x50)

/*
 * Local copy of these parameters to allow for customization for this
 * board design.  The generic version resides in lib_octeon_shared.h.
 *
 */
#define JUNIPER_SRX_SIEGE_MODEREG_PARAMS1_1RANK_1SLOT	\
{							\
	.cn63xx = {					\
		.pasr_00	= 0,			\
		.asr_00		= 0,			\
		.srt_00		= 0,			\
		.rtt_wr_00	= 0,			\
		.dic_00		= 0,			\
		.rtt_nom_00	= rttnom_40ohm,		\
		.pasr_01	= 0,			\
		.asr_01		= 0,			\
		.srt_01		= 0,			\
		.rtt_wr_01	= 0,			\
		.dic_01		= 0,			\
		.rtt_nom_01	= 0,			\
		.pasr_10	= 0,			\
		.asr_10		= 0,			\
		.srt_10		= 0,			\
		.rtt_wr_10	= 0,			\
		.dic_10		= 0,			\
		.rtt_nom_10	= 0,			\
		.pasr_11	= 0,			\
		.asr_11		= 0,			\
		.srt_11		= 0,			\
		.rtt_wr_11	= 0,			\
		.dic_11		= 0,			\
		.rtt_nom_11	= 0			\
	}						\
}

#define JUNIPER_SRX_SIEGE_MODEREG_PARAMS1_2RANK_1SLOT	\
{							\
	.cn63xx = {					\
		.pasr_00	= 0,			\
		.asr_00		= 0,			\
		.srt_00		= 0,			\
		.rtt_wr_00	= 0,			\
		.dic_00		= 0,			\
		.rtt_nom_00	= rttnom_40ohm,		\
		.pasr_01	= 0,			\
		.asr_01		= 0,			\
		.srt_01		= 0,			\
		.rtt_wr_01	= 0,			\
		.dic_01		= 0,			\
		.rtt_nom_01	= 0,			\
		.pasr_10	= 0,			\
		.asr_10		= 0,			\
		.srt_10		= 0,			\
		.rtt_wr_10	= 0,			\
		.dic_10		= 0,			\
		.rtt_nom_10	= 0,			\
		.pasr_11	= 0,			\
		.asr_11		= 0,			\
		.srt_11		= 0,			\
		.rtt_wr_11	= 0,			\
		.dic_11		= 0,			\
		.rtt_nom_11	= 0			\
	}						\
}



#define JUNIPER_SRX_SIEGE_DRAM_ODT_1RANK_CONFIGURATION \
	/* DIMMS   DQX_CTL  WODT_MASK                LMCX_MODEREG_PARAMS1              reserved        RODT_CTL    RODT_MASK   reserved */	\
	/* =====   ======== ============== ==========================================  ============== ========= ============== ======== */	\
	/*   1 */ {   0,    0x00000001ULL, JUNIPER_SRX_SIEGE_MODEREG_PARAMS1_1RANK_1SLOT,    {.u64=0x0000},  3,     0x00000000ULL,  0  }	\

#define JUNIPER_SRX_SIEGE_DRAM_ODT_2RANK_CONFIGURATION \
	/* DIMMS   DQX_CTL  WODT_MASK                LMCX_MODEREG_PARAMS1              reserved       RODT_CTL    RODT_MASK    reserved */	\
	/* =====   ======== ============== ==========================================  ============== ========= ============== ======== */	\
	/*   1 */ {   0,    0x00000101ULL, JUNIPER_SRX_SIEGE_MODEREG_PARAMS1_2RANK_1SLOT,   {.u64=0x0000},  3,     0x00000000ULL,    0  }    \

#define OCTEON_EVB7000_DRAM_ODT_2RANK_CONFIGURATION \
	/* DIMMS   DQX_CTL  WODT_MASK                LMCX_MODEREG_PARAMS1              reserved       RODT_CTL    RODT_MASK    reserved */	\
	/* =====   ======== ============== ==========================================  ============== ========= ============== ======== */	\
        /*   1 */ {   4,    0x00000101ULL, OCTEON_EVB7000_MODEREG_PARAMS1_2RANK_1SLOT, {.u64=0x0000},     3,     0x00000000ULL,    0  } \

/* Construct a static initializer for the ddr_configuration_t variable that holds
 * (almost) all of the information required for DDR initialization.
 */

/*
  The parameters below make up the custom_lmc_config data structure.
  This structure is used to customize the way that the LMC DRAM
  Controller is configured for a particular board design.

  Refer to the file lib_octeon_board_table_entry.h for a description
  of the custom board settings.  It is usually kept in the following
  location... arch/mips/include/asm/arch-octeon/

 */

#define JUNIPER_SRX_SIEGE_4GB_DDR_CONFIGURATION {				\
	/* Interface 0 */						\
	.custom_lmc_config = {						\
		.min_rtt_nom_idx	= 1,				\
		.max_rtt_nom_idx	= 5,				\
		.min_rodt_ctl		= 1,				\
		.max_rodt_ctl		= 5,				\
		.dqx_ctl		= 4,				\
		.ck_ctl			= 4,				\
		.cmd_ctl		= 4,				\
		.ctl_ctl		= 4,				\
		.min_cas_latency	= 0,				\
		.offset_en 		= 1,				\
		.offset_udimm		= 2,				\
		.offset_rdimm		= 2,				\
                .ntune_offset		= -2,       \
                .ptune_offset		= 1,        \
		.ddr_rtt_nom_auto	= 0,				\
		.ddr_rodt_ctl_auto	= 0,				\
        .rlevel_comp_offset_udimm = 7,/* juniper todo need this test not exist at acton codes */ \
		.rlevel_compute 	= 0,				\
		.ddr2t_udimm 		= 1,				\
		.ddr2t_rdimm 		= 1,				\
        .maximum_adjacent_rlevel_delay_increment = 2,           \
		.fprch2			= 2,				\
		.parity			= 0,				\
		.mode32b		= 1,				\
                .dll_write_offset	= NULL,      \
                .dll_read_offset 	= NULL,      \
	},								\
        .dimm_config_table = {						\
		JUNIPER_SRX_SIEGE_4GB_DRAM_SOCKET_CONFIGURATION0,		\
		DIMM_CONFIG_TERMINATOR,					\
	},								\
	.unbuffered = {							\
		.ddr_board_delay = 0,					\
		.lmc_delay_clk = 0,					\
		.lmc_delay_cmd = 0,					\
		.lmc_delay_dq = 0,					\
	},								\
	.registered = {							\
		.ddr_board_delay = 0,					\
		.lmc_delay_clk = 0,					\
		.lmc_delay_cmd = 0,					\
		.lmc_delay_dq = 0,					\
	},								\
	.odt_1rank_config = {                        			\
		JUNIPER_SRX_SIEGE_DRAM_ODT_1RANK_CONFIGURATION,		\
	},								\
	.odt_2rank_config = {						\
		JUNIPER_SRX_SIEGE_DRAM_ODT_2RANK_CONFIGURATION,		\
	},								\
}

#endif   /* __JUNIPER_SRX_SIEGE_SHARED_H__ */
