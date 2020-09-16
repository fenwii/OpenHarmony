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

#include "mkp_vo_dev.h"
#include "mkp_vo_intf.h"
#include "mkp_vo_init.h"
#include "mkp_vo_video.h"
#include "mkp_vo_comm.h"
#include "mkp_vo_gfx.h"
#include "hi_math.h"
#include "mkp_vo.h"
#include "hi_board.h"
#include "common.h"
#include "vo.h"

static hi_u32 g_bg_color[HI_VO_MAX_PHYS_DEV_NUM] = {0x00ffff, 0xFF00, 0xFF00}; /* default value is CYAN */

hi_u32 vo_dev_get_bg_color(hi_vo_dev dev)
{
    return g_bg_color[dev];
}

hi_void vo_dev_set_bg_color(hi_vo_dev dev, hi_u32 bg_color)
{
    g_bg_color[dev] = bg_color;
}

#if VO_DESC("dev pub api")
vo_dev_info g_vo_dev[HI_VO_MAX_DEV_NUM] = {0};

vo_dev_info *vo_get_dev_ctx(hi_vo_dev vo_dev)
{
    return &(g_vo_dev[vo_dev]);
}

hi_s32 vo_init_dev_ctx(hi_vo_dev dev)
{
    hi_u32 dev_ctx_len;
    vo_dev_info *dev_ctx = HI_NULL;

    dev_ctx = vo_get_dev_ctx(dev);

    dev_ctx_len = sizeof(vo_dev_info);

    memset(dev_ctx, 0, dev_ctx_len);
    vo_init_vga_param(&(dev_ctx->vga_param));
    vo_init_hdmi_param(&(dev_ctx->hdmi_param));
    vo_init_rgb_param(&(dev_ctx->rgb_param));
    vo_init_bt_param(&(dev_ctx->bt_param));
    return HI_SUCCESS;
}

hi_void vo_init_dev_info(hi_void)
{
    if ((vo_get_vo_init_flag() == HI_FALSE)) {
        vo_drv_dev_info_init();
    }
}

hi_bool vo_is_dev_enabled(hi_vo_dev dev)
{
    vo_dev_info *dev_ctx = HI_NULL;

    if (vo_def_check_dev_id(dev) != HI_SUCCESS) {
        vo_warn_trace("Vo device id %d is invalid!\n", dev);
        return HI_FALSE;
    }

    dev_ctx = vo_get_dev_ctx(dev);
    if (dev_ctx == HI_NULL) {
        return HI_FALSE;
    }

    return dev_ctx->vo_enable;
}

hi_void vo_get_dev_max_size(hi_vo_dev dev, hi_size *dev_size)
{
    vo_dev_info *dev_ctx = HI_NULL;

    dev_ctx = vo_get_dev_ctx(dev);
    if (dev_ctx == HI_NULL) {
        vo_err_trace("vo dev id %d ctx is HI_NULL!\n", dev);
        dev_size->width = 0;
        dev_size->height = 0;
        return;
    }

    dev_size->width = dev_ctx->max_width;
    dev_size->height = dev_ctx->max_height;
}

#endif

