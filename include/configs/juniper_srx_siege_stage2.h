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

#define CONFIG_OCTEON_SPI_BOOT

#define CONFIG_SRX_SIEGE
#define CONFIG_SRX_SIEGE_STAGE2
#if 0
#define CONFIG_SYS_LDSCRIPT     "arch/mips/cpu/octeon/u-boot.o32.lds"
#else
#define CONFIG_SYS_LDSCRIPT     "arch/mips/cpu/octeon/u-boot.lds"
#endif

/*
 * Define CONFIG_OCTEON_PCI_HOST = 1 to map the pci devices on the
 * bus.  Define CONFIG_OCTEON_PCI_HOST = 0 for target mode when the
 * host system performs the pci bus mapping instead.  Note that pci
 * commands are enabled to allow access to configuration space for
 * both modes.
 */
#ifndef CONFIG_OCTEON_PCI_HOST
# define CONFIG_OCTEON_PCI_HOST		0
#endif

/* JUNOS make crc image*/
#ifndef CONFIG_CRC_U_BOOT 
#define CONFIG_CRC_U_BOOT      1
#endif

/* for api version and u-boot version string */
#include "juniper_srx_siege_version.h"

#define CFG_UBOOT_METADATA_OFFSET       0x500
#define CFG_UBOOT_METADATA_SIZE         0x100
#define CFG_UBOOT_METADATA_END          (CFG_UBOOT_METADATA_OFFSET \
                                         + CFG_UBOOT_METADATA_SIZE)
/* JUNOS end */

#define CONFIG_OCTEON_NO_FAILSAFE
#define CONFIG_OCTEON_DISABLE_UBI
#define CONFIG_OCTEON_DISABLE_JFFS2
#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_OCTEON_DISABLE_NETWORKING
#define CONFIG_OCTEON_DISABLE_QLM

#include "octeon_common_spi_stage2.h"

#define CONFIG_SPI_FLASH_MACRONIX

/* CONFIG_OCTEON_GENERIC_NAND set by Makefile in include/config.h */
#define SPI_STAGE2_BOARD_TYPE			CVMX_BOARD_TYPE_GENERIC

/**
 * Add command to boot stage 3 bootloader out of NAND
 */
#define CONFIG_CMD_OCTEON_SPI_BOOT_STAGE3

/**
 * Start of where the SPI bootloader images are placed.  Must be on an erase
 * block boundary/
 */
#define CONFIG_OCTEON_SPI_BOOT_START		0x1000

/**
 * Start of where the SPI bootloader stage3 are placed.  Must be on an erase
 * block boundary/
 */
#define CONFIG_OCTEON_SPI_STAGE3_BOOT_START		(0x80000 - 0x18000)  /*512k - 96k*/

/**
 * End of the NAND boot partition which is searched for a bootloader.  Must be
 * on an erase block boundary.  It should be large enough to be able to handle
 * at least one bad block.
 */
#define CONFIG_OCTEON_SPI_BOOT_END		0x600000

/**
 * Address to load the stage 3 bootloader for booting
 */
#define CONFIG_OCTEON_STAGE3_LOAD_ADDR	0x81000000

/**
 * If more than one NAND chip is present, define which one contains the
 * bootloader.
 */
#define DEFAULT_DDR3_CLOCK_FREQ_MHZ		667

#define DEFAULT_CPU_REF_FREQUENCY_MHZ		50
#define DEFAULT_DDR_REF_FREQUENCY_MHZ		50

/** Address of board EEPROM on TWSI bus */
#define CONFIG_SYS_I2C_EEPROM_ADDR	(gd->arch.tlv_addr)

/** Default EEPROM address */
#define CONFIG_SYS_DEF_EEPROM_ADDR	CONFIG_SYS_I2C_EEPROM_ADDR
/* These speed up writes to the serial EEPROM by enabling page writes.
 * Please see the datasheet for details.
 */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	5	/* 32 bytes */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	5

/* Set bootdelay to 0 for immediate boot */
#define CONFIG_BOOTDELAY	1	/* autoboot after X seconds	*/
#define CONFIG_BOOTCOMMAND	"bootjuniperstage3"

/* boot stage3 before enter main loop */
#define CONFIG_PREBOOT "bootjuniperstage3"

#undef	CONFIG_BOOTARGS

/*
 * The EBB6300 does not use the internal arbiter in Octeon.
 * Enable this for boards that do.
 */
/* #define USE_OCTEON_INTERNAL_ARBITER */

#include "octeon_cmd_conf.h"

#define CONFIG_SYS_LONGHELP

#undef CONFIG_BZIP2
#undef CONFIG_ZIP
#undef CONFIG_GZIP
#undef CONFIG_LZMA
#undef CONFIG_CMD_UNZIP
#undef CONFIG_REGEX
#undef CONFIG_FIT
#undef CONFIG_CMD_MEMINFO
#undef CONFIG_CMD_ASKENV
#undef CONFIG_CMD_EDITENV
#undef CONFIG_CMD_BDI
#undef CONFIG_CMD_XIMG
#undef CONFIG_CMD_GPIO
#undef CONFIG_CMD_CRAMFS
#undef CONFIG_CMD_OCTEON_REGINFO
#undef CONFIG_CMD_I2C
#undef CONFIG_CMD_GREPENV
#undef CONFIG_CMD_OCTEON_LINUX
#undef CONFIG_CMD_OCTEON_ELF
#undef CONFIG_CMD_OCTEON
#undef CONFIG_CMD_OCTEON_MEM
#undef CONFIG_CMD_TIME
#undef CONFIG_CMD_STRINGS
#undef CONFIG_CMD_SOURCE
#undef CONFIG_CMD_NMI
#undef CONFIG_CMD_ITEST
#undef CONFIG_CMD_CONSOLE
#undef CONFIG_CMD_SAVEENV
#undef CONFIG_CMD_SETEXPR
#undef CONFIG_CMD_ENV
#undef CONFIG_CMD_FDT
#undef CONFIG_CMD_I2C
#undef CONFIG_CMD_BOOTM
#undef CONFIG_CMD_MEMORY

#undef CONFIG_ENV_IS_IN_FLASH
#undef CONFIG_CMD_OCTNAND

#undef CONFIG_HW_WATCHDOG

#define CONFIG_OCTEON_DISABLE_DDR2

#undef CONFIG_SYS_CBSIZE
#define CONFIG_SYS_CBSIZE		256

#undef CONFIG_OCTEON_QLM

/*
 * Miscellaneous configurable options
 */

/* Environment variables that will be set by default */
#define	CONFIG_EXTRA_ENV_SETTINGS					\
        "autoload=n\0"							\
        "bootcmd=bootjuniperstage3\0"						\
        "bootdelay=0\0"							\
        "\0"
#define CONFIG_ENV_SIZE			4096

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CONFIG_SYS_DCACHE_SIZE		(32 * 1024)
#define CONFIG_SYS_ICACHE_SIZE		(78 * 1024)


/* Include shared board configuration, consisting mainly of DRAM details. */
#include "juniper_srx_siege_stage2_shared.h"


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

#undef CONFIG_BOOTM_VXWORKS
#undef CONFIG_PARTITIONS


#define CONFIG_OCTEON_CN70XX

#endif	/* __CONFIG_H__ */
