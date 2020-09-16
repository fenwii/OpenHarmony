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
#include "hdmi_hal_ctrl.h"
#include "hdmi_hal_intf.h"
#include "hdmi_osal.h"
#include "hdmi_reg_tx.h"
#include "hdmi_reg_video_path.h"
#include "hdmi_reg_aon.h"
#include "hdmi_reg_ctrl.h"
#include "hdmi_hal_ddc.h"
#include "hdmi_reg_crg.h"
#include "hdmi_product_define.h"
#include "hdmi_reg_dphy.h"

#define CTRL_CHANNEL0_Y    0x0
#define CTRL_CHANNEL0_Y422 0x3
#define CTRL_CHANNEL1_CB   0x1
#define CTRL_CHANNEL1_Y422 0x4
#define CTRL_CHANNEL2_CR   0x2
#define CTRL_CHANNEL2_Y422 0x3
#define CTRL_COLORMETRY_OUT_MASK 0xfc
#define CTRL_COLORMETRY_OUT_BIT  0       /* out colormetry offset in reg_csc_mode */
#define CTRL_COLORMETRY_IN_MASK  0xcf
#define CTRL_COLORMETRY_IN_BIT   0x4     /* in colormetry offset in reg_csc_mode */
#define CTRL_COLORMETRY_MASK     0x3
#define CTRL_RGB_OUT_BIT         0x3     /* out color space offset in reg_csc_mode */
#define CTRL_RGB_IN_BIT          0x7     /* in color space offset in reg_csc_mode */
#define CTRL_QUANTIZAION_OUT_BIT 0x2     /* out quantization offset in reg_csc_mode */
#define CTRL_QUANTIZAION_IN_BIT  0x6     /* in quantization offset in reg_csc_mode */
#define CTRL_SYCN_POL_V_BIT      0       /* vsync offset in reg_inver_sync */
#define CTRL_SYCN_POL_H_BIT      1       /* hsync offset in reg_inver_sync */
#define CTRL_SYCN_POL_DE_BIT     0x3     /* DE offset in reg_inver_sync */
#define CTRL_BLACK_Y_CB_CR       0x000000
#define CTRL_BLACK_DATA_YUV_CR   0x200   /* cr val for yuv black */
#define CTRL_BLACK_DATA_YUV_Y    0x40    /* y val for yuv black */
#define CTRL_BLACK_DATA_YUV_CB   0x200   /* cb val for yuv black */
#define CTRL_BLACK_DATA_RGB_R    0x40    /* r val for rgb black */
#define CTRL_BLACK_DATA_RGB_G    0x40    /* g val for rgb black */
#define CTRL_BLACK_DATA_RGB_B    0x40    /* b val for rgb black */
#define CTRL_DATA_RESET_DELAY    2
#define START_TIME_MAX           30
#define TMDS_TOP_THRESHOLD_1     1
#define TMDS_TOP_THRESHOLD_2     2
#define TMDS_TOP_THRESHOLD_4     4
#define TX_CTRL_ADDR             0x0980
#define TX_CTRL_ADDR_OFFSET      3
#define TX_DEEPCOLOR_CTRL_ADDR   0x1800

typedef struct {
    hi_bool in_rgb;
    hi_bool out_rgb;
    hi_bool csc_enable;
    hi_bool y422_enable;
    hi_bool y420_enable;
    hi_bool dwsm_hori_enable;
    hi_bool dwsm_vert_enable;
} ctrl_colorspace_en;

static hdmi_ctrl_info g_ctrl_info[HDMI_DEVICE_ID_BUTT];

static hdmi_ctrl_info *ctrl_info_get(hdmi_device_id hdmi_id)
{
    if (hdmi_id < HDMI_DEVICE_ID_BUTT) {
        return &g_ctrl_info[hdmi_id];
    }
    return HI_NULL;
}

