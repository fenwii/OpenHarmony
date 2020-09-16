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

#include "hal_vo_video_comm.h"
#include "drv_vo.h"
#include "hal_vo.h"
#include "hi_math.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */
#if VO_DESC("UBOOT_VO")

#if VO_DESC("video")

hi_void hal_video_set_layer_up_mode(hal_disp_layer layer, hi_u32 up_mode)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_v0_ctrl v0_ctrl;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_layer_return(layer);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_ctrl.u32));
    v0_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_ctrl.bits.rgup_mode = up_mode;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_ctrl.u32);
}

hi_void hal_video_set_layer_disp_rect(hal_disp_layer layer, hi_rect *rect)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_dfpos v0_dfpos;
    volatile reg_v0_dlpos v0_dlpos;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_layer_return(layer);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_dfpos.u32));
    v0_dfpos.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_dfpos.bits.disp_xfpos = rect->x;
    v0_dfpos.bits.disp_yfpos = rect->y;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_dfpos.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_dlpos.u32));
    v0_dlpos.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_dlpos.bits.disp_xlpos = rect->x + rect->width - 1;
    v0_dlpos.bits.disp_ylpos = rect->y + rect->height - 1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_dlpos.u32);
}

hi_void hal_video_set_layer_video_rect(hal_disp_layer layer, hi_rect *rect)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_vfpos v0_vfpos;
    volatile reg_v0_vlpos v0_vlpos;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_layer_return(layer);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_vfpos.u32));
    v0_vfpos.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_vfpos.bits.video_xfpos = rect->x;
    v0_vfpos.bits.video_yfpos = rect->y;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_vfpos.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_vlpos.u32));
    v0_vlpos.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_vlpos.bits.video_xlpos = rect->x + rect->width - 1;
    v0_vlpos.bits.video_ylpos = rect->y + rect->height - 1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_vlpos.u32);
}

hi_void hal_video_set_multi_area_lum_addr(hal_disp_layer layer, hi_u32 area_num, hi_ulong addr,
    hi_u16 stride)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    hi_ulong reg_addr;
    reg_vid_stride vid_stride;

    vo_hal_check_video_layer_return(layer);

    /* low 32 bits to vid_addr_l */
    reg_addr = vou_get_vid_abs_addr(layer, (hi_uintptr_t) & (vo_reg->vid_addr_l));
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) reg_addr, get_low_addr(addr));

    /* high 32 bits to vid_addr_h */
    reg_addr = vou_get_vid_abs_addr(layer, (hi_uintptr_t) & (vo_reg->vid_addr_h));
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) reg_addr, get_high_addr(addr));

    reg_addr = vou_get_vid_abs_addr(layer, (hi_uintptr_t) & (vo_reg->vid_stride.u32));
    vid_stride.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) reg_addr);
    vid_stride.bits.lm_stride = stride;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) reg_addr, vid_stride.u32);
}

hi_void hal_video_set_multi_area_chm_addr(hal_disp_layer layer, hi_u32 area_num, hi_ulong addr,
    hi_u16 stride)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    hi_ulong reg_addr;
    reg_vid_stride vid_stride;

    vo_hal_check_video_layer_return(layer);

    /* low 32 bits to vid_caddr_l */
    reg_addr = vou_get_vid_abs_addr(layer, (hi_uintptr_t) & (vo_reg->vid_caddr_l));
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) reg_addr, get_low_addr(addr));

    /* high 32 bits to vid_caddr_h */
    reg_addr = vou_get_vid_abs_addr(layer, (hi_uintptr_t) & (vo_reg->vid_caddr_h));
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) reg_addr, get_high_addr(addr));

    reg_addr = vou_get_vid_abs_addr(layer, (hi_uintptr_t) & (vo_reg->vid_stride.u32));
    vid_stride.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) reg_addr);
    vid_stride.bits.chm_stride = stride;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) reg_addr, vid_stride.u32);
}

