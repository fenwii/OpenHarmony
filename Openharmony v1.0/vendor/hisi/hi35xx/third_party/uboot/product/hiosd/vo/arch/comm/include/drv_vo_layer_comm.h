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

#ifndef __DRV_VO_LAYER_COMM_H__
#define __DRV_VO_LAYER_COMM_H__

#include "hi_inner_vo.h"
#include "drv_vo_coef_comm.h"
#include "hal_vo_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")

#if VO_DESC("layer")
#define VO_LAYER_CSC_SCALE2P_DEF_VAL 0xa
#define VO_LAYER_CSC_CLIP_MIN 0x0
#define VO_LAYER_CSC_CLIP_MAX 0xfff
#endif

#if VO_DESC("layer csc")
hi_s32 vo_drv_get_csc_matrix(hi_vo_csc_matrix csc_matrix, const csc_coef **csc_tmp);
hi_void vo_drv_calculate_yuv2rgb(hal_csc_value *csc_value, const csc_coef *csc_tmp, csc_coef *coef);
hi_void vo_drv_calculate_rgb2yuv(hal_csc_value *csc_value, const csc_coef *csc_tmp, csc_coef *coef);
hi_void vo_drv_clip_layer_csc_coef(csc_coef *coef);
hi_void vou_drv_calc_csc_matrix(const hi_vo_csc *csc, hi_vo_csc_matrix csc_matrix, csc_coef *coef);
hi_void vou_drv_layer_csc_config(hi_vo_layer layer, hi_vo_csc *csc, csc_coef_param *csc_param);
hi_void vou_drv_get_layer_csc_param(hi_vo_layer layer, csc_coef_param *csc_param);
#endif
#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* end of #ifdef __cplusplus */
#endif

#endif /* end of __DRV_VO_LAYER_COMM_H__ */
