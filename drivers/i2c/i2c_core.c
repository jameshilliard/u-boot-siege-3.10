/*
 * Copyright (C) 2009 Sergey Kubushyn <ksi@koi8.net>
 *
 * (C) Copyright 2012
 * Heiko Schocher, DENX Software Engineering, hs@denx.de.
 *
 * Multibus/multiadapter I2C core functions (wrappers)
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 * The following url indicates the file that this code is based on,
 * but note parts of the code could also come from other versions of U-Boot or other
 * GPL sources:
 *
 * based on http://git.denx.de/?p=u-boot.git;a=blob;f=drivers/i2c/i2c_core.c;h=16b1aba32aaca5437cba1a25084dfefe3d4423d1;hb=793fd86f722f5c5e13290be2074816b001359b76
 */
#include <common.h>
#include <i2c.h>

struct i2c_adapter *i2c_get_adapter(int index)
{
	struct i2c_adapter *i2c_adap_p = ll_entry_start(struct i2c_adapter,
						i2c);
	int max = ll_entry_count(struct i2c_adapter, i2c);
	int i;

	if (index >= max) {
		printf("Error, wrong i2c adapter %d max %d possible\n",
		       index, max);
		return i2c_adap_p;
	}
	if (index == 0)
		return i2c_adap_p;

	for (i = 0; i < index; i++)
		i2c_adap_p++;

	return i2c_adap_p;
}

#if !defined(CONFIG_SYS_I2C_DIRECT_BUS)
struct i2c_bus_hose i2c_bus[CONFIG_SYS_NUM_I2C_BUSES] =
			CONFIG_SYS_I2C_BUSES;
#endif

DECLARE_GLOBAL_DATA_PTR;

void i2c_reloc_fixup(void)
{
#if defined(CONFIG_NEEDS_MANUAL_RELOC)
	struct i2c_adapter *i2c_adap_p = ll_entry_start(struct i2c_adapter,
						i2c);
	struct i2c_adapter *tmp = i2c_adap_p;
	int max = ll_entry_count(struct i2c_adapter, i2c);
	int		i;
	unsigned long	addr;

	if (gd->reloc_off == 0)
		return;

	for (i = 0; i < max; i++) {
		/* i2c_init() */
		addr = (unsigned long)i2c_adap_p->init;
		addr += gd->reloc_off;
		i2c_adap_p->init = (void *)addr;
		/* i2c_probe() */
		addr = (unsigned long)i2c_adap_p->probe;
		addr += gd->reloc_off;
		i2c_adap_p->probe = (void *)addr;
		/* i2c_read() */
		addr = (unsigned long)i2c_adap_p->read;
		addr += gd->reloc_off;
		i2c_adap_p->read = (void *)addr;
		/* i2c_write() */
		addr = (unsigned long)i2c_adap_p->write;
		addr += gd->reloc_off;
		i2c_adap_p->write = (void *)addr;
		/* i2c_set_bus_speed() */
		addr = (unsigned long)i2c_adap_p->set_bus_speed;
		addr += gd->reloc_off;
		i2c_adap_p->set_bus_speed = (void *)addr;
		/* name */
		addr = (unsigned long)i2c_adap_p->name;
		addr += gd->reloc_off;
		i2c_adap_p->name = (char *)addr;
		tmp++;
		i2c_adap_p = tmp;
	}
#endif
}

#ifndef CONFIG_SYS_I2C_DIRECT_BUS
/*
 * i2c_mux_set()
 * -------------
 *
 * This turns on the given channel on I2C multiplexer chip connected to
 * a given I2C adapter directly or via other multiplexers. In the latter
 * case the entire multiplexer chain must be initialized first starting
 * with the one connected directly to the adapter. When disabling a chain
 * muxes must be programmed in reverse order, starting with the one
 * farthest from the adapter.
 *
 * mux_id is the multiplexer chip type from defined in i2c.h. So far only
 * NXP (Philips) PCA954x multiplexers are supported. Switches are NOT
 * supported (anybody uses them?)
 */

