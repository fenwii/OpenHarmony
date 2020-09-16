/*
 * boot0.h
 *
 * This file is related to startup.
 *
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

#ifndef __BOOT0_H
#define __BOOT0_H

#define ARM_SOC_BOOT0_HOOK

/* BOOT0 header information */
#define HI35XX_BOOT0_HOOK   \
	__blank_zone_start : \
	.fill 1024 * 8, 1, 0;   \
	__blank_zone_end :

#include <../mach-hi35xx/boot0_hook.S>
#endif /* __BOOT0_H */
