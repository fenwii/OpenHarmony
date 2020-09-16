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

#include "boot_hdmi_intf.h"
#include "drv_hdmi_common.h"
#include "hi_hdmi.h"
#include "hdmi_product_define.h"
#include "hi_common_vo.h"

#define HDMI_MULTIPLE_2P0(x)      ((x) *= 2)
#define HDMI_MULTIPLE_1P5(x)      ((x) = ((x) * 3) >> 1)
#define HDMI_MULTIPLE_1P25(x)     ((x) = ((x) * 5) >> 2)
#define HDMI_MULTIPLE_0P5(x)      ((x) >>= 1)
#define HDMI_MAX_HDMI14_TMDS_RATE 340000
#define HDMI_VIC_VIRTUAL_BASE     255U
#define HDMI_VIC_PC_BASE          ((HDMI_VIC_VIRTUAL_BASE) + 0x100)
#define FMT_VIC_800X600           ((HDMI_VIC_PC_BASE) + 9)
#define FMT_VIC_1024X768          ((HDMI_VIC_PC_BASE) + 13)
#define FMT_VIC_1280X1024         ((HDMI_VIC_PC_BASE) + 25)
#define FMT_VIC_1366X768          ((HDMI_VIC_PC_BASE) + 28)
#define FMT_VIC_1920X1200         ((HDMI_VIC_PC_BASE) + 41)
#define HDMI_INVALID_PIXFREQ      0xffffffff
#define MAX_HDMI_HW_PARAM         43
#define MAX_HDMI_FT_PARAM         4
#define SCRAMBLE_INTERVAL         20
#define SCRAMBLE_TIMEOUT          200
#ifndef HI_PLATFORM_H8
#define FMT_4K_50 VO_OUTPUT_3840X2160_50
#define FMT_4K_60 VO_OUTPUT_3840X2160_60
#else
#define FMT_4K_50 HI_VO_OUT_3840x2160_50
#define FMT_4K_60 HI_VO_OUT_3840x2160_60
#endif

typedef struct {
    hi_u32 vic;
    hi_u32 pixl_freq; /* KHz */
    hi_u32 hor_active;
    hi_u32 ver_active;
    hi_u32 field_rate; /* 0.01Hz */
    hi_u32 format;
} hdmi_fmt_param;

#define hdmi_if_failure_return(ret)                                     \
    do {                                                                \
        if ((ret) != HI_SUCCESS) {                                      \
            printf("ERROR:%s[%d], return fail!\n", __func__, __LINE__); \
            return HI_FAILURE;                                          \
        }                                                               \
    } while (0)

#define VIDMODE_2_COLORSPACE(vid_mode, color_space)             \
    do {                                                        \
        if ((vid_mode) == HI_HDMI_VIDEO_MODE_RGB444) {          \
            color_space = HDMI_COLORSPACE_RGB;                  \
        } else if ((vid_mode) == HI_HDMI_VIDEO_MODE_YCBCR422) { \
            color_space = HDMI_COLORSPACE_YCBCR422;             \
        } else {                                                \
            color_space = HDMI_COLORSPACE_YCBCR444;             \
        }                                                       \
    } while (0)

static hdmi_device g_hdmi_dev[HDMI_DEVICE_ID_BUTT];

