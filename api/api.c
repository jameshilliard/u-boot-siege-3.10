/*
 * (C) Copyright 2007 Semihalf
 *
 * Written by: Rafal Jaworowski <raj@semihalf.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <config.h>
#include <command.h>
#include <common.h>
#include <malloc.h>
#include <environment.h>
#include <linux/types.h>
#include <api_public.h>

#include "api_private.h"
#ifdef CONFIG_SRX_SIEGE
#include <exports.h>
#endif

#define DEBUG
#undef DEBUG

/*****************************************************************************
 *
 * This is the API core.
 *
 * API_ functions are part of U-Boot code and constitute the lowest level
 * calls:
 *
 *  - they know what values they need as arguments
 *  - their direct return value pertains to the API_ "shell" itself (0 on
 *    success, some error code otherwise)
 *  - if the call returns a value it is buried within arguments
 *
 ****************************************************************************/

#ifdef DEBUG
#define debugf(fmt, args...) do { printf("%s(): ", __func__); printf(fmt, ##args); } while (0)
#else
#define debugf(fmt, args...)
#endif

#ifdef CONFIG_OCTEON
DECLARE_GLOBAL_DATA_PTR;
#endif

typedef	int (*cfp_t)(va_list argp);

static int calls_no;

#if defined(CONFIG_SRX_SIEGE) && !defined(_ABIO32)
/* For O32 call N32 API */
static u_int32_t *api_caller_stack = NULL;
#endif

/*
 * pseudo signature:
 *
 * int API_getc(int *c)
 */
static int API_getc(va_list ap)
{
	int *c;

	if ((c = (int *)va_arg(ap, u_int32_t)) == NULL)
		return API_EINVAL;

	*c = getc();
	return 0;
}

/*
 * pseudo signature:
 *
 * int API_tstc(int *c)
 */
static int API_tstc(va_list ap)
{
	int *t;

	if ((t = (int *)va_arg(ap, u_int32_t)) == NULL)
		return API_EINVAL;

	*t = tstc();
	return 0;
}

/*
 * pseudo signature:
 *
 * int API_putc(char *ch)
 */
static int API_putc(va_list ap)
{
	char *c;

	if ((c = (char *)va_arg(ap, u_int32_t)) == NULL)
		return API_EINVAL;

	putc(*c);
	return 0;
}

/*
 * pseudo signature:
 *
 * int API_puts(char **s)
 */
static int API_puts(va_list ap)
{
	char *s;

	if ((s = (char *)va_arg(ap, u_int32_t)) == NULL)
		return API_EINVAL;

	puts(s);
	return 0;
}

#ifdef CONFIG_SRX_SIEGE
extern void set_last_booseq_record_finish(void);
#endif
/*
 * pseudo signature:
 *
 * int API_reset(void)
 */
static int API_reset(va_list ap)
{
#ifdef CONFIG_SRX_SIEGE
    set_last_booseq_record_finish();
#endif
	do_reset(NULL, 0, 0, NULL);

	/* NOT REACHED */
	return 0;
}

/*
 * pseudo signature:
 *
 * int API_get_sys_info(struct sys_info *si)
 *
 * fill out the sys_info struct containing selected parameters about the
 * machine
 */
static int API_get_sys_info(va_list ap)
{
	struct sys_info *si;

	si = (struct sys_info *)va_arg(ap, u_int32_t);
	if (si == NULL)
		return API_ENOMEM;

	return (platform_sys_info(si)) ? 0 : API_ENODEV;
}

/*
 * pseudo signature:
 *
 * int API_udelay(unsigned long *udelay)
 */
static int API_udelay(va_list ap)
{
	unsigned long *d;

	if ((d = (unsigned long *)va_arg(ap, u_int32_t)) == NULL)
		return API_EINVAL;
#ifndef CONFIG_OCTEON_SIM_SPEED
	udelay(*d);
#endif
	return 0;
}

/*
 * pseudo signature:
 *
 * int API_get_timer(unsigned long *current, unsigned long *base)
 */
static int API_get_timer(va_list ap)
{
	unsigned long *base, *cur;

	cur = (unsigned long *)va_arg(ap, u_int32_t);
	if (cur == NULL)
		return API_EINVAL;

	base = (unsigned long *)va_arg(ap, u_int32_t);
	if (base == NULL)
		return API_EINVAL;

	*cur = get_timer(*base);
	return 0;
}


