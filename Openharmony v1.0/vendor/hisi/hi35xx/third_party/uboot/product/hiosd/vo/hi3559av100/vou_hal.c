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

#include "vou_hal.h"
#include <asm/io.h>
#include "hi3559av100_vo.h"

#define IO_ADDRESS(x) (x)

#define HI_INVALID_LAYER (-1)

#define CRG_REGS_ADDR 0x12010000
#define CRG_REGS_SIZE 0X10000

#define CRG_PERCTL2_ADDR (0x0008 + CRG_REGS_ADDR)
#define CRG_PERCTL3_ADDR (0x000C + CRG_REGS_ADDR)
#define CRG_PERCTL4_ADDR (0x0010 + CRG_REGS_ADDR)
#define CRG_PERCTL5_ADDR (0x0014 + CRG_REGS_ADDR)
#define CRG_PERCTL6_ADDR (0x0018 + CRG_REGS_ADDR)
#define CRG_PERCTL7_ADDR (0x001c + CRG_REGS_ADDR)

#define CRG_PERCTL10_ADDR (0x0028 + CRG_REGS_ADDR)
#define CRG_PERCTL11_ADDR (0x002c + CRG_REGS_ADDR)

#define CRG_PERCTL18_ADDR (0x0048 + CRG_REGS_ADDR)
#define CRG_PERCTL19_ADDR (0x004c + CRG_REGS_ADDR)

#define CRG_PERCTL64_ADDR (0x0100 + CRG_REGS_ADDR) /* VDP low power CRG */
#define CRG_PERCTL72_ADDR (0x0120 + CRG_REGS_ADDR) /* VDP CRG */
#define CRG_PERCTL73_ADDR (0x0124 + CRG_REGS_ADDR) /* VDP CRG */
#define CRG_PERCTL15_ADDR (0x003C + CRG_REGS_ADDR)

#define HDMI_REGS_ADDR          0x201f0000L
#define HDMI_REGS_SIZE          0X10000
#define IO_CONFIG_ADDR          0x1F000000
#define IO_CONFIG_BT1120_CLK    (0x1084 + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA0  (0x1088 + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA1  (0x108C + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA2  (0x1090 + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA3  (0x1094 + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA4  (0x1098 + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA5  (0x109C + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA6  (0x10A0 + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA7  (0x10A4 + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA8  (0x10A8 + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA9  (0x10AC + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA10 (0x10B0 + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA11 (0x10B4 + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA12 (0x10B8 + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA13 (0x10BC + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA14 (0x10C0 + IO_CONFIG_ADDR)
#define IO_CONFIG_BT1120_DATA15 (0x10C4 + IO_CONFIG_ADDR)

#define IO_CONFIG_LCD_CLK    (0x10EC + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DE     (0x10A4 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_HSYNC  (0x109C + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_VSYNC  (0x10E4 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA0  (0x1098 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA1  (0x1094 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA2  (0x1090 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA3  (0x108C + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA4  (0x1088 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA5  (0x10C4 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA6  (0x10C0 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA7  (0x10A8 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA8  (0x10B8 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA9  (0x10B4 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA10 (0x10B0 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA11 (0x10AC + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA12 (0x1008 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA13 (0x100C + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA14 (0x1010 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA15 (0x1000 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA16 (0x1014 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA17 (0x1038 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA18 (0x101C + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA19 (0x1030 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA20 (0x1020 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA21 (0x1024 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA22 (0x1028 + IO_CONFIG_ADDR)
#define IO_CONFIG_LCD_DATA23 (0x102C + IO_CONFIG_ADDR)

volatile S_VDP_REGS_TYPE *g_vo_reg = HI_NULL;
volatile S_HIPP_REGS_TYPE *g_vo_hipp_reg = HI_NULL;

hi_void hal_vo_init(hi_void)
{
    g_vo_reg = (volatile S_VDP_REGS_TYPE *)IO_ADDRESS(VO_BASE_ADDR);
    g_vo_hipp_reg = (volatile S_HIPP_REGS_TYPE *)IO_ADDRESS(VO_BASE_ADDR);
}

hi_void hal_vo_exit(hi_void)
{
}

static inline void hi_reg_set_bit(unsigned long value, unsigned long offset,
                                  unsigned long addr)
{
    unsigned long t, mask;

    mask = 1 << offset;
    t = readl(addr);
    t &= ~mask;
    t |= (value << offset) & mask;
    writel(t, addr);
}

static inline void hi_reg_write32(unsigned long value, unsigned long mask,
                                  unsigned long addr)
{
    unsigned long t;

    t = readl(addr);
    t &= ~mask;
    t |= value & mask;
    writel(t, addr);
}

hi_void hal_write_reg(hi_u32 *address, hi_u32 value)
{
    *(volatile hi_u32 *)address = value;
    return;
}

hi_u32 hal_read_reg(const hi_u32 *address)
{
    return *(volatile hi_u32 *)(address);
}

hi_s32 sys_hal_vo_bt1120_chn_sel(hi_u32 clk_sel)
{
    hi_reg_set_bit(clk_sel, 25, IO_ADDRESS(CRG_PERCTL73_ADDR));  /* register 25bit */

    return 0;
}

hi_s32 sys_hal_vo_bt_bp_clk_en(hi_bool clk_en)
{
    volatile hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, 8, IO_ADDRESS(CRG_PERCTL73_ADDR));  /* register 8bit */

    return 0;
}

hi_s32 sys_hal_lcd_mclk_div(hi_u32 mclk_div)
{
    hi_reg_write32(mclk_div, 0x7ffffff, IO_ADDRESS(CRG_PERCTL72_ADDR));

    return 0;
}

hi_s32 sys_hal_vo_bt_clk_en(hi_bool clk_en)
{
    volatile hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, 9, IO_ADDRESS(CRG_PERCTL73_ADDR));  /* register 9bit */

    return 0;
}

hi_s32 sys_hal_sel_vo_clk(hi_u32 clk_sel)
{
    hi_reg_write32(clk_sel << 14, 0x3 << 14, IO_ADDRESS(CRG_PERCTL73_ADDR));  /* register 14bit to 0x3 */
    return 0;
}

hi_s32 sys_hal_vo_vdp_low_power(hi_bool clk_en)
{
    volatile hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, 13, IO_ADDRESS(CRG_PERCTL64_ADDR)); /* register 13bit */

    return 0;
}
hi_s32 sys_hal_vo_bus_reset_sel(hi_bool reset)
{
    volatile hi_u32 tmp = (reset == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, 0, IO_ADDRESS(CRG_PERCTL73_ADDR));

    return 0;
}

hi_s32 sys_hal_vo_lcd_clk_en(hi_bool clk_en)
{
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, 27, IO_ADDRESS(CRG_PERCTL72_ADDR)); /* register 27bit */

    return 0;
}

hi_s32 sys_hal_lcd_data_mode(hi_u32 data_mode)
{
    hi_reg_write32(data_mode << 26, 0x7 << 26, IO_ADDRESS(0x04528004));  /* register 26bit to 0x7 */

    return 0;
}

hi_s32 sys_hal_vo_dev_clk_en(hi_s32 vo_dev, hi_bool clk_en)
{
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;

    if (vo_dev == 0) {
        hi_reg_set_bit(tmp, 4, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 4bit */
        hi_reg_set_bit(tmp, 5, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 5bit */
        hi_reg_set_bit(tmp, 6, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 6bit */
    } else if (vo_dev == 1) {
        hi_reg_set_bit(tmp, 4, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 4bit */
        hi_reg_set_bit(tmp, 5, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 5bit */
        hi_reg_set_bit(tmp, 7, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 7bit */
    } else {
        return -1;
    }

    return 0;
}

hi_s32 sys_hal_vo_hdmi_clk_en(hi_s32 vo_dev, hi_bool hdmi_clk_en)
{
    hi_u32 tmp = (hdmi_clk_en == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, 27, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 27bit */
    hi_reg_set_bit(tmp, 10, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 10bit */

    return 0;
}

hi_s32 sys_hal_vo_mipi_tx_chn_sel(hi_u32 clk_sel)
{
    hi_reg_set_bit(clk_sel, 26, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 26bit */
    hi_reg_set_bit(clk_sel, 30, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 30bit */

    return 0;
}

hi_s32 sys_hal_vo_hd_out_pctrl(hi_bool clk_reverse)
{
    hi_u32 tmp = (clk_reverse == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, 29, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 29bit */

    return 0;
}

hi_s32 sys_hal_vo_mipi_clk_en(hi_s32 vo_dev, hi_bool mipi_clk_en)
{
    hi_u32 tmp = (mipi_clk_en == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, 11, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 11bit */

    return 0;
}
hi_s32 sys_hal_vo_hd0_div_mode(hi_s32 dev, hi_u32 hd0_div_mod)
{
    if ((dev == 0) || (dev == 1)) {
        hi_reg_write32(hd0_div_mod << 12, 0x3 << 12, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 12bit to 0x3 */
    } else {
        return -1;
    }

    return 0;
}

hi_s32 sys_hal_set_vo_pll_frac(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 0, 0xffffff << 0, IO_ADDRESS(CRG_PERCTL10_ADDR));

        if (bits_set == 0) {
            hi_reg_set_bit(1, 24, IO_ADDRESS(CRG_PERCTL11_ADDR)); /* register 24bit to 1 */
        } else {
            hi_reg_set_bit(0, 24, IO_ADDRESS(CRG_PERCTL11_ADDR)); /* register 24bit to 0 */
        }
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 0, 0xffffff << 0, IO_ADDRESS(CRG_PERCTL10_ADDR));

        if (bits_set == 0) {
            hi_reg_set_bit(1, 24, IO_ADDRESS(CRG_PERCTL11_ADDR)); /* register 24bit to 1 */
        } else {
            hi_reg_set_bit(0, 24, IO_ADDRESS(CRG_PERCTL11_ADDR)); /* register 24bit to 0 */
        }
    } else {
        return -1;
    }
    return 0;
}

hi_s32 sys_hal_set_vo_pll_postdiv1(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 24, 0x7 << 24, IO_ADDRESS(CRG_PERCTL10_ADDR)); /* register 24bit to 0x7 */
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 24, 0x7 << 24, IO_ADDRESS(CRG_PERCTL10_ADDR)); /* register 24bit to 0x7 */
    } else {
        return -1;
    }
    return 0;
}

hi_s32 sys_hal_set_vo_pll_postdiv2(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 28, 0x7 << 28, IO_ADDRESS(CRG_PERCTL10_ADDR)); /* register 28bit to 0x7 */
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 28, 0x7 << 28, IO_ADDRESS(CRG_PERCTL10_ADDR)); /* register 28bit to 0x7 */
    } else {
        return -1;
    }
    return 0;
}
hi_s32 sys_hal_set_vo_pll_refdiv(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 12, 0x3f << 12, IO_ADDRESS(CRG_PERCTL11_ADDR));  /* register 12bit to 0x3f */
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 12, 0x3f << 12, IO_ADDRESS(CRG_PERCTL11_ADDR)); /* register 12bit to 0x3f */
    } else {
        return -1;
    }
    return 0;
}
hi_s32 sys_hal_set_vo_pll_fbdiv(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 0, 0xfff << 0, IO_ADDRESS(CRG_PERCTL11_ADDR));
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 0, 0xfff << 0, IO_ADDRESS(CRG_PERCTL11_ADDR));
    } else {
        return -1;
    }
    return 0;
}

hi_s32 sys_hal_set_vo_s_pll_frac(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 0, 0xffffff << 0, IO_ADDRESS(CRG_PERCTL18_ADDR));

        if (bits_set == 0) {
            hi_reg_set_bit(1, 24, IO_ADDRESS(CRG_PERCTL19_ADDR));  /* register 24bit to 1 */
        } else {
            hi_reg_set_bit(0, 24, IO_ADDRESS(CRG_PERCTL19_ADDR)); /* register 24bit to 0 */
        }
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 0, 0xffffff << 0, IO_ADDRESS(CRG_PERCTL18_ADDR));

        if (bits_set == 0) {
            hi_reg_set_bit(1, 24, IO_ADDRESS(CRG_PERCTL19_ADDR)); /* register 24bit to 1 */
        } else {
            hi_reg_set_bit(0, 24, IO_ADDRESS(CRG_PERCTL19_ADDR)); /* register 24bit to 0 */
        }
    } else {
        return -1;
    }
    return 0;
}

hi_s32 sys_hal_set_vo_s_pll_postdiv1(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 24, 0x7 << 24, IO_ADDRESS(CRG_PERCTL18_ADDR)); /* register 24bit to 0x7 */
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 24, 0x7 << 24, IO_ADDRESS(CRG_PERCTL18_ADDR)); /* register 24bit to 0x7 */
    } else {
        return -1;
    }
    return 0;
}

hi_s32 sys_hal_set_vo_s_pll_postdiv2(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 28, 0x7 << 28, IO_ADDRESS(CRG_PERCTL18_ADDR)); /* register 28bit to 0x7 */
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 28, 0x7 << 28, IO_ADDRESS(CRG_PERCTL18_ADDR)); /* register 28bit to 0x7 */
    } else {
        return -1;
    }
    return 0;
}
hi_s32 sys_hal_set_vo_s_pll_refdiv(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 12, 0x3f << 12, IO_ADDRESS(CRG_PERCTL19_ADDR)); /* register 12bit to 0x3f */
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 12, 0x3f << 12, IO_ADDRESS(CRG_PERCTL19_ADDR)); /* register 12bit to 0x3f */
    } else {
        return -1;
    }
    return 0;
}
hi_s32 sys_hal_set_vo_s_pll_fbdiv(hi_s32 pll, hi_u32 bits_set)
{
    if (pll == 0) {
        hi_reg_write32(bits_set << 0, 0xfff << 0, IO_ADDRESS(CRG_PERCTL19_ADDR));
    } else if (pll == 1) {
        hi_reg_write32(bits_set << 0, 0xfff << 0, IO_ADDRESS(CRG_PERCTL19_ADDR));
    } else {
        return -1;
    }
    return 0;
}

