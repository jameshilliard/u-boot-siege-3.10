/*
 * $Id: platform_srx_siege.c,v 1.5.78.2 2009-09-24 13:07:15 jyan Exp $
 *
 * platform_srxsme.c: Platform releated bootsequencing
 *		      Implementation for srxsme platforms.
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

#include <common.h>
#include <watchdog_cpu.h>
#include <cvmx.h>
#include <lib_octeon_shared.h>
#include <octeon_boot.h>
#include <configs/octeon_common.h>
#include "srx_siege_board.h"
#include "srx_siege_cpld.h"
#include <exports.h>
#include <platform_srx_siege.h>
#include <sata.h>

DECLARE_GLOBAL_DATA_PTR;

#define BOOTSEQ_DEBUG 0	

#if BOOTSEQ_DEBUG
#define BSDEBUG(fmt, args...) uart_debug(fmt, ## args)
#else
#define BSDEBUG(fmt, args...)
#endif

/* more detailed debug */
#define bs_debug(fmt, args...)

#define RECOVERY_SLICE_ENV		"recovery_slice"
#define BOOTSEQ_DISABLE_ENV		"boot.btsq.disable"

#define MBR_BUF_SIZE			512

#define MAX_NUM_SLICES			4
#define FIRST_SLICE			1
#define IS_NUMERAL(num) 		(num >= 0 && num <= 9 ? TRUE : FALSE)
#define IS_VALID_SLICE(slice)		(slice >= FIRST_SLICE &&	      \
        slice <= MAX_NUM_SLICES	      \
        ? TRUE : FALSE)

#define IS_BOOT_SEQ_DISABLED()	(getenv(BOOTSEQ_DISABLE_ENV) != NULL &&	      \
        simple_strtoul(getenv(BOOTSEQ_DISABLE_ENV),  \
            NULL, 0) != 0     \
        ? TRUE : FALSE)

#define LIST_MAX_LEN            256

typedef int (* disk_read_vector) (int dev, int lba, int totcnt, char *buf);

static uint8_t  *platform_name;
static uint8_t  *platform_default_bootlist = NULL;
static uint32_t bootseq_sector_start_offset;
static uint32_t bootseq_sector_len;
static srx_siege_device_t *p_siege_dev_map = NULL;
static uint32_t num_bootable_media;

#define SRX_SIEGE_DEF_BOOT_LIST   "eUSB:usb"
#define SRX_AIRBUS_DEF_BOOT_LIST   "SSD:usb"

static void disable_not_required_media(srx_siege_device_t *devlist,
                                        uint32_t numdevices);
static void print_enabled_media (srx_siege_device_t *devlist);

static int srx_siege_is_valid_devlist (const char *devlist);
static void srx_siege_validate_bootlist_env(void);
static void disable_not_required_media (srx_siege_device_t *devlist,
                            uint32_t numdevices);
static void print_enabled_media(srx_siege_device_t *devlist);


static srx_siege_device_t srx_siege_dev_map[] = {
    {
        "eUSB",       /* device name (user visible) */
        "disk0",      /* device string */
        SD_DEVICE_ENABLED       /* device flags */
    },
    {
        "usb",
        "disk1",
        SD_DEVICE_ENABLED
    }
};

static srx_siege_device_t srx_airbus_dev_map[] = {
    {
        "SSD",       /* device name (user visible) */
        "disk0",      /* device string */
        SD_DEVICE_ENABLED       /* device flags */
    },
    {
        "usb",
        "disk1",
        SD_DEVICE_ENABLED
    }
};


/*
 * Initialize the bootsequencing logic and the
 * the data structures.
 */
void
srx_siege_bootseq_init (void)
{
    DECLARE_GLOBAL_DATA_PTR;

    /* Decide platform name */
    switch (gd->arch.board_desc.board_type) {
        CASE_ALL_JSRX_SWORD_MODELS
            platform_name = "srx-sword";
            break;
        CASE_ALL_JSRX_TRIDENT_MODELS
            platform_name = "srx-trident";
            break;
        CASE_ALL_JSRX_AIRBUS_MODELS
            platform_name = "srx-airbus";
            break;
        default:
            platform_name = "srx-siege";
        break;
    }

    /* Decide boot-sequencing sector start address */
    /* setted these env before call srx_siege_bootseq_init at boot_variables_setup */
    bootseq_sector_start_offset = simple_strtoul(getenv("boot.btsq.start"), NULL, 16);
    bootseq_sector_len = simple_strtoul(getenv("boot.btsq.len"), NULL, 16);

    /* Decide boot devices */
    switch (gd->arch.board_desc.board_type) {
        CASE_ALL_JSRX_AIRBUS_MODELS
            p_siege_dev_map = srx_airbus_dev_map;
            platform_default_bootlist = SRX_AIRBUS_DEF_BOOT_LIST;
            num_bootable_media = sizeof(srx_airbus_dev_map) / sizeof(srx_siege_device_t);
            break;
        CASE_ALL_JSRX_SWORD_MODELS
        CASE_ALL_JSRX_TRIDENT_MODELS
        default:
            p_siege_dev_map = srx_siege_dev_map;
            platform_default_bootlist = SRX_SIEGE_DEF_BOOT_LIST;
            num_bootable_media = sizeof(srx_siege_dev_map) / sizeof(srx_siege_device_t);
            break;
    }

    srx_siege_validate_bootlist_env();
    disable_not_required_media(p_siege_dev_map, num_bootable_media);
    print_enabled_media(p_siege_dev_map);
}



/*
 * srxsme_is_next_bootdev_present  determinses
 * is selected nextbootdev in the list is present or
 * not
 */
static int
srx_siege_is_bootdev_present (unsigned int bootdev)
{
    DECLARE_GLOBAL_DATA_PTR;

    switch (bootdev) {
    case DISK_ZERO:
        switch (gd->arch.board_desc.board_type)  {
        CASE_ALL_JSRX_AIRBUS_MODELS
            return 1;
        CASE_ALL_JSRX_SIEGE_MODELS
        default:
            return 1;
        }
        break;

    case DISK_FIRST:
        switch (gd->arch.board_desc.board_type)  {
            CASE_ALL_JSRX_AIRBUS_MODELS
                return (num_usb_disks() > 0) ? 1 : 0;
            CASE_ALL_JSRX_SIEGE_MODELS
            default:
                /* SRXLE NAND flash platforms: Disk-1 is external USB */
                return (num_usb_disks() > 1) ? 1 : 0;
        }
        break;

    case DISK_SECOND:
    default:
        return 0;
    }
}


