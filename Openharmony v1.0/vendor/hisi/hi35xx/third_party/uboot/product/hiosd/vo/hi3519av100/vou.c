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

#include "vou.h"
#include "vou_drv.h"
#include "vou_hal.h"
#include <cpu_func.h>

static hi_u32 g_bg_color[2] = { 0xFF, 0xFF }; /* 2 devices 0xFF default blue */

static hi_bool g_inited = HI_FALSE;
static hi_rect g_max_rect = {0};

#define vo_align(val, align) (((val) + (align) - 1) & (~((align) - 1)))

static hi_void vo_dcache_range(unsigned long start_addr, hi_u64 size)
{
    if (dcache_status()) {
        flush_dcache_range(start_addr, start_addr + size);
    }
}

static unsigned int gfx_convert_layer(unsigned int layer)
{
    unsigned int gfx_layer;

    /* hard cursor is not supported. */
    switch (layer) {
        case 0: /* 0 layer */
            gfx_layer = VO_LAYER_G0;
            break;
        case 1: /* 1 layer */
            gfx_layer = VO_LAYER_G1;
            break;
        default:
            gfx_layer = VO_LAYER_G0;
            break;
    }
    return gfx_layer;
}

static hal_disp_layer gfx_convert_to_hal_layer(unsigned int layer)
{
    hal_disp_layer hal_gfx_layer;

    /* hard cursor is not supported. */
    switch (layer) {
        case 0: /* 0 layer */
            hal_gfx_layer = HAL_DISP_LAYER_GFX0;
            break;
        case 1: /* 1 layer */
            hal_gfx_layer = HAL_DISP_LAYER_GFX1;
            break;
        default:
            hal_gfx_layer = HAL_DISP_LAYER_GFX0;
            break;
    }
    return hal_gfx_layer;
}
static hi_vo_layer video_layer_convert(unsigned int layer)
{
    hi_vo_layer video_layer;

    /* hard cursor is not supported. */
    switch (layer) {
        case 0: /* 0 layer */
            video_layer = VO_LAYER_VHD0;
            break;
        case 1: /* 1 layer */
            video_layer = VO_LAYER_VHD1;
            break;
        default:
            video_layer = VO_LAYER_VHD0;
            break;
    }
    return video_layer;
}

static hal_disp_layer video_layer_convert_to_hal(unsigned int layer)
{
    hal_disp_layer hal_video_layer;

    /* hard cursor is not supported. */
    switch (layer) {
        case 0: /* 0 layer */
            hal_video_layer = HAL_DISP_LAYER_VHD0;
            break;
        case 1: /* 1 layer */
            hal_video_layer = HAL_DISP_LAYER_VHD1;
            break;
        default:
            hal_video_layer = HAL_DISP_LAYER_VHD0;
            break;
    }
    return hal_video_layer;
}

int set_vobg(unsigned int dev, unsigned int rgb)
{
    if (dev < 2) { /* 2 device */
        g_bg_color[dev] = rgb;
    }
    return 0;
}