/*****************************************************************************
 *
 * pseudo signature:
 *
 * int API_dev_enum(struct device_info *)
 *
 *
 * cookies uniqely identify the previously enumerated device instance and
 * provide a hint for what to inspect in current enum iteration:
 *
 *   - net: &eth_device struct address from list pointed to by eth_devices
 *
 *   - storage: block_dev_desc_t struct address from &ide_dev_desc[n],
 *     &scsi_dev_desc[n] and similar tables
 *
 ****************************************************************************/

#ifdef CONFIG_SRX_SIEGE
static int boot_record_updated = 0;
extern int32_t get_next_bootdev(uint8_t *bootdev, int32_t update);
#endif

static int API_dev_enum(va_list ap)
{
	struct device_info *di;

	/* arg is ptr to the device_info struct we are going to fill out */
	di = (struct device_info *)va_arg(ap, u_int32_t);
	if (di == NULL)
		return API_EINVAL;

	if (di->cookie == NULL) {
		/* start over - clean up enumeration */
		dev_enum_reset();	/* XXX shouldn't the name contain 'stor'? */
		debugf("RESTART ENUM\n");
#ifdef CONFIG_SRX_SIEGE
        /* prepare storage enum */
        disk_scan(-1);
        /* for Airbus, need to disk_scan USB */
        disk_scan(0);

        /* update boot record once veloader bootup */
        if (!boot_record_updated) {
            uint8_t bootdev[32];

            get_next_bootdev(bootdev, 1);
            boot_record_updated = 1;
        }
#endif
		/* net device enumeration first */
		if (dev_enum_net(di))
			return 0;
	}

	/*
	 * The hidden assumption is there can only be one active network
	 * device and it is identified upon enumeration (re)start, so there's
	 * no point in trying to find network devices in other cases than the
	 * (re)start and hence the 'next' device can only be storage
	 */
#ifdef CONFIG_SRX_SIEGE
	if (dev_enum_storage(di)) {
        if (dev_open_stor(di->cookie) == 0) {
            /* open device on enumberation */
            di->state = DEV_STA_OPEN;
        }
    } else {
		/* make sure we mark there are no more devices */
		di->cookie = NULL;
    }
#else
	if (!dev_enum_storage(di))
		/* make sure we mark there are no more devices */
		di->cookie = NULL;
#endif

	return 0;
}


static int API_dev_open(va_list ap)
{
	struct device_info *di;
	int err = 0;

	/* arg is ptr to the device_info struct */
	di = (struct device_info *)va_arg(ap, u_int32_t);
	if (di == NULL)
		return API_EINVAL;

	/* Allow only one consumer of the device at a time */
#ifndef CONFIG_SRX_SIEGE
	if (di->state == DEV_STA_OPEN)
		return API_EBUSY;
#endif

	if (di->cookie == NULL)
		return API_ENODEV;

	if (di->type & DEV_TYP_STOR)
		err = dev_open_stor(di->cookie);

	else if (di->type & DEV_TYP_NET)
		err = dev_open_net(di->cookie);
	else
		err = API_ENODEV;

	if (!err)
		di->state = DEV_STA_OPEN;

	return err;
}


static int API_dev_close(va_list ap)
{
	struct device_info *di;
	int err = 0;

	/* arg is ptr to the device_info struct */
	di = (struct device_info *)va_arg(ap, u_int32_t);
	if (di == NULL)
		return API_EINVAL;

	if (di->state == DEV_STA_CLOSED)
		return 0;

	if (di->cookie == NULL)
		return API_ENODEV;

	if (di->type & DEV_TYP_STOR)
		err = dev_close_stor(di->cookie);

	else if (di->type & DEV_TYP_NET)
		err = dev_close_net(di->cookie);
	else
		/*
		 * In case of unknown device we cannot change its state, so
		 * only return error code
		 */
		err = API_ENODEV;

	if (!err)
		di->state = DEV_STA_CLOSED;

	return err;
}


/*
 * Notice: this is for sending network packets only, as U-Boot does not
 * support writing to storage at the moment (12.2007)
 *
 * pseudo signature:
 *
 * int API_dev_write(
 *	struct device_info *di,
 *	void *buf,
 *	int *len
 * )
 *
 * buf:	ptr to buffer from where to get the data to send
 *
 * len: length of packet to be sent (in bytes)
 *
 */