static hi_void ctrl_avmute_set(const hdmi_avmute_cfg *avmute_cfg)
{
    hdmi_cea_cp_en_set(HI_FALSE);
    /* set GCP set mute & clr mute */
    hdmi_cp_set_avmute_set(avmute_cfg->mute_set);
    hdmi_cp_clr_avmute_set(avmute_cfg->mute_clr);
    /* set GCP avmute funtion enable,sent loop */
    hdmi_cea_cp_rpt_cnt_set(avmute_cfg->rpt_cnt);
    hdmi_cea_cp_rpt_en_set(avmute_cfg->mute_rpt_en);
    hdmi_cea_cp_en_set(avmute_cfg->mute_pkg_en);

    return;
}

static hi_void ctrl_videopath_deep_clr_set(hi_bool enalbe_gcp, hdmi_deep_color deep_color_bit)
{
    hi_u32 reg;

    if (hdmi_tx_channel_reg_vid_bypass_sel_get() == HI_TRUE) {
        /* 36bit must use 2.0 channel */
        reg = hdmi_tx_ctrl_read(TX_DEEPCOLOR_CTRL_ADDR);
        reg &= 0xFFFFFFFC; /* reset BIT[1:0] */
        reg |= deep_color_bit;
        hdmi_tx_ctrl_write(TX_DEEPCOLOR_CTRL_ADDR, reg);
    } else {
        hdmi_tx_pack_fifo_ctrl_tmds_pack_mode_set(deep_color_bit);
    }
    hdmi_avmixer_config_dc_pkt_en_set(enalbe_gcp);

    return;
}

static hi_void ctrl_videopath_polarity_set(const hdmi_sync_pol *out_sync_pol)
{
    hi_u32 sync_pol_cfg = 0;

    if (out_sync_pol->h_pol_invert) {
        hdmi_set_bit(sync_pol_cfg, CTRL_SYCN_POL_H_BIT);
    } else {
        hdmi_clr_bit(sync_pol_cfg, CTRL_SYCN_POL_H_BIT);
    }
    if (out_sync_pol->v_pol_invert) {
        hdmi_set_bit(sync_pol_cfg, CTRL_SYCN_POL_V_BIT);
    } else {
        hdmi_clr_bit(sync_pol_cfg, CTRL_SYCN_POL_V_BIT);
    }
    if (out_sync_pol->de_invert) {
        hdmi_set_bit(sync_pol_cfg, CTRL_SYCN_POL_DE_BIT);
    } else {
        hdmi_clr_bit(sync_pol_cfg, CTRL_SYCN_POL_DE_BIT);
    }
    hdmi_video_dmux_ctrl_reg_inver_sync_set(sync_pol_cfg);
    hdmi_video_dmux_ctrl_reg_syncmask_en_set(HI_FALSE);

    return;
}

static hi_void ctrl_videopath_dither_set(hi_bool enable, hdmi_video_dither dither_mode)
{
    hdmi_dither_config_rnd_byp_set((!enable));
    hdmi_dither_config_mode_set(dither_mode);
    return;
}

static hi_void ctrl_video_color_rgb_set(hi_bool rgb_in, hi_bool rgb_out)
{
    hi_u32 reg_value;

    reg_value = hdmi_multi_csc_ctrl_reg_csc_mode_get();
    if (rgb_in) {
        hdmi_set_bit(reg_value, CTRL_RGB_IN_BIT);
    } else {
        hdmi_clr_bit(reg_value, CTRL_RGB_IN_BIT);
    }
    if (rgb_out) {
        hdmi_set_bit(reg_value, CTRL_RGB_OUT_BIT);
    } else {
        hdmi_clr_bit(reg_value, CTRL_RGB_OUT_BIT);
    }
    hdmi_multi_csc_ctrl_reg_csc_mode_set(reg_value);
    hdmi_yuv_rgb_cfg_reg_set(rgb_in);

    return;
}

static hi_void ctrl_video_color_csc_set(hi_bool csc_enable)
{
    hdmi_multi_csc_ctrl_reg_csc_en_set(csc_enable);
    return;
}