hi_void vo_set_disp_max_size(vo_hal_dev vo_dev, vo_intf_sync vo_out_mode)
{
    /* default is 720x576 */
    hi_u32 max_width = 720;
    hi_u32 max_height = 576;

    /* to get the width and height of the sync, not magic num */
    switch (vo_out_mode) {
        case VO_OUTPUT_PAL:
        case VO_OUTPUT_576P50:
            max_width = 720;
            max_height = 576;
            break;
        case VO_OUTPUT_NTSC:
        case VO_OUTPUT_480P60:
            max_width = 720;
            max_height = 480;
            break;
        case VO_OUTPUT_720P60:
        case VO_OUTPUT_720P50:
            max_width = 1280;
            max_height = 720;
            break;
        case VO_OUTPUT_1080I50:
        case VO_OUTPUT_1080I60:
        case VO_OUTPUT_1080P24:
        case VO_OUTPUT_1080P25:
        case VO_OUTPUT_1080P30:
        case VO_OUTPUT_1080P50:
        case VO_OUTPUT_1080P60:
            max_width = 1920;
            max_height = 1080;
            break;
        case VO_OUTPUT_800x600_60:
        case VO_OUTPUT_800x600_50:
            max_width = 800;
            max_height = 600;
            break;
        case VO_OUTPUT_1024x768_60:
            max_width = 1024;
            max_height = 768;
            break;
        case VO_OUTPUT_1280x1024_60:
            max_width = 1280;
            max_height = 1024;
            break;
        case VO_OUTPUT_1366x768_60:
            max_width = 1366;
            max_height = 768;
            break;
        case VO_OUTPUT_1440x900_60:
            max_width = 1440;
            max_height = 900;
            break;
        case VO_OUTPUT_1280x800_60:
            max_width = 1280;
            max_height = 800;
            break;
        case VO_OUTPUT_1600x1200_60:
            max_width = 1600;
            max_height = 1200;
            break;
        case VO_OUTPUT_1680x1050_60:
            max_width = 1680;
            max_height = 1050;
            break;
        case VO_OUTPUT_1920x1200_60:
            max_width = 1920;
            max_height = 1200;
            break;
        case VO_OUTPUT_640x480_60:
            max_width = 640;
            max_height = 480;
            break;
        case VO_OUTPUT_1920x2160_30:
            max_width = 1920;
            max_height = 2160;
            break;
        case VO_OUTPUT_2560x1440_30:
        case VO_OUTPUT_2560x1440_60:
            max_width = 2560;
            max_height = 1440;
            break;
        case VO_OUTPUT_2560x1600_60:
            max_width = 2560;
            max_height = 1600;
            break;
        case VO_OUTPUT_3840x2160_24:
        case VO_OUTPUT_3840x2160_25:
        case VO_OUTPUT_3840x2160_30:
        case VO_OUTPUT_3840x2160_50:
        case VO_OUTPUT_3840x2160_60:
            max_width = 3840;
            max_height = 2160;
            break;
        case VO_OUTPUT_4096x2160_24:
        case VO_OUTPUT_4096x2160_25:
        case VO_OUTPUT_4096x2160_30:
        case VO_OUTPUT_4096x2160_50:
        case VO_OUTPUT_4096x2160_60:
            max_width = 4096;
            max_height = 2160;
            break;
        case VO_OUTPUT_320x240_50:
        case VO_OUTPUT_320x240_60: /* just for hi3518ev200 hi3519 */
            max_width = 320;
            max_height = 240;
            break;
        case VO_OUTPUT_240x320_50: /* just for hi3518ev200 hi3519 */
        case VO_OUTPUT_240x320_60:
            max_width = 240;
            max_height = 320;
            break;
        case VO_OUTPUT_720x1280_60:
            max_width = 720;
            max_height = 1280;
            break;
        case VO_OUTPUT_1080x1920_60:
            max_width = 1080;
            max_height = 1920;
            break;
        case VO_OUTPUT_7680x4320_30:
            max_width = 7680;
            max_height = 4320;
            break;

        default:
            max_width = 1920;
            max_height = 1080;
    }

    g_max_rect.width = max_width;
    g_max_rect.height = max_height;
}

int start_vo(unsigned int dev, unsigned int type, unsigned int sync)
{
    if (g_inited == HI_FALSE) {
        sys_hal_set_vo_low_power_ctrl(HI_TRUE);
        sys_hal_vo_bus_reset_sel(HI_FALSE);

        /* open clk */
        vo_drv_set_all_crg_clk(HI_TRUE);
        vo_drv_board_init();
        hal_sys_control();

        g_inited = HI_TRUE;
    }

    if ((dev == VO_DEV_DHD0) || (dev == VO_DEV_DHD1)) {
        sys_hal_vo_dev_clk_en(dev, HI_TRUE);
    }

    vo_drv_def_layer_bind_dev();
    vo_set_disp_max_size(dev, sync);
    vo_drv_set_dev_intf_type(dev, type);
    vo_drv_set_dev_out_sync(dev, sync);
    vo_drv_set_dev_bk_grd(dev, g_bg_color[dev]);
    vo_drv_set_dev_clk(dev);
    vo_drv_open(dev);

    return 0;
}

int stop_vo(unsigned int dev)
{
    vo_drv_close(dev);
    sys_hal_vo_dev_clk_en(dev, HI_FALSE);

    return 0;
}

