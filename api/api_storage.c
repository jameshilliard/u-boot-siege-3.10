/*
 * (C) Copyright 2007-2008 Semihalf
 *
 * Written by: Rafal Jaworowski <raj@semihalf.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <config.h>
#include <common.h>
#include <api_public.h>

#if defined(CONFIG_CMD_USB) && defined(CONFIG_USB_STORAGE)
#include <usb.h>
#endif
#ifdef CONFIG_SRX_SIEGE
#include <asm/arch-octeon/cvmx-app-init.h>
#include "../board/juniper/srx_siege/srx_siege_board.h"
#endif

#undef DEBUG

#ifdef DEBUG
#define debugf(fmt, args...) do { printf("%s(): ", __func__); printf(fmt, ##args); } while (0)
#else
#define debugf(fmt, args...)
#endif

#define errf(fmt, args...) do { printf("ERROR @ %s(): ", __func__); printf(fmt, ##args); } while (0)


#ifdef CONFIG_SRX_SIEGE
/* move SATA before USB, at srx380, we use sata as disk 0 */
#define ENUM_IDE	0
#define ENUM_SATA   1	
#define ENUM_USB    2	
#define ENUM_SCSI   3	
#define ENUM_MMC    4	
#define ENUM_MAX	5
#else
#define ENUM_IDE	0
#define ENUM_USB	1
#define ENUM_SCSI	2
#define ENUM_MMC	3
#define ENUM_SATA	4
#define ENUM_MAX	5
#endif

struct stor_spec {
    int     start_dev;  /* start_dev_id for this type */
	int		max_dev;
	int		enum_started;
	int		enum_ended;
	int		type;		/* "external" type: DT_STOR_{IDE,USB,etc} */
	char		*name;
};

static struct stor_spec specs[ENUM_MAX] = { { 0, 0, 0, 0, "" }, };

#ifdef CONFIG_SRX_SIEGE
DECLARE_GLOBAL_DATA_PTR;
#endif

void dev_stor_init(void)
{
#if defined(CONFIG_CMD_IDE)
	specs[ENUM_IDE].start_dev = 0;
	specs[ENUM_IDE].max_dev = CONFIG_SYS_IDE_MAXDEVICE;
	specs[ENUM_IDE].enum_started = 0;
	specs[ENUM_IDE].enum_ended = 0;
	specs[ENUM_IDE].type = DEV_TYP_STOR | DT_STOR_IDE;
	specs[ENUM_IDE].name = "ide";
#endif
#if defined(CONFIG_CMD_MMC)
	specs[ENUM_MMC].start_dev = 0;
	specs[ENUM_MMC].max_dev = CONFIG_SYS_MMC_MAX_DEVICE;
	specs[ENUM_MMC].enum_started = 0;
	specs[ENUM_MMC].enum_ended = 0;
	specs[ENUM_MMC].type = DEV_TYP_STOR | DT_STOR_MMC;
	specs[ENUM_MMC].name = "mmc";
#endif
#if defined(CONFIG_CMD_SATA)
	specs[ENUM_SATA].start_dev = 0;
#ifdef CONFIG_SRX_SIEGE
    if (IS_PLATFORM_AIRBUS(gd->arch.board_desc.board_type)) {
        specs[ENUM_SATA].start_dev = 1;
    }
#endif
	specs[ENUM_SATA].max_dev = CONFIG_SYS_SATA_MAX_DEVICE;
	specs[ENUM_SATA].enum_started = 0;
	specs[ENUM_SATA].enum_ended = 0;
	specs[ENUM_SATA].type = DEV_TYP_STOR | DT_STOR_SATA;
	specs[ENUM_SATA].name = "sata";
#endif
#if defined(CONFIG_CMD_SCSI)
	specs[ENUM_SCSI].start_dev = 0;
	specs[ENUM_SCSI].max_dev = CONFIG_SYS_SCSI_MAX_DEVICE;
	specs[ENUM_SCSI].enum_started = 0;
	specs[ENUM_SCSI].enum_ended = 0;
	specs[ENUM_SCSI].type = DEV_TYP_STOR | DT_STOR_SCSI;
	specs[ENUM_SCSI].name = "scsi";
#endif
#if defined(CONFIG_CMD_USB) && defined(CONFIG_USB_STORAGE)
	specs[ENUM_USB].start_dev = 0;
	specs[ENUM_USB].max_dev = USB_MAX_STOR_DEV;
	specs[ENUM_USB].enum_started = 0;
	specs[ENUM_USB].enum_ended = 0;
	specs[ENUM_USB].type = DEV_TYP_STOR | DT_STOR_USB;
	specs[ENUM_USB].name = "usb";
#endif
}

