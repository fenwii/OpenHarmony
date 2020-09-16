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

#ifndef __MKP_VO_VIDEO_H__
#define __MKP_VO_VIDEO_H__

#include "hi_common_vo.h"
#include "hi_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#define VO_LAYER_DISPLAY_MAX_FRAME_RATE  240 /* max display frame rate */

#define VO_LAYER_PLAY_TOLERATION_UNIT   1000

hi_bool vo_is_multi_layer(hi_vo_layer layer);
hi_bool vo_is_single_layer(hi_vo_layer layer);
hi_bool vo_is_layer_enabled(hi_vo_layer layer);
hi_bool vo_is_layer_configured(hi_vo_layer layer);
hi_bool vo_is_layer_bypass(hi_vo_layer layer);
hi_bool vo_is_layer_cluster_mode_enabled(hi_vo_layer layer);
hi_vo_dev vo_get_video_layer_bind_dev(hi_vo_layer layer);
hi_s32 vo_check_layer_binded_dev(hi_vo_layer layer, hi_vo_dev dev);
hi_bool vo_is_layer_binded_dev(hi_vo_layer layer);
hi_bool vo_is_dev_layer_enabled(hi_vo_dev dev);
hi_bool vo_is_layer_chn_enabled(hi_vo_layer layer);
hi_void vo_exit_layer(hi_void);

hi_s32 vo_init_layer_ctx(hi_vo_layer layer);

hi_void vo_init_layer_info(hi_void);
hi_void vo_init_layer_resource(hi_void);
hi_void vo_deinit_layer_info(hi_void);

hi_s32 vo_enable_video_layer(hi_vo_layer layer, const hi_vo_video_layer_attr *video_attr);
hi_s32 vo_disable_video_layer(hi_vo_layer layer);

hi_s32 vo_set_video_layer_attr(hi_vo_layer layer, const hi_vo_video_layer_attr *video_attr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of #ifndef __MKP_VO_VIDEO_H__ */

