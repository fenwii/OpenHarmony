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
 * Description: Hieth MAC operation header file
 */


#ifndef __HIETH_MAC_H__
#define __HIETH_MAC_H__

#include "hieth.h"

#ifdef HIETH_SFV300

#define U_MAC_PORTSEL     0x0200
#define D_MAC_PORTSEL     0x2200
#define U_MAC_RO_STAT     0x0204
#define D_MAC_RO_STAT     0x2204
#define U_MAC_PORTSET     0x0208
#define D_MAC_PORTSET     0x2208
#define U_MAC_STAT_CHANGE 0x020C
#define D_MAC_STAT_CHANGE 0x220C
#define U_MAC_SET         0x0210
#define D_MAC_SET         0x2210
#define U_MAC_RX_IPGCTRL  0x0214
#define D_MAC_RX_IPGCTRL  0x2214
#define U_MAC_TX_IPGCTRL  0x0218
#define D_MAC_TX_IPGCTRL  0x2218

/* bits of UD_MAC_PORTSET and UD_MAC_RO_STAT */
#define BITS_MACSTAT mk_bits(0, 3)

/* bits of U_MAC_PORTSEL and D_MAC_PORTSEL */
#define BITS_NEGMODE  mk_bits(0, 1)
#define BITS_MII_MODE mk_bits(1, 1)

/* bits of U_MAC_TX_IPGCTRL and D_MAC_TX_IPGCTRL */
#define BITS_PRE_CNT_LIMIT mk_bits(23, 3)
#define BITS_IPG           mk_bits(16, 7)
#define BITS_FC_INTER      mk_bits(0, 16)

#endif

#define HIETH_SPD_100M bit(2)
#define HIETH_LINKED   bit(1)
#define HIETH_DUP_FULL bit(0)

void hieth_set_mac_leadcode_cnt_limit(struct hieth_netdev_local *ld, u32 cnt);
void hieth_set_mac_trans_interval_bits(struct hieth_netdev_local *ld, u32 nbits);
void hieth_set_mac_fc_interval(struct hieth_netdev_local *ld, u32 para);

void hieth_set_linkstat(struct hieth_netdev_local *ld, u32 mode);
u32 hieth_get_linkstat(struct hieth_netdev_local *ld);

#define HIETH_NEGMODE_CPUSET 1
#define HIETH_NEGMODE_AUTO   0

void hieth_set_negmode(struct hieth_netdev_local *ld, u32 mode);
u32 hieth_get_negmode(struct hieth_netdev_local *ld);

#define HIETH_MII_MODE  0
#define HIETH_RMII_MODE 1

void hieth_set_mii_mode(struct hieth_netdev_local *ld, u32 mode);

#endif
