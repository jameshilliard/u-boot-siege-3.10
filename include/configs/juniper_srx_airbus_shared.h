/*
 * Copyright (c) 2007-2019, Juniper Networks, Inc.
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
#ifndef __JNPR_SRX_AIRBUS_SHARED_H__
#define __JNPR_SRX_AIRBUS_SHARED_H__

#define JNPR_SRX_AIRBUS_DRAM_SOCKET_CONFIGURATION0	\
	{{0x50, 0x0}, {NULL, NULL}}, {{0, 0x0}, {NULL, NULL}}
#define JNPR_SRX_AIRBUS_DRAM_SOCKET_CONFIGURATION1	\
	{{0, 0x0}, {NULL, NULL}}, {{0, 0x0}, {NULL, NULL}}

#define JNPR_SRX_AIRBUS_BOARD_EEPROM_TWSI_ADDR        (0x56)

/*
 * Local copy of these parameters to allow for customization for this
 * board design.  The generic version resides in lib_octeon_shared.h.
 */

/* LMC0_MODEREG_PARAMS1 */
#define JNPR_SRX_AIRBUS_MODEREG_PARAMS1_1RANK_1SLOT      \
	{							\
		.cn78xx = {					\
			.pasr_00	= 0,			\
                  .asr_00       = 0,                    \
                  .srt_00       = 0,                    \
			.rtt_wr_00	= ddr4_rttwr_80ohm&3,	\
			.rtt_wr_00_ext	= (ddr4_rttwr_80ohm>>2)&1,	\
                  .dic_00	= ddr4_dic_34ohm,	\
                  .rtt_nom_00	= 0,                    \
                  .pasr_01      = 0,                    \
                  .asr_01       = 0,                    \
                  .srt_01       = 0,                    \
                  .rtt_wr_01    = 0,                    \
                  .dic_01	= ddr4_dic_34ohm,	\
                  .rtt_nom_01   = 0,                    \
                  .pasr_10      = 0,                    \
                  .asr_10       = 0,                    \
                  .srt_10       = 0,                    \
                  .rtt_wr_10    = 0,                    \
                  .dic_10	= ddr4_dic_34ohm,	\
                  .rtt_nom_10   = 0,                    \
                  .pasr_11      = 0,                    \
                  .asr_11       = 0,                    \
                  .srt_11       = 0,                    \
                  .rtt_wr_11    = 0,                    \
                  .dic_11	= ddr4_dic_34ohm,	\
                  .rtt_nom_11   = 0,                    \
        }                                               \
    }

#define JNPR_SRX_AIRBUS_MODEREG_PARAMS1_1RANK_2SLOT      \
	{							\
		.cn78xx = {					\
			.pasr_00	= 0,			\
                  .asr_00       = 0,                    \
                  .srt_00       = 0,                    \
			.rtt_wr_00	= ddr4_rttwr_80ohm&3,	\
			.rtt_wr_00_ext	= (ddr4_rttwr_80ohm>>2)&1,	\
                  .dic_00	= ddr4_dic_34ohm,	\
                  .rtt_nom_00   = 0,                    \
                  .pasr_01      = 0,                    \
                  .asr_01       = 0,                    \
                  .srt_01       = 0,                    \
                  .rtt_wr_01    = 0,                    \
                  .dic_01	= ddr4_dic_34ohm,	\
                  .rtt_nom_01   = 0,                    \
                  .pasr_10      = 0,                    \
                  .asr_10       = 0,                    \
                  .srt_10       = 0,                    \
			.rtt_wr_10	= ddr4_rttwr_80ohm&3,	\
			.rtt_wr_10_ext	= (ddr4_rttwr_80ohm>>2)&1,	\
                  .dic_10	= ddr4_dic_34ohm,	\
                  .rtt_nom_10   = 0,                    \
                  .pasr_11      = 0,                    \
                  .asr_11       = 0,                    \
                  .srt_11       = 0,                    \
                  .rtt_wr_11    = 0,                    \
                  .dic_11	= ddr4_dic_34ohm,	\
                  .rtt_nom_11   = 0                     \
        }                                               \
    }

