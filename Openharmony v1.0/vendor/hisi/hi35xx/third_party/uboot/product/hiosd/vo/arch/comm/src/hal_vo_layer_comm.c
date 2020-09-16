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

#include "hal_vo_layer_comm.h"
#include "drv_vo.h"
#include "hal_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")
#if VO_DESC("layer")
hi_void hal_video_set_layer_alpha(hal_disp_layer layer, hi_u32 arange)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_alpha v0_alpha;
    volatile reg_g0_alpha g0_alpha;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_gfx_layer_return(layer);

    if (vo_hal_is_video_layer(layer)) {
        addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_alpha.u32));
        v0_alpha.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
        v0_alpha.bits.vbk_alpha = arange;
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_alpha.u32);
        return;
    }

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_alpha.u32));
    g0_alpha.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_alpha.bits.vbk_alpha = arange;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_alpha.u32);
}

hi_void hal_layer_csc_set_enable_ck_gt_en(hal_disp_layer layer, hi_bool csc_en, hi_bool ck_gt_en)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_v0_hipp_csc_ctrl v0_hipp_csc_ctrl;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_gfx_layer_return(layer);

    if (vo_hal_is_video_layer(layer)) {
        addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_ctrl.u32));
    } else {
        addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_ctrl.u32));
    }

    v0_hipp_csc_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_ctrl.bits.hipp_csc_en = csc_en;
    v0_hipp_csc_ctrl.bits.hipp_csc_ck_gt_en = ck_gt_en;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_ctrl.u32);
}

static hi_void hal_layer_csc_set_video_coef(hal_disp_layer layer, vdp_csc_coef *coef)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_v0_hipp_csc_coef00 v0_hipp_csc_coef00;
    reg_v0_hipp_csc_coef01 v0_hipp_csc_coef01;
    reg_v0_hipp_csc_coef02 v0_hipp_csc_coef02;
    reg_v0_hipp_csc_coef10 v0_hipp_csc_coef10;
    reg_v0_hipp_csc_coef11 v0_hipp_csc_coef11;
    reg_v0_hipp_csc_coef12 v0_hipp_csc_coef12;
    reg_v0_hipp_csc_coef20 v0_hipp_csc_coef20;
    reg_v0_hipp_csc_coef21 v0_hipp_csc_coef21;
    reg_v0_hipp_csc_coef22 v0_hipp_csc_coef22;
    volatile hi_ulong addr_reg;

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_coef00.u32));
    v0_hipp_csc_coef00.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_coef00.bits.hipp_csc_coef00 = coef->csc_coef00;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_coef00.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_coef01.u32));
    v0_hipp_csc_coef01.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_coef01.bits.hipp_csc_coef01 = coef->csc_coef01;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_coef01.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_coef02.u32));
    v0_hipp_csc_coef02.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_coef02.bits.hipp_csc_coef02 = coef->csc_coef02;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_coef02.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_coef10.u32));
    v0_hipp_csc_coef10.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_coef10.bits.hipp_csc_coef10 = coef->csc_coef10;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_coef10.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_coef11.u32));
    v0_hipp_csc_coef11.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_coef11.bits.hipp_csc_coef11 = coef->csc_coef11;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_coef11.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_coef12.u32));
    v0_hipp_csc_coef12.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_coef12.bits.hipp_csc_coef12 = coef->csc_coef12;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_coef12.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_coef20.u32));
    v0_hipp_csc_coef20.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_coef20.bits.hipp_csc_coef20 = coef->csc_coef20;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_coef20.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_coef21.u32));
    v0_hipp_csc_coef21.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_coef21.bits.hipp_csc_coef21 = coef->csc_coef21;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_coef21.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_coef22.u32));
    v0_hipp_csc_coef22.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_coef22.bits.hipp_csc_coef22 = coef->csc_coef22;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_coef22.u32);
}

