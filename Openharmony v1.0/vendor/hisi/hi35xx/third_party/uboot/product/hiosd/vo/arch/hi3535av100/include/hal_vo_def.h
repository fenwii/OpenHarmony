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

#ifndef __HAL_VO_DEF_H__
#define __HAL_VO_DEF_H__

#include "hi_type.h"
#include "hi_defines.h"
#include "hal_vo_def_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")

#define VHD_REGS_LEN        0x1000 /* len of V0's regs */
#define GFX_REGS_LEN        0x800
#define DHD_REGS_LEN        0x1000
#define INTF_REGS_LEN       0x100
#define VID_REGS_LEN        0x200 /* len of VID regs */
#define GRF_REGS_LEN        0x200 /* len of GFX regs */

/* offset define */
/* 0x200 bytes, 0x200/4 regs */
#define FDR_VID_OFFSET      (0x200 / 4)

#define ZME_HPREC           (1 << 20)
#define ZME_VPREC           (1 << 12)

typedef enum {
    VO_DEV_DHD0 = 0, /* ultra high definition device */
    VO_DEV_DHD1 = 1, /* high definition device */
    VO_DEV_DSD0 = 2, /* standard definition device */
    VO_DEV_BUTT
} vo_hal_dev;

typedef enum {
    VO_HAL_LAYER_VHD0 = 0, /* V0 layer */
    VO_HAL_LAYER_VHD1 = 1, /* V1 layer */
    VO_HAL_LAYER_VHD2 = 2, /* V2 layer */
    VO_HAL_LAYER_VSD0 = 3, /* V3 layer */

    VO_HAL_LAYER_G0 = 4, /* G0 layer */
    VO_HAL_LAYER_G1 = 5, /* G1 layer */
    VO_HAL_LAYER_G2 = 6, /* G2 layer */
    VO_HAL_LAYER_G3 = 7, /* G3 layer */

    VO_HAL_LAYER_WBC = 8, /* wbc layer */

    VO_HAL_LAYER_BUTT
} vo_hal_layer;

typedef enum {
    VO_SW_LAYER_VHD0 = 0,
    VO_SW_LAYER_VHD1 = 1,
    VO_SW_LAYER_VHD2 = 2,
    VO_SW_LAYER_VSD0 = 3,

    VO_SW_LAYER_VIRT0 = hi_vo_get_virt_layer(HI_VO_VIRT_DEV_0),
    VO_SW_LAYER_VIRT1 = hi_vo_get_virt_layer(HI_VO_VIRT_DEV_1),
    VO_SW_LAYER_VIRT2 = hi_vo_get_virt_layer(HI_VO_VIRT_DEV_2),
    VO_SW_LAYER_VIRT3 = hi_vo_get_virt_layer(HI_VO_VIRT_DEV_3),
    VO_SW_LAYER_VIRT31 = (VO_SW_LAYER_VIRT0 + HI_VO_MAX_VIRT_DEV_NUM),

    VO_SW_LAYER_CAS1 = hi_vo_get_cas_layer(HI_VO_CAS_DEV_1),
    VO_SW_LAYER_CAS2 = hi_vo_get_cas_layer(HI_VO_CAS_DEV_2),
    VOU_SW_LAYER_BUTT
} vo_sw_layer;

typedef enum {
    HAL_DISP_LAYER_VHD0 = 0,
    HAL_DISP_LAYER_VHD1 = 1,
    HAL_DISP_LAYER_VHD2 = 2,
    HAL_DISP_LAYER_VSD0 = 3,

    HAL_DISP_LAYER_GFX0 = 4,
    HAL_DISP_LAYER_GFX1 = 5,
    HAL_DISP_LAYER_GFX2 = 6,  /* not used */
    HAL_DISP_LAYER_GFX3 = 7,  /* for hardware cursor */

    HAL_DISP_LAYER_WBC = 8,

    HAL_DISP_LAYER_TT = 9,
    HAL_DISP_LAYER_BUTT,
    HAL_DISP_INVALID_LAYER = -1
} hal_disp_layer;

typedef enum {
    GX_LAYER_INDEX0 = 0,
    GX_LAYER_INDEX1,
    GX_LAYER_INDEX2,
    GX_LAYER_INDEX3,

    GX_LAYER_INDEX_BUTT,
}gx_layer_index;

