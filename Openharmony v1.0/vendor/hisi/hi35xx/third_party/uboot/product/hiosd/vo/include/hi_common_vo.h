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

#ifndef __HI_COMMON_VO_H__
#define __HI_COMMON_VO_H__

#include "hi_type.h"
#include "hi_errno.h"
#include "hi_common_video.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

/* Vo define error code */
#define HI_ERR_VO_INVALID_DEV_ID      HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_INVALID_DEV_ID)
#define HI_ERR_VO_INVALID_CHN_ID      HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_INVALID_CHN_ID)
#define HI_ERR_VO_INVALID_LAYER_ID    HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_INVALID_LAYER_ID)
#define HI_ERR_VO_ILLEGAL_PARAM       HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_ILLEGAL_PARAM)
#define HI_ERR_VO_NULL_PTR            HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_NULL_PTR)
#define HI_ERR_VO_NOT_CFG             HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_CFG)
#define HI_ERR_VO_NOT_SUPPORT         HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_SUPPORT)
#define HI_ERR_VO_NOT_PERM            HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_PERM)
#define HI_ERR_VO_NOT_ENABLE          HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_ENABLE)
#define HI_ERR_VO_NOT_DISABLE         HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_DISABLE)
#define HI_ERR_VO_NO_MEM              HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_NO_MEM)
#define HI_ERR_VO_NOT_READY           HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_READY)
#define HI_ERR_VO_TIMEOUT             HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_TIMEOUT)
#define HI_ERR_VO_BUSY                HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_BUSY)
#define HI_ERR_VO_NOT_BINDED          HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_BINDED)
#define HI_ERR_VO_BINDED              HI_DEFINE_ERR(HI_ID_VO, HI_ERR_LEVEL_ERROR, HI_ERR_BINDED)

/* VO video output interface type */
#define HI_VO_INTF_CVBS       (0x01L << 0)
#define HI_VO_INTF_VGA        (0x01L << 1)
#define HI_VO_INTF_BT656      (0x01L << 2)
#define HI_VO_INTF_BT1120     (0x01L << 3)
#define HI_VO_INTF_HDMI       (0x01L << 4)
#define HI_VO_INTF_RGB_6BIT   (0x01L << 5)
#define HI_VO_INTF_RGB_8BIT   (0x01L << 6)
#define HI_VO_INTF_RGB_16BIT  (0x01L << 7)
#define HI_VO_INTF_RGB_18BIT  (0x01L << 8)
#define HI_VO_INTF_RGB_24BIT  (0x01L << 9)
#define HI_VO_INTF_MIPI       (0x01L << 10)
#define HI_VO_INTF_MIPI_SLAVE (0x01L << 11)

typedef hi_u32 hi_vo_intf_type;