static hi_void hal_layer_set_layer_zme_info(hal_disp_layer layer, hi_u32 width, hi_u32 height,
    hal_disp_zme_outfmt zme_out_fmt)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_zme_vinfo v0_zme_vinfo;
    volatile reg_v0_zme_hinfo v0_zme_hinfo;
    volatile reg_v1_cvfir_vinfo v1_cvfir_vinfo;
    volatile reg_v2_cvfir_vinfo v2_cvfir_vinfo;
    volatile hi_ulong addr_reg;

    if (layer == HAL_DISP_LAYER_VHD0) {
        addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v0_zme_vinfo.u32);
        v0_zme_vinfo.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
        v0_zme_vinfo.bits.vzme_ck_gt_en = 1;
        v0_zme_vinfo.bits.out_height = height - 1;
        v0_zme_vinfo.bits.out_fmt = zme_out_fmt;
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_zme_vinfo.u32);

        addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v0_zme_hinfo.u32);
        v0_zme_hinfo.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
        v0_zme_hinfo.bits.out_width = width - 1;
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_zme_hinfo.u32);
    } else if (layer == HAL_DISP_LAYER_VHD1) {
        /* vertical info */
        addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v1_cvfir_vinfo.u32);
        v1_cvfir_vinfo.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
        v1_cvfir_vinfo.bits.vzme_ck_gt_en = 1;
        v1_cvfir_vinfo.bits.out_height = height - 1;
        v1_cvfir_vinfo.bits.out_fmt = zme_out_fmt;
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v1_cvfir_vinfo.u32);
    } else if (layer == HAL_DISP_LAYER_VHD2) {
        /* vertical info */
        addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v2_cvfir_vinfo.u32);
        v2_cvfir_vinfo.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
        v2_cvfir_vinfo.bits.vzme_ck_gt_en = 1;
        v2_cvfir_vinfo.bits.out_height = height - 1;
        v2_cvfir_vinfo.bits.out_fmt = zme_out_fmt;
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v2_cvfir_vinfo.u32);
    }
}

hi_void hal_layer_set_zme_info(hal_disp_layer layer, hi_u32 width, hi_u32 height,
                               hal_disp_zme_outfmt zme_out_fmt)
{
    if (vo_hal_is_video_layer(layer)) {
        hal_layer_set_layer_zme_info(layer, width, height, zme_out_fmt);
    }
}

hi_void hal_layer_enable_layer(hal_disp_layer layer, hi_u32 enable)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_ctrl v0_ctrl;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_layer_return(layer);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_ctrl.u32));
    v0_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_ctrl.bits.surface_en = enable;
    v0_ctrl.bits.nosec_flag = 1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_ctrl.u32);
}

hi_void hal_layer_set_layer_data_fmt(hal_disp_layer layer, hal_disp_pixel_format data_fmt)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vid_src_info vid_src_info;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_layer_return(layer);

    addr_reg = vou_get_vid_abs_addr(layer, (hi_uintptr_t) & (vo_reg->vid_src_info.u32));
    vid_src_info.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    vid_src_info.bits.data_type = data_fmt;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, vid_src_info.u32);
}

hi_void hal_layer_set_src_resolution(hal_disp_layer layer, const hi_rect *rect)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_vid_src_reso vid_src_reso;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_layer_return(layer);

    addr_reg = vou_get_vid_abs_addr(layer, (hi_uintptr_t) & (vo_reg->vid_src_reso.u32));
    vid_src_reso.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    vid_src_reso.bits.src_w = rect->width - 1;
    vid_src_reso.bits.src_h = rect->height - 1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, vid_src_reso.u32);
}

#if VO_DESC("layer zme")
static hi_void vo_hal_layer_set_zme_vinfo_basic_cfg(hal_disp_layer layer, hi_u32 vratio,
    vo_v0_zme_cfg *cfg, vo_zme_comm_pq_cfg *pq_cfg)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_zme_vinfo v0_zme_vinfo;
    volatile reg_v0_zme_vsp v0_zme_vsp;
    volatile reg_v0_zme_voffset v0_zme_voffset;
    volatile reg_v0_zme_vboffset v0_zme_vboffset;

    v0_zme_vinfo.u32 = vo_reg->v0_zme_vinfo.u32;
    v0_zme_vsp.u32 = vo_reg->v0_zme_vsp.u32;
    v0_zme_voffset.u32 = vo_reg->v0_zme_voffset.u32;
    v0_zme_vboffset.u32 = vo_reg->v0_zme_vboffset.u32;

    v0_zme_vinfo.bits.out_height = cfg->out_height - 1;
    v0_zme_vinfo.bits.out_fmt = cfg->out_fmt;
    v0_zme_vinfo.bits.out_pro = cfg->out_pro;
    v0_zme_vinfo.bits.vzme_ck_gt_en = cfg->ck_gt_en;
    v0_zme_vsp.bits.vratio = vratio;
    v0_zme_vsp.bits.graphdet_en = cfg->graphdet_en;
    v0_zme_vsp.bits.cvfir_mode = cfg->cvfir_mode;
    v0_zme_vsp.bits.lvfir_mode = cfg->lvfir_mode;
    v0_zme_vsp.bits.vfir_1tap_en = cfg->vfir_1tap_en;
    v0_zme_vsp.bits.cvmid_en = cfg->cvmid_en;
    v0_zme_vsp.bits.lvmid_en = cfg->lvmid_en;
    v0_zme_vsp.bits.cvfir_en = cfg->cvfir_en;
    v0_zme_vsp.bits.lvfir_en = cfg->lvfir_en;
    v0_zme_voffset.bits.vchroma_offset = pq_cfg->vchroma_offset;
    v0_zme_voffset.bits.vluma_offset = pq_cfg->vluma_offset;
    v0_zme_vboffset.bits.vbchroma_offset = pq_cfg->vbchroma_offset;
    v0_zme_vboffset.bits.vbluma_offset = pq_cfg->vbluma_offset;

    vo_reg->v0_zme_vinfo.u32 = v0_zme_vinfo.u32 ;
    vo_reg->v0_zme_vsp.u32 = v0_zme_vsp.u32;
    vo_reg->v0_zme_voffset.u32 = v0_zme_voffset.u32;
    vo_reg->v0_zme_vboffset.u32 = v0_zme_vboffset.u32;
}

