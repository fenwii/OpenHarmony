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
#ifndef __MKP_VO_BMP_H__
#define __MKP_VO_BMP_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

typedef struct {
    hi_u16 bi_size;
    hi_u32 bi_width;
    hi_s32 bi_height;
    hi_u16 bi_planes;
    hi_u16 bi_bit_count;
    hi_u32 bi_compression;
    hi_u32 bi_size_image;
    hi_u32 bi_x_pels_per_meter;
    hi_u32 bi_y_pels_per_meter;
    hi_u32 bi_clr_used;
    hi_u32 bi_clr_important;
} osd_bitmap_info_header;

typedef struct {
    hi_u8 rgb_blue;
    hi_u8 rgb_green;
    hi_u8 rgb_red;
    hi_u8 rgb_reserved;
} osd_rgb_quad;

typedef struct {
    hi_u32 bf_size;
    hi_u16 bf_reserved1;
    hi_u16 bf_reserved2;
    hi_u32 bf_off_bits;
} osd_bitmap_file_header;

typedef struct {
    osd_bitmap_info_header bmi_header;
    osd_rgb_quad bmi_colors[1];
} osd_bitmap_info;

typedef struct {
    hi_u32 width;       /* out */
    hi_u32 height;      /* out */
    hi_u32 stride;      /* in */
    hi_phys_addr_t rgb_buffer; /* in */
} osd_logo_t;

typedef enum {
    OSD_BI_BIT_COUNT_1BPP = 1,
    OSD_BI_BIT_COUNT_4BPP = 4,
    OSD_BI_BIT_COUNT_8BPP = 8,
    OSD_BI_BIT_COUNT_16BPP = 16,
    OSD_BI_BIT_COUNT_24BPP = 24,
    OSD_BI_BIT_COUNT_32BPP = 32,
} osd_bi_bit_count;

hi_s32 load_bmp(hi_phys_addr_t bmp_addr, osd_logo_t *video_logo);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of #ifndef __MKP_VO_BMP__ */