/* disable device which is not in boot.devlist env */
static void
disable_not_required_media (srx_siege_device_t *devlist,
                            uint32_t numdevices)
{
    int bcount = 0;
    char *bootlist = NULL;

    if ((bootlist = getenv(SRX_SIEGE_BOOTDEVLIST_ENV)) != NULL) {
        for (bcount = 0; bcount < numdevices; bcount++) {
            BSDEBUG("Checking if media %s should be disabled... ",
                    devlist[bcount].sd_devname);
            if (strstr(bootlist,
                       (const char *)devlist[bcount].sd_devname) != NULL) {
                BSDEBUG("NO\n");
            } else {
                BSDEBUG("YES\n");
                /* disable the device */
                devlist[bcount].sd_flags &= ~SD_DEVICE_ENABLED;
            }
        }
    }
}

static void
print_enabled_media (srx_siege_device_t *devlist)
{
    int bcount = 0;

    printf("Boot Media: ");

    for (bcount = 0; bcount < num_bootable_media; bcount++) {
        /* disable the device */
        if (devlist[bcount].sd_flags & SD_DEVICE_ENABLED) {
            printf("%s ", devlist[bcount].sd_devname);
        }
    }
    printf("\n");
}

int
srx_siege_is_device_enabled (int dev_idx)
{
    if (dev_idx < 0 || dev_idx >= num_bootable_media) {
        return 0;
    }

    return (p_siege_dev_map[dev_idx].sd_flags & SD_DEVICE_ENABLED);
}


int
srx_siege_is_valid_devname (const char *devname)
{
    int bcount, found = 0;

    for (bcount = 0; bcount < num_bootable_media; bcount++) {
        if (!strcmp((const char *)p_siege_dev_map[bcount].sd_devname, devname)) {
            found = 1;
            break;
        }
    }

    return (found);
}

static int
srx_siege_is_valid_devlist (const char *devlist)
{
    char *tok;
    char list[LIST_MAX_LEN];

    memcpy(list, devlist, LIST_MAX_LEN);
    tok = strtok(list, ",:");

    while (tok != NULL) {
        if (!srx_siege_is_valid_devname(tok))
            return 0;

        tok = strtok (NULL, ",:");
    }

    return (1);
}

static void
srx_siege_validate_bootlist_env (void)
{
    /*
     * Check if valid boot list is defined in environments. If no,
     * go by defaults. This is because we will not try the
     * devices which are absent in this list.
     */
    if ((getenv(SRX_SIEGE_BOOTDEVLIST_ENV)) == NULL) {
        setenv(SRX_SIEGE_BOOTDEVLIST_ENV, platform_default_bootlist);
        saveenv();
    } else {
        /*
         * If boot.devlist is not null then check if it has all valid devices.
         * if not then set boot.devlist to default devices.
         */
        if (!srx_siege_is_valid_devlist(getenv(SRX_SIEGE_BOOTDEVLIST_ENV))) {
            printf("WARNING: Found one or more invalid media in boot list. "
                   "Falling to defaults.\n");
            setenv(SRX_SIEGE_BOOTDEVLIST_ENV, platform_default_bootlist);
            saveenv();
        }
    }
}


/*
 * Returns the first device present in the
 * boot.devlist
 */
static int
get_default_dev (const char *bootlist)
{
    char *bootdev = NULL;
    int i = 0;
    char devlist[LIST_MAX_LEN];


    if (NULL == bootlist) {
        printf("Bootlist is NULL\n");
        return -1;
    }

    bs_debug("bootlist : %s \n", bootlist);

    memcpy(devlist, bootlist, LIST_MAX_LEN);
    bootdev = strtok(devlist, ",:");
    if (!bootdev) {
        printf("Empty SRX_SIEGE_BOOTDEVLIST_ENV\n");
        return -1;
    }
    /*
     * reset the retry count, set the next boot dev to
     * first dev in bootdev list environment.
     */
    bs_debug("num_bootable_media = %d \n", num_bootable_media);
    bs_debug("p_siege_dev_map = %x \n", p_siege_dev_map);
    bs_debug("srx_siege_dev_map = %x \n", srx_siege_dev_map);


    for (i = 0; i < num_bootable_media; i++) {
    bs_debug("bootdev: %s \n", bootdev);
    bs_debug("p_siege_dev_map[i].sd_devname: %s \n", p_siege_dev_map[i].sd_devname);
        if (strcmp(bootdev,
                    p_siege_dev_map[i].sd_devname) == 0) {
            return i;
        }
    }
    /* Should never get here */
    printf("boot.devlist is invalid\n");
    return -1;
}


static int32_t
read_last_booseq_record (bootseqinfo_t *bootinfo)
{

    uint8_t       bootseq_sector_buffer[CONFIG_BOOTSEQ_SECT_SIZE];
    uint32_t          num_bootseq_rec;
    bootseqinfo_t *bootrecord;
    int32_t       last_good_index = -1;
    int32_t       rec_count;


    if ((bootinfo == NULL)) {
        printf("bootinfo or magic is null\n");
        return -1;
    }

    board_spi_flash_read( bootseq_sector_start_offset,
                          bootseq_sector_len,
                          bootseq_sector_buffer,
                          0);

    /* cast temp buffer to pointer boot_sequence_t */
    bootrecord = (bootseqinfo_t*)bootseq_sector_buffer;

    /* maximum number of records that could fit in the sector */
    num_bootseq_rec = bootseq_sector_len / sizeof(bootseqinfo_t);

    for (rec_count = 0; rec_count < num_bootseq_rec; rec_count++) {
        if (memcmp(bootrecord[rec_count].sb_magic, BOOTSEQ_MAGIC_STR, BOOTSEQ_MAGIC_LEN) != 0)
            break;

        last_good_index = rec_count;
    }

    /*
     * check the magic of previous record, as we dont know, did
     * we find magic or loop terminated
     * if magic is found copy the record else return 0xff in all feilds.
     */
    if (last_good_index != -1)
        memcpy(bootinfo, (void *)(&bootrecord[last_good_index]), sizeof(bootseqinfo_t));
    else
        memset(bootinfo, 0xff, sizeof(bootseqinfo_t));

    return last_good_index;
}


