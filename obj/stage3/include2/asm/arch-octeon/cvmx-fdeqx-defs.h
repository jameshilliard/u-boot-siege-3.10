/***********************license start***************
 * Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
 * reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.

 *   * Neither the name of Cavium Inc. nor the names of
 *     its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.

 * This Software, including technical data, may be subject to U.S. export  control
 * laws, including the U.S. Export Administration Act and its  associated
 * regulations, and may be subject to export or import  regulations in other
 * countries.

 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
 * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 * THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY REPRESENTATION OR
 * DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT DEFECTS, AND CAVIUM
 * SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES OF TITLE,
 * MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF
 * VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK ARISING OUT OF USE OR
 * PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 ***********************license end**************************************/


/**
 * cvmx-fdeqx-defs.h
 *
 * Configuration and status register (CSR) type definitions for
 * Octeon fdeqx.
 *
 * This file is auto generated. Do not edit.
 *
 * <hr>$Revision$<hr>
 *
 */
#ifndef __CVMX_FDEQX_DEFS_H__
#define __CVMX_FDEQX_DEFS_H__

#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_BIST_STATUS0(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_BIST_STATUS0(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3300060ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_BIST_STATUS0(offset) (CVMX_ADD_IO_SEG(0x00011800B3300060ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_CONFIG(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_CONFIG(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3300020ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_CONFIG(offset) (CVMX_ADD_IO_SEG(0x00011800B3300020ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_CONTROL(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_CONTROL(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3300000ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_CONTROL(offset) (CVMX_ADD_IO_SEG(0x00011800B3300000ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_ECC_CONTROL0(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_ECC_CONTROL0(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3300050ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_ECC_CONTROL0(offset) (CVMX_ADD_IO_SEG(0x00011800B3300050ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_ECC_STATUS0(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_ECC_STATUS0(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3300058ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_ECC_STATUS0(offset) (CVMX_ADD_IO_SEG(0x00011800B3300058ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_ECO(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_ECO(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3300008ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_ECO(offset) (CVMX_ADD_IO_SEG(0x00011800B3300008ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_ERROR_ENABLE0(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_ERROR_ENABLE0(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3300040ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_ERROR_ENABLE0(offset) (CVMX_ADD_IO_SEG(0x00011800B3300040ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_ERROR_ENABLE1(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_ERROR_ENABLE1(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3300048ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_ERROR_ENABLE1(offset) (CVMX_ADD_IO_SEG(0x00011800B3300048ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_ERROR_SOURCE0(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_ERROR_SOURCE0(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3300030ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_ERROR_SOURCE0(offset) (CVMX_ADD_IO_SEG(0x00011800B3300030ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_ERROR_SOURCE1(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_ERROR_SOURCE1(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3300038ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_ERROR_SOURCE1(offset) (CVMX_ADD_IO_SEG(0x00011800B3300038ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_JD0_CFG0(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_JD0_CFG0(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3302088ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_JD0_CFG0(offset) (CVMX_ADD_IO_SEG(0x00011800B3302088ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_JD0_CFG1(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_JD0_CFG1(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3302090ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_JD0_CFG1(offset) (CVMX_ADD_IO_SEG(0x00011800B3302090ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_JD0_CFG2(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_JD0_CFG2(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3302098ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_JD0_CFG2(offset) (CVMX_ADD_IO_SEG(0x00011800B3302098ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_JD0_CFG3(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_JD0_CFG3(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B33020A0ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_JD0_CFG3(offset) (CVMX_ADD_IO_SEG(0x00011800B33020A0ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_JD0_CFG4(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_JD0_CFG4(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B33020A8ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_JD0_CFG4(offset) (CVMX_ADD_IO_SEG(0x00011800B33020A8ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_JD0_CFG5(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_JD0_CFG5(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B33020B0ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_JD0_CFG5(offset) (CVMX_ADD_IO_SEG(0x00011800B33020B0ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_JD0_MMSE_CFGX(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && (((offset <= 16)) && ((block_id <= 1))))))
		cvmx_warn("CVMX_FDEQX_JD0_MMSE_CFGX(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x00011800B3302000ull) + (((offset) & 31) + ((block_id) & 1) * 0x40000ull) * 8;
}
#else
#define CVMX_FDEQX_JD0_MMSE_CFGX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800B3302000ull) + (((offset) & 31) + ((block_id) & 1) * 0x40000ull) * 8)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_JD1_CFG0(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_JD1_CFG0(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3304088ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_JD1_CFG0(offset) (CVMX_ADD_IO_SEG(0x00011800B3304088ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_JD1_CFG1(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_JD1_CFG1(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3304090ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_JD1_CFG1(offset) (CVMX_ADD_IO_SEG(0x00011800B3304090ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_JD1_CFG2(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_JD1_CFG2(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3304098ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_JD1_CFG2(offset) (CVMX_ADD_IO_SEG(0x00011800B3304098ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_JD1_CFG3(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_JD1_CFG3(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B33040A0ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_JD1_CFG3(offset) (CVMX_ADD_IO_SEG(0x00011800B33040A0ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_JD1_CFG4(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_JD1_CFG4(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B33040A8ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_JD1_CFG4(offset) (CVMX_ADD_IO_SEG(0x00011800B33040A8ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_JD1_CFG5(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_JD1_CFG5(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B33040B0ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_JD1_CFG5(offset) (CVMX_ADD_IO_SEG(0x00011800B33040B0ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_JD1_MMSE_CFGX(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && (((offset <= 16)) && ((block_id <= 1))))))
		cvmx_warn("CVMX_FDEQX_JD1_MMSE_CFGX(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x00011800B3304000ull) + (((offset) & 31) + ((block_id) & 1) * 0x40000ull) * 8;
}
#else
#define CVMX_FDEQX_JD1_MMSE_CFGX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800B3304000ull) + (((offset) & 31) + ((block_id) & 1) * 0x40000ull) * 8)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_PIPELINE_DISABLE(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_PIPELINE_DISABLE(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3301000ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_PIPELINE_DISABLE(offset) (CVMX_ADD_IO_SEG(0x00011800B3301000ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_STATUS(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_STATUS(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3300018ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_STATUS(offset) (CVMX_ADD_IO_SEG(0x00011800B3300018ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_TEST(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_TEST(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3300010ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_TEST(offset) (CVMX_ADD_IO_SEG(0x00011800B3300010ull) + ((offset) & 1) * 0x200000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_FDEQX_TEST2(unsigned long offset)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CNF75XX) && ((offset <= 1)))))
		cvmx_warn("CVMX_FDEQX_TEST2(%lu) is invalid on this chip\n", offset);
	return CVMX_ADD_IO_SEG(0x00011800B3300028ull) + ((offset) & 1) * 0x200000ull;
}
#else
#define CVMX_FDEQX_TEST2(offset) (CVMX_ADD_IO_SEG(0x00011800B3300028ull) + ((offset) & 1) * 0x200000ull)
#endif

