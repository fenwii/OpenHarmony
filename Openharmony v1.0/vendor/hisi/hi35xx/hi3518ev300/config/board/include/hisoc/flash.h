/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __HISOC_FLASH_H__
#define __HISOC_FLASH_H__

#include "asm/platform.h"
#include "hisoc/sys_ctrl.h"
#include "asm/io.h"
#include "linux/delay.h"
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/* FMC CRG register offset */
#define PERI_CRG48              0xc0
#define REG_FMC_CRG             PERI_CRG48
#define FMC_CLK_SEL(_clk)       (((_clk) & 0x7) << 2)
#define FMC_CLK_SEL_MASK        (0x7 << 2)
#define GET_CLK_TYPE(_reg)      (((_reg) >> 2) & 0x7)
/* SDR/DDR clock */
#define FMC_CLK_24M             0
#define FMC_CLK_75M             1
#define FMC_CLK_125M            2
#define FMC_CLK_150M            3
#define FMC_CLK_200M            4
#define FMC_CLK_250M            5
/* Only DDR clock */
#define FMC_CLK_300M            6
#define FMC_CLK_400M            7
#define FMC_CLK_ENABLE          (0x1 << 1)
#define FMC_SOFT_RST_REQ        (0x1 << 0)

/* bit[9]=0: 3-Byte address mode; bit[9]=1: 4-Byte address mode */
#define GET_SPI_NOR_ADDR_MODE(_reg) (((_reg) >> 9) & 0x1)

/****************************************************************************/
/* REG_SYSSTAT 0: 3 Bytes address boot mode; 1: 4Bytes address boot mode */
#define REG_SYSSTAT            0x008C
#define GET_FMC_BOOT_MODE ({ \
            unsigned int regval; \
            unsigned int boot_mode = 0; \
            regval = readl(SYS_CTRL_REG_BASE + REG_SYSSTAT); \
            boot_mode = GET_SPI_NOR_ADDR_MODE(regval); \
            boot_mode; })


/* This define just for Padctrl, PHY and DC configuration
 * of nand flash */
#define MISC_CTRL28         0x28
#define EMMC_PHY_INIT_CTRL  IO_DEVICE_ADDR(0x12160004)
#define PHY_INIT_EN         0x1
#define PHY_ZCAL_EN         (0x1 << 3)

#define EMMC_PHY_IOCTL_RONSEL_1_0   IO_DEVICE_ADDR(0x12160264)
#define RG_EMMC_RONSEL1             0x7ff
#define RG_EMMC_RONSEL0             0x7ff
#define EMMC_PHY_IOCTL_OD_RONSEL_2  IO_DEVICE_ADDR(0x12160268)
#define EMMC_PHY_IOCTL_IOE          IO_DEVICE_ADDR(0x1216026c)
#define NAND_IO_EN                  0x00ff00ff

static inline void nand_io_config(void)
{
    /* Padctrl, PHY and DC configuration */
    unsigned int reg_val = 0;
    unsigned int timeout = 20;

    /* set pad ctrl reg for nand */
    writel(0x1a3, IO_MUX_REG_BASE + 0x91c);
    writel(0x103, IO_MUX_REG_BASE + 0x920);
    writel(0x100, IO_MUX_REG_BASE + 0x924);
    writel(0x1a3, IO_MUX_REG_BASE + 0x928);
    writel(0x100, IO_MUX_REG_BASE + 0x92c);
    writel(0x100, IO_MUX_REG_BASE + 0x930);

    /* disable emmc io isolation mode */
    reg_val = readl(MISC_REG_BASE + MISC_CTRL28);
    reg_val &= ~0x1;
    writel(reg_val, MISC_REG_BASE + MISC_CTRL28);

    /* enable phy init */
    reg_val = readl(EMMC_PHY_INIT_CTRL);
    reg_val |= (PHY_INIT_EN | PHY_ZCAL_EN);
    writel(reg_val, EMMC_PHY_INIT_CTRL);

    /* wait phy init and zcal done */
    for(; ; ) {
        reg_val = readl(EMMC_PHY_INIT_CTRL);
        if (!(reg_val & (PHY_INIT_EN | PHY_ZCAL_EN)))
            break;
        udelay(100);
        if (timeout-- == 0) {
            dprintf("ERROR: wait mmc phy cal done time out\n");
            return;
        }
    }

    /* DRV50 */
    writel((RG_EMMC_RONSEL1 << 16) | RG_EMMC_RONSEL0,
            EMMC_PHY_IOCTL_RONSEL_1_0);
    /* DRV50, OD = 0 */
    writel(0, EMMC_PHY_IOCTL_OD_RONSEL_2);

    writel(NAND_IO_EN, EMMC_PHY_IOCTL_IOE);

    writel(0x2, IO_MUX_REG_BASE + 69 * 4);
    writel(0x2, IO_MUX_REG_BASE + 70 * 4);
    writel(0x2, IO_MUX_REG_BASE + 71 * 4);
    writel(0x2, IO_MUX_REG_BASE + 72 * 4);
    writel(0x2, IO_MUX_REG_BASE + 73 * 4);
    writel(0x2, IO_MUX_REG_BASE + 74 * 4);
    writel(0x2, IO_MUX_REG_BASE + 75 * 4);
    writel(0x2, IO_MUX_REG_BASE + 76 * 4);
    writel(0x2, IO_MUX_REG_BASE + 79 * 4);
    writel(0x2, IO_MUX_REG_BASE + 80 * 4);
    writel(0x2, IO_MUX_REG_BASE + 81 * 4);
    writel(0x2, IO_MUX_REG_BASE + 82 * 4);
    writel(0x2, IO_MUX_REG_BASE + 83 * 4);
    writel(0x2, IO_MUX_REG_BASE + 84 * 4);
}