/* save bootseq record right after the last good one.*/
static int32_t
save_booseq_record (bootseqinfo_t *bootinfo,
                    int32_t last_record_idx)
{

    uint32_t          num_bootseq_rec;
    int32_t       current_index;


    if ((bootinfo == NULL)) {
        printf("bootinfo or magic is null\n");
        return -1;
    }

    /* maximum number of records that could fit in the sector */
    /* remain flash memory won't be used */
    num_bootseq_rec = bootseq_sector_len / sizeof(bootseqinfo_t);

    bs_debug(" save_booseq_record, num_bootseq_rec = %d\n", num_bootseq_rec );
    bs_debug(" bootseq_sector_len = %d\n", bootseq_sector_len);
    bs_debug(" last_record_idx = %d\n", last_record_idx);

    /* if bootseq sector is full or empty, erase whole sector */
    if (last_record_idx >= num_bootseq_rec - 1 ||
        last_record_idx < 0) {
        /* bs_debug */
        printf(" bootseq_sector_start_offset = %d\n", bootseq_sector_start_offset);

        if (board_spi_flash_erase(bootseq_sector_start_offset,
                                  bootseq_sector_len,
                                  0)){

            printf("bootseq sector erase fail !!!\n");
            return -1;
        }
        printf(" bootseq erase done \n");

        current_index = 0;
    } else {
        current_index = last_record_idx + 1;
    }

    /* add magic signature to the record */
    memcpy(bootinfo->sb_magic, BOOTSEQ_MAGIC_STR, BOOTSEQ_MAGIC_LEN);

    /* set the current boot record version */
    bootinfo->sb_slice.sl_fields.version = CURR_BOOT_REC_VERSION;

    return board_spi_flash_write(bootinfo,
                bootseq_sector_start_offset + current_index * (sizeof(bootseqinfo_t)),
                sizeof(bootseqinfo_t), 0);

}

/*
 * Reset the boot sequencing information.
 * This is needed when someone changes
 * boot.devlist.
 */
void
srx_siege_reset_bootseq (const char *bootlist, int32_t last_good_idx)
{
    bootseqinfo_t binfo;
    int i = 0;

    i = get_default_dev(bootlist);

    /*
     * reset the retry count, set the next boot dev to
     * first dev in bootdev list environment.
     */
    binfo.sb_next_bootdev = i;
    binfo.sb_cur_bootdev  = i;
    binfo.sb_retry_count  = 0;
    binfo.sb_boot_success = 0;

    /* reset the slice and set boot mode to normal */
    binfo.sb_slice.sl_fields.next_slice = SELECT_ACTIVE_SLICE;
    binfo.sb_slice.sl_fields.boot_mode = BOOT_MODE_NORMAL;

    save_booseq_record (&binfo, last_good_idx);
}


/**
 * @brief
 * Get the device index from the devices defined
 * in the list. For example, 0 from disk0:, 1
 * from disk1: etc.
 *
 * @param[in] dev_name
 * Device name string from which ID is to be extracted.
 */
int
get_devid_from_device (const uint8_t *dev_name)
{
    int dev_unit = -1;

    if (dev_name == NULL) {
        goto cleanup;
    }

    int len = strlen(dev_name);

    if (!len) {
        goto cleanup;
    }

    /*
     * Devices are named disk0, disk1. Where
     * numbers appended to their name are unit or device
     * id. We can use these appended number to call
     * disk read vector. Take the number out from name.
     */
    if (dev_name[len - 1] == ':') {
        dev_unit = dev_name[len - 2] - '0';
    } else {
        dev_unit = dev_name[len - 1] - '0';
    }

    /*
     * check if its a valid number.
     */
    if (IS_NUMERAL(dev_unit))
        goto cleanup;
    else {
        dev_unit = -1;
    }

cleanup:
    return dev_unit;
}

/*
 * @brief
 * Little endian 16-bit shuffling.
 *
 * @param[in] pp
 * Pointer to 16-bit value.
 */
static uint16_t
le16dec(const void *pp)
{
    unsigned char const *p = (unsigned char const *)pp;

    return ((p[1] << 8) | p[0]);
}

/*
 * @brief
 * Check if the buffer given is a Master Boot Record.
 *
 * @param[in] sector_buf
 * Pointer to the 512-bytes buffer containing data
 * read out from master boot record of a device.
 */
static int
ismbr (uint8_t *sector_buf)
{
    uint8_t *p;
    uint32_t index, sum;
    uint16_t magic;

    magic = le16dec(sector_buf + DISK_PART_MAGIC_OFFSET);

    /* check if 0xAA, 0x55 are present */
    if (magic != DISK_PART_MAGIC) {
    return 0;
    }

    /*
     * What follows is to avoid false positives when presented
     * with a FAT12, FAT16 or FAT32 file system. The boot sector
     * has the same magic number as a MBR.
     */
    for (index = 0; index < NUM_DISK_PART; index++) {
    p = sector_buf + DISK_PART_TBL_OFFSET + index * DISK_PART_SIZE;
    if (p[0] != 0 && p[0] != ACTIVE_FLAG) {
        return (0);
    }
    }

    sum = 0;
    for (index = 0; index < NUM_DISK_PART * DISK_PART_SIZE; index++) {
    sum += sector_buf[DISK_PART_TBL_OFFSET + index];
    if (sum != 0) {
        return (1);
    }
    }

    /*
     * At this point we could have an empty MBR. We treat that
     * as not having a MBR at all. Without slices, there cannot
     * be any partitions and/or file systems to open anyway.
     * The FAT file system code will correctly reject this as
     * a boot sector.
     */
    return (0);
}


/**
 * @brief
 * Read master boot record from given device
 *
 * @param[in] dev
 * Device index in u-boot device list.
 *
 * @param[out] buf
 * A 512-byte buffer in which MBR should be copied.
 *
 * @warning
 * buf should be at least 512-byte long.
 */
static int
read_device_mbr (int dev, uint8_t *buf)
{
    disk_read_vector rvec;

    /*
     * Get the disk read vector from Jump table.
     */
    rvec = gd->jt[XF_board_disk_read];

    if (!rvec) {
        BSDEBUG("Error: Jump table not initialized!\n");
        return -1;
    }

    /* Read the MBR. */
    if (rvec(dev, 0, 1, buf) != 0) {
        BSDEBUG("Error: Cannot read MBR on device %d\n", dev);
        return -1;
    }

    if (!ismbr(buf)) {
        BSDEBUG("Error: Invalid entries in MBR in device %d\n", dev);
        return -1;
    }

    return 0;
}

/**
 * @brief
 * Get the active slice for given device.
 *
 * @param[in] dev
 * Index into the device list.
 */
int
get_active_slice (int dev)
{
    uint8_t buf[MBR_BUF_SIZE];
    disk_part_t *dp;
    int idx = 0, found = 0;

    if (read_device_mbr(dev, buf) == 0) {
        dp = (disk_part_t *)(buf + DISK_PART_TBL_OFFSET);

        /* for each entry in MBR find slice marked active */
        for (idx = 0; idx < MAX_NUM_SLICES; idx++, dp++) {

            /* check if the slice is active */
            if (dp->boot_flag == ACTIVE_FLAG) {
                found = TRUE;
                break;
            }
        }
    }

    return (found ? (idx + 1) : -1);
}