static hi_void hal_layer_csc_set_gfx_coef(hal_disp_layer layer, vdp_csc_coef *coef)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_v0_hipp_csc_coef00 g0_hipp_csc_coef00;
    reg_v0_hipp_csc_coef01 g0_hipp_csc_coef01;
    reg_v0_hipp_csc_coef02 g0_hipp_csc_coef02;
    reg_v0_hipp_csc_coef10 g0_hipp_csc_coef10;
    reg_v0_hipp_csc_coef11 g0_hipp_csc_coef11;
    reg_v0_hipp_csc_coef12 g0_hipp_csc_coef12;
    reg_v0_hipp_csc_coef20 g0_hipp_csc_coef20;
    reg_v0_hipp_csc_coef21 g0_hipp_csc_coef21;
    reg_v0_hipp_csc_coef22 g0_hipp_csc_coef22;
    volatile hi_ulong addr_reg;

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_coef00.u32));
    g0_hipp_csc_coef00.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_coef00.bits.hipp_csc_coef00 = coef->csc_coef00;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_coef00.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_coef01.u32));
    g0_hipp_csc_coef01.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_coef01.bits.hipp_csc_coef01 = coef->csc_coef01;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_coef01.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_coef02.u32));
    g0_hipp_csc_coef02.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_coef02.bits.hipp_csc_coef02 = coef->csc_coef02;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_coef02.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_coef10.u32));
    g0_hipp_csc_coef10.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_coef10.bits.hipp_csc_coef10 = coef->csc_coef10;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_coef10.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_coef11.u32));
    g0_hipp_csc_coef11.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_coef11.bits.hipp_csc_coef11 = coef->csc_coef11;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_coef11.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_coef12.u32));
    g0_hipp_csc_coef12.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_coef12.bits.hipp_csc_coef12 = coef->csc_coef12;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_coef12.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_coef20.u32));
    g0_hipp_csc_coef20.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_coef20.bits.hipp_csc_coef20 = coef->csc_coef20;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_coef20.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_coef21.u32));
    g0_hipp_csc_coef21.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_coef21.bits.hipp_csc_coef21 = coef->csc_coef21;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_coef21.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_coef22.u32));
    g0_hipp_csc_coef22.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_coef22.bits.hipp_csc_coef22 = coef->csc_coef22;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_coef22.u32);
}

static hi_void hal_layer_csc_set_video_dc_coef(hal_disp_layer layer, vdp_csc_dc_coef *csc_dc_coef)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_v0_hipp_csc_idc0 v0_hipp_csc_idc0;
    reg_v0_hipp_csc_idc1 v0_hipp_csc_idc1;
    reg_v0_hipp_csc_idc2 v0_hipp_csc_idc2;
    reg_v0_hipp_csc_odc0 v0_hipp_csc_odc0;
    reg_v0_hipp_csc_odc1 v0_hipp_csc_odc1;
    reg_v0_hipp_csc_odc2 v0_hipp_csc_odc2;
    volatile hi_ulong addr_reg;

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_idc0.u32));
    v0_hipp_csc_idc0.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_idc0.bits.hipp_csc_idc0 = csc_dc_coef->csc_in_dc0;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_idc0.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_idc1.u32));
    v0_hipp_csc_idc1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_idc1.bits.hipp_csc_idc1 = csc_dc_coef->csc_in_dc1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_idc1.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_idc2.u32));
    v0_hipp_csc_idc2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_idc2.bits.hipp_csc_idc2 = csc_dc_coef->csc_in_dc2;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_idc2.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_odc0.u32));
    v0_hipp_csc_odc0.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_odc0.bits.hipp_csc_odc0 = csc_dc_coef->csc_out_dc0;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_odc0.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_odc1.u32));
    v0_hipp_csc_odc1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_odc1.bits.hipp_csc_odc1 = csc_dc_coef->csc_out_dc1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_odc1.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_odc2.u32));
    v0_hipp_csc_odc2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_odc2.bits.hipp_csc_odc2 = csc_dc_coef->csc_out_dc2;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_odc2.u32);
}

static hi_void hal_layer_csc_set_gfx_dc_coef(hal_disp_layer layer, vdp_csc_dc_coef *csc_dc_coef)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_v0_hipp_csc_idc0 g0_hipp_csc_idc0;
    reg_v0_hipp_csc_idc1 g0_hipp_csc_idc1;
    reg_v0_hipp_csc_idc2 g0_hipp_csc_idc2;
    reg_v0_hipp_csc_odc0 g0_hipp_csc_odc0;
    reg_v0_hipp_csc_odc1 g0_hipp_csc_odc1;
    reg_v0_hipp_csc_odc2 g0_hipp_csc_odc2;
    volatile hi_ulong addr_reg;

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_idc0.u32));
    g0_hipp_csc_idc0.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_idc0.bits.hipp_csc_idc0 = csc_dc_coef->csc_in_dc0;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_idc0.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_idc1.u32));
    g0_hipp_csc_idc1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_idc1.bits.hipp_csc_idc1 = csc_dc_coef->csc_in_dc1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_idc1.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_idc2.u32));
    g0_hipp_csc_idc2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_idc2.bits.hipp_csc_idc2 = csc_dc_coef->csc_in_dc2;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_idc2.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_odc0.u32));
    g0_hipp_csc_odc0.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_odc0.bits.hipp_csc_odc0 = csc_dc_coef->csc_out_dc0;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_odc0.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_odc1.u32));
    g0_hipp_csc_odc1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_odc1.bits.hipp_csc_odc1 = csc_dc_coef->csc_out_dc1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_odc1.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_odc2.u32));
    g0_hipp_csc_odc2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_odc2.bits.hipp_csc_odc2 = csc_dc_coef->csc_out_dc2;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_odc2.u32);
}