hi_s32 sys_hal_vo_out_clk_sel(hi_s32 dev, hi_u32 clk_sel)
{
    if ((dev == 0) || (dev == 1)) {
        hi_reg_write32(clk_sel << 18, 0x7 << 18, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 18bit to 0x7 */
    } else {
        return -1;
    }

    return 0;
}

/* VO DHD clk sel */
hi_s32 sys_hal_vo_hd_clk_sel(hi_s32 dev, hi_u32 clk_sel)
{
    if (dev == 0) {
        hi_reg_write32(clk_sel << 16, 0x3 << 16, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 16bit to 0x3 */
    } else {
        return -1;
    }

    return 0;
}

hi_s32 sys_hal_vo_hd1_div_mode(hi_s32 dev, hi_u32 hd1_div_mod)
{
    if ((dev == 0) || (dev == 1)) {
        hi_reg_write32(hd1_div_mod << 14, 0x3 << 14, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 14bit to 0x3 */
    } else {
        return -1;
    }

    return 0;
}

hi_s32 sys_hal_vo_cfg_clk_en(hi_s32 dev, hi_bool clk_en)
{
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;

    if (dev == 0) {
        hi_reg_set_bit(tmp, 3, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 3bit */
    } else {
        return -1;
    }

    return 0;
}

hi_s32 sys_hal_vo_core_clk_en(hi_s32 dev, hi_bool clk_en)
{
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;

    if (dev == 0) {
        hi_reg_set_bit(tmp, 5, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 5bit */
    } else {
        return -1;
    }

    return 0;
}

/* VO APB clk en */
hi_s32 sys_hal_vo_apb_clk_en(hi_s32 dev, hi_bool clk_en)
{
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;

    if (dev == 0) {
        hi_reg_set_bit(tmp, 1, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 1bit */
    } else {
        return -1;
    }

    return 0;
}

/* VO AXI BUS CLK */
hi_s32 sys_hal_vo_bus_clk_en(hi_bool clk_en)
{
    hi_u32 tmp = (clk_en == HI_TRUE) ? 1 : 0;
    hi_reg_set_bit(tmp, 2, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 2bit */

    return 0;
}

hi_s32 sys_hal_vo_mipi_tx_clk_en(hi_s32 vo_dev, hi_bool mipi_clk_en)
{
    hi_u32 tmp = (mipi_clk_en == HI_TRUE) ? 1 : 0;

    hi_reg_set_bit(tmp, 28, IO_ADDRESS(CRG_PERCTL73_ADDR)); /* register 28bit */

    return 0;
}

hi_void hal_sys_control(hi_void)
{
    volatile U_VOCTRL VOCTRL;

    /* outstand */
    VOCTRL.u32 = g_vo_reg->VOCTRL.u32;
    VOCTRL.u32 = 0x80000000; /* 0x80000000 vo contrl */
    g_vo_reg->VOCTRL.u32 = VOCTRL.u32;
}

hi_u32 inline hal_get_xdc_buma(hi_s32 value)
{
    hi_u32 abs_value = value << 2;  /* 2 to cal abs value */

    if (value >= 0) {
        return abs_value & 0x7ff; /* 0x7ff to get the low value */
    } else {
        abs_value = (~((hi_u32)((-1) * (hi_s32)abs_value)) + 1); /* -1 1 to get the bit */
        abs_value = ((abs_value & 0x7ff) | 0x400); /* 0x7ff 0x400 to get the bits */
        return abs_value;
    }
}

hi_u32 inline hal_get_odc_buma_new(hi_s32 value)
{
    hi_u32 abs_value = value << 2; /* 2 to cal abs value */

    if (value >= 0) {
        return abs_value & 0xfff; /* 0xfff to get the low value */
    } else {
        abs_value = (~((hi_u32)((-1) * (hi_s32)abs_value)) + 1); /* -1 1 to get the bit */
        abs_value = ((abs_value & 0xfff) | 0x1000); /* 0xfff 0x1000 to get the bits */
        return abs_value;
    }
}

hi_u32 inline hal_conver_csc_coef(hi_s32 value)
{
    hi_s32 result = ((value << 10) / 1000); /* 10 / 1000 to cal resule */

    if (result < 0) {
        result = (~((-1) * result) + 1);  /* -1 1 to get the bit */

        /* 5.8 format */
        result = ((result & 0x7fff) | 0x4000); /* 0x7ff 0x4000 to get the bits */
    } else {
        result = result & 0x7fff; /* 0x7ff to get the low value */
    }

    return (hi_u32)result;
}

hi_u32 inline hal_conver_csc_coef_new(hi_s32 value)
{
    hi_s32 result = ((value << 10) / 1000); /* 10 / 1000 to cal resule */

    if (result < 0) {
        result = (~((-1) * result) + 1); /* -1 1 to get the bit */

        result = ((result & 0xffff) | 0x8000); /* 0xffff 0x8000 to get the bits */
    } else {
        result = result & 0xffff; /* 0xffff to get low bits */
    }

    return (hi_u32)result;
}

hi_ulong vo_get_abs_addr(hal_disp_layer layer, hi_ulong reg)
{
    hi_ulong reg_abs_addr;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1: {
            reg_abs_addr = (reg) + (layer - HAL_DISP_LAYER_VHD0) * VHD_REGS_LEN;
            break;
        }

        case HAL_DISP_LAYER_GFX0:
        case HAL_DISP_LAYER_GFX1: {
            reg_abs_addr = (reg) + (layer - HAL_DISP_LAYER_GFX0) * GFX_REGS_LEN;
            break;
        }

        case HAL_DISP_LAYER_WBC:
            reg_abs_addr = (reg);
            break;

        default: {
            printf("error channel id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return 0;
        }
    }

    return reg_abs_addr;
}

hi_ulong vo_get_chn_abs_addr(hal_disp_outputchannel chan, hi_ulong reg)
{
    volatile hi_ulong reg_abs_addr;

    switch (chan) {
        case HAL_DISP_CHANNEL_DHD0:
        case HAL_DISP_CHANNEL_DHD1: {
            reg_abs_addr = reg + (chan - HAL_DISP_CHANNEL_DHD0) * DHD_REGS_LEN;
            break;
        }

        default: {
            printf("error channel id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return 0;
        }
    }

    return reg_abs_addr;
}

hi_ulong vo_get_hdmi_or_mipi_intf_abs_addr(hal_disp_intf intf, hi_ulong reg)
{
    volatile hi_ulong reg_abs_addr;

    switch (intf) {
        case HAL_DISP_INTF_HDMI: {
            reg_abs_addr = reg;
            break;
        }

        case HAL_DISP_INTF_MIPI: {
            reg_abs_addr = reg + 0x80; /* 0x80 register offset */
            break;
        }
        default: {
            printf("error intf id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return 0;
        }
    }

    return reg_abs_addr;
}

/* for get intf abs addr */
hi_ulong vo_get_intf_abs_addr(hal_disp_intf intf, hi_ulong reg)
{
    volatile hi_ulong reg_abs_addr;

    switch (intf) {
        case HAL_DISP_INTF_HDMI: {
            reg_abs_addr = reg;
            break;
        }

        case HAL_DISP_INTF_MIPI: {
            reg_abs_addr = reg + 0x80; /* 0x80 register offset */
            break;
        }

        case HAL_DISP_INTF_BT656:
        case HAL_DISP_INTF_BT1120: {
            reg_abs_addr = reg + 1 * INTF_REGS_LEN; /* 1 register offset */
            break;
        }

        case HAL_DISP_INTF_LCD:
        case HAL_DISP_INTF_LCD_6BIT:
        case HAL_DISP_INTF_LCD_8BIT:
        case HAL_DISP_INTF_LCD_16BIT:
        case HAL_DISP_INTF_LCD_18BIT:
        case HAL_DISP_INTF_LCD_24BIT: {
            reg_abs_addr = reg + 2 * INTF_REGS_LEN;  /* 2 to get addr */
            break;
        }

        default: {
            printf("error intf id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return 0;
        }
    }
    return reg_abs_addr;
}

hi_ulong vo_get_vid_abs_addr(hal_disp_layer layer, hi_ulong reg)
{
    volatile hi_ulong reg_abs_addr;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1: {
            reg_abs_addr = reg + (layer - HAL_DISP_LAYER_VHD0) * VID_REGS_LEN;
            break;
        }

        case HAL_DISP_LAYER_WBC:
            reg_abs_addr = reg;
            break;

        default: {
            printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return 0;
        }
    }

    return reg_abs_addr;
}

hi_ulong vo_get_gfx_abs_addr(hal_disp_layer layer, hi_ulong reg)
{
    volatile hi_ulong reg_abs_addr;

    switch (layer) {
        case HAL_DISP_LAYER_GFX0:
        case HAL_DISP_LAYER_GFX1: {
            reg_abs_addr = reg + (layer - HAL_DISP_LAYER_GFX0) * GRF_REGS_LEN;
            break;
        }
        default: {
            printf("error layer id found in FUNC:%s,LINE:%d\n", __FUNCTION__, __LINE__);
            return 0;
        }
    }

    return reg_abs_addr;
}

hi_void hal_sys_set_outstanding(hi_void)
{
    return;
}

/* AXI master select */
hi_void hal_sys_set_axi_master(hi_void)
{
    return;
}

hi_void hal_sys_set_rd_bus_id(hi_u32 mode)
{
    return;
}

hi_bool hal_disp_set_lcd_serial_perd(hi_u32 serial_perd)
{
    U_INTF_LCD_CTRL INTF_LCD_CTRL;
    volatile hi_ulong addr_reg;

    addr_reg   = vo_get_intf_abs_addr(HAL_DISP_INTF_LCD_8BIT, (hi_uintptr_t)&(g_vo_reg->INTF_HDMI_CTRL.u32));
    INTF_LCD_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);

    INTF_LCD_CTRL.bits.lcd_serial_perd = serial_perd;

    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, INTF_LCD_CTRL.u32);
    return HI_TRUE;
}

hi_bool hal_disp_set_intf_enable(hal_disp_outputchannel chan, hi_bool intf)
{
    volatile U_DHD0_CTRL DHD0_CTRL;
    volatile hi_ulong addr_reg;

    switch (chan) {
        case HAL_DISP_CHANNEL_DHD0:
        case HAL_DISP_CHANNEL_DHD1: {
            addr_reg = vo_get_chn_abs_addr(chan, (hi_uintptr_t)&(g_vo_reg->DHD0_CTRL.u32));
            DHD0_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            DHD0_CTRL.bits.intf_en = intf;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, DHD0_CTRL.u32);

            break;
        }

        default: {
            printf("error channel id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

static hi_void hal_disp_set_bt_ctrl(hal_disp_intf intf, const hi_u32 *ctrl_info)
{
    U_INTF_BT_CTRL INTF_BT_CTRL;
    U_INTF_BT_CTRL *bt_ctrl = HI_NULL;

    volatile hi_ulong addr_reg;

    bt_ctrl = (U_INTF_BT_CTRL *)ctrl_info;
    addr_reg = vo_get_intf_abs_addr(intf, (hi_uintptr_t)&(g_vo_reg->INTF_HDMI_CTRL.u32));
    INTF_BT_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    INTF_BT_CTRL.bits.hdmi_mode = bt_ctrl->bits.hdmi_mode;
    INTF_BT_CTRL.bits.lcd_serial_mode = bt_ctrl->bits.lcd_serial_mode;
    INTF_BT_CTRL.bits.lcd_serial_perd = bt_ctrl->bits.lcd_serial_perd;
    INTF_BT_CTRL.bits.lcd_parallel_order = bt_ctrl->bits.lcd_parallel_order;
    INTF_BT_CTRL.bits.lcd_data_inv = bt_ctrl->bits.lcd_data_inv;
    INTF_BT_CTRL.bits.lcd_parallel_mode = bt_ctrl->bits.lcd_parallel_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, INTF_BT_CTRL.u32);
}

static hi_void hal_disp_set_lcd_ctrl(hal_disp_intf intf, const hi_u32 *ctrl_info)
{
    U_INTF_LCD_CTRL INTF_LCD_CTRL;
    U_INTF_LCD_CTRL *lcd_ctrl = HI_NULL;

    volatile hi_ulong addr_reg;

    lcd_ctrl = (U_INTF_LCD_CTRL *)ctrl_info;
    addr_reg = vo_get_intf_abs_addr(intf, (hi_uintptr_t)&(g_vo_reg->INTF_HDMI_CTRL.u32));
    INTF_LCD_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    INTF_LCD_CTRL.bits.hdmi_mode = lcd_ctrl->bits.hdmi_mode;
    INTF_LCD_CTRL.bits.lcd_serial_mode = lcd_ctrl->bits.lcd_serial_mode;
    INTF_LCD_CTRL.bits.lcd_serial_perd = lcd_ctrl->bits.lcd_serial_perd;
    INTF_LCD_CTRL.bits.lcd_parallel_order = lcd_ctrl->bits.lcd_parallel_order;
    INTF_LCD_CTRL.bits.lcd_data_inv = lcd_ctrl->bits.lcd_data_inv;
    INTF_LCD_CTRL.bits.lcd_parallel_mode = lcd_ctrl->bits.lcd_parallel_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, INTF_LCD_CTRL.u32);
}

static hi_void hal_disp_set_hdmi_ctrl(hal_disp_intf intf, const hi_u32 *ctrl_info)
{
    U_INTF_HDMI_CTRL INTF_HDMI_CTRL;
    U_INTF_HDMI_CTRL *hdmi_ctrl = HI_NULL;

    volatile hi_ulong addr_reg;

    hdmi_ctrl = (U_INTF_HDMI_CTRL *)ctrl_info;
    addr_reg = vo_get_hdmi_or_mipi_intf_abs_addr(intf, (hi_uintptr_t)&(g_vo_reg->INTF_HDMI_CTRL.u32));
    INTF_HDMI_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    INTF_HDMI_CTRL.bits.hdmi_mode = hdmi_ctrl->bits.hdmi_mode;
    INTF_HDMI_CTRL.bits.intf_420_mode = hdmi_ctrl->bits.intf_420_mode;
    INTF_HDMI_CTRL.bits.intf_420_en = hdmi_ctrl->bits.intf_420_en;
    INTF_HDMI_CTRL.bits.intf_422_en = hdmi_ctrl->bits.intf_422_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, INTF_HDMI_CTRL.u32);
}

hi_bool hal_disp_set_intf_ctrl(hal_disp_intf intf, const hi_u32 *ctrl_info)
{
    if ((intf == VO_INTF_BT1120) ||
        (intf == VO_INTF_BT656)) {
        hal_disp_set_bt_ctrl(intf, ctrl_info);
    } else if ((intf == VO_INTF_LCD) ||
               (intf == VO_INTF_LCD_6BIT) ||
               (intf == VO_INTF_LCD_8BIT) ||
               (intf == VO_INTF_LCD_16BIT) ||
               (intf == VO_INTF_LCD_18BIT) ||
               (intf == VO_INTF_LCD_24BIT)) {
        hal_disp_set_lcd_ctrl(intf, ctrl_info);
    } else if ((intf == VO_INTF_HDMI) ||
               (intf == VO_INTF_MIPI)) {
        hal_disp_set_hdmi_ctrl(intf, ctrl_info);
    } else {
        printf("error interface type found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

static hi_void hal_disp_set_intf_horiz_sync(hal_disp_outputchannel chan,
                                            const hal_disp_syncinfo *sync_info)
{
    volatile U_DHD0_HSYNC1 DHD0_HSYNC1;
    volatile U_DHD0_HSYNC2 DHD0_HSYNC2;

    volatile hi_ulong addr_reg;

    addr_reg = vo_get_chn_abs_addr(chan, (hi_uintptr_t)&(g_vo_reg->DHD0_HSYNC1.u32));
    DHD0_HSYNC1.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    DHD0_HSYNC1.bits.hact = sync_info->hact - 1;
    DHD0_HSYNC1.bits.hbb = (sync_info->hbb) - 1;
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, DHD0_HSYNC1.u32);

    addr_reg = vo_get_chn_abs_addr(chan, (hi_uintptr_t)&(g_vo_reg->DHD0_HSYNC2.u32));
    DHD0_HSYNC2.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    DHD0_HSYNC2.bits.hmid = (sync_info->hmid == 0) ? 0 : sync_info->hmid - 1;
    DHD0_HSYNC2.bits.hfb = (sync_info->hfb) - 1;
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, DHD0_HSYNC2.u32);
}

static hi_void hal_disp_set_intf_vertical_sync(hal_disp_outputchannel chan,
                                               const hal_disp_syncinfo *sync_info)
{
    volatile U_DHD0_VSYNC1 DHD0_VSYNC1;
    volatile U_DHD0_VSYNC2 DHD0_VSYNC2;
    volatile U_DHD0_VPLUS1 DHD0_VPLUS1;
    volatile U_DHD0_VPLUS2 DHD0_VPLUS2;

    volatile hi_ulong addr_reg;

    /* register is the value -1 */
    addr_reg = vo_get_chn_abs_addr(chan, (hi_uintptr_t)&(g_vo_reg->DHD0_VSYNC1.u32));
    DHD0_VSYNC1.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    DHD0_VSYNC1.bits.vact = sync_info->vact - 1;
    DHD0_VSYNC1.bits.vbb = sync_info->vbb - 1;
    hal_write_reg ((hi_u32*)(hi_uintptr_t)addr_reg, DHD0_VSYNC1.u32);

    addr_reg = vo_get_chn_abs_addr(chan, (hi_uintptr_t)&(g_vo_reg->DHD0_VSYNC2.u32));
    DHD0_VSYNC2.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    DHD0_VSYNC2.bits.vfb = sync_info->vfb - 1;
    hal_write_reg ((hi_u32*)(hi_uintptr_t)addr_reg, DHD0_VSYNC2.u32);

    addr_reg = vo_get_chn_abs_addr(chan, (hi_uintptr_t)&(g_vo_reg->DHD0_VPLUS1.u32));
    DHD0_VPLUS1.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    DHD0_VPLUS1.bits.bvact = sync_info->bvact - 1;
    DHD0_VPLUS1.bits.bvbb = sync_info->bvbb - 1;
    hal_write_reg ((hi_u32*)(hi_uintptr_t)addr_reg, DHD0_VPLUS1.u32);

    addr_reg = vo_get_chn_abs_addr(chan, (hi_uintptr_t)&(g_vo_reg->DHD0_VPLUS2.u32));
    DHD0_VPLUS2.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    DHD0_VPLUS2.bits.bvfb = sync_info->bvfb - 1;
    hal_write_reg ((hi_u32*)(hi_uintptr_t)addr_reg, DHD0_VPLUS2.u32);

    return;
}

hi_bool hal_disp_set_intf_sync(hal_disp_outputchannel chan,
                               const hal_disp_syncinfo *sync_info)
{
    volatile U_DHD0_CTRL DHD0_CTRL;
    volatile U_DHD0_PWR DHD0_PWR;

    volatile hi_ulong addr_reg;

    switch (chan) {
        case HAL_DISP_CHANNEL_DHD0:
        case HAL_DISP_CHANNEL_DHD1: {
            addr_reg = vo_get_chn_abs_addr(chan, (hi_uintptr_t)&(g_vo_reg->DHD0_CTRL.u32));
            DHD0_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            DHD0_CTRL.bits.iop = sync_info->iop;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, DHD0_CTRL.u32);

            hal_disp_set_intf_horiz_sync(chan, sync_info);

            hal_disp_set_intf_vertical_sync(chan, sync_info);

            /* register is the value -1 */
            addr_reg = vo_get_chn_abs_addr(chan, (hi_uintptr_t)&(g_vo_reg->DHD0_PWR.u32));
            DHD0_PWR.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            DHD0_PWR.bits.hpw = sync_info->hpw - 1;
            DHD0_PWR.bits.vpw = sync_info->vpw - 1;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, DHD0_PWR.u32);

            break;
        }

        default: {
            printf("error channel id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_disp_set_dev_multi_chn_en(hal_disp_outputchannel chn, hal_multi_chn multi_chn_en)
{
    volatile U_DHD0_PWR DHD0_PWR;
    volatile hi_ulong addr_reg;
    addr_reg = vo_get_chn_abs_addr(chn, (hi_uintptr_t)&(g_vo_reg->DHD0_PWR.u32));
    DHD0_PWR.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    DHD0_PWR.bits.multichn_en = multi_chn_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, DHD0_PWR.u32);

    return HI_TRUE;
}

hi_bool hal_disp_set_intf_sync_inv(hal_disp_intf intf, const hal_disp_syncinv *inv)
{
    volatile U_INTF_HDMI_SYNC_INV INTF_HDMI_SYNC_INV;
    volatile hi_ulong addr_reg;
    addr_reg = vo_get_intf_abs_addr(intf, (hi_uintptr_t)&(g_vo_reg->INTF_HDMI_SYNC_INV.u32));
    INTF_HDMI_SYNC_INV.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    INTF_HDMI_SYNC_INV.bits.f_inv = inv->f_inv;
    INTF_HDMI_SYNC_INV.bits.vs_inv = inv->vs_inv;
    INTF_HDMI_SYNC_INV.bits.hs_inv = inv->hs_inv;
    INTF_HDMI_SYNC_INV.bits.dv_inv = inv->dv_inv;
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, INTF_HDMI_SYNC_INV.u32);

    return HI_TRUE;
}

hi_bool hal_disp_set_intf_mux_default_sel(hi_void)
{
    return HI_TRUE;
}

static hi_bool hal_disp_set_uhd_intf_mux_sel(hal_disp_intf intf)
{
    volatile U_VO_MUX VO_MUX;
    volatile hi_ulong addr_reg;

    addr_reg = (hi_uintptr_t)&(g_vo_reg->VO_MUX.u32);
    VO_MUX.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    /* the number is the register config */
    switch (intf) {
        case HAL_DISP_INTF_BT1120: {
            VO_MUX.bits.digital_sel = 0;
            VO_MUX.bits.bt_sel = 0;
            break;
        }

        case HAL_DISP_INTF_BT656: {
            VO_MUX.bits.digital_sel = 1;
            VO_MUX.bits.bt_sel = 0;
            break;
        }

        case HAL_DISP_INTF_MIPI: {
            VO_MUX.bits.digital_sel = 0;
            VO_MUX.bits.mipi_sel = 0;
            break;
        }

        case HAL_DISP_INTF_LCD:
        case HAL_DISP_INTF_LCD_6BIT:
        case HAL_DISP_INTF_LCD_8BIT:
        case HAL_DISP_INTF_LCD_16BIT:
        case HAL_DISP_INTF_LCD_18BIT:
        case HAL_DISP_INTF_LCD_24BIT: {
            VO_MUX.bits.digital_sel = 2; /* 2 register config */
            VO_MUX.bits.lcd_sel = 0;
            break;
        }

        default: {
            printf("error interface id found in %s: L%d \n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->VO_MUX.u32), VO_MUX.u32);

    return HI_TRUE;
}

static hi_bool hal_disp_set_hd_intf_mux_sel(hal_disp_intf intf)
{
    volatile U_VO_MUX VO_MUX;
    volatile hi_ulong addr_reg;

    addr_reg = (hi_uintptr_t)&(g_vo_reg->VO_MUX.u32);
    VO_MUX.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);

    /* the number is the register config */
    switch (intf) {
        case HAL_DISP_INTF_BT1120: {
            VO_MUX.bits.digital_sel = 0;
            VO_MUX.bits.bt_sel = 1;
            break;
        }

        case HAL_DISP_INTF_BT656: {
            VO_MUX.bits.digital_sel = 1;
            VO_MUX.bits.bt_sel = 1;
            break;
        }

        case HAL_DISP_INTF_MIPI: {
            VO_MUX.bits.digital_sel = 0;
            VO_MUX.bits.mipi_sel = 1;
            break;
        }

        case HAL_DISP_INTF_LCD:
        case HAL_DISP_INTF_LCD_6BIT:
        case HAL_DISP_INTF_LCD_8BIT:
        case HAL_DISP_INTF_LCD_16BIT:
        case HAL_DISP_INTF_LCD_24BIT: {
            VO_MUX.bits.digital_sel = 2;  /* 2 register config */
            VO_MUX.bits.lcd_sel = 1;
            break;
        }

        default: {
            printf("error interface id found in %s: L%d \n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->VO_MUX.u32), VO_MUX.u32);

    return HI_TRUE;
}

hi_bool hal_disp_set_intf_mux_sel(hal_disp_outputchannel chan, hal_disp_intf intf)
{
    hi_bool ret = HI_FALSE;

    switch (chan) {
        case HAL_DISP_CHANNEL_DHD0: {
            ret = hal_disp_set_uhd_intf_mux_sel(intf);
            if (ret == HI_FALSE) {
                return HI_FALSE;
            }
            break;
        }

        case HAL_DISP_CHANNEL_DHD1: {
            ret = hal_disp_set_hd_intf_mux_sel(intf);
            if (ret == HI_FALSE) {
                return HI_FALSE;
            }
            break;
        }

        default: {
            printf("error channel id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_disp_set_intf_clip(hal_disp_intf intf,
                               hi_bool clip,
                               const hal_disp_clip *clip_data)
{
    volatile U_BT_CLIP0_L BT_CLIP0_L;
    volatile U_BT_CLIP0_H BT_CLIP0_H;

    volatile hi_ulong addr_reg;

    addr_reg = (hi_uintptr_t)&(g_vo_reg->BT_CLIP0_L.u32);
    BT_CLIP0_L.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    BT_CLIP0_L.bits.clip_en = clip;
    BT_CLIP0_L.bits.clip_cl2 = clip_data->clip_low_y;
    BT_CLIP0_L.bits.clip_cl1 = clip_data->clip_low_cb;
    BT_CLIP0_L.bits.clip_cl0 = clip_data->clip_low_cr;
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, BT_CLIP0_L.u32);

    addr_reg = (hi_uintptr_t)&(g_vo_reg->BT_CLIP0_H.u32);
    BT_CLIP0_H.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    BT_CLIP0_H.bits.clip_ch2 = clip_data->clip_high_y;
    BT_CLIP0_H.bits.clip_ch1 = clip_data->clip_high_cb;
    BT_CLIP0_H.bits.clip_ch0 = clip_data->clip_high_cr;
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, BT_CLIP0_H.u32);

    return HI_TRUE;
}

hi_bool hal_disp_set_vt_thd_mode(hal_disp_outputchannel chan, hi_u32 field_mode)
{
    volatile U_DHD0_VTTHD DHD0_VTTHD;
    volatile U_WBC_DHD0_CTRL WBC_DHD0_CTRL;
    volatile hi_ulong addr_reg;

    switch (chan) {
        case HAL_DISP_CHANNEL_DHD0:
        case HAL_DISP_CHANNEL_DHD1: {
            addr_reg = vo_get_chn_abs_addr(chan, (hi_uintptr_t)&(g_vo_reg->DHD0_VTTHD.u32));
            DHD0_VTTHD.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            DHD0_VTTHD.bits.thd1_mode = field_mode;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, DHD0_VTTHD.u32);
            break;
        }

        case HAL_DISP_CHANNEL_WBC: {
            addr_reg = (hi_uintptr_t)&(g_vo_reg->WBC_DHD0_CTRL.u32);
            WBC_DHD0_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            WBC_DHD0_CTRL.bits.mode_out = field_mode;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, WBC_DHD0_CTRL.u32);
            break;
        }

        default: {
            printf("error channel id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }
    return HI_TRUE;
}

hi_bool hal_disp_set_vt_thd(hal_disp_outputchannel chan, hi_u32 vtthd)
{
    volatile U_DHD0_VTTHD DHD0_VTTHD;
    volatile hi_ulong addr_reg;

    switch (chan) {
        case HAL_DISP_CHANNEL_DHD0:
        case HAL_DISP_CHANNEL_DHD1: {
            addr_reg = vo_get_chn_abs_addr(chan, (hi_uintptr_t)&(g_vo_reg->DHD0_VTTHD.u32));
            DHD0_VTTHD.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            DHD0_VTTHD.bits.vtmgthd1 = vtthd;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, DHD0_VTTHD.u32);
            break;
        }

        default: {
            printf("error channel id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_disp_set_int_mask(hi_u32 mask_en)
{
    volatile U_VOINTMSK VOINTMSK;
    /* dispaly interrupt mask enable */
    VOINTMSK.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->VOINTMSK.u32));
    VOINTMSK.u32 = VOINTMSK.u32 | mask_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->VOINTMSK.u32), VOINTMSK.u32);

    return HI_TRUE;
}

hi_bool hal_disp_clr_int_mask(hi_u32 mask_en)
{
    volatile U_VOINTMSK VOINTMSK;

    /* dispaly interrupt mask enable */
    VOINTMSK.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->VOINTMSK.u32));
    VOINTMSK.u32 = VOINTMSK.u32 & (~mask_en);
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->VOINTMSK.u32), VOINTMSK.u32);

    return HI_TRUE;
}

hi_bool hal_disp_clear_int_status(hi_u32 int_msk)
{
    /* read interrupt status */
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->VOMSKINTSTA.u32), int_msk);
    return HI_TRUE;
}

hi_bool hal_disp_set_clk_gate_enable(hi_u32 data)
{
    volatile U_VOCTRL VOCTRL;

    VOCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->VOCTRL.u32));
    VOCTRL.bits.vo_ck_gt_en = data;
    hal_write_reg ((hi_u32*)(hi_uintptr_t)&(g_vo_reg->VOCTRL.u32), VOCTRL.u32);
    return HI_TRUE;
}

hi_bool hal_disp_set_int_mask1(hi_u32 mask_en)
{
    volatile U_VOINTMSK1 VOINTMSK1;
    /* dispaly interrupt mask enable */
    VOINTMSK1.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->VOINTMSK1.u32));
    VOINTMSK1.u32 = VOINTMSK1.u32 | mask_en;

    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->VOINTMSK1.u32), VOINTMSK1.u32);
    VOINTMSK1.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->VOINTMSK1.u32));

    return HI_TRUE;
}

