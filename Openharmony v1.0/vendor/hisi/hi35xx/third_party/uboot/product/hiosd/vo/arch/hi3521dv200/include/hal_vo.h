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

#ifndef __HAL_VO_H__
#define __HAL_VO_H__

#include "hal_vo_reg.h"
#include "hal_vo_def.h"
#include "hi_inner_vo.h"
#include "hal_vo_comm.h"
#include "hal_vo_dev.h"
#include "hal_vo_video.h"
#include "hal_vo_layer_comm.h"
#include "hal_vo_gfx_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */
#if VO_DESC("UBOOT_VO")

#if VO_DESC("hal pub")
volatile reg_vdp_regs *vo_hal_get_reg(hi_void);
hi_void vo_hal_set_reg(volatile reg_vdp_regs *reg);
#endif

#if VO_DESC("get abs addr")
hi_ulong vou_get_abs_addr(hal_disp_layer layer, hi_ulong reg);
hi_ulong vou_get_chn_abs_addr(hi_vo_dev dev, hi_ulong reg);
hi_ulong vou_get_vid_abs_addr(hal_disp_layer layer, hi_ulong reg);
hi_ulong vou_get_gfx_abs_addr(hal_disp_layer layer, hi_ulong reg);
#endif

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of __HAL_VO_H__ */
