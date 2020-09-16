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

#include "drv_vo_dev.h"
#include "drv_vo.h"
#include "hal_vo.h"
#include "hi_math.h"
#include "vo.h"
#include <common.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */
#if VO_DESC("UBOOT_VO")

#define VO_VGA_GAIN_DEF                 0xB
#define VO_CVBS_DAC_GC_DEF_PAL          0x36
#define VO_CVBS_DAC_GC_DEF_NTSC         0x35

#if VO_DESC("dev")

hi_void vo_drv_set_dev_user_intf_sync_attr(hi_vo_dev dev, const hi_vo_user_sync_info *sync_info)
{
    hi_mpp_chn mpp_chn = {0};
    hi_u32 hd_clk_sel = 0;
    hi_u32 fb_div;
    hi_u32 frac;
    hi_u32 ref_div;
    hi_u32 post_div1;
    hi_u32 post_div2;
    const hi_vo_pll *vo_pll = &sync_info->user_sync_attr.vo_pll;

    mpp_chn.mod_id = HI_ID_VO;
    mpp_chn.dev_id = dev;
    mpp_chn.chn_id = 0;

    fb_div = vo_pll->fb_div;
    frac = vo_pll->frac;
    ref_div = vo_pll->ref_div;
    post_div1 = vo_pll->post_div1;
    post_div2 = vo_pll->post_div2;

    if ((dev == VO_DEV_DHD0) || (dev == VO_DEV_DHD1)) {
        if ((sync_info->user_sync_attr.clk_src == HI_VO_CLK_SRC_PLL) ||
            (sync_info->user_sync_attr.clk_src == HI_VO_CLK_SRC_PLL_FOUT4)) {
            /* clk source */
            if (sync_info->user_sync_attr.clk_src == HI_VO_CLK_SRC_PLL) {
                hd_clk_sel = 0;
            } else {
                hd_clk_sel = 1;
            }
            call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HD_CLK_SEL, &hd_clk_sel);
            /* clk value */
            call_sys_drv_ioctrl(&mpp_chn, SYS_VO_PLL_FBDIV_SET, &fb_div);
            call_sys_drv_ioctrl(&mpp_chn, SYS_VO_PLL_FRAC_SET, &frac);
            call_sys_drv_ioctrl(&mpp_chn, SYS_VO_PLL_REFDIV_SET, &ref_div);
            call_sys_drv_ioctrl(&mpp_chn, SYS_VO_PLL_POSTDIV1_SET, &post_div1);
            call_sys_drv_ioctrl(&mpp_chn, SYS_VO_PLL_POSTDIV2_SET, &post_div2);
        }
    }
}

hi_void vo_drv_set_dev_div(hi_vo_dev dev, hi_u32 dev_div)
{
    hi_mpp_chn mpp_chn = {0};
    hi_u32 div_mode = dev_div - 1;
    hi_vo_intf_type intf_type;

    mpp_chn.mod_id = HI_ID_VO;
    mpp_chn.dev_id = dev;
    mpp_chn.chn_id = 0;

    if (dev == VO_DEV_DHD0) {
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HD0_DIV_MOD, &div_mode);
    } else if (dev == VO_DEV_DHD1) {
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HD1_DIV_MOD, &div_mode);
    } else if (dev == VO_DEV_DSD0) {
        if (dev_div == VO_INTF_CVBS_DIV_MODE) { /* if 4div, 0 to regs */
            div_mode = 0;
        }
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_SD_CLK_DIV, &div_mode);
    }

    intf_type = vo_drv_get_dev_intf_type(dev);
    if (((HI_VO_INTF_RGB_6BIT & intf_type)
        || (HI_VO_INTF_RGB_8BIT & intf_type))) {
        if (dev_div == VO_INTF_RGB_DIV_MODE_3) { /* 3div */
            hal_disp_set_lcd_serial_perd(0);
        } else {
            hal_disp_set_lcd_serial_perd(1);
        }
    }
    return;
}

static hi_void vo_drv_dev_set_hdmi_ssc_vdp_div(hi_vo_dev dev, hi_u32 hdmi_ssc_vdp_div)
{
    hi_mpp_chn mpp_chn;

    vo_drv_set_dev_mpp_chn(dev, &mpp_chn);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HDMI_SSC_VDP_DIV, &hdmi_ssc_vdp_div);
}

hi_void vo_drv_set_hdmi_div(hi_vo_dev dev, hi_u32 pre_div)
{
    vo_drv_dev *dev_ctx = HI_NULL;

    dev_ctx = vo_drv_get_dev_ctx(dev);
    if (vo_drv_is_hdmi_intf(dev_ctx->vou_attr.intf_type)) {
        vo_drv_dev_set_hdmi_ssc_vdp_div(dev, pre_div - 1);
    }
}

static hi_vo_intf_type vou_drv_get_dev_supported_intf(hi_void)
{
    hi_vo_intf_type dev_support_intf;
#ifdef CHIP_HI3520DV500
    dev_support_intf = HI_VO_INTF_HDMI |
                       HI_VO_INTF_BT1120 |
                       HI_VO_INTF_BT656 |
                       HI_VO_INTF_VGA |
                       HI_VO_INTF_RGB_16BIT |
                       HI_VO_INTF_RGB_18BIT |
                       HI_VO_INTF_RGB_24BIT;
#else
    dev_support_intf = HI_VO_INTF_HDMI |
                       HI_VO_INTF_BT1120 |
                       HI_VO_INTF_BT656 |
                       HI_VO_INTF_VGA;
#endif
    return dev_support_intf;
}

static hi_vo_intf_type vou_drv_get_dev_homologous_intf(hi_void)
{
    hi_vo_intf_type homologous_intf =  HI_VO_INTF_HDMI |
                                       HI_VO_INTF_BT1120 |
                                       HI_VO_INTF_VGA;
    return homologous_intf;
}

static hi_s32 vou_drv_check_dhd_homologous_intf(hi_vo_dev dev, hi_vo_intf_type intf_type)
{
    hi_vo_intf_type homologous_intf = vou_drv_get_dev_homologous_intf();
#ifdef CHIP_HI3520DV500
    if ((intf_type & ~(homologous_intf)) &&
        (intf_type & ~(HI_VO_INTF_BT656)) &&
        (intf_type & ~(HI_VO_INTF_RGB_16BIT)) &&
        (intf_type & ~(HI_VO_INTF_RGB_18BIT)) &&
        (intf_type & ~(HI_VO_INTF_RGB_24BIT))) {
        vo_err_trace("device HD%d, does not support homologous intf(%d)!\n", dev, intf_type);
        return HI_ERR_VO_NOT_SUPPORT;
    }
#else
    if ((intf_type & ~(homologous_intf)) &&
        (intf_type & ~(HI_VO_INTF_BT656))) {
        vo_err_trace("device HD%d, does not support homologous intf(%d)!\n", dev, intf_type);
        return HI_ERR_VO_NOT_SUPPORT;
    }
#endif
    return HI_SUCCESS;
}

static hi_s32 vou_drv_check_dhd_intf(hi_vo_dev dev, hi_vo_intf_type intf_type)
{
    hi_vo_intf_type dev_support_intf = vou_drv_get_dev_supported_intf();
    if ((intf_type & ~(dev_support_intf)) || (intf_type == 0)) {
        vo_err_trace("device HD%d does not support intf(%d)!\n", dev, intf_type);
        return HI_ERR_VO_NOT_SUPPORT;
    }

    return vou_drv_check_dhd_homologous_intf(dev, intf_type);
}

static hi_s32 vou_drv_check_intf_share(hi_vo_dev dev, hi_vo_intf_type intf_type)
{
    vo_drv_dev *drv_dev_ctx = HI_NULL;

    hi_vo_intf_type dev_support_intf = vou_drv_get_dev_supported_intf();
    if ((dev != VO_DEV_DHD0) && (dev != VO_DEV_DHD1)) {
        return HI_SUCCESS;
    }

    drv_dev_ctx = vo_drv_get_dev_ctx(1 - dev);
    if (drv_dev_ctx->config == HI_TRUE) {
        if ((intf_type & drv_dev_ctx->vou_attr.intf_type) & (dev_support_intf)) {
            vo_err_trace("vo(%d), the intf %d is used in hd(%d) !\n",
                dev, intf_type & drv_dev_ctx->vou_attr.intf_type, (1 - dev));
            return HI_ERR_VO_NOT_SUPPORT;
        }
    }

    return HI_SUCCESS;
}

hi_s32 vou_drv_check_dev_intf(hi_vo_dev dev, hi_vo_intf_type intf_type)
{
    hi_s32 ret = HI_ERR_VO_INVALID_DEV_ID;

    if ((dev == VO_DEV_DHD0) || (dev == VO_DEV_DHD1)) {
        ret = vou_drv_check_dhd_intf(dev, intf_type);
    } else if (dev == VO_DEV_DSD0) {
        ret = vou_drv_check_dsd_intf(dev, intf_type);
    }

    if (ret != HI_SUCCESS) {
        return ret;
    }

    ret = vou_drv_check_intf_share(dev, intf_type);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    return HI_SUCCESS;
}

