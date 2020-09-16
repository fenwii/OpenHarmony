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

#include "drv_vo_comm.h"
#include "drv_vo.h"
#include "hal_vo.h"
#include "vo.h"
#include "hi_math.h"
#include <common.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")
#if VO_DESC("dev drv api")

hi_u32 vo_drv_get_dev_bg_color(hi_vo_dev dev)
{
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(dev);
    return drv_dev_ctx->vou_attr.bg_color;
}

hi_vo_intf_type vo_drv_get_dev_intf_type(hi_vo_dev dev)
{
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(dev);
    return drv_dev_ctx->vou_attr.intf_type;
}

hi_vo_intf_sync vo_drv_get_dev_intf_sync(hi_vo_dev dev)
{
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(dev);
    return drv_dev_ctx->vou_attr.intf_sync;
}

hi_u32 vo_drv_get_dev_vtth(hi_vo_dev dev)
{
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(dev);
    return drv_dev_ctx->vtth;
}

hi_u32 vo_drv_get_dev_vtth2(hi_vo_dev dev)
{
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(dev);
    return drv_dev_ctx->vtth2;
}

hi_void vou_drv_set_disp_max_size(hi_vo_dev dev, hi_u32 max_width, hi_u32 max_height)
{
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(dev);
    drv_dev_ctx->max_width = max_width;
    drv_dev_ctx->max_height = max_height;
}

#endif
#if VO_DESC("dev")
hi_void vo_drv_get_sync_info(hi_vo_dev dev, hal_disp_syncinfo *sync_info)
{
    hal_disp_syncinfo *hal_sync = HI_NULL;
    hi_vo_sync_info *vo_sync_info = HI_NULL;
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(dev);

    if (drv_dev_ctx->vou_attr.intf_sync == HI_VO_OUT_USER) {
        vo_sync_info = &drv_dev_ctx->vou_attr.sync_info;
        sync_info->syncm = vo_sync_info->syncm;
        sync_info->iop = vo_sync_info->iop;
        sync_info->intfb = vo_sync_info->intfb;
        sync_info->vact = vo_sync_info->vact;
        sync_info->vbb = vo_sync_info->vbb;
        sync_info->vfb = vo_sync_info->vfb;
        sync_info->hact = vo_sync_info->hact;
        sync_info->hbb = vo_sync_info->hbb;
        sync_info->hfb = vo_sync_info->hfb;
        sync_info->hmid = vo_sync_info->hmid;
        sync_info->bvact = vo_sync_info->bvact;
        sync_info->bvbb = vo_sync_info->bvbb;
        sync_info->bvfb = vo_sync_info->bvfb;
        sync_info->hpw = vo_sync_info->hpw;
        sync_info->vpw = vo_sync_info->vpw;
        sync_info->idv = vo_sync_info->idv;
        sync_info->ihs = vo_sync_info->ihs;
        sync_info->ivs = vo_sync_info->ivs;
        return;
    }

    hal_sync = vo_drv_comm_get_sync_timing(drv_dev_ctx->vou_attr.intf_sync);
    memcpy(sync_info, hal_sync, sizeof(hal_disp_syncinfo));
}

hi_void vo_drv_set_sync_info(hi_vo_dev dev, hal_disp_syncinfo *sync_info)
{
    vo_hal_intf_set_sync_info(dev, sync_info);
}

hi_bool vo_drv_is_progressive(hi_vo_dev dev)
{
    hal_disp_syncinfo sync_info = {0};

    vo_drv_get_sync_info(dev, &sync_info);
    return sync_info.iop;
}

hi_void vo_drv_int_reg_up_mode(hi_vo_layer layer, vo_int_mode int_mode)
{
    hal_video_set_layer_up_mode(layer, int_mode);
}