typedef enum {
    HI_VO_OUT_PAL = 0, /* PAL standard */
    HI_VO_OUT_NTSC = 1, /* NTSC standard */
    HI_VO_OUT_960H_PAL = 2, /* ITU-R BT.1302 960 x 576 at 50 Hz (interlaced) */
    HI_VO_OUT_960H_NTSC = 3, /* ITU-R BT.1302 960 x 480 at 60 Hz (interlaced) */

    HI_VO_OUT_640x480_60 = 4, /* VESA 640 x 480 at 60 Hz (non-interlaced) CVT */
    HI_VO_OUT_480P60 = 5, /* 720  x  480 at 60 Hz. */
    HI_VO_OUT_576P50 = 6, /* 720  x  576 at 50 Hz. */
    HI_VO_OUT_800x600_60 = 7, /* VESA 800 x 600 at 60 Hz (non-interlaced) */
    HI_VO_OUT_1024x768_60 = 8, /* VESA 1024 x 768 at 60 Hz (non-interlaced) */
    HI_VO_OUT_720P50 = 9, /* 1280 x  720 at 50 Hz. */
    HI_VO_OUT_720P60 = 10, /* 1280 x  720 at 60 Hz. */
    HI_VO_OUT_1280x800_60 = 11, /* 1280*800@60Hz VGA@60Hz */
    HI_VO_OUT_1280x1024_60 = 12, /* VESA 1280 x 1024 at 60 Hz (non-interlaced) */
    HI_VO_OUT_1366x768_60 = 13, /* VESA 1366 x 768 at 60 Hz (non-interlaced) */
    HI_VO_OUT_1400x1050_60 = 14, /* VESA 1400 x 1050 at 60 Hz (non-interlaced) CVT */
    HI_VO_OUT_1440x900_60 = 15, /* VESA 1440 x 900 at 60 Hz (non-interlaced) CVT Compliant */
    HI_VO_OUT_1600x1200_60 = 16, /* VESA 1600 x 1200 at 60 Hz (non-interlaced) */
    HI_VO_OUT_1680x1050_60 = 17, /* VESA 1680 x 1050 at 60 Hz (non-interlaced) */

    HI_VO_OUT_1080P24 = 18, /* 1920 x 1080 at 24 Hz. */
    HI_VO_OUT_1080P25 = 19, /* 1920 x 1080 at 25 Hz. */
    HI_VO_OUT_1080P30 = 20, /* 1920 x 1080 at 30 Hz. */
    HI_VO_OUT_1080I50 = 21, /* 1920 x 1080 at 50 Hz, interlaced. */
    HI_VO_OUT_1080I60 = 22, /* 1920 x 1080 at 60 Hz, interlaced. */
    HI_VO_OUT_1080P50 = 23, /* 1920 x 1080 at 50 Hz. */
    HI_VO_OUT_1080P60 = 24, /* 1920 x 1080 at 60 Hz. */

    HI_VO_OUT_1920x1200_60 = 25, /* VESA 1920 x 1200 at 60 Hz (non-interlaced) CVT (Reduced Blanking) */
    HI_VO_OUT_1920x2160_30 = 26, /* 1920x2160_30 */
    HI_VO_OUT_2560x1440_30 = 27, /* 2560x1440_30 */
    HI_VO_OUT_2560x1440_60 = 28, /* 2560x1440_60 */
    HI_VO_OUT_2560x1600_60 = 29, /* 2560x1600_60 */

    HI_VO_OUT_3840x2160_24 = 30, /* 3840x2160_24 */
    HI_VO_OUT_3840x2160_25 = 31, /* 3840x2160_25 */
    HI_VO_OUT_3840x2160_30 = 32, /* 3840x2160_30 */
    HI_VO_OUT_3840x2160_50 = 33, /* 3840x2160_50 */
    HI_VO_OUT_3840x2160_60 = 34, /* 3840x2160_60 */
    HI_VO_OUT_4096x2160_24 = 35, /* 4096x2160_24 */
    HI_VO_OUT_4096x2160_25 = 36, /* 4096x2160_25 */
    HI_VO_OUT_4096x2160_30 = 37, /* 4096x2160_30 */
    HI_VO_OUT_4096x2160_50 = 38, /* 4096x2160_50 */
    HI_VO_OUT_4096x2160_60 = 39, /* 4096x2160_60 */
    HI_VO_OUT_7680x4320_30 = 40, /* 7680x4320_30 */

    HI_VO_OUT_240x320_50 = 41, /* 240x320_50 */
    HI_VO_OUT_320x240_50 = 42, /* 320x240_50 */
    HI_VO_OUT_240x320_60 = 43, /* 240x320_60 */
    HI_VO_OUT_320x240_60 = 44, /* 320x240_60 */
    HI_VO_OUT_800x600_50 = 45, /* 800x600_60 */

    HI_VO_OUT_720x1280_60 = 46, /* For MIPI DSI Tx 720 x1280 at 60 Hz */
    HI_VO_OUT_1080x1920_60 = 47, /* For MIPI DSI Tx 1080x1920 at 60 Hz */

    HI_VO_OUT_USER = 48, /* User timing. */

    HI_VO_OUT_BUTT,
} hi_vo_intf_sync;

typedef struct {
    hi_bool syncm; /* RW; sync mode(0:timing,as BT.656; 1:signal,as LCD) */
    hi_bool iop; /* RW; interlaced or progressive display(0:i; 1:p) */
    hi_u8 intfb; /* RW; interlaced bit width while output */

    hi_u16 vact; /* RW; vertical active area */
    hi_u16 vbb; /* RW; vertical back blank porch */
    hi_u16 vfb; /* RW; vertical front blank porch */

    hi_u16 hact; /* RW; horizontal active area */
    hi_u16 hbb; /* RW; horizontal back blank porch */
    hi_u16 hfb; /* RW; horizontal front blank porch */
    hi_u16 hmid; /* RW; bottom horizontal active area */

    hi_u16 bvact; /* RW; bottom vertical active area */
    hi_u16 bvbb; /* RW; bottom vertical back blank porch */
    hi_u16 bvfb; /* RW; bottom vertical front blank porch */

    hi_u16 hpw; /* RW; horizontal pulse width */
    hi_u16 vpw; /* RW; vertical pulse width */

    hi_bool idv; /* RW; inverse data valid of output */
    hi_bool ihs; /* RW; inverse horizontal synchronization signal */
    hi_bool ivs; /* RW; inverse vertical synchronization signal */
} hi_vo_sync_info;