#ifndef HI_PLATFORM_H8
static const hdmi_fmt_param g_fmt_param_table[] = {
    /*         VIC      PixFreq  HACT  VACT FldRate     EncFmt           */
    {                 0, 106500, 1440,  900, 6000, VO_OUTPUT_1440X900_60  },
    {                 0,  71000, 1280,  800, 6000, VO_OUTPUT_1280X800_60  },
    {                 0, 119000, 1680, 1560, 6000, VO_OUTPUT_1680X1050_60 },
    {                 0, 162000, 1600, 1200, 6000, VO_OUTPUT_1600X1200_60 },
    {                 0, 268500, 2560, 1600, 6000, VO_OUTPUT_2560X1600_60 },
    {                 0, 130000, 2560, 1440, 3000, VO_OUTPUT_2560X1440_30 },
    {                 0, 238750, 2560, 1440, 6000, VO_OUTPUT_2560X1440_60 },
    {                 0, 170000, 1920, 2160, 3000, VO_OUTPUT_1920X2160_30 },
    {                 1,  25175,  640,  480, 6000, VO_OUTPUT_640X480_60   },
    {                 2,  27000,  720,  480, 6000, VO_OUTPUT_480P60       },
    {                 3,  27000,  720,  480, 6000, VO_OUTPUT_480P60       },
    {                 4,  74170, 1280,  720, 6000, VO_OUTPUT_720P60       },
    {                 5,  74170, 1920, 1080, 6000, VO_OUTPUT_1080I60      },
    {                 6,  27000,  720,  480, 6000, VO_OUTPUT_NTSC         },
    {                 7,  27000,  720,  480, 6000, VO_OUTPUT_NTSC         },
    {                16, 148500, 1920, 1080, 6000, VO_OUTPUT_1080P60      },
    {                17,  27000,  720,  576, 5000, VO_OUTPUT_576P50       },
    {                18,  27000,  720,  576, 5000, VO_OUTPUT_576P50       },
    {                19,  74250, 1280,  720, 5000, VO_OUTPUT_720P50       },
    {                20,  74250, 1920, 1080, 5000, VO_OUTPUT_1080I50      },
    {                21,  27000, 1440,  576, 5000, VO_OUTPUT_PAL          },
    {                22,  27000, 1440,  576, 5000, VO_OUTPUT_PAL          },
    {                31, 148500, 1920, 1080, 5000, VO_OUTPUT_1080P50      },
    {                32,  74170, 1920, 1080, 2400, VO_OUTPUT_1080P24      },
    {                33,  74250, 1920, 1080, 2500, VO_OUTPUT_1080P25      },
    {                34,  74170, 1920, 1080, 3000, VO_OUTPUT_1080P30      },
    {                93, 297000, 3840, 2160, 2400, VO_OUTPUT_3840X2160_24 },
    {                94, 297000, 3840, 2160, 2500, VO_OUTPUT_3840X2160_25 },
    {                95, 297000, 3840, 2160, 3000, VO_OUTPUT_3840X2160_30 },
    {                96, 594000, 3840, 2160, 5000, VO_OUTPUT_3840X2160_50 },
    {                97, 594000, 3840, 2160, 6000, VO_OUTPUT_3840X2160_60 },
    {                98, 297000, 4096, 2160, 2400, VO_OUTPUT_4096X2160_24 },
    {                99, 297000, 4096, 2160, 2500, VO_OUTPUT_4096X2160_25 },
    {               100, 297000, 4096, 2160, 3000, VO_OUTPUT_4096X2160_30 },
    {               101, 594000, 4096, 2160, 5000, VO_OUTPUT_4096X2160_50 },
    {               102, 594000, 4096, 2160, 6000, VO_OUTPUT_4096X2160_60 },
    {   FMT_VIC_800X600,  37879,  800,  600, 6000, VO_OUTPUT_800X600_60   },
    {  FMT_VIC_1024X768,  65000, 1024,  768, 6000, VO_OUTPUT_1024X768_60  },
    { FMT_VIC_1280X1024, 108000, 1280, 1024, 6000, VO_OUTPUT_1280X1024_60 },
    {  FMT_VIC_1366X768,  85500, 1360,  768, 6000, VO_OUTPUT_1366X768_60  },
    { FMT_VIC_1920X1200, 154000, 1920, 1200, 6000, VO_OUTPUT_1920X1200_60 }
};
#else
static const hdmi_fmt_param g_fmt_param_table[] = {
    /*         VIC      PixFreq  HACT  VACT FldRate     EncFmt           */
    {                 0, 106500, 1440,  900, 6000, HI_VO_OUT_1440x900_60  },
    {                 0,  83500, 1280,  800, 6000, HI_VO_OUT_1280x800_60  },
    {                 0, 146250, 1680, 1560, 6000, HI_VO_OUT_1680x1050_60 },
    {                 0, 162000, 1600, 1200, 6000, HI_VO_OUT_1600x1200_60 },
    {                 0, 268500, 2560, 1600, 6000, HI_VO_OUT_2560x1600_60 },
    {                 0, 119375, 2560, 1440, 3000, HI_VO_OUT_2560x1440_30 },
    {                 0, 238750, 2560, 1440, 6000, HI_VO_OUT_2560x1440_60 },
    {                 0, 148500, 1920, 2160, 3000, HI_VO_OUT_1920x2160_30 },
    {                 0, 121750, 1400, 1050, 6000, HI_VO_OUT_1400x1050_60 },
    {                 1,  25175,  640,  480, 6000, HI_VO_OUT_640x480_60   },
    {                 2,  27000,  720,  480, 6000, HI_VO_OUT_480P60       },
    {                 3,  27000,  720,  480, 6000, HI_VO_OUT_480P60       },
    {                 4,  74250, 1280,  720, 6000, HI_VO_OUT_720P60       },
    {                 5,  74250, 1920, 1080, 6000, HI_VO_OUT_1080I60      },
    {                 6,  27000,  720,  480, 6000, HI_VO_OUT_NTSC         },
    {                 7,  27000,  720,  480, 6000, HI_VO_OUT_NTSC         },
    {                16, 148500, 1920, 1080, 6000, HI_VO_OUT_1080P60      },
    {                17,  27000,  720,  576, 5000, HI_VO_OUT_576P50       },
    {                18,  27000,  720,  576, 5000, HI_VO_OUT_576P50       },
    {                19,  74250, 1280,  720, 5000, HI_VO_OUT_720P50       },
    {                20,  74250, 1920, 1080, 5000, HI_VO_OUT_1080I50      },
    {                21,  27000, 1440,  576, 5000, HI_VO_OUT_PAL          },
    {                22,  27000, 1440,  576, 5000, HI_VO_OUT_PAL          },
    {                31, 148500, 1920, 1080, 5000, HI_VO_OUT_1080P50      },
    {                32,  74250, 1920, 1080, 2400, HI_VO_OUT_1080P24      },
    {                33,  74250, 1920, 1080, 2500, HI_VO_OUT_1080P25      },
    {                34,  74250, 1920, 1080, 3000, HI_VO_OUT_1080P30      },
    {                93, 297000, 3840, 2160, 2400, HI_VO_OUT_3840x2160_24 },
    {                94, 297000, 3840, 2160, 2500, HI_VO_OUT_3840x2160_25 },
    {                95, 297000, 3840, 2160, 3000, HI_VO_OUT_3840x2160_30 },
    {                96, 594000, 3840, 2160, 5000, HI_VO_OUT_3840x2160_50 },
    {                97, 594000, 3840, 2160, 6000, HI_VO_OUT_3840x2160_60 },
    {                98, 297000, 4096, 2160, 2400, HI_VO_OUT_4096x2160_24 },
    {                99, 297000, 4096, 2160, 2500, HI_VO_OUT_4096x2160_25 },
    {               100, 297000, 4096, 2160, 3000, HI_VO_OUT_4096x2160_30 },
    {               101, 594000, 4096, 2160, 5000, HI_VO_OUT_4096x2160_50 },
    {               102, 594000, 4096, 2160, 6000, HI_VO_OUT_4096x2160_60 },
    {   FMT_VIC_800X600,  37879,  800,  600, 6000, HI_VO_OUT_800x600_60   },
    {  FMT_VIC_1024X768,  65000, 1024,  768, 6000, HI_VO_OUT_1024x768_60  },
    { FMT_VIC_1280X1024, 108000, 1280, 1024, 6000, HI_VO_OUT_1280x1024_60 },
    {  FMT_VIC_1366X768,  85500, 1360,  768, 6000, HI_VO_OUT_1366x768_60  },
    { FMT_VIC_1920X1200, 154000, 1920, 1200, 6000, HI_VO_OUT_1920x1200_60 }
};
#endif

static hi_u32 hdmi_pixel_freq_search(hi_u32 fmt)
{
    hi_u32 i;
    hdmi_fmt_param *fmt_param = HI_NULL;

    hdmi_info("fmt:%d. \n", fmt);
    if (fmt >= VO_OUTPUT_BUTT) {
        return HDMI_INVALID_PIXFREQ;
    }

    for (i = 0; i < HDMI_ARRAY_SIZE(g_fmt_param_table); i++) {
        fmt_param = (hdmi_fmt_param *)&g_fmt_param_table[i];
        if ((fmt_param != HI_NULL) && (fmt_param->format == fmt)) {
            return fmt_param->pixl_freq;
        }
    }

    hdmi_info("pix_freq search fail, invalid format=%u\n", fmt);

    return HDMI_INVALID_PIXFREQ;

}

