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

#include "hal_vo_comm.h"
#include "drv_vo.h"
#include "hal_vo.h"
#include "hi_board.h"
#include <common.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")
#if VO_DESC("hal pub")

hi_void hal_vou_init(hi_void)
{
    volatile reg_vdp_regs *reg = vo_hal_get_reg();
    if (reg == HI_NULL) {
        reg = (volatile reg_vdp_regs *)IO_ADDRESS(VOU_REGS_ADDR);
        vo_hal_set_reg(reg);
    }

    if (reg == HI_NULL) {
        HI_PRINT("ioremap failed\n");
    }
}

hi_void hal_write_reg(hi_u32 *address, hi_u32 value)
{
    *(volatile hi_u32 *)address = value;
}

hi_u32 hal_read_reg(const hi_u32 *address)
{
    return *(volatile hi_u32 *)(address);
}

#endif
#if VO_DESC("hal check")

hi_bool vo_hal_is_phy_dev(hi_vo_dev dev)
{
    if ((dev >= DEV_PHY_START) && (dev <= DEV_PHY_END)) {
        return HI_TRUE;
    }

    return HI_FALSE;
}

hi_bool vo_hal_is_video_layer(hal_disp_layer layer)
{
    if ((layer >= LAYER_VID_START) && (layer <= LAYER_VID_END)) {
        return HI_TRUE;
    }

    return HI_FALSE;
}

hi_bool vo_hal_is_gfx_layer(hal_disp_layer layer)
{
    if ((layer >= LAYER_GFX_START) && (layer <= LAYER_GFX_END)) {
        return HI_TRUE;
    }

    return HI_FALSE;
}

#endif

#ifdef VO_HAL_CHECK_DEBUG

hi_bool vo_hal_is_video_gfx_layer(hal_disp_layer layer)
{
    if (vo_hal_is_video_layer(layer) || vo_hal_is_gfx_layer(layer)) {
        return HI_TRUE;
    }

    return HI_FALSE;
}

#endif

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
