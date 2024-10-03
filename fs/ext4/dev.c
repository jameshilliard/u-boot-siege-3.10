// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2011 - 2012 Samsung Electronics
 * EXT4 filesystem implementation in Uboot by
 * Uma Shankar <uma.shankar@samsung.com>
 * Manjunatha C Achar <a.manjunatha@samsung.com>
 *
 * made from existing ext2/dev.c file of Uboot
 * (C) Copyright 2004
 * esd gmbh <www.esd-electronics.com>
 * Reinhard Arlt <reinhard.arlt@esd-electronics.com>
 *
 * based on code of fs/reiserfs/dev.c by
 *
 * (C) Copyright 2003 - 2004
 * Sysgo AG, <www.elinos.com>, Pavel Bartusek <pba@sysgo.com>
 */

/*
 * Changelog:
 *	0.1 - Newly created file for ext4fs support. Taken from
 *		fs/ext2/dev.c file in uboot.
 */

#include <common.h>
#include <part.h>
#include <config.h>
#include <ext4fs.h>
#include <ext_common.h>
#include "ext4_common.h"

lbaint_t part_offset;

static struct block_dev_desc *ext4fs_block_dev_desc;
static disk_partition_t *part_info;

void ext4fs_set_blk_dev(struct block_dev_desc *rbdd, disk_partition_t *info)
{
	assert(rbdd->blksz == (1 << rbdd->log2blksz));
	ext4fs_block_dev_desc = rbdd;
	get_fs()->dev_desc = rbdd;
	part_info = info;
	part_offset = info->start;
	get_fs()->total_sect = ((uint64_t)info->size * info->blksz) >>
		get_fs()->dev_desc->log2blksz;
}

/* fs_devread was imported from 2018_05 U-Boot fs_internal.c. */
int fs_devread(struct block_dev_desc *blk, disk_partition_t *partition,
	       lbaint_t sector, int byte_offset, int byte_len, char *buf)
{
	unsigned block_len;
	int log2blksz;
	char sec_buf[blk ? blk->blksz : 0];
	if (blk == NULL) {
		printf("** Invalid Block Device Descriptor (NULL)\n");
		return 0;
	}
		log2blksz = blk->log2blksz;

	/* Check partition boundaries */
	if ((sector + ((byte_offset + byte_len - 1) >> log2blksz))
	    >= partition->size) {
		printf("%s read outside partition " LBAFU "\n", __func__,
		       sector);
		return 0;
	}

	/* Get the read to the beginning of a partition */
	sector += byte_offset >> log2blksz;
	byte_offset &= blk->blksz - 1;

	debug(" <" LBAFU ", %d, %d>\n", sector, byte_offset, byte_len);

	if (byte_offset != 0) {
		int readlen;
		/* read first part which isn't aligned with start of sector */
		if (blk_dread(blk, partition->start + sector, 1,
			      (void *)sec_buf) != 1) {
			printf(" ** %s read error **\n", __func__);
			return 0;
		}
		readlen = min((int)blk->blksz - byte_offset,
			      byte_len);
		memcpy(buf, sec_buf + byte_offset, readlen);
		buf += readlen;
		byte_len -= readlen;
		sector++;
	}

	if (byte_len == 0)
		return 1;

	/* read sector aligned part */
	block_len = byte_len & ~(blk->blksz - 1);

	if (block_len == 0) {
		uint8_t p[blk->blksz];

		block_len = blk->blksz;
		blk_dread(blk, partition->start + sector, 1,
			  (void *)p);
		memcpy(buf, p, byte_len);
		return 1;
	}

	if (blk_dread(blk, partition->start + sector,
		      block_len >> log2blksz, (void *)buf) !=
					       block_len >> log2blksz) {
		printf(" ** %s read error - block\n", __func__);
		return 0;
	}
	block_len = byte_len & ~(blk->blksz - 1);
	buf += block_len;
	byte_len -= block_len;
	sector += block_len / blk->blksz;

	if (byte_len != 0) {
		/* read rest of data which are not in whole sector */
		if (blk_dread(blk, partition->start + sector, 1,
			      (void *)sec_buf) != 1) {
			printf("* %s read error - last part\n", __func__);
			return 0;
		}
		memcpy(buf, sec_buf, byte_len);
	}
	return 1;
}

int ext4fs_devread(lbaint_t sector, int byte_offset, int byte_len,
		   char *buffer)
{
	return fs_devread(get_fs()->dev_desc, part_info, sector, byte_offset,
			  byte_len, buffer);
}

int ext4_read_superblock(char *buffer)
{
	struct ext_filesystem *fs = get_fs();
	int sect = SUPERBLOCK_START >> fs->dev_desc->log2blksz;
	int off = SUPERBLOCK_START % fs->dev_desc->blksz;

	return ext4fs_devread(sect, off, SUPERBLOCK_SIZE,
				buffer);
}
