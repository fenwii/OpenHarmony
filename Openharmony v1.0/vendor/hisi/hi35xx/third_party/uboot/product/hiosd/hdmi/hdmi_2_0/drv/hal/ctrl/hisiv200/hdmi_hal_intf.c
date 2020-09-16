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
#include "hdmi_hal_intf.h"
#include "hdmi_hal_phy.h"
#include "hdmi_reg_crg.h"
#include "hdmi_product_define.h"
#include "boot_hdmi_intf.h"
#include "ubi_uboot.h"
#include "malloc.h"

#define TMDS_MAX_CLK       600
#define TMDS_CLK_RATIO_10X 10
#define TMDS_CLK_RATIO_40X 40

static hdmi_hal_cfg g_hal_cfg[HDMI_DEVICE_ID_BUTT];

static hdmi_deep_color depth_convert_to_deep_color(hdmi_video_bit_depth video_bit_depth)
{
    hdmi_deep_color ret;

    switch (video_bit_depth) {
        case HDMI_VIDEO_BITDEPTH_8:
            ret = HDMI_DEEP_COLOR_24BIT;
            break;
        case HDMI_VIDEO_BITDEPTH_10:
            ret = HDMI_DEEP_COLOR_30BIT;
            break;
        case HDMI_VIDEO_BITDEPTH_12:
            ret = HDMI_DEEP_COLOR_36BIT;
            break;
        case HDMI_VIDEO_BITDEPTH_16:
            ret = HDMI_DEEP_COLOR_48BIT;
            break;
        case HDMI_VIDEO_BITDEPTH_OFF:
            ret = HDMI_DEEP_COLOR_OFF;
            break;
        default:
           ret = HDMI_DEEP_COLOR_OFF;
            break;
    }

    return ret;
}

static hdmi_hal_cfg *intf_hal_info_get(hdmi_device_id hdmi_id)
{
    if (hdmi_id < HDMI_DEVICE_ID_BUTT) {
        return &g_hal_cfg[hdmi_id];
    }
    return HI_NULL;
}

static hi_void intf_tx_capability_init(hdmi_device_id hdmi_id)
{
    hdmi_hal_cfg *hal_cfg = intf_hal_info_get(hdmi_id);

    hdmi_if_null_return_void(hal_cfg);

    /* Tx Capability */
    hal_cfg->tx_capability.tx_hdmi_14  = HI_TRUE;
    hal_cfg->tx_capability.tx_hdmi_20  = HI_TRUE;
    hal_cfg->tx_capability.tx_hdmi_21  = HI_TRUE;
    hal_cfg->tx_capability.tx_hdcp_14  = HI_TRUE;
    hal_cfg->tx_capability.tx_hdcp_22  = HI_TRUE;
    hal_cfg->tx_capability.tx_rgb444   = HI_TRUE;
    hal_cfg->tx_capability.tx_ycbcr444 = HI_TRUE;
    hal_cfg->tx_capability.tx_ycbcr422 = HI_TRUE;
    hal_cfg->tx_capability.tx_ycbcr420 = HI_TRUE;
    hal_cfg->tx_capability.tx_deep_clr10_bit = HI_TRUE;
    hal_cfg->tx_capability.tx_deep_clr12_bit = HI_TRUE;
    hal_cfg->tx_capability.tx_deep_clr16_bit = HI_FALSE;
    hal_cfg->tx_capability.tx_rgb_ycbcr444 = HI_TRUE;
    hal_cfg->tx_capability.tx_ycbcr444_422 = HI_TRUE;
    hal_cfg->tx_capability.tx_ycbcr422_420 = HI_TRUE;
    hal_cfg->tx_capability.tx_ycbcr420_422 = HI_TRUE;
    hal_cfg->tx_capability.tx_ycbcr422_444 = HI_TRUE;
    hal_cfg->tx_capability.tx_ycbcr444_rgb = HI_TRUE;
    hal_cfg->tx_capability.tx_scdc         = HI_TRUE;
    hal_cfg->tx_capability.tx_max_tmds_clk = TMDS_MAX_CLK;

    return;
}

static hi_void hal_hdmi_hardware_init(const struct hi_hdmi_hal_ *hdmi_hal)
{
    drv_hdmi_prod_crg_init();
    return;
}

static hi_void hal_hdmi_tmds_mode_set(const struct hi_hdmi_hal_ *hdmi_hal, hdmi_tmds_mode tmds_mode)
{
    hdmi_if_null_return_void(hdmi_hal);
    hal_hdmi_ctrl_tmds_mode_set(hdmi_hal->hal_ctx.hdmi_id, tmds_mode);
    return;
}

