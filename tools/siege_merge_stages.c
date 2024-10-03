/*
 * Copyright (c) 2015-2016, Juniper Networks, Inc.
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

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <arpa/inet.h>

#include "mkimage.h"
#include <image.h>
#include <version.h>

extern unsigned long crc32(unsigned long, const unsigned char *, unsigned int);
void usage(void);

#define STAGE1_SIZE 0x2000  /*8 K*/ 
/* 8K */
#define STAGE2_BEGIN 0x2000
#define STAGE3_BEGIN (0x80000 - 0x18000) /* 512k - 96k */ 
#define CFG_UBOOT_SIZE 0x200000

#if 0
#define STAGE3_BEGIN (0x100000) /* 1m */ 
#define CFG_UBOOT_SIZE 0x300000
#endif


#define uswap_32(x) \
	((((x) & 0xff000000) >> 24) | \
	 (((x) & 0x00ff0000) >>  8) | \
	 (((x) & 0x0000ff00) <<  8) | \
	 (((x) & 0x000000ff) << 24))

#define host_2_be uswap_32


int main(int argc, char *argv[])
{
    /* file handler for stage1 stage2 stage3 */
	int fd1 = -1, fd2 = -1, fd3 = -1, fd_target = -1;
    image_header_t *new_header;
    unsigned char *buf = NULL;
    int len, i, stage3_begin;
    int target_file_size;
    uint32_t crc, data_size;

    if (argc < 5) {
        printf("argc %d\n ", argc);
        for(i=0; i<argc; i++) {
            printf("argv[%d]: %s\n ", i, argv[i]);
        }
        usage();
    }

	if ((fd1 = open(argv[1], O_RDONLY)) < 0) {
		printf("Unable to open file: %s\n", argv[1]);
        goto error_exit;
	}
	if ((fd2 = open(argv[2], O_RDONLY)) < 0) {
		printf("Unable to open file: %s\n", argv[2]);
        goto error_exit;
	}
	if ((fd3 = open(argv[3], O_RDONLY)) < 0) {
		printf("Unable to open file: %s\n", argv[3]);
        goto error_exit;
	}

    /* by markli for Linux environment */
	if ((fd_target = open(argv[4], O_CREAT|O_WRONLY, 0777)) < 0) {
		printf("Unable to create file: %s\n", argv[4]);
        goto error_exit;
	}


    buf = malloc(CFG_UBOOT_SIZE + 0x80000);
    if (buf == NULL) {
		printf("Unable to allocate file buffer\n");
        goto error_exit;
    }

    /* copy stage1 */
	if ((len = read(fd1, buf, CFG_UBOOT_SIZE)) > 0) {
        printf("stage1 size %d\n", len);
        if (len >= STAGE1_SIZE) {
            printf("stage1 size too large!\n");
            goto error_exit;
        }
    }

    for (i=len; i<STAGE2_BEGIN; i++) {
        buf[i] = 0xff;
    }

	if ((len = read(fd2, &buf[STAGE2_BEGIN], CFG_UBOOT_SIZE - STAGE2_BEGIN)) > 0) {
        printf("stage2 size %d\n", len);
        if (len >= STAGE3_BEGIN) {
            printf("stage2 size too large!\n");
            goto error_exit;
        }
    }

    if (len + STAGE2_BEGIN <= STAGE3_BEGIN) {
        stage3_begin = STAGE3_BEGIN;   /* 0.5M - 32k */
    } else {
        stage3_begin = STAGE3_BEGIN + 0x10000;  /* 0.5M */
    }

    for (i=STAGE2_BEGIN + len; i<stage3_begin; i++) {
        buf[i] = 0xff;
    }

	if ((len = read(fd3, &buf[stage3_begin], CFG_UBOOT_SIZE+0x80000 - stage3_begin)) > 0) {
        printf("stage3 size %d\n", len);
        if (len >= CFG_UBOOT_SIZE - stage3_begin) {
            printf("stage3 size too large!\n");
            goto error_exit;
        }
    }

    target_file_size = stage3_begin + len;

    /* remake the file header ...*/
    new_header = (image_header_t *)(buf+IMG_HEADER_OFFSET);

    /* copy stage3 header to stage1 */
    memcpy((void *)new_header, &buf[stage3_begin+IMG_HEADER_OFFSET], sizeof(image_header_t));

    /*
     * header offset defination
     * #define CFG_UBOOT_METADATA_OFFSET       0x500
     * #define CFG_UBOOT_METADATA_SIZE         0x100
     */

    /* copy stage3 versio0n descriptor to stage1 */
    memcpy((void *)(buf+0x500), &buf[stage3_begin+0x500], 0x100);

    data_size = target_file_size - IMG_DATA_OFFSET;
    new_header->ih_size = host_2_be(data_size);
    crc = crc32(0, (unsigned char *)(buf+ IMG_DATA_OFFSET), data_size);
    new_header->ih_dcrc = host_2_be(crc);

    new_header->ih_hcrc = 0;
    crc = crc32(0, (unsigned char *)(buf+ IMG_HEADER_OFFSET), sizeof(image_header_t));
    new_header->ih_hcrc = host_2_be(crc);

	write(fd_target, buf, target_file_size);
    printf("target file merge finish !!!\n");

error_exit:
    if (buf)
        free(buf);

    if (fd1 >= 0)
        close(fd1);

    if (fd2 >= 0)
        close(fd2);

    if (fd3 >= 0)
        close(fd3);

    if (fd_target >= 0)
        close(fd_target);

	return 0;
}

void usage(void)
{
	printf("Usage: siege_merge_stages <stage1> <stage2> <stage3> \n");
}