static hi_void hal_layer_csc_set_video_param(hal_disp_layer layer, csc_coef_param *csc_param)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_v0_hipp_csc_scale v0_hipp_csc_scale;
    reg_v0_hipp_csc_min_y v0_hipp_csc_min_y;
    reg_v0_hipp_csc_min_c v0_hipp_csc_min_c;
    reg_v0_hipp_csc_max_y v0_hipp_csc_max_y;
    reg_v0_hipp_csc_max_c v0_hipp_csc_max_c;
    volatile hi_ulong addr_reg;

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_scale.u32));
    v0_hipp_csc_scale.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_scale.bits.hipp_csc_scale = csc_param->csc_scale2p;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_scale.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_min_y.u32));
    v0_hipp_csc_min_y.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_min_y.bits.hipp_csc_min_y = csc_param->csc_clip_min;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_min_y.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_min_c.u32));
    v0_hipp_csc_min_c.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_min_c.bits.hipp_csc_min_c = csc_param->csc_clip_min;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_min_c.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_max_y.u32));
    v0_hipp_csc_max_y.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_max_y.bits.hipp_csc_max_y = csc_param->csc_clip_max;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_max_y.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_hipp_csc_max_c.u32));
    v0_hipp_csc_max_c.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    v0_hipp_csc_max_c.bits.hipp_csc_max_c = csc_param->csc_clip_max;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_hipp_csc_max_c.u32);
}

static hi_void hal_layer_csc_set_gfx_param(hal_disp_layer layer, csc_coef_param *csc_param)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_v0_hipp_csc_scale g0_hipp_csc_scale;
    reg_v0_hipp_csc_min_y g0_hipp_csc_min_y;
    reg_v0_hipp_csc_min_c g0_hipp_csc_min_c;
    reg_v0_hipp_csc_max_y g0_hipp_csc_max_y;
    reg_v0_hipp_csc_max_c g0_hipp_csc_max_c;
    volatile hi_ulong addr_reg;

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_scale.u32));
    g0_hipp_csc_scale.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_scale.bits.hipp_csc_scale = csc_param->csc_scale2p;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_scale.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_min_y.u32));
    g0_hipp_csc_min_y.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_min_y.bits.hipp_csc_min_y = csc_param->csc_clip_min;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_min_y.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_min_c.u32));
    g0_hipp_csc_min_c.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_min_c.bits.hipp_csc_min_c = csc_param->csc_clip_min;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_min_c.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_max_y.u32));
    g0_hipp_csc_max_y.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_max_y.bits.hipp_csc_max_y = csc_param->csc_clip_max;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_max_y.u32);

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_hipp_csc_max_c.u32));
    g0_hipp_csc_max_c.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_hipp_csc_max_c.bits.hipp_csc_max_c = csc_param->csc_clip_max;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_hipp_csc_max_c.u32);
}

hi_void hal_layer_set_csc_coef(hal_disp_layer layer, csc_coef *coef)
{
    if (vo_hal_is_video_layer(layer)) {
        hal_layer_csc_set_video_dc_coef(layer, (vdp_csc_dc_coef *)(&coef->csc_in_dc0));
        hal_layer_csc_set_video_coef(layer, (vdp_csc_coef *)(&coef->csc_coef00));
        hal_layer_csc_set_video_param(layer, (csc_coef_param *)(&coef->new_csc_scale2p));
        return;
    }

    hal_layer_csc_set_gfx_dc_coef(layer, (vdp_csc_dc_coef *)(&coef->csc_in_dc0));
    hal_layer_csc_set_gfx_coef(layer, (vdp_csc_coef *)(&coef->csc_coef00));
    hal_layer_csc_set_gfx_param(layer, (csc_coef_param *)(&coef->new_csc_scale2p));
}

hi_void hal_layer_set_layer_global_alpha(hal_disp_layer layer, hi_u8 alpha0)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_v0_ctrl v0_ctrl;
    volatile reg_g0_ctrl g0_ctrl;
    volatile hi_ulong addr_reg;

    vo_hal_check_video_gfx_layer_return(layer);

    if (vo_hal_is_video_layer(layer)) {
        addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->v0_ctrl.u32));
        v0_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
        v0_ctrl.bits.galpha = alpha0;
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, v0_ctrl.u32);
        return;
    }

    addr_reg = vou_get_abs_addr(layer, (hi_uintptr_t) & (vo_reg->g0_ctrl.u32));
    g0_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    g0_ctrl.bits.galpha = alpha0;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, g0_ctrl.u32);
}
#endif
#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