typedef struct {
    hi_u32 bg_color; /* RW; background color of a device, in RGB format. */
    hi_vo_intf_type intf_type; /* RW; type of a VO interface */
    hi_vo_intf_sync intf_sync; /* RW; type of a VO interface timing */
    hi_vo_sync_info sync_info; /* RW; information about VO interface timing */
} hi_vo_pub_attr;

typedef struct {
    hi_bool exit_dev_en;  /* RW, range: [0, 1];  whether to disable the vo device when sys exit */
    hi_bool dev_clk_ext_en;  /* RW, range: [0, 1];  whether to open the vo device clock by the external user */
    hi_bool vga_detect_en;   /* RW, range: [0, 1];  whether to enable the vga detect */
    hi_u32 vdac_detect_cycle;  /* RW; VDAC(video digital-to-analog converter) detect cycle; Unit: frame interruption */
} hi_vo_mod_param;

typedef enum {
    HI_VO_CLK_SRC_PLL = 0,       /* Clock source type PLL */
    HI_VO_CLK_SRC_LCDMCLK = 1,   /* Clock source type LCDMCLK */
    HI_VO_CLK_SRC_PLL_FOUT4 = 2, /* Clock source type PLL FOUT4 */
    HI_VO_CLK_SRC_FIXED = 3,     /* Clock source type FIXED */

    HI_VO_CLK_SRC_BUTT,
} hi_vo_clk_src;

typedef enum {
    HI_VO_FIXED_CLK_65M    = 0, /* Fixed clock source 65MHz */
    HI_VO_FIXED_CLK_74_25M = 1, /* Fixed clock source 74.25MHz */
    HI_VO_FIXED_CLK_108M   = 2, /* Fixed clock source 108MHz */
    HI_VO_FIXED_CLK_135M   = 3, /* Fixed clock source 135MHz */
    HI_VO_FIXED_CLK_148_5M = 4, /* Fixed clock source 148.5MHz */
    HI_VO_FIXED_CLK_297M   = 5, /* Fixed clock source 297MHz */

    HI_VO_FIXED_CLK_BUTT,
} hi_vo_fixed_clk;

typedef struct {
    hi_u32 fb_div;    /* RW, range: [0, 0xfff];  frequency double division */
    hi_u32 frac;      /* RW, range: [0, 0xffffff]; fractional division */
    hi_u32 ref_div;   /* RW, range: (0, 0x3f]; reference clock division */
    hi_u32 post_div1; /* RW, range: (0, 0x7]; level 1 post division */
    hi_u32 post_div2; /* RW, range: (0, 0x7]; level 2 post division */
} hi_vo_pll;

typedef struct {
    hi_vo_clk_src clk_src; /* RW; clock source type */

    union {
        /*
         * RW; user synchronization timing clock PLL information.
         * AUTO: hi_vo_clk_src:HI_VO_CLK_SRC_PLL, HI_VO_CLK_SRC_PLL_FOUT4;
         */
        hi_vo_pll vo_pll;
        /*
         * RW, range: [1, 8473341]; LCD clock division.
         * AUTO: hi_vo_clk_src:HI_VO_CLK_SRC_LCDMCLK;
         */
        hi_u32 lcd_m_clk_div;

        hi_vo_fixed_clk fixed_clk; /* RW; fixed clock. AUTO: hi_vo_clk_src:HI_VO_CLK_SRC_FIXED; */
    };
} hi_vo_user_sync_attr;

typedef struct {
    hi_vo_user_sync_attr user_sync_attr; /* RW; user synchronization timing attribute */
    hi_u32 pre_div;                      /* RW, range: [1, 32]; device previous division */
    hi_u32 dev_div;                      /* RW, range: [1, 4]; device clock division */
    hi_bool clk_reverse_en;              /* RW, range: [0, 1]; whether to reverse clock  */
} hi_vo_user_sync_info;

typedef struct {
    hi_bool enable;  /* RW, less buf enable */
    hi_u32 vtth;     /* RW, vtth value */
}hi_vo_less_buf_attr;

