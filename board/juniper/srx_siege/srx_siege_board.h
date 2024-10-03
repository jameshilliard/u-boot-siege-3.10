
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

#ifndef __SRX_SIEGE_BOARD_H__
#define __SRX_SIEGE_BOARD_H__

#define SIEGE_LOCAL_BUS_REGION_1_BASE 0x1fbf0000
#include "srx_siege_cpld.h"


#define I2C_ID_SRX550M_CHASSIS                   0x058E  /* SRX550M Chassis */

#define I2C_ID_JSRXNLE_SRX300_BASE_PIC                  0x0680  /* SRX300 base PIC */
#define I2C_ID_JSRXNLE_SRX320_BASE_PIC                  0x0681  /* SRX320 base PIC */
#define I2C_ID_JSRXNLE_SRX340_BASE_PIC                  0x0682  /* SRX340 base PIC */

#define I2C_ID_JSRXNLE_SRX300_BASE_COMBO_FPC         0x0780  /* SRX300 baseboard FPC */
#define I2C_ID_JSRXNLE_SRX320_BASE_COMBO_FPC         0x0781  /* SRX320 baseboard FPC */
#define I2C_ID_JSRXNLE_SRX340_BASE_COMBO_FPC         0x0782  /* SRX340 baseboard FPC */

#define CASE_ALL_I2CID_SRX380_CHASSIS        \
    case I2C_ID_JSRXNLE_SRX380_POE_AC_CHASSIS:

#define CASE_ALL_I2CID_SRX300_CHASSIS        \
    case I2C_ID_JSRXNLE_SRX300_CHASSIS:      \
    case I2C_ID_JSRXNLE_SRX300_LEM_CHASSIS:

#define CASE_ALL_I2CID_SRX320_CHASSIS        \
    case I2C_ID_JSRXNLE_SRX320_CHASSIS:      \
    case I2C_ID_JSRXNLE_SRX320_LEM_CHASSIS:\
    case I2C_ID_JSRXNLE_SRX320_LTE_AA_CHASSIS:\
    case I2C_ID_JSRXNLE_SRX320_LTE_AE_CHASSIS:

#define CASE_ALL_I2CID_SRX320_POE_CHASSIS     \
    case I2C_ID_JSRXNLE_SRX320_POE_CHASSIS:   \
    case I2C_ID_JSRXNLE_SRX320_POE_LEM_CHASSIS:\
    case I2C_ID_JSRXNLE_SRX320_POE_LTE_AA_CHASSIS:\
    case I2C_ID_JSRXNLE_SRX320_POE_LTE_AE_CHASSIS:

#define CASE_ALL_I2CID_SRX340_CHASSIS       \
    case I2C_ID_JSRXNLE_SRX340_CHASSIS:     \
    case I2C_ID_JSRXNLE_SRX340_LEM_CHASSIS:

#define CASE_ALL_I2CID_SRX345_CHASSIS       \
    case I2C_ID_JSRXNLE_SRX345_CHASSIS:     \
    case I2C_ID_JSRXNLE_SRX345_LEM_CHASSIS: \
    case I2C_ID_JSRXNLE_SRX345_DUAL_AC_CHASSIS:\
    case I2C_ID_JSRXNLE_SRX345_DC_CHASSIS:


#define CASE_ALL_JSRX_SWORD_MODELS \
    CASE_ALL_I2CID_SRX300_CHASSIS    \
    CASE_ALL_I2CID_SRX320_CHASSIS    \
    CASE_ALL_I2CID_SRX320_POE_CHASSIS

#define CASE_ALL_JSRX_TRIDENT_MODELS \
    CASE_ALL_I2CID_SRX340_CHASSIS   \
    CASE_ALL_I2CID_SRX345_CHASSIS

#define CASE_ALL_JSRX_SIEGE_MODELS \
        CASE_ALL_JSRX_SWORD_MODELS \
        CASE_ALL_JSRX_TRIDENT_MODELS

#define CASE_ALL_JSRX_AIRBUS_MODELS \
    CASE_ALL_I2CID_SRX380_CHASSIS


#define IS_PLATFORM_SWORD(board_type) \
                ((((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX300_CHASSIS)    \
              || (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX320_CHASSIS)    \
              || (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX320_POE_CHASSIS)    \
              || (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX300_LEM_CHASSIS)    \
              || (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX320_LEM_CHASSIS)    \
              || (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX320_POE_LEM_CHASSIS)\
              || (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX320_LTE_AA_CHASSIS)    \
              || (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX320_LTE_AE_CHASSIS)    \
              || (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX320_POE_LTE_AA_CHASSIS)    \
              || (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX320_POE_LTE_AE_CHASSIS))


#define IS_PLATFORM_TRIDENT(board_type) \
                ((((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX340_CHASSIS)    \
              || (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX345_CHASSIS)    \
              || (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX340_LEM_CHASSIS) \
              || (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX345_LEM_CHASSIS) \
              || (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX345_DUAL_AC_CHASSIS) \
              || (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX345_DC_CHASSIS))


#define IS_PLATFORM_SIEGE(board_type) \
                 (IS_PLATFORM_SWORD(board_type)      ||  \
                  IS_PLATFORM_TRIDENT(board_type))

#define IS_PLATFORM_AIRBUS(board_type) \
    (((uint16_t)board_type) == I2C_ID_JSRXNLE_SRX380_POE_AC_CHASSIS)



void srx_siege_boot_bus_init(void);
void srx_airbus_boot_bus_init(void);


int board_spi_flash_read( u32 offset,
        size_t len,
        void *buf,
        uint32_t is_backup);

int board_spi_flash_write(uint32_t mem_addr,
        uint32_t flash_start,
        uint32_t size,
        uint32_t is_backup);

int board_spi_flash_erase(uint32_t flash_start,
                        uint32_t size,
                        uint32_t is_backup);

int board_spi_flash_update(uint32_t offset,
                        uint32_t len,
                        const char *buf,
                        uint32_t is_backup);


int check_ushell_magic_key(void * ushell_mem_buf);
uint16_t board_type_2_memory_type(uint16_t type);

extern int   ethact_init;





#endif  /* __SRX_SIEGE_BOARD_H__ */


