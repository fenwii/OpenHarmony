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

#include "mkp_vo_gfx.h"
#include "hi_common_vo.h"
#include "mkp_vo_gfx.h"
#include "mkp_vo_dev.h"
#include "mkp_vo_video.h"
#include "mkp_vo_comm.h"
#include "drv_vo_gfx.h"
#include "vo.h"
#include "drv_vo.h"
#include "common.h"

#if VO_DESC("public api")
vo_gfxlayer_context g_vo_gfx_layer_ctx[HI_VO_MAX_GFX_LAYER_NUM];

vo_gfxlayer_context *vo_get_gfx_layer_ctx(hi_vo_layer vo_layer)
{
    return &(g_vo_gfx_layer_ctx[vo_layer - HI_VO_LAYER_G0]);
}

hi_void vo_init_gfx(hi_void)
{
    hi_vo_layer gfx_layer;
    vo_gfxlayer_context *gfx_layer_ctx = HI_NULL;

    for (gfx_layer = HI_VO_LAYER_G0; gfx_layer < HI_VO_LAYER_G0 + HI_VO_MAX_GFX_LAYER_NUM; gfx_layer++) {
        gfx_layer_ctx = vo_get_gfx_layer_ctx(gfx_layer);

        gfx_layer_ctx->gfx_csc.csc_matrix = HI_VO_CSC_MATRIX_RGBFULL_TO_BT601FULL;
        gfx_layer_ctx->gfx_csc.luma = VO_CSC_DEF_VAL;
        gfx_layer_ctx->gfx_csc.contrast = VO_CSC_DEF_VAL;
        gfx_layer_ctx->gfx_csc.hue = VO_CSC_DEF_VAL;
        gfx_layer_ctx->gfx_csc.saturation = VO_CSC_DEF_VAL;
        gfx_layer_ctx->gfx_csc.ex_csc_en = HI_FALSE;
        gfx_layer_ctx->csc_param.csc_scale2p = GFX_CSC_SCALE;
        gfx_layer_ctx->csc_param.csc_clip_min = GFX_CSC_CLIP_MIN;
        gfx_layer_ctx->csc_param.csc_clip_max = GFX_CSC_CLIP_MAX;
    }
}

hi_vo_dev vo_get_gfx_bind_dev(hi_vo_layer layer)
{
    return vou_drv_get_gfx_bind_dev(layer);
}

hi_s32 vo_check_gfx_id(hi_vo_layer gfx_layer)
{
    if (vo_def_is_gfx_layer_id(gfx_layer) != HI_TRUE) {
        return HI_ERR_VO_INVALID_LAYER_ID;
    }

    return vo_drv_check_gfx_id(gfx_layer);
}
#endif

