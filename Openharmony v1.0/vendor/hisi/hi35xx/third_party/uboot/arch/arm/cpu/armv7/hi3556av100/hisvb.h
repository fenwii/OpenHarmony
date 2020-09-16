/*
 * hisvb.h
 *
 * The SVB Device Driver for hisilicon
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

#ifndef __HISILICON_SVB_HEADER__
#define __HISILICON_SVB_HEADER__

enum power_domain {
	DOMAIN_MEDIA,
	DOMAIN_CORE,
	DOMAIN_CPU,
	DOMAIN_DDR,
	DOMAIN_GPU,
	DOMAIN_SVP,
	DOMAIN_OTHER,
};

#ifndef NUM_0
#define NUM_0	0
#define NUM_1	1
#define NUM_2	2
#define NUM_3	3
#define NUM_4	4
#define NUM_5	5
#define NUM_6	6
#define NUM_7	7
#define NUM_10	10
#endif

#endif /* __HISILICON_SVB_HEADER__ */
