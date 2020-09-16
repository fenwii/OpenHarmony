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

#ifndef __HI_BOARD_H__
#define __HI_BOARD_H__

#include "hi_common.h"

#define CRG_REGS_ADDR             0x11010000
#define VOU_REGS_ADDR             0x17A00000

#define CRG_PERCTL_PLL224_ADDR      (0x0380 + CRG_REGS_ADDR)
#define CRG_PERCTL_PLL225_ADDR      (0x0384 + CRG_REGS_ADDR)
#define CRG_PERCTL_PLL256_ADDR      (0x0400 + CRG_REGS_ADDR)
#define CRG_PERCTL_PLL257_ADDR      (0x0404 + CRG_REGS_ADDR)

#define CRG_PERCTL8336_ADDR         (0x8240 + CRG_REGS_ADDR)
#define CRG_PERCTL8338_ADDR         (0x8248 + CRG_REGS_ADDR)
#define CRG_PERCTL8340_ADDR         (0x8250 + CRG_REGS_ADDR)
#define CRG_PERCTL8341_ADDR         (0x8254 + CRG_REGS_ADDR)
#define CRG_PERCTL8342_ADDR         (0x8258 + CRG_REGS_ADDR)
#define CRG_PERCTL8348_ADDR         (0x8270 + CRG_REGS_ADDR)
#define CRG_PERCTL8349_ADDR         (0x8274 + CRG_REGS_ADDR)
#define CRG_PERCTL8350_ADDR         (0x8278 + CRG_REGS_ADDR)
#define CRG_PERCTL8351_ADDR         (0x827C + CRG_REGS_ADDR)

#endif /* __HI_BOARD_H__ */
