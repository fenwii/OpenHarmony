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

#include "mkp_vo_bmp.h"
#include "common.h"

hi_s32 load_bmp(hi_phys_addr_t bmp_addr, osd_logo_t *video_logo)
{
    hi_u16 bpp;
    osd_bitmap_file_header bmp_file_header;
    osd_bitmap_info bmp_info;

    memcpy(&bmp_file_header, (char *)(uintptr_t)(bmp_addr + sizeof(hi_u16)), sizeof(osd_bitmap_file_header));
    memcpy(&bmp_info, (char *)(uintptr_t)(bmp_addr + sizeof(hi_u16) + sizeof(osd_bitmap_file_header)), sizeof(osd_bitmap_info));
    video_logo->width = bmp_info.bmi_header.bi_width;
    video_logo->height = bmp_info.bmi_header.bi_height;
    video_logo->stride = bmp_info.bmi_header.bi_width * (OSD_BI_BIT_COUNT_16BPP / 8); /* 8 bits per bytes */
    video_logo->rgb_buffer = bmp_addr + bmp_file_header.bf_off_bits;

    bpp = bmp_info.bmi_header.bi_bit_count;
    if (bpp != OSD_BI_BIT_COUNT_16BPP) { /* 16 bits, 2bytes per pixel bitmap format */
        printf("bitmap format bpp=%d not supported! only supoort format bpp=%d\n", bpp, OSD_BI_BIT_COUNT_16BPP);
        return -1;
    }
    return 0;
}
