/*
 * hw_decompress.c
 *
 * Files related to software decompression and hardware decompression
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

#if (defined CONFIG_TARGET_HI3559AV100) || (defined CONFIG_HI3559AV100) || \
	(defined CONFIG_TARGET_HI3556AV100) || (defined CONFIG_TARGET_HI3519AV100) ||\
	(defined CONFIG_TARGET_HI3569V100)  || (defined CONFIG_HI3569V100)
#include "hw_decompress_v2.c"
#endif

#if ((defined CONFIG_TARGET_HI3559V200) || (defined CONFIG_TARGET_HI3556V200) || \
	(defined CONFIG_TARGET_HI3516DV300) || (defined CONFIG_TARGET_HI3516AV300) || \
	(defined CONFIG_TARGET_HI3516CV500) || (defined CONFIG_TARGET_HI3516EV200) || \
	(defined CONFIG_TARGET_HI3516EV300) || (defined CONFIG_TARGET_HI3518EV300) || \
	(defined CONFIG_TARGET_HI3516DV200) || (defined CONFIG_TARGET_HI3566V100)  || \
	(defined CONFIG_TARGET_HI3562V100))
#include "hw_decompress_v1.c"
#endif