typedef enum {
    HI_VO_INTF_STATUS_NO_PLUG = 0,  /* Interface status is not plugged */
    HI_VO_INTF_STATUS_PLUG = 1,     /* Interface status is plugged */
    HI_VO_INTF_STATUS_BUTT,
}hi_vo_intf_plug_status;

typedef struct {
    hi_vo_intf_plug_status plug_status;  /* R; Interface plug status */
}hi_vo_intf_status;

typedef enum {
    HI_VO_CSC_MATRIX_BT601LIMIT_TO_BT601LIMIT = 0, /* Identity matrix.   from BT.601 limit to BT.601 limit */
    HI_VO_CSC_MATRIX_BT601FULL_TO_BT601LIMIT = 1,  /* Change color space from BT.601 full to BT.601 limit */
    HI_VO_CSC_MATRIX_BT709LIMIT_TO_BT601LIMIT = 2, /* Change color space from BT.709 limit to BT.601 limit */
    HI_VO_CSC_MATRIX_BT709FULL_TO_BT601LIMIT = 3,  /* Change color space from BT.709 full to BT.601 limit */

    HI_VO_CSC_MATRIX_BT601LIMIT_TO_BT709LIMIT = 4, /* Change color space from BT.601 limit to BT.709 limit */
    HI_VO_CSC_MATRIX_BT601FULL_TO_BT709LIMIT = 5,  /* Change color space from BT.601 full to BT.709 limit */
    HI_VO_CSC_MATRIX_BT709LIMIT_TO_BT709LIMIT = 6, /* Identity matrix.   from BT.709 limit to BT.709 limit */
    HI_VO_CSC_MATRIX_BT709FULL_TO_BT709LIMIT = 7,  /* Change color space from BT.709 full to BT.709 limit */

    HI_VO_CSC_MATRIX_BT601LIMIT_TO_BT601FULL = 8,  /* Change color space from BT.601 limit to BT.601 full */
    HI_VO_CSC_MATRIX_BT601FULL_TO_BT601FULL = 9,   /* Identity matrix.   from BT.601 full to BT.601 full */
    HI_VO_CSC_MATRIX_BT709LIMIT_TO_BT601FULL = 10,  /* Change color space from BT.709 limit to BT.601 full */
    HI_VO_CSC_MATRIX_BT709FULL_TO_BT601FULL = 11,   /* Change color space from BT.709 full to BT.601 full */

    HI_VO_CSC_MATRIX_BT601LIMIT_TO_BT709FULL = 12,  /* Change color space from BT.601 limit to BT.709 full */
    HI_VO_CSC_MATRIX_BT601FULL_TO_BT709FULL = 13,   /* Change color space from BT.601 full to BT.709 full */
    HI_VO_CSC_MATRIX_BT709LIMIT_TO_BT709FULL = 14,  /* Change color space from BT.709 limit to BT.709 full */
    HI_VO_CSC_MATRIX_BT709FULL_TO_BT709FULL = 15,   /* Identity matrix.   from BT.709 full to BT.709 full */

    HI_VO_CSC_MATRIX_BT601LIMIT_TO_RGBFULL = 16,    /* Change color space from BT.601 limit to RGB full */
    HI_VO_CSC_MATRIX_BT601FULL_TO_RGBFULL = 17,     /* Change color space from BT.601 full to RGB full */
    HI_VO_CSC_MATRIX_BT709LIMIT_TO_RGBFULL = 18,    /* Change color space from BT.709 limit to RGB full */
    HI_VO_CSC_MATRIX_BT709FULL_TO_RGBFULL = 19,     /* Change color space from BT.709 full to RGB full */

    HI_VO_CSC_MATRIX_BT601LIMIT_TO_RGBLIMIT = 20,   /* Change color space from BT.601 limit to RGB limit */
    HI_VO_CSC_MATRIX_BT601FULL_TO_RGBLIMIT = 21,    /* Change color space from BT.709 full to RGB limit */
    HI_VO_CSC_MATRIX_BT709LIMIT_TO_RGBLIMIT = 22,   /* Change color space from BT.601 limit to RGB limit */
    HI_VO_CSC_MATRIX_BT709FULL_TO_RGBLIMIT = 23,    /* Change color space from BT.709 full to RGB limit */

    HI_VO_CSC_MATRIX_RGBFULL_TO_BT601LIMIT = 24,    /* Change color space from RGB full to BT.601 limit */
    HI_VO_CSC_MATRIX_RGBFULL_TO_BT601FULL = 25,     /* Change color space from RGB full to BT.601 full */
    HI_VO_CSC_MATRIX_RGBFULL_TO_BT709LIMIT = 26,    /* Change color space from RGB full to BT.709 limit */
    HI_VO_CSC_MATRIX_RGBFULL_TO_BT709FULL = 27,     /* Change color space from RGB full to BT.709 full */

    HI_VO_CSC_MATRIX_BUTT,
} hi_vo_csc_matrix;