hi_bool hal_disp_clr_int_mask1(hi_u32 mask_en)
{
    volatile U_VOINTMSK1 VOINTMSK1;

    /* dispaly interrupt mask enable */
    VOINTMSK1.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->VOINTMSK1.u32));
    VOINTMSK1.u32 = VOINTMSK1.u32 & (~mask_en);
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->VOINTMSK1.u32), VOINTMSK1.u32);

    return HI_TRUE;
}

hi_bool hal_intf_bt_set_dfir_en(hi_u32 dfir_en)
{
    U_INTF_BT_CTRL INTF_BT_CTRL;

    INTF_BT_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->INTF_BT_CTRL.u32));
    INTF_BT_CTRL.bits.dfir_en = dfir_en;
    hal_write_reg ((hi_u32*)(hi_uintptr_t)&(g_vo_reg->INTF_BT_CTRL.u32), INTF_BT_CTRL.u32);

    return HI_TRUE;
}

hi_void hal_disp_set_reg_up(hal_disp_outputchannel chan)
{
    volatile U_DHD0_CTRL DHD0_CTRL;
    volatile hi_ulong addr_reg;

    if (chan > HAL_DISP_CHANNEL_DHD1) {
        printf("error,hal_disp_set_reg_up select wrong CHANNEL ID\n");
        return;
    }

    addr_reg = vo_get_chn_abs_addr(chan, (hi_uintptr_t)&(g_vo_reg->DHD0_CTRL.u32));
    DHD0_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    DHD0_CTRL.bits.regup = 0x1;
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, DHD0_CTRL.u32);
    return;
}

hi_bool hal_video_set_layer_up_mode(hal_disp_layer layer, hi_u32 up_mode)
{
    U_V0_CTRL V0_CTRL;
    volatile hi_ulong addr_reg;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1: {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_CTRL.u32));
            V0_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_CTRL.bits.rgup_mode = up_mode;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_CTRL.u32);
            break;
        }

        default: {
            printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }
    return HI_TRUE;
}

hi_bool hal_video_set_hfir_mode(hal_disp_layer layer, hal_hfirmode mode)
{
    volatile U_V0_HFIR_CTRL V0_HFIR_CTRL;
    volatile U_WD_HPZME_CTRL WD_HPZME_CTRL;
    volatile U_WD_HCDS_CTRL WD_HCDS_CTRL;

    volatile hi_ulong addr_reg;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1: {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_HFIR_CTRL.u32));
            V0_HFIR_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_HFIR_CTRL.bits.hfir_mode = mode;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_HFIR_CTRL.u32);
            break;
        }

        case HAL_DISP_LAYER_WBC: {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->WD_HPZME_CTRL.u32));
            WD_HPZME_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            WD_HPZME_CTRL.bits.ck_gt_en = 1;
            WD_HPZME_CTRL.bits.hfir_mode = mode;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, WD_HPZME_CTRL.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->WD_HCDS_CTRL.u32));
            WD_HCDS_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            WD_HCDS_CTRL.bits.ck_gt_en = 1;
            WD_HCDS_CTRL.bits.hfir_en = 1;
            WD_HCDS_CTRL.bits.hfir_mode = 0x0;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, WD_HCDS_CTRL.u32);

            break;
        }

        default: {
            printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_video_set_hfir_coef(hal_disp_layer layer, const hi_s32 *coef)
{
    volatile U_V0_HFIRCOEF01 V0_HFIRCOEF01;
    volatile U_V0_HFIRCOEF23 V0_HFIRCOEF23;
    volatile U_V0_HFIRCOEF45 V0_HFIRCOEF45;
    volatile U_V0_HFIRCOEF67 V0_HFIRCOEF67;
    volatile hi_ulong addr_reg;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1: {
            /* the number is to get the value from the coef array */
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF01.u32));
            V0_HFIRCOEF01.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_HFIRCOEF01.bits.coef0 = coef[0];
            V0_HFIRCOEF01.bits.coef1 = coef[1];
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_HFIRCOEF01.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF23.u32));
            V0_HFIRCOEF23.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_HFIRCOEF23.bits.coef2 = coef[2];
            V0_HFIRCOEF23.bits.coef3 = coef[3];
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_HFIRCOEF23.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF45.u32));
            V0_HFIRCOEF45.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_HFIRCOEF45.bits.coef4 = coef[4];
            V0_HFIRCOEF45.bits.coef5 = coef[5];
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_HFIRCOEF45.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF67.u32));
            V0_HFIRCOEF67.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_HFIRCOEF67.bits.coef6 = coef[6];
            V0_HFIRCOEF67.bits.coef7 = coef[7];
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_HFIRCOEF67.u32);
            break;
        }

        default: {
            printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_video_set_layer_disp_rect(hal_disp_layer layer, const hi_rect *rect)
{
    volatile U_V0_DFPOS V0_DFPOS;
    volatile U_V0_DLPOS V0_DLPOS;

    volatile U_G0_DFPOS G0_DFPOS;
    volatile U_G0_DLPOS G0_DLPOS;
    volatile hi_ulong addr_reg;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1: {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_DFPOS.u32));
            V0_DFPOS.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_DFPOS.bits.disp_xfpos = rect->x;
            V0_DFPOS.bits.disp_yfpos = rect->y;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_DFPOS.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_DLPOS.u32));
            V0_DLPOS.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_DLPOS.bits.disp_xlpos = rect->x + rect->width - 1;
            V0_DLPOS.bits.disp_ylpos = rect->y + rect->height - 1;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_DLPOS.u32);
            break;
        }

        case HAL_DISP_LAYER_GFX0:
        case HAL_DISP_LAYER_GFX1: {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->G0_DFPOS.u32));
            G0_DFPOS.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            G0_DFPOS.bits.disp_xfpos = rect->x;
            G0_DFPOS.bits.disp_yfpos = rect->y;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G0_DFPOS.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->G0_DLPOS.u32));
            G0_DLPOS.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            G0_DLPOS.bits.disp_xlpos = rect->x + rect->width - 1;
            G0_DLPOS.bits.disp_ylpos = rect->y + rect->height - 1;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G0_DLPOS.u32);
            break;
        }

        default: {
            printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_video_set_layer_video_rect(hal_disp_layer layer, const hi_rect *rect)
{
    volatile U_V0_VFPOS V0_VFPOS;
    volatile U_V0_VLPOS V0_VLPOS;
    volatile U_G0_VFPOS G0_VFPOS;
    volatile U_G0_VLPOS G0_VLPOS;
    volatile hi_ulong addr_reg;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1: {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_VFPOS.u32));
            V0_VFPOS.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_VFPOS.bits.video_xfpos = rect->x;
            V0_VFPOS.bits.video_yfpos = rect->y;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_VFPOS.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_VLPOS.u32));
            V0_VLPOS.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_VLPOS.bits.video_xlpos = rect->x + rect->width - 1;
            V0_VLPOS.bits.video_ylpos = rect->y + rect->height - 1;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_VLPOS.u32);

            break;
        }

        case HAL_DISP_LAYER_GFX0:
        case HAL_DISP_LAYER_GFX1: {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->G0_VFPOS.u32));
            G0_VFPOS.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            G0_VFPOS.bits.video_xfpos = rect->x;
            G0_VFPOS.bits.video_yfpos = rect->y;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G0_VFPOS.u32);

            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->G0_VLPOS.u32));
            G0_VLPOS.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            G0_VLPOS.bits.video_xlpos = rect->x + rect->width - 1;
            G0_VLPOS.bits.video_ylpos = rect->y + rect->height - 1;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G0_VLPOS.u32);
            break;
        }

        default: {
            printf("error layer id %d# found in %s,%s: L%d\n", layer, __FILE__, __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_video_set_multi_area_l_addr(hal_disp_layer layer, hi_u32 area_num, hi_ulong l_addr, hi_u16 stride)
{
    hi_ulong pxaddr_addr;
    hi_ulong pxstride_addr;
    U_VID_STRIDE VID_STRIDE;

    if ((layer == HAL_DISP_LAYER_VHD0) || (layer == HAL_DISP_LAYER_VHD1)) {
        pxaddr_addr = vo_get_vid_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->VID_ADDR_L));
        hal_write_reg((hi_u32*)(hi_uintptr_t)pxaddr_addr, get_low_addr(l_addr));

        pxaddr_addr = vo_get_vid_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->VID_ADDR_H));
        hal_write_reg((hi_u32*)(hi_uintptr_t)pxaddr_addr, get_high_addr(l_addr));

        pxstride_addr = vo_get_vid_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->VID_STRIDE.u32));
        VID_STRIDE.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)pxstride_addr);
        VID_STRIDE.bits.lm_stride = stride;
        hal_write_reg((hi_u32*)(hi_uintptr_t)pxstride_addr, VID_STRIDE.u32);
    } else {
        printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_video_set_multi_area_c_addr(hal_disp_layer layer, hi_u32 area_num, hi_ulong c_addr, hi_u16 stride)
{
    hi_ulong pxaddr_addr;
    hi_ulong pxstride_addr;
    U_VID_STRIDE VID_STRIDE;

    if ((layer == HAL_DISP_LAYER_VHD0) || (layer == HAL_DISP_LAYER_VHD1)) {
        pxaddr_addr = vo_get_vid_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->VID_CADDR_L));
        hal_write_reg((hi_u32*)(hi_uintptr_t)pxaddr_addr, get_low_addr(c_addr));

        pxaddr_addr = vo_get_vid_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->VID_CADDR_H));
        hal_write_reg((hi_u32*)(hi_uintptr_t)pxaddr_addr, get_high_addr(c_addr));

        pxstride_addr = vo_get_vid_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->VID_STRIDE.u32));
        VID_STRIDE.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)pxstride_addr);
        VID_STRIDE.bits.chm_stride = stride;
        hal_write_reg((hi_u32*)(hi_uintptr_t)pxstride_addr, VID_STRIDE.u32);
    } else {
        printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_video_set_multi_area_enable(hal_disp_layer layer, hi_u32 area_num, hi_u32 enable)
{
    return HI_TRUE;
}

hi_bool hal_video_set_multi_area_reso(hal_disp_layer layer, hi_u32 area_num,
                                      hi_u32 width)
{
    return HI_TRUE;
}

hi_bool hal_video_set_multi_area_rect(hal_disp_layer layer, hi_u32 area_num, const hi_rect *video_area_rect)
{
    return HI_TRUE;
}
hi_bool hal_layer_enable_layer(hal_disp_layer layer, hi_u32 enable)
{
    volatile U_V0_CTRL V0_CTRL;
    volatile U_G0_CTRL G0_CTRL;
    volatile hi_ulong addr_reg;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1: {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_CTRL.u32));
            V0_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_CTRL.bits.surface_en = enable;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_CTRL.u32);
            break;
        }
        case HAL_DISP_LAYER_GFX0:
        case HAL_DISP_LAYER_GFX1: {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->G0_CTRL.u32));
            G0_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            G0_CTRL.bits.surface_en = enable;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G0_CTRL.u32);
            break;
        }
        default: {
            printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

hi_bool hal_layer_set_layer_data_fmt(hal_disp_layer layer,
                                     hal_disp_pixel_format data_fmt)
{
    volatile U_VID_SRC_INFO VID_SRC_INFO;
    volatile U_GFX_SRC_INFO GFX_SRC_INFO;
    volatile hi_ulong addr_reg;

    if ((layer == HAL_DISP_LAYER_VHD0) || (layer == HAL_DISP_LAYER_VHD1)) {
        addr_reg = vo_get_vid_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->VID_SRC_INFO.u32));
        VID_SRC_INFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        VID_SRC_INFO.bits.data_type = data_fmt;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, VID_SRC_INFO.u32);
    } else if ((layer == HAL_DISP_LAYER_GFX0) || (layer == HAL_DISP_LAYER_GFX1)) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->GFX_SRC_INFO.u32));
        GFX_SRC_INFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        GFX_SRC_INFO.bits.ifmt = data_fmt;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, GFX_SRC_INFO.u32);
    } else {
        printf("error layer id found in FILE:%s,FUNC:%s,LINE%d\n", __FILE__, __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

static hi_void hal_layer_csc_set_video0_dc_coef(hal_disp_layer layer, const vo_csc_coef *csc_coef)
{
    volatile U_HIHDR_V_YUV2RGB_IN_DC00 HIHDR_V_YUV2RGB_IN_DC00;
    volatile U_HIHDR_V_YUV2RGB_IN_DC01 HIHDR_V_YUV2RGB_IN_DC01;
    volatile U_HIHDR_V_YUV2RGB_IN_DC02 HIHDR_V_YUV2RGB_IN_DC02;
    volatile U_HIHDR_V_YUV2RGB_OUT_DC00 HIHDR_V_YUV2RGB_OUT_DC00;
    volatile U_HIHDR_V_YUV2RGB_OUT_DC01 HIHDR_V_YUV2RGB_OUT_DC01;
    volatile U_HIHDR_V_YUV2RGB_OUT_DC02 HIHDR_V_YUV2RGB_OUT_DC02;

    volatile hi_ulong addr_reg;

    addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_IN_DC00.u32);
    HIHDR_V_YUV2RGB_IN_DC00.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    HIHDR_V_YUV2RGB_IN_DC00.bits.hihdr_y2r_idc00 = hal_get_xdc_buma(csc_coef->new_csc_in_dc00);
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_IN_DC00.u32);

    addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_IN_DC01.u32);
    HIHDR_V_YUV2RGB_IN_DC01.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    HIHDR_V_YUV2RGB_IN_DC01.bits.hihdr_y2r_idc01 = hal_get_xdc_buma(csc_coef->new_csc_in_dc01);
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_IN_DC01.u32);

    addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_IN_DC02.u32);
    HIHDR_V_YUV2RGB_IN_DC02.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    HIHDR_V_YUV2RGB_IN_DC02.bits.hihdr_y2r_idc02 = hal_get_xdc_buma(csc_coef->new_csc_in_dc02);
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_IN_DC02.u32);

    addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_OUT_DC00.u32);
    HIHDR_V_YUV2RGB_OUT_DC00.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    HIHDR_V_YUV2RGB_OUT_DC00.bits.hihdr_y2r_odc00 = hal_get_odc_buma_new(csc_coef->new_csc_out_dc00);
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_OUT_DC00.u32);

    addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_OUT_DC01.u32);
    HIHDR_V_YUV2RGB_OUT_DC01.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    HIHDR_V_YUV2RGB_OUT_DC01.bits.hihdr_y2r_odc01 = hal_get_odc_buma_new(csc_coef->new_csc_out_dc01);
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_OUT_DC01.u32);

    addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_OUT_DC02.u32);
    HIHDR_V_YUV2RGB_OUT_DC02.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    HIHDR_V_YUV2RGB_OUT_DC02.bits.hihdr_y2r_odc02 = hal_get_odc_buma_new(csc_coef->new_csc_out_dc02);
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_OUT_DC02.u32);
}