#if VO_DESC("intf sync info")
static vo_intf_sync_info g_vo_intf_sync_info[HI_VO_OUT_BUTT] = {
    { HI_VO_OUT_PAL,          720,  576  },
    { HI_VO_OUT_NTSC,         720,  480  },
    { HI_VO_OUT_960H_PAL,     960,  576  },
    { HI_VO_OUT_960H_NTSC,    960,  480  },

    { HI_VO_OUT_640x480_60,   640,  480  },
    { HI_VO_OUT_480P60,       720,  480  },
    { HI_VO_OUT_576P50,       720,  576  },
    { HI_VO_OUT_800x600_60,   800,  600  },
    { HI_VO_OUT_1024x768_60,  1024, 768  },
    { HI_VO_OUT_720P50,       1280, 720  },
    { HI_VO_OUT_720P60,       1280, 720  },
    { HI_VO_OUT_1280x800_60,  1280, 800  },
    { HI_VO_OUT_1280x1024_60, 1280, 1024 },
    { HI_VO_OUT_1366x768_60,  1366, 768 },
    { HI_VO_OUT_1400x1050_60, 1400, 1050 },
    { HI_VO_OUT_1440x900_60,  1440, 900 },
    { HI_VO_OUT_1600x1200_60, 1600, 1200 },
    { HI_VO_OUT_1680x1050_60, 1680, 1050 },

    { HI_VO_OUT_1080P24,      1920, 1080 },
    { HI_VO_OUT_1080P25,      1920, 1080 },
    { HI_VO_OUT_1080P30,      1920, 1080 },
    { HI_VO_OUT_1080I50,      1920, 1080 },
    { HI_VO_OUT_1080I60,      1920, 1080 },
    { HI_VO_OUT_1080P50,      1920, 1080 },
    { HI_VO_OUT_1080P60,      1920, 1080 },

    { HI_VO_OUT_1920x1200_60, 1920, 1200 },
    { HI_VO_OUT_1920x2160_30, 1920, 2160 },
    { HI_VO_OUT_2560x1440_30, 2560, 1440 },
    { HI_VO_OUT_2560x1440_60, 2560, 1440 },
    { HI_VO_OUT_2560x1600_60, 2560, 1600 },

    { HI_VO_OUT_3840x2160_24, 3840, 2160 },
    { HI_VO_OUT_3840x2160_25, 3840, 2160 },
    { HI_VO_OUT_3840x2160_30, 3840, 2160 },
    { HI_VO_OUT_3840x2160_50, 3840, 2160 },
    { HI_VO_OUT_3840x2160_60, 3840, 2160 },
    { HI_VO_OUT_4096x2160_24, 4096, 2160 },
    { HI_VO_OUT_4096x2160_25, 4096, 2160 },
    { HI_VO_OUT_4096x2160_30, 4096, 2160 },
    { HI_VO_OUT_4096x2160_50, 4096, 2160 },
    { HI_VO_OUT_4096x2160_60, 4096, 2160 },
    { HI_VO_OUT_7680x4320_30, 7680, 4320 },

    { HI_VO_OUT_240x320_50,   240,  320 },
    { HI_VO_OUT_320x240_50,   320,  240 },
    { HI_VO_OUT_240x320_60,   240,  320 },
    { HI_VO_OUT_320x240_60,   320,  240 },
    { HI_VO_OUT_800x600_50,   800,  600 },

    { HI_VO_OUT_720x1280_60,  720,  1280 },
    { HI_VO_OUT_1080x1920_60, 1080, 1920 },

    { HI_VO_OUT_USER,         0,    0,   },
};

static vo_intf_sync_info *vo_get_intf_sync_info(hi_vo_intf_sync intf_sync)
{
    return &g_vo_intf_sync_info[intf_sync];
}

hi_void vo_get_intf_sync_size(hi_vo_intf_sync intf_sync, hi_u32 *width, hi_u32 *height)
{
    vo_intf_sync_info *sync_info = HI_NULL;

    if (vo_is_typical_intf_sync(intf_sync) != HI_TRUE) {
        return;
    }

    sync_info = vo_get_intf_sync_info(intf_sync);
    if (sync_info->intf_sync == intf_sync) {
        *width = sync_info->width;
        *height = sync_info->height;
    }
}

static hi_void vo_get_intf_sync_size_user(const hi_vo_sync_info *sync_info, hi_u32 *width, hi_u32 *height)
{
    *width = sync_info->hact;
    *height = (sync_info->iop) ? sync_info->vact : sync_info->vact * 2; /* 2 times */
}
#endif

#if VO_DESC("enable dev")

static hi_void vo_enable_clk(hi_void)
{
    vo_lpw_bus_reset(HI_FALSE);
    vo_drv_set_all_crg_clk(HI_TRUE);
}

static hi_s32 vo_check_enable_user_div(hi_vo_dev dev)
{
    hi_s32 ret;
    hi_u32 dev_div;
    hi_u32 pre_div;
    vo_dev_info *dev_ctx = HI_NULL;

    dev_ctx = vo_get_dev_ctx(dev);
    if ((dev_ctx->vou_attr.intf_sync != HI_VO_OUT_USER) || (dev_ctx->user_config != HI_TRUE)) {
        return HI_SUCCESS;
    }

    dev_div = dev_ctx->vo_user_sync_info.dev_div;
    pre_div = dev_ctx->vo_user_sync_info.pre_div;
    ret = vo_check_dev_user_div(dev, dev_div, pre_div);
    if (ret != HI_SUCCESS) {
        vo_err_trace("vo dev %d user sync dev_div %d or pre_div %d is illegal, pls check the user sync info!\n",
            dev, dev_div, pre_div);
        return ret;
    }

    return HI_SUCCESS;
}

