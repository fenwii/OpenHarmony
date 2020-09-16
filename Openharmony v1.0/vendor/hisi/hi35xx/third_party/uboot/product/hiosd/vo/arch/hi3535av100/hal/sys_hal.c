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

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <version.h>
#include <net.h>
#include <asm/io.h>
#include <asm/arch/platform.h>

#include "hi_type.h"
#include "hi_board.h"
#include "sys_hal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#define IO_CRG_ADDRESS(x) (x)
#define IO_CRG_PLL_ADDRESS(x) (x)

static void hi_reg_set_bit(unsigned long value, unsigned long offset,
                           unsigned long addr)
{
    unsigned long t, mask;

    mask = 1 << offset;
    t = readl((const volatile void *)(hi_uintptr_t)addr);
    t &= ~mask;
    t |= (value << offset) & mask;
    writel (t, (volatile void *)(hi_uintptr_t)addr);
}

static void hi_reg_write32(unsigned long value, unsigned long mask,
                           unsigned long addr)
{
    unsigned long t;

    t = readl((const volatile void *)(hi_uintptr_t)addr);
    t &= ~mask;
    t |= value & mask;
    writel (t, (volatile void *)(hi_uintptr_t)addr);
}

hi_s32 sys_hal_vo_bus_reset_sel(hi_bool reset)
{
    hi_u32 tmp = (reset == HI_TRUE) ? 1 : 0;
    hi_u32 bit = 0; /* 0: 0bit */

    hi_reg_set_bit(tmp, bit, IO_CRG_ADDRESS(CRG_PERCTL8336_ADDR));
    return HI_SUCCESS;
}

/* VO CFG CLK */
hi_s32 sys_hal_vo_cfg_clk_en(hi_bool clk_en)
{
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;
    hi_u32 bit = 7; /* 7: 7bit */

    hi_reg_set_bit(tmp, bit, IO_CRG_ADDRESS(CRG_PERCTL8336_ADDR));
    return HI_SUCCESS;
}

/* VO APB */
hi_s32 sys_hal_vo_apb_clk_en(hi_bool clk_en)
{
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;
    hi_u32 bit = 8; /* 8: 8bit */

    hi_reg_set_bit(tmp, bit, IO_CRG_ADDRESS(CRG_PERCTL8336_ADDR));
    return HI_SUCCESS;
}

/* VO AXI BUS CLK */
hi_s32 sys_hal_vo_bus_clk_en(hi_bool clk_en)
{
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;
    hi_u32 bit = 9; /* 9: 9bit */

    hi_reg_set_bit(tmp, bit, IO_CRG_ADDRESS(CRG_PERCTL8336_ADDR));
    return HI_SUCCESS;
}

hi_s32 sys_hal_vo_out_hd_phase_ctrl(hi_s32 vo_dev, hi_bool reverse)
{
    hi_u32 tmp = (reverse == HI_TRUE) ? 1 : 0;
    hi_u32 bit = 20; /* 20: 20bit */

    if ((vo_dev != 0) && (vo_dev != 1)) {
        return HI_FAILURE;
    }

    hi_reg_set_bit(tmp, bit, IO_CRG_ADDRESS(CRG_PERCTL8338_ADDR));
    return HI_SUCCESS;
}

hi_s32 sys_hal_vo_dly_tune(hi_s32 vo_dev, hi_u32 dly_tune)
{
    hi_u32 bit = 24; /* 24: 24bit */
    hi_u32 mask = 0x3f;

    if ((vo_dev != 0) && (vo_dev != 1)) {
        return HI_FAILURE;
    }

    hi_reg_write32(dly_tune << bit, mask << bit, IO_CRG_ADDRESS(CRG_PERCTL8338_ADDR));
    return HI_SUCCESS;
}

hi_s32 sys_hal_vo_out_hd_clk_div(hi_s32 vo_dev, hi_u32 clk_div)
{
    hi_u32 bit = 30; /* 30: 30bit */

    if ((vo_dev != 0) && (vo_dev != 1)) {
        return HI_FAILURE;
    }

    hi_reg_set_bit(clk_div, bit, IO_CRG_ADDRESS(CRG_PERCTL8338_ADDR));
    return HI_SUCCESS;
}