/**
 * cvmx_fdeq#_bist_status0
 *
 * This register indicates BIST status. Place holder for now.
 *
 */
union cvmx_fdeqx_bist_status0 {
	uint64_t u64;
	struct cvmx_fdeqx_bist_status0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_5_63                : 59;
	uint64_t wrdma_bist_status            : 1;  /**< WRDMA memory BIST status. */
	uint64_t dft_oif_bist_status          : 1;  /**< DFT IN memory BIST status. */
	uint64_t dft_ping_bist_status         : 1;  /**< DFT IN memory BIST status. */
	uint64_t dft_pong_bist_status         : 1;  /**< DFT OUT memory BIST status. */
	uint64_t buf_bist_status              : 1;  /**< BUF memory BIST status. */
#else
	uint64_t buf_bist_status              : 1;
	uint64_t dft_pong_bist_status         : 1;
	uint64_t dft_ping_bist_status         : 1;
	uint64_t dft_oif_bist_status          : 1;
	uint64_t wrdma_bist_status            : 1;
	uint64_t reserved_5_63                : 59;
#endif
	} s;
	struct cvmx_fdeqx_bist_status0_s      cnf75xx;
};
typedef union cvmx_fdeqx_bist_status0 cvmx_fdeqx_bist_status0_t;

/**
 * cvmx_fdeq#_config
 */
union cvmx_fdeqx_config {
	uint64_t u64;
	struct cvmx_fdeqx_config_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_1_63                : 63;
	uint64_t mmse_bypass                  : 1;  /**< When MMSE_BYPASS=0, the read DMA data is provided to the MMSE engine.
                                                         When the MMSE_BYPASS=1, the read DMA data bypassed the MMSE and is
                                                         passed to the FDEQm block. */
#else
	uint64_t mmse_bypass                  : 1;
	uint64_t reserved_1_63                : 63;
#endif
	} s;
	struct cvmx_fdeqx_config_s            cnf75xx;
};
typedef union cvmx_fdeqx_config cvmx_fdeqx_config_t;

/**
 * cvmx_fdeq#_control
 */
union cvmx_fdeqx_control {
	uint64_t u64;
	struct cvmx_fdeqx_control_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_48_63               : 16;
	uint64_t jobid1                       : 16; /**< Job ID for slot 1. */
	uint64_t jobid0                       : 16; /**< Job ID for slot 0. */
	uint64_t reserved_2_15                : 14;
	uint64_t start1                       : 1;  /**< Start processing job in slot 1. */
	uint64_t start0                       : 1;  /**< Start processing job in slot 0. */
#else
	uint64_t start0                       : 1;
	uint64_t start1                       : 1;
	uint64_t reserved_2_15                : 14;
	uint64_t jobid0                       : 16;
	uint64_t jobid1                       : 16;
	uint64_t reserved_48_63               : 16;
#endif
	} s;
	struct cvmx_fdeqx_control_s           cnf75xx;
};
typedef union cvmx_fdeqx_control cvmx_fdeqx_control_t;

/**
 * cvmx_fdeq#_ecc_control0
 *
 * This register controls ECC parameters.
 *
 */
union cvmx_fdeqx_ecc_control0 {
	uint64_t u64;
	struct cvmx_fdeqx_ecc_control0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_15_63               : 49;
	uint64_t wrdma_flip_syn               : 2;  /**< WRDMA memory syndrome flip bits. */
	uint64_t wrdma_cor_dis                : 1;  /**< WRDMA memory ECC disable. */
	uint64_t dft_oif_flip_syn             : 2;  /**< DFT OIF memory syndrome flip bits. */
	uint64_t dft_oif_cor_dis              : 1;  /**< DFT OIF memory ECC disable. */
	uint64_t dft_ping_flip_syn            : 2;  /**< DFT PING memory syndrome flip bits. */
	uint64_t dft_ping_cor_dis             : 1;  /**< DFT PING memory ECC disable. */
	uint64_t dft_pong_flip_syn            : 2;  /**< DFT OUT memory syndrome flip bits. */
	uint64_t dft_pong_cor_dis             : 1;  /**< DFT OUT memory ECC disable. */
	uint64_t buf_flip_syn                 : 2;  /**< FDEQ BUF memory syndrome flip bits. */
	uint64_t buf_cor_dis                  : 1;  /**< FDEQ BUF memory ECC disable. */
#else
	uint64_t buf_cor_dis                  : 1;
	uint64_t buf_flip_syn                 : 2;
	uint64_t dft_pong_cor_dis             : 1;
	uint64_t dft_pong_flip_syn            : 2;
	uint64_t dft_ping_cor_dis             : 1;
	uint64_t dft_ping_flip_syn            : 2;
	uint64_t dft_oif_cor_dis              : 1;
	uint64_t dft_oif_flip_syn             : 2;
	uint64_t wrdma_cor_dis                : 1;
	uint64_t wrdma_flip_syn               : 2;
	uint64_t reserved_15_63               : 49;
#endif
	} s;
	struct cvmx_fdeqx_ecc_control0_s      cnf75xx;
};
typedef union cvmx_fdeqx_ecc_control0 cvmx_fdeqx_ecc_control0_t;

/**
 * cvmx_fdeq#_ecc_status0
 *
 * This register indicates ECC status.
 *
 */
union cvmx_fdeqx_ecc_status0 {
	uint64_t u64;
	struct cvmx_fdeqx_ecc_status0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_10_63               : 54;
	uint64_t wrdma_dbe                    : 1;  /**< WRDMA memory double-bit error. */
	uint64_t wrdma_sbe                    : 1;  /**< WRDMA memory single-bit error. */
	uint64_t dft_oif_dbe                  : 1;  /**< DFT IN memory double-bit error. */
	uint64_t dft_oif_sbe                  : 1;  /**< DFT IN memory single-bit error. */
	uint64_t dft_ping_dbe                 : 1;  /**< DFT IN memory double-bit error. */
	uint64_t dft_ping_sbe                 : 1;  /**< DFT IN memory single-bit error. */
	uint64_t dft_pong_dbe                 : 1;  /**< DFT OUT memory double-bit error. */
	uint64_t dft_pong_sbe                 : 1;  /**< DFT OUT memory single-bit error. */
	uint64_t buf_dbe                      : 1;  /**< FDEQ BUF memory double-bit error. */
	uint64_t buf_sbe                      : 1;  /**< FDEQ BUF memory single-bit error. */
#else
	uint64_t buf_sbe                      : 1;
	uint64_t buf_dbe                      : 1;
	uint64_t dft_pong_sbe                 : 1;
	uint64_t dft_pong_dbe                 : 1;
	uint64_t dft_ping_sbe                 : 1;
	uint64_t dft_ping_dbe                 : 1;
	uint64_t dft_oif_sbe                  : 1;
	uint64_t dft_oif_dbe                  : 1;
	uint64_t wrdma_sbe                    : 1;
	uint64_t wrdma_dbe                    : 1;
	uint64_t reserved_10_63               : 54;
#endif
	} s;
	struct cvmx_fdeqx_ecc_status0_s       cnf75xx;
};
typedef union cvmx_fdeqx_ecc_status0 cvmx_fdeqx_ecc_status0_t;

