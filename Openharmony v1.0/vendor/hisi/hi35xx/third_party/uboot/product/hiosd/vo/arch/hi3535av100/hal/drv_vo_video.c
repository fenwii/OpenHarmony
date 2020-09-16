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

#include "drv_vo_video.h"
#include "hi_math.h"
#include "vo.h"
#include "hal_vo.h"
#include "drv_vo.h"

#include <common.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")

#define VO_LAYER_DISP_RECT_W_MAX_OF_VHDX 3840
#define VO_LAYER_DISP_RECT_H_MAX_OF_VHDX 3840
#define VO_LAYER_DISP_RECT_W_MAX_OF_VHD1 1920
#define VO_LAYER_DISP_RECT_H_MAX_OF_VHD1 1920
#define VO_LAYER_DISP_RECT_W_MAX_OF_VSD0 720
#define VO_LAYER_DISP_RECT_H_MAX_OF_VSD0 720

#define VO_LAYER_CSC_MIN_COEF_VAL   (-2048)
#define VO_LAYER_CSC_MAX_COEF_VAL   2047

#if VO_DESC("layer zme & cvfir")

hi_void vo_drv_get_zme_comm_pq_cfg(vo_zme_ds_info *ds_info, vo_zme_mode zme_mode, vo_zme_comm_pq_cfg *pq_cfg)
{
    if (zme_mode == VO_ZME_TYP) {
        pq_cfg->vluma_offset = 0;  /*  v_phase_rand   ; */
        pq_cfg->vchroma_offset = 0;  /*  v_phase_rand_c ; */
        pq_cfg->vbluma_offset = 0;
        pq_cfg->vbchroma_offset = 0;
        pq_cfg->vl_flatdect_mode = 1;
        pq_cfg->vl_coringadj_en = 1;
        pq_cfg->vl_gain = 32; /* 32, vl gain typical */
        pq_cfg->vl_coring = 16; /* 16, vl coring typical */
        pq_cfg->vc_flatdect_mode = 1;
        pq_cfg->vc_coringadj_en = 1;
        pq_cfg->vc_gain = 32; /* 32, vc gain typical */
        pq_cfg->vc_coring = 16; /* 16, vc coring typical */
        pq_cfg->lhfir_offset = 0;
        pq_cfg->chfir_offset = 0;
        pq_cfg->hl_flatdect_mode = 1;
        pq_cfg->hl_coringadj_en = 1;
        pq_cfg->hl_gain = 32; /* 32, hl gain typical */
        pq_cfg->hl_coring = 16; /* 16, hl coring typical */
        pq_cfg->hc_flatdect_mode = 1;
        pq_cfg->hc_coringadj_en = 1;
        pq_cfg->hc_gain = 32; /* 32, hc gain typical */
        pq_cfg->hc_coring = 16; /* 16, hc coring typical */
    }
}

static hi_void vo_drv_get_zme_typ_pq_cfg(vo_zme_comm_pq_cfg *pq_cfg, hi_u32 zme_vprec, hi_u32 zme_hprec)
{
    /*
     * 32, gain typical
     * 16, coring typical
     */
    pq_cfg->vluma_offset = 0;  /*  v_phase_rand   ; */
    pq_cfg->vchroma_offset = 0;  /*  v_phase_rand_c ; */
    pq_cfg->vbluma_offset = 0;
    pq_cfg->vbchroma_offset = 0;
    pq_cfg->vl_flatdect_mode = 1;
    pq_cfg->vl_coringadj_en = 1;
    pq_cfg->vl_gain = 32; /* 32, vl gain typical */
    pq_cfg->vl_coring = 16; /* 16, vl coring typical */
    pq_cfg->vc_flatdect_mode = 1;
    pq_cfg->vc_coringadj_en = 1;
    pq_cfg->vc_gain = 32; /* 32, vc gain typical */
    pq_cfg->vc_coring = 16; /* 16, vc coring typical */
    pq_cfg->lhfir_offset = 0;
    pq_cfg->chfir_offset = 0;
    pq_cfg->hl_flatdect_mode = 1;
    pq_cfg->hl_coringadj_en = 1;
    pq_cfg->hl_gain = 32; /* 32, hl gain typical */
    pq_cfg->hl_coring = 16; /* 16, hl coring typical */
    pq_cfg->hc_flatdect_mode = 1;
    pq_cfg->hc_coringadj_en = 1;
    pq_cfg->hc_gain = 32; /* 32, hc gain typical */
    pq_cfg->hc_coring = 16; /* 16, hc coring typical */
}