#define JNPR_SRX_AIRBUS_MODEREG_PARAMS1_2RANK_1SLOT      \
	{							\
		.cn78xx = {					\
			.pasr_00	= 0,			\
                  .asr_00       = 0,                    \
                  .srt_00       = 0,                    \
                  .rtt_wr_00	= ddr4_rttwr_240ohm,    \
                  .dic_00	= ddr4_dic_34ohm,       \
                  .rtt_nom_00	= 0,                    \
                  .pasr_01      = 0,                    \
                  .asr_01       = 0,                    \
                  .srt_01       = 0,                    \
                  .rtt_wr_01	= ddr4_rttwr_240ohm,    \
                  .dic_01	= ddr4_dic_34ohm,       \
                  .rtt_nom_01	= 0,                    \
                  .pasr_10      = 0,                    \
                  .asr_10       = 0,                    \
                  .srt_10       = 0,                    \
                  .dic_10	= ddr4_dic_34ohm,       \
                  .rtt_nom_10	= 0,                    \
                  .pasr_11      = 0,                    \
                  .asr_11       = 0,                    \
                  .srt_11       = 0,                    \
                  .rtt_wr_11    = 0,                    \
                  .dic_11	= ddr4_dic_34ohm,	\
                  .rtt_nom_11   = 0,                    \
        }                                               \
    }

#define JNPR_SRX_AIRBUS_MODEREG_PARAMS1_2RANK_2SLOT      \
	{							\
		.cn78xx = {					\
			.pasr_00	= 0,			\
                  .asr_00       = 0,                    \
                  .srt_00       = 0,                    \
                  .rtt_wr_00	= ddr4_rttwr_240ohm,    \
                  .dic_00	= ddr4_dic_34ohm,       \
                  .rtt_nom_00	= ddr4_rttnom_120ohm,   \
                  .pasr_01      = 0,                    \
                  .asr_01       = 0,                    \
                  .srt_01       = 0,                    \
                  .rtt_wr_01	= ddr4_rttwr_240ohm,    \
                  .dic_01	= ddr4_dic_34ohm,       \
                  .rtt_nom_01	= ddr4_rttnom_120ohm,   \
                  .pasr_10      = 0,                    \
                  .asr_10       = 0,                    \
                  .srt_10       = 0,                    \
                  .rtt_wr_10	= ddr4_rttwr_240ohm,    \
                  .dic_10	= ddr4_dic_34ohm,       \
                  .rtt_nom_10	= ddr4_rttnom_120ohm,   \
                  .pasr_11      = 0,                    \
                  .asr_11       = 0,                    \
                  .srt_11       = 0,                    \
                  .rtt_wr_11	= ddr4_rttwr_240ohm,    \
                  .dic_11	= ddr4_dic_34ohm,       \
                  .rtt_nom_11	= ddr4_rttnom_120ohm,   \
        }                                               \
    }

#define JNPR_SRX_AIRBUS_MODEREG_PARAMS1_4RANK_1SLOT      \
	{							\
		.cn78xx = {					\
			.pasr_00	= 0,			\
                  .asr_00       = 0,                    \
                  .srt_00       = 0,                    \
                  .rtt_wr_00    = rttwr_60ohm,          \
                  .dic_00       = dic_34ohm,            \
                  .rtt_nom_00   = rttnom_20ohm,         \
                  .pasr_01      = 0,                    \
                  .asr_01       = 0,                    \
                  .srt_01       = 0,                    \
                  .rtt_wr_01    = rttwr_60ohm,          \
                  .dic_01       = dic_34ohm,            \
                  .rtt_nom_01   = rttnom_none,          \
                  .pasr_10      = 0,                    \
                  .asr_10       = 0,                    \
                  .srt_10       = 0,                    \
                  .rtt_wr_10    = rttwr_60ohm,          \
                  .dic_10       = dic_34ohm,            \
                  .rtt_nom_10   = rttnom_20ohm,         \
                  .pasr_11      = 0,                    \
                  .asr_11       = 0,                    \
                  .srt_11       = 0,                    \
                  .rtt_wr_11    = rttwr_60ohm,          \
                  .dic_11       = dic_34ohm,            \
                  .rtt_nom_11   = rttnom_none,          \
        }                                               \
    }