/**
 * @brief
 * This function returns the recovery slice as specified by
 * environment variable.
 */
static inline int
get_recovery_slice (void)
{
    int aslice;

    aslice = simple_strtoul(getenv(RECOVERY_SLICE_ENV), NULL, 10);

    if (!IS_VALID_SLICE(aslice)) {
        BSDEBUG("Invalid recovery slice %d\n", aslice);
        aslice = DEFAULT_RECOVERY_SLICE;
    }

    return aslice;
}

/**
 * @brief
 * Checks if given slice number in the given device
 * is marked as a BSD slice in MBR.
 *
 * @warning
 * Slice number are expected from 1 to 4.
 *
 * @param[in] dev
 * Index into the device list.
 *
 * @param[in] slice
 * Slice number to check.
 */
int
is_bsd_slice (int dev, int slice)
{
    uint8_t buf[MBR_BUF_SIZE];
    disk_part_t dp;

    if (!IS_VALID_SLICE(slice)) {
        return FALSE;
    }

    /*
     * Slice number are from 1 to 4,
     * but indexing on disk goes 0 to 3.
     * Adjust slice value for indexing.
     */
    slice--;

    if (read_device_mbr(dev, buf) == 0) {
        memcpy(&dp, buf + DISK_PART_TBL_OFFSET + slice *
                DISK_PART_SIZE, sizeof(dp));

        /* if slice type is BSD */
        if (dp.part_type == BSD_MAGIC) {
            return TRUE;
        }
    }

    return FALSE;
}

/**
 * @brief
 * Checks the number of BSD slices in given device.
 *
 * @param[in] dev
 * Index into device list.
 */
int
get_num_bsd_slices (int dev)
{
    uint8_t buf[MBR_BUF_SIZE];
    disk_part_t *dp;
    int bsd_slices = 0, counter;

    if (read_device_mbr(dev, buf) == 0) {
        dp = (disk_part_t *)(buf + DISK_PART_TBL_OFFSET);

        for (counter = 0; counter < MAX_NUM_SLICES; counter++, dp++) {
            /* if slice type is BSD, increment the counter. */
            if (dp->part_type == BSD_MAGIC) {
                bsd_slices++;
            }
        }
    }

    return bsd_slices;
}


/**
 * @brief
 * This function is the heart of slicing logic, i.e.
 * next slice to be tried on a given device.
 * Input to this function is device index and the current
 * slice that is being tried. Based on the current slice
 * that is being tried it decides on next slice to be tried.
 * Here is the function's behaviour in differnt scenarios.
 *   If current slice is invalid, return "reset" slice
 *       as next slice.
 *   Increment the current slice and take it as next slice.
 *       then do following:
 *       1.  check if its active slice, return "reset as next
 *           slice, because if next slice to be tried is same as
 *           active slice, it means that all slices have been tried.
 *       2.  If its next slice to be tried is not active, check if
 *           its recovery slice. If its recovery slice, skip this
 *           slice and try next.
 *       3.  otherwise return this slice as next slice.
 *
 * @param[in] curr_slice
 * Current slice is being tried and based on which next slice
 * should be calculated.
 */
int
get_next_slice_for_device (int dev, int curr_slice)
{
    int next_slice = SELECT_ACTIVE_SLICE, active_slice, recovery_slice;
    int done = 0;

    /* in case of invalid slice reset the next slice */
    if (!IS_VALID_SLICE(curr_slice)) {
        goto cleanup;
    } else {
        /*
         * Get the active slice for this device.
         * We will use this to check if we have tried all slices.
         */
        active_slice = get_active_slice(dev);

        /*
         * Something is seriously wrong if finding active slice
         * failed. Better go by defaults.
         */
        if (active_slice < 0) {
            BSDEBUG("Invalid active slice for device %d\n", dev);
            goto cleanup;
        }

        recovery_slice = get_recovery_slice();

        /*
         * Using current slice as starting index, we will
         * move to next slice by incrementing it by one.
         */
        next_slice = curr_slice + 1;
        next_slice = (next_slice <= MAX_NUM_SLICES ? next_slice : FIRST_SLICE);

        /*
         * Starting from the slice will circulate the in the
         * slice list until we find a valid next slice for
         * given slice.
         */
        do {
            BSDEBUG("Next candidate slice: %d\n", next_slice);

            /*
             * If next slice that we calculated is same as active.
             * we have tried all slices. So reset the slice.
             */
            if (next_slice == active_slice) {
                BSDEBUG("%d slice is same as active. Resetting slice.\n");
                next_slice = SELECT_ACTIVE_SLICE;
                break;
            }

            /*
             * Keep trying the next slice until we reach
             * a valid BSD slice.
             */
            if (!is_bsd_slice(dev, next_slice)) {
                BSDEBUG("Invalid next slice %d\n", next_slice);
                next_slice++;
                next_slice = (next_slice <= MAX_NUM_SLICES ? next_slice : FIRST_SLICE);
                continue;
            }

            /*
             * Only if number of bsd slices are greater than one, we skip
             * recovery slice. This will prevent user to set recover_slice
             * to 1 on JUNOS images which support only one
             * partition.
             */
            if (get_num_bsd_slices(dev) > 1 &&
                    next_slice == recovery_slice) {
                BSDEBUG("%d slice is recovery slice. Skipping.\n", next_slice);
                next_slice++;
                next_slice = (next_slice <= MAX_NUM_SLICES ? next_slice : FIRST_SLICE);
                continue;
            }

            /* currently Siege device support dual partition boot, which is 4 partition.*/
            if (get_num_bsd_slices(dev) > 1 &&
                    next_slice == DEFAULT_CONFIG_SLICE) {
                BSDEBUG("%d slice is config slice. Skipping.\n", next_slice);
                next_slice++;
                next_slice = (next_slice <= MAX_NUM_SLICES ? next_slice : FIRST_SLICE);
                continue;
            }

            done = 1;
        } while (!done);
    }

cleanup:
    return next_slice;
}

int32_t
get_next_bootdev_jt (uint8_t *bootdev)
{
    return get_next_bootdev(bootdev, 1);
}

/*
 * get_next_bootdev srxsme platform specfic implementation
 * of boot sequencing and returns
 * get next
 * output : bootdev
 */

