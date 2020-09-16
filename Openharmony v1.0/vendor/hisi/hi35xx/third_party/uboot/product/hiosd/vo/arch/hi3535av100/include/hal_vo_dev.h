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

#ifndef __HAL_VO_DEV_H__
#define __HAL_VO_DEV_H__

#include "hal_vo_dev_comm.h"
#include "hi_inner_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")

hi_void hal_sys_set_outstanding(hi_void);

#if VO_DESC("dev intf")
#define VO_CVBS_DATE_PAL 0x628412dc
hi_void vo_hal_intf_set_date_cvbs_gain(hi_u32 data);
hi_void vo_hal_intf_set_sync_inv(hi_vo_intf_type intf_type, hal_disp_syncinv *inv);
hi_void vo_hal_intf_set_mux_sel_hd(hi_vo_dev dev, hi_vo_intf_type intf);
hi_void vo_hal_intf_set_csc_enable(hi_vo_intf_type intf, hi_bool enable);
hi_void vo_hal_intf_set_csc_dc_coef(hi_vo_intf_type intf, vdp_csc_dc_coef *csc_dc_coef);
hi_void vo_hal_intf_set_csc_coef(hi_vo_intf_type intf, vdp_csc_coef *csc_coef);
#endif

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of __HAL_VO_DEV_H__ */