#if VO_DESC("gfx attr")
static hi_s32 vo_check_gfx_attr_display_rect(hi_vo_dev dev, hi_vo_layer layer, const hi_rect *rect)
{
    hi_size dev_size;

    vo_get_dev_max_size(dev, &dev_size);
    if ((rect->x < 0) || (rect->y < 0) || (rect->width < VO_RESO_MIN_WDT) || (rect->height < VO_RESO_MIN_HGT) ||
        ((rect->width + rect->x) > dev_size.width) || ((rect->height + rect->y) > dev_size.height)) {
        vo_err_trace("layer(%d) display rect(%d, %d, %d,%d) is illegal, should between (%d, %d) and (%d, %d)\n",
            layer, rect->x, rect->y, rect->width, rect->height,
            VO_RESO_MIN_WDT, VO_RESO_MIN_HGT, dev_size.width, dev_size.height);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    if (vo_check_rect_align(rect) != HI_SUCCESS) {
        vo_err_trace("layer(%d), display rect (%d, %d, %d, %d) dosen't aligned by 2 pixels!\n",
            layer, rect->x, rect->y, rect->width, rect->height);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return vo_drv_check_gfx_attr_display_rect(layer, rect);
}

static hi_s32 vo_check_gfx_attr_stride(hi_vo_layer layer, const hi_vo_gfx_attr *attr)
{
    if (((attr->stride % VO_RECT_ALIGN) != 0)) {
        vo_err_trace("layer%d's stride %d is illegal!\n", layer, attr->stride);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    if (((attr->address % VO_ADDR_ALIGN) != 0)) {
        vo_err_trace("layer%d's addr 0x%lx is illegal, it should be %d bytes align!\n", layer, attr->address,
            VO_ADDR_ALIGN);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

static hi_s32 vo_check_gfx_attr_type(hi_vo_layer layer, const hi_vo_gfx_attr *attr)
{
    if ((attr->type != HI_VO_GFX_TYPE_ARGB1555) &&
        (attr->type != HI_VO_GFX_TYPE_BMP1555)) {
        vo_err_trace("layer%d's picture type %d is illegal!\n", layer, attr->type);
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

static hi_s32 vo_check_gfx_attr(hi_vo_dev dev, hi_vo_layer layer, const hi_vo_gfx_attr *attr)
{
    hi_s32 ret;
    ret = vo_check_gfx_attr_display_rect(dev, layer, &attr->display_rect);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    ret = vo_check_gfx_attr_stride(layer, attr);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    return vo_check_gfx_attr_type(layer, attr);
}

static hi_s32 vo_check_set_gfx_attr(hi_vo_layer layer, const hi_vo_gfx_attr *attr)
{
    hi_vo_dev dev;

    dev = vo_get_gfx_bind_dev(layer);
    if (vo_check_layer_binded_dev(layer, dev) != HI_SUCCESS) {
        vo_err_trace("vo layer %d can't set layer attr when the layer has not been binded!\n", layer);
        return HI_ERR_VO_NOT_BINDED;
    }

    if (vo_is_dev_enabled(dev) != HI_TRUE) {
        vo_err_trace("vo gfx layer %d bind dev %d doesn't enable!\n", layer, dev);
        return HI_ERR_VO_NOT_ENABLE;
    }

    return vo_check_gfx_attr(dev, layer, attr);
}

static hi_void vo_set_gfx_attr_in_drv(hi_vo_layer layer, const hi_vo_gfx_attr *attr)
{
    hal_disp_layer gfx_layer = HAL_DISP_LAYER_GFX0;
    vo_gfxlayer_context *gfx_layer_ctx = HI_NULL;

    gfx_layer_ctx = vo_get_gfx_layer_ctx(layer);
    vo_drv_get_hal_gfx_layer(layer, &gfx_layer);
    vo_drv_set_gfx_layer_csc(gfx_layer, &gfx_layer_ctx->gfx_csc, &gfx_layer_ctx->csc_param);
    vou_drv_layer_csc_enable(gfx_layer, HI_TRUE);
}

static hi_s32 vo_do_set_gfx_attr(hi_vo_layer layer, const hi_vo_gfx_attr *attr)
{
    hi_s32 ret;

    ret = vo_check_set_gfx_attr(layer, attr);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    vo_set_gfx_attr_in_drv(layer, attr);

    return HI_SUCCESS;
}

hi_s32 vo_set_gfx_attr(hi_vo_layer layer, const hi_vo_gfx_attr *attr)
{
    hi_s32 ret;

    vo_check_null_ptr_return(attr);
    vo_check_gfx_id_return(layer);

    ret = vo_do_set_gfx_attr(layer, attr);
    return ret;
}

#endif

#if VO_DESC("enable gfx")

hi_bool vo_is_gfx_layer_enabled(hi_vo_layer layer)
{
    vo_gfxlayer_context *ctx = HI_NULL;

    ctx = vo_get_gfx_layer_ctx(layer);
    return ctx->opened;
}

hi_bool vo_is_dev_gfx_layer_enabled(hi_vo_dev dev)
{
    hi_vo_layer gfx_layer;

    gfx_layer = vo_drv_get_gfx_layer(dev);
    if (vo_is_gfx_layer_enabled(gfx_layer) == HI_TRUE) {
        vo_err_trace("vo %d's gfx layer %d doesn't disable!\n", dev, gfx_layer);
        return HI_TRUE;
    }

    return HI_FALSE;
}

static hi_s32 vo_check_enable_gfx_layer(hi_vo_layer layer)
{
    hi_vo_dev dev;

    dev = vo_get_gfx_bind_dev(layer);
    if (vo_check_layer_binded_dev(layer, dev) != HI_SUCCESS) {
        vo_err_trace("layer(%d) is not bind any dev!\n", layer);
        return HI_ERR_VO_NOT_BINDED;
    }

    if (vo_is_dev_enabled(dev) != HI_TRUE) {
        vo_err_trace("vo device %d doesn't enable!\n", dev);
        return HI_ERR_VO_NOT_ENABLE;
    }

    return HI_SUCCESS;
}

static hi_s32 vo_do_enable_gfx_layer(hi_vo_layer layer, const hi_vo_gfx_attr *gfx_attr)
{
    hi_s32 ret;
    vo_gfxlayer_context *gfx_ctx = HI_NULL;

    gfx_ctx = vo_get_gfx_layer_ctx(layer);
    if (gfx_ctx->opened == HI_TRUE) {
        vo_warn_trace("video layer%d has been enabled!\n", layer);
        return HI_SUCCESS;
    }

    ret = vo_check_enable_gfx_layer(layer);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    gfx_ctx->opened = HI_TRUE;

    vo_drv_gfx_open(layer, gfx_attr);

    return HI_SUCCESS;
}

hi_s32 vo_enable_gfx_layer(hi_vo_layer layer, const hi_vo_gfx_attr *gfx_attr)
{
    hi_s32 ret;
    vo_check_gfx_id_return(layer);
    ret = vo_do_enable_gfx_layer(layer, gfx_attr);
    return ret;
}

#endif

#if VO_DESC("disable gfx")
static hi_s32 vo_check_disable_gfx_layer(hi_vo_layer layer)
{
    hi_vo_dev dev;

    dev = vo_get_gfx_bind_dev(layer);
    if (vo_check_layer_binded_dev(layer, dev) != HI_SUCCESS) {
        vo_err_trace("layer(%d) is not bind any dev!\n", layer);
        return HI_ERR_VO_NOT_BINDED;
    }
    return HI_SUCCESS;
}

static hi_s32 vo_do_disable_gfx_layer(hi_vo_layer layer)
{
    hi_s32 ret;
    vo_gfxlayer_context *gfx_layer_ctx = HI_NULL;
    ret = vo_check_disable_gfx_layer(layer);
    if (ret != HI_SUCCESS) {
        return ret;
    }
    gfx_layer_ctx = vo_get_gfx_layer_ctx(layer);
    if (gfx_layer_ctx->opened == HI_FALSE) {
        return HI_SUCCESS;
    }
    vo_drv_gfx_close(layer);
    /* sleep: msleep(40); */
    gfx_layer_ctx->opened = HI_FALSE;

    return HI_SUCCESS;
}

hi_s32 vo_disable_gfx_layer(hi_vo_layer layer_id)
{
    hi_s32 ret;

    vo_check_gfx_id_return(layer_id);
    ret = vo_do_disable_gfx_layer(layer_id);

    return ret;
}
#endif