#ifndef HI_PLATFORM_H8
static hdmi_video_timing disp_fmt_to_hdmi_timing(hi_u32 fmt)
{
    hdmi_video_timing video_timing_mode;

    switch (fmt) {
        case VO_OUTPUT_PAL:
            video_timing_mode = HDMI_VIDEO_TIMING_1440X576I_50000;
            break;
        case VO_OUTPUT_NTSC:
            video_timing_mode = HDMI_VIDEO_TIMING_1440X480I_60000;
            break;
        case VO_OUTPUT_1080P24:
            video_timing_mode = HDMI_VIDEO_TIMING_1920X1080P_24000;
            break;
        case VO_OUTPUT_1080P25:
            video_timing_mode = HDMI_VIDEO_TIMING_1920X1080P_25000;
            break;
        case VO_OUTPUT_1080P30:
            video_timing_mode = HDMI_VIDEO_TIMING_1920X1080P_30000;
            break;
        case VO_OUTPUT_720P50:
            video_timing_mode = HDMI_VIDEO_TIMING_1280X720P_50000;
            break;
        case VO_OUTPUT_720P60:
            video_timing_mode = HDMI_VIDEO_TIMING_1280X720P_60000;
            break;
        case VO_OUTPUT_1080I50:
            video_timing_mode = HDMI_VIDEO_TIMING_1920X1080I_50000;
            break;
        case VO_OUTPUT_1080I60:
            video_timing_mode = HDMI_VIDEO_TIMING_1920X1080I_60000;
            break;
        case VO_OUTPUT_1080P50:
            video_timing_mode = HDMI_VIDEO_TIMING_1920X1080P_50000;
            break;
        case VO_OUTPUT_1080P60:
            video_timing_mode = HDMI_VIDEO_TIMING_1920X1080P_60000;
            break;
        case VO_OUTPUT_576P50:
            video_timing_mode = HDMI_VIDEO_TIMING_720X576P_50000;
            break;
        case VO_OUTPUT_480P60:
            video_timing_mode = HDMI_VIDEO_TIMING_720X480P_60000;
            break;
        case VO_OUTPUT_640X480_60:
            video_timing_mode = HDMI_VIDEO_TIMING_640X480P_60000;
            break;
        case VO_OUTPUT_3840X2160_30:
            video_timing_mode = HDMI_VIDEO_TIMING_3840X2160P_30000;
            break;
        case VO_OUTPUT_3840X2160_60:
            video_timing_mode = HDMI_VIDEO_TIMING_3840X2160P_60000;
            break;
        case VO_OUTPUT_3840X2160_24:
            video_timing_mode = HDMI_VIDEO_TIMING_3840X2160P_24000;
            break;
        case VO_OUTPUT_3840X2160_25:
            video_timing_mode = HDMI_VIDEO_TIMING_3840X2160P_25000;
            break;
        case VO_OUTPUT_3840X2160_50:
            video_timing_mode = HDMI_VIDEO_TIMING_3840X2160P_50000;
            break;
        case VO_OUTPUT_4096X2160_30:
            video_timing_mode = HDMI_VIDEO_TIMING_4096X2160P_30000;
            break;
        case VO_OUTPUT_4096X2160_60:
            video_timing_mode = HDMI_VIDEO_TIMING_4096X2160P_60000;
            break;
        case VO_OUTPUT_4096X2160_24:
            video_timing_mode = HDMI_VIDEO_TIMING_4096X2160P_24000;
            break;
        case VO_OUTPUT_4096X2160_25:
            video_timing_mode = HDMI_VIDEO_TIMING_4096X2160P_25000;
            break;
        case VO_OUTPUT_4096X2160_50:
            video_timing_mode = HDMI_VIDEO_TIMING_4096X2160P_50000;
            break;
        default:
            hdmi_info("Non CEA video timing:%d\n", fmt);
            /* 4k2k && vesa */
            video_timing_mode = HDMI_VIDEO_TIMING_UNKNOWN;
            break;

    }
    return video_timing_mode;
}
#else
static hdmi_video_timing disp_fmt_to_hdmi_timing(hi_u32 fmt)
{
    hdmi_video_timing video_timing_mode;

    switch (fmt) {
        case HI_VO_OUT_PAL:
            video_timing_mode = HDMI_VIDEO_TIMING_1440X576I_50000;
            break;
        case HI_VO_OUT_NTSC:
            video_timing_mode = HDMI_VIDEO_TIMING_1440X480I_60000;
            break;
        case HI_VO_OUT_1080P24:
            video_timing_mode = HDMI_VIDEO_TIMING_1920X1080P_24000;
            break;
        case HI_VO_OUT_1080P25:
            video_timing_mode = HDMI_VIDEO_TIMING_1920X1080P_25000;
            break;
        case HI_VO_OUT_1080P30:
            video_timing_mode = HDMI_VIDEO_TIMING_1920X1080P_30000;
            break;
        case HI_VO_OUT_720P50:
            video_timing_mode = HDMI_VIDEO_TIMING_1280X720P_50000;
            break;
        case HI_VO_OUT_720P60:
            video_timing_mode = HDMI_VIDEO_TIMING_1280X720P_60000;
            break;
        case HI_VO_OUT_1080I50:
            video_timing_mode = HDMI_VIDEO_TIMING_1920X1080I_50000;
            break;
        case HI_VO_OUT_1080I60:
            video_timing_mode = HDMI_VIDEO_TIMING_1920X1080I_60000;
            break;
        case HI_VO_OUT_1080P50:
            video_timing_mode = HDMI_VIDEO_TIMING_1920X1080P_50000;
            break;
        case HI_VO_OUT_1080P60:
            video_timing_mode = HDMI_VIDEO_TIMING_1920X1080P_60000;
            break;
        case HI_VO_OUT_576P50:
            video_timing_mode = HDMI_VIDEO_TIMING_720X576P_50000;
            break;
        case HI_VO_OUT_480P60:
            video_timing_mode = HDMI_VIDEO_TIMING_720X480P_60000;
            break;
        case HI_VO_OUT_640x480_60:
            video_timing_mode = HDMI_VIDEO_TIMING_640X480P_60000;
            break;
        case HI_VO_OUT_3840x2160_30:
            video_timing_mode = HDMI_VIDEO_TIMING_3840X2160P_30000;
            break;
        case HI_VO_OUT_3840x2160_60:
            video_timing_mode = HDMI_VIDEO_TIMING_3840X2160P_60000;
            break;
        case HI_VO_OUT_3840x2160_24:
            video_timing_mode = HDMI_VIDEO_TIMING_3840X2160P_24000;
            break;
        case HI_VO_OUT_3840x2160_25:
            video_timing_mode = HDMI_VIDEO_TIMING_3840X2160P_25000;
            break;
        case HI_VO_OUT_3840x2160_50:
            video_timing_mode = HDMI_VIDEO_TIMING_3840X2160P_50000;
            break;
        case HI_VO_OUT_4096x2160_30:
            video_timing_mode = HDMI_VIDEO_TIMING_4096X2160P_30000;
            break;
        case HI_VO_OUT_4096x2160_60:
            video_timing_mode = HDMI_VIDEO_TIMING_4096X2160P_60000;
            break;
        case HI_VO_OUT_4096x2160_24:
            video_timing_mode = HDMI_VIDEO_TIMING_4096X2160P_24000;
            break;
        case HI_VO_OUT_4096x2160_25:
            video_timing_mode = HDMI_VIDEO_TIMING_4096X2160P_25000;
            break;
        case HI_VO_OUT_4096x2160_50:
            video_timing_mode = HDMI_VIDEO_TIMING_4096X2160P_50000;
            break;
        default:
            hdmi_info("Non CEA video timing:%d\n", fmt);
            /* 4k2k && vesa */
            video_timing_mode = HDMI_VIDEO_TIMING_UNKNOWN;
            break;

    }

    return video_timing_mode;
}
#endif

