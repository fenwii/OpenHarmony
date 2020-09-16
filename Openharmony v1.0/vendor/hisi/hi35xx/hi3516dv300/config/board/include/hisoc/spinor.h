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

#ifndef __HISOC_SPINOR_H__
#define __HISOC_SPINOR_H__

#include "asm/platform.h"
#include "asm/io.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define PERI_CRG48                (CRG_REG_BASE + 0x00C0)
#define PERI_CRG48_RST            (1 << 0)
#define PERI_CRG48_CLKEN            (1 << 1)
#define PERI_CRG48_CLK_24M            (0 << 2)
#define PERI_CRG48_CLK_75M            ((0 << 3) | (1 << 2))
#define PERI_CRG48_CLK_125M            ((1 << 2) | (1 << 3))

#define SFC_ADDR_MODE_REG            (0x8C)
#define SFC_ADDR_MODE_MASK            (0x80)
#define SFC_CLSEL_MASK                (0xC)
#define SFC_PERI_CLKDIV1_SHIFT            (28)
#define SFC_PERI_CLKDIV1_MASK            (0xF)

/*****************************************************************************/
#undef GET_SFC_ADDR_MODE
#define GET_SFC_ADDR_MODE ({ \
    int start_up_mode = 0; \
    start_up_mode = readl(IO_ADDRESS(SYS_CTRL_REG_BASE + SFC_ADDR_MODE_REG)); \
    start_up_mode &= SFC_ADDR_MODE_MASK; \
    start_up_mode; })

/*****************************************************************************/
static inline void hisfc350_set_system_clock(unsigned clock, int clk_en)
{
    unsigned int regval = readl(PERI_CRG48);

    regval = regval & (~SFC_CLSEL_MASK);

    if (clock) {
        regval &= ~SFC_CLSEL_MASK;
        regval |= clock & SFC_CLSEL_MASK;
    } else {
        regval &= ~SFC_CLSEL_MASK;
        regval |= PERI_CRG48_CLK_24M; /* Default Clock */
    }

    if (clk_en)
        regval |= PERI_CRG48_CLKEN;

    if (regval != readl(PERI_CRG48))
        writel(regval, (PERI_CRG48));
}

/*****************************************************************************/
static inline void hisfc350_get_best_clock(unsigned int *clock)
{
    int ix;
    int clk_reg;

#define CLK_2X(_clk)    (((_clk) + 1) >> 1)
    unsigned int sysclk[] = {
        CLK_2X(24),    PERI_CRG48_CLK_24M,
        CLK_2X(75),    PERI_CRG48_CLK_75M,
        CLK_2X(125),    PERI_CRG48_CLK_125M,
        0, 0,
    };
#undef CLK_2X

    clk_reg = PERI_CRG48_CLK_24M;
    for (ix = 0; sysclk[ix]; ix += 2) {
        if (*clock < sysclk[ix])
            break;
        clk_reg = sysclk[ix + 1];
    }

    *clock = clk_reg;
}

/*****************************************************************************/
#ifdef CONFIG_HISFC350_SHOW_CYCLE_TIMING
static inline char * hisfc350_get_clock_str(unsigned int clk_reg)
{
    static char buffer[40];

    /* calculate reference PERI_CLKDIV1[31:28] */
    SFC_PR(BT_DBG, "clk_reg=0x%0x.\n", clk_reg);
    clk_reg = 216 / ((clk_reg >> SFC_PERI_CLKDIV1_SHIFT)
                & SFC_PERI_CLKDIV1_MASK);
    (VOID)sprintf_s(buffer, sizeof(buffer), "%dM", clk_reg);

    return buffer;
}
#endif /* CONFIG_PERI_SHOW_CYCLE_TIMING */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */


#endif

