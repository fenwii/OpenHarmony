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

#ifndef __HAL_VO_LAYER_COMM_H__
#define __HAL_VO_LAYER_COMM_H__

#include "hal_vo_def.h"
#include "drv_vo_coef_comm.h"
#include "hi_inner_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")
#if VO_DESC("layer")
hi_void hal_video_set_layer_alpha(hal_disp_layer layer, hi_u32 arange);
hi_void hal_layer_set_csc_coef(hal_disp_layer layer, csc_coef *coef);
hi_void hal_layer_set_layer_global_alpha(hal_disp_layer layer, hi_u8 alpha0);
hi_void hal_layer_csc_set_enable_ck_gt_en(hal_disp_layer layer, hi_bool csc_en, hi_bool ck_gt_en);
#endif
#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of __HAL_VO_LAYER_COMM_H__ */