static hi_void ctrl_video_color_ycbcr422_set(hi_bool ycbcr422)
{
    if (ycbcr422) {
        hdmi_video_dmux_ctrl_reg_vmux_y_sel_set(CTRL_CHANNEL0_Y422);
        hdmi_video_dmux_ctrl_reg_vmux_cb_sel_set(CTRL_CHANNEL1_Y422);
        hdmi_video_dmux_ctrl_reg_vmux_cr_sel_set(CTRL_CHANNEL2_Y422);
    } else {
        hdmi_video_dmux_ctrl_reg_vmux_y_sel_set(CTRL_CHANNEL0_Y);
        hdmi_video_dmux_ctrl_reg_vmux_cb_sel_set(CTRL_CHANNEL1_CB);
        hdmi_video_dmux_ctrl_reg_vmux_cr_sel_set(CTRL_CHANNEL2_CR);
    }

    return;
}

static hi_void ctrl_video_color_ycbcr420_set(hi_bool ycbcr420)
{
    hdmi_data_align_ctrl_reg_demux_420_en_set(ycbcr420);
    hdmi_data_align_ctrl_reg_pxl_div_en_set(ycbcr420);
    return;
}

static hi_void ctrl_video_color_dwsm_vert_set(hi_bool dwsm_vert)
{
    hi_u32 reg;

    if (hdmi_tx_channel_reg_vid_bypass_sel_get() == HI_TRUE) {
        /* 2.0 channel is different */
        reg = hdmi_tx_ctrl_read(TX_CTRL_ADDR);
        reg &= (~(1 << TX_CTRL_ADDR_OFFSET));
        reg |= ((!dwsm_vert) << TX_CTRL_ADDR_OFFSET);
        hdmi_tx_ctrl_write(TX_CTRL_ADDR, reg);
    } else {
        hdmi_data_align_ctrl_reg_vert_cbcr_sel_set(HI_FALSE);
    }
    hdmi_video_dwsm_ctrl_reg_dwsm_vert_en_set(dwsm_vert);

    return;
}

static hi_void ctrl_video_color_dwsm_hori_set(hi_bool dwsm_hori)
{
    hdmi_video_dwsm_ctrl_reg_dwsm_hori_en_set(dwsm_hori);
    if (hdmi_tx_channel_reg_vid_bypass_sel_get() == HI_TRUE) {
        /* 2.0 channel */
        hdmi_video_dwsm_ctrl_reg_hori_filter_en_set(dwsm_hori);
    } else {
        hdmi_video_dwsm_ctrl_reg_hori_filter_en_set(HI_FALSE);
    }

    return;
}

static hi_void ctrl_videopath_colormetry_set(hdmi_colormetry in_colormetry, hdmi_colormetry out_colormetry)
{
    hi_u32 csc_mode;

    csc_mode = hdmi_multi_csc_ctrl_reg_csc_mode_get();
    out_colormetry &= CTRL_COLORMETRY_MASK;
    csc_mode &= CTRL_COLORMETRY_OUT_MASK;
    csc_mode |= out_colormetry << CTRL_COLORMETRY_OUT_BIT;
    in_colormetry &= CTRL_COLORMETRY_MASK;
    csc_mode &= CTRL_COLORMETRY_IN_MASK;
    csc_mode |= in_colormetry << CTRL_COLORMETRY_IN_BIT;
    hdmi_multi_csc_ctrl_reg_csc_mode_set(csc_mode);

    return;
}

