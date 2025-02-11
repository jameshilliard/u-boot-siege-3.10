/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <common.h>
#include <part.h>
#include <ext4fs.h>
#include <fat.h>
#include <fs.h>
#include <sandboxfs.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

static block_dev_desc_t *fs_dev_desc;
static disk_partition_t fs_partition;
static int fs_type = FS_TYPE_ANY;

static inline int fs_probe_unsupported(block_dev_desc_t *fs_dev_desc,
				      disk_partition_t *fs_partition)
{
	printf("** Unrecognized filesystem type **\n");
	return -1;
}

static inline int fs_ls_unsupported(const char *dirname)
{
	return -1;
}

static inline int fs_exists_unsupported(const char *filename)
{
	return 0;
}

static inline int fs_read_unsupported(const char *filename, void *buf,
				      int offset, int len)
{
	return -1;
}

static inline int fs_write_unsupported(const char *filename, void *buf,
				      int offset, int len)
{
	return -1;
}

static inline void fs_close_unsupported(void)
{
}

struct fstype_info {
	int fstype;
	/*
	 * Is it legal to pass NULL as .probe()'s fs_dev_desc parameter?  This
	 * should be false in most cases.  For "virtual" filesystems which
	 * aren't based on a U-Boot block device (i.e. sandbox), this can be
	 * set to true.  This should also be true for the dummy entry at the
	 * end of fstypes[], since that is essentially a "virtual"
	 * (non-existent) filesystem.
	 */
	bool null_dev_desc_ok;
	int (*probe)(block_dev_desc_t *fs_dev_desc,
		     disk_partition_t *fs_partition);
	int (*ls)(const char *dirname);
	int (*exists)(const char *filename);
	int (*read)(const char *filename, void *buf, int offset, int len);
	int (*write)(const char *filename, void *buf, int offset, int len);
	void (*close)(void);
};

static struct fstype_info fstypes[] = {
#ifdef CONFIG_FS_FAT
	{
		.fstype = FS_TYPE_FAT,
		.null_dev_desc_ok = false,
		.probe = fat_set_blk_dev,
		.close = fat_close,
		.ls = file_fat_ls,
		.exists = fat_exists,
		.read = fat_read_file,
		.write = fs_write_unsupported,
	},
#endif
#ifdef CONFIG_FS_EXT4
	{
		.fstype = FS_TYPE_EXT,
		.null_dev_desc_ok = false,
		.probe = ext4fs_probe,
		.close = ext4fs_close,
		.ls = ext4fs_ls,
		.exists = ext4fs_exists,
		.read = ext4_read_file_compat,
#ifdef CONFIG_CMD_EXT4_WRITE
		.write = ext4_write_file_compat,
#else
		.write = fs_write_unsupported,
#endif
	},
#endif
#ifdef CONFIG_SANDBOX
	{
		.fstype = FS_TYPE_SANDBOX,
		.null_dev_desc_ok = true,
		.probe = sandbox_fs_set_blk_dev,
		.close = sandbox_fs_close,
		.ls = sandbox_fs_ls,
		.exists = sandbox_fs_exists,
		.read = fs_read_sandbox,
		.write = fs_write_sandbox,
	},
#endif
	{
		.fstype = FS_TYPE_ANY,
		.null_dev_desc_ok = true,
		.probe = fs_probe_unsupported,
		.close = fs_close_unsupported,
		.ls = fs_ls_unsupported,
		.exists = fs_exists_unsupported,
		.read = fs_read_unsupported,
		.write = fs_write_unsupported,
	},
};

static struct fstype_info *fs_get_info(int fstype)
{
	struct fstype_info *info;
	int i;

	for (i = 0, info = fstypes; i < ARRAY_SIZE(fstypes) - 1; i++, info++) {
		if (fstype == info->fstype)
			return info;
	}

	/* Return the 'unsupported' sentinel */
	return info;
}

int fs_set_blk_dev(const char *ifname, const char *dev_part_str, int fstype)
{
	struct fstype_info *info;
	int part, i;
#ifdef CONFIG_NEEDS_MANUAL_RELOC
	static int relocated;

	if (!relocated) {
		for (i = 0, info = fstypes; i < ARRAY_SIZE(fstypes);
				i++, info++) {
			info->probe += gd->reloc_off;
			info->close += gd->reloc_off;
			info->ls += gd->reloc_off;
			info->read += gd->reloc_off;
			info->write += gd->reloc_off;
		}
		relocated = 1;
	}
#endif

	part = get_device_and_partition(ifname, dev_part_str, &fs_dev_desc,
					&fs_partition, 1);
	if (part < 0)
		return -1;

	for (i = 0, info = fstypes; i < ARRAY_SIZE(fstypes); i++, info++) {
		if (fstype != FS_TYPE_ANY && info->fstype != FS_TYPE_ANY &&
				fstype != info->fstype)
			continue;

		if (!fs_dev_desc && !info->null_dev_desc_ok)
			continue;

		if (!info->probe(fs_dev_desc, &fs_partition)) {
			fs_type = info->fstype;
			return 0;
		}
	}

	return -1;
}

static void fs_close(void)
{
	struct fstype_info *info = fs_get_info(fs_type);

	info->close();

	fs_type = FS_TYPE_ANY;
}

int fs_ls(const char *dirname)
{
	int ret;

	struct fstype_info *info = fs_get_info(fs_type);

	ret = info->ls(dirname);

	fs_type = FS_TYPE_ANY;
	fs_close();

	return ret;
}

int fs_exists(const char *filename)
{
	int ret;

	struct fstype_info *info = fs_get_info(fs_type);

	ret = info->exists(filename);

	fs_close();

	return ret;
}

int fs_read(const char *filename, ulong addr, int offset, int len)
{
	struct fstype_info *info = fs_get_info(fs_type);
	void *buf;
	int ret;

	/*
	 * We don't actually know how many bytes are being read, since len==0
	 * means read the whole file.
	 */
	buf = map_sysmem(addr, len);
	ret = info->read(filename, buf, offset, len);
	unmap_sysmem(buf);

	/* If we requested a specific number of bytes, check we got it */
	if (ret >= 0 && len && ret != len) {
		printf("** Unable to read file %s **\n", filename);
		ret = -1;
	}
	fs_close();

	return ret;
}

int file_exists(const char *dev_type, const char *dev_part, const char *file,
		int fstype)
{
	if (fs_set_blk_dev(dev_type, dev_part, fstype))
		return 0;

	return fs_exists(file);
}

int fs_write(const char *filename, ulong addr, int offset, int len)
{
	struct fstype_info *info = fs_get_info(fs_type);
	void *buf;
	int ret;

	buf = map_sysmem(addr, len);
	ret = info->write(filename, buf, offset, len);
	unmap_sysmem(buf);

	if (ret >= 0 && ret != len) {
		printf("** Unable to write file %s **\n", filename);
		ret = -1;
	}
	fs_close();

	return ret;
}

int do_load(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[],
		int fstype, int cmdline_base)
{
	unsigned long addr;
	const char *addr_str;
	const char *filename;
	unsigned long bytes;
	unsigned long pos;
	int len_read;
	unsigned long time;

	if (argc < 2)
		return CMD_RET_USAGE;
	if (argc > 7)
		return CMD_RET_USAGE;

	if (fs_set_blk_dev(argv[1], (argc >= 3) ? argv[2] : NULL, fstype))
		return 1;

#ifdef CONFIG_OCTEON
	if (argc >= 4)
		addr = simple_strtoul(argv[3], NULL, cmdline_base);
	else
		addr = 0;
	if (addr == 0) {
#else
	if (argc >= 4) {
		addr = simple_strtoul(argv[3], NULL, cmdline_base);
	} else {
#endif
		addr_str = getenv("loadaddr");
		if (addr_str != NULL)
			addr = simple_strtoul(addr_str, NULL, 16);
		else
			addr = CONFIG_SYS_LOAD_ADDR;
	}
	if (argc >= 5) {
		filename = argv[4];
	} else {
		filename = getenv("bootfile");
		if (!filename) {
			puts("** No boot file defined **\n");
			return 1;
		}
	}
	if (argc >= 6)
		bytes = simple_strtoul(argv[5], NULL, cmdline_base);
	else
		bytes = 0;
	if (argc >= 7)
		pos = simple_strtoul(argv[6], NULL, cmdline_base);
	else
		pos = 0;

	time = get_timer(0);
	len_read = fs_read(filename, addr, pos, bytes);
	time = get_timer(time);
	if (len_read <= 0)
		return 1;

	printf("%d bytes read in %lu ms", len_read, time);
	if (time > 0) {
		puts(" (");
		print_size(len_read / time * 1000, "/s");
		puts(")");
	}
	puts("\n");

	setenv_hex("filesize", len_read);
	setenv_hex("fileaddr", addr);

	return 0;
}

int do_ls(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[],
	int fstype)
{
	if (argc < 2)
		return CMD_RET_USAGE;
	if (argc > 4)
		return CMD_RET_USAGE;

	if (fs_set_blk_dev(argv[1], (argc >= 3) ? argv[2] : NULL, fstype))
		return 1;

	if (fs_ls(argc >= 4 ? argv[3] : "/"))
		return 1;

	return 0;
}

int do_save(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[],
		int fstype, int cmdline_base)
{
	unsigned long addr;
	const char *filename;
	unsigned long bytes;
	unsigned long pos;
	int len;
	unsigned long time;

	if (argc < 6 || argc > 7)
		return CMD_RET_USAGE;

	if (fs_set_blk_dev(argv[1], argv[2], fstype))
		return 1;

	filename = argv[4];
	addr = simple_strtoul(argv[3], NULL, cmdline_base);
#ifdef CONFIG_OCTEON
	if (addr == 0)
		addr = getenv_hex("loadaddr", CONFIG_SYS_LOAD_ADDR);
#endif
	bytes = simple_strtoul(argv[5], NULL, cmdline_base);
	if (argc >= 7)
		pos = simple_strtoul(argv[6], NULL, cmdline_base);
	else
		pos = 0;

	printf("%s: Calling fswrite(%s, 0x%lx, 0x%lx, 0x%lx)\n:", __func__,
	       filename, addr, pos, bytes);
	time = get_timer(0);
	len = fs_write(filename, addr, pos, bytes);
	time = get_timer(time);
	printf("  fs_write returned %d\n", len);
	if (len <= 0)
		return 1;

	printf("%d bytes written in %lu ms", len, time);
	if (time > 0) {
		puts(" (");
		print_size(len / time * 1000, "/s");
		puts(")");
	}
	puts("\n");

	return 0;
}