/**
 * cvmx_fdeq#_eco
 *
 * An ECO CSR
 *
 */
union cvmx_fdeqx_eco {
	uint64_t u64;
	struct cvmx_fdeqx_eco_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t eco_rw                       : 64; /**< Reserved for ECO usage. */
#else
	uint64_t eco_rw                       : 64;
#endif
	} s;
	struct cvmx_fdeqx_eco_s               cnf75xx;
};
typedef union cvmx_fdeqx_eco cvmx_fdeqx_eco_t;

/**
 * cvmx_fdeq#_error_enable0
 *
 * This register enables reporting for error reported in
 * FDEQ()_ERROR_SOURCE0.
 */
union cvmx_fdeqx_error_enable0 {
	uint64_t u64;
	struct cvmx_fdeqx_error_enable0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t rsv1                         : 58; /**< Reserved. */
	uint64_t rp1_of_en                    : 1;  /**< Error enable for port 1 overflow. */
	uint64_t rp0_of_en                    : 1;  /**< Error enable for port 0 overflow. */
	uint64_t rsv0                         : 2;  /**< Reserved. */
	uint64_t rp1_uf_en                    : 1;  /**< Error enable for port 1 underflow. */
	uint64_t rp0_uf_en                    : 1;  /**< Error enable for port 0 underflow. */
#else
	uint64_t rp0_uf_en                    : 1;
	uint64_t rp1_uf_en                    : 1;
	uint64_t rsv0                         : 2;
	uint64_t rp0_of_en                    : 1;
	uint64_t rp1_of_en                    : 1;
	uint64_t rsv1                         : 58;
#endif
	} s;
	struct cvmx_fdeqx_error_enable0_s     cnf75xx;
};
typedef union cvmx_fdeqx_error_enable0 cvmx_fdeqx_error_enable0_t;

/**
 * cvmx_fdeq#_error_enable1
 *
 * This register enables reporting for error reported in
 * FDEQ()_ERROR_SOURCE1.
 */
union cvmx_fdeqx_error_enable1 {
	uint64_t u64;
	struct cvmx_fdeqx_error_enable1_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t rsv                          : 63; /**< Reserved. */
	uint64_t mmse_err_en                  : 1;  /**< Error enable for all errors in FDEQ()_ERROR_SOURCE1. */
#else
	uint64_t mmse_err_en                  : 1;
	uint64_t rsv                          : 63;
#endif
	} s;
	struct cvmx_fdeqx_error_enable1_s     cnf75xx;
};
typedef union cvmx_fdeqx_error_enable1 cvmx_fdeqx_error_enable1_t;

/**
 * cvmx_fdeq#_error_source0
 *
 * This register indicates the source of read overflow/underflow errors.
 *
 */
union cvmx_fdeqx_error_source0 {
	uint64_t u64;
	struct cvmx_fdeqx_error_source0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_48_63               : 16;
	uint64_t rp1_jobid_ufof               : 16; /**< Job ID of the job which reported the overflow/underflow error on read
                                                         port 1. */
	uint64_t rp0_jobid_ufof               : 16; /**< Job ID of the job which reported the overflow/underflow error on read
                                                         port 0. */
	uint64_t reserved_6_15                : 10;
	uint64_t rp1_of                       : 1;  /**< Read port 1 overflow. */
	uint64_t rp0_of                       : 1;  /**< Read port 0 overflow. */
	uint64_t reserved_2_3                 : 2;
	uint64_t rp1_uf                       : 1;  /**< Read port 1 underflow. */
	uint64_t rp0_uf                       : 1;  /**< Read port 0 underflow. */
#else
	uint64_t rp0_uf                       : 1;
	uint64_t rp1_uf                       : 1;
	uint64_t reserved_2_3                 : 2;
	uint64_t rp0_of                       : 1;
	uint64_t rp1_of                       : 1;
	uint64_t reserved_6_15                : 10;
	uint64_t rp0_jobid_ufof               : 16;
	uint64_t rp1_jobid_ufof               : 16;
	uint64_t reserved_48_63               : 16;
#endif
	} s;
	struct cvmx_fdeqx_error_source0_s     cnf75xx;
};
typedef union cvmx_fdeqx_error_source0 cvmx_fdeqx_error_source0_t;

/**
 * cvmx_fdeq#_error_source1
 *
 * This register describes the source of errors.
 *
 */
union cvmx_fdeqx_error_source1 {
	uint64_t u64;
	struct cvmx_fdeqx_error_source1_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_58_63               : 6;
	uint64_t subdemap_fifo_err            : 16; /**< Sub DEMAP FIFO error. */
	uint64_t regen_fifo_err               : 8;  /**< Regen FIFO error. */
	uint64_t fde_fifo_err                 : 2;  /**< FDE FIFO error. */
	uint64_t rp1_jobid_err                : 16; /**< Job ID for error. */
	uint64_t rp0_jobid_err                : 16; /**< Job ID for error. */
#else
	uint64_t rp0_jobid_err                : 16;
	uint64_t rp1_jobid_err                : 16;
	uint64_t fde_fifo_err                 : 2;
	uint64_t regen_fifo_err               : 8;
	uint64_t subdemap_fifo_err            : 16;
	uint64_t reserved_58_63               : 6;
#endif
	} s;
	struct cvmx_fdeqx_error_source1_s     cnf75xx;
};
typedef union cvmx_fdeqx_error_source1 cvmx_fdeqx_error_source1_t;

/**
 * cvmx_fdeq#_jd0_cfg0
 */