static hi_void videopath_colorspace_param_get(hdmi_colorspace in, hdmi_colorspace out, ctrl_colorspace_en *en)
{
    if (in == HDMI_COLORSPACE_YCBCR444) {
        switch (out) {
            case HDMI_COLORSPACE_YCBCR422:
                en->y422_enable      = HI_TRUE;
                en->dwsm_hori_enable = HI_TRUE;
                break;
            case HDMI_COLORSPACE_YCBCR420:
                en->dwsm_hori_enable = HI_TRUE;
                en->y420_enable      = HI_TRUE;
                en->dwsm_vert_enable = HI_TRUE;
                break;
            case HDMI_COLORSPACE_RGB:
                en->out_rgb    = HI_TRUE;
                en->csc_enable = HI_TRUE;
                break;
            default:
                break;
        }
    } else if (in == HDMI_COLORSPACE_RGB) {
        switch (out) {
            case HDMI_COLORSPACE_YCBCR444:
                en->in_rgb     = HI_TRUE;
                en->csc_enable = HI_TRUE;
                break;
            case HDMI_COLORSPACE_YCBCR422:
                en->in_rgb           = HI_TRUE;
                en->csc_enable       = HI_TRUE;
                en->y422_enable      = HI_TRUE;
                en->dwsm_hori_enable = HI_TRUE;
                break;
            case HDMI_COLORSPACE_YCBCR420:
                en->in_rgb           = HI_TRUE;
                en->csc_enable       = HI_TRUE;
                en->dwsm_hori_enable = HI_TRUE;
                en->y420_enable      = HI_TRUE;
                en->dwsm_vert_enable = HI_TRUE;
                break;
            default:
                en->in_rgb  = HI_TRUE;
                en->out_rgb = HI_TRUE;
                break;
        }
    } else {
        hdmi_warn("ctrl un-expected colorspace=%u\n", in);
    }
    return;
}

static hi_void ctrl_videopath_colorspace_set(hdmi_colorspace in_colorspace, hdmi_colorspace out_colorspace)
{
    ctrl_colorspace_en colorspace_en = {0};

    videopath_colorspace_param_get(in_colorspace, out_colorspace, &colorspace_en);
    hdmi_info("Ctrl csc set:\n"
              "in_rgb=%u, out_rgb=%u,csc_enable=%u \n"
              "y422_enable=%u, dwsm_hori_enable=%u \n"
              "y420_enable=%u, dwsm_vert_enable=%u \n",
              colorspace_en.in_rgb, colorspace_en.out_rgb, colorspace_en.csc_enable,
              colorspace_en.y422_enable, colorspace_en.dwsm_hori_enable,
              colorspace_en.y420_enable, colorspace_en.dwsm_vert_enable);

    ctrl_video_color_rgb_set(colorspace_en.in_rgb, colorspace_en.out_rgb);
    ctrl_video_color_ycbcr422_set(colorspace_en.y422_enable);
    ctrl_video_color_dwsm_hori_set(colorspace_en.dwsm_hori_enable);
    ctrl_video_color_ycbcr420_set(colorspace_en.y420_enable);
    ctrl_video_color_dwsm_vert_set(colorspace_en.dwsm_vert_enable);
    ctrl_video_color_csc_set(colorspace_en.csc_enable);

    return;
}

static hi_void ctrl_videopath_quantization_set(hdmi_quantization in_quantization, hdmi_quantization out_quantization)
{
    hi_u32 csc_mode;

    csc_mode = hdmi_multi_csc_ctrl_reg_csc_mode_get();
    if (in_quantization != HDMI_QUANTIZATION_RANGE_LIMITED) {
        hdmi_set_bit(csc_mode, CTRL_QUANTIZAION_IN_BIT);
    } else {
        hdmi_clr_bit(csc_mode, CTRL_QUANTIZAION_IN_BIT);
    }
    if (out_quantization != HDMI_QUANTIZATION_RANGE_LIMITED) {
        hdmi_set_bit(csc_mode, CTRL_QUANTIZAION_OUT_BIT);
    } else {
        hdmi_clr_bit(csc_mode, CTRL_QUANTIZAION_OUT_BIT);
    }
    hdmi_multi_csc_ctrl_reg_csc_mode_set(csc_mode);
    hdmi_multi_csc_ctrl_reg_csc_saturate_en_set(HI_TRUE);

    return;
}

static hi_s32 ctrl_vendor_infoframe_en_set(hi_bool enable)
{
    hdmi_cea_vsif_rpt_en_set(enable);
    hdmi_cea_vsif_en_set(enable);
    return HI_SUCCESS;
}