static hi_s32 vo_check_enable(hi_vo_dev dev)
{
    hi_s32 ret;
    vo_dev_info *dev_ctx = HI_NULL;

    dev_ctx = vo_get_dev_ctx(dev);
    if (dev_ctx->config != HI_TRUE) {
        vo_err_trace("vo device %d doesn't configured!\n", dev);
        return HI_ERR_VO_NOT_CFG;
    }

    if (dev_ctx->vo_enable == HI_TRUE) {
        vo_err_trace("vo device %d has enabled!\n", dev);
        return HI_ERR_VO_NOT_DISABLE;
    }

    ret = vo_check_enable_user_div(dev);
    if (ret != HI_SUCCESS) {
        vo_err_trace("vo%d's user sync info div is illegal!\n", dev);
        return ret;
    }

    return HI_SUCCESS;
}

static hi_void vo_set_dev_intf_param(hi_vo_dev dev)
{
    vo_dev_info *dev_ctx = HI_NULL;
    dev_ctx = vo_get_dev_ctx(dev);
    if (HI_VO_INTF_HDMI & dev_ctx->vou_attr.intf_type) {
        vo_drv_set_hdmi_param(dev, &dev_ctx->hdmi_param);
    }

    if (HI_VO_INTF_VGA & dev_ctx->vou_attr.intf_type) {
        vo_drv_set_vga_param(dev, &dev_ctx->vga_param);
    }

    if ((vo_drv_is_dev_support_rgb(dev) == HI_TRUE) &&
        (vo_drv_is_rgb_intf(dev_ctx->vou_attr.intf_type))) {
        vo_drv_set_rgb_param(dev, &dev_ctx->rgb_param);
    }
}

static hi_void vo_do_enable_dev(hi_vo_dev dev)
{
    vou_drv_set_dev_clk(dev);
    vo_drv_set_dev_clk_en_sel(dev);
    vo_drv_open(dev);
    vo_set_dev_intf_param(dev);
}

static hi_void vo_had_enable(hi_vo_dev dev)
{
    vo_dev_info *dev_ctx = HI_NULL;
    dev_ctx = vo_get_dev_ctx(dev);

    vo_drv_enable(dev);
    dev_ctx->vo_enable = HI_TRUE;
}

static hi_s32 vo_do_enable(hi_vo_dev dev)
{
    hi_s32 ret;
    vo_enable_clk();

    ret = vo_check_enable(dev);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    vo_do_enable_dev(dev);
    vo_had_enable(dev);
    return HI_SUCCESS;
}

hi_s32 vo_enable(hi_vo_dev dev)
{
    hi_s32 ret;
    vo_check_dev_id_return(dev);
    ret = vo_do_enable(dev);
    return ret;
}
#endif

#if VO_DESC("disable dev")
hi_void vo_reset_dev_intf_param(hi_vo_dev dev)
{
    vo_dev_info *dev_ctx = HI_NULL;

    dev_ctx = vo_get_dev_ctx(dev);
    vo_init_vga_param(&dev_ctx->vga_param);
    vo_init_hdmi_param(&dev_ctx->hdmi_param);
    vo_init_rgb_param(&dev_ctx->rgb_param);
}

hi_void vo_reset_dev_vars(hi_vo_dev dev)
{
    vo_reset_dev_intf_param(dev);
}

static hi_s32 vo_check_disable(hi_vo_dev dev)
{
    if (vo_is_dev_layer_enabled(dev)) {
        return HI_ERR_VO_NOT_DISABLE;
    }

    if (vo_is_dev_gfx_layer_enabled(dev)) {
        return HI_ERR_VO_NOT_DISABLE;
    }

    return HI_SUCCESS;
}

static hi_void vo_reset_vtth(hi_vo_dev dev)
{
    if (vo_is_phy_dev(dev)) {
        vo_drv_set_dev_default_vtth(dev);
    }
}

static hi_void vo_disable_clk(hi_void)
{
    hi_vo_dev dev;
    vo_dev_info *dev_ctx = HI_NULL;

    for (dev = 0; dev < HI_VO_MAX_PHYS_DEV_NUM; dev++) {
        dev_ctx = vo_get_dev_ctx(dev);
        if (dev_ctx == HI_NULL) {
            continue;
        }
        if ((dev_ctx->vo_enable) || (vou_drv_get_dev_enable(dev) == HI_TRUE)) {
            break;
        }
    }

    if (dev == HI_VO_MAX_PHYS_DEV_NUM) {
        vo_drv_set_all_crg_clk(HI_FALSE);
    }
}

static hi_s32 vo_do_disable(hi_vo_dev dev)
{
    hi_s32 ret;
    vo_dev_info *dev_ctx = HI_NULL;
    vo_drv_set_all_crg_clk(HI_TRUE);

    ret = vo_check_disable(dev);
    if (ret != HI_SUCCESS) {
        return ret;
    }
    if (vo_is_phy_dev(dev)) {
        vo_drv_close(dev);
    }

    vo_drv_disable(dev);

    dev_ctx = vo_get_dev_ctx(dev);
    dev_ctx->config = HI_FALSE;
    dev_ctx->vo_enable = HI_FALSE;
    dev_ctx->user_config = HI_FALSE;
    vo_reset_dev_vars(dev);

    vo_reset_vtth(dev);

    vo_disable_clk();

    return HI_SUCCESS;
}

