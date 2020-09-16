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

#ifndef __DRV_HDMI_COMMON_H_
#define __DRV_HDMI_COMMON_H_

#include "hi_type.h"
#include "drv_hdmi_infoframe.h"

#define HDMI_VER_MAJOR    2
#define HDMI_VER_MINOR    0
#define HDMI_VER_REVISE   0
#define HDMI_VER_DATE     20200513
#define HDMI_VER_TIMES    0

#define MAKE_VER_BIT(x) # x
#define MAKE_MACRO2STR(exp) MAKE_VER_BIT(exp)
#define MAKE_VERSION \
    MAKE_MACRO2STR(HDMI_VER_MAJOR) "."  \
    MAKE_MACRO2STR(HDMI_VER_MINOR) "."  \
    MAKE_MACRO2STR(HDMI_VER_REVISE) "." \
    MAKE_MACRO2STR(HDMI_VER_DATE) "."   \
    MAKE_MACRO2STR(HDMI_VER_TIMES)
/* FRL */
#define MAX_FRL_RATE            6
#define HDMI_FRL_LANE_MAX_NUM   4
#ifdef HDMI_FPGA_SUPPORT
#define FPGA_SUPPORT HI_TRUE
#else
#define FPGA_SUPPORT HI_FALSE
#endif

#define hdmi_id_check_return(hdmi_id, err_no) \
    do {                                      \
        if ((hdmi_id) >= HI_HDMI_ID_BUTT) {   \
            hdmi_err("param err!\n");         \
            return (err_no);                  \
        }                                     \
    } while (0)

#define hdmi_set_bit(var, bit) \
    do {                       \
        (var) |= 1 << (bit);   \
    } while (0)

#define hdmi_clr_bit(var, bit)  \
    do {                        \
        (var) &= ~(1 << (bit)); \
    } while (0)

