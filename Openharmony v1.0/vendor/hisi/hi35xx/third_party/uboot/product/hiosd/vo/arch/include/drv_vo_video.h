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

#ifndef __DRV_VO_VIDEO_H__
#define __DRV_VO_VIDEO_H__

#include "drv_vo_video_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")

#if VO_DESC("layer")

typedef struct {
    hi_u32 vid_iw;
    hi_u32 vid_ih;
    hi_u32 vid_ow;
    hi_u32 vid_oh;

    hi_u32 zme_en;
    hi_u32 hfir_en;
    hi_u32 csc_en;
    hi_u32 hdr_en;
} vdp_vid_ip_cfg;

typedef struct {
    hi_u32 zme_vprec;
    hi_u32 zme_hprec;
} vo_zme_ds_info;

#endif

#if VO_DESC("layer zme")
hal_disp_layer vou_drv_convert_layer(hi_vo_layer layer);
#endif

#if VO_DESC("layer")
hi_void vo_drv_get_zme_comm_pq_cfg(vo_zme_ds_info *ds_info,
                                   vo_zme_mode zme_mode,
                                   vo_zme_comm_pq_cfg *comm_pq_cfg);

hi_void vo_drv_get_cvfir_pq_cfg(vo_zme_ds_info *ds_info,
                                vo_zme_mode zme_mode,
                                vo_zme_comm_pq_cfg *comm_pq_cfg);
hi_void vo_drv_layer_info_init(hi_void);
hi_void vo_drv_video_set_zme_enable(hi_u32 layer, vdp_vid_ip_cfg *vid_cfg);
#endif

hi_void vou_drv_layer_csc_enable(hi_vo_layer layer, hi_bool csc_en);
hi_void vo_drv_get_layer_csc_coef_range(hi_s32 *min_coef, hi_s32 *max_coef);
#if VO_DESC("layer")
hi_s32 vo_drv_check_video_layer_id(hi_vo_layer layer);
hi_s32 vo_drv_check_layer_attr_display_rect(hi_vo_layer layer, const hi_rect *rect);
#endif

#if VO_DESC("layer open")
hi_void vo_drv_layer_open(hi_vo_layer layer_id, const hi_vo_video_layer_attr *video_attr);
hi_void vo_drv_layer_close(hi_vo_layer layer_id);
#endif

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of __DRV_VO_VIDEO_H__ */
