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
#include <asm/arch/octeon_fdt.h>
#include <asm/arch/lib_octeon_shared.h>
#include <asm/arch/lib_octeon.h>
#include <asm/arch/cvmx-helper-jtag.h>
#include <asm/gpio.h>
#include <asm/arch/cvmx-pcie.h>
#include <asm/arch/cvmx-qlm.h>
#include <asm/arch/cvmx-mdio.h>
#include <asm/arch/cvmx.h>
#include <asm/arch/cvmx-agl.h>
#include <asm/arch/cvmx-agl-defs.h>
#include <i2c.h>
#include <watchdog_cpu.h>

#include <spi_flash.h>
#include "juniper_board_common.h"
#include "../srx_siege/srx_siege_board.h"

DECLARE_GLOBAL_DATA_PTR;

uint8_t
board_read_id_eeprom (uint8_t offset)
{
    uint8_t val;

    if (0 == i2c_read(CONFIG_SYS_I2C_EEPROM_ADDR, offset, ID_EEPROM_ALEN,
                      &val, 1)) {
        return val;
    }
    else {
        return JSRXNLE_I2C_ERR;
    }
}

uint8_t
board_write_id_eeprom(uint8_t offset, uint8_t val)
{
    uint8_t data = val;

    return i2c_write(CONFIG_SYS_I2C_EEPROM_ADDR, offset, ID_EEPROM_ALEN,
				&data, 1);
}

/*
 * Reads the board descriptor from the TLV EEPROM or fills in the default
 * values.
 *
 * @param type		board type
 * @param rev_major	board major revision
 * @param rev_minor	board minor revision
 */
void octeon_board_get_descriptor(enum cvmx_board_types_enum type,
				 int rev_major, int rev_minor)
{
    uint16_t jdec_code;
    uint8_t  ideeprom_format_version;
    uint32_t i;

	gd->arch.board_desc.board_type = CVMX_BOARD_TYPE_NULL;

    for (i = 0; i < SERIAL_STR_LEN; i++) {
        gd->arch.board_desc.serial_str[i] =
            board_read_id_eeprom(BOARD_ID_EEPROM_SERIAL_NO_OFFSET + i);
    }
    gd->arch.board_desc.serial_str[SERIAL_STR_LEN] = '\0';

    jdec_code =
        ((uint16_t)board_read_id_eeprom(BOARD_ID_EEPROM_JDEC_OFFSET) << 8)
        | board_read_id_eeprom(BOARD_ID_EEPROM_JDEC_OFFSET + 1);
    ideeprom_format_version =
        board_read_id_eeprom(BOARD_ID_EEPROM_FORMAT_VERSION_OFFSET);

    if (jdec_code == JUNIPER_JDEC_CODE
        && ((ideeprom_format_version == JUNIPER_EEPROM_FORMAT_V1)
            || (ideeprom_format_version == JUNIPER_EEPROM_FORMAT_V2))) {
        gd->arch.board_desc.board_type =
         ((uint16_t)board_read_id_eeprom(BOARD_ID_EEPROM_I2CID_OFFSET) << 8)
         | board_read_id_eeprom(BOARD_ID_EEPROM_I2CID_OFFSET + 1);

        /*
         * This is for handling the case where the ID EEPROM values
         * are wrong. we do our best to come up so that we can write
         * the correct EEPROM values once u-boot is up
         */
        if (!is_valid_board_type(gd->arch.board_desc.board_type)) {
            gd->flags |= GD_FLG_BOARD_DESC_MISSING;
            gd->arch.board_desc.board_type = CVMX_BOARD_TYPE_NULL;
        } else {
            gd->board_type = gd->arch.board_desc.board_type;
            gd->arch.board_desc.rev_major =
                board_read_id_eeprom(BOARD_ID_EEPROM_MAJOR_REV_OFFSET);
            gd->arch.board_desc.rev_minor =
                board_read_id_eeprom(BOARD_ID_EEPROM_MINOR_REV_OFFSET);
        }
    }

	if (gd->arch.board_desc.board_type == CVMX_BOARD_TYPE_NULL) {
		debug("Setting board type to passed-in type %s\n",
		      cvmx_board_type_to_string(type));
		gd->flags |= GD_FLG_BOARD_DESC_MISSING;
		gd->arch.board_desc.rev_major = rev_major;
		gd->arch.board_desc.rev_minor = rev_minor;
		gd->board_type = gd->arch.board_desc.board_type = type;
	}
}


/*
 * Gets the MAC address for a board from the TLV EEPROM.  If not present a
 * random MAC address is generated.
 */
void
octeon_board_get_mac_addr (void)
{
    uint8_t mac_magic;
    uint8_t mac_version;
    uint8_t mac_offset;

    /* Juniper has it's own TLV EEPROM data format, check magic&ver before read mac */
    mac_magic = board_read_id_eeprom(BOARD_ID_EEPROM_MAC_MAGIC_OFFSET);
    mac_version = board_read_id_eeprom(BOARD_ID_EEPROM_MAC_VERSION_OFFSET);

    if ((mac_magic == JUNIPER_MAC_MAGIC)
            && (mac_version == JUNIPER_MAC_VERSION)) {
        switch (gd->arch.board_desc.board_type) {
        CASE_ALL_JSRX_SIEGE_MODELS
        default:
            gd->arch.mac_desc.count = 1;
            break;
        }

        for (mac_offset = 0; mac_offset < 6; mac_offset++) {
            gd->arch.mac_desc.mac_addr_base[mac_offset]
                = board_read_id_eeprom(BOARD_ID_EEPROM_MAC_ADDR_OFFSET + mac_offset);
        }
    } else {
        /* use octeon evl board mac addr */
        octeon_board_create_random_mac_addr();
    }
}

/* platform specific octeon_boot_bus_board_init func */
void octeon_boot_bus_board_init(void)
{
    /* use switch for further expansion */
    switch (gd->arch.board_desc.board_type) {
    CASE_ALL_JSRX_SIEGE_MODELS
        return srx_siege_boot_bus_init();
    CASE_ALL_JSRX_AIRBUS_MODELS
        return srx_airbus_boot_bus_init();
    default:
        return srx_siege_boot_bus_init();
    }

}