static hi_void video_layer_set_zme_cfg(unsigned int layer, const hi_rect *disp_rect)
{
    vdp_vid_ip_cfg vid_cfg = {0};

    vid_cfg.csc_en = 0;
    vid_cfg.hfir_en = 1;
    vid_cfg.vid_iw = disp_rect->width;
    vid_cfg.vid_ih = disp_rect->height;

    vid_cfg.vid_ow = disp_rect->width;
    vid_cfg.vid_oh = disp_rect->height;
    vid_cfg.zme_en = HI_FALSE;
    vo_vid_set_zme_enable(layer, &vid_cfg);
}

static hi_void video_layer_set_csc_by_intf(unsigned int layer, vo_intf_type intf_type)
{
    hi_vo_layer vo_layer;
    hal_disp_layer hal_video_layer;
    vo_csc csc;
    csc_coef_param csc_coef;

    vo_layer = video_layer_convert(layer);
    hal_video_layer = video_layer_convert_to_hal(layer);

    if ((intf_type & VO_INTF_MIPI) ||
        (intf_type & VO_INTF_MIPI_SLAVE)) {
        /* do yuv to rgb. */
        csc.csc_matrix = VO_CSC_MATRIX_BT709_TO_RGB_PC;
        csc.luma = 50; /* 50 default value */
        csc.contrast = 50; /* 50 default value */
        csc.hue = 50; /* 50 default value */
        csc.satuature = 50; /* 50 default value */
        csc_coef.csc_scale2p = GFX_CSC_SCALE;
        csc_coef.csc_clip_min = GFX_CSC_CLIP_MIN;
        csc_coef.csc_clip_max = GFX_CSC_CLIP_MAX;
        /* do rgb to yuv. */
        vo_drv_set_csc_coef(hal_video_layer, &csc, &csc_coef);

        hal_layer_set_csc_en(vo_layer, HI_TRUE);
    } else {
        /* do rgb to rgb or do nothing. */
        hal_layer_set_csc_en(vo_layer, HI_FALSE);
    }
}

int start_videolayer(unsigned int layer, unsigned long addr, unsigned int strd, hi_vo_rect layer_rect)
{
    int i;
    hi_rect disp_rect = { layer_rect.x, layer_rect.y, layer_rect.w, layer_rect.h };
    hi_vo_layer vo_layer;
    hal_disp_layer hal_video_layer;
    const hi_s32 as32_hfir_coef[2][8] = { /* 2 8 hifb coef array */
        { 0x3f9, 0xc, 0x3ef, 0x19, 0x3da, 0x3a, 0x397, 0x148 },
        { 0x3f5, 0xf, 0x3ec, 0x1c, 0x3d8, 0x3d, 0x395, 0x14a }
    };
    vo_intf_type intf_type;

    vo_dcache_range(addr, strd * layer_rect.h * 3 / 2); /* 3 / 2 times */

    vo_layer = video_layer_convert(layer);
    hal_video_layer = video_layer_convert_to_hal(layer);
    hal_layer_set_layer_data_fmt(layer, VO_LAYER_PIXERL_FORMAT_SP_Y_CB_CR_420);

    intf_type = vo_drv_get_dev_intf_type(layer);

    video_layer_set_csc_by_intf(layer, intf_type);

    for (i = 0; i <= HAL_DISP_LAYER_VHD1; i++) {
        hal_video_set_hfir_mode(i, HAL_HFIRMODE_COPY);
        hal_video_set_hfir_coef(i, as32_hfir_coef[i]);
    }

    hal_video_hfir_set_ck_gt_en(layer, HI_TRUE);

    hal_video_set_layer_disp_rect(layer, &disp_rect);
    hal_video_set_layer_video_rect(layer, &disp_rect);
    hal_layer_set_layer_in_rect(layer, &disp_rect);
    hal_layer_set_layer_galpha(layer, 255); /* 255 max alpha */
    hal_layer_set_src_resolution(layer, &disp_rect);

    hal_layer_set_zme_enable(layer, HAL_DISP_ZMEMODE_ALL, HI_FALSE);

    video_layer_set_zme_cfg(layer, &disp_rect);

    hal_layer_set_zme_info(layer, disp_rect.width, disp_rect.height, HAL_DISP_ZME_OUTFMT422);

    /* area 0 */
    hal_video_set_multi_area_l_addr(layer, 0, addr, strd);
    hal_video_set_multi_area_c_addr(layer, 0, addr + strd * vo_align(layer_rect.h, 16), strd); /* align 16 */

    hal_layer_enable_layer(vo_layer, HI_TRUE);
    hal_layer_set_reg_up(hal_video_layer);

    return 0;
}