static hi_u32 vo_drv_get_dev_default_vtth(hi_vo_dev dev)
{
    hi_u32 dev_vtth = 0;
    hi_vo_intf_sync intf_sync;

    if (vo_drv_is_phy_dev_hd(dev)) {
        intf_sync = vo_drv_get_dev_intf_sync(dev);
        switch (intf_sync) {
            case HI_VO_OUT_7680x4320_30:
                dev_vtth = 8 * VO_HD_VTTH_WATERLINE; /* 8 */
                break;

            case HI_VO_OUT_3840x2160_60:
            case HI_VO_OUT_3840x2160_50:
            case HI_VO_OUT_4096x2160_60:
            case HI_VO_OUT_4096x2160_50:
                dev_vtth = 4 * VO_HD_VTTH_WATERLINE; /* 4 */
                break;

            case HI_VO_OUT_2560x1600_60:
            case HI_VO_OUT_3840x2160_24:
            case HI_VO_OUT_3840x2160_25:
            case HI_VO_OUT_3840x2160_30:
            case HI_VO_OUT_4096x2160_24:
            case HI_VO_OUT_4096x2160_25:
            case HI_VO_OUT_4096x2160_30:
                dev_vtth = 2 * VO_HD_VTTH_WATERLINE; /* 2 */
                break;

            default:
                dev_vtth = VO_HD_VTTH_WATERLINE;
                break;
        }
    } else {
        dev_vtth = VO_SD_VTTH_WATERLINE;
    }

    return dev_vtth;
}

hi_void vo_drv_set_dev_default_vtth(hi_vo_dev dev)
{
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(dev);

    if (vo_drv_is_phy_dev_hd(dev) == HI_TRUE) {
        drv_dev_ctx->vtth = VO_HD_VTTH_WATERLINE;
    } else {
        drv_dev_ctx->vtth = VO_SD_VTTH_WATERLINE;
    }
}

