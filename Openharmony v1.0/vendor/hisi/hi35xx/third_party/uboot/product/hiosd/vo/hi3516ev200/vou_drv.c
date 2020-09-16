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
#include "vou_drv.h"
#include "hi_type.h"
#include "vou_reg.h"
#include "vou_def.h"
#include "vou_hal.h"
#include "vou_coef_org.h"

#define VO_DEV_MAX_NUM   1
#define VO_LAYER_MAX_NUM 1

#define VO_SD_VTTH_WATERLINE 100
#define VO_HD_VTTH_WATERLINE 240

#define VO_BACKGROUD_BLACK   0x8080
#define VO_BACKGROUD_GREEN   0x804D3A42
#define VO_BACKGROUD_WHITE   0x3fffffff
#define VO_BACKGROUD_DEFAULT VO_BACKGROUD_WHITE

#define max2(x, y)       ((x) > (y) ? (x) : (y))
#define min2(x, y)       ((x) < (y) ? (x) : (y))
#define clip_min(x, min) (((x) >= (min)) ? (x) : (min))

static hi_u32 rgb_to_yuv_full(hi_u32 rgb)
{
    hi_u16 y, u, v;
    hi_u16 r, g, b;
    hi_u16 py_temp, pcb_temp, pcr_temp;

    r = rgb_r(rgb);
    g = rgb_g(rgb);
    b = rgb_b(rgb);

    /* to calculate rgb to yc, the numbers is from algorithm, not magic numbers */
    py_temp = (hi_u16)(((r * 76 + g * 150 + b * 29) >> 8) * 4);
    pcb_temp = (hi_u16)(clip_min(((((b * 130 - r * 44) - g * 86) >> 8) + 128), 0) * 4);
    pcr_temp = (hi_u16)(clip_min(((((r * 130 - g * 109) - b * 21) >> 8) + 128), 0) * 4);

    /* value 0 - 1023 */
    y = max2(min2(py_temp, 1023), 0);
    u = max2(min2(pcb_temp, 1023), 0);
    v = max2(min2(pcr_temp, 1023), 0);

    return yuv(y, u, v);
}

/* vou interrupt mask type */
typedef enum {
    VO_INTMSK_NONE = 0,
    VO_INTMSK_DHD0_VTTHD1 = 0x1,
    VO_INTMSK_DHD0_VTTHD2 = 0x2,
    VO_INTMSK_DHD0_VTTHD3 = 0x4,
    VO_INTMSK_DHD0_UFINT = 0x8,

    VO_INTMSK_DHD1_VTTHD1 = 0x10,
    VO_INTMSK_DHD1_VTTHD2 = 0x20,
    VO_INTMSK_DHD1_VTTHD3 = 0x40,
    VO_INTMSK_DHD1_UFINT = 0x80,

    VO_INTMSK_DSD_VTTHD1 = 0x100,
    VO_INTMSK_DSD_VTTHD2 = 0x200,
    VO_INTMSK_DSD_VTTHD3 = 0x400,
    VO_INTMSK_DSD_UFINT = 0x800,

    VO_INTMSK_B0_ERR = 0x1000,
    VO_INTMSK_B1_ERR = 0x2000,
    VO_INTMSK_B2_ERR = 0x4000,

    VO_INTMSK_WBC_DHDOVER = 0x8000,

    VO_INTREPORT_ALL = 0xffffffff
} vo_int_mask;

typedef struct {
    hi_bool enable;
    hi_u32 bk_grd;
    vo_intf_type intf_type;
    vo_intf_sync out_sync;
    hal_disp_pixel_format pixel_fmt;
} hal_dev_config;

typedef struct {
    hi_u32 bk_grd;
} hal_layer_config;

typedef struct {
    hi_s32 luma;
    hi_s32 cont;
    hi_s32 hue;
    hi_s32 satu;
} hal_csc_value;

typedef struct {
    hi_u32 base_phys;
    hi_void *base_virt;
    hi_u32 hor;
    hi_u32 ver422;
    hi_u32 ver420;
    hi_u32 lut;
    hi_u32 gam;
    hi_u32 acc;
} hal_coef_addr;

vo_user_intfsync_info g_user_intfsync_info = {
    .dev_div = 1,
    .clk_reverse = HI_TRUE,
    .user_intf_sync_attr = {
        .clk_source = VO_CLK_SOURCE_LCDMCLK,
        .lcd_m_clk_div = 0xC5E41,
    }
};

/* user time default value */
hal_disp_syncinfo g_user_sync_timing = {
    .synm = 0,
    .iop = 1,
    .intfb = 1,
    .vact = 480,
    .vbb = 4,
    .vfb = 8,
    .hact = 320,
    .hbb = 8,
    .hfb = 38,
    .hmid = 1,
    .bvact = 240,
    .bvbb = 14,
    .bvfb = 9,
    .hpw = 4,
    .vpw = 4,
    .idv = 0,
    .ihs = 1,
    .ivs = 1,
};

