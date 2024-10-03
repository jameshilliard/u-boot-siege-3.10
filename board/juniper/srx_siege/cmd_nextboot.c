/*
 * Copyright (c) 2015-2020, Juniper Networks, Inc.
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
#include <platform_srx_siege.h>

static int
do_nextboot(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    int i;
    unsigned char bootdev[64];

    switch (argc) {
    case 0:
    case 1:
        printf ("Usage:\n%s\n", cmdtp->usage);
        show_bootdev_list();

        get_next_bootdev(bootdev, 0);
        /* bootdev format: disk0s1 */
        printf("Current bootdev: %s, %s\r\n",
                get_devname_by_disk_id(bootdev[4]-'0'), bootdev);

        return 1;

    case 2:
        if (srx_siege_is_valid_devname(argv[1])) {
            set_next_bootdev(argv[1]);
            update_loaderdev();
            printf("Set next boot device: %s\r\n", argv[1]);
            return 0;
        }

        show_bootdev_list();
        return 1;

    default:
        show_bootdev_list();
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }
}

U_BOOT_CMD(
	nextboot, 2, 1, do_nextboot,
	"nextboot - get/set nextboot",
	"nextboot   \n"
	"    - read next boot device\n"
	"nextboot  <dev>\n"
	"    - set next boot device\n"
);
