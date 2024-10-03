#include <common.h>
#include <exports.h>
#include <spi.h>

DECLARE_GLOBAL_DATA_PTR;

__attribute__((unused)) static void dummy(void)
{
}


/*
 * weak this function,
 * so that srx_siege can define it's own get_uboot_version func
 */
unsigned long get_uboot_version(void)
	__attribute__((weak, alias("__get_uboot_version")));

unsigned long __get_uboot_version(void)
{
	return XF_VERSION;
}


unsigned long get_version(void)
{
	return get_uboot_version();
}

/* Reuse _exports.h with a little trickery to avoid bitrot */
#define EXPORT_FUNC(sym) gd->jt[XF_##sym] = (void *)sym;

#if !defined(CONFIG_X86) && !defined(CONFIG_PPC)
# define install_hdlr      dummy
# define free_hdlr         dummy
#else /* kludge for non-standard function naming */
# define install_hdlr      irq_install_handler
# define free_hdlr         irq_free_handler
#endif
#ifndef CONFIG_CMD_I2C
# define i2c_write         dummy
# define i2c_read          dummy
#endif
#ifndef CONFIG_CMD_SPI
# define spi_init          dummy
# define spi_setup_slave   dummy
# define spi_free_slave    dummy
# define spi_claim_bus     dummy
# define spi_release_bus   dummy
# define spi_xfer          dummy
#endif


#ifdef CONFIG_SRX_SIEGE_STAGE3
/* to match u-boot 1.1.6, loader check the return value*/
int uboot_eth_init(bd_t *bis)
{
    int ret;
    ret = eth_init(bis);

    if (ret == 0)
        return 1;

    return 0;
}


extern void set_last_booseq_record_finish(void );
int do_reset_jt(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
    set_last_booseq_record_finish();
    return do_reset(NULL, 0, 0, NULL);
}

#endif

void jumptable_init(void)
{
	gd->jt = malloc(XF_MAX * sizeof(void *));
#include <_exports.h>

#ifdef CONFIG_SRX_SIEGE_STAGE3
    gd->jt[XF_eth_init] = (void *)uboot_eth_init;
    gd->jt[XF_do_reset] = (void *)do_reset_jt;
#endif

}