int stop_videolayer(unsigned int layer)
{
    hi_vo_layer vo_layer;
    hal_disp_layer hal_video_layer;

    vo_layer = video_layer_convert(layer);
    hal_video_layer = video_layer_convert_to_hal(layer);

    hal_layer_enable_layer(vo_layer, HI_FALSE);
    hal_layer_set_reg_up(hal_video_layer);

    return 0;
}

int start_gx(unsigned int layer, unsigned long addr, unsigned int strd, hi_vo_rect gx_rect)
{
    hi_rect disp_rect = { gx_rect.x, gx_rect.y, gx_rect.w, gx_rect.h };
    hi_vo_layer vo_layer;
    hal_disp_layer hal_gfx_layer;
    vo_intf_type intf_type;
    vo_csc gfx_csc;
    csc_coef_param csc_coef;

    vo_layer = gfx_convert_layer(layer);
    hal_gfx_layer = gfx_convert_layer(layer);
    intf_type = vo_drv_get_dev_intf_type(layer);

    vo_dcache_range(addr, strd * gx_rect.h);

    hal_graphic_set_gfx_ext(vo_layer, HAL_GFX_BITEXTEND_3RD);
    hal_graphic_set_gfx_palpha(vo_layer, HI_TRUE, HI_TRUE, 0xff, 0xff); /* 0xff max alpha */
    hal_layer_set_layer_galpha(vo_layer, 0xff); /* 0xff max alpha */
    hal_graphic_set_gfx_pre_mult(vo_layer, HI_FALSE);

    /* for mipi_tx, close csc */
    if ((intf_type & VO_INTF_MIPI) ||
        (intf_type & VO_INTF_MIPI_SLAVE)) {
        hal_layer_set_csc_en(vo_layer, HI_FALSE);
    } else {
        gfx_csc.csc_matrix = VO_CSC_MATRIX_RGB_TO_BT601_TV;
        gfx_csc.luma = 50; /* 50 default value */
        gfx_csc.contrast = 50; /* 50 default value */
        gfx_csc.hue = 50; /* 50 default value */
        gfx_csc.satuature = 50; /* 50 default value */
        csc_coef.csc_scale2p = GFX_CSC_SCALE;
        csc_coef.csc_clip_min = GFX_CSC_CLIP_MIN;
        csc_coef.csc_clip_max = GFX_CSC_CLIP_MAX;
        /* do rgb to yuv. */
        vo_drv_set_csc_coef(hal_gfx_layer, &gfx_csc, &csc_coef);
        hal_layer_set_csc_en(vo_layer, HI_TRUE);
    }

    hal_graphic_set_gfx_addr(vo_layer, addr);
    hal_graphic_set_gfx_stride(vo_layer, strd >> 4); /* 4 to set register */
    hal_layer_set_layer_in_rect(vo_layer, &disp_rect);

    hal_video_set_layer_disp_rect(vo_layer, &disp_rect);
    hal_video_set_layer_video_rect(vo_layer, &disp_rect);

    hal_gfx_set_src_resolution(vo_layer, &disp_rect);

    hal_layer_set_layer_data_fmt(vo_layer, HAL_INPUTFMT_ARGB_1555);

    hal_layer_enable_layer(vo_layer, HI_TRUE);
    hal_layer_set_reg_up(hal_gfx_layer);

    return 0;
}

int stop_gx(unsigned int layer)
{
    hi_vo_layer vo_layer;
    hal_disp_layer hal_gfx_layer;

    vo_layer = gfx_convert_layer(layer);
    hal_gfx_layer = gfx_convert_to_hal_layer(layer);

    hal_layer_set_reg_up(vo_layer);
    hal_layer_enable_layer(vo_layer, HI_FALSE);
    hal_layer_set_reg_up(hal_gfx_layer);

    return 0;
}

