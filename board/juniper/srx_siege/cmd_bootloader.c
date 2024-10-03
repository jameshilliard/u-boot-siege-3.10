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


/*
 * JSRXNLE bootloader upgrade
 */
#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>
#include <asm/arch/octeon_boot.h>
#include <asm/arch/octeon_board_common.h>
#include <asm/arch/octeon_fdt.h>
#include <asm/arch/lib_octeon_shared.h>
#include <asm/arch/lib_octeon.h>

#include "srx_siege_board.h"
#include "srx_siege_cpld.h"

#ifndef CONFIG_SF_DEFAULT_SPEED
# define CONFIG_SF_DEFAULT_SPEED	1000000
#endif
#ifndef CONFIG_SF_DEFAULT_MODE
# define CONFIG_SF_DEFAULT_MODE		SPI_MODE_3
#endif
#ifndef CONFIG_SF_DEFAULT_CS
# define CONFIG_SF_DEFAULT_CS		0
#endif
#ifndef CONFIG_SF_DEFAULT_BUS
# define CONFIG_SF_DEFAULT_BUS		0
#endif

#define IMG_TYPE_UBOOT  1
#define IMG_TYPE_LOADER 2
#define IMG_TYPE_USHELL 3

extern char console_buffer[];

/*
 * This function expects a loader with a header containing crc in
 * the beginning. Its purpose is to srip this CRC header from loader_section_begining
 * and move it to the end.
 */
/*
   move loader data to begin of loader_section
   move loader header to the end of loader_section;
 */
static uint32_t
shuffle_loader_hdr (uint32_t addr, uint32_t ldr_partition_len)
{
    uint32_t ldr_addr, hdr_addr;
    image_header_t header;
    uint32_t target_addr = CONFIG_BOOT_IMAGE_VERIFY_ADDR;

    header = *((image_header_t *)addr);
    ldr_addr = addr + sizeof(image_header_t);
    memcpy((void *)target_addr, (void *)ldr_addr, ldr_partition_len);
    ldr_addr = target_addr;
    hdr_addr = target_addr + ldr_partition_len - sizeof(image_header_t);
    memcpy((void *)hdr_addr, (void *)&header, sizeof(image_header_t));

    return ldr_addr;
}

/*
 * WARNING: This function holds true as long as the image
 * header for the loader lies at the last *sizeof(image_header_t)*
 * bytesof the loader partition.
 *
 * So if the fashion in which the loader is being upgraded
 * changes, please revisit this function. Or while upgrading
 * the loader always make sure that the image header is written
 * in the last of the partition.
 */
static int
is_valid_loader_partition_mem (uint32_t addr, uint32_t partition_len)
{
    uint32_t chksum = 0;
    image_header_t tmp_hdr;
    image_header_t* header =
        (image_header_t*)(addr + partition_len - sizeof(image_header_t));

    if (header->ih_magic != IH_MAGIC) {
        printf("\nWARNING: Image with missing CRC header.\n");
        return 0;
    }

    memcpy(&tmp_hdr, header, sizeof(image_header_t));

    tmp_hdr.ih_hcrc = 0;

    if ((chksum = crc32(0, (uint8_t *)(&tmp_hdr),
                    sizeof(image_header_t))) != header->ih_hcrc) {
        printf("\nWARNING: Image header checksum failure.\n");
        return 0;
    }

    if ((chksum = crc32(0, (uint8_t *)(addr),
                    header->ih_size)) == header->ih_dcrc) {
        return 1;
    }

    printf("\nWARNING: Image data checksum failure.\n");
    return 0;
}

int
is_valid_image_mem (uint32_t addr,
        uint32_t size_limit,
        uint32_t header_offset,
        uint32_t data_offset)
{
    uint32_t chksum = 0;
    image_header_t tmp_hdr;

    image_header_t *header =
        (image_header_t *)(addr + header_offset);

    /* check if the image has a valid magic number */
    if (header->ih_magic != IH_MAGIC) {
        printf("\nWARNING: Image with missing CRC header.\n");
        return 0;
    }

    /*
     * Copy the header to temp and zero out the header
     * checksum field, so that we can verify the header
     * checksum. Only when the header checksum is fine,
     * we can rely on the length of the data field.
     */
    memcpy(&tmp_hdr, header, sizeof(image_header_t));

    tmp_hdr.ih_hcrc = 0;

    /* calculate the header checksum */
    if ((chksum = crc32(0, (unsigned char *)(&tmp_hdr),
                    sizeof(image_header_t))) != header->ih_hcrc) {
        printf("WARNING: Image header checksum failure.\n");
        return 0;
    }

    if ((header->ih_size + data_offset) > size_limit) {
        printf("WARNING: Image size greater than limit size.\n");
        return 0;
    }

    /* calculate the data checksum */
    if ((chksum = crc32(0, (unsigned char *)(addr + data_offset),
                    header->ih_size)) == header->ih_dcrc) {

        /*
         * Check if the size of image can fit in the partition.
         * If the check is being done on the image present in
         * boot flash, the checksum would have already failed.
         * So this case would essentially run when u-boot is
         * being upgraded.
         */

        return 1;
    }

    printf("\nWARNING: Image data checksum failure.\n");
    return 0;
}


int
is_valid_uboot_image_spi (uint32_t spi_addr,
        uint32_t section_size,
        uint32_t is_backup)
{
    void *buf = (void *)CONFIG_BOOT_IMAGE_VERIFY_ADDR;

    if (board_spi_flash_read(CFG_SPI_FLASH_UBOOT_START,
                CFG_UBOOT_SIZE, buf, is_backup)) {
        printf("Could not read SPI flash to find uboot\n");
        return 0;
    }

    return is_valid_image_mem((uint32_t)buf, CFG_UBOOT_SIZE,
                              IMG_HEADER_OFFSET, IMG_DATA_OFFSET);
}

int
is_valid_loader_image_spi (uint32_t spi_addr,
        uint32_t section_size,
        uint32_t is_backup)
{
    void *buf = (void *)CONFIG_BOOT_IMAGE_VERIFY_ADDR;

    if (board_spi_flash_read(CFG_LOADER_HDR_OFFSET,
                sizeof(image_header_t), buf, is_backup)) {
        printf("Could not read SPI flash n");
        return 0;
    }

    if (board_spi_flash_read(CFG_SPI_FLASH_LOADER_P1_START,
                CFG_LOADER_P1_DATA_SIZE, buf+sizeof(image_header_t), is_backup)) {
        printf("Could not read SPI flash n");
        return 0;
    }

    if (board_spi_flash_read(CFG_SPI_FLASH_LOADER_P2_START,
                CFG_LOADER_P2_SIZE, buf+CFG_LOADER_P1_SIZE, is_backup)) {
        printf("Could not read SPI flash n");
        return 0;
    }
    return is_valid_image_mem((uint32_t)buf, CFG_LOADER_SIZE,
                              0, sizeof(image_header_t));
}


/*
 * @brief:
 * Flush out the input console buffer.
 *
 * Until the characters are available in the console
 * input, take them out and discard them.
 *
 * @param:
 * None.
 *
 * @return:
 * No return value.
 */
void
flush_console_input (void)
{
    /* Until some character */
    while (tstc()) {
        /* take and discard character */
        (void)getc();
    }
}


/* upgrade uboot with console interaction.. */
static int
cmd_upgrade_uboot (uint32_t mem_addr, unsigned long is_backup)
{
    uint32_t size = CFG_UBOOT_SIZE;
    uint32_t uboot_start = CFG_SPI_FLASH_UBOOT_START;
    uint32_t image_has_crc = 0;
    int      len;

    static char response[256] = { 0, };

    if (!is_backup) {
        printf("Checking sanity of backup u-boot...");
        /* check secondary u-boot */
        if (!is_valid_uboot_image_spi(CFG_SPI_FLASH_UBOOT_START,
                    CFG_UBOOT_SIZE, 1)) {
            printf("NO valid backup u-boot,Do you want to continue? [Y/N] "
                    "(Default: N)");

            /* string response is static, not in stack, memset before use */
            memset(response, 0, sizeof(response));
            flush_console_input();
            len = readline("");
            if (len > 0) {
                strcpy(response, console_buffer);
                if (response[0] != 'y'
                        && response[0] != 'Y') {
                    return 0;
                }
            } else {
                return 1;
            }
        } else {
            printf("OK\n");
        }
    }

    image_header_t* hdr =
        (image_header_t *)(mem_addr + IMG_HEADER_OFFSET);

    /*
     * If image has a CRC header but CRC fails, then we
     * won't write anything. If image doesn't have a CRC
     * header, we will complain to user but write the
     * image.
     */
    if (hdr->ih_magic == IH_MAGIC) {
        image_has_crc = 1;
        /*
         * Before upgrading check if the source mem_address
         * has a valid u-boot image. Then upgrade the
         * image on bootflash. While upgrading make sure
         * that size of the image can fit in the
         * partition.
         */
        if (!is_valid_image_mem(mem_addr, size,
                    IMG_HEADER_OFFSET, IMG_DATA_OFFSET)) {
            printf("WARNING: bad source U-Boot image! \n");
            return 1;
        }
    } else {
        printf("WARNING: U-boot image with missing "
                "CRC header!\nDo you want to continue?"
                "[Y/N] (Default: N)");

        flush_console_input();
        len = readline("");
        response[0] = '\0';
        if (len > 0) {
            strcpy(response, console_buffer);
            if (response[0] != 'y' && response[0] != 'Y'){
                return 1;
            }
        } else {
            return 1;
        }

        image_has_crc = 0;
    }

    if (board_spi_flash_update(uboot_start,
                                size,
                                (void *)mem_addr,
                                is_backup) ) {
        printf("WARNING: U-Boot upgrade failed\n");
        return 1;
    }

    if (image_has_crc && !is_backup) {
        /*
         * check if image was written
         * correctly
         */
        printf("Verifying the new u-boot... ");
        if (!is_valid_uboot_image_spi(uboot_start,
                    size, is_backup)) {
            return 1;
        } else {
            printf("OK\n");
        }
    }

    return 0;

}

static int
cmd_upgrade_loader (uint32_t mem_addr, unsigned long is_backup)
{
    image_header_t *hdr = (image_header_t *)mem_addr;
    uint32_t loader_size  = CFG_LOADER_SIZE;
    uint32_t loader_start = CFG_SPI_FLASH_LOADER_P1_START;
    int len;
    static char response[256] = { 0, };

    if (hdr->ih_magic == IH_MAGIC) {
        uint32_t addr;
        /*
         * !!! WARNING: Make sure that the image header is
         * written in the last *sizeof(image_header_t)* bytes
         * of the loader partition. Because thats where the
         * "bootloader check loader" command looks for the
         * image header.
         *
         * Move the header to the end of the loader space.
         * Currently the loader_size is same as the size of
         * the partition. So image header automatically goes
         * at the end of the partition.
         */
        if (!is_valid_image_mem(mem_addr, loader_size,
                               0, sizeof(image_header_t))) {
            printf("WARNING: invalid loader source data!\n");
            return 1;
        }

        addr = shuffle_loader_hdr(mem_addr, CFG_LOADER_P1_SIZE);

        if (board_spi_flash_update(CFG_SPI_FLASH_LOADER_P1_START,
                                    CFG_LOADER_P1_SIZE,
                                    (void *)addr,
                                    is_backup) ) {
            printf("WARNING: loader upgrade p1 failed\n");
            return 1;
        }
        if (hdr->ih_size > CFG_LOADER_P1_DATA_SIZE) {
            if (board_spi_flash_update(CFG_SPI_FLASH_LOADER_P2_START,
                                        CFG_LOADER_P2_SIZE,
                                        (void *)mem_addr+ CFG_LOADER_P1_SIZE,
                                        is_backup) ) {
                printf("WARNING: loader upgrade p2 failed\n");
                return 1;
            }
        }

        printf("Verifying new loader image...");
        if (is_valid_loader_image_spi(loader_start,
                    loader_size,
                    is_backup)) {
            printf("OK\n");
        } else {
            printf("WARNING: target data verify failed!\n");
            return 1;
        }

    } else {
        /* no crc? print the warning and update the image */
        printf("WARNING: Loader image with missing CRC header!\n"
                "Do you want to continue? [Y/N] (Default: N) ");

        response[0] = '\0';
        flush_console_input();
        len = readline("");
        if (len > 0) {
            strcpy(response, console_buffer);
            if (response[0] == 'y' || response[0] == 'Y') {
                if (board_spi_flash_update(CFG_SPI_FLASH_LOADER_P1_START,
                                            CFG_LOADER_P1_DATA_SIZE,
                                            (void *)mem_addr,
                                            is_backup) ) {
                    printf("WARNING: loader upgrade failed\n");
                    return 1;
                }
                if (board_spi_flash_update(CFG_SPI_FLASH_LOADER_P2_START,
                                            CFG_LOADER_P2_SIZE,
                                            (void *)mem_addr + CFG_LOADER_P1_DATA_SIZE,
                                            is_backup) ) {
                    printf("WARNING: loader upgrade failed\n");
                    return 1;
                }
            }
        } else {
            printf("WARNING: upgrade aborted!\n");
            /* abort */
            return 1;
        }
    }

    return 0;
}

