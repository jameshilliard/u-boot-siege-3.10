
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
#include <command.h>
#include "srx_siege_board.h"

DECLARE_GLOBAL_DATA_PTR;

uint8_t
cpld_is_boot_from_backup (void)
{
    uint8_t val;
    val = cpld_read(CPLD_REG_MISC);

    if (val & (1<<5))
        return 1;
    else
        return 0;
}

uint8_t
cpld_read (uint8_t addr)
{
    return *((volatile uint8_t *)(BOARD_CPLD_BASE + addr));
}

void
cpld_write (uint8_t addr, uint8_t val)
{
    volatile uint8_t *ptr;

    ptr = (volatile uint8_t *)(BOARD_CPLD_BASE | addr);
    *ptr = val;
}

void
cpld_set_bootfinish (void)
{
    uint8_t val;
    val = cpld_read(CPLD_REG_MISC);
    val |= (1<<6);
    cpld_write(CPLD_REG_MISC, val);
}

void
cpld_switch_spi (uint32_t is_backup)
{
    static int first_check = 1;
    uint8_t val, correct_dev_sel;

    /* for evb board UT test */
    val = cpld_read(CPLD_REG_MISC);

    /* if box boot from backup flash, BOOT_SECTOR is 1
     * but BOOT_DEV_SEL is 0, in this case, we need to
     * switch 1 first, and then switch to 0 */
    if (first_check) {
        correct_dev_sel = cpld_is_boot_from_backup()<<4;
        if (correct_dev_sel != (val & 0x10)) {
            val &= 0xef;
            val |= correct_dev_sel;

            cpld_write(CPLD_REG_MISC, val);
            mdelay(1);
            val = cpld_read(CPLD_REG_MISC);
        }
        first_check = 0;
    }

    correct_dev_sel = is_backup << 4;
    if (correct_dev_sel != (val & 0x10)) {
        val &= 0xef;
        val |= correct_dev_sel;

        cpld_write(CPLD_REG_MISC, val);
        mdelay(1);
    }
}

void
cpld_board_reset (void)
{
    uint8_t temp;
    uint8_t device_reset_mask = 0xf9;

    /*
     * Reset all devices except for CPU
     */
    temp = cpld_read(CPLD_REG_RESET1);
    temp &= ~(device_reset_mask);
    cpld_write(CPLD_REG_RESET1, temp);

    /*
     * wait for 50 milliseconds before pulling
     * devices out of reset.
     */
    udelay(50000);

    /* pull devices out of reset */
    temp |= device_reset_mask;
    cpld_write(CPLD_REG_RESET1, temp);
    /* wait 100 milliseconds */
    udelay(100000);
}

void
cpld_board_reset_all (void)
{
    uint8_t temp;

    /*
     * Reset all devices except for CPU
     */
    temp = cpld_read(CPLD_REG_RESET1);
    temp &= ~(0x1<<1);
    cpld_write(CPLD_REG_RESET1, temp);

}


void
cpld_usb_enable (void)
{
    uint8_t val;

    val = cpld_read(CPLD_REG_USB_STATUS_CTL);
    val |= 0x1;
    cpld_write(CPLD_REG_USB_STATUS_CTL, val);
}

void
cpld_set_led_status_amber(void)
{
    uint8_t val;
    val = cpld_read(CPLD_REG_BOARD_LED_CTL);
    val |= ((1<<2) | (1<<3)); /* set both status green and status red on */

    cpld_write(CPLD_REG_BOARD_LED_CTL, val);
}

void
enable_srx_siege_cpld_watchdog (void)
{
    uint8_t val;
    val = cpld_read(CPLD_REG_MISC);

    cpld_write(CPLD_REG_MISC, (val | 0x1));
}

void
disable_srx_siege_watchdog (void)
{
    uint8_t val;
    val = cpld_read(CPLD_REG_MISC);

    /* clear bit1 */
    cpld_write(CPLD_REG_MISC, (val & 0xfe));
}


void
pat_srx_siege_cpld_watchdog (void)
{
    /* Clear CPLD register 4 to clear watchdog counter */
    cpld_write(4, 0x00);
}

