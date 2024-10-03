/*
 * Copyright (c) 2008-2015, Juniper Networks, Inc.
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

/* MDK functions */

#include <common.h>
#include <cvmx.h>
#include <lib_octeon_shared.h>
#include <octeon_boot.h>
#include <configs/octeon_common.h>
#include <asm/arch/cvmx-mdio.h>
#include "srx_siege_board.h"
#include "srx_siege_cpld.h"
#include <exports.h>
#include <platform_srx_siege.h>

DECLARE_GLOBAL_DATA_PTR;

static uint32_t bcm_mdk_dram_start_addr = CFG_MDK_DRAM_START_ADDR;
static uint32_t bcm_mdk_sz = CFG_USHELL_SIZE;
extern int loader_init;
uint32_t ushell_running = 0;

static int
run_mdk (void)
{
    int rc;

    ushell_running = 1;
    /* run the bcm ushell entry function which is loaded to memory */
    rc = ((int (*)(int, char *[]))bcm_mdk_dram_start_addr)(0, NULL);
    ushell_running = 0;
    return rc;
}

int
check_ushell_magic_key (void * ushell_mem_buf)
{
    if ((*(uint32_t *)(ushell_mem_buf) & 0xffff0000)
            != CFG_MDK_MAGIC_KEY) {
        return -1;
    }
    return 0;
}


/* copies ushell from bootflash to DRAM */
int32_t
copy_mdk(uint32_t is_backup)
{
    int loop;
    uint32_t bcm_mdk_boot_start_addr;
    void *buf = CONFIG_USHELL_IMAGE_VERIFY_ADDR;

    switch (gd->arch.board_desc.board_type) {
    CASE_ALL_JSRX_SWORD_MODELS
        bcm_mdk_boot_start_addr = CFG_SPI_FLASH_USHELL_START;
        break;
    default:
        printf("MDK not needed by this platform\n");
        return 1;
    }


    if (board_spi_flash_read(bcm_mdk_boot_start_addr,
                CFG_USHELL_SIZE, buf, is_backup)) {
        printf("Could not read SPI flash to find uboot\n");
        return 1;
    }

    /*
     * Check magic key of MDK application,If it doesn't
     * exist then don't initialize the switch
     */
    if (check_ushell_magic_key(buf) < 0) {
        printf("Switch driver image not programmed properly in bootflash\n");
        printf("Expected 0x%x, actual 0x%x\n",
                CFG_MDK_MAGIC_KEY, *(uint32_t *)(buf));
        return 1;
    }


    /* bcm_mdk_sz is multiple of 4 */
    for (loop = 0; loop < bcm_mdk_sz/4; ++loop) {
        memcpy((void *)(bcm_mdk_dram_start_addr + (loop * 4)),
           (void *)((uint32_t)buf + (loop * 4)),
           sizeof (uint32_t));
    }

    return 0;
}

#define CVMX_SRX_SWORD_IFACE 0

int
mdk_init (void)
{
    int rc;
    int rcode = 0;
    int iface;
    uint32_t bcm_mdk_boot_start_addr;

    switch (gd->arch.board_desc.board_type) {
    CASE_ALL_JSRX_SWORD_MODELS
        bcm_mdk_boot_start_addr = CFG_SPI_FLASH_USHELL_START;
        iface = CVMX_SRX_SWORD_IFACE;
        break;
    default:
        return 0;
    }

    if (copy_mdk(0)) {
        return 1;
    };

    /*
     * pass address parameter as argv[0] (aka command name),
     * and all remaining args
     */
    rc = run_mdk();
    if (rc != 0)
        rcode = 1;

    /*
     * pass address parameter as argv[0] (aka command name),
     * and all remaining args
     */
    rc = run_mdk();
    if (rc != 0)
        rcode = 1;

    if (rcode) {
        printf("Error: Broadcom Mini-Driver Kit Initialization failed\n");
    }

    return rcode;
}


