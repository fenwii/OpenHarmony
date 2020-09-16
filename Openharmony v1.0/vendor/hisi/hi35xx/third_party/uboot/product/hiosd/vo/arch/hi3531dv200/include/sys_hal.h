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

#include "hi_type.h"
#include "hi_common.h"

#ifndef __SYS_HAL_H__
#define __SYS_HAL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

hi_s32 sys_hal_vo_bus_reset_sel(hi_bool reset);
hi_s32 sys_hal_vo_vdac_phase_ctrl(hi_s32 dev, hi_bool clk_reverse);
hi_s32 sys_hal_vo_cfg_clk_en(hi_bool clk_en);
hi_s32 sys_hal_vo_apb_clk_en(hi_bool clk_en);
hi_s32 sys_hal_vo_bus_clk_en(hi_bool clk_en);
hi_s32 sys_hal_vo_out_hd_phase_ctrl(hi_s32 vo_dev, hi_bool reverse);
hi_s32 sys_hal_vo_dly_tune(hi_s32 vo_dev, hi_u32 dly_tune);
hi_s32 sys_hal_vo_out_hd_clk_div(hi_s32 vo_dev, hi_u32 clk_div);
hi_s32 sys_hal_vo_hd0_div_mode(hi_s32 dev, hi_u32 hd0_div_mod);
hi_s32 sys_hal_vo_hd_clk_sel(hi_s32 dev, hi_u32 clk_sel);
hi_s32 sys_hal_vo_core_clk_en(hi_s32 dev, hi_bool clk_en);
hi_s32 sys_hal_vo_dev_clk_en(hi_s32 vo_dev, hi_bool clk_en);
hi_s32 sys_hal_vo_hd1_div_mode(hi_s32 dev, hi_u32 div_mod);
hi_s32 sys_hal_vo_sd_div_mode(hi_s32 dev, hi_u32 div_mod);
hi_s32 sys_hal_vo_sd_clk_sel(hi_s32 dev, hi_u32 clk_sel);
hi_s32 sys_hal_vo_bt_clk_en(hi_s32 vo_dev, hi_bool bt_clk_en);
hi_s32 sys_hal_vo_bt_clk_sel(hi_s32 vo_dev, hi_u32 bt_clk_ch_sel);
hi_s32 sys_hal_vo_vdac_phase_ctrl(hi_s32 vo_dev, hi_bool clk_reverse);
hi_s32 sys_hal_vo_hd_vdac_clk_sel(hi_s32 vo_dev, hi_bool clk_sel);
hi_s32 sys_hal_vo_vdac_clk_en(hi_s32 vo_dev, hi_bool clk_en);
hi_s32 sys_hal_vo_hdmi_ssc_vdp_div(hi_s32 vo_dev, hi_u32 div_mode);
hi_s32 sys_hal_vo_hdmi_clk_en(hi_s32 vo_dev, hi_bool hdmi_clk_en);
hi_s32 sys_hal_vo_hdmi_clk_sel(hi_s32 vo_dev, hi_u32 clk_ch_sel);
hi_s32 sys_hal_vo_set_pll_postdiv2(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_vo_set_pll_postdiv1(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_vo_set_pll_frac(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_vo_set_pll_refdiv(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_vo_set_pll_fbdiv(hi_s32 pll, hi_u32 bits_set);
hi_s32 sys_hal_vo_set_pll_power_ctrl(hi_s32 pll, hi_bool power_on);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of #ifndef __SYS_HAL_H__ */