static hi_void hal_layer_csc_set_video1_dc_coef(hal_disp_layer layer, const vo_csc_coef *csc_coef)
{
    volatile U_V1_CSC_IDC V1_CSC_IDC;
    volatile U_V1_CSC_ODC V1_CSC_ODC;
    volatile U_V1_CSC_IODC V1_CSC_IODC;

    V1_CSC_IDC.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_IDC.u32));
    V1_CSC_IDC.bits.cscidc1 = hal_get_xdc_buma(csc_coef->csc_in_dc1);
    V1_CSC_IDC.bits.cscidc0 = hal_get_xdc_buma(csc_coef->csc_in_dc0);
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_IDC.u32), V1_CSC_IDC.u32);

    V1_CSC_ODC.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_ODC.u32));
    V1_CSC_ODC.bits.cscodc1 = hal_get_xdc_buma(csc_coef->csc_out_dc1);
    V1_CSC_ODC.bits.cscodc0 = hal_get_xdc_buma(csc_coef->csc_out_dc0);
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_ODC.u32), V1_CSC_ODC.u32);

    V1_CSC_IODC.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_IODC.u32));
    V1_CSC_IODC.bits.cscodc2 = hal_get_xdc_buma(csc_coef->csc_out_dc2);
    V1_CSC_IODC.bits.cscidc2 = hal_get_xdc_buma(csc_coef->csc_in_dc2);
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_IODC.u32), V1_CSC_IODC.u32);
}

static hi_void hal_layer_csc_set_video_dc_coef(hal_disp_layer layer, const vo_csc_coef *csc_dc_coef)
{
    if (layer == HAL_DISP_LAYER_VHD0) {
        hal_layer_csc_set_video0_dc_coef(layer, csc_dc_coef);
    } else if (layer == HAL_DISP_LAYER_VHD1) {
        hal_layer_csc_set_video1_dc_coef(layer, csc_dc_coef);
    }
}

static hi_void hal_layer_csc_set_gfx_dc_coef(hal_disp_layer layer, const vo_csc_coef *csc_coef)
{
    volatile U_HIHDR_G_RGB2YUV_IDC0 HIHDR_G_RGB2YUV_IDC0;
    volatile U_HIHDR_G_RGB2YUV_IDC1 HIHDR_G_RGB2YUV_IDC1;
    volatile U_HIHDR_G_RGB2YUV_IDC2 HIHDR_G_RGB2YUV_IDC2;
    volatile U_HIHDR_G_RGB2YUV_ODC0 HIHDR_G_RGB2YUV_ODC0;
    volatile U_HIHDR_G_RGB2YUV_ODC1 HIHDR_G_RGB2YUV_ODC1;
    volatile U_HIHDR_G_RGB2YUV_ODC2 HIHDR_G_RGB2YUV_ODC2;
    volatile U_G1_CSC_IDC G1_CSC_IDC;
    volatile U_G1_CSC_ODC G1_CSC_ODC;
    volatile U_G1_CSC_IODC G1_CSC_IODC;
    volatile hi_ulong addr_reg;

    if (layer == HAL_DISP_LAYER_GFX0) {
        HIHDR_G_RGB2YUV_IDC0.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_IDC0.u32));
        HIHDR_G_RGB2YUV_IDC0.bits.hihdr_r2y_idc0 = (csc_coef->csc_in_dc0);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_IDC0.u32), HIHDR_G_RGB2YUV_IDC0.u32);

        HIHDR_G_RGB2YUV_IDC1.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_IDC1.u32));
        HIHDR_G_RGB2YUV_IDC1.bits.hihdr_r2y_idc1 = (csc_coef->csc_in_dc1);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_IDC1.u32), HIHDR_G_RGB2YUV_IDC1.u32);

        HIHDR_G_RGB2YUV_IDC2.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_IDC2.u32));
        HIHDR_G_RGB2YUV_IDC2.bits.hihdr_r2y_idc2 = (csc_coef->csc_in_dc2);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_IDC2.u32), HIHDR_G_RGB2YUV_IDC2.u32);

        HIHDR_G_RGB2YUV_ODC0.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_ODC0.u32));
        HIHDR_G_RGB2YUV_ODC0.bits.hihdr_r2y_odc0 = (csc_coef->csc_out_dc0);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_ODC0.u32), HIHDR_G_RGB2YUV_ODC0.u32);

        HIHDR_G_RGB2YUV_ODC1.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_ODC1.u32));
        HIHDR_G_RGB2YUV_ODC1.bits.hihdr_r2y_odc1 = (csc_coef->csc_out_dc1);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_ODC1.u32), HIHDR_G_RGB2YUV_ODC1.u32);

        HIHDR_G_RGB2YUV_ODC2.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_ODC2.u32));
        HIHDR_G_RGB2YUV_ODC2.bits.hihdr_r2y_odc2 = (csc_coef->csc_out_dc2);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_ODC2.u32), HIHDR_G_RGB2YUV_ODC2.u32);
    } else if (layer == HAL_DISP_LAYER_GFX1) {
        addr_reg = (hi_uintptr_t)&(g_vo_reg->G1_CSC_IDC.u32);
        G1_CSC_IDC.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        G1_CSC_IDC.bits.cscidc1 = hal_get_xdc_buma(csc_coef->csc_in_dc1);
        G1_CSC_IDC.bits.cscidc0 = hal_get_xdc_buma(csc_coef->csc_in_dc0);
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G1_CSC_IDC.u32);
        addr_reg = (hi_uintptr_t)&(g_vo_reg->G1_CSC_ODC.u32);
        G1_CSC_ODC.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        G1_CSC_ODC.bits.cscodc1 = hal_get_xdc_buma(csc_coef->csc_out_dc1);
        G1_CSC_ODC.bits.cscodc0 = hal_get_xdc_buma(csc_coef->csc_out_dc0);
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G1_CSC_ODC.u32);
        addr_reg = (hi_uintptr_t)&(g_vo_reg->G1_CSC_IODC.u32);
        G1_CSC_IODC.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        G1_CSC_IODC.bits.cscodc2 = hal_get_xdc_buma(csc_coef->csc_out_dc2);
        G1_CSC_IODC.bits.cscidc2 = hal_get_xdc_buma(csc_coef->csc_in_dc2);
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G1_CSC_IODC.u32);
    }
}

hi_void hal_layer_csc_set_dc_coef(hal_disp_layer layer, const vo_csc_coef *csc_dc_coef)
{
    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        hal_layer_csc_set_video_dc_coef(layer, csc_dc_coef);
    } else if ((layer >= HAL_DISP_LAYER_GFX0) && (layer <= HAL_DISP_LAYER_GFX3)) {
        hal_layer_csc_set_gfx_dc_coef(layer, csc_dc_coef);
    } else {
        printf("error layer id found in %s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);
    }
}

static void hal_layer_csc_set_video_param(hal_disp_layer layer, const vo_csc_coef *csc_coef)
{
    volatile U_HIHDR_V_YUV2RGB_SCALE2P HIHDR_V_YUV2RGB_SCALE2P;
    volatile U_HIHDR_V_YUV2RGB_MIN HIHDR_V_YUV2RGB_MIN;
    volatile U_HIHDR_V_YUV2RGB_MAX HIHDR_V_YUV2RGB_MAX;
    volatile hi_ulong addr_reg;

    addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_SCALE2P.u32);
    HIHDR_V_YUV2RGB_SCALE2P.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    HIHDR_V_YUV2RGB_SCALE2P.bits.hihdr_y2r_v0_scale2p = csc_coef->new_csc_scale2p;
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_SCALE2P.u32);

    HIHDR_V_YUV2RGB_MIN.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_MIN.u32));
    HIHDR_V_YUV2RGB_MIN.bits.hihdr_y2r_v0_clip_min = csc_coef->new_csc_clip_min;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_MIN.u32), HIHDR_V_YUV2RGB_MIN.u32);

    HIHDR_V_YUV2RGB_MAX.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_MAX.u32));
    HIHDR_V_YUV2RGB_MAX.bits.hihdr_y2r_v0_clip_max = csc_coef->new_csc_clip_max;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_MAX.u32), HIHDR_V_YUV2RGB_MAX.u32);
}

static hi_void hal_layer_csc_set_gfx_param(hal_disp_layer layer, const vo_csc_coef *coef_param)
{
    return;
}

hi_void hal_layer_csc_set_param(hal_disp_layer layer, const vo_csc_coef *coef_param)
{
    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        hal_layer_csc_set_video_param(layer, coef_param);
    } else if ((layer >= LAYER_GFX_START) && (layer <= LAYER_GFX_END)) {
        hal_layer_csc_set_gfx_param(layer, coef_param);
    }
}

static hi_void hal_layer_csc_set_video_coef0x(hal_disp_layer layer, const vo_csc_coef *csc_coef)
{
    volatile U_HIHDR_V_YUV2RGB_COEF00 HIHDR_V_YUV2RGB_COEF00;
    volatile U_HIHDR_V_YUV2RGB_COEF01 HIHDR_V_YUV2RGB_COEF01;
    volatile U_HIHDR_V_YUV2RGB_COEF02 HIHDR_V_YUV2RGB_COEF02;
    volatile U_V1_CSC_P0 V1_CSC_P0;
    volatile U_V1_CSC_P1 V1_CSC_P1;
    volatile U_V1_CSC_P2 V1_CSC_P2;
    volatile U_V1_CSC_P3 V1_CSC_P3;
    volatile U_V1_CSC_P4 V1_CSC_P4;
    volatile hi_ulong addr_reg;

    if (layer == HAL_DISP_LAYER_VHD0) {
        addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_COEF00.u32);
        HIHDR_V_YUV2RGB_COEF00.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        HIHDR_V_YUV2RGB_COEF00.bits.hihdr_y2r_coef00 = hal_conver_csc_coef_new(csc_coef->new_csc_coef00);
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_COEF00.u32);

        addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_COEF01.u32);
        HIHDR_V_YUV2RGB_COEF01.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        HIHDR_V_YUV2RGB_COEF01.bits.hihdr_y2r_coef01 = hal_conver_csc_coef_new(csc_coef->new_csc_coef01);
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_COEF01.u32);

        addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_COEF02.u32);
        HIHDR_V_YUV2RGB_COEF02.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        HIHDR_V_YUV2RGB_COEF02.bits.hihdr_y2r_coef02 = hal_conver_csc_coef_new(csc_coef->new_csc_coef02);
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_COEF02.u32);
    } else if (layer == HAL_DISP_LAYER_VHD1) {
        V1_CSC_P0.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_P0.u32));
        V1_CSC_P0.bits.cscp00 = hal_conver_csc_coef(csc_coef->csc_coef00);
        V1_CSC_P0.bits.cscp01 = hal_conver_csc_coef(csc_coef->csc_coef01);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_P0.u32), V1_CSC_P0.u32);

        V1_CSC_P1.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_P1.u32));
        V1_CSC_P1.bits.cscp02 = hal_conver_csc_coef(csc_coef->csc_coef02);
        V1_CSC_P1.bits.cscp10 = hal_conver_csc_coef(csc_coef->csc_coef10);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_P1.u32), V1_CSC_P1.u32);

        V1_CSC_P2.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_P2.u32));
        V1_CSC_P2.bits.cscp11 = hal_conver_csc_coef(csc_coef->csc_coef11);
        V1_CSC_P2.bits.cscp12 = hal_conver_csc_coef(csc_coef->csc_coef12);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_P2.u32), V1_CSC_P2.u32);

        V1_CSC_P3.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_P3.u32));
        V1_CSC_P3.bits.cscp20 = hal_conver_csc_coef(csc_coef->csc_coef20);
        V1_CSC_P3.bits.cscp21 = hal_conver_csc_coef(csc_coef->csc_coef21);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_P3.u32), V1_CSC_P3.u32);

        V1_CSC_P4.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_P4.u32));
        V1_CSC_P4.bits.cscp22 = hal_conver_csc_coef(csc_coef->csc_coef22);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_P4.u32), V1_CSC_P4.u32);
    }
}

static hi_void hal_layer_csc_set_video_coef1x(hal_disp_layer layer, const vo_csc_coef *csc_coef)
{
    volatile U_HIHDR_V_YUV2RGB_COEF03 HIHDR_V_YUV2RGB_COEF03;
    volatile U_HIHDR_V_YUV2RGB_COEF04 HIHDR_V_YUV2RGB_COEF04;
    volatile U_HIHDR_V_YUV2RGB_COEF05 HIHDR_V_YUV2RGB_COEF05;
    volatile hi_ulong addr_reg;

    addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_COEF03.u32);
    HIHDR_V_YUV2RGB_COEF03.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    HIHDR_V_YUV2RGB_COEF03.bits.hihdr_y2r_coef03 = hal_conver_csc_coef_new(csc_coef->new_csc_coef03);
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_COEF03.u32);

    addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_COEF04.u32);
    HIHDR_V_YUV2RGB_COEF04.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    HIHDR_V_YUV2RGB_COEF04.bits.hihdr_y2r_coef04 = hal_conver_csc_coef_new(csc_coef->new_csc_coef04);
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_COEF04.u32);

    addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_COEF05.u32);
    HIHDR_V_YUV2RGB_COEF05.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    HIHDR_V_YUV2RGB_COEF05.bits.hihdr_y2r_coef05 = hal_conver_csc_coef_new(csc_coef->new_csc_coef05);
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_COEF05.u32);
}

static hi_void hal_layer_csc_set_video_coef2x(hal_disp_layer layer, const vo_csc_coef *csc_coef)
{
    volatile U_HIHDR_V_YUV2RGB_COEF06 HIHDR_V_YUV2RGB_COEF06;
    volatile U_HIHDR_V_YUV2RGB_COEF07 HIHDR_V_YUV2RGB_COEF07;
    volatile U_HIHDR_V_YUV2RGB_COEF08 HIHDR_V_YUV2RGB_COEF08;
    volatile hi_ulong addr_reg;

    addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_COEF06.u32);
    HIHDR_V_YUV2RGB_COEF06.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    HIHDR_V_YUV2RGB_COEF06.bits.hihdr_y2r_coef06 = hal_conver_csc_coef_new(csc_coef->new_csc_coef06);
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_COEF06.u32);

    addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_COEF07.u32);
    HIHDR_V_YUV2RGB_COEF07.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    HIHDR_V_YUV2RGB_COEF07.bits.hihdr_y2r_coef07 = hal_conver_csc_coef_new(csc_coef->new_csc_coef07);
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_COEF07.u32);

    addr_reg = (hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_COEF08.u32);
    HIHDR_V_YUV2RGB_COEF08.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
    HIHDR_V_YUV2RGB_COEF08.bits.hihdr_y2r_coef08 = hal_conver_csc_coef_new(csc_coef->new_csc_coef08);
    hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, HIHDR_V_YUV2RGB_COEF08.u32);
}