int32_t
get_next_bootdev (uint8_t *bootdev, int32_t update)
{
    unsigned int bootsuccess;
    unsigned int next_bootdev, cur_bootdev, tmp_bootdev;
    unsigned int retrycount = 0;
    unsigned int count = 0;
    int disk_default = 0;
    int slice, curr_slice, device_id, boot_mode;
    uint8_t slice_buffer[8];
    int32_t     last_good_idx;

    bootseqinfo_t previous_bootinfo;
    bootseqinfo_t current_bootinfo;
    unsigned long boot_unattended;

    /*
     * If boot sequencing is disabled, don't
     * do anything. currdev will anyways be
     * set to the default device.
     */
    if (IS_BOOT_SEQ_DISABLED()) {
        strcpy(bootdev, "disk0");
        return 0;
    }

    /*
     * set the default disk to
     * first dev in bootdev list environment.
     */
    disk_default = get_default_dev(getenv(SRX_SIEGE_BOOTDEVLIST_ENV));
    bs_debug("disk_default = %d\n", disk_default);

    /* changed by siege */
    /* failed to get default dev, use first one */
    if (disk_default == -1)
        disk_default = 0;

    /* tickle watchdog */
    reload_watchdog(PAT_WATCHDOG);

    /* Read bootseq record info from flash */

    last_good_idx = read_last_booseq_record(&previous_bootinfo);

    /* If boot record version is incompatible, go by defaults */
    if (!VALID_BOOT_REC_VERSION(previous_bootinfo.sb_slice.sl_fields.version)) {
        BSDEBUG("Boot record with invalid version %d.\n",
                previous_bootinfo.sb_slice.sl_fields.version);
        previous_bootinfo.sb_slice.sl_fields.next_slice = SELECT_ACTIVE_SLICE;
        previous_bootinfo.sb_slice.sl_fields.boot_mode = BOOT_MODE_NORMAL;
    }

    /*
     * copy entire previous boot record read from flash to the current
     * record that will be written on to flash	with some feilds modified.
     */
    memcpy(&current_bootinfo, &previous_bootinfo,
            sizeof(bootseqinfo_t));

    /* validate the record itself */
    if (memcmp(previous_bootinfo.sb_magic, BOOTSEQ_MAGIC_STR,
                BOOTSEQ_MAGIC_LEN) != 0) {

        printf("No valid bootsequence record found,continuing with default\n");

        strncpy(current_bootinfo.sb_magic, BOOTSEQ_MAGIC_STR, BOOTSEQ_MAGIC_LEN);
        current_bootinfo.sb_retry_count  = 0;
        current_bootinfo.sb_next_bootdev = disk_default;
        current_bootinfo.sb_cur_bootdev  = disk_default;
        current_bootinfo.sb_boot_success = 0;

        /* reset the slice and set boot mode to normal */
        current_bootinfo.sb_slice.sl_fields.next_slice = SELECT_ACTIVE_SLICE;
        current_bootinfo.sb_slice.sl_fields.boot_mode = BOOT_MODE_NORMAL;

        strcpy(bootdev, p_siege_dev_map[disk_default].sd_diskname);

        /*
         * Try to get an active slice to be appended to default
         * disk we are returning. Also if successful, get the
         * next slice to boot from.
         *
         * get_devid_from_device is back
         * bone of slicing infrastructure. If its failing,
         * we have something seriously wrong here. Better
         * we continue with old sequencing scheme where we
         * don't append any slicing info to device. If in case,
         * things are bad only here, then loader will still
         * be able to boot.
         */
        device_id = get_devid_from_device(bootdev);
        bs_debug("device_id = %d\n", device_id);

        if ((curr_slice = get_active_slice(device_id)) > 0) {
            BSDEBUG("%d is active on device %d\n", curr_slice, device_id);
            slice = get_next_slice_for_device(device_id, curr_slice);

            /*
             * if we got a reset slice in return, it means we
             * can't continue with the same media next time.
             * change the media.
             */
            if (slice == SELECT_ACTIVE_SLICE) {
                BSDEBUG("Next slice for %d is reset. Flipping next device\n");
                next_bootdev = disk_default + 1;
                next_bootdev = next_bootdev % num_bootable_media;
                current_bootinfo.sb_next_bootdev = next_bootdev;
            }

            current_bootinfo.sb_slice.sl_fields.next_slice = slice;
        } else {
            /*
             * If no slicing information was found, it means
             * there was something wrong with reading MBR.
             * Either MBR was corrupt or we had some problem
             * in reading it. Continue with default slice.
             */
            printf("WARNING: No MBR found in media %s. "
                    "Using slice %d as default\n",
                    bootdev, DEFAULT_SLICE_TO_TRY);
            slice = curr_slice = DEFAULT_SLICE_TO_TRY;
            next_bootdev = disk_default + 1;
            next_bootdev %= num_bootable_media;

            current_bootinfo.sb_next_bootdev = next_bootdev;

            /* try active of next device */
            current_bootinfo.sb_slice.sl_fields.next_slice = SELECT_ACTIVE_SLICE;
        }

        /*
         * If everything was fine, slice will have a valid slice
         * in it. If still an invalid slice, use default slice
         */
        if (!IS_VALID_SLICE(curr_slice)) {
            BSDEBUG("Invalid slice %d. Using default slice.\n", curr_slice);
            curr_slice = DEFAULT_SLICE_TO_TRY;
        }

        /* append slice information to device */
        snprintf(slice_buffer, sizeof(slice_buffer),"s%d", curr_slice);
        strncat(bootdev, slice_buffer, sizeof(slice_buffer)-1);

        printf("[%d]Booting from %s slice %d\n", current_bootinfo.sb_retry_count,
                p_siege_dev_map[disk_default].sd_devname , curr_slice);

        if (update) {
            save_booseq_record(&current_bootinfo, last_good_idx);
        }

        return 0;
    }

    /*
     * find out whats is the retry count, this count
     * indicates how many times loader has looped
     * to boot kernel and failed
     */
    retrycount = previous_bootinfo.sb_retry_count;

    /* validate the data present in record needed for bootup */
    cur_bootdev  = previous_bootinfo.sb_cur_bootdev;
    next_bootdev = previous_bootinfo.sb_next_bootdev;
    bootsuccess  = previous_bootinfo.sb_boot_success;
    curr_slice = previous_bootinfo.sb_slice.sl_fields.next_slice;
    boot_mode = previous_bootinfo.sb_slice.sl_fields.boot_mode;
	
    bs_debug("### read bootinfo cur_dev %d, next_dev %d, success %d, retry %d,curr_slice %d, boot_mode %d!\r\n",
            cur_bootdev, next_bootdev, bootsuccess, retrycount, curr_slice, boot_mode);

    /*
     * validate the values present in record related to
     * bootseq, if any feild is found invalid just boot from
     * internal nand flash.
     */
    if ((cur_bootdev >= num_bootable_media)  ||
            (next_bootdev >= num_bootable_media) ||
            (bootsuccess > 1)) {
        /*
         *  found invalid data
         *  try booting only from default device
         *  and also create and write new record
         *  with proper values
         */
        current_bootinfo.sb_retry_count  = 0;
        current_bootinfo.sb_next_bootdev = disk_default;
        current_bootinfo.sb_cur_bootdev  = disk_default;
        current_bootinfo.sb_boot_success = 0;
        strcpy(bootdev, p_siege_dev_map[disk_default].sd_diskname);

        /* reset the slice and set boot mode to normal */
        current_bootinfo.sb_slice.sl_fields.next_slice = SELECT_ACTIVE_SLICE;
        current_bootinfo.sb_slice.sl_fields.boot_mode = BOOT_MODE_NORMAL;

        /*
         * Try to get an active slice to be appended to default
         * disk we are returning.
         */
        device_id = get_devid_from_device(bootdev);
        if ((slice = get_active_slice(device_id)) > 0) {
            snprintf(slice_buffer, sizeof(slice_buffer),"s%d", slice);
            strncat(bootdev, slice_buffer, sizeof(slice_buffer)-1);
        }

        printf("Invalid boot sequence records found,continuing with default\n");
        if (update) {
            save_booseq_record(&current_bootinfo, last_good_idx);
        }
        return 0;
    }

    boot_unattended = getenv_ulong("boot_unattended", 10, 0);

    /*
     * if retrycount exceeds the defined BOOTSEQ_MAX_RETRIES,
     * disable watchdog, so this time even though kernel is not
     * found in any media loader just stay in loader prompt
     */
    if ((retrycount >= BOOTSEQ_MAX_RETRIES) &&
            (bootsuccess != 1)) {
        /*
         * reset the retry count, set the next boot dev to
         * default dev.
         */
        current_bootinfo.sb_retry_count  = 0;
        current_bootinfo.sb_next_bootdev = disk_default;
        current_bootinfo.sb_cur_bootdev  = disk_default;
        current_bootinfo.sb_boot_success = 0;

        /* reset the slice and set boot mode to normal */
        current_bootinfo.sb_slice.sl_fields.next_slice = SELECT_ACTIVE_SLICE;
        current_bootinfo.sb_slice.sl_fields.boot_mode = BOOT_MODE_NORMAL;

        strcpy(bootdev, p_siege_dev_map[disk_default].sd_diskname);
        bs_debug("### exceed max retry count, booting with default device!");
        /*
         * Try to get an active slice to be appended to default
         * disk we are returning.
         */
        device_id = get_devid_from_device(bootdev);
        if ((slice = get_active_slice(device_id)) > 0) {
            snprintf(slice_buffer, sizeof(slice_buffer),"s%d", slice);
            strncat(bootdev, slice_buffer, sizeof(slice_buffer)-1);
        }

        if (update) {
            save_booseq_record(&current_bootinfo, last_good_idx);
        }
        reload_watchdog(DISABLE_WATCHDOG);
        return 0;
    } else if ((retrycount == NORMAL_MODE_BOOTSEQ_RETRIES) &&
            (bootsuccess != 1) &&
            !boot_unattended) {

        printf("WARNING: Failed to boot normally. "
                "Switching to recovery mode.\n");
        bs_debug("### reach to max retry count %d, boot with recovery!", NORMAL_MODE_BOOTSEQ_RETRIES);

        /*
         * Return a device which is enabled. If no device is enabled,
         * return error and reset boot sequencing. As a result of returning error,
         * loader will fall to loader prompt.
         */
        for (tmp_bootdev = disk_default; tmp_bootdev < num_bootable_media;
                tmp_bootdev++) {
            if (srx_siege_is_device_enabled(tmp_bootdev)) {
                break;
            }
        }

        /* No device is enabled in boot.devlist. Return error. */
        if (tmp_bootdev == num_bootable_media) {
            srx_siege_reset_bootseq(getenv(SRX_SIEGE_BOOTDEVLIST_ENV), last_good_idx);
            reload_watchdog(DISABLE_WATCHDOG);
            return -1;
        }

        strcpy(bootdev, p_siege_dev_map[tmp_bootdev].sd_diskname);

        /*
         * Normal tries were done in previous invocations. we
         * will enter in recovery mode and try the default media now.
         */
        next_bootdev = tmp_bootdev + 1;
        next_bootdev %= num_bootable_media;

        /*
         * Set the next boot dev to default dev but
         * dont reset the retry count rather increase it,
         * because next we will try in recovery mode.
         */
        current_bootinfo.sb_retry_count  += 1;
        current_bootinfo.sb_next_bootdev = next_bootdev;
        current_bootinfo.sb_cur_bootdev  = tmp_bootdev;
        current_bootinfo.sb_boot_success = 0;

        /* set the slice to recovery and set boot mode to recovery */
        current_bootinfo.sb_slice.sl_fields.boot_mode = BOOT_MODE_RECOVERY;

        current_bootinfo.sb_slice.sl_fields.next_slice = get_recovery_slice();

        snprintf(slice_buffer, sizeof(slice_buffer), "s%d",
                current_bootinfo.sb_slice.sl_fields.next_slice);
        strncat(bootdev, slice_buffer, sizeof(slice_buffer)-1);

        printf("[%d]Booting from %s slice %d\n", current_bootinfo.sb_retry_count,
                p_siege_dev_map[tmp_bootdev].sd_devname,
                current_bootinfo.sb_slice.sl_fields.next_slice);

        if (update) {
            save_booseq_record(&current_bootinfo, last_good_idx);
        }

        return 0;
    }

    /*
     * check "bootsuccess", this is needed to manage
     * retry_count
     */
    if (bootsuccess) {
        /*
         * clear retry count, indicates that kernel was booted last
         * time, and now we are trying to boot from other media
         */
        current_bootinfo.sb_retry_count = 0;

        /* boot success, still boot from this dev. */
        next_bootdev = cur_bootdev;

        /*
         * If box boot up successfully, from older JUNOS images, slice
         * might not be set to reset. Set it to reset explicitly.
         * Reset the boot mode also.
         */
        curr_slice = SELECT_ACTIVE_SLICE;
        boot_mode = BOOT_MODE_NORMAL;
        bs_debug("### boot success, select active slice!");
    } else {
        /*
         * loader is trying to boot kernel from media available
         * but failing, so increment retry count each time to
         * keep track of how many time loader tried in this path
         * since last kernl boot
         */
        current_bootinfo.sb_retry_count = retrycount + 1;
        BSDEBUG("Retry count: %d\n", current_bootinfo.sb_retry_count);
    }
    /*
     * Now decide which device to boot from
     * reset: disk0:
     * request system reboot: disk0:
     * request system reboot media internal: disk0:
     * request system reboot media usb: disk1:
     *
     */
    while (count < num_bootable_media) {

        strcpy(bootdev, p_siege_dev_map[disk_default].sd_diskname);

        /*
         * check is 'nextboot' is present try to boot from next by traversing
         * boot list
         */
        if (srx_siege_is_bootdev_present(next_bootdev) &&
                (p_siege_dev_map[next_bootdev].sd_flags & SD_DEVICE_ENABLED)) {

            strcpy(bootdev, p_siege_dev_map[next_bootdev].sd_diskname);
            BSDEBUG("Using %s for booting\n", bootdev);

            device_id = get_devid_from_device(bootdev);

            /* device booting from */
            current_bootinfo.sb_cur_bootdev = next_bootdev;

            /*
             * if boot mode is recovery, we don't do much
             * except for flipping the boot media. Slice
             * remains the same.
             */
            if (boot_mode == BOOT_MODE_RECOVERY) {

                slice = get_recovery_slice();

                BSDEBUG("Recover Mode: Got Slice %d as recover\n", slice);

                /*
                 * If already chosen slice from boot record is not
                 * recovery slice, set it to recovery slice.
                 */
                if (curr_slice != slice)
                    curr_slice = slice;

                BSDEBUG("Boot mode is recovery. Flipping media.\n");

                /*
                 * if we are in recovery mode, there
                 * is only one slice to try. We can
                 * flip the next boot device right away
                 * as we don't have to wait to try other slices.
                 */
                next_bootdev++;
                next_bootdev %= num_bootable_media;
                current_bootinfo.sb_slice.sl_fields.boot_mode = BOOT_MODE_RECOVERY;
            } else {
                /*
                 * If current slice points to reset. we need to try
                 * from active.
                 */
                if (curr_slice == SELECT_ACTIVE_SLICE) {
                    curr_slice = get_active_slice(device_id);
                    BSDEBUG("Current slice is reset. Reading active(%d).\n",
                            curr_slice);
                }

                /*
                 * If for reasons, we couldn't find active,
                 * go by default slice.
                 */
                if (!IS_VALID_SLICE(curr_slice)) {
                    BSDEBUG("Invalid current slice %d. Using default\n",
                            curr_slice);
                    curr_slice = DEFAULT_SLICE_TO_TRY;
                }

                slice = get_next_slice_for_device(device_id, curr_slice);
                BSDEBUG("Next slice for %d is %d\n", curr_slice, slice);

                /*
                 * flip device only when getting other slice info failed. Get
                 * next slice function will fail only when there is no MBR or
                 * next slice cylcing has reached.
                 */
                if (slice == SELECT_ACTIVE_SLICE) {
                    BSDEBUG("Boot mode is not recovery but next slice is reset."
                            " Flipping media.\n");
                    next_bootdev++;
                    next_bootdev %= num_bootable_media;
                }

                current_bootinfo.sb_slice.sl_fields.boot_mode = BOOT_MODE_NORMAL;
            }

            snprintf(slice_buffer, sizeof(slice_buffer),"s%d", curr_slice);
            strncat(bootdev, slice_buffer, sizeof(slice_buffer)-1);

            printf("[%d]Booting from %s slice %d\n", current_bootinfo.sb_retry_count,
                    p_siege_dev_map[current_bootinfo.sb_cur_bootdev].sd_devname,
                    curr_slice);

            current_bootinfo.sb_slice.sl_fields.next_slice = slice;

            BSDEBUG("Next Boot Dev: %d Slice: %d\n", next_bootdev, slice);


            /*
             * device the loader should try booting next time
             */
            current_bootinfo.sb_next_bootdev = next_bootdev;

            /*
             * clear bootsuccess
             */
            current_bootinfo.sb_boot_success = 0;

            /*
             * able to determine which device to boot from
             * come out of while
             */
            break;

        } else {
            BSDEBUG("Device %d is not present or enabled.\n", next_bootdev);
            /*
             * if the device was not found, just increment the list
             * and check is that device device is avaliable and can be
             * booted from
             */
            next_bootdev++;
            next_bootdev = next_bootdev % num_bootable_media;
            curr_slice = SELECT_ACTIVE_SLICE;
        }
        count++;
    }

    if (count == num_bootable_media) {
        /*
         * reset the retry count, set the next boot dev to
         * default dev.
         */
        current_bootinfo.sb_retry_count  = 0;
        current_bootinfo.sb_next_bootdev = disk_default;
        current_bootinfo.sb_cur_bootdev  = disk_default;
        current_bootinfo.sb_boot_success = 0;

        /* reset the slice and set boot mode to normal */
        current_bootinfo.sb_slice.sl_fields.next_slice = SELECT_ACTIVE_SLICE;
        current_bootinfo.sb_slice.sl_fields.boot_mode = BOOT_MODE_NORMAL;

        strcpy(bootdev, p_siege_dev_map[disk_default].sd_diskname);

        if (update) {
            save_booseq_record(&current_bootinfo, last_good_idx);
        }
        reload_watchdog(DISABLE_WATCHDOG);
        return -1;
    }

    /*
     * handle_booseq_record for write cmd can fail if flash
     * problems are found and if write fails to write new record needed
     * for nextboot up and if previous	record is valid and pointing
     * to some device, the loader always tries to boot from it,
     * so rather than allowing loader trying some device,
     * force it to try default always.
     */
    if (update && save_booseq_record(&current_bootinfo, last_good_idx)) {
        printf("Failed to create new record, Booting from default\n");
        strcpy(bootdev, p_siege_dev_map[disk_default].sd_diskname);
    }
    return 0;
}

