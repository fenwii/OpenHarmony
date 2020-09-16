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

#ifndef __VOU_HAL_H__
#define __VOU_HAL_H__

#include "vou_reg.h"
#include "vou_def.h"
#include "vou_coef.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of #ifdef __cplusplus */

hi_void hal_vo_init(hi_void);
hi_void hal_vo_exit(hi_void);

hi_void hal_write_reg(hi_u32 *address, hi_u32 value);
hi_u32 hal_read_reg(const hi_u32 *address);

hi_s32 sys_hal_vo_bt1120_chn_sel(hi_u32 clk_sel);
hi_s32 sys_hal_vo_bt_bp_clk_en(hi_bool clk_en);
hi_s32 sys_hal_lcd_mclk_div(hi_u32 mclk_div);
hi_s32 sys_hal_vo_bt_clk_en(hi_bool clk_en);
hi_s32 sys_hal_sel_vo_clk(hi_u32 clk_sel);
hi_s32 sys_hal_vo_vdp_low_power(hi_bool clk_en);
hi_s32 sys_hal_vo_bus_reset_sel(hi_bool reset);
hi_s32 sys_hal_vo_lcd_clk_en(hi_bool clk_en);
hi_s32 sys_hal_vo_dev_clk_en(hi_s32 vo_dev, hi_bool clk_en);
hi_s32 sys_hal_vo_hdmi_clk_en(hi_s32 vo_dev, hi_bool hdmi_clk_en);
hi_s32 sys_hal_vo_mipi_tx_chn_sel(hi_u32 clk_sel);
hi_s32 sys_hal_vo_hd_out_pctrl(hi_bool clk_reverse);
hi_s32 sys_hal_vo_mipi_clk_en(hi_s32 vo_dev, hi_bool mipi_clk_en);
hi_s32 sys_hal_vo_hd0_div_mode(hi_s32 dev, hi_u32 hd0_div_mod);
hi_s32 sys_hal_set_vo_pll_frac(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_pll_postdiv1(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_pll_postdiv2(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_pll_refdiv(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_pll_fbdiv(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_s_pll_frac(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_s_pll_postdiv1(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_s_pll_postdiv2(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_s_pll_refdiv(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_set_vo_s_pll_fbdiv(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_vo_out_clk_sel(hi_s32 dev, hi_u32 clk_sel);
hi_s32 sys_hal_vo_hd_clk_sel(hi_s32 dev, hi_u32 clk_sel);
hi_s32 sys_hal_vo_hd1_div_mode(hi_s32 dev, hi_u32 hd1_div_mod);
hi_s32 sys_hal_vo_cfg_clk_en(hi_s32 dev, hi_bool clk_en);
hi_s32 sys_hal_vo_core_clk_en(hi_s32 dev, hi_bool clk_en);
hi_s32 sys_hal_vo_apb_clk_en(hi_s32 dev, hi_bool clk_en);
hi_s32 sys_hal_vo_bus_clk_en(hi_bool clk_en);
hi_s32 sys_hal_vo_mipi_tx_clk_en(hi_s32 vo_dev, hi_bool mipi_tx_clk_en);
hi_void hal_sys_control(hi_void);
hi_void hal_sys_set_outstanding(hi_void);
hi_void hal_sys_set_axi_master(hi_void);
hi_void hal_sys_set_arb_mode(hi_u32 mode);
hi_void hal_sys_set_rd_bus_id(hi_u32 mode);
hi_void hal_sys_vdp_reset_clk(hi_u32 sel);

hi_bool hal_disp_set_lcd_serial_perd(hi_u32 serial_perd);
hi_bool hal_disp_set_intf_enable(hal_disp_outputchannel chan, hi_bool intf);
hi_bool hal_disp_set_intf_ctrl(hal_disp_intf intf, const hi_u32 *ctrl_info);
hi_bool hal_disp_set_intf_sync(hal_disp_outputchannel chan,
                               const hal_disp_syncinfo *sync_info);
hi_bool hal_disp_set_dev_multi_chn_en(hal_disp_outputchannel chn, hal_multi_chn multi_chn_en);
hi_bool hal_disp_set_intf_sync_inv(hal_disp_intf intf, const hal_disp_syncinv *inv);
hi_bool hal_disp_set_intf_mux_default_sel(hi_void);
hi_bool hal_disp_set_intf_mux_sel(hal_disp_outputchannel chan, hal_disp_intf intf);
hi_bool hal_disp_set_bt1120_sel(hal_disp_outputchannel chan);
hi_bool hal_disp_set_intf_clip(hal_disp_intf intf, hi_bool clip, const hal_disp_clip *clip_data);
hi_bool hal_disp_set_vt_thd_mode(hal_disp_outputchannel chan, hi_u32 field_mode);
hi_bool hal_disp_set_vt_thd(hal_disp_outputchannel chan, hi_u32 vtthd);

hi_bool hal_disp_set_int_mask(hi_u32 mask_en);
hi_bool hal_disp_clr_int_mask(hi_u32 mask_en);
hi_bool hal_disp_set_int_mask1(hi_u32 mask_en);
hi_bool hal_disp_clr_int_mask1(hi_u32 mask_en);
hi_bool hal_disp_clear_int_status(hi_u32 int_msk);
hi_bool hal_disp_set_clk_gate_enable(hi_u32 data);

hi_bool hal_intf_bt_set_dfir_en(hi_u32 dfir_en);
hi_void hal_disp_set_reg_up(hal_disp_outputchannel chan);

hi_bool hal_video_set_layer_up_mode(hal_disp_layer layer, hi_u32 up_mode);
hi_bool hal_video_set_hfir_mode(hal_disp_layer layer, hal_hfirmode mode);
hi_bool hal_video_set_hfir_coef(hal_disp_layer layer, const hi_s32 *coef);
hi_bool hal_video_set_layer_disp_rect(hal_disp_layer layer, const hi_rect *rect);
hi_bool hal_video_set_layer_video_rect(hal_disp_layer layer, const hi_rect *rect);
hi_bool hal_video_set_multi_area_l_addr(hal_disp_layer layer, hi_u32 area_num, hi_ulong l_addr, hi_u16 stride);
hi_bool hal_video_set_multi_area_c_addr(hal_disp_layer layer, hi_u32 area_num, hi_ulong c_addr, hi_u16 stride);
hi_bool hal_video_set_multi_area_enable(hal_disp_layer layer, hi_u32 area_num, hi_u32 enable);
hi_bool hal_video_set_multi_area_reso(hal_disp_layer layer, hi_u32 area_num,
                                      hi_u32 width);
hi_bool hal_video_set_multi_area_rect(hal_disp_layer layer, hi_u32 area_num, const hi_rect *video_area_rect);

hi_bool hal_layer_enable_layer(hal_disp_layer layer, hi_u32 enable);
hi_bool hal_layer_set_layer_data_fmt(hal_disp_layer layer,
                                     hal_disp_pixel_format data_fmt);
hi_bool hal_layer_set_csc_coef(hal_disp_layer layer, const vo_csc_coef *csc_coef);
hi_bool hal_layer_set_csc_en(hal_disp_layer layer, hi_bool csc_en);
hi_bool hal_layer_set_layer_in_rect(hal_disp_layer layer, const hi_rect *rect);
hi_bool hal_layer_set_layer_out_rect(hal_disp_layer layer, const hi_rect *rect);
hi_bool hal_layer_set_layer_galpha(hal_disp_layer layer,
                                   hi_u8 alpha0);
hi_bool hal_layer_set_zme_info(hal_disp_layer layer, hi_u32 width, hi_u32 height,
                               hal_disp_zme_outfmt zme_out_fmt);
hi_bool hal_layer_set_zme_enable(hal_disp_layer layer,
                                 hal_disp_zmemode mode,
                                 hi_u32 enable);
hi_bool hal_layer_set_zme_msc_enable(hal_disp_layer layer, hal_disp_zmemode mode, hi_u32 enable);
hi_bool hal_layer_set_reg_up(hal_disp_layer layer);
hi_bool hal_layer_set_src_resolution(hal_disp_layer layer,
                                     const hi_rect *rect);

hi_bool hal_graphic_set_gfx_addr(hal_disp_layer layer, hi_u64 l_addr);
hi_bool hal_graphic_set_gfx_stride(hal_disp_layer layer, hi_u16 pitch);
hi_bool hal_graphic_set_gfx_ext(hal_disp_layer layer,
                                hal_gfx_bitextend mode);
hi_bool hal_graphic_set_gfx_pre_mult(hal_disp_layer layer, hi_u32 enable);
hi_bool hal_graphic_set_gfx_palpha(hal_disp_layer layer,
                                   hi_u32 alpha_en, hi_u32 arange,
                                   hi_u8 alpha0, hi_u8 alpha1);
hi_bool hal_graphic_get_gfx_palpha(hal_disp_layer layer, hi_u32 *alpha_en,
                                   hi_u8 *alpha0, hi_u8 *alpha1);

hi_bool hal_graphic_set_gfx_palpha_range(hal_disp_layer layer, hi_u32 arange);

hi_bool hal_gfx_set_src_resolution(hal_disp_layer layer, const hi_rect *rect);

hi_bool hal_cbm_set_cbm_bkg(hi_u32 mixer_id, const hal_disp_bkcolor *bkg);
hi_bool hal_cbm_set_cbm_mixer_prio(hal_disp_layer layer, hi_u8 prio, hi_u8 mixer_id);
hi_bool hal_disp_set_vga_csc_en(hal_disp_layer layer, hi_bool csc_en);
hi_void hal_hihdr_g_set_hihdr_r2y_scale2p(hi_u32 hihdr_r2y_scale2p);
hi_void hal_hihdr_g_set_hihdr_r2y_clip_min(hi_u32 hihdr_r2y_clip_min);
hi_void hal_hihdr_g_set_hihdr_r2y_clip_max(hi_u32 hihdr_r2y_clip_max);

hi_void hal_v0_zme_set_hzme_ck_gt_en(hi_u32 hzme_ck_gt_en);
hi_void hal_v0_zme_set_out_width(hi_u32 out_width);
hi_void hal_v0_zme_set_lhfir_en(hi_u32 lhfir_en);
hi_void hal_v0_zme_set_chfir_en(hi_u32 chfir_en);
hi_void hal_v0_zme_set_lhmid_en(hi_u32 lhmid_en);
hi_void hal_v0_zme_set_chmid_en(hi_u32 chmid_en);
hi_void hal_v0_zme_set_non_lnr_en(hi_u32 non_lnr_en);
hi_void hal_v0_zme_set_lhfir_mode(hi_u32 lhfir_mode);
hi_void hal_v0_zme_set_chfir_mode(hi_u32 chfir_mode);
hi_void hal_v0_zme_set_hfir_order(hi_u32 hfir_order);
hi_void hal_v0_zme_set_hratio(hi_u32 hratio);
hi_void hal_v0_zme_set_lhfir_offset(hi_u32 lhfir_offset);
hi_void hal_v0_zme_set_chfir_offset(hi_u32 chfir_offset);
hi_void hal_v0_zme_set_zone0_delta(hi_u32 zone0_delta);
hi_void hal_v0_zme_set_zone2_delta(hi_u32 zone2_delta);
hi_void hal_v0_zme_set_zone1_end(hi_u32 zone1_end);
hi_void hal_v0_zme_set_zone0_end(hi_u32 zone0_end);
hi_void hal_v0_zme_set_hl_shootctrl_en(hi_u32 hl_shootctrl_en);
hi_void hal_v0_zme_set_hl_shootctrl_mode(hi_u32 hl_shootctrl_mode);
hi_void hal_v0_zme_set_hl_flatdect_mode(hi_u32 hl_flatdect_mode);
hi_void hal_v0_zme_set_hl_coringadj_en(hi_u32 hl_coringadj_en);
hi_void hal_v0_zme_set_hl_gain(hi_u32 hl_gain);
hi_void hal_v0_zme_set_hl_coring(hi_u32 hl_coring);
hi_void hal_v0_zme_set_hc_shootctrl_en(hi_u32 hc_shootctrl_en);
hi_void hal_v0_zme_set_hc_shootctrl_mode(hi_u32 hc_shootctrl_mode);
hi_void hal_v0_zme_set_hc_flatdect_mode(hi_u32 hc_flatdect_mode);
hi_void hal_v0_zme_set_hc_coringadj_en(hi_u32 hc_coringadj_en);
hi_void hal_v0_zme_set_hc_gain(hi_u32 hc_gain);
hi_void hal_v0_zme_set_hc_coring(hi_u32 hc_coring);
hi_void hal_v0_zme_set_vzme_ck_gt_en(hi_u32 vzme_ck_gt_en);
hi_void hal_v0_zme_set_out_pro(hi_u32 out_pro);
hi_void hal_v0_zme_set_out_fmt(hi_u32 out_fmt);
hi_void hal_v0_zme_set_out_height(hi_u32 out_height);
hi_void hal_v0_zme_set_lvfir_en(hi_u32 lvfir_en);
hi_void hal_v0_zme_set_cvfir_en(hi_u32 cvfir_en);
hi_void hal_v0_zme_set_lvmid_en(hi_u32 lvmid_en);
hi_void hal_v0_zme_set_cvmid_en(hi_u32 cvmid_en);
hi_void hal_v0_zme_set_vfir1tap_en(hi_u32 vfir_1tap_en);
hi_void hal_v0_zme_set_lvfir_mode(hi_u32 lvfir_mode);
hi_void hal_v0_zme_set_cvfir_mode(hi_u32 cvfir_mode);
hi_void hal_v0_zme_set_graphdet_en(hi_u32 graphdet_en);
hi_void hal_v0_zme_set_vratio(hi_u32 vratio);
hi_void hal_v0_zme_set_vluma_offset(hi_u32 vluma_offset);
hi_void hal_v0_zme_set_vchroma_offset(hi_u32 vchroma_offset);
hi_void hal_v0_zme_set_vbluma_offset(hi_u32 vbluma_offset);
hi_void hal_v0_zme_set_vbchroma_offset(hi_u32 vbchroma_offset);
hi_void hal_v0_zme_set_vl_shootctrl_en(hi_u32 vl_shootctrl_en);
hi_void hal_v0_zme_set_vl_shootctrl_mode(hi_u32 vl_shootctrl_mode);
hi_void hal_v0_zme_set_vl_flatdect_mode(hi_u32 vl_flatdect_mode);
hi_void hal_v0_zme_set_vl_coringadj_en(hi_u32 vl_coringadj_en);
hi_void hal_v0_zme_set_vl_gain(hi_u32 vl_gain);
hi_void hal_v0_zme_set_vl_coring(hi_u32 vl_coring);
hi_void hal_v0_zme_set_vc_shootctrl_en(hi_u32 vc_shootctrl_en);
hi_void hal_v0_zme_set_vc_shootctrl_mode(hi_u32 vc_shootctrl_mode);
hi_void hal_v0_zme_set_vc_flatdect_mode(hi_u32 vc_flatdect_mode);
hi_void hal_v0_zme_set_vc_coringadj_en(hi_u32 vc_coringadj_en);
hi_void hal_v0_zme_set_vc_gain(hi_u32 vc_gain);
hi_void hal_v0_zme_set_vc_coring(hi_u32 vc_coring);

hi_void hal_v0_hfir_set_ck_gt_en(hi_u32 ck_gt_en);
hi_void hal_v0_hfir_set_mid_en(hi_u32 mid_en);
hi_void hal_v0_hfir_set_hfir_mode(hi_u32 hfir_mode);
hi_void hal_v0_hfir_set_hfir_en(hi_u32 hfir_en);
hi_void hal_v0_hfir_set_coef1(hi_u32 coef1);
hi_void hal_v0_hfir_set_coef0(hi_u32 coef0);
hi_void hal_v0_hfir_set_coef3(hi_u32 coef3);
hi_void hal_v0_hfir_set_coef2(hi_u32 coef2);
hi_void hal_v0_hfir_set_coef5(hi_u32 coef5);
hi_void hal_v0_hfir_set_coef4(hi_u32 coef4);
hi_void hal_v0_hfir_set_coef7(hi_u32 coef7);
hi_void hal_v0_hfir_set_coef6(hi_u32 coef6);
hi_void hal_v1_hfir_set_ck_gt_en(hi_u32 ck_gt_en);
hi_void hal_v1_hfir_set_mid_en(hi_u32 mid_en);
hi_void hal_v1_hfir_set_hfir_mode(hi_u32 hfir_mode);
hi_void hal_v1_hfir_set_hfir_en(hi_u32 hfir_en);
hi_void hal_v1_hfir_set_coef1(hi_u32 coef1);
hi_void hal_v1_hfir_set_coef0(hi_u32 coef0);
hi_void hal_v1_hfir_set_coef3(hi_u32 coef3);
hi_void hal_v1_hfir_set_coef2(hi_u32 coef2);
hi_void hal_v1_hfir_set_coef5(hi_u32 coef5);
hi_void hal_v1_hfir_set_coef4(hi_u32 coef4);
hi_void hal_v1_hfir_set_coef7(hi_u32 coef7);
hi_void hal_v1_hfir_set_coef6(hi_u32 coef6);

hi_void hal_v1_cvfir_set_vzme_ck_gt_en(hi_u32 vzme_ck_gt_en);
hi_void hal_v1_cvfir_set_out_pro(hi_u32 out_pro);
hi_void hal_v1_cvfir_set_out_fmt(hi_u32 out_fmt);
hi_void hal_v1_cvfir_set_out_height(hi_u32 out_height);
hi_void hal_v1_cvfir_set_cvfir_en(hi_u32 cvfir_en);
hi_void hal_v1_cvfir_set_cvmid_en(hi_u32 cvmid_en);
hi_void hal_v1_cvfir_set_cvfir_mode(hi_u32 cvfir_mode);
hi_void hal_v1_cvfir_set_vratio(hi_u32 vratio);
hi_void hal_v1_cvfir_set_vchroma_offset(hi_u32 vchroma_offset);
hi_void hal_v1_cvfir_set_vbchroma_offset(hi_u32 vbchroma_offset);

hi_void hal_g0_zme_set_ck_gt_en(hi_u32 ck_gt_en);
hi_void hal_g0_zme_set_out_width(hi_u32 out_width);
hi_void hal_g0_zme_set_hfir_en(hi_u32 hfir_en);
hi_void hal_g0_zme_set_ahfir_mid_en(hi_u32 ahfir_mid_en);
hi_void hal_g0_zme_set_lhfir_mid_en(hi_u32 lhfir_mid_en);
hi_void hal_g0_zme_set_chfir_mid_en(hi_u32 chfir_mid_en);
hi_void hal_g0_zme_set_lhfir_mode(hi_u32 lhfir_mode);
hi_void hal_g0_zme_set_ahfir_mode(hi_u32 ahfir_mode);
hi_void hal_g0_zme_set_hfir_order(hi_u32 hfir_order);
hi_void hal_g0_zme_set_hratio(hi_u32 hratio);
hi_void hal_g0_zme_set_lhfir_offset(hi_u32 lhfir_offset);
hi_void hal_g0_zme_set_chfir_offset(hi_u32 chfir_offset);
hi_void hal_g0_zme_set_out_pro(hi_u32 out_pro);
hi_void hal_g0_zme_set_out_height(hi_u32 out_height);
hi_void hal_g0_zme_set_vfir_en(hi_u32 vfir_en);
hi_void hal_g0_zme_set_avfir_mid_en(hi_u32 avfir_mid_en);
hi_void hal_g0_zme_set_lvfir_mid_en(hi_u32 lvfir_mid_en);
hi_void hal_g0_zme_set_cvfir_mid_en(hi_u32 cvfir_mid_en);
hi_void hal_g0_zme_set_lvfir_mode(hi_u32 lvfir_mode);
hi_void hal_g0_zme_set_vafir_mode(hi_u32 vafir_mode);
hi_void hal_g0_zme_set_vratio(hi_u32 vratio);
hi_void hal_g0_zme_set_vtp_offset(hi_u32 vtp_offset);
hi_void hal_g0_zme_set_vbtm_offset(hi_u32 vbtm_offset);

__inline static hi_u32 get_low_addr(hi_u64 phyaddr)
{
    return (hi_u32)phyaddr;
}

__inline static hi_u32 get_high_addr(hi_u64 phyaddr)
{
    return (hi_u32)(phyaddr >> 32); /* 32 to get high address */
}

#ifdef __cplusplus
}
#endif /* end of #ifdef __cplusplus */
#endif /* end of __VOU_HAL_H__ */

