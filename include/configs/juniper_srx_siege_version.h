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

#ifndef __juniper_srx_siege_version_h__
#define __juniper_srx_siege_version_h__

/*
 * 3.0 first srx siege u-boot version
 * 3.1 fix eUSB detect problem.
 * 3.2 check boot_unattended env to disable input when bootdelay=0 
 * 3.3 add support for LTE related boards.
 * 3.4 Disable memory commands, disable boot from slice 3.
 * 3.5 when configured boot_unattend, will not enter recovery mode.
 * 3.6 disable boot loader when 'Unsupported flash IDs' happen, to avoid spi flash hacker.
 *     hide boot elf image address info.
 * 3.8 update to SDK3.12, support Airbus
 * 3.9 support veloader 
 * 3.10 disable SATA for veloader if not support boot from it,
 *      support new flash for srx380 
 * */

#define UBOOT_API_REVISION_NUMBER   "3.10"

/* macro U_BOOT_VERSION will like "U-Boot 2013.7-JNPR-x.x" */
#define CONFIG_VENDOR_U_BOOT_VER_APPEND "-JNPR-3.10"


#endif