/*
 * get_next_bootdev reads next bootdev from bootflash
 */
/* no one use it currently */
uint8_t
get_next_bootdev_disk_id (void)
{
    bootseqinfo_t next_bootinfo;
    uint8_t bootdev;
    int32_t last_good_idx;

    /* Read bootseq record info from flash */
    last_good_idx = read_last_booseq_record(&next_bootinfo);

    if (last_good_idx >=0 ) {
        bootdev = next_bootinfo.sb_next_bootdev;
        if (next_bootinfo.sb_next_bootdev >= num_bootable_media) {
            bootdev = DISK_FIRST;
        }
    } else {
        bootdev = DISK_FIRST;
    }

    return bootdev;
}

/*
 * srxsme_show_bootdev_list displays the bootable device
 * for the platform.
 */
void
show_bootdev_list (void)
{
   unsigned int i;

   printf("Platform: %s\n", platform_name);
   for (i = 0; i< num_bootable_media; i++) {
       printf("    %s\n", p_siege_dev_map[i].sd_devname);
   }
}

/*
 * srxsme_set_next_bootdev selects the "bootdev"
 * as next boot device
 */
int32_t
set_next_bootdev (uint8_t *bootdev)
{
    uint32_t i = 0;
    bootseqinfo_t current_bootinfo;
    bootseqinfo_t previous_bootinfo;
    int32_t last_good_idx;

    if (IS_BOOT_SEQ_DISABLED()) {
        return 0;
    }

    /*
     * Read bootseq record info from flash
     */
    last_good_idx = read_last_booseq_record(&previous_bootinfo);

    /*
     * copy entire previous boot record read from flash to the current
     * record that will be written on to flash  with some feilds modified.
     */
    memcpy(&current_bootinfo, &previous_bootinfo,
            sizeof(bootseqinfo_t));

    for (i = 0; i < num_bootable_media; i++) {
        if (strcmp((const char *)bootdev,
                    (const char *)p_siege_dev_map[i].sd_devname) == 0) {
            current_bootinfo.sb_boot_success = 0;
            current_bootinfo.sb_retry_count = 0;
            printf("Setting next boot dev %s\n", bootdev);
            current_bootinfo.sb_next_bootdev = i;
            current_bootinfo.sb_cur_bootdev = i;
            current_bootinfo.sb_slice.sl_fields.next_slice = SELECT_ACTIVE_SLICE;
            current_bootinfo.sb_slice.sl_fields.boot_mode = BOOT_MODE_NORMAL;
            save_booseq_record(&current_bootinfo, last_good_idx);
            break;
        }
    }
    if (i == num_bootable_media) {
        printf("Invalid device %s\n", bootdev);
        return -1;
    }
    return 0;
}


