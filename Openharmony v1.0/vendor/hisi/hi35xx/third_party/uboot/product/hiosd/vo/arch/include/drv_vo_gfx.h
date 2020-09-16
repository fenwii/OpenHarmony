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

#ifndef __DRV_GFX_H__
#define __DRV_GFX_H__

#include "hi_type.h"
#include "hi_common_vo.h"
#include "mkp_vo.h"
#include "drv_vo_gfx_comm.h"

hi_s32 vo_drv_check_gfx_id(hi_vo_layer gfx_layer);
hi_s32 vo_drv_get_hal_gfx_layer(hi_vo_layer gfx_layer, hal_disp_layer *hal_layer);
hi_s32 vou_drv_get_gfx_bind_dev(hi_vo_layer layer);

hi_s32 graphic_drv_init(hi_void);
hi_s32 vo_drv_check_gfx_layer_id(hi_vo_layer layer);
hi_s32 vo_drv_check_gfx_attr_display_rect(hi_vo_layer layer, const hi_rect *rect);

hi_s32 vo_drv_gfx_convert_gfx_attr(const hi_vo_gfx_attr *gfx_attr_in, hi_vo_gfx_attr *gfx_attr_out);
hi_void vo_drv_gfx_open(hi_vo_layer gfx_id, const hi_vo_gfx_attr *gfx_attr);
hi_void vo_drv_gfx_close(hi_vo_layer layer_id);
#endif
