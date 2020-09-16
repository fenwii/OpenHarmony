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

#ifndef __MKP_VO_H__
#define __MKP_VO_H__

#include "hi_common.h"
#include "hi_common_video.h"
#include "hi_common_vo.h"
#include "hi_inner_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#define VO_LAYER_BUTT HI_VO_MAX_PHYS_LAYER_NUM

#define vo_err_trace(fmt, ...)                                                                            \
    HI_ERR_TRACE(HI_ID_VO, "[Func]:%s [Line]:%d [Info]:" fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__);

#define vo_warn_trace(fmt, ...)                                                                            \
    HI_WARN_TRACE(HI_ID_VO, "[Func]:%s [Line]:%d [Info]:" fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__);

hi_s32 vo_def_check_dev_id(hi_vo_dev dev);
hi_s32 vo_def_check_layer_id(hi_vo_layer layer);
hi_bool vo_def_is_gfx_layer_id(hi_vo_layer layer);

#define vo_check_null_ptr_return(ptr)                              \
    do {                                                           \
        if ((ptr) == HI_NULL) {                                    \
            vo_err_trace("null ptr!\n");                           \
            return HI_ERR_VO_NULL_PTR;                             \
        }                                                          \
    } while (0)

/* vo device relative */
#define vo_check_dev_id_return(dev)                         \
    do {                                                    \
        if (vo_drv_check_dev_id(dev) != HI_SUCCESS) {       \
            vo_err_trace("dev %d invalid!\n", dev);         \
            return HI_ERR_VO_INVALID_DEV_ID;                \
        }                                                   \
    } while (0)

/* vo video relative */
#define vo_check_layer_id_return(layer)                   \
    do {                                                  \
        if (vo_drv_check_layer_id(layer) != HI_SUCCESS) { \
            vo_err_trace("layer %d invalid!\n", layer);   \
            return HI_ERR_VO_INVALID_LAYER_ID;            \
        }                                                 \
    } while (0)

#define vo_check_gfx_id_return(gfx_layer)                       \
    do {                                                        \
        if (vo_check_gfx_id(gfx_layer) != HI_SUCCESS) {         \
            vo_err_trace("gfx layer %d invalid!\n", gfx_layer); \
            return HI_ERR_VO_INVALID_LAYER_ID;                  \
        }                                                       \
    } while (0)

#define vo_check_gfx_layer_return(layer)                                     \
    do {                                                                     \
        if (vo_def_is_gfx_layer_id(layer)) {                                 \
            vo_err_trace("vo layer %d is gfx layer, not support!\n", layer); \
            return HI_ERR_VO_NOT_SUPPORT;                                    \
        }                                                                    \
    } while (0)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of #ifndef __MKP_VO_H__ */