#define JNPR_SRX_AIRBUS_MODEREG_PARAMS2_1RANK_1SLOT	\
{							\
	.cn78xx = {					\
		.rtt_park_00    = ddr4_rttpark_60ohm,	\
		.vref_value_00  = 0x22,			\
		.vref_range_00  = 0,			\
		.rtt_park_01    = 0,			\
		.vref_value_01  = 0,			\
		.vref_range_01  = 0,			\
		.rtt_park_10    = 0,			\
		.vref_value_10  = 0,			\
		.vref_range_10  = 0,			\
		.rtt_park_11    = 0,			\
		.vref_value_11  = 0,			\
		.vref_range_11  = 0			\
	}						\
}

/* FIX */
#define JNPR_SRX_AIRBUS_MODEREG_PARAMS2_1RANK_2SLOT	\
{							\
	.cn78xx = {					\
		.rtt_park_00    = ddr4_rttpark_48ohm,	\
		.vref_value_00  = 0x1f,			\
		.vref_range_00  = 0,			\
		.rtt_park_01    = 0,			\
		.vref_value_01  = 0,			\
		.vref_range_01  = 0,			\
		.rtt_park_10    = ddr4_rttpark_48ohm,	\
		.vref_value_10  = 0x1f,			\
		.vref_range_10  = 0,			\
		.rtt_park_11    = 0,			\
		.vref_value_11  = 0,			\
		.vref_range_11  = 0			\
	}						\
}

#define JNPR_SRX_AIRBUS_MODEREG_PARAMS2_2RANK_1SLOT	\
{							\
	.cn78xx = {					\
		.rtt_park_00    = ddr4_rttpark_120ohm,	\
		.vref_value_00  = 0x19,			\
		.vref_range_00  = 0,			\
		.rtt_park_01    = ddr4_rttpark_120ohm,	\
		.vref_value_01  = 0x19,			\
		.vref_range_01  = 0,			\
		.rtt_park_10    = 0,			\
		.vref_value_10  = 0,			\
		.vref_range_10  = 0,			\
		.rtt_park_11    = 0,			\
		.vref_value_11  = 0,			\
		.vref_range_11  = 0			\
	}						\
}

#define JNPR_SRX_AIRBUS_MODEREG_PARAMS2_2RANK_2SLOT	\
{							\
	.cn78xx = {					\
		.rtt_park_00    = ddr4_rttpark_60ohm,	\
		.vref_value_00  = 0x19,			\
		.vref_range_00  = 0,			\
		.rtt_park_01    = ddr4_rttpark_60ohm,	\
		.vref_value_01  = 0x19,			\
		.vref_range_01  = 0,			\
		.rtt_park_10    = ddr4_rttpark_60ohm,	\
		.vref_value_10  = 0x19,			\
		.vref_range_10  = 0,			\
		.rtt_park_11    = ddr4_rttpark_60ohm,	\
		.vref_value_11  = 0x19,			\
		.vref_range_11  = 0			\
	}						\
}

#define JNPR_SRX_AIRBUS_MODEREG_PARAMS2_4RANK_1SLOT	\
{							\
	.cn78xx = {					\
		.rtt_park_00    = ddr4_rttpark_80ohm,	\
		.vref_value_00  = 0x1f,			\
		.vref_range_00  = 0,			\
		.rtt_park_01    = ddr4_rttpark_80ohm,	\
		.vref_value_01  = 0x1f,			\
		.vref_range_01  = 0,			\
		.rtt_park_10    = 0,			\
		.vref_value_10  = 0,			\
		.vref_range_10  = 0,			\
		.rtt_park_11    = 0,			\
		.vref_value_11  = 0,			\
		.vref_range_11  = 0			\
	}						\
}

#define JNPR_SRX_AIRBUS_CN78XX_DRAM_ODT_1RANK_CONFIGURATION \
    /* DIMMS    DQX_CTL  WODT_MASK                LMCX_MODEREG_PARAMS1                        LMCX_MODEREG_PARAMS2            RODT_CTL   RODT_MASK    rsv'ed */ \
    /* =====   ======== ============== ==========================================  ========================================== ======== ============== ====== */ \
    /*   1 */ {   ddr4_dqx_driver_34_ohm,    0x00000000ULL, JNPR_SRX_AIRBUS_MODEREG_PARAMS1_1RANK_1SLOT, JNPR_SRX_AIRBUS_MODEREG_PARAMS2_1RANK_1SLOT,   ddr4_rodt_ctl_48_ohm,    0x00000000ULL,    0  }, \
    /*   2 */ {   ddr4_dqx_driver_34_ohm,    0x00000000ULL, JNPR_SRX_AIRBUS_MODEREG_PARAMS1_1RANK_2SLOT, JNPR_SRX_AIRBUS_MODEREG_PARAMS2_1RANK_2SLOT,   ddr4_rodt_ctl_80_ohm,    0x00000000ULL,    0  }