hal_disp_syncinfo g_sync_timing[VO_OUTPUT_BUTT] = {
    /* synm, iop, itf,   vact, vbb,  vfb,  hact,  hbb,  hfb, hmid,bvact,bvbb, bvfb, hpw, vpw,idv, ihs, ivs */
    { 0, 0, 0, 288,  22, 2,  720,  132, 12,   1,    288, 23, 2, 126, 3,  0, 0, 0 }, /* 576I(PAL)  */
    { 0, 0, 0, 240,  18, 4,  720,  119, 19,   1,    240, 19, 4, 124, 3,  0, 0, 0 }, /* 480I(NTSC) */
    { 0, 1, 1, 1080, 41, 4,  1920, 192, 638,  1,    1,   1,  1, 44,  5,  0, 0, 0 }, /* 1080P@24Hz */
    { 0, 1, 1, 1080, 41, 4,  1920, 192, 528,  1,    1,   1,  1, 44,  5,  0, 0, 0 }, /* 1080P@25Hz */
    { 0, 1, 1, 1080, 41, 4,  1920, 192, 88,   1,    1,   1,  1, 44,  5,  0, 0, 0 }, /* 1080P@30Hz */
    { 0, 1, 1, 720,  25, 5,  1280, 260, 440,  1,    1,   1,  1, 40,  5,  0, 0, 0 }, /* 720P@50Hz */
    { 0, 1, 1, 720,  25, 5,  1280, 260, 110,  1,    1,   1,  1, 40,  5,  0, 0, 0 }, /* 720P@60Hz */
    { 0, 0, 1, 540,  20, 2,  1920, 192, 528,  1128, 540, 21, 2, 44,  5,  0, 0, 0 }, /* 1080I@50Hz */
    { 0, 0, 1, 540,  20, 2,  1920, 192, 88,   908,  540, 21, 2, 44,  5,  0, 0, 0 }, /* 1080I@60Hz */
    { 0, 1, 1, 1080, 41, 4,  1920, 192, 528,  1,    1,   1,  1, 44,  5,  0, 0, 0 }, /* 1080P@50Hz */
    { 0, 1, 1, 1080, 41, 4,  1920, 192, 88,   1,    1,   1,  1, 44,  5,  0, 0, 0 }, /* 1080P@60Hz */
    { 1, 1, 1, 576,  44, 5,  720,  132, 12,   1,    1,   1,  1, 64,  5,  0, 0, 0 }, /* 576P@50Hz */
    { 1, 1, 1, 480,  36, 9,  720,  122, 16,   1,    1,   1,  1, 62,  6,  0, 0, 0 }, /* 480P@60Hz */
    { 1, 1, 2, 600,  27, 1,  800,  216, 40,   1,    1,   1,  1, 128, 4,  0, 0, 0 }, /* 800*600@60Hz VGA@60Hz */
    { 1, 1, 2, 768,  35, 3,  1024, 296, 24,   1,    1,   1,  1, 136, 6,  0, 1, 1 }, /* 1024x768@60Hz */
    { 1, 1, 2, 1024, 41, 1,  1280, 360, 48,   1,    1,   1,  1, 112, 3,  0, 0, 0 }, /* 1280x1024@60Hz */
    { 1, 1, 2, 768,  27, 3,  1366, 356, 70,   1,    1,   1,  1, 143, 3,  0, 0, 0 }, /* 1366x768@60Hz */
    { 1, 1, 2, 900,  31, 3,  1440, 384, 80,   1,    1,   1,  1, 152, 6,  0, 1, 0 }, /* 1440x900@60Hz */
    { 1, 1, 2, 800,  28, 3,  1280, 328, 72,   1,    1,   1,  1, 128, 6,  0, 1, 0 }, /* 1280*800@60Hz VGA@60Hz */
    { 1, 1, 2, 1200, 49, 1,  1600, 496, 64,   1,    1,   1,  1, 192, 3,  0, 0, 0 }, /* 1600*1200@60Hz */
    { 1, 1, 2, 1050, 36, 3,  1680, 456, 104,  1,    1,   1,  1, 176, 6,  0, 1, 0 }, /* 1680*1050@60Hz */
    /* 1920*1200@60Hz CVT (reduced blanking) */
    { 1, 1, 2, 1200, 32, 3,  1920, 112, 48,   1,    1,   1,  1, 32,  6,  0, 0, 1 },
    { 1, 1, 2, 480,  35, 10, 640,  144, 16,   1,    1,   1,  1, 96,  2,  0, 1, 1 }, /* 640*480@60Hz CVT */
    { 0, 0, 0, 288,  22, 2,  960,  176, 16,   1,    288, 23, 2, 168, 3,  0, 0, 0 }, /* 960H(PAL) */
    { 0, 0, 0, 240,  18, 4,  960,  163, 21,   1,    240, 19, 4, 168, 3,  0, 0, 0 }, /* 960H(NTSC) */
    { 0, 1, 1, 2160, 72, 8,  1920, 192, 88,   1,    1,   1,  1, 44,  5,  0, 0, 0 }, /* 1920*2160@30Hz */
    { 1, 1, 2, 1440, 39, 2,  2560, 112, 48,   1,    1,   1,  1, 32,  5,  0, 0, 0 }, /* 2560*1440@30Hz */
    { 1, 1, 2, 1440, 39, 2,  2560, 112, 48,   1,    1,   1,  1, 32,  5,  0, 0, 0 }, /* 2560*1440@60Hz */
    /* 2560*1600@60Hz CVT (reduced blanking) */
    { 0, 1, 2, 1600, 43, 3,  2560, 112, 48,   1,    1,   1,  1, 32,  6,  0, 0, 1 },
    { 0, 1, 1, 2160, 82, 8,  3840, 384, 1276, 1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 3840*2160@24Hz */
    { 0, 1, 1, 2160, 82, 8,  3840, 384, 1056, 1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 3840*2160@25Hz */
    { 0, 1, 1, 2160, 82, 8,  3840, 384, 176,  1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 3840*2160@30Hz */
    { 0, 1, 1, 2160, 82, 8,  3840, 384, 1056, 1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 3840*2160@50Hz */
    { 0, 1, 1, 2160, 82, 8,  3840, 384, 176,  1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 3840*2160@60Hz */
    { 0, 1, 1, 2160, 82, 8,  4096, 384, 1020, 1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 4096x2160@24 */
    { 0, 1, 1, 2160, 82, 8,  4096, 216, 968,  1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 4096x2160@25 */
    { 0, 1, 1, 2160, 82, 8,  4096, 216, 88,   1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 4096x2160@30 */
    { 0, 1, 1, 2160, 82, 8,  4096, 216, 968,  1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 4096x2160@50 */
    { 0, 1, 1, 2160, 82, 8,  4096, 216, 88,   1,    1,   1,  1, 88,  10, 0, 0, 0 }, /* 4096x2160@60 */
    { 0, 1, 1, 240,  15, 9,  320,  65,  7,    1,    240, 14, 9, 1,   1,  0, 0, 0 }, /* 320X240@60  8bit LCD */
    { 0, 1, 1, 240,  2,  2,  320,  5,   10,   1,    1,   1,  1, 10,  1,  0, 0, 0 }, /* 320X240@50  6bit LCD */
    { 0, 1, 1, 320,  10, 4,  240,  30,  10,   1,    1,   1,  1, 10,  2,  0, 0, 0 }, /* 240X320@50  6bit LCD */
    { 0, 1, 1, 320,  2,  2,  240,  20,  10,   1,    1,   1,  1, 2,   1,  0, 0, 0 }, /* 240X320@60 16bit LCD */
    { 0, 1, 1, 600,  23, 12, 800,  210, 46,   1,    1,   1,  1, 2,   1,  0, 0, 0 }, /* 800X600@60 24bit LCD */
    { 0, 1, 1, 1280, 24, 8,  720,  123, 99,   1,    1,   1,  1, 24,  4,  0, 0, 0 }, /* 720 x1280 at 60 hz */
    { 0, 1, 1, 1920, 36, 16, 1080, 28,  130,  1,    1,   1,  1, 8,   10, 0, 0, 0 }, /* 1080 x1920 at 60 hz */
    { 0, 1, 1, 4320, 64, 16, 7680, 768, 552,  1,    1,   1,  1, 176, 20, 0, 0, 0 }, /* 7680x4320@30 */
    {}                                                                              /* user */
};

static hal_dev_config g_hal_dev_cfg[VO_DEV_MAX_NUM] = {
    {
        .enable = HI_FALSE,
        .bk_grd = VO_BACKGROUD_DEFAULT,
        .intf_type = VO_INTF_BT1120 | VO_INTF_LCD,
        .out_sync = VO_OUTPUT_1080P30,
        .pixel_fmt = HAL_INPUTFMT_Y_CB_CR_SEMIPLANAR_422,
    }
};

hi_void vo_drv_board_init(hi_void)
{
    hal_vo_init();
    vo_drv_default_setting();
}

hi_void vo_drv_int_reg_up_mode(vo_hal_layer vo_layer, vo_int_mode int_mode)
{
    hal_video_set_layer_up_mode(vo_layer, int_mode);
    return;
}

hi_void vo_drv_set_dev_intf_type(hi_s32 vo_dev, vo_intf_type intf_type)
{
    g_hal_dev_cfg[vo_dev].intf_type = intf_type;
    return;
}

hi_void vo_drv_set_dev_bk_grd(hi_s32 vo_dev, hi_u32 bg_color)
{
    g_hal_dev_cfg[vo_dev].bk_grd = bg_color;
    return;
}

hi_void vo_drv_set_dev_out_sync(hi_s32 vo_dev, vo_intf_sync vo_out_mode)
{
    g_hal_dev_cfg[vo_dev].out_sync = vo_out_mode;
    return;
}

/* interrupt relative */
hi_void vo_drv_dev_int_enable(vo_hal_dev vo_dev, hi_bool enable)
{
    vo_int_mask int_type;

    switch (vo_dev) {
        case VO_DEV_DHD0:
            int_type = VO_INTMSK_DHD0_VTTHD1;
            break;

        default:
            return;
    }

    if (enable == HI_TRUE) {
        hal_disp_set_int_mask(int_type);
    } else {
        hal_disp_clr_int_mask(int_type);
    }

    return;
}

hi_void vo_drv_int_set_mode(hi_s32 vo_dev, vo_int_mode int_mode)
{
    hal_disp_set_vt_thd_mode(vo_dev, int_mode);
    return;
}

hi_void vo_drv_layer_enable(vo_hal_layer vo_layer, hi_bool enable)
{
    hal_layer_enable_layer(vo_layer, enable);
    return;
}

hi_void vo_drv_def_layer_bind_dev(hi_void)
{
    hal_cbm_set_cbm_mixer_prio(HAL_DISP_LAYER_VHD0, VO_MIX_PRIO0, HAL_CBMMIX1);
    hal_cbm_set_cbm_mixer_prio(HAL_DISP_LAYER_GFX0, VO_MIX_PRIO1, HAL_CBMMIX1);
    return;
}

hi_void vo_drv_set_dev_clk(vo_hal_dev vo_dev)
{
    /* the numbers below is the default value of the register. */
    hi_bool clk_en = HI_FALSE;
    hi_u32 vdp_out_clk_sel = 0x0;
    hi_u32 vdp_hd_clk_sel = 0x0;
    hi_u32 lcd_mclk_div = 0x00FFFFF;
    switch (g_hal_dev_cfg[vo_dev].out_sync) {
        /* the number is pll register config, calculate from out sync */
        case VO_OUTPUT_PAL:
        case VO_OUTPUT_NTSC:
        case VO_OUTPUT_576P50:
        case VO_OUTPUT_480P60: {
            /* 27MHz */
            vdp_out_clk_sel = 0xa;
            break;
        }

        case VO_OUTPUT_1080P24:
        case VO_OUTPUT_1080P25:
        case VO_OUTPUT_1080P30:
        case VO_OUTPUT_720P50:
        case VO_OUTPUT_720P60:
        case VO_OUTPUT_1080I50:
        case VO_OUTPUT_1080I60:
        case VO_OUTPUT_720x1280_60: {
            /* 74.25MHz */
            vdp_out_clk_sel = 0x8;
            break;
        }

        case VO_OUTPUT_1080P50:
        case VO_OUTPUT_1080P60:
        case VO_OUTPUT_1920x2160_30:
        case VO_OUTPUT_1080x1920_60: {
            /* 148.5MHz */
            vdp_out_clk_sel = 0x0;
            break;
        }

        case VO_OUTPUT_640x480_60: {
            /* 25.175MHz */
            vdp_out_clk_sel = 0x5;
            vdp_hd_clk_sel = 0x0;
            lcd_mclk_div = 0x1cac08;
            clk_en = HI_TRUE;
            break;
        }

        case VO_OUTPUT_800x600_60: {
            /* 40MHz */
            vdp_out_clk_sel = 0x5;
            vdp_hd_clk_sel = 0x0;
            lcd_mclk_div = 0x2d45b3;
            clk_en = HI_TRUE;
            break;
        }

        case VO_OUTPUT_1024x768_60: {
            /* 65MHz */
            vdp_out_clk_sel = 0x5;
            vdp_hd_clk_sel = 0x0;
            lcd_mclk_div = 0x49f369;
            clk_en = HI_TRUE;
            break;
        }

        case VO_OUTPUT_1280x1024_60: {
            /* 108MHz */
            vdp_out_clk_sel = 0x5;
            vdp_hd_clk_sel = 0x0;
            lcd_mclk_div = 0x7ad6ef;
            clk_en = HI_TRUE;
            break;
        }

        case VO_OUTPUT_1366x768_60: {
            /* 85.5MHz */
            vdp_out_clk_sel = 0x5;
            vdp_hd_clk_sel = 0x0;
            lcd_mclk_div = 0x619f57;
            clk_en = HI_TRUE;
            break;
        }

        case VO_OUTPUT_1280x800_60: {
            /* 83.5MHz */
            vdp_out_clk_sel = 0x5;
            vdp_hd_clk_sel = 0x0;
            lcd_mclk_div = 0x5f4e44;
            clk_en = HI_TRUE;
            break;
        }

        case VO_OUTPUT_320x240_60: {
            /* lcd clk config */
            vdp_out_clk_sel = 0x5;
            vdp_hd_clk_sel = 0x3;
            lcd_mclk_div = 0x1c4255;
            clk_en = HI_TRUE;
            break;
        }

        case VO_OUTPUT_320x240_50: {
            /* lcd clk config */
            vdp_out_clk_sel = 0x5;
            vdp_hd_clk_sel = 0x2;
            lcd_mclk_div = 0xdf346;
            clk_en = HI_TRUE;
            break;
        }

        case VO_OUTPUT_240x320_50: {
            /* lcd clk config */
            vdp_out_clk_sel = 0x5;
            vdp_hd_clk_sel = 0x2;
            lcd_mclk_div = 0xff5f3;
            clk_en = HI_TRUE;
            break;
        }

        case VO_OUTPUT_240x320_60: {
            /* lcd clk config */
            vdp_out_clk_sel = 0x5;
            vdp_hd_clk_sel = 0x0;
            lcd_mclk_div = 0x5f8d2;
            clk_en = HI_TRUE;
            break;
        }

        case VO_OUTPUT_USER: {
            if (vo_dev == 0) {
                if (g_user_intfsync_info.user_intf_sync_attr.clk_source == VO_CLK_SOURCE_LCDMCLK) {
                    /* LCD_MCLK_DIV */
                    vdp_out_clk_sel = 0x5; /* 0x5 register value for lcd */
                    sys_hal_vo_out_clk_sel(vdp_out_clk_sel);
                    /* configuring the clock */
                    sys_hal_lcd_mclk_div(g_user_intfsync_info.user_intf_sync_attr.lcd_m_clk_div);
                    sys_hal_vo_lcd_clk_en(HI_TRUE);
                } else if (g_user_intfsync_info.user_intf_sync_attr.clk_source == VO_CLK_SOURCE_PLL) {
                    printf("vo_dev(%d) clk source %d illegal.\n", vo_dev,
                           g_user_intfsync_info.user_intf_sync_attr.clk_source);
                }
            } else {
                printf("VO dev %d is illegal\n", vo_dev);
            }

            sys_hal_vo_hd_out_pctrl(g_user_intfsync_info.clk_reverse);
            sys_hal_vo_hd0_div_mode(g_user_intfsync_info.dev_div - 1);

            if ((VO_INTF_LCD_6BIT & g_hal_dev_cfg[vo_dev].intf_type) ||
                (VO_INTF_LCD_8BIT & g_hal_dev_cfg[vo_dev].intf_type)) {
                if (g_user_intfsync_info.dev_div == 3) { /* div 3 */
                    hal_disp_set_lcd_serial_perd(0);
                } else {
                    hal_disp_set_lcd_serial_perd(1);
                }
            }
            return;
            break;
        }

        default: {
            return;
        }
    }

    sys_hal_vo_lcd_clk_en(clk_en);
    sys_hal_lcd_mclk_div(lcd_mclk_div);
    sys_hal_vo_hd0_div_mode(vdp_hd_clk_sel);
    sys_hal_vo_out_clk_sel(vdp_out_clk_sel);

    return;
}

static hi_bool vo_drv_get_dither_io_mode(hi_u32 dither_io_mode,
    hi_u32 *dither_mode,
    hi_u32 *i_data_width_dither,
    hi_u32 *o_data_width_dither)
{
    if (dither_io_mode == DITHER_IO_MODE_12_10) {
        *dither_mode           = DITHER_MODE_10BIT;
        *i_data_width_dither   = DITHER_IWIDTH_MODE_12BIT;
        *o_data_width_dither   = DITHER_OWIDTH_MODE_10BIT;
    } else if (dither_io_mode == DITHER_IO_MODE_12_8) {
        *dither_mode           = DITHER_MODE_8BIT;
        *i_data_width_dither   = DITHER_IWIDTH_MODE_12BIT;
        *o_data_width_dither   = DITHER_OWIDTH_MODE_8BIT;
    } else if (dither_io_mode == DITHER_IO_MODE_10_8) {
        *dither_mode           = DITHER_MODE_8BIT;
        *i_data_width_dither   = DITHER_IWIDTH_MODE_10BIT;
        *o_data_width_dither   = DITHER_OWIDTH_MODE_8BIT;
    } else if (dither_io_mode == DITHER_IO_MODE_10_6) {
        *dither_mode           = DITHER_MODE_8BIT;
        *i_data_width_dither   = DITHER_IWIDTH_MODE_10BIT;
        *o_data_width_dither   = DITHER_OWIDTH_MODE_6BIT;
    } else if (dither_io_mode == DITHER_IO_MODE_9_6) {
        *dither_mode           = DITHER_MODE_8BIT;
        *i_data_width_dither   = DITHER_IWIDTH_MODE_9BIT;
        *o_data_width_dither   = DITHER_OWIDTH_MODE_6BIT;
    } else if (dither_io_mode == DITHER_IO_MODE_8_6) {
        *dither_mode           = DITHER_MODE_8BIT;
        *i_data_width_dither   = DITHER_IWIDTH_MODE_8BIT;
        *o_data_width_dither   = DITHER_OWIDTH_MODE_6BIT;
    } else if (dither_io_mode == 0) {
        *dither_mode           = DITHER_MODE_8BIT;
        *i_data_width_dither   = DITHER_IWIDTH_MODE_8BIT;
        *o_data_width_dither   = DITHER_OWIDTH_MODE_6BIT;
    } else {
        return HI_FALSE;
    }

    return HI_TRUE;
}

static hi_void vo_drv_get_dither_sed(hal_disp_dihter_sed *tmp_sed)
{
    /* number is from algorithm, not magic number */
    tmp_sed->dither_sed_y0 = 2147483647;
    tmp_sed->dither_sed_u0 = 2147482647;
    tmp_sed->dither_sed_v0 = 2147481647;
    tmp_sed->dither_sed_w0 = 2147480647;
    tmp_sed->dither_sed_y1 = tmp_sed->dither_sed_y0;
    tmp_sed->dither_sed_u1 = tmp_sed->dither_sed_u0;
    tmp_sed->dither_sed_v1 = tmp_sed->dither_sed_v0;
    tmp_sed->dither_sed_w1 = tmp_sed->dither_sed_w0;
    tmp_sed->dither_sed_y2 = tmp_sed->dither_sed_y0;
    tmp_sed->dither_sed_u2 = tmp_sed->dither_sed_u0;
    tmp_sed->dither_sed_v2 = tmp_sed->dither_sed_v0;
    tmp_sed->dither_sed_w2 = tmp_sed->dither_sed_w0;
    tmp_sed->dither_sed_y3 = tmp_sed->dither_sed_y0;
    tmp_sed->dither_sed_u3 = tmp_sed->dither_sed_u0;
    tmp_sed->dither_sed_v3 = tmp_sed->dither_sed_v0;
    tmp_sed->dither_sed_w3 = tmp_sed->dither_sed_w0;

    return;
}

hi_void vo_drv_set_dev_dither_mode(vo_hal_dev vo_dev, vdp_dither_mode drv_dither_mode, vdp_dither_cfg *cfg)
{
    hal_disp_outputchannel vo_channel;
    hal_disp_dihter_sed dither_sed;
    hi_u32 dither_round_unlim;
    hi_u32 i_data_width_dither = 0;
    hi_u32 o_data_width_dither = 0;
    hi_u32 dither_en;
    hi_u32 dither_io_mode;
    hi_u32 dither_mode = 0;
    hi_u32 dither_round;
    hi_u32 dither_domain_mode;
    hi_u32 dither_tap_mode;
    hi_u32 dither_thr_max = 0;
    hi_u32 dither_thr_min = 0;
    hi_bool ret = HI_FALSE;

    dither_en = cfg->dither_en;
    dither_round = cfg->dither_round;
    dither_round_unlim = cfg->dither_round_unlim;
    dither_domain_mode = cfg->dither_domain_mode;
    dither_tap_mode = cfg->dither_tap_mode;
    dither_io_mode = cfg->dither_io_mode;

    ret = vo_drv_get_dither_io_mode(dither_io_mode, &dither_mode, &i_data_width_dither, &o_data_width_dither);
    if (ret == HI_FALSE) {
        return;
    }

    if (drv_dither_mode == VDP_DITHER_MODE_TYP) {
        vo_drv_get_dither_sed(&dither_sed);
        dither_thr_max = 60000; /* 60000 max */
        dither_thr_min = 120; /* 120 min */
    } else {
        return;
    }

    vo_channel = HAL_DISP_CHANNEL_DHD0;
    hal_disp_set_dither_round_unlim(vo_channel, dither_round_unlim);
    hal_disp_set_dither_data_in_out(vo_channel, i_data_width_dither, o_data_width_dither);
    hal_disp_set_dither_en(vo_channel, dither_en);
    hal_disp_set_dither_mode(vo_channel, dither_mode);
    hal_disp_set_dither_round(vo_channel, dither_round);
    hal_disp_set_dither_domain_mode(vo_channel, dither_domain_mode);
    hal_disp_set_dither_tap_mode(vo_channel, dither_tap_mode);
    hal_disp_set_dither_sed(vo_channel, &dither_sed);
    hal_disp_set_dither_thr_min_max(vo_channel, dither_thr_min, dither_thr_max);
}

hi_void vo_drv_set_dev_dither_cfg(vo_hal_dev vo_dev, hi_u32 in_bit_widht, hi_u32 out_bit_widht)
{
    vdp_dither_cfg dither_cfg;

    if ((in_bit_widht == 10) && (out_bit_widht == 8)) { /* 10bit 8bit */
        /* the numbers below are register config, not magic number. */
        dither_cfg.dither_en = 1;
        dither_cfg.dither_round = 1;
        dither_cfg.dither_round_unlim = 1;
        dither_cfg.dither_domain_mode = 1;
        dither_cfg.dither_tap_mode = 1;
        dither_cfg.dither_io_mode = DITHER_IO_MODE_12_8;

        vo_drv_set_dev_dither_mode(vo_dev, VDP_DITHER_MODE_TYP, &dither_cfg);
        hal_disp_set_dither_en(vo_dev, HI_TRUE);
        hal_disp_set_dither_data_in_out(vo_dev, 0x4, 0x5);  /* 4:12bit 5:10bit;3:8bit */
    } else if ((in_bit_widht == 10) && (out_bit_widht == 6)) { /* 10bit 6bit */
        /* the numbers below are register config, not magic number. */
        dither_cfg.dither_en = 1;
        dither_cfg.dither_round = 0;
        dither_cfg.dither_round_unlim = 1;
        dither_cfg.dither_domain_mode = 1;
        dither_cfg.dither_tap_mode = 1;
        dither_cfg.dither_io_mode = DITHER_IO_MODE_10_6;
        vo_drv_set_dev_dither_mode(vo_dev, VDP_DITHER_MODE_TYP, &dither_cfg);
        hal_disp_set_dither_en(vo_dev, HI_TRUE);
        hal_disp_set_dither_data_in_out(vo_dev, 0x2, 0x1); /* 4:12bit 5:10bit;3:8bit */
    } else if (((in_bit_widht == 10) && (out_bit_widht == 10)) || /* 10bit */
               ((in_bit_widht == 8) && (out_bit_widht == 8))) { /* 8bit */
        hal_disp_set_dither_en(vo_dev, HI_FALSE);
    }
}

hi_u32 vo_drv_get_dev_vtth(vo_hal_dev vo_dev)
{
    hi_u32 dev_vtth;

    switch (g_hal_dev_cfg[vo_dev].out_sync) {
        case VO_OUTPUT_3840x2160_60:
        case VO_OUTPUT_3840x2160_50:
        case VO_OUTPUT_4096x2160_60:
        case VO_OUTPUT_4096x2160_50:
            dev_vtth = 4 * VO_HD_VTTH_WATERLINE; /* 4 times of default */
            break;

        case VO_OUTPUT_2560x1600_60:
        case VO_OUTPUT_3840x2160_24:
        case VO_OUTPUT_3840x2160_25:
        case VO_OUTPUT_3840x2160_30:
        case VO_OUTPUT_4096x2160_24:
        case VO_OUTPUT_4096x2160_25:
        case VO_OUTPUT_4096x2160_30:
            dev_vtth = 2 * VO_HD_VTTH_WATERLINE; /* 2 times of default */
            break;

        default:
            dev_vtth = VO_HD_VTTH_WATERLINE;
    }

    return dev_vtth;
}

/* turn on clk */
hi_void vo_drv_set_all_crg_clk(hi_bool clk_en)
{
    hi_bool vo_clk_en = clk_en;

    sys_hal_vo_dev_clk_en(0, vo_clk_en); /* dev 0 */
    sys_hal_vo_core_clk_en(0, vo_clk_en); /* dev 0 */
    sys_hal_vo_cfg_clk_en(vo_clk_en);
    sys_hal_vo_apb_clk_en(vo_clk_en);
    sys_hal_vo_bus_clk_en(vo_clk_en);
    return;
}

hi_u32 vo_drv_get_dev_intf_type(vo_hal_dev vo_dev)
{
    return g_hal_dev_cfg[vo_dev].intf_type;
}

void vo_drv_set_cbm_bkg(hi_s32 vo_dev)
{
    hal_disp_bkcolor bkg;
    vo_intf_type intf_type;
    hi_u32 yuv_bk_grd = 0;
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];

    intf_type = hal_dev_cfg->intf_type;

    if ((VO_INTF_LCD_6BIT & intf_type) ||
        (VO_INTF_LCD_8BIT & intf_type) ||
        (VO_INTF_LCD_16BIT & intf_type)) {
        bkg.bkg_y = rgb_r(hal_dev_cfg->bk_grd);
        bkg.bkg_cb = rgb_g(hal_dev_cfg->bk_grd);
        bkg.bkg_cr = rgb_b(hal_dev_cfg->bk_grd);
        /* for 30bit register. */
        bkg.bkg_y = bkg.bkg_y << 2; /* 2 to turn 8 to 10 value */
        bkg.bkg_cb = bkg.bkg_cb << 2; /* 2 to turn 8 to 10 value */
        bkg.bkg_cr = bkg.bkg_cr << 2; /* 2 to turn 8 to 10 value */
    } else {
        yuv_bk_grd = rgb_to_yuv_full(hal_dev_cfg->bk_grd);
        bkg.bkg_y = yuv_y(yuv_bk_grd);
        bkg.bkg_cb = yuv_u(yuv_bk_grd);
        bkg.bkg_cr = yuv_v(yuv_bk_grd);
    }

    hal_cbm_set_cbm_bkg(HAL_CBMMIX1, &bkg);
}

void vo_drv_get_intf_property(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, hal_disp_syncinv *inv)
{
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];

    if (hal_dev_cfg->out_sync != VO_OUTPUT_USER) {
        memcpy(sync_info, &g_sync_timing[hal_dev_cfg->out_sync], sizeof(hal_disp_syncinfo));
    } else {
        memcpy(sync_info, &g_user_sync_timing, sizeof(hal_disp_syncinfo));
    }

    /* the numbers below are register config, not magic number. */
    inv->hs_inv = sync_info->ihs ? 1 : 0;
    inv->vs_inv = sync_info->ivs ? 1 : 0;
    inv->dv_inv = sync_info->idv ? 1 : 0;
}

void vo_drv_set_intf_bt1120_cfg(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, hal_disp_syncinv *inv)
{
    sys_hal_vo_bt_clk_en(HI_TRUE);

    hal_disp_set_intf_mux_sel(vo_dev, VO_INTF_BT1120);
    hal_intf_bt_set_dfir_en(0x1);  /* 0x1 enable */
}

void vo_drv_set_intf_bt656_cfg(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, hal_disp_syncinv *inv, hi_u32 *div_mod)
{
    sys_hal_vo_bt_clk_en(HI_TRUE);

    /* the numbers below are register config, not magic number. */
    hal_disp_set_intf_mux_sel(vo_dev, VO_INTF_BT656);
    hal_intf_bt_set_dfir_en(0x1);
    *div_mod = 1;
}

void vo_drv_set_intf_lcd_cfg(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, hal_disp_syncinv *inv, hi_u32 *div_mod)
{
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];
    U_INTF_LCD_CTRL LCD_CTRL;
    vo_intf_type intf_type;
    hi_u32 data_mode = 0x0;
    vo_intf_sync out_sync;

    intf_type = hal_dev_cfg->intf_type;
    out_sync = hal_dev_cfg->out_sync;

    sys_hal_vo_bt_clk_en(HI_TRUE);
    sys_hal_vo_lcd_clk_en(HI_TRUE);
    hal_disp_set_intf_mux_sel(vo_dev, intf_type);

    if (VO_INTF_LCD_8BIT & intf_type) {
        /* the numbers below are register config, not magic number. */
        *div_mod = 3; /* 3 register config */
        data_mode = 1;
        LCD_CTRL.bits.hdmi_mode = 1;
        LCD_CTRL.bits.lcd_serial_mode = 1;
        LCD_CTRL.bits.lcd_serial_perd = 1;
        LCD_CTRL.bits.lcd_parallel_order = 0;
        LCD_CTRL.bits.lcd_data_inv = 0;
        LCD_CTRL.bits.lcd_parallel_mode = 1;  /* 0:RGB565, 1:RGB888 */
    } else if (VO_INTF_LCD_6BIT & intf_type) {
        /* the numbers below are register config, not magic number. */
        *div_mod = 2; /* 2 register config */
        data_mode = 0;

        LCD_CTRL.bits.lcd_serial_mode = 1;
        LCD_CTRL.bits.lcd_serial_perd = 0;
        LCD_CTRL.bits.lcd_parallel_order = 0;
        LCD_CTRL.bits.lcd_data_inv = 0;
        LCD_CTRL.bits.lcd_parallel_mode = 0;
    } else if (VO_INTF_LCD_16BIT & intf_type) {
        /* the numbers below are register config, not magic number. */
        *div_mod = 0;
        data_mode = 2; /* 2 register config */

        LCD_CTRL.bits.lcd_serial_mode = 0;
        LCD_CTRL.bits.lcd_serial_perd = 0;
        LCD_CTRL.bits.lcd_parallel_order = 0;
        LCD_CTRL.bits.lcd_data_inv = 0;
        LCD_CTRL.bits.lcd_parallel_mode = 1;
    }

    sys_hal_lcd_data_mode(data_mode);
    hal_disp_set_intf_ctrl(intf_type, &(LCD_CTRL.u32));

    if (out_sync != VO_OUTPUT_USER) {
        hal_disp_set_lcd_serial_perd(LCD_CTRL.bits.lcd_serial_perd);
    }
}

void vo_drv_set_intf_cfg(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, hal_disp_syncinv *inv, hi_u32 *div_mod)
{
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];
    vo_intf_type intf_type;

    intf_type = hal_dev_cfg->intf_type;

    if (VO_INTF_BT1120 & hal_dev_cfg->intf_type) {
        vo_drv_set_intf_bt1120_cfg(vo_dev, sync_info, inv);
    }

    if (VO_INTF_BT656 & intf_type) {
        vo_drv_set_intf_bt656_cfg(vo_dev, sync_info, inv, div_mod);
    }

    if ((VO_INTF_LCD_6BIT & intf_type) ||
        (VO_INTF_LCD_8BIT & intf_type) ||
        (VO_INTF_LCD_16BIT & intf_type)) {
        vo_drv_set_intf_lcd_cfg(vo_dev, sync_info, inv, div_mod);
    }
}

void vo_drv_set_dev_multichn(hi_s32 vo_dev)
{
    hal_multi_chn multi_chn_en = HAL_MULTICHN_EN_1P1C;
    hal_disp_set_dev_multi_chn_en(vo_dev, multi_chn_en);
}

void vo_drv_set_dev_clip_by_intf(hi_s32 vo_dev)
{
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];
    vo_intf_type intf_type;

    intf_type = hal_dev_cfg->intf_type;

    if (VO_INTF_BT1120 & intf_type) {
        const hal_disp_clip clip_data = { 0x40, 0x40, 0x40, 0x3ac, 0x3c0, 0x3c0 }; /* clip register config */
        hal_disp_set_intf_clip(VO_INTF_BT1120, HI_TRUE, &clip_data);
    }

    if (VO_INTF_BT656 & intf_type) {
        const hal_disp_clip clip_data = { 0x40, 0x40, 0x40, 0x3ac, 0x3c0, 0x3c0 }; /* clip register config */
        hal_disp_set_intf_clip(VO_INTF_BT656, HI_TRUE, &clip_data);
    }
}
void vo_drv_set_dev_int_mode(hi_s32 vo_dev, hal_disp_syncinfo *sync_info)
{
    vo_int_mode int_mode;

    if (sync_info->iop == 0) {
        int_mode = VO_INT_MODE_FIELD;
    } else {
        int_mode = VO_INT_MODE_FRAME;
    }

    vo_drv_int_set_mode(vo_dev, int_mode);
    vo_drv_int_reg_up_mode(vo_dev, int_mode);
}

void vo_drv_set_dev_out_pctrl(hi_s32 vo_dev)
{
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];
    vo_intf_sync out_sync;
    hi_bool clk_reverse = HI_TRUE;

    out_sync = hal_dev_cfg->out_sync;

    if (out_sync != VO_OUTPUT_USER) {
        sys_hal_vo_hd_out_pctrl(clk_reverse);
    }
}

void vo_drv_set_dev_div_mod(hi_s32 vo_dev, hi_u32 div_mod)
{
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];
    vo_intf_sync out_sync;

    out_sync = hal_dev_cfg->out_sync;

    if (out_sync != VO_OUTPUT_USER) {
        if (vo_dev == 0) {
            sys_hal_vo_hd0_div_mode(div_mod);
        }
    }
}

void vo_drv_set_dev_dither(hi_s32 vo_dev)
{
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];
    vo_intf_type intf_type;

    intf_type = hal_dev_cfg->intf_type;
    if ((VO_INTF_LCD_6BIT & intf_type) ||
        (VO_INTF_LCD_16BIT & intf_type)) {
        vo_drv_set_dev_dither_cfg(vo_dev, 10, 6); /* 10 to 6 */
    } else {
        vo_drv_set_dev_dither_cfg(vo_dev, 10, 8); /* 10 to 8 */
    }
}

hi_void vo_drv_open(hi_s32 vo_dev)
{
    hal_disp_syncinfo sync_info;
    hi_u16 vtth_line;
    hal_disp_syncinv inv = {0};
    hi_u32 div_mode = 0;

    vo_drv_set_all_crg_clk(HI_TRUE);
    hal_disp_set_intf_enable(vo_dev, HI_FALSE);

    sys_hal_vo_dev_clk_en(0, HI_TRUE);
    sys_hal_vo_out_clk_en(0, HI_TRUE);

    vo_drv_set_cbm_bkg(vo_dev);

    /* set interface property */
    vo_drv_get_intf_property(vo_dev, &sync_info, &inv);

    vo_drv_set_intf_cfg(vo_dev, &sync_info, &inv, &div_mode);

    vo_drv_set_dev_out_pctrl(vo_dev);
    vo_drv_set_dev_div_mod(vo_dev, div_mode);

    hal_disp_set_intf_sync(vo_dev, &sync_info, &inv);
    vo_drv_set_dev_multichn(vo_dev);

    /* set clip */
    vo_drv_set_dev_clip_by_intf(vo_dev);

    vo_drv_set_dev_int_mode(vo_dev, &sync_info);

    vtth_line = sync_info.vact + sync_info.vfb + sync_info.vbb - 1 - vo_drv_get_dev_vtth(vo_dev);
    hal_disp_set_vt_thd(vo_dev, vtth_line);

    /* dither config */
    vo_drv_set_dev_dither(vo_dev);

    hal_disp_set_intf_enable(vo_dev, HI_TRUE);
    vo_drv_dev_int_enable(vo_dev, HI_TRUE);
    hal_disp_set_reg_up(vo_dev);
    g_hal_dev_cfg[vo_dev].enable = HI_TRUE;

    return;
}

hi_void vo_drv_close(hi_s32 vo_dev)
{
    hi_u32 i;

    hal_disp_set_intf_enable(vo_dev, HI_FALSE);
    hal_disp_set_reg_up(vo_dev);

    hal_disp_set_intf_mux_sel(vo_dev, HAL_DISP_INTF_BUTT);

    g_hal_dev_cfg[vo_dev].enable = HI_FALSE;

    for (i = 0; i < VO_DEV_MAX_NUM; i++) {
        if (g_hal_dev_cfg[vo_dev].enable) {
            break;
        }
    }

    if (i == VO_DEV_MAX_NUM) {
        vo_drv_set_all_crg_clk(HI_FALSE);
    }

    return;
}

hi_void vo_drv_default_setting(hi_void)
{
    hal_layer_set_layer_galpha(HAL_DISP_LAYER_VHD0, 255);  /* 255 max alpha */
    vo_drv_layer_enable(HAL_DISP_LAYER_VHD0, HI_FALSE);

    return;
}

hi_void vo_drv_func_get_cvfir_pq_cfg(vo_zme_ds_info *ds_info, vo_zme_mode zme_mode,
                                     vo_zme_comm_pq_cfg *comm_pq_cfg)
{
    hi_u32 zme_vprec;
    /* the zme num is from algorithm, not magic num */
    if (zme_mode == VO_ZME_TYP) {
        zme_vprec = ds_info->zme_vprec;
        comm_pq_cfg->vluma_offset = 0;
        comm_pq_cfg->vchroma_offset = 0;
        comm_pq_cfg->vbluma_offset = MIN_OFFSET * (hi_s32)zme_vprec / 2;
        comm_pq_cfg->vbchroma_offset = MIN_OFFSET * (hi_s32)zme_vprec / 2;
        comm_pq_cfg->vl_flatdect_mode = 1;
        comm_pq_cfg->vl_coringadj_en = 1;
        comm_pq_cfg->vl_gain = 32;
        comm_pq_cfg->vl_coring = 16;
        comm_pq_cfg->vc_flatdect_mode = 1;
        comm_pq_cfg->vc_coringadj_en = 1;
        comm_pq_cfg->vc_gain = 32;
        comm_pq_cfg->vc_coring = 16;
        comm_pq_cfg->lhfir_offset = 0;
        comm_pq_cfg->chfir_offset = 0;
        comm_pq_cfg->hl_flatdect_mode = 1;
        comm_pq_cfg->hl_coringadj_en = 1;
        comm_pq_cfg->hl_gain = 32;
        comm_pq_cfg->hl_coring = 16;
        comm_pq_cfg->hc_flatdect_mode = 1;
        comm_pq_cfg->hc_coringadj_en = 1;
        comm_pq_cfg->hc_gain = 32;
        comm_pq_cfg->hc_coring = 16;
    }
}

static hi_void vo_drv_set_layer_cvfir_mode(hi_u32 layer, vo_zme_mode zme_mode, const vdp_v1_cvfir_cfg *cfg)
{
    hi_u32 vzme_ck_gt_en;
    hi_u32 out_pro;
    hi_u32 out_fmt;
    hi_u32 out_height;
    hi_u32 cvfir_en;
    hi_u32 cvmid_en;
    hi_u32 cvfir_mode;
    hi_u32 vratio;
    hi_u32 vchroma_offset;
    hi_u32 vbchroma_offset;
    vo_zme_ds_info ds_info = {0};
    vo_zme_comm_pq_cfg comm_pq_cfg = {0};

    ds_info.zme_vprec = ZME_VPREC;
    ds_info.zme_hprec = ZME_HPREC;

    vzme_ck_gt_en = cfg->ck_gt_en;
    cvfir_en = cfg->cvfir_en;
    cvfir_mode = cfg->cvfir_mode;
    cvmid_en = cfg->cvmid_en;

    out_pro = cfg->out_pro;
    out_fmt = cfg->out_fmt;
    out_height = cfg->in_height;
    vratio = ds_info.zme_vprec;

    vo_drv_func_get_cvfir_pq_cfg(&ds_info, zme_mode, &comm_pq_cfg);

    vchroma_offset = comm_pq_cfg.vchroma_offset;
    vbchroma_offset = comm_pq_cfg.vbchroma_offset;

    hal_video_cvfir_set_out_height(layer, out_height);
    hal_video_cvfir_set_out_fmt(layer, out_fmt);
    hal_video_cvfir_set_out_pro(layer, out_pro);
    hal_video_cvfir_set_vzme_ck_gt_en(layer, vzme_ck_gt_en);

    hal_video_cvfir_set_cvfir_en(layer, cvfir_en);
    hal_video_cvfir_set_cvmid_en(layer, cvmid_en);
    hal_video_cvfir_set_cvfir_mode(layer, cvfir_mode);
    hal_video_cvfir_set_vratio(layer, vratio);

    hal_video_cvfir_set_v_chroma_offset(layer, vchroma_offset);
    hal_video_cvfir_set_vb_chroma_offset(layer, vbchroma_offset);
}

hi_void vo_vid_set_zme_enable(hi_u32 layer, const vdp_vid_ip_cfg *vid_cfg)
{
    /* the numbers below are register config from algorithm, not magic number. */
    vdp_v1_cvfir_cfg cvfir_cfg;
    cvfir_cfg.hfir_order = 0;
    cvfir_cfg.lhfir_en = 0;
    cvfir_cfg.chfir_en = 0;
    cvfir_cfg.lhmid_en = 0;
    cvfir_cfg.chmid_en = 0;
    cvfir_cfg.lhfir_mode = 0;
    cvfir_cfg.chfir_mode = 0;
    cvfir_cfg.hl_shootctrl_en = 0;
    cvfir_cfg.hl_shootctrl_mode = 0;
    cvfir_cfg.hc_shootctrl_en = 0;
    cvfir_cfg.hc_shootctrl_mode = 0;
    cvfir_cfg.lvfir_en = 0;
    cvfir_cfg.lvmid_en = 0;
    cvfir_cfg.lvfir_mode = 0;
    cvfir_cfg.vl_shootctrl_en = 0;
    cvfir_cfg.vl_shootctrl_mode = 0;
    cvfir_cfg.vc_shootctrl_en = 0;
    cvfir_cfg.vc_shootctrl_mode = 0;

    /* CVFIR */
    cvfir_cfg.ck_gt_en = 0;
    cvfir_cfg.cvfir_en = 1;
    cvfir_cfg.cvmid_en = 0;
    cvfir_cfg.cvfir_mode = 0;
    cvfir_cfg.out_pro = VDP_RMODE_PROGRESSIVE;
    cvfir_cfg.out_fmt = VDP_PROC_FMT_SP_422;
    cvfir_cfg.in_width = vid_cfg->vid_iw;
    cvfir_cfg.in_height = vid_cfg->vid_ih;
    cvfir_cfg.out_width = vid_cfg->vid_ow;
    cvfir_cfg.out_height = vid_cfg->vid_oh;
    vo_drv_set_layer_cvfir_mode(layer, VO_ZME_TYP, &cvfir_cfg);
}

hi_s32 vo_drv_get_csc_matrix(hal_csc_mode csc_mode, const vo_csc_coef **csc_tmp)
{
    switch (csc_mode) {
        case HAL_CSC_MODE_BT601_TO_BT601:
        case HAL_CSC_MODE_BT709_TO_BT709:
        case HAL_CSC_MODE_RGB_TO_RGB:
            *csc_tmp = &g_csc_init;
            break;

        case HAL_CSC_MODE_BT709_TO_BT601:
            *csc_tmp = &g_csc_yuv_to_yuv_709_601;
            break;

        case HAL_CSC_MODE_BT601_TO_BT709:
            *csc_tmp = &g_csc_yuv_to_yuv_601_709;
            break;

        case HAL_CSC_MODE_BT601_TO_RGB_PC:
            *csc_tmp = &g_csc_yuv601_to_rgb_pc;
            break;

        case HAL_CSC_MODE_BT709_TO_RGB_PC:
            *csc_tmp = &g_csc_yuv709_to_rgb_pc;
            break;

        case HAL_CSC_MODE_RGB_TO_BT601_PC:
            *csc_tmp = &g_csc_rgb_to_yuv601_pc;
            break;

        case HAL_CSC_MODE_RGB_TO_BT709_PC:
            *csc_tmp = &g_csc_rgb_to_yuv709_pc;
            break;

        case HAL_CSC_MODE_RGB_TO_BT601_TV:
            *csc_tmp = &g_csc_rgb_to_yuv601_tv;
            break;

        case HAL_CSC_MODE_RGB_TO_BT709_TV:
            *csc_tmp = &g_csc_rgb_to_yuv709_tv;
            break;

        default:
            return HI_FAILURE;
    }

    return HI_SUCCESS;
}

hi_void vo_drv_get_hal_cscvalue(const vo_csc *csc, hal_csc_value *csc_value)
{
    csc_value->luma = (hi_s32)csc->luma * 64 / 100 - 32; /* x64/100 -32 to adjust the value */
    csc_value->cont = ((hi_s32)csc->contrast - 50) * 2 + 100; /* -50) * 2 + 100 to adjust the value */
    csc_value->hue = (hi_s32)csc->hue * 60 / 100; /* x60/100 to adjust the value */
    csc_value->satu = ((hi_s32)csc->satuature - 50) * 2 + 100; /* -50) * 2 + 100 to adjust the value */
}

hi_void vo_drv_set_csc_coef_y2r(const hal_csc_value *csc_value, const vo_csc_coef *csc_tmp, vo_csc_coef *csc_coef)
{
    hi_s32 luma;
    hi_s32 contrast;
    hi_s32 hue;
    hi_s32 satu;

    luma = csc_value->luma;
    contrast = csc_value->cont;
    hue = csc_value->hue;
    satu = csc_value->satu;
    /* 100 and 1000 is to adjust the coef */
    csc_coef->csc_coef00 = (contrast * csc_tmp->csc_coef00) / 100;
    csc_coef->csc_coef01 = (contrast * satu * ((csc_tmp->csc_coef01 * g_cos_table[hue] -
                           csc_tmp->csc_coef02 * g_sin_table[hue]) / 1000)) / 10000;
    csc_coef->csc_coef02 = (contrast * satu * ((csc_tmp->csc_coef01 * g_sin_table[hue] +
                           csc_tmp->csc_coef02 * g_cos_table[hue]) / 1000)) / 10000;
    csc_coef->csc_coef10 = (contrast * csc_tmp->csc_coef10) / 100;
    csc_coef->csc_coef11 = (contrast * satu * ((csc_tmp->csc_coef11 * g_cos_table[hue] -
                           csc_tmp->csc_coef12 * g_sin_table[hue]) / 1000)) / 10000;
    csc_coef->csc_coef12 = (contrast * satu * ((csc_tmp->csc_coef11 * g_sin_table[hue] +
                           csc_tmp->csc_coef12 * g_cos_table[hue]) / 1000)) / 10000;
    csc_coef->csc_coef20 = (contrast * csc_tmp->csc_coef20) / 100;
    csc_coef->csc_coef21 = (contrast * satu * ((csc_tmp->csc_coef21 * g_cos_table[hue] -
                           csc_tmp->csc_coef22 * g_sin_table[hue]) / 1000)) / 10000;
    csc_coef->csc_coef22 = (contrast * satu * ((csc_tmp->csc_coef21 * g_sin_table[hue] +
                           csc_tmp->csc_coef22 * g_cos_table[hue]) / 1000)) / 10000;
    csc_coef->csc_in_dc0 += (contrast != 0) ? (luma * 100 / contrast) : luma * 100;
}

hi_void vo_drv_set_csc_coef_r2y(hal_csc_value *csc_value, const vo_csc_coef *csc_tmp, vo_csc_coef *csc_coef)
{
    hi_s32 luma;
    hi_s32 contrast;
    hi_s32 hue;
    hi_s32 satu;

    luma = csc_value->luma;
    contrast = csc_value->cont;
    hue = csc_value->hue;
    satu = csc_value->satu;

    /* 100 and 1000 is to adjust the coef */
    csc_coef->csc_coef00 = (contrast * csc_tmp->csc_coef00) / 100;
    csc_coef->csc_coef01 = (contrast * csc_tmp->csc_coef01) / 100;
    csc_coef->csc_coef02 = (contrast * csc_tmp->csc_coef02) / 100;
    csc_coef->csc_coef10 = (contrast * satu * ((csc_tmp->csc_coef10 * g_cos_table[hue] +
                           csc_tmp->csc_coef20 * g_sin_table[hue]) / 1000)) / 10000;
    csc_coef->csc_coef11 = (contrast * satu * ((csc_tmp->csc_coef11 * g_cos_table[hue] +
                           csc_tmp->csc_coef21 * g_sin_table[hue]) / 1000)) / 10000;
    csc_coef->csc_coef12 = (contrast * satu * ((csc_tmp->csc_coef12 * g_cos_table[hue] +
                           csc_tmp->csc_coef22 * g_sin_table[hue]) / 1000)) / 10000;
    csc_coef->csc_coef20 = (contrast * satu * ((csc_tmp->csc_coef20 * g_cos_table[hue] -
                           csc_tmp->csc_coef10 * g_sin_table[hue]) / 1000)) / 10000;
    csc_coef->csc_coef21 = (contrast * satu * ((csc_tmp->csc_coef21 * g_cos_table[hue] -
                           csc_tmp->csc_coef11 * g_sin_table[hue]) / 1000)) / 10000;
    csc_coef->csc_coef22 = (contrast * satu * ((csc_tmp->csc_coef22 * g_cos_table[hue] -
                           csc_tmp->csc_coef12 * g_sin_table[hue]) / 1000)) / 10000;
    csc_coef->csc_out_dc0 += luma;
}

hi_void vo_drv_calc_csc_matrix(const vo_csc *csc, hal_csc_mode csc_mode, vo_csc_coef *cst_coef)
{
    const vo_csc_coef *csc_tmp = HI_NULL;
    hi_s32 ret;
    hal_csc_value csc_value = {0};

    vo_drv_get_hal_cscvalue(csc, &csc_value);

    ret = vo_drv_get_csc_matrix(csc_mode, &csc_tmp);
    if (ret != HI_SUCCESS) {
        return;
    }

    cst_coef->csc_in_dc0 = csc_tmp->csc_in_dc0;
    cst_coef->csc_in_dc1 = csc_tmp->csc_in_dc1;
    cst_coef->csc_in_dc2 = csc_tmp->csc_in_dc2;
    cst_coef->csc_out_dc0 = csc_tmp->csc_out_dc0;
    cst_coef->csc_out_dc1 = csc_tmp->csc_out_dc1;
    cst_coef->csc_out_dc2 = csc_tmp->csc_out_dc2;

    if ((csc_mode == HAL_CSC_MODE_BT601_TO_RGB_PC) || (csc_mode == HAL_CSC_MODE_BT709_TO_RGB_PC) ||
        (csc_mode == HAL_CSC_MODE_BT601_TO_RGB_TV) || (csc_mode == HAL_CSC_MODE_BT709_TO_RGB_TV)) {
        vo_drv_set_csc_coef_y2r(&csc_value, csc_tmp, cst_coef);
    } else {
        vo_drv_set_csc_coef_r2y(&csc_value, csc_tmp, cst_coef);
    }

    return;
}

hi_s32 graphic_drv_set_csc_coef(hal_disp_layer gfx_layer, const vo_csc *gfx_csc, const csc_coef_param *coef_param)
{
    vo_csc_coef coef;
    hal_csc_mode csc_mode;

    if (gfx_csc->csc_matrix == VO_CSC_MATRIX_IDENTITY) {
        csc_mode = HAL_CSC_MODE_NONE;
    } else if (gfx_csc->csc_matrix == VO_CSC_MATRIX_RGB_TO_BT601_PC) {
        csc_mode = HAL_CSC_MODE_RGB_TO_BT601_PC;
    } else if (gfx_csc->csc_matrix == VO_CSC_MATRIX_RGB_TO_BT709_PC) {
        csc_mode = HAL_CSC_MODE_RGB_TO_BT709_PC;
    } else {
        printf("csc_matrix %d err, should only be RGB to yuv matrix\n", gfx_csc->csc_matrix);
        return HI_FAILURE;
    }

    coef.new_csc_clip_max = GFX_CSC_CLIP_MAX;
    coef.new_csc_clip_min = GFX_CSC_CLIP_MIN;
    coef.new_csc_scale2p = GFX_CSC_SCALE;

    hal_layer_set_csc_coef(gfx_layer, &coef);
    hal_layer_csc_set_csc_mode(gfx_layer, csc_mode);

    return HI_SUCCESS;
}

hi_void vo_drv_get_hal_cscmode(vo_csc_matrix csc_matrix, hal_csc_mode *csc_mode)
{
    switch (csc_matrix) {
        case VO_CSC_MATRIX_IDENTITY:
            *csc_mode = HAL_CSC_MODE_BT601_TO_BT601;
            break;
        case VO_CSC_MATRIX_BT601_TO_BT709:
            *csc_mode = HAL_CSC_MODE_BT601_TO_BT709;
            break;
        case VO_CSC_MATRIX_BT709_TO_BT601:
            *csc_mode = HAL_CSC_MODE_BT709_TO_BT601;
            break;
        case VO_CSC_MATRIX_BT601_TO_RGB_PC:
            *csc_mode = HAL_CSC_MODE_BT601_TO_RGB_PC;
            break;
        case VO_CSC_MATRIX_BT709_TO_RGB_PC:
            *csc_mode = HAL_CSC_MODE_BT709_TO_RGB_PC;
            break;
        case VO_CSC_MATRIX_RGB_TO_BT601_PC:
            *csc_mode = HAL_CSC_MODE_RGB_TO_BT601_PC;
            break;
        case VO_CSC_MATRIX_RGB_TO_BT709_PC:
            *csc_mode = HAL_CSC_MODE_RGB_TO_BT709_PC;
            break;
        default:
            *csc_mode = HAL_CSC_MODE_BT601_TO_BT601;
            break;
    }
}

hi_s32 vo_drv_video_set_csc_coef(vo_hal_layer vo_layer, vo_csc_matrix csc_matrix)
{
    vo_csc_coef csc_coef;
    hal_csc_mode csc_mode;
    const hi_u32 dc_pre = 4;
    vo_csc csc = {0};

    /* 50 default value */
    csc.contrast = 50;
    csc.hue = 50;
    csc.luma = 50;
    csc.satuature = 50;

    if ((vo_layer < LAYER_VHD_START) || (vo_layer > LAYER_VHD_END)) {
        printf("[%s][%d] vo_layer:%d not supported\n", __FUNCTION__, __LINE__, vo_layer);
        return HI_FAILURE;
    }

    vo_drv_get_hal_cscmode(csc_matrix, &csc_mode);

    vo_drv_calc_csc_matrix(&csc, csc_mode, &csc_coef);

    /* 0xfff 0x0 0x8 default value from algorithm */
    csc_coef.new_csc_clip_max = 0xfff;
    csc_coef.new_csc_clip_min = 0x0;
    csc_coef.new_csc_scale2p = 0x8;

    /* x1024/1000 is to adjust coef value */
    csc_coef.csc_coef00 = csc_coef.csc_coef00 * 1024 / 1000;
    csc_coef.csc_coef01 = csc_coef.csc_coef01 * 1024 / 1000;
    csc_coef.csc_coef02 = csc_coef.csc_coef02 * 1024 / 1000;
    csc_coef.csc_coef10 = csc_coef.csc_coef10 * 1024 / 1000;
    csc_coef.csc_coef11 = csc_coef.csc_coef11 * 1024 / 1000;
    csc_coef.csc_coef12 = csc_coef.csc_coef12 * 1024 / 1000;
    csc_coef.csc_coef20 = csc_coef.csc_coef20 * 1024 / 1000;
    csc_coef.csc_coef21 = csc_coef.csc_coef21 * 1024 / 1000;
    csc_coef.csc_coef22 = csc_coef.csc_coef22 * 1024 / 1000;

    /* 0x7ff is the max value */
    csc_coef.csc_coef00 = (csc_coef.csc_coef00 > 0x7ff) ? 0x7ff : csc_coef.csc_coef00;
    csc_coef.csc_coef01 = (csc_coef.csc_coef01 > 0x7ff) ? 0x7ff : csc_coef.csc_coef01;
    csc_coef.csc_coef02 = (csc_coef.csc_coef02 > 0x7ff) ? 0x7ff : csc_coef.csc_coef02;
    csc_coef.csc_coef10 = (csc_coef.csc_coef10 > 0x7ff) ? 0x7ff : csc_coef.csc_coef10;
    csc_coef.csc_coef11 = (csc_coef.csc_coef11 > 0x7ff) ? 0x7ff : csc_coef.csc_coef11;
    csc_coef.csc_coef12 = (csc_coef.csc_coef12 > 0x7ff) ? 0x7ff : csc_coef.csc_coef12;
    csc_coef.csc_coef20 = (csc_coef.csc_coef20 > 0x7ff) ? 0x7ff : csc_coef.csc_coef20;
    csc_coef.csc_coef21 = (csc_coef.csc_coef21 > 0x7ff) ? 0x7ff : csc_coef.csc_coef21;
    csc_coef.csc_coef22 = (csc_coef.csc_coef22 > 0x7ff) ? 0x7ff : csc_coef.csc_coef22;

    csc_coef.csc_in_dc0 = (hi_s32)csc_coef.csc_in_dc0;
    csc_coef.csc_in_dc1 = (hi_s32)csc_coef.csc_in_dc1;
    csc_coef.csc_in_dc2 = (hi_s32)csc_coef.csc_in_dc2;
    csc_coef.csc_out_dc0 = (hi_s32)dc_pre * csc_coef.csc_out_dc0;
    csc_coef.csc_out_dc1 = (hi_s32)dc_pre * csc_coef.csc_out_dc1;
    csc_coef.csc_out_dc2 = (hi_s32)dc_pre * csc_coef.csc_out_dc2;

    hal_layer_set_csc_coef(vo_layer, &csc_coef);

    return HI_SUCCESS;
}

hi_s32 load_bmp(hi_phys_addr_t bmp_addr, osd_logo_t *video_logo)
{
    hi_u16 bpp;
    osd_bitmap_file_header bmp_file_header;
    osd_bitmap_info bmp_info;

    memcpy(&bmp_file_header, (char *)(uintptr_t)(bmp_addr + sizeof(hi_u16)), sizeof(osd_bitmap_file_header));
    memcpy(&bmp_info, (char *)(uintptr_t)(bmp_addr + sizeof(hi_u16) + sizeof(osd_bitmap_file_header)), sizeof(osd_bitmap_info));
    video_logo->width = bmp_info.bmi_header.bi_width;
    video_logo->height = bmp_info.bmi_header.bi_height;
    video_logo->stride = bmp_info.bmi_header.bi_width * (OSD_BI_BIT_COUNT_16BPP / 8); /* 8 bits per bytes */
    video_logo->rgb_buffer = bmp_addr + bmp_file_header.bf_off_bits;

    bpp = bmp_info.bmi_header.bi_bit_count;
    if (bpp != OSD_BI_BIT_COUNT_16BPP) { /* 16 bits, 2bytes per pixel bitmap format */
        printf("bitmap format bpp=%d not supported! only supoort format bpp=%d\n", bpp, OSD_BI_BIT_COUNT_16BPP);
        return -1;
    }
    return 0;
}
