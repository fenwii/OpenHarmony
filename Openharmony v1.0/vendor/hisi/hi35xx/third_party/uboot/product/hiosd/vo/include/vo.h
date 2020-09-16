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

#ifndef __VO_H__
#define __VO_H__

#include "hi_common_vo.h"

#define VO_RECT_ALIGN                       2
#define VO_ALPHA_OPACITY                    0xFF /* opacity alpha */
#define VOU_ALIGN(val, align) (((val) + (align) - 1) & (~((align) - 1)))
#define VO_MAX_VTTH_WATERLINE                8191

/* typical value of video size */
typedef enum {
    VO_DISP_1080_WIDTH = 1920,
    VO_DISP_1080_HEIGHT = 1080,
    VO_DISP_720P_WIDTH = 1280,
    VO_DISP_720P_HEIGHT = 720,
    VO_DISP_D1_WIDTH = 720,
    VO_DISP_D1P_HEIGH = 576,
    VO_DISP_D1N_HEIGH = 480,
    VO_DISP_VGA_1024 = 1024,
    VO_DISP_VGA_768 = 768,
    VO_DISP_VGA_800 = 800,
    VO_DISP_VGA_600 = 600,
    VO_DISP_VIRT_WIDTH = 5000,
    VO_DISP_VIRT_HEIGHT = 5000,
    VO_DISP_8K_WIDTH = 8192,
    VO_DISP_8K_HEIGHT = 4320,
    VO_DISP_BUTT
} vo_disp_size;

int set_vobg(unsigned int dev, unsigned int rgb);
int start_vo(unsigned int dev, unsigned int type, unsigned int sync);
int stop_vo(unsigned int dev);
int start_gx(unsigned int layer, unsigned long addr, unsigned int strd, hi_rect gx_rect, unsigned int type);
int stop_gx(unsigned int layer);
int start_videolayer(unsigned int layer, unsigned long addr, unsigned int strd, hi_rect layer_rect);
int stop_videolayer(unsigned int layer);
hi_void vo_dcache_range(hi_phys_addr_t start_addr, hi_u64 size);
typedef struct {
    hi_bool video_enable;
    hi_bool video_config;
    hi_vo_csc layer_csc;
    hi_vo_video_layer_attr vou_video_attr;
} vo_layer_info;

#endif /* end of __VO_H__ */