static int API_dev_write(va_list ap)
{
	struct device_info *di;
	void *buf;
	int *len;
	int err = 0;

	/* 1. arg is ptr to the device_info struct */
	di = (struct device_info *)va_arg(ap, u_int32_t);
	if (di == NULL)
		return API_EINVAL;

	/* XXX should we check if device is open? i.e. the ->state ? */

	if (di->cookie == NULL)
		return API_ENODEV;

	/* 2. arg is ptr to buffer from where to get data to write */
	buf = (void *)va_arg(ap, u_int32_t);
	if (buf == NULL)
		return API_EINVAL;

	/* 3. arg is length of buffer */
#if defined(CONFIG_SRX_SIEGE) && !defined(_ABIO32)
	len = (int *)(api_caller_stack[4]);
#else
	len = (int *)va_arg(ap, u_int32_t);
#endif
	if (len == NULL)
		return API_EINVAL;
	if (*len <= 0)
		return API_EINVAL;

	if (di->type & DEV_TYP_STOR)
		/*
		 * write to storage is currently not supported by U-Boot:
		 * no storage device implements block_write() method
		 */
		return API_ENODEV;

	else if (di->type & DEV_TYP_NET)
		err = dev_write_net(di->cookie, buf, *len);
	else
		err = API_ENODEV;

	return err;
}


/*
 * pseudo signature:
 *
 * int API_dev_read(
 *	struct device_info *di,
 *	void *buf,
 *	size_t *len,
 *	unsigned long *start
 *	size_t *act_len
 * )
 *
 * buf:	ptr to buffer where to put the read data
 *
 * len: ptr to length to be read
 *      - network: len of packet to read (in bytes)
 *      - storage: # of blocks to read (can vary in size depending on define)
 *
 * start: ptr to start block (only used for storage devices, ignored for
 *        network)
 *
 * act_len: ptr to where to put the len actually read
 */
static int API_dev_read(va_list ap)
{
	struct device_info *di;
	void *buf;
	lbasize_t *len_stor, *act_len_stor;
	lbastart_t *start;
	int *len_net, *act_len_net;

	/* 1. arg is ptr to the device_info struct */
	di = (struct device_info *)va_arg(ap, u_int32_t);
	if (di == NULL)
		return API_EINVAL;

	/* XXX should we check if device is open? i.e. the ->state ? */

	if (di->cookie == NULL)
		return API_ENODEV;

	/* 2. arg is ptr to buffer from where to put the read data */
	buf = (void *)va_arg(ap, u_int32_t);
	if (buf == NULL)
		return API_EINVAL;

	if (di->type & DEV_TYP_STOR) {
		/* 3. arg - ptr to var with # of blocks to read */
#if defined(CONFIG_SRX_SIEGE) && !defined(_ABIO32)
		len_stor = (lbasize_t *)(api_caller_stack[4]);
#else
		len_stor = (lbasize_t *)va_arg(ap, u_int32_t);
#endif
		if (!len_stor)
			return API_EINVAL;

		if (*len_stor <= 0)
			return API_EINVAL;

		/* 4. arg - ptr to var with start block */
#if defined(CONFIG_SRX_SIEGE) && !defined(_ABIO32)
		start = (lbastart_t *)(api_caller_stack[5]);
#else
		start = (lbastart_t *)va_arg(ap, u_int32_t);
#endif

		/* 5. arg - ptr to var where to put the len actually read */
#if defined(CONFIG_SRX_SIEGE) && !defined(_ABIO32)
		act_len_stor = (lbasize_t *)(api_caller_stack[6]);
#else
		act_len_stor = (lbasize_t *)va_arg(ap, u_int32_t);
#endif
		if (!act_len_stor)
			return API_EINVAL;

		*act_len_stor = dev_read_stor(di->cookie, buf, *len_stor, *start);

	} else if (di->type & DEV_TYP_NET) {

		/* 3. arg points to the var with length of packet to read */
#if defined(CONFIG_SRX_SIEGE) && !defined(_ABIO32)
		len_net = (int *)(api_caller_stack[4]);
#else
		len_net = (int *)va_arg(ap, u_int32_t);
#endif
		if (!len_net)
			return API_EINVAL;
		if (*len_net <= 0)
			return API_EINVAL;

		/* 4. - ptr to var where to put the len actually read */
#if defined(CONFIG_SRX_SIEGE) && !defined(_ABIO32)
		act_len_net = (int *)(api_caller_stack[5]);
#else
		act_len_net = (int *)va_arg(ap, u_int32_t);
#endif
		if (!act_len_net)
			return API_EINVAL;

		*act_len_net = dev_read_net(di->cookie, buf, *len_net);
        if (getenv("debug_eth")) {
            int i;
            int p_len = (*act_len_net > 32) ? 32 : *act_len_net;
            unsigned char *pkt = buf;

            printf("R:act_l %d\r\n", *act_len_net);
            for (i=0; i<p_len; i++) {
                printf("%02x ", pkt[i]);
            }
            printf("\r\n");
        }

	} else {
		return API_ENODEV;
    }

	return 0;
}


