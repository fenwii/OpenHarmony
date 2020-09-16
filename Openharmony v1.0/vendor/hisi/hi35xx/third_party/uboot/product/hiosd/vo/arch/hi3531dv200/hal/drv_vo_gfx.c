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

#include "drv_vo_gfx.h"
#include "hi_common_vo.h"

#include "vo.h"
#include "drv_vo.h"

#if VO_DESC("UBOOT_VO")
hi_s32 vo_drv_check_gfx_id(hi_vo_layer gfx_layer)
{
    if (gfx_layer == HI_VO_LAYER_G2) {
        return HI_ERR_VO_INVALID_LAYER_ID;
    }

    return HI_SUCCESS;
}

#define VO_GFX_DISP_RECT_W_MAX_OF_GFXX 3840
#define VO_GFX_DISP_RECT_H_MAX_OF_GFXX 3840
#define VO_GFX_DISP_RECT_W_MAX_OF_GFX1 1920
#define VO_GFX_DISP_RECT_H_MAX_OF_GFX1 1920
#define VO_GFX_DISP_RECT_W_MAX_OF_GFX3 720
#define VO_GFX_DISP_RECT_H_MAX_OF_GFX3 720

#if VO_DESC("vo gfx")
hi_s32 vou_drv_get_gfx_bind_dev(hi_vo_layer layer)
{
    hi_vo_dev bind_dev;
    if (layer == HAL_DISP_LAYER_GFX0) {
        bind_dev = VO_DEV_DHD0;
    } else if (layer == HAL_DISP_LAYER_GFX1) {
        bind_dev = VO_DEV_DHD1;
    } else if (layer == HAL_DISP_LAYER_GFX2) {
        bind_dev = VO_DEV_DHD0;
    } else if (layer == HAL_DISP_LAYER_GFX3) {
        bind_dev = VO_DEV_DSD0;
    } else {
        bind_dev = HI_INVALID_DEV;
    }
    return bind_dev;
}
hi_s32 vo_drv_get_hal_gfx_layer(hi_vo_layer gfx_layer, hal_disp_layer *hal_layer)
{
    switch (gfx_layer) {
        case HI_VO_LAYER_G0:
            *hal_layer = HAL_DISP_LAYER_GFX0;
            break;

        case HI_VO_LAYER_G1:
            *hal_layer = HAL_DISP_LAYER_GFX1;
            break;

        case HI_VO_LAYER_G2:
            *hal_layer = HAL_DISP_LAYER_GFX2;
            break;

        case HI_VO_LAYER_G3:
            *hal_layer = HAL_DISP_LAYER_GFX3;
            break;

        default:
            return HI_ERR_VO_INVALID_LAYER_ID;
    }

    return HI_SUCCESS;
}

#endif

#if VO_DESC("gfx")

static hi_void vo_drv_get_gfx_attr_max_rect(hi_vo_layer layer, hi_u32 *width, hi_u32 *height)
{
    *width = VO_GFX_DISP_RECT_W_MAX_OF_GFXX;
    *height = VO_GFX_DISP_RECT_H_MAX_OF_GFXX;

    if (layer == VO_HAL_LAYER_G3) {
        *width = VO_GFX_DISP_RECT_W_MAX_OF_GFX3;
        *height = VO_GFX_DISP_RECT_H_MAX_OF_GFX3;
    }
}

hi_s32 vo_drv_check_gfx_attr_display_rect(hi_vo_layer layer, const hi_rect *rect)
{
    hi_u32 max_width;
    hi_u32 max_height;

    if ((layer >= VO_HAL_LAYER_G0) && (layer <= VO_HAL_LAYER_G3)) {
        vo_drv_get_gfx_attr_max_rect(layer, &max_width, &max_height);
        if ((rect->width > max_width) || (rect->height > max_height)) {
            vo_err_trace("gfx layer (%d) disp rect width(%d) height(%d) can't be larger than %dx%d!\n",
                layer, rect->width, rect->height,
                VO_GFX_DISP_RECT_W_MAX_OF_GFX3, VO_GFX_DISP_RECT_H_MAX_OF_GFX3);
            return HI_ERR_VO_ILLEGAL_PARAM;
        }
    } else {
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}
#endif
#endif /* #if VO_DESC("UBOOT_VO") */