hi_void vo_drv_get_cvfir_pq_cfg(vo_zme_ds_info *ds_info, vo_zme_mode zme_mode, vo_zme_comm_pq_cfg *comm_pq_cfg)
{
    hi_u32 zme_vprec = ds_info->zme_vprec;
    hi_u32 zme_hprec = ds_info->zme_hprec;

    if (zme_mode == VO_ZME_TYP) {
        vo_drv_get_zme_typ_pq_cfg(comm_pq_cfg, zme_vprec, zme_hprec);
    }
}

static hi_void vou_drv_set_layer_cvfir_mode(hi_u32 layer, vo_zme_mode zme_mode, vdp_v1_cvfir_cfg *cfg)
{
    hi_u32 vratio;
    vo_zme_ds_info ds_info = {0};
    vo_zme_comm_pq_cfg comm_pq_cfg = {0};

    ds_info.zme_vprec = ZME_VPREC;
    ds_info.zme_hprec = ZME_HPREC;

    vratio = ((cfg->in_height * ds_info.zme_vprec) / cfg->in_height);

    vo_drv_get_cvfir_pq_cfg(&ds_info, zme_mode, &comm_pq_cfg);

    vo_hal_layer_set_cvfir_cfg(layer, vratio, cfg, &comm_pq_cfg);
}

static hi_void vou_drv_set_layer_zme_mode(hi_u32 layer, vo_zme_mode zme_mode, vo_v0_zme_cfg *cfg)
{
    hi_u32 hratio;
    hi_u32 vratio;
    vo_zme_ds_info ds_info = {0};
    vo_zme_comm_pq_cfg comm_pq_cfg = {0};

    ds_info.zme_vprec = ZME_VPREC;
    ds_info.zme_hprec = ZME_HPREC;

    vratio = (cfg->in_height * ds_info.zme_vprec / cfg->out_height);
    hratio = (cfg->in_width * ds_info.zme_hprec / cfg->out_width);

    vo_drv_get_zme_comm_pq_cfg(&ds_info, zme_mode, &comm_pq_cfg);
    vo_hal_layer_set_zme_cfg(layer, vratio, hratio, cfg, &comm_pq_cfg);
}

#endif

#if VO_DESC("layer")
hi_void vo_drv_layer_info_init(hi_void)
{
    hi_s32 i;
    hi_u32 ctx_len;
    vo_drv_layer *drv_layer_ctx = HI_NULL;

    drv_layer_ctx = vo_drv_get_layer_ctx(0);
    ctx_len = sizeof(vo_drv_layer) * HI_VO_MAX_LAYER_NUM;
    memset(drv_layer_ctx, 0, ctx_len);

    for (i = 0; i < HI_VO_MAX_LAYER_NUM; i++) {
        drv_layer_ctx = vo_drv_get_layer_ctx(i);

        if (i == VO_SW_LAYER_VHD0) {
            drv_layer_ctx->bind_dev = VO_DEV_DHD0;
        } else if (i == VO_SW_LAYER_VHD1) {
            drv_layer_ctx->bind_dev = VO_DEV_DHD1;
        } else if (i == VO_SW_LAYER_VHD2) {
            drv_layer_ctx->bind_dev = VO_DEV_DHD0;
        } else if (i == VO_SW_LAYER_VSD0) {
            drv_layer_ctx->bind_dev = VO_DEV_DSD0;
        }
    }

    return;
}
#endif

#if VO_DESC("layer")

