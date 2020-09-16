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
 * Description: Higmac mdio operation header file
 */

#ifndef __HIGMAC_MDIO_H__
#define __HIGMAC_MDIO_H__

#include "util.h"

#define	REG_MDIO_SINGLE_CMD			0x000003C0
#define	REG_MDIO_SINGLE_DATA		0x000003C4
#define	REG_MDIO_RDATA_STATUS		0x000003D0

/* 0:mdio operation done,1: start mdio operation */
#define	MDIO_CMD					mk_bits(20, 1)

#define	MDIO_WR_DATA				mk_bits(0, 16)
#define	MDIO_RDATA_STATUS			mk_bits(0, 1)

#define	MDIO_CMD_READ				2
#define	MDIO_CMD_WRITE				1

#define mdio_mk_rwctl(rw, phy_exaddr, phy_regnum) \
	(((0x1)<<20) | (((rw)&0x3)<<16) | \
	(((phy_exaddr)&0x1f)<<8) | ((phy_regnum)&0x1f))

#define mdio_start_phyread(ld, phy_addr, regnum) \
	higmac_writel(ld, mdio_mk_rwctl(MDIO_CMD_READ, phy_addr, regnum), \
			REG_MDIO_SINGLE_CMD)

#define mdio_get_phyread_val(ld) (higmac_readl(ld, REG_MDIO_SINGLE_DATA) >> 16)

#define mdio_phywrite(ld, phy_addr, regnum) \
	higmac_writel(ld, mdio_mk_rwctl(MDIO_CMD_WRITE, phy_addr, regnum), \
			REG_MDIO_SINGLE_CMD)

#define test_mdio_ready(ld)     (higmac_readl_bits((ld), \
			REG_MDIO_SINGLE_CMD, MDIO_CMD) == 0)

#define test_mdio_read_data_done(ld)    (higmac_readl_bits(ld, \
			REG_MDIO_RDATA_STATUS, MDIO_RDATA_STATUS) == 0)

int higmac_mdiobus_read(struct mii_dev *bus, int addr, int devad, int reg);
int higmac_mdiobus_write(struct mii_dev *bus, int addr, int devad,
		  int reg, unsigned short val);
#endif
