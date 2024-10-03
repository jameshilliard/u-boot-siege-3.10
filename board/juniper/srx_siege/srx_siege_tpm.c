/*
 * Copyright (c) 2007-2016, Juniper Networks, Inc.
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
#include <command.h>
#include <tpm.h>
#include "srx_siege_board.h"
#include "srx_siege_cpld.h"
#include "srx_siege_tpm.h"

DECLARE_GLOBAL_DATA_PTR;

/* #define TPM_DEBUG */

#define MAX_DELAY_US (1000 * 1000)


static uint8_t
cpld_tpm_chk_ready(void)
{
    uint32_t time_us = MAX_DELAY_US;

    while (time_us > 0) {

        if (cpld_chk_tpm_busy()) {
            udelay(1); /* 1 us */
            time_us--;
        } else {
            return 1;
        }
    }
    uart_debug("\n TPM Not Ready.. ");
    return 0;
}

/* TPM access wrappers to support tracing */
uint8_t tpm_read_byte(uint8_t *ptr)
{
    uint8_t      value=0;
    uint32_t addr;

    addr = (uint32_t) ptr;

    if (cpld_tpm_chk_ready()) {
        /* Write ADDR[0:7] to register */
        cpld_set_lpc_addr_byte1(addr & 0xff);

        /* Write ADDR[15:8] to register */
        cpld_set_lpc_addr_byte2(((addr &0xff00) >> 8));

        /* Write bit to start transaction & memory read */
        cpld_start_lpc_mem_read_trans();

        value = cpld_get_trans_result();
        udelay(1);

        if (value == 0) {
            /* Read data in register to get data from TPM */
            value = cpld_get_lpc_din();

            udelay(5); /* 5 us */

#ifdef TPM_DEBUG
            printf("\n tpm_read_byte:  Addr: %04x :\t  %02x ", addr, value);
#endif

        }
    }

    return value;
}


uint32_t tpm_read_word(uint32_t *ptr)
{
    uint32_t ret;
    uint8_t  byte1, byte2, byte3, byte4;
    uint8_t  *ptr_addr = (uint8_t *) ptr;

    byte1 = tpm_read_byte(ptr_addr);
    ptr_addr++;

    byte2 = tpm_read_byte(ptr_addr);
    ptr_addr++;

    byte3 = tpm_read_byte(ptr_addr);
    ptr_addr++;

    byte4 = tpm_read_byte(ptr_addr);

    ret = (byte4 << 24);        /* bits 31 to 24 */
    ret = (ret | (byte3 << 16));    /* bits 23 to 16 */

    ret = (ret | (byte2 << 8)); /* bits 8 to 15 */
    ret = (ret | byte1);        /* bits 7 to 0  */

#ifdef TPM_DEBUG
    printf("\n tpm_read_word: Addr: %08x :\t  %08x ", ptr, ret);
#endif

    return ret;
}


void tpm_write_byte(uint8_t data, uint8_t *ptr)
{
    if (cpld_tpm_chk_ready())
    {
        volatile uint8_t value;
        uint32_t         addr;

        addr = (uint32_t) ptr;

        /* Write ADDR[0:7] to register */
        cpld_set_lpc_addr_byte1(addr & 0xff);

        /* Write ADDR[15:8] to register */
        cpld_set_lpc_addr_byte2((addr & 0xff00) >> 8);

        /* Write data to data out register */
        cpld_set_lpc_dout(data);

        /* Start transaction */
        cpld_start_lpc_mem_write_trans();

        value = cpld_get_trans_result();

        if (value == 0) {
#ifdef TPM_DEBUG
        printf("\n tpm_write_byte: Addr: %08x = %02x ", ptr, data);
#endif
        } else {
#ifdef TPM_DEBUG
        printf("\n tpm_write_byte failed: Addr: %08x = %02x return %d", ptr, data, value);
#endif
        }
    } else {
#ifdef TPM_DEBUG
        printf("\n tpm_write_byte failed: cpld_tpm_chk_ready Addr: %08x = %02x ", ptr, data);
#endif

    }
}

void tpm_write_word(uint32_t value, uint32_t *ptr)
{
    uint8_t  value_to_write;
    uint8_t  *ptr_addr = (uint8_t *) ptr;

    value_to_write = (value & 0xff);
    tpm_write_byte(value_to_write, ptr_addr); /* write 0 to 7 bits */
    ptr_addr++;

    value_to_write = ((value & 0xff00) >> 8);
    tpm_write_byte(value_to_write, ptr_addr); /* write 8 to 15 bits */
    ptr_addr++;

    value_to_write = ((value & 0xff0000) >> 16);
    tpm_write_byte(value_to_write, ptr_addr); /* write 16 to 23 bits */
    ptr_addr++;

    value_to_write = ((value & 0xff000000) >> 24);
    tpm_write_byte(value_to_write, ptr_addr); /* write 24 to 31 bits */

#ifdef TPM_DEBUG
    printf("\n tpm_write_word: Addr: %08x = %08x ", ptr, value);
#endif

}


void siege_tpm_chk_deactivated(void)
{
    uint8_t data[50];
    unsigned int rc;
    int count = 50;

    /*
     * Get TPM_PERMANENT_FLAGS structure contents
     * Capability flag = TPM_CAP_FLAG
     * Sub Flag = TPM_CAP_FLAG_PERMANENT
     */
    rc = tpm_get_capability(TPM_CAP_FLAG, TPM_CAP_FLAG_PERMANENT, data, count);
    if (rc) {
        printf("\nTPM: error getting TPM_CAP_FLAG_PERMANENT contents!!!\n");
        return;
    }

    /*
     * Enable TPM first to execute the required commands
     */
    rc = tpm_tsc_physical_presence(TPM_PHYSICAL_PRESENCE_PRESENT);
    rc = tpm_physical_enable();

    if (data[TPM_CAP_DEACTIVATED_OFFSET] == 0x01) {
        rc = tpm_physical_set_deactivated(0);
        rc = tpm_get_capability(TPM_CAP_FLAG, TPM_CAP_FLAG_PERMANENT, data, count);
        if (data[TPM_CAP_DEACTIVATED_OFFSET] == 0x01) {
            printf("\nError!!!, clearing deactivated flag\n");
        } else {
            printf("\nResetting board to activate TPM...\n");
            cpld_board_reset_all();
        }
    }
}


int siege_tpm_init(void)
{
    unsigned int rc;

    rc = tpm_init();
    if (!rc) {
        rc = tpm_startup(TPM_ST_CLEAR);
        if (!rc) {
            rc = tpm_self_test_full();
            if (!rc) {

                /*
                 * Ignore error as life time lock already set, but if it is
                 * not make sure this command is executed, and in case of error
                 * next command will fail
                 */
                rc =
                    tpm_tsc_physical_presence(TPM_PHYSICAL_PRESENCE_CMD_ENABLE);
                siege_tpm_chk_deactivated();
                printf("TPM initialized\n");
            } else {
                printf("TPM: Self Test Error.\n");
                return 1;
            }
        } else {
            printf("TPM: Startup Error.\n");
            return 1;
        }
    } else {
        printf("TPM: Init Error.\n");
        return 1;
    }

    return 0;
}