static hi_void hal_hdmi_avmute_set(const struct hi_hdmi_hal_ *hdmi_hal, hi_bool avmute)
{
    hdmi_avmute_cfg avmute_cfg = {0};
    hdmi_if_null_return_void(hdmi_hal);
    hal_hdmi_ctrl_avmute_set(hdmi_hal->hal_ctx.hdmi_id, &avmute_cfg);
    return;
}

static hi_void hal_hdmi_csc_param_set(struct hi_hdmi_hal_ *hdmi_hal, const hdmi_video_config *video_cfg)
{
    hdmi_if_null_return_void(hdmi_hal);
    hdmi_if_null_return_void(video_cfg);

    hal_hdmi_ctrl_csc_set(hdmi_hal->hal_ctx.hdmi_id, video_cfg);
    hdmi_hal->hal_ctx.video_cfg.in_colorspace  = video_cfg->in_colorspace;
    hdmi_hal->hal_ctx.video_cfg.out_colorspace = video_cfg->out_colorspace;
    hdmi_hal->hal_ctx.video_cfg.out_csc_quantization = video_cfg->out_csc_quantization;
    hdmi_hal->hal_ctx.video_cfg.conv_std = video_cfg->conv_std;

    return;
}

static hi_void hal_hdmi_infoframe_set(const struct hi_hdmi_hal_ *hdmi_hal,
                                      hdmi_infoframe_id infoframe_id, const hi_u8 *in_buffer)
{
    hdmi_if_null_return_void(hdmi_hal);
    hdmi_if_null_return_void(in_buffer);
    hal_hdmi_ctrl_infoframe_data_set(hdmi_hal->hal_ctx.hdmi_id, infoframe_id, in_buffer);
    return;
}

static hi_void hal_hdmi_infoframe_enable_set(const struct hi_hdmi_hal_ *hdmi_hal,
                                             hdmi_infoframe_id infoframe_id, hi_bool enable)
{
    hdmi_if_null_return_void(hdmi_hal);
    hal_hdmi_ctrl_infoframe_en_set(hdmi_hal->hal_ctx.hdmi_id, infoframe_id, enable);
    return;
}

static hi_s32 hal_hdmi_video_path_set(const struct hi_hdmi_hal_ *hdmi_hal, const hdmi_video_config *video_cfg)
{
    hdmi_video_path   video_path = {0};
    hdmi_hal_cfg      *hal_cfg = HI_NULL;
    hdmi_phy_tmds_cfg phy_tmds = {0};

    hdmi_if_null_return(hdmi_hal, HI_FAILURE);
    hdmi_if_null_return(video_cfg, HI_FAILURE);
    hal_cfg = intf_hal_info_get(hdmi_hal->hal_ctx.hdmi_id);
    hdmi_if_null_return(hal_cfg, HI_FAILURE);
    hal_cfg->tmds_clk = video_cfg->tmds_clk;

    video_path.in_colorspace = video_cfg->in_colorspace;
    video_path.out_colorspace = video_cfg->out_colorspace;
    video_path.in_deep_color = depth_convert_to_deep_color(video_cfg->in_bit_depth);
    video_path.out_deep_color = video_cfg->deep_color;
    video_path.out_hv_sync_pol.de_invert = video_cfg->de_pol;
    video_path.out_hv_sync_pol.h_pol_invert = video_cfg->h_sync_pol;
    video_path.out_hv_sync_pol.v_pol_invert = video_cfg->v_sync_pol;

    switch (video_cfg->conv_std) {
        case HDMI_CONV_STD_BT_601:
            video_path.out_colormetry = HDMI_COLORMETRY_BT601;
            break;
        case HDMI_CONV_STD_BT_709:
            video_path.out_colormetry = HDMI_COLORMETRY_BT709;
            break;
        case HDMI_CONV_STD_BT_2020_NON_CONST_LUMINOUS:
            video_path.out_colormetry = HDMI_COLORMETRY_BT2020;
            break;
        case HDMI_CONV_STD_BT_2020_CONST_LUMINOUS:
            video_path.out_colormetry = HDMI_COLORMETRY_BT2020_CONST;
            break;
        default:
            video_path.out_colormetry = HDMI_COLORMETRY_BT709;
            break;
    }
    video_path.in_colormetry    = video_path.out_colormetry;
    video_path.in_quantization  = video_cfg->out_csc_quantization;
    video_path.out_quantization = video_cfg->out_csc_quantization;
    video_path.in_pixel_clk     = video_cfg->pixel_clk;
    video_path.out_tmds_clk     = video_cfg->tmds_clk;
    video_path.timming          = video_cfg->timming;

    hal_hdmi_ctrl_videopath_set(hdmi_hal->hal_ctx.hdmi_id, &video_path);
    /* PHY config */
    phy_tmds.emi_enable = video_cfg->emi_enable;
    phy_tmds.deep_color = video_cfg->deep_color;
    phy_tmds.pixel_clk  = video_cfg->pixel_clk;
    phy_tmds.tmds_clk   = video_cfg->tmds_clk;
    phy_tmds.mode_cfg   = HDMI_PHY_MODE_CFG_TMDS;
    phy_tmds.trace_len  = HDMI_TRACE_LEN_1;
    (hi_void)hal_hdmi_phy_tmds_set(&phy_tmds);

    return HI_SUCCESS;
}

