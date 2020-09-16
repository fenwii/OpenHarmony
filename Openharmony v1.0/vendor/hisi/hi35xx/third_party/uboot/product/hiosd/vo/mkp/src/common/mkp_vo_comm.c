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

#include "mkp_vo_comm.h"
#include "vo.h"
#include "hi_common_vo.h"
#include "hi_common_video.h"

#include "mkp_vo.h"
#include "sys_ext.h"

#include "hi_board.h"
#include "drv_vo.h"

#if VO_DESC("dev check")

hi_s32 vo_def_check_dev_id(hi_vo_dev dev)
{
    if ((dev < 0) || (dev >= HI_VO_MAX_PHYS_DEV_NUM)) {
        return HI_ERR_VO_INVALID_DEV_ID;
    }

    return HI_SUCCESS;
}

hi_s32 vo_def_check_layer_id(hi_vo_layer layer)
{
    if ((layer < 0) || (layer >= HI_VO_MAX_LAYER_NUM)) {
        return HI_ERR_VO_INVALID_LAYER_ID;
    }

    return HI_SUCCESS;
}

hi_bool vo_def_is_gfx_layer_id(hi_vo_layer layer)
{
    if ((layer >= HI_VO_LAYER_G0) && (layer < VO_LAYER_BUTT)) {
        return HI_TRUE;
    }

    return HI_FALSE;
}

#endif

#if VO_DESC("check attr pub")

hi_s32 vo_check_bool_value(hi_bool bool_val)
{
    if ((bool_val != HI_TRUE) && (bool_val != HI_FALSE)) {
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

hi_s32 vo_check_rect_align(const hi_rect *rect)
{
    if ((rect->x % VO_RECT_ALIGN) || (rect->y % VO_RECT_ALIGN) ||
        (rect->width % VO_RECT_ALIGN) || (rect->height % VO_RECT_ALIGN)) {
        return HI_ERR_VO_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}
#endif

#if VO_DESC("check dev pub")

hi_bool vo_is_phy_dev(hi_vo_dev dev)
{
    return HI_TRUE;
}

hi_bool vo_is_typical_intf_sync(hi_vo_intf_sync intf_sync)
{
    if ((intf_sync < HI_VO_OUT_BUTT) && (intf_sync != HI_VO_OUT_USER)) {
        return HI_TRUE;
    }

    return HI_FALSE;
}

hi_bool vo_is_user_intf_sync(hi_vo_intf_sync intf_sync)
{
    if (intf_sync == HI_VO_OUT_USER) {
        return HI_TRUE;
    }

    return HI_FALSE;
}

#endif
