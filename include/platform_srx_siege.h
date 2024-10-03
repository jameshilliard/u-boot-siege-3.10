/*
 * $Id: platform_srxsme.h,v 1.4.132.2 2009-09-24 13:07:19 jyan Exp $
 *
 * platform_srx_siege.h: SRX siege Platform releated declerations
 *
 * Copyright (c) 2009-2015, Juniper Networks, Inc.
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
 * along with this program. If not, see
 * <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>
 */


#ifndef __PLATFORM_SRX_SIEGE__H__
#define __PLATFORM_SRX_SIEGE__H__

/* Max retries */
#define NORMAL_MODE_BOOTSEQ_RETRIES  12
#define BOOTSEQ_MAX_RETRIES	    (NORMAL_MODE_BOOTSEQ_RETRIES + 4)

#define SRX_SIEGE_MAX_BOOTDEVS	    2

/* porting from Juniper u-boot 1.1.6 platform_srxsme.h */
#define DEFAULT_SECTOR_SIZE	    512
#define NUM_DISK_PART		    4
#define DISK_PART_SIZE		    0x10
#define DISK_PART_TBL_OFFSET	    0x1be
#define DISK_PART_MAGIC_OFFSET	    0x1fe
#define DISK_PART_MAGIC		    0xAA55
#define BSD_MAGIC		    0xa5
#define ACTIVE_FLAG		    0x80

typedef struct disk_part {
    uint8_t	boot_flag;	    /* active				*/
    uint8_t	head;		    /* start head			*/
    uint8_t	sector;		    /* start sector			*/
    uint8_t	cylinder;	    /* start cylinder			*/
    uint8_t	part_type;	    /* type of partition.		*/
    uint8_t	end_head;	    /* end of head			*/
    uint8_t	end_sector;	    /* end of sector			*/
    uint8_t	end_cylinder;	    /* end of cylinder			*/
    uint8_t	start_sec[4];	    /* start sector from 0		*/
    uint8_t	size_sec[4];	    /* number of sectors in partition	*/
} disk_part_t;

/* Mask for different bootable devices */
#define DISK_ZERO    0x0
#define DISK_FIRST   0x1
#define DISK_SECOND  0x2
#define DISK_THIRD   0x3
#define DISK_DEFAULT_SRX_SIEGE_MODELS   DISK_ZERO

#define BOOT_SUCCESS	   0x1
#define MAX_DISK_STR_LEN   16


#define SELECT_ACTIVE_SLICE		0
#define BOOT_MODE_NORMAL		0
#define BOOT_MODE_RECOVERY		1
#define DEFAULT_RECOVERY_SLICE		4
#define DEFAULT_CONFIG_SLICE		3
#define DEFAULT_SLICE_TO_TRY		1
#define CURR_BOOT_REC_VERSION		0x00
#define MIN_BOOT_REC_VER_SUPPORTED	0x00
#define VALID_BOOT_REC_VERSION(x)	((uint8_t)x >= MIN_BOOT_REC_VER_SUPPORTED    \
					 && (uint8_t)x != 0x0F ? 1 : 0)

typedef union slice_info {
    uint8_t sl_info;
    struct {
        uint8_t version:4;	/* boot record version */
        uint8_t boot_mode:1;	/* boot mode, recovery or normal */
        uint8_t next_slice:3;	/* next slice to be tried for booting */
    }sl_fields;
} slice_info_t;

/*
 * srxsme_bootseqinfo is used by bootsequening
 */
#define READ_BOOTSEQ_RECORD   0x01
#define WRITE_BOOTSEQ_RECORD  0x02

typedef struct bootseqinfo {
#define BOOTSEQ_MAGIC_LEN  4
#define BOOTSEQ_MAGIC_STR  "BTSQ"
    uint8_t sb_magic[BOOTSEQ_MAGIC_LEN];
#define REBOOT_REASON_LEN     2
    uint8_t sb_reset_reason[REBOOT_REASON_LEN];
    uint8_t sb_retry_count;
    uint8_t sb_next_bootdev;
    uint8_t sb_boot_success;
    uint8_t sb_cur_bootdev;
    slice_info_t sb_slice;
#define MAX_DUMMY_LEN	      1
    uint8_t sb_dummy[MAX_DUMMY_LEN];
} bootseqinfo_t;

#define SD_DEVICE_ENABLED	(0x01UL << 0)

/*
 * srxsme_device is used for mapping device to corrosponding "disk" names
 */
typedef struct srx_siege_device {
    int8_t *sd_devname;
    int8_t *sd_diskname;
    uint32_t sd_flags;
} srx_siege_device_t;

int32_t get_next_bootdev(uint8_t *bootdev, int32_t update);
int32_t get_next_bootdev_jt(uint8_t *bootdev);
extern uint32_t get_uboot_version (void);
int usb_disk_scan(int dev);
int usb_disk_read (int dev, int lba, int totcnt, char *buf);
int usb_disk_write (int dev, int lba, int cnt, void *buf);
extern int32_t set_next_bootdev(uint8_t *bootdev);
extern void show_bootdev_list(void);
extern int srx_siege_is_valid_devname (const char *devname);
void update_loaderdev(void);
char* get_devname_by_disk_id(uint32_t id);
void set_last_booseq_record_finish(void);

#endif