static hi_vo_intf_sync vo_drv_get_vga_max_intf_sync(hi_vo_dev dev)
{
    hi_vo_intf_sync max_intf_sync;

#ifdef CHIP_HI3520DV500
    max_intf_sync = HI_VO_OUT_1080P60;
#else
    if (dev == VO_DEV_DHD0) {
        max_intf_sync = HI_VO_OUT_2560x1600_60;
    } else {
        max_intf_sync = HI_VO_OUT_1080P60;
    }
#endif

    return max_intf_sync;
}

hi_s32 vou_drv_check_hdmi_sync(hi_vo_dev dev, hi_vo_intf_type intf_type, hi_vo_intf_sync intf_sync)
{
    if (intf_type & HI_VO_INTF_HDMI) {
        if ((dev == VO_DEV_DHD0)) {
            if ((intf_sync < HI_VO_OUT_640x480_60) || (intf_sync > HI_VO_OUT_3840x2160_30)) {
                vo_err_trace("for HDMI interface, vo%d's intfsync %d illegal!\n", dev, intf_sync);
                return HI_ERR_VO_NOT_SUPPORT;
            }
        } else if ((dev == VO_DEV_DHD1)) {
            if (((intf_sync < HI_VO_OUT_640x480_60) || (intf_sync > HI_VO_OUT_1080P60))) {
                vo_err_trace("for HDMI interface, vo%d's intfsync %d illegal!\n", dev, intf_sync);
                return HI_ERR_VO_NOT_SUPPORT;
            }
        }
    }
    return HI_SUCCESS;
}

hi_s32 vou_drv_check_bt_sync(hi_vo_dev dev, hi_vo_intf_type intf_type, hi_vo_intf_sync intf_sync)
{
    if (intf_type & HI_VO_INTF_BT1120) {
        if (((intf_sync < HI_VO_OUT_640x480_60) ||
            (intf_sync > HI_VO_OUT_1080P60))) {
            vo_err_trace("for BT.1120 interface, vo%d's intfsync %d illegal!\n", dev, intf_sync);
            return HI_ERR_VO_NOT_SUPPORT;
        }
    }

    if (intf_type & HI_VO_INTF_BT656) {
        if ((intf_sync != HI_VO_OUT_PAL) &&
            (intf_sync != HI_VO_OUT_NTSC)) {
            vo_err_trace("for BT.656 interface, vo%d's intfsync %d illegal!\n", dev, intf_sync);
            return HI_ERR_VO_NOT_SUPPORT;
        }
    }

    return HI_SUCCESS;
}

hi_s32 vou_drv_check_vga_sync(hi_vo_dev dev, hi_vo_intf_type intf_type, hi_vo_intf_sync intf_sync)
{
    if (intf_type & HI_VO_INTF_VGA) {
        if (((intf_sync < HI_VO_OUT_640x480_60) || (intf_sync > vo_drv_get_vga_max_intf_sync(dev)))) {
            vo_err_trace("for VGA interface, vo%d's intfsync %d illegal!\n", dev, intf_sync);
            return HI_ERR_VO_NOT_SUPPORT;
        }
    }

    return HI_SUCCESS;
}

hi_s32 vou_drv_check_rgb_sync(hi_vo_dev dev, hi_vo_intf_type intf_type, hi_vo_intf_sync intf_sync)
{
    if ((intf_type & HI_VO_INTF_RGB_16BIT) ||
        (intf_type & HI_VO_INTF_RGB_18BIT) ||
        (intf_type & HI_VO_INTF_RGB_24BIT)) {
        if (intf_sync != HI_VO_OUT_USER) {
            vo_err_trace("for RGB_16/18/24BIT interface, vo%d's intfsync %d illegal!\n", dev, intf_sync);
            return HI_ERR_VO_NOT_SUPPORT;
        }
    }

    return HI_SUCCESS;
}

hi_u32 vo_drv_get_vga_gain_def(hi_void)
{
    return VO_VGA_GAIN_DEF;
}

#endif

#if VO_DESC("dev")

static hi_void vo_drv_dev_cfg_init(hi_vo_dev dev)
{
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(dev);
    if (dev == VO_DEV_DHD0) {
        drv_dev_ctx->vtth = VO_HD_VTTH_WATERLINE;
        drv_dev_ctx->vtth2 = VO_HD_VTTH_WATERLINE2;
    } else if (dev == VO_DEV_DHD1) {
        drv_dev_ctx->vtth = VO_HD_VTTH_WATERLINE;
        drv_dev_ctx->vtth2 = VO_HD_VTTH_WATERLINE2;
    } else if (dev == VO_DEV_DSD0) {
        drv_dev_ctx->vtth = VO_SD_VTTH_WATERLINE;
        drv_dev_ctx->vtth2 = VO_SD_VTTH_WATERLINE2;
    }
}

static hi_void vo_drv_dev_layer_info_init(hi_vo_dev dev)
{
    vo_drv_dev *drv_dev_ctx = HI_NULL;

    drv_dev_ctx = vo_drv_get_dev_ctx(dev);
    if (dev == VO_DEV_DHD0) {
        /* 2 video layer and 3 graphic layer in DHD0 */
        drv_dev_ctx->layer_num = 2;         /* 2: 2 video layer V0/V2 */
    } else if (dev == VO_DEV_DHD1) {
        /* 2 video layer and 3 graphic layer in DHD1 */
        drv_dev_ctx->layer_num = 1;         /* 1: default 1 video layer V1, can bind to V2 */
    } else if (dev == VO_DEV_DSD0) {
        /* 1 video layer and 2 graphic layer in DSD0 */
        drv_dev_ctx->layer_num = 1;             /* 1: default 1 video layer V3 */
    }
}

hi_void vo_drv_dev_info_init(hi_void)
{
    hi_vo_dev dev;
    hi_u32 ctx_len;
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(0);

    ctx_len = sizeof(vo_drv_dev) * HI_VO_MAX_DEV_NUM;
    memset(drv_dev_ctx, 0, ctx_len);

    for (dev = 0; dev < HI_VO_MAX_DEV_NUM; dev++) {
        vo_drv_dev_cfg_init(dev);
        vo_drv_dev_layer_info_init(dev);
    }
}

#endif

#if VO_DESC("dev")

hi_vo_layer vo_drv_get_layer(hi_vo_dev dev)
{
    hal_disp_layer hal_layer = HAL_DISP_LAYER_VHD0;

    if (dev == VO_DEV_DHD0) {
        hal_layer = HAL_DISP_LAYER_VHD0;
    } else if (dev == VO_DEV_DHD1) {
        hal_layer = HAL_DISP_LAYER_VHD1;
    } else if (dev == VO_DEV_DSD0) {
        hal_layer = HAL_DISP_LAYER_VSD0;
    }

    return hal_layer;
}

static hi_void vo_drv_set_dev_clk_sel(hi_vo_dev dev, hi_u32 clk_sel)
{
    hi_mpp_chn mpp_chn;
    hi_u32 hd_clk_sel = clk_sel;
    hi_u32 sd_clk_sel = clk_sel;

    vo_drv_set_dev_mpp_chn(dev, &mpp_chn);

    if ((dev == VO_DEV_DHD0) || (dev == VO_DEV_DHD1)) {
        vo_drv_dev_get_clk_pll_src(dev, &hd_clk_sel);
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HD_CLK_SEL, &hd_clk_sel);
    } else if (dev == VO_DEV_DSD0) {
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_SD_CLK_SEL, &sd_clk_sel);
    }
}

static hi_void vo_drv_set_dev_clk_en(hi_vo_dev dev, hi_bool clk_en)
{
    hi_mpp_chn mpp_chn;
    hi_bool vo_clk_en = clk_en;

    vo_drv_set_dev_mpp_chn(dev, &mpp_chn);

    if ((dev == VO_DEV_DHD0) || (dev == VO_DEV_DHD1) || (dev == VO_DEV_DSD0)) {
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_DEV_CLK_EN, &vo_clk_en);
    }
}

hi_void vo_drv_set_dev_clk_en_sel(hi_vo_dev dev)
{
    vo_drv_dev *dev_ctx = HI_NULL;

    vo_drv_set_dev_clk_en(dev, HI_TRUE);
    dev_ctx = vo_drv_get_dev_ctx(dev);
    if (dev_ctx->vou_attr.intf_sync == HI_VO_OUT_USER) {
        return;
    }
    vo_drv_set_dev_clk_sel(dev, 0);
}

static hi_void vo_drv_get_dev_hdmi_mode(hi_vo_intf_type intf_type, hi_u32 *hdmi_mode)
{
    if (vo_drv_is_rgb_intf(intf_type) ||
        vo_drv_is_mipi_intf(intf_type)) {
        *hdmi_mode = 1;
    } else {
        *hdmi_mode = 0;
    }
}

