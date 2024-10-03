/*
 * You do not need to use #ifdef around functions that may not exist
 * in the final configuration (such as i2c).
 */
EXPORT_FUNC(get_version)
EXPORT_FUNC(getc)
EXPORT_FUNC(tstc)
EXPORT_FUNC(putc)
EXPORT_FUNC(puts)
EXPORT_FUNC(printf)
EXPORT_FUNC(install_hdlr)
EXPORT_FUNC(free_hdlr)
EXPORT_FUNC(malloc)
EXPORT_FUNC(free)
EXPORT_FUNC(udelay)
EXPORT_FUNC(get_timer)
EXPORT_FUNC(vprintf)
EXPORT_FUNC(do_reset)
EXPORT_FUNC(getenv)
EXPORT_FUNC(setenv)
EXPORT_FUNC(simple_strtoul)
#if defined(CONFIG_SRX_SIEGE_STAGE3)
/* to match 1.1.6 loader and ushell Jump table defination */
EXPORT_FUNC(i2c_write)
EXPORT_FUNC(i2c_read)
EXPORT_FUNC(eth_init)     /* loader */
EXPORT_FUNC(eth_halt)     /* loader */
EXPORT_FUNC(eth_send)     /* loader */
EXPORT_FUNC(eth_receive)  /* loader */
EXPORT_FUNC(disk_scan)    /* loader */
EXPORT_FUNC(board_disk_read)    /* loader */
EXPORT_FUNC(board_disk_write)   /* loader */
EXPORT_FUNC(lcd_printf)   /* loader */
EXPORT_FUNC(saveenv)      /* loader */
EXPORT_FUNC(i2c_read8)
EXPORT_FUNC(i2c_read16)
EXPORT_FUNC(i2c_write8)
EXPORT_FUNC(i2c_write16)
EXPORT_FUNC(octeon_twsi_write_max)
EXPORT_FUNC(octeon_twsi_read_max)
EXPORT_FUNC(i2c_read8_generic)
EXPORT_FUNC(i2c_write8_generic)
EXPORT_FUNC(i2c_switch_programming)
EXPORT_FUNC(cvmx_pcie_mem_read32)
EXPORT_FUNC(cvmx_pcie_mem_write32)
EXPORT_FUNC(cvmx_pcie_config_read32)
EXPORT_FUNC(cvmx_pcie_config_write32)
EXPORT_FUNC(eth_set_current)
EXPORT_FUNC(cvmx_pcie_config_regex)
EXPORT_FUNC(get_next_bootdev_jt)   /* loader */
EXPORT_FUNC(set_next_bootdev)   /* loader */
EXPORT_FUNC(show_bootdev_list)  /* loader */
EXPORT_FUNC(reload_watchdog)    /* loader */
EXPORT_FUNC(cpld_read)
EXPORT_FUNC(cpld_write)
EXPORT_FUNC(uart_init)
EXPORT_FUNC(uart_getc)
EXPORT_FUNC(uart_putc)
EXPORT_FUNC(octeon_pci_read_io)
EXPORT_FUNC(octeon_pci_write_io)
EXPORT_FUNC(octeon_read_config)
EXPORT_FUNC(init_octeon_pci)
EXPORT_FUNC(octeon_gpio_ext_cfg_output)
EXPORT_FUNC(octeon_gpio_set)
EXPORT_FUNC(limit_l2_ways)
EXPORT_FUNC(nand_phys_page_read)
#endif
EXPORT_FUNC(strict_strtoul)
EXPORT_FUNC(simple_strtol)
EXPORT_FUNC(strcmp)
#ifndef CONFIG_SRX_SIEGE_STAGE3
EXPORT_FUNC(i2c_write)
EXPORT_FUNC(i2c_read)
#endif
EXPORT_FUNC(spi_init)
EXPORT_FUNC(spi_setup_slave)
EXPORT_FUNC(spi_free_slave)
EXPORT_FUNC(spi_claim_bus)
EXPORT_FUNC(spi_release_bus)
EXPORT_FUNC(spi_xfer)