static hi_void vo_hal_layer_set_zme_vinfo_ext_cfg(hal_disp_layer layer, vo_v0_zme_cfg *cfg,
    vo_zme_comm_pq_cfg *pq_cfg)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_zme_vl_shootctrl v0_zme_vl_shootctrl;
    volatile reg_v0_zme_vc_shootctrl v0_zme_vc_shootctrl;

    v0_zme_vl_shootctrl.u32 = vo_reg->v0_zme_vl_shootctrl.u32;
    v0_zme_vc_shootctrl.u32 = vo_reg->v0_zme_vc_shootctrl.u32;

    v0_zme_vl_shootctrl.bits.vl_coring = pq_cfg->vl_coring;
    v0_zme_vl_shootctrl.bits.vl_gain = pq_cfg->vl_gain;
    v0_zme_vl_shootctrl.bits.vl_coringadj_en = pq_cfg->vl_coringadj_en;
    v0_zme_vl_shootctrl.bits.vl_flatdect_mode = pq_cfg->vl_flatdect_mode;
    v0_zme_vl_shootctrl.bits.vl_shootctrl_mode = cfg->vl_shootctrl_mode;
    v0_zme_vl_shootctrl.bits.vl_shootctrl_en = cfg->vl_shootctrl_en;
    v0_zme_vc_shootctrl.bits.vc_coring = pq_cfg->vc_coring;
    v0_zme_vc_shootctrl.bits.vc_gain = pq_cfg->vc_gain;
    v0_zme_vc_shootctrl.bits.vc_coringadj_en = pq_cfg->vc_coringadj_en;
    v0_zme_vc_shootctrl.bits.vc_flatdect_mode = pq_cfg->vc_flatdect_mode;
    v0_zme_vc_shootctrl.bits.vc_shootctrl_mode = cfg->vc_shootctrl_mode;
    v0_zme_vc_shootctrl.bits.vc_shootctrl_en = cfg->vc_shootctrl_en;

    vo_reg->v0_zme_vl_shootctrl.u32 = v0_zme_vl_shootctrl.u32;
    vo_reg->v0_zme_vc_shootctrl.u32 = v0_zme_vc_shootctrl.u32;
}

static hi_void vo_hal_layer_set_zme_hinfo_basic_cfg(hal_disp_layer layer, hi_u32 hratio,
    vo_v0_zme_cfg *cfg, vo_zme_comm_pq_cfg *pq_cfg)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_zme_hinfo v0_zme_hinfo;
    volatile reg_v0_zme_hsp v0_zme_hsp;
    volatile reg_v0_zme_hloffset v0_zme_hloffset;
    volatile reg_v0_zme_hcoffset v0_zme_hcoffset;

    v0_zme_hinfo.u32 = vo_reg->v0_zme_hinfo.u32;
    v0_zme_hsp.u32 = vo_reg->v0_zme_hsp.u32;
    v0_zme_hloffset.u32 = vo_reg->v0_zme_hloffset.u32;
    v0_zme_hcoffset.u32 = vo_reg->v0_zme_hcoffset.u32;

    v0_zme_hinfo.bits.out_width = cfg->out_width - 1;
    v0_zme_hinfo.bits.hzme_ck_gt_en = cfg->ck_gt_en;
    v0_zme_hsp.bits.hratio = hratio;
    v0_zme_hsp.bits.hfir_order = cfg->hfir_order;
    v0_zme_hsp.bits.chfir_mode = cfg->chfir_mode;
    v0_zme_hsp.bits.lhfir_mode = cfg->lhfir_mode;
    v0_zme_hsp.bits.non_lnr_en = cfg->non_lnr_en;
    v0_zme_hsp.bits.chmid_en = cfg->chmid_en;
    v0_zme_hsp.bits.lhmid_en = cfg->lhmid_en;
    v0_zme_hsp.bits.chfir_en = cfg->chfir_en;
    v0_zme_hsp.bits.lhfir_en = cfg->lhfir_en;
    v0_zme_hloffset.bits.lhfir_offset = pq_cfg->lhfir_offset;
    v0_zme_hcoffset.bits.chfir_offset = pq_cfg->chfir_offset;

    vo_reg->v0_zme_hinfo.u32 = v0_zme_hinfo.u32;
    vo_reg->v0_zme_hsp.u32 = v0_zme_hsp.u32;
    vo_reg->v0_zme_hloffset.u32 = v0_zme_hloffset.u32;
    vo_reg->v0_zme_hcoffset.u32 = v0_zme_hcoffset.u32;
}