/*
 * Finds next available device in the storage group
 *
 * type:	storage group type - ENUM_IDE, ENUM_SCSI etc.
 *
 * first:	if 1 the first device in the storage group is returned (if
 *              exists), if 0 the next available device is searched
 *
 * more:	returns 0/1 depending if there are more devices in this group
 *		available (for future iterations)
 *
 * returns:	0/1 depending if device found in this iteration
 */
static int dev_stor_get(int type, int first, int *more, struct device_info *di)
{
	int found = 0;
	*more = 0;

	int i;

	block_dev_desc_t *dd;

	if (first) {
		di->cookie = (void *)get_dev(specs[type].name, specs[type].start_dev);
		if (di->cookie == NULL) {
			return 0;
		} else {
			found = 1;
            /*
             * set right *more value, otherwise enum for this type will end.
             */
            if ( (specs[type].start_dev + 1) < specs[type].max_dev) {
                *more = 1;
            }

        }
	} else {

continue_check:
		for (i = specs[type].start_dev; i < specs[type].max_dev; i++)
			if (di->cookie == (void *)get_dev(specs[type].name, i)) {
				/* previous cookie found -- advance to the
				 * next device, if possible */

				if (++i >= specs[type].max_dev) {
					/* out of range, no more to enum */
					di->cookie = NULL;
					break;
				}

				di->cookie = (void *)get_dev(specs[type].name, i);
				if (di->cookie == NULL)
					return 0;
				else
					found = 1;

				/* provide hint if there are more devices in
				 * this group to enumerate */
				if ((i + 1) < specs[type].max_dev)
					*more = 1;

				break;
			}
	}

	if (found) {
		di->type = specs[type].type;

		if (di->cookie != NULL) {
			dd = (block_dev_desc_t *)di->cookie;
			if (dd->type == DEV_TYPE_UNKNOWN) {
				debugf("device instance exists, but is not active..");
				found = 0;
                /* find an invalid one, but we have others to check */
                if (*more) {
                    *more = 0;
                    goto continue_check;
                }
			} else {
				di->di_stor.block_count = dd->lba;
				di->di_stor.block_size = dd->blksz;
			}
		}

	} else
		di->cookie = NULL;

	return found;
}


/*
 * returns:	ENUM_IDE, ENUM_USB etc. based on block_dev_desc_t
 */
static int dev_stor_type(block_dev_desc_t *dd)
{
	int i, j;

	for (i = ENUM_IDE; i < ENUM_MAX; i++)
		for (j = 0; j < specs[i].max_dev; j++)
			if (dd == get_dev(specs[i].name, j))
				return i;

	return ENUM_MAX;
}


/*
 * returns:	0/1 whether cookie points to some device in this group
 */
static int dev_is_stor(int type, struct device_info *di)
{
	return (dev_stor_type(di->cookie) == type) ? 1 : 0;
}


static int dev_enum_stor(int type, struct device_info *di)
{
	int found = 0, more = 0;

	debugf("called, type %d\n", type);

	/*
	 * Formulae for enumerating storage devices:
	 * 1. if cookie (hint from previous enum call) is NULL we start again
	 *    with enumeration, so return the first available device, done.
	 *
	 * 2. if cookie is not NULL, check if it identifies some device in
	 *    this group:
	 *
	 * 2a. if cookie is a storage device from our group (IDE, USB etc.),
	 *     return next available (if exists) in this group
	 *
	 * 2b. if it isn't device from our group, check if such devices were
	 *     ever enumerated before:
	 *     - if not, return the first available device from this group
	 *     - else return 0
	 */

	if (di->cookie == NULL) {

		debugf("group%d - enum restart\n", type);

		/*
		 * 1. Enumeration (re-)started: take the first available
		 * device, if exists
		 */
		found = dev_stor_get(type, 1, &more, di);
		specs[type].enum_started = 1;

	} else if (dev_is_stor(type, di)) {

		debugf("group%d - enum continued for the next device\n", type);

		if (specs[type].enum_ended) {
			debugf("group%d - nothing more to enum!\n", type);
			return 0;
		}

		/* 2a. Attempt to take a next available device in the group */
		found = dev_stor_get(type, 0, &more, di);

	} else {

		if (specs[type].enum_ended) {
			debugf("group %d - already enumerated, skipping\n", type);
			return 0;
		}

		debugf("group%d - first time enum\n", type);

		if (specs[type].enum_started == 0) {
			/*
			 * 2b.  If enumerating devices in this group did not
			 * happen before, it means the cookie pointed to a
			 * device frome some other group (another storage
			 * group, or network); in this case try to take the
			 * first available device from our group
			 */
			specs[type].enum_started = 1;

			/*
			 * Attempt to take the first device in this group:
			 *'first element' flag is set
			 */
			found = dev_stor_get(type, 1, &more, di);

		} else {
			errf("group%d - out of order iteration\n", type);
			found = 0;
			more = 0;
		}
	}

	/*
	 * If there are no more devices in this group, consider its
	 * enumeration finished
	 */
	specs[type].enum_ended = (!more) ? 1 : 0;

	if (found)
		debugf("device found, returning cookie 0x%08x\n",
			(u_int32_t)di->cookie);
	else
		debugf("no device found\n");

	return found;
}

void dev_enum_reset(void)
{
	int i;

	for (i = 0; i < ENUM_MAX; i ++) {
		specs[i].enum_started = 0;
		specs[i].enum_ended = 0;
	}
}

#ifdef CONFIG_SRX_SIEGE
int srx_siege_support_boot_sata (void);
#endif

int dev_enum_storage(struct device_info *di)
{
	int i;

	/*
	 * check: ide, usb, scsi, mmc
	 */
	for (i = ENUM_IDE; i < ENUM_MAX; i ++) {
#ifdef CONFIG_SRX_SIEGE
        /* skip scan SATA if not support boot from it */
        if (i == ENUM_SATA && !srx_siege_support_boot_sata())
            continue;
#endif

		if (dev_enum_stor(i, di))
			return 1;
	}

	return 0;
}

static int dev_stor_is_valid(int type, block_dev_desc_t *dd)
{
	int i;

	for (i = 0; i < specs[type].max_dev; i++)
		if (dd == get_dev(specs[type].name, i))
			if (dd->type != DEV_TYPE_UNKNOWN)
				return 1;

	return 0;
}


int dev_open_stor(void *cookie)
{
	int type = dev_stor_type(cookie);

	if (type == ENUM_MAX)
		return API_ENODEV;

	if (dev_stor_is_valid(type, (block_dev_desc_t *)cookie))
		return 0;

	return API_ENODEV;
}


int dev_close_stor(void *cookie)
{
	/*
	 * Not much to do as we actually do not alter storage devices upon
	 * close
	 */
	return 0;
}


static int dev_stor_index(block_dev_desc_t *dd)
{
	int i, type;

	type = dev_stor_type(dd);
	for (i = 0; i < specs[type].max_dev; i++)
		if (dd == get_dev(specs[type].name, i))
			return i;

	return (specs[type].max_dev);
}


lbasize_t dev_read_stor(void *cookie, void *buf, lbasize_t len, lbastart_t start)
{
#ifdef CONFIG_SRX_SIEGE
	lbasize_t rt;
    char *usb_bounce_buffer = (void *)JSRX_SIEGE_USB_BOUNCE_BUFFER_OFFSET;
    char *io_buf = NULL;
#endif
	int type;
	block_dev_desc_t *dd = (block_dev_desc_t *)cookie;

	if ((type = dev_stor_type(dd)) == ENUM_MAX)
		return 0;

	if (!dev_stor_is_valid(type, dd))
		return 0;

	if ((dd->block_read) == NULL) {
		debugf("no block_read() for device 0x%08x\n", cookie);
		return 0;
	}

#ifdef CONFIG_SRX_SIEGE
    if (ENUM_USB == dev_stor_type(dd)) {
        io_buf = usb_bounce_buffer;
#define USB_MAX_READ_BLK 32
        if (USB_MAX_READ_BLK < len) {
            printf("### %s read len too long, need to change this func \r\n", __func__);
        }
    } else {
        io_buf = buf;
    }
    rt = (dd->block_read(dev_stor_index(dd), start, len, io_buf));
    if (io_buf != buf && rt != 0) {
        memcpy(buf, io_buf, rt * 512);
    }
    return rt;

#else
	return (dd->block_read(dev_stor_index(dd), start, len, buf));
#endif
}