/*
 * pseudo signature:
 *
 * int API_env_get(const char *name, char **value)
 *
 * name: ptr to name of env var
 */
static int API_env_get(va_list ap)
{
	char *name, **value;

	if ((name = (char *)va_arg(ap, u_int32_t)) == NULL)
		return API_EINVAL;
	if ((value = (char **)va_arg(ap, u_int32_t)) == NULL)
		return API_EINVAL;

	*value = getenv(name);

	return 0;
}

/*
 * pseudo signature:
 *
 * int API_env_set(const char *name, const char *value)
 *
 * name: ptr to name of env var
 *
 * value: ptr to value to be set
 */
static int API_env_set(va_list ap)
{
	char *name, *value;

	if ((name = (char *)va_arg(ap, u_int32_t)) == NULL)
		return API_EINVAL;
	if ((value = (char *)va_arg(ap, u_int32_t)) == NULL)
		return API_EINVAL;

	setenv(name, value);

	return 0;
}

/*
 * pseudo signature:
 *
 * int API_env_enum(const char *last, char **next)
 *
 * last: ptr to name of env var found in last iteration
 */
static int API_env_enum(va_list ap)
{
	int i, n;
	char *last, **next;

	last = (char *)va_arg(ap, u_int32_t);

	if ((next = (char **)va_arg(ap, u_int32_t)) == NULL)
		return API_EINVAL;

	if (last == NULL)
		/* start over */
		*next = ((char *)env_get_addr(0));
	else {
		*next = last;

		for (i = 0; env_get_char(i) != '\0'; i = n + 1) {
			for (n = i; env_get_char(n) != '\0'; ++n) {
				if (n >= CONFIG_ENV_SIZE) {
					/* XXX shouldn't we set *next = NULL?? */
					return 0;
				}
			}

			if (envmatch((uchar *)last, i) < 0)
				continue;

			/* try to get next name */
			i = n + 1;
			if (env_get_char(i) == '\0') {
				/* no more left */
				*next = NULL;
				return 0;
			}

			*next = ((char *)env_get_addr(i));
			return 0;
		}
	}

	return 0;
}

/*
 * pseudo signature:
 *
 * int API_display_get_info(int type, struct display_info *di)
 */
static int API_display_get_info(va_list ap)
{
	int type;
	struct display_info *di;

	type = va_arg(ap, int);
	di = va_arg(ap, struct display_info *);

	return display_get_info(type, di);
}

/*
 * pseudo signature:
 *
 * int API_display_draw_bitmap(ulong bitmap, int x, int y)
 */
static int API_display_draw_bitmap(va_list ap)
{
	ulong bitmap;
	int x, y;

	bitmap = va_arg(ap, ulong);
	x = va_arg(ap, int);
	y = va_arg(ap, int);

	return display_draw_bitmap(bitmap, x, y);
}

/*
 * pseudo signature:
 *
 * void API_display_clear(void)
 */
static int API_display_clear(va_list ap)
{
	display_clear();
	return 0;
}

static cfp_t calls_table[API_MAXCALL] = { NULL, };

/*
 * The main syscall entry point - this is not reentrant, only one call is
 * serviced until finished.
 *
 * e.g. syscall(1, int *, u_int32_t, u_int32_t, u_int32_t, u_int32_t);
 *
 * call:	syscall number
 *
 * retval:	points to the return value placeholder, this is the place the
 *		syscall puts its return value, if NULL the caller does not
 *		expect a return value
 *
 * ...		syscall arguments (variable number)
 *
 * returns:	0 if the call not found, 1 if serviced
 */
