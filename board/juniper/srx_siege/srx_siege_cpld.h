
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
#ifndef __SRX_SIEGE_CPLD_H__
#define __SRX_SIEGE_CPLD_H__

#define BOARD_CPLD_BASE SIEGE_LOCAL_BUS_REGION_1_BASE

#define CPLD_REG_CPLD_VER           0x00
/* Bit[7:4],CPLD version */
/* Bit[3:0],CPLD revision */

#define CPLD_REG_BOARD_LED_CTL      0x01
/*
   Bit7 Red power LED on front panel control.
   Bit6 Green power LED
   Bit5 Red alarm LED
   Bit4 Green alarm LED
   Bit3 Green status LED. CAUTION: the bit sequence of status LED is swapped
   Bit2 Red status LED
   Bit1 Red HA (High available) LED
   Bit0 Green HA LED
   Write '1' to turn on the LED, '0' to turn off.
   All LEDs are dual-color LEDs. If red and green are lit up at the same time. User will see yellow color.
 */

#define CPLD_REG_RESET1             0x02
/*
   Reset value: 0xff
   Bit7 Reset mini-PIM 4  (Trident only)
   Bit6 Reset mini-PIM 3  (Trident only)
   Bit5 Reset mini-PIM 2
   Bit4 Reset POE controller BCM59121 (Sword-M-POE only)
   Bit3 Reset Ethernet sub-system (including all switch and PHYs)
   Bit2 Reset the CPU
   Bit1 Reset all components on the board
   Bit0 Reset mini-PIM 1
   1' for normal operation. '0' for reset.
   A write to "Board reset" bit will reset all the devices on board.
   All bits except CPU bit have to be restored to '1' by software after reset.
 */

#define CPLD_REG_MISC               0x03
/*
    Bit7    Bit6    Bit5    Bit4    Bit3     Bit2       Bit1        Bit0
            BOOT    BOOT    BOOT    FAN      FAN        Power       Watchdog
            FINISHED SECTOR DEV_SEL SPEED B2 SPEED_B1   cycling     enable
            RW      RO      RW      RW       RW         RW          RW
            0       0       0       1        1          0           1
    Reset value:    0x0d
    Bit6    Boot finished flag. Software should write to this bit to notify CPLD a boot up process is finished.
        Or a reboot will occure.
    Bit5    Current boot device. This is a read only version of "boot device select" bit.
        It's here for compatibility reason.
    Bit4    Boot device select. 0: boot from SPI FLASH 1 next time. 1: Boot from SPI FLASH 2.
        Write to this bit will change the boot device selection. This bit will be inverted automatically
        if a boot up process doesn't finished in time.
    Bit[3:2]    Bit 2 and 1 of fan speed control. Bit 0 (LSB) is in MISC2 register
        The register value and speed setting relation is:
        FANSPD[2:0] Speed (percent of full speed)
        3'b000  0 (stopped)
        3'b001  14
        3'b010  28
        3'b011  42
        3'b100  56
        3'b101  70
        3'b110  84
        3'b111  100 (full speed)
    Bit1    Power cycling. Write '1' will turn the power of the whole device off.
        Power won't be restored automatically.
    Bit0    Watchdog enable. '1' is enable
*/

#define CPLD_REG_WATCHDOG_VAL       0x04
#define CPLD_REG_INT_EN1            0x05
#define CPLD_REG_INT_STATUS1        0x06
#define CPLD_REG_MPIM_FPGA_CFG      0x07

#define CPLD_REG_FAN_TACHO_1_2      0x08
#define CPLD_REG_FAN_TACHO_3_4      0x09
#define CPLD_REG_FAN_TACHO_5_6      0x0a

#define CPLD_REG_MISC2              0x0b
#define CPLD_REG_MUX_SELECT         0x0c
#define CPLD_REG_MPIM_INT_EN        0x0d
#define CPLD_REG_MPIM_INT_STATUS    0x0e
#define CPLD_REG_PROTOTYPE_ID       0x0f
#define CPLD_REG_BOARD_ID           0x10


#define CPLD_REG_MPIM_LED_CTL           0x1c
#define CPLD_REG_USB_STATUS_CTL         0x1d

#define CPLD_REG_RESET2                 0x20
#define CPLD_REG_RESET3                 0x21
#define CPLD_REG_INT_EN_2               0x22
#define CPLD_REG_INT_STATUS_2           0x23
#define CPLD_REG_INT_EN_3               0x24
#define CPLD_REG_INT_STATUS_3           0x25
#define CPLD_REG_CONSOLE_STATUS_CTL     0x26
#define CPLD_REG_MPIM_PRESENT           0x27
#define CPLD_REG_SFP_PRESENT            0x28
#define CPLD_REG_SFP_TX_FAULT           0x29
#define CPLD_REG_SFP_TX_DISABLE         0x2a
#define CPLD_REG_POWER_GOOD_STATUS      0x2b

#define CPLD_REG_PLL_COREVOLTAGE        0x30
#define CPLD_REG_PLL_AUTOSET_STATUS     0x31
#define CPLD_REG_PLL_AUTOSET_CTL        0x32

#define CPLD_REG_FAN_1_TACH0        0x35
#define CPLD_REG_FAN_2_TACH0        0x36
#define CPLD_REG_FAN_3_TACH0        0x37
#define CPLD_REG_FAN_4_TACH0        0x38

#define CPLD_REG_LPC_CTRL_STATUS        0x40

#define CPLD_REG_LPC_ADDRESS_BYTE1      0x41
#define CPLD_REG_LPC_ADDRESS_BYTE2      0x42
#define CPLD_REG_LPC_DATA_IN            0x43
#define CPLD_REG_LPC_DATA_OUT            0x44


extern uint8_t cpld_read(uint8_t addr);
extern void    cpld_write(uint8_t addr, uint8_t val);
void cpld_switch_spi(uint32_t is_backup);
void enable_srx_siege_cpld_watchdog (void);
void pat_srx_siege_cpld_watchdog (void);
void disable_srx_siege_watchdog (void);
void cpld_usb_enable(void);
void cpld_set_fan_speed(uint8_t speed_percent);
uint8_t cpld_is_boot_from_backup(void);
void cpld_set_bootfinish(void);
void cpld_board_reset(void);
void cpld_board_reset_all(void);
void cpld_set_led_status_amber(void);

int  cpld_chk_tpm_busy(void);
void cpld_set_lpc_addr_byte1(uint8_t addr_val);
void cpld_set_lpc_addr_byte2(uint8_t addr_val);
void cpld_start_lpc_mem_read_trans(void);
void cpld_start_lpc_mem_write_trans(void);
int cpld_get_trans_result(void);
uint8_t cpld_get_lpc_din(void);
void cpld_set_lpc_dout(uint8_t data_out);



#endif