static hi_void vo_drv_set_cbm_bkg(hi_vo_dev dev)
{
    hal_disp_bkcolor bkg;
    hi_u32 bg_color;
    hi_u32 yuv_bk_grd;
    hal_cbmmix mixer = dev;

    bg_color = vo_drv_get_dev_bg_color(dev);
    yuv_bk_grd = rgb_to_yuv_full(bg_color);
    bkg.bkg_y = YUV_Y(yuv_bk_grd);
    bkg.bkg_cb = YUV_U(yuv_bk_grd);
    bkg.bkg_cr = YUV_V(yuv_bk_grd);

    hal_cbm_set_cbm_bkg(mixer, &bkg);
}

static hi_void vo_drv_set_intf_hdmi_cfg(hi_vo_dev dev, hi_u32 hdmi_mode)
{
    hi_mpp_chn mpp_chn;
    hi_bool hdmi_clk_en = 0x1;
    hi_bool hdmi_clk_sel = dev;

    vo_drv_set_dev_mpp_chn(dev, &mpp_chn);

    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HDMI_CLK_EN, &hdmi_clk_en);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HDMI_CLK_SEL, &hdmi_clk_sel);

    vo_hal_intf_set_mux_sel(dev, HI_VO_INTF_HDMI);

    hal_disp_set_hdmi_mode(dev, hdmi_mode);
}

static hi_void vo_drv_set_intf_bt1120_cfg(hi_vo_dev dev)
{
    hi_bool bt_clk_en = HI_TRUE;
    hi_u32 bt_sel = dev;
    hi_u32 bt_clk_reverse = HI_TRUE;
    hi_u32 bt_out_dly_tune = 8; /* 8 */
    hi_mpp_chn mpp_chn;

    vo_drv_set_dev_mpp_chn(dev, &mpp_chn);

    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_BT1120_CLK_EN, &bt_clk_en);  /*  [8][9] bt clk en ,bt bp en. */
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_BT1120_CLK_SEL, &bt_sel);  /* [25] bt selection ch 0 or ch 1. */

    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HD_CLKOUT_PHASIC_REVERSE_EN, &bt_clk_reverse);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_OUT_DLY_TUNE, &bt_out_dly_tune);

    vo_hal_intf_set_mux_sel(dev, HI_VO_INTF_BT1120);

    hal_intf_bt_set_dfir_en(0x1);
    hal_intf_bt_set_data_width(0x1);
}

static hi_void vo_drv_set_intf_bt656_cfg(hi_vo_dev dev)
{
    hi_mpp_chn mpp_chn;
    hi_bool bt_clk_en = HI_TRUE;
    hi_u32 bt_sel = dev;

    vo_drv_set_dev_mpp_chn(dev, &mpp_chn);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_BT1120_CLK_EN, &bt_clk_en);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_BT1120_CLK_SEL, &bt_sel);
    vo_hal_intf_set_mux_sel(dev, HI_VO_INTF_BT656);
    hal_intf_bt_set_dfir_en(0x1);
}

static hi_void vo_drv_set_intf_vga_cfg(hi_vo_dev dev)
{
    hi_mpp_chn mpp_chn;
    hi_bool dac_clk_en = HI_TRUE;
    hi_bool dac_clk_sel = dev;

    vo_drv_set_dev_mpp_chn(dev, &mpp_chn);

    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_DEV_DAC_EN, &dac_clk_en);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HD_DAC_SEL, &dac_clk_sel);

    vo_hal_intf_set_mux_sel(dev, HI_VO_INTF_VGA);

    vo_hal_intf_set_dac_sel(HI_VO_INTF_VGA);
    vo_hal_intf_set_vga_and_cvbs_dac_enable(HI_TRUE);
    vo_hal_intf_set_dac_chn_enable(HI_VO_INTF_VGA, HI_TRUE);
    vo_hal_intf_set_dac_gc(HI_VO_INTF_VGA, VO_VGA_GAIN_DEF);
}

static hi_u32 vo_drv_get_intf_cvbs_dac_gc(hi_vo_intf_sync intf_sync, hi_u32 vact)
{
    if (intf_sync == HI_VO_OUT_PAL) {
        return VO_CVBS_DAC_GC_DEF_PAL;
    } else if (intf_sync == HI_VO_OUT_NTSC) {
        return VO_CVBS_DAC_GC_DEF_NTSC;
    }

    if (vact == 288) { /* 288 = 576 / 2 */
        return VO_CVBS_DAC_GC_DEF_PAL;
    } else if (vact == 240) { /* 240 = 480 / 2 */
        return VO_CVBS_DAC_GC_DEF_NTSC;
    } else {
        vo_err_trace("HI_VO_OUT_USER wrong vact: %u\n", vact);
        return VO_CVBS_DAC_GC_DEF_PAL;
    }
}

static hi_void vo_drv_set_intf_cvbs_cfg(hi_vo_dev dev)
{
    hi_mpp_chn mpp_chn;
    hal_disp_syncinfo sync_info = {0};
    hi_bool dac_clk_en = HI_TRUE;
    hi_u32 date;
    hi_u32 dac_gc;

    vo_drv_set_dev_mpp_chn(dev, &mpp_chn);

    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_DEV_DAC_EN, &dac_clk_en);

    vo_drv_get_sync_info(dev, &sync_info);
    date = vo_hal_intf_get_date(vo_drv_get_dev_intf_sync(dev), sync_info.vact);
    vo_hal_intf_set_date_cfg(vo_drv_get_dev_intf_sync(dev), date);

    vo_hal_intf_set_mux_sel(dev, HI_VO_INTF_CVBS);
    vo_hal_intf_set_dac_sel(HI_VO_INTF_CVBS);
    vo_hal_intf_set_vga_and_cvbs_dac_enable(HI_TRUE);
    vo_hal_intf_set_cvbs_dac_cfg();
    vo_hal_intf_set_dac_chn_enable(HI_VO_INTF_CVBS, HI_TRUE);
    dac_gc = vo_drv_get_intf_cvbs_dac_gc(vo_drv_get_dev_intf_sync(dev), sync_info.vact);
    vo_hal_intf_set_dac_gc(HI_VO_INTF_CVBS, dac_gc);
}

static hi_void vo_drv_get_intf_rgb_ctrl(hi_vo_intf_type intf_type, reg_intf_lcd_ctrl *lcd_ctrl)
{
    if (HI_VO_INTF_RGB_6BIT & intf_type) {
        lcd_ctrl->bits.lcd_format = 4; /* 4: serial */
        lcd_ctrl->bits.lcd_serial_perd = 0; /* 0: 3 period */
        lcd_ctrl->bits.dfir_en = 0;
        lcd_ctrl->bits.hdmi_mode = 0;
    } else if (HI_VO_INTF_RGB_8BIT & intf_type) {
        lcd_ctrl->bits.lcd_format = 3; /* 3: serial 8bit */
        lcd_ctrl->bits.lcd_serial_perd = 1; /* 0: 4 period */
        lcd_ctrl->bits.dfir_en = 0;
        lcd_ctrl->bits.hdmi_mode = 0;
    } else if (HI_VO_INTF_RGB_16BIT & intf_type) {
        lcd_ctrl->bits.lcd_format = 1; /* 1: parallel 16bit,RGB656 */
        lcd_ctrl->bits.lcd_serial_perd = 0;
        lcd_ctrl->bits.dfir_en = 0;
        lcd_ctrl->bits.hdmi_mode = 0;
    } else if (HI_VO_INTF_RGB_18BIT & intf_type) {
        lcd_ctrl->bits.lcd_format = 2; /* 2: parallel 18bit,RGB666 */
        lcd_ctrl->bits.lcd_serial_perd = 0;
        lcd_ctrl->bits.dfir_en = 0;
        lcd_ctrl->bits.hdmi_mode = 0;
    } else if (HI_VO_INTF_RGB_24BIT & intf_type) {
        lcd_ctrl->bits.lcd_format = 0; /* 0: parallel 24bit,RGB888 */
        lcd_ctrl->bits.lcd_serial_perd = 0;
        lcd_ctrl->bits.dfir_en = 0;
        lcd_ctrl->bits.hdmi_mode = 0;
    }
}

static hi_u32 vo_drv_get_rgb_dither_out_width(hi_vo_intf_type intf_type)
{
    if ((intf_type == HI_VO_INTF_RGB_16BIT) ||
        (intf_type == HI_VO_INTF_RGB_18BIT)) {
        return 6; /* 6bit */
    } else {
        return 8; /* 8bit */
    }
}

static hi_void vo_drv_set_intf_rgb_cfg(hi_vo_dev dev)
{
    hi_u32 bt_sel = dev;
    hi_bool bt_clk_en = HI_TRUE;
    hi_vo_intf_type intf_type;
    reg_intf_lcd_ctrl lcd_ctrl = {0};
    hi_vo_intf_sync intf_sync;
    hi_mpp_chn mpp_chn;

    intf_type = vo_drv_get_dev_intf_type(dev);
    intf_sync = vo_drv_get_dev_intf_sync(dev);

    vo_drv_set_dev_mpp_chn(dev, &mpp_chn);

    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_BT1120_CLK_EN, &bt_clk_en);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_BT1120_CLK_SEL, &bt_sel);

    vo_hal_intf_set_mux_sel(dev, intf_type);

    vo_drv_get_intf_rgb_ctrl(intf_type, &lcd_ctrl);

    vo_hal_set_intf_ctrl(intf_type, &(lcd_ctrl.u32));

    /* dither config */
    vo_drv_set_intf_dither(intf_type, vo_drv_get_rgb_dither_out_width(intf_type));

    if (intf_sync != HI_VO_OUT_USER) {
        hal_disp_set_lcd_serial_perd(lcd_ctrl.bits.lcd_serial_perd);
    }
}

