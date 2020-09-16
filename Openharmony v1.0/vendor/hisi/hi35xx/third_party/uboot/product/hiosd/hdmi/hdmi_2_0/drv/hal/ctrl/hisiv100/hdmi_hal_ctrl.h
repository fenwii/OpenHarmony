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
#ifndef __HDMI_HAL_CTRL_H__
#define __HDMI_HAL_CTRL_H__

#include "hi_type.h"
#include "drv_hdmi_common.h"

typedef enum {
    HDMI_COLORMETRY_BT709,
    HDMI_COLORMETRY_BT601,
    HDMI_COLORMETRY_BT2020,
    HDMI_COLORMETRY_BT2020_CONST,
    HDMI_COLORMETRY_BUTT
} hdmi_colormetry;

typedef struct {
    hi_bool h_pol_invert;
    hi_bool v_pol_invert;
    hi_bool de_invert;
} hdmi_sync_pol;

typedef struct {
    hdmi_video_timing timming;
    hi_u32            in_pixel_clk;
    hi_u32            out_tmds_clk;
    hdmi_colorspace   in_colorspace;
    hdmi_colorspace   out_colorspace;
    hdmi_colormetry   in_colormetry;
    hdmi_colormetry   out_colormetry;
    hdmi_deep_color   in_deep_color;
    hdmi_deep_color   out_deep_color;
    hdmi_sync_pol     out_hv_sync_pol;
    hdmi_quantization in_quantization;
    hdmi_quantization out_quantization;
} hdmi_video_path;

typedef struct {
    hi_bool init;
    hdmi_video_path video_path;
} hdmi_ctrl_info;

hi_s32 hal_hdmi_ctrl_init(hdmi_device_id hdmi_id, const hdmi_hal_init *hal_init);

hi_void hal_hdmi_ctrl_deinit(hdmi_device_id hdmi_id);

hi_void hal_hdmi_ctrl_avmute_set(hdmi_device_id hdmi_id, const hdmi_avmute_cfg *avmute_cfg);

hi_void hal_hdmi_ctrl_videopath_set(hdmi_device_id hdmi_id, hdmi_video_path *video_path);

hi_s32 hal_hdmi_ctrl_tmds_mode_set(hdmi_device_id hdmi_id, hdmi_tmds_mode tmds_mode);

hi_s32 hal_hdmi_ctrl_infoframe_en_set(hdmi_device_id hdmi_id, hdmi_infoframe_id infoframe_id, hi_bool enable);

hi_s32 hal_hdmi_ctrl_infoframe_data_set(hdmi_device_id hdmi_id, hdmi_infoframe_id infoframe_id, const hi_u8 *if_data);

hi_void hal_hdmi_ctrl_csc_set(hdmi_device_id hdmi_id, const hdmi_video_config *video_cfg);

hi_void hal_hdmi_ctrl_data_reset(hdmi_device_id hdmi_id, hi_bool debug_mode, hi_u32 delay_ms);

hi_void hal_hdmi_ctrl_tmds_stable_get(hdmi_device_id hdmi_id, hi_bool *stable);

#endif /* __HDMI_HAL_CTRL_H__ */