int
disk_scan (int dev)
{
    int rt;
    switch (gd->arch.board_desc.board_type) {
        CASE_ALL_JSRX_AIRBUS_MODELS
            if (dev == -1) {
                return scan_sata_devices();

            } else {
                rt = usb_disk_scan(dev-1);
                if (rt != -1) /* usb disk exist, use usb_disk + 1 */
                    rt += 1;
                return rt;

            }
            break;
        CASE_ALL_JSRX_SWORD_MODELS
        CASE_ALL_JSRX_TRIDENT_MODELS
        default:
            return usb_disk_scan(dev);
    }
}

int
board_disk_read (int dev, int lba, int totcnt, void *buf)
{
    int rc = 0;
    switch (gd->arch.board_desc.board_type) {
        CASE_ALL_JSRX_AIRBUS_MODELS
            if (dev == 0) {
                /* device 0 is SSD */
                rc = sata_read(CONFIG_BOARD_SATA_DEVICE, lba, totcnt, (char *)buf);
                return (rc > 0) ? (totcnt-rc) : totcnt;

            } else {
                return usb_disk_read(dev - 1, lba, totcnt, (char *)buf);
            }
            break;
        CASE_ALL_JSRX_SWORD_MODELS
        CASE_ALL_JSRX_TRIDENT_MODELS
        default:
            return usb_disk_read(dev, lba, totcnt, (char *)buf);
    }

}