/* VO HD0 */
hi_s32 sys_hal_vo_hd0_div_mode(hi_s32 dev, hi_u32 hd0_div_mod)
{
    hi_u32 bit = 24; /* 24: 24bit */
    hi_u32 mask = 0x3;

    if (dev != 0) {
        return HI_FAILURE;
    }

    hi_reg_write32(hd0_div_mod << bit, mask << bit, IO_CRG_ADDRESS(CRG_PERCTL8340_ADDR));
    return HI_SUCCESS;
}

/* VO DHD0 HPLL, VI CMOS8 */
hi_s32 sys_hal_vo_hd_clk_sel(hi_s32 dev, hi_u32 clk_sel)
{
    hi_u32 bit = 12; /* 12: 12bit */
    hi_u32 mask = 0x1;

    if (dev != 0) {
        return HI_FAILURE;
    }

    hi_reg_write32(clk_sel << bit, mask << bit, IO_CRG_ADDRESS(CRG_PERCTL8340_ADDR));
    return HI_SUCCESS;
}

hi_s32 sys_hal_vo_core_clk_en(hi_s32 dev, hi_bool clk_en)
{
    hi_u32 bit = 5; /* 5: 5bit */
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;

    if ((dev == 0) || (dev == 1) || (dev == 2)) {  /* 2: DSD0 */
        hi_reg_set_bit(tmp, bit, IO_CRG_ADDRESS(CRG_PERCTL8340_ADDR));
        return HI_SUCCESS;
    }
    return HI_FAILURE;
}