static hi_void ctrl_vendor_infoframe_data_set(const hi_u8 *if_data)
{
    hdmi_vsif_pkt_header_hb_set(if_data[0], if_data[1], if_data[2]);
    hdmi_vsif_sub_pkt0_l_pb_set(if_data[3], if_data[4], if_data[5], if_data[6]);
    hdmi_vsif_sub_pkt0_h_pb_set(if_data[7], if_data[8], if_data[9]);
    hdmi_vsif_sub_pkt1_l_pb_set(if_data[10], if_data[11], if_data[12], if_data[13]);
    hdmi_vsif_sub_pkt1_h_pb_set(if_data[14], if_data[15], if_data[16]);
    hdmi_vsif_sub_pkt2_l_pb_set(if_data[17], if_data[18], if_data[19], if_data[20]);
    hdmi_vsif_sub_pkt2_h_pb_set(if_data[21], if_data[22], if_data[23]);
    hdmi_vsif_sub_pkt3_l_pb_set(if_data[24], if_data[25], if_data[26], if_data[27]);
    hdmi_vsif_sub_pkt3_h_pb_set(if_data[28], if_data[29], if_data[30]);

    return;
}

static hi_s32 ctrl_avi_infoframe_en_set(hi_bool enable)
{
    hdmi_cea_avi_rpt_en_set(enable);
    hdmi_cea_avi_en_set(enable);
    return HI_SUCCESS;
}

static hi_void ctrl_avi_infoframe_data_set(const hi_u8 *if_data)
{
    hdmi_avi_pkt_header_hb_set(if_data[0], if_data[1], if_data[2]);
    hdmi_avi_sub_pkt0_l_pb_set(if_data[3], if_data[4], if_data[5], if_data[6]);
    hdmi_avi_sub_pkt0_h_pb_set(if_data[7], if_data[8], if_data[9]);
    hdmi_avi_sub_pkt1_l_pb_set(if_data[10], if_data[11], if_data[12], if_data[13]);
    hdmi_avi_sub_pkt1_h_pb_set(if_data[14], if_data[15], if_data[16]);
    hdmi_avi_sub_pkt2_l_pb_set(if_data[17], if_data[18], if_data[19], if_data[20]);
    hdmi_avi_sub_pkt2_h_pb_set(if_data[21], if_data[22], if_data[23]);
    hdmi_avi_sub_pkt3_l_pb_set(if_data[24], if_data[25], if_data[26], if_data[27]);
    hdmi_avi_sub_pkt3_h_pb_set(if_data[28], if_data[29], if_data[30]);

    return;
}