void
cpld_set_fan_speed (uint8_t spd_percent)
{
    uint8_t fanspd;
    uint8_t misc, misc2;

    fanspd = (spd_percent > 100) ? 100:spd_percent;
    fanspd = fanspd/14;

    misc = cpld_read(CPLD_REG_MISC);
    misc2 = cpld_read(CPLD_REG_MISC2);

    misc &= 0xf3;  /* clear bit2, bit3 */
    misc2 &= 0xf7;   /* clear bit3*/

    misc |= ((fanspd & 0x6)<< 1);  /* fanspd bit1, bit2 goto misc bit2, bit3 */
    misc2 |= ((fanspd & 0x1)<< 3);  /* fanspd bit0, misc2 bit3 */

    cpld_write(CPLD_REG_MISC, misc);
    cpld_write(CPLD_REG_MISC2, misc2);
}

/*
 * Get status of Ready bit in LPC CSR register.
 *
 * if set   - TPM is busy
 * if clear - TPM is ready
 */
int cpld_chk_tpm_busy(void)
{
    uint8_t lpc_csr_reg_val;

    lpc_csr_reg_val = cpld_read(CPLD_REG_LPC_CTRL_STATUS);

    return (lpc_csr_reg_val & 0x1);
}

/*
 * Set Address[7:0] to transfer to TPM
 *
 */
void cpld_set_lpc_addr_byte1(uint8_t addr_val)
{
    cpld_write(CPLD_REG_LPC_ADDRESS_BYTE1, addr_val);
}

/*
 * Set Address[15:8] to transfer to TPM
 *
 */
void cpld_set_lpc_addr_byte2(uint8_t addr_val)
{
    cpld_write(CPLD_REG_LPC_ADDRESS_BYTE2, addr_val);
}

/*
 * Start a Memory Read Transaction
 *  - Set memory read cycle type - 1 for memory read
 *  - Set start transaction bit
 *
 */
void cpld_start_lpc_mem_read_trans(void)
{
    uint8_t lpc_csr_reg_val;

    lpc_csr_reg_val = cpld_read(CPLD_REG_LPC_CTRL_STATUS);

    /* Set Memory Read cycle type */
    lpc_csr_reg_val |= (0x1<<1);

    /* Start transaction */
    lpc_csr_reg_val |= (0x1<<3);
    cpld_write(CPLD_REG_LPC_CTRL_STATUS, lpc_csr_reg_val);
}

/*
 * Start a Memory Write Transaction
 * - Set memory write cycle type - 0 for memory write
 * - Set start transaction bit
 *
 */
void cpld_start_lpc_mem_write_trans(void)
{
    uint8_t lpc_csr_reg_val;

    lpc_csr_reg_val = cpld_read(CPLD_REG_LPC_CTRL_STATUS);

    /* Set Memory Write cycle type */
    lpc_csr_reg_val &= ~(0x1<<1);  /* cleare bit 1*/

    /* Start transaction */
    lpc_csr_reg_val |= (0x1<<3); /*set bit 3*/

    cpld_write(CPLD_REG_LPC_CTRL_STATUS, lpc_csr_reg_val);
}


/*
 * Check LPC transaction result
 *
 *  00 - Success
 *  01 - Additional Wait States by Peripheral
 *  02 - Error
 */
int cpld_get_trans_result(void)
{
    uint8_t lpc_csr_reg_val;

    lpc_csr_reg_val = cpld_read(CPLD_REG_LPC_CTRL_STATUS);
    return ((lpc_csr_reg_val >> 4) & 0x3);  /* return bit4,5 */
}

/*
 * Get LPC Data In register value which is read from
 * peripheral
 *
 */
uint8_t cpld_get_lpc_din(void)
{
    uint8_t tpm_din_val;

    tpm_din_val = cpld_read(CPLD_REG_LPC_DATA_IN);

    return tpm_din_val;
}

/*
 * Set LPC Data Out register value to transmit to
 * peripheral
 *
 */
void cpld_set_lpc_dout(uint8_t data_out)
{
    cpld_write(CPLD_REG_LPC_DATA_OUT, data_out);
}