#define JNPR_SRX_AIRBUS_CN78XX_DRAM_ODT_2RANK_CONFIGURATION \
    /* DIMMS    DQX_CTL  WODT_MASK                LMCX_MODEREG_PARAMS1                        LMCX_MODEREG_PARAMS2            RODT_CTL   RODT_MASK    rsv'ed */ \
    /* =====   ======== ============== ==========================================  ========================================== ======== ============== ====== */ \
    /*   1 */ {   ddr4_dqx_driver_34_ohm,    0x00000000ULL, JNPR_SRX_AIRBUS_MODEREG_PARAMS1_2RANK_1SLOT, JNPR_SRX_AIRBUS_MODEREG_PARAMS2_2RANK_1SLOT,   ddr4_rodt_ctl_80_ohm,    0x00000000ULL,    0  }, \
    /*   2 */ {   ddr4_dqx_driver_34_ohm,    0x0c0c0303ULL, JNPR_SRX_AIRBUS_MODEREG_PARAMS1_2RANK_2SLOT, JNPR_SRX_AIRBUS_MODEREG_PARAMS2_2RANK_2SLOT,   ddr4_rodt_ctl_48_ohm,    0x04080102ULL,    0  }

#define JNPR_SRX_AIRBUS_CN78XX_DRAM_ODT_4RANK_CONFIGURATION \
    /* DIMMS    DQX_CTL  WODT_MASK                LMCX_MODEREG_PARAMS1                        LMCX_MODEREG_PARAMS2            RODT_CTL   RODT_MASK    rsv'ed */ \
    /* =====   ======== ============== ==========================================  ========================================== ======== ============== ====== */ \
    /*   1 */ {   ddr4_dqx_driver_34_ohm,    0x01030203ULL, JNPR_SRX_AIRBUS_MODEREG_PARAMS1_4RANK_1SLOT, JNPR_SRX_AIRBUS_MODEREG_PARAMS2_4RANK_1SLOT,   ddr4_rodt_ctl_48_ohm,    0x01010202ULL,    0  }

/* Construct a static initializer for the ddr_configuration_t variable that holds
** (almost) all of the information required for DDR initialization.
*/

/*
  The parameters below make up the custom_lmc_config data structure.
  This structure is used to customize the way that the LMC DRAM
  Controller is configured for a particular board design.

  Refer to the file lib_octeon_board_table_entry.h for a description
  of the custom board settings.  It is usually kept in the following
  location... arch/mips/include/asm/arch-octeon/

*/

