/************************license start***************
 * Copyright (c) 2014 Cavium Inc. (support@cavium.com). All rights
 * reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *
 *     * Neither the name of Cavium Inc. nor the names of
 *       its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS
 * OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
 * RESPECT TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
 * REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
 * DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
 * OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
 * PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET
 * POSSESSION OR CORRESPONDENCE TO DESCRIPTION.  THE ENTIRE RISK ARISING OUT
 * OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 ***********************license end**************************************/


/*
  We install this program at the bootvector:
------------------------------------
	.set noreorder
	.set nomacro
	.set noat
reset_vector:
	dmtc0	$k0, $31, 0	# Save $k0 to DESAVE
	dmtc0	$k1, $31, 3	# Save $k1 to KScratch2

	mfc0	$k0, $12, 0	# Status
	mfc0	$k1, $15, 1	# Ebase

	ori	$k0, 0x84	# Enable 64-bit addressing, set ERL (should already be set)
	andi	$k1, 0x3ff	# mask out core ID

	mtc0	$k0, $12, 0	# Status
	sll	$k1, 5

	lui	$k0, 0xbfc0
	cache	17, 0($0)	# Core-14345, clear L1 Dcache virtual tags if the core hit an NMI

	ld	$k0, 0x78($k0)	# k0 <- (bfc00078) pointer to the reset vector
	synci	0($0)		# Invalidate ICache to get coherent view of target code.

	daddu	$k0, $k0, $k1
	nop

	ld	$k0, 0($k0)	# k0 <- core specific target address
	dmfc0	$k1, $31, 3	# Restore $k1 from KScratch2

	beqz	$k0, wait_loop	# Spin in wait loop
	nop

	jr	$k0
	nop

	nop			# NOPs needed here to fill delay slots
	nop			# on endian reversal of previous instructions

wait_loop:
	wait
	nop

	b	wait_loop
	nop

	nop
	nop
------------------------------------

0000000000000000 <reset_vector>:
   0:	40baf800	dmtc0	k0,c0_desave
   4:	40bbf803	dmtc0	k1,c0_kscratch2

   8:	401a6000	mfc0	k0,c0_status
   c:	401b7801	mfc0	k1,c0_ebase

  10:	375a0084	ori	k0,k0,0x84
  14:	337b03ff	andi	k1,k1,0x3ff

  18:	409a6000	mtc0	k0,c0_status
  1c:	001bd940 	sll	k1,k1,0x5

  20:	3c1abfc0	lui	k0,0xbfc0
  24:	bc110000	cache	0x11,0(zero)

  28:	df5a0078	ld	k0,120(k0)
  2c:	041f0000 	synci	0(zero)

  30:	035bd02d	daddu	k0,k0,k1
  34:	00000000	nop

  38:	df5a0000	ld	k0,0(k0)
  3c:	403bf803	dmfc0	k1,c0_kscratch2

  40:	13400005	beqz	k0,58 <wait_loop>
  44:	00000000	nop

  48:	03400008	jr	k0
  4c:	00000000	nop

  50:	00000000	nop
  54:	00000000	nop

0000000000000058 <wait_loop>:
  58:	42000020	wait
  5c:	00000000	nop

  60:	1000fffd	b	58 <wait_loop>
  64:	00000000	nop

  68:	00000000	nop
  6c:	00000000	nop

 */

#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
#include <asm/octeon/cvmx-boot-vector.h>
#include <asm/octeon/cvmx-bootmem.h>
#else

#include <asm/addrspace.h>
#include <asm/arch/cvmx.h>
#include <asm/arch/cvmx-core.h>
#include <asm/arch/cvmx-bootloader.h>
#include <asm/arch/octeon_boot.h>
#include <asm/arch/octeon-boot-info.h>
#include <asm/arch/lib_octeon_shared.h>
#include <asm/arch/octeon-pci-console.h>
#include <asm/arch/cvmx-bootmem.h>
#include <asm/arch/octeon_boot.h>

#include "cvmx-boot-vector.h"
#include "cvmx-bootmem.h"
#endif

static CVMX_SHARED unsigned long long _cvmx_bootvector_data[16] = {
	0x40baf80040bbf803ull,  /* patch low order 8-bits if no KScratch*/
	0x401a6000401b7801ull,
	0x375a0084337b03ffull,
	0x409a6000001bd940ull,
	0x3c1abfc0bc110000ull,
	0xdf5a0078041f0000ull,
	0x035bd02d00000000ull,
	0xdf5a0000403bf803ull,  /* patch low order 8-bits if no KScratch*/
	0x1340000500000000ull,
	0x0340000800000000ull,
	0x0000000000000000ull,
	0x4200002000000000ull,
	0x1000fffd00000000ull,
	0x0000000000000000ull,
	OCTEON_BOOT_MOVEABLE_MAGIC1,
	0 /* To be filled in with address of vector block*/
};

/* 2^10 CPUs */
#ifndef CONFIG_SRX_SIEGE
#define VECTOR_TABLE_SIZE (1024 * sizeof(struct cvmx_boot_vector_element))
#else
/* 16 CPU */
#define VECTOR_TABLE_SIZE (1024 * sizeof(struct cvmx_boot_vector_element))
#endif

static void cvmx_boot_vector_init(void *mem)
{
	uint64_t kseg0_mem;
	int i;

	memset(mem, 0, VECTOR_TABLE_SIZE);
    /* save the boot vector base to moveable bootbus location ...*/
	kseg0_mem = cvmx_ptr_to_phys(mem) | 0x8000000000000000ull;

	for (i = 0; i < 15; i++) {
		uint64_t v = _cvmx_bootvector_data[i];
		if (OCTEON_IS_OCTEON1PLUS() && (i == 0 || i == 7))
			v &= 0xffffffff00000000ull; /* KScratch not availble. */
		cvmx_write_csr(CVMX_MIO_BOOT_LOC_ADR, i * 8);
		cvmx_write_csr(CVMX_MIO_BOOT_LOC_DAT, v);
	}
	cvmx_write_csr(CVMX_MIO_BOOT_LOC_ADR, 15 * 8);
	cvmx_write_csr(CVMX_MIO_BOOT_LOC_DAT, kseg0_mem);
	cvmx_write_csr(CVMX_MIO_BOOT_LOC_CFGX(0), 0x81fc0000);
}

/**
 * Get a pointer to the per-core table of reset vector pointers
 *
 */
struct cvmx_boot_vector_element *cvmx_boot_vector_get(void)
{
	struct cvmx_boot_vector_element* ret;

#ifndef CONFIG_SRX_SIEGE
	ret = cvmx_bootmem_alloc_named_range_once(VECTOR_TABLE_SIZE, 0, (1ull << 32) - 1, 8,
						  "__boot_vector1__", cvmx_boot_vector_init);
#else
    static int boot_vector_inited = 0;

    /* we still use the reserved boot vector at low memory. 48 cpu for us is enough */
    ret = (struct cvmx_boot_vector_element*) BOOT_VECTOR_BASE;
    if (!boot_vector_inited) {
        cvmx_boot_vector_init(ret);
        boot_vector_inited = 1;
    }
#endif
	return ret;
}
EXPORT_SYMBOL(cvmx_boot_vector_get);
