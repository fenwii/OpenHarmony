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
 */


#define HIETH_SFV300

#include "hieth.h"
#include "mac.h"

static u32 _set_linkstat(struct hieth_netdev_local *ld, u32 mode)
{
	u32 old;

	old = hieth_readl_bits(ld, ud_reg_name(MAC_PORTSET), BITS_MACSTAT);
	hieth_writel_bits(ld, mode, ud_reg_name(MAC_PORTSET), BITS_MACSTAT);

	return old;
}

static u32 _set_negmode(struct hieth_netdev_local *ld, u32 mode)
{
	u32 old;

	old = hieth_readl_bits(ld, ud_reg_name(MAC_PORTSEL), BITS_NEGMODE);
	hieth_writel_bits(ld, mode, ud_reg_name(MAC_PORTSEL), BITS_NEGMODE);

	return old;
}

static u32 _get_negmode(struct hieth_netdev_local *ld)
{
	u32 val;

	val = hieth_readl_bits(ld, ud_reg_name(MAC_PORTSEL), BITS_NEGMODE);
	return val;
}

void hieth_set_linkstat(struct hieth_netdev_local *ld, u32 mode)
{
	local_lock(ld);
	(void)_set_linkstat(ld, mode);
	local_unlock(ld);
}

u32 hieth_get_linkstat(struct hieth_netdev_local *ld)
{
	u32 val;

	local_lock(ld);
	val = hieth_readl_bits(ld, ud_reg_name(MAC_RO_STAT), BITS_MACSTAT);
	local_unlock(ld);
	return val;
}

void hieth_set_mac_leadcode_cnt_limit(struct hieth_netdev_local *ld, u32 cnt)
{
	local_lock(ld);
	(void)hieth_readl_bits(ld, ud_reg_name(MAC_TX_IPGCTRL),
						   BITS_PRE_CNT_LIMIT);
	hieth_writel_bits(ld, cnt, ud_reg_name(MAC_TX_IPGCTRL),
					  BITS_PRE_CNT_LIMIT);
	local_unlock(ld);
}

void hieth_set_mac_trans_interval_bits(struct hieth_netdev_local *ld, u32 nbits)
{
	u32 linkstat, negmode;

	local_lock(ld);

	negmode = _set_negmode(ld, HIETH_NEGMODE_CPUSET);
	linkstat = _set_linkstat(ld, 0);
	mdelay(1);

	(void)hieth_readl_bits(ld, ud_reg_name(MAC_TX_IPGCTRL), BITS_IPG);
	hieth_writel_bits(ld, nbits, ud_reg_name(MAC_TX_IPGCTRL), BITS_IPG);
	udelay(100); /* delay 100us */

	_set_negmode(ld, negmode);
	_set_linkstat(ld, linkstat);

	local_unlock(ld);
}

void hieth_set_mac_fc_interval(struct hieth_netdev_local *ld, u32 para)
{
	local_lock(ld);
	(void)hieth_readl_bits(ld, ud_reg_name(MAC_TX_IPGCTRL), BITS_FC_INTER);
	hieth_writel_bits(ld, para, ud_reg_name(MAC_TX_IPGCTRL), BITS_FC_INTER);
	local_unlock(ld);
}

void hieth_set_negmode(struct hieth_netdev_local *ld, u32 mode)
{
	local_lock(ld);
	_set_negmode(ld, mode);
	local_unlock(ld);
}

u32 hieth_get_negmode(struct hieth_netdev_local *ld)
{
	u32 val;

	local_lock(ld);
	val = _get_negmode(ld);
	local_unlock(ld);
	return val;
}

void hieth_set_mii_mode(struct hieth_netdev_local *ld, u32 mode)
{
	local_lock(ld);
	(void)hieth_readl_bits(ld, ud_reg_name(MAC_PORTSEL), BITS_MII_MODE);
	hieth_writel_bits(ld, mode, ud_reg_name(MAC_PORTSEL), BITS_MII_MODE);
	local_unlock(ld);
}
