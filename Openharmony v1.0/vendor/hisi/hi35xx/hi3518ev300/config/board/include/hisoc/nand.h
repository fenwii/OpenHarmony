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

#ifndef __HISOC_NAND_H__
#define __HISOC_NAND_H__

#include "asm/platform.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define PERI_CRG52                      (CRG_REG_BASE + 0x00D0)
#define PERI_CRG52_CLK_EN               (1U << 1)
#define PERI_CRG52_CLK_SEL_198M        (1U << 2)

#define REG_SYSSTAT            0x008C
#define BOOT_FROM_NAND            2

static void hinfc620_clk_enable(int enable)
{
    unsigned int reg_val = readl(PERI_CRG52);

    if (enable)
        reg_val |= (PERI_CRG52_CLK_EN | PERI_CRG52_CLK_SEL_198M);
    else
        reg_val &= ~PERI_CRG52_CLK_EN;

    writel(reg_val, (PERI_CRG52));
}
#define check_boot_type() ((readl(SYS_CTRL_REG_BASE + REG_SYSSTAT) >> 4) & 0x3);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif

