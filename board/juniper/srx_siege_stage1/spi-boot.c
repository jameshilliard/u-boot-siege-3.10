/*
 * Copyright 2013-2014 Cavium, Inc. <support@cavium.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/* Juniper srx-siege, for easy review */
#define CONFIG_SRX_SIEGE_STAGE1

#include <spi-config.h>
#include <tinylibc.h>
#include <spi.h>
/* Juniper, remove include tiny_stdio.c */
#ifndef CONFIG_SRX_SIEGE_STAGE1
#include <cvmx-bootloader.h>

#include "tiny_stdio.c"
#endif
#include "tinylibc.c"
#include "spi.c"
#include "cvmx-l2c-defs.h"

extern int cvmx_node;
extern int cvmx_uart;
extern unsigned long timestamp;
extern uint64_t cpu_speed;
extern unsigned long __start, __end, _edata;

extern void jump_to_bootloader(uint64_t addr);
typedef void (*move_and_start_t)(uint64_t dest, uint64_t src_start,
				 uint64_t src_end);

extern void move_and_start(uint64_t dest, uint64_t src_start, uint64_t src_end);
extern char move_and_start_end;


#ifdef CONFIG_SRX_SIEGE_STAGE1
#define CONFIG_OCTEON_SPI_STAGE3_BOOT_START (0x80000 - 0x18000)
/* Juniper, u-boot header defines */
#define IH_MAGIC        0x27051956  /* Image Magic Number       */
#define IH_NMLEN        32  /* Image Name Length        */

/* Reused from common.h */
#define ROUND(a, b)     (((a) + (b) - 1) & ~((b) - 1))

/*
 * Legacy format image header,
 * all data in network byte order (aka natural aka bigendian).
 */
typedef struct image_header {
    uint32_t    ih_magic;   /* Image Header Magic Number    */
    uint32_t    ih_hcrc;    /* Image Header CRC Checksum    */
    uint32_t    ih_time;    /* Image Creation Timestamp */
    uint32_t    ih_size;    /* Image Data Size      */
    uint32_t    ih_load;    /* Data  Load  Address      */
    uint32_t    ih_ep;      /* Entry Point Address      */
    uint32_t    ih_dcrc;    /* Image Data CRC Checksum  */
    uint8_t     ih_os;      /* Operating System     */
    uint8_t     ih_arch;    /* CPU architecture     */
    uint8_t     ih_type;    /* Image Type           */
    uint8_t     ih_comp;    /* Compression Type     */
    uint8_t     ih_name[IH_NMLEN];  /* Image Name       */
} image_header_t;

/* JUNOS begin */
/* 
 * The offset at which image header is put in image
 * when mkimage is called with -c flag. 
 */
#define IMG_HEADER_OFFSET       0x30

/*  
 * The offset from where the data starts. The data
 * crc is calcualted starting from this offset.
 */ 
#define IMG_DATA_OFFSET         0x100
/* JUNOS end */
    

static int
is_valid_junos_uboot_header(const image_header_t* header)
{
    uint32_t chksum;

    image_header_t tmp_hdr;

    if (header->ih_magic != IH_MAGIC) 
        return 0;

    memcpy(&tmp_hdr, header, sizeof(image_header_t));

    tmp_hdr.ih_hcrc = 0;

    /* calculate the header checksum */
    if ((chksum = crc32(0, (unsigned char *)(&tmp_hdr), 
                    sizeof(image_header_t))) != header->ih_hcrc) {
        return 0;
    }   

    return 1;
}


int find_header(int node, int cs, int start_offset, int end_offset,
		int interval, image_header_t *header,
		int flags __attribute__((unused)))
{
	int offset, hdr_offset;
	u8 spi_addr[4];
	int rc;
	int alen = 3;
	int addr_offset;

	for (offset = start_offset; offset < end_offset; offset += interval) {
        hdr_offset = offset + IMG_HEADER_OFFSET;
		spi_addr[0] = (hdr_offset >> 24) & 0xff;
		spi_addr[1] = (hdr_offset >> 16) & 0xff;
		spi_addr[2] = (hdr_offset >> 8) & 0xff;
		spi_addr[3] = hdr_offset & 0xff;
		if (hdr_offset >> 24) {
			alen = 4;
			spi_addr[0] = (hdr_offset >> 24) & 0xff;
		}

		addr_offset = sizeof(spi_addr) - alen;

		printf("Searching offset %d\r", offset);
		rc = spi_read(node, cs, &spi_addr[addr_offset], alen,
			      header, sizeof(*header));
		if (rc < 0) {
			puts("Error reading bootloader header\n");
			return -1;
		}
#ifdef DEBUG
		print_buffer(offset, header, 1, sizeof(*header), 0);
#endif
		if (is_valid_junos_uboot_header(header))
			return offset;
	}
	return -1;
}
#else
int find_header(int node, int cs, int start_offset, int end_offset,
		int interval, struct bootloader_header *header,
		int flags __attribute__((unused)))
{
	int offset;
	u8 spi_addr[4];
	int rc;
	int alen = 3;
	int addr_offset;

	for (offset = start_offset; offset < end_offset; offset += interval) {
		spi_addr[0] = (offset >> 24) & 0xff;
		spi_addr[1] = (offset >> 16) & 0xff;
		spi_addr[2] = (offset >> 8) & 0xff;
		spi_addr[3] = offset & 0xff;
		if (offset >> 24) {
			alen = 4;
			spi_addr[0] = (offset >> 24) & 0xff;
		}

		addr_offset = sizeof(spi_addr) - alen;

		printf("Searching offset %d\r", offset);
		rc = spi_read(node, cs, &spi_addr[addr_offset], alen,
			      header, sizeof(*header));
		if (rc < 0) {
			puts("Error reading bootloader header\n");
			return -1;
		}
#ifdef DEBUG
		print_buffer(offset, header, 1, sizeof(*header), 0);
#endif
		if (octeon_validate_bootloader_header(header))
			return offset;
	}
	return -1;
}
#endif

#if 0
static inline uint32_t cvmx_get_proc_id(void)
{
	uint32_t id;
	asm("mfc0 %0, $15,0":"=r"(id));
	return id;
}
#endif

int load_spi(int node, int cs, int offset, u64 addr)
{
#ifdef CONFIG_SRX_SIEGE_STAGE1
	image_header_t tmp_header,*header;
    uint32_t chksum;
    uint32_t cpu_id;
#else
	struct bootloader_header *header = (struct bootloader_header *)addr;
#endif
	u8 *buffer;
	uint start;
	uint image_size;
	int fn_size;
	move_and_start_t fn_ptr;
	int rc;
	u8 spi_addr[3];
	u8 __attribute__((unused)) id[5];
#ifdef CONFIG_SRX_SIEGE_STAGE1
    header = &tmp_header;
#endif

	spi_init();

#ifdef CONFIG_SPI_NOR
	if (spi_read_id(node, cs, id))
		puts("Error reading ID\n");
	else
		printf("SPI ID: %02x:%02x:%02x:%02x:%02x\n",
		       id[0], id[1], id[2], id[3], id[4]);
#endif

#ifndef CONFIG_SRX_SIEGE_STAGE1
	start = (uint)((char *)&_edata - (char *)&__start);
	start += CONFIG_HEADER_SEARCH_INCREMENT - 1;
	start &= ~(CONFIG_HEADER_SEARCH_INCREMENT - 1);
	offset = find_header(node, cs, start, CONFIG_HEADER_SEARCH_END,
			     CONFIG_HEADER_SEARCH_INCREMENT, header, 0);
#else
    cpu_id = cvmx_get_proc_id();
    if ((cpu_id & 0xff00) == 0x9600) { /* CN7100 and CN70xx, l2 cache size 512k */
        /* stage2 start from 8k */
        start = 0x2000;
    } else if ((cpu_id & 0xff00) == 0x9700) { /* 0x97 = CN73XX, can load stage3 directly to l2 cache  */
        start = CONFIG_OCTEON_SPI_STAGE3_BOOT_START;
    } else {
        start = 0x2000;
    }

	offset = find_header(node, cs, start, CONFIG_HEADER_SEARCH_END,
			     0x2000, header, 0);
#endif
	if (offset < 0)
		puts("header not found\n");
	else {
		printf("header found at offset 0x%x\n", offset);

#ifdef CONFIG_SRX_SIEGE_STAGE1
		printf("Image address: 0x%x, header length: %d, data length: %u\n",
		       header->ih_load,
               sizeof(*header),
		       header->ih_size);

		buffer = CASTPTR(uint8_t, addr);
		image_size = IMG_DATA_OFFSET + header->ih_size;
#else
		printf("Image %d.%d: address: 0x%lx, header length: %d, data length: %d\n",
		       header->maj_rev, header->min_rev, header->address,
		       header->hlen, header->dlen);
		buffer = CASTPTR(uint8_t, STAGE2_LOAD_ADDR);
		image_size = header->hlen + header->dlen;
#endif
		l2c_lock_mem_region(STAGE2_LOAD_ADDR, image_size + 256);
		spi_addr[0] = (offset >> 16) & 0xff;
		spi_addr[1] = (offset >> 8) & 0xff;
		spi_addr[2] = offset & 0xff;
		debug("Reading %u bytes to address %p\n", image_size, buffer);
		rc = spi_read(node, cs, spi_addr, sizeof(spi_addr),
			      buffer, image_size);
		if (rc < 0) {
			puts("Error reading stage 1.5 bootloader\n");
			return -1;
		}
		printf("Validating data...\n");
#ifdef CONFIG_SRX_SIEGE_STAGE1
        if ((chksum = crc32(0, (unsigned char *)(buffer + IMG_DATA_OFFSET),
                        header->ih_size)) != header->ih_dcrc) {
            puts("Corrupted stage 1.5 bootloader\n");
            return -1;
        }
#else
		if (octeon_validate_data((struct bootloader_header *)buffer)) {
			puts("Corrupted stage 1.5 bootloader\n");
			return -1;
		}
#endif
		fn_size = (void *)(&move_and_start_end) - (void *)(&move_and_start);
		fn_ptr = (move_and_start_t)
		((uint8_t *)((STAGE2_LOAD_ADDR + image_size + 64) & ~7ull));
		memcpy(fn_ptr, &move_and_start, fn_size);
		printf("Starting stage 1.5 bootloader at 0x%llx\n", STAGE2_START_ADDR);

		CVMX_ICACHE_INVALIDATE;
		CVMX_ICACHE_INVALIDATE2;
		fn_ptr(STAGE2_START_ADDR, STAGE2_LOAD_ADDR, image_size);
	}

	return 0;
}

int main(void)
{
	cvmx_l2c_wpar_ppx_t l2c_wpar_ppx;

	/* Turn way partitioning back on */
	l2c_wpar_ppx.u64 = 0;
	l2c_wpar_ppx.s.mask = 0;
	cvmx_write_csr(CVMX_L2C_WPAR_PPX(0), l2c_wpar_ppx.u64);

	cvmx_node = cvmx_get_node_num();

	cpu_speed = octeon_get_cpu_speed();

	octeon_set_uart(UART_NODE, UART_PORT);

    octeon_set_baudrate(CONFIG_BAUDRATE, 0);

    puts("\r\n\r\n");
	puts("SPI stage 1 bootloader (Build time: ");
    puts(__DATE__);
    puts(" - ");
    puts(__TIME__);
    puts(")\r\n");

	load_spi(0, 0, 0x2000, STAGE2_LOAD_ADDR);

	puts("Stage 1.5 bootloader did not start\n");
	octeon_do_reset();
	return 0;
}