static hi_void vo_drv_set_intf_cfg(hi_vo_dev dev, hi_u32 hdmi_mode)
{
    hi_vo_intf_type intf_type;

    intf_type = vo_drv_get_dev_intf_type(dev);
    if (HI_VO_INTF_HDMI & intf_type) {
        vo_drv_set_intf_hdmi_cfg(dev, hdmi_mode);
    }

    if (HI_VO_INTF_BT1120 & intf_type) {
        vo_drv_set_intf_bt1120_cfg(dev);
    }

    if (HI_VO_INTF_BT656 & intf_type) {
        vo_drv_set_intf_bt656_cfg(dev);
    }

    if (HI_VO_INTF_VGA & intf_type) {
        vo_drv_set_intf_vga_cfg(dev);
    }

    if (HI_VO_INTF_CVBS & intf_type) {
        vo_drv_set_intf_cvbs_cfg(dev);
    }

    if (vo_drv_is_rgb_intf(intf_type)) {
        vo_drv_set_intf_rgb_cfg(dev);
    }
}

static hi_void vo_drv_get_sync_inv(hi_vo_dev dev, hal_disp_syncinv *inv)
{
    hal_disp_syncinfo sync_info;
    hi_vo_intf_type intf_type;
    hi_vo_intf_sync intf_sync;

    intf_type = vo_drv_get_dev_intf_type(dev);
    intf_sync = vo_drv_get_dev_intf_sync(dev);

    vo_drv_get_sync_info(dev, &sync_info);

    inv->hs_inv = sync_info.ihs ? 1 : 0;
    inv->vs_inv = sync_info.ivs ? 1 : 0;
    inv->dv_inv = sync_info.idv ? 1 : 0;

    if (HI_VO_INTF_HDMI & intf_type) {
        if ((intf_sync == HI_VO_OUT_576P50) || (intf_sync == HI_VO_OUT_480P60)) {
            inv->hs_inv = 1 - inv->hs_inv;
            inv->vs_inv = 1 - inv->vs_inv;
        }
    }

    if (HI_VO_INTF_BT656 & intf_type) {
        inv->hs_inv = 1;
    }

    if (HI_VO_INTF_VGA & intf_type) {
        if (intf_sync == HI_VO_OUT_1024x768_60) {
            inv->vs_inv = 1 - inv->vs_inv;
        }
    }

    if (HI_VO_INTF_CVBS & intf_type) {
        inv->hs_inv = 1;
    }
}

static hi_void vo_drv_set_sync_inv(hi_vo_dev dev, hal_disp_syncinv *inv)
{
    hi_vo_intf_type intf_type;

    intf_type = vo_drv_get_dev_intf_type(dev);
    if (HI_VO_INTF_HDMI & intf_type) {
        vo_hal_intf_set_sync_inv(HI_VO_INTF_HDMI, inv);
    }

    if (HI_VO_INTF_BT1120 & intf_type) {
        vo_hal_intf_set_sync_inv(HI_VO_INTF_BT1120, inv);
    }

    if (HI_VO_INTF_BT656 & intf_type) {
        vo_hal_intf_set_sync_inv(HI_VO_INTF_BT656, inv);
    }

    if (HI_VO_INTF_VGA & intf_type) {
        vo_hal_intf_set_sync_inv(HI_VO_INTF_VGA, inv);
    }

    if (HI_VO_INTF_CVBS & intf_type) {
        vo_hal_intf_set_sync_inv(HI_VO_INTF_CVBS, inv);
    }

    if (vo_drv_is_rgb_intf(intf_type)) {
        vo_hal_intf_set_sync_inv(HI_VO_INTF_RGB_6BIT, inv);
    }
}

static hi_void vo_drv_get_dev_out_reverse_by_rgb_intf(hi_vo_intf_type intf_type, hi_bool *clk_reverse)
{
    if ((HI_VO_INTF_RGB_6BIT & intf_type) ||
        (HI_VO_INTF_RGB_8BIT & intf_type) ||
        (HI_VO_INTF_RGB_16BIT & intf_type) ||
        (HI_VO_INTF_RGB_18BIT & intf_type)) {
        *clk_reverse = HI_TRUE;
    } else if (HI_VO_INTF_RGB_24BIT & intf_type) {
        *clk_reverse = HI_FALSE;
    }
}

static hi_void vo_drv_get_dev_out_reverse(hi_vo_dev dev, hi_bool *clk_reverse)
{
    hi_vo_intf_type intf_type = vo_drv_get_dev_intf_type(dev);
    if ((HI_VO_INTF_HDMI & intf_type) ||
        (HI_VO_INTF_BT1120 & intf_type) ||
        (HI_VO_INTF_BT656 & intf_type) ||
        (HI_VO_INTF_VGA & intf_type) ||
        (HI_VO_INTF_CVBS & intf_type)) {
        *clk_reverse = HI_TRUE;
    } else if (vo_drv_is_rgb_intf(intf_type)) {
        vo_drv_get_dev_out_reverse_by_rgb_intf(intf_type, clk_reverse);
    }
}

static hi_void vo_drv_set_dev_out_reverse(hi_vo_dev dev, hi_bool clk_reverse_en)
{
    hi_mpp_chn mpp_chn;
    hi_vo_intf_sync intf_sync;

    intf_sync = vo_drv_get_dev_intf_sync(dev);

    vo_drv_set_dev_mpp_chn(dev, &mpp_chn);

    if (intf_sync != HI_VO_OUT_USER) {
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HD_CLKOUT_PHASIC_REVERSE_EN, &clk_reverse_en);
    }
}

static hi_void vo_drv_get_div_mod_by_rgb_intf(hi_vo_intf_type intf_type, hi_u32 *div_mode)
{
    if (HI_VO_INTF_RGB_8BIT & intf_type) {
        *div_mode = 3; /* 3: 4div */
    } else if (HI_VO_INTF_RGB_6BIT & intf_type) {
        *div_mode = 2; /* 2: 3div */
    } else if ((HI_VO_INTF_RGB_16BIT & intf_type) ||
               (HI_VO_INTF_RGB_18BIT & intf_type) ||
               (HI_VO_INTF_RGB_24BIT & intf_type)) {
        *div_mode = 0; /* 0: 1div */
    }
}

static hi_void vo_drv_get_div_mod(hi_vo_dev dev, hi_u32 *div_mode)
{
    hi_vo_intf_type intf_type;

    intf_type = vo_drv_get_dev_intf_type(dev);
    if (HI_VO_INTF_HDMI & intf_type) {
        *div_mode = 0; /* 0: 1div */
    }

    if (HI_VO_INTF_BT1120 & intf_type) {
        *div_mode = 0; /* 0: 1div */
    }

    if (HI_VO_INTF_BT656 & intf_type) {
        *div_mode = 1; /* 1: 2div */
    }

    if (HI_VO_INTF_VGA & intf_type) {
        *div_mode = 0; /* 0: 1div */
    }

    if (HI_VO_INTF_CVBS & intf_type) {
        *div_mode = 0; /* 0: 4div, 1: 1div */
    }

    if (vo_drv_is_rgb_intf(intf_type)) {
        vo_drv_get_div_mod_by_rgb_intf(intf_type, div_mode);
    }
}

static hi_void vo_drv_set_div_mod(hi_vo_dev dev, hi_u32 div_mode)
{
    hi_mpp_chn mpp_chn;
    hi_vo_intf_sync intf_sync;

    intf_sync = vo_drv_get_dev_intf_sync(dev);

    vo_drv_set_dev_mpp_chn(dev, &mpp_chn);
    if (intf_sync == HI_VO_OUT_USER) {
        return;
    }
    if (dev == VO_DEV_DHD0) {
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HD0_DIV_MOD, &div_mode);
    } else if (dev == VO_DEV_DHD1) {
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HD1_DIV_MOD, &div_mode);
    } else if (dev == VO_DEV_DSD0) {
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_SD_CLK_DIV, &div_mode);
    }
}

static hi_void vo_drv_set_intf_clip(hi_vo_dev dev)
{
    hi_vo_intf_type intf_type;
    intf_type = vo_drv_get_dev_intf_type(dev);
    if (HI_VO_INTF_BT1120 & intf_type) {
        hal_disp_clip clip_data = {0x40, 0x40, 0x40, 0x3ac, 0x3c0, 0x3c0};
        vo_hal_intf_set_clip_cfg(HI_VO_INTF_BT1120, HI_TRUE, &clip_data);
    }

    if (HI_VO_INTF_CVBS & intf_type) {
        hal_disp_clip clip_data = {0x40, 0x40, 0x40, 0x3ac, 0x3c0, 0x3c0};
        vo_hal_intf_set_clip_cfg(HI_VO_INTF_CVBS, HI_TRUE, &clip_data);
    }

    if (HI_VO_INTF_BT656 & intf_type) {
        hal_disp_clip clip_data = {0x40, 0x40, 0x40, 0x3ac, 0x3c0, 0x3c0};
        vo_hal_intf_set_clip_cfg(HI_VO_INTF_BT656, HI_TRUE, &clip_data);
    }
}