static hi_void vo_drv_video_set_zme_enable_cfg(hi_vo_dev dev, hi_u32 layer,
    vdp_vid_ip_cfg *vid_cfg)
{
    vo_v0_zme_cfg zme_cfg = { 0 };

    zme_cfg.ck_gt_en = 1;
    zme_cfg.in_height = vid_cfg->vid_ih;
    zme_cfg.out_height = vid_cfg->vid_oh;
    zme_cfg.out_fmt = VDP_PROC_FMT_SP_422;
    zme_cfg.out_pro = VDP_RMODE_PROGRESSIVE;
    zme_cfg.lvfir_mode = 0;
    /* cvfir_mode copy */
    zme_cfg.cvfir_mode = 0;
    zme_cfg.lvmid_en = 0;
    zme_cfg.cvmid_en = 0;
    zme_cfg.vfir_1tap_en = 0;
    zme_cfg.vl_shootctrl_en = 0;
    zme_cfg.vl_shootctrl_mode = 0;
    zme_cfg.vc_shootctrl_en = 0;
    zme_cfg.vc_shootctrl_mode = 0;

    zme_cfg.in_width = vid_cfg->vid_iw;
    zme_cfg.out_width = vid_cfg->vid_ow;
    zme_cfg.lhfir_mode = 0;
    /* chfir_mode copy */
    zme_cfg.chfir_mode = 0;
    zme_cfg.lhmid_en = 0;
    zme_cfg.chmid_en = 0;
    zme_cfg.non_lnr_en = 0;
    zme_cfg.hl_shootctrl_en = 0;
    zme_cfg.hl_shootctrl_mode = 0;
    zme_cfg.hc_shootctrl_en = 0;
    zme_cfg.hc_shootctrl_mode = 0;

    if (vid_cfg->zme_en == HI_TRUE) {
        zme_cfg.lhfir_en = 1;
        zme_cfg.chfir_en = 1;
        zme_cfg.lvfir_en = 1;
        zme_cfg.cvfir_en = 1;
    } else {
        zme_cfg.lhfir_en = 0;
        zme_cfg.chfir_en = 0;
        zme_cfg.lvfir_en = 0;
        zme_cfg.cvfir_en = 1;
    }

    if (vo_drv_is_progressive(dev) == HI_FALSE) {
        zme_cfg.out_pro = VDP_RMODE_INTERFACE;
    }

    vou_drv_set_layer_zme_mode(layer, VO_ZME_TYP, &zme_cfg);
}

static hi_void vo_drv_video_set_cvfir_enable_cfg(hi_vo_dev dev, hi_u32 layer,
    vdp_vid_ip_cfg *vid_cfg)
{
    vdp_v1_cvfir_cfg cvfir_cfg = { 0 };

    cvfir_cfg.hfir_order = 0;
    cvfir_cfg.lhfir_en = 0;
    cvfir_cfg.chfir_en = 0;
    cvfir_cfg.lhmid_en = 0;
    cvfir_cfg.chmid_en = 0;
    cvfir_cfg.lhfir_mode = 0;
    cvfir_cfg.chfir_mode = 0;
    cvfir_cfg.hl_shootctrl_en = 0;
    cvfir_cfg.hl_shootctrl_mode = 0;
    cvfir_cfg.hc_shootctrl_en = 0;
    cvfir_cfg.hc_shootctrl_mode = 0;
    cvfir_cfg.lvfir_en = 0;
    cvfir_cfg.lvmid_en = 0;
    cvfir_cfg.lvfir_mode = 0;
    cvfir_cfg.vl_shootctrl_en = 0;
    cvfir_cfg.vl_shootctrl_mode = 0;
    cvfir_cfg.vc_shootctrl_en = 0;
    cvfir_cfg.vc_shootctrl_mode = 0;

    /* CVFIR */
    cvfir_cfg.ck_gt_en = 1;
    cvfir_cfg.cvfir_en = 1;
    cvfir_cfg.cvmid_en = 0;

    cvfir_cfg.cvfir_mode = 0;
    cvfir_cfg.out_pro = VDP_RMODE_PROGRESSIVE;

    if (vo_drv_is_progressive(dev) == HI_FALSE) {
        cvfir_cfg.out_pro = VDP_RMODE_INTERFACE;
    }
    cvfir_cfg.out_fmt = VDP_PROC_FMT_SP_422;
    cvfir_cfg.in_width = vid_cfg->vid_iw;
    cvfir_cfg.in_height = vid_cfg->vid_ih;
    cvfir_cfg.out_width = vid_cfg->vid_ow;
    cvfir_cfg.out_height = vid_cfg->vid_oh;
    vou_drv_set_layer_cvfir_mode(layer, VO_ZME_TYP, &cvfir_cfg);
}

