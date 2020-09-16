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
 * Description: Hieth pre init header file
 */


#ifndef __HIETH_GLB_H__
#define __HIETH_GLB_H__

#include "hieth.h"

#define GLB_HOSTMAC_L32  0x1300
#define BITS_HOSTMAC_L32 mk_bits(0, 32)
#define GLB_HOSTMAC_H16  0x1304
#define BITS_HOSTMAC_H16 mk_bits(0, 16)

#define GLB_SOFT_RESET      0x1308
#define BITS_ETH_SOFT_RESET mk_bits(0, 1)

#define GLB_FWCTRL           0x1310
#define BITS_VLAN_ENABLE     mk_bits(0, 1)
#define BITS_FW2CPU_ENA_UP   mk_bits(5, 1)
#define BITS_FWALL2CPU_UP    mk_bits(7, 1)
#define BITS_FW2CPU_ENA_DOWN mk_bits(9, 1)
#define BITS_FWALL2CPU_DOWN  mk_bits(11, 1)

#define GLB_MACTCTRL        0x1314
#define BITS_BROAD2CPU_UP   mk_bits(5, 1)
#define BITS_BROAD2CPU_DOWN mk_bits(13, 1)
#define BITS_MACT_ENA_DOWN  mk_bits(15, 1)
#define BITS_MACT_ENA_UP    mk_bits(7, 1)

#define GLB_MAC0_L32      0x1400
#define GLB_MAC0_H16      0x1404
#define BITS_MAC0_H16     mk_bits(0, 16)
#define BITS_PKT2CPU_UP   mk_bits(21, 1)
#define BITS_PKT2CPU_DOWN mk_bits(19, 1)

int hieth_glb_preinit_dummy(struct hieth_netdev_local *ld);

#endif