static hi_void vo_drv_set_int_mode(hi_vo_dev dev)
{
    hi_vo_layer layer;
    vo_int_mode int_mode;
    hal_disp_syncinfo sync_info;

    if (vo_drv_is_phy_dev_hd(dev) || vo_drv_is_phy_dev_sd(dev)) {
        layer = vo_drv_get_layer(dev);
        vo_drv_get_sync_info(dev, &sync_info);
        if (sync_info.iop == 0) {
            int_mode = VO_INT_MODE_FIELD;
        } else {
            int_mode = VO_INT_MODE_FRAME;
        }

        vo_drv_int_set_mode(dev, int_mode);
        vo_drv_int_reg_up_mode(layer, int_mode);
    }
}

static hi_void vo_drv_set_vtth(hi_vo_dev dev)
{
    hal_disp_syncinfo sync_info;
    vo_drv_dev *drv_dev_ctx = HI_NULL;
    hi_u16 vtth_line = 0;
    hi_u16 vtth2_line = 0;
    hi_u32 vtth_temp = 0;
    hi_u32 vtth2_temp = 0;
    hi_u16 vert_all = 0;

    drv_dev_ctx = vo_drv_get_dev_ctx(dev);
    vo_drv_get_sync_info(dev, &sync_info);

    if (vo_drv_is_phy_dev_hd(dev) || vo_drv_is_phy_dev_sd(dev)) {
        vtth_temp = drv_dev_ctx->vtth;
        vtth2_temp = drv_dev_ctx->vtth2;
        vert_all = sync_info.vact + sync_info.vfb + sync_info.vbb;

        if (vtth_temp >= vert_all) {
            /* argu 0 means : set to default value. */
            vo_drv_set_dev_vtth(dev, 0);
            vo_err_trace("vo dev %d vtthd : %d is not in logic [%d,%d], set to default minimum: %d\n",
                dev, vtth_temp, 0, vert_all - 1, drv_dev_ctx->vtth);
        }

        if ((vtth2_temp >= vert_all) || (vtth2_temp > drv_dev_ctx->vtth)) {
            /* argu 0 means : set to default value. */
            vo_drv_set_dev_vtth2(dev, 0);
            vo_err_trace("vo dev %d vtthd2 : %d is not in logic [%d,%d] or larger than vtthd: %d, set to default"
                " minimum: %d\n", dev, vtth2_temp, 0, vert_all - 1, drv_dev_ctx->vtth, drv_dev_ctx->vtth2);
        }

        vtth_line = vert_all - 1 - (hi_u16)(drv_dev_ctx->vtth);
        vtth2_line = vert_all - 1 - (hi_u16)(drv_dev_ctx->vtth2);
    }

    hal_disp_set_vtthd(dev, vtth_line, vtth2_line);
}

hi_void vo_drv_open(hi_vo_dev dev)
{
    hal_disp_syncinfo sync_info;
    hal_disp_syncinv inv = {0};
    hi_bool clk_reverse_en = HI_TRUE;
    hi_u32 div_mode = 0;
    hi_u32 hdmi_mode = 0;

    vo_drv_get_dev_hdmi_mode(dev, &hdmi_mode);
    vo_drv_set_cbm_bkg(dev);

    vo_drv_set_intf_cfg(dev, hdmi_mode);

    vo_drv_get_sync_inv(dev, &inv);
    vo_drv_set_sync_inv(dev, &inv);
    vo_drv_get_sync_info(dev, &sync_info);
    vo_drv_set_sync_info(dev, &sync_info);

    vo_drv_get_div_mod(dev, &div_mode);
    vo_drv_set_div_mod(dev, div_mode);

    vo_drv_get_dev_out_reverse(dev, &clk_reverse_en);
    vo_drv_set_dev_out_reverse(dev, clk_reverse_en);

    hal_disp_set_dev_multi_chn_en(dev, HAL_MULTICHN_EN_1P1C);

    vo_drv_set_intf_clip(dev);

    vo_drv_set_int_mode(dev);

    vo_drv_set_vtth(dev);

    hal_disp_set_intf_enable(dev, HI_TRUE);

    hal_disp_set_reg_up(dev);
}

hi_void vo_drv_close(hi_vo_dev dev)
{
    hi_mpp_chn mpp_chn;
    hi_bool clk_en = HI_FALSE;
    hi_bool hdmi_ssc_div = 0x0;
    hi_bool hdmi_clk_en = 0x0;
    hi_vo_intf_type intf_type;

    hal_disp_set_intf_enable(dev, HI_FALSE);
    hal_disp_set_reg_up(dev);

    vo_drv_set_dev_mpp_chn(dev, &mpp_chn);

    vo_drv_get_dev_reg_up(dev);

    intf_type = vo_drv_get_dev_intf_type(dev);
    if (HI_VO_INTF_HDMI & intf_type) {
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HDMI_SSC_VDP_DIV, &hdmi_ssc_div);
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HDMI_CLK_EN, &hdmi_clk_en);
    }

    if (HI_VO_INTF_BT1120 & intf_type) {
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_BT1120_CLK_EN, &clk_en);
    }

    if (HI_VO_INTF_BT656 & intf_type) {
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_BT1120_CLK_EN, &clk_en);
    }

    if (vo_drv_is_rgb_intf(intf_type)) {
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_BT1120_CLK_EN, &clk_en);
    }

    if (HI_VO_INTF_CVBS & intf_type) {
        vo_hal_intf_set_dac_chn_enable(HI_VO_INTF_CVBS, HI_FALSE);
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_DEV_DAC_EN, &clk_en);
    }

    if (HI_VO_INTF_VGA & intf_type) {
        vo_hal_intf_set_dac_chn_enable(HI_VO_INTF_VGA, HI_FALSE);
        call_sys_drv_ioctrl(&mpp_chn, SYS_VO_DEV_DAC_EN, &clk_en);
    }

    /* close clk */
    vo_drv_set_dev_clk_en(dev, HI_FALSE);
}

static hi_s32 vo_drv_check_dev_id_support(hi_vo_dev dev)
{
#ifdef CHIP_HI3520DV500
    if (dev == VO_DEV_DHD1) {
        return HI_ERR_VO_INVALID_DEV_ID;
    }
#endif
    return HI_SUCCESS;
}

static hi_s32 vo_drv_check_layer_id_support(hi_vo_layer layer)
{
    if (layer == HI_VO_LAYER_V2) {
        return HI_ERR_VO_INVALID_LAYER_ID;
    }

#ifdef CHIP_HI3520DV500
    if (layer == HI_VO_LAYER_V1) {
        return HI_ERR_VO_INVALID_LAYER_ID;
    }
#endif
    return HI_SUCCESS;
}

hi_s32 vo_drv_check_dev_id(hi_vo_dev dev)
{
    hi_s32 ret;
    ret =  vo_drv_check_dev_id_pub(dev);
    if (ret != HI_SUCCESS) {
        return ret;
    }
    return vo_drv_check_dev_id_support(dev);
}

hi_s32 vo_drv_check_layer_id(hi_vo_layer layer)
{
    hi_s32 ret;
    ret = vo_drv_check_layer_id_pub(layer);
    if (ret != HI_SUCCESS) {
        return ret;
    }
    return vo_drv_check_layer_id_support(layer);
}
#endif

#if VO_DESC("dev")

hi_void vo_drv_dev_get_clk_pll_src(hi_vo_dev dev, hi_u32 *pll_src)
{
    vo_drv_dev *dev_ctx = HI_NULL;
    hi_vo_intf_type intf_type;

    dev_ctx = vo_drv_get_dev_ctx(dev);
    intf_type = dev_ctx->vou_attr.intf_type;

    if (vo_drv_is_rgb_intf(intf_type)) {
        *pll_src = VO_CLK_PLL_SRC_FOUT4;
    }
}