static hi_void hal_layer_csc_set_gfx_coef0x(hal_disp_layer layer, const vo_csc_coef *csc_coef)
{
    volatile U_HIHDR_G_RGB2YUV_COEF0 HIHDR_G_RGB2YUV_COEF0;
    volatile U_HIHDR_G_RGB2YUV_COEF1 HIHDR_G_RGB2YUV_COEF1;
    volatile U_HIHDR_G_RGB2YUV_COEF2 HIHDR_G_RGB2YUV_COEF2;
    volatile U_G1_CSC_P0 G1_CSC_P0;
    volatile U_G1_CSC_P1 G1_CSC_P1;
    volatile U_G1_CSC_P2 G1_CSC_P2;
    volatile U_G1_CSC_P3 G1_CSC_P3;
    volatile U_G1_CSC_P4 G1_CSC_P4;
    volatile hi_ulong addr_reg;

    if (layer == HAL_DISP_LAYER_GFX0) {
        HIHDR_G_RGB2YUV_COEF0.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF0.u32));
        HIHDR_G_RGB2YUV_COEF0.bits.hihdr_r2y_coef00 = (csc_coef->csc_coef00);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF0.u32), HIHDR_G_RGB2YUV_COEF0.u32);

        HIHDR_G_RGB2YUV_COEF1.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF1.u32));
        HIHDR_G_RGB2YUV_COEF1.bits.hihdr_r2y_coef01 = (csc_coef->csc_coef01);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF1.u32), HIHDR_G_RGB2YUV_COEF1.u32);

        HIHDR_G_RGB2YUV_COEF2.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF2.u32));
        HIHDR_G_RGB2YUV_COEF2.bits.hihdr_r2y_coef02 = (csc_coef->csc_coef02);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF2.u32), HIHDR_G_RGB2YUV_COEF2.u32);
    } else if (layer == HAL_DISP_LAYER_GFX1) {
        addr_reg = (hi_uintptr_t)&(g_vo_reg->G1_CSC_P0.u32);
        G1_CSC_P0.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        G1_CSC_P0.bits.cscp00 = hal_conver_csc_coef(csc_coef->csc_coef00);
        G1_CSC_P0.bits.cscp01 = hal_conver_csc_coef(csc_coef->csc_coef01);
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G1_CSC_P0.u32);
        addr_reg = (hi_uintptr_t)&(g_vo_reg->G1_CSC_P1.u32);
        G1_CSC_P1.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        G1_CSC_P1.bits.cscp02 = hal_conver_csc_coef(csc_coef->csc_coef02);
        G1_CSC_P1.bits.cscp10 = hal_conver_csc_coef(csc_coef->csc_coef10);
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G1_CSC_P1.u32);
        addr_reg = (hi_uintptr_t)&(g_vo_reg->G1_CSC_P2.u32);
        G1_CSC_P2.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        G1_CSC_P2.bits.cscp11 = hal_conver_csc_coef(csc_coef->csc_coef11);
        G1_CSC_P2.bits.cscp12 = hal_conver_csc_coef(csc_coef->csc_coef12);
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G1_CSC_P2.u32);
        addr_reg = (hi_uintptr_t)&(g_vo_reg->G1_CSC_P3.u32);
        G1_CSC_P3.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        G1_CSC_P3.bits.cscp20 = hal_conver_csc_coef(csc_coef->csc_coef20);
        G1_CSC_P3.bits.cscp21 = hal_conver_csc_coef(csc_coef->csc_coef21);
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G1_CSC_P3.u32);
        addr_reg = (hi_uintptr_t)&(g_vo_reg->G1_CSC_P4.u32);
        G1_CSC_P4.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        G1_CSC_P4.bits.cscp22 = hal_conver_csc_coef(csc_coef->csc_coef22);
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G1_CSC_P4.u32);
    }
}

static hi_void hal_layer_csc_set_gfx_coef1x(hal_disp_layer layer, const vo_csc_coef *csc_coef)
{
    volatile U_HIHDR_G_RGB2YUV_COEF3 HIHDR_G_RGB2YUV_COEF3;
    volatile U_HIHDR_G_RGB2YUV_COEF4 HIHDR_G_RGB2YUV_COEF4;
    volatile U_HIHDR_G_RGB2YUV_COEF5 HIHDR_G_RGB2YUV_COEF5;

    HIHDR_G_RGB2YUV_COEF3.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF3.u32));
    HIHDR_G_RGB2YUV_COEF3.bits.hihdr_r2y_coef10 = (csc_coef->csc_coef10);
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF3.u32), HIHDR_G_RGB2YUV_COEF3.u32);

    HIHDR_G_RGB2YUV_COEF4.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF4.u32));
    HIHDR_G_RGB2YUV_COEF4.bits.hihdr_r2y_coef11 = (csc_coef->csc_coef11);
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF4.u32), HIHDR_G_RGB2YUV_COEF4.u32);

    HIHDR_G_RGB2YUV_COEF5.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF5.u32));
    HIHDR_G_RGB2YUV_COEF5.bits.hihdr_r2y_coef12 = (csc_coef->csc_coef12);
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF5.u32), HIHDR_G_RGB2YUV_COEF5.u32);
}

static hi_void hal_layer_csc_set_gfx_coef2x(hal_disp_layer layer, const vo_csc_coef *csc_coef)
{
    volatile U_HIHDR_G_RGB2YUV_COEF6 HIHDR_G_RGB2YUV_COEF6;
    volatile U_HIHDR_G_RGB2YUV_COEF7 HIHDR_G_RGB2YUV_COEF7;
    volatile U_HIHDR_G_RGB2YUV_COEF8 HIHDR_G_RGB2YUV_COEF8;

    HIHDR_G_RGB2YUV_COEF6.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF6.u32));
    HIHDR_G_RGB2YUV_COEF6.bits.hihdr_r2y_coef20 = (csc_coef->csc_coef20);
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF6.u32), HIHDR_G_RGB2YUV_COEF6.u32);

    HIHDR_G_RGB2YUV_COEF7.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF7.u32));
    HIHDR_G_RGB2YUV_COEF7.bits.hihdr_r2y_coef21 = (csc_coef->csc_coef21);
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF7.u32), HIHDR_G_RGB2YUV_COEF7.u32);

    HIHDR_G_RGB2YUV_COEF8.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF8.u32));
    HIHDR_G_RGB2YUV_COEF8.bits.hihdr_r2y_coef22 = (csc_coef->csc_coef22);
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_COEF8.u32), HIHDR_G_RGB2YUV_COEF8.u32);
}

hi_void hal_layer_csc_set_coef(hal_disp_layer layer, const vo_csc_coef *csc_coef)
{
    if ((layer >= LAYER_VHD_START) && (layer <= LAYER_VHD_END)) {
        hal_layer_csc_set_video_coef0x(layer, csc_coef);
        hal_layer_csc_set_video_coef1x(layer, csc_coef);
        hal_layer_csc_set_video_coef2x(layer, csc_coef);
    } else if ((layer >= HAL_DISP_LAYER_GFX0) && (layer <= HAL_DISP_LAYER_GFX3)) {
        hal_layer_csc_set_gfx_coef0x(layer, csc_coef);
        hal_layer_csc_set_gfx_coef1x(layer, csc_coef);
        hal_layer_csc_set_gfx_coef2x(layer, csc_coef);
    } else {
        printf("error layer id found in %s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);
    }

    return;
}

hi_bool hal_layer_set_csc_coef(hal_disp_layer layer, const vo_csc_coef *csc_coef)
{
    hal_layer_csc_set_dc_coef(layer, csc_coef);
    hal_layer_csc_set_coef(layer, csc_coef);
    hal_layer_csc_set_param(layer, csc_coef);

    return HI_TRUE;
}

hi_bool hal_layer_set_csc_en(hal_disp_layer layer, hi_bool csc_en)
{
    U_HIHDR_V_YUV2RGB_CTRL HIHDR_V_YUV2RGB_CTRL;
    U_V1_CSC_IDC V1_CSC_IDC;
    U_HIHDR_G_RGB2YUV_CTRL HIHDR_G_RGB2YUV_CTRL;
    U_G1_CSC_IDC G1_CSC_IDC;
    if (layer == HAL_DISP_LAYER_VHD0) {
        HIHDR_V_YUV2RGB_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_CTRL.u32));
        HIHDR_V_YUV2RGB_CTRL.bits.hihdr_v0_y2r_en = 0x1;
        HIHDR_V_YUV2RGB_CTRL.bits.hihdr_y2r_ck_gt_en = 0x1;
        HIHDR_V_YUV2RGB_CTRL.bits.hihdr_y2r_en = csc_en;
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_V_YUV2RGB_CTRL.u32), HIHDR_V_YUV2RGB_CTRL.u32);
    } else if (layer == HAL_DISP_LAYER_VHD1) {
        V1_CSC_IDC.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_IDC.u32));
        V1_CSC_IDC.bits.csc_en = csc_en;
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CSC_IDC.u32), V1_CSC_IDC.u32);
    } else if (layer == HAL_DISP_LAYER_GFX0) {
        HIHDR_G_RGB2YUV_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_CTRL.u32));
        HIHDR_G_RGB2YUV_CTRL.bits.hihdr_r2y_en = csc_en;
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_CTRL.u32), HIHDR_G_RGB2YUV_CTRL.u32);
    } else if (layer == HAL_DISP_LAYER_GFX1) {
        G1_CSC_IDC.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G1_CSC_IDC.u32));
        G1_CSC_IDC.bits.csc_en = csc_en;
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G1_CSC_IDC.u32), G1_CSC_IDC.u32);
    } else {
        printf("error:wrong layer ID in hal_layer_set_csc_en !\n");
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_layer_set_layer_in_rect(hal_disp_layer layer, const hi_rect *rect)
{
    U_VID_IN_RESO VID_IN_RESO;
    U_GFX_IRESO GFX_IRESO;
    volatile hi_ulong addr_reg;

    if ((layer == HAL_DISP_LAYER_VHD0) || (layer == HAL_DISP_LAYER_VHD1)) {
        addr_reg = vo_get_vid_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->VID_IN_RESO.u32));
        VID_IN_RESO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        VID_IN_RESO.bits.ireso_w = rect->width - 1;
        VID_IN_RESO.bits.ireso_h = rect->height - 1;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, VID_IN_RESO.u32);
    } else if ((layer == HAL_DISP_LAYER_GFX0) || (layer == HAL_DISP_LAYER_GFX1)) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->GFX_IRESO.u32));
        GFX_IRESO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        GFX_IRESO.bits.ireso_w = rect->width - 1;
        GFX_IRESO.bits.ireso_h = rect->height - 1;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, GFX_IRESO.u32);
    } else {
        printf("error layer id found in %s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);
        return HI_FALSE;
    }
    return HI_TRUE;
}

hi_bool hal_layer_set_layer_out_rect(hal_disp_layer layer, const hi_rect *rect)
{
    return HI_FALSE;
}

hi_bool hal_layer_set_layer_galpha(hal_disp_layer layer,
                                   hi_u8 alpha0)
{
    volatile U_V0_CTRL V0_CTRL;
    volatile U_G0_CTRL G0_CTRL;

    volatile hi_ulong addr_reg;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0:
        case HAL_DISP_LAYER_VHD1: {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_CTRL.u32));
            V0_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_CTRL.bits.galpha = alpha0;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_CTRL.u32);
            break;
        }

        case HAL_DISP_LAYER_GFX0:
        case HAL_DISP_LAYER_GFX1: {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->G0_CTRL.u32));
            G0_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            G0_CTRL.bits.galpha = alpha0;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G0_CTRL.u32);
            break;
        }

        default: {
            printf("error layer id %d found in %s: L%d\n", layer, __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

static hi_void hal_layer_set_video_zme_info(hal_disp_layer layer, hi_u32 width, hi_u32 height,
                                            hal_disp_zme_outfmt zme_out_fmt)
{
    volatile U_V0_ZME_HINFO V0_ZME_HINFO;
    volatile U_V0_ZME_VINFO V0_ZME_VINFO;

    volatile U_V1_CVFIR_VINFO V1_CVFIR_VINFO;
    volatile U_V2_CVFIR_VINFO V2_CVFIR_VINFO;

    volatile hi_ulong addr_reg;

    if (layer == HAL_DISP_LAYER_VHD0) {
        addr_reg = (hi_uintptr_t)&(g_vo_reg->V0_ZME_HINFO.u32);
        V0_ZME_HINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        V0_ZME_HINFO.bits.out_width = width - 1;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_ZME_HINFO.u32);

        addr_reg = (hi_uintptr_t)&(g_vo_reg->V0_ZME_VINFO.u32);
        V0_ZME_VINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        V0_ZME_VINFO.bits.out_pro = 1;
        V0_ZME_VINFO.bits.out_height = height - 1;
        V0_ZME_VINFO.bits.out_fmt = zme_out_fmt;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_ZME_VINFO.u32);
    } else if (layer == HAL_DISP_LAYER_VHD1) {
        addr_reg = (hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VINFO.u32);
        V1_CVFIR_VINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        V1_CVFIR_VINFO.bits.vzme_ck_gt_en = 1;
        V1_CVFIR_VINFO.bits.out_pro = 1;
        V1_CVFIR_VINFO.bits.out_height = height;
        V1_CVFIR_VINFO.bits.out_fmt = zme_out_fmt;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V1_CVFIR_VINFO.u32);
    } else if (layer == HAL_DISP_LAYER_VHD2) {
        addr_reg = (hi_uintptr_t)&(g_vo_reg->V2_CVFIR_VINFO.u32);
        V2_CVFIR_VINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        V2_CVFIR_VINFO.bits.vzme_ck_gt_en = 1;
        V2_CVFIR_VINFO.bits.out_pro = 1;
        V2_CVFIR_VINFO.bits.out_height = height;
        V2_CVFIR_VINFO.bits.out_fmt = zme_out_fmt;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V2_CVFIR_VINFO.u32);
    }
}

static hi_void hal_layer_set_gfx_zme_info(hal_disp_layer layer, hi_u32 width, hi_u32 height,
                                          hal_disp_zme_outfmt zme_out_fmt)
{
    volatile U_G0_ZME_HINFO G0_ZME_HINFO;
    volatile U_G0_ZME_VINFO G0_ZME_VINFO;

    volatile hi_ulong addr_reg;
    if (layer == HAL_DISP_LAYER_GFX0) {
        addr_reg = (hi_uintptr_t)&(g_vo_reg->G0_ZME_HINFO.u32);
        G0_ZME_HINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        G0_ZME_HINFO.bits.out_width = width;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G0_ZME_HINFO.u32);

        addr_reg = (hi_uintptr_t)&(g_vo_reg->G0_ZME_VINFO.u32);
        G0_ZME_VINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        G0_ZME_VINFO.bits.out_pro = 1;
        G0_ZME_VINFO.bits.out_height = height;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G0_ZME_VINFO.u32);
    }
}

hi_bool hal_layer_set_zme_info(hal_disp_layer layer, hi_u32 width, hi_u32 height,
                               hal_disp_zme_outfmt zme_out_fmt)
{
    if (layer == HAL_DISP_LAYER_VHD0 ||
        layer == HAL_DISP_LAYER_VHD1 ||
        layer == HAL_DISP_LAYER_VHD2) {
        hal_layer_set_video_zme_info(layer, width, height, zme_out_fmt);
    } else if (layer == HAL_DISP_LAYER_GFX0) {
        hal_layer_set_gfx_zme_info(layer, width, height, zme_out_fmt);
    } else {
        printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_layer_set_src_resolution(hal_disp_layer layer,
                                     const hi_rect *rect)
{
    U_VID_SRC_RESO VID_SRC_RESO;

    volatile hi_ulong addr_reg;

    if ((layer == HAL_DISP_LAYER_VHD0) ||
        (layer == HAL_DISP_LAYER_VHD1) ||
        (layer == HAL_DISP_LAYER_VHD2)) {
        addr_reg = vo_get_vid_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->VID_SRC_RESO.u32));
        VID_SRC_RESO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        VID_SRC_RESO.bits.src_w = rect->width - 1;
        VID_SRC_RESO.bits.src_h = rect->height - 1;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, VID_SRC_RESO.u32);
    }

    return HI_TRUE;
}

static void hal_layer_set_video_zme_enable(hal_disp_layer layer,
                                           hal_disp_zmemode mode,
                                           hi_u32 enable)
{
    volatile U_V0_ZME_HSP V0_ZME_HSP;
    volatile U_V0_ZME_VSP V0_ZME_VSP;
    volatile U_V1_CVFIR_VSP V1_CVFIR_VSP;

    volatile hi_ulong addr_reg;

    if (layer == HAL_DISP_LAYER_VHD0) {
        if ((mode == HAL_DISP_ZMEMODE_HORL) || (mode == HAL_DISP_ZMEMODE_HOR) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32));
            V0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_ZME_HSP.bits.lhfir_en = enable;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_ZME_HSP.u32);
        }

        if ((mode == HAL_DISP_ZMEMODE_HORC) || (mode == HAL_DISP_ZMEMODE_HOR) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32));
            V0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_ZME_HSP.bits.chfir_en = enable;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_ZME_HSP.u32);
        }

        if ((mode == HAL_DISP_ZMEMODE_VERL) || (mode == HAL_DISP_ZMEMODE_VER) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32));
            V0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_ZME_VSP.bits.lvfir_en = enable;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_ZME_VSP.u32);
        }

        if ((mode == HAL_DISP_ZMEMODE_VERC) || (mode == HAL_DISP_ZMEMODE_VER) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32));
            V0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V0_ZME_VSP.bits.cvfir_en = enable;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_ZME_VSP.u32);
        }
    }else if (layer == HAL_DISP_LAYER_VHD1) {
        if ((mode == HAL_DISP_ZMEMODE_VERL) || (mode == HAL_DISP_ZMEMODE_VER) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = (hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VSP.u32);
            V1_CVFIR_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            V1_CVFIR_VSP.bits.cvfir_en = enable;
            V1_CVFIR_VSP.bits.cvmid_en = enable;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V1_CVFIR_VSP.u32);
        }
    }
}

static void hal_layer_set_gfx_zme_enable(hal_disp_layer layer,
                                         hal_disp_zmemode mode,
                                         hi_u32 enable)
{
    volatile U_G0_ZME_HSP G0_ZME_HSP;
    volatile U_G0_ZME_VSP G0_ZME_VSP;

    volatile hi_ulong addr_reg;

    if (layer == HAL_DISP_LAYER_GFX0) {
        if ((mode == HAL_DISP_ZMEMODE_HORL) || (mode == HAL_DISP_ZMEMODE_HOR) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32));
            G0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            G0_ZME_HSP.bits.hfir_en = 1;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G0_ZME_HSP.u32);
        }

        if ((mode == HAL_DISP_ZMEMODE_VERL) || (mode == HAL_DISP_ZMEMODE_VER) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32));
            G0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            G0_ZME_VSP.bits.vfir_en = 1;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G0_ZME_VSP.u32);
        }
    }
}

/* vou zoom enable */
hi_bool hal_layer_set_zme_enable(hal_disp_layer layer,
                                 hal_disp_zmemode mode,
                                 hi_u32 enable)
{
    if (layer == HAL_DISP_LAYER_VHD0 ||
        layer == HAL_DISP_LAYER_VHD1) {
        hal_layer_set_video_zme_enable(layer, mode, enable);
    } else if (layer == HAL_DISP_LAYER_GFX0) {
        hal_layer_set_gfx_zme_enable(layer, mode, enable);
    } else {
        printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }
    return HI_TRUE;
}