static int i2c_mux_set(struct i2c_adapter *adap, int mux_id, int chip,
			int channel)
{
	uint8_t	buf;
	int ret;

	/* channel < 0 - turn off the mux */
	if (channel < 0) {
		buf = 0;
		ret = adap->write(adap, chip, 0, 0, &buf, 1);
		if (ret)
			printf("%s: Could not turn off the mux.\n", __func__);
		return ret;
	}

	switch (mux_id) {
	case I2C_MUX_PCA9540_ID:
	case I2C_MUX_PCA9542_ID:
		if (channel > 1)
			return -1;
		buf = (uint8_t)((channel & 0x01) | (1 << 2));
		break;
	case I2C_MUX_PCA9544_ID:
		if (channel > 3)
			return -1;
		buf = (uint8_t)((channel & 0x03) | (1 << 2));
		break;
	case I2C_MUX_PCA9546_ID:
		if (channel > 3)
			return -1;
		buf = (uint8_t)(1 << channel);
		break;
	case I2C_MUX_PCA9547_ID:
		if (channel > 7)
			return -1;
		buf = (uint8_t)((channel & 0x07) | (1 << 3));
		break;
	case I2C_MUX_PCA9548_ID:
		if (channel > 7)
			return -1;
		buf = (uint8_t)(0x01 << channel);
		break;
	default:
		printf("%s: wrong mux id: %d\n", __func__, mux_id);
		return -1;
	}

	ret = adap->write(adap, chip, 0, 0, &buf, 1);
	if (ret)
		printf("%s: could not set mux: id: %d chip: %x channel: %d\n",
		       __func__, mux_id, chip, channel);
	return ret;
}

static int i2c_mux_set_all(void)
{
	struct i2c_bus_hose *i2c_bus_tmp = &i2c_bus[I2C_BUS];
	int i;

	/* Connect requested bus if behind muxes */
	if (i2c_bus_tmp->next_hop[0].chip != 0) {
		/* Set all muxes along the path to that bus */
		for (i = 0; i < CONFIG_SYS_I2C_MAX_HOPS; i++) {
			int	ret;

			if (i2c_bus_tmp->next_hop[i].chip == 0)
				break;

			ret = i2c_mux_set(I2C_ADAP,
					i2c_bus_tmp->next_hop[i].mux.id,
					i2c_bus_tmp->next_hop[i].chip,
					i2c_bus_tmp->next_hop[i].channel);
			if (ret != 0)
				return ret;
		}
	}
	return 0;
}

static int i2c_mux_disconnet_all(void)
{
	struct	i2c_bus_hose *i2c_bus_tmp = &i2c_bus[I2C_BUS];
	int	i;
	uint8_t	buf = 0;

	if (I2C_ADAP->init_done == 0)
		return 0;

	/* Disconnect current bus (turn off muxes if any) */
	if ((i2c_bus_tmp->next_hop[0].chip != 0) &&
	    (I2C_ADAP->init_done != 0)) {
		i = CONFIG_SYS_I2C_MAX_HOPS;
		do {
			uint8_t	chip;
			int ret;

			chip = i2c_bus_tmp->next_hop[--i].chip;
			if (chip == 0)
				continue;

			ret = I2C_ADAP->write(I2C_ADAP, chip, 0, 0, &buf, 1);
			if (ret != 0) {
				printf("i2c: mux diconnect error\n");
				return ret;
			}
		} while (i > 0);
	}

	return 0;
}
#endif

/*
 * i2c_init_bus():
 * ---------------
 *
 * Initializes one bus. Will initialize the parent adapter. No current bus
 * changes, no mux (if any) setup.
 */
static void i2c_init_bus(unsigned int bus_no, int speed, int slaveaddr)
{
	if (bus_no >= CONFIG_SYS_NUM_I2C_BUSES)
		return;

	I2C_ADAP->init(I2C_ADAP, speed, slaveaddr);

	if (gd->flags & GD_FLG_RELOC) {
		I2C_ADAP->init_done = 1;
		I2C_ADAP->speed = speed;
		I2C_ADAP->slaveaddr = slaveaddr;
	}
}

/* implement possible board specific board init */
static void __def_i2c_init_board(void)
{
}
void i2c_init_board(void)
	__attribute__((weak, alias("__def_i2c_init_board")));

/*
 * i2c_init_all():
 *
 * not longer needed, will deleted. Actual init the SPD_BUS
 * for compatibility.
 * i2c_adap[] must be initialized beforehead with function pointers and
 * data, including speed and slaveaddr.
 */
void i2c_init_all(void)
{
	i2c_init_board();
	i2c_set_bus_num(CONFIG_SYS_SPD_BUS_NUM);
	return;
}

/*
 * i2c_get_bus_num():
 * ------------------
 *
 *  Returns index of currently active I2C bus.  Zero-based.
 */
unsigned int i2c_get_bus_num(void)
{
	return gd->cur_i2c_bus;
}

