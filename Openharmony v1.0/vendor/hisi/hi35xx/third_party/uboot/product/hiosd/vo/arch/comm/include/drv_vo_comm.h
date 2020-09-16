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

#ifndef __DRV_VO_COMM_H__
#define __DRV_VO_COMM_H__

#include "hi_common_vo.h"
#include "hi_common_video.h"
#include "mkp_vo.h"
#include "drv_vo_coef_comm.h"
#include "hal_vo_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")

typedef enum {
    /* for video surface interface */
    VOU_LAYER_PIXERL_FORMAT_SP_YCBCR_400 = 0x1,
    VOU_LAYER_PIXERL_FORMAT_SP_YCBCR_420 = 0x2,
    VOU_LAYER_PIXERL_FORMAT_SP_YCBCR_422 = 0x3,
    VOU_LAYER_PIXERL_FORMAT_BUTT
} vou_layer_pixerl_format;

/* vou interrupt mask type */
typedef enum {
    VO_INTMSK_NONE = 0,
    VO_INTMSK_DHD0_VTTHD1 = 0x1,
    VO_INTMSK_DHD0_VTTHD2 = 0x2,
    VO_INTMSK_DHD0_VTTHD3 = 0x4,
    VO_INTMSK_DHD0_UFINT = 0x8,

    VO_INTMSK_DHD1_VTTHD1 = 0x10,
    VO_INTMSK_DHD1_VTTHD2 = 0x20,
    VO_INTMSK_DHD1_VTTHD3 = 0x40,
    VO_INTMSK_DHD1_UFINT = 0x80,

    VO_INTMSK_DSD_VTTHD1 = 0x100,
    VO_INTMSK_DSD_VTTHD2 = 0x200,
    VO_INTMSK_DSD_VTTHD3 = 0x400,
    VO_INTMSK_DSD_UFINT = 0x800,

    VO_INTMSK_B0_ERR = 0x1000,
    VO_INTMSK_B1_ERR = 0x2000,
    VO_INTMSK_B2_ERR = 0x4000,

    VO_INTMSK_WBC_DHDOVER = 0x8000,

    VO_INTMSK_VGA_VDAC = 0x70000,   /*  INT VDAC0/VDAC1/VDAC2 */
    VO_INTMSK_CVBS_VDAC = 0x80000,  /*  INT VDAC3 */

    VO_INTREPORT_ALL = 0xffffffff
} vo_int_mask;

typedef enum {
    VO_INT_MODE_FRAME = 0x0,
    VO_INT_MODE_FIELD = 0x1,
    VO_INT_MODE_BUTT
} vo_int_mode;

#if VO_DESC("wbc zme")
typedef enum {
    VO_ZME_TYP = 0,
    VO_ZME_TYP1,
    VO_ZME_RAND,
    VO_ZME_MAX,
    VO_ZME_MIN,
    VO_ZME_ZERO,
    VO_ZME_BUTT
} vo_zme_mode;
#endif

#if VO_DESC("pub")
hal_disp_syncinfo *vo_drv_comm_get_sync_timing(hi_vo_intf_sync sync);
hi_s32 vou_drv_check_cvbs_sync(hi_vo_dev dev, hi_vo_intf_type intf_type, hi_vo_intf_sync intf_sync);
hal_disp_pixel_format vou_drv_convert_data_format(vou_layer_pixerl_format data_fmt);
hi_void vo_drv_board_init(hi_void);
hi_void vo_drv_csc_trans_to_register(csc_coef *coef);
#endif

#endif /* end of #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of __DRV_VO_COMM_H__ */