union cvmx_fdeqx_jd0_cfg0 {
	uint64_t u64;
	struct cvmx_fdeqx_jd0_cfg0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_47_63               : 17;
	uint64_t mmse_idft_bypass             : 1;  /**< MMSE and IDFT bypass. Set to 1 to bypass MMSE processing and IDFT and
                                                         subsequent processing. */
	uint64_t mmse_bypass                  : 1;  /**< MMSE bypass. Set to 1 to bypass MMSE processing. If [MMSE_BYPASS]=1,
                                                         then [IDFT_BYPASS] must be 0. To bypass both MMSE and IDFT processing,
                                                         see [MMSE_IDFT_BYPASS]. */
	uint64_t idft_bypass                  : 1;  /**< IDFT bypass. Set to 1 to bypass IDFT and all subsequent processing.
                                                         If set to 1, IDFT and all subsequent modules are bypassed. If
                                                         [IDFT_BYPASS]=1, then [MMSE_BYPASS] must be 0. To bypass both MMSE and
                                                         IDFT processing, see [MMSE_IDFT_BYPASS]. */
	uint64_t demapper_bypass              : 1;  /**< Demapper bypass. Set to 1 to bypass the demapper and all subsequent
                                                         processing. */
	uint64_t descrambler_bypass           : 1;  /**< Descrambler bypass. Set to 1 to bypass the descrambler and all
                                                         subsequent processing. */
	uint64_t ack_scomb_bypass             : 1;  /**< ACK soft-combining bypass. Set to 1 to bypass ACK soft-combining. */
	uint64_t ri_scomb_bypass              : 1;  /**< RI soft combining bypass. Set to 1 to bypass RI soft-combining. */
	uint64_t cqi_scomb_bypass             : 1;  /**< CQI soft combining bypass. When set to 1, indicates CQI is not RM
                                                         encoded and soft-combining will be bypassed as a result. */
	uint64_t ack_extract_bypass           : 1;  /**< ACK extraction bypass. Set to 1 to disable ACK extraction. */
	uint64_t ri_extract_bypass            : 1;  /**< RI extraction bypass. Set to 1 to disable RI extraction. */
	uint64_t report_bypass                : 1;  /**< FDEQ report bypass. Set to 1 to disable generation of the FDEQ report
                                                         output. [REPORT_BYPASS] must be set to 1 if any of the following
                                                         fields are set to 1 - [MMSE_IDFT_BYPASS], [IDFT_BYPASS],
                                                         [DEMAPPER_BYPASS], [DESCRAMBLER_BYPASS], [ACK_SCOMB_BYPASS],
                                                         [RI_SCOMB_BYPASS], or [CQI_SCOMB_BYPASS]. */
	uint64_t reserved_33_35               : 3;
	uint64_t cp_type                      : 1;  /**< Cyclic-prefix (CP) type:
                                                         0 = Normal CP.
                                                         1 = Extended CP. */
	uint64_t reserved_29_31               : 3;
	uint64_t layer_id                     : 1;  /**< Layer identifier. [LAYER_ID] must be 0 if [NUM_LAYERS]=1. */
	uint64_t reserved_26_27               : 2;
	uint64_t num_layers                   : 2;  /**< Number of layers. Must be set to either 1 or 2 layers. */
	uint64_t reserved_23_23               : 1;
	uint64_t mod_order                    : 3;  /**< Modulation order.
                                                         0x2 = QPSK.
                                                         0x4 = 16QAM.
                                                         0x6 = 64QAM. */
	uint64_t reserved_18_19               : 2;
	uint64_t slot_id                      : 2;  /**< Slot identifier:
                                                         0x0 = Slot 0.
                                                         0x1 = Slot 1.
                                                         0x2 = Subframe (i.e., slots 0 and 1). */
	uint64_t reserved_9_15                : 7;
	uint64_t srs_flag                     : 1;  /**< SRS flag is present. Set to 1 when the last symbol of the input is an
                                                         SRS symbol. */
	uint64_t reserved_6_7                 : 2;
	uint64_t ndft_indx                    : 6;  /**< Selects the DFT/IDFT size (N_DFT):
                                                         0x0 = 0xC.
                                                         0x1 = 0x18.
                                                         0x2 = 0x24.
                                                         0x3 = 0x30.
                                                         0x4 = 0x3C.
                                                         0x5 = 0x48.
                                                         0x6 = 0x60.
                                                         0x7 = 0x6C.
                                                         0x8 = 0x78.
                                                         0x9 = 0x90.
                                                         0xA = 0xB4.
                                                         0xB = 0xC0.
                                                         0xC = 0xD8.
                                                         0xD = 0xF0.
                                                         0xE = 0x120.
                                                         0xF = 0x12C.
                                                         0x10 = 0x144.
                                                         0x11 = 0x168.
                                                         0x12 = 0x180.
                                                         0x13 = 0x1B0.
                                                         0x14 = 0x1E0.
                                                         0x15 = 0x21C.
                                                         0x16 = 0x240.
                                                         0x17 = 0x258.
                                                         0x18 = 0x288.
                                                         0x19 = 0x2D0.
                                                         0x1A = 0x300.
                                                         0x1B = 0x360.
                                                         0x1C = 0x384.
                                                         0x1D = 0x3C0.
                                                         0x1E = 0x3CC.
                                                         0x1F = 0x438.
                                                         0x20 = 0x480.
                                                         0x21 = 0x4B0.
                                                         0x22 = 0x510. */
#else
	uint64_t ndft_indx                    : 6;
	uint64_t reserved_6_7                 : 2;
	uint64_t srs_flag                     : 1;
	uint64_t reserved_9_15                : 7;
	uint64_t slot_id                      : 2;
	uint64_t reserved_18_19               : 2;
	uint64_t mod_order                    : 3;
	uint64_t reserved_23_23               : 1;
	uint64_t num_layers                   : 2;
	uint64_t reserved_26_27               : 2;
	uint64_t layer_id                     : 1;
	uint64_t reserved_29_31               : 3;
	uint64_t cp_type                      : 1;
	uint64_t reserved_33_35               : 3;
	uint64_t report_bypass                : 1;
	uint64_t ri_extract_bypass            : 1;
	uint64_t ack_extract_bypass           : 1;
	uint64_t cqi_scomb_bypass             : 1;
	uint64_t ri_scomb_bypass              : 1;
	uint64_t ack_scomb_bypass             : 1;
	uint64_t descrambler_bypass           : 1;
	uint64_t demapper_bypass              : 1;
	uint64_t idft_bypass                  : 1;
	uint64_t mmse_bypass                  : 1;
	uint64_t mmse_idft_bypass             : 1;
	uint64_t reserved_47_63               : 17;
#endif
	} s;
	struct cvmx_fdeqx_jd0_cfg0_s          cnf75xx;
};
typedef union cvmx_fdeqx_jd0_cfg0 cvmx_fdeqx_jd0_cfg0_t;

/**
 * cvmx_fdeq#_jd0_cfg1
 */
