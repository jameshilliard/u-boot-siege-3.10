#ifndef __EXPORTS_H__
#define __EXPORTS_H__

#ifndef __ASSEMBLY__

/* These are declarations of exported functions available in C code */
unsigned long get_version(void);
int  getc(void);
int  tstc(void);
void putc(const char);
void puts(const char*);
int printf(const char* fmt, ...);
void install_hdlr(int, void (*interrupt_handler_t)(void *), void*);
void free_hdlr(int);
void *malloc(size_t);
void free(void*);
void __udelay(unsigned long);
unsigned long get_timer(unsigned long);
int vprintf(const char *, va_list);
unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base);
int strict_strtoul(const char *cp, unsigned int base, unsigned long *res);
char *getenv (const char *name);
int setenv (const char *varname, const char *varvalue);
long simple_strtol(const char *cp,char **endp,unsigned int base);
int strcmp(const char * cs,const char * ct);
unsigned long ustrtoul(const char *cp, char **endp, unsigned int base);
unsigned long long ustrtoull(const char *cp, char **endp, unsigned int base);
#if defined(CONFIG_CMD_I2C)
int i2c_write (uchar, uint, int , uchar* , int);
int i2c_read (uchar, uint, int , uchar* , int);
#endif

/* exports functions by srx_siege */
#if defined(CONFIG_SRX_SIEGE_STAGE3)
extern int eth_receive(void *packet, int length);
uint32_t cvmx_pcie_config_read32(int pcie_port, int bus, int dev, int fn, int reg);
void cvmx_pcie_config_write32(int pcie_port, int bus, int dev, int fn, int reg, uint32_t val);
uint32_t cvmx_pcie_mem_read32(int pcie_port, uint32_t offset);
void cvmx_pcie_mem_write32(int pcie_port, uint32_t offset, uint32_t val);

extern uint8_t cpld_read(uint8_t addr);
extern void cpld_write(uint8_t addr, uint8_t val);
uint32_t octeon_pci_read_io(uint32_t addr, uint8_t size);
int octeon_pci_write_io(uint32_t addr, uint8_t size, uint32_t val);
int octeon_read_config(pci_dev_t dev, int reg, int size, uint32_t * val);
extern void init_octeon_pci(void );
int limit_l2_ways(int ways, int verbose);

extern int disk_scan(int last);
extern int board_disk_read(int dev, int lba, int blks, void *buf);
extern int board_disk_write(int dev, int lba, int nlks, void *buf);

/*
 * we defined these jump table entries to match u-boot 1.1.6 JT defination
 * however some of them are not used by either loader or ushell,
 * assign these unused Jumptable entry dummy;
 */
#ifndef CONFIG_LCD
#define lcd_printf      dummy
#else
void lcd_printf(const char *fmt, ...);
#endif

#define uart_init       dummy
#define uart_getc       dummy
#define uart_putc       dummy
#define i2c_read8       dummy
#define i2c_read16      dummy
#define i2c_write8      dummy
#define i2c_write16     dummy
#define octeon_twsi_write_max       dummy 
#define octeon_twsi_read_max        dummy
#define octeon_gpio_ext_cfg_output  dummy
#define octeon_gpio_set             dummy

#define cvmx_pcie_config_regex      dummy
#define nand_phys_page_read         dummy
#define i2c_read8_generic           dummy
#define i2c_write8_generic          dummy
#define i2c_switch_programming      dummy

extern int32_t get_next_bootdev_jt(uint8_t *bootdev);
extern int32_t set_next_bootdev(uint8_t *bootdev);
extern void show_bootdev_list(void); 
void reload_watchdog(int32_t val);
#endif   /* CONFIG_SRX_SIEGE_STAGE3 */

void app_startup(char * const *);

#endif    /* ifndef __ASSEMBLY__ */

enum {
#define EXPORT_FUNC(x) XF_ ## x ,
#include <_exports.h>
#undef EXPORT_FUNC

	XF_MAX
};

#define XF_VERSION	6

#if defined(CONFIG_X86)
extern gd_t *global_data;
#endif

#endif	/* __EXPORTS_H__ */
