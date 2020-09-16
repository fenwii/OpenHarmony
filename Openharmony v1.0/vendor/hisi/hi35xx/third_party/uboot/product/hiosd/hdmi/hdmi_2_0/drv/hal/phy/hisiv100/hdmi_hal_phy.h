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
#ifndef __HDMI_HAL_PHY_H__
#define __HDMI_HAL_PHY_H__

#include "hdmi_hal_intf.h"

typedef enum {
    PHY_RPRE_50,
    PHY_RPRE_56,
    PHY_RPRE_71,
    PHY_RPRE_83,
    PHY_RPRE_100,
    PHY_RPRE_125,
    PHY_RPRE_250,
    PHY_RPRE_500,
    PHY_RPRE_BUTT
} phy_rpre;

typedef enum {
    PHY_RTERM_MODE_SINGLE,
    PHY_RTERM_MODE_SOURCE,
    PHY_RTERM_MODE_LOAD,
    PHY_RTERM_MODE_DOUBLEDIFF,
    PHY_RTERM_MODE_BUTT
} phy_rterm_mode;

typedef enum {
    PHY_FEEDTHRU_CAP_DELAY_18,
    PHY_FEEDTHRU_CAP_DELAY_35,
    PHY_FEEDTHRU_CAP_DELAY_45,
    PHY_FEEDTHRU_CAP_DELAY_55
} phy_feedthru_cap_delay;

typedef struct {
    hi_u32 ssc_amptd; /* 1/1M ppm */
    hi_u32 ssc_freq;  /* 1Hz */
} phy_ssc_cfg;

typedef struct {
    hi_bool     ssc_enable;
    hi_bool     ssc_debug_en;
    phy_ssc_cfg phy_ssc_cfg;
} hdmi_phy_ssc;

typedef struct {
    hi_u32          pix_clk;    /* Pixel colck,in KHz */
    hi_u32          tmds_clk;   /* TMDS colck,in KHz */
    hdmi_deep_color deep_color; /* Deep color(color depth) */
    hdmi_phy_ssc    phy_ssc;    /* Spread Spectrum ctrl(ssc) para */
} hdmi_phy_ssc_cfg;

typedef struct {
    hi_u32         de_main_clk;
    hi_u32         de_main_d0;
    hi_u32         de_main_d1;
    hi_u32         de_main_d2;
    hi_u32         main_clk;
    hi_u32         main_d0;
    hi_u32         main_d1;
    hi_u32         main_d2;
    hi_u32         de_pre_clk;
    hi_u32         de_pre_d0;
    hi_u32         de_pre_d1;
    hi_u32         de_pre_d2;
    hi_u32         pre_clk;
    hi_u32         pre_d0;
    hi_u32         pre_d1;
    hi_u32         pre_d2;
    phy_rpre       de_rpre_clk;
    phy_rpre       de_rpre_d0;
    phy_rpre       de_rpre_d1;
    phy_rpre       de_rpre_d2;
    phy_rpre       rpre_clk;
    phy_rpre       rpre_d0;
    phy_rpre       rpre_d1;
    phy_rpre       rpre_d2;
    phy_rterm_mode term_mode_clk;
    hi_u32         term_clk;
    phy_rterm_mode term_mode_d0;
    hi_u32         term_d0;
    phy_rterm_mode term_mode_d1;
    hi_u32         term_d1;
    phy_rterm_mode term_mode_d2;
    hi_u32         term_d2;
} phy_hw_spec_cfg;

