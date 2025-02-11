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
 * @file
 *
 * Automatically generated error messages for cn31xx.
 *
 * This file is auto generated. Do not edit.
 *
 * <hr>$Revision$<hr>
 *
 * <hr><h2>Error tree for CN31XX</h2>
 * @dot
 * digraph cn31xx
 * {
 *     rankdir=LR;
 *     node [shape=record, width=.1, height=.1, fontsize=8, font=helvitica];
 *     edge [fontsize=7, font=helvitica];
 *     cvmx_root [label="ROOT|<root>root"];
 *     cvmx_ciu_int0_sum0 [label="CIU_INTX_SUM0(0)|<rml>rml"];
 *     cvmx_npi_rsl_int_blocks [label="NPI_RSL_INT_BLOCKS|<l2c>l2c|<npi>npi|<gmx0>gmx0|<mio>mio|<ipd>ipd|<pow>pow|<asx0>asx0|<pko>pko|<tim>tim|<zip>zip|<pip>pip|<fpa>fpa|<lmc>lmc|<dfa>dfa|<iob>iob|<usb>usb"];
 *     cvmx_l2d_err [label="L2D_ERR|<sec_err>sec_err|<ded_err>ded_err"];
 *     cvmx_npi_rsl_int_blocks:l2c:e -> cvmx_l2d_err [label="l2c"];
 *     cvmx_l2t_err [label="L2T_ERR|<sec_err>sec_err|<ded_err>ded_err|<lckerr>lckerr|<lckerr2>lckerr2"];
 *     cvmx_npi_rsl_int_blocks:l2c:e -> cvmx_l2t_err [label="l2c"];
 *     cvmx_npi_int_sum [label="NPI_INT_SUM|<rml_rto>rml_rto|<rml_wto>rml_wto|<po0_2sml>po0_2sml|<po1_2sml>po1_2sml|<i0_rtout>i0_rtout|<i1_rtout>i1_rtout|<i0_overf>i0_overf|<i1_overf>i1_overf|<p0_rtout>p0_rtout|<p1_rtout>p1_rtout|<p0_perr>p0_perr|<p1_perr>p1_perr|<g0_rtout>g0_rtout|<g1_rtout>g1_rtout|<p0_pperr>p0_pperr|<p1_pperr>p1_pperr|<p0_ptout>p0_ptout|<p1_ptout>p1_ptout|<i0_pperr>i0_pperr|<i1_pperr>i1_pperr|<win_rto>win_rto|<p_dperr>p_dperr|<iobdma>iobdma|<fcr_s_e>fcr_s_e|<fcr_a_f>fcr_a_f|<pcr_s_e>pcr_s_e|<pcr_a_f>pcr_a_f|<q2_s_e>q2_s_e|<q2_a_f>q2_a_f|<q3_s_e>q3_s_e|<q3_a_f>q3_a_f|<com_s_e>com_s_e|<com_a_f>com_a_f|<pnc_s_e>pnc_s_e|<pnc_a_f>pnc_a_f|<rwx_s_e>rwx_s_e|<rdx_s_e>rdx_s_e|<pcf_p_e>pcf_p_e|<pcf_p_f>pcf_p_f|<pdf_p_e>pdf_p_e|<pdf_p_f>pdf_p_f|<q1_s_e>q1_s_e|<q1_a_f>q1_a_f|<pci_rsl>pci_rsl"];
 *     cvmx_pci_int_sum2 [label="NPI_PCI_INT_SUM2|<tr_wabt>tr_wabt|<mr_wabt>mr_wabt|<mr_wtto>mr_wtto|<tr_abt>tr_abt|<mr_abt>mr_abt|<mr_tto>mr_tto|<msi_per>msi_per|<msi_tabt>msi_tabt|<msi_mabt>msi_mabt|<msc_msg>msc_msg|<tsr_abt>tsr_abt|<serr>serr|<aperr>aperr|<dperr>dperr|<ill_rwr>ill_rwr|<ill_rrd>ill_rrd|<win_wr>win_wr|<ill_wr>ill_wr|<ill_rd>ill_rd"];
 *     cvmx_npi_int_sum:pci_rsl:e -> cvmx_pci_int_sum2 [label="pci_rsl"];
 *     cvmx_npi_rsl_int_blocks:npi:e -> cvmx_npi_int_sum [label="npi"];
 *     cvmx_gmx0_bad_reg [label="GMXX_BAD_REG(0)|<out_ovr>out_ovr|<loststat>loststat|<statovr>statovr|<inb_nxa>inb_nxa"];
 *     cvmx_npi_rsl_int_blocks:gmx0:e -> cvmx_gmx0_bad_reg [label="gmx0"];
 *     cvmx_gmx0_rx0_int_reg [label="GMXX_RXX_INT_REG(0,0)|<carext>carext|<maxerr>maxerr|<alnerr>alnerr|<lenerr>lenerr|<skperr>skperr|<niberr>niberr|<ovrerr>ovrerr"];
 *     cvmx_npi_rsl_int_blocks:gmx0:e -> cvmx_gmx0_rx0_int_reg [label="gmx0"];
 *     cvmx_gmx0_rx1_int_reg [label="GMXX_RXX_INT_REG(1,0)|<carext>carext|<maxerr>maxerr|<alnerr>alnerr|<lenerr>lenerr|<skperr>skperr|<niberr>niberr|<ovrerr>ovrerr"];
 *     cvmx_npi_rsl_int_blocks:gmx0:e -> cvmx_gmx0_rx1_int_reg [label="gmx0"];
 *     cvmx_gmx0_rx2_int_reg [label="GMXX_RXX_INT_REG(2,0)|<carext>carext|<maxerr>maxerr|<alnerr>alnerr|<lenerr>lenerr|<skperr>skperr|<niberr>niberr|<ovrerr>ovrerr"];
 *     cvmx_npi_rsl_int_blocks:gmx0:e -> cvmx_gmx0_rx2_int_reg [label="gmx0"];
 *     cvmx_gmx0_tx_int_reg [label="GMXX_TX_INT_REG(0)|<pko_nxa>pko_nxa|<undflw>undflw"];
 *     cvmx_npi_rsl_int_blocks:gmx0:e -> cvmx_gmx0_tx_int_reg [label="gmx0"];
 *     cvmx_mio_boot_err [label="MIO_BOOT_ERR|<adr_err>adr_err|<wait_err>wait_err"];
 *     cvmx_npi_rsl_int_blocks:mio:e -> cvmx_mio_boot_err [label="mio"];
 *     cvmx_ipd_int_sum [label="IPD_INT_SUM|<prc_par0>prc_par0|<prc_par1>prc_par1|<prc_par2>prc_par2|<prc_par3>prc_par3|<bp_sub>bp_sub"];
 *     cvmx_npi_rsl_int_blocks:ipd:e -> cvmx_ipd_int_sum [label="ipd"];
 *     cvmx_pow_ecc_err [label="POW_ECC_ERR|<sbe>sbe|<dbe>dbe|<rpe>rpe"];
 *     cvmx_npi_rsl_int_blocks:pow:e -> cvmx_pow_ecc_err [label="pow"];
 *     cvmx_asx0_int_reg [label="ASXX_INT_REG(0)|<ovrflw>ovrflw|<txpop>txpop|<txpsh>txpsh"];
 *     cvmx_npi_rsl_int_blocks:asx0:e -> cvmx_asx0_int_reg [label="asx0"];
 *     cvmx_pko_reg_error [label="PKO_REG_ERROR|<parity>parity|<doorbell>doorbell"];
 *     cvmx_npi_rsl_int_blocks:pko:e -> cvmx_pko_reg_error [label="pko"];
 *     cvmx_tim_reg_error [label="TIM_REG_ERROR|<mask>mask"];
 *     cvmx_npi_rsl_int_blocks:tim:e -> cvmx_tim_reg_error [label="tim"];
 *     cvmx_zip_error [label="ZIP_ERROR|<doorbell>doorbell"];
 *     cvmx_npi_rsl_int_blocks:zip:e -> cvmx_zip_error [label="zip"];
 *     cvmx_pip_int_reg [label="PIP_INT_REG|<prtnxa>prtnxa|<badtag>badtag|<skprunt>skprunt|<todoovr>todoovr|<feperr>feperr|<beperr>beperr"];
 *     cvmx_npi_rsl_int_blocks:pip:e -> cvmx_pip_int_reg [label="pip"];
 *     cvmx_fpa_int_sum [label="FPA_INT_SUM|<fed0_sbe>fed0_sbe|<fed0_dbe>fed0_dbe|<fed1_sbe>fed1_sbe|<fed1_dbe>fed1_dbe|<q0_und>q0_und|<q0_coff>q0_coff|<q0_perr>q0_perr|<q1_und>q1_und|<q1_coff>q1_coff|<q1_perr>q1_perr|<q2_und>q2_und|<q2_coff>q2_coff|<q2_perr>q2_perr|<q3_und>q3_und|<q3_coff>q3_coff|<q3_perr>q3_perr|<q4_und>q4_und|<q4_coff>q4_coff|<q4_perr>q4_perr|<q5_und>q5_und|<q5_coff>q5_coff|<q5_perr>q5_perr|<q6_und>q6_und|<q6_coff>q6_coff|<q6_perr>q6_perr|<q7_und>q7_und|<q7_coff>q7_coff|<q7_perr>q7_perr"];
 *     cvmx_npi_rsl_int_blocks:fpa:e -> cvmx_fpa_int_sum [label="fpa"];
 *     cvmx_lmc0_mem_cfg0 [label="LMCX_MEM_CFG0(0)|<sec_err>sec_err|<ded_err>ded_err"];
 *     cvmx_npi_rsl_int_blocks:lmc:e -> cvmx_lmc0_mem_cfg0 [label="lmc"];
 *     cvmx_dfa_err [label="DFA_ERR|<cp2sbe>cp2sbe|<cp2dbe>cp2dbe|<dtesbe>dtesbe|<dtedbe>dtedbe|<dteperr>dteperr|<cp2perr>cp2perr|<dblovf>dblovf"];
 *     cvmx_npi_rsl_int_blocks:dfa:e -> cvmx_dfa_err [label="dfa"];
 *     cvmx_iob_int_sum [label="IOB_INT_SUM|<np_sop>np_sop|<np_eop>np_eop|<p_sop>p_sop|<p_eop>p_eop"];
 *     cvmx_npi_rsl_int_blocks:iob:e -> cvmx_iob_int_sum [label="iob"];
 *     cvmx_usbn0_int_sum [label="USBNX_INT_SUM(0)|<pr_po_e>pr_po_e|<pr_pu_f>pr_pu_f|<nr_po_e>nr_po_e|<nr_pu_f>nr_pu_f|<lr_po_e>lr_po_e|<lr_pu_f>lr_pu_f|<pt_po_e>pt_po_e|<pt_pu_f>pt_pu_f|<nt_po_e>nt_po_e|<nt_pu_f>nt_pu_f|<lt_po_e>lt_po_e|<lt_pu_f>lt_pu_f|<dcred_e>dcred_e|<dcred_f>dcred_f|<l2c_s_e>l2c_s_e|<l2c_a_f>l2c_a_f|<lt_fi_e>lt_fi_e|<lt_fi_f>lt_fi_f|<rg_fi_e>rg_fi_e|<rg_fi_f>rg_fi_f|<rq_q2_f>rq_q2_f|<rq_q2_e>rq_q2_e|<rq_q3_f>rq_q3_f|<rq_q3_e>rq_q3_e|<uod_pe>uod_pe|<uod_pf>uod_pf|<n2u_pf>n2u_pf|<n2u_pe>n2u_pe|<u2n_d_pe>u2n_d_pe|<u2n_d_pf>u2n_d_pf|<u2n_c_pf>u2n_c_pf|<u2n_c_pe>u2n_c_pe|<ltl_f_pe>ltl_f_pe|<ltl_f_pf>ltl_f_pf|<nd4o_rpe>nd4o_rpe|<nd4o_rpf>nd4o_rpf|<nd4o_dpe>nd4o_dpe|<nd4o_dpf>nd4o_dpf"];
 *     cvmx_npi_rsl_int_blocks:usb:e -> cvmx_usbn0_int_sum [label="usb"];
 *     cvmx_gmx0_bad_reg -> cvmx_gmx0_rx0_int_reg [style=invis];
 *     cvmx_gmx0_rx0_int_reg -> cvmx_gmx0_rx1_int_reg [style=invis];
 *     cvmx_gmx0_rx1_int_reg -> cvmx_gmx0_rx2_int_reg [style=invis];
 *     cvmx_gmx0_rx2_int_reg -> cvmx_gmx0_tx_int_reg [style=invis];
 *     cvmx_ciu_int0_sum0:rml:e -> cvmx_npi_rsl_int_blocks [label="rml"];
 *     cvmx_root:root:e -> cvmx_ciu_int0_sum0 [label="root"];
 *     cvmx_ciu_int_sum1 [label="CIU_INT_SUM1"];
 *     cvmx_root:root:e -> cvmx_ciu_int_sum1 [label="root"];
 * }
 * @enddot
 */
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
#include <asm/octeon/cvmx.h>
#include <asm/octeon/cvmx-error.h>
#include <asm/octeon/cvmx-error-custom.h>
#include <asm/octeon/cvmx-csr-typedefs.h>
#else
#include "cvmx.h"
#include "cvmx-error.h"
#include "cvmx-error-custom.h"
#endif