static hi_s32 disp_fmt_to_voattr(hi_u32 disp_fmt, hdmi_vo_attr *video_attr)
{
    video_attr->video_timing = disp_fmt_to_hdmi_timing(disp_fmt);
    video_attr->clk_fs = hdmi_pixel_freq_search(disp_fmt);
    if (video_attr->clk_fs == HDMI_INVALID_PIXFREQ) {
        return HI_FAILURE;
    }

    if (video_attr->video_timing == HDMI_VIDEO_TIMING_640X480P_60000 ||
       video_attr->video_timing == HDMI_VIDEO_TIMING_720X480P_60000 ||
       video_attr->video_timing == HDMI_VIDEO_TIMING_720X576P_50000) {
        video_attr->colorimetry   = HDMI_COLORIMETRY_ITU_709;
        video_attr->picture_aspect = HDMI_PICTURE_ASPECT_4_3;
    } else if (video_attr->video_timing <= HDMI_VIDEO_TIMING_4096X2160P_60000 &&
        video_attr->video_timing >= HDMI_VIDEO_TIMING_4096X2160P_24000) {
        video_attr->colorimetry    = HDMI_COLORIMETRY_ITU_709;
        video_attr->picture_aspect = HDMI_PICTURE_ASPECT_256_135;
    } else {
        video_attr->colorimetry    = HDMI_COLORIMETRY_ITU_709;
        video_attr->picture_aspect = HDMI_PICTURE_ASPECT_16_9;
    }

    video_attr->de_pol = HI_FALSE;
    video_attr->h_sync_pol = HI_FALSE;
    video_attr->v_sync_pol = HI_FALSE;
    video_attr->pixel_repeat = 1;
    if (video_attr->video_timing == HDMI_VIDEO_TIMING_1440X480I_60000 ||
        video_attr->video_timing == HDMI_VIDEO_TIMING_1440X576I_50000) {
        video_attr->pixel_repeat = 2;
    }

    if (video_attr->video_timing <= HDMI_VIDEO_TIMING_640X480P_60000) {
        video_attr->rgb_quantization = HDMI_QUANTIZATION_RANGE_FULL;
    } else {
        video_attr->ycc_quantization = HDMI_YCC_QUANTIZATION_RANGE_LIMITED;
    }

    if (video_attr->video_timing != HDMI_VIDEO_TIMING_UNKNOWN) {
        video_attr->in_colorspace = HDMI_COLORSPACE_YCBCR444;
    } else {
        video_attr->in_colorspace = HDMI_COLORSPACE_RGB;
    }

    video_attr->stereo_mode   = HDMI_3D_BUTT;
    video_attr->in_bit_depth  = HDMI_VIDEO_BITDEPTH_10;
    video_attr->active_aspect = HDMI_ACTIVE_ASPECT_PICTURE;

    return HI_SUCCESS;
}

hdmi_device *get_hdmi_device(hdmi_device_id hdmi_id)
{
    if (hdmi_id < HDMI_DEVICE_ID_BUTT) {
        g_hdmi_dev[hdmi_id].hdmi_dev_id = hdmi_id;
        return &g_hdmi_dev[hdmi_id];
    }
    return HI_NULL;
}

static hi_s32 hdmi_device_init(hdmi_device *hdmi_dev)
{
    hdmi_vo_attr  *video_attr = HI_NULL;
    hdmi_app_attr *app_attr = HI_NULL;

    hdmi_if_null_return(hdmi_dev, HI_FAILURE);
    video_attr = &hdmi_dev->attr.vo_attr;
    app_attr = &hdmi_dev->attr.app_attr;

    hdmi_dev->tmds_mode = HDMI_TMDS_MODE_HDMI_1_4;
    /* application attribute init */
    app_attr->enable_hdmi = HI_TRUE;
    app_attr->enable_clr_space_adapt = HI_TRUE;
    app_attr->enable_deep_clr_adapt = HI_TRUE;
    app_attr->deep_color_mode = HDMI_DEEP_COLOR_24BIT;

    /* video attribute init */
    video_attr->video_timing = HDMI_VIDEO_TIMING_1280X720P_50000;
    if (video_attr->video_timing == HDMI_VIDEO_TIMING_640X480P_60000 ||
       video_attr->video_timing == HDMI_VIDEO_TIMING_720X480P_60000 ||
       video_attr->video_timing == HDMI_VIDEO_TIMING_720X576P_50000) {
        video_attr->colorimetry = HDMI_COLORIMETRY_ITU_709;
        video_attr->picture_aspect = HDMI_PICTURE_ASPECT_4_3;
    } else if (video_attr->video_timing <= HDMI_VIDEO_TIMING_4096X2160P_60000 &&
        video_attr->video_timing >= HDMI_VIDEO_TIMING_4096X2160P_24000) {
        video_attr->colorimetry = HDMI_COLORIMETRY_ITU_709;
        video_attr->picture_aspect = HDMI_PICTURE_ASPECT_256_135;
    } else {
        video_attr->colorimetry = HDMI_COLORIMETRY_ITU_709;
        video_attr->picture_aspect = HDMI_PICTURE_ASPECT_16_9;
    }

    video_attr->de_pol = HI_FALSE;
    video_attr->h_sync_pol = HI_FALSE;
    video_attr->v_sync_pol = HI_FALSE;
    video_attr->pixel_repeat = 1;
    if (video_attr->video_timing == HDMI_VIDEO_TIMING_1440X480I_60000 ||
        video_attr->video_timing == HDMI_VIDEO_TIMING_1440X576I_50000) {
        video_attr->pixel_repeat = 2;
    }

    if (video_attr->video_timing <= HDMI_VIDEO_TIMING_640X480P_60000) {
        video_attr->rgb_quantization = HDMI_QUANTIZATION_RANGE_FULL;
    } else {
        video_attr->ycc_quantization = HDMI_YCC_QUANTIZATION_RANGE_LIMITED;
    }

    if (video_attr->video_timing != HDMI_VIDEO_TIMING_UNKNOWN) {
        video_attr->in_colorspace = HDMI_COLORSPACE_YCBCR444;
    } else {
        video_attr->in_colorspace = HDMI_COLORSPACE_RGB;
    }

    video_attr->stereo_mode   = HDMI_3D_BUTT;
    video_attr->in_bit_depth  = HDMI_VIDEO_BITDEPTH_10;
    video_attr->active_aspect = HDMI_ACTIVE_ASPECT_PICTURE;

#if defined(PHY_CRAFT_S28)
    hdmi_dev->mode_param.trace_len = HDMI_TRACE_BUTT;
    hdmi_dev->mode_param.emi_en = HI_FALSE;
#else
    hdmi_dev->mode_param.trace_len = HDMI_TRACE_LEN_0;
#endif

    return HI_SUCCESS;
}