static hi_void vo_hal_layer_set_zme_hinfo_ext_cfg(hal_disp_layer layer, vo_v0_zme_cfg *cfg,
    vo_zme_comm_pq_cfg *pq_cfg)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_zme_hzone0delta v0_zme_hzone0delta;
    volatile reg_v0_zme_hzone2delta v0_zme_hzone2delta;
    volatile reg_v0_zme_hzoneend v0_zme_hzoneend;
    volatile reg_v0_zme_hl_shootctrl v0_zme_hl_shootctrl;
    volatile reg_v0_zme_hc_shootctrl v0_zme_hc_shootctrl;

    v0_zme_hzone0delta.u32 = vo_reg->v0_zme_hzone0delta.u32;
    v0_zme_hzone2delta.u32 = vo_reg->v0_zme_hzone2delta.u32;
    v0_zme_hzoneend.u32 = vo_reg->v0_zme_hzoneend.u32;
    v0_zme_hl_shootctrl.u32 = vo_reg->v0_zme_hl_shootctrl.u32;
    v0_zme_hc_shootctrl.u32 = vo_reg->v0_zme_hc_shootctrl.u32;

    v0_zme_hzone0delta.bits.zone0_delta = 0;
    v0_zme_hzone2delta.bits.zone2_delta = 0;
    v0_zme_hzoneend.bits.zone0_end = 0;
    v0_zme_hzoneend.bits.zone1_end = 0;
    v0_zme_hl_shootctrl.bits.hl_coring = pq_cfg->hl_coring;
    v0_zme_hl_shootctrl.bits.hl_gain = pq_cfg->hl_gain;
    v0_zme_hl_shootctrl.bits.hl_coringadj_en = pq_cfg->hl_coringadj_en;
    v0_zme_hl_shootctrl.bits.hl_flatdect_mode = pq_cfg->hl_flatdect_mode;
    v0_zme_hl_shootctrl.bits.hl_shootctrl_mode = cfg->hl_shootctrl_mode;
    v0_zme_hl_shootctrl.bits.hl_shootctrl_en = cfg->hl_shootctrl_en;
    v0_zme_hc_shootctrl.bits.hc_coring = pq_cfg->hc_coring;
    v0_zme_hc_shootctrl.bits.hc_gain = pq_cfg->hc_gain;
    v0_zme_hc_shootctrl.bits.hc_coringadj_en = pq_cfg->hc_coringadj_en;
    v0_zme_hc_shootctrl.bits.hc_flatdect_mode = pq_cfg->hc_flatdect_mode;
    v0_zme_hc_shootctrl.bits.hc_shootctrl_mode = cfg->hc_shootctrl_mode;
    v0_zme_hc_shootctrl.bits.hc_shootctrl_en = cfg->hc_shootctrl_en;

    vo_reg->v0_zme_hzone0delta.u32 = v0_zme_hzone0delta.u32;
    vo_reg->v0_zme_hzone2delta.u32 = v0_zme_hzone2delta.u32;
    vo_reg->v0_zme_hzoneend.u32 = v0_zme_hzoneend.u32;
    vo_reg->v0_zme_hl_shootctrl.u32 = v0_zme_hl_shootctrl.u32;
    vo_reg->v0_zme_hc_shootctrl.u32 = v0_zme_hc_shootctrl.u32;
}

hi_void vo_hal_layer_set_zme_cfg(hal_disp_layer layer, hi_u32 vratio, hi_u32 hratio,
    vo_v0_zme_cfg *cfg, vo_zme_comm_pq_cfg *pq_cfg)
{
    vo_hal_layer_set_zme_vinfo_basic_cfg(layer, vratio, cfg, pq_cfg);
    vo_hal_layer_set_zme_vinfo_ext_cfg(layer, cfg, pq_cfg);
    vo_hal_layer_set_zme_hinfo_basic_cfg(layer, hratio, cfg, pq_cfg);
    vo_hal_layer_set_zme_hinfo_ext_cfg(layer, cfg, pq_cfg);
}