static inline void spi_io_config(void)
{
    /* set pad ctrl reg for spi */
    writel(0x1C0, IO_MUX_REG_BASE + 0x91c);
    writel(0x130, IO_MUX_REG_BASE + 0x920);
    writel(0x130, IO_MUX_REG_BASE + 0x924);
    writel(0x130, IO_MUX_REG_BASE + 0x928);
    writel(0x130, IO_MUX_REG_BASE + 0x92c);
    writel(0x103, IO_MUX_REG_BASE + 0x930);

    /* set mux ctrl reg for spi */
    writel(0x1, IO_MUX_REG_BASE + 0x13c);
    writel(0x1, IO_MUX_REG_BASE + 0x140);
    writel(0x1, IO_MUX_REG_BASE + 0x144);
    writel(0x1, IO_MUX_REG_BASE + 0x148);
    writel(0x1, IO_MUX_REG_BASE + 0x14c);
    writel(0x1, IO_MUX_REG_BASE + 0x150);
}

/*---------------------------------------------------------------------------*/
/* hifmc100_set_fmc_system_clock */
/*---------------------------------------------------------------------------*/
static inline void hifmc100_set_system_clock(unsigned clock, int clk_en)
{
    unsigned int old_val, regval;

    old_val = regval = readl(CRG_REG_BASE + REG_FMC_CRG);

    regval &= ~FMC_CLK_SEL_MASK;

    if (clock)
        regval |= clock & FMC_CLK_SEL_MASK;
    else {
        regval |= FMC_CLK_SEL(FMC_CLK_24M); /* Default Clock */
        spi_io_config();
    }

    if (clk_en)
        regval |= FMC_CLK_ENABLE;
    else
        regval &= ~FMC_CLK_ENABLE;

    if (regval != old_val)
        writel(regval, (CRG_REG_BASE + REG_FMC_CRG));
}

/*---------------------------------------------------------------------------*/
/* hifmc100_get_best_clock */
/*---------------------------------------------------------------------------*/
static inline void hifmc100_get_best_clock(unsigned int *clock)
{
    int ix;
    unsigned int clk_reg, clk_type;

#define CLK_2X(_clk)    (((_clk) + 1) >> 1)
    unsigned int sys_2X_clk[] = {
        CLK_2X(24), FMC_CLK_SEL(FMC_CLK_24M),
        CLK_2X(75), FMC_CLK_SEL(FMC_CLK_75M),
        CLK_2X(125),    FMC_CLK_SEL(FMC_CLK_125M),
        CLK_2X(150),    FMC_CLK_SEL(FMC_CLK_150M),
        CLK_2X(200),    FMC_CLK_SEL(FMC_CLK_200M),
        // CLK_2X(250),    FMC_CLK_SEL(FMC_CLK_250M),
        0,      0,
    };
#undef CLK_2X

    clk_type = FMC_CLK_24M;
    clk_reg = FMC_CLK_SEL(clk_type);
    for (ix = 0; sys_2X_clk[ix]; ix += 2) {
        if (*clock < sys_2X_clk[ix])
            break;
        clk_reg = sys_2X_clk[ix + 1];
        clk_type = GET_CLK_TYPE(clk_reg);
    }

    *clock = clk_reg;
}

static inline void hifmc100_nand_clk_enable(int enable)
{
    unsigned int old_val, regval;

    old_val = regval = readl(CRG_REG_BASE + REG_FMC_CRG);

    regval |= FMC_CLK_SEL(FMC_CLK_200M);

    if (enable)
        regval |= FMC_CLK_ENABLE;
    else
        regval &= ~FMC_CLK_ENABLE;

    regval &= ~FMC_SOFT_RST_REQ;
    if (regval != old_val)
        writel(regval, (CRG_REG_BASE + REG_FMC_CRG));
    nand_io_config();
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

