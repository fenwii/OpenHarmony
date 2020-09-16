/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Description: Higmac mdio operation
 */

#include <errno.h>
#include <phy.h>
#include "higmac.h"
#include "ctrl.h"
#include "mdio.h"
#include "util.h"

static void mdio_set_phywrite_val(struct higmac_netdev_local *ld, unsigned short val)
{
	int reg;

	higmac_writel_bits(ld, val, REG_MDIO_SINGLE_DATA, MDIO_WR_DATA);
	reg = higmac_readl(ld, REG_MDIO_SINGLE_DATA);
	higmac_trace(HIGMAC_TRACE_MDIO, "write reg 0x%x, bits:0x%x= 0x%x, then read = 0x%x",
			REG_MDIO_SINGLE_DATA, MDIO_WR_DATA, val, reg);
}

static int mdio_wait_ready(struct higmac_netdev_local *ld)
{
	int timeout_us = 1000;

	while (--timeout_us && !test_mdio_ready(ld))
		udelay(1);

	return timeout_us;
}

static int higmac_mdio_read(struct higmac_netdev_local *ld,
		  char *devname, unsigned char phy,
		  unsigned char reg, unsigned short *value)
{
	int timeout = 1000;

	if (!mdio_wait_ready(ld))
		return -1;

	mdio_start_phyread(ld, phy, reg);

	while (!mdio_wait_ready(ld) && timeout-- > 0)
		udelay(1);

	if (timeout <= 0 || !test_mdio_read_data_done(ld)) {
		*value = 0;
		/* it should return Error(-1), but miiphy_read() will
		 * print error info, it's annoying
		 */
		return 0;
	}

	*value = mdio_get_phyread_val(ld);

	higmac_trace(HIGMAC_TRACE_MDIO, "mdio read phy:%x, reg:%x = %x\n",
		phy, reg, *value);

	return 0;
}

static int higmac_mdio_write(struct higmac_netdev_local *ld,
		  char *devname, unsigned char phy,
		  unsigned char reg, unsigned short val)
{
	if (!mdio_wait_ready(ld))
		return -1;

	higmac_trace(HIGMAC_TRACE_MDIO, "mdio write phy:%x, reg:%x = %x\n",
		phy, reg, val);

	mdio_set_phywrite_val(ld, val);
	mdio_phywrite(ld, phy, reg);

	return 0;
}

static struct higmac_netdev_local *higmac_get_netdev_by_name(const char *devname)
{
	int i;

	for (i = 0; i < CONFIG_GMAC_NUMS; i++) {
		if (!strcmp(devname, g_higmac_board_info[i].mii_name))
			return &g_higmac_board_info[i].higmac_ld;
	}

	return NULL;
}

int higmac_mdiobus_read(struct mii_dev *bus, int addr, int devad, int reg)
{
	struct higmac_netdev_local *ld = higmac_get_netdev_by_name(bus->name);
	unsigned short value;
	int ret;

	if (ld == NULL)
		return -EINVAL;

	ret = higmac_mdio_read(ld, bus->name, addr, reg, &value);

	return ret ? -1 : (int)value;
}

int higmac_mdiobus_write(struct mii_dev *bus, int addr, int devad,
		  int reg, unsigned short val)
{
	struct higmac_netdev_local *ld = higmac_get_netdev_by_name(bus->name);

	if (ld == NULL)
		return -EINVAL;

	return higmac_mdio_write(ld, bus->name, addr, reg, val);
}
