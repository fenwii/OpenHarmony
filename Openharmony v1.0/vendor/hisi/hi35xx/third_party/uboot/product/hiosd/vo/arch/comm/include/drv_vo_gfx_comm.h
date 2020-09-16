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

#ifndef __DRV_GFX_COMM_H__
#define __DRV_GFX_COMM_H__

#include "hi_type.h"
#include "hi_common_vo.h"
#include "mkp_vo.h"
#include "hi_inner_vo.h"
#include "hal_vo_def.h"
#include "drv_vo_coef_comm.h"

#if VO_DESC("UBOOT_VO")
#define GFX_CSC_SCALE    0xa
#define GFX_CSC_CLIP_MIN 0x0
#define GFX_CSC_CLIP_MAX 0x3ff
hi_s32 vo_drv_set_gfx_layer_csc(hi_vo_layer gfx_layer, hi_vo_csc *csc, csc_coef_param *csc_param);
typedef struct {
    hi_bool opened;

    hi_vo_csc gfx_csc;
    csc_coef_param csc_param;
} vo_gfxlayer_context;

hi_s32 graphic_drv_set_csc_coef(hal_disp_layer gfx_layer, hi_vo_csc *gfx_csc, csc_coef_param *csc_param);
hi_void gfx_drv_init_default_csc(hi_vo_layer layer, hi_vo_csc *csc);
hi_void gfx_drv_init_default_csc_param(hi_vo_layer layer, csc_coef_param *csc_param);
#endif /* #if VO_DESC("UBOOT_VO") */

#endif