typedef struct {
    hi_vo_csc_matrix csc_matrix; /* RW; CSC matrix */
    hi_u32 luma; /* RW; range: [0, 100]; luminance, default: 50 */
    hi_u32 contrast; /* RW; range: [0, 100]; contrast, default: 50 */
    hi_u32 hue; /* RW; range: [0, 100]; hue, default: 50 */
    hi_u32 saturation; /* RW; range: [0, 100]; saturation, default: 50 */
    hi_bool ex_csc_en; /* RW; range: [0, 1]; extended csc switch for luminance, default: 0 */
} hi_vo_csc;

typedef struct {
    hi_vo_csc csc;  /* RW; color space */
    hi_u32 gain;  /* RW; range: [0, 64); current gain of VGA signals. */
    hi_s32 sharpen_strength;  /* RW; range: [0, 255]; current sharpen strength of VGA signals. */
} hi_vo_vga_param;

typedef struct {
    hi_vo_csc csc; /* RW, color space */
} hi_vo_hdmi_param;

typedef struct {
    hi_vo_csc csc; /* RW, color space */
    hi_bool rgb_inverted_en; /* RW; component r g b inverted, rgb to bgr, default: 0, rgb */
    hi_bool bit_inverted_en; /* RW; data's bit inverted,
                                rgb6bit: bit[5:0] to bit[0:5],
                                rgb8bit: bit[7:0] to bit[0:7],
                                rgb16bit: bit[15:0] to bit[0:15],
                                rgb18bit: bit[17:0] to bit[0:17],
                                rgb24bit: bit[23:0] to bit[0:23],
                                default: 0, bit[5/7/15/17/23:0] */
} hi_vo_rgb_param;

typedef struct {
    hi_bool yc_inverted_en; /* RW; component y c inverted, yc to cy, default: 0, yc */
    hi_bool bit_inverted_en; /* RW; data's bit inverted, bt.656: bit[7:0] to bit[0:7],
                                bt.1120: bit[15:0] to bit[0:15],
                                default: 0, bit[7:0] or bit[15:0] */
} hi_vo_bt_param;

typedef enum {
    HI_VO_PARTITION_MODE_SINGLE = 0, /* Single partition, use software to make multi-picture in one hardware cell */
    HI_VO_PARTITION_MODE_MULTI = 1,  /* Multi partition, each partition is a hardware cell */
    HI_VO_PARTITION_MODE_BUTT,
} hi_vo_partition_mode;

typedef struct {
    hi_rect display_rect; /* RW; display resolution */
    hi_phys_addr_t address;
    hi_u32 stride;
} hi_vo_video_layer_attr;

typedef enum {
    HI_VO_GFX_TYPE_ARGB1555 = 0,
    HI_VO_GFX_TYPE_BMP1555 = 1,

    HI_VO_GFX_TYPE_BUTT
}hi_vo_gfx_type;

typedef struct {
    hi_rect display_rect;
    hi_phys_addr_t address;
    hi_u32 stride;
    hi_vo_gfx_type type;
} hi_vo_gfx_attr;

typedef struct {
    hi_aspect_ratio aspect_ratio; /* RW; aspect ratio */
} hi_vo_layer_param;

typedef struct {
    hi_u32 priority; /* RW; video out overlay priority sd */
    hi_rect rect; /* RW; rectangle of video output channel */
    hi_bool deflicker_en; /* RW; deflicker or not sd */
} hi_vo_chn_attr;

typedef struct {
    hi_aspect_ratio aspect_ratio; /* RW; aspect ratio */
} hi_vo_chn_param;

typedef enum {
    HI_VO_ZOOM_IN_RECT = 0, /* Zoom in by rect */
    HI_VO_ZOOM_IN_RATIO = 1, /* Zoom in by ratio */
    HI_VO_ZOOM_IN_BUTT,
} hi_vo_zoom_in_type;