int
board_disk_write (int dev, int lba, int cnt, void *buf)
{
    int rc = 0;
    switch (gd->arch.board_desc.board_type) {
        CASE_ALL_JSRX_AIRBUS_MODELS
            if (dev == 0) {
                /* device 0 is SSD */
                rc = sata_write(CONFIG_BOARD_SATA_DEVICE, lba, cnt, buf);
                return (rc > 0) ? (cnt-rc) : cnt;
            } else {
                return usb_disk_write(dev-1, lba, cnt, buf);
            }
            break;
        CASE_ALL_JSRX_SWORD_MODELS
        CASE_ALL_JSRX_TRIDENT_MODELS
        default:
            return usb_disk_write(dev, lba, cnt, buf);
    }

}

extern void hw_watchdog_start(int msecs);
extern void hw_watchdog_disable(void);
extern void hw_watchdog_reset(void );
/*
 * reload_watchdog: common routine for branching out
 * of watchdog functionality
 */

static int siege_wtd_status = 0;

/* API in JT table */
void
reload_watchdog (int32_t val)
{
    if (val == PAT_WATCHDOG) {
        hw_watchdog_reset();
    } else if (val == DISABLE_WATCHDOG) {

        if ( siege_wtd_status != 1) {
            hw_watchdog_disable();
            siege_wtd_status = 1;
        }

    } else if (val == ENABLE_WATCHDOG) {
		char *e;
		int msecs = 0;
		if ((e = getenv("watchdog_timeout")) != NULL) {
			msecs = simple_strtoul(e, NULL, 0);
		}
		if (!msecs)
			msecs = CONFIG_OCTEON_WD_TIMEOUT * 1000;

        if ( siege_wtd_status != 2) {
            hw_watchdog_start(msecs);
            siege_wtd_status = 2;
        }

    }
}

void
reload_cpld_watchdog (int val)
{
    if (val == PAT_WATCHDOG) {
        pat_srx_siege_cpld_watchdog();
    } else if (val == DISABLE_WATCHDOG) {
        /*
         * disable watchdog
         */
        disable_srx_siege_watchdog();
    } else if (val == ENABLE_WATCHDOG) {
        /*
         * enable watchdog
         */
        enable_srx_siege_cpld_watchdog();
    }
}

void
update_loaderdev(void)
{
    unsigned char bootdev[64];

    get_next_bootdev(bootdev, 0);
    /* bootdev format is: disk0s1 or disk1s1 */
    if (bootdev[5] == 's')
        bootdev[5] = ':';

    setenv("loaderdev", bootdev);
}

char *
get_devname_by_disk_id(uint32_t id)
{
    if (id < num_bootable_media) {
        return p_siege_dev_map[id].sd_devname;
    }
}

void
set_last_booseq_record_finish(void)
{
    int32_t last_good_idx;
    bootseqinfo_t bootinfo;
    uint32_t num_bootseq_rec = bootseq_sector_len / sizeof(bootseqinfo_t);

    last_good_idx = read_last_booseq_record(&bootinfo);
    if (last_good_idx < 0 || last_good_idx >= num_bootseq_rec)
        return;

    bootinfo.sb_boot_success = 1;
    save_booseq_record(&bootinfo, last_good_idx);
}

int
srx_siege_support_boot_sata (void)
{
    DECLARE_GLOBAL_DATA_PTR;

    /* choose whether to enum SATA device for veloader */
    switch (gd->arch.board_desc.board_type) {
        CASE_ALL_JSRX_SWORD_MODELS
        CASE_ALL_JSRX_TRIDENT_MODELS
            return 0;
        CASE_ALL_JSRX_AIRBUS_MODELS
            return 1;
        default:
            return 0;
    }
}