static vo_pll_param g_vo_pll_param_no_div[HI_VO_OUT_BUTT] = {
    /* index,                fb_div, frac, ref_div, post_div1,post_div2 */
    {HI_VO_OUT_PAL,          {81,   0,       2,  6, 6}, 0}, /* 27MHz, 2 * 13.5MHz */
    {HI_VO_OUT_NTSC,         {81,   0,       2,  6, 6}, 0}, /* 27MHz, 2 * 13.5MHz */
    {HI_VO_OUT_960H_PAL,     {36,   0,       1,  6, 2}, 0}, /* 36MHz */
    {HI_VO_OUT_960H_NTSC,    {36,   0,       1,  6, 2}, 0}, /* 36MHz */
    {HI_VO_OUT_640x480_60,   {113, 4823450,  3,  6, 6}, 0}, /* 25.175MHz */
    {HI_VO_OUT_480P60,       {81,   0,       2,  6, 6}, 0}, /* 27MHz */
    {HI_VO_OUT_576P50,       {81,   0,       2,  6, 6}, 0}, /* 27MHz */
    {HI_VO_OUT_800x600_60,   {80,   0,       2,  6, 4}, 0}, /* 40MHz */
    {HI_VO_OUT_1024x768_60,  {65,   0,       1,  6, 4}, 0}, /* 65MHz */
    {HI_VO_OUT_720P50,       {99,   0,       2,  4, 4}, 0}, /* 74.25MHz */
    {HI_VO_OUT_720P60,       {99,   0,       2,  4, 4}, 0}, /* 74.25MHz */
    {HI_VO_OUT_1280x800_60,  {167,  0,       4,  6, 2}, 0}, /* 83.5MHz */
    {HI_VO_OUT_1280x1024_60, {72,   0,       2,  4, 2}, 0}, /* 108MHz */
    {HI_VO_OUT_1366x768_60,  {171,  0,       4,  6, 2}, 0}, /* 85.5MHz */
    {HI_VO_OUT_1400x1050_60, {487,  0,      12,  4, 2}, 0}, /* 121.75MHz */
    {HI_VO_OUT_1440x900_60,  {213,  0,       4,  6, 2}, 0}, /* 106.5MHz */
    {HI_VO_OUT_1600x1200_60, {81,   0,       2,  3, 2}, 0}, /* 162MHz */
    {HI_VO_OUT_1680x1050_60, {585,  0,       8,  6, 2}, 0}, /* 146.25MHz */
    {HI_VO_OUT_1080P24,      {99,   0,       2,  4, 4}, 0}, /* 74.25MHz */
    {HI_VO_OUT_1080P25,      {99,   0,       2,  4, 4}, 0}, /* 74.25MHz */
    {HI_VO_OUT_1080P30,      {99,   0,       2,  4, 4}, 0}, /* 74.25MHz */
    {HI_VO_OUT_1080I50,      {99,   0,       2,  4, 4}, 0}, /* 74.25MHz */
    {HI_VO_OUT_1080I60,      {99,   0,       2,  4, 4}, 0}, /* 74.25MHz */
    {HI_VO_OUT_1080P50,      {99,   0,       2,  4, 2}, 0}, /* 148.5MHz */
    {HI_VO_OUT_1080P60,      {99,   0,       2,  4, 2}, 0}, /* 148.5MHz */
    {HI_VO_OUT_1920x1200_60, {154,  0,       4,  3, 2}, 0}, /* 154MHz */
    {HI_VO_OUT_1920x2160_30, {99,   0,       2,  4, 2}, 0}, /* 148.5MHz */
    {HI_VO_OUT_2560x1440_30, {1209, 0,       24, 5, 2}, 0}, /* 120.9MHz */
    {HI_VO_OUT_2560x1440_60, {161,  0,       4,  4, 1}, 0}, /* 241.5MHz */
    {HI_VO_OUT_2560x1600_60, {179,  0,       2,  4, 2}, 0}, /* 268.5MHz */
    {HI_VO_OUT_3840x2160_24, {99,   0,       2,  4, 1}, 0}, /* 297MHz */
    {HI_VO_OUT_3840x2160_25, {99,   0,       2,  4, 1}, 0}, /* 297MHz */
    {HI_VO_OUT_3840x2160_30, {99,   0,       2,  4, 1}, 0}, /* 297MHz */
    {HI_VO_OUT_3840x2160_50, {99,   0,       2,  2, 1}, 0}, /* 594MHz */
    {HI_VO_OUT_3840x2160_60, {99,   0,       2,  2, 1}, 0}, /* 594MHz */
    {HI_VO_OUT_4096x2160_24, {99,   0,       2,  4, 1}, 0}, /* 297MHz */
    {HI_VO_OUT_4096x2160_25, {99,   0,       2,  4, 1}, 0}, /* 297MHz */
    {HI_VO_OUT_4096x2160_30, {99,   0,       2,  4, 1}, 0}, /* 297MHz */
    {HI_VO_OUT_4096x2160_50, {99,   0,       2,  2, 1}, 0}, /* 594MHz */
    {HI_VO_OUT_4096x2160_60, {99,   0,       2,  2, 1}, 0}, /* 594MHz */
    {HI_VO_OUT_7680x4320_30, {99,   0,       2,  2, 1}, 0}, /* 1188MHz */
    {HI_VO_OUT_240x320_50,   {36, 1207960,   1,  4, 2}, 0}, /* 4.5MHz */
    {HI_VO_OUT_320x240_50,   {36, 13136560,  1,  3, 3}, 0}, /* 4.0MHz */
    {HI_VO_OUT_240x320_60,   {36, 12348031,  1,  5, 4}, 0}, /* 5.5MHz */
    {HI_VO_OUT_320x240_60,   {41, 6630356,   1,  5, 4}, 0}, /* 6.2MHz */
    {HI_VO_OUT_800x600_50,   {33, 8858370,   1,  3, 1}, 0}, /* 33.5MHz */
    {HI_VO_OUT_720x1280_60,  {99,   0,       2,  4, 2}, 0}, /* 148.5MHz */
    {HI_VO_OUT_1080x1920_60, {99,   0,       2,  4, 2}, 0}, /* 148.5MHz */
    {} /* user */
};

