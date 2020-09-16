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

#include "drv_vo.h"
#include "hal_vo.h"
#include "vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")

#if VO_DESC("pub")

vo_drv_dev g_vo_drv_dev[HI_VO_MAX_DEV_NUM];
vo_drv_layer g_vo_drv_layer[HI_VO_MAX_LAYER_NUM];

vo_drv_dev *vo_drv_get_dev_ctx(hi_vo_dev vo_dev)
{
    return &g_vo_drv_dev[vo_dev];
}

vo_drv_layer *vo_drv_get_layer_ctx(hi_vo_layer layer)
{
    return &g_vo_drv_layer[layer];
}

hi_void vo_drv_set_clk_reverse(hi_vo_dev dev, hi_bool reverse)
{
    hi_mpp_chn mpp_chn = {0};

    vo_drv_set_dev_mpp_chn(dev, &mpp_chn);
    call_sys_drv_ioctrl(&mpp_chn, SYS_VO_HD_CLKOUT_PHASIC_REVERSE_EN, &reverse);
}

hi_void vou_drv_def_layer_bind_dev(hi_void)
{
    hal_cbm_set_cbm_attr(HAL_DISP_LAYER_VHD2, VO_DEV_DHD0);
    hal_cbm_set_cbm_attr(HAL_DISP_LAYER_GFX2, VO_DEV_DHD0);

    vou_drv_set_layer_priority(VO_DEV_DHD0, HI_VO_LAYER_V0, VOU_MIX_PRIO0);
    vou_drv_set_layer_priority(VO_DEV_DHD0, HI_VO_LAYER_V2, VOU_MIX_PRIO1);
    vou_drv_set_layer_priority(VO_DEV_DHD0, HI_VO_LAYER_G0, VOU_MIX_PRIO2);
    vou_drv_set_layer_priority(VO_DEV_DHD0, HI_VO_LAYER_G2, VOU_MIX_PRIO4);

    vou_drv_set_layer_priority(VO_DEV_DHD1, HI_VO_LAYER_V1, VOU_MIX_PRIO0);
    vou_drv_set_layer_priority(VO_DEV_DHD1, HI_VO_LAYER_G1, VOU_MIX_PRIO2);

    vou_drv_set_layer_priority(VO_DEV_DSD0, HI_VO_LAYER_V3, VOU_MIX_PRIO0);
    vou_drv_set_layer_priority(VO_DEV_DSD0, HI_VO_LAYER_G3, VOU_MIX_PRIO1);

    hal_disp_set_reg_up(VO_DEV_DHD0);
    hal_disp_set_reg_up(VO_DEV_DHD1);
    hal_disp_set_reg_up(VO_DEV_DSD0);

    return;
}

hi_void vo_drv_default_setting(hi_void)
{
    hi_u32 i;
    hfir_coef h_coef[LAYER_VID_END + 1] = {
        { 0x3f5, 0xf, 0x3ec, 0x1c, 0x3d8, 0x3d, 0x395, 0x14a },
        { 0x3f5, 0xf, 0x3ec, 0x1c, 0x3d8, 0x3d, 0x395, 0x14a },
        { 0x3f5, 0xf, 0x3ec, 0x1c, 0x3d8, 0x3d, 0x395, 0x14a },
        { 0x3f5, 0xf, 0x3ec, 0x1c, 0x3d8, 0x3d, 0x395, 0x14a }
    };

    hal_sys_set_rd_bus_id(1);

    /* set dac default cablectr */
    vo_hal_intf_set_dac_cablectr(HI_VO_INTF_VGA, VO_DAC_CABLE_CTR_DEF);
    vo_hal_intf_set_dac_cablectr(HI_VO_INTF_CVBS, VO_DAC_CABLE_CTR_DEF);

    /* set each video/graphic layer global alpha */
    for (i = LAYER_VID_START; i <= LAYER_GFX_END; i++) {
        hal_layer_set_layer_global_alpha(i, 255); /* global alpha max 255 */
        hal_video_set_layer_alpha(i, 255); /* alpha max 255 */
    }

    /* select graphic layer's alpha range(0: 0~128,1:0~255) */
    for (i = LAYER_GFX_START; i <= LAYER_GFX_END; i++) {
        hal_gfx_set_pixel_alpha_range(i, 1);
    }

    /* set video layer hfir enable */
    for (i = LAYER_VID_START; i <= LAYER_VID_END; i++) {
        hal_video_hfir_set_hfir_mode(i, HAL_HFIRMODE_COPY);
        hal_video_hfir_set_coef(i, &h_coef[i]);
        hal_video_hfir_set_mid_en(i, HI_TRUE);
    }

    /* set each cross bar default PRI */
    vou_drv_def_layer_bind_dev();

    /* outstanding */
    hal_sys_set_outstanding();

    hal_disp_clear_int_status(VO_INTREPORT_ALL);

    /* only set video layer */
    for (i = LAYER_VID_START; i <= LAYER_VID_END; i++) {
        vou_drv_layer_enable(i, HI_FALSE);
        vou_drv_set_layer_data_fmt(i, VOU_LAYER_PIXERL_FORMAT_SP_YCBCR_422);
    }
}

#endif
#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
