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

#ifndef __HISOC_SPINAND_H__
#define __HISOC_SPINAND_H__

#include "asm/platform.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */
/*****************************************************************************/
#define CRG48                             0xc0
#define CRG48_SPI_NAND_CLK_SEL(_clk)      (((_clk) & 0x3) << 6)
#define CRG48_SPI_NAND_CLK_EN             (1 << 5)
#define CRG48_SPI_NAND_SOFT_RST_REQ       (1 << 4)

#define SPI_NAND_CLK_SEL_MASK       (0x3 << 6)
#define DEVICE_TYPE_SHIFT            1
#define DEVICE_TYPE_MASK            (0x1 << 1)

#define CLK_24M                         0
#define CLK_75M                         1
#define CLK_125M                        2

#define SPI_NAND_CLK_SEL_24M        CRG48_SPI_NAND_CLK_SEL(CLK_24M)
#define SPI_NAND_CLK_SEL_75M        CRG48_SPI_NAND_CLK_SEL(CLK_75M)
#define SPI_NAND_CLK_SEL_125M       CRG48_SPI_NAND_CLK_SEL(CLK_125M)

#define GET_CLK_TYPE(_reg)          (((_reg) >> 2) & 0x3)

/*****************************************************************************/
static void hisnfc100_set_system_clock(int clock, int clk_en)
{
    unsigned base = CRG_REG_BASE;
    unsigned regval = readl(base + CRG48);

    if (!clock)
        clock = SPI_NAND_CLK_SEL_75M;
    regval = (regval & SPI_NAND_CLK_SEL_MASK) | clock;

    if (clk_en)
        regval |= CRG48_SPI_NAND_CLK_EN;
    else
        regval &= ~CRG48_SPI_NAND_CLK_EN;

    if (readl(base + CRG48) != regval)
        writel(regval, (base + CRG48));
}

/*****************************************************************************/
static void hisnfc100_get_best_clock(unsigned int *clock)
{
    int ix;
    int clk_reg;
#define CLK_2X(_clk)    (((_clk) + 1) >> 1)
    unsigned int sysclk[] = {
        CLK_2X(24),    SPI_NAND_CLK_SEL_24M,
        CLK_2X(75),    SPI_NAND_CLK_SEL_75M,
        CLK_2X(125),    SPI_NAND_CLK_SEL_125M,
        0, 0,
    };
#undef CLK_2X

    clk_reg = SPI_NAND_CLK_SEL_24M;
    for (ix = 0; sysclk[ix]; ix += 2) {
        if (*clock < sysclk[ix])
            break;
        clk_reg = sysclk[ix + 1];
    }
    *clock = clk_reg;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif

