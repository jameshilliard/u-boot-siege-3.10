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

#ifndef __CONFIG_H__
#define __CONFIG_H__

#define CONFIG_SRX_SIEGE
#define CONFIG_SRX_SIEGE_STAGE3

/* remove unused codes to reduce size */
#define SIEGE_REDUCE_SIZE  

#if 0
#define CONFIG_SYS_LDSCRIPT     "arch/mips/cpu/octeon/u-boot.o32.lds"
#else
#define CONFIG_SYS_LDSCRIPT     "arch/mips/cpu/octeon/u-boot.lds"
#endif

#define CONFIG_BOARD_SATA_DEVICE 1
# define CONFIG_LIBATA
# define CONFIG_CMD_SATA            /* Enable the sata command */
# define CONFIG_SYS_SATA_MAX_DEVICE 2   /* Support up to 2 devices */
# define CONFIG_SATA_AHCI
# define CONFIG_SATA_AHCI_PLAT
# define CONFIG_SATA_AHCI_OCTEON
# define CONFIG_SATA_PMP
# define CONFIG_AHCI_SETFEATURES_XFER
# define CONFIG_SYS_SATA_MAX_LUN    6

/*#define CONFIG_SATA_PMP */
/*#define CONFIG_SATA_SIL*/

/* enable juniper tpm codes */
#define CONFIG_JNPR_SIEGE_TPM
#define CONFIG_TPM_TIS_LPC
#define CONFIG_TPM_TIS_BASE_ADDRESS 0xFED40000
#define CONFIG_CMD_TPM

/*
 * Define CONFIG_OCTEON_PCI_HOST = 1 to map the pci devices on the
 * bus.  Define CONFIG_OCTEON_PCI_HOST = 0 for target mode when the
 * host system performs the pci bus mapping instead.  Note that pci
 * commands are enabled to allow access to configuration space for
 * both modes.
 */
#ifndef CONFIG_OCTEON_PCI_HOST
# define CONFIG_OCTEON_PCI_HOST		1
#endif

/* juniper copy from actom codes */
#define CONFIG_OCTEON_ENABLE_PAL
/* copy end */

/* JUNOS begin */
#include "juniper_srx_siege_version.h"

#ifndef CONFIG_CRC_U_BOOT
#define CONFIG_CRC_U_BOOT      1
#endif

#define CONFIG_SWAP_USB_CTRL

/* for eth link_update */
#define RX_SYNC_COUNT 5

/* for api eth_recieve */
#define CONFIG_API

#define CONFIG_SYS_MMC_MAX_DEVICE 0

/* must define it before octeon_common.h it will check it */
#define CONFIG_SYS_NO_FLASH 1

/* for api version and u-boot version string */
#define CFG_UBOOT_METADATA_OFFSET       0x500
#define CFG_UBOOT_METADATA_SIZE         0x100
#define CFG_UBOOT_METADATA_END          (CFG_UBOOT_METADATA_OFFSET \
                                         + CFG_UBOOT_METADATA_SIZE)

#define CONFIG_OCTEON_BIG_STACK_SIZE		0x4000	/** 16K stack */

/* JUNOS end */
#define CONFIG_OCTEON_USB_OCTEON3	/* Enable USB support on OCTEON III */

#include "octeon_common.h"

/* CONFIG_JUNIPER_SRX_SIEGE set by Makefile in include/config.h */

/* Default DDR clock if tuple doesn't exist in EEPROM */
#define SRX_SIEGE_DEF_DRAM_FREQ		667
#define SRX_AIRBUS_DEF_DRAM_FREQ	1066	

#define CONFIG_LBA48			/* 48-bit mode */
#define CONFIG_SYS_ATA_BASE_ADDR	0 /* Make compile happy */
/* Base address of Common memory for Compact flash */

/* Address of board EEPROM on TWSI bus */
#define CONFIG_SYS_I2C_EEPROM_ADDR	JUNIPER_SRX_SIEGE_BOARD_EEPROM_TWSI_ADDR

/* Default EEPROM address */
#define CONFIG_SYS_DEF_EEPROM_ADDR	CONFIG_SYS_I2C_EEPROM_ADDR
#define ID_EEPROM_ALEN 1

/* These speed up writes to the serial EEPROM by enabling page writes.
 * Please see the datasheet for details.
 */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	5	/* 32 bytes */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	5

/* Set bootdelay to 0 for immediate boot */
#define CONFIG_BOOTDELAY	1	/* autoboot after X seconds	*/

/* by markli for test */
#define CONFIG_AUTOBOOT_KEYED
#define CONFIG_AUTOBOOT_STOP_STR    " "
#define CONFIG_AUTOBOOT_PROMPT "Press SPACE to stop autoboot: %2d "

#undef	CONFIG_BOOTARGS

/* The 'mtdids' environment variable is used in conjunction with the 'mtdparts'
 * variable to define the MTD partitions for u-boot.
 */
#define MTDPARTS_DEFAULT				\
	"octeon_nor0:2560k(bootloader)ro,"		\
	"2m(kernel),"					\
	"3520k(cramfs),"				\
	"64k(environment)ro;"				\
	"octeon_nand0:6m(bootloader)ro,"		\
	"2m(environment),"				\
	"8m(kernel),"					\
	"512m(rootfs)\0"


#define MTDIDS_DEFAULT	"nor0=octeon_nor0,nand0=octeon_nand0\0"
#if defined(CONFIG_OCTEON_NAND_BOOT)
/*
 * Start of where the NAND bootloader images are placed.  Must be on an erase
 * block boundary/
 */
#define CONFIG_OCTEON_NAND_BOOT_START		0

/* Maximum number of NAND devices */
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_FORCE_WIDTH	8	/* Force to 8-bit width */
/* Not used for Octeon, but must be set */
#define CONFIG_SYS_NAND_BASE		0
/* Maximum number of NAND devices */
#define CONFIG_SYS_NAND_MAX_CHIPS	CONFIG_SYS_MAX_NAND_DEVICE

/* Enable multi-bit ECC support */
#if 0
#define CONFIG_OCTEON_HW_BCH
#endif
#include "config_octeon_nand.h"

/*
 * End of the NAND boot partition which is searched for a bootloader.  Must be
 * on an erase block boundary.  It should be large enough to be able to handle
 * at least one bad block.
 */
#define CONFIG_OCTEON_NAND_BOOT_END		0x600000
#endif

/* Define this to enable built-in octeon ethernet support */
#define CONFIG_OCTEON_SGMII_ENET		/* Enable SGMII support */
#define CONFIG_OCTEON_QSGMII_ENET		/* Enable QSGMII support */
#define CONFIG_OCTEON_XAUI_ENET			/* Enable XAUI support */

/* For SRX380 */
#define CONFIG_OCTEON_RGMII_ENET		/* srx340, srx380 use RGMII Enable RGMII support */

/* Enable Octeon built-in networking if RGMII support is enabled */
#if defined(CONFIG_OCTEON_RGMII_ENET) || defined(CONFIG_OCTEON_SGMII_ENET) || \
	defined(CONFIG_OCTEON_XAUI_ENET) || defined(CONFIG_OCTEON_QSGMII_ENET)
# define CONFIG_OCTEON_INTERNAL_ENET		/* Enable Octeon enet support */
#endif

#define CONFIG_OCTEON_BOOTCMD

#include "octeon_cmd_conf.h"

#undef CONFIG_REGEX
#undef CONFIG_LZMA
#undef CONFIG_CMD_UNZIP
#undef CONFIG_BZIP2
#undef CONFIG_ZIP
#undef CONFIG_GZIP
#undef CONFIG_CMD_ASKENV
#undef CONFIG_CMD_EDITENV
#undef CONFIG_CMD_BDI
#undef CONFIG_CMD_XIMG
#undef CONFIG_CMD_CRAMFS
#undef CONFIG_CMD_GREPENV
#undef CONFIG_CMD_TIME
#undef CONFIG_CMD_STRINGS
#undef CONFIG_CMD_SOURCE
#undef CONFIG_CMD_ITEST
#undef CONFIG_CMD_CONSOLE
#undef CONFIG_CMD_SETEXPR
#undef CONFIG_CMD_SPI_EEPROM
#undef CONFIG_CMD_DATE			/* Date command for RTC	*/
#undef CONFIG_CMD_FLASH		/* flinfo, erase, protect	*/
#undef CONFIG_CMD_EXT2			/* EXT2/3 filesystem support	*/
#undef CONFIG_CMD_EXT4			/* EXT4 filesystem support	*/

#if 0  /* Enable memory commands for tmp */
#undef CONFIG_CMD_MEMORY
#undef CONFIG_CMD_OCTEON_MEM
#endif

/*
 * these options can't disabled by us, will cause compile issue
 * CONFIG_FIT
 * CONFIG_CMD_OCTEON_REGINFO
 * CONFIG_CMD_I2C
 * CONFIG_CMD_MEMORY
 * CONFIG_CMD_OCTEON_ELF
 * CONFIG_CMD_OCTEON
 * CONFIG_CMD_BOOTM
 * CONFIG_CMD_OCTEON_LINUX
 * CONFIG_CMD_FDT
 * CONFIG_CMD_OCTEON_MEM
 */

#define CONFIG_MDK_DEBUG
#define CONFIG_CMD_BOOTD        /* enable boot default command */
#ifdef  CONFIG_CMD_NET
/*
 * Define available PHYs
 */
# define CONFIG_PHY_GIGE		/* GigE PHY support		*/
# define CONFIG_PHYLIB_10G		/* 10G PHY support		*/
# define CONFIG_PHY_BROADCOM
# include "octeon_network.h"
#endif

#define CONFIG_CMD_QLM			/* "qlm" command		*/

#if defined(CONFIG_OCTEON_NAND_BOOT)
#define CONFIG_CMD_MTDPARTS		/* Enable MTD partitioning support */
#endif

/* Enable "date" command to set and get date from RTC */
#define CONFIG_CMD_FAT			/* FAT support			*/
#define CONFIG_FAT_WRITE		/* FAT write support		*/

/* SPI NOR flash support */
#define CONFIG_SF_DEFAULT_BUS		0	/* Default SPI bus	*/
#define CONFIG_SF_DEFAULT_CS		0	/* Default SPI chip select */
#define CONFIG_SF_DEFAULT_SPEED		16000000/* Default SPI speed	*/
#define CONFIG_SF_DEFAULT_MODE      3   /* Default SPI mode */

#define CONFIG_OCTEON_SPI		/* Enable OCTEON SPI driver	*/
#define CONFIG_SPI_FLASH		/* Enable SPI flash driver	*/
/* we are using Micron N25Q064A*/
#define CONFIG_SPI_FLASH_STMICRO	/* Enable ST Micro SPI flash	*/
#define CONFIG_SPI_FLASH_MACRONIX
#define CONFIG_SPI_FLASH_MICRON

/* For Airbus */
#define CONFIG_SPI_FLASH_WINBOND
#define CONFIG_CMD_SPI			/* Enable SPI command		*/
#define CONFIG_CMD_SF			/* Enable SPI flash command	*/

/*
 * Miscellaneous configurable options
 */
/* Environment variables that will be set by default */
#define	CONFIG_EXTRA_ENV_SETTINGS					\
        "autoload=n\0"					\
        ""

/* Environment variable names */
#define SRX_SIEGE_BOOTDEVLIST_ENV              "boot.devlist"

/* JUNOS, save env at spi-flash */
#define	CONFIG_ENV_IS_IN_SPI_FLASH	1
#define CONFIG_SYS_SPI_FLASH_SIZE  0x800000


/* env_sf.c will use these 2 macros */
#define CONFIG_ENV_SPI_BUS      CONFIG_SF_DEFAULT_BUS
#define CONFIG_ENV_SPI_CS       CONFIG_SF_DEFAULT_CS
#define	CONFIG_ENV_SPI_MAX_HZ   CONFIG_SF_DEFAULT_SPEED
/*
    #define CONFIG_ENV_SPI_MODE
*/

/* SPI-Flash related definition */
#define CFG_SPI_FLASH_UBOOT_START  0    /* 0m-2m */
 
#define CFG_UBOOT_SIZE             0x200000
#define CFG_SPI_FLASH_UBOOT_END    0x1fffff

#define CFG_SPI_FLASH_2ND_UBOOT_START 0

#define CFG_SPI_FLASH_LOADER_P1_START  0x200000   /*2m - 3m */
#define CFG_LOADER_SIZE             0x200000
#define CFG_LOADER_P1_SIZE             0x100000
#define CFG_LOADER_P1_DATA_SIZE       (0x100000 - 0x40)
#define CFG_LOADER_P2_SIZE             0x100000
#define CFG_SPI_FLASH_LOADER_P1_END    0x2fffff

#define CFG_SPI_FLASH_USHELL_START  0x300000   /*3m - 4m */
#define CFG_USHELL_SIZE             0X100000

#define CFG_SPI_FLASH_LOADER_P2_START  0x400000   /*4m - 5m */
#define CFG_SPI_FLASH_LOADER_P2_END    0x4fffff

#define CFG_SPI_FLASH_USHELL_END    (CFG_SPI_FLASH_USHELL_START + CFG_USHELL_SIZE - 1)

#define CFG_LOADER_HDR_OFFSET       (CFG_SPI_FLASH_LOADER_P1_START + CFG_LOADER_P1_SIZE - 0x40)
#define CFG_LOADER_DATA_OFFSET      CFG_SPI_FLASH_LOADER_P1_START

/* 6.5m - (8m-128k) free now*/
#define CONFIG_ENV_SECT_SIZE (64*1024)
#define CONFIG_ENV_SIZE		(8*1024)
#define CONFIG_ENV_OFFSET   (CONFIG_SYS_SPI_FLASH_SIZE - CONFIG_ENV_SECT_SIZE)    /* 8m -64k */

#define CONFIG_BOOTSEQ_SECT_SIZE (64*1024)
#define CONFIG_BOOTSEQ_OFFSET   (CONFIG_SYS_SPI_FLASH_SIZE \
                                 - CONFIG_ENV_SECT_SIZE - CONFIG_BOOTSEQ_SECT_SIZE)  /* 8m - 128k */

#define CFG_MDK_MAGIC_KEY        0x3c1c0000

/* RAM addresses */
#define CFG_MDK_DRAM_START_ADDR          0x80200000   /* start at 2M */
#define CONFIG_BOOT_IMAGE_VERIFY_ADDR    0x81000000   /* 16M */
#define CONFIG_USHELL_IMAGE_VERIFY_ADDR  0x81200000   /* 18M */
#define CONFIG_ENV_RAM_ADDR              0x82000000   /* 32M */
#define CONFIG_LOADER_RAM_ADDR           0X8F000000   /* 256M - 16M */
/* USB bounce buffer */
#define JSRX_SIEGE_USB_BOUNCE_BUFFER_OFFSET (255 * (1024*1024))  /* 255M */


/* DCache size (not used) */
#define CONFIG_SYS_DCACHE_SIZE		(32 * 1024)
/* ICache size (not used) */
#define CONFIG_SYS_ICACHE_SIZE		(78 * 1024)

#if CONFIG_OCTEON_PCI_HOST
# define CONFIG_LIBATA
#endif  /* PCI_HOST */

/*
 * The CN70XX has two TWSI buses and the EVB7000 sff board uses both
 * of them
 */
#undef CONFIG_SYS_MAX_I2C_BUS
#define CONFIG_SYS_MAX_I2C_BUS		1	/* Maximum I2C bus number */

#define CONFIG_PCA953X				/* PCA953X I2C GPIO expander */
#define CONFIG_CMD_PCA953X			/* PCA953x command */
#define CONFIG_CMD_PCA953X_INFO			/* PCA953x info command */

#define CONFIG_HW_WATCHDOG			/* Enable watchdog support */

/* Configure QLM */
#define CONFIG_OCTEON_QLM

/* Include shared board configuration, consisting mainly of DRAM details. */
#include "juniper_srx_siege_shared.h"
#include "juniper_srx_airbus_shared.h"

/* Disable DDR2 support */
#define CONFIG_OCTEON_DISABLE_DDR2

/* Limit image size to 2MB */
#ifndef CONFIG_BOARD_SIZE_LIMIT
# define CONFIG_BOARD_SIZE_LIMIT	0x00200000
#endif

#undef CONFIG_CMD_QLM
#undef CONFIG_CMD_OCTEON_BOOTBUS
#undef CONFIG_CMD_OCTEON_BOOTLOADER_UPDATE
#undef CONFIG_CMD_OCTEON_ERASEENV
#undef CONFIG_CMD_OCTEON_LINUX
#undef CONFIG_CMD_OCTEON_NAND
#undef CONFIG_CMD_OCTEON_NAND_BOOT_STAGE3
#undef CONFIG_CMD_OCTEON_REGINFO
#undef CONFIG_CMD_OCTEON_TLVEEPROM
#undef CONFIG_OCTEON_ADMA
#undef CONFIG_CMD_IDE
#undef CONFIG_OCTEON_MGMT_ENET
#undef CONFIG_BOOTP_VENDOREX
#undef CONFIG_OCTEON_MMC
#undef CONFIG_NAND_OCTEON

#undef CONFIG_CMD_BUNZIP
#undef CONFIG_CMD_UNLZMA

#if 0 
#define CONFIG_OCTEON_CN70XX
#endif
#define CVMX_BUILD_FOR_UBOOT     1
#define CVMX_ENABLE_DEBUG_PRINTS 1


#endif	/* __CONFIG_H__ */