#endif

#if VO_DESC("layer cvfir")
hi_void vo_hal_layer_set_v1_cvfir_cfg(hi_u32 vratio, vdp_v1_cvfir_cfg *cfg,
    vo_zme_comm_pq_cfg *pq_cfg)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v1_cvfir_vinfo v1_cvfir_vinfo;
    volatile reg_v1_cvfir_vsp v1_cvfir_vsp;
    volatile reg_v1_cvfir_voffset v1_cvfir_voffset;
    volatile reg_v1_cvfir_vboffset v1_cvfir_vboffset;
    volatile hi_ulong addr_reg;

    addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v1_cvfir_vinfo.u32);
    v1_cvfir_vinfo.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v1_cvfir_vinfo.bits.out_height = cfg->out_height - 1;
    v1_cvfir_vinfo.bits.out_fmt = cfg->out_fmt;
    v1_cvfir_vinfo.bits.out_pro = cfg->out_pro;
    v1_cvfir_vinfo.bits.vzme_ck_gt_en = cfg->ck_gt_en;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v1_cvfir_vinfo.u32);

    addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v1_cvfir_vsp.u32);
    v1_cvfir_vsp.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v1_cvfir_vsp.bits.vratio = vratio;
    v1_cvfir_vsp.bits.cvfir_mode = cfg->cvfir_mode;
    v1_cvfir_vsp.bits.cvmid_en = cfg->cvmid_en;
    v1_cvfir_vsp.bits.cvfir_en = cfg->cvfir_en;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v1_cvfir_vsp.u32);

    addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v1_cvfir_voffset.u32);
    v1_cvfir_voffset.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v1_cvfir_voffset.bits.vchroma_offset = pq_cfg->vchroma_offset;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v1_cvfir_voffset.u32);

    addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v1_cvfir_vboffset.u32);
    v1_cvfir_vboffset.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v1_cvfir_vboffset.bits.vbchroma_offset = pq_cfg->vbchroma_offset;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v1_cvfir_vboffset.u32);
}

hi_void vo_hal_layer_set_v2_cvfir_cfg(hi_u32 vratio, vdp_v1_cvfir_cfg *cfg,
    vo_zme_comm_pq_cfg *pq_cfg)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v2_cvfir_vinfo v2_cvfir_vinfo;
    volatile reg_v2_cvfir_vsp v2_cvfir_vsp;
    volatile reg_v2_cvfir_voffset v2_cvfir_voffset;
    volatile reg_v2_cvfir_vboffset v2_cvfir_vboffset;
    volatile hi_ulong addr_reg;

    addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v2_cvfir_vinfo.u32);
    v2_cvfir_vinfo.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v2_cvfir_vinfo.bits.out_height = cfg->out_height - 1;
    v2_cvfir_vinfo.bits.out_fmt = cfg->out_fmt;
    v2_cvfir_vinfo.bits.out_pro = cfg->out_pro;
    v2_cvfir_vinfo.bits.vzme_ck_gt_en = cfg->ck_gt_en;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v2_cvfir_vinfo.u32);

    addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v2_cvfir_vsp.u32);
    v2_cvfir_vsp.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v2_cvfir_vsp.bits.vratio = vratio;
    v2_cvfir_vsp.bits.cvfir_mode = cfg->cvfir_mode;
    v2_cvfir_vsp.bits.cvmid_en = cfg->cvmid_en;
    v2_cvfir_vsp.bits.cvfir_en = cfg->cvfir_en;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v2_cvfir_vsp.u32);

    addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v2_cvfir_voffset.u32);
    v2_cvfir_voffset.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v2_cvfir_voffset.bits.vchroma_offset = pq_cfg->vchroma_offset;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v2_cvfir_voffset.u32);

    addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v2_cvfir_vboffset.u32);
    v2_cvfir_vboffset.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v2_cvfir_vboffset.bits.vbchroma_offset = pq_cfg->vbchroma_offset;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v2_cvfir_vboffset.u32);
}

