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

#ifndef __HAL_VO_COMM_H__
#define __HAL_VO_COMM_H__

#include "hal_vo_def.h"
#include "hi_inner_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")

#define IO_ADDRESS(x) (x)

#ifdef HI_DEBUG
#define VO_HAL_CHECK_DEBUG /* vo hal check debug, debug only */
#endif
/* 4bytes */
#define REG_BYTES 4

#if VO_DESC("hal pub")
hi_void hal_vou_init(hi_void);
hi_void hal_write_reg(hi_u32 *address, hi_u32 value);
hi_u32 hal_read_reg(const hi_u32 *address);
#endif

#if VO_DESC("hal check")
hi_bool vo_hal_is_phy_dev(hi_vo_dev dev);
hi_bool vo_hal_is_video_layer(hal_disp_layer layer);
hi_bool vo_hal_is_gfx_layer(hal_disp_layer layer);
hi_bool vo_hal_is_video_gfx_layer(hal_disp_layer layer);
#endif

#ifdef VO_HAL_CHECK_DEBUG

#define vo_hal_check_phy_dev_return(dev)         \
    do {                                                    \
        if (vo_hal_is_phy_dev(dev) != HI_TRUE) {   \
            HI_PRINT("err dev in %s: L%d\n", __FUNCTION__, __LINE__); \
            return;          \
        }                     \
    } while (0)

#define vo_hal_check_video_layer_return(layer)         \
    do {                                                    \
        if (vo_hal_is_video_layer(layer) != HI_TRUE) {   \
            HI_PRINT("err layer in %s: L%d\n", __FUNCTION__, __LINE__); \
            return;          \
        }                     \
    } while (0)

#define vo_hal_check_gfx_layer_return(layer)         \
    do {                                                    \
        if (vo_hal_is_gfx_layer(layer) != HI_TRUE) {   \
            HI_PRINT("err layer in %s: L%d\n", __FUNCTION__, __LINE__); \
            return;          \
        }                     \
    } while (0)

#define vo_hal_check_video_gfx_layer_return(layer)         \
    do {                                                    \
        if (vo_hal_is_video_gfx_layer(layer) != HI_TRUE) {   \
            HI_PRINT("err layer in %s: L%d\n", __FUNCTION__, __LINE__); \
            return;          \
        }                     \
    } while (0)

#else

#define vo_hal_check_phy_dev_return(dev)
#define vo_hal_check_video_layer_return(layer)
#define vo_hal_check_gfx_layer_return(layer)
#define vo_hal_check_video_gfx_layer_return(layer)

#endif
#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of __HAL_VO_COMM_H__ */