void
do_link_update (void)
{
    /* If mdk_init not happened then don't do link update */
    if (!ethact_init) {
        return;
    }

    /*
     * Do link update for SRX240 boards. This is needed to update
     * internal phy and MAC with autoneg results. The same is not
     * required for SRX650 as there we only use external PHY as we
     * have sysio BCM in between. Internal PHY and MAC of base board
     * remains at 1G there
     */
    switch (gd->arch.board_desc.board_type) {
    CASE_ALL_JSRX_SWORD_MODELS
        /* Process link update on BCM ushell */
        setenv("linkUpdate", "1");

        /*
         * when tftp is going on and if tftp server is killed, u-boot tries
         * to re-init the mdk and if tftp has transfered more than 1MB
         * it would have overwritten ushell residing at 0x80200000, so
         * verify ushell in DRAM before calling run_mdk()
         */
        if ((*(uint32_t *)(bcm_mdk_dram_start_addr) & 0xffff0000)
                != CFG_MDK_MAGIC_KEY) {
            printf("BCM MDK initializing ...\n");
            if (copy_mdk(0)) {
                printf("Error: copy_mdk failed \n");
                setenv("linkUpdate", "0");
                return;
            }
            /*
             * A second call to run mdk() ensures that the link update of the
             * front/uplink port happens.
             * This is required when ushell is loaded again before tftp install
             */
            (void)run_mdk();
            printf("BCM MDK init done.\n");
        }
        (void)run_mdk();
        setenv("linkUpdate", "0");
        break;
    default:
        break;
    }
}

int
do_mdk_init (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    int     rcode = 0;

    rcode = mdk_init();

    return rcode;
}

#ifdef CONFIG_MDK_DEBUG
/* copies ushell from bootflash to DRAM */
static int32_t
copy_mdk_mem(ulong addr)
{
    int loop;

    /*
     * Check magic key of MDK application,If it doesn't
     * exist then don't initialize the switch
     */
    if (check_ushell_magic_key((void *)addr) < 0) {
        printf("Switch driver image not programmed properly in bootflash\n");
        printf("Expected 0x%x, actual 0x%x\n",
                CFG_MDK_MAGIC_KEY, *(uint32_t *)(addr));
        return 1;
    }

    printf("#### clear ushell target mem \n");
    memset(bcm_mdk_dram_start_addr, 0, 0x400000);
    printf("#### clear ushell target mem done\n ");

    for (loop = 0; loop < 0x80000; ++loop) {
        memcpy((void *)(bcm_mdk_dram_start_addr + (loop * 4)),
           (void *)((uint32_t)addr + (loop * 4)),
           sizeof (uint32_t));
    }

    return 0;
}

/* debug function for testing ushell codes in memory */
int do_test_mdk_mem(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    ulong	addr, rc;
    int     rcode = 0;

    if (argc < 2)
        return CMD_RET_USAGE;

    addr = simple_strtoul(argv[1], NULL, 16);

    printf ("## Starting ushell at 0x%08lX ...\n", addr);
    setenv("linkUpdate", "1");
    if (copy_mdk_mem(addr)) {
        setenv("linkUpdate", "0");
        return 1;
    };
    /*
     * pass address parameter as argv[0] (aka command name),
     * and all remaining args
     */
    rc = run_mdk();
    if (rc != 0)
        rcode = 1;

    /*
     * pass address parameter as argv[0] (aka command name),
     * and all remaining args
     */
    rc = run_mdk();
    if (rc != 0)
        rcode = 1;
    setenv("linkUpdate", "0");

    if (rcode) {
        printf("Error: Broadcom Mini-Driver Kit Initialization failed\n");
    }

    return rcode;

}

U_BOOT_CMD(
        test_mdk_mem, 3, 1,	do_test_mdk_mem,
        "test_mdk_mem - start mdk at address 'addr'",
        "test_mdk_mem - start mdk at address 'addr'\n"
        );

#endif  /* defined CONFIG_MDK_DEBUG */

