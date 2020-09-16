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
 * Description: Higmac util header file
 */

#ifndef __HIGMAC_UTIL_H__
#define __HIGMAC_UTIL_H__

#include <common.h>

#define HIGMAC_TRACE_ETH		2
#define HIGMAC_TRACE_MDIO		4
#define HIGMAC_TRACE_DRV		7
#define HIGMAC_TRACE_LEVEL		8

#define mk_bits(shift, nbits) ((((shift) & 0x1F) << 16) | ((nbits) & 0x3F))

#endif