static hi_void vo_hal_layer_set_v1_cvfir_coef(cvfir_coef *coef)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v1_cvfir_vcoef0 v1_cvfir_vcoef0;
    volatile reg_v1_cvfir_vcoef1 v1_cvfir_vcoef1;
    volatile reg_v1_cvfir_vcoef2 v1_cvfir_vcoef2;
    volatile hi_ulong addr_reg;

    addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v1_cvfir_vcoef0.u32);
    v1_cvfir_vcoef0.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v1_cvfir_vcoef0.bits.vccoef00 = coef->vccoef00;
    v1_cvfir_vcoef0.bits.vccoef01 = coef->vccoef01;
    v1_cvfir_vcoef0.bits.vccoef02 = coef->vccoef02;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v1_cvfir_vcoef0.u32);

    addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v1_cvfir_vcoef1.u32);
    v1_cvfir_vcoef1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v1_cvfir_vcoef1.bits.vccoef03 = coef->vccoef03;
    v1_cvfir_vcoef1.bits.vccoef10 = coef->vccoef10;
    v1_cvfir_vcoef1.bits.vccoef11 = coef->vccoef11;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v1_cvfir_vcoef1.u32);

    addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v1_cvfir_vcoef2.u32);
    v1_cvfir_vcoef2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v1_cvfir_vcoef2.bits.vccoef12 = coef->vccoef12;
    v1_cvfir_vcoef2.bits.vccoef13 = coef->vccoef13;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v1_cvfir_vcoef2.u32);
}

static hi_void vo_hal_layer_set_v2_cvfir_coef(cvfir_coef *coef)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v2_cvfir_vcoef0 v2_cvfir_vcoef0;
    volatile reg_v2_cvfir_vcoef1 v2_cvfir_vcoef1;
    volatile reg_v2_cvfir_vcoef2 v2_cvfir_vcoef2;
    volatile hi_ulong addr_reg;

    addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v2_cvfir_vcoef0.u32);
    v2_cvfir_vcoef0.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v2_cvfir_vcoef0.bits.vccoef00 = coef->vccoef00;
    v2_cvfir_vcoef0.bits.vccoef01 = coef->vccoef01;
    v2_cvfir_vcoef0.bits.vccoef02 = coef->vccoef02;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v2_cvfir_vcoef0.u32);

    addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v2_cvfir_vcoef1.u32);
    v2_cvfir_vcoef1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v2_cvfir_vcoef1.bits.vccoef03 = coef->vccoef03;
    v2_cvfir_vcoef1.bits.vccoef10 = coef->vccoef10;
    v2_cvfir_vcoef1.bits.vccoef11 = coef->vccoef11;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v2_cvfir_vcoef1.u32);

    addr_reg = (hi_ulong)(hi_uintptr_t) & (vo_reg->v2_cvfir_vcoef2.u32);
    v2_cvfir_vcoef2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v2_cvfir_vcoef2.bits.vccoef12 = coef->vccoef12;
    v2_cvfir_vcoef2.bits.vccoef13 = coef->vccoef13;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v2_cvfir_vcoef2.u32);
}

hi_void vo_hal_layer_set_cvfir_coef(hal_disp_layer layer, cvfir_coef *coef)
{
    if (layer == HAL_DISP_LAYER_VHD1) {
        vo_hal_layer_set_v1_cvfir_coef(coef);
    } else if (layer == HAL_DISP_LAYER_VHD2) {
        vo_hal_layer_set_v2_cvfir_coef(coef);
    }
}
#endif

#if VO_DESC("layer chroma copy")

hi_void vo_hal_layer_set_chroma_copy(hi_u32 layer, hi_bool chroma_copy_flag)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vid_read_ctrl vid_read_ctrl;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_layer_return(layer);

    addr_reg = (hi_ulong)(hi_uintptr_t) (&(vo_reg->vid_read_ctrl.u32) + layer * FDR_VID_OFFSET);
    vid_read_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    vid_read_ctrl.bits.chm_copy_en = chroma_copy_flag;
    hal_write_reg((hi_u32 *)(hi_uintptr_t)addr_reg, vid_read_ctrl.u32);
}

#endif

hi_void hal_video_hfir_set_ck_gt_en(hal_disp_layer layer, hi_u32 ck_gt_en)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_hfir_ctrl v0_hfir_ctrl;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_layer_return(layer);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hfir_ctrl.u32));
    v0_hfir_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hfir_ctrl.bits.ck_gt_en = ck_gt_en;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hfir_ctrl.u32);
}

hi_void hal_video_hfir_set_mid_en(hal_disp_layer layer, hi_u32 mid_en)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_hfir_ctrl v0_hfir_ctrl;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_layer_return(layer);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hfir_ctrl.u32));
    v0_hfir_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hfir_ctrl.bits.mid_en = mid_en;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hfir_ctrl.u32);
}

hi_void hal_video_hfir_set_hfir_mode(hal_disp_layer layer, hi_u32 hfir_mode)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_hfir_ctrl v0_hfir_ctrl;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_layer_return(layer);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hfir_ctrl.u32));
    v0_hfir_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hfir_ctrl.bits.hfir_mode = hfir_mode;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hfir_ctrl.u32);
}

