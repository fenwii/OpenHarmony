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

#ifndef __DRV_VO_DEV_H__
#define __DRV_VO_DEV_H__

#include "hi_common.h"
#include "sys_ext.h"
#include "hi_common_vo.h"
#include "hi_inner_vo.h"
#include "drv_vo_comm.h"
#include "drv_vo_dev_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")

typedef enum {
    VO_CLK_DIV1 = 0,
    VO_CLK_DIV2 = 1,
    VO_CLK_DIV_BUTT
} vo_clk_div;

typedef enum {
    SSC_VDP_DIV_25_TO_50 = 15, /* 25MHz~50MHz, 16div */
    SSC_VDP_DIV_50_TO_100 = 7, /* 50MHz~100MHz, 8div */
    SSC_VDP_DIV_100_TO_200 = 3, /* 100MHz~200MHz, 4div */
    SSC_VDP_DIV_200_TO_340 = 1, /* 200MHz~340MHz, 2div */
    SSC_VDP_DIV_340_TO_600 = 0, /* 340MHz~600MHz, 1div */

    SSC_VDP_DIV_BUTT
}hi_vo_hdmi_ssc_vdp_div_mode;

typedef struct {
    hi_vo_intf_sync index;
    hi_vo_pll pll;
    hi_vo_hdmi_ssc_vdp_div_mode div;
}vo_pll_param;

typedef enum {
    VO_CLK_PLL_SRC_FOUTPOSTDIV = 0, /* FOUTVCO / (postdiv1 * postdiv2) */
    VO_CLK_PLL_SRC_FOUT4 = 1, /* FOUTVCO / (postdiv1 * postdiv2 * 8) */

    VO_CLK_PLL_SRC_BUTT
}vo_clk_pll_src;

#if VO_DESC("dev")
hi_void vo_drv_set_dev_user_intf_sync_attr(hi_vo_dev dev, const hi_vo_user_sync_info *sync_info);
hi_void vo_drv_set_dev_div(hi_vo_dev dev, hi_u32 dev_div);
hi_void vo_drv_set_hdmi_div(hi_vo_dev dev, hi_u32 pre_div);
hi_s32 vo_drv_check_dev_clk_src(hi_vo_dev dev, hi_vo_clk_src clk_src);
hi_s32 vo_drv_check_intf_user_dev_div(hi_vo_dev dev, hi_u32 dev_div);
hi_s32 vo_drv_check_dev_fixed_clk(hi_vo_dev dev, hi_vo_fixed_clk fixed_clk);
#endif

#if VO_DESC("dev intf")
hi_s32 vou_drv_check_hdmi_sync(hi_vo_dev dev, hi_vo_intf_type intf_type, hi_vo_intf_sync intf_sync);
hi_s32 vou_drv_check_bt_sync(hi_vo_dev dev, hi_vo_intf_type intf_type, hi_vo_intf_sync intf_sync);
hi_s32 vou_drv_check_vga_sync(hi_vo_dev dev, hi_vo_intf_type intf_type, hi_vo_intf_sync intf_sync);
hi_s32 vou_drv_check_rgb_sync(hi_vo_dev dev, hi_vo_intf_type intf_type, hi_vo_intf_sync intf_sync);
hi_s32 vou_drv_check_dev_intf(hi_vo_dev dev, hi_vo_intf_type intf_type);
hi_u32 vo_drv_get_vga_gain_def(hi_void);
#endif

#if VO_DESC("dev")

hi_void vo_drv_open(hi_vo_dev dev);
hi_void vo_drv_close(hi_vo_dev dev);

hi_void vo_drv_dev_info_init(hi_void);
hi_vo_layer vo_drv_get_layer(hi_vo_dev dev);
hi_void vo_drv_default_setting(hi_void);
hi_s32 vo_drv_check_dev_id(hi_vo_dev dev);
hi_s32 vo_drv_check_layer_id(hi_vo_layer layer);
hi_void vou_drv_set_dev_clk(hi_vo_dev dev);
hi_void vo_drv_set_out_clk_div(hi_u32 dev, hi_u32 vo_out_clk_div);
hi_void vo_drv_set_dev_clk_en_sel(hi_vo_dev dev);
hi_void vo_drv_dev_get_clk_pll_src(hi_vo_dev dev, hi_u32 *pll_src);
hi_void vo_drv_set_intf_dither(hi_vo_intf_type intf_type, hi_u32 in_bit_width);
hi_u32 vo_drv_dev_get_max_clk(hi_vo_dev dev);
#endif

hi_void vo_drv_dev_get_pll_cfg(hi_vo_dev dev, hi_vo_pll *pll);
hi_void vo_drv_get_pll_cfg_no_div(hi_vo_intf_sync intf_sync, hi_vo_pll *pll);
hi_void vo_drv_get_hdmi_ssc_vdp_div(hi_vo_intf_sync intf_sync, hi_u32 *hdmi_ssc_vdp_div);
hi_void vo_drv_dev_set_pll_cfg(hi_vo_dev dev, hi_vo_pll *pll);

#if VO_DESC("dev")
hi_void vo_drv_set_all_crg_clk(hi_bool clk_en);
hi_void vo_lpw_bus_reset(hi_bool reset);
#endif

hi_bool vo_drv_is_dev_support_rgb(hi_vo_dev dev);

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of __DRV_VO_DEV_H__ */