/* VO HD SD */
hi_s32 sys_hal_vo_dev_clk_en(hi_s32 vo_dev, hi_bool clk_en)
{
    hi_u32 bit = 4; /* 4: 4bit */
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;

    if (vo_dev == 0) {
        hi_reg_set_bit(tmp, bit, IO_CRG_ADDRESS(CRG_PERCTL8340_ADDR));
    } else if (vo_dev == 1) {
        hi_reg_set_bit(tmp, bit, IO_CRG_ADDRESS(CRG_PERCTL8341_ADDR));
    } else if (vo_dev == 2) { /* 2: DSD0 */
        hi_reg_set_bit(tmp, bit, IO_CRG_ADDRESS(CRG_PERCTL8342_ADDR));
    } else {
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

/* VO HD1 */
hi_s32 sys_hal_vo_hd1_div_mode(hi_s32 dev, hi_u32 div_mod)
{
    hi_u32 bit = 24; /* 24: 24bit */
    hi_u32 mask = 0x3;

    if (dev != 1) {
        return HI_FAILURE;
    }

    hi_reg_write32(div_mod << bit, mask << bit, IO_CRG_ADDRESS(CRG_PERCTL8341_ADDR));
    return HI_SUCCESS;
}

hi_s32 sys_hal_vo_sd_div_mode(hi_s32 dev, hi_u32 div_mod)
{
    hi_u32 bit = 24; /* 24: 24bit */
    hi_u32 mask = 0x3;

    if (dev != 2) {  /* 2: DSD0 */
        return HI_FAILURE;
    }

    hi_reg_write32(div_mod << bit, mask << bit, IO_CRG_ADDRESS(CRG_PERCTL8342_ADDR));
    return HI_SUCCESS;
}

hi_s32 sys_hal_vo_sd_clk_sel(hi_s32 dev, hi_u32 clk_sel)
{
    hi_u32 bit = 12; /* 12: 12bit */
    hi_u32 mask = 0x1;

    if (dev != 2) { /* 2: DSD0 */
        return HI_FAILURE;
    }

    hi_reg_write32(clk_sel << bit, mask << bit, IO_CRG_ADDRESS(CRG_PERCTL8342_ADDR));
    return HI_SUCCESS;
}

/* BT.1120 */
hi_s32 sys_hal_vo_bt_clk_en(hi_s32 vo_dev, hi_bool bt_clk_en)
{
    hi_u32 bit_bt = 5; /* 5: 5bit */
    hi_u32 bit_bt_bp = 4; /* 4: 4bit */
    hi_u32 tmp = (bt_clk_en == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, bit_bt, IO_CRG_ADDRESS(CRG_PERCTL8348_ADDR));
    hi_reg_set_bit(tmp, bit_bt_bp, IO_CRG_ADDRESS(CRG_PERCTL8348_ADDR));
    return HI_SUCCESS;
}

/* BT.1120 */
hi_s32 sys_hal_vo_bt_clk_sel(hi_s32 vo_dev, hi_u32 bt_clk_ch_sel)
{
    hi_u32 bit = 12; /* 12: 12bit */
    hi_u32 mask = 0x3;

    if ((vo_dev == 0) || (vo_dev == 1)) {
        hi_reg_write32(bt_clk_ch_sel << bit, mask << bit, IO_CRG_ADDRESS(CRG_PERCTL8348_ADDR));
        return HI_SUCCESS;
    }
    return HI_FAILURE;
}

hi_s32 sys_hal_vo_vdac_phase_ctrl(hi_s32 vo_dev, hi_bool clk_reverse)
{
    hi_u32 bit_hd_dac_hs_vs = 21; /* 21: 21bit */
    hi_u32 bit_hd_dac = 20; /* 20: 20bit */
    hi_u32 bit_sd_dac = 20; /* 20: 20bit */
    hi_u32 tmp = (clk_reverse == HI_TRUE) ? 1 : 0;

    if ((vo_dev == 0) || (vo_dev == 1)) {
        hi_reg_set_bit(tmp, bit_hd_dac, IO_CRG_ADDRESS(CRG_PERCTL8349_ADDR));
        hi_reg_set_bit(tmp, bit_hd_dac_hs_vs, IO_CRG_ADDRESS(CRG_PERCTL8349_ADDR));
    } else if (vo_dev == 2) { /* 2: DSD0 */
        hi_reg_set_bit(tmp, bit_sd_dac, IO_CRG_ADDRESS(CRG_PERCTL8350_ADDR));
    }else {
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

hi_s32 sys_hal_vo_hd_vdac_clk_sel(hi_s32 vo_dev, hi_bool clk_sel)
{
    hi_u32 bit = 12; /* 12: 12bit */

    if ((vo_dev == 0) || (vo_dev == 1)) {
        hi_reg_set_bit(clk_sel, bit, IO_CRG_ADDRESS(CRG_PERCTL8349_ADDR));
        return HI_SUCCESS;
    }
    return HI_FAILURE;
}

hi_s32 sys_hal_vo_vdac_clk_en(hi_s32 vo_dev, hi_bool clk_en)
{
    hi_u32 bit = 4; /* 4: 4bit */
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;

    if ((vo_dev == 0) || (vo_dev == 1)) {
        hi_reg_set_bit(tmp, bit, IO_CRG_ADDRESS(CRG_PERCTL8349_ADDR));
    } else if (vo_dev == 2) { /* 2: DSD0 */
        hi_reg_set_bit(tmp, bit, IO_CRG_ADDRESS(CRG_PERCTL8350_ADDR));
    } else {
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

/* HDMI */
hi_s32 sys_hal_vo_hdmi_ssc_vdp_div(hi_s32 vo_dev, hi_u32 div_mode)
{
    hi_u32 bit = 24; /* 24: 24bit */
    hi_u32 mask = 0x1f;

    if ((vo_dev == 0) || (vo_dev == 1)) {
        hi_reg_write32(div_mode << bit, mask << bit, IO_CRG_ADDRESS(CRG_PERCTL8351_ADDR));
        return HI_SUCCESS;
    }
    return HI_FAILURE;
}

/* HDMI */
hi_s32 sys_hal_vo_hdmi_clk_en(hi_s32 vo_dev, hi_bool hdmi_clk_en)
{
    hi_u32 bit_pixel = 4; /* 4: 4bit */
    hi_u32 bit_vdp = 5; /* 5: 5bit */
    hi_u32 tmp = (hdmi_clk_en == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, bit_pixel, IO_CRG_ADDRESS(CRG_PERCTL8351_ADDR));
    hi_reg_set_bit(tmp, bit_vdp, IO_CRG_ADDRESS(CRG_PERCTL8351_ADDR));
    return HI_SUCCESS;
}

/* hdmi */
hi_s32 sys_hal_vo_hdmi_clk_sel(hi_s32 vo_dev, hi_u32 clk_ch_sel)
{
    hi_u32 bit = 20; /* 20: 20bit */
    hi_u32 mask = 0x1;

    if ((vo_dev == 0) || (vo_dev == 1)) {
        hi_reg_write32(clk_ch_sel << bit, mask << bit, IO_CRG_ADDRESS(CRG_PERCTL8351_ADDR));
        return HI_SUCCESS;
    }
    return HI_FAILURE;
}

hi_s32 sys_hal_vo_set_pll_postdiv2(hi_s32 pll, hi_u32 bits_set)
{
    hi_u32 bit = 28; /* 28: 28bit */
    hi_u32 mask = 0x7;

    if (pll == 0) {
        hi_reg_write32(bits_set << bit, mask << bit, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL224_ADDR));
    } else if (pll == 1) {
        hi_reg_write32(bits_set << bit, mask << bit, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL256_ADDR));
    } else {
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

hi_s32 sys_hal_vo_set_pll_postdiv1(hi_s32 pll, hi_u32 bits_set)
{
    hi_u32 bit = 24; /* 24: 24bit */
    hi_u32 mask = 0x7;

    if (pll == 0) {
        hi_reg_write32(bits_set << bit, mask << bit, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL224_ADDR));
    } else if (pll == 1) {
        hi_reg_write32(bits_set << bit, mask << bit, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL256_ADDR));
    } else {
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

hi_s32 sys_hal_vo_set_pll_frac(hi_s32 pll, hi_u32 bits_set)
{
    hi_u32 bit = 0;
    hi_u32 bit_dsmpd = 25; /* 25 */
    hi_u32 mask = 0xffffff;
    if (pll == 0) {
        hi_reg_write32(bits_set << bit, mask << bit, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL224_ADDR));

        if (bits_set == 0) {
            hi_reg_set_bit(1, bit_dsmpd, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL225_ADDR));
        } else {
            hi_reg_set_bit(0, bit_dsmpd, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL225_ADDR));
        }
    } else if (pll == 1) {
        hi_reg_write32(bits_set << bit, mask << bit, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL256_ADDR));

        if (bits_set == 0) {
            hi_reg_set_bit(1, bit_dsmpd, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL257_ADDR));
        } else {
            hi_reg_set_bit(0, bit_dsmpd, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL257_ADDR));
        }
    } else {
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

hi_s32 sys_hal_vo_set_pll_refdiv(hi_s32 pll, hi_u32 bits_set)
{
    hi_u32 bit = 12;    /* 12: 12bit */
    hi_u32 mask = 0x3f;

    if (pll == 0) {
        hi_reg_write32(bits_set << bit, mask << bit, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL225_ADDR));
    } else if (pll == 1) {
        hi_reg_write32(bits_set << bit, mask << bit, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL257_ADDR));
    } else {
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

hi_s32 sys_hal_vo_set_pll_fbdiv(hi_s32 pll, hi_u32 bits_set)
{
    hi_u32 bit = 0;     /* 0: 0bit */
    hi_u32 mask = 0xfff;

    if (pll == 0) {
        hi_reg_write32(bits_set << bit, mask << bit, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL225_ADDR));
    } else if (pll == 1) {
        hi_reg_write32(bits_set << bit, mask << bit, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL257_ADDR));
    } else {
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

hi_s32 sys_hal_vo_set_pll_power_ctrl(hi_s32 pll, hi_bool power_on)
{
    hi_u32 bit = 20; /* 20: 20bit */
    hi_u32 tmp = (power_on == HI_TRUE) ? 1 : 0;

    if (pll == 0) {
        hi_reg_set_bit(tmp, bit, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL225_ADDR));
    } else if (pll == 1) {
        hi_reg_set_bit(tmp, bit, IO_CRG_PLL_ADDRESS(CRG_PERCTL_PLL257_ADDR));
    } else {
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