hi_bool hal_layer_set_zme_msc_enable(hal_disp_layer layer, hal_disp_zmemode mode, hi_u32 enable)
{
    U_WBC_ME_ZME_HSP WBC_ME_ZME_HSP;
    U_WBC_ME_ZME_VSP WBC_ME_ZME_VSP;

    volatile hi_ulong addr_reg;

    if ((layer == HAL_DISP_LAYER_VHD0) || (layer == HAL_DISP_LAYER_VHD1)) {
    } else if (layer == HAL_DISP_LAYER_WBC) {
        if ((mode == HAL_DISP_ZMEMODE_HORL) || (mode == HAL_DISP_ZMEMODE_HOR) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->WBC_ME_ZME_HSP.u32));
            WBC_ME_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            WBC_ME_ZME_HSP.bits.hlmsc_en = enable;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, WBC_ME_ZME_HSP.u32);
        }

        if ((mode == HAL_DISP_ZMEMODE_HORC) || (mode == HAL_DISP_ZMEMODE_HOR) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->WBC_ME_ZME_HSP.u32));
            WBC_ME_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            WBC_ME_ZME_HSP.bits.hchmsc_en = enable;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, WBC_ME_ZME_HSP.u32);
        }

        if ((mode == HAL_DISP_ZMEMODE_VERL) || (mode == HAL_DISP_ZMEMODE_VER) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->WBC_ME_ZME_VSP.u32));
            WBC_ME_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            WBC_ME_ZME_VSP.bits.vlmsc_en = enable;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, WBC_ME_ZME_VSP.u32);
        }

        if ((mode == HAL_DISP_ZMEMODE_VERC) || (mode == HAL_DISP_ZMEMODE_VER) || (mode == HAL_DISP_ZMEMODE_ALL)) {
            addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->WBC_ME_ZME_VSP.u32));
            WBC_ME_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            WBC_ME_ZME_VSP.bits.vchmsc_en = enable;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, WBC_ME_ZME_VSP.u32);
        }
    } else {
        printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_layer_set_reg_up(hal_disp_layer layer)
{
    U_V0_UPD V0_UPD;
    U_G0_UPD G0_UPD;
    U_WBC_DHD0_UPD WBC_DHD0_UPD;

    volatile hi_ulong addr_reg;
    if (layer <= HAL_DISP_LAYER_VSD0) {
        addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->V0_UPD.u32));
        V0_UPD.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        /* layer register update */
        V0_UPD.bits.regup = 0x1;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, V0_UPD.u32);
    } else if ((layer >= LAYER_GFX_START) && (layer <= LAYER_GFX_END)) {
        addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->G0_UPD.u32));
        G0_UPD.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        /* layer register update */
        G0_UPD.bits.regup = 0x1;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, G0_UPD.u32);
    } else if (layer == HAL_DISP_LAYER_WBC_D) {
        addr_reg = vo_get_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->WBC_DHD0_UPD.u32));
        WBC_DHD0_UPD.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        /* G1 layer register update */
        WBC_DHD0_UPD.bits.regup = 0x1;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, WBC_DHD0_UPD.u32);
    } else {
        printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_graphic_set_gfx_addr(hal_disp_layer layer, hi_u64 l_addr)
{
    volatile hi_ulong gfx_addr_h;
    volatile hi_ulong gfx_addr_l;

    if ((layer == HAL_DISP_LAYER_GFX0) || (layer == HAL_DISP_LAYER_GFX1)) {
        gfx_addr_l = vo_get_gfx_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->GFX_ADDR_L));
        hal_write_reg((hi_u32*)(hi_uintptr_t)gfx_addr_l, get_low_addr(l_addr));

        gfx_addr_h = vo_get_gfx_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->GFX_ADDR_H));
        hal_write_reg((hi_u32*)(hi_uintptr_t)gfx_addr_h, get_high_addr(l_addr));
    } else {
        printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_graphic_set_gfx_stride(hal_disp_layer layer, hi_u16 pitch)
{
    volatile U_GFX_STRIDE GFX_STRIDE;
    volatile hi_ulong addr_reg;

    if ((layer == HAL_DISP_LAYER_GFX0) || (layer == HAL_DISP_LAYER_GFX1)) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->GFX_STRIDE.u32));
        GFX_STRIDE.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        GFX_STRIDE.bits.surface_stride = pitch;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, GFX_STRIDE.u32);
    } else {
        printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }
    return HI_TRUE;
}

hi_bool hal_gfx_set_src_resolution(hal_disp_layer layer, const hi_rect *rect)
{
    U_GFX_SRC_RESO GFX_SRC_RESO;
    volatile hi_ulong addr_reg;

    if ((layer == HAL_DISP_LAYER_GFX0) ||
        (layer == HAL_DISP_LAYER_GFX1) ||
        (layer == HAL_DISP_LAYER_GFX3)) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->GFX_SRC_RESO.u32));
        GFX_SRC_RESO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        GFX_SRC_RESO.bits.src_w = rect->width - 1;
        GFX_SRC_RESO.bits.src_h = rect->height - 1;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, GFX_SRC_RESO.u32);
    } else {
        printf("error:layer id not found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_graphic_set_gfx_ext(hal_disp_layer layer,
                                hal_gfx_bitextend mode)
{
    U_GFX_OUT_CTRL GFX_OUT_CTRL;

    volatile hi_ulong addr_reg;

    if ((layer == HAL_DISP_LAYER_GFX0) || (layer == HAL_DISP_LAYER_GFX1)) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->GFX_OUT_CTRL.u32));
        GFX_OUT_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        GFX_OUT_CTRL.bits.bitext = mode;
        hal_write_reg ((hi_u32*)(hi_uintptr_t)addr_reg, GFX_OUT_CTRL.u32);
    } else {
        printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_graphic_set_gfx_pre_mult(hal_disp_layer layer, hi_u32 enable)
{
    U_GFX_OUT_CTRL GFX_OUT_CTRL;

    volatile hi_ulong addr_reg;

    if ((layer == HAL_DISP_LAYER_GFX0) || (layer == HAL_DISP_LAYER_GFX1)) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->GFX_OUT_CTRL.u32));
        GFX_OUT_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        GFX_OUT_CTRL.bits.premulti_en = enable;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, GFX_OUT_CTRL.u32);
    } else {
        printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_graphic_set_gfx_palpha(hal_disp_layer layer,
                                   hi_u32 alpha_en, hi_u32 arange,
                                   hi_u8 alpha0, hi_u8 alpha1)
{
    U_GFX_OUT_CTRL GFX_OUT_CTRL;
    U_GFX_1555_ALPHA GFX_1555_ALPHA;
    volatile hi_ulong addr_reg;

    if ((layer == HAL_DISP_LAYER_GFX0) || (layer == HAL_DISP_LAYER_GFX1)) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->GFX_OUT_CTRL.u32));
        GFX_OUT_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
        GFX_OUT_CTRL.bits.palpha_en = alpha_en;
        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, GFX_OUT_CTRL.u32);

        if (alpha_en == HI_TRUE) {
            addr_reg = vo_get_gfx_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->GFX_1555_ALPHA.u32));
            GFX_1555_ALPHA.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            GFX_1555_ALPHA.bits.alpha_1 = alpha1;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, GFX_1555_ALPHA.u32);

            addr_reg = vo_get_gfx_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->GFX_1555_ALPHA.u32));
            GFX_1555_ALPHA.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            GFX_1555_ALPHA.bits.alpha_0 = alpha0;
            hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, GFX_1555_ALPHA.u32);
        } else {
            addr_reg = vo_get_gfx_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->GFX_1555_ALPHA.u32));
            GFX_1555_ALPHA.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            GFX_1555_ALPHA.bits.alpha_1 = 0xff; /* 0xff max alpha */
            hal_write_reg ((hi_u32*)(hi_uintptr_t)addr_reg, GFX_1555_ALPHA.u32);

            addr_reg = vo_get_gfx_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->GFX_1555_ALPHA.u32));
            GFX_1555_ALPHA.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);
            GFX_1555_ALPHA.bits.alpha_0 = 0xff; /* 0xff max alpha */
            hal_write_reg ((hi_u32*)(hi_uintptr_t)addr_reg, GFX_1555_ALPHA.u32);
        }
    } else {
        printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_graphic_set_gfx_palpha_range(hal_disp_layer layer, hi_u32 arange)
{
    U_GFX_OUT_CTRL GFX_OUT_CTRL;
    volatile hi_ulong addr_reg;

    if ((layer >= HAL_DISP_LAYER_GFX0) && (layer <= HAL_DISP_LAYER_GFX1)) {
        addr_reg = vo_get_gfx_abs_addr(layer, (hi_uintptr_t)&(g_vo_reg->GFX_OUT_CTRL.u32));

        GFX_OUT_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)addr_reg);

        GFX_OUT_CTRL.bits.palpha_range = arange;

        hal_write_reg((hi_u32*)(hi_uintptr_t)addr_reg, GFX_OUT_CTRL.u32);
    } else {
        printf("error layer id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_cbm_set_cbm_bkg(hi_u32 mixer_id, const hal_disp_bkcolor *bkg)
{
    U_CBM_BKG1 CBM_BKG1;
    U_CBM_BKG2 CBM_BKG2;

    if (mixer_id == HAL_CBMMIX1) {
        CBM_BKG1.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->CBM_BKG1.u32));
        CBM_BKG1.bits.cbm_bkgy1 = (bkg->bkg_y);
        CBM_BKG1.bits.cbm_bkgcb1 = (bkg->bkg_cb);
        CBM_BKG1.bits.cbm_bkgcr1 = (bkg->bkg_cr);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->CBM_BKG1.u32), CBM_BKG1.u32);
    } else if (mixer_id == HAL_CBMMIX2) {
        CBM_BKG2.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->CBM_BKG2.u32));
        CBM_BKG2.bits.cbm_bkgy2 = (bkg->bkg_y);
        CBM_BKG2.bits.cbm_bkgcb2 = (bkg->bkg_cb);
        CBM_BKG2.bits.cbm_bkgcr2 = (bkg->bkg_cr);
        hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->CBM_BKG2.u32), CBM_BKG2.u32);
    } else {
        printf("error mix id found in %s: L%d\n", __FUNCTION__, __LINE__);
        return HI_FALSE;
    }

    return HI_TRUE;
}

static hi_bool hal_cbm_set_cbm_mixer1(hal_disp_layer layer, hi_u8 prio)
{
    U_CBM_MIX1 CBM_MIX1;
    hi_u8 layer_id = 0;

    switch (layer) {
        case HAL_DISP_LAYER_VHD0: {
            layer_id = 0x1; /* 0x1 register config */
            break;
        }

        case HAL_DISP_LAYER_GFX0: {
            layer_id = 0x2; /* 0x2 register config */
            break;
        }

        default: {
            printf("error layer id %d found in %s: L%d\n", layer, __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    CBM_MIX1.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->CBM_MIX1.u32));

    switch (prio) {
        case 0: { /* prio 0 */
            CBM_MIX1.bits.mixer_prio0 = layer_id;
            break;
        }

        case 1: { /* prio 1 */
            CBM_MIX1.bits.mixer_prio1 = layer_id;
            break;
        }

        case 2: { /* prio 2 */
            CBM_MIX1.bits.mixer_prio2 = layer_id;
            break;
        }

        default: {
            printf("error priority id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->CBM_MIX1.u32), CBM_MIX1.u32);
    return HI_TRUE;
}

static hi_bool hal_cbm_set_cbm_mixer2(hal_disp_layer layer, hi_u8 prio)
{
    U_CBM_MIX2 CBM_MIX2;
    hi_u8 layer_id = 0;

    switch (layer) {
        case HAL_DISP_LAYER_VHD1: {
            layer_id = 0x1; /* 0x1 register config */
            break;
        }

        case HAL_DISP_LAYER_GFX1: {
            layer_id = 0x2; /* 0x2 register config */
            break;
        }

        default: {
            printf("error layer id %d found in %s: L%d\n", layer, __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    CBM_MIX2.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->CBM_MIX2.u32));

    switch (prio) {
        case 0: { /* prio 0 */
            CBM_MIX2.bits.mixer_prio0 = layer_id;
            break;
        }

        case 1: { /* prio 1 */
            CBM_MIX2.bits.mixer_prio1 = layer_id;
            break;
        }

        default: {
            printf("error priority id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->CBM_MIX2.u32), CBM_MIX2.u32);
    return HI_TRUE;
}

static hi_bool hal_cbm_set_cbm_mixer3(hal_disp_layer layer, hi_u8 prio)
{
    U_CBM_MIX3 CBM_MIX3;
    hi_u8 layer_id = 0;

    /* settings for v1 and g1 check layer availability */
    switch (layer) {
        case HAL_DISP_LAYER_VHD1: {
            layer_id = 0x1; /* 0x1 register config */
            break;
        }

        case HAL_DISP_LAYER_GFX1: {
            layer_id = 0x3; /* 0x3 register config */
            break;
        }

        default: {
            printf("error layer id %d found in %s: L%d\n", layer, __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    CBM_MIX3.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->CBM_MIX3.u32));

    switch (prio) {
        case 0: { /* prio 0 */
            CBM_MIX3.bits.mixer_prio0 = layer_id;
            break;
        }

        case 1: { /* prio 1 */
            CBM_MIX3.bits.mixer_prio1 = layer_id;
            break;
        }

        case 2: { /* prio 2 */
            CBM_MIX3.bits.mixer_prio2 = layer_id;
            break;
        }

        default: {
            printf("error priority id found in %s: L%d\n", __FUNCTION__, __LINE__);
            return HI_FALSE;
        }
    }

    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->CBM_MIX3.u32), CBM_MIX3.u32);
    return HI_TRUE;
}

hi_bool hal_cbm_set_cbm_mixer_prio(hal_disp_layer layer, hi_u8 prio, hi_u8 mixer_id)
{
    hi_bool ret = HI_FALSE;

    if (mixer_id == HAL_CBMMIX1) {
        ret = hal_cbm_set_cbm_mixer1(layer, prio);
        if (ret == HI_FALSE) {
            return HI_FALSE;
        }
    } else if (mixer_id == HAL_CBMMIX2) {
        ret = hal_cbm_set_cbm_mixer2(layer, prio);
        if (ret == HI_FALSE) {
            return HI_FALSE;
        }
    } else if (mixer_id == HAL_CBMMIX3) {
        ret = hal_cbm_set_cbm_mixer3(layer, prio);
        if (ret == HI_FALSE) {
            return HI_FALSE;
        }
    } else {
        printf("error, mixer_id %d vou_set_cbm_mixer_prio() set a wrong CBMMIX\n", mixer_id);
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_void hal_hihdr_g_set_hihdr_r2y_scale2p(hi_u32 hihdr_r2y_scale2p)
{
    U_HIHDR_G_RGB2YUV_SCALE2P HIHDR_G_RGB2YUV_SCALE2P;

    HIHDR_G_RGB2YUV_SCALE2P.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_SCALE2P.u32));
    HIHDR_G_RGB2YUV_SCALE2P.bits.hihdr_r2y_scale2p = hihdr_r2y_scale2p;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_SCALE2P.u32), HIHDR_G_RGB2YUV_SCALE2P.u32);

    return;
}

hi_void hal_hihdr_g_set_hihdr_r2y_clip_min(hi_u32 hihdr_r2y_clip_min)
{
    U_HIHDR_G_RGB2YUV_MIN HIHDR_G_RGB2YUV_MIN;

    HIHDR_G_RGB2YUV_MIN.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_MIN.u32));
    HIHDR_G_RGB2YUV_MIN.bits.hihdr_r2y_clip_min = hihdr_r2y_clip_min;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_MIN.u32), HIHDR_G_RGB2YUV_MIN.u32);

    return;
}

hi_void hal_hihdr_g_set_hihdr_r2y_clip_max(hi_u32 hihdr_r2y_clip_max)
{
    U_HIHDR_G_RGB2YUV_MAX HIHDR_G_RGB2YUV_MAX;

    HIHDR_G_RGB2YUV_MAX.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_MAX.u32));
    HIHDR_G_RGB2YUV_MAX.bits.hihdr_r2y_clip_max = hihdr_r2y_clip_max;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_hipp_reg->HIHDR_G_RGB2YUV_MAX.u32), HIHDR_G_RGB2YUV_MAX.u32);

    return;
}

hi_void hal_v0_zme_set_hzme_ck_gt_en(hi_u32 hzme_ck_gt_en)
{
    U_V0_ZME_HINFO V0_ZME_HINFO;

    V0_ZME_HINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HINFO.u32));
    V0_ZME_HINFO.bits.hzme_ck_gt_en = hzme_ck_gt_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HINFO.u32), V0_ZME_HINFO.u32);

    return;
}

hi_void hal_v0_zme_set_out_width(hi_u32 out_width)
{
    U_V0_ZME_HINFO V0_ZME_HINFO;

    V0_ZME_HINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HINFO.u32));
    V0_ZME_HINFO.bits.out_width = out_width;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HINFO.u32), V0_ZME_HINFO.u32);

    return;
}

hi_void hal_v0_zme_set_lhfir_en(hi_u32 lhfir_en)
{
    U_V0_ZME_HSP V0_ZME_HSP;

    V0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32));
    V0_ZME_HSP.bits.lhfir_en = lhfir_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32), V0_ZME_HSP.u32);

    return;
}

hi_void hal_v0_zme_set_chfir_en(hi_u32 chfir_en)
{
    U_V0_ZME_HSP V0_ZME_HSP;

    V0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32));
    V0_ZME_HSP.bits.chfir_en = chfir_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32), V0_ZME_HSP.u32);

    return;
}

hi_void hal_v0_zme_set_lhmid_en(hi_u32 lhmid_en)
{
    U_V0_ZME_HSP V0_ZME_HSP;

    V0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32));
    V0_ZME_HSP.bits.lhmid_en = lhmid_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32), V0_ZME_HSP.u32);

    return;
}

hi_void hal_v0_zme_set_chmid_en(hi_u32 chmid_en)
{
    U_V0_ZME_HSP V0_ZME_HSP;

    V0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32));
    V0_ZME_HSP.bits.chmid_en = chmid_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32), V0_ZME_HSP.u32);

    return;
}

hi_void hal_v0_zme_set_non_lnr_en(hi_u32 non_lnr_en)
{
    U_V0_ZME_HSP V0_ZME_HSP;

    V0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32));
    V0_ZME_HSP.bits.non_lnr_en = non_lnr_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32), V0_ZME_HSP.u32);

    return;
}

hi_void hal_v0_zme_set_lhfir_mode(hi_u32 lhfir_mode)
{
    U_V0_ZME_HSP V0_ZME_HSP;

    V0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32));
    V0_ZME_HSP.bits.lhfir_mode = lhfir_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32), V0_ZME_HSP.u32);

    return;
}

hi_void hal_v0_zme_set_chfir_mode(hi_u32 chfir_mode)
{
    U_V0_ZME_HSP V0_ZME_HSP;

    V0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32));
    V0_ZME_HSP.bits.chfir_mode = chfir_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32), V0_ZME_HSP.u32);

    return;
}

hi_void hal_v0_zme_set_hfir_order(hi_u32 hfir_order)
{
    U_V0_ZME_HSP V0_ZME_HSP;

    V0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32));
    V0_ZME_HSP.bits.hfir_order = hfir_order;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32), V0_ZME_HSP.u32);

    return;
}

hi_void hal_v0_zme_set_hratio(hi_u32 hratio)
{
    U_V0_ZME_HSP V0_ZME_HSP;

    V0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32));
    V0_ZME_HSP.bits.hratio = hratio;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HSP.u32), V0_ZME_HSP.u32);

    return;
}