hi_void vo_drv_video_set_zme_enable(hi_u32 layer, vdp_vid_ip_cfg *vid_cfg)
{
    hi_vo_dev dev;

    if ((vid_cfg->vid_iw == 0) || (vid_cfg->vid_ih == 0) ||
        (vid_cfg->vid_ow == 0) || (vid_cfg->vid_oh == 0)) {
        vo_err_trace("layer(%d) ZME error: input w=%d,h=%d,output w=%d,h=%d!\n",
            layer, vid_cfg->vid_iw, vid_cfg->vid_ih, vid_cfg->vid_ow, vid_cfg->vid_oh);
        return;
    }

    dev = vou_drv_get_video_layer_bind_dev(layer);
    if (layer == VDP_LAYER_VID0) {
        vo_drv_video_set_zme_enable_cfg(dev, layer, vid_cfg);
    } else if ((layer == VDP_LAYER_VID1) || (layer == VDP_LAYER_VID2)) {
        vo_drv_video_set_cvfir_enable_cfg(dev, layer, vid_cfg);
    } else if (layer == VDP_LAYER_VID3) {
        vo_hal_layer_set_chroma_copy(layer, HI_TRUE);
    }
}

#endif

#if VO_DESC("layer")

static hi_void vo_drv_get_layer_attr_max_rect(hi_vo_layer layer, hi_u32 *width, hi_u32 *height)
{
    *width = VO_LAYER_DISP_RECT_W_MAX_OF_VHDX;
    *height = VO_LAYER_DISP_RECT_H_MAX_OF_VHDX;

#if (HICHIP == HI3535A_V100)
    if (layer == VO_SW_LAYER_VHD1) {
        *width = VO_LAYER_DISP_RECT_W_MAX_OF_VHD1;
        *height = VO_LAYER_DISP_RECT_H_MAX_OF_VHD1;
    }
#endif

    if (layer == VO_SW_LAYER_VSD0) {
        *width = VO_LAYER_DISP_RECT_W_MAX_OF_VSD0;
        *height = VO_LAYER_DISP_RECT_H_MAX_OF_VSD0;
    }
}

hi_s32 vo_drv_check_layer_attr_display_rect(hi_vo_layer layer, const hi_rect *rect)
{
    hi_u32 max_width;
    hi_u32 max_height;

    if ((layer >= VO_SW_LAYER_VHD0) && (layer <= VO_SW_LAYER_VSD0)) {
        vo_drv_get_layer_attr_max_rect(layer, &max_width, &max_height);
        if ((rect->width > max_width) || (rect->height > max_height)) {
            vo_err_trace("VO layer(%d) disp rect width(%d) height(%d) can't be larger than %dx%d!\n",
                layer, rect->width, rect->height,
                max_width, max_height);
            return HI_ERR_VO_ILLEGAL_PARAM;
        }
    } else if (layer < VOU_SW_LAYER_BUTT) {
    } else {
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}
#endif

#if VO_DESC("layer")

hal_disp_layer vou_drv_convert_layer(hi_vo_layer layer)
{
    hal_disp_layer disp_layer = HAL_DISP_LAYER_BUTT;

    switch (layer) {
        case VO_HAL_LAYER_VHD0:
            disp_layer = HAL_DISP_LAYER_VHD0;
            break;

        case VO_HAL_LAYER_VHD1:
            disp_layer = HAL_DISP_LAYER_VHD1;
            break;

        case VO_HAL_LAYER_VHD2:
            disp_layer = HAL_DISP_LAYER_VHD2;
            break;

        case VO_HAL_LAYER_VSD0:
            disp_layer = HAL_DISP_LAYER_VSD0;
            break;

        default:
            break;
    }

    return disp_layer;
}
#endif

hi_void vo_drv_get_layer_csc_coef_range(hi_s32 *min_coef, hi_s32 *max_coef)
{
    *min_coef = VO_LAYER_CSC_MIN_COEF_VAL;
    *max_coef = VO_LAYER_CSC_MAX_COEF_VAL;
}

hi_void vou_drv_layer_csc_enable(hi_vo_layer layer, hi_bool csc_en)
{
    hal_layer_csc_set_enable_ck_gt_en(layer, csc_en, HI_FALSE);
}

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