typedef struct {
    /* RW; range: [0, 1000]; x_ratio = x * 1000 / W, x means start point to be zoomed, W means channel's width. */
    hi_u32 x_ratio;
    /* RW; range: [0, 1000]; y_ratio = y * 1000 / H, y means start point to be zoomed, H means channel's height. */
    hi_u32 y_ratio;
    /* RW; range: [0, 1000]; width_ratio = w * 1000 / W, w means width to be zoomed, W means channel's width. */
    hi_u32 width_ratio;
    /* RW; range: [0, 1000]; height_ratio = h * 1000 / H, h means height to be zoomed, H means channel's height. */
    hi_u32 height_ratio;
} hi_vo_zoom_ratio;

typedef struct {
    hi_vo_zoom_in_type zoom_type; /* RW; choose the type of zoom in */
    union {
        hi_rect zoom_rect; /* RW; zoom in by rect. AUTO:hi_vo_zoom_in_type:HI_VO_ZOOM_IN_RECT; */
        hi_vo_zoom_ratio zoom_ratio; /* RW; zoom in by ratio. AUTO:hi_vo_zoom_in_type:HI_VO_ZOOM_IN_RATIO; */
    };
} hi_vo_zoom_attr;

typedef struct {
    hi_bool enable; /* RW; do frame or not */
    hi_border border; /* RW; frame's top, bottom, left, right width and color */
} hi_vo_border;

typedef struct {
    hi_u32 chn_buf_used; /* R; channel buffer that been used */
} hi_vo_chn_status;

typedef struct {
    hi_size target_size; /* RW; WBC zoom target size */
    hi_pixel_format pixel_format; /* RW; the pixel format of WBC output */
    hi_u32 frame_rate; /* RW; frame rate control */
    hi_dynamic_range dynamic_range; /* RW; write back dynamic range type */
    hi_compress_mode compress_mode; /* RW; write back compressing mode   */
} hi_vo_wbc_attr;

typedef enum {
    HI_VO_WBC_MODE_NORM = 0, /* In this mode, wbc will capture frames according to dev frame rate
                                and wbc frame rate */
    HI_VO_WBC_MODE_DROP_REPEAT = 1, /* In this mode, wbc will drop dev repeat frame, and capture the real frame
                                according to video layer's display rate and wbc frame rate */
    HI_VO_WBC_MODE_PROGRESSIVE_TO_INTERLACED = 2, /* In this mode, wbc will drop dev repeat frame which repeats more
                                than 3 times, and change two progressive frames to one interlaced frame */
    HI_VO_WBC_MODE_BUTT,
} hi_vo_wbc_mode;

typedef enum {
    HI_VO_WBC_SRC_DEV = 0, /* WBC source is device */
    HI_VO_WBC_SRC_VIDEO = 1, /* WBC source is video layer */
    HI_VO_WBC_SRC_BUTT,
} hi_vo_wbc_src_type;

typedef struct {
    hi_vo_wbc_src_type src_type; /* RW; WBC source's type */
    hi_u32 src_id; /* RW; WBC source's ID */
} hi_vo_wbc_src;

typedef enum {
    HI_VO_CAS_MODE_SINGLE = 0, /* cascade mode is single */
    HI_VO_CAS_MODE_DUAL = 1, /* cascade mode is dual */
    HI_VO_CAS_MODE_BUTT,
} hi_vo_cas_mode;

typedef enum {
    HI_VO_CAS_MODE_SINGLE_EDGE = 0, /* single transmission,clock rising edge or falling edge trigger transmission */
    HI_VO_CAS_MODE_DUAL_EDGE = 1, /* dual transmission,clock rising edge and falling edge trigger transmission */
    HI_VO_CAS_MODE_EDGE_BUTT,
} hi_vo_cas_data_transmission_mode;

typedef enum {
    HI_VO_CAS_RGN_64 = 0, /* cascade region number 64 */
    HI_VO_CAS_RGN_32 = 1, /* cascade region number 32 */
    HI_VO_CAS_RGN_BUTT,
} hi_vo_cas_rgn;

typedef struct {
    hi_bool         is_slave;                        /* RW; HI_TRUE: slave mode, HI_FALSE: master mode */
    hi_vo_cas_rgn   cas_rgn;                         /* RW; cascade region number */
    hi_vo_cas_mode  cas_mode;                        /* RW; cascade mode */
    hi_vo_cas_data_transmission_mode cas_edge_mode;  /* RW; cascade data transmission mode  */
} hi_vo_cas_attr;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of #ifndef __HI_COMMON_VO_H__ */