static vo_pll_param g_vo_pll_param_with_div[HI_VO_OUT_BUTT] = {
    /* index,                fb_div, frac, ref_div, post_div1,post_div2 */
    {HI_VO_OUT_PAL,          {0,    0,  0,  0, 0},                      0}, /* 13.5MHz */
    {HI_VO_OUT_NTSC,         {0,    0,  0,  0, 0},                      0}, /* 13.5MHz */
    {HI_VO_OUT_960H_PAL,     {0,    0,  0,  0, 0},                      0}, /* 36MHz */
    {HI_VO_OUT_960H_NTSC,    {0,    0,  0,  0, 0},                      0}, /* 36MHz */
    {HI_VO_OUT_640x480_60,   {1007, 0, 15,  2, 2},   SSC_VDP_DIV_25_TO_50}, /* 25.175MHz */
    {HI_VO_OUT_480P60,       {36,   0,  1,  2, 1},   SSC_VDP_DIV_25_TO_50}, /* 27MHz */
    {HI_VO_OUT_576P50,       {36,   0,  1,  2, 1},   SSC_VDP_DIV_25_TO_50}, /* 27MHz */
    {HI_VO_OUT_800x600_60,   {80,   0,  1,  3, 1},   SSC_VDP_DIV_25_TO_50}, /* 40MHz */
    {HI_VO_OUT_1024x768_60,  {130,  0,  3,  2, 1},  SSC_VDP_DIV_50_TO_100}, /* 65MHz */
    {HI_VO_OUT_720P50,       {99,   0,  2,  2, 1},  SSC_VDP_DIV_50_TO_100}, /* 74.25MHz */
    {HI_VO_OUT_720P60,       {99,   0,  2,  2, 1},  SSC_VDP_DIV_50_TO_100}, /* 74.25MHz */
    {HI_VO_OUT_1280x800_60,  {167,  0,  3,  2, 1},  SSC_VDP_DIV_50_TO_100}, /* 83.5MHz */
    {HI_VO_OUT_1280x1024_60, {36,   0,  1,  2, 1}, SSC_VDP_DIV_100_TO_200}, /* 108MHz */
    {HI_VO_OUT_1366x768_60,  {57,   0,  1,  2, 1},  SSC_VDP_DIV_50_TO_100}, /* 85.5MHz */
    {HI_VO_OUT_1400x1050_60, {487,  0,  6,  2, 2}, SSC_VDP_DIV_100_TO_200}, /* 121.75MHz */
    {HI_VO_OUT_1440x900_60,  {71,   0,  2,  2, 1}, SSC_VDP_DIV_100_TO_200}, /* 106.5MHz */
    {HI_VO_OUT_1600x1200_60, {54,   0,  1,  2, 1}, SSC_VDP_DIV_100_TO_200}, /* 162MHz */
    {HI_VO_OUT_1680x1050_60, {195,  0,  4,  2, 1}, SSC_VDP_DIV_100_TO_200}, /* 146.25MHz */
    {HI_VO_OUT_1080P24,      {99,   0,  2,  2, 1},  SSC_VDP_DIV_50_TO_100}, /* 74.25MHz */
    {HI_VO_OUT_1080P25,      {99,   0,  2,  2, 1},  SSC_VDP_DIV_50_TO_100}, /* 74.25MHz */
    {HI_VO_OUT_1080P30,      {99,   0,  2,  2, 1},  SSC_VDP_DIV_50_TO_100}, /* 74.25MHz */
    {HI_VO_OUT_1080I50,      {99,   0,  2,  2, 1},  SSC_VDP_DIV_50_TO_100}, /* 74.25MHz */
    {HI_VO_OUT_1080I60,      {99,   0,  2,  2, 1},  SSC_VDP_DIV_50_TO_100}, /* 74.25MHz */
    {HI_VO_OUT_1080P50,      {99,   0,  2,  2, 1}, SSC_VDP_DIV_100_TO_200}, /* 148.5MHz */
    {HI_VO_OUT_1080P60,      {99,   0,  2,  2, 1}, SSC_VDP_DIV_100_TO_200}, /* 148.5MHz */
    {HI_VO_OUT_1920x1200_60, {154,  0,  2,  3, 1}, SSC_VDP_DIV_100_TO_200}, /* 154MHz */
    {HI_VO_OUT_1920x2160_30, {99,   0,  2,  2, 1}, SSC_VDP_DIV_100_TO_200}, /* 148.5MHz */
    {HI_VO_OUT_2560x1440_30, {1209, 0,  12, 5, 1}, SSC_VDP_DIV_100_TO_200}, /* 120.9MHz */
    {HI_VO_OUT_2560x1440_60, {161,  0,  4,  2, 1}, SSC_VDP_DIV_200_TO_340}, /* 241.5MHz */
    {HI_VO_OUT_2560x1600_60, {179,  0,  2,  2, 2}, SSC_VDP_DIV_200_TO_340}, /* 268.5MHz */
    {HI_VO_OUT_3840x2160_24, {99,   0,  2,  2, 1}, SSC_VDP_DIV_200_TO_340}, /* 297MHz */
    {HI_VO_OUT_3840x2160_25, {99,   0,  2,  2, 1}, SSC_VDP_DIV_200_TO_340}, /* 297MHz */
    {HI_VO_OUT_3840x2160_30, {99,   0,  2,  2, 1}, SSC_VDP_DIV_200_TO_340}, /* 297MHz */
    {HI_VO_OUT_3840x2160_50, {99,   0,  2,  2, 1}, SSC_VDP_DIV_340_TO_600}, /* 594MHz */
    {HI_VO_OUT_3840x2160_60, {99,   0,  2,  2, 1}, SSC_VDP_DIV_340_TO_600}, /* 594MHz */
    {HI_VO_OUT_4096x2160_24, {99,   0,  2,  2, 1}, SSC_VDP_DIV_200_TO_340}, /* 297MHz */
    {HI_VO_OUT_4096x2160_25, {99,   0,  2,  2, 1}, SSC_VDP_DIV_200_TO_340}, /* 297MHz */
    {HI_VO_OUT_4096x2160_30, {99,   0,  2,  2, 1}, SSC_VDP_DIV_200_TO_340}, /* 297MHz */
    {HI_VO_OUT_4096x2160_50, {99,   0,  2,  2, 1}, SSC_VDP_DIV_340_TO_600}, /* 594MHz */
    {HI_VO_OUT_4096x2160_60, {99,   0,  2,  2, 1}, SSC_VDP_DIV_340_TO_600}, /* 594MHz */
    {HI_VO_OUT_7680x4320_30, {99,   0,  2,  2, 1},                      0}, /* 1188MHz */
    {HI_VO_OUT_240x320_50,   {36, 1207960,  1,  4, 2},                  0}, /* 4.5MHz */
    {HI_VO_OUT_320x240_50,   {36, 13136560, 1,  3, 3},                  0}, /* 4.0MHz */
    {HI_VO_OUT_240x320_60,   {36, 12348031, 1,  5, 4},                  0}, /* 5.5MHz */
    {HI_VO_OUT_320x240_60,   {41, 6630356,  1,  5, 1},                  0}, /* 6.2MHz */
    {HI_VO_OUT_800x600_50,   {33, 8858370,  1,  3, 1},                  0}, /* 33.5MHz */
    {HI_VO_OUT_720x1280_60,  {99,   0,  2,  2, 1}, SSC_VDP_DIV_100_TO_200}, /* 148.5MHz */
    {HI_VO_OUT_1080x1920_60, {99,   0,  2,  2, 1}, SSC_VDP_DIV_100_TO_200}, /* 148.5MHz */
    {} /* user */
};

static vo_pll_param *vo_drv_get_pll_param_with_div(hi_vo_intf_sync intf_sync)
{
    return &g_vo_pll_param_with_div[intf_sync];
}

static vo_pll_param *vo_drv_get_pll_param_no_div(hi_vo_intf_sync intf_sync)
{
    return &g_vo_pll_param_no_div[intf_sync];
}

static hi_vo_hdmi_ssc_vdp_div_mode vo_drv_get_pll_div(hi_vo_intf_sync intf_sync)
{
    return g_vo_pll_param_with_div[intf_sync].div;
}

hi_void vo_drv_get_pll_cfg_no_div(hi_vo_intf_sync intf_sync, hi_vo_pll *pll)
{
    vo_pll_param pll_init = {HI_VO_OUT_1080P60, {99, 0, 2, 4, 2}};
    vo_pll_param *pll_ret = &pll_init;

    if (intf_sync < HI_VO_OUT_USER) {
        pll_ret = vo_drv_get_pll_param_no_div(intf_sync);
    }

    pll->post_div2 = pll_ret->pll.post_div2;
    pll->post_div1 = pll_ret->pll.post_div1;
    pll->frac = pll_ret->pll.frac;
    pll->fb_div = pll_ret->pll.fb_div;
    pll->ref_div = pll_ret->pll.ref_div;
}

hi_void vo_drv_get_pll_cfg_with_div(hi_vo_intf_sync intf_sync, hi_vo_pll *pll)
{
    vo_pll_param pll_init = {HI_VO_OUT_1080P60, {99, 0, 2, 2, 1}};
    vo_pll_param *pll_ret = &pll_init;

    if (intf_sync < HI_VO_OUT_USER) {
        pll_ret = vo_drv_get_pll_param_with_div(intf_sync);
    }

    pll->post_div2 = pll_ret->pll.post_div2;
    pll->post_div1 = pll_ret->pll.post_div1;
    pll->frac = pll_ret->pll.frac;
    pll->fb_div = pll_ret->pll.fb_div;
    pll->ref_div = pll_ret->pll.ref_div;
}

hi_void vo_drv_dev_get_pll_cfg(hi_vo_dev dev, hi_vo_pll *pll)
{
    vo_drv_dev *dev_ctx = HI_NULL;
    hi_vo_intf_sync intf_sync;

    dev_ctx = vo_drv_get_dev_ctx(dev);
    intf_sync = dev_ctx->vou_attr.intf_sync;

    if (vo_drv_is_hdmi_intf(dev_ctx->vou_attr.intf_type)) {
        vo_drv_get_pll_cfg_with_div(intf_sync, pll);
    } else {
        vo_drv_get_pll_cfg_no_div(intf_sync, pll);
    }
}

hi_void vo_drv_dev_set_pll_cfg(hi_vo_dev dev, hi_vo_pll *pll)
{
    hi_mpp_chn mpp_chn = {0};
    vo_drv_set_dev_mpp_chn(dev, &mpp_chn);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_PLL_FBDIV_SET, &pll->fb_div);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_PLL_FRAC_SET, &pll->frac);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_PLL_REFDIV_SET, &pll->ref_div);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_PLL_POSTDIV1_SET, &pll->post_div1);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_PLL_POSTDIV2_SET, &pll->post_div2);
}

hi_u32 vo_drv_dev_get_max_clk(hi_vo_dev dev)
{
    hi_u32 max_clk;

    max_clk = (dev == VO_DEV_DHD0) ?  VO_PLL_MAX_CLK_297000 : VO_PLL_MAX_CLK_148500;
    return max_clk;
}

hi_void vo_drv_get_hdmi_ssc_vdp_div(hi_vo_intf_sync intf_sync, hi_u32 *hdmi_ssc_vdp_div)
{
    if (intf_sync < HI_VO_OUT_USER) {
        *hdmi_ssc_vdp_div = vo_drv_get_pll_div(intf_sync);
    }
}

hi_void vou_drv_set_hd_clk(hi_vo_dev dev)
{
    hi_vo_pll pll = {0};
    hi_u32 hdmi_ssc_vdp_div = 0x0;
    vo_drv_dev *dev_ctx = HI_NULL;
    hi_vo_intf_sync intf_sync;

    dev_ctx = vo_drv_get_dev_ctx(dev);
    intf_sync = dev_ctx->vou_attr.intf_sync;

    vo_drv_dev_get_pll_cfg(dev, &pll);
    vo_drv_dev_set_pll_cfg(dev, &pll);

    if (vo_drv_is_hdmi_intf(dev_ctx->vou_attr.intf_type)) {
        vo_drv_get_hdmi_ssc_vdp_div(intf_sync, &hdmi_ssc_vdp_div);
        vo_drv_dev_set_hdmi_ssc_vdp_div(dev, hdmi_ssc_vdp_div);
    }
}