#define JNPR_SRX_AIRBUS_DDR_CONFIGURATION             \
/* Interface 0 */							\
{									\
        .custom_lmc_config = {                                          \
            .min_rtt_nom_idx	= 1,                                    \
            .max_rtt_nom_idx	= 7,                                    \
            .min_rodt_ctl	= 1,                                    \
            .max_rodt_ctl	= 7,                                    \
            .ck_ctl		= ddr4_driver_34_ohm,                   \
            .cmd_ctl		= ddr4_driver_34_ohm,                   \
            .ctl_ctl		= ddr4_driver_34_ohm,                   \
            .min_cas_latency	= 0,                                    \
            .offset_en 		= 1,                                    \
            .offset_udimm	= 2,                                    \
            .offset_rdimm	= 2,                                    \
            .ddr_rtt_nom_auto	= 0,                                    \
            .ddr_rodt_ctl_auto	= 0,                                    \
            .rlevel_comp_offset_udimm	= 0,                            \
            .rlevel_comp_offset_rdimm	= 0,                            \
            .rlevel_compute 	= 0,                                    \
            .ddr2t_udimm 	= 1,                                    \
            .ddr2t_rdimm 	= 1,                                    \
            .maximum_adjacent_rlevel_delay_increment = 2,               \
            .fprch2		= 2,                                    \
            .dll_write_offset   = NULL,                                 \
            .dll_read_offset    = NULL,                                 \
		.parity				= 0			\
    },                                                                  \
            .dimm_config_table = {                                      \
		JNPR_SRX_AIRBUS_DRAM_SOCKET_CONFIGURATION0,		\
		DIMM_CONFIG_TERMINATOR					\
    },                                                                  \
                 .unbuffered = {                                        \
            .ddr_board_delay = 0,                                       \
            .lmc_delay_clk = 0,                                         \
            .lmc_delay_cmd = 0,                                         \
		.lmc_delay_dq			= 0			\
	},								\
                      .registered = {                                   \
            .ddr_board_delay = 0,                                       \
            .lmc_delay_clk = 0,                                         \
            .lmc_delay_cmd = 0,                                         \
		.lmc_delay_dq			= 0			\
	},								\
                           .odt_1rank_config = {                        \
		JNPR_SRX_AIRBUS_CN78XX_DRAM_ODT_1RANK_CONFIGURATION	\
	},								\
                                .odt_2rank_config = {                   \
		JNPR_SRX_AIRBUS_CN78XX_DRAM_ODT_2RANK_CONFIGURATION	\
    },                                                                  \
	.odt_4rank_config = {						\
		JNPR_SRX_AIRBUS_CN78XX_DRAM_ODT_4RANK_CONFIGURATION	\
	}								\
},									\
/* Interface 1 */							\
{									\
        .custom_lmc_config = {                                          \
            .min_rtt_nom_idx	= 1,                                    \
            .max_rtt_nom_idx	= 7,                                    \
            .min_rodt_ctl	= 1,                                    \
            .max_rodt_ctl	= 7,                                    \
            .ck_ctl		= ddr4_driver_34_ohm,                   \
            .cmd_ctl		= ddr4_driver_34_ohm,                   \
            .ctl_ctl		= ddr4_driver_34_ohm,                   \
            .min_cas_latency	= 0,                                    \
            .offset_en 		= 1,                                    \
            .offset_udimm	= 2,                                    \
            .offset_rdimm	= 2,                                    \
            .ddr_rtt_nom_auto	= 0,                                    \
            .ddr_rodt_ctl_auto	= 0,                                    \
            .rlevel_comp_offset_udimm	= 0,                            \
            .rlevel_comp_offset_rdimm	= 0,                            \
            .rlevel_compute 	= 0,                                    \
            .ddr2t_udimm 	= 1,                                    \
            .ddr2t_rdimm 	= 1,                                    \
            .maximum_adjacent_rlevel_delay_increment = 2,               \
            .fprch2		= 2,                                    \
            .dll_write_offset   = NULL,                                 \
            .dll_read_offset    = NULL,                                 \
		.parity				= 0			\
	},								\
            .dimm_config_table = {                                      \
                JNPR_SRX_AIRBUS_DRAM_SOCKET_CONFIGURATION1,		\
		DIMM_CONFIG_TERMINATOR					\
	},								\
                 .unbuffered = {                                        \
            .ddr_board_delay = 0,                                       \
            .lmc_delay_clk = 0,                                         \
            .lmc_delay_cmd = 0,                                         \
		.lmc_delay_dq			= 0			\
	},								\
                      .registered = {                                   \
            .ddr_board_delay = 0,                                       \
            .lmc_delay_clk = 0,                                         \
            .lmc_delay_cmd = 0,                                         \
		.lmc_delay_dq			= 0			\
	},								\
                           .odt_1rank_config = {                        \
		JNPR_SRX_AIRBUS_CN78XX_DRAM_ODT_1RANK_CONFIGURATION	\
	},        							\
                                .odt_2rank_config = {                   \
		JNPR_SRX_AIRBUS_CN78XX_DRAM_ODT_2RANK_CONFIGURATION	\
	},								\
                                     .odt_4rank_config = {              \
		JNPR_SRX_AIRBUS_CN78XX_DRAM_ODT_4RANK_CONFIGURATION	\
	}								\
},

#endif   /* __JNPR_SRX_AIRBUS_SHARED_H__ */