union cvmx_fdeqx_jd0_cfg1 {
	uint64_t u64;
	struct cvmx_fdeqx_jd0_cfg1_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_53_63               : 11;
	uint64_t rs_bits_last                 : 5;  /**< Output scaling at the last stage of DFT/iDFT.  Setting
                                                         [RS_BITS_LAST]=15 will result in unity gain for the overall DFT.
                                                         Must be in the range 15 to 19. */
	uint64_t reserved_45_47               : 3;
	uint64_t ack_ri_dmp_treatment         : 1;  /**< Special treatment for 1-bit and 2-bit ACK/RI information symbols. When
                                                         set to 1, the demapper uses a priori information that some
                                                         constellation points are invalid when calculating LLR_0 and LLR_1 for
                                                         1-bit and 2-bit ACK/RI information symbols. */
	uint64_t q_format                     : 4;  /**< Fixed point Q format for the demapper. The format is specified as a
                                                         tuple (M4_CONST1, M4_CONST3, M6_CONST1, M6_CONST3, M6_CONST5,
                                                         M6_CONST7). The following formats are supported:
                                                         0x9 = (81, 729, 40, 356, 988, 1936).
                                                         0xA = (162, 1457, 79, 711, 1975, 3871).
                                                         0xB = (324, 2914, 158, 1422, 3950, 7742).
                                                         0xC = (648, 5829, 316, 2844, 7900, 15485).
                                                         0xD = (1295, 11657, 632, 5688, 15801, 30969).
                                                         0xE = (2591, 23315, 1264, 11376, 31601, 61939). */
	uint64_t scaled_sinr_rsft             : 4;  /**< Right shift applied after multiplying SCALE by SINR. Must be in the
                                                         range 10 to 15. */
	uint64_t reserved_34_35               : 2;
	uint64_t mod_rsft                     : 6;  /**< Modulation dependent right shift factor. Must be less than or equal to
                                                         40. */
	uint64_t llr_bit_width                : 4;  /**< LLR bit width. Must be either 6, 7, or 8. */
	uint64_t reserved_23_23               : 1;
	uint64_t llr_offset_input             : 7;  /**< LLR offset value ranging from 0 to 2^([LLR_BIT_WIDTH]-1)-1. */
	uint64_t mod_scale                    : 16; /**< Modulation dependent scale value. */
#else
	uint64_t mod_scale                    : 16;
	uint64_t llr_offset_input             : 7;
	uint64_t reserved_23_23               : 1;
	uint64_t llr_bit_width                : 4;
	uint64_t mod_rsft                     : 6;
	uint64_t reserved_34_35               : 2;
	uint64_t scaled_sinr_rsft             : 4;
	uint64_t q_format                     : 4;
	uint64_t ack_ri_dmp_treatment         : 1;
	uint64_t reserved_45_47               : 3;
	uint64_t rs_bits_last                 : 5;
	uint64_t reserved_53_63               : 11;
#endif
	} s;
	struct cvmx_fdeqx_jd0_cfg1_s          cnf75xx;
};
typedef union cvmx_fdeqx_jd0_cfg1 cvmx_fdeqx_jd0_cfg1_t;

/**
 * cvmx_fdeq#_jd0_cfg2
 */
union cvmx_fdeqx_jd0_cfg2 {
	uint64_t u64;
	struct cvmx_fdeqx_jd0_cfg2_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_63_63               : 1;
	uint64_t cinit                        : 31; /**< Initial value for the second m-sequence used to produce the scrambling
                                                         sequence. */
	uint64_t reserved_17_31               : 15;
	uint64_t seq_offset                   : 17; /**< Skip offset for the scrambling sequence. The scrambler skips the first
                                                         [SEQ_OFFSET] bits in the scrambling sequence. */
#else
	uint64_t seq_offset                   : 17;
	uint64_t reserved_17_31               : 15;
	uint64_t cinit                        : 31;
	uint64_t reserved_63_63               : 1;
#endif
	} s;
	struct cvmx_fdeqx_jd0_cfg2_s          cnf75xx;
};
typedef union cvmx_fdeqx_jd0_cfg2 cvmx_fdeqx_jd0_cfg2_t;

/**
 * cvmx_fdeq#_jd0_cfg3
 */
union cvmx_fdeqx_jd0_cfg3 {
	uint64_t u64;
	struct cvmx_fdeqx_jd0_cfg3_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_51_63               : 13;
	uint64_t ack_enc_cat                  : 3;  /**< ACK encoding category:
                                                         0x0 =  no ACK.
                                                         0x1 =  O^ACK = 1.
                                                         0x2 =  O^ACK = 1 with ACK bundling.
                                                         0x3 =  O^ACK = 2.
                                                         0x4 =  O^ACK = 2 with ACK bundling.
                                                         0x5 =  3 <= O^ACK <= 11.
                                                         0x6 =  11 < O^ACK <= 20.
                                                         0x7 =  Reserved. */
	uint64_t reserved_35_47               : 13;
	uint64_t ri_enc_cat                   : 3;  /**< RI encoding category:
                                                         0x0 =  no RI.
                                                         0x1 =  O^RI = 1.
                                                         0x2 =  O^RI = 2.
                                                         0x3 =  3 <= O^RI <= 11.
                                                         0x4 =  11 < O^RI <= 15.
                                                         0x5-0x7 =  Reserved. */
	uint64_t reserved_29_31               : 3;
	uint64_t num_ack_re                   : 13; /**< Number of ACK REs per layer. Must be in the range 0 to 5184. */
	uint64_t reserved_13_15               : 3;
	uint64_t num_ri_re                    : 13; /**< Number of RI REs per layer. Must be in the range 0 to 5184. */
#else
	uint64_t num_ri_re                    : 13;
	uint64_t reserved_13_15               : 3;
	uint64_t num_ack_re                   : 13;
	uint64_t reserved_29_31               : 3;
	uint64_t ri_enc_cat                   : 3;
	uint64_t reserved_35_47               : 13;
	uint64_t ack_enc_cat                  : 3;
	uint64_t reserved_51_63               : 13;
#endif
	} s;
	struct cvmx_fdeqx_jd0_cfg3_s          cnf75xx;
};
typedef union cvmx_fdeqx_jd0_cfg3 cvmx_fdeqx_jd0_cfg3_t;

/**
 * cvmx_fdeq#_jd0_cfg4
 */