typedef struct {
    hi_u32                 i_demain_clk;
    hi_u32                 i_demain_d0;
    hi_u32                 i_demain_d1;
    hi_u32                 i_demain_d2;
    hi_u32                 i_main_clk;
    hi_u32                 i_main_d0;
    hi_u32                 i_main_d1;
    hi_u32                 i_main_d2;
    hi_bool                feedthru_cap_clk_en;
    hi_bool                feedthru_cap_d0_en;
    hi_bool                feedthru_cap_d1_en;
    hi_bool                feedthru_cap_d2_en;
    phy_feedthru_cap_delay feedthru_cap_delay_clk;
    phy_feedthru_cap_delay feedthru_cap_delay_d0;
    phy_feedthru_cap_delay feedthru_cap_delay_d1;
    phy_feedthru_cap_delay feedthru_cap_delay_d2;
    phy_rterm_mode         rterm_mode_clk;
    hi_u32                 rterm_clk;
    phy_rterm_mode         rterm_mode_d0;
    hi_u32                 rterm_d0;
    phy_rterm_mode         rterm_mode_d1;
    hi_u32                 rterm_d1;
    phy_rterm_mode         rterm_mode_d2;
    hi_u32                 rterm_d2;
    hi_u32                 vcm_sel;
} phy_hwspec_enhance_cfg;

typedef struct {
    hi_bool         hw_spec_debug_en;
    phy_hw_spec_cfg phy_spec_cfg;
    phy_hwspec_enhance_cfg enhance_cfg;
} hdmi_phy_hw_spec;

typedef struct {
    hi_u32 tmds_clk;               /* TMDS colck, in KHz */
    hdmi_trace_len trace_len;
    hdmi_phy_hw_spec hdmi_phy_spec; /* phy specification para */
} hdmi_phy_hw_spec_cfg;

typedef struct {
    hi_u32            pixel_clk;
    hi_u32            tmds_clk;   /* TMDS colck,in KHz */
    hi_bool           emi_enable;
    hdmi_deep_color   deep_color; /* Deep color(color depth) */
    hdmi_phy_mode_cfg mode_cfg;   /* TMDS/FRL/TxFFE */
    hdmi_trace_len    trace_len;
} hdmi_phy_tmds_cfg;

typedef struct {
    hi_bool           init;
    hi_bool           power_enable;
    hi_bool           oe_enable;
    hdmi_phy_tmds_cfg tmds_cfg;
    hdmi_phy_ssc      ssc_cfg;
    phy_hw_spec_cfg   hw_spec_cfg;
    hdmi_hw_spec      hw_spec;
    phy_hwspec_enhance_cfg spec_enhance_cfg;
} hdmi_phy_info;

typedef struct {
    hdmi_hw_spec  hw_spec_cfg;
    hdmi_hw_spec  hw_spec_def;
    hdmi_hw_param hw_param_cur;
} hdmi_phy_hw_param;

hi_s32 hal_hdmi_phy_init(const hdmi_hal_init *hal_init);

hi_s32 hal_hdmi_phy_deinit(hi_void);

hi_void hal_hdmi_phy_reset(hi_void);

hi_s32 hal_hdmi_phy_power_get(hi_bool *enable);

hi_void hal_hdmi_phy_power_set(hi_bool enable);

hi_void hal_hdmi_phy_oe_set(hi_bool enable);

hi_s32 hal_hdmi_phy_oe_get(hi_bool *enable);

hi_s32 hal_hdmi_phy_tmds_set(const hdmi_phy_tmds_cfg *tmds_cfg);

hi_s32 hal_hdmi_phy_spec_set(hdmi_phy_hw_spec_cfg *hdmi_spec_cfg);

hi_s32 hal_hdmi_phy_info_get(hdmi_phy_info *phy_status);

hi_s32 hal_hdmi_phy_ssc_set(hdmi_phy_ssc_cfg *hdmi_ssc_cfg);

hi_s32 hal_hdmi_phy_ssc_get(hi_bool *enable);

#ifdef PHY_CRAFT_S28
hi_s32 hal_hdmi_phy_params_get(hdmi_phy_hw_param *hw_param);

hi_s32 hal_hdmi_phy_params_set(hdmi_hal_hw_param param);
#endif
#endif /* __HDMI_HAL_PHY_H__ */