#ifdef HDMI_SCDC_SUPPORT
static hi_s32 hdmi_scramble_enable_set(hdmi_device *hdmi_dev, hi_bool enable)
{
    hdmi_scdc_status scdc_status = {0};
    hdmi_scdc_status current_status = {0};

    hdmi_info("scdc enable=%d\n", enable);

    scdc_status.scramble_interval  = SCRAMBLE_INTERVAL;
    scdc_status.scramble_timeout   = SCRAMBLE_TIMEOUT;
    scdc_status.sink_read_quest    = HI_FALSE;
    scdc_status.sink_scramble_on   = enable;
    scdc_status.source_scramble_on = enable;
    scdc_status.tmds_bit_clk_ratio = enable ? 40 : 10;
    hal_call_void(hal_hdmi_scdc_status_get, hdmi_dev->hal, &current_status);

    if (current_status.tmds_bit_clk_ratio != scdc_status.tmds_bit_clk_ratio ||
        current_status.sink_scramble_on != scdc_status.sink_scramble_on ||
        current_status.source_scramble_on != scdc_status.source_scramble_on) {
        hdmi_info("cur clk_ratio=%d, sink_scramble_on=%d, source_scramble=%d, set scdc!\n",
            current_status.tmds_bit_clk_ratio, current_status.sink_scramble_on, current_status.source_scramble_on);
        hal_call_void(hal_hdmi_scdc_status_set, hdmi_dev->hal, &scdc_status);
    }
    return HI_SUCCESS;
}
#endif

static hi_s32 hdmi_mode_schedule(hdmi_device *hdmi_dev)
{
#ifdef HDMI_SCDC_SUPPORT
    hi_bool  scramble_enable = HI_FALSE;
#endif

    if (hdmi_dev->attr.vo_attr.hdmi_adapt_pix_clk >= HDMI_MAX_HDMI14_TMDS_RATE) {
        /* enOutColorSpace should change to YCbCr422 for 10bit out. */
        hdmi_dev->tmds_mode = HDMI_TMDS_MODE_HDMI_2_0;
    } else {
        if (hdmi_dev->attr.app_attr.enable_hdmi == HI_TRUE) {
            hdmi_dev->tmds_mode = HDMI_TMDS_MODE_HDMI_1_4;
        } else {
            hdmi_dev->tmds_mode = HDMI_TMDS_MODE_DVI;
            hdmi_dev->attr.app_attr.out_colorspace = HDMI_COLORSPACE_RGB;
        }
    }
    hdmi_info("Tmds mode switch to %d, outSpace=%d\n", hdmi_dev->tmds_mode, hdmi_dev->attr.app_attr.out_colorspace);
    hal_call_void(hal_hdmi_tmds_mode_set, hdmi_dev->hal, hdmi_dev->tmds_mode);
#ifdef HDMI_SCDC_SUPPORT
    scramble_enable = (hdmi_dev->tmds_mode == HDMI_TMDS_MODE_HDMI_2_0) ? HI_TRUE : HI_FALSE;
    hdmi_scramble_enable_set(hdmi_dev, scramble_enable);
#endif

    return HI_SUCCESS;
}

hi_s32 drv_hdmi_open(hdmi_device *hdmi_dev)
{
    hi_s32 ret;
    hdmi_if_null_return(hdmi_dev, HI_FAILURE);

    /* open hdmi hal module */
    ret = hal_hdmi_open(HI_NULL, &hdmi_dev->hal);
    if (ret != HI_SUCCESS) {
        return HI_FAILURE;
    }
    hdmi_device_init(hdmi_dev);
    hdmi_if_null_return(hdmi_dev->hal, HI_FAILURE);
    hdmi_dev->hal->hal_ctx.hdmi_dev = hdmi_dev;
    hdmi_dev->hal->hal_ctx.hdmi_id = hdmi_dev->hdmi_dev_id;

    hal_call_void(hal_hdmi_hardware_init, hdmi_dev->hal);

    return HI_SUCCESS;
}

hi_s32 drv_hdmi_avmute_set(hdmi_device *hdmi_dev, hi_bool av_mute)
{
    hal_call_void(hal_hdmi_avmute_set, hdmi_dev->hal, av_mute);

    return HI_SUCCESS;
}

hi_s32 drv_hdmi_start(hdmi_device *hdmi_dev)
{
    hdmi_if_null_return(hdmi_dev, HI_FAILURE);

    hdmi_mode_schedule(hdmi_dev);
    hal_call_void(hal_hdmi_phy_power_enable_set, hdmi_dev->hal, HI_TRUE);
    hal_call_void(hal_hdmi_phy_output_enable_set, hdmi_dev->hal, HI_TRUE);
    drv_hdmi_avmute_set(hdmi_dev, HI_FALSE);

    return HI_SUCCESS;
}

hi_s32 drv_hdmi_stop(hdmi_device *hdmi_dev)
{
    hdmi_if_null_return(hdmi_dev, HI_FAILURE);

    drv_hdmi_avmute_set(hdmi_dev, HI_TRUE);
    hal_call_void(hal_hdmi_phy_output_enable_set, hdmi_dev->hal, HI_FALSE);
    hal_call_void(hal_hdmi_phy_power_enable_set, hdmi_dev->hal, HI_FALSE);

    return HI_SUCCESS;
}

hi_s32 drv_hdmi_close(hdmi_device *hdmi_dev)
{
    hdmi_if_null_return(hdmi_dev, HI_FAILURE);

    drv_hdmi_stop(hdmi_dev);
    hal_hdmi_close(hdmi_dev->hal);
    hdmi_dev->hal = HI_NULL;

    return HI_SUCCESS;
}

