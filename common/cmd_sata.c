/*
 * Copyright (C) 2000-2005, DENX Software Engineering
 *		Wolfgang Denk <wd@denx.de>
 * Copyright (C) Procsys. All rights reserved.
 *		Mushtaq Khan <mushtaq_k@procsys.com>
 *			<mushtaqk_921@yahoo.co.in>
 * Copyright (C) 2008 Freescale Semiconductor, Inc.
 *		Dave Liu <daveliu@freescale.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <part.h>
#include <sata.h>

static int sata_curr_device = -1;
block_dev_desc_t sata_dev_desc[CONFIG_SYS_SATA_MAX_DEVICE];

int scan_sata_devices(void) __attribute__((weak, alias("__scan_sata_devices")));

int __scan_sata_devices(void)
{
	int i, rc;
	for (i = 0; i < CONFIG_SYS_SATA_MAX_DEVICE; i++) {
		if (sata_dev_desc[i].type == DEV_TYPE_HARDDISK) {
			rc = scan_sata(i);
			if (!rc && (sata_dev_desc[i].lba > 0) &&
			    (sata_dev_desc[i].blksz > 0))
				init_part(&sata_dev_desc[i]);
		}
	}
	return 0;
}


int __sata_initialize(void)
{
	int rc;
	int i;
	bool scan_device[CONFIG_SYS_SATA_MAX_DEVICE];
	bool found = false;

	memset(scan_device, 0, sizeof(scan_device));
	for (i = 0; i < CONFIG_SYS_SATA_MAX_DEVICE; i++) {
		memset(&sata_dev_desc[i], 0, sizeof(struct block_dev_desc));
		sata_dev_desc[i].if_type = IF_TYPE_SATA;
		sata_dev_desc[i].dev = i;
		sata_dev_desc[i].part_type = PART_TYPE_UNKNOWN;
		sata_dev_desc[i].type = DEV_TYPE_HARDDISK;
		sata_dev_desc[i].lba = 0;
		sata_dev_desc[i].blksz = 512;
		sata_dev_desc[i].log2blksz = LOG2(sata_dev_desc[i].blksz);
		sata_dev_desc[i].block_read = (int)sata_read;
		sata_dev_desc[i].block_write = (int)sata_write;

		rc = init_sata(i);
		if (!rc) {
			scan_device[i] = true;
			found = true;
		}
	}
	scan_sata_devices();

#ifdef CONFIG_BOARD_SATA_DEVICE
	sata_curr_device = CONFIG_BOARD_SATA_DEVICE;
#else
	sata_curr_device = 0;
#endif
	return !found;
}
int sata_initialize(void) __attribute__((weak,alias("__sata_initialize")));

#ifdef CONFIG_PARTITIONS
block_dev_desc_t *sata_get_dev(int dev)
{
	return (dev < CONFIG_SYS_SATA_MAX_DEVICE) ? &sata_dev_desc[dev] : NULL;
}
#endif

static int do_sata(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int rc = 0;

	if (argc == 2 && strcmp(argv[1], "init") == 0) {
		rc = sata_initialize();
		if (rc < 0) {
			puts("SATA initialization failed.\n");
			return CMD_RET_FAILURE;
		}
		return CMD_RET_SUCCESS;
	}

	/* If the user has not yet run `sata init`, do it now */
	if (sata_curr_device == -1)
		if (sata_initialize())
			return 1;

	switch (argc) {
	case 0:
	case 1:
		return CMD_RET_USAGE;
	case 2:
		if (strncmp(argv[1],"inf", 3) == 0) {
			int i;
			putc('\n');
			for (i = 0; i < CONFIG_SYS_SATA_MAX_DEVICE; ++i) {
				if (sata_dev_desc[i].type == DEV_TYPE_UNKNOWN)
					continue;
				printf ("SATA device %d: ", i);
				dev_print(&sata_dev_desc[i]);
			}
			return 0;
		} else if (strncmp(argv[1],"dev", 3) == 0) {
			if ((sata_curr_device < 0) || (sata_curr_device >= CONFIG_SYS_SATA_MAX_DEVICE)) {
				puts("\nno SATA devices available\n");
				return 1;
			}
			printf("\nSATA device %d: ", sata_curr_device);
			dev_print(&sata_dev_desc[sata_curr_device]);
			return 0;
		} else if (strncmp(argv[1],"part",4) == 0) {
			int dev, ok;

			for (ok = 0, dev = 0; dev < CONFIG_SYS_SATA_MAX_DEVICE; ++dev) {
				if (sata_dev_desc[dev].part_type != PART_TYPE_UNKNOWN) {
					++ok;
					if (dev)
						putc ('\n');
					print_part(&sata_dev_desc[dev]);
				}
			}
			if (!ok) {
				puts("\nno SATA devices available\n");
				rc ++;
			}
			return rc;
		}
		return CMD_RET_USAGE;
	case 3:
		if (strncmp(argv[1], "dev", 3) == 0) {
			int dev = (int)simple_strtoul(argv[2], NULL, 10);

			printf("\nSATA device %d: ", dev);
			if (dev >= CONFIG_SYS_SATA_MAX_DEVICE) {
				puts ("unknown device\n");
				return 1;
			}
			dev_print(&sata_dev_desc[dev]);

			if (sata_dev_desc[dev].type == DEV_TYPE_UNKNOWN)
				return 1;

			sata_curr_device = dev;

			puts("... is now current device\n");

			return 0;
		} else if (strncmp(argv[1], "part", 4) == 0) {
			int dev = (int)simple_strtoul(argv[2], NULL, 10);

			if (sata_dev_desc[dev].part_type != PART_TYPE_UNKNOWN) {
				print_part(&sata_dev_desc[dev]);
			} else {
				printf("\nSATA device %d not available\n", dev);
				rc = 1;
			}
			return rc;
		}
		return CMD_RET_USAGE;

	default: /* at least 4 args */
		if (strcmp(argv[1], "read") == 0) {
			ulong addr = simple_strtoul(argv[2], NULL, 16);
			ulong cnt = simple_strtoul(argv[4], NULL, 16);
			ulong n;
			lbaint_t blk = simple_strtoul(argv[3], NULL, 16);

			printf("\nSATA read: device %d block # %ld, count %ld ... ",
				sata_curr_device, blk, cnt);

			n = sata_read(sata_curr_device, blk, cnt, (u32 *)addr);

			/* flush cache after read */
			flush_cache(addr, cnt * sata_dev_desc[sata_curr_device].blksz);

			printf("%ld blocks read: %s\n",
				n, (n==cnt) ? "OK" : "ERROR");
			return (n == cnt) ? 0 : 1;
		} else if (strcmp(argv[1], "write") == 0) {
			ulong addr = simple_strtoul(argv[2], NULL, 16);
			ulong cnt = simple_strtoul(argv[4], NULL, 16);
			ulong n;

			lbaint_t blk = simple_strtoul(argv[3], NULL, 16);

			printf("\nSATA write: device %d block # %ld, count %ld ... ",
				sata_curr_device, blk, cnt);

			n = sata_write(sata_curr_device, blk, cnt, (u32 *)addr);

			printf("%ld blocks written: %s\n",
				n, (n == cnt) ? "OK" : "ERROR");
			return (n == cnt) ? 0 : 1;
		} else {
			return CMD_RET_USAGE;
		}

		return rc;
	}
}

U_BOOT_CMD(
	sata, 5, 1, do_sata,
	"SATA sub system",
	"init - init SATA sub system\n"
	"sata info - show available SATA devices\n"
	"sata device [dev] - show or set current device\n"
	"sata part [dev] - print partition table\n"
	"sata read addr blk# cnt\n"
	"sata write addr blk# cnt"
);