hi_void hal_video_hfir_set_coef(hal_disp_layer layer, hfir_coef *coef)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_hfircoef01 v0_hfir_coef01;
    volatile reg_v0_hfircoef23 v0_hfir_coef23;
    volatile reg_v0_hfircoef45 v0_hfir_coef45;
    volatile reg_v0_hfircoef67 v0_hfir_coef67;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_layer_return(layer);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hfircoef01.u32));
    v0_hfir_coef01.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hfir_coef01.bits.coef0 = coef->coef0;
    v0_hfir_coef01.bits.coef1 = coef->coef1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hfir_coef01.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hfircoef23.u32));
    v0_hfir_coef23.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hfir_coef23.bits.coef2 = coef->coef2;
    v0_hfir_coef23.bits.coef3 = coef->coef3;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hfir_coef23.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hfircoef45.u32));
    v0_hfir_coef45.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hfir_coef45.bits.coef4 = coef->coef4;
    v0_hfir_coef45.bits.coef5 = coef->coef5;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hfir_coef45.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hfircoef67.u32));
    v0_hfir_coef67.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hfir_coef67.bits.coef6 = coef->coef6;
    v0_hfir_coef67.bits.coef7 = coef->coef7;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hfir_coef67.u32);
}

hi_void hal_layer_set_layer_in_rect(hal_disp_layer layer, hi_rect *rect)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vid_in_reso vid_in_reso;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_layer_return(layer);

    addr_reg = vou_get_vid_abs_addr(layer, (hi_uintptr_t) & (vo_reg->vid_in_reso.u32));
    vid_in_reso.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    vid_in_reso.bits.ireso_w = rect->width - 1;
    vid_in_reso.bits.ireso_h = rect->height - 1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, vid_in_reso.u32);
}

hi_void hal_layer_set_reg_up(hal_disp_layer layer)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_upd v0_upd;
    volatile reg_g0_upd g0_upd;
    volatile hi_ulong addr_reg;

    if (vo_hal_is_video_layer(layer)) {
        addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_upd.u32));
        v0_upd.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
        /* video layer register update */
        v0_upd.bits.regup = 0x1;
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_upd.u32);
    } else if (vo_hal_is_gfx_layer(layer)) {
        addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_upd.u32));
        g0_upd.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
        /* graphic layer register update */
        g0_upd.bits.regup = 0x1;
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_upd.u32);
    }
}

hi_void hal_cbm_set_cbm_attr(hal_disp_layer layer, hi_vo_dev dev)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_link_ctrl link_ctrl;

    if (layer == HAL_DISP_LAYER_VHD2) {
        link_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) & (vo_reg->link_ctrl.u32));
        link_ctrl.bits.v2_link = dev;
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) & (vo_reg->link_ctrl.u32), link_ctrl.u32);
    } else if (layer == HAL_DISP_LAYER_GFX2) {
        link_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) & (vo_reg->link_ctrl.u32));
        link_ctrl.bits.g2_link = dev;
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) & (vo_reg->link_ctrl.u32), link_ctrl.u32);
    } else if (layer == HAL_DISP_LAYER_GFX3) {
        link_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) & (vo_reg->link_ctrl.u32));
        link_ctrl.bits.g3_link = dev;
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) & (vo_reg->link_ctrl.u32), link_ctrl.u32);
    }
}

hi_void hal_cbm_set_cbm_bkg(hal_cbmmix mixer, hal_disp_bkcolor *bkg)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_cbm_bkg1 cbm_bkg1;
    volatile reg_cbm_bkg2 cbm_bkg2;
    volatile reg_cbm_bkg3 cbm_bkg3;

    if (mixer == HAL_CBMMIX1) {
        cbm_bkg1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) & (vo_reg->cbm_bkg1.u32));
        cbm_bkg1.bits.cbm_bkgy1 = (bkg->bkg_y);
        cbm_bkg1.bits.cbm_bkgcb1 = (bkg->bkg_cb);
        cbm_bkg1.bits.cbm_bkgcr1 = (bkg->bkg_cr);
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) & (vo_reg->cbm_bkg1.u32), cbm_bkg1.u32);
    } else if (mixer == HAL_CBMMIX2) {
        cbm_bkg2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) & (vo_reg->cbm_bkg2.u32));
        cbm_bkg2.bits.cbm_bkgy2 = (bkg->bkg_y);
        cbm_bkg2.bits.cbm_bkgcb2 = (bkg->bkg_cb);
        cbm_bkg2.bits.cbm_bkgcr2 = (bkg->bkg_cr);
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) & (vo_reg->cbm_bkg2.u32), cbm_bkg2.u32);
    } else if (mixer == HAL_CBMMIX3) {
        cbm_bkg3.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) & (vo_reg->cbm_bkg3.u32));
        cbm_bkg3.bits.cbm_bkgy3 = (bkg->bkg_y);
        cbm_bkg3.bits.cbm_bkgcb3 = (bkg->bkg_cb);
        cbm_bkg3.bits.cbm_bkgcr3 = (bkg->bkg_cr);
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) & (vo_reg->cbm_bkg3.u32), cbm_bkg3.u32);
    }
}