#ifdef PHY_CRAFT_S28
static hi_s32 drv_hdmi_get_hw_spec(hi_hdmi_id hdmi, hi_hdmi_hw_spec *hw_spec)
{
    hi_s32 ret;
    drv_hdmi_hw_spec param = {0};
    hdmi_device *hdmi_dev = HI_NULL;

    hdmi_info(">>> in...\n");

    hdmi_if_null_return(hw_spec, HI_FAILURE);
    hdmi_dev = get_hdmi_device(hdmi);
    hdmi_if_null_return(hdmi_dev, HI_FAILURE);

    memset(hw_spec, 0, sizeof(hi_hdmi_hw_spec));
    hal_call_ret(ret, hal_hdmi_phy_hw_spec_get, hdmi_dev->hal, &param.hw_spec);
    if (ret == HI_SUCCESS) {
        memcpy(hw_spec, &param.hw_spec, sizeof(hi_hdmi_hw_spec));
    }
    hdmi_info("<<< out...\n");

    return ret;
}


static hi_s32 hdmi_hw_spec_check_valid(const hi_hdmi_hw_spec *hw_spec)
{
    hi_u8 i;

    for (i = 0; i < HI_HDMI_HW_PARAM_NUM; i++) {
        if ((hw_spec->hw_param[i].i_de_main_clk > MAX_HDMI_HW_PARAM) ||
            (hw_spec->hw_param[i].i_de_main_data > MAX_HDMI_HW_PARAM) ||
            (hw_spec->hw_param[i].i_main_clk > MAX_HDMI_HW_PARAM) ||
            (hw_spec->hw_param[i].i_main_data > MAX_HDMI_HW_PARAM) ||
            (hw_spec->hw_param[i].ft_cap_clk > MAX_HDMI_FT_PARAM) ||
            (hw_spec->hw_param[i].ft_cap_data > MAX_HDMI_FT_PARAM) ||
            (hw_spec->hw_param[i].i_main_clk == 0) ||
            (hw_spec->hw_param[i].i_main_data == 0)) {
            hdmi_err("stage(%u),u32i_de_main_clk:%u u32i_de_main_data:%u u32i_main_clk:%u u32i_main_data:%u"
                "Valid Range:0-%u\n", i, hw_spec->hw_param[i].i_de_main_clk, hw_spec->hw_param[i].i_de_main_data,
                hw_spec->hw_param[i].i_main_clk, hw_spec->hw_param[i].i_main_data, MAX_HDMI_HW_PARAM);
            hdmi_err("stage(%u),ft_cap_clk:%u ft_cap_data:%u Valid Range:0-%u\n",
                i, hw_spec->hw_param[i].ft_cap_clk, hw_spec->hw_param[i].ft_cap_data, MAX_HDMI_HW_PARAM);
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

static hi_s32 drv_hdmi_set_hw_spec(hi_hdmi_id hdmi, const hi_hdmi_hw_spec *hw_spec)
{
    hi_s32 ret;
    hdmi_hw_spec hw_param = {0};
    hdmi_hal_hw_param param = {0};
    hdmi_device *hdmi_dev = HI_NULL;

    hdmi_info(">>> in...\n");

    hdmi_if_null_return(hw_spec, HI_FAILURE);
    hdmi_dev = get_hdmi_device(hdmi);
    hdmi_if_null_return(hdmi_dev, HI_FAILURE);

    ret = hdmi_hw_spec_check_valid(hw_spec);
    if (ret != HI_SUCCESS) {
        hdmi_err("spec err.\n");
        return ret;
    }

    memcpy(&hw_param, hw_spec, sizeof(hw_param));

    param.hw_spec = &hw_param;
    param.trace_len = hdmi_dev->mode_param.trace_len;
    param.tmds_clk = hdmi_dev->attr.vo_attr.hdmi_adapt_pix_clk;;
    hal_call_ret(ret, hal_hdmi_phy_hw_spec_set, hdmi_dev->hal, param);
    hdmi_info("<<< out...\n");

    return ret;
}

static hi_s32 drv_hdmi_get_mod_param(hi_hdmi_id hdmi, hi_hdmi_mod_param *mode_param)
{
    hdmi_device *hdmi_dev = HI_NULL;
    hdmi_mode_param *param = HI_NULL;

    hdmi_if_null_return(mode_param, HI_FAILURE);
    hdmi_dev = get_hdmi_device(hdmi);
    hdmi_if_null_return(hdmi_dev, HI_FAILURE);

    param = &hdmi_dev->mode_param;
    mode_param->trace_len = param->trace_len;
    mode_param->emi_en = param->emi_en;

    return HI_SUCCESS;
}

static hi_s32 drv_hdmi_set_mod_param(hi_hdmi_id hdmi, const hi_hdmi_mod_param *mode_param)
{
    hdmi_device *hdmi_dev = HI_NULL;
    hdmi_mode_param *param = HI_NULL;

    hdmi_if_null_return(mode_param, HI_FAILURE);
    hdmi_dev = get_hdmi_device(hdmi);
    hdmi_if_null_return(hdmi_dev, HI_FAILURE);

    if (mode_param->trace_len > HI_HDMI_TRACE_BUTT) {
        hdmi_err("param invalid!\n");
        return HI_FAILURE;
    }
    param = &hdmi_dev->mode_param;
    param->trace_len = mode_param->trace_len;
    param->emi_en = mode_param->emi_en;
    hdmi_info("set trace length: %u, set emi enable: %u\n", param->trace_len, param->emi_en);

    return HI_SUCCESS;
}
#endif

static hi_s32 check_video_attr(hdmi_vo_attr *vo_attr)
{
    if (vo_attr->video_timing >= HDMI_VIDEO_TIMING_BUTT) {
        hdmi_info("Hdmi video timing(%d) is wrong\n", vo_attr->video_timing);
        return HI_FAILURE;
    }

    if (vo_attr->in_colorspace >= HDMI_COLORSPACE_BUTT) {
        hdmi_info("Hdmi video InColorSpace(%d) is wrong\n", vo_attr->in_colorspace);
        return HI_FAILURE;
    }

    if (vo_attr->colorimetry <= HDMI_COLORIMETRY_NONE ||
        vo_attr->colorimetry > HDMI_COLORIMETRY_EXTENDED) {
        hdmi_info("Hdmi video Colorimetry(%d) is wrong\n", vo_attr->colorimetry);
        return HI_FAILURE;
    }

    if (vo_attr->rgb_quantization > HDMI_QUANTIZATION_RANGE_FULL) {
        hdmi_info("Hdmi video RGBQuantization(%d) is wrong\n", vo_attr->rgb_quantization);
        return HI_FAILURE;
    }

    if (vo_attr->picture_aspect < HDMI_PICTURE_ASPECT_4_3 ||
        vo_attr->picture_aspect > HDMI_PICTURE_ASPECT_256_135) {
        hdmi_info("Hdmi video PictureAspect(%d) is wrong\n", vo_attr->picture_aspect);
        return HI_FAILURE;
    }

    if (vo_attr->in_bit_depth > HDMI_VIDEO_BITDEPTH_12) {
        hdmi_info("Hdmi video InBitDepth(%d) is wrong\n", vo_attr->in_bit_depth);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static hi_s32 hdmi_video_path_set(hdmi_device *hdmi_dev, hdmi_vo_attr *vo_attr)
{
    hdmi_video_config vid_cfg = {0};
    hdmi_app_attr *app_attr = HI_NULL;

    hdmi_if_null_return(hdmi_dev, HI_FAILURE);
    hdmi_if_null_return(vo_attr, HI_FAILURE);

    app_attr = &hdmi_dev->attr.app_attr;

    vid_cfg.in_bit_depth  = vo_attr->in_bit_depth;
    vid_cfg.quantization  = vo_attr->rgb_quantization;
    vid_cfg.in_colorspace = vo_attr->in_colorspace;
    vid_cfg.pixel_clk     = (app_attr->out_colorspace == HDMI_COLORSPACE_YCBCR420) ?
        (vo_attr->clk_fs >> 1) : vo_attr->clk_fs;
    vid_cfg.tmds_clk       = vo_attr->hdmi_adapt_pix_clk;
    vid_cfg.deep_color     = app_attr->deep_color_mode;
    vid_cfg.out_colorspace = app_attr->out_colorspace;
    vid_cfg.de_pol         = vo_attr->de_pol;
    vid_cfg.h_sync_pol     = vo_attr->h_sync_pol;
    vid_cfg.v_sync_pol     = vo_attr->v_sync_pol;
    vid_cfg.trace_len      = hdmi_dev->mode_param.trace_len;
    vid_cfg.emi_enable     = hdmi_dev->mode_param.emi_en;

    switch (vo_attr->colorimetry) {
        case HDMI_COLORIMETRY_ITU_601:
            vid_cfg.conv_std = HDMI_CONV_STD_BT_601;
            break;
        case HDMI_COLORIMETRY_ITU_709:
            vid_cfg.conv_std = HDMI_CONV_STD_BT_709;
            break;
        case HDMI_COLORIMETRY_EXTENDED:
            if (vo_attr->extended_colorimetry == HDMI_EXTENDED_COLORIMETRY_2020_NON_CONST_LUMINOUS) {
                vid_cfg.conv_std = HDMI_CONV_STD_BT_2020_NON_CONST_LUMINOUS;
            } else if (vo_attr->extended_colorimetry == HDMI_EXTENDED_COLORIMETRY_2020_CONST_LUMINOUS) {
                vid_cfg.conv_std = HDMI_CONV_STD_BT_2020_CONST_LUMINOUS;
            }
            break;
        default:
            break;
    }

    hdmi_info("pixel_clk(%d), tmds_clk(%d)\n", vid_cfg.pixel_clk, vid_cfg.tmds_clk);
    /* Video will mute and unmute in this function call */
    hal_call_void(hal_hdmi_video_path_set, hdmi_dev->hal, &vid_cfg);

    return HI_SUCCESS;
}

hi_s32 drv_hdmi_attr_get(hdmi_device *hdmi_dev, hdmi_attr *attr)
{
    hdmi_if_null_return(hdmi_dev, HI_FAILURE);
    hdmi_if_null_return(attr, HI_FAILURE);
    memcpy(attr, &hdmi_dev->attr, sizeof(hdmi_attr));

    return HI_SUCCESS;
}

static hi_s32 hdmi_tmdsclk_get(hdmi_device *hdmi_dev)
{
    hdmi_app_attr *app_attr = HI_NULL;
    hdmi_vo_attr *video_attr = HI_NULL;

    app_attr = &hdmi_dev->attr.app_attr;
    video_attr = &hdmi_dev->attr.vo_attr;

    video_attr->hdmi_adapt_pix_clk = video_attr->clk_fs;
    if (app_attr->out_colorspace == HDMI_COLORSPACE_YCBCR420) {
        HDMI_MULTIPLE_0P5(video_attr->hdmi_adapt_pix_clk); /* Y420 */
        HDMI_MULTIPLE_0P5(video_attr->clk_fs);
    }
    if (app_attr->out_colorspace != HDMI_COLORSPACE_YCBCR422) {
        switch (app_attr->deep_color_mode) {
            case HDMI_DEEP_COLOR_30BIT:
                HDMI_MULTIPLE_1P25(video_attr->hdmi_adapt_pix_clk);
                break;
            case HDMI_DEEP_COLOR_36BIT:
                HDMI_MULTIPLE_1P5(video_attr->hdmi_adapt_pix_clk);
                break;
            case HDMI_DEEP_COLOR_48BIT:
                HDMI_MULTIPLE_2P0(video_attr->hdmi_adapt_pix_clk);
                break;
            case HDMI_DEEP_COLOR_24BIT:
            case HDMI_DEEP_COLOR_OFF:
            default:
                app_attr->deep_color_mode = HDMI_DEEP_COLOR_24BIT;
                break;
        }
    } else {
        app_attr->deep_color_mode = HDMI_DEEP_COLOR_OFF;
    }

    return HI_SUCCESS;
}

static hi_s32 hdmi_caps_check(unsigned int vosync)
{
#ifdef HI_HDMI_SUPPORT_1_4
    hi_bool support = HI_FALSE;
    support = (vosync == FMT_4K_50 || vosync == FMT_4K_60);
    if (support == HI_TRUE) {
        hdmi_err("param is invalid, This chip is not support HDMI2.0\n");
        return HI_FAILURE;
    }
#endif

    return HI_SUCCESS;
}

hi_s32 drv_hdmi_attr_set(hdmi_device *hdmi_dev, hdmi_attr *attr)
{
    hdmi_vo_attr *video_attr = HI_NULL;

    hdmi_if_null_return(hdmi_dev, HI_FAILURE);
    hdmi_if_null_return(attr, HI_FAILURE);

    video_attr = &attr->vo_attr;
    check_video_attr(video_attr);
    memcpy(&hdmi_dev->attr, attr, sizeof(hdmi_attr));

    /* YUV422 is not support when the fmt is PAL or NTSC. */
    if (hdmi_dev->attr.vo_attr.video_timing == HDMI_VIDEO_TIMING_1440X480I_60000 ||
        hdmi_dev->attr.vo_attr.video_timing == HDMI_VIDEO_TIMING_1440X576I_50000) {
        if (hdmi_dev->attr.app_attr.out_colorspace == HDMI_COLORSPACE_YCBCR422) {
            hdmi_info("Y422 is not support at pal and ntsc, force adapt to rgb.\n");
            hdmi_dev->attr.app_attr.out_colorspace = HDMI_COLORSPACE_RGB;
        }
    }

    hdmi_tmdsclk_get(hdmi_dev);
    hdmi_video_path_set(hdmi_dev, &hdmi_dev->attr.vo_attr);
    drv_hdmi_avi_infoframe_send(&hdmi_dev->infoframe, HI_TRUE);
    drv_hdmi_vendor_infoframe_send(&hdmi_dev->infoframe, HI_TRUE);

    return HI_SUCCESS;
}

hi_s32 hi_drv_hdmi_init(hi_void)
{
    return HI_SUCCESS;
}

hi_s32 hi_drv_hdmi_open(hi_unf_hdmi_id hdmi_id)
{
    if (hdmi_id >= HI_HDMI_ID_BUTT) {
        hdmi_err("param err!\n");
        return HI_FAILURE;
    }
    memset(&g_hdmi_dev[hdmi_id], 0, sizeof(hdmi_device));
    g_hdmi_dev[hdmi_id].hdmi_dev_id = hdmi_id;

    return drv_hdmi_open(&g_hdmi_dev[hdmi_id]);
}

hi_s32 hi_drv_hdmi_set_attr(hi_unf_hdmi_id hdmi_id, hi_drv_hdmi_attr *attr)
{
    hi_s32 ret;
    hdmi_attr attr_tmp = {0};

    hdmi_if_null_return(attr, HI_FAILURE);
    hdmi_id_check_return(hdmi_id, HI_FAILURE);

    drv_hdmi_attr_get(&g_hdmi_dev[hdmi_id], &attr_tmp);
    ret = disp_fmt_to_voattr(attr->disp_fmt, &attr_tmp.vo_attr);
    if (ret != HI_SUCCESS) {
        hdmi_info("Please input a correct Fmt(%d)!\n", attr->disp_fmt);
        return ret;
    }
    attr_tmp.app_attr.enable_hdmi = attr->enable_hdmi;
    VIDMODE_2_COLORSPACE(attr->vid_out_mode, attr_tmp.app_attr.out_colorspace);
    VIDMODE_2_COLORSPACE(attr->vid_in_mode, attr_tmp.vo_attr.in_colorspace);

    return drv_hdmi_attr_set(&g_hdmi_dev[hdmi_id], &attr_tmp);
}

void hdmi_stop(void)
{
    hi_drv_hdmi_close(HI_HDMI_ID_0);
    hi_drv_hdmi_de_init();
    return;
}

int hdmi_display(unsigned int vosync, unsigned int input, unsigned int output)
{
    hi_s32 ret;
    hi_drv_hdmi_attr attr = {0};

    ret = hdmi_caps_check(vosync);
    hdmi_if_failure_return(ret);

    ret = hi_drv_hdmi_init();
    hdmi_if_failure_return(ret);

    ret = hi_drv_hdmi_open(HI_HDMI_ID_0);
    hdmi_if_failure_return(ret);

    attr.enable_hdmi  = HI_TRUE;
    attr.disp_fmt     = vosync;
    attr.vid_out_mode = output;
    attr.vid_in_mode  = input;
    ret = hi_drv_hdmi_set_attr(HI_HDMI_ID_0, &attr);
    hdmi_if_failure_return(ret);

    ret = hi_drv_hdmi_start(HI_HDMI_ID_0);
    hdmi_if_failure_return(ret);

    return ret;
}

hi_s32 hi_drv_hdmi_start(hi_unf_hdmi_id hdmi_id)
{
    hdmi_id_check_return(hdmi_id, HI_FAILURE);
    return drv_hdmi_start(&g_hdmi_dev[hdmi_id]);
}

hi_s32 hi_drv_hdmi_close(hi_unf_hdmi_id hdmi_id)
{
    hdmi_id_check_return(hdmi_id, HI_FAILURE);
    return drv_hdmi_close(&g_hdmi_dev[hdmi_id]);
}

hi_s32 hi_drv_hdmi_de_init(hi_void)
{
    return HI_SUCCESS;
}

hi_s32 HI_UNF_HDMI_Init(void)
{
    return hi_drv_hdmi_init();
}

hi_s32 HI_UNF_HDMI_DeInit(void)
{
    return hi_drv_hdmi_de_init();
}

hi_s32 HI_UNF_HDMI_Open(hi_unf_hdmi_id hdmi)
{
    return hi_drv_hdmi_open(hdmi);
}

hi_s32 HI_UNF_HDMI_SetAttr(hi_unf_hdmi_id hdmi, hi_unf_hdmi_attr *attr)
{
    return hi_drv_hdmi_set_attr(hdmi, (hi_drv_hdmi_attr*)attr);
}

hi_s32 HI_UNF_HDMI_Start(hi_unf_hdmi_id hdmi)
{
    return hi_drv_hdmi_start(hdmi);
}

hi_s32 HI_UNF_HDMI_Close(hi_unf_hdmi_id hdmi)
{
    return hi_drv_hdmi_close(hdmi);
}

#ifdef PHY_CRAFT_S28
hi_s32 hi_unf_hdmi_set_hw_spec(hi_hdmi_id hdmi, const hi_hdmi_hw_spec *hw_spec)
{
    hdmi_if_null_return(hw_spec, HI_FAILURE);

    return drv_hdmi_set_hw_spec(hdmi, hw_spec);
}

hi_s32 hi_unf_hdmi_get_hw_spec(hi_hdmi_id hdmi, hi_hdmi_hw_spec *hw_spec)
{
    hdmi_if_null_return(hw_spec, HI_FAILURE);

    return drv_hdmi_get_hw_spec(hdmi, hw_spec);
}

hi_s32 hi_unf_hdmi_set_mod_param(hi_hdmi_id hdmi, const hi_hdmi_mod_param *mod_param)
{
    hdmi_if_null_return(mod_param, HI_FAILURE);

    return drv_hdmi_set_mod_param(hdmi, mod_param);
}

hi_s32 hi_unf_hdmi_get_mod_param(hi_hdmi_id hdmi, hi_hdmi_mod_param *mod_param)
{
    hdmi_if_null_return(mod_param, HI_FAILURE);

    return drv_hdmi_get_mod_param(hdmi, mod_param);
}
#endif

