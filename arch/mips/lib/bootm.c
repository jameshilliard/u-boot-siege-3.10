/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <image.h>
#include <u-boot/zlib.h>
#include <asm/byteorder.h>
#include <asm/addrspace.h>

DECLARE_GLOBAL_DATA_PTR;

#define	LINUX_MAX_ENVS		256
#define	LINUX_MAX_ARGS		256

static int linux_argc;
static char **linux_argv;

static char **linux_env;
static char *linux_env_p;
static int linux_env_idx;

static void linux_params_init(ulong start, char *commandline);
static void linux_env_set(char *env_name, char *env_val);

static void boot_prep_linux(bootm_headers_t *images)
{
	char *commandline = getenv("bootargs");
	char env_buf[12];
	char *cp;

#ifdef DEBUG
	void (*theKernel) (int, char **, char **, int *);

	/* find kernel entry point */
	theKernel = (void (*)(int, char **, char **, int *))images->ep;
	printf("## Transferring control to Linux (at address %08lx) ...\n",
		(ulong) theKernel);
#endif

#ifndef CONFIG_OCTEON
	linux_params_init(UNCACHED_SDRAM(gd->bd->bi_boot_params), commandline);
#else
	linux_params_init (gd->bd->bi_boot_params, commandline);
#endif

#ifdef CONFIG_MEMSIZE_IN_BYTES
	sprintf(env_buf, "%lu", (ulong)gd->ram_size);
	debug("## Giving linux memsize in bytes, %lu\n", (ulong)gd->ram_size);
#else
	sprintf(env_buf, "%lu", (ulong)(gd->ram_size >> 20));
	debug("## Giving linux memsize in MB, %lu\n",
		(ulong)(gd->ram_size >> 20));
#endif /* CONFIG_MEMSIZE_IN_BYTES */

	linux_env_set("memsize", env_buf);

#ifndef CONFIG_OCTEON
	sprintf(env_buf, "0x%08X", (uint) UNCACHED_SDRAM(images->rd_start));
#else
	sprintf (env_buf, "0x%08X", (uint)images->rd_start);
#endif
	linux_env_set("initrd_start", env_buf);

	sprintf(env_buf, "0x%X", (uint) (images->rd_end - images->rd_start));
	linux_env_set("initrd_size", env_buf);

	sprintf(env_buf, "0x%08X", (uint) (gd->bd->bi_flashstart));
	linux_env_set("flash_start", env_buf);

	sprintf(env_buf, "0x%X", (uint) (gd->bd->bi_flashsize));
	linux_env_set("flash_size", env_buf);

	cp = getenv("ethaddr");
	if (cp)
		linux_env_set("ethaddr", cp);

	cp = getenv("eth1addr");
	if (cp)
		linux_env_set("eth1addr", cp);
}

static void boot_jump_linux(bootm_headers_t *images)
{
	void (*theKernel) (int, char **, char **, int *);

	/* find kernel entry point */
	theKernel = (void (*)(int, char **, char **, int *))images->ep;

	debug("## Transferring control to Linux (at address %08lx) ...\n",
		(ulong) theKernel);

	bootstage_mark(BOOTSTAGE_ID_RUN_OS);

	/* we assume that the kernel is in place */
	printf("\nStarting kernel ...\n\n");

	theKernel(linux_argc, linux_argv, linux_env, 0);
}

int do_bootm_linux(int flag, int argc, char * const argv[],
			bootm_headers_t *images)
{
	/* No need for those on MIPS */
	if (flag & BOOTM_STATE_OS_BD_T || flag & BOOTM_STATE_OS_CMDLINE)
		return -1;

	if (flag & BOOTM_STATE_OS_PREP) {
		boot_prep_linux(images);
		return 0;
	}

	if (flag & BOOTM_STATE_OS_GO) {
		boot_jump_linux(images);
		return 0;
	}

	boot_prep_linux(images);
	boot_jump_linux(images);

	/* does not return */
	return 1;
}

static void linux_params_init(ulong start, char *line)
{
	char *next, *quote, *argp;

	linux_argc = 1;
	linux_argv = (char **) start;
	linux_argv[0] = 0;
	argp = (char *) (linux_argv + LINUX_MAX_ARGS);

	next = line;

	while (line && *line && linux_argc < LINUX_MAX_ARGS) {
		quote = strchr(line, '"');
		next = strchr(line, ' ');

		while (next && quote && quote < next) {
			/* we found a left quote before the next blank
			 * now we have to find the matching right quote
			 */
			next = strchr(quote + 1, '"');
			if (next) {
				quote = strchr(next + 1, '"');
				next = strchr(next + 1, ' ');
			}
		}

		if (!next)
			next = line + strlen(line);

		linux_argv[linux_argc] = argp;
		memcpy(argp, line, next - line);
		argp[next - line] = 0;

		argp += next - line + 1;
		linux_argc++;

		if (*next)
			next++;

		line = next;
	}

	linux_env = (char **) (((ulong) argp + 15) & ~15);
	linux_env[0] = 0;
	linux_env_p = (char *) (linux_env + LINUX_MAX_ENVS);
	linux_env_idx = 0;
}

static void linux_env_set(char *env_name, char *env_val)
{
	if (linux_env_idx < LINUX_MAX_ENVS - 1) {
		linux_env[linux_env_idx] = linux_env_p;

		strcpy(linux_env_p, env_name);
		linux_env_p += strlen(env_name);

		strcpy(linux_env_p, "=");
		linux_env_p += 1;

		strcpy(linux_env_p, env_val);
		linux_env_p += strlen(env_val);

		linux_env_p++;
		linux_env[++linux_env_idx] = 0;
	}
}
