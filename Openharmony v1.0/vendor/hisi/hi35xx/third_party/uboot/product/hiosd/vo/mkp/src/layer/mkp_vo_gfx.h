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

#ifndef __MKP_VO_GFX_H__
#define __MKP_VO_GFX_H__

#include "hi_type.h"
#include "hi_common.h"
#include "hi_common_vo.h"
#include "drv_vo_gfx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

hi_void vo_init_gfx(hi_void);
hi_bool vo_is_dev_gfx_layer_enabled(hi_vo_dev dev);
hi_s32 vo_set_gfx_attr(hi_vo_layer layer, const hi_vo_gfx_attr *attr);
hi_s32 vo_enable_gfx_layer(hi_vo_layer layer, const hi_vo_gfx_attr *gfx_attr);
hi_s32 vo_disable_gfx_layer(hi_vo_layer layer_id);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of #ifndef __MKP_VO_GFX_H__ */
