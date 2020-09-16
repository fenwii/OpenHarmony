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

#ifndef __MKP_VO_DEV_H__
#define __MKP_VO_DEV_H__

#include "hi_common_vo.h"
#include "drv_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#define VO_DEV_TIME_REF_STEP        2

#define VO_DEV_MAX_FRAME_RATE       240

typedef struct {
    hi_vo_intf_sync intf_sync;
    hi_u32 width;
    hi_u32 height;
} vo_intf_sync_info;

typedef struct {
    hi_bool vo_enable;
    hi_bool config;
    hi_vo_pub_attr vou_attr;

    hi_u32 max_width;
    hi_u32 max_height;

    hi_bool user_config;
    hi_vo_user_sync_info vo_user_sync_info;
    hi_vo_vga_param vga_param;
    hi_vo_hdmi_param hdmi_param;
    hi_vo_rgb_param rgb_param;
    hi_vo_bt_param bt_param;
} vo_dev_info;

hi_void vo_init_dev_info(hi_void);
vo_dev_info *vo_get_dev_ctx(hi_vo_dev vo_dev);
hi_s32 vo_init_dev_ctx(hi_vo_dev dev);

hi_bool vo_is_dev_enabled(hi_vo_dev dev);
hi_void vo_get_dev_max_size(hi_vo_dev dev, hi_size *dev_size);
hi_void vo_get_intf_sync_size(hi_vo_intf_sync intf_sync, hi_u32 *width, hi_u32 *height);
hi_void vo_get_dev_max_size(hi_vo_dev dev, hi_size *dev_size);

hi_s32 vo_enable(hi_vo_dev dev);
hi_s32 vo_disable(hi_vo_dev dev);

hi_s32 vo_set_pub_attr(hi_vo_dev dev, const hi_vo_pub_attr *pub_attr);
hi_s32 vo_get_pub_attr(hi_vo_dev dev, hi_vo_pub_attr *pub_attr);

hi_s32 vo_check_dev_user_div(hi_vo_dev dev, hi_u32 dev_div, hi_u32 pre_div);
hi_s32 vo_set_user_sync_info(hi_vo_dev dev, const hi_vo_user_sync_info *sync_info);

hi_u32 vo_dev_get_bg_color(hi_vo_dev dev);
hi_void vo_dev_set_bg_color(hi_vo_dev dev, hi_u32 bg_color);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of #ifndef __MKP_VO_DEV_H__ */