union cvmx_fdeqx_jd0_cfg4 {
	uint64_t u64;
	struct cvmx_fdeqx_jd0_cfg4_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_62_63               : 2;
	uint64_t num_cqi_re0                  : 14; /**< Number of CQI REs per layer for hypothesis 0. Must be in the range 0
                                                         to 15552. */
	uint64_t reserved_46_47               : 2;
	uint64_t num_cqi_re1                  : 14; /**< Number of CQI REs per layer for hypothesis 1. Must be in the range 0
                                                         to 15552. */
	uint64_t reserved_30_31               : 2;
	uint64_t num_cqi_re2                  : 14; /**< Number of CQI REs per layer for hypothesis 2. Must be in the range 0
                                                         to 15552. */
	uint64_t reserved_14_15               : 2;
	uint64_t num_cqi_re3                  : 14; /**< Number of CQI REs per layer for hypothesis 3. Must be in the range 0
                                                         to 15552. */
#else
	uint64_t num_cqi_re3                  : 14;
	uint64_t reserved_14_15               : 2;
	uint64_t num_cqi_re2                  : 14;
	uint64_t reserved_30_31               : 2;
	uint64_t num_cqi_re1                  : 14;
	uint64_t reserved_46_47               : 2;
	uint64_t num_cqi_re0                  : 14;
	uint64_t reserved_62_63               : 2;
#endif
	} s;
	struct cvmx_fdeqx_jd0_cfg4_s          cnf75xx;
};
typedef union cvmx_fdeqx_jd0_cfg4 cvmx_fdeqx_jd0_cfg4_t;

/**
 * cvmx_fdeq#_jd0_cfg5
 */
union cvmx_fdeqx_jd0_cfg5 {
	uint64_t u64;
	struct cvmx_fdeqx_jd0_cfg5_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_62_63               : 2;
	uint64_t num_cqi_re4                  : 14; /**< Number of CQI REs per layer for hypothesis 4. Must be in the range 0
                                                         to 15552. */
	uint64_t reserved_46_47               : 2;
	uint64_t num_cqi_re5                  : 14; /**< Number of CQI REs per layer for hypothesis 5. Must be in the range 0
                                                         to 1552. */
	uint64_t reserved_30_31               : 2;
	uint64_t num_cqi_re6                  : 14; /**< Number of CQI REs per layer for hypothesis 6. Must be in the range 0
                                                         to 15552. */
	uint64_t reserved_14_15               : 2;
	uint64_t num_cqi_re7                  : 14; /**< Number of CQI REs per layer for hypothesis 7. Must be in the range 0
                                                         to 15552. */
#else
	uint64_t num_cqi_re7                  : 14;
	uint64_t reserved_14_15               : 2;
	uint64_t num_cqi_re6                  : 14;
	uint64_t reserved_30_31               : 2;
	uint64_t num_cqi_re5                  : 14;
	uint64_t reserved_46_47               : 2;
	uint64_t num_cqi_re4                  : 14;
	uint64_t reserved_62_63               : 2;
#endif
	} s;
	struct cvmx_fdeqx_jd0_cfg5_s          cnf75xx;
};
typedef union cvmx_fdeqx_jd0_cfg5 cvmx_fdeqx_jd0_cfg5_t;

/**
 * cvmx_fdeq#_jd0_mmse_cfg#
 *
 * This register space contains the MMSE portion of the job descriptor.
 *
 */
union cvmx_fdeqx_jd0_mmse_cfgx {
	uint64_t u64;
	struct cvmx_fdeqx_jd0_mmse_cfgx_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t mmse_job                     : 64; /**< MMSE job descriptor data. */
#else
	uint64_t mmse_job                     : 64;
#endif
	} s;
	struct cvmx_fdeqx_jd0_mmse_cfgx_s     cnf75xx;
};
typedef union cvmx_fdeqx_jd0_mmse_cfgx cvmx_fdeqx_jd0_mmse_cfgx_t;

/**
 * cvmx_fdeq#_jd1_cfg0
 */
union cvmx_fdeqx_jd1_cfg0 {
	uint64_t u64;
	struct cvmx_fdeqx_jd1_cfg0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_47_63               : 17;
	uint64_t mmse_idft_bypass             : 1;  /**< See FDEQ()_JD0_CFG0[MMSE_IDFT_BYPASS]. */
	uint64_t mmse_bypass                  : 1;  /**< See FDEQ()_JD0_CFG0[MMSE_BYPASS]. */
	uint64_t idft_bypass                  : 1;  /**< See FDEQ()_JD0_CFG0[IDFT_BYPASS]. */
	uint64_t demapper_bypass              : 1;  /**< See FDEQ()_JD0_CFG0[DEMAPPER_BYPASS]. */
	uint64_t descrambler_bypass           : 1;  /**< See FDEQ()_JD0_CFG0[DESCRAMBLER_BYPASS]. */
	uint64_t ack_scomb_bypass             : 1;  /**< See FDEQ()_JD0_CFG0[ACK_SCOMB_BYPASS]. */
	uint64_t ri_scomb_bypass              : 1;  /**< See FDEQ()_JD0_CFG0[RI_SCOMB_BYPASS]. */
	uint64_t cqi_scomb_bypass             : 1;  /**< See FDEQ()_JD0_CFG0[CQI_SCOMB_BYPASS]. */
	uint64_t ack_extract_bypass           : 1;  /**< See FDEQ()_JD0_CFG0[ACK_EXTRACT_BYPASS]. */
	uint64_t ri_extract_bypass            : 1;  /**< See FDEQ()_JD0_CFG0[RI_EXTRACT_BYPASS]. */
	uint64_t report_bypass                : 1;  /**< See FDEQ()_JD0_CFG0[REPORT_BYPASS]. */
	uint64_t reserved_33_35               : 3;
	uint64_t cp_type                      : 1;  /**< See FDEQ()_JD0_CFG0[CP_TYPE]. */
	uint64_t reserved_29_31               : 3;
	uint64_t layer_id                     : 1;  /**< See FDEQ()_JD0_CFG0[LAYER_ID]. */
	uint64_t reserved_26_27               : 2;
	uint64_t num_layers                   : 2;  /**< See FDEQ()_JD0_CFG0[NUM_LAYERS]. */
	uint64_t reserved_23_23               : 1;
	uint64_t mod_order                    : 3;  /**< See FDEQ()_JD0_CFG0[MOD_ORDER]. */
	uint64_t reserved_18_19               : 2;
	uint64_t slot_id                      : 2;  /**< See FDEQ()_JD0_CFG0[SLOT_ID]. */
	uint64_t reserved_9_15                : 7;
	uint64_t srs_flag                     : 1;  /**< See FDEQ()_JD0_CFG0[SRS_FLAG]. */
	uint64_t reserved_6_7                 : 2;
	uint64_t ndft_indx                    : 6;  /**< See FDEQ()_JD0_CFG0[NDFT_INDX]. */
#else
	uint64_t ndft_indx                    : 6;
	uint64_t reserved_6_7                 : 2;
	uint64_t srs_flag                     : 1;
	uint64_t reserved_9_15                : 7;
	uint64_t slot_id                      : 2;
	uint64_t reserved_18_19               : 2;
	uint64_t mod_order                    : 3;
	uint64_t reserved_23_23               : 1;
	uint64_t num_layers                   : 2;
	uint64_t reserved_26_27               : 2;
	uint64_t layer_id                     : 1;
	uint64_t reserved_29_31               : 3;
	uint64_t cp_type                      : 1;
	uint64_t reserved_33_35               : 3;
	uint64_t report_bypass                : 1;
	uint64_t ri_extract_bypass            : 1;
	uint64_t ack_extract_bypass           : 1;
	uint64_t cqi_scomb_bypass             : 1;
	uint64_t ri_scomb_bypass              : 1;
	uint64_t ack_scomb_bypass             : 1;
	uint64_t descrambler_bypass           : 1;
	uint64_t demapper_bypass              : 1;
	uint64_t idft_bypass                  : 1;
	uint64_t mmse_bypass                  : 1;
	uint64_t mmse_idft_bypass             : 1;
	uint64_t reserved_47_63               : 17;
#endif
	} s;
	struct cvmx_fdeqx_jd1_cfg0_s          cnf75xx;
};
typedef union cvmx_fdeqx_jd1_cfg0 cvmx_fdeqx_jd1_cfg0_t;