int cvmx_error_initialize_cn31xx(void)
{
    cvmx_error_info_t info;
    int fail = 0;

    /* CVMX_CIU_INTX_SUM0(0) */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_CIU_INTX_SUM0(0);
    info.status_mask        = 0;
    info.enable_addr        = 0;
    info.enable_mask        = 0;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = __CVMX_ERROR_REGISTER_NONE;
    info.parent.status_addr = 0;
    info.parent.status_mask = 0;
    info.func               = __cvmx_error_decode;
    info.user_info          = 0;
    fail |= cvmx_error_add(&info);

    /* CVMX_NPI_RSL_INT_BLOCKS */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_RSL_INT_BLOCKS;
    info.status_mask        = 0;
    info.enable_addr        = 0;
    info.enable_mask        = 0;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_CIU_INTX_SUM0(0);
    info.parent.status_mask = 1ull<<46 /* rml */;
    info.func               = __cvmx_error_decode;
    info.user_info          = 0;
    fail |= cvmx_error_add(&info);

    /* CVMX_L2D_ERR */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_L2D_ERR;
    info.status_mask        = 1ull<<3 /* sec_err */;
    info.enable_addr        = CVMX_L2D_ERR;
    info.enable_mask        = 1ull<<1 /* sec_intena */;
    info.flags              = CVMX_ERROR_TYPE_SBE;
    info.group              = CVMX_ERROR_GROUP_L2C;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<16 /* l2c */;
    info.func               = __cvmx_error_handle_l2d_err_sec_err;
    info.user_info          = (long)
        "ERROR L2D_ERR[SEC_ERR]: L2D Single Error corrected (SEC)\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_L2D_ERR;
    info.status_mask        = 1ull<<4 /* ded_err */;
    info.enable_addr        = CVMX_L2D_ERR;
    info.enable_mask        = 1ull<<2 /* ded_intena */;
    info.flags              = CVMX_ERROR_TYPE_DBE;
    info.group              = CVMX_ERROR_GROUP_L2C;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<16 /* l2c */;
    info.func               = __cvmx_error_handle_l2d_err_ded_err;
    info.user_info          = (long)
        "ERROR L2D_ERR[DED_ERR]: L2D Double Error detected (DED)\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_L2T_ERR */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_L2T_ERR;
    info.status_mask        = 1ull<<3 /* sec_err */;
    info.enable_addr        = CVMX_L2T_ERR;
    info.enable_mask        = 1ull<<1 /* sec_intena */;
    info.flags              = CVMX_ERROR_TYPE_SBE;
    info.group              = CVMX_ERROR_GROUP_L2C;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<16 /* l2c */;
    info.func               = __cvmx_error_handle_l2t_err_sec_err;
    info.user_info          = (long)
        "ERROR L2T_ERR[SEC_ERR]: L2T Single Bit Error corrected (SEC)\n"
        "    During every L2 Tag Probe, all 8 sets Tag's (at a\n"
        "    given index) are checked for single bit errors(SBEs).\n"
        "    This bit is set if ANY of the 8 sets contains an SBE.\n"
        "    SBEs are auto corrected in HW and generate an\n"
        "    interrupt(if enabled).\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_L2T_ERR;
    info.status_mask        = 1ull<<4 /* ded_err */;
    info.enable_addr        = CVMX_L2T_ERR;
    info.enable_mask        = 1ull<<2 /* ded_intena */;
    info.flags              = CVMX_ERROR_TYPE_DBE;
    info.group              = CVMX_ERROR_GROUP_L2C;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<16 /* l2c */;
    info.func               = __cvmx_error_handle_l2t_err_ded_err;
    info.user_info          = (long)
        "ERROR L2T_ERR[DED_ERR]: L2T Double Bit Error detected (DED)\n"
        "    During every L2 Tag Probe, all 8 sets Tag's (at a\n"
        "    given index) are checked for double bit errors(DBEs).\n"
        "    This bit is set if ANY of the 8 sets contains a DBE.\n"
        "    DBEs also generated an interrupt(if enabled).\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_L2T_ERR;
    info.status_mask        = 1ull<<24 /* lckerr */;
    info.enable_addr        = CVMX_L2T_ERR;
    info.enable_mask        = 1ull<<25 /* lck_intena */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_L2C;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<16 /* l2c */;
    info.func               = __cvmx_error_handle_l2t_err_lckerr;
    info.user_info          = (long)
        "ERROR L2T_ERR[LCKERR]: SW attempted to LOCK DOWN the last available set of\n"
        "    the INDEX (which is ignored by HW - but reported to SW).\n"
        "    The LDD(L1 load-miss) for the LOCK operation is completed\n"
        "    successfully, however the address is NOT locked.\n"
        "    NOTE: 'Available' sets takes the L2C_SPAR*[UMSK*]\n"
        "    into account. For example, if diagnostic PPx has\n"
        "    UMSKx defined to only use SETs [1:0], and SET1 had\n"
        "    been previously LOCKED, then an attempt to LOCK the\n"
        "    last available SET0 would result in a LCKERR. (This\n"
        "    is to ensure that at least 1 SET at each INDEX is\n"
        "    not LOCKED for general use by other PPs).\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_L2T_ERR;
    info.status_mask        = 1ull<<26 /* lckerr2 */;
    info.enable_addr        = CVMX_L2T_ERR;
    info.enable_mask        = 1ull<<27 /* lck_intena2 */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_L2C;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<16 /* l2c */;
    info.func               = __cvmx_error_handle_l2t_err_lckerr2;
    info.user_info          = (long)
        "ERROR L2T_ERR[LCKERR2]: HW detected a case where a Rd/Wr Miss from PP#n\n"
        "    could not find an available/unlocked set (for\n"
        "    replacement).\n"
        "    Most likely, this is a result of SW mixing SET\n"
        "    PARTITIONING with ADDRESS LOCKING. If SW allows\n"
        "    another PP to LOCKDOWN all SETs available to PP#n,\n"
        "    then a Rd/Wr Miss from PP#n will be unable\n"
        "    to determine a 'valid' replacement set (since LOCKED\n"
        "    addresses should NEVER be replaced).\n"
        "    If such an event occurs, the HW will select the smallest\n"
        "    available SET(specified by UMSK'x)' as the replacement\n"
        "    set, and the address is unlocked.\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_NPI_INT_SUM */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<0 /* rml_rto */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<0 /* rml_rto */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[RML_RTO]: Set '1' when the RML does not receive read data\n"
        "    back from a RSL after sending a read command to\n"
        "    a RSL.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<1 /* rml_wto */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<1 /* rml_wto */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[RML_WTO]: Set '1' when the RML does not receive a commit\n"
        "    back from a RSL after sending a write command to\n"
        "    a RSL.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<3 /* po0_2sml */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<3 /* po0_2sml */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[PO0_2SML]: The packet being sent out on Port0 is smaller\n"
        "    than the NPI_BUFF_SIZE_OUTPUT0[ISIZE] field.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<4 /* po1_2sml */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<4 /* po1_2sml */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[PO1_2SML]: The packet being sent out on Port1 is smaller\n"
        "    than the NPI_BUFF_SIZE_OUTPUT1[ISIZE] field.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<7 /* i0_rtout */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<7 /* i0_rtout */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[I0_RTOUT]: Port-0 had a read timeout while attempting to\n"
        "    read instructions.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<8 /* i1_rtout */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<8 /* i1_rtout */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[I1_RTOUT]: Port-1 had a read timeout while attempting to\n"
        "    read instructions.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<11 /* i0_overf */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<11 /* i0_overf */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[I0_OVERF]: Port-0 had a doorbell overflow. Bit[31] of the\n"
        "    doorbell count was set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<12 /* i1_overf */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<12 /* i1_overf */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[I1_OVERF]: Port-1 had a doorbell overflow. Bit[31] of the\n"
        "    doorbell count was set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<15 /* p0_rtout */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<15 /* p0_rtout */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[P0_RTOUT]: Port-0 had a read timeout while attempting to\n"
        "    read packet data.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<16 /* p1_rtout */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<16 /* p1_rtout */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[P1_RTOUT]: Port-1 had a read timeout while attempting to\n"
        "    read packet data.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<19 /* p0_perr */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<19 /* p0_perr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[P0_PERR]: If a parity error occured on the port's packet\n"
        "    data this bit may be set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<20 /* p1_perr */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<20 /* p1_perr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[P1_PERR]: If a parity error occured on the port's packet\n"
        "    data this bit may be set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<23 /* g0_rtout */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<23 /* g0_rtout */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[G0_RTOUT]: Port-0 had a read timeout while attempting to\n"
        "    read a gather list.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<24 /* g1_rtout */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<24 /* g1_rtout */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[G1_RTOUT]: Port-1 had a read timeout while attempting to\n"
        "    read a gather list.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<27 /* p0_pperr */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<27 /* p0_pperr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[P0_PPERR]: If a parity error occured on the port DATA/INFO\n"
        "    pointer-pair, this bit may be set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<28 /* p1_pperr */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<28 /* p1_pperr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[P1_PPERR]: If a parity error occured on the port DATA/INFO\n"
        "    pointer-pair, this bit may be set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<31 /* p0_ptout */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<31 /* p0_ptout */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[P0_PTOUT]: Port-0 output had a read timeout on a DATA/INFO\n"
        "    pair.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<32 /* p1_ptout */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<32 /* p1_ptout */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[P1_PTOUT]: Port-1 output had a read timeout on a DATA/INFO\n"
        "    pair.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<35 /* i0_pperr */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<35 /* i0_pperr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[I0_PPERR]: If a parity error occured on the port's instruction\n"
        "    this bit may be set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<36 /* i1_pperr */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<36 /* i1_pperr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[I1_PPERR]: If a parity error occured on the port's instruction\n"
        "    this bit may be set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<39 /* win_rto */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<39 /* win_rto */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[WIN_RTO]: Windowed Load Timed Out.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<40 /* p_dperr */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<40 /* p_dperr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[P_DPERR]: If a parity error occured on data written to L2C\n"
        "    from the PCI this bit may be set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<41 /* iobdma */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<41 /* iobdma */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[IOBDMA]: Requested IOBDMA read size exceeded 128 words.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<42 /* fcr_s_e */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<42 /* fcr_s_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[FCR_S_E]: Attempted to subtract when FPA Credits is empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<43 /* fcr_a_f */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<43 /* fcr_a_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[FCR_A_F]: Attempted to add when FPA Credits is full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<44 /* pcr_s_e */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<44 /* pcr_s_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[PCR_S_E]: Attempted to subtract when POW Credits is empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<45 /* pcr_a_f */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<45 /* pcr_a_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[PCR_A_F]: Attempted to add when POW Credits is full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<46 /* q2_s_e */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<46 /* q2_s_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[Q2_S_E]: Attempted to subtract when Queue-2 FIFO is empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<47 /* q2_a_f */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<47 /* q2_a_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[Q2_A_F]: Attempted to add when Queue-2 FIFO is full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<48 /* q3_s_e */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<48 /* q3_s_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[Q3_S_E]: Attempted to subtract when Queue-3 FIFO is empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<49 /* q3_a_f */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<49 /* q3_a_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[Q3_A_F]: Attempted to add when Queue-3 FIFO is full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<50 /* com_s_e */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<50 /* com_s_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[COM_S_E]: Attempted to subtract when PCN-Commit Counter is 0.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<51 /* com_a_f */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<51 /* com_a_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[COM_A_F]: Attempted to add when PCN-Commit Counter is max.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<52 /* pnc_s_e */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<52 /* pnc_s_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[PNC_S_E]: Attempted to subtract when PNI-NPI Credits are 0.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<53 /* pnc_a_f */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<53 /* pnc_a_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[PNC_A_F]: Attempted to add when PNI-NPI Credits are max.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<54 /* rwx_s_e */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<54 /* rwx_s_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[RWX_S_E]: Attempted to subtract when RDN-XFR-Wait count is 0.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<55 /* rdx_s_e */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<55 /* rdx_s_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[RDX_S_E]: Attempted to subtract when DPI-XFR-Wait count is 0.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<56 /* pcf_p_e */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<56 /* pcf_p_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[PCF_P_E]: Attempted to pop an empty PCN-CNT-FIFO.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<57 /* pcf_p_f */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<57 /* pcf_p_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[PCF_P_F]: Attempted to push a full PCN-CNT-FIFO.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<58 /* pdf_p_e */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<58 /* pdf_p_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[PDF_P_E]: Attempted to pop an empty PCN-DATA-FIFO.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<59 /* pdf_p_f */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<59 /* pdf_p_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[PDF_P_F]: Attempted to push a full PCN-DATA-FIFO.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<60 /* q1_s_e */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<60 /* q1_s_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[Q1_S_E]: Attempted to subtract when Queue-1 FIFO is empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 1ull<<61 /* q1_a_f */;
    info.enable_addr        = CVMX_NPI_INT_ENB;
    info.enable_mask        = 1ull<<61 /* q1_a_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_INT_SUM[Q1_A_F]: Attempted to add when Queue-1 FIFO is full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_INT_SUM;
    info.status_mask        = 0;
    info.enable_addr        = 0;
    info.enable_mask        = 0;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<3 /* npi */;
    info.func               = __cvmx_error_decode;
    info.user_info          = 0;
    fail |= cvmx_error_add(&info);

    /* CVMX_NPI_PCI_INT_SUM2 */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<0 /* tr_wabt */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<0 /* rtr_wabt */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[TR_WABT]: PCI Target Abort detected on write.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<1 /* mr_wabt */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<1 /* rmr_wabt */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[MR_WABT]: PCI Master Abort detected on write.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<2 /* mr_wtto */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<2 /* rmr_wtto */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[MR_WTTO]: PCI Master Retry Timeout on write.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<3 /* tr_abt */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<3 /* rtr_abt */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[TR_ABT]: PCI Target Abort On Read.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<4 /* mr_abt */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<4 /* rmr_abt */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[MR_ABT]: PCI Master Abort On Read.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<5 /* mr_tto */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<5 /* rmr_tto */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[MR_TTO]: PCI Master Retry Timeout On Read.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<6 /* msi_per */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<6 /* rmsi_per */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[MSI_PER]: PCI MSI Parity Error.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<7 /* msi_tabt */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<7 /* rmsi_tabt */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[MSI_TABT]: PCI MSI Target Abort.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<8 /* msi_mabt */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<8 /* rmsi_mabt */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[MSI_MABT]: PCI MSI Master Abort.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<9 /* msc_msg */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<9 /* rmsc_msg */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[MSC_MSG]: Master Split Completion Message Detected\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<10 /* tsr_abt */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<10 /* rtsr_abt */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[TSR_ABT]: Target Split-Read Abort Detected\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<11 /* serr */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<11 /* rserr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[SERR]: SERR# detected by PCX Core\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<12 /* aperr */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<12 /* raperr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[APERR]: Address Parity Error detected by PCX Core\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<13 /* dperr */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<13 /* rdperr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[DPERR]: Data Parity Error detected by PCX Core\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<14 /* ill_rwr */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<14 /* ill_rwr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[ILL_RWR]: A write to the disabled PCI registers took place.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<15 /* ill_rrd */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<15 /* ill_rrd */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[ILL_RRD]: A read  to the disabled PCI registers took place.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<31 /* win_wr */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<31 /* win_wr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[WIN_WR]: A write to the disabled Window Write Data or\n"
        "    Read-Address Register took place.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<32 /* ill_wr */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<32 /* ill_wr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[ILL_WR]: A write to a disabled area of bar1 or bar2,\n"
        "    when the mem area is disabled.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_NPI_PCI_INT_SUM2;
    info.status_mask        = 1ull<<33 /* ill_rd */;
    info.enable_addr        = CVMX_NPI_PCI_INT_ENB2;
    info.enable_mask        = 1ull<<33 /* ill_rd */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_PCI;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_INT_SUM;
    info.parent.status_mask = 1ull<<2 /* pci_rsl */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR NPI_PCI_INT_SUM2[ILL_RD]: A read to a disabled area of bar1 or bar2,\n"
        "    when the mem area is disabled.\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_GMXX_BAD_REG(0) */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_BAD_REG(0);
    info.status_mask        = 0x7ull<<2 /* out_ovr */;
    info.enable_addr        = 0;
    info.enable_mask        = 0;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_BAD_REG(0)[OUT_OVR]: Outbound data FIFO overflow (per port)\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_BAD_REG(0);
    info.status_mask        = 0x7ull<<22 /* loststat */;
    info.enable_addr        = 0;
    info.enable_mask        = 0;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_BAD_REG(0)[LOSTSTAT]: TX Statistics data was over-written (per RGM port)\n"
        "    TX Stats are corrupted\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_BAD_REG(0);
    info.status_mask        = 1ull<<26 /* statovr */;
    info.enable_addr        = 0;
    info.enable_mask        = 0;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_BAD_REG(0)[STATOVR]: TX Statistics overflow\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_BAD_REG(0);
    info.status_mask        = 0xfull<<27 /* inb_nxa */;
    info.enable_addr        = 0;
    info.enable_mask        = 0;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_BAD_REG(0)[INB_NXA]: Inbound port > GMX_RX_PRTS\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_GMXX_RXX_INT_REG(0,0) */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(0,0);
    info.status_mask        = 1ull<<1 /* carext */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(0,0);
    info.enable_mask        = 1ull<<1 /* carext */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(0,0)[CAREXT]: RGMII carrier extend error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(0,0);
    info.status_mask        = 1ull<<2 /* maxerr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(0,0);
    info.enable_mask        = 1ull<<2 /* maxerr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(0,0)[MAXERR]: Frame was received with length > max_length\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(0,0);
    info.status_mask        = 1ull<<5 /* alnerr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(0,0);
    info.enable_mask        = 1ull<<5 /* alnerr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(0,0)[ALNERR]: Frame was received with an alignment error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(0,0);
    info.status_mask        = 1ull<<6 /* lenerr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(0,0);
    info.enable_mask        = 1ull<<6 /* lenerr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(0,0)[LENERR]: Frame was received with length error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(0,0);
    info.status_mask        = 1ull<<8 /* skperr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(0,0);
    info.enable_mask        = 1ull<<8 /* skperr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(0,0)[SKPERR]: Skipper error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(0,0);
    info.status_mask        = 1ull<<9 /* niberr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(0,0);
    info.enable_mask        = 1ull<<9 /* niberr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(0,0)[NIBERR]: Nibble error (hi_nibble != lo_nibble)\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(0,0);
    info.status_mask        = 1ull<<10 /* ovrerr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(0,0);
    info.enable_mask        = 1ull<<10 /* ovrerr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(0,0)[OVRERR]: Internal Data Aggregation Overflow\n"
        "    This interrupt should never assert\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_GMXX_RXX_INT_REG(1,0) */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(1,0);
    info.status_mask        = 1ull<<1 /* carext */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(1,0);
    info.enable_mask        = 1ull<<1 /* carext */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 1;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(1,0)[CAREXT]: RGMII carrier extend error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(1,0);
    info.status_mask        = 1ull<<2 /* maxerr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(1,0);
    info.enable_mask        = 1ull<<2 /* maxerr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 1;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(1,0)[MAXERR]: Frame was received with length > max_length\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(1,0);
    info.status_mask        = 1ull<<5 /* alnerr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(1,0);
    info.enable_mask        = 1ull<<5 /* alnerr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 1;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(1,0)[ALNERR]: Frame was received with an alignment error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(1,0);
    info.status_mask        = 1ull<<6 /* lenerr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(1,0);
    info.enable_mask        = 1ull<<6 /* lenerr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 1;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(1,0)[LENERR]: Frame was received with length error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(1,0);
    info.status_mask        = 1ull<<8 /* skperr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(1,0);
    info.enable_mask        = 1ull<<8 /* skperr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 1;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(1,0)[SKPERR]: Skipper error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(1,0);
    info.status_mask        = 1ull<<9 /* niberr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(1,0);
    info.enable_mask        = 1ull<<9 /* niberr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 1;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(1,0)[NIBERR]: Nibble error (hi_nibble != lo_nibble)\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(1,0);
    info.status_mask        = 1ull<<10 /* ovrerr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(1,0);
    info.enable_mask        = 1ull<<10 /* ovrerr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 1;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(1,0)[OVRERR]: Internal Data Aggregation Overflow\n"
        "    This interrupt should never assert\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_GMXX_RXX_INT_REG(2,0) */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(2,0);
    info.status_mask        = 1ull<<1 /* carext */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(2,0);
    info.enable_mask        = 1ull<<1 /* carext */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 2;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(2,0)[CAREXT]: RGMII carrier extend error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(2,0);
    info.status_mask        = 1ull<<2 /* maxerr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(2,0);
    info.enable_mask        = 1ull<<2 /* maxerr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 2;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(2,0)[MAXERR]: Frame was received with length > max_length\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(2,0);
    info.status_mask        = 1ull<<5 /* alnerr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(2,0);
    info.enable_mask        = 1ull<<5 /* alnerr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 2;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(2,0)[ALNERR]: Frame was received with an alignment error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(2,0);
    info.status_mask        = 1ull<<6 /* lenerr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(2,0);
    info.enable_mask        = 1ull<<6 /* lenerr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 2;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(2,0)[LENERR]: Frame was received with length error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(2,0);
    info.status_mask        = 1ull<<8 /* skperr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(2,0);
    info.enable_mask        = 1ull<<8 /* skperr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 2;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(2,0)[SKPERR]: Skipper error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(2,0);
    info.status_mask        = 1ull<<9 /* niberr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(2,0);
    info.enable_mask        = 1ull<<9 /* niberr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 2;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(2,0)[NIBERR]: Nibble error (hi_nibble != lo_nibble)\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_RXX_INT_REG(2,0);
    info.status_mask        = 1ull<<10 /* ovrerr */;
    info.enable_addr        = CVMX_GMXX_RXX_INT_EN(2,0);
    info.enable_mask        = 1ull<<10 /* ovrerr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 2;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_RXX_INT_REG(2,0)[OVRERR]: Internal Data Aggregation Overflow\n"
        "    This interrupt should never assert\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_GMXX_TX_INT_REG(0) */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_TX_INT_REG(0);
    info.status_mask        = 1ull<<0 /* pko_nxa */;
    info.enable_addr        = CVMX_GMXX_TX_INT_EN(0);
    info.enable_mask        = 1ull<<0 /* pko_nxa */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_TX_INT_REG(0)[PKO_NXA]: Port address out-of-range from PKO Interface\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_GMXX_TX_INT_REG(0);
    info.status_mask        = 0x7ull<<2 /* undflw */;
    info.enable_addr        = CVMX_GMXX_TX_INT_EN(0);
    info.enable_mask        = 0x7ull<<2 /* undflw */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<1 /* gmx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR GMXX_TX_INT_REG(0)[UNDFLW]: TX Underflow (RGMII mode only)\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_MIO_BOOT_ERR */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_MIO_BOOT_ERR;
    info.status_mask        = 1ull<<0 /* adr_err */;
    info.enable_addr        = CVMX_MIO_BOOT_INT;
    info.enable_mask        = 1ull<<0 /* adr_int */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<0 /* mio */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR MIO_BOOT_ERR[ADR_ERR]: Address decode error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_MIO_BOOT_ERR;
    info.status_mask        = 1ull<<1 /* wait_err */;
    info.enable_addr        = CVMX_MIO_BOOT_INT;
    info.enable_mask        = 1ull<<1 /* wait_int */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<0 /* mio */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR MIO_BOOT_ERR[WAIT_ERR]: Wait mode error\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_IPD_INT_SUM */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_IPD_INT_SUM;
    info.status_mask        = 1ull<<0 /* prc_par0 */;
    info.enable_addr        = CVMX_IPD_INT_ENB;
    info.enable_mask        = 1ull<<0 /* prc_par0 */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<9 /* ipd */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR IPD_INT_SUM[PRC_PAR0]: Set when a parity error is dected for bits\n"
        "    [31:0] of the PBM memory.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_IPD_INT_SUM;
    info.status_mask        = 1ull<<1 /* prc_par1 */;
    info.enable_addr        = CVMX_IPD_INT_ENB;
    info.enable_mask        = 1ull<<1 /* prc_par1 */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<9 /* ipd */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR IPD_INT_SUM[PRC_PAR1]: Set when a parity error is dected for bits\n"
        "    [63:32] of the PBM memory.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_IPD_INT_SUM;
    info.status_mask        = 1ull<<2 /* prc_par2 */;
    info.enable_addr        = CVMX_IPD_INT_ENB;
    info.enable_mask        = 1ull<<2 /* prc_par2 */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<9 /* ipd */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR IPD_INT_SUM[PRC_PAR2]: Set when a parity error is dected for bits\n"
        "    [95:64] of the PBM memory.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_IPD_INT_SUM;
    info.status_mask        = 1ull<<3 /* prc_par3 */;
    info.enable_addr        = CVMX_IPD_INT_ENB;
    info.enable_mask        = 1ull<<3 /* prc_par3 */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<9 /* ipd */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR IPD_INT_SUM[PRC_PAR3]: Set when a parity error is dected for bits\n"
        "    [127:96] of the PBM memory.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_IPD_INT_SUM;
    info.status_mask        = 1ull<<4 /* bp_sub */;
    info.enable_addr        = CVMX_IPD_INT_ENB;
    info.enable_mask        = 1ull<<4 /* bp_sub */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<9 /* ipd */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR IPD_INT_SUM[BP_SUB]: Set when a backpressure subtract is done with a\n"
        "    supplied illegal value.\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_POW_ECC_ERR */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_POW_ECC_ERR;
    info.status_mask        = 1ull<<0 /* sbe */;
    info.enable_addr        = CVMX_POW_ECC_ERR;
    info.enable_mask        = 1ull<<2 /* sbe_ie */;
    info.flags              = CVMX_ERROR_TYPE_SBE;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<12 /* pow */;
    info.func               = __cvmx_error_handle_pow_ecc_err_sbe;
    info.user_info          = (long)
        "ERROR POW_ECC_ERR[SBE]: Single bit error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_POW_ECC_ERR;
    info.status_mask        = 1ull<<1 /* dbe */;
    info.enable_addr        = CVMX_POW_ECC_ERR;
    info.enable_mask        = 1ull<<3 /* dbe_ie */;
    info.flags              = CVMX_ERROR_TYPE_DBE;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<12 /* pow */;
    info.func               = __cvmx_error_handle_pow_ecc_err_dbe;
    info.user_info          = (long)
        "ERROR POW_ECC_ERR[DBE]: Double bit error\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_POW_ECC_ERR;
    info.status_mask        = 1ull<<12 /* rpe */;
    info.enable_addr        = CVMX_POW_ECC_ERR;
    info.enable_mask        = 1ull<<13 /* rpe_ie */;
    info.flags              = CVMX_ERROR_TYPE_DBE;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<12 /* pow */;
    info.func               = __cvmx_error_handle_pow_ecc_err_rpe;
    info.user_info          = (long)
        "ERROR POW_ECC_ERR[RPE]: Remote pointer error\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_ASXX_INT_REG(0) */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_ASXX_INT_REG(0);
    info.status_mask        = 0x7ull<<0 /* ovrflw */;
    info.enable_addr        = CVMX_ASXX_INT_EN(0);
    info.enable_mask        = 0x7ull<<0 /* ovrflw */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<22 /* asx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR ASXX_INT_REG(0)[OVRFLW]: RX FIFO overflow on RMGII port\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_ASXX_INT_REG(0);
    info.status_mask        = 0x7ull<<4 /* txpop */;
    info.enable_addr        = CVMX_ASXX_INT_EN(0);
    info.enable_mask        = 0x7ull<<4 /* txpop */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<22 /* asx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR ASXX_INT_REG(0)[TXPOP]: TX FIFO underflow on RMGII port\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_ASXX_INT_REG(0);
    info.status_mask        = 0x7ull<<8 /* txpsh */;
    info.enable_addr        = CVMX_ASXX_INT_EN(0);
    info.enable_mask        = 0x7ull<<8 /* txpsh */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_ETHERNET;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<22 /* asx0 */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR ASXX_INT_REG(0)[TXPSH]: TX FIFO overflow on RMGII port\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_PKO_REG_ERROR */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_PKO_REG_ERROR;
    info.status_mask        = 1ull<<0 /* parity */;
    info.enable_addr        = CVMX_PKO_REG_INT_MASK;
    info.enable_mask        = 1ull<<0 /* parity */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<10 /* pko */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR PKO_REG_ERROR[PARITY]: Read parity error at port data buffer\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_PKO_REG_ERROR;
    info.status_mask        = 1ull<<1 /* doorbell */;
    info.enable_addr        = CVMX_PKO_REG_INT_MASK;
    info.enable_mask        = 1ull<<1 /* doorbell */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<10 /* pko */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR PKO_REG_ERROR[DOORBELL]: A doorbell count has overflowed\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_TIM_REG_ERROR */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_TIM_REG_ERROR;
    info.status_mask        = 0xffffull<<0 /* mask */;
    info.enable_addr        = CVMX_TIM_REG_INT_MASK;
    info.enable_mask        = 0xffffull<<0 /* mask */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<11 /* tim */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR TIM_REG_ERROR[MASK]: Bit mask indicating the rings in error\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_ZIP_ERROR */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_ZIP_ERROR;
    info.status_mask        = 1ull<<0 /* doorbell */;
    info.enable_addr        = CVMX_ZIP_INT_MASK;
    info.enable_mask        = 1ull<<0 /* doorbell */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<7 /* zip */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR ZIP_ERROR[DOORBELL]: A doorbell count has overflowed\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_PIP_INT_REG */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_PIP_INT_REG;
    info.status_mask        = 1ull<<3 /* prtnxa */;
    info.enable_addr        = CVMX_PIP_INT_EN;
    info.enable_mask        = 1ull<<3 /* prtnxa */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<20 /* pip */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR PIP_INT_REG[PRTNXA]: Non-existent port\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_PIP_INT_REG;
    info.status_mask        = 1ull<<4 /* badtag */;
    info.enable_addr        = CVMX_PIP_INT_EN;
    info.enable_mask        = 1ull<<4 /* badtag */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<20 /* pip */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR PIP_INT_REG[BADTAG]: A bad tag was sent from IPD\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_PIP_INT_REG;
    info.status_mask        = 1ull<<5 /* skprunt */;
    info.enable_addr        = CVMX_PIP_INT_EN;
    info.enable_mask        = 1ull<<5 /* skprunt */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<20 /* pip */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR PIP_INT_REG[SKPRUNT]: Packet was engulfed by skipper\n"
        "    This interrupt can occur with received PARTIAL\n"
        "    packets that are truncated to SKIP bytes or\n"
        "    smaller.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_PIP_INT_REG;
    info.status_mask        = 1ull<<6 /* todoovr */;
    info.enable_addr        = CVMX_PIP_INT_EN;
    info.enable_mask        = 1ull<<6 /* todoovr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<20 /* pip */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR PIP_INT_REG[TODOOVR]: Todo list overflow\n"
        "    (not used in O2P)\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_PIP_INT_REG;
    info.status_mask        = 1ull<<7 /* feperr */;
    info.enable_addr        = CVMX_PIP_INT_EN;
    info.enable_mask        = 1ull<<7 /* feperr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<20 /* pip */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR PIP_INT_REG[FEPERR]: Parity Error in front end memory\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_PIP_INT_REG;
    info.status_mask        = 1ull<<8 /* beperr */;
    info.enable_addr        = CVMX_PIP_INT_EN;
    info.enable_mask        = 1ull<<8 /* beperr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<20 /* pip */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR PIP_INT_REG[BEPERR]: Parity Error in back end memory\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_FPA_INT_SUM */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<0 /* fed0_sbe */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<0 /* fed0_sbe */;
    info.flags              = CVMX_ERROR_TYPE_SBE;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[FED0_SBE]: Set when a Single Bit Error is detected in FPF0.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<1 /* fed0_dbe */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<1 /* fed0_dbe */;
    info.flags              = CVMX_ERROR_TYPE_DBE;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[FED0_DBE]: Set when a Double Bit Error is detected in FPF0.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<2 /* fed1_sbe */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<2 /* fed1_sbe */;
    info.flags              = CVMX_ERROR_TYPE_SBE;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[FED1_SBE]: Set when a Single Bit Error is detected in FPF1.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<3 /* fed1_dbe */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<3 /* fed1_dbe */;
    info.flags              = CVMX_ERROR_TYPE_DBE;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[FED1_DBE]: Set when a Double Bit Error is detected in FPF1.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<4 /* q0_und */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<4 /* q0_und */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q0_UND]: Set when a Queue0 page count available goes\n"
        "    negative.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<5 /* q0_coff */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<5 /* q0_coff */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q0_COFF]: Set when a Queue0 stack end tag is present and\n"
        "    the count available is greater than pointers\n"
        "    present in the FPA.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<6 /* q0_perr */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<6 /* q0_perr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q0_PERR]: Set when a Queue0 pointer read from the stack in\n"
        "    the L2C does not have the FPA owner ship bit set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<7 /* q1_und */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<7 /* q1_und */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q1_UND]: Set when a Queue0 page count available goes\n"
        "    negative.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<8 /* q1_coff */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<8 /* q1_coff */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q1_COFF]: Set when a Queue0 stack end tag is present and\n"
        "    the count available is greater than pointers\n"
        "    present in the FPA.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<9 /* q1_perr */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<9 /* q1_perr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q1_PERR]: Set when a Queue0 pointer read from the stack in\n"
        "    the L2C does not have the FPA owner ship bit set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<10 /* q2_und */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<10 /* q2_und */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q2_UND]: Set when a Queue0 page count available goes\n"
        "    negative.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<11 /* q2_coff */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<11 /* q2_coff */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q2_COFF]: Set when a Queue0 stack end tag is present and\n"
        "    the count available is greater than than pointers\n"
        "    present in the FPA.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<12 /* q2_perr */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<12 /* q2_perr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q2_PERR]: Set when a Queue0 pointer read from the stack in\n"
        "    the L2C does not have the FPA owner ship bit set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<13 /* q3_und */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<13 /* q3_und */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q3_UND]: Set when a Queue0 page count available goes\n"
        "    negative.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<14 /* q3_coff */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<14 /* q3_coff */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q3_COFF]: Set when a Queue0 stack end tag is present and\n"
        "    the count available is greater than than pointers\n"
        "    present in the FPA.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<15 /* q3_perr */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<15 /* q3_perr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q3_PERR]: Set when a Queue0 pointer read from the stack in\n"
        "    the L2C does not have the FPA owner ship bit set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<16 /* q4_und */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<16 /* q4_und */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q4_UND]: Set when a Queue0 page count available goes\n"
        "    negative.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<17 /* q4_coff */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<17 /* q4_coff */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q4_COFF]: Set when a Queue0 stack end tag is present and\n"
        "    the count available is greater than than pointers\n"
        "    present in the FPA.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<18 /* q4_perr */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<18 /* q4_perr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q4_PERR]: Set when a Queue0 pointer read from the stack in\n"
        "    the L2C does not have the FPA owner ship bit set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<19 /* q5_und */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<19 /* q5_und */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q5_UND]: Set when a Queue0 page count available goes\n"
        "    negative.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<20 /* q5_coff */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<20 /* q5_coff */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q5_COFF]: Set when a Queue0 stack end tag is present and\n"
        "    the count available is greater than than pointers\n"
        "    present in the FPA.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<21 /* q5_perr */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<21 /* q5_perr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q5_PERR]: Set when a Queue0 pointer read from the stack in\n"
        "    the L2C does not have the FPA owner ship bit set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<22 /* q6_und */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<22 /* q6_und */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q6_UND]: Set when a Queue0 page count available goes\n"
        "    negative.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<23 /* q6_coff */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<23 /* q6_coff */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q6_COFF]: Set when a Queue0 stack end tag is present and\n"
        "    the count available is greater than than pointers\n"
        "    present in the FPA.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<24 /* q6_perr */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<24 /* q6_perr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q6_PERR]: Set when a Queue0 pointer read from the stack in\n"
        "    the L2C does not have the FPA owner ship bit set.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<25 /* q7_und */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<25 /* q7_und */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q7_UND]: Set when a Queue0 page count available goes\n"
        "    negative.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<26 /* q7_coff */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<26 /* q7_coff */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q7_COFF]: Set when a Queue0 stack end tag is present and\n"
        "    the count available is greater than than pointers\n"
        "    present in the FPA.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_FPA_INT_SUM;
    info.status_mask        = 1ull<<27 /* q7_perr */;
    info.enable_addr        = CVMX_FPA_INT_ENB;
    info.enable_mask        = 1ull<<27 /* q7_perr */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<5 /* fpa */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR FPA_INT_SUM[Q7_PERR]: Set when a Queue0 pointer read from the stack in\n"
        "    the L2C does not have the FPA owner ship bit set.\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_LMCX_MEM_CFG0(0) */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_LMCX_MEM_CFG0(0);
    info.status_mask        = 0xfull<<21 /* sec_err */;
    info.enable_addr        = CVMX_LMCX_MEM_CFG0(0);
    info.enable_mask        = 1ull<<19 /* intr_sec_ena */;
    info.flags              = CVMX_ERROR_TYPE_SBE;
    info.group              = CVMX_ERROR_GROUP_LMC;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<17 /* lmc */;
    info.func               = __cvmx_error_handle_lmcx_mem_cfg0_sec_err;
    info.user_info          = (long)
        "ERROR LMCX_MEM_CFG0(0)[SEC_ERR]: Single Error (corrected) of Rd Data\n"
        "    In 64b mode, ecc is calculated on 2 cycle worth of data\n"
        "    [0] corresponds to DQ[63:0]_c0_p0\n"
        "    [1] corresponds to DQ[63:0]_c0_p1\n"
        "    [2] corresponds to DQ[63:0]_c1_p0\n"
        "    [3] corresponds to DQ[63:0]_c1_p1\n"
        "    In 32b mode, ecc is calculated on 4 cycle worth of data\n"
        "    [0] corresponds to [DQ[31:0]_c0_p1, DQ[31:0]_c0_p0]\n"
        "    [1] corresponds to [DQ[31:0]_c1_p1, DQ[31:0]_c1_p0]\n"
        "    [2] corresponds to [DQ[31:0]_c2_p1, DQ[31:0]_c2_p0]\n"
        "    [3] corresponds to [DQ[31:0]_c3_p1, DQ[31:0]_c3_p0]\n"
        "      where _cC_pP denotes cycle C and phase P\n"
        "    Write of 1 will clear the corresponding error bit\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_LMCX_MEM_CFG0(0);
    info.status_mask        = 0xfull<<25 /* ded_err */;
    info.enable_addr        = CVMX_LMCX_MEM_CFG0(0);
    info.enable_mask        = 1ull<<20 /* intr_ded_ena */;
    info.flags              = CVMX_ERROR_TYPE_DBE;
    info.group              = CVMX_ERROR_GROUP_LMC;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<17 /* lmc */;
    info.func               = __cvmx_error_handle_lmcx_mem_cfg0_ded_err;
    info.user_info          = (long)
        "ERROR LMCX_MEM_CFG0(0)[DED_ERR]: Double Error detected (DED) of Rd Data\n"
        "    In 64b mode, ecc is calculated on 2 cycle worth of data\n"
        "    [0] corresponds to DQ[63:0]_c0_p0\n"
        "    [1] corresponds to DQ[63:0]_c0_p1\n"
        "    [2] corresponds to DQ[63:0]_c1_p0\n"
        "    [3] corresponds to DQ[63:0]_c1_p1\n"
        "    In 32b mode, ecc is calculated on 4 cycle worth of data\n"
        "    [0] corresponds to [DQ[31:0]_c0_p1, DQ[31:0]_c0_p0]\n"
        "    [1] corresponds to [DQ[31:0]_c1_p1, DQ[31:0]_c1_p0]\n"
        "    [2] corresponds to [DQ[31:0]_c2_p1, DQ[31:0]_c2_p0]\n"
        "    [3] corresponds to [DQ[31:0]_c3_p1, DQ[31:0]_c3_p0]\n"
        "      where _cC_pP denotes cycle C and phase P\n"
        "    Write of 1 will clear the corresponding error bit\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_DFA_ERR */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_DFA_ERR;
    info.status_mask        = 1ull<<1 /* cp2sbe */;
    info.enable_addr        = 0;
    info.enable_mask        = 0;
    info.flags              = CVMX_ERROR_TYPE_SBE;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<6 /* dfa */;
    info.func               = __cvmx_error_handle_dfa_err_cp2sbe;
    info.user_info          = (long)
        "ERROR DFA_ERR[CP2SBE]: PP-CP2 Single Bit Error Corrected - Status bit\n"
        "    When set, a single bit error had been detected and\n"
        "    corrected for a PP-generated QW Mode read\n"
        "    transaction.\n"
        "    If the CP2DBE=0, then the CP2SYN contains the\n"
        "    failing syndrome (used during correction).\n"
        "    Refer to CP2ECCENA.\n"
        "    If the CP2SBINA had previously been enabled(set),\n"
        "    an interrupt will be posted. Software can clear\n"
        "    the interrupt by writing a 1 to this register bit.\n"
        "    See also: DFA_MEMFADR CSR which contains more data\n"
        "    about the memory address/control to help isolate\n"
        "    the failure.\n"
        "    NOTE: PP-generated LW Mode Read transactions\n"
        "    do not participate in ECC check/correct).\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_DFA_ERR;
    info.status_mask        = 1ull<<2 /* cp2dbe */;
    info.enable_addr        = 0;
    info.enable_mask        = 0;
    info.flags              = CVMX_ERROR_TYPE_DBE;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<6 /* dfa */;
    info.func               = __cvmx_error_handle_dfa_err_cp2dbe;
    info.user_info          = (long)
        "ERROR DFA_ERR[CP2DBE]: PP-CP2 Double Bit Error Detected - Status bit\n"
        "    When set, a double bit error had been detected\n"
        "    for a PP-generated QW Mode read transaction.\n"
        "    The CP2SYN contains the failing syndrome.\n"
        "     NOTE: PP-generated LW Mode Read transactions\n"
        "    do not participate in ECC check/correct).\n"
        "    Refer to CP2ECCENA.\n"
        "    If the CP2DBINA had previously been enabled(set),\n"
        "    an interrupt will be posted. Software can clear\n"
        "    the interrupt by writing a 1 to this register bit.\n"
        "    See also: DFA_MEMFADR CSR which contains more data\n"
        "    about the memory address/control to help isolate\n"
        "    the failure.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_DFA_ERR;
    info.status_mask        = 1ull<<14 /* dtesbe */;
    info.enable_addr        = 0;
    info.enable_mask        = 0;
    info.flags              = CVMX_ERROR_TYPE_SBE;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<6 /* dfa */;
    info.func               = __cvmx_error_handle_dfa_err_dtesbe;
    info.user_info          = (long)
        "ERROR DFA_ERR[DTESBE]: DTE 25b Single Bit Error Corrected - Status bit\n"
        "    When set, a single bit error had been detected and\n"
        "    corrected for a DTE-generated 32b SIMPLE Mode read\n"
        "    transaction.\n"
        "    If the DTEDBE=0, then the DTESYN contains the\n"
        "    failing syndrome (used during correction).\n"
        "    NOTE: DTE-generated 16b SIMPLE Mode Read\n"
        "    transactions do not participate in ECC check/correct).\n"
        "    If the DTESBINA had previously been enabled(set),\n"
        "    an interrupt will be posted. Software can clear\n"
        "    the interrupt by writing a 1 to this register bit.\n"
        "    See also: DFA_MEMFADR CSR which contains more data\n"
        "    about the memory address/control to help isolate\n"
        "    the failure.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_DFA_ERR;
    info.status_mask        = 1ull<<15 /* dtedbe */;
    info.enable_addr        = 0;
    info.enable_mask        = 0;
    info.flags              = CVMX_ERROR_TYPE_DBE;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<6 /* dfa */;
    info.func               = __cvmx_error_handle_dfa_err_dtedbe;
    info.user_info          = (long)
        "ERROR DFA_ERR[DTEDBE]: DTE 25b Double Bit Error Detected - Status bit\n"
        "    When set, a double bit error had been detected\n"
        "    for a DTE-generated 32b SIMPLE Mode read transaction.\n"
        "    The DTESYN contains the failing syndrome.\n"
        "    If the DTEDBINA had previously been enabled(set),\n"
        "    an interrupt will be posted. Software can clear\n"
        "    the interrupt by writing a 1 to this register bit.\n"
        "    See also: DFA_MEMFADR CSR which contains more data\n"
        "    about the memory address/control to help isolate\n"
        "    the failure.\n"
        "    NOTE: DTE-generated 16b SIMPLE Mode Read transactions\n"
        "    do not participate in ECC check/correct).\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_DFA_ERR;
    info.status_mask        = 1ull<<26 /* dteperr */;
    info.enable_addr        = 0;
    info.enable_mask        = 0;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<6 /* dfa */;
    info.func               = __cvmx_error_handle_dfa_err_dteperr;
    info.user_info          = (long)
        "ERROR DFA_ERR[DTEPERR]: DTE Parity Error Detected (for 16b SIMPLE mode ONLY)\n"
        "    When set, all DTE-generated 16b SIMPLE Mode read\n"
        "    transactions which encounter a parity error (across\n"
        "    the 17b of data) are reported.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_DFA_ERR;
    info.status_mask        = 1ull<<29 /* cp2perr */;
    info.enable_addr        = 0;
    info.enable_mask        = 0;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<6 /* dfa */;
    info.func               = __cvmx_error_handle_dfa_err_cp2perr;
    info.user_info          = (long)
        "ERROR DFA_ERR[CP2PERR]: PP-CP2 Parity Error Detected - Status bit\n"
        "    When set, a parity error had been detected for a\n"
        "    PP-generated LW Mode read transaction.\n"
        "    If the CP2PINA had previously been enabled(set),\n"
        "    an interrupt will be posted. Software can clear\n"
        "    the interrupt by writing a 1 to this register bit.\n"
        "    See also: DFA_MEMFADR CSR which contains more data\n"
        "    about the memory address/control to help isolate\n"
        "    the failure.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_DFA_ERR;
    info.status_mask        = 1ull<<31 /* dblovf */;
    info.enable_addr        = 0;
    info.enable_mask        = 0;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<6 /* dfa */;
    info.func               = __cvmx_error_handle_dfa_err_dblovf;
    info.user_info          = (long)
        "ERROR DFA_ERR[DBLOVF]: Doorbell Overflow detected - Status bit\n"
        "    When set, the 20b accumulated doorbell register\n"
        "    had overflowed (SW wrote too many doorbell requests).\n"
        "    If the DBLINA had previously been enabled(set),\n"
        "    an interrupt will be posted. Software can clear\n"
        "    the interrupt by writing a 1 to this register bit.\n"
        "    NOTE: Detection of a Doorbell Register overflow\n"
        "    is a catastrophic error which may leave the DFA\n"
        "    HW in an unrecoverable state.\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_IOB_INT_SUM */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_IOB_INT_SUM;
    info.status_mask        = 1ull<<0 /* np_sop */;
    info.enable_addr        = CVMX_IOB_INT_ENB;
    info.enable_mask        = 1ull<<0 /* np_sop */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<30 /* iob */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR IOB_INT_SUM[NP_SOP]: Set when a SOP is followed by an SOP for the same\n"
        "    port for a non-passthrough packet.\n"
        "    The first detected error associated with bits [3:0]\n"
        "    of this register will only be set here. A new bit\n"
        "    can be set when the previous reported bit is cleared.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_IOB_INT_SUM;
    info.status_mask        = 1ull<<1 /* np_eop */;
    info.enable_addr        = CVMX_IOB_INT_ENB;
    info.enable_mask        = 1ull<<1 /* np_eop */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<30 /* iob */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR IOB_INT_SUM[NP_EOP]: Set when a EOP is followed by an EOP for the same\n"
        "    port for a non-passthrough packet.\n"
        "    The first detected error associated with bits [3:0]\n"
        "    of this register will only be set here. A new bit\n"
        "    can be set when the previous reported bit is cleared.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_IOB_INT_SUM;
    info.status_mask        = 1ull<<2 /* p_sop */;
    info.enable_addr        = CVMX_IOB_INT_ENB;
    info.enable_mask        = 1ull<<2 /* p_sop */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<30 /* iob */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR IOB_INT_SUM[P_SOP]: Set when a SOP is followed by an SOP for the same\n"
        "    port for a passthrough packet.\n"
        "    The first detected error associated with bits [3:0]\n"
        "    of this register will only be set here. A new bit\n"
        "    can be set when the previous reported bit is cleared.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_IOB_INT_SUM;
    info.status_mask        = 1ull<<3 /* p_eop */;
    info.enable_addr        = CVMX_IOB_INT_ENB;
    info.enable_mask        = 1ull<<3 /* p_eop */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_INTERNAL;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<30 /* iob */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR IOB_INT_SUM[P_EOP]: Set when a EOP is followed by an EOP for the same\n"
        "    port for a passthrough packet.\n"
        "    The first detected error associated with bits [3:0]\n"
        "    of this register will only be set here. A new bit\n"
        "    can be set when the previous reported bit is cleared.\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_USBNX_INT_SUM(0) */
    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<0 /* pr_po_e */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<0 /* pr_po_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[PR_PO_E]: PP  Request Fifo Popped When Empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<1 /* pr_pu_f */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<1 /* pr_pu_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[PR_PU_F]: PP  Request Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<2 /* nr_po_e */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<2 /* nr_po_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[NR_PO_E]: NPI Request Fifo Popped When Empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<3 /* nr_pu_f */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<3 /* nr_pu_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[NR_PU_F]: NPI Request Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<4 /* lr_po_e */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<4 /* lr_po_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[LR_PO_E]: L2C Request Fifo Popped When Empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<5 /* lr_pu_f */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<5 /* lr_pu_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[LR_PU_F]: L2C Request Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<6 /* pt_po_e */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<6 /* pt_po_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[PT_PO_E]: PP  Trasaction Fifo Popped When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<7 /* pt_pu_f */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<7 /* pt_pu_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[PT_PU_F]: PP  Trasaction Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<8 /* nt_po_e */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<8 /* nt_po_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[NT_PO_E]: NPI Trasaction Fifo Popped When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<9 /* nt_pu_f */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<9 /* nt_pu_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[NT_PU_F]: NPI Trasaction Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<10 /* lt_po_e */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<10 /* lt_po_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[LT_PO_E]: L2C Trasaction Fifo Popped When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<11 /* lt_pu_f */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<11 /* lt_pu_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[LT_PU_F]: L2C Trasaction Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<12 /* dcred_e */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<12 /* dcred_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[DCRED_E]: Data Credit Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<13 /* dcred_f */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<13 /* dcred_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[DCRED_F]: Data CreditFifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<14 /* l2c_s_e */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<14 /* l2c_s_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[L2C_S_E]: L2C Credit Count Subtracted When Empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<15 /* l2c_a_f */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<15 /* l2c_a_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[L2C_A_F]: L2C Credit Count Added When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<16 /* lt_fi_e */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<16 /* l2_fi_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[LT_FI_E]: L2C Request Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<17 /* lt_fi_f */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<17 /* l2_fi_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[LT_FI_F]: L2C Request Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<18 /* rg_fi_e */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<18 /* rg_fi_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[RG_FI_E]: Register Request Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<19 /* rg_fi_f */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<19 /* rg_fi_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[RG_FI_F]: Register Request Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<20 /* rq_q2_f */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<20 /* rq_q2_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[RQ_Q2_F]: Request Queue-2 Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<21 /* rq_q2_e */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<21 /* rq_q2_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[RQ_Q2_E]: Request Queue-2 Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<22 /* rq_q3_f */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<22 /* rq_q3_f */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[RQ_Q3_F]: Request Queue-3 Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<23 /* rq_q3_e */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<23 /* rq_q3_e */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[RQ_Q3_E]: Request Queue-3 Fifo Pushed When Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<24 /* uod_pe */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<24 /* uod_pe */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[UOD_PE]: UOD Fifo Pop Empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<25 /* uod_pf */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<25 /* uod_pf */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[UOD_PF]: UOD Fifo Push Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<26 /* n2u_pf */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<26 /* n2u_pf */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[N2U_PF]: N2U Fifo Push Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<27 /* n2u_pe */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<27 /* n2u_pe */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[N2U_PE]: N2U Fifo Pop Empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<28 /* u2n_d_pe */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<28 /* u2n_d_pe */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[U2N_D_PE]: U2N Data Fifo Pop Empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<29 /* u2n_d_pf */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<29 /* u2n_d_pf */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[U2N_D_PF]: U2N Data Fifo Push Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<30 /* u2n_c_pf */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<30 /* u2n_c_pf */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[U2N_C_PF]: U2N Control Fifo Push Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<31 /* u2n_c_pe */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<31 /* u2n_c_pe */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[U2N_C_PE]: U2N Control Fifo Pop Empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<32 /* ltl_f_pe */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<32 /* ltl_f_pe */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[LTL_F_PE]: L2C Transfer Length Fifo Pop Empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<33 /* ltl_f_pf */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<33 /* ltl_f_pf */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[LTL_F_PF]: L2C Transfer Length Fifo Push Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<34 /* nd4o_rpe */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<34 /* nd4o_rpe */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[ND4O_RPE]: NCB DMA Out Request Fifo Pop Empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<35 /* nd4o_rpf */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<35 /* nd4o_rpf */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[ND4O_RPF]: NCB DMA Out Request Fifo Push Full.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<36 /* nd4o_dpe */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<36 /* nd4o_dpe */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[ND4O_DPE]: NCB DMA Out Data Fifo Pop Empty.\n";
    fail |= cvmx_error_add(&info);

    info.reg_type           = CVMX_ERROR_REGISTER_IO64;
    info.status_addr        = CVMX_USBNX_INT_SUM(0);
    info.status_mask        = 1ull<<37 /* nd4o_dpf */;
    info.enable_addr        = CVMX_USBNX_INT_ENB(0);
    info.enable_mask        = 1ull<<37 /* nd4o_dpf */;
    info.flags              = 0;
    info.group              = CVMX_ERROR_GROUP_USB;
    info.group_index        = 0;
    info.parent.reg_type    = CVMX_ERROR_REGISTER_IO64;
    info.parent.status_addr = CVMX_NPI_RSL_INT_BLOCKS;
    info.parent.status_mask = 1ull<<13 /* usb */;
    info.func               = __cvmx_error_display;
    info.user_info          = (long)
        "ERROR USBNX_INT_SUM(0)[ND4O_DPF]: NCB DMA Out Data Fifo Push Full.\n";
    fail |= cvmx_error_add(&info);

    /* CVMX_CIU_INT_SUM1 */
    return fail;
}