hi_s32 vo_drv_set_dev_vtth(hi_vo_dev dev, hi_u32 vtth)
{
    hi_u32 dft_vtth;
    hi_u32 vtth_max = VO_MAX_VTTH_WATERLINE;
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(dev);

    dft_vtth = vo_drv_get_dev_default_vtth(dev);
    if (vtth > vtth_max) {
        vo_err_trace("dev:%d, vtth value(%d) should be in range: [%d,%d]\n",
            dev, vtth, dft_vtth, vtth_max);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    drv_dev_ctx->vtth = MAX2(vtth, dft_vtth);
    return HI_SUCCESS;
}

static hi_u32 vo_drv_get_dev_default_vtth2(hi_vo_dev dev)
{
    hi_u32 dft_vtth2;

    dft_vtth2 = (vo_drv_is_phy_dev_hd(dev) == HI_TRUE) ? VO_HD_VTTH_WATERLINE2 : VO_SD_VTTH_WATERLINE2;
    return dft_vtth2;
}

hi_void vo_drv_set_dev_default_vtth2(hi_vo_dev dev)
{
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(dev);
    drv_dev_ctx->vtth2 = vo_drv_get_dev_default_vtth2(dev);
}

hi_s32 vo_drv_set_dev_vtth2(hi_vo_dev dev, hi_u32 vtth)
{
    hi_u32 dft_vtth2;
    hi_u32 drv_vtth2;
    hi_u32 vtth1;
    hi_u32 vtth_max = VO_MAX_VTTH_WATERLINE;
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(dev);

    dft_vtth2 = vo_drv_get_dev_default_vtth2(dev);
    if (vtth > vtth_max) {
        vo_err_trace("dev:%d, vtth value(%d) should be in range: [%d,%d]\n",
            dev, vtth, dft_vtth2, vtth_max);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }
    drv_vtth2 = MAX2(vtth, dft_vtth2);
    vtth1 = drv_dev_ctx->vtth;

    drv_dev_ctx->vtth2 = MIN2(drv_vtth2, vtth1);
    return HI_SUCCESS;
}

hi_bool vou_drv_get_dev_enable(hi_vo_dev dev)
{
    hi_bool intf_en = HI_FALSE;

    hal_disp_get_intf_enable(dev, &intf_en);
    return intf_en;
}

static hi_s32 vo_drv_check_dev_pll_param(hi_vo_dev dev, const hi_vo_pll *pll)
{
    if ((pll->fb_div > 0xfff) ||
        (pll->frac > 0xffffff) ||
        (pll->ref_div > 0x3f) ||
        (pll->ref_div == 0) ||
        (pll->post_div1 > 0x7) ||
        (pll->post_div1 == 0) ||
        (pll->post_div2 > 0x7) ||
        (pll->post_div2 == 0)) {
        vo_err_trace("dev(%d) pll param (fb_div,frac,ref_div,post_div1,post_div2)="
            "(0x%x,0x%x,0x%x,0x%x,0x%x) illegal .\n", dev,
            pll->fb_div, pll->frac, pll->ref_div,
            pll->post_div1, pll->post_div2);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

static hi_s32 vo_drv_check_dev_pll_postdiv(hi_vo_dev dev, const hi_vo_pll *pll)
{
    if (pll->post_div1 < pll->post_div2) {
        vo_err_trace("dev(%d) pll postdiv (post_div1,post_div2)="
            "(0x%x,0x%x) illegal, it should be div1 >= div2.\n", dev, pll->post_div1, pll->post_div2);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

static hi_s32 vo_drv_check_dev_pll_foutvco(hi_vo_dev dev, const hi_vo_user_sync_info *sync_info)
{
    hi_u32 foutcvo;
    hi_u32 src_clk;
    hi_u32 pixel_clk;
    hi_u32 max_clk;
    const hi_vo_pll *pll = &(sync_info->user_sync_attr.vo_pll);

    /* 0x01000000: 2^24 */
    foutcvo = VO_PLL_FREF * pll->fb_div / pll->ref_div + VO_PLL_FREF * pll->frac / VO_PLL_FRAC_PREC / pll->ref_div;
    if ((foutcvo < VO_PLL_FOUTCVO_MIN) || (foutcvo > VO_PLL_FOUTCVO_MAX)) {
        vo_err_trace("dev(%d) pll foutcvo (fb_div,frac,ref_div)=(%u,%u,%u) illegal. foutcvo %u, not in [%u, %u]\n",
            dev, pll->fb_div, pll->frac, pll->ref_div, foutcvo, VO_PLL_FOUTCVO_MIN, VO_PLL_FOUTCVO_MAX);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    src_clk = foutcvo * VO_CLK_MHZ_UNIT / (pll->post_div1 * pll->post_div2);
    pixel_clk = src_clk / (sync_info->pre_div * sync_info->dev_div);
    max_clk = vo_drv_dev_get_max_clk(dev);
    if (pixel_clk > max_clk) {
        vo_err_trace("dev(%d) pll (fb_div,frac,ref_div,post_div1,post_div2,pre_div,dev_div)=(%u,%u,%u,%u,%u,%u,%u)"
            " is illegal. pixel clk %uHz is larger than %uHz.\n", dev, pll->fb_div, pll->frac, pll->ref_div,
            pll->post_div1, pll->post_div2, sync_info->pre_div, sync_info->dev_div, pixel_clk, max_clk);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

static hi_s32 vo_drv_check_dev_pll(hi_vo_dev dev, const hi_vo_user_sync_info *sync_info)
{
    hi_s32 ret;

    ret = vo_drv_check_dev_pll_param(dev, &sync_info->user_sync_attr.vo_pll);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    ret = vo_drv_check_dev_pll_postdiv(dev, &sync_info->user_sync_attr.vo_pll);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    return vo_drv_check_dev_pll_foutvco(dev, sync_info);
}

static hi_s32 vo_drv_check_dev_lcdmclkdiv(hi_vo_dev dev, hi_u32 lcd_m_clk_div)
{
    if ((lcd_m_clk_div > VO_LCDMCLK_DIV_MAX) || (lcd_m_clk_div == 0)) {
        vo_err_trace("dev(%d) lcd_mclk value %d illegal, it must be in (0,%d].\n",
            dev, lcd_m_clk_div, VO_LCDMCLK_DIV_MAX);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

hi_s32 vo_drv_check_dev_clkvalue(hi_vo_dev dev, const hi_vo_user_sync_info *sync_info)
{
    hi_s32 ret;
    hi_vo_clk_src clk_src = sync_info->user_sync_attr.clk_src;

    if ((dev != VO_DEV_DHD0) && (dev != VO_DEV_DHD1)) {
        return HI_SUCCESS;
    }

    ret = vo_drv_check_dev_clk_src(dev, sync_info->user_sync_attr.clk_src);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    if ((clk_src == HI_VO_CLK_SRC_PLL) || (clk_src == HI_VO_CLK_SRC_PLL_FOUT4)) {
        return vo_drv_check_dev_pll(dev, sync_info);
    } else if (clk_src == HI_VO_CLK_SRC_LCDMCLK) {
        return vo_drv_check_dev_lcdmclkdiv(dev, sync_info->user_sync_attr.lcd_m_clk_div);
    } else if (clk_src == HI_VO_CLK_SRC_FIXED) {
        return vo_drv_check_dev_fixed_clk(dev, sync_info->user_sync_attr.fixed_clk);
    }

    return HI_ERR_VO_ILLEGAL_PARAM;
}

hi_s32 vou_drv_check_dsd_intf(hi_vo_dev dev, hi_vo_intf_type intf_type)
{
    if ((intf_type & ~(HI_VO_INTF_CVBS)) || (intf_type == 0)) {
        vo_err_trace("vo device%d does not support intf(%d) !\n", dev, intf_type);
        return HI_ERR_VO_NOT_SUPPORT;
    }

    return HI_SUCCESS;
}

hi_s32 vou_drv_check_dev_sync(hi_vo_dev dev, hi_vo_intf_type intf_type, hi_vo_intf_sync intf_sync)
{
    hi_s32 ret;

    if ((intf_sync == HI_VO_OUT_960H_PAL) || (intf_sync == HI_VO_OUT_960H_NTSC)) {
        vo_err_trace("vo%d's intfsync %d illegal, vo doesn't support interlaced sync %d!\n", dev,
            intf_sync, intf_sync);
        return HI_ERR_VO_NOT_SUPPORT;
    }

    ret = vou_drv_check_hdmi_sync(dev, intf_type, intf_sync);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    ret = vou_drv_check_bt_sync(dev, intf_type, intf_sync);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    ret = vou_drv_check_vga_sync(dev, intf_type, intf_sync);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    ret = vou_drv_check_cvbs_sync(dev, intf_type, intf_sync);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    ret = vou_drv_check_rgb_sync(dev, intf_type, intf_sync);
    return ret;
}

static hi_s32 vo_drv_check_bool_value(hi_bool bool_val)
{
    if ((bool_val != HI_TRUE) && (bool_val != HI_FALSE)) {
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

static hi_s32 vo_drv_check_dev_bool_sync_info(hi_vo_dev dev, const hi_vo_sync_info *sync_info)
{
    if ((vo_drv_check_bool_value(sync_info->syncm) != HI_SUCCESS) ||
        (vo_drv_check_bool_value(sync_info->iop) != HI_SUCCESS) ||
        (vo_drv_check_bool_value(sync_info->idv) != HI_SUCCESS) ||
        (vo_drv_check_bool_value(sync_info->ihs) != HI_SUCCESS) ||
        (vo_drv_check_bool_value(sync_info->ivs) != HI_SUCCESS)) {
        vo_err_trace("vo%d: sync's syncm(%d),iop(%d),idv(%d),ihs(%d),ivs(%u) should be %u or %u!\n",
            dev, sync_info->syncm, sync_info->iop, sync_info->idv, sync_info->ihs, sync_info->ivs, HI_TRUE, HI_FALSE);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

static hi_s32 vo_drv_check_dev_vertical_sync_info(hi_vo_dev dev, const hi_vo_sync_info *sync_info)
{
    if (sync_info->intfb > VO_MAX_USER_SYNC_INTFB) {
        vo_err_trace("vo%d: sync's intfb(%u) should be [0, %u]!", dev, sync_info->intfb, VO_MAX_USER_SYNC_INTFB);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    if ((sync_info->vact < VO_MIN_USER_SYNC_VACT) || (sync_info->vact > VO_MAX_USER_SYNC_VACT)) {
        vo_err_trace("vo%d: sync's vact(%u) should be [%u, %u]!\n", dev, sync_info->vact,
            VO_MIN_USER_SYNC_VACT, VO_MAX_USER_SYNC_VACT);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    if ((sync_info->vbb < VO_MIN_USER_SYNC_VBB) || (sync_info->vbb > VO_MAX_USER_SYNC_VBB)) {
        vo_err_trace("vo%d: sync's vbb(%u) should be [%u, %u]!\n", dev, sync_info->vbb,
            VO_MIN_USER_SYNC_VBB, VO_MAX_USER_SYNC_VBB);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    if ((sync_info->vfb < VO_MIN_USER_SYNC_VFB) || (sync_info->vfb > VO_MAX_USER_SYNC_VFB)) {
        vo_err_trace("vo%d: sync's vfb(%u) should be [%u, %u]!\n", dev, sync_info->vfb,
            VO_MIN_USER_SYNC_VFB, VO_MAX_USER_SYNC_VFB);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

static hi_s32 vo_drv_check_dev_horizontal_sync_info(hi_vo_dev dev, const hi_vo_sync_info *sync_info)
{
    if ((sync_info->hact < VO_MIN_USER_SYNC_HACT) || (sync_info->hact > VO_MAX_USER_SYNC_HACT)) {
        vo_err_trace("vo%d: sync's hact(%u) should be [%u, %u]!\n", dev, sync_info->hact,
            VO_MIN_USER_SYNC_HACT, VO_MAX_USER_SYNC_HACT);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    if (sync_info->hbb < VO_MIN_USER_SYNC_HBB) {
        vo_err_trace("vo%d: sync's hbb(%u) should be [%u, %u]!\n", dev, sync_info->hbb,
            VO_MIN_USER_SYNC_HBB, VO_MAX_USER_SYNC_HBB);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    if (sync_info->hfb < VO_MIN_USER_SYNC_HFB) {
        vo_err_trace("vo%d: sync's hfb(%u) should be [%u, %u]!\n", dev, sync_info->hfb,
            VO_MIN_USER_SYNC_HFB, VO_MAX_USER_SYNC_HFB);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

static hi_s32 vo_drv_check_dev_bottom_sync_info(hi_vo_dev dev, const hi_vo_sync_info *sync_info)
{
    if ((sync_info->iop == 0) && ((sync_info->bvact == 0) || (sync_info->bvbb == 0) || (sync_info->bvfb == 0))) {
        vo_err_trace("vo%d: sync's bvact(%u) bvbb(%u) bvfb(%u) can't be 0 when interlaced timing!\n",
            dev, sync_info->bvact, sync_info->bvbb, sync_info->bvfb);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    if (sync_info->bvact > VO_MAX_USER_SYNC_BVACT) {
        vo_err_trace("vo%d: sync's bvact(%u) should be [0, %u]!", dev, sync_info->bvact, VO_MAX_USER_SYNC_BVACT);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    if (sync_info->bvbb > VO_MAX_USER_SYNC_BVBB) {
        vo_err_trace("vo%d: sync's bvbb(%u) should be [0, %u]!", dev, sync_info->bvbb, VO_MAX_USER_SYNC_BVBB);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    if (sync_info->bvfb > VO_MAX_USER_SYNC_BVFB) {
        vo_err_trace("vo%d: sync's bvfb(%u) should be [0, %u]!", dev, sync_info->bvfb, VO_MAX_USER_SYNC_BVFB);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

static hi_s32 vo_drv_check_dev_pulse_sync_info(hi_vo_dev dev, const hi_vo_sync_info *sync_info)
{
    if (sync_info->hpw < VO_MIN_USER_SYNC_HPW) {
        vo_err_trace("vo%d: sync's hpw(%u) should be [%u, %u]!\n", dev, sync_info->hpw,
            VO_MIN_USER_SYNC_HPW, VO_MAX_USER_SYNC_HPW);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    if ((sync_info->vpw < VO_MIN_USER_SYNC_VPW) || (sync_info->vpw > VO_MAX_USER_SYNC_VPW)) {
        vo_err_trace("vo%d: sync's vpw(%u) should be [%u, %u]!\n", dev, sync_info->vpw,
            VO_MIN_USER_SYNC_VPW, VO_MAX_USER_SYNC_VPW);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

static hi_s32 vo_drv_check_dev_sync_info(hi_vo_dev dev, const hi_vo_sync_info *sync_info)
{
    hi_s32 ret;

    ret = vo_drv_check_dev_bool_sync_info(dev, sync_info);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    ret = vo_drv_check_dev_vertical_sync_info(dev, sync_info);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    ret = vo_drv_check_dev_horizontal_sync_info(dev, sync_info);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    ret = vo_drv_check_dev_bottom_sync_info(dev, sync_info);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    ret = vo_drv_check_dev_pulse_sync_info(dev, sync_info);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    return HI_SUCCESS;
}

hi_s32 vou_drv_check_dev_pub_attr(hi_vo_dev dev, const hi_vo_pub_attr *pub_attr)
{
    hi_s32 ret = HI_SUCCESS;

    if (vo_drv_is_phy_dev_hd(dev) || vo_drv_is_phy_dev_sd(dev)) {
        ret = vou_drv_check_dev_intf(dev, pub_attr->intf_type);
        if (ret != HI_SUCCESS) {
            vo_err_trace("vo%d check device's interface %d illegal!\n", dev, pub_attr->intf_type);
            return ret;
        }
    }

    if (pub_attr->intf_sync == HI_VO_OUT_USER) {
        /*
         * user defined sync will be welcome for all interface type
         * WARNING: user must make sure to config right sync, otherwise, screen dosen't work!
         */
        return vo_drv_check_dev_sync_info(dev, &(pub_attr->sync_info));
    }

    ret = vou_drv_check_dev_sync(dev, pub_attr->intf_type, pub_attr->intf_sync);
    return ret;
}

hi_void vo_drv_get_dev_reg_up(hi_vo_dev dev)
{
    hi_u64 start;
    start = get_timer(0);

    do {
        if (get_timer(start) >= VO_DEV_REG_UP_TIMEOUT) { /* 50 ms */
            break;
        }
    } while (hal_disp_get_reg_up(dev) != 0);
}

#endif

#if VO_DESC("dev layer prio")

hi_void vou_drv_set_layer_priority(hi_vo_dev dev, hi_vo_layer layer, hi_u32 priority)
{
    hal_cbm_set_cbm_mixer_prio(layer, priority, dev);

    hal_disp_set_reg_up(dev);
}
#endif

#if VO_DESC("dev intf")
hi_void vou_drv_intf_csc_config(hi_vo_intf_type intf, const hi_vo_csc *csc)
{
    csc_coef coef;

    memset(&coef, 0x0, sizeof(csc_coef));

    vou_drv_calc_csc_matrix(csc, csc->csc_matrix, &coef);

    vo_drv_csc_trans_to_register(&coef);

    vo_hal_intf_set_csc_cfg(intf, &coef);
}

hi_void vo_drv_set_vga_param(hi_vo_dev dev, const hi_vo_vga_param *vga_param)
{
    vo_hal_intf_set_csc_enable(HI_VO_INTF_VGA, HI_TRUE);
    vou_drv_intf_csc_config(HI_VO_INTF_VGA, &vga_param->csc);
    vo_hal_intf_set_dac_gc(HI_VO_INTF_VGA, vga_param->gain);
    vo_hal_intf_set_vga_hsp_cfg(HI_TRUE, (hi_u32)vga_param->sharpen_strength);
    hal_disp_set_reg_up(dev);
}

hi_void vo_drv_set_hdmi_mode(hi_vo_dev dev, const hi_vo_hdmi_param *hdmi_param)
{
    if ((hdmi_param->csc.csc_matrix >= HI_VO_CSC_MATRIX_BT601LIMIT_TO_RGBFULL) &&
        (hdmi_param->csc.csc_matrix <= HI_VO_CSC_MATRIX_BT709FULL_TO_RGBLIMIT)) {
        hal_disp_set_hdmi_mode(dev, 1);  /* 1: RGB */
    } else  {
        hal_disp_set_hdmi_mode(dev, 0);  /* 0: RGB */
    }
}

hi_void vo_drv_set_hdmi_param(hi_vo_dev dev, const hi_vo_hdmi_param *hdmi_param)
{
    vo_hal_intf_set_csc_enable(HI_VO_INTF_HDMI, HI_TRUE);
    vou_drv_intf_csc_config(HI_VO_INTF_HDMI, &hdmi_param->csc);
    vo_drv_set_hdmi_mode(dev, hdmi_param);
    hal_disp_set_reg_up(dev);
}

hi_void vo_drv_set_rgb_param(hi_vo_dev dev, const hi_vo_rgb_param *rgb_param)
{
    vo_hal_intf_set_csc_enable(HI_VO_INTF_RGB_6BIT, HI_TRUE);
    vou_drv_intf_csc_config(HI_VO_INTF_RGB_6BIT, &rgb_param->csc);
    hal_disp_set_reg_up(dev);
}

hi_void vo_drv_set_dev_mpp_chn(hi_vo_dev dev, hi_mpp_chn *mpp_chn)
{
    mpp_chn->mod_id = HI_ID_VO;
    mpp_chn->chn_id = 0;
    mpp_chn->dev_id = dev;
}

hi_bool vo_drv_is_hdmi_intf(hi_vo_intf_type intf_type)
{
    if (intf_type & HI_VO_INTF_HDMI) {
        return HI_TRUE;
    }
    return HI_FALSE;
}

hi_bool vo_drv_is_bt1120_intf(hi_vo_intf_type intf_type)
{
    if ((intf_type & HI_VO_INTF_BT1120)) {
        return HI_TRUE;
    }
    return HI_FALSE;
}

hi_bool vo_drv_is_rgb_intf(hi_vo_intf_type intf_type)
{
    if ((intf_type & HI_VO_INTF_RGB_6BIT) ||
        (intf_type & HI_VO_INTF_RGB_8BIT) ||
        (intf_type & HI_VO_INTF_RGB_16BIT) ||
        (intf_type & HI_VO_INTF_RGB_18BIT) ||
        (intf_type & HI_VO_INTF_RGB_24BIT)) {
        return HI_TRUE;
    }
    return HI_FALSE;
}

hi_bool vo_drv_is_mipi_intf(hi_vo_intf_type intf_type)
{
    if ((intf_type & HI_VO_INTF_MIPI) ||
        (intf_type & HI_VO_INTF_MIPI_SLAVE)) {
        return HI_TRUE;
    }
    return HI_FALSE;
}
#endif

#if VO_DESC("dev interrupt")

hi_void vo_drv_int_set_mode(hi_vo_dev dev, vo_int_mode int_mode)
{
    hal_disp_set_vtthd_mode(dev, int_mode);
}
#endif

#if VO_DESC("check dev id")
hi_s32 vo_drv_check_dev_id_pub(hi_vo_dev dev)
{
    if ((dev < 0) || (dev >= HI_VO_MAX_DEV_NUM)) {
        return HI_ERR_VO_INVALID_DEV_ID;
    }
    return HI_SUCCESS;
}

#endif

#if VO_DESC("check layer id")
hi_s32 vo_drv_check_layer_id_pub(hi_vo_layer layer)
{
    if ((layer < 0) || (layer >= HI_VO_MAX_LAYER_NUM)) {
        return HI_ERR_VO_INVALID_LAYER_ID;
    }
    return HI_SUCCESS;
}

#endif

hi_void vo_drv_set_pub_attr(hi_vo_dev dev, const hi_vo_pub_attr *pub_attr)
{
    vo_drv_dev *drv_dev_ctx = HI_NULL;
    drv_dev_ctx = vo_drv_get_dev_ctx(dev);

    memcpy(&drv_dev_ctx->vou_attr, pub_attr, sizeof(hi_vo_pub_attr));
    drv_dev_ctx->config = HI_TRUE;
}

hi_void vo_drv_enable(hi_vo_dev dev)
{
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(dev);
    drv_dev_ctx->vo_enable = HI_TRUE;
}

hi_void vo_drv_disable(hi_vo_dev dev)
{
    vo_drv_dev *drv_dev_ctx = vo_drv_get_dev_ctx(dev);

    drv_dev_ctx->config = HI_FALSE;
    drv_dev_ctx->vo_enable = HI_FALSE;
    memset(&drv_dev_ctx->vou_attr, 0, sizeof(hi_vo_pub_attr));
}

hi_u32 vou_drv_get_dev_layer_num(hi_vo_dev dev)
{
    vo_drv_dev *dev_ctx = HI_NULL;
    dev_ctx = vo_drv_get_dev_ctx(dev);
    return dev_ctx->layer_num;
}

hi_void vou_drv_get_dev_layer(hi_vo_dev dev, hi_vo_layer *layer, hi_u32 vo_layer_num)
{
    hi_u32 layer_num;
    hi_u32 i, j;
    vo_drv_layer *layer_ctx = HI_NULL;

    layer_num = vou_drv_get_dev_layer_num(dev);
    if (layer_num > vo_layer_num) {
        vo_err_trace("the layer num(%u) is larger than the input num(%u)", layer_num, vo_layer_num);
        layer_num = vo_layer_num;
    }

    for (i = 0, j = 0; i < HI_VO_MAX_LAYER_NUM; i++) {
        layer_ctx = vo_drv_get_layer_ctx(i);
        if (dev == layer_ctx->bind_dev) {
            *(layer + j) = i;
            j++;
        }

        if (j == layer_num) {
            return;
        }
    }

    return;
}

#if VO_DESC("dev")
hi_bool vo_drv_is_phy_dev_uhd(hi_vo_dev dev)
{
    if (dev == VO_DEV_DHD0) {
        return HI_TRUE;
    }

    return HI_FALSE;
}

hi_bool vo_drv_is_phy_dev_hd(hi_vo_dev dev)
{
    if ((dev == VO_DEV_DHD0) ||
        (dev == VO_DEV_DHD1)) {
        return HI_TRUE;
    }

    return HI_FALSE;
}

hi_bool vo_drv_is_phy_dev_sd(hi_vo_dev dev)
{
    if ((dev == VO_DEV_DSD0)) {
        return HI_TRUE;
    }

    return HI_FALSE;
}
#endif

hi_vo_layer vo_drv_get_gfx_layer(hi_vo_dev dev)
{
    hal_disp_layer hal_layer;

    switch (dev) {
        case VO_DEV_DHD0:
            hal_layer = HAL_DISP_LAYER_GFX0;
            break;
        case VO_DEV_DHD1:
            hal_layer = HAL_DISP_LAYER_GFX1;
            break;
        case VO_DEV_DSD0:
            hal_layer = HAL_DISP_LAYER_GFX3;
            break;
        default:
            hal_layer = HAL_DISP_LAYER_BUTT;
            break;
    }

    return hal_layer;
}

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