/**
 * cvmx_fdeq#_jd1_cfg1
 */
union cvmx_fdeqx_jd1_cfg1 {
	uint64_t u64;
	struct cvmx_fdeqx_jd1_cfg1_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_53_63               : 11;
	uint64_t rs_bits_last                 : 5;  /**< See FDEQ()_JD0_CFG1[RS_BITS_LAST]. */
	uint64_t reserved_45_47               : 3;
	uint64_t ack_ri_dmp_treatment         : 1;  /**< See FDEQ()_JD0_CFG1[ACK_RI_DMP_TREATMENT]. */
	uint64_t q_format                     : 4;  /**< See FDEQ()_JD0_CFG1[Q_FORMAT]. */
	uint64_t scaled_sinr_rsft             : 4;  /**< See FDEQ()_JD0_CFG1[SCALED_SINR_RSFT]. */
	uint64_t reserved_34_35               : 2;
	uint64_t mod_rsft                     : 6;  /**< See FDEQ()_JD0_CFG1[MOD_RSFT]. */
	uint64_t llr_bit_width                : 4;  /**< See FDEQ()_JD0_CFG1[LLR_BIT_WIDTH]. */
	uint64_t reserved_23_23               : 1;
	uint64_t llr_offset_input             : 7;  /**< See FDEQ()_JD0_CFG1[LLR_OFFSET_INPUT]. */
	uint64_t mod_scale                    : 16; /**< See FDEQ()_JD0_CFG1[MOD_SCALE]. */
#else
	uint64_t mod_scale                    : 16;
	uint64_t llr_offset_input             : 7;
	uint64_t reserved_23_23               : 1;
	uint64_t llr_bit_width                : 4;
	uint64_t mod_rsft                     : 6;
	uint64_t reserved_34_35               : 2;
	uint64_t scaled_sinr_rsft             : 4;
	uint64_t q_format                     : 4;
	uint64_t ack_ri_dmp_treatment         : 1;
	uint64_t reserved_45_47               : 3;
	uint64_t rs_bits_last                 : 5;
	uint64_t reserved_53_63               : 11;
#endif
	} s;
	struct cvmx_fdeqx_jd1_cfg1_s          cnf75xx;
};
typedef union cvmx_fdeqx_jd1_cfg1 cvmx_fdeqx_jd1_cfg1_t;

/**
 * cvmx_fdeq#_jd1_cfg2
 */
union cvmx_fdeqx_jd1_cfg2 {
	uint64_t u64;
	struct cvmx_fdeqx_jd1_cfg2_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_63_63               : 1;
	uint64_t cinit                        : 31; /**< N/A */
	uint64_t reserved_17_31               : 15;
	uint64_t seq_offset                   : 17; /**< See FDEQ()_JD0_CFG2[SEQ_OFFSET]. */
#else
	uint64_t seq_offset                   : 17;
	uint64_t reserved_17_31               : 15;
	uint64_t cinit                        : 31;
	uint64_t reserved_63_63               : 1;
#endif
	} s;
	struct cvmx_fdeqx_jd1_cfg2_s          cnf75xx;
};
typedef union cvmx_fdeqx_jd1_cfg2 cvmx_fdeqx_jd1_cfg2_t;

/**
 * cvmx_fdeq#_jd1_cfg3
 */
union cvmx_fdeqx_jd1_cfg3 {
	uint64_t u64;
	struct cvmx_fdeqx_jd1_cfg3_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_51_63               : 13;
	uint64_t ack_enc_cat                  : 3;  /**< See FDEQ()_JD0_CFG3[ACK_ENC_CAT]. */
	uint64_t reserved_35_47               : 13;
	uint64_t ri_enc_cat                   : 3;  /**< See FDEQ()_JD0_CFG3[RI_ENC_CAT]. */
	uint64_t reserved_29_31               : 3;
	uint64_t num_ack_re                   : 13; /**< See FDEQ()_JD0_CFG3[NUM_ACK_RE]. */
	uint64_t reserved_13_15               : 3;
	uint64_t num_ri_re                    : 13; /**< See FDEQ()_JD0_CFG3[NUM_RI_RE]. */
#else
	uint64_t num_ri_re                    : 13;
	uint64_t reserved_13_15               : 3;
	uint64_t num_ack_re                   : 13;
	uint64_t reserved_29_31               : 3;
	uint64_t ri_enc_cat                   : 3;
	uint64_t reserved_35_47               : 13;
	uint64_t ack_enc_cat                  : 3;
	uint64_t reserved_51_63               : 13;
#endif
	} s;
	struct cvmx_fdeqx_jd1_cfg3_s          cnf75xx;
};
typedef union cvmx_fdeqx_jd1_cfg3 cvmx_fdeqx_jd1_cfg3_t;

/**
 * cvmx_fdeq#_jd1_cfg4
 */