#define hdmi_if_null_return(p, ret)                 \
    do {                                            \
        if ((p) == HI_NULL) {                       \
            hdmi_warn("%s is null pointer!\n", #p); \
            return (ret);                           \
        }                                           \
    } while (0)

#define hdmi_if_null_return_void(p)                 \
    do {                                            \
        if ((p) == HI_NULL) {                       \
            hdmi_warn("%s is null pointer!\n", #p); \
            return;                                 \
        }                                           \
    } while (0)

#define hdmi_if_false_return(tmp, ret)         \
    do {                                       \
        if ((tmp) != HI_TRUE) {                \
            hdmi_warn("%s is FALSE!\n", #tmp); \
            return (ret);                      \
        }                                      \
    } while (0)

#define hdmi_if_false_return_void(tmp)         \
    do {                                       \
        if ((tmp) != HI_TRUE) {                \
            hdmi_warn("%s is false!\n", #tmp); \
            return;                            \
        }                                      \
    } while (0)

#define hdmi_if_fpga_return(ret)      \
    do {                              \
        if (FPGA_SUPPORT) {           \
            hdmi_warn("FPGA CFG!\n"); \
            return(ret);              \
        }                             \
    } while (0)

#define HDMI_IF_FAILURE_RET_FAILURE(tmp)         \
    do {                                         \
        if ((tmp) != HI_SUCCESS) {               \
            hdmi_warn("%s is failure!\n", #tmp); \
            return HI_FAILURE;                   \
        }                                        \
    } while (0)

#define HDMI_IF_FAILURE_RET_VOID(tmp)            \
    do {                                         \
        if ((tmp) != HI_SUCCESS) {               \
            hdmi_warn("%s is failure!\n", #tmp); \
            return;                              \
        }                                        \
    } while (0)

#define hal_call_void(func, param...)                          \
    do {                                                       \
        if (hdmi_dev != HI_NULL && hdmi_dev->hal != HI_NULL && \
            hdmi_dev->hal->func != HI_NULL) {                  \
            hdmi_dev->hal->func(param);                        \
        } else {                                               \
            hdmi_warn("null pointer! \n");                     \
        }                                                      \
    } while (0)

#define hal_call_ret(ret, func, param...)                      \
    do {                                                       \
        if (hdmi_dev != HI_NULL && hdmi_dev->hal != HI_NULL && \
            hdmi_dev->hal->func != HI_NULL) {                  \
            ret = hdmi_dev->hal->func(param);                  \
        } else {                                               \
            ret = HI_FAILURE;                                  \
        }                                                      \
    } while (0)

typedef enum {
    HDMI_DEVICE_ID0,
    HDMI_DEVICE_ID_BUTT
} hdmi_device_id;

typedef enum {
    HDMI_THREAD_STATE_RUN,
    HDMI_THREAD_STATE_STOP
} hdmi_thread_state;

typedef enum {
    HDMI_EVENT_HOTPLUG = 0x10,
    HDMI_EVENT_HOTUNPLUG,
    HDMI_EVENT_EDID_FAIL,
    HDMI_EVENT_HDCP_FAIL,
    HDMI_EVENT_HDCP_SUCCESS,
    HDMI_EVENT_RSEN_CONNECT,
    HDMI_EVENT_RSEN_DISCONNECT,
    HDMI_EVENT_HDCP_USERSETTING,
    HDMI_EVENT_HDCP_OFF,
    HDMI_EVENT_SCRAMBLE_FAIL,
    HDMI_EVENT_SCRAMBLE_SUCCESS,
    HDMI_EVENT_ZERO_DRMIF_TIMEOUT,
    HDMI_EVENT_SWITCH_TO_HDRMODE_TIMEOUT,
    HDMI_EVENT_BUTT
} hdmi_event;

typedef enum {
    HDMI_INT_TYPE_NONE,
    HDMI_INT_TYPE_HPD_RSEN,
    HDMI_INT_TYPE_HDCP,
    HDMI_INT_TYPE_HDCP2X,
    HDMI_INT_TYPE_CEC,
} hdmi_int_type;

typedef hi_s32 (*hdmi_callback)(hi_void*, hdmi_event);

typedef struct {
    hi_void       *event_data;
    hdmi_callback event_callback;
    hi_u32        hdmi_dev_id;
    hi_char       *base_addr;
    hi_char       *phy_addr;
} hdmi_hal_init;

#define HDMI_ARRAY_SIZE(a)        ((sizeof(a)) / (sizeof(a[0])))
#define FMT_PIX_CLK_13400          13400
#define FMT_PIX_CLK_74250          74250
#define FMT_PIX_CLK_165000         165000
#define FMT_PIX_CLK_190000         190000
#define FMT_PIX_CLK_297000         297000
#define FMT_PIX_CLK_340000         340000
#define ZERO_DRMIF_SEND_TIME       2000
#define HDRMODE_CHANGE_TIME        500
#define HDMI_EDID_BLOCK_SIZE       128
#define HDMI_EDID_TOTAL_BLOCKS     4
#define HDMI_EDID_SIZE            ((HDMI_EDID_BLOCK_SIZE) * (HDMI_EDID_TOTAL_BLOCKS))
#define PHY_ADDR_LEN               4
#define AKSV_LEN                   5
#define BKSV_LEN                   5
#define HDMI_INFO_FRAME_MAX_SIZE   31
#define CEAVIDEO_CODES_MAX         44
#define VESAVIDEO_CODES_MAX        31
#define CEA861_FVIDEO_CODES_MAX_4K 4
#define HDMI_REG_SIZE              4

typedef struct {
    hi_u8  edid_valid;
    hi_u32 edid_len;
    hi_u8  edid[HDMI_EDID_SIZE];
} hdmi_edid_rawdata;

typedef struct {
    hi_u8 *input_encrypted_key_addr;
    hi_u32 key_length;
} hdmi_load_key;

typedef struct {
    hi_u32 input_encrypted_key_addr;
    hi_u32 key_length;
} hdmi_compat_load_key;

typedef enum {
    HDMI_HDCP_VERSION_NONE,
    HDMI_HDCP_VERSION_1_4,
    HDMI_HDCP_VERSION_2_2,
    HDMI_HDCP_VERSION_BUTT
} hdmi_hdcp_version;

typedef struct {
    hi_bool connected;
    hi_bool sink_power_on;
    hi_bool authed;
    hi_u8   bksv[BKSV_LEN];
    hdmi_hdcp_version hdcp_version;
} hdmi_status;

typedef enum {
    HDMI_DEEP_COLOR_24BIT,
    HDMI_DEEP_COLOR_30BIT,
    HDMI_DEEP_COLOR_36BIT,
    HDMI_DEEP_COLOR_48BIT,
    HDMI_DEEP_COLOR_OFF = 0xff,
    HDMI_DEEP_COLOR_BUTT
} hdmi_deep_color;

typedef enum {
    HDMI_VIDEO_BITDEPTH_8,
    HDMI_VIDEO_BITDEPTH_10,
    HDMI_VIDEO_BITDEPTH_12,
    HDMI_VIDEO_BITDEPTH_16,
    HDMI_VIDEO_BITDEPTH_OFF,
    HDMI_VIDEO_BITDEPTH_BUTT
} hdmi_video_bit_depth;

typedef enum {
    HDMI_HV_SYNC_POL_HPVP,
    HDMI_HV_SYNC_POL_HPVN,
    HDMI_HV_SYNC_POL_HNVP,
    HDMI_HV_SYNC_POL_HNVN,
    HDMI_HV_SYNC_POL_BUTT
} hdmi_hvsync_polarity;

typedef enum {
    HDMI_PICTURE_NON_UNIFORM__SCALING,
    HDMI_PICTURE_SCALING_H,
    HDMI_PICTURE_SCALING_V,
    HDMI_PICTURE_SCALING_HV
} hdmi_picture_scaling;

typedef struct {
    hi_u32                      clk_fs;             /* VDP setting(in) */
    hi_u32                      hdmi_adapt_pix_clk; /* HDMI adapt setting(out) */
    hi_u32                      pixel_repeat;
    hi_bool                     v_sync_pol;
    hi_bool                     h_sync_pol;
    hi_bool                     de_pol;
    hdmi_video_timing           video_timing;
    hdmi_3d_mode                stereo_mode;
    hdmi_colorspace             in_colorspace;
    hdmi_colorimetry            colorimetry;
    hdmi_extended_colorimetry   extended_colorimetry;
    hdmi_quantization           rgb_quantization;
    hdmi_ycc_quantization_range ycc_quantization;
    hdmi_picture_aspect         picture_aspect;
    hdmi_active_aspect          active_aspect;
    hdmi_picture_scaling        picture_scaling;
    hdmi_video_bit_depth        in_bit_depth;
    hi_u32                      disp_fmt;
} hdmi_vo_attr;

typedef enum {
    HDMI_TMDS_MODE_NONE,
    HDMI_TMDS_MODE_DVI,
    HDMI_TMDS_MODE_HDMI_1_4,
    HDMI_TMDS_MODE_HDMI_2_0,
    HDMI_TMDS_MODE_AUTO,
    HDMI_TMDS_MODE_HDMI_2_1,
    HDMI_TMDS_MODE_BUTT
} hdmi_tmds_mode;

typedef enum {
    HDMI_DEFAULT_ACTION_NULL,
    HDMI_DEFAULT_ACTION_HDMI,
    HDMI_DEFAULT_ACTION_DVI,
    HDMI_DEFAULT_ACTION_BUTT
} hdmi_default_action;

typedef enum {
    HDMI_VIDEO_DITHER_12_10,
    HDMI_VIDEO_DITHER_12_8,
    HDMI_VIDEO_DITHER_10_8,
    HDMI_VIDEO_DITHER_DISALBE
} hdmi_video_dither;

typedef struct {
    hi_bool             enable_hdmi;
    hi_bool             enable_video;
    hi_bool             enable_audio;
    hdmi_colorspace     out_colorspace;
    hdmi_quantization   out_csc_quantization;
    hdmi_deep_color     deep_color_mode;
    hi_bool             bxv_ycc_mode;
    hi_bool             enable_avi_infoframe;
    hi_bool             enable_spd_infoframe;
    hi_bool             enable_mpeg_infoframe;
    hi_bool             enable_aud_infoframe;
    hi_u32              debug_flag;
    hi_bool             hdcp_enable;
    hdmi_default_action hdmi_action;
    hi_bool             enable_clr_space_adapt;
    hi_bool             enable_deep_clr_adapt;
    hi_bool             auth_mode;
    hi_bool             enable_drm_infoframe;
} hdmi_app_attr;

typedef enum {
    HDMI_HDR_MODE_DISABLE,           /* HDR & Dolby mode disable */
    HDMI_HDR_MODE_DOLBY_NORMAL,      /* Dolby normal(YCbCr422-12bit) mode enable */
    HDMI_HDR_MODE_DOLBY_TUNNELING,   /* Dolby tunneling(RGB-8bit) mode enable */
    HDMI_HDR_MODE_CEA_861_3,         /* HDR standar mode enable(according to <CEA-861-3.2015>) */
    HDMI_HDR_MODE_CEA_861_3_AUTHEN,  /* HDR authen mode */
    HDMI_HDR_MODE_BUTT
} hdmi_hdr_mode;

typedef enum {
    HDMI_HDR_USERMODE_SDR,
    HDMI_HDR_USERMODE_HDR10,
    HDMI_HDR_USERMODE_DOLBY,
    HDMI_HDR_USERMODE_BUTT
} hdmi_hdr_usermode;

typedef struct {
    hdmi_hdr_mode            hdr_mode;      /* HDR mode */
    hdmi_hdr_usermode        user_hdr_mode; /* User HDR mode */
    hdmi_eotf_type           eotf_type;     /* EOTF type.  When enHdrMode==HI_UNF_HDMI_HDR_MODE_CEA_861_3 valid */
    hdmi_static_meta_type_id metadata_id;   /* Metadata Descriptor type(ID).  When enHdrMode==HI_UNF_HDMI_HDR_MODE_CEA_861_3 valid */
    hdmi_meta_descriptor_un  descriptor;    /* Static Metadata Descriptor Type.  When enHdrMode==HI_UNF_HDMI_HDR_MODE_CEA_861_3 valid */
} hdmi_hdr_attr;

typedef struct {
    hdmi_vo_attr  vo_attr;
    hdmi_app_attr app_attr;
} hdmi_attr;

typedef enum {
    HDMI_TRANSITION_NONE     = 0x0,
    HDMI_TRANSITION_BOOT_MCE = 0x1,
    HDMI_TRANSITION_MCE_APP  = 0x2,
    HDMI_TRANSITION_BOOT_APP = 0x4
} hdmi_transition_state;

typedef enum {
    HDMI_RUN_STATE_NONE   = 0x00,
    HDMI_RUN_STATE_INIT   = 0x01,
    HDMI_RUN_STATE_OPEN   = 0x02,
    HDMI_RUN_STATE_START  = 0x04,
    HDMI_RUN_STATE_STOP   = 0x08,
    HDMI_RUN_STATE_CLOSE  = 0x10,
    HDMI_RUN_STATE_DEINIT = 0x20
} hdmi_run_state;

typedef enum {
    HDMI_TX_SUPPORT_HDMI1_4    = 0x1,
    HDMI_TX_SUPPORT_HDMI2_0    = 0x2,
    HDMI_TX_SUPPORT_HDCP1_4    = 0x4,
    HDMI_TX_SUPPORT_HDCP2_2    = 0x8,
    HDMI_TX_SUPPORT_YUV420     = 0x10,
    HDMI_TX_SUPPORT_YUV420_422 = 0x20,
    HDMI_TX_SUPPORT_YUV422_444 = 0x40,
    HDMI_TX_SUPPORT_YUV444_422 = 0x80,
    HDMI_TX_SUPPORT_YUV422_420 = 0x100,
    HDMI_TX_SUPPORT_YUV2RGB    = 0x200,
    HDMI_TX_SUPPORT_RGB2YUV    = 0x400,
    HDMI_TX_SUPPORT_SCRAMBLE   = 0x800,
} hdmi_tx_capability_type;

typedef struct {
    hi_bool tx_hdmi_14;
    hi_bool tx_hdmi_20;
    hi_bool tx_hdmi_21;
    hi_bool tx_hdcp_14;
    hi_bool tx_hdcp_22;
    hi_bool tx_rgb444;
    hi_bool tx_ycbcr444;
    hi_bool tx_ycbcr422;
    hi_bool tx_ycbcr420;
    hi_bool tx_deep_clr10_bit;
    hi_bool tx_deep_clr12_bit;
    hi_bool tx_deep_clr16_bit;
    hi_bool tx_rgb_ycbcr444;
    hi_bool tx_ycbcr444_422;
    hi_bool tx_ycbcr422_420;
    hi_bool tx_ycbcr420_422;
    hi_bool tx_ycbcr422_444;
    hi_bool tx_ycbcr444_rgb;
    hi_bool tx_scdc;
    hi_u32  tx_max_tmds_clk; /* in MHz */
} hdmi_tx_capability;

typedef enum {
    HDMI_CONV_STD_BT_709,
    HDMI_CONV_STD_BT_601,
    HDMI_CONV_STD_BT_2020_NON_CONST_LUMINOUS,
    HDMI_CONV_STD_BT_2020_CONST_LUMINOUS,
    HDMI_CONV_STD_BUTT
} hdmi_conversion_std;

typedef enum {
    HDMI_TRACE_LEN_0, /* 1.0 inch */
    HDMI_TRACE_LEN_1, /* 1.5 inch */
    HDMI_TRACE_LEN_2, /* 2.0 inch */
    HDMI_TRACE_LEN_3, /* 2.5 inch */
    HDMI_TRACE_LEN_4, /* 3.0 inch */
    HDMI_TRACE_LEN_5, /* 3.5 inch */
    HDMI_TRACE_LEN_6, /* 4.0 inch */
    HDMI_TRACE_LEN_7, /* 4.5 inch */
    HDMI_TRACE_LEN_8, /* 5.0 inch */
    HDMI_TRACE_BUTT
} hdmi_trace_len;

typedef struct {
    hdmi_video_timing    timming;
    hi_u32               pixel_clk;
    hi_u32               tmds_clk;
    hi_bool              v_sync_pol;
    hi_bool              h_sync_pol;
    hi_bool              de_pol;
    hdmi_conversion_std  conv_std;
    hdmi_quantization    quantization;
    hdmi_colorspace      in_colorspace;
    hdmi_colorspace      out_colorspace;
    hdmi_deep_color      deep_color;
    hdmi_video_bit_depth in_bit_depth;
    hdmi_quantization    out_csc_quantization;
    hi_bool              emi_enable;
    hdmi_trace_len       trace_len;
} hdmi_video_config;

typedef struct {
    hi_u8 data_swing;      /* data-swing */
    hi_u8 clk_swing;       /* CLK-swing */
    hi_u8 src_termination; /* source termination */
    hi_u8 tx_vnb_value;    /* Tx driver vnb value setting */
    hi_u8 adjust_clk;      /* Fine adjust clock source termination */
    hi_u8 tx_reg_zone;     /* tx_reg_zone */
} hdmi_phy_config;

typedef struct {
    hi_bool              phy_oe;
    hi_bool              phy_power_on;
    hdmi_video_bit_depth deep_color;
    hdmi_phy_config      phy_config;
} hdmi_phy_status;

typedef struct {
    hi_bool              video_mute;
    hi_bool              ycbcr2_rgb;
    hi_bool              rgb2_ycbcr;
    hi_bool              ycbcr444_422;
    hi_bool              ycbcr422_420;
    hi_bool              ycbcr420_422;
    hi_bool              ycbcr422_444;
    hi_bool              in420_ydemux;
    hi_bool              out420_ydemux;
    hdmi_video_dither    dither;
    hi_bool              v_sync_pol;
    hi_bool              h_sync_pol;
    hi_bool              c_sync_pol;
    hi_bool              de_pol;
    hi_bool              swap_hs_cs;
    hdmi_colorspace      in_colorspace;
    hdmi_colorspace      out_colorspace;
    hdmi_video_bit_depth out_bit_depth;
    hdmi_hvsync_polarity hv_sync_pol;
    hdmi_quantization    out_csc_quantization;
#if defined (HDMI_SUPPORT_LOGIC_HISIV100)
    /* detect timming */
    hi_bool sync_sw_enable;
    hi_bool v_sync_polarity; /* when bSyncSwEnable==0,indicates hw;or ,indicates sw */
    hi_bool h_sync_polarity; /* when bSyncSwEnable==0,indicates hw;or ,indicates sw */
    hi_bool progressive;
    hi_u32  h_sync_total;
    hi_u32  h_active_cnt;
    hi_u32  v_sync_total;
    hi_u32  v_active_cnt;
#endif
} hdmi_video_status;

typedef struct {
    hi_bool hdcp14_support;
    hi_bool hdcp22_support;
} hdmi_hdcp_capability;

typedef struct {
    hi_bool hot_plug;
    hi_bool rsen;
    hi_bool av_mute;
    hdmi_tmds_mode tmds_mode;
} hdmi_common_status;

typedef struct {
    hi_bool source_scramble_on;
    hi_bool sink_scramble_on;
    hi_u8   tmds_bit_clk_ratio;
#if defined (HDMI_SUPPORT_LOGIC_HISIV100)
    hi_bool sink_read_quest;
    hi_u32  scramble_timeout;  /* in unit of ms.for [0,200],force to default 200;or,set the value cfg(>200). */
    /* in unit of ms,range[20,200).for [0,20] or >=200,force to default 20;or,set the value cfg[20,200). */
    hi_u32  scramble_interval;
#endif
} hdmi_scdc_status;

typedef struct {
    hi_bool avi_enable;
    hi_bool audio_enable;
    hi_bool vsif_enable;
    hi_bool spd_enable;
    hi_bool mpeg_enable;
    hi_bool gbd_enable;
    hi_u8   avi[HDMI_INFO_FRAME_MAX_SIZE];
    hi_u8   audio[HDMI_INFO_FRAME_MAX_SIZE];
    hi_u8   vsif[HDMI_INFO_FRAME_MAX_SIZE];
    hi_u8   spd[HDMI_INFO_FRAME_MAX_SIZE];
    hi_u8   mpeg[HDMI_INFO_FRAME_MAX_SIZE];
    hi_u8   gdb[HDMI_INFO_FRAME_MAX_SIZE];
    hi_bool drm_enable;
    hi_u8   drm[HDMI_INFO_FRAME_MAX_SIZE];
} hdmi_infoframe_status;

typedef struct {
    hi_bool hdcp22_enable;
    hi_bool hdcp14_enable;
    hi_bool repeater_on;
    hi_u8   bksvs[BKSV_LEN];
    hi_u8   aksvs[AKSV_LEN];
    hi_u8   hdcp_status;
} hdmi_hdcp_status;

typedef enum {
    FRL_WORK_MODE_NONE,
    FRL_WORK_MODE_3L3G,
    FRL_WORK_MODE_3L6G,
    FRL_WORK_MODE_4L6G,
    FRL_WORK_MODE_4L8G,
    FRL_WORK_MODE_4L10G,
    FRL_WORK_MODE_4L12G,
    FRL_WORK_MODE_BUTT
} frl_work_mode;

typedef struct {
    hi_bool       frl_start;
    hi_bool       work_en;
    frl_work_mode work_mode;
} hdmi_frl_status;

typedef enum {
    FRL_TXFFE_MODE_0,
    FRL_TXFFE_MODE_1,
    FRL_TXFFE_MODE_2,
    FRL_TXFFE_MODE_3,
    FRL_TXFFE_MODE_BUTT
} frl_txffe_mode;

typedef struct {
    hdmi_common_status    common_status;
    hdmi_phy_status       phy_status;
    hdmi_video_status     video_status;
    hdmi_infoframe_status infoframe_status;
    hdmi_hdcp_status      hdcp_status;
} hdmi_hardware_status;

typedef struct {
    hi_u32  max_tmds_character_rate;
    hi_bool scdc_present;
    hi_bool rr_capable;
    hi_bool lte340_mcsc_scramble;
    hi_bool b3d_osd_disparity;
    hi_bool dual_view;
    hi_bool independent_view;
    hi_bool dc30bit420;
    hi_bool dc36bit420;
    hi_bool dc48bit420;
    hi_bool scdc_enable;
} hdmi_scdc_config;

typedef struct {
    hi_u32  mute_delay;       /* <delay for avmute */
    hi_u32  fmt_delay;        /* <delay for setformat */
    hi_bool force_fmt_delay;  /* <force setformat delay mode */
    hi_bool force_mute_delay; /* <force avmute delay mode */
} hdmi_delay;

typedef enum {
    HDMI_VIDEO_UNKNOWN,
    HDMI_VIDEO_PROGRESSIVE,
    HDMI_VIDEO_INTERLACE,
    HDMI_VIDEO_BUTT
} hdmi_video_p_i_type;

typedef struct {
    hdmi_video_code     video_code;
    hi_u32              pixclk;
    hi_u32              rate;
    hi_u32              hactive;
    hi_u32              vactive;
    hi_u32              hblank;
    hi_u32              vblank;
    hi_u32              hfront;
    hi_u32              hsync;
    hi_u32              hback;
    hi_u32              vfront;
    hi_u32              vsync;
    hi_u32              vback;
    hdmi_picture_aspect aspect_ratio;
    hdmi_video_timing   timing;
    hdmi_video_p_i_type pi_type;
    hi_char             *fmt_str;
} hdmi_video_def;

typedef struct {
    hdmi_vsif_vic       hdmi_vic;
    hdmi_video_code     equivalent_video_code;  /* real vic */
    hi_u32              pixclk;
    hi_u32              rate;
    hi_u32              hactive;
    hi_u32              vactive;
    hdmi_picture_aspect aspect_ratio;
    hdmi_video_timing   timing;
    hdmi_video_p_i_type pi_type;
    hi_char             *fmt_str;
} hdmi_video_4k_def;

typedef struct {
    hi_u32 attach_in_time;
    hi_u32 attach_out_time;
    hi_u32 de_attach_in_time;
    hi_u32 de_attach_out_time;
    hi_u32 preformat_in_time;
    hi_u32 preformat_out_time;
    hi_u32 setformat_in_time;
    hi_u32 setformat_out_time;
    hi_u32 suspend_in_time;
    hi_u32 suspend_out_time;
    hi_u32 resume_in_time;
    hi_u32 resume_out_time;
} hdmi_intf_status;

typedef struct {
    hi_bool blac_enable;
    hi_u8   in_colorspace;
    hi_u8   in_bit_depth;
    hi_u8   in_quantization;
} hdmi_black_frame_info;

typedef struct {
    hi_u32 stop_delay;
    hdmi_intf_status intf_status;
} hdmi_debug;

typedef enum {
    HDMI_TIMER_ZERO_DRMIF,
    HDMI_TIMER_SDR_TO_HDR10,
    HDMI_TIMER_TYPE_BUTT
} hdmi_timer_type;

typedef struct {
    hdmi_timer_type timer_type;
    hi_bool timer_start;
    hi_u32 time;
} hdmi_timer_config;

typedef enum {
    HDMI_HDR_DEBUG_MODE_NONE,   /* HDR mode change, SDR->HDR10 don't change anything */
    HDMI_HDR_DEBUG_MODE_OE,     /* HDR mode change, SDR->HDR10 output disable and enable */
    HDMI_HDR_DEBUG_MODE_AVMUTE, /* HDR mode change, SDR->HDR10 send avmute */
    HDMI_HDR_DEBUG_MODE_BUTT
} hdmi_hdr_debug_mod;

typedef struct {
    hdmi_hdr_debug_mod hdr_debug_mode;     /* HDR debug mode. To solve the problem of some TV can not switch smoothly from non-HDR10 to HDR10. */
    hdmi_timer_config  zero_drm_if_timer;  /* should send Zero DRM Infoframe when the HDR mode from HDR10 to non-HDR10. */
    hdmi_timer_config  hdr_mode_chn_timer; /* HDR debug timer. */
} hdmi_hdr_info;

typedef struct {
    hi_u32 i_de_main_clk;
    hi_u32 i_de_main_data;
    hi_u32 i_main_clk;
    hi_u32 i_main_data;
    hi_u32 ft_cap_clk;
    hi_u32 ft_cap_data;
} hdmi_hw_param;

typedef struct {
    hdmi_hw_param hw_param[4];
} hdmi_hw_spec;

typedef struct {
    hi_bool mute_pkg_en;
    hi_bool mute_set;
    hi_bool mute_clr;
    hi_bool mute_rpt_en;
    hi_u32  rpt_cnt;
} hdmi_avmute_cfg;

/* FRL */
typedef enum {
    HDMI_FRL_SCDC_TYPE_SINK_VERSION,
    HDMI_FRL_SCDC_TYPE_SOURCE_VERSION,
    HDMI_FRL_SCDC_TYPE_UPDATE_FLAGS,
    HDMI_FRL_SCDC_TYPE_STATUS_FLAGS,
    HDMI_FRL_SCDC_TYPE_CONFIG,
    HDMI_FRL_SCDC_TYPE_TXFFE_REQ,
    HDMI_FRL_FLAGS_TYPE_BUTT
} hdmi_frl_scdc_type;

typedef enum {
    HDMI_FRL_TRAIN_PATTERN_NONE,
    HDMI_FRL_TRAIN_PATTERN_LP1,
    HDMI_FRL_TRAIN_PATTERN_LP2,
    HDMI_FRL_TRAIN_PATTERN_LP3,
    HDMI_FRL_TRAIN_PATTERN_LP4,
    HDMI_FRL_TRAIN_PATTERN_LP5,
    HDMI_FRL_TRAIN_PATTERN_LP6,
    HDMI_FRL_TRAIN_PATTERN_LP7,
    HDMI_FRL_TRAIN_PATTERN_LP8,
    HDMI_FRL_TRAIN_PATTERN_RESERVED,
    HDMI_FRL_TRAIN_PATTERN_0E = 0xE,
    HDMI_FRL_TRAIN_PATTERN_0F = 0xF,
    HDMI_FRL_TRAIN_PATTERN_BUTT
} hdmi_frl_train_pattern;

typedef enum {
    HDMI_FRL_TRAIN_NONE,
    HDMI_FRL_TRAIN_FAIL,
    HDMI_FRL_TRAIN_SUCCESS,
    HDMI_FRL_TRAIN_BUSY,
    HDMI_FRL_TRAIN_BUTT
} hdmi_frl_train_status;

typedef enum {
    HDMI_FRL_TRAIN_FAIL_NORMAL,
    HDMI_FRL_TRAIN_FAIL_FLTTIMEOUT,
    HDMI_FRL_TRAIN_FAIL_FLTSTEPTIMEOUT,
    HDMI_FRL_TRAIN_FAIL_RATECHANGE,
    HDMI_FRL_TRAIN_FAIL_FFECHANGE,
    HDMI_FRL_TRAIN_FAIL_BUTT
} hdmi_frl_train_fail;

typedef enum {
    HDMI_FRL_TRAIN_SEL_SW,
    HDMI_FRL_TRAIN_SEL_HW,
    HDMI_FRL_TRAIN_SEL_BUTT
} hdmi_frl_train_sel;

typedef struct {
    hdmi_frl_train_status  frl_train_status;
    hdmi_frl_train_pattern train_pattern[HDMI_FRL_LANE_MAX_NUM];
    hdmi_frl_train_fail    train_fail_res;
} hdmi_frl_train_status_s;

typedef struct {
    hi_u32 flt_wait_config_ms;
    hi_u32 flt_wait_result_ms;
    hi_u32 flt_timeout;
    hi_u32 flt_step_timeout;
    hi_u32 flt_update_timeout;
} hdmi_frl_timer_info;

typedef struct {
    hi_bool             frl_no_timeout;
    hi_u8               frl_rate;
    hi_u8               ffe_levels;
    hdmi_frl_timer_info timer;
    hdmi_frl_train_sel  train_sel;
} hdmi_frl_train_config;

typedef enum {
    SCDC_CMD_SET_SOURCE_VER,
    SCDC_CMD_GET_SOURCE_VER,
    SCDC_CMD_GET_SINK_VER,
    SCDC_CMD_SET_FLT_UPDATE,
    SCDC_CMD_GET_FLT_UPDATE,
    SCDC_CMD_SET_FLT_UPDATE_TRIM,
    SCDC_CMD_GET_FLT_UPDATE_TRIM,
    SCDC_CMD_SET_FLT_START,
    SCDC_CMD_GET_FLT_START,
    SCDC_CMD_SET_CONFIG1,
    SCDC_CMD_GET_CONFIG1,
    SCDC_CMD_GET_TEST_CONFIG,
    SCDC_CMD_GET_FLT_READY,
    SCDC_CMD_GET_LTP_REQ,
    SCDC_CMD_BUTT
} scdc_cmd;

typedef struct {
    hi_u8 frl_rate;
    hi_u8 ffe_levels;
} scdc_config;

typedef struct {
    hi_bool pre_shoot_only;
    hi_bool de_emphasis_only;
    hi_bool no_ffe;
    hi_bool flt_no_timeout;
    hi_bool dsc_frl_max;
    hi_bool frl_max;
} scdc_test_config;

typedef struct {
    hi_u8 ln0_ltp;
    hi_u8 ln1_ltp;
    hi_u8 ln2_ltp;
    hi_u8 ln3_ltp;
} scdc_ltp_req;

typedef enum {
    HDMI_PHY_MODE_CFG_TMDS,
    HDMI_PHY_MODE_CFG_FRL,
    HDMI_PHY_MODE_CFG_TXFFE
} hdmi_phy_mode_cfg;

typedef struct {
    hi_bool emi_en;
    hdmi_trace_len trace_len;
} hdmi_mode_param;

typedef struct {
    hdmi_device_id hdmi_id;
    hdmi_trace_len trace_len;
} drv_hdmi_mod_param;

typedef struct {
    hdmi_device_id hdmi_id;
    hdmi_hw_spec   hw_spec;
} drv_hdmi_hw_spec;

typedef struct {
    hi_u32            pixel_clk;
    hi_u32            tmds_clk;   /* TMDS colck,in kHz */
    hi_bool           emi_enable;
    hdmi_deep_color   deep_color; /* Deep color(color depth)  */
    hdmi_phy_mode_cfg mode_cfg;   /* TMDS/FRL/TxFFE */
    hdmi_trace_len    trace_len;
} hdmi_phy_cfg;

extern hdmi_video_def g_cea_video_codes_des[CEAVIDEO_CODES_MAX];

extern hdmi_video_4k_def g_h14b_hdmi_video_codes_4k[CEA861_FVIDEO_CODES_MAX_4K];

hdmi_video_code drv_hdmi_vic_search(hdmi_video_timing timming, hdmi_picture_aspect aspect, hi_bool _3d_enable);

hi_void hdmi_reg_write(volatile hi_void *reg_addr, hi_u32 value);

hi_u32 hdmi_reg_read(volatile hi_void *reg_addr);

hi_void drv_hdmi_milli_delay(hi_u32 m_sec);

hi_u32 drv_hdmi_vic_to_index(hi_u32 vic);

#endif /* __DRV_HDMI_COMMON_H_ */

