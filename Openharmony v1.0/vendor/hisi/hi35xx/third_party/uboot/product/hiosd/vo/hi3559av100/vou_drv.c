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

#define VO_DEV_MAX_NUM   2
#define VO_LAYER_MAX_NUM 17

#define VO_SD_VTTH_WATERLINE 100
#define VO_HD_VTTH_WATERLINE 240

#define VO_BACKGROUD_BLACK   0x8080
#define VO_BACKGROUD_GREEN   0x804D3A42
#define VO_BACKGROUD_WHITE   0x3fffffff
#define VO_BACKGROUD_DEFAULT VO_BACKGROUD_WHITE

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

static hal_layer_config g_hal_layer_cfg[VO_LAYER_MAX_NUM];

vo_user_intfsync_info g_user_intfsync_info;

hal_disp_syncinfo g_sync_timing[VO_OUTPUT_BUTT] = {
    /* synm, iop, itf,   vact, vbb,  vfb,  hact,  hbb,  hfb, hmid,bvact,bvbb, bvfb, hpw, vpw,idv, ihs, ivs */
    { 0, 0, 0, 288, 22, 2, 720, 132, 12, 1, 288, 23, 2, 126, 3, 0, 0, 0 }, /* 576I(PAL)  */
    { 0, 0, 0, 240, 18, 4, 720, 119, 19, 1, 240, 19, 4, 124, 3, 0, 0, 0 }, /* 480I(NTSC) */
    { 0, 1, 1, 1080, 41, 4, 1920, 192, 638, 1, 1, 1, 1, 44, 5, 0, 0, 0 }, /* 1080P@24Hz */
    { 0, 1, 1, 1080, 41, 4, 1920, 192, 528, 1, 1, 1, 1, 44, 5, 0, 0, 0 }, /* 1080P@25Hz */
    { 0, 1, 1, 1080, 41, 4, 1920, 192, 88,  1, 1, 1, 1, 44, 5, 0, 0, 0 }, /* 1080P@30Hz */
    { 0, 1, 1, 720,  25, 5, 1280, 260, 440, 1,    1,   1,  1, 40, 5, 0, 0, 0 }, /* 720P@50Hz */
    { 0, 1, 1, 720,  25, 5, 1280, 260, 110, 1,    1,   1,  1, 40, 5, 0, 0, 0 }, /* 720P@60Hz */
    { 0, 0, 1, 540,  20, 2, 1920, 192, 528, 1128, 540, 21, 2, 44, 5, 0, 0, 0 }, /* 1080I@50Hz */
    { 0, 0, 1, 540,  20, 2, 1920, 192, 88,  908,  540, 21, 2, 44, 5, 0, 0, 0 }, /* 1080I@60Hz */
    { 0, 1, 1, 1080, 41, 4, 1920, 192, 528, 1,    1,   1,  1, 44, 5, 0, 0, 0 }, /* 1080P@50Hz */
    { 0, 1, 1, 1080, 41, 4, 1920, 192, 88,  1,    1,   1,  1, 44, 5, 0, 0, 0 }, /* 1080P@60Hz */
    { 1, 1, 1, 576, 44, 5, 720, 132, 12, 1, 1, 1, 1, 64, 5, 0, 0, 0 }, /* 576P@50Hz */
    { 1, 1, 1, 480, 36, 9, 720, 122, 16, 1, 1, 1, 1, 62, 6, 0, 0, 0 }, /* 480P@60Hz */
    { 1, 1, 2, 600,  27, 1,  800,  216, 40,  1, 1, 1, 1, 128, 4, 0, 0, 0 }, /* 800*600@60Hz VGA@60Hz */
    { 1, 1, 2, 768,  35, 3,  1024, 296, 24,  1, 1, 1, 1, 136, 6, 0, 1, 1 }, /* 1024x768@60Hz */
    { 1, 1, 2, 1024, 41, 1,  1280, 360, 48,  1, 1, 1, 1, 112, 3, 0, 0, 0 }, /* 1280x1024@60Hz */
    { 1, 1, 2, 768,  27, 3,  1366, 356, 70,  1, 1, 1, 1, 143, 3, 0, 0, 0 }, /* 1366x768@60Hz */
    { 1, 1, 2, 900,  31, 3,  1440, 384, 80,  1, 1, 1, 1, 152, 6, 0, 1, 0 }, /* 1440x900@60Hz */
    { 1, 1, 2, 800,  28, 3,  1280, 328, 72,  1, 1, 1, 1, 128, 6, 0, 1, 0 }, /* 1280*800@60Hz VGA@60Hz */
    { 1, 1, 2, 1200, 49, 1,  1600, 496, 64,  1, 1, 1, 1, 192, 3, 0, 0, 0 }, /* 1600*1200@60Hz */
    { 1, 1, 2, 1050, 36, 3,  1680, 456, 104, 1, 1, 1, 1, 176, 6, 0, 1, 0 }, /* 1680*1050@60Hz */
    { 1, 1, 2, 1200, 32, 3,  1920, 112, 48,  1, 1, 1, 1, 32,  6, 0, 1, 0 }, /* 1920*1200@60Hz CVT (reduced blanking) */
    { 1, 1, 2, 480,  35, 10, 640,  144, 16,  1, 1, 1, 1, 96,  2, 0, 1, 1 }, /* 640*480@60Hz CVT */
    { 0, 0, 0, 288, 22, 2, 960, 176, 16, 1, 288, 23, 2, 168, 3, 0, 0, 0 }, /* 960H(PAL) */
    { 0, 0, 0, 240, 18, 4, 960, 163, 21, 1, 240, 19, 4, 168, 3, 0, 0, 0 }, /* 960H(NTSC) */
    { 0, 1, 1, 2160, 72, 8, 1920, 192, 88,   1, 1, 1, 1, 44, 5,  0, 0, 0 }, /* 1920*2160@30Hz */
    { 0, 1, 1, 1440, 37, 3, 2560, 80,  48,   1, 1, 1, 1, 32, 6,  0, 0, 0 }, /* 2560*1440@30Hz */
    { 1, 1, 2, 1440, 39, 2, 2560, 112, 48,   1, 1, 1, 1, 32, 5,  0, 0, 0 }, /* 2560*1440@60Hz */
    { 0, 1, 2, 1600, 43, 3, 2560, 112, 48,   1, 1, 1, 1, 32, 6,  0, 0, 0 }, /* 2560*1600@60Hz CVT (reduced blanking) */
    { 0, 1, 1, 2160, 82, 8, 3840, 384, 1276, 1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 3840*2160@24Hz */
    { 0, 1, 1, 2160, 82, 8, 3840, 384, 1056, 1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 3840*2160@25Hz */
    { 0, 1, 1, 2160, 82, 8, 3840, 384, 176,  1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 3840*2160@30Hz */
    { 0, 1, 1, 2160, 82, 8, 3840, 384, 1056, 1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 3840*2160@50Hz */
    { 0, 1, 1, 2160, 82, 8, 3840, 384, 176,  1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 3840*2160@60Hz */
    { 0, 1, 1, 2160, 82, 8, 4096, 384, 1020, 1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 4096x2160@24 */
    { 0, 1, 1, 2160, 82, 8, 4096, 216, 968,  1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 4096x2160@25 */
    { 0, 1, 1, 2160, 82, 8, 4096, 216, 88,   1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 4096x2160@30 */
    { 0, 1, 1, 2160, 82, 8, 4096, 216, 968,  1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 4096x2160@50 */
    { 0, 1, 1, 2160, 82, 8, 4096, 216, 88,   1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 4096x2160@60 */
    { 0, 1, 1, 240, 15, 9,  320, 65,  7,  1, 240, 14, 9, 1,  1, 0, 0, 0 }, /* 320X240@30 8bit LCD */
    { 0, 1, 1, 240, 2,  2,  320, 5,   10, 1, 1,   1,  1, 10, 1, 0, 0, 0 }, /* 320X240@50 6bit LCD */
    { 0, 1, 1, 320, 10, 4,  240, 20,  10, 1, 1,   1,  1, 10, 2, 0, 0, 0 }, /* 240X320@50 6bit LCD */
    { 0, 1, 1, 320, 4,  8,  240, 20,  10, 1, 1,   1,  1, 2,  2, 0, 0, 0 }, /* 240X320 16bit LCD */
    { 0, 1, 1, 600, 23, 12, 800, 210, 46, 1, 1,   1,  1, 2,  1, 0, 0, 0 }, /* 800*600@60Hz */
    { 0, 1, 1, 1280, 24, 8, 720, 123, 99, 1, 1, 1, 1, 24, 4, 0, 0, 0 },   /* 720 x1280 at 60 hz */
    { 0, 1, 1, 1920, 36, 16, 1080, 28, 130, 1, 1, 1, 1, 24, 4, 0, 0, 0 }, /* 1080 x1920 at 60 hz */
    { 0, 1, 1, 4320, 64, 16, 7680, 768, 552, 1, 1, 1, 1, 176, 20, 0, 0, 0 }, /* 7680x4320@30 */
    {} /* user */
};

static hal_dev_config g_hal_dev_cfg[VO_DEV_MAX_NUM] = {
    {
        .enable = HI_FALSE,
        .bk_grd = VO_BACKGROUD_DEFAULT,
        .intf_type = VO_INTF_HDMI | VO_INTF_BT1120 | VO_INTF_BT656,
        .out_sync = VO_OUTPUT_1080P60,
        .pixel_fmt = HAL_INPUTFMT_Y_CB_CR_SEMIPLANAR_422,
    },
    {
        .enable = HI_FALSE,
        .bk_grd = VO_BACKGROUD_DEFAULT,
        .intf_type = VO_INTF_BT1120 | VO_INTF_BT656 | VO_INTF_LCD,
        .out_sync = VO_OUTPUT_1080P60,
        .pixel_fmt = HAL_INPUTFMT_Y_CB_CR_SEMIPLANAR_422,
    }
};

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

hi_void vo_drv_dev_int_enable(vo_hal_dev vo_dev, hi_bool enable)
{
    vo_int_mask int_type;
    vo_int_mask hifb_int_type = 0x0;

    switch (vo_dev) {
        case VO_DEV_DHD0:
            int_type = VO_INTMSK_DHD0_VTTHD1;
            hifb_int_type = VO_INTMSK_DHD0_VTTHD2 | VO_INTMSK_DHD0_VTTHD3;
            break;

        case VO_DEV_DHD1:
            int_type = VO_INTMSK_DHD1_VTTHD1;
            hifb_int_type = VO_INTMSK_DHD1_VTTHD2 | VO_INTMSK_DHD1_VTTHD3;
            break;

        default:
            return;
    }

    if (enable == HI_TRUE) {
        hal_disp_set_int_mask(int_type);
        hal_disp_set_int_mask1(hifb_int_type);
    } else {
        hal_disp_clr_int_mask(int_type);
        hal_disp_clr_int_mask1(hifb_int_type);
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

hi_void vo_drv_set_layer_bk_grd(vo_hal_layer vo_layer, hi_u32 bk_grd)
{
    g_hal_layer_cfg[vo_layer].bk_grd = bk_grd;
    return;
}

hi_void vo_drv_set_layer_data_fmt(vo_hal_layer vo_layer, vo_layer_pixerl_format data_fmt)
{
    hal_disp_layer hal_video_layer = vo_layer;
    hal_disp_pixel_format hal_fmt = HAL_DISP_PIXELFORMAT_BUTT;
    switch (data_fmt) {
        case VO_LAYER_PIXERL_FORMAT_SP_Y_CB_CR_400:
            hal_fmt = HAL_INPUTFMT_Y_CB_CR_SEMIPLANAR_400;
            break;
        case VO_LAYER_PIXERL_FORMAT_SP_Y_CB_CR_420:
            hal_fmt = HAL_INPUTFMT_Y_CB_CR_SEMIPLANAR_420;
            break;
        case VO_LAYER_PIXERL_FORMAT_SP_Y_CB_CR_422:
            hal_fmt = HAL_INPUTFMT_Y_CB_CR_SEMIPLANAR_422;
            break;
        default:
            hal_fmt = HAL_INPUTFMT_Y_CB_CR_SEMIPLANAR_420;
            break;
    }
    hal_layer_set_layer_data_fmt(hal_video_layer, hal_fmt);
    return;
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

hi_s32 vo_drv_graphics_set_csc_coef(vo_hal_layer vo_layer)
{
    vo_csc_coef csc_coef;
    hal_csc_mode csc_mode;
    hi_u32 hihdr_r2y_scale2p = 0;
    hi_u32 hihdr_r2y_clip_min = 0;
    hi_u32 hihdr_r2y_clip_max = 0;
    vo_csc csc = {0};

    /* 50 default value */
    csc.contrast = 50;
    csc.hue = 50;
    csc.luma = 50;
    csc.satuature = 50;

    if ((vo_layer < LAYER_GFX_START) || (vo_layer > LAYER_GFX_END)) {
        printf("[%s][%d] vo_layer:%d not supported\n", __FUNCTION__, __LINE__, vo_layer);
        return HI_FAILURE;
    }

    if ((vo_layer == HAL_DISP_LAYER_GFX0) || (vo_layer == HAL_DISP_LAYER_GFX1)) {
        csc_mode = HAL_CSC_MODE_RGB_TO_BT709_PC;
    } else {
        printf("[%s][%d] vo_layer:%d not supported\n", __FUNCTION__, __LINE__, vo_layer);
        return HI_FAILURE;
    }
    if (vo_layer == HAL_DISP_LAYER_GFX0) {
        /* 0xd 0x0 0x3ff default value */
        hihdr_r2y_scale2p = 0xd;
        hihdr_r2y_clip_min = 0x0;
        hihdr_r2y_clip_max = 0x3ff;
        vo_drv_calc_csc_matrix(&csc, csc_mode, &csc_coef);
        /* 8 and 4 to adjust the coef config */
        csc_coef.csc_coef00 *= 8;
        csc_coef.csc_coef01 *= 8;
        csc_coef.csc_coef02 *= 8;
        csc_coef.csc_coef10 *= 8;
        csc_coef.csc_coef11 *= 8;
        csc_coef.csc_coef12 *= 8;
        csc_coef.csc_coef20 *= 8;
        csc_coef.csc_coef21 *= 8;
        csc_coef.csc_coef22 *= 8;

        csc_coef.csc_out_dc0 *= 4;
        csc_coef.csc_out_dc1 *= 4;
        csc_coef.csc_out_dc2 *= 4;

        hal_layer_set_csc_coef(vo_layer, &csc_coef);
        hal_hihdr_g_set_hihdr_r2y_scale2p(hihdr_r2y_scale2p);
        hal_hihdr_g_set_hihdr_r2y_clip_min(hihdr_r2y_clip_min);
        hal_hihdr_g_set_hihdr_r2y_clip_max(hihdr_r2y_clip_max);
    } else if (vo_layer == HAL_DISP_LAYER_GFX1) {
        vo_drv_calc_csc_matrix(&csc, csc_mode, &csc_coef);
        hal_layer_set_csc_coef(vo_layer, &csc_coef);
    }

    return HI_SUCCESS;
}

hi_s32 vo_drv_video_set_csc_coef(vo_hal_layer vo_layer)
{
    vo_csc_coef csc_coef;
    hal_csc_mode csc_mode;
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

    if ((vo_layer == HAL_DISP_LAYER_VHD0) || (vo_layer == HAL_DISP_LAYER_VHD1)) {
        csc_mode = HAL_CSC_MODE_BT709_TO_RGB_PC;
    } else {
        printf("[%s][%d] vo_layer:%d not supported\n", __FUNCTION__, __LINE__, vo_layer);
        return HI_FAILURE;
    }

    if (vo_layer == HAL_DISP_LAYER_VHD0) {
        /* 0xeb0 0x100 0xb default value */
        csc_coef.new_csc_clip_max = 0xeb0;
        csc_coef.new_csc_clip_min = 0x100;
        csc_coef.new_csc_scale2p = 0xb;
        vo_drv_calc_csc_matrix(&csc, csc_mode, &csc_coef);

        /* 8 and 4 to adjust the coef config */
        csc_coef.new_csc_coef00 = 8 * csc_coef.csc_coef00;
        csc_coef.new_csc_coef01 = 8 * csc_coef.csc_coef01;
        csc_coef.new_csc_coef02 = 8 * csc_coef.csc_coef02;
        csc_coef.new_csc_coef03 = 8 * csc_coef.csc_coef10;
        csc_coef.new_csc_coef04 = 8 * csc_coef.csc_coef11;
        csc_coef.new_csc_coef05 = 8 * csc_coef.csc_coef12;
        csc_coef.new_csc_coef06 = 8 * csc_coef.csc_coef20;
        csc_coef.new_csc_coef07 = 8 * csc_coef.csc_coef21;
        csc_coef.new_csc_coef08 = 8 * csc_coef.csc_coef22;

        csc_coef.new_csc_in_dc00 = csc_coef.csc_in_dc0;
        csc_coef.new_csc_in_dc01 = csc_coef.csc_in_dc1;
        csc_coef.new_csc_in_dc02 = csc_coef.csc_in_dc2;

        csc_coef.new_csc_out_dc00 = 4 * csc_coef.csc_out_dc0;
        csc_coef.new_csc_out_dc01 = 4 * csc_coef.csc_out_dc1;
        csc_coef.new_csc_out_dc02 = 4 * csc_coef.csc_out_dc2;

        hal_layer_set_csc_coef(vo_layer, &csc_coef);
    } else if (vo_layer == HAL_DISP_LAYER_VHD1) {
        vo_drv_calc_csc_matrix(&csc, csc_mode, &csc_coef);
        hal_layer_set_csc_coef(vo_layer, &csc_coef);
    }

    return HI_SUCCESS;
}

hi_void vo_drv_def_layer_bind_dev(hi_void)
{
    hal_cbm_set_cbm_mixer_prio(VO_LAYER_VHD0, VO_MIX_PRIO0, HAL_CBMMIX1);
    hal_cbm_set_cbm_mixer_prio(VO_LAYER_G0, VO_MIX_PRIO1, HAL_CBMMIX1);

    hal_cbm_set_cbm_mixer_prio(VO_LAYER_VHD1, VO_MIX_PRIO0, HAL_CBMMIX2);
    hal_cbm_set_cbm_mixer_prio(VO_LAYER_G1, VO_MIX_PRIO1, HAL_CBMMIX2);

    return;
}

hi_void vo_drv_set_lcd_serial_perd(vo_dev dev, hi_u32 dev_div)
{
    vo_intf_type intf_type;

    intf_type = g_hal_dev_cfg[dev].intf_type;

    if ((VO_INTF_LCD_6BIT & intf_type) ||
        (VO_INTF_LCD_8BIT & intf_type)) {
        if (dev_div == 3) { /* div mode 3 */
            hal_disp_set_lcd_serial_perd(0);
        } else {
            hal_disp_set_lcd_serial_perd(1);
        }
    }
}

hi_void vo_drv_set_uhd_user_clk(hi_void)
{
    vo_user_intfsync_pll *pll = HI_NULL;

    if (g_user_intfsync_info.user_intfsync_attr.user_sync_pll.fbdiv == 0) {
        printf("error: please set g_user_intfsync_info value!\n");
        return;
    }

    if (g_user_intfsync_info.user_intfsync_attr.clk_source == VO_CLK_SOURCE_PLL) {
        pll = &g_user_intfsync_info.user_intfsync_attr.user_sync_pll;
        sys_hal_set_vo_pll_fbdiv(VO_DEV_DHD0, pll->fbdiv);
        sys_hal_set_vo_pll_frac(VO_DEV_DHD0, pll->frac);
        sys_hal_set_vo_pll_refdiv(VO_DEV_DHD0, pll->refdiv);
        sys_hal_set_vo_pll_postdiv2(VO_DEV_DHD0, pll->postdiv2);
        sys_hal_set_vo_pll_postdiv1(VO_DEV_DHD0, pll->postdiv1);
    } else {
        printf("error: vo clk source is illegal\n");
        return;
    }

    sys_hal_vo_hd_clk_sel(VO_DEV_DHD0, 0);
    sys_hal_vo_hd_out_pctrl(g_user_intfsync_info.clk_reverse);
    sys_hal_vo_hd0_div_mode(VO_DEV_DHD0, g_user_intfsync_info.dev_div - 1);
    vo_drv_set_lcd_serial_perd(VO_DEV_DHD0, g_user_intfsync_info.dev_div);
    return;
}

hi_void vo_drv_set_uhd_clk(vo_hal_dev vo_dev, vo_intf_sync intf_sync)
{
    /* the numbers below is the default value of the register. */
    hi_u32 frac = 0;
    hi_u32 postdiv1 = 0;
    hi_u32 postdiv2 = 0;
    hi_u32 fbdiv = 0;
    hi_u32 refdiv = 0;
    hi_u32 vdp_hd_clk_sel = 0x0;

    if (g_hal_dev_cfg[vo_dev].out_sync == VO_OUTPUT_USER) {
        vo_drv_set_uhd_user_clk();
        return;
    }

    switch (g_hal_dev_cfg[vo_dev].out_sync) {
        /* the number is pll register config, calculate from out sync */
        case VO_OUTPUT_PAL:
        case VO_OUTPUT_NTSC: {
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
            fbdiv = 99;
            frac = 0;
            refdiv = 2;
            postdiv1 = 4;
            postdiv2 = 4;
            break;
        }

        case VO_OUTPUT_1080P50:
        case VO_OUTPUT_1080P60:
        case VO_OUTPUT_1920x2160_30:
        case VO_OUTPUT_1080x1920_60: {
            /* 148.5MHz */
            fbdiv = 99;
            frac = 0;
            refdiv = 2;
            postdiv1 = 4;
            postdiv2 = 2;
            vdp_hd_clk_sel = 0x2;
            break;
        }

        case VO_OUTPUT_576P50:
        case VO_OUTPUT_480P60: {
            fbdiv = 81;
            frac = 0;
            refdiv = 2;
            postdiv1 = 6;
            postdiv2 = 6;
            break;
        }
        case VO_OUTPUT_800x600_60: {
            /* 40MHz */
            fbdiv = 80;
            frac = 0;
            refdiv = 2;
            postdiv1 = 6;
            postdiv2 = 4;
            break;
        }
        case VO_OUTPUT_1024x768_60: {
            /* 65MHz */
            fbdiv = 65;
            frac = 0;
            refdiv = 1;
            postdiv1 = 6;
            postdiv2 = 4;
            break;
        }

        case VO_OUTPUT_1280x1024_60: {
            /* 108MHz */
            fbdiv = 72;
            frac = 0;
            refdiv = 2;
            postdiv1 = 4;
            postdiv2 = 2;
            break;
        }
        case VO_OUTPUT_1366x768_60: {
            /* 85.5MHz */
            fbdiv = 171;
            frac = 0;
            refdiv = 4;
            postdiv1 = 6;
            postdiv2 = 2;
            break;
        }
        case VO_OUTPUT_1440x900_60: {
            /* 106.5MHz */
            fbdiv = 213;
            frac = 0;
            refdiv = 4;
            postdiv1 = 6;
            postdiv2 = 2;
            break;
        }
        case VO_OUTPUT_1280x800_60: {
            /* 83.5MHz */
            fbdiv = 167;
            frac = 0;
            refdiv = 4;
            postdiv1 = 6;
            postdiv2 = 2;
            break;
        }
        case VO_OUTPUT_1600x1200_60: {
            /* 162MHz */
            fbdiv = 81;
            frac = 0;
            refdiv = 2;
            postdiv1 = 3;
            postdiv2 = 2;
            break;
        }
        case VO_OUTPUT_1680x1050_60: {
            /* 146.25MHz */
            fbdiv = 585;
            frac = 0;
            refdiv = 8;
            postdiv1 = 6;
            postdiv2 = 2;
            break;
        }
        case VO_OUTPUT_1920x1200_60: {
            /* 154MHz */
            fbdiv = 154;
            frac = 0;
            refdiv = 4;
            postdiv1 = 3;
            postdiv2 = 2;
            break;
        }
        case VO_OUTPUT_640x480_60: {
            /* 25.175MHz */
            fbdiv = 113;
            frac = 4823450;
            refdiv = 3;
            postdiv1 = 6;
            postdiv2 = 6;
            break;
        }

        case VO_OUTPUT_320x240_60: {
            /* lcd clk config */
            fbdiv = 101;
            frac = 7016903;
            refdiv = 2;
            postdiv1 = 7;
            postdiv2 = 7;
            break;
        }

        case VO_OUTPUT_320x240_50: {
            /* lcd clk config */
            vdp_hd_clk_sel = 0x2;
            break;
        }

        case VO_OUTPUT_240x320_50: {
            /* lcd clk config */
            vdp_hd_clk_sel = 0x2;
            break;
        }

        case VO_OUTPUT_240x320_60: {
            /* lcd clk config */
            vdp_hd_clk_sel = 0x0;
            break;
        }

        case VO_OUTPUT_800x600_50: {
            /* lcd clk config */
            vdp_hd_clk_sel = 0x0;
            break;
        }

        case VO_OUTPUT_2560x1440_30: {
            /* 241.6992MHz */
            fbdiv = 159;
            frac = 2796202;
            refdiv = 2;
            postdiv1 = 4;
            postdiv2 = 4;
            break;
        }

        case VO_OUTPUT_2560x1440_60: {
            /* 241.6992MHz */
            fbdiv = 161;
            frac = 0;
            refdiv = 4;
            postdiv1 = 4;
            postdiv2 = 1;
            vdp_hd_clk_sel = 0x1;
            break;
        }

        case VO_OUTPUT_2560x1600_60: {
            /* 268.6272MHz */
            fbdiv = 179;
            frac = 0;
            refdiv = 2;
            postdiv1 = 4;
            postdiv2 = 2;
            break;
        }

        case VO_OUTPUT_3840x2160_24:
        case VO_OUTPUT_3840x2160_25:
        case VO_OUTPUT_3840x2160_30:
        case VO_OUTPUT_4096x2160_24:
        case VO_OUTPUT_4096x2160_25:
        case VO_OUTPUT_4096x2160_30: {
            /* 297MHz */
            fbdiv = 99;
            frac = 0;
            refdiv = 2;
            postdiv1 = 4;
            postdiv2 = 1;
            vdp_hd_clk_sel = 0x1;
            break;
        }

        case VO_OUTPUT_3840x2160_50:
        case VO_OUTPUT_3840x2160_60:
        case VO_OUTPUT_4096x2160_50:
        case VO_OUTPUT_4096x2160_60: {
            /* 594MHz */
            fbdiv = 99;
            frac = 0;
            refdiv = 2;
            postdiv1 = 2;
            postdiv2 = 1;

            vdp_hd_clk_sel = 0x1;

            break;
        }
        case VO_OUTPUT_7680x4320_30: {
            /* 594MHz */
            fbdiv = 99;
            frac = 0;
            refdiv = 2;
            postdiv1 = 2;
            postdiv2 = 1;
            vdp_hd_clk_sel = 0x0;
            break;
        }

        default: {
            /* user set the pll reg. */
            return;
        }
    }
    sys_hal_vo_hd_clk_sel(vo_dev, vdp_hd_clk_sel);

    sys_hal_set_vo_pll_fbdiv(vo_dev, fbdiv);
    sys_hal_set_vo_pll_frac(vo_dev, frac);
    sys_hal_set_vo_pll_refdiv(vo_dev, refdiv);
    sys_hal_set_vo_pll_postdiv1(vo_dev, postdiv1);
    sys_hal_set_vo_pll_postdiv2(vo_dev, postdiv2);
    return;
}

hi_void vo_drv_set_hd_user_clk(hi_void)
{
    /* 0x0 0x015E4C3 default value */
    hi_u32 vdp_out_clk_sel = 0x0;
    hi_u32 lcd_mclk_div = 0x015E4C3;
    vo_user_intfsync_pll *pll = HI_NULL;
    if (g_user_intfsync_info.user_intfsync_attr.user_sync_pll.fbdiv == 0 ||
        g_user_intfsync_info.dev_div < 1 || g_user_intfsync_info.dev_div > 4) { /* div should be [1, 4] */
        printf("error: please set g_user_intfsync_info value!\n");
        return;
    }
    if (g_user_intfsync_info.user_intfsync_attr.clk_source == VO_CLK_SOURCE_PLL) {
        vdp_out_clk_sel = 0x7; /* 0x7 sel clk */
        sys_hal_vo_out_clk_sel(VO_DEV_DHD1, vdp_out_clk_sel);

        pll = &g_user_intfsync_info.user_intfsync_attr.user_sync_pll;
        sys_hal_set_vo_s_pll_fbdiv(VO_DEV_DHD1, pll->fbdiv);
        sys_hal_set_vo_s_pll_frac(VO_DEV_DHD1, pll->frac);
        sys_hal_set_vo_s_pll_refdiv(VO_DEV_DHD1, pll->refdiv);
        sys_hal_set_vo_s_pll_postdiv2(VO_DEV_DHD1, pll->postdiv2);
        sys_hal_set_vo_s_pll_postdiv1(VO_DEV_DHD1, pll->postdiv1);
    } else if (g_user_intfsync_info.user_intfsync_attr.clk_source == VO_CLK_SOURCE_LCDMCLK) {
        vdp_out_clk_sel = 0x6; /* 0x6 sel clk */
        sys_hal_vo_out_clk_sel(VO_DEV_DHD1, vdp_out_clk_sel);

        lcd_mclk_div = g_user_intfsync_info.user_intfsync_attr.lcd_mclk_div;
        sys_hal_lcd_mclk_div(lcd_mclk_div);
        sys_hal_vo_lcd_clk_en(HI_TRUE);
    } else {
        printf("error: vo clk source is illegal\n");
        return;
    }

    sys_hal_vo_hd_clk_sel(VO_DEV_DHD1, 0);
    sys_hal_vo_hd_out_pctrl(g_user_intfsync_info.clk_reverse);
    sys_hal_vo_hd1_div_mode(VO_DEV_DHD1, g_user_intfsync_info.dev_div - 1);
    vo_drv_set_lcd_serial_perd(VO_DEV_DHD1, g_user_intfsync_info.dev_div);

    return;
}

hi_void vo_drv_set_hd_clk(vo_hal_dev vo_dev, vo_intf_sync intf_sync)
{
    /* the numbers below is the default value of the register. */
    hi_u32 spll_frac = 0;
    hi_u32 spll_postdiv1 = 0;
    hi_u32 spll_postdiv2 = 0;
    hi_u32 spll_fbdiv = 0;
    hi_u32 spll_refdiv = 0;
    hi_u32 vdp_out_clk_sel = 0x0;
    hi_u32 hd1_div_mod = 0x0;
    hi_u32 lcd_mclk_div = 0x015E4C3;

    if (g_hal_dev_cfg[vo_dev].out_sync == VO_OUTPUT_USER) {
        vo_drv_set_hd_user_clk();
        return;
    }

    switch (intf_sync) {
        /* the number is pll register config, calculate from out sync */
        case VO_OUTPUT_PAL:
        case VO_OUTPUT_NTSC: {
            /* 27MHz */
            vdp_out_clk_sel = 0x5;
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
            vdp_out_clk_sel = 0x1;
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

        case VO_OUTPUT_576P50:
        case VO_OUTPUT_480P60: {
            /* 27MHz */
            vdp_out_clk_sel = 0x5;
            break;
        }

        case VO_OUTPUT_800x600_60: {
            /* 40MHz */
            spll_fbdiv = 80;
            spll_frac = 0;
            spll_refdiv = 2;
            spll_postdiv1 = 6;
            spll_postdiv2 = 4;
            vdp_out_clk_sel = 0x7;
            break;
        }
        case VO_OUTPUT_1024x768_60: {
            /* 65MHz */
            spll_fbdiv = 65;
            spll_frac = 0;
            spll_refdiv = 1;
            spll_postdiv1 = 6;
            spll_postdiv2 = 4;
            vdp_out_clk_sel = 0x7;
            break;
        }
        case VO_OUTPUT_1280x1024_60: {
            /* 108MHz */
            spll_fbdiv = 72;
            spll_frac = 0;
            spll_refdiv = 2;
            spll_postdiv1 = 4;
            spll_postdiv2 = 2;
            vdp_out_clk_sel = 0x7;
            break;
        }
        case VO_OUTPUT_1366x768_60: {
            /* 85.5MHz */
            spll_fbdiv = 171;
            spll_frac = 0;
            spll_refdiv = 4;
            spll_postdiv1 = 6;
            spll_postdiv2 = 2;
            vdp_out_clk_sel = 0x7;
            break;
        }
        case VO_OUTPUT_1440x900_60: {
            /* 106.5MHz */
            spll_fbdiv = 213;
            spll_frac = 0;
            spll_refdiv = 4;
            spll_postdiv1 = 6;
            spll_postdiv2 = 2;
            vdp_out_clk_sel = 0x7;
            break;
        }
        case VO_OUTPUT_1280x800_60: {
            /* 83.5MHz */
            spll_fbdiv = 167;
            spll_frac = 0;
            spll_refdiv = 4;
            spll_postdiv1 = 6;
            spll_postdiv2 = 2;
            vdp_out_clk_sel = 0x7;
            break;
        }
        case VO_OUTPUT_1600x1200_60: {
            /* 162MHz */
            spll_fbdiv = 81;
            spll_frac = 0;
            spll_refdiv = 2;
            spll_postdiv1 = 3;
            spll_postdiv2 = 2;
            vdp_out_clk_sel = 0x7;
            break;
        }
        case VO_OUTPUT_1680x1050_60: {
            /* 146.25MHz */
            spll_fbdiv = 585;
            spll_frac = 0;
            spll_refdiv = 8;
            spll_postdiv1 = 6;
            spll_postdiv2 = 2;
            vdp_out_clk_sel = 0x7;
            break;
        }
        case VO_OUTPUT_1920x1200_60: {
            /* 154MHz */
            spll_fbdiv = 154;
            spll_frac = 0;
            spll_refdiv = 4;
            spll_postdiv1 = 3;
            spll_postdiv2 = 2;
            vdp_out_clk_sel = 0x7;
            break;
        }
        case VO_OUTPUT_640x480_60: {
            /* 25.175MHz */
            spll_fbdiv = 113;
            spll_frac = 4823450;
            spll_refdiv = 3;
            spll_postdiv1 = 6;
            spll_postdiv2 = 6;
            vdp_out_clk_sel = 0x7;
            break;
        }

        case VO_OUTPUT_960H_PAL: {
            /* 35.942MHz */
            vdp_out_clk_sel = 0x6;
            hd1_div_mod = 0x1;
            lcd_mclk_div = 0x83df618;
            break;
        }

        case VO_OUTPUT_960H_NTSC: {
            /* 35.967360MHz */
            vdp_out_clk_sel = 0x6;
            hd1_div_mod = 0x1;
            lcd_mclk_div = 0x83e011c;
            break;
        }

        case VO_OUTPUT_320x240_60: {
            /* lcd clk config */
            vdp_out_clk_sel = 0x6;
            hd1_div_mod = 0x3;
            lcd_mclk_div = 0x82aE4C3;
            break;
        }

        case VO_OUTPUT_320x240_50: {
            /* lcd clk config */
            vdp_out_clk_sel = 0x6;
            hd1_div_mod = 0x2;
            lcd_mclk_div = 0x152306;
            break;
        }

        case VO_OUTPUT_240x320_50: {
            /* lcd clk config */
            vdp_out_clk_sel = 0x6;
            hd1_div_mod = 0x2;
            lcd_mclk_div = 0x1751bc;
            break;
        }

        case VO_OUTPUT_240x320_60: {
            /* lcd clk config */
            vdp_out_clk_sel = 0x6;
            hd1_div_mod = 0x0;
            lcd_mclk_div = 0x90c54;
            break;
        }

        case VO_OUTPUT_800x600_50: {
            /* lcd clk config */
            vdp_out_clk_sel = 0x6;
            hd1_div_mod = 0x0;
            lcd_mclk_div = 0x39cc92;
            break;
        }

        default: {
            /* user set the pll reg. */
            return;
        }
    }

    sys_hal_lcd_mclk_div(lcd_mclk_div);

    sys_hal_vo_out_clk_sel(vo_dev, vdp_out_clk_sel);
    sys_hal_vo_hd1_div_mode(vo_dev, hd1_div_mod);

    if ((g_hal_dev_cfg[vo_dev].out_sync == VO_OUTPUT_800x600_60) ||
        (g_hal_dev_cfg[vo_dev].out_sync == VO_OUTPUT_1024x768_60) ||
        (g_hal_dev_cfg[vo_dev].out_sync == VO_OUTPUT_1280x1024_60) ||
        (g_hal_dev_cfg[vo_dev].out_sync == VO_OUTPUT_1366x768_60) ||
        (g_hal_dev_cfg[vo_dev].out_sync == VO_OUTPUT_1440x900_60) ||
        (g_hal_dev_cfg[vo_dev].out_sync == VO_OUTPUT_1280x800_60) ||
        (g_hal_dev_cfg[vo_dev].out_sync == VO_OUTPUT_1600x1200_60) ||
        (g_hal_dev_cfg[vo_dev].out_sync == VO_OUTPUT_1680x1050_60) ||
        (g_hal_dev_cfg[vo_dev].out_sync == VO_OUTPUT_1920x1200_60) ||
        (g_hal_dev_cfg[vo_dev].out_sync == VO_OUTPUT_640x480_60)) {
        sys_hal_set_vo_s_pll_fbdiv(vo_dev, spll_fbdiv);
        sys_hal_set_vo_s_pll_frac(vo_dev, spll_frac);
        sys_hal_set_vo_s_pll_refdiv(vo_dev, spll_refdiv);
        sys_hal_set_vo_s_pll_postdiv1(vo_dev, spll_postdiv1);
        sys_hal_set_vo_s_pll_postdiv2(vo_dev, spll_postdiv2);
    }
    return;
}

hi_void vo_drv_set_dev_clk(vo_hal_dev vo_dev)
{
    /* set vpll */
    if (vo_dev == 0) {
        vo_drv_set_uhd_clk(vo_dev, g_hal_dev_cfg[vo_dev].out_sync);
    } else {
        vo_drv_set_hd_clk(vo_dev, g_hal_dev_cfg[vo_dev].out_sync);
    }

    return;
}

hi_u32 vo_drv_get_dev_vtth(vo_hal_dev vo_dev)
{
    hi_u32 dev_vtth;

    if (((vo_dev) == VO_DEV_DHD0) || ((vo_dev) == VO_DEV_DHD1)) {
        switch (g_hal_dev_cfg[vo_dev].out_sync) {
            case VO_OUTPUT_3840x2160_60:
                dev_vtth = 4 * VO_HD_VTTH_WATERLINE; /* 4 times of default */
                break;
            case VO_OUTPUT_2560x1600_60:
            case VO_OUTPUT_3840x2160_30:
                dev_vtth = 2 * VO_HD_VTTH_WATERLINE; /* 2 times of default */
                break;
            default:
                dev_vtth = VO_HD_VTTH_WATERLINE;
        }
    } else {
        dev_vtth = VO_SD_VTTH_WATERLINE;
    }

    return dev_vtth;
}

/* turn on clk */
hi_void vo_drv_set_all_crg_clk(hi_bool clk_en)
{
    int i = 0;
    hi_bool vo_clk_en = clk_en;

    for (i = 0; i < VO_DEV_MAX_NUM; i++) {
        sys_hal_vo_dev_clk_en(i, vo_clk_en);
    }
    i = 0;
    sys_hal_vo_cfg_clk_en(i, vo_clk_en);
    sys_hal_vo_apb_clk_en(i, vo_clk_en);
    sys_hal_vo_core_clk_en(i, vo_clk_en);
    sys_hal_vo_bus_clk_en(vo_clk_en);

    return;
}

hi_u32 vo_drv_get_dev_intf_type(vo_hal_dev vo_dev)
{
    return g_hal_dev_cfg[vo_dev].intf_type;
}

hi_bool vo_drv_is_lcd_intf(vo_intf_type intf_type)
{
    if ((VO_INTF_LCD & intf_type) ||
        (VO_INTF_LCD_8BIT & intf_type) ||
        (VO_INTF_LCD_6BIT & intf_type) ||
        (VO_INTF_LCD_16BIT & intf_type) ||
        (VO_INTF_LCD_18BIT & intf_type) ||
        (VO_INTF_LCD_24BIT & intf_type)) {
        return 1;
    }
    return 0;
}

void vo_drv_set_cbm_bkg(hi_s32 vo_dev)
{
    hal_disp_bkcolor bkg;
    hi_u32 yuv_bk_grd;
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];
    vo_intf_type type = hal_dev_cfg->intf_type;

    if ((VO_INTF_MIPI & type) ||
        vo_drv_is_lcd_intf(type)) {
        bkg.bkg_y = rgb_r(hal_dev_cfg->bk_grd);
        bkg.bkg_cb = rgb_g(hal_dev_cfg->bk_grd);
        bkg.bkg_cr = rgb_b(hal_dev_cfg->bk_grd);

        bkg.bkg_y = bkg.bkg_y << 2; /* 2 to turn 8 to 10 value */
        bkg.bkg_cb = bkg.bkg_cb << 2; /* 2 to turn 8 to 10 value */
        bkg.bkg_cr = bkg.bkg_cr << 2; /* 2 to turn 8 to 10 value */
    } else {
        yuv_bk_grd = rgb_to_yuv_full(hal_dev_cfg->bk_grd);
        bkg.bkg_y = yuv_y(yuv_bk_grd);
        bkg.bkg_cb = yuv_u(yuv_bk_grd);
        bkg.bkg_cr = yuv_v(yuv_bk_grd);
    }
    if (vo_dev == VO_DEV_DHD0) {
        hal_cbm_set_cbm_bkg(HAL_CBMMIX1, &bkg);
    } else if (vo_dev == VO_DEV_DHD1) {
        hal_cbm_set_cbm_bkg(HAL_CBMMIX2, &bkg);
    }
}

void vo_drv_get_intf_property(hi_s32 vo_dev, hal_disp_syncinfo *sync_info, hal_disp_syncinv *inv)
{
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];

    memcpy(sync_info, &g_sync_timing[hal_dev_cfg->out_sync], sizeof(hal_disp_syncinfo));
    inv->hs_inv = sync_info->ihs ? 1 : 0;
    inv->vs_inv = sync_info->ivs ? 1 : 0;
    inv->dv_inv = sync_info->idv ? 1 : 0;
}

void vo_drv_set_intf_bt1120_cfg(hi_s32 vo_dev, hal_disp_syncinv *inv)
{
    hal_disp_set_intf_sync_inv(VO_INTF_BT1120, inv);
    hal_intf_bt_set_dfir_en(0x1);
    sys_hal_vo_bt1120_chn_sel(vo_dev);
    sys_hal_vo_bt_bp_clk_en(HI_TRUE);
    sys_hal_vo_bt_clk_en(HI_TRUE);
}
void vo_drv_set_intf_hdmi_cfg(hi_s32 vo_dev, hal_disp_syncinv *inv, hi_u32 *div_mod)
{
    hi_u32 hd0_div_mod = 0x1;
    hi_bool hdmi_clk_en = 0x1;
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];

    sys_hal_vo_hdmi_clk_en(vo_dev, hdmi_clk_en);
    *div_mod = hd0_div_mod;

    if ((hal_dev_cfg->out_sync == VO_OUTPUT_576P50) ||
        (hal_dev_cfg->out_sync == VO_OUTPUT_480P60)) {
        inv->hs_inv = 1 - inv->hs_inv;
        inv->vs_inv = 1 - inv->vs_inv;
        hal_disp_set_intf_sync_inv(VO_INTF_HDMI, inv);
    } else {
        hal_disp_set_intf_sync_inv(VO_INTF_HDMI, inv);
    }

    if (g_hal_dev_cfg[vo_dev].out_sync == VO_OUTPUT_7680x4320_30) {
        hd0_div_mod = 0;
        *div_mod = hd0_div_mod;
    }
}
void vo_drv_set_intf_mipi_cfg(hi_s32 vo_dev, hi_u32 *div_mod)
{
    hi_bool mipi_clk_en = 0x1;
    hi_u32 hd0_div_mod = 0x1;
    hi_u32 hd1_div_mod = 0x0;

    sys_hal_vo_mipi_clk_en(vo_dev, mipi_clk_en);
    sys_hal_vo_mipi_tx_clk_en(vo_dev, mipi_clk_en);
    sys_hal_vo_mipi_tx_chn_sel(vo_dev);
    if (vo_dev == VO_DEV_DHD0) {
        hd0_div_mod = 0x1;
        *div_mod = hd0_div_mod;
    } else if (vo_dev == VO_DEV_DHD1) {
        hd1_div_mod = 0x0;
        *div_mod = hd1_div_mod;
    }
    hal_disp_set_intf_mux_sel(vo_dev, VO_INTF_MIPI);
}

void vo_drv_get_lcd_ctrl(vo_intf_type intf_type, U_INTF_LCD_CTRL *lcd_ctrl)
{
    switch (intf_type) {
        /* the numbers is register config, not magic numbers */
        case VO_INTF_LCD_8BIT: {
            lcd_ctrl->bits.hdmi_mode = 1;
            lcd_ctrl->bits.lcd_serial_mode = 1;
            lcd_ctrl->bits.lcd_serial_perd = 1;
            lcd_ctrl->bits.lcd_parallel_order = 0;
            lcd_ctrl->bits.lcd_data_inv = 0;
            lcd_ctrl->bits.lcd_parallel_mode = 1;
            break;
        }
        case VO_INTF_LCD_6BIT: {
            lcd_ctrl->bits.lcd_serial_mode = 1;
            lcd_ctrl->bits.lcd_serial_perd = 0;
            lcd_ctrl->bits.lcd_parallel_order = 0;
            lcd_ctrl->bits.lcd_data_inv = 0;
            lcd_ctrl->bits.lcd_parallel_mode = 0;
            break;
        }
        case VO_INTF_LCD_16BIT: {
            lcd_ctrl->bits.lcd_serial_mode = 0;
            lcd_ctrl->bits.lcd_serial_perd = 0;
            lcd_ctrl->bits.lcd_parallel_order = 0;
            lcd_ctrl->bits.lcd_data_inv = 0;
            /* always set lcd_parallel_mode to 1 in parallel mode. */
            lcd_ctrl->bits.lcd_parallel_mode = 1;
            break;
        }
        case VO_INTF_LCD_18BIT: {
            lcd_ctrl->bits.lcd_serial_mode = 0;
            lcd_ctrl->bits.lcd_serial_perd = 0;
            lcd_ctrl->bits.lcd_parallel_order = 0;
            lcd_ctrl->bits.lcd_data_inv = 0;
            /* always set lcd_parallel_mode to 1 in parallel mode. */
            lcd_ctrl->bits.lcd_parallel_mode = 1;
            break;
        }
        case VO_INTF_LCD_24BIT: {
            lcd_ctrl->bits.lcd_serial_mode = 0;
            lcd_ctrl->bits.lcd_serial_perd = 0;
            lcd_ctrl->bits.lcd_parallel_order = 0;
            lcd_ctrl->bits.lcd_data_inv = 0;
            lcd_ctrl->bits.lcd_parallel_mode = 1;
            break;
        }
        default:
            printf("error: unknown lcd type.\n");
            break;
    }
}

void vo_drv_set_intf_lcd_cfg(hi_s32 vo_dev,
    hal_disp_syncinv *inv,
    hi_u32 *div_mod,
    hi_bool *clk_reverse)
{
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];
    vo_intf_type intf_type = hal_dev_cfg->intf_type;
    hi_bool bt_clk_en, lcd_clk_en;
    hi_u32 bt_sel;
    U_INTF_LCD_CTRL LCD_CTRL = {0};

    hal_disp_set_intf_mux_sel(vo_dev, VO_INTF_LCD);
    hal_disp_set_intf_sync_inv(VO_INTF_LCD, inv);

    bt_clk_en = HI_TRUE;
    lcd_clk_en = HI_TRUE;
    bt_sel = vo_dev;
    sys_hal_vo_bt_clk_en(bt_clk_en);
    sys_hal_vo_bt_bp_clk_en(HI_TRUE);
    sys_hal_vo_bt1120_chn_sel(bt_sel);
    sys_hal_vo_lcd_clk_en(lcd_clk_en);

    if (VO_INTF_LCD_8BIT & intf_type) {
        *div_mod = 3; /* 3 register config */
    } else if (VO_INTF_LCD_6BIT & intf_type) {
        *div_mod = 2; /* 2 register config */
    } else if (VO_INTF_LCD_16BIT & intf_type) {
        *div_mod = 0;
    } else if (VO_INTF_LCD_18BIT & intf_type) {
        *div_mod = 0;
    } else if (VO_INTF_LCD_24BIT & intf_type) {
        *clk_reverse = HI_FALSE;
        *div_mod = 0;
    }

    vo_drv_get_lcd_ctrl(intf_type, &LCD_CTRL);

    if (hal_dev_cfg->out_sync != VO_OUTPUT_USER) {
        hal_disp_set_lcd_serial_perd(LCD_CTRL.bits.lcd_serial_perd);
    }

    hal_disp_set_intf_ctrl(intf_type, &(LCD_CTRL.u32));

    return;
}

void vo_drv_set_intf_cfg(hi_s32 vo_dev,
    hal_disp_syncinv *inv,
    hi_u32 *div_mod,
    hi_bool *clk_reverse)
{
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];
    vo_intf_type intf_type = hal_dev_cfg->intf_type;

    if (VO_INTF_BT1120 & hal_dev_cfg->intf_type) {
        hal_disp_set_intf_mux_sel(vo_dev, VO_INTF_BT1120);
        *div_mod = 0;
        vo_drv_set_intf_bt1120_cfg(vo_dev, inv);
    }
    if (VO_INTF_HDMI & hal_dev_cfg->intf_type) {
        vo_drv_set_intf_hdmi_cfg(vo_dev, inv, div_mod);
    }

    if (VO_INTF_MIPI & hal_dev_cfg->intf_type) {
        vo_drv_set_intf_mipi_cfg(vo_dev, div_mod);
    }

    if (vo_drv_is_lcd_intf(intf_type)) {
        vo_drv_set_intf_lcd_cfg(vo_dev, inv, div_mod, clk_reverse);
    }
}

void vo_drv_set_dev_out_pctrl(hi_s32 vo_dev, hi_bool clk_reverse)
{
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];
    vo_intf_sync out_sync;

    out_sync = hal_dev_cfg->out_sync;

    if (out_sync != VO_OUTPUT_USER) {
        sys_hal_vo_hd_out_pctrl(clk_reverse);
    }
}

hi_bool vo_drv_special_work_flow(vo_dev dev)
{
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[dev];

    vo_intf_type type = hal_dev_cfg->intf_type;
    vo_intf_sync sync = hal_dev_cfg->out_sync;
    hi_u32 div_mod = g_user_intfsync_info.dev_div;

    /* only for dhd1 */
    hi_bool flag_dev = (dev == VO_DEV_DHD1);
    /* lcd 8bit screen ota5182 320x240@60, default 4div */
    hi_bool flag_8bit_nonuser = (type == VO_INTF_LCD_8BIT && sync == VO_OUTPUT_320x240_60);
    /* lcd 8bit screen user, 4div */
    hi_bool flag_8bit_4div = (type == VO_INTF_LCD_8BIT && sync == VO_OUTPUT_USER && div_mod == 4);
    /* lcd 6bit screen user, 4div */
    hi_bool flag_6bit_4div = (type == VO_INTF_LCD_6BIT && sync == VO_OUTPUT_USER && div_mod == 4);

    if (flag_dev && (flag_8bit_nonuser || flag_8bit_4div || flag_6bit_4div)) {
        return HI_TRUE;
    }

    return HI_FALSE;
}

void vo_drv_set_dev_div_mod(hi_s32 vo_dev, hi_u32 div_mod)
{
    hal_dev_config *hal_dev_cfg = &g_hal_dev_cfg[vo_dev];
    vo_intf_sync out_sync;

    out_sync = hal_dev_cfg->out_sync;

    if (vo_drv_special_work_flow(vo_dev)) {
        /* do not set dev's div_mode in special work flow */
    } else {
        if (out_sync != VO_OUTPUT_USER) {
            if (vo_dev == 0) {
                sys_hal_vo_hd0_div_mode(vo_dev, div_mod);
            } else if (vo_dev == 1) {
                sys_hal_vo_hd1_div_mode(vo_dev, div_mod);
            }
        }
    }
}

void vo_drv_set_dev_multichn(hi_s32 vo_dev)
{
    hal_multi_chn multi_chn_en;
    multi_chn_en = HAL_MULTICHN_EN_1P1C;
    hal_disp_set_dev_multi_chn_en(vo_dev, multi_chn_en);

    if (VO_INTF_HDMI & g_hal_dev_cfg[vo_dev].intf_type) {
        multi_chn_en = HAL_MULTICHN_EN_2P1C;
        hal_disp_set_dev_multi_chn_en(vo_dev, multi_chn_en);
    }

    if (VO_INTF_MIPI & g_hal_dev_cfg[vo_dev].intf_type) {
        if (vo_dev == VO_DEV_DHD0) {
            multi_chn_en = HAL_MULTICHN_EN_2P1C;
        } else if (vo_dev == VO_DEV_DHD1) {
            multi_chn_en = HAL_MULTICHN_EN_1P1C;
        }
        hal_disp_set_dev_multi_chn_en(vo_dev, multi_chn_en);
    }
}

void vo_drv_set_dev_clip_by_intf(hi_s32 vo_dev)
{
    /* set clip */
    if (VO_INTF_BT1120 & g_hal_dev_cfg[vo_dev].intf_type) {
        const hal_disp_clip clip_data = { 0x40, 0x40, 0x40, 0x3ac, 0x3c0, 0x3c0 }; /* clip register config */
        hal_disp_set_intf_clip(VO_INTF_BT1120, HI_TRUE, &clip_data);
    }

    if (VO_INTF_BT656 & g_hal_dev_cfg[vo_dev].intf_type) {
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

hi_void vo_drv_open(hi_s32 vo_dev)
{
    hal_disp_syncinfo sync_info;
    hi_u16 vtth_line;
    hal_disp_syncinv inv = {0};
    hi_u32 div_mode = 0;
    hi_bool clk_reverse = HI_TRUE;

    vo_drv_set_all_crg_clk(HI_TRUE);

    hal_disp_set_intf_enable(vo_dev, HI_FALSE);

    vo_drv_set_cbm_bkg(vo_dev);

    /* set interface property */
    vo_drv_get_intf_property(vo_dev, &sync_info, &inv);

    vo_drv_set_intf_cfg(vo_dev, &inv, &div_mode, &clk_reverse);

    vo_drv_set_dev_out_pctrl(vo_dev, clk_reverse);

    vo_drv_set_dev_div_mod(vo_dev, div_mode);

    hal_disp_set_intf_sync(vo_dev, &sync_info);

    vo_drv_set_dev_multichn(vo_dev);

    vo_drv_set_dev_clip_by_intf(vo_dev);

    vtth_line = sync_info.vact - vo_drv_get_dev_vtth(vo_dev);
    vo_drv_set_dev_int_mode(vo_dev, &sync_info);
    hal_disp_set_vt_thd(vo_dev, vtth_line);
    hal_disp_set_intf_enable(vo_dev, HI_TRUE);
    vo_drv_dev_int_enable(vo_dev, HI_TRUE);
    hal_disp_set_reg_up(vo_dev);
    g_hal_dev_cfg[vo_dev].enable = HI_TRUE;

    return;
}

hi_void vo_drv_close(hi_s32 vo_dev)
{
    hi_u32 i;
    hi_bool hdmi_clk_en = 0x0;
    hi_bool clk_en = 0x0;
    vo_intf_type intf_type = g_hal_dev_cfg[vo_dev].intf_type;

    hal_disp_set_intf_enable(vo_dev, HI_FALSE);
    hal_disp_set_reg_up(vo_dev);
    /* wait for finishing refresh */
    udelay(25 * 1000); /* delaye 25x1000 us */

    if (VO_INTF_HDMI & g_hal_dev_cfg[vo_dev].intf_type) {
        sys_hal_vo_hdmi_clk_en(vo_dev, hdmi_clk_en);
    }

    if (vo_drv_is_lcd_intf(intf_type)) {
        sys_hal_vo_lcd_clk_en(clk_en);
        sys_hal_vo_bt_clk_en(clk_en);
    }

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
    hi_u32 i;

    hal_sys_set_rd_bus_id(1);

    for (i = HAL_DISP_LAYER_VHD0; i <= HAL_DISP_LAYER_VHD1; i++) {
        hal_layer_set_layer_galpha(i, 255);  /* 255 max alpha */
    }
    for (i = HAL_DISP_LAYER_GFX0; i <= HAL_DISP_LAYER_GFX1; i++) {
        hal_graphic_set_gfx_palpha_range(i, 1);
    }
    vo_drv_def_layer_bind_dev();
    hal_disp_set_clk_gate_enable(1);
    hal_sys_set_axi_master();
    hal_sys_set_outstanding();
    hal_disp_clear_int_status(VO_INTREPORT_ALL);
    for (i = HAL_DISP_LAYER_VHD0; i <= HAL_DISP_LAYER_VHD1; i++) {
        vo_drv_layer_enable(i, HI_FALSE);
        vo_drv_set_layer_data_fmt(i, VO_LAYER_PIXERL_FORMAT_SP_Y_CB_CR_422);
        vo_drv_set_layer_bk_grd(i, VO_BACKGROUD_DEFAULT);
    }

    hal_disp_set_intf_mux_default_sel();

    return;
}

hi_void vo_func_get_zme_comm_pq_cfg(vo_zme_ds_info *ds_info, vo_zme_mode zme_mode,
                                    vo_zme_comm_pq_cfg *comm_pq_cfg)
{
    hi_u32 zme_vprec;
    /* zme config, the numbers is from algorithm, not magic numbers */
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

void vo_drv_set_zme_hinfo(hi_u32 layer, vo_v0_zme_cfg *cfg)
{
    hi_u32 hzme_ck_gt_en;
    hi_u32 out_width;

    hzme_ck_gt_en = cfg->ck_gt_en;
    out_width = cfg->out_width - 1;

    hal_v0_zme_set_hzme_ck_gt_en(hzme_ck_gt_en);
    hal_v0_zme_set_out_width(out_width);
}

void vo_drv_set_zme_hsp(hi_u32 layer, vo_v0_zme_cfg *cfg)
{
    vo_zme_ds_info ds_info = {0};

    ds_info.zme_vprec = ZME_VPREC;
    ds_info.zme_hprec = ZME_HPREC;

    hi_u32 lhfir_en;
    hi_u32 chfir_en;
    hi_u32 lhmid_en;
    hi_u32 chmid_en;
    hi_u32 non_lnr_en = 0;
    hi_u32 lhfir_mode;
    hi_u32 chfir_mode;
    hi_u32 hfir_order;
    hi_u32 hratio;

    lhfir_en = cfg->lhfir_en;
    chfir_en = cfg->chfir_en;
    lhfir_mode = cfg->lhfir_mode;
    chfir_mode = cfg->chfir_mode;
    lhmid_en = 0;
    chmid_en = 0;
    hfir_order = cfg->hfir_order;
    hratio = (cfg->in_width * ds_info.zme_hprec) / cfg->out_width;

    hal_v0_zme_set_lhfir_en(lhfir_en);
    hal_v0_zme_set_chfir_en(chfir_en);
    hal_v0_zme_set_lhmid_en(lhmid_en);
    hal_v0_zme_set_chmid_en(chmid_en);
    hal_v0_zme_set_non_lnr_en(non_lnr_en);
    hal_v0_zme_set_lhfir_mode(lhfir_mode);
    hal_v0_zme_set_chfir_mode(chfir_mode);
    hal_v0_zme_set_hfir_order(hfir_order);
    hal_v0_zme_set_hratio(hratio);
}

void vo_drv_set_zme_hoffset(hi_u32 layer, vo_zme_comm_pq_cfg *comm_pq_cfg)
{
    hi_u32 lhfir_offset;
    hi_u32 chfir_offset;

    lhfir_offset = comm_pq_cfg->lhfir_offset;
    chfir_offset = comm_pq_cfg->chfir_offset;

    hal_v0_zme_set_lhfir_offset(lhfir_offset);
    hal_v0_zme_set_chfir_offset(chfir_offset);
}

void vo_drv_set_zme_zone(void)
{
    hi_u32 zone0_delta = 0;
    hi_u32 zone2_delta = 0;
    hi_u32 zone1_end = 0;
    hi_u32 zone0_end = 0;

    hal_v0_zme_set_zone0_delta(zone0_delta);
    hal_v0_zme_set_zone2_delta(zone2_delta);
    hal_v0_zme_set_zone1_end(zone1_end);
    hal_v0_zme_set_zone0_end(zone0_end);
}

void vo_drv_set_zme_hlshoot(hi_u32 layer, vo_v0_zme_cfg *cfg, vo_zme_comm_pq_cfg *comm_pq_cfg)
{
    hi_u32 hl_shootctrl_en;
    hi_u32 hl_shootctrl_mode;
    hi_u32 hl_flatdect_mode;
    hi_u32 hl_coringadj_en;
    hi_u32 hl_gain;
    hi_u32 hl_coring;

    hl_shootctrl_en = cfg->hl_shootctrl_en;
    hl_shootctrl_mode = cfg->hl_shootctrl_mode;
    hl_flatdect_mode = comm_pq_cfg->hl_flatdect_mode;
    hl_coringadj_en = comm_pq_cfg->hl_coringadj_en;
    hl_gain = comm_pq_cfg->hl_gain;
    hl_coring = comm_pq_cfg->hl_coring;

    hal_v0_zme_set_hl_shootctrl_en(hl_shootctrl_en);
    hal_v0_zme_set_hl_shootctrl_mode(hl_shootctrl_mode);
    hal_v0_zme_set_hl_flatdect_mode(hl_flatdect_mode);
    hal_v0_zme_set_hl_coringadj_en(hl_coringadj_en);
    hal_v0_zme_set_hl_gain(hl_gain);
    hal_v0_zme_set_hl_coring(hl_coring);
}

void vo_drv_set_zme_hcshoot(hi_u32 layer, vo_v0_zme_cfg *cfg, vo_zme_comm_pq_cfg *comm_pq_cfg)
{
    hi_u32 hc_shootctrl_en;
    hi_u32 hc_shootctrl_mode;
    hi_u32 hc_flatdect_mode;
    hi_u32 hc_coringadj_en;
    hi_u32 hc_gain;
    hi_u32 hc_coring;

    hc_shootctrl_en = cfg->hc_shootctrl_en;
    hc_shootctrl_mode = cfg->hc_shootctrl_mode;
    hc_flatdect_mode = comm_pq_cfg->hc_flatdect_mode;
    hc_coringadj_en = comm_pq_cfg->hc_coringadj_en;
    hc_gain = comm_pq_cfg->hc_gain;
    hc_coring = comm_pq_cfg->hc_coring;

    hal_v0_zme_set_hc_shootctrl_en(hc_shootctrl_en);
    hal_v0_zme_set_hc_shootctrl_mode(hc_shootctrl_mode);
    hal_v0_zme_set_hc_flatdect_mode(hc_flatdect_mode);
    hal_v0_zme_set_hc_coringadj_en(hc_coringadj_en);
    hal_v0_zme_set_hc_gain(hc_gain);
    hal_v0_zme_set_hc_coring(hc_coring);
}

void vo_drv_set_zme_vinfo(hi_u32 layer, vo_v0_zme_cfg *cfg)
{
    hi_u32 vzme_ck_gt_en;
    hi_u32 out_pro;
    hi_u32 out_fmt;
    hi_u32 out_height;

    vzme_ck_gt_en = cfg->ck_gt_en;
    out_pro = cfg->out_pro;
    out_fmt = cfg->out_fmt;
    out_height = cfg->out_height - 1;

    hal_v0_zme_set_vzme_ck_gt_en(vzme_ck_gt_en);
    hal_v0_zme_set_out_pro(out_pro);
    hal_v0_zme_set_out_fmt(out_fmt);
    hal_v0_zme_set_out_height(out_height);
}

void vo_drv_set_zme_vsp(hi_u32 layer, vo_v0_zme_cfg *cfg)
{
    vo_zme_ds_info ds_info = {0};
    hi_u32 lvfir_en;
    hi_u32 cvfir_en;
    hi_u32 lvmid_en;
    hi_u32 cvmid_en;
    hi_u32 vfir_1tap_en = 0;
    hi_u32 lvfir_mode;
    hi_u32 cvfir_mode;
    hi_u32 graphdet_en = 0;
    hi_u32 vratio;

    ds_info.zme_vprec = ZME_VPREC;
    ds_info.zme_hprec = ZME_HPREC;

    lvfir_en = cfg->lvfir_en;
    cvfir_en = cfg->cvfir_en;
    lvfir_mode = cfg->lvfir_mode;
    cvfir_mode = cfg->cvfir_mode;
    lvmid_en = 0;
    cvmid_en = 0;
    vratio = (cfg->in_height * ds_info.zme_vprec) / cfg->out_height;

    hal_v0_zme_set_lvfir_en(lvfir_en);
    hal_v0_zme_set_cvfir_en(cvfir_en);
    hal_v0_zme_set_lvmid_en(lvmid_en);
    hal_v0_zme_set_cvmid_en(cvmid_en);
    hal_v0_zme_set_vfir1tap_en(vfir_1tap_en);
    hal_v0_zme_set_lvfir_mode(lvfir_mode);
    hal_v0_zme_set_cvfir_mode(cvfir_mode);
    hal_v0_zme_set_graphdet_en(graphdet_en);
    hal_v0_zme_set_vratio(vratio);
}

void vo_drv_set_zme_voffset(hi_u32 layer, vo_v0_zme_cfg *cfg, vo_zme_comm_pq_cfg *comm_pq_cfg)
{
    hi_u32 vluma_offset;
    hi_u32 vchroma_offset;
    hi_u32 vbluma_offset;
    hi_u32 vbchroma_offset;

    vluma_offset = comm_pq_cfg->vluma_offset;
    vchroma_offset = comm_pq_cfg->vchroma_offset;
    vbluma_offset = comm_pq_cfg->vbluma_offset;
    vbchroma_offset = comm_pq_cfg->vbchroma_offset;

    hal_v0_zme_set_vluma_offset(vluma_offset);
    hal_v0_zme_set_vchroma_offset(vchroma_offset);
    hal_v0_zme_set_vbluma_offset(vbluma_offset);
    hal_v0_zme_set_vbchroma_offset(vbchroma_offset);
}

void vo_drv_set_zme_vlshoot(hi_u32 layer, vo_v0_zme_cfg *cfg, vo_zme_comm_pq_cfg *comm_pq_cfg)
{
    hi_u32 vl_shootctrl_en;
    hi_u32 vl_shootctrl_mode;
    hi_u32 vl_flatdect_mode = 0;
    hi_u32 vl_coringadj_en;
    hi_u32 vl_gain;
    hi_u32 vl_coring;

    vl_shootctrl_en = cfg->vl_shootctrl_en;
    vl_shootctrl_mode = cfg->vl_shootctrl_mode;

    vl_coringadj_en = comm_pq_cfg->vl_coringadj_en;
    vl_gain = comm_pq_cfg->vl_gain;
    vl_coring = comm_pq_cfg->vl_coring;

    hal_v0_zme_set_vl_shootctrl_en(vl_shootctrl_en);
    hal_v0_zme_set_vl_shootctrl_mode(vl_shootctrl_mode);
    hal_v0_zme_set_vl_flatdect_mode(vl_flatdect_mode);
    hal_v0_zme_set_vl_coringadj_en(vl_coringadj_en);
    hal_v0_zme_set_vl_gain(vl_gain);
    hal_v0_zme_set_vl_coring(vl_coring);
}

void vo_drv_set_zme_vcshoot(hi_u32 layer, vo_v0_zme_cfg *cfg, vo_zme_comm_pq_cfg *comm_pq_cfg)
{
    hi_u32 vc_shootctrl_en;
    hi_u32 vc_shootctrl_mode;
    hi_u32 vc_flatdect_mode;
    hi_u32 vc_coringadj_en;
    hi_u32 vc_gain;
    hi_u32 vc_coring;

    vc_shootctrl_en = cfg->vc_shootctrl_en;
    vc_shootctrl_mode = cfg->vc_shootctrl_mode;

    vc_flatdect_mode = comm_pq_cfg->vc_flatdect_mode;
    vc_coringadj_en = comm_pq_cfg->vc_coringadj_en;
    vc_gain = comm_pq_cfg->vc_gain;
    vc_coring = comm_pq_cfg->vc_coring;

    hal_v0_zme_set_vc_shootctrl_en(vc_shootctrl_en);
    hal_v0_zme_set_vc_shootctrl_mode(vc_shootctrl_mode);
    hal_v0_zme_set_vc_flatdect_mode(vc_flatdect_mode);
    hal_v0_zme_set_vc_coringadj_en(vc_coringadj_en);
    hal_v0_zme_set_vc_gain(vc_gain);
    hal_v0_zme_set_vc_coring(vc_coring);
}

hi_void vo_func_set_v0_zme_mode(hi_u32 layer, vo_zme_mode zme_mode, vo_v0_zme_cfg *cfg)
{
    vo_zme_ds_info ds_info = {0};
    vo_zme_comm_pq_cfg comm_pq_cfg = {0};

    ds_info.zme_vprec = ZME_VPREC;
    ds_info.zme_hprec = ZME_HPREC;

    vo_func_get_zme_comm_pq_cfg(&ds_info, zme_mode, &comm_pq_cfg);

    vo_drv_set_zme_hinfo(layer, cfg);
    vo_drv_set_zme_hsp(layer, cfg);
    vo_drv_set_zme_hoffset(layer, &comm_pq_cfg);
    vo_drv_set_zme_zone();
    vo_drv_set_zme_hlshoot(layer, cfg, &comm_pq_cfg);
    vo_drv_set_zme_hcshoot(layer, cfg, &comm_pq_cfg);
    vo_drv_set_zme_vinfo(layer, cfg);
    vo_drv_set_zme_vsp(layer, cfg);
    vo_drv_set_zme_voffset(layer, cfg, &comm_pq_cfg);
    vo_drv_set_zme_vlshoot(layer, cfg, &comm_pq_cfg);
    vo_drv_set_zme_vcshoot(layer, cfg, &comm_pq_cfg);
}

hi_void vo_drv_func_set_v0_hfir_mode(hi_u32 layer, vo_v0_hfir_mode v0_hfir_mode, vo_v0_hfir_cfg *cfg)
{
    hi_u32 ck_gt_en;
    hi_u32 mid_en;
    hi_u32 hfir_mode;
    hi_s32 coef0 = 0;
    hi_s32 coef1 = 0;
    hi_s32 coef2 = 0;
    hi_s32 coef3 = 0;
    hi_s32 coef4 = 0;
    hi_s32 coef5 = 0;
    hi_s32 coef6 = 0;
    hi_s32 coef7 = 0;

    ck_gt_en = cfg->ck_gt_en;
    hfir_mode = cfg->hfir_mode;
    mid_en = cfg->mid_en;
    /* the numbers is from algorithm, not magic numbers */
    if (v0_hfir_mode == VDP_V0_HFIR_TYP) {
        coef0 = -7;
        coef1 = 12;
        coef2 = -17;
        coef3 = 25;
        coef4 = -38;
        coef5 = 58;
        coef6 = -105;
        coef7 = 328;
    }

    hal_v0_hfir_set_ck_gt_en(ck_gt_en);
    hal_v0_hfir_set_mid_en(mid_en);
    hal_v0_hfir_set_hfir_mode(hfir_mode);
    hal_v0_hfir_set_coef0(coef0);
    hal_v0_hfir_set_coef1(coef1);
    hal_v0_hfir_set_coef2(coef2);
    hal_v0_hfir_set_coef3(coef3);
    hal_v0_hfir_set_coef4(coef4);
    hal_v0_hfir_set_coef5(coef5);
    hal_v0_hfir_set_coef6(coef6);
    hal_v0_hfir_set_coef7(coef7);
}

hi_void vo_drv_func_get_cvfir_pq_cfg(
    vo_zme_ds_info *ds_info, vo_zme_mode zme_mode, vo_zme_comm_pq_cfg *comm_pq_cfg)
{
    hi_u32 zme_vprec = ds_info->zme_vprec;

    /* the zme num is from algorithm, not magic num */
    if (zme_mode == VO_ZME_TYP) {
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

hi_void vo_drv_func_set_v1_cvfir_mode(hi_u32 layer, vo_zme_mode zme_mode, vdp_v1_cvfir_cfg *cfg)
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
    out_height = cfg->in_height - 1;
    vratio = (cfg->in_height * ds_info.zme_vprec) / cfg->in_height;

    vo_drv_func_get_cvfir_pq_cfg(&ds_info, zme_mode, &comm_pq_cfg);
    vchroma_offset = comm_pq_cfg.vchroma_offset;
    vbchroma_offset = comm_pq_cfg.vbchroma_offset;

    hal_v1_cvfir_set_vzme_ck_gt_en(vzme_ck_gt_en);
    hal_v1_cvfir_set_out_pro(out_pro);
    hal_v1_cvfir_set_out_fmt(out_fmt);
    hal_v1_cvfir_set_out_height(out_height);
    hal_v1_cvfir_set_cvfir_en(cvfir_en);
    hal_v1_cvfir_set_cvmid_en(cvmid_en);
    hal_v1_cvfir_set_cvfir_mode(cvfir_mode);
    hal_v1_cvfir_set_vratio(vratio);
    hal_v1_cvfir_set_vchroma_offset(vchroma_offset);
    hal_v1_cvfir_set_vbchroma_offset(vbchroma_offset);
}

hi_void vo_drv_func_set_v1_hfir_mode(hi_u32 layer, vdp_v1_hfir_mode v1_hfir_mode, vdp_v1_hfir_cfg *cfg)
{
    hi_u32 ck_gt_en;
    hi_u32 mid_en;
    hi_u32 hfir_mode;

    hi_s32 coef0 = 0;
    hi_s32 coef1 = 0;
    hi_s32 coef2 = 0;
    hi_s32 coef3 = 0;
    hi_s32 coef4 = 0;
    hi_s32 coef5 = 0;
    hi_s32 coef6 = 0;
    hi_s32 coef7 = 0;

    ck_gt_en = cfg->ck_gt_en;
    mid_en = cfg->mid_en;
    hfir_mode = cfg->hfir_mode;

    /* the numbers is from algorithm, not magic numbers */
    if (v1_hfir_mode == VDP_V1_HFIR_TYP) {
        coef0 = -11;
        coef1 = 15;
        coef2 = -20;
        coef3 = 28;
        coef4 = -40;
        coef5 = 61;
        coef6 = -107;
        coef7 = 330;
    }

    hal_v1_hfir_set_ck_gt_en(ck_gt_en);
    hal_v1_hfir_set_mid_en(mid_en);
    hal_v1_hfir_set_hfir_mode(hfir_mode);
    hal_v1_hfir_set_coef0(coef0);
    hal_v1_hfir_set_coef1(coef1);
    hal_v1_hfir_set_coef2(coef2);
    hal_v1_hfir_set_coef3(coef3);
    hal_v1_hfir_set_coef4(coef4);
    hal_v1_hfir_set_coef5(coef5);
    hal_v1_hfir_set_coef6(coef6);
    hal_v1_hfir_set_coef7(coef7);
}

void vo_drv_get_zme_cfg(const vdp_vid_ip_cfg *vid_cfg, vo_v0_zme_cfg *zme_cfg)
{
    /* the numbers is from algorithm, not magic numbers */
    zme_cfg->ck_gt_en = 0;
    zme_cfg->in_height = vid_cfg->vid_ih;
    zme_cfg->out_height = vid_cfg->vid_oh;
    zme_cfg->out_fmt = VDP_PROC_FMT_SP_422;
    zme_cfg->out_pro = 1;
    zme_cfg->lvfir_mode = 1;
    zme_cfg->cvfir_mode = 1;
    zme_cfg->lvmid_en = 0;
    zme_cfg->cvmid_en = 0;
    zme_cfg->vfir_1tap_en = 0;
    zme_cfg->vl_shootctrl_en = 0;
    zme_cfg->vl_shootctrl_mode = 0;
    zme_cfg->vc_shootctrl_en = 0;
    zme_cfg->vc_shootctrl_mode = 0;

    zme_cfg->in_width = vid_cfg->vid_iw;
    zme_cfg->out_width = vid_cfg->vid_ow;
    zme_cfg->lhfir_mode = 1;
    zme_cfg->chfir_mode = 1;
    zme_cfg->lhmid_en = 0;
    zme_cfg->chmid_en = 0;
    zme_cfg->non_lnr_en = 0;
    zme_cfg->hl_shootctrl_en = 0;
    zme_cfg->hl_shootctrl_mode = 0;
    zme_cfg->hc_shootctrl_en = 0;
    zme_cfg->hc_shootctrl_mode = 0;

    zme_cfg->hfir_order = 0;
}

void vo_drv_get_v1_cvfir_cfg(const vdp_vid_ip_cfg *vid_cfg, vdp_v1_cvfir_cfg *v1_cvfir_cfg)
{
    /* the numbers is from algorithm, not magic numbers */
    v1_cvfir_cfg->hfir_order = 0;
    v1_cvfir_cfg->lhfir_en = 0;
    v1_cvfir_cfg->chfir_en = 0;
    v1_cvfir_cfg->lhmid_en = 0;
    v1_cvfir_cfg->chmid_en = 0;
    v1_cvfir_cfg->lhfir_mode = 0;
    v1_cvfir_cfg->chfir_mode = 0;
    v1_cvfir_cfg->hl_shootctrl_en = 0;
    v1_cvfir_cfg->hl_shootctrl_mode = 0;
    v1_cvfir_cfg->hc_shootctrl_en = 0;
    v1_cvfir_cfg->hc_shootctrl_mode = 0;
    v1_cvfir_cfg->lvfir_en = 0;
    v1_cvfir_cfg->lvmid_en = 0;
    v1_cvfir_cfg->lvfir_mode = 0;
    v1_cvfir_cfg->vl_shootctrl_en = 0;
    v1_cvfir_cfg->vl_shootctrl_mode = 0;
    v1_cvfir_cfg->vc_shootctrl_en = 0;
    v1_cvfir_cfg->vc_shootctrl_mode = 0;

    v1_cvfir_cfg->ck_gt_en = 0;
    v1_cvfir_cfg->cvfir_en = 1;
    v1_cvfir_cfg->cvmid_en = 0;
    v1_cvfir_cfg->cvfir_mode = 0;
    v1_cvfir_cfg->out_pro = VDP_RMODE_PROGRESSIVE;
    v1_cvfir_cfg->out_fmt = VDP_PROC_FMT_SP_422;
    v1_cvfir_cfg->in_width = vid_cfg->vid_iw;
    v1_cvfir_cfg->in_height = vid_cfg->vid_ih;
    v1_cvfir_cfg->out_width = vid_cfg->vid_ow;
    v1_cvfir_cfg->out_height = vid_cfg->vid_oh;
}

hi_void vo_vid_set_zme_enable(hi_u32 layer, const vdp_vid_ip_cfg *vid_cfg)
{
    vo_v0_zme_cfg zme_cfg;
    vdp_v1_cvfir_cfg v1_cvfir_cfg;
    vo_v0_hfir_cfg v0_hfir_cfg;
    vdp_v1_hfir_cfg v1_hfir_cfg;

    if (layer == HAL_DISP_LAYER_VHD0) {
        vo_drv_get_zme_cfg(vid_cfg, &zme_cfg);
        /* the numbers is from algorithm, not magic numbers */
        zme_cfg.lhfir_en = 1;
        zme_cfg.chfir_en = 1;
        zme_cfg.lvfir_en = 1;
        zme_cfg.cvfir_en = 1;

        zme_cfg.lhfir_mode = 0;
        zme_cfg.chfir_mode = 0;
        zme_cfg.lvfir_mode = 0;
        zme_cfg.cvfir_mode = 0;

        vo_func_set_v0_zme_mode(layer, VO_ZME_TYP, &zme_cfg);

        if (vid_cfg->hfir_en == 1) {
            v0_hfir_cfg.ck_gt_en = 0;
            v0_hfir_cfg.mid_en = 0;
            v0_hfir_cfg.hfir_mode = XDP_V0_HFIR_FILT;

            vo_drv_func_set_v0_hfir_mode(layer, VDP_V0_HFIR_TYP, &v0_hfir_cfg);
        }
    } else if (layer == HAL_DISP_LAYER_VHD1) {
        vo_drv_get_v1_cvfir_cfg(vid_cfg, &v1_cvfir_cfg);
        vo_drv_func_set_v1_cvfir_mode(layer, VO_ZME_TYP, &v1_cvfir_cfg);

        if (vid_cfg->hfir_en == 1) {
            v1_hfir_cfg.ck_gt_en = 0;
            v1_hfir_cfg.mid_en = 0;
            v1_hfir_cfg.hfir_mode = XDP_HFIR_FILT;

            vo_drv_func_set_v1_hfir_mode(layer, VDP_V1_HFIR_TYP, &v1_hfir_cfg);
        }
    }
}

void vo_drv_get_gfx_zme_commpqcfg(vo_zme_ds_info *ds_info,
    gf_g0_zme_mode g0_zme_mode,
    vo_gfx_zme_comm_pq_cfg *gfx_zme_comm_pq_cfg)
{
    if (g0_zme_mode == VDP_G0_ZME_TYP) {
        gfx_zme_comm_pq_cfg->lhfir_offset = 0;
        gfx_zme_comm_pq_cfg->chfir_offset = 0;
        gfx_zme_comm_pq_cfg->vtp_offset = 0;
        gfx_zme_comm_pq_cfg->vbtm_offset = (-1) * (hi_s64)ds_info->zme_vprec / 2; /* 2 cal offset */
    }
}

void vo_drv_set_gfx_zme_hinfo(hi_u32 layer, const gf_g0_zme_cfg *cfg)
{
    hi_u32 ck_gt_en = cfg->ck_gt_en;
    hi_u32 out_width = cfg->out_width;

    hal_g0_zme_set_ck_gt_en(ck_gt_en);
    hal_g0_zme_set_out_width(out_width);
}

void vo_drv_set_gfx_zme_hsp(hi_u32 layer, const gf_g0_zme_cfg *cfg, const vo_gfx_zme_comm_pq_cfg *gfx_zme_comm_pq_cfg)
{
    vo_zme_ds_info ds_info = {0};
    hi_u32 hfir_order = 1;

    hi_u32 hfir_en = cfg->hfir_en;
    hi_u32 ahfir_mid_en = cfg->ahmid_en;
    hi_u32 lhfir_mid_en = cfg->lhmid_en;
    hi_u32 chfir_mid_en = cfg->lhmid_en;
    hi_u32 lhfir_mode = cfg->lhfir_mode;
    hi_u32 ahfir_mode = cfg->ahfir_mode;
    hi_s32 lhfir_offset;
    hi_s32 chfir_offset;
    ds_info.zme_hprec = ZME_HPREC;
    ds_info.zme_vprec = ZME_VPREC;
    hi_u32 hratio = (cfg->in_width * ds_info.zme_hprec) / cfg->out_width;

    lhfir_offset = gfx_zme_comm_pq_cfg->lhfir_offset;
    chfir_offset = gfx_zme_comm_pq_cfg->chfir_offset;

    hal_g0_zme_set_hfir_en(hfir_en);
    hal_g0_zme_set_ahfir_mid_en(ahfir_mid_en);
    hal_g0_zme_set_lhfir_mid_en(lhfir_mid_en);
    hal_g0_zme_set_chfir_mid_en(chfir_mid_en);
    hal_g0_zme_set_lhfir_mode(lhfir_mode);
    hal_g0_zme_set_ahfir_mode(ahfir_mode);
    hal_g0_zme_set_hfir_order(hfir_order);
    hal_g0_zme_set_hratio(hratio);
    hal_g0_zme_set_lhfir_offset(lhfir_offset);
    hal_g0_zme_set_chfir_offset(chfir_offset);
}

void vo_drv_set_gfx_zme_vinfo(hi_u32 layer, const gf_g0_zme_cfg *cfg)
{
    hi_u32 out_pro = cfg->out_pro;
    hi_u32 out_height = cfg->out_height;
    hal_g0_zme_set_out_pro(out_pro);
    hal_g0_zme_set_out_height(out_height);
}

void vo_drv_set_gfx_zme_vsp(hi_u32 layer, const gf_g0_zme_cfg *cfg, const vo_gfx_zme_comm_pq_cfg *gfx_zme_comm_pq_cfg)
{
    vo_zme_ds_info ds_info = {0};
    hi_u32 vfir_en = cfg->vfir_en;

    hi_u32 avfir_mid_en = cfg->avmid_en;
    hi_u32 lvfir_mid_en = cfg->lvmid_en;
    hi_u32 cvfir_mid_en = cfg->lvmid_en;
    hi_u32 lvfir_mode = cfg->lvfir_mode;
    hi_u32 avfir_mode = cfg->avfir_mode;
    hi_s32 vtp_offset;
    hi_s32 vbtm_offset;
    ds_info.zme_hprec = ZME_HPREC;
    ds_info.zme_vprec = ZME_VPREC;
    hi_u32 vratio = (cfg->in_height * ds_info.zme_vprec) / cfg->out_height;

    vtp_offset = gfx_zme_comm_pq_cfg->vtp_offset;
    vbtm_offset = gfx_zme_comm_pq_cfg->vbtm_offset;
    hal_g0_zme_set_vfir_en(vfir_en);
    hal_g0_zme_set_avfir_mid_en(avfir_mid_en);
    hal_g0_zme_set_lvfir_mid_en(lvfir_mid_en);
    hal_g0_zme_set_cvfir_mid_en(cvfir_mid_en);
    hal_g0_zme_set_lvfir_mode(lvfir_mode);
    hal_g0_zme_set_vafir_mode(avfir_mode);
    hal_g0_zme_set_vratio(vratio);
    hal_g0_zme_set_vtp_offset(vtp_offset);
    hal_g0_zme_set_vbtm_offset(vbtm_offset);
}

hi_void gf_func_set_g0_zme_mode(hi_u32 layer, gf_g0_zme_mode g0_zme_mode, const gf_g0_zme_cfg *cfg)
{
    vo_zme_ds_info ds_info = {0};
    vo_gfx_zme_comm_pq_cfg gfx_zme_comm_pq_cfg = {0};

    ds_info.zme_hprec = ZME_HPREC;
    ds_info.zme_vprec = ZME_VPREC;

    vo_drv_get_gfx_zme_commpqcfg(&ds_info, g0_zme_mode, &gfx_zme_comm_pq_cfg);

    vo_drv_set_gfx_zme_hinfo(layer, cfg);
    vo_drv_set_gfx_zme_hsp(layer, cfg, &gfx_zme_comm_pq_cfg);
    vo_drv_set_gfx_zme_vinfo(layer, cfg);
    vo_drv_set_gfx_zme_vsp(layer, cfg, &gfx_zme_comm_pq_cfg);
}

hi_bool graphic_drv_enable_zme(hi_u32 layer, const gf_g0_zme_cfg *zme_cfg, hi_bool enable_zme)
{
    gf_g0_zme_cfg drv_zme_cfg;

    if ((zme_cfg->in_width == 0) ||
        (zme_cfg->in_height == 0) ||
        (zme_cfg->out_width == 0) ||
        (zme_cfg->out_height == 0)) {
        printf("%s,%d,error: args invalid\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    drv_zme_cfg.ck_gt_en = 0;
    drv_zme_cfg.out_pro = VDP_RMODE_PROGRESSIVE;

    /* the numbers is from algorithm, not magic numbers */
    drv_zme_cfg.in_width = zme_cfg->in_width;
    drv_zme_cfg.in_height = zme_cfg->in_height;
    drv_zme_cfg.out_width = zme_cfg->out_width;
    drv_zme_cfg.out_height = zme_cfg->out_height;
    drv_zme_cfg.lhmid_en = 1;
    drv_zme_cfg.ahmid_en = 1;
    drv_zme_cfg.lhfir_mode = 1;
    drv_zme_cfg.ahfir_mode = 1;
    drv_zme_cfg.lvmid_en = 1;
    drv_zme_cfg.avmid_en = 1;
    drv_zme_cfg.lvfir_mode = 1;
    drv_zme_cfg.avfir_mode = 1;

    if (enable_zme) {
        drv_zme_cfg.hfir_en = 1;
        drv_zme_cfg.vfir_en = 1;
        drv_zme_cfg.lhfir_mode = 0;
        drv_zme_cfg.ahfir_mode = 0;

        gf_func_set_g0_zme_mode(HAL_DISP_LAYER_GFX0, VDP_G0_ZME_TYP, &drv_zme_cfg);
    } else {
        drv_zme_cfg.hfir_en = 0;
        drv_zme_cfg.vfir_en = 0;

        gf_func_set_g0_zme_mode(HAL_DISP_LAYER_GFX0, VDP_G0_ZME_TYP, &drv_zme_cfg);
    }

    return HI_TRUE;
}

