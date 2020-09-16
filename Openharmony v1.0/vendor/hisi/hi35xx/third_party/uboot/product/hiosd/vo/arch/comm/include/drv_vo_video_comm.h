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

#ifndef __DRV_VO_VIDEO_COMM_H__
#define __DRV_VO_VIDEO_COMM_H__

#include "drv_vo_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")

#if VO_DESC("layer cfg")
hi_void vou_drv_layer_enable(hi_vo_layer layer, hi_bool enable);
hi_void vo_drv_disable_layer(hi_vo_layer layer);
hi_void vou_drv_set_layer_reg_up(hi_vo_layer layer);
hi_void vou_drv_set_layer_data_fmt(hi_vo_layer layer, vou_layer_pixerl_format data_fmt);
#endif

#if VO_DESC("layer")
hi_void vou_drv_init_default_csc(hi_vo_layer layer);
hi_void vou_drv_init_default_csc_param(hi_vo_layer layer);
hi_void vou_drv_set_default_csc(hi_vo_layer layer, hi_vo_csc *csc);
hi_s32 vou_drv_get_video_layer_bind_dev(hi_vo_layer layer);
hi_void vo_drv_set_layer_attr(hi_vo_layer layer, const hi_vo_video_layer_attr *vo_layer_attr);
hi_void vou_drv_get_default_csc(hi_vo_layer layer, hi_vo_csc *csc);

#endif

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* end of #ifdef __cplusplus */
#endif

#endif /* end of __DRV_VO_COMM_LAYER_H__ */