/*
 * i2c_set_bus_num():
 * ------------------
 *
 *  Change the active I2C bus. Subsequent read/write calls will
 *  go to this one. Sets all of the muxes in a proper condition
 *  if that bus is behind muxes.
 *  If previously selected bus is behind the muxes turns off all the
 *  muxes along the path to that bus.
 *
 *	bus - bus index, zero based
 *
 *	Returns: 0 on success, not 0 on failure
 */
int i2c_set_bus_num(unsigned int bus)
{
	int max;

	if ((bus == I2C_BUS) && (I2C_ADAP->init_done > 0))
		return 0;

#ifndef CONFIG_SYS_I2C_DIRECT_BUS
	if (bus >= CONFIG_SYS_NUM_I2C_BUSES)
		return -1;
#endif

	max = ll_entry_count(struct i2c_adapter, i2c);
	if (I2C_ADAPTER(bus) >= max) {
		printf("Error, wrong i2c adapter %d max %d possible\n",
		       I2C_ADAPTER(bus), max);
		return -2;
	}

#ifndef CONFIG_SYS_I2C_DIRECT_BUS
	i2c_mux_disconnet_all();
#endif

	gd->cur_i2c_bus = bus;
	if (I2C_ADAP->init_done == 0)
		i2c_init_bus(bus, I2C_ADAP->speed, I2C_ADAP->slaveaddr);

#ifndef CONFIG_SYS_I2C_DIRECT_BUS
	i2c_mux_set_all();
#endif
	return 0;
}

/*
 * Probe the given I2C chip address.  Returns 0 if a chip responded,
 * not 0 on failure.
 */
int i2c_probe(uint8_t chip)
{
	return I2C_ADAP->probe(I2C_ADAP, chip);
}

/*
 * Read/Write interface:
 *   chip:    I2C chip address, range 0..127
 *   addr:    Memory (register) address within the chip
 *   alen:    Number of bytes to use for addr (typically 1, 2 for larger
 *              memories, 0 for register type devices with only one
 *              register)
 *   buffer:  Where to read/write the data
 *   len:     How many bytes to read/write
 *
 *   Returns: 0 on success, not 0 on failure
 */
int i2c_read(uint8_t chip, unsigned int addr, int alen,
				uint8_t *buffer, int len)
{
	return I2C_ADAP->read(I2C_ADAP, chip, addr, alen, buffer, len);
}

int i2c_write(uint8_t chip, unsigned int addr, int alen,
				uint8_t *buffer, int len)
{
	return I2C_ADAP->write(I2C_ADAP, chip, addr, alen, buffer, len);
}

unsigned int i2c_set_bus_speed(unsigned int speed)
{
	unsigned int ret;

	if (I2C_ADAP->set_bus_speed == NULL)
		return 0;
	ret = I2C_ADAP->set_bus_speed(I2C_ADAP, speed);
	if (gd->flags & GD_FLG_RELOC)
		I2C_ADAP->speed = ret;

	return ret;
}

unsigned int i2c_get_bus_speed(void)
{
	struct i2c_adapter *cur = I2C_ADAP;
	return cur->speed;
}

uint8_t i2c_reg_read(uint8_t addr, uint8_t reg)
{
	uint8_t buf;

#ifdef CONFIG_8xx
	/* MPC8xx needs this.  Maybe one day we can get rid of it. */
	/* maybe it is now the time for it ... */
	i2c_set_bus_num(i2c_get_bus_num());
#endif
	i2c_read(addr, reg, 1, &buf, 1);

#ifdef DEBUG
	printf("%s: bus=%d addr=0x%02x, reg=0x%02x, val=0x%02x\n",
	       __func__, i2c_get_bus_num(), addr, reg, buf);
#endif

	return buf;
}

void i2c_reg_write(uint8_t addr, uint8_t reg, uint8_t val)
{
#ifdef CONFIG_8xx
	/* MPC8xx needs this.  Maybe one day we can get rid of it. */
	/* maybe it is now the time for it ... */
	i2c_set_bus_num(i2c_get_bus_num());
#endif

#ifdef DEBUG
	printf("%s: bus=%d addr=0x%02x, reg=0x%02x, val=0x%02x\n",
	       __func__, i2c_get_bus_num(), addr, reg, val);
#endif

	i2c_write(addr, reg, 1, &val, 1);
}

void __i2c_init(int speed, int slaveaddr)
{
	i2c_init_bus(i2c_get_bus_num(), speed, slaveaddr);
}
void i2c_init(int speed, int slaveaddr)
	__attribute__((weak, alias("__i2c_init")));