#define DEV_PHY_START       VO_DEV_DHD0
#define DEV_PHY_END         VO_DEV_DSD0

#define LAYER_VID_START     HAL_DISP_LAYER_VHD0  /* VHD0 */
#define LAYER_VID_END       HAL_DISP_LAYER_VSD0  /* VSD0 */

#define LAYER_GFX_START     HAL_DISP_LAYER_GFX0  /* GFX0 */
#define LAYER_GFX_END       HAL_DISP_LAYER_GFX3  /* GFX3 */

typedef struct {
    hi_u32 ck_gt_en;
    hi_u32 out_pro;
    hi_u32 out_fmt;
    hi_u64 in_height;
    hi_u64 out_height;
    hi_u64 in_width;
    hi_u64 out_width;
    hi_u32 cvfir_en;
    hi_u32 cvmid_en;
    hi_u32 cvfir_mode;

    hi_u32 hfir_order;
    hi_u32 lhfir_en;
    hi_u32 chfir_en;
    hi_u32 lhmid_en;
    hi_u32 chmid_en;
    hi_u32 non_lnr_en;
    hi_u32 lhfir_mode;
    hi_u32 chfir_mode;
    hi_u32 hl_shootctrl_en;
    hi_u32 hl_shootctrl_mode;
    hi_u32 hc_shootctrl_en;
    hi_u32 hc_shootctrl_mode;

    hi_u32 in_pro;
    hi_u32 graphdet_en;

    hi_u32 lvfir_en;
    hi_u32 lvmid_en;
    hi_u32 vfir_1tap_en;
    hi_u32 lvfir_mode;
    hi_u32 vl_shootctrl_en;
    hi_u32 vl_shootctrl_mode;
    hi_u32 vc_shootctrl_en;
    hi_u32 vc_shootctrl_mode;
} vdp_v1_cvfir_cfg;

typedef struct {
    hi_u32 vluma_offset;
    hi_u32 vchroma_offset;
    hi_u32 vbluma_offset;
    hi_u32 vbchroma_offset;
    hi_u32 lhfir_offset;
    hi_u32 chfir_offset;
    hi_u32 vl_flatdect_mode;
    hi_u32 vl_coringadj_en;
    hi_u32 vl_gain;
    hi_u32 vl_coring;
    hi_u32 vc_flatdect_mode;
    hi_u32 vc_coringadj_en;
    hi_u32 vc_gain;
    hi_u32 vc_coring;
    hi_u32 hl_flatdect_mode;
    hi_u32 hl_coringadj_en;
    hi_u32 hl_gain;
    hi_u32 hl_coring;
    hi_u32 hc_flatdect_mode;
    hi_u32 hc_coringadj_en;
    hi_u32 hc_gain;
    hi_u32 hc_coring;
} vo_zme_comm_pq_cfg;

typedef struct {
    hi_u32 ck_gt_en;
    hi_u32 hfir_order;
    hi_u32 lhfir_en;
    hi_u32 chfir_en;
    hi_u32 lhmid_en;
    hi_u32 chmid_en;
    hi_u32 non_lnr_en;
    hi_u32 lhfir_mode;
    hi_u32 chfir_mode;
    hi_u32 hl_shootctrl_en;
    hi_u32 hl_shootctrl_mode;
    hi_u32 hc_shootctrl_en;
    hi_u32 hc_shootctrl_mode;

    hi_u32 in_pro;
    hi_u32 out_pro;
    hi_u32 out_fmt;
    hi_u64 in_height;
    hi_u64 out_height;
    hi_u64 in_width;
    hi_u64 out_width;
    hi_u32 graphdet_en;

    hi_u32 lvfir_en;
    hi_u32 cvfir_en;
    hi_u32 lvmid_en;
    hi_u32 cvmid_en;
    hi_u32 vfir_1tap_en;
    hi_u32 lvfir_mode;
    hi_u32 cvfir_mode;
    hi_u32 vl_shootctrl_en;
    hi_u32 vl_shootctrl_mode;
    hi_u32 vc_shootctrl_en;
    hi_u32 vc_shootctrl_mode;
} vo_v0_zme_cfg;

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
#endif /* end of __HAL_VO_DEF_H__ */
