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

#ifndef __VOU_COEF_ORG_H__
#define __VOU_COEF_ORG_H__

#include "vou_coef.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of #ifdef __cplusplus */

/* RGB->YUV601 */
extern const vo_csc_coef g_csc_rgb_to_yuv601_pc;
/* RGB->YUV709 */
extern const vo_csc_coef g_csc_rgb_to_yuv709_pc;
/* YUV601->RGB */
extern const vo_csc_coef g_csc_yuv601_to_rgb_pc;
/* YUV709->RGB */
extern const vo_csc_coef g_csc_yuv709_to_rgb_pc;
/* YUV601->YUV709 */
extern const vo_csc_coef g_csc_yuv_to_yuv_601_709;
/* YUV709->YUV601 */
extern const vo_csc_coef g_csc_yuv_to_yuv_709_601;
/* YUV601->YUV709 */
extern const vo_csc_coef g_csc_init;

extern const int g_sin_table[61]; /* 61 sin table array */
extern const int g_cos_table[61]; /* 61 cos table array */

#ifdef __cplusplus
}
#endif /* end of #ifdef __cplusplus */

#endif
