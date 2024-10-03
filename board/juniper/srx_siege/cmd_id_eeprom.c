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


/* ID EEPROM support for JSRXNLE boards */

#include <common.h>
#include <command.h>
#include <watchdog_cpu.h>
#include <cvmx.h>
#include <lib_octeon_shared.h>
#include <octeon_boot.h>
#include <configs/octeon_common.h>
#include <i2c.h>
#include "../common/juniper_board_common.h"
#include "srx_siege_board.h"

static void
eeprom_print_all (void)
{
    unsigned int i = 0;
    unsigned int addr = 0;
    unsigned int total = BOARD_ID_EEPROM_BOARD_DRAM_OFFSET;
    unsigned int linebytes;
#define LINE_LEN 16
    unsigned char   linebuf[LINE_LEN];

    do {
        linebytes = (total - addr > LINE_LEN) ? LINE_LEN : (total - addr);

        /* read a line data */
        for (i=0; i<linebytes; i++) {
            linebuf[i] = board_read_id_eeprom(addr + i);
        }

        /* write a line */
        printf("%04x:", addr);
        for (i=0; i<linebytes; i++) {
            printf(" %02x", linebuf[i]);
        }

        puts ("    ");
        for (i=0; i<linebytes; i++) {
            if ((linebuf[i] < 0x20) || (linebuf[i] > 0x7e))
                puts (".");
            else
                printf("%c", linebuf[i]);
        }
        putc ('\n');

        addr += linebytes;

    } while (addr < total);

}

static int
do_eeprom_at24c (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    int rcode;

    switch (argc) {
    case 0:
    case 1:
        printf ("Usage:\n%s\n", cmdtp->usage);
        rcode = 1;
        break;

    case 2:
        if (strcmp(argv[1],"read") == 0) {
            eeprom_print_all();
        } else {
            printf ("Usage:\n%s\n", cmdtp->usage);
            rcode = 1;
        }
        break;
    case 3:
        if (strcmp(argv[1],"read") == 0) {
            uint8_t val;
            uint8_t offset = (uint8_t)simple_strtoul(argv[2], NULL, 16);

            val = board_read_id_eeprom(offset);
            printf("board_read_id_eeprom: offset 0x%x value 0x%x\n", offset, val);
        } else {
            printf ("Usage:\n%s\n", cmdtp->usage);
            rcode = 1;
        }
        break;
    case 4:
        if (strcmp(argv[1],"write") == 0) {
            uint8_t offset = (uint8_t)simple_strtoul(argv[2], NULL, 16);
            uint8_t val = (uint32_t)simple_strtoul(argv[3], NULL, 16);

            if (board_write_id_eeprom(offset, val)) {
                printf( "board_write_id_eeprom: failed to write to offset 0x%x \n",
                        offset);
            }
            else {
                printf("board_write_id_eeprom: offset 0x%x value 0x%x\n", offset, val);
            }
        } else {
            printf ("Usage:\n%s\n", cmdtp->usage);
            rcode = 1;
        }
        break;
    default:
        printf ("Usage:\n%s\n", cmdtp->usage);
        rcode = 1;
        break;
    }

    return rcode;
}

U_BOOT_CMD(
	id_eeprom, 10, 1, do_eeprom_at24c,
	"id_eeprom     - peek/poke EEPROM",
	"id_eeprom read  <offset>\n"
	"    - read the specified EEPROM offset\n"
	"id_eeprom write <offset> <value>\n"
	"    - write 'value' at the specified EEPROM offset\n"
);