hi_s32 vo_disable(hi_vo_dev dev)
{
    hi_s32 ret;

    vo_check_dev_id_return(dev);

    ret = vo_do_disable(dev);
    return ret;
}
#endif

#if VO_DESC("pub attr")

static hi_s32 vo_check_set_pub_attr(hi_vo_dev dev, const hi_vo_pub_attr *pub_attr)
{
    hi_s32 ret;
    vo_dev_info *dev_ctx = HI_NULL;

    dev_ctx = vo_get_dev_ctx(dev);
    if (dev_ctx->vo_enable == HI_TRUE) {
        vo_err_trace("vo%d doesn't disabled!\n", dev);
        return HI_ERR_VO_NOT_DISABLE;
    }

    ret = vou_drv_check_dev_pub_attr(dev, pub_attr);
    if (ret != HI_SUCCESS) {
        vo_err_trace("vo%d's pub attr is illegal!\n", dev);
        return ret;
    }
    return HI_SUCCESS;
}

static hi_void vo_set_phy_dev_pub_attr(hi_vo_dev dev)
{
    hi_u32 vtth;

    vtth = vo_drv_get_dev_vtth(dev);
    vo_drv_set_dev_vtth(dev, vtth);
}

static hi_void vo_set_disp_max_size(hi_vo_dev dev, const hi_vo_pub_attr *pub_attr)
{
    hi_u32 max_width = VO_DISP_1080_WIDTH;
    hi_u32 max_height = VO_DISP_1080_HEIGHT;
    vo_dev_info *dev_ctx = HI_NULL;
    hi_vo_intf_sync intf_sync = pub_attr->intf_sync;

    if (vo_is_typical_intf_sync(intf_sync)) {
        vo_get_intf_sync_size(intf_sync, &max_width, &max_height);
    } else if (vo_is_user_intf_sync(intf_sync)) {
        vo_get_intf_sync_size_user(&pub_attr->sync_info, &max_width, &max_height);
    }

    dev_ctx = vo_get_dev_ctx(dev);
    dev_ctx->max_width = max_width;
    dev_ctx->max_height = max_height;

    vou_drv_set_disp_max_size(dev, max_width, max_height);
}

static hi_s32 vo_do_set_pub_attr(hi_vo_dev dev, const hi_vo_pub_attr *pub_attr)
{
    hi_s32 ret;
    vo_dev_info *dev_ctx = HI_NULL;

    ret = vo_check_set_pub_attr(dev, pub_attr);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    vo_set_disp_max_size(dev, pub_attr);
    vo_drv_set_pub_attr(dev, pub_attr);

    dev_ctx = vo_get_dev_ctx(dev);
    memcpy(&dev_ctx->vou_attr, pub_attr, sizeof(hi_vo_pub_attr));
    dev_ctx->config = HI_TRUE;

    if (vo_is_phy_dev(dev)) {
        vo_set_phy_dev_pub_attr(dev);
    }

    return HI_SUCCESS;
}

hi_s32 vo_set_pub_attr(hi_vo_dev dev, const hi_vo_pub_attr *pub_attr)
{
    hi_s32 ret;

    vo_check_null_ptr_return(pub_attr);
    vo_check_dev_id_return(dev);

    ret = vo_do_set_pub_attr(dev, pub_attr);

    return ret;
}
#endif