static hi_void hal_hdmi_ctrl_reset(const struct hi_hdmi_hal_ *hdmi_hal)
{
    hi_bool output = HI_FALSE;

    hdmi_if_null_return_void(hdmi_hal);
    hal_hdmi_phy_oe_get(&output);
    if (output == HI_FALSE) {
        hdmi_info("oe enable, do not reset!\n");
        hal_hdmi_ctrl_data_reset(hdmi_hal->hal_ctx.hdmi_id);
    }

    return;
}

static hi_void hal_hdmi_phy_output_enable_set(const struct hi_hdmi_hal_ *hdmi_hal, hi_bool enable)
{
    hdmi_if_null_return_void(hdmi_hal);
#ifndef HDMI_FPGA_SUPPORT
    hal_hdmi_phy_oe_set(enable);
#endif
    return;
}

static hi_void hal_hdmi_phy_power_enable_set(const struct hi_hdmi_hal_ *hdmi_hal, hi_bool enable)
{
#ifndef HDMI_FPGA_SUPPORT
    hi_bool old_eable = HI_FALSE;

    hal_hdmi_phy_power_get(&old_eable);
    if (enable != old_eable) {
        hal_hdmi_phy_power_set(enable);
    }
#endif
    return;
}

static hi_void hal_hdmi_phy_set(const struct hi_hdmi_hal_ *hdmi_hal, const hdmi_phy_cfg *phy_cfg)
{
#ifndef HDMI_FPGA_SUPPORT
    hdmi_phy_tmds_cfg cfg = {0};

    hdmi_if_null_return_void(phy_cfg);
    memcpy(&cfg, phy_cfg, sizeof(hdmi_phy_tmds_cfg));
    hal_hdmi_phy_tmds_set(&cfg);
#endif
    return;
}

static hi_void hal_hdmi_tx_capability_get(const struct hi_hdmi_hal_ *hdmi_hal, hdmi_tx_capability *tx_capability)
{
    hdmi_hal_cfg *hal_cfg = HI_NULL;

    hdmi_if_null_return_void(hdmi_hal);
    hdmi_if_null_return_void(tx_capability);
    hal_cfg = intf_hal_info_get(hdmi_hal->hal_ctx.hdmi_id);
    hdmi_if_null_return_void(hal_cfg);
    hdmi_if_false_return_void(hal_cfg->init);
    memcpy(tx_capability, &hal_cfg->tx_capability, sizeof(hdmi_tx_capability));
    return;
}

#ifdef HDMI_SCDC_SUPPORT
static hi_void hal_hdmi_scdc_status_set(const struct hi_hdmi_hal_ *hdmi_hal, const hdmi_scdc_status *status)
{
    scdc_attr attr = {0};

    hdmi_if_null_return_void(hdmi_hal);
    hdmi_if_null_return_void(status);
    attr.sink_read_quest   = HI_FALSE;
    attr.sink_scramble     = status->sink_scramble_on;
    attr.src_scramble      = status->source_scramble_on;
    attr.tmds_clk_ratio40x = status->tmds_bit_clk_ratio == TMDS_CLK_RATIO_40X ? HI_TRUE : HI_FALSE;
    attr.scramble_interval = status->scramble_interval;
    attr.scramble_timeout  = status->scramble_timeout;
    hal_hdmi_scdc_attr_set(hdmi_hal->hal_ctx.hdmi_id, &attr);

    return;
}

static hi_void hal_hdmi_scdc_status_get(const struct hi_hdmi_hal_ *hdmi_hal, hdmi_scdc_status *status)
{
    scdc_attr attr = {0};

    hdmi_if_null_return_void(hdmi_hal);
    hdmi_if_null_return_void(status);
    hal_hdmi_scdc_attr_get(hdmi_hal->hal_ctx.hdmi_id, &attr);
    status->sink_read_quest    = HI_FALSE;
    status->sink_scramble_on   = attr.sink_scramble;
    status->source_scramble_on = attr.src_scramble;
    status->tmds_bit_clk_ratio = attr.tmds_clk_ratio40x ? TMDS_CLK_RATIO_40X : TMDS_CLK_RATIO_10X;
    status->scramble_interval  = attr.scramble_interval;
    status->scramble_timeout   = attr.scramble_timeout;

    return;
}
#endif

