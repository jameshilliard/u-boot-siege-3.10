/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, <wd@denx.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 ********************************************************************
 * NOTE: This header file defines an interface to U-Boot. Including
 * this (unmodified) header file in another file is considered normal
 * use of U-Boot, and does *not* fall under the heading of "derived
 * work".
 ********************************************************************
 */

#ifndef _U_BOOT_H_
#define _U_BOOT_H_	1

#ifndef __U_BOOT__
typedef unsigned long phys_size_t;
#define u64 uint64_t
#define u32 uint32_t
#endif

#ifdef CONFIG_SRX_SIEGE
typedef struct bd_info {
	unsigned int	bi_baudrate;	/* serial console baudrate */
	unsigned long	bi_ip_addr;	/* IP Address */
    /* JUNOS, change position */
	unsigned char	bi_enetaddr[6];	/* Ethernet address */
    /* JUNOS, change position end*/
	unsigned long	bi_arch_number;	/* unique id for this board */
	unsigned long	bi_boot_params;	/* where this board expects params */
#if 0
	unsigned long	bi_memstart;	/* start of DRAM memory */
	unsigned long   bi_memsize;	/* size	 of DRAM memory in bytes */
#else
	unsigned long	bi_memstart;	/* start of DRAM memory */
	unsigned long	pad;
    /* 8 */
	phys_size_t     bi_memsize;	/* size	 of DRAM memory in bytes */
#endif

    /* JUNOS */
	unsigned long	bi_flashstart;	/* start of FLASH memory */   /*ushell& loader no use */
	unsigned long	bi_flashsize;	/* size  of FLASH memory */ /*ushell& loader no use */
#if 0
	unsigned long	bi_flashoffset;	/* reserved area for startup monitor */ /*ushell& loader no use */
	uint32_t	bi_uboot_map_size;  /* ushell& loader no use */
#endif

    /* 12 */

	unsigned long	bi_uboot_ram_used_size; /* size of u-boot in RAM */ /* ushell& loader no use */
    /* added by JUNOS, used by loader and ushell */
    unsigned long   bi_i2c_id;
	uint64_t        bi_uboot_ram_addr; /* start physical address in RAM for u-boot */  /* ushell& loader no use */
    /* JUNOS add end */
	ulong		bi_bootflags;	/* boot flags passed to board_init_f */
#if 1 
	unsigned long	bi_flashoffset;	/* reserved area for startup monitor */ /*ushell& loader no use */
	uint32_t	bi_uboot_map_size;  /* ushell& loader no use */
#endif
} bd_t;

#else  /* !def CONFIG_SRX_SIEGE */
typedef struct bd_info {
	unsigned int	bi_baudrate;	/* serial console baudrate */
	unsigned long	bi_ip_addr;	/* IP Address */
	unsigned long	bi_arch_number;	/* unique id for this board */
	unsigned long	bi_boot_params;	/* where this board expects params */
	unsigned long	bi_memstart;	/* start of DRAM memory */
	phys_size_t	bi_memsize;	/* size	 of DRAM memory in bytes */
	unsigned long	bi_flashstart;	/* start of FLASH memory */
	unsigned long	bi_flashsize;	/* size  of FLASH memory */
	unsigned long	bi_flashoffset;	/* reserved area for startup monitor */
#ifdef CONFIG_OCTEON
	unsigned char	bi_enetaddr[6];	/* Ethernet address */
	uint64_t	bi_uboot_ram_addr; /* start address in RAM for u-boot */
	unsigned long	bi_uboot_ram_used_size; /* size of u-boot in RAM */
	uint32_t	bi_uboot_map_size;
	ulong		bi_bootflags;	/* boot flags passed to board_init_f */
#endif
} bd_t;

#endif

/* For image.h:image_check_target_arch() */
#define IH_ARCH_DEFAULT IH_ARCH_MIPS
#define bi_env_data bi_env->data
#define bi_env_crc  bi_env->crc

#endif	/* _U_BOOT_H_ */