#if VO_DESC("user sync info")
static hi_s32 vo_check_dev_user_dev_div(hi_vo_dev dev, hi_u32 dev_div)
{
    if ((dev_div < VO_MIN_DIV_MODE) || (dev_div > VO_MAX_DIV_MODE)) {
        vo_err_trace("vo(%d) dev div %u is illegal, it must be in [%u,%u].\n", dev, dev_div, VO_MIN_DIV_MODE,
            VO_MAX_DIV_MODE);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return vo_drv_check_intf_user_dev_div(dev, dev_div);
}

static hi_s32 vo_check_intf_user_pre_div(hi_vo_dev dev, hi_u32 pre_div)
{
    hi_vo_intf_type intf_type;
    vo_dev_info *dev_ctx = HI_NULL;

    dev_ctx = vo_get_dev_ctx(dev);
    intf_type = dev_ctx->vou_attr.intf_type;
    if (vo_drv_is_hdmi_intf(intf_type) != HI_TRUE) {
        if (pre_div != VO_INTF_NO_HDMI_PRE_DIV_MODE) {
            vo_err_trace("vo(%d) pre div %u is illegal, it must be %u when intf type is %u.\n", dev, pre_div,
                VO_INTF_NO_HDMI_PRE_DIV_MODE, intf_type);
            return HI_ERR_VO_ILLEGAL_PARAM;
        }
    }

    return HI_SUCCESS;
}

hi_s32 vo_check_dev_user_pre_div(hi_vo_dev dev, hi_u32 pre_div)
{
    if ((pre_div < VO_MIN_PRE_DIV_MODE) || (pre_div > VO_MAX_PRE_DIV_MODE)) {
        vo_err_trace("vo(%d) pre div %u is illegal, it must be in [%u,%u].\n", dev, pre_div,
            VO_MIN_PRE_DIV_MODE, VO_MAX_PRE_DIV_MODE);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return vo_check_intf_user_pre_div(dev, pre_div);
}

hi_s32 vo_check_dev_user_div(hi_vo_dev dev, hi_u32 dev_div, hi_u32 pre_div)
{
    hi_s32 ret;

    ret = vo_check_dev_user_dev_div(dev, dev_div);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    return vo_check_dev_user_pre_div(dev, pre_div);
}

static hi_s32 vo_check_dev_user_sync_info(hi_vo_dev dev, const hi_vo_user_sync_info *sync_info)
{
    hi_s32 ret;

    ret = vo_check_dev_user_div(dev, sync_info->dev_div, sync_info->pre_div);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    if (vo_check_bool_value(sync_info->clk_reverse_en) != HI_SUCCESS) {
        vo_err_trace("vo(%d) clk_reverse_en %d is illegal!\n", dev, sync_info->clk_reverse_en);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return vo_drv_check_dev_clkvalue(dev, sync_info);;
}
static hi_s32 vo_check_do_user_sync_info(hi_vo_dev dev)
{
    vo_dev_info *dev_ctx = HI_NULL;

    dev_ctx = vo_get_dev_ctx(dev);
    if (dev_ctx->config != HI_TRUE) {
        vo_err_trace("vo device %d doesn't configured!\n", dev);
        return HI_ERR_VO_NOT_CFG;
    }

    if (dev_ctx->vou_attr.intf_sync != HI_VO_OUT_USER) {
        vo_err_trace("vo device %d only support this in user sync.\n", dev);
        return HI_ERR_VO_NOT_SUPPORT;
    }

    return HI_SUCCESS;
}
static hi_s32 vo_check_set_user_sync_info(hi_vo_dev dev, const hi_vo_user_sync_info *sync_info)
{
    hi_s32 ret;
    vo_dev_info *dev_ctx = HI_NULL;

    ret = vo_check_do_user_sync_info(dev);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    dev_ctx = vo_get_dev_ctx(dev);
    if (dev_ctx->vo_enable == HI_TRUE) {
        vo_err_trace("vo device %d has enabled!\n", dev);
        return HI_ERR_VO_NOT_DISABLE;
    }

    ret = vo_check_dev_user_sync_info(dev, sync_info);
    if (ret != HI_SUCCESS) {
        vo_err_trace("VO%d's user sync info is illegal ret=0x%x!\n", dev, ret);
        return ret;
    }

    return HI_SUCCESS;
}

static hi_s32 vo_do_set_user_sync_info(hi_vo_dev dev, const hi_vo_user_sync_info *sync_info)
{
    hi_s32 ret;
    vo_dev_info *dev_ctx = HI_NULL;
    vo_drv_set_all_crg_clk(HI_TRUE);

    ret = vo_check_set_user_sync_info(dev, sync_info);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    vo_drv_set_dev_user_intf_sync_attr(dev, sync_info);

    vo_drv_set_dev_div(dev, sync_info->dev_div);

    vo_drv_set_hdmi_div(dev, sync_info->pre_div);

    vo_drv_set_clk_reverse(dev, sync_info->clk_reverse_en);

    dev_ctx = vo_get_dev_ctx(dev);
    memcpy(&dev_ctx->vo_user_sync_info, sync_info, sizeof(hi_vo_user_sync_info));
    dev_ctx->user_config = HI_TRUE;
    return HI_SUCCESS;
}

hi_s32 vo_set_user_sync_info(hi_vo_dev dev, const hi_vo_user_sync_info *sync_info)
{
    hi_s32 ret;

    vo_check_dev_id_return(dev);
    vo_check_null_ptr_return(sync_info);

    ret = vo_do_set_user_sync_info(dev, sync_info);

    return ret;
}
#endif
