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

#ifndef __HAL_VO_DEV_COMM_H__
#define __HAL_VO_DEV_COMM_H__

#include "hal_vo_def.h"
#include "drv_vo_coef_comm.h"
#include "hi_inner_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")
#if VO_DESC("intf")
#define VO_CVBS_DATE_NTSC 0x108410dc
hi_void hal_sys_set_rd_bus_id(hi_u32 mode);
hi_void hal_disp_set_intf_enable(hi_vo_dev dev, hi_bool intf);
hi_void hal_disp_get_intf_enable(hi_vo_dev dev, hi_bool *intf_en);
hi_void hal_disp_set_hdmi_mode(hi_vo_dev dev, hi_u32 color_space);
hi_void hal_disp_set_dev_multi_chn_en(hi_vo_dev dev, hal_multichn_en multi_chn_en);
#endif

#if VO_DESC("disp intf")
hi_void hal_disp_set_vtthd_mode(hi_vo_dev dev, hi_u32 field_mode);
hi_void hal_disp_set_vtthd(hi_vo_dev dev, hi_u32 vtthd, hi_u32 vtthd2);
hi_void hal_disp_clear_int_status(hi_u32 int_msk);
hi_void hal_intf_bt_set_dfir_en(hi_u32 dfir_en);
hi_void hal_intf_bt_set_data_width(hi_u32 data_width);
hi_void hal_disp_set_reg_up(hi_vo_dev dev);
hi_u32 hal_disp_get_reg_up(hi_vo_dev dev);
#endif

#if VO_DESC("intf")
hi_void vo_hal_intf_set_mux_sel(hi_vo_dev dev, hi_vo_intf_type intf);
hi_void vo_hal_intf_set_bt_sync_inv(hal_disp_syncinv *inv);
hi_void vo_hal_intf_set_cvbs_sync_inv(hal_disp_syncinv *inv);
hi_void vo_hal_intf_set_vga_sync_inv(hal_disp_syncinv *inv);
hi_void vo_hal_intf_set_hdmi_sync_inv(hal_disp_syncinv *inv);
hi_void vo_hal_intf_set_hdmi_csc_dc_coef(vdp_csc_dc_coef *csc_dc_coef);
hi_void vo_hal_intf_set_vga_csc_dc_coef(vdp_csc_dc_coef *csc_dc_coef);
hi_void vo_hal_intf_set_hdmi_csc_coef(vdp_csc_coef *csc_coef);
hi_void vo_hal_intf_set_vga_csc_coef(vdp_csc_coef *csc_coef);
hi_void vo_hal_intf_set_csc_cfg(hi_vo_intf_type intf, csc_coef *coef);
hi_void vo_hal_intf_set_dac_sel(hi_vo_intf_type intf_type);
hi_void vo_hal_intf_set_vga_and_cvbs_dac_enable(hi_bool enable);
hi_void vo_hal_intf_set_cvbs_dac_cfg(hi_void);
hi_void vo_hal_intf_set_dac_chn_enable(hi_vo_intf_type intf_type, hi_bool enable);
hi_void vo_hal_intf_set_dac_gc(hi_vo_intf_type intf_type, hi_u32 dac_gc);
hi_void vo_hal_intf_set_dac_cablectr(hi_vo_intf_type intf_type, hi_u32 cablectr);
hi_void vo_hal_intf_set_dac_det(hi_vo_dev dev, hi_vo_intf_type intf_type, hi_bool enable);
hi_void vo_hal_intf_set_vga_hsp_cfg(hi_bool enable, hi_u32 strength);
hi_void vo_hal_intf_set_date_cvbs_burst_start(hi_void);
hi_void vo_hal_intf_set_date_cvbs_color_burst(hi_void);
hi_u32 vo_hal_intf_get_date(hi_vo_intf_sync intf_sync, hi_u32 vact);
hi_void vo_hal_intf_set_date_cfg(hi_vo_intf_sync intf_sync, hi_u32 date);
hi_void vo_hal_intf_set_clip_cfg(hi_vo_intf_type intf_type, hi_bool clip, hal_disp_clip *clip_data);
hi_void vo_hal_intf_set_sync_info(hi_vo_dev dev, hal_disp_syncinfo *sync_info);
#endif
#endif /* #if VO_DESC("UBOOT VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of __HAL_VO_DEV_COMM_H__ */
