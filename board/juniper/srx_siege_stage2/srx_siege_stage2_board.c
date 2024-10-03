/*
 * Copyright (c) 2015-2016, Juniper Networks, Inc.
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
#include <asm/arch/lib_octeon_shared.h>
#include <asm/arch/lib_octeon.h>
#include <asm/arch/cvmx.h>
#include <asm/arch/cvmx-app-init.h>
#include <asm/arch/octeon-model.h>

#include "../common/juniper_board_common.h"
#include "../srx_siege/srx_siege_board.h"

DECLARE_GLOBAL_DATA_PTR;

uint16_t board_type_2_memory_type(uint16_t type)
{
    if (IS_PLATFORM_AIRBUS(type)) {
        return I2C_ID_MEMORY_MODEL_AIRBUS;
    } else {
        return I2C_ID_MEMORY_MODEL_SIEGE;
    }
}

/* Add juniper board_id */
static const uint8_t tuple_addresses[] = {
    JUNIPER_SRX_SIEGE_BOARD_EEPROM_TWSI_ADDR,
};

int is_valid_board_type(uint16_t type)
{
    return (IS_PLATFORM_SIEGE(type) || IS_PLATFORM_AIRBUS(type));
}

/* Perform early board initialization */
int early_board_init(void)
{
	const int cpu_ref = DEFAULT_CPU_REF_FREQUENCY_MHZ;
    uint32_t cpu_id;
	int i;

    for (i = 0; i < ARRAY_SIZE(tuple_addresses); i++) {
        gd->arch.tlv_addr = tuple_addresses[i];
        octeon_board_get_descriptor(CVMX_BOARD_TYPE_GENERIC,
                        1, 0);
        if (gd->board_type != CVMX_BOARD_TYPE_GENERIC) {
            break;
        }
    }
    if (i == ARRAY_SIZE(tuple_addresses)) {
        printf("ERROR: Board TLV descriptor not found!  Cannot continue!\n"
             "Use the tlv_eeprom command to program the board type.\n");

        cpu_id = cvmx_get_proc_id();

        if ((cpu_id & 0xff00) == 0x9600) {
            if (cvmx_read_csr(CVMX_MIO_FUS_PDF) & (0x1ULL << 32)) { /* 71 family */
                octeon_board_get_descriptor(I2C_ID_JSRXNLE_SRX340_CHASSIS, 1, 0);
            } else {  /* 70 family */
                octeon_board_get_descriptor(I2C_ID_JSRXNLE_SRX300_CHASSIS, 1, 0);
            }
        } else if ((cpu_id & 0xff00) == 0x9700) { /* 0x97 = CN73XX */
            printf("#### unexpected cpu_id set board_id to srx380 by default!");
            octeon_board_get_descriptor(I2C_ID_JSRXNLE_SRX380_POE_AC_CHASSIS, 1, 0);
        } else {
            printf("#### unexpected cpu_id set board_id to srx300 by default!");
            octeon_board_get_descriptor(I2C_ID_JSRXNLE_SRX300_CHASSIS, 1, 0);
        }
    }

	gd->arch.ddr_ref_hertz = 50000000;

	/*
     * NOTE: this is early in the init process, so the serial port is not
	 * yet configured
	 */
	octeon_board_get_clock_info(DEFAULT_DDR3_CLOCK_FREQ_MHZ);

	/* Read CPU clock multiplier */
	gd->cpu_clk = octeon_get_cpu_multiplier() * cpu_ref * 1000000;

	return 0;
}

/* Perform initialization late in the init process */
void late_board_init(void)
{
	char buf[256];
	char *board_name;
	board_name = getenv("boardname");
	if (board_name) {
		sprintf(buf, "u-boot-octeon_%s.bin", board_name);
		setenv("octeon_stage3_bootloader", buf);
		debug("Detected board type %s\n", board_name);
		sprintf(buf, "%s (SPI stage 2)", board_name);
		setenv("prompt", buf);
	}
}