int
do_bootloader (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    unsigned long board_type;
    unsigned long image_type = 0;
    unsigned long backup = 0;
    unsigned long upgrade = 0;
    int ret = 0;

    DECLARE_GLOBAL_DATA_PTR;


    board_type = gd->arch.board_desc.board_type;

    if (argc < 3 || argc > 5) {
        goto cmd_error;
    }
    /* arg0 */
    /* bootloader */

    /* check arg1 */
    if (strcmp(argv[1], "check") == 0) {
        upgrade = 0;
    } else if (strcmp(argv[1], "upgrade") == 0) {
        upgrade = 1;
    } else {
        goto cmd_error;
    }

    /* check arg2 */
    if (strcmp(argv[2], "u-boot") == 0) {
        image_type = IMG_TYPE_UBOOT;
    } else if (strcmp(argv[2], "loader") == 0) {
        image_type = IMG_TYPE_LOADER;
    } else if (strcmp(argv[2], "ushell") == 0) {
        image_type = IMG_TYPE_USHELL;
    } else {
        goto cmd_error;
    }

    /* check arg3 for u-boot operation,loader&ushell no arg3 */
    if (image_type == IMG_TYPE_UBOOT) {
        if (strcmp(argv[3], "active") == 0) {
            backup = 0;
        } else if (strcmp(argv[3], "backup") == 0) {
            backup = 1;
        } else {
            goto cmd_error;
        }
    }

    if (upgrade) {
        uint32_t mem_addr;
        /* upgrade */
        if (image_type == IMG_TYPE_UBOOT) {
            if (argc != 5) {
                goto cmd_error;
            }
            mem_addr  = (uint32_t)simple_strtoul(argv[4], NULL, 16);
        } else {
            if (argc != 4) {
                goto cmd_error;
            }
            mem_addr  = (uint32_t)simple_strtoul(argv[3], NULL, 16);
        }

        switch (image_type) {
            case IMG_TYPE_UBOOT:
                ret = cmd_upgrade_uboot(mem_addr, backup);
                break;

            case IMG_TYPE_LOADER:
                ret = cmd_upgrade_loader(mem_addr, backup);
                break;

            case IMG_TYPE_USHELL:
                if (IS_PLATFORM_TRIDENT(gd->arch.board_desc.board_type)) {
                    printf("This platform not need to install ushell \n");
                    return 1;
                }

                if (check_ushell_magic_key((void *)mem_addr) < 0) {
                    printf("Invalid ushell data!\n");
                    printf("Expected 0x%x, actual 0x%x\n",
                            CFG_MDK_MAGIC_KEY, *(uint32_t *)(mem_addr));
                    return 1;
                }

                if (board_spi_flash_update(CFG_SPI_FLASH_USHELL_START,
                                           CFG_USHELL_SIZE,
                                           (void *)mem_addr,
                                           backup) ) {
                    printf("WARNING: loader upgrade failed\n");
                    ret = 1;
                }
            default:
                break;
        }
    } else {
        /* check command */
        switch (image_type) {
            case IMG_TYPE_UBOOT:
                if (backup) {
                    printf("Checking for a valid secondary u-boot... ");
                } else {
                    printf("Checking for a valid primary u-boot... ");
                }

                if (is_valid_uboot_image_spi(CFG_SPI_FLASH_UBOOT_START,
                            CFG_UBOOT_SIZE, backup)) {
                    printf("OK\n");
                    ret = 0;
                } else {
                    printf("failed\n");
                    ret = 1;
                }
                break;

            case IMG_TYPE_LOADER:
                if (backup) {
                    printf("Checking for a valid secondary loader ... ");
                } else {
                    printf("Checking for a valid primary loader ... ");
                }
                if (is_valid_loader_image_spi(CFG_SPI_FLASH_LOADER_P1_START,
                            CFG_LOADER_SIZE, backup)){
                    printf("OK\n");
                    ret = 0;
                } else {
                    printf("failed\n");
                    ret = 1;
                }

                break;
            case IMG_TYPE_USHELL:
            default:
                goto cmd_error;
                break;
        }
    }

    /* cpld will use the configured spi flash to reboot */
    cpld_switch_spi(0);
    return ret;

cmd_error:
    printf ("Usage:\n%s\n", cmdtp->usage);
    return 1;
}

U_BOOT_CMD(
        bootloader,  5,  0,  do_bootloader,
        "bootloader - upgrade u-boot\n"
        "              bootloader - upgrade loader\n"
        "              bootloader - upgrade ushell\n"
        "              bootloader - check u-boot\n"
        "              bootloader - check loader",
        "upgrade u-boot <active/backup>  addr\n"
        "    - copy the active or backup copy of u-boot\n"
        "      from 'addr' in memory to the boot flash\n"
        "upgrade loader addr\n"
        "    - copy the active or backup copy of loader\n"
        "      from 'addr' in memory to the boot flash\n"
        "upgrade ushell addr\n"
        "    - copy the active or backup copy of ushell\n"
        "      from 'addr' in memory to the boot flash\n"
        "check u-boot <active/backup>\n"
        "    - Check the presence and the sanity of the\n"
        "      u-boot on active and backup partitions\n"
        "      respectively\n"
        "check loader \n"
        "    - Check the presence and the sanity of the\n"
        "      loader on active and backup partitions\n"
        "      respectively\n"

);