#if 1
int do_speed(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char *end;
	ulong speed;
    int val;

    /* get speed */
    if (strcmp(argv[1], "get") == 0 ||
        strcmp(argv[1], "ge") == 0 ||
        strcmp(argv[1], "g") == 0) {
        val = cvmx_mdio_read(0, 1, 1);

        printf("reg 1: [0x%x], ", val);
        if (val & (1<<2)) {
            printf("Up \r\n");
        } else {
            printf("Down \r\n");
        }

        /* status */
        val = cvmx_mdio_read(0, 1, 0x19);
        printf("reg 0x19 [0x%x] ", val);
        switch ((val & 0x700) >> 8)
        {
            case 0x7: 
                printf("1000M full\r\n");
                break;
            case 0x6: 
                printf("1000M half\r\n");
                break;
            case 0x5: 
                printf("100T full\r\n");
                break;
            case 0x4: 
                printf("100T4\r\n");
                break;
            case 0x3: 
                printf("100T half \r\n");
                break;
            case 0x2: 
                printf("10M full\r\n");
                break;
            case 0x1: 
                printf("10M half\r\n");
                break;
            default:
                printf("unknown state \r\n");
        }
        return 0;
    }

    if (strcmp(argv[1], "set") == 0 ||
        strcmp(argv[1], "se") == 0 ||
        strcmp(argv[1], "s") == 0) {

        if (strcmp(argv[2], "full") == 0 ||
            strcmp(argv[2], "ful") == 0 ||
            strcmp(argv[2], "fu") == 0 ||
            strcmp(argv[2], "f") == 0 ) {
            /* full speed */
            printf("Enable autoneg all speed at phy 1\r\n");
            cvmx_mdio_write(0, 1, 0x4, 0x1e1);  /* enable 100m, 10m neg */
            cvmx_mdio_write(0, 1, 0x9, 0x300);  /* enable 1000m neg */
            cvmx_mdio_write(0, 1, 0x0, 0x1340);  /* restart neg */

            return 0;
        }

        speed = simple_strtoul(argv[2], &end, 10);
        if (speed == 1000) {
            /* full speed */
            printf("Enable autoneg 1000M speed at phy 1\r\n");
            cvmx_mdio_write(0, 1, 0x4, 0x1);  /* enable 100m, 10m neg */
            cvmx_mdio_write(0, 1, 0x9, 0x300);  /* enable 1000m neg */
            cvmx_mdio_write(0, 1, 0x0, 0x1340);  /* restart neg */
            return 0;
        }

        if (speed == 100) {
            /* full speed */
            printf("Enable autoneg 100/10M speed at phy 1\r\n");
            cvmx_mdio_write(0, 1, 0x4, 0x1e1);  /* enable 100m, 10m neg */
            cvmx_mdio_write(0, 1, 0x9, 0x0);  /* disable 1000m neg */
            cvmx_mdio_write(0, 1, 0x0, 0x1340);  /* restart neg */
            return 0;
        }

        return -1;

    }

    if (strcmp(argv[1], "force") == 0 ||
        strcmp(argv[1], "forc") == 0 ||
        strcmp(argv[1], "for") == 0 ||
        strcmp(argv[1], "fo") == 0 ||
        strcmp(argv[1], "f") == 0) {

        speed = simple_strtoul(argv[2], &end, 10);
        if (speed == 1000) {
            /* force 1000 */
            printf("Force 1000M full duplex at phy 1\r\n");
            cvmx_mdio_write(0, 1, 0x0, 0x0140);  /* bit6 1, bit8 1, bit 12 0,*/
            return 0;
        }

        if (speed == 100) {
            /* force 100 */
            printf("Force 1000M full duplex at phy 1\r\n");
            cvmx_mdio_write(0, 1, 0x0, 0x2100);  /* bit6 0, bit13 1, bit8 1, bit 12 0,*/
            return 0;
        }

        return -1;

    }

    return -1;
}

U_BOOT_CMD(
	speed,	3,	1,	do_speed,
	"set/get/force octrgmii0 max speed",
	"speed get; speed set|force [full | 1000 | 100]"
);

#endif


U_BOOT_CMD(
        mdkinit, 2, 1,	do_mdk_init,
        "mdkinit      - start MDK",
        "mdkinit      - start MDK\n"
        );