hi_void hal_v0_zme_set_lhfir_offset(hi_u32 lhfir_offset)
{
    U_V0_ZME_HLOFFSET V0_ZME_HLOFFSET;

    V0_ZME_HLOFFSET.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HLOFFSET.u32));
    V0_ZME_HLOFFSET.bits.lhfir_offset = lhfir_offset;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HLOFFSET.u32), V0_ZME_HLOFFSET.u32);

    return;
}

hi_void hal_v0_zme_set_chfir_offset(hi_u32 chfir_offset)
{
    U_V0_ZME_HCOFFSET V0_ZME_HCOFFSET;

    V0_ZME_HCOFFSET.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HCOFFSET.u32));
    V0_ZME_HCOFFSET.bits.chfir_offset = chfir_offset;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HCOFFSET.u32), V0_ZME_HCOFFSET.u32);

    return;
}

hi_void hal_v0_zme_set_zone0_delta(hi_u32 zone0_delta)
{
    U_V0_ZME_HZONE0DELTA V0_ZME_HZONE0DELTA;

    V0_ZME_HZONE0DELTA.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HZONE0DELTA.u32));
    V0_ZME_HZONE0DELTA.bits.zone0_delta = zone0_delta;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HZONE0DELTA.u32), V0_ZME_HZONE0DELTA.u32);

    return;
}

hi_void hal_v0_zme_set_zone2_delta(hi_u32 zone2_delta)
{
    U_V0_ZME_HZONE2DELTA V0_ZME_HZONE2DELTA;

    V0_ZME_HZONE2DELTA.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HZONE2DELTA.u32));
    V0_ZME_HZONE2DELTA.bits.zone2_delta = zone2_delta;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HZONE2DELTA.u32), V0_ZME_HZONE2DELTA.u32);

    return;
}

hi_void hal_v0_zme_set_zone1_end(hi_u32 zone1_end)
{
    U_V0_ZME_HZONEEND V0_ZME_HZONEEND;

    V0_ZME_HZONEEND.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HZONEEND.u32));
    V0_ZME_HZONEEND.bits.zone1_end = zone1_end;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HZONEEND.u32), V0_ZME_HZONEEND.u32);

    return;
}

hi_void hal_v0_zme_set_zone0_end(hi_u32 zone0_end)
{
    U_V0_ZME_HZONEEND V0_ZME_HZONEEND;

    V0_ZME_HZONEEND.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HZONEEND.u32));
    V0_ZME_HZONEEND.bits.zone0_end = zone0_end;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HZONEEND.u32), V0_ZME_HZONEEND.u32);

    return;
}

hi_void hal_v0_zme_set_hl_shootctrl_en(hi_u32 hl_shootctrl_en)
{
    U_V0_ZME_HL_SHOOTCTRL V0_ZME_HL_SHOOTCTRL;

    V0_ZME_HL_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HL_SHOOTCTRL.u32));
    V0_ZME_HL_SHOOTCTRL.bits.hl_shootctrl_en = hl_shootctrl_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HL_SHOOTCTRL.u32), V0_ZME_HL_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_hl_shootctrl_mode(hi_u32 hl_shootctrl_mode)
{
    U_V0_ZME_HL_SHOOTCTRL V0_ZME_HL_SHOOTCTRL;

    V0_ZME_HL_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HL_SHOOTCTRL.u32));
    V0_ZME_HL_SHOOTCTRL.bits.hl_shootctrl_mode = hl_shootctrl_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HL_SHOOTCTRL.u32), V0_ZME_HL_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_hl_flatdect_mode(hi_u32 hl_flatdect_mode)
{
    U_V0_ZME_HL_SHOOTCTRL V0_ZME_HL_SHOOTCTRL;

    V0_ZME_HL_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HL_SHOOTCTRL.u32));
    V0_ZME_HL_SHOOTCTRL.bits.hl_flatdect_mode = hl_flatdect_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HL_SHOOTCTRL.u32), V0_ZME_HL_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_hl_coringadj_en(hi_u32 hl_coringadj_en)
{
    U_V0_ZME_HL_SHOOTCTRL V0_ZME_HL_SHOOTCTRL;

    V0_ZME_HL_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HL_SHOOTCTRL.u32));
    V0_ZME_HL_SHOOTCTRL.bits.hl_coringadj_en = hl_coringadj_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HL_SHOOTCTRL.u32), V0_ZME_HL_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_hl_gain(hi_u32 hl_gain)
{
    U_V0_ZME_HL_SHOOTCTRL V0_ZME_HL_SHOOTCTRL;

    V0_ZME_HL_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HL_SHOOTCTRL.u32));
    V0_ZME_HL_SHOOTCTRL.bits.hl_gain = hl_gain;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HL_SHOOTCTRL.u32), V0_ZME_HL_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_hl_coring(hi_u32 hl_coring)
{
    U_V0_ZME_HL_SHOOTCTRL V0_ZME_HL_SHOOTCTRL;

    V0_ZME_HL_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HL_SHOOTCTRL.u32));
    V0_ZME_HL_SHOOTCTRL.bits.hl_coring = hl_coring;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HL_SHOOTCTRL.u32), V0_ZME_HL_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_hc_shootctrl_en(hi_u32 hc_shootctrl_en)
{
    U_V0_ZME_HC_SHOOTCTRL V0_ZME_HC_SHOOTCTRL;

    V0_ZME_HC_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HC_SHOOTCTRL.u32));
    V0_ZME_HC_SHOOTCTRL.bits.hc_shootctrl_en = hc_shootctrl_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HC_SHOOTCTRL.u32), V0_ZME_HC_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_hc_shootctrl_mode(hi_u32 hc_shootctrl_mode)
{
    U_V0_ZME_HC_SHOOTCTRL V0_ZME_HC_SHOOTCTRL;

    V0_ZME_HC_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HC_SHOOTCTRL.u32));
    V0_ZME_HC_SHOOTCTRL.bits.hc_shootctrl_mode = hc_shootctrl_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HC_SHOOTCTRL.u32), V0_ZME_HC_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_hc_flatdect_mode(hi_u32 hc_flatdect_mode)
{
    U_V0_ZME_HC_SHOOTCTRL V0_ZME_HC_SHOOTCTRL;

    V0_ZME_HC_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HC_SHOOTCTRL.u32));
    V0_ZME_HC_SHOOTCTRL.bits.hc_flatdect_mode = hc_flatdect_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HC_SHOOTCTRL.u32), V0_ZME_HC_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_hc_coringadj_en(hi_u32 hc_coringadj_en)
{
    U_V0_ZME_HC_SHOOTCTRL V0_ZME_HC_SHOOTCTRL;

    V0_ZME_HC_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HC_SHOOTCTRL.u32));
    V0_ZME_HC_SHOOTCTRL.bits.hc_coringadj_en = hc_coringadj_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HC_SHOOTCTRL.u32), V0_ZME_HC_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_hc_gain(hi_u32 hc_gain)
{
    U_V0_ZME_HC_SHOOTCTRL V0_ZME_HC_SHOOTCTRL;

    V0_ZME_HC_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HC_SHOOTCTRL.u32));
    V0_ZME_HC_SHOOTCTRL.bits.hc_gain = hc_gain;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HC_SHOOTCTRL.u32), V0_ZME_HC_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_hc_coring(hi_u32 hc_coring)
{
    U_V0_ZME_HC_SHOOTCTRL V0_ZME_HC_SHOOTCTRL;

    V0_ZME_HC_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HC_SHOOTCTRL.u32));
    V0_ZME_HC_SHOOTCTRL.bits.hc_coring = hc_coring;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_HC_SHOOTCTRL.u32), V0_ZME_HC_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_vzme_ck_gt_en(hi_u32 vzme_ck_gt_en)
{
    U_V0_ZME_VINFO V0_ZME_VINFO;

    V0_ZME_VINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VINFO.u32));
    V0_ZME_VINFO.bits.vzme_ck_gt_en = vzme_ck_gt_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VINFO.u32), V0_ZME_VINFO.u32);

    return;
}

hi_void hal_v0_zme_set_out_pro(hi_u32 out_pro)
{
    U_V0_ZME_VINFO V0_ZME_VINFO;

    V0_ZME_VINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VINFO.u32));
    V0_ZME_VINFO.bits.out_pro = out_pro;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VINFO.u32), V0_ZME_VINFO.u32);

    return;
}

hi_void hal_v0_zme_set_out_fmt(hi_u32 out_fmt)
{
    U_V0_ZME_VINFO V0_ZME_VINFO;

    V0_ZME_VINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VINFO.u32));
    V0_ZME_VINFO.bits.out_fmt = out_fmt;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VINFO.u32), V0_ZME_VINFO.u32);

    return;
}

hi_void hal_v0_zme_set_out_height(hi_u32 out_height)
{
    U_V0_ZME_VINFO V0_ZME_VINFO;

    V0_ZME_VINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VINFO.u32));
    V0_ZME_VINFO.bits.out_height = out_height;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VINFO.u32), V0_ZME_VINFO.u32);

    return;
}

hi_void hal_v0_zme_set_lvfir_en(hi_u32 lvfir_en)
{
    U_V0_ZME_VSP V0_ZME_VSP;

    V0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32));
    V0_ZME_VSP.bits.lvfir_en = lvfir_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32), V0_ZME_VSP.u32);

    return;
}

hi_void hal_v0_zme_set_cvfir_en(hi_u32 cvfir_en)
{
    U_V0_ZME_VSP V0_ZME_VSP;

    V0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32));
    V0_ZME_VSP.bits.cvfir_en = cvfir_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32), V0_ZME_VSP.u32);

    return;
}

hi_void hal_v0_zme_set_lvmid_en(hi_u32 lvmid_en)
{
    U_V0_ZME_VSP V0_ZME_VSP;

    V0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32));
    V0_ZME_VSP.bits.lvmid_en = lvmid_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32), V0_ZME_VSP.u32);

    return;
}

hi_void hal_v0_zme_set_cvmid_en(hi_u32 cvmid_en)
{
    U_V0_ZME_VSP V0_ZME_VSP;

    V0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32));
    V0_ZME_VSP.bits.cvmid_en = cvmid_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32), V0_ZME_VSP.u32);

    return;
}

hi_void hal_v0_zme_set_vfir1tap_en(hi_u32 vfir_1tap_en)
{
    U_V0_ZME_VSP V0_ZME_VSP;

    V0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32));
    V0_ZME_VSP.bits.vfir_1tap_en = vfir_1tap_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32), V0_ZME_VSP.u32);

    return;
}

hi_void hal_v0_zme_set_lvfir_mode(hi_u32 lvfir_mode)
{
    U_V0_ZME_VSP V0_ZME_VSP;

    V0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32));
    V0_ZME_VSP.bits.lvfir_mode = lvfir_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32), V0_ZME_VSP.u32);

    return;
}

hi_void hal_v0_zme_set_cvfir_mode(hi_u32 cvfir_mode)
{
    U_V0_ZME_VSP V0_ZME_VSP;

    V0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32));
    V0_ZME_VSP.bits.cvfir_mode = cvfir_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32), V0_ZME_VSP.u32);

    return;
}

hi_void hal_v0_zme_set_graphdet_en(hi_u32 graphdet_en)
{
    U_V0_ZME_VSP V0_ZME_VSP;

    V0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32));
    V0_ZME_VSP.bits.graphdet_en = graphdet_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32), V0_ZME_VSP.u32);

    return;
}

hi_void hal_v0_zme_set_vratio(hi_u32 vratio)
{
    U_V0_ZME_VSP V0_ZME_VSP;

    V0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32));
    V0_ZME_VSP.bits.vratio = vratio;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VSP.u32), V0_ZME_VSP.u32);

    return;
}

hi_void hal_v0_zme_set_vluma_offset(hi_u32 vluma_offset)
{
    U_V0_ZME_VOFFSET V0_ZME_VOFFSET;

    V0_ZME_VOFFSET.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VOFFSET.u32));
    V0_ZME_VOFFSET.bits.vluma_offset = vluma_offset;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VOFFSET.u32), V0_ZME_VOFFSET.u32);

    return;
}

hi_void hal_v0_zme_set_vchroma_offset(hi_u32 vchroma_offset)
{
    U_V0_ZME_VOFFSET V0_ZME_VOFFSET;

    V0_ZME_VOFFSET.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VOFFSET.u32));
    V0_ZME_VOFFSET.bits.vchroma_offset = vchroma_offset;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VOFFSET.u32), V0_ZME_VOFFSET.u32);

    return;
}

hi_void hal_v0_zme_set_vbluma_offset(hi_u32 vbluma_offset)
{
    U_V0_ZME_VBOFFSET V0_ZME_VBOFFSET;

    V0_ZME_VBOFFSET.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VBOFFSET.u32));
    V0_ZME_VBOFFSET.bits.vbluma_offset = vbluma_offset;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VBOFFSET.u32), V0_ZME_VBOFFSET.u32);

    return;
}

hi_void hal_v0_zme_set_vbchroma_offset(hi_u32 vbchroma_offset)
{
    U_V0_ZME_VBOFFSET V0_ZME_VBOFFSET;

    V0_ZME_VBOFFSET.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VBOFFSET.u32));
    V0_ZME_VBOFFSET.bits.vbchroma_offset = vbchroma_offset;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VBOFFSET.u32), V0_ZME_VBOFFSET.u32);

    return;
}

hi_void hal_v0_zme_set_vl_shootctrl_en(hi_u32 vl_shootctrl_en)
{
    U_V0_ZME_VL_SHOOTCTRL V0_ZME_VL_SHOOTCTRL;

    V0_ZME_VL_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VL_SHOOTCTRL.u32));
    V0_ZME_VL_SHOOTCTRL.bits.vl_shootctrl_en = vl_shootctrl_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VL_SHOOTCTRL.u32), V0_ZME_VL_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_vl_shootctrl_mode(hi_u32 vl_shootctrl_mode)
{
    U_V0_ZME_VL_SHOOTCTRL V0_ZME_VL_SHOOTCTRL;

    V0_ZME_VL_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VL_SHOOTCTRL.u32));
    V0_ZME_VL_SHOOTCTRL.bits.vl_shootctrl_mode = vl_shootctrl_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VL_SHOOTCTRL.u32), V0_ZME_VL_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_vl_flatdect_mode(hi_u32 vl_flatdect_mode)
{
    U_V0_ZME_VL_SHOOTCTRL V0_ZME_VL_SHOOTCTRL;

    V0_ZME_VL_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VL_SHOOTCTRL.u32));
    V0_ZME_VL_SHOOTCTRL.bits.vl_flatdect_mode = vl_flatdect_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VL_SHOOTCTRL.u32), V0_ZME_VL_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_vl_coringadj_en(hi_u32 vl_coringadj_en)
{
    U_V0_ZME_VL_SHOOTCTRL V0_ZME_VL_SHOOTCTRL;

    V0_ZME_VL_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VL_SHOOTCTRL.u32));
    V0_ZME_VL_SHOOTCTRL.bits.vl_coringadj_en = vl_coringadj_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VL_SHOOTCTRL.u32), V0_ZME_VL_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_vl_gain(hi_u32 vl_gain)
{
    U_V0_ZME_VL_SHOOTCTRL V0_ZME_VL_SHOOTCTRL;

    V0_ZME_VL_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VL_SHOOTCTRL.u32));
    V0_ZME_VL_SHOOTCTRL.bits.vl_gain = vl_gain;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VL_SHOOTCTRL.u32), V0_ZME_VL_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_vl_coring(hi_u32 vl_coring)
{
    U_V0_ZME_VL_SHOOTCTRL V0_ZME_VL_SHOOTCTRL;

    V0_ZME_VL_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VL_SHOOTCTRL.u32));
    V0_ZME_VL_SHOOTCTRL.bits.vl_coring = vl_coring;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VL_SHOOTCTRL.u32), V0_ZME_VL_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_vc_shootctrl_en(hi_u32 vc_shootctrl_en)
{
    U_V0_ZME_VC_SHOOTCTRL V0_ZME_VC_SHOOTCTRL;

    V0_ZME_VC_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VC_SHOOTCTRL.u32));
    V0_ZME_VC_SHOOTCTRL.bits.vc_shootctrl_en = vc_shootctrl_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VC_SHOOTCTRL.u32), V0_ZME_VC_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_vc_shootctrl_mode(hi_u32 vc_shootctrl_mode)
{
    U_V0_ZME_VC_SHOOTCTRL V0_ZME_VC_SHOOTCTRL;

    V0_ZME_VC_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VC_SHOOTCTRL.u32));
    V0_ZME_VC_SHOOTCTRL.bits.vc_shootctrl_mode = vc_shootctrl_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VC_SHOOTCTRL.u32), V0_ZME_VC_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_vc_flatdect_mode(hi_u32 vc_flatdect_mode)
{
    U_V0_ZME_VC_SHOOTCTRL V0_ZME_VC_SHOOTCTRL;

    V0_ZME_VC_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VC_SHOOTCTRL.u32));
    V0_ZME_VC_SHOOTCTRL.bits.vc_flatdect_mode = vc_flatdect_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VC_SHOOTCTRL.u32), V0_ZME_VC_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_vc_coringadj_en(hi_u32 vc_coringadj_en)
{
    U_V0_ZME_VC_SHOOTCTRL V0_ZME_VC_SHOOTCTRL;

    V0_ZME_VC_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VC_SHOOTCTRL.u32));
    V0_ZME_VC_SHOOTCTRL.bits.vc_coringadj_en = vc_coringadj_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VC_SHOOTCTRL.u32), V0_ZME_VC_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_vc_gain(hi_u32 vc_gain)
{
    U_V0_ZME_VC_SHOOTCTRL V0_ZME_VC_SHOOTCTRL;

    V0_ZME_VC_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VC_SHOOTCTRL.u32));
    V0_ZME_VC_SHOOTCTRL.bits.vc_gain = vc_gain;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VC_SHOOTCTRL.u32), V0_ZME_VC_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_zme_set_vc_coring(hi_u32 vc_coring)
{
    U_V0_ZME_VC_SHOOTCTRL V0_ZME_VC_SHOOTCTRL;

    V0_ZME_VC_SHOOTCTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VC_SHOOTCTRL.u32));
    V0_ZME_VC_SHOOTCTRL.bits.vc_coring = vc_coring;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_ZME_VC_SHOOTCTRL.u32), V0_ZME_VC_SHOOTCTRL.u32);

    return;
}

hi_void hal_v0_hfir_set_ck_gt_en(hi_u32 ck_gt_en)
{
    U_V0_HFIR_CTRL V0_HFIR_CTRL;

    V0_HFIR_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIR_CTRL.u32));
    V0_HFIR_CTRL.bits.ck_gt_en = ck_gt_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIR_CTRL.u32), V0_HFIR_CTRL.u32);

    return;
}

hi_void hal_v0_hfir_set_mid_en(hi_u32 mid_en)
{
    U_V0_HFIR_CTRL V0_HFIR_CTRL;

    V0_HFIR_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIR_CTRL.u32));
    V0_HFIR_CTRL.bits.mid_en = mid_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIR_CTRL.u32), V0_HFIR_CTRL.u32);

    return;
}

