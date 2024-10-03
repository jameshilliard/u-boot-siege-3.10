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

#ifndef __JUNIPER_BOARD_COMMON_H__
#define __JUNIPER_BOARD_COMMON_H__


/* board ID eeprom definations */
#define BOARD_ID_EEPROM_JDEC_OFFSET              0x00
#define BOARD_ID_EEPROM_FORMAT_VERSION_OFFSET    0x02
#define BOARD_ID_EEPROM_I2CID_OFFSET             0x04
#define BOARD_ID_EEPROM_MAJOR_REV_OFFSET         0x06
#define BOARD_ID_EEPROM_MINOR_REV_OFFSET         0x07
#define BOARD_ID_EEPROM_REV_STRING_OFFSET        0x08
#define BOARD_ID_EEPROM_SERIAL_NO_OFFSET         0x20
#define BOARD_ID_EEPROM_MAC_MAGIC_OFFSET         0x34
#define BOARD_ID_EEPROM_MAC_VERSION_OFFSET       0x35
#define BOARD_ID_EEPROM_MAC_ADDR_OFFSET          0x38
#define BOARD_ID_EEPROM_BOARD_DRAM_OFFSET        0x80

#define JUNIPER_JDEC_CODE                       0x7fb0
#define JUNIPER_EEPROM_FORMAT_V1                0x01
#define JUNIPER_EEPROM_FORMAT_V2                0x02
#define JUNIPER_MAC_MAGIC                       0xad
#define JUNIPER_MAC_VERSION                     0x01
#define SERIAL_STR_LEN                          0x0c


#define ID_EEPROM_ALEN 1
#define JSRXNLE_I2C_SUCCESS 1
#define JSRXNLE_I2C_ERR 0

uint8_t board_read_id_eeprom(uint8_t offset);
uint8_t board_write_id_eeprom(uint8_t offset, uint8_t val);

/* defined in each board */
int is_valid_board_type(uint16_t type);



#endif

