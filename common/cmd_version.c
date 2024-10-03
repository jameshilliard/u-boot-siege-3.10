/*
 * Copyright 2000-2009
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <version.h>
#include <linux/compiler.h>
#ifdef CONFIG_SYS_COREBOOT
#include <asm/arch/sysinfo.h>
#endif

const char __weak version_string[] = U_BOOT_VERSION_STRING;
#ifdef CONFIG_SRX_SIEGE
void print_cavium_licence()
{
    printf("\nParts of this binary are covered by this Cavium license :\n");

    printf("/***********************license start***************\n");
    printf(" * Copyright (c) 2013  Cavium Inc. (support@cavium.com). All rights\n");
    printf(" * reserved.\n");
    printf(" *\n");
    printf(" *\n");
    printf(" * Redistribution and use in source and binary forms, with or without\n");
    printf(" * modification, are permitted provided that the following conditions are\n");
    printf(" * met:\n");
    printf(" *\n");
    printf(" *   * Redistributions of source code must retain the above copyright\n");
    printf(" *     notice, this list of conditions and the following disclaimer.\n");
    printf(" *\n");
    printf(" *   * Redistributions in binary form must reproduce the above\n");
    printf(" *     copyright notice, this list of conditions and the following\n");
    printf(" *     disclaimer in the documentation and/or other materials provided\n");
    printf(" *     with the distribution.\n");
    printf("\n");
    printf(" *   * Neither the name of Cavium Inc. nor the names of\n");
    printf(" *     its contributors may be used to endorse or promote products\n");
    printf(" *     derived from this software without specific prior written\n");
    printf(" *     permission.\n");
    printf("\n");
    printf(" * This Software, including technical data, may be subject to U.S. export  control\n");
    printf(" * laws, including the U.S. Export Administration Act and its  associated\n");
    printf(" * regulations, and may be subject to export or import  regulations in other\n");
    printf(" * countries.\n");
    printf("\n");
    printf(" * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED \"AS IS\"\n");
    printf(" * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR\n");
    printf(" * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO\n");
    printf(" * THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY REPRESENTATION OR\n");
    printf(" * DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT DEFECTS, AND CAVIUM\n");
    printf(" * SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES OF TITLE,\n");
    printf(" * MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF\n");
    printf(" * VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR\n");
    printf(" * CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK ARISING OUT OF USE OR\n");
    printf(" * PERFORMANCE OF THE SOFTWARE LIES WITH YOU.\n");
    printf(" ***********************license end**************************************/\n");
}
#endif

static int do_version(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	printf("\n%s\n", version_string);
#ifdef CC_VERSION_STRING
	puts(CC_VERSION_STRING "\n");
#endif
#ifdef LD_VERSION_STRING
	puts(LD_VERSION_STRING "\n");
#endif
#ifdef CONFIG_SYS_COREBOOT
	printf("coreboot-%s (%s)\n", lib_sysinfo.version, lib_sysinfo.build);
#endif

#ifdef CONFIG_SRX_SIEGE
    print_cavium_licence();
#endif
	return 0;
}

U_BOOT_CMD(
	version,	1,		1,	do_version,
	"print monitor, compiler and linker version",
	""
);