static hi_s32 ctrl_tmds_mode_set(hdmi_tmds_mode tmds_mode)
{
    switch (tmds_mode) {
        case HDMI_TMDS_MODE_DVI:
            hdmi_avmixer_config_hdmi_mode_set(HI_FALSE);
            break;
        case HDMI_TMDS_MODE_HDMI_1_4:
            hdmi_avmixer_config_hdmi_mode_set(HI_TRUE);
            hdmi_enc_hdmi2_on_set(HI_FALSE);
            break;
        case HDMI_TMDS_MODE_HDMI_2_0:
            hdmi_avmixer_config_hdmi_mode_set(HI_TRUE);
            hdmi_enc_hdmi2_on_set(HI_TRUE);
            hdmi_enc_bypass_set(HI_FALSE);
            break;
        default:
            hdmi_warn("un-known tmds mode:%u\n", tmds_mode);
            return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static hi_s32 ctrl_null_packet_set(hi_bool enable)
{
    hdmi_avmixer_config_null_pkt_en_set(enable);
    return HI_SUCCESS;
}

hi_s32 hal_hdmi_ctrl_init(hdmi_device_id hdmi, const hdmi_hal_init *hal_init)
{
    hi_s32 ret = HI_SUCCESS;
    hdmi_ctrl_info *ctrl_info = ctrl_info_get(hdmi);

    hdmi_if_null_return(ctrl_info, HI_FAILURE);
    if (!ctrl_info->init) {
        ret += reg_hdmi_crg_reg_init();
        ret += hdmi_tx_aon_reg_type_init();
        ret += hdmi_tx_ctrl_reg_type_init();
        ret += hdmi_tx_reg_type_init();
        ret += hdmi_tx_videopath_reg_type_init();
        ctrl_info->init = HI_TRUE;
        drv_hdmi_prod_crg_gate_set(HI_TRUE);
    }

    return (ret != HI_SUCCESS) ? HI_FAILURE : HI_SUCCESS;
}

hi_void hal_hdmi_ctrl_deinit(hdmi_device_id hdmi_id)
{
    hdmi_ctrl_info *ctrl_info = ctrl_info_get(hdmi_id);

    hdmi_if_null_return_void(ctrl_info);
    hdmi_if_false_return_void(ctrl_info->init);
    hdmi_tx_aon_reg_type_deinit();
    hdmi_tx_ctrl_reg_type_deinit();
    hdmi_tx_reg_type_deinit();
    hdmi_tx_videopath_reg_type_deinit();
    memset(ctrl_info, 0, sizeof(hdmi_ctrl_info));
    ctrl_info->init = HI_FALSE;

    return;
}

hi_s32 hal_hdmi_ctrl_avmute_set(hdmi_device_id hdmi_id, const hdmi_avmute_cfg *avmute_cfg)
{
    hdmi_ctrl_info *ctrl_info = ctrl_info_get(hdmi_id);

    hdmi_if_null_return(ctrl_info, HI_FAILURE);
    hdmi_if_null_return(avmute_cfg, HI_FAILURE);
    hdmi_if_false_return(ctrl_info->init, HI_FAILURE);
    ctrl_avmute_set(avmute_cfg);

    return HI_SUCCESS;
}

hi_void hal_hdmi_ctrl_csc_set(hdmi_device_id hdmi_id, const hdmi_video_config *video_cfg)
{
    hdmi_if_null_return_void(video_cfg);
    ctrl_videopath_colormetry_set(video_cfg->conv_std, video_cfg->conv_std);
    ctrl_videopath_quantization_set(video_cfg->out_csc_quantization, video_cfg->out_csc_quantization);
    ctrl_videopath_colorspace_set(video_cfg->in_colorspace, video_cfg->out_colorspace);
    return;
}

#ifdef HDMI_PRODUCT_HI3559A
static hi_void dither_logic_change(hdmi_deep_color out_deep_color)
{
    if (out_deep_color == HDMI_DEEP_COLOR_36BIT) {
        /* 36bit must use 2.0 channel */
        drv_hdmi_prod_crg_all_reset_set(HI_TRUE);
        hdmi_tx_channel_reg_vid_bypass_sel_set(HI_TRUE);
    } else {
        if (hdmi_tx_channel_reg_vid_bypass_sel_get() == HI_TRUE) {
            drv_hdmi_prod_crg_all_reset_set(HI_TRUE);
        }
        hdmi_tx_channel_reg_vid_bypass_sel_set(HI_FALSE);
    }

    return;
}
#endif

static hi_void ctrl_video_dither_set(hdmi_video_path *path)
{
    hi_bool enable_gcp = HI_FALSE;
    hi_bool enable_dither = HI_FALSE;
    hdmi_video_dither dither_mode = HDMI_VIDEO_DITHER_DISALBE;

    if (path->out_deep_color != HDMI_DEEP_COLOR_30BIT && path->out_deep_color != HDMI_DEEP_COLOR_36BIT) {
        path->out_deep_color = HDMI_DEEP_COLOR_24BIT;
    }
    /* dither */
    switch (path->out_deep_color) {
        case HDMI_DEEP_COLOR_24BIT:
            enable_gcp = HI_FALSE;
            switch (path->in_deep_color) {
                case HDMI_DEEP_COLOR_30BIT:
                    enable_dither = HI_TRUE;
                    dither_mode = HDMI_VIDEO_DITHER_10_8;
                    break;
                case HDMI_DEEP_COLOR_36BIT:
                    enable_dither = HI_TRUE;
                    dither_mode = HDMI_VIDEO_DITHER_12_8;
                    break;
                default:
                    break;
            }
            break;
        case HDMI_DEEP_COLOR_30BIT:
            enable_gcp = HI_TRUE;
            if (path->in_deep_color == HDMI_DEEP_COLOR_36BIT) {
                enable_dither = HI_TRUE;
                dither_mode = HDMI_VIDEO_DITHER_12_10;
            }
            break;
        case HDMI_DEEP_COLOR_36BIT:
            enable_gcp = HI_TRUE;
            break;
        default:
            break;
    }

    if (path->timming == HDMI_VIDEO_TIMING_1440X480I_60000 || path->timming == HDMI_VIDEO_TIMING_1440X576I_50000 ||
        path->out_colorspace == HDMI_COLORSPACE_YCBCR422) {
        enable_dither = HI_FALSE;
        dither_mode = HDMI_VIDEO_DITHER_DISALBE;
    }

#ifdef HDMI_PRODUCT_HI3559A
    /* hi3559av100 is not support dither (vdp support). */
    dither_mode = HDMI_VIDEO_DITHER_DISALBE;
    /* 59A must reset hardware when change logic channel between HDMI2.0 and HDMI2.1 */
    dither_logic_change(path->out_deep_color);
#endif
    ctrl_videopath_dither_set(enable_dither, dither_mode);
    ctrl_videopath_deep_clr_set(enable_gcp, path->out_deep_color);
}

hi_void hal_hdmi_ctrl_videopath_set(hdmi_device_id hdmi_id, hdmi_video_path *video_path)
{
    hi_bool fifo_auto_rst = HI_TRUE;
    hdmi_ctrl_info *ctrl_info = ctrl_info_get(hdmi_id);

    hdmi_if_null_return_void(video_path);
    hdmi_if_null_return_void(ctrl_info);
    hdmi_if_false_return_void(ctrl_info->init);

    memcpy(&ctrl_info->video_path, video_path, sizeof(hdmi_video_path));
    /* dither */
    ctrl_video_dither_set(video_path);
    ctrl_videopath_polarity_set(&video_path->out_hv_sync_pol);
    ctrl_videopath_colormetry_set(video_path->in_colormetry, video_path->out_colormetry);
    ctrl_videopath_quantization_set(video_path->in_quantization, video_path->out_quantization);
    ctrl_videopath_colorspace_set(video_path->in_colorspace, video_path->out_colorspace);

    if (hdmi_tx_channel_reg_vid_bypass_sel_get() == HI_FALSE) {
        /* 24/30bit use 2.1 channel */
        if (video_path->in_pixel_clk <= HDMI_ONE_BEAT_CLK && video_path->out_colorspace == HDMI_COLORSPACE_YCBCR420) {
            fifo_auto_rst = HI_FALSE;
        }
        /* reg_fifo_auto_rst_en should be set 0 when pixclk <= 600M and enOutColorSpace is YCbCr420 */
        hdmi_tx_pack_fifo_ctrl_reg_fifo_auto_rst_en_set(fifo_auto_rst);
        /* vidpath_dout_clk_sel should be set 1 when pixclk <= 600M and enOutColorSpace is YCbCr420 */
        hdmi_vidpath_dout_clk_sel_set(!fifo_auto_rst);
    }

    return;
}

hi_s32 hal_hdmi_ctrl_tmds_mode_set(hdmi_device_id hdmi_id, hdmi_tmds_mode tmds_mode)
{
    hi_s32 ret;
    hdmi_ctrl_info *ctrl_info = ctrl_info_get(hdmi_id);

    hdmi_if_null_return(ctrl_info, HI_FAILURE);
    hdmi_if_false_return(ctrl_info->init, HI_FAILURE);
    ret = ctrl_tmds_mode_set(tmds_mode);
    return ret;
}

hi_s32 hal_hdmi_ctrl_infoframe_en_set(hdmi_device_id hdmi_id, hdmi_infoframe_id infoframe_id, hi_bool enable)
{
    hi_s32 ret;
    hdmi_ctrl_info *ctrl_info = ctrl_info_get(hdmi_id);

    hdmi_if_null_return(ctrl_info, HI_FAILURE);
    hdmi_if_false_return(ctrl_info->init, HI_FAILURE);

    switch (infoframe_id) {
        case HDMI_INFOFRAME_TYPE_NULL:
            ret = ctrl_null_packet_set(enable);
            break;
        case HDMI_INFOFRAME_TYPE_VENDOR:
            ret = ctrl_vendor_infoframe_en_set(enable);
            break;
        case HDMI_INFOFRAME_TYPE_AVI:
            ret = ctrl_avi_infoframe_en_set(enable);
            break;
        default:
            hdmi_warn("ctrl un-support infoframe type:%u!\n", infoframe_id);
            ret = HI_FAILURE;
            break;
    }

    return ret;
}

hi_s32 hal_hdmi_ctrl_infoframe_data_set(hdmi_device_id hdmi_id, hdmi_infoframe_id infoframe_id, const hi_u8 *if_data)
{
    hi_s32 ret = HI_SUCCESS;
    hdmi_ctrl_info *ctrl_info = ctrl_info_get(hdmi_id);

    hdmi_if_null_return(ctrl_info, HI_FAILURE);
    hdmi_if_null_return(if_data, HI_FAILURE);
    hdmi_if_false_return(ctrl_info->init, HI_FAILURE);

    switch (infoframe_id) {
        case HDMI_INFOFRAME_TYPE_VENDOR:
            ctrl_vendor_infoframe_data_set(if_data);
            break;
        case HDMI_INFOFRAME_TYPE_AVI:
            ctrl_avi_infoframe_data_set(if_data);
            break;
        default:
            hdmi_warn("ctrl un-support infoframe type:%u!\n", infoframe_id);
            ret = HI_FAILURE;
            break;
    }

    return ret;
}

hi_void hal_hdmi_ctrl_data_reset(hdmi_device_id hdmi_id)
{
    hi_u32 h_total_pre = 0;
    hi_u32 h_total_cur;
    hi_u32 start_time = 0;
    hi_u32 threshold;

    switch (hdmi_tx_pack_fifo_ctrl_tmds_pack_mode_get()) {
        case 0:
            threshold = TMDS_TOP_THRESHOLD_1;
            break;
        case 1:
            threshold = TMDS_TOP_THRESHOLD_2;
            break;
        default:
            threshold = TMDS_TOP_THRESHOLD_4;
            break;
    }
    /* disable continuous FCON */
    hdmi_fccontinset0_p_contin_upd_en_set(HI_FALSE);
    /* pwd reset */
    hdmi_tx_pwd_srst_req_set(HI_TRUE);
    /* Must delay 2us. Because internal clock of HDMI is smaller than APB clock. */
    udelay(CTRL_DATA_RESET_DELAY);
    hdmi_tx_pwd_srst_req_set(HI_FALSE);
    /* Must delay 40us. FIFO will calculate the clock stability after the SRS was cleared. */
    /* enable continuous FCON */
    hdmi_fccontinset0_p_contin_upd_en_set(HI_TRUE);
    mdelay(1);

    while (start_time < START_TIME_MAX) {
        /* TMDS PACK FIFO reset */
        hdmi_tx_pack_fifo_ctrl_reg_fifo_manu_rst_set(HI_TRUE);
        udelay(CTRL_DATA_RESET_DELAY);
        hdmi_tx_pack_fifo_ctrl_reg_fifo_manu_rst_set(HI_FALSE);

        /* HDMI_TOP reset */
        hdmi_tx_hdmi_srst_req_set(HI_TRUE);
        udelay(CTRL_DATA_RESET_DELAY);
        hdmi_tx_hdmi_srst_req_set(HI_FALSE);
        mdelay(1);
        h_total_cur = hdmi_htotal_hw_get();
        if ((abs(((hi_s32)h_total_cur - h_total_pre)) < threshold)) {
            break;
        }
        h_total_pre = h_total_cur;
        start_time++;
    }

    return;
}

