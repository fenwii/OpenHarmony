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

#ifndef __HAL_VO_GFX_COMM_H__
#define __HAL_VO_GFX_COMM_H__

#include "hal_vo_def.h"
#include "drv_vo_coef_comm.h"
#include "hi_inner_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")
#if VO_DESC("gfx uboot only")
hi_void hal_gfx_set_layer_disp_rect(hal_disp_layer layer, hi_rect *rect);
hi_void hal_gfx_set_layer_video_rect(hal_disp_layer layer, hi_rect *rect);
hi_void hal_gfx_enable_layer(hal_disp_layer layer, hi_u32 enable);
hi_void hal_gfx_set_layer_data_fmt(hal_disp_layer layer, hal_disp_pixel_format data_fmt);
hi_void hal_gfx_set_layer_in_rect(hal_disp_layer layer, hi_rect *rect);
hi_bool hal_gfx_set_reg_up(hal_disp_layer layer);
hi_void hal_gfx_set_gfx_pre_mult(hal_disp_layer layer, hi_u32 enable);
hi_void hal_gfx_set_gfx_addr(hal_disp_layer layer, hi_phys_addr_t l_addr);
hi_void hal_gfx_set_gfx_stride(hal_disp_layer layer, hi_u16 pitch);
hi_void hal_gfx_set_src_resolution(hal_disp_layer layer, hi_rect *rect);
#endif

#if VO_DESC("gfx")
hi_void hal_gfx_set_pixel_alpha_range(hal_disp_layer layer, hi_u32 arange);
#endif
#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of __HAL_VO_GFX_COMM_H__ */