hi_void hal_v0_hfir_set_hfir_mode(hi_u32 hfir_mode)
{
    U_V0_HFIR_CTRL V0_HFIR_CTRL;

    V0_HFIR_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIR_CTRL.u32));
    V0_HFIR_CTRL.bits.hfir_mode = hfir_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIR_CTRL.u32), V0_HFIR_CTRL.u32);

    return;
}

hi_void hal_v0_hfir_set_coef1(hi_u32 coef1)
{
    U_V0_HFIRCOEF01 V0_HFIRCOEF01;

    V0_HFIRCOEF01.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF01.u32));
    V0_HFIRCOEF01.bits.coef1 = coef1;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF01.u32), V0_HFIRCOEF01.u32);

    return;
}

hi_void hal_v0_hfir_set_coef0(hi_u32 coef0)
{
    U_V0_HFIRCOEF01 V0_HFIRCOEF01;

    V0_HFIRCOEF01.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF01.u32));
    V0_HFIRCOEF01.bits.coef0 = coef0;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF01.u32), V0_HFIRCOEF01.u32);

    return;
}

hi_void hal_v0_hfir_set_coef3(hi_u32 coef3)
{
    U_V0_HFIRCOEF23 V0_HFIRCOEF23;

    V0_HFIRCOEF23.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF23.u32));
    V0_HFIRCOEF23.bits.coef3 = coef3;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF23.u32), V0_HFIRCOEF23.u32);

    return;
}

hi_void hal_v0_hfir_set_coef2(hi_u32 coef2)
{
    U_V0_HFIRCOEF23 V0_HFIRCOEF23;

    V0_HFIRCOEF23.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF23.u32));
    V0_HFIRCOEF23.bits.coef2 = coef2;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF23.u32), V0_HFIRCOEF23.u32);

    return;
}

hi_void hal_v0_hfir_set_coef5(hi_u32 coef5)
{
    U_V0_HFIRCOEF45 V0_HFIRCOEF45;

    V0_HFIRCOEF45.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF45.u32));
    V0_HFIRCOEF45.bits.coef5 = coef5;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF45.u32), V0_HFIRCOEF45.u32);

    return;
}

hi_void hal_v0_hfir_set_coef4(hi_u32 coef4)
{
    U_V0_HFIRCOEF45 V0_HFIRCOEF45;

    V0_HFIRCOEF45.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF45.u32));
    V0_HFIRCOEF45.bits.coef4 = coef4;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF45.u32), V0_HFIRCOEF45.u32);

    return;
}

hi_void hal_v0_hfir_set_coef7(hi_u32 coef7)
{
    U_V0_HFIRCOEF67 V0_HFIRCOEF67;

    V0_HFIRCOEF67.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF67.u32));
    V0_HFIRCOEF67.bits.coef7 = coef7;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF67.u32), V0_HFIRCOEF67.u32);

    return;
}

hi_void hal_v0_hfir_set_coef6(hi_u32 coef6)
{
    U_V0_HFIRCOEF67 V0_HFIRCOEF67;

    V0_HFIRCOEF67.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF67.u32));
    V0_HFIRCOEF67.bits.coef6 = coef6;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V0_HFIRCOEF67.u32), V0_HFIRCOEF67.u32);

    return;
}

hi_void hal_v1_hfir_set_ck_gt_en(hi_u32 ck_gt_en)
{
    U_V1_HFIR_CTRL V1_HFIR_CTRL;

    V1_HFIR_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIR_CTRL.u32));
    V1_HFIR_CTRL.bits.ck_gt_en = ck_gt_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIR_CTRL.u32), V1_HFIR_CTRL.u32);

    return;
}

hi_void hal_v1_hfir_set_mid_en(hi_u32 mid_en)
{
    U_V1_HFIR_CTRL V1_HFIR_CTRL;

    V1_HFIR_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIR_CTRL.u32));
    V1_HFIR_CTRL.bits.mid_en = mid_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIR_CTRL.u32), V1_HFIR_CTRL.u32);

    return;
}

hi_void hal_v1_hfir_set_hfir_mode(hi_u32 hfir_mode)
{
    U_V1_HFIR_CTRL V1_HFIR_CTRL;

    V1_HFIR_CTRL.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIR_CTRL.u32));
    V1_HFIR_CTRL.bits.hfir_mode = hfir_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIR_CTRL.u32), V1_HFIR_CTRL.u32);

    return;
}

hi_void hal_v1_hfir_set_coef1(hi_u32 coef1)
{
    U_V1_HFIRCOEF01 V1_HFIRCOEF01;

    V1_HFIRCOEF01.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF01.u32));
    V1_HFIRCOEF01.bits.coef1 = coef1;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF01.u32), V1_HFIRCOEF01.u32);

    return;
}

hi_void hal_v1_hfir_set_coef0(hi_u32 coef0)
{
    U_V1_HFIRCOEF01 V1_HFIRCOEF01;

    V1_HFIRCOEF01.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF01.u32));
    V1_HFIRCOEF01.bits.coef0 = coef0;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF01.u32), V1_HFIRCOEF01.u32);

    return;
}

hi_void hal_v1_hfir_set_coef3(hi_u32 coef3)
{
    U_V1_HFIRCOEF23 V1_HFIRCOEF23;

    V1_HFIRCOEF23.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF23.u32));
    V1_HFIRCOEF23.bits.coef3 = coef3;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF23.u32), V1_HFIRCOEF23.u32);

    return;
}

hi_void hal_v1_hfir_set_coef2(hi_u32 coef2)
{
    U_V1_HFIRCOEF23 V1_HFIRCOEF23;

    V1_HFIRCOEF23.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF23.u32));
    V1_HFIRCOEF23.bits.coef2 = coef2;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF23.u32), V1_HFIRCOEF23.u32);

    return;
}

hi_void hal_v1_hfir_set_coef5(hi_u32 coef5)
{
    U_V1_HFIRCOEF45 V1_HFIRCOEF45;

    V1_HFIRCOEF45.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF45.u32));
    V1_HFIRCOEF45.bits.coef5 = coef5;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF45.u32), V1_HFIRCOEF45.u32);

    return;
}

hi_void hal_v1_hfir_set_coef4(hi_u32 coef4)
{
    U_V1_HFIRCOEF45 V1_HFIRCOEF45;

    V1_HFIRCOEF45.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF45.u32));
    V1_HFIRCOEF45.bits.coef4 = coef4;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF45.u32), V1_HFIRCOEF45.u32);

    return;
}

hi_void hal_v1_hfir_set_coef7(hi_u32 coef7)
{
    U_V1_HFIRCOEF67 V1_HFIRCOEF67;

    V1_HFIRCOEF67.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF67.u32));
    V1_HFIRCOEF67.bits.coef7 = coef7;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF67.u32), V1_HFIRCOEF67.u32);

    return;
}

hi_void hal_v1_hfir_set_coef6(hi_u32 coef6)
{
    U_V1_HFIRCOEF67 V1_HFIRCOEF67;

    V1_HFIRCOEF67.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF67.u32));
    V1_HFIRCOEF67.bits.coef6 = coef6;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_HFIRCOEF67.u32), V1_HFIRCOEF67.u32);

    return;
}

hi_void hal_v1_cvfir_set_vzme_ck_gt_en(hi_u32 vzme_ck_gt_en)
{
    U_V1_CVFIR_VINFO V1_CVFIR_VINFO;

    V1_CVFIR_VINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VINFO.u32));
    V1_CVFIR_VINFO.bits.vzme_ck_gt_en = vzme_ck_gt_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VINFO.u32), V1_CVFIR_VINFO.u32);

    return;
}

hi_void hal_v1_cvfir_set_out_pro(hi_u32 out_pro)
{
    U_V1_CVFIR_VINFO V1_CVFIR_VINFO;

    V1_CVFIR_VINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VINFO.u32));
    V1_CVFIR_VINFO.bits.out_pro = out_pro;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VINFO.u32), V1_CVFIR_VINFO.u32);

    return;
}

hi_void hal_v1_cvfir_set_out_fmt(hi_u32 out_fmt)
{
    U_V1_CVFIR_VINFO V1_CVFIR_VINFO;

    V1_CVFIR_VINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VINFO.u32));
    V1_CVFIR_VINFO.bits.out_fmt = out_fmt;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VINFO.u32), V1_CVFIR_VINFO.u32);

    return;
}

hi_void hal_v1_cvfir_set_out_height(hi_u32 out_height)
{
    U_V1_CVFIR_VINFO V1_CVFIR_VINFO;

    V1_CVFIR_VINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VINFO.u32));
    V1_CVFIR_VINFO.bits.out_height = out_height;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VINFO.u32), V1_CVFIR_VINFO.u32);

    return;
}

hi_void hal_v1_cvfir_set_cvfir_en(hi_u32 cvfir_en)
{
    U_V1_CVFIR_VSP V1_CVFIR_VSP;

    V1_CVFIR_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VSP.u32));
    V1_CVFIR_VSP.bits.cvfir_en = cvfir_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VSP.u32), V1_CVFIR_VSP.u32);

    return;
}

hi_void hal_v1_cvfir_set_cvmid_en(hi_u32 cvmid_en)
{
    U_V1_CVFIR_VSP V1_CVFIR_VSP;

    V1_CVFIR_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VSP.u32));
    V1_CVFIR_VSP.bits.cvmid_en = cvmid_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VSP.u32), V1_CVFIR_VSP.u32);

    return;
}

hi_void hal_v1_cvfir_set_cvfir_mode(hi_u32 cvfir_mode)
{
    U_V1_CVFIR_VSP V1_CVFIR_VSP;

    V1_CVFIR_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VSP.u32));
    V1_CVFIR_VSP.bits.cvfir_mode = cvfir_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VSP.u32), V1_CVFIR_VSP.u32);

    return;
}

hi_void hal_v1_cvfir_set_vratio(hi_u32 vratio)
{
    U_V1_CVFIR_VSP V1_CVFIR_VSP;

    V1_CVFIR_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VSP.u32));
    V1_CVFIR_VSP.bits.vratio = vratio;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VSP.u32), V1_CVFIR_VSP.u32);

    return;
}

hi_void hal_v1_cvfir_set_vchroma_offset(hi_u32 vchroma_offset)
{
    U_V1_CVFIR_VOFFSET V1_CVFIR_VOFFSET;

    V1_CVFIR_VOFFSET.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VOFFSET.u32));
    V1_CVFIR_VOFFSET.bits.vchroma_offset = vchroma_offset;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VOFFSET.u32), V1_CVFIR_VOFFSET.u32);

    return;
}

hi_void hal_v1_cvfir_set_vbchroma_offset(hi_u32 vbchroma_offset)
{
    U_V1_CVFIR_VBOFFSET V1_CVFIR_VBOFFSET;

    V1_CVFIR_VBOFFSET.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VBOFFSET.u32));
    V1_CVFIR_VBOFFSET.bits.vbchroma_offset = vbchroma_offset;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->V1_CVFIR_VBOFFSET.u32), V1_CVFIR_VBOFFSET.u32);

    return;
}

hi_void hal_g0_zme_set_ck_gt_en(hi_u32 ck_gt_en)
{
    U_G0_ZME_HINFO G0_ZME_HINFO;

    G0_ZME_HINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HINFO.u32));
    G0_ZME_HINFO.bits.ck_gt_en = ck_gt_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HINFO.u32), G0_ZME_HINFO.u32);

    return;
}

hi_void hal_g0_zme_set_out_width(hi_u32 out_width)
{
    U_G0_ZME_HINFO G0_ZME_HINFO;

    G0_ZME_HINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HINFO.u32));
    G0_ZME_HINFO.bits.out_width = out_width - 1;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HINFO.u32), G0_ZME_HINFO.u32);

    return;
}

hi_void hal_g0_zme_set_hfir_en(hi_u32 hfir_en)
{
    U_G0_ZME_HSP G0_ZME_HSP;

    G0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32));
    G0_ZME_HSP.bits.hfir_en = hfir_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32), G0_ZME_HSP.u32);

    return;
}

hi_void hal_g0_zme_set_ahfir_mid_en(hi_u32 ahfir_mid_en)
{
    U_G0_ZME_HSP G0_ZME_HSP;

    G0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32));
    G0_ZME_HSP.bits.ahfir_mid_en = ahfir_mid_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32), G0_ZME_HSP.u32);

    return;
}

hi_void hal_g0_zme_set_lhfir_mid_en(hi_u32 lhfir_mid_en)
{
    U_G0_ZME_HSP G0_ZME_HSP;

    G0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32));
    G0_ZME_HSP.bits.lhfir_mid_en = lhfir_mid_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32), G0_ZME_HSP.u32);

    return;
}

hi_void hal_g0_zme_set_chfir_mid_en(hi_u32 chfir_mid_en)
{
    U_G0_ZME_HSP G0_ZME_HSP;

    G0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32));
    G0_ZME_HSP.bits.chfir_mid_en = chfir_mid_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32), G0_ZME_HSP.u32);

    return;
}

hi_void hal_g0_zme_set_lhfir_mode(hi_u32 lhfir_mode)
{
    U_G0_ZME_HSP G0_ZME_HSP;

    G0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32));
    G0_ZME_HSP.bits.lhfir_mode = lhfir_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32), G0_ZME_HSP.u32);

    return;
}

hi_void hal_g0_zme_set_ahfir_mode(hi_u32 ahfir_mode)
{
    U_G0_ZME_HSP G0_ZME_HSP;

    G0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32));
    G0_ZME_HSP.bits.ahfir_mode = ahfir_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32), G0_ZME_HSP.u32);

    return;
}

hi_void hal_g0_zme_set_hfir_order(hi_u32 hfir_order)
{
    U_G0_ZME_HSP G0_ZME_HSP;

    G0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32));
    G0_ZME_HSP.bits.hfir_order = hfir_order;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32), G0_ZME_HSP.u32);

    return;
}

hi_void hal_g0_zme_set_hratio(hi_u32 hratio)
{
    U_G0_ZME_HSP G0_ZME_HSP;

    G0_ZME_HSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32));
    G0_ZME_HSP.bits.hratio = hratio;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HSP.u32), G0_ZME_HSP.u32);

    return;
}

hi_void hal_g0_zme_set_lhfir_offset(hi_u32 lhfir_offset)
{
    U_G0_ZME_HLOFFSET G0_ZME_HLOFFSET;

    G0_ZME_HLOFFSET.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HLOFFSET.u32));
    G0_ZME_HLOFFSET.bits.lhfir_offset = lhfir_offset;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HLOFFSET.u32), G0_ZME_HLOFFSET.u32);

    return;
}

hi_void hal_g0_zme_set_chfir_offset(hi_u32 chfir_offset)
{
    U_G0_ZME_HCOFFSET G0_ZME_HCOFFSET;

    G0_ZME_HCOFFSET.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HCOFFSET.u32));
    G0_ZME_HCOFFSET.bits.chfir_offset = chfir_offset;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_HCOFFSET.u32), G0_ZME_HCOFFSET.u32);

    return;
}

hi_void hal_g0_zme_set_out_pro(hi_u32 out_pro)
{
    U_G0_ZME_VINFO G0_ZME_VINFO;

    G0_ZME_VINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VINFO.u32));
    G0_ZME_VINFO.bits.out_pro = out_pro;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VINFO.u32), G0_ZME_VINFO.u32);

    return;
}

hi_void hal_g0_zme_set_out_height(hi_u32 out_height)
{
    U_G0_ZME_VINFO G0_ZME_VINFO;

    G0_ZME_VINFO.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VINFO.u32));
    G0_ZME_VINFO.bits.out_height = out_height - 1;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VINFO.u32), G0_ZME_VINFO.u32);

    return;
}

hi_void hal_g0_zme_set_vfir_en(hi_u32 vfir_en)
{
    U_G0_ZME_VSP G0_ZME_VSP;

    G0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32));
    G0_ZME_VSP.bits.vfir_en = vfir_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32), G0_ZME_VSP.u32);

    return;
}

hi_void hal_g0_zme_set_avfir_mid_en(hi_u32 avfir_mid_en)
{
    U_G0_ZME_VSP G0_ZME_VSP;

    G0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32));
    G0_ZME_VSP.bits.avfir_mid_en = avfir_mid_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32), G0_ZME_VSP.u32);

    return;
}

hi_void hal_g0_zme_set_lvfir_mid_en(hi_u32 lvfir_mid_en)
{
    U_G0_ZME_VSP G0_ZME_VSP;

    G0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32));
    G0_ZME_VSP.bits.lvfir_mid_en = lvfir_mid_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32), G0_ZME_VSP.u32);

    return;
}

hi_void hal_g0_zme_set_cvfir_mid_en(hi_u32 cvfir_mid_en)
{
    U_G0_ZME_VSP G0_ZME_VSP;

    G0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32));
    G0_ZME_VSP.bits.cvfir_mid_en = cvfir_mid_en;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32), G0_ZME_VSP.u32);

    return;
}

hi_void hal_g0_zme_set_lvfir_mode(hi_u32 lvfir_mode)
{
    U_G0_ZME_VSP G0_ZME_VSP;

    G0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32));
    G0_ZME_VSP.bits.lvfir_mode = lvfir_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32), G0_ZME_VSP.u32);

    return;
}

hi_void hal_g0_zme_set_vafir_mode(hi_u32 vafir_mode)
{
    U_G0_ZME_VSP G0_ZME_VSP;

    G0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32));
    G0_ZME_VSP.bits.vafir_mode = vafir_mode;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32), G0_ZME_VSP.u32);

    return;
}

hi_void hal_g0_zme_set_vratio(hi_u32 vratio)
{
    U_G0_ZME_VSP G0_ZME_VSP;

    G0_ZME_VSP.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32));
    G0_ZME_VSP.bits.vratio = vratio;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VSP.u32), G0_ZME_VSP.u32);

    return;
}

hi_void hal_g0_zme_set_vtp_offset(hi_u32 vtp_offset)
{
    U_G0_ZME_VOFFSET G0_ZME_VOFFSET;

    G0_ZME_VOFFSET.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VOFFSET.u32));
    G0_ZME_VOFFSET.bits.vtp_offset = vtp_offset;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VOFFSET.u32), G0_ZME_VOFFSET.u32);

    return;
}

hi_void hal_g0_zme_set_vbtm_offset(hi_u32 vbtm_offset)
{
    U_G0_ZME_VOFFSET G0_ZME_VOFFSET;

    G0_ZME_VOFFSET.u32 = hal_read_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VOFFSET.u32));
    G0_ZME_VOFFSET.bits.vbtm_offset = vbtm_offset;
    hal_write_reg((hi_u32*)(hi_uintptr_t)&(g_vo_reg->G0_ZME_VOFFSET.u32), G0_ZME_VOFFSET.u32);

    return;
}