static hi_void hal_cbm_set_cbm1_mixer_prio(hi_vo_layer layer, hi_u8 prio)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_cbm_mix1 cbm_mix1;
    hi_u8 layer_id = 0;

    /* check layer availability */
    if (hal_cbm_get_cbm1_mixer_layer_id(layer, &layer_id) != HI_TRUE) {
        return;
    }

     /* set mixer prio */
    cbm_mix1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) & (vo_reg->cbm_mix1.u32));

    switch (prio) {
        case 0:  /* 0: prio 0 */
            cbm_mix1.bits.mixer_prio0 = layer_id;
            break;

        case 1:  /* 1: prio 1 */
            cbm_mix1.bits.mixer_prio1 = layer_id;
            break;

        case 2:  /* 2: prio 2 */
            cbm_mix1.bits.mixer_prio2 = layer_id;
            break;

        case 3:  /* 3: prio 3 */
            cbm_mix1.bits.mixer_prio3 = layer_id;
            break;

        case 4:  /* 4: prio 4 */
            cbm_mix1.bits.mixer_prio4 = layer_id;
            break;

        default:
            vo_err_trace("error priority id %d found\n", prio);
            return;
    }

    hal_write_reg ((hi_u32 *)(hi_uintptr_t) & (vo_reg->cbm_mix1.u32), cbm_mix1.u32);
}

static hi_void hal_cbm_set_cbm2_mixer_prio(hi_vo_layer layer, hi_u8 prio)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_cbm_mix2 cbm_mix2;
    hi_u8 layer_id = 0;

    /* check layer availability */
    if (hal_cbm_get_cbm2_mixer_layer_id(layer, &layer_id) != HI_TRUE) {
        return;
    }

    /* set mixer prio */
    cbm_mix2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) & (vo_reg->cbm_mix2.u32));

    switch (prio) {
        case 0:  /* 0: prio 0 */
            cbm_mix2.bits.mixer_prio0 = layer_id;
            break;

        case 1:  /* 1: prio 1 */
            cbm_mix2.bits.mixer_prio1 = layer_id;
            break;

        case 2:  /* 2: prio 2 */
            cbm_mix2.bits.mixer_prio2 = layer_id;
            break;

        case 3:  /* 3: prio 3 */
            cbm_mix2.bits.mixer_prio3 = layer_id;
            break;

        case 4:  /* 4: prio 4 */
            cbm_mix2.bits.mixer_prio4 = layer_id;
            break;

        default:
            vo_err_trace("error priority id %d found\n", prio);
            return;
    }

    hal_write_reg ((hi_u32 *)(hi_uintptr_t) & (vo_reg->cbm_mix2.u32), cbm_mix2.u32);
}

static hi_void hal_cbm_set_cbm3_mixer_prio(hi_vo_layer layer, hi_u8 prio)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_cbm_mix3 cbm_mix3;
    hi_u8 layer_id = 0;

    /* check layer availability */
    if (hal_cbm_get_cbm3_mixer_layer_id(layer, &layer_id) != HI_TRUE) {
        return;
    }

    /* set mixer prio */
    cbm_mix3.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) & (vo_reg->cbm_mix3.u32));

    switch (prio) {
        case 0:  /* 0: prio 0 */
            cbm_mix3.bits.mixer_prio0 = layer_id;
            break;

        case 1:  /* 1: prio 1 */
            cbm_mix3.bits.mixer_prio1 = layer_id;
            break;

        case 2:  /* 2: prio 2 */
            cbm_mix3.bits.mixer_prio2 = layer_id;
            break;

        default:
            vo_err_trace("error priority id %d found\n", prio);
            return;
    }

    hal_write_reg ((hi_u32 *)(hi_uintptr_t) & (vo_reg->cbm_mix3.u32), cbm_mix3.u32);
}

hi_void hal_cbm_set_cbm_mixer_prio(hi_vo_layer layer, hi_u8 prio, hi_u8 mixer_id)
{
    if (mixer_id == HAL_CBMMIX1) {
        hal_cbm_set_cbm1_mixer_prio(layer, prio);
    } else if (mixer_id == HAL_CBMMIX2) {
        hal_cbm_set_cbm2_mixer_prio(layer, prio);
    } else if (mixer_id == HAL_CBMMIX3) {
        hal_cbm_set_cbm3_mixer_prio(layer, prio);
    }
}

#endif
#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