union cvmx_fdeqx_jd1_cfg4 {
	uint64_t u64;
	struct cvmx_fdeqx_jd1_cfg4_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_62_63               : 2;
	uint64_t num_cqi_re0                  : 14; /**< See FDEQ()_JD0_CFG4[NUM_CQI_RE0]. */
	uint64_t reserved_46_47               : 2;
	uint64_t num_cqi_re1                  : 14; /**< See FDEQ()_JD0_CFG4[NUM_CQI_RE1]. */
	uint64_t reserved_30_31               : 2;
	uint64_t num_cqi_re2                  : 14; /**< See FDEQ()_JD0_CFG4[NUM_CQI_RE2]. */
	uint64_t reserved_14_15               : 2;
	uint64_t num_cqi_re3                  : 14; /**< See FDEQ()_JD0_CFG4[NUM_CQI_RE3]. */
#else
	uint64_t num_cqi_re3                  : 14;
	uint64_t reserved_14_15               : 2;
	uint64_t num_cqi_re2                  : 14;
	uint64_t reserved_30_31               : 2;
	uint64_t num_cqi_re1                  : 14;
	uint64_t reserved_46_47               : 2;
	uint64_t num_cqi_re0                  : 14;
	uint64_t reserved_62_63               : 2;
#endif
	} s;
	struct cvmx_fdeqx_jd1_cfg4_s          cnf75xx;
};
typedef union cvmx_fdeqx_jd1_cfg4 cvmx_fdeqx_jd1_cfg4_t;

/**
 * cvmx_fdeq#_jd1_cfg5
 */
union cvmx_fdeqx_jd1_cfg5 {
	uint64_t u64;
	struct cvmx_fdeqx_jd1_cfg5_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_62_63               : 2;
	uint64_t num_cqi_re4                  : 14; /**< See FDEQ()_JD0_CFG5[NUM_CQI_RE4]. */
	uint64_t reserved_46_47               : 2;
	uint64_t num_cqi_re5                  : 14; /**< See FDEQ()_JD0_CFG5[NUM_CQI_RE5]. */
	uint64_t reserved_30_31               : 2;
	uint64_t num_cqi_re6                  : 14; /**< See FDEQ()_JD0_CFG5[NUM_CQI_RE6]. */
	uint64_t reserved_14_15               : 2;
	uint64_t num_cqi_re7                  : 14; /**< See FDEQ()_JD0_CFG5[NUM_CQI_RE7]. */
#else
	uint64_t num_cqi_re7                  : 14;
	uint64_t reserved_14_15               : 2;
	uint64_t num_cqi_re6                  : 14;
	uint64_t reserved_30_31               : 2;
	uint64_t num_cqi_re5                  : 14;
	uint64_t reserved_46_47               : 2;
	uint64_t num_cqi_re4                  : 14;
	uint64_t reserved_62_63               : 2;
#endif
	} s;
	struct cvmx_fdeqx_jd1_cfg5_s          cnf75xx;
};
typedef union cvmx_fdeqx_jd1_cfg5 cvmx_fdeqx_jd1_cfg5_t;

/**
 * cvmx_fdeq#_jd1_mmse_cfg#
 *
 * This register space contains the MMSE job descriptor data.
 *
 */
union cvmx_fdeqx_jd1_mmse_cfgx {
	uint64_t u64;
	struct cvmx_fdeqx_jd1_mmse_cfgx_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t mmse_job                     : 64; /**< MMSE Job descriptors. */
#else
	uint64_t mmse_job                     : 64;
#endif
	} s;
	struct cvmx_fdeqx_jd1_mmse_cfgx_s     cnf75xx;
};
typedef union cvmx_fdeqx_jd1_mmse_cfgx cvmx_fdeqx_jd1_mmse_cfgx_t;

/**
 * cvmx_fdeq#_pipeline_disable
 *
 * This register controls job pipelining with the MMSE sub-block.
 *
 */
union cvmx_fdeqx_pipeline_disable {
	uint64_t u64;
	struct cvmx_fdeqx_pipeline_disable_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_1_63                : 63;
	uint64_t dis_pipeline                 : 1;  /**< Set to 1 to disable job pipelining within MMSE. */
#else
	uint64_t dis_pipeline                 : 1;
	uint64_t reserved_1_63                : 63;
#endif
	} s;
	struct cvmx_fdeqx_pipeline_disable_s  cnf75xx;
};
typedef union cvmx_fdeqx_pipeline_disable cvmx_fdeqx_pipeline_disable_t;

/**
 * cvmx_fdeq#_status
 */
union cvmx_fdeqx_status {
	uint64_t u64;
	struct cvmx_fdeqx_status_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_2_63                : 62;
	uint64_t status1                      : 1;  /**< When set, slot 1 is busy processing a job. */
	uint64_t status0                      : 1;  /**< When set, slot 0 is busy processing a job. */
#else
	uint64_t status0                      : 1;
	uint64_t status1                      : 1;
	uint64_t reserved_2_63                : 62;
#endif
	} s;
	struct cvmx_fdeqx_status_s            cnf75xx;
};
typedef union cvmx_fdeqx_status cvmx_fdeqx_status_t;

/**
 * cvmx_fdeq#_test
 *
 * This register is used to stress internal Hardware backpressure points for Testing
 *
 */
union cvmx_fdeqx_test {
	uint64_t u64;
	struct cvmx_fdeqx_test_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t enable                       : 4;  /**< Enable test mode. For diagnostic use only. */
	uint64_t reserved_24_59               : 36;
	uint64_t bp_cfg                       : 8;  /**< Enable backpressure. For diagnostic use only. */
	uint64_t reserved_12_15               : 4;
	uint64_t lfsr_freq                    : 12; /**< Test LFSR update frequency in coprocessor-clocks minus one. */
#else
	uint64_t lfsr_freq                    : 12;
	uint64_t reserved_12_15               : 4;
	uint64_t bp_cfg                       : 8;
	uint64_t reserved_24_59               : 36;
	uint64_t enable                       : 4;
#endif
	} s;
	struct cvmx_fdeqx_test_s              cnf75xx;
};
typedef union cvmx_fdeqx_test cvmx_fdeqx_test_t;

/**
 * cvmx_fdeq#_test2
 *
 * This register is used to stress internal Hardware backpressure points for Testing
 *
 */
union cvmx_fdeqx_test2 {
	uint64_t u64;
	struct cvmx_fdeqx_test2_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t enable                       : 4;  /**< Enable test mode. For diagnostic use only. */
	uint64_t reserved_24_59               : 36;
	uint64_t bp_cfg                       : 8;  /**< Enable backpressure. For diagnostic use only. */
	uint64_t reserved_12_15               : 4;
	uint64_t lfsr_freq                    : 12; /**< Test LFSR update frequency in coprocessor-clocks minus one. */
#else
	uint64_t lfsr_freq                    : 12;
	uint64_t reserved_12_15               : 4;
	uint64_t bp_cfg                       : 8;
	uint64_t reserved_24_59               : 36;
	uint64_t enable                       : 4;
#endif
	} s;
	struct cvmx_fdeqx_test2_s             cnf75xx;
};
typedef union cvmx_fdeqx_test2 cvmx_fdeqx_test2_t;

#endif