int syscall(int call, int *retval, ...)
{
	va_list	ap;
	int rv;

#if defined(CONFIG_SRX_SIEGE) && !defined(_ABIO32)
	register volatile uint32_t reg_sp asm ("sp");
	uint32_t *addr = (void *)syscall;
	uint32_t *stack_top;
	int16_t  stack_depth;

	/* find addiu sp sp instruction */
	while ((*addr & 0xffff0000) != 0x27bd0000) {
		addr ++;
	}    

	stack_depth = ((*addr)& 0xffff);
	stack_depth = 0 - stack_depth;

	stack_top = (uint32_t *)(reg_sp + stack_depth);

	/*
		get the caller's stack, we can find args from the caller stack
		------------------------------------
		(stack of caller func)
			.....
		args[5] at stack[5];
		args[4] at caller_stack[4];
		regs a0->a3 keep args[0]-> args[3];
        ------------------------------------
		(stack of this syscall func)
        ------------------------------------
	*/
	api_caller_stack = stack_top;
#endif
	if (call < 0 || call >= calls_no) {
		debugf("invalid call #%d\n", call);
		return 0;
	}

	if (calls_table[call] == NULL) {
		debugf("syscall #%d does not have a handler\n", call);
		return 0;
	}

	va_start(ap, retval);
	rv = calls_table[call](ap);
	if (retval != NULL)
		*retval = rv;

	return 1;
}

void api_init(void)
{
	struct api_signature *sig = NULL;

	/* TODO put this into linker set one day... */
	calls_table[API_RSVD] = NULL;
	calls_table[API_GETC] = &API_getc;
	calls_table[API_PUTC] = &API_putc;
	calls_table[API_TSTC] = &API_tstc;
	calls_table[API_PUTS] = &API_puts;
	calls_table[API_RESET] = &API_reset;
	calls_table[API_GET_SYS_INFO] = &API_get_sys_info;
	calls_table[API_UDELAY] = &API_udelay;
	calls_table[API_GET_TIMER] = &API_get_timer;
	calls_table[API_DEV_ENUM] = &API_dev_enum;
	calls_table[API_DEV_OPEN] = &API_dev_open;
	calls_table[API_DEV_CLOSE] = &API_dev_close;
	calls_table[API_DEV_READ] = &API_dev_read;
	calls_table[API_DEV_WRITE] = &API_dev_write;
	calls_table[API_ENV_GET] = &API_env_get;
	calls_table[API_ENV_SET] = &API_env_set;
	calls_table[API_ENV_ENUM] = &API_env_enum;
	calls_table[API_DISPLAY_GET_INFO] = &API_display_get_info;
	calls_table[API_DISPLAY_DRAW_BITMAP] = &API_display_draw_bitmap;
	calls_table[API_DISPLAY_CLEAR] = &API_display_clear;
	calls_no = API_MAXCALL;

	debugf("API initialized with %d calls\n", calls_no);

	dev_stor_init();

	/*
	 * Produce the signature so the API consumers can find it
	 */
	sig = malloc(sizeof(struct api_signature));
	if (sig == NULL) {
		printf("API: could not allocate memory for the signature!\n");
		return;
	}

	debugf("API sig @ 0x%08x\n", sig);
	memcpy(sig->magic, API_SIG_MAGIC, 8);
	sig->version = API_SIG_VERSION;
	sig->syscall = &syscall;
	sig->checksum = 0;
	sig->checksum = crc32(0, (unsigned char *)sig,
			      sizeof(struct api_signature));
#ifdef CONFIG_OCTEON
	/* Since the OCTEON bootloader is rather large we need a better way
	 * to hint where the signature is so we pass it as an argument.
	 */
	gd->arch.api_sig_addr = sig;
#endif
	debugf("syscall entry: 0x%08x\n", sig->syscall);
}

void platform_set_mr(struct sys_info *si, unsigned long start, unsigned long size,
			int flags)
{
	int i;

	if (!si->mr || !size || (flags == 0))
		return;

	/* find free slot */
	for (i = 0; i < si->mr_no; i++)
		if (si->mr[i].flags == 0) {
			/* insert new mem region */
			si->mr[i].start = start;
			si->mr[i].size = size;
			si->mr[i].flags = flags;
			return;
		}
}
