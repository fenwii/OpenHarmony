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

#include "hi_common.h"
#include "sys_drv.h"
#include "sys_hal.h"
#include "sys_ext.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

hi_s32 sys_drv_drv_ioctrl(hi_mpp_chn *mpp_chn, sys_func func_id, hi_void *io_args)
{
    hi_s32 dev;

    dev = mpp_chn->dev_id;
    switch (func_id) {
        case SYS_VO_BUS_RESET_SEL: {
            hi_bool *reset = HI_NULL;
            reset = (hi_bool *)io_args;
            sys_hal_vo_bus_reset_sel(*reset);
            break;
        }

        case SYS_VO_CFG_CLK_EN: {
            hi_bool *clk_en = HI_NULL;
            clk_en = (hi_bool *)io_args;
            sys_hal_vo_cfg_clk_en(*clk_en);
            break;
        }
        case SYS_VO_APB_CLK_EN: {
            hi_bool *clk_en = HI_NULL;
            clk_en = (hi_bool *)io_args;
            sys_hal_vo_apb_clk_en(*clk_en);
            break;
        }

        case SYS_VO_BUS_CLK_EN: {
            hi_bool *clk_en = HI_NULL;
            clk_en = (hi_bool *)io_args;
            sys_hal_vo_bus_clk_en(*clk_en);
            break;
        }

        case SYS_VO_HD_CLKOUT_PHASIC_REVERSE_EN: {
            hi_bool *clk_reverse_en = HI_NULL;
            clk_reverse_en = (hi_bool *)io_args;
            sys_hal_vo_out_hd_phase_ctrl(dev, *clk_reverse_en);
            break;
        }

        case SYS_VO_OUT_DLY_TUNE: {
            hi_u32 *dly_tune = HI_NULL;
            dly_tune = (hi_u32 *)io_args;
            sys_hal_vo_dly_tune(dev, *dly_tune);
            break;
        }

        case SYS_VO_OUT_HD_DIV: {
            hi_u32 *div_mode = HI_NULL;
            div_mode = (hi_u32 *)io_args;
            sys_hal_vo_out_hd_clk_div(dev, *div_mode);
            break;
        }

        case SYS_VO_HD0_DIV_MOD: {
            hi_u32 *clk_sel = HI_NULL;
            clk_sel = (hi_u32 *)io_args;
            sys_hal_vo_hd0_div_mode(dev, *clk_sel);
            break;
        }

        case SYS_VO_HD_CLK_SEL: {
            hi_u32 *clk_sel = HI_NULL;
            clk_sel = (hi_u32 *)io_args;
            sys_hal_vo_hd_clk_sel(dev, *clk_sel);
            break;
        }

        case SYS_VO_CORE_CLK_EN: {
            hi_bool *clk_en = HI_NULL;
            clk_en = (hi_bool *)io_args;
            sys_hal_vo_core_clk_en(dev, *clk_en);
            break;
        }

        case SYS_VO_DEV_CLK_EN: {
            hi_bool *clk_en = HI_NULL;
            clk_en = (hi_bool *)io_args;
            sys_hal_vo_dev_clk_en(dev, *clk_en);
            break;
        }

        case SYS_VO_HD1_DIV_MOD: {
            hi_u32 *clk_sel = HI_NULL;
            clk_sel = (hi_u32 *)io_args;
            sys_hal_vo_hd1_div_mode(dev, *clk_sel);
            break;
        }

        case SYS_VO_SD_CLK_DIV: {
            hi_u32 *div_mode = HI_NULL;
            div_mode = (hi_u32 *)io_args;
            sys_hal_vo_sd_div_mode(dev, *div_mode);
            break;
        }

        case SYS_VO_SD_CLK_SEL: {
            hi_u32 *clk_sel = HI_NULL;
            clk_sel = (hi_u32 *)io_args;
            sys_hal_vo_sd_clk_sel(dev, *clk_sel);
            break;
        }

        case SYS_VO_BT1120_CLK_EN: {
            hi_bool *bt1120_clk_en = HI_NULL;
            bt1120_clk_en = (hi_bool *)io_args;
            sys_hal_vo_bt_clk_en(dev, *bt1120_clk_en);
            break;
        }

        case SYS_VO_BT1120_CLK_SEL: {
            hi_u32 *bt1120_clk_ch_sel = HI_NULL;
            bt1120_clk_ch_sel = (hi_u32 *)io_args;
            sys_hal_vo_bt_clk_sel(dev, *bt1120_clk_ch_sel);
            break;
        }

        case SYS_VO_DAC_CLK_PHASIC_REVERSE_EN: {
            hi_u32 *rev = HI_NULL;
            rev = (hi_u32 *)io_args;
            sys_hal_vo_vdac_phase_ctrl(dev, *rev);
            break;
        }

        case SYS_VO_HD_DAC_SEL: {
            hi_bool *clk_sel = HI_NULL;
            clk_sel = (hi_bool *)io_args;
            sys_hal_vo_hd_vdac_clk_sel(dev, *clk_sel);
            break;
        }

        case SYS_VO_DEV_DAC_EN: {
            hi_bool *clk_en = HI_NULL;
            clk_en = (hi_bool *)io_args;
            sys_hal_vo_vdac_clk_en(dev, *clk_en);
            break;
        }

        case SYS_VO_HDMI_SSC_VDP_DIV: {
            hi_u32 *div_mode = HI_NULL;
            div_mode = (hi_u32 *)io_args;
            sys_hal_vo_hdmi_ssc_vdp_div(dev, *div_mode);
            break;
        }

        case SYS_VO_HDMI_CLK_EN: {
            hi_bool *hdmi_clk_en = HI_NULL;
            hdmi_clk_en = (hi_bool *)io_args;
            sys_hal_vo_hdmi_clk_en(dev, *hdmi_clk_en);
            break;
        }

        case SYS_VO_HDMI_CLK_SEL: {
            hi_bool *clk_sel = HI_NULL;
            clk_sel = (hi_bool *)io_args;
            sys_hal_vo_hdmi_clk_sel(dev, *clk_sel);
            break;
        }

        case SYS_VO_PLL_POSTDIV2_SET: {
            hi_s32 pll;
            hi_u32 bits_set;
            pll = mpp_chn->dev_id;
            bits_set = *(hi_u32 *)io_args;
            sys_hal_vo_set_pll_postdiv2(pll, bits_set);
            break;
        }

        case SYS_VO_PLL_POSTDIV1_SET: {
            hi_s32 pll;
            hi_u32 bits_set;
            pll = mpp_chn->dev_id;
            bits_set = *(hi_u32 *)io_args;
            sys_hal_vo_set_pll_postdiv1(pll, bits_set);
            break;
        }

        case SYS_VO_PLL_FRAC_SET: {
            hi_s32 pll;
            hi_u32 bits_set;
            pll = mpp_chn->dev_id;
            bits_set = *(hi_u32 *)io_args;
            sys_hal_vo_set_pll_frac(pll, bits_set);
            break;
        }

        case SYS_VO_PLL_REFDIV_SET: {
            hi_s32 pll;
            hi_u32 bits_set;
            pll = mpp_chn->dev_id;
            bits_set = *(hi_u32 *)io_args;
            sys_hal_vo_set_pll_refdiv(pll, bits_set);
            break;
        }

        case SYS_VO_PLL_FBDIV_SET: {
            hi_s32 pll;
            hi_u32 bits_set;
            pll = mpp_chn->dev_id;
            bits_set = *(hi_u32 *)io_args;
            sys_hal_vo_set_pll_fbdiv(pll, bits_set);
            break;
        }

        case SYS_VO_PLL_POWER_CTRL: {
            hi_s32 pll;
            hi_bool *power_on = HI_NULL;
            pll = mpp_chn->dev_id;
            power_on = (hi_bool *)io_args;
            sys_hal_vo_set_pll_power_ctrl(pll, *power_on);
            break;
        }

        default:
        {
            return HI_FAILURE;
        }
    }
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
        }
#endif
#endif /* end of #ifdef __cplusplus */