static hi_void hal_pfn_init(hdmi_hal *hal)
{
    hal->hal_hdmi_hardware_init         = hal_hdmi_hardware_init;
    hal->hal_hdmi_avmute_set            = hal_hdmi_avmute_set;
    hal->hal_hdmi_tmds_mode_set         = hal_hdmi_tmds_mode_set;
    hal->hal_hdmi_infoframe_set         = hal_hdmi_infoframe_set;
    hal->hal_hdmi_infoframe_enable_set  = hal_hdmi_infoframe_enable_set;
    hal->hal_hdmi_video_path_set        = hal_hdmi_video_path_set;
    hal->hal_hdmi_phy_power_enable_set  = hal_hdmi_phy_power_enable_set;
    hal->hal_hdmi_phy_output_enable_set = hal_hdmi_phy_output_enable_set;
    hal->hal_hdmi_tx_capability_get     = hal_hdmi_tx_capability_get;
    hal->hal_hdmi_csc_param_set         = hal_hdmi_csc_param_set;
    hal->hal_hdmi_phy_set               = hal_hdmi_phy_set;
    hal->hal_hdmi_ctrl_reset            = hal_hdmi_ctrl_reset;
#ifdef HDMI_SCDC_SUPPORT
    hal->hal_hdmi_scdc_status_get = hal_hdmi_scdc_status_get;
    hal->hal_hdmi_scdc_status_set = hal_hdmi_scdc_status_set;
#endif

    return;
}

hi_s32 hal_hdmi_open(const hdmi_hal_init *hal_init, hdmi_hal** hal_handle)
{
    hdmi_hal *hal = HI_NULL;
    hdmi_hal_cfg *hal_cfg = HI_NULL;

    hal = (hdmi_hal *)vmalloc(sizeof(hdmi_hal));
    if (hal == HI_NULL) {
        hdmi_err("Alloc HDMI_HAL_S struct memory fail\n");
        return HI_FAILURE;
    }
    memset(hal, 0, sizeof(hdmi_hal));
    if (hal_init != HI_NULL) {
        hal->hal_ctx.callback  = hal_init->event_callback;
        hal->hal_ctx.hdmi_dev  = hal_init->event_data;
        hal->hal_ctx.hdmi_id   = hal_init->hdmi_dev_id;
        hal->hal_ctx.base_addr = hal_init->base_addr;
        hal->hal_ctx.phy_addr  = hal_init->phy_addr;
    } else {
        hdmi_info("hal_init null! open in boot!\n");
    }
    hal_cfg = intf_hal_info_get(hal->hal_ctx.hdmi_id);
    if (hal_cfg == HI_NULL) {
        vfree(hal);
        hdmi_err("hal_cfg null,fail!\n");
        return HI_FAILURE;
    }

    intf_tx_capability_init(hal->hal_ctx.hdmi_id);
#ifndef HDMI_FPGA_SUPPORT
    hal_hdmi_phy_init(hal_init);
#endif
    hal_hdmi_ctrl_init(hal->hal_ctx.hdmi_id, hal_init);
    hal_hdmi_ddc_init(hal->hal_ctx.hdmi_id);
#ifdef HDMI_SCDC_SUPPORT
    hal_hdmi_scdc_init(hal->hal_ctx.hdmi_id);
#endif
    hal_pfn_init(hal);
    *hal_handle = hal;
    hal_cfg->init = HI_TRUE;

    return HI_SUCCESS;
}

void hal_hdmi_close(hdmi_hal *hal)
{
    hdmi_hal_cfg *hal_cfg = (hdmi_hal_cfg *)HI_NULL;

    hdmi_if_null_return_void(hal);
    hal_cfg = intf_hal_info_get(hal->hal_ctx.hdmi_id);
    hdmi_if_null_return_void(hal_cfg);

#ifdef HDMI_SCDC_SUPPORT
    hal_hdmi_scdc_deinit(hal->hal_ctx.hdmi_id);
#endif
    hal_hdmi_ddc_deinit(hal->hal_ctx.hdmi_id);
    hal_hdmi_ctrl_deinit(hal->hal_ctx.hdmi_id);
#ifndef HDMI_FPGA_SUPPORT
    hal_hdmi_phy_deinit();
#endif
    reg_hdmi_crg_reg_deinit();
    hal->hal_ctx.base_addr = HI_NULL;
    hal->hal_ctx.phy_addr  = HI_NULL;
    memset(hal, 0, sizeof(hdmi_hal));
    vfree(hal);
    hal_cfg->init = HI_FALSE;

    return;
}