hi_void vou_drv_set_dev_clk(hi_vo_dev dev)
{
    vo_drv_dev *dev_ctx = HI_NULL;

    dev_ctx = vo_drv_get_dev_ctx(dev);
    if (dev_ctx->vou_attr.intf_sync == HI_VO_OUT_USER) {
        return;
    }
    if (vo_drv_is_phy_dev_uhd(dev) || vo_drv_is_phy_dev_hd(dev)) {
        vou_drv_set_hd_clk(dev);
    } else if (vo_drv_is_phy_dev_sd(dev)) {
        /* do nothing. */
    }
}

#endif

#if VO_DESC("dev clk")

static hi_void vo_drv_set_sd_date_crg_clk(hi_bool clk_en)
{
    vo_drv_set_dev_clk_en(VO_DEV_DSD0, clk_en);
}

hi_void vo_drv_set_all_crg_clk(hi_bool clk_en)
{
    hi_mpp_chn mpp_chn;
    hi_bool vo_clk_en = clk_en;

    mpp_chn.mod_id = HI_ID_VO;
    mpp_chn.chn_id = 0;
    mpp_chn.dev_id = 0;

    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_CFG_CLK_EN, &vo_clk_en);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_APB_CLK_EN, &vo_clk_en);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_BUS_CLK_EN, &vo_clk_en);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_CORE_CLK_EN, &vo_clk_en);

    vo_drv_set_sd_date_crg_clk(clk_en);
}

hi_void vo_lpw_bus_reset(hi_bool reset)
{
    hi_mpp_chn mpp_chn;
    hi_bool vo_reset = reset;

    mpp_chn.mod_id = HI_ID_VO;
    mpp_chn.dev_id = 0;
    mpp_chn.chn_id = 0;
    /* see sys_hal_vo_bus_reset_sel */
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_BUS_RESET_SEL, &vo_reset);
}

#endif

#if VO_DESC("dev intf")
hi_bool vo_drv_is_dev_support_rgb(hi_vo_dev dev)
{
#ifdef CHIP_HI3520DV500
    return vo_drv_is_phy_dev_uhd(dev);
#else
    return HI_FALSE;
#endif
}
#endif

hi_s32 vo_drv_check_dev_clk_src(hi_vo_dev dev, hi_vo_clk_src clk_src)
{
    if ((clk_src != HI_VO_CLK_SRC_PLL) && (clk_src != HI_VO_CLK_SRC_PLL_FOUT4)) {
        vo_err_trace("dev(%d) clk source %d illegal, dev only support pll/pll fout4 clk source.\n",
            dev, clk_src);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

hi_s32 vo_drv_check_intf_user_dev_div(hi_vo_dev dev, hi_u32 dev_div)
{
    hi_vo_intf_type intf_type;
    hi_u32 intf_dev_div = 0;

    intf_type = vo_drv_get_dev_intf_type(dev);
    if (vo_drv_is_rgb_intf(intf_type)) {
        if ((dev_div != VO_INTF_RGB_DIV_MODE_1) &&
            (dev_div != VO_INTF_RGB_DIV_MODE_3) &&
            (dev_div != VO_INTF_RGB_DIV_MODE_4)) {
            vo_err_trace("vo(%d) div mode %d is illegal, it must be %d/%d/%d when intf type is %d.\n", dev, dev_div,
                VO_INTF_RGB_DIV_MODE_1, VO_INTF_RGB_DIV_MODE_3, VO_INTF_RGB_DIV_MODE_4, intf_type);
            return HI_ERR_VO_ILLEGAL_PARAM;
        }

        return HI_SUCCESS;
    }

    if (intf_type & (HI_VO_INTF_HDMI | HI_VO_INTF_BT1120 | HI_VO_INTF_VGA)) {
        intf_dev_div = VO_INTF_HDMI_DIV_MODE;
    }

    if (intf_type & HI_VO_INTF_CVBS) {
        intf_dev_div = VO_INTF_CVBS_DIV_MODE;
    }

    if (intf_type & HI_VO_INTF_BT656) {
        intf_dev_div = VO_INTF_BT656_DIV_MODE;
    }

    if (dev_div != intf_dev_div) {
        vo_err_trace("vo(%d) dev div mode %d is illegal, it must be %d when intf type is %d.\n", dev, dev_div,
            intf_dev_div, intf_type);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

#if VO_DESC("intf dither")
static hi_void vo_drv_get_intf_dither_in_out_mode(vdp_dither_cfg *cfg)
{
    hi_u32 i_data_width_dither = 0;
    hi_u32 o_data_width_dither = 0;
    hi_u32 dither_io_md;
    hi_u32 dither_md = 0;

    dither_io_md = cfg->io_mode;
    if (dither_io_md == DITHER_IO_MODE_12_8) { /* rgb24bit */
        dither_md = DITHER_MODE_8BIT;
        i_data_width_dither = DITHER_IWIDTH_MODE_12BIT;
        o_data_width_dither = DITHER_OWIDTH_MODE_8BIT;
    } else if (dither_io_md == DITHER_IO_MODE_10_6) { /* rgb16bit, rgb18bit */
        dither_md = DITHER_MODE_8BIT;
        i_data_width_dither = DITHER_IWIDTH_MODE_10BIT;
        o_data_width_dither = DITHER_OWIDTH_MODE_6BIT;
    }
    cfg->dither_mode = dither_md;
    cfg->i_data_width_dither = i_data_width_dither;
    cfg->o_data_width_dither = o_data_width_dither;
}

static hi_void vo_drv_get_intf_dither_sed_and_thr(vdp_dither_cfg *cfg)
{
    const hi_u32 sed_y0 = 2147483647; /* 2147483647: typical y0 */
    const hi_u32 sed_u0 = 2147482647; /* 2147482647: typical u0 */
    const hi_u32 sed_v0 = 2147481647; /* 2147481647: typical v0 */
    const hi_u32 sed_w0 = 2147480647; /* 2147480647: typical w0 */
    const hi_u32 thr_max = 60000; /* 60000: dither threshold max */
    const hi_u32 thr_min = 120; /* 120: dither threshold max */

    cfg->dither_sed.dither_sed_y0 = sed_y0;
    cfg->dither_sed.dither_sed_u0 = sed_u0;
    cfg->dither_sed.dither_sed_v0 = sed_v0;
    cfg->dither_sed.dither_sed_w0 = sed_w0;
    cfg->dither_sed.dither_sed_y1 = sed_y0;
    cfg->dither_sed.dither_sed_u1 = sed_u0;
    cfg->dither_sed.dither_sed_v1 = sed_v0;
    cfg->dither_sed.dither_sed_w1 = sed_w0;
    cfg->dither_sed.dither_sed_y2 = sed_y0;
    cfg->dither_sed.dither_sed_u2 = sed_u0;
    cfg->dither_sed.dither_sed_v2 = sed_v0;
    cfg->dither_sed.dither_sed_w2 = sed_w0;
    cfg->dither_sed.dither_sed_y3 = sed_y0;
    cfg->dither_sed.dither_sed_u3 = sed_u0;
    cfg->dither_sed.dither_sed_v3 = sed_v0;
    cfg->dither_sed.dither_sed_w3 = sed_w0;
    cfg->dither_thr_max = thr_max;
    cfg->dither_thr_min = thr_min;
}

static hi_void vo_drv_set_intf_rgb_dither_mode(vdp_dither_cfg *cfg)
{
    /* drv transfer */
    vo_drv_get_intf_dither_in_out_mode(cfg);
    vo_drv_get_intf_dither_sed_and_thr(cfg);
    vo_hal_intf_set_lcd_dither(cfg);
}

static hi_void vo_drv_set_intf_rgb_dither(hi_u32 in_bit_width, hi_u32 out_bit_width)
{
    vdp_dither_cfg dither_cfg = {0};

    /* default setting for rgb24bit */
    dither_cfg.dither_en = 1;
    dither_cfg.dither_round = 1;
    dither_cfg.dither_round_unlim = 1;
    dither_cfg.dither_domain_mode = 1;
    dither_cfg.dither_tap_mode = 1;
    dither_cfg.io_mode = DITHER_IO_MODE_12_8; /* dither模块输入默认10bit转到12bit */

    if (in_bit_width == VO_INPUT_BIT_WIDTH_10) {
        if (out_bit_width == VO_OUTPUT_BIT_WIDTH_10) {
            dither_cfg.dither_en = 0;
        } else if (out_bit_width == VO_OUTPUT_BIT_WIDTH_6) { /* for rgb16bit, rgb18bit */
            dither_cfg.dither_round = 0;
            dither_cfg.io_mode = DITHER_IO_MODE_10_6;
        }
    }

    vo_drv_set_intf_rgb_dither_mode(&dither_cfg);
}

hi_void vo_drv_set_intf_dither(hi_vo_intf_type intf_type, hi_u32 out_bit_width)
{
    if (vo_drv_is_rgb_intf(intf_type)) {
        vo_drv_set_intf_rgb_dither(VO_INPUT_BIT_WIDTH_10, out_bit_width); /* it is always 10bit before dither */
    }
}
#endif

hi_s32 vo_drv_check_dev_fixed_clk(hi_vo_dev dev, hi_vo_fixed_clk fixed_clk)
{
    return HI_ERR_VO_NOT_SUPPORT;
}

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
