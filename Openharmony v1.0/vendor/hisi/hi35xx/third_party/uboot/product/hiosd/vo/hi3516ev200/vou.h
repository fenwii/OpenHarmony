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

#ifndef __VOU_H__
#define __VOU_H__

#include "hi3516ev200_vo.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of #ifdef __cplusplus */

int set_vobg(unsigned int dev, unsigned int rgb);
int start_vo(unsigned int dev, unsigned int type, unsigned int sync);
int stop_vo(unsigned int dev);
int start_videolayer(unsigned int layer, unsigned long addr, unsigned int strd, hi_vo_rect layer_rect);
int stop_videolayer(unsigned int layer);
int start_gx(unsigned int layer, unsigned long addr, unsigned int strd, hi_vo_rect gx_rect);
int stop_gx(unsigned int layer);

#ifdef __cplusplus
}
#endif /* end of #ifdef __cplusplus */

#endif /* end of #ifdef __VOU_H__ */
