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

#include "hal_vo.h"
#include "mkp_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")

volatile reg_vdp_regs *g_vo_reg = HI_NULL;

#if VO_DESC("pub")

volatile reg_vdp_regs *vo_hal_get_reg(hi_void)
{
    return g_vo_reg;
}

hi_void vo_hal_set_reg(volatile reg_vdp_regs *reg)
{
    g_vo_reg = reg;
}

#endif

#if VO_DESC("get abs addr")

hi_ulong vou_get_abs_addr(hal_disp_layer layer, hi_ulong reg)
{
    volatile hi_ulong reg_abs_addr;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1:
        case HAL_DISP_LAYER_VHD2:
        case HAL_DISP_LAYER_VSD0:
            reg_abs_addr = reg + (layer - HAL_DISP_LAYER_VHD0) * VHD_REGS_LEN;
            break;

        case HAL_DISP_LAYER_GFX0:
        case HAL_DISP_LAYER_GFX1:
        case HAL_DISP_LAYER_GFX2:
        case HAL_DISP_LAYER_GFX3:
            reg_abs_addr = reg + (layer - HAL_DISP_LAYER_GFX0) * GFX_REGS_LEN;
            break;

        /* one wbc dev */
        case HAL_DISP_LAYER_WBC:
            reg_abs_addr = reg;
            break;

        default:
            vo_err_trace("invalid layer %d!\n", layer);
            reg_abs_addr = reg;
            break;
    }

    return reg_abs_addr;
}

hi_ulong vou_get_chn_abs_addr(hi_vo_dev dev, hi_ulong reg)
{
    volatile hi_ulong reg_abs_addr;

    switch (dev) {
        case VO_DEV_DHD0:
        case VO_DEV_DHD1:
        case VO_DEV_DSD0:
            reg_abs_addr = reg + (dev - VO_DEV_DHD0) * DHD_REGS_LEN;
            break;

        default:
            vo_err_trace("invalid dev %d!\n", dev);
            reg_abs_addr = reg;
            break;
    }

    return reg_abs_addr;
}

hi_ulong vou_get_vid_abs_addr(hal_disp_layer layer, hi_ulong reg)
{
    volatile hi_ulong reg_abs_addr;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1:
        case HAL_DISP_LAYER_VHD2:
        case HAL_DISP_LAYER_VSD0:
            reg_abs_addr = reg + (layer - HAL_DISP_LAYER_VHD0) * VID_REGS_LEN;
            break;

        default:
            vo_err_trace("invalid layer %d!\n", layer);
            reg_abs_addr = reg;
            break;
    }

    return reg_abs_addr;
}

hi_ulong vou_get_gfx_abs_addr(hal_disp_layer layer, hi_ulong reg)
{
    volatile hi_ulong reg_abs_addr;

    switch (layer) {
        case HAL_DISP_LAYER_GFX0:
        case HAL_DISP_LAYER_GFX1:
        case HAL_DISP_LAYER_GFX2:
        case HAL_DISP_LAYER_GFX3:
            reg_abs_addr = reg + (layer - HAL_DISP_LAYER_GFX0) * GRF_REGS_LEN;
            break;

        default:
            vo_err_trace("invalid layer %d!\n", layer);
            reg_abs_addr = reg;
            break;
    }

    return reg_abs_addr;
}
#endif

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
