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

#ifndef __HAL_VO_VIDEO_COMM_H__
#define __HAL_VO_VIDEO_COMM_H__

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
hi_void hal_video_set_layer_up_mode(hal_disp_layer layer, hi_u32 up_mode);
hi_void hal_video_set_layer_disp_rect(hal_disp_layer layer, hi_rect *rect);
hi_void hal_video_set_layer_video_rect(hal_disp_layer layer, hi_rect *rect);
hi_void hal_video_set_multi_area_lum_addr(hal_disp_layer layer, hi_u32 area_num, hi_ulong addr,
    hi_u16 stride);
hi_void hal_video_set_multi_area_chm_addr(hal_disp_layer layer, hi_u32 area_num, hi_ulong addr,
    hi_u16 stride);
#endif

#if VO_DESC("layer zme")
hi_void vo_hal_layer_set_zme_cfg(hal_disp_layer layer, hi_u32 vratio, hi_u32 hratio,
    vo_v0_zme_cfg *cfg, vo_zme_comm_pq_cfg *pq_cfg);
#endif

#if VO_DESC("cvfir")
hi_void vo_hal_layer_set_v1_cvfir_cfg(hi_u32 vratio, vdp_v1_cvfir_cfg *cfg,
    vo_zme_comm_pq_cfg *pq_cfg);
hi_void vo_hal_layer_set_v2_cvfir_cfg(hi_u32 vratio, vdp_v1_cvfir_cfg *cfg,
    vo_zme_comm_pq_cfg *pq_cfg);

hi_void vo_hal_layer_set_chroma_copy(hi_u32 layer, hi_bool chroma_copy_flag);
#endif

#if VO_DESC("layer")
/* video layer HFIR relative hal functions */
hi_void hal_video_hfir_set_ck_gt_en(hal_disp_layer layer, hi_u32 ck_gt_en);
hi_void hal_video_hfir_set_mid_en(hal_disp_layer layer, hi_u32 mid_en);
hi_void hal_video_hfir_set_hfir_mode(hal_disp_layer layer, hi_u32 hfir_mode);
hi_void hal_video_hfir_set_coef(hal_disp_layer layer, hfir_coef *coef);

hi_void hal_layer_enable_layer(hal_disp_layer layer, hi_u32 enable);
hi_void hal_layer_set_layer_data_fmt(hal_disp_layer layer, hal_disp_pixel_format data_fmt);
hi_void hal_layer_set_src_resolution(hal_disp_layer layer, const hi_rect *rect);
hi_void hal_layer_set_layer_in_rect(hal_disp_layer layer, hi_rect *rect);
hi_void hal_layer_set_zme_info(hal_disp_layer layer, hi_u32 width, hi_u32 height,
                               hal_disp_zme_outfmt data_fmt);
hi_void hal_layer_set_reg_up(hal_disp_layer layer);
hi_void hal_cbm_set_cbm_attr(hal_disp_layer layer, hi_vo_dev dev);
hi_void hal_cbm_set_cbm_bkg(hal_cbmmix mixer, hal_disp_bkcolor *bkg);
hi_void hal_cbm_set_cbm_mixer_prio(hi_vo_layer layer, hi_u8 prio, hi_u8 mixer_id);
#endif
#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of __HAL_VO_VIDEO_COMM_H__ */
