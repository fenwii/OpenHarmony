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

#include <hi3861_platform_base.h>
#include <hi_tsensor.h>

#define TSENSOR_BASE_ADDRESS                (W_CTL_BASE_ADDR)
#define TSENSOR_START                       0x0500    /* TSENSOR start register */
#define TSENSOR_CTRL                        0x0504    /* TSENSOR control register */
#define TSENSOR_MAN_STS                     0x0508    /* TSENSOR manual control status register */
#define TSENSOR_AUTO_STS                    0x050C    /* TSENSOR auto control status register */
#define TSENSOR_TRIM_CTRL                   0x0510    /* TSENSOR TRIM configuration register */
#define TSENSOR_TEMP_HIGH_LIMIT             0x0514    /* TSENSOR high temperature threshold register */
#define TSENSOR_TEMP_LOW_LIMIT              0x0518    /* TSENSOR low temperature threshold register */
#define TSENSOR_TEMP_OVER_LIMIT             0x051C    /* TSENSOR over temperature threshold register */
#define TSENSOR_TEMP_INT_EN                 0x0520    /* TSENSOR interrupt configuration register */
#define TSENSOR_TEMP_INT_CLR                0x0524    /* TSENSOR interrupt clear register */
#define TSENSOR_TEMP_INT_STATE              0x0528    /* TSENSOR interrupt state register */
#define TSENSOR_TEMP_PD_LIMIT               0x0530    /* TSENSOR power down temperature threshold register */
#define TSENSOR_AUTO_REFRESH_PERIOD         0x0540    /* TSENSOR auto refresh period control register */
#define TSENSOR_AUTO_REFRESH_CFG            0x0544    /* TSENSOR auto refresh control register */

#define TSENSOR_CLK_GATE_BIT                3
#define TSENSOR_CLK_SET_VALUE               ((hi_u16)1 << (TSENSOR_CLK_GATE_BIT))

typedef struct {
    hi_u16 trim_ctrl;
    hi_u16 high_limit;
    hi_u16 low_limit;
    hi_u16 over_limit;
    hi_u16 pd_limit;
    hi_u16 int_en;
    hi_u16 int_clr;
    hi_u16 clk_en;
    hi_u16 clk_div;
    hi_u16 ctrl;
    hi_u16 refresh_period;
    hi_u16 refresh_en;
    hi_u16 start;
} tsensor_lp_regs;

tsensor_lp_regs g_lp_regs_save = {0};

hi_void  hi_tsensor_lp_save(hi_void)
{
    g_lp_regs_save.trim_ctrl = hi_reg_read_val16(TSENSOR_BASE_ADDRESS + TSENSOR_TRIM_CTRL);
    g_lp_regs_save.high_limit = hi_reg_read_val16(TSENSOR_BASE_ADDRESS + TSENSOR_TEMP_HIGH_LIMIT);
    g_lp_regs_save.low_limit = hi_reg_read_val16(TSENSOR_BASE_ADDRESS + TSENSOR_TEMP_LOW_LIMIT);
    g_lp_regs_save.over_limit = hi_reg_read_val16(TSENSOR_BASE_ADDRESS + TSENSOR_TEMP_OVER_LIMIT);
    g_lp_regs_save.pd_limit = hi_reg_read_val16(TSENSOR_BASE_ADDRESS + TSENSOR_TEMP_PD_LIMIT);

    g_lp_regs_save.int_en = hi_reg_read_val16(TSENSOR_BASE_ADDRESS + TSENSOR_TEMP_INT_EN);
    g_lp_regs_save.int_clr = hi_reg_read_val16(TSENSOR_BASE_ADDRESS + TSENSOR_TEMP_INT_CLR);

    g_lp_regs_save.clk_en = hi_reg_read_val16(W_CTL_UART_MAC80M_CLKEN_REG);
    g_lp_regs_save.clk_div = hi_reg_read_val16(W_CTL_TSENSOR_DIV_REG);
    g_lp_regs_save.ctrl = hi_reg_read_val16(TSENSOR_BASE_ADDRESS + TSENSOR_CTRL);
    g_lp_regs_save.refresh_period = hi_reg_read_val16(TSENSOR_BASE_ADDRESS + TSENSOR_AUTO_REFRESH_PERIOD);
    g_lp_regs_save.refresh_en = hi_reg_read_val16(TSENSOR_BASE_ADDRESS + TSENSOR_AUTO_REFRESH_CFG);

    g_lp_regs_save.start = hi_reg_read_val16(TSENSOR_BASE_ADDRESS + TSENSOR_START);
}

hi_void hi_tsensor_lp_restore(hi_void)
{
    hi_reg_write16((TSENSOR_BASE_ADDRESS + TSENSOR_TRIM_CTRL), g_lp_regs_save.trim_ctrl);
    hi_reg_write16((TSENSOR_BASE_ADDRESS + TSENSOR_TEMP_HIGH_LIMIT), g_lp_regs_save.high_limit);
    hi_reg_write16((TSENSOR_BASE_ADDRESS + TSENSOR_TEMP_LOW_LIMIT), g_lp_regs_save.low_limit);
    hi_reg_write16((TSENSOR_BASE_ADDRESS + TSENSOR_TEMP_OVER_LIMIT), g_lp_regs_save.over_limit);
    hi_reg_write16((TSENSOR_BASE_ADDRESS + TSENSOR_TEMP_PD_LIMIT), g_lp_regs_save.pd_limit);

    hi_reg_write16((TSENSOR_BASE_ADDRESS + TSENSOR_TEMP_INT_EN), g_lp_regs_save.int_en);
    hi_reg_write16((TSENSOR_BASE_ADDRESS + TSENSOR_TEMP_INT_CLR), g_lp_regs_save.int_clr);

    if ((g_lp_regs_save.clk_en & TSENSOR_CLK_SET_VALUE) == TSENSOR_CLK_SET_VALUE) {
        hi_reg_setbit(W_CTL_UART_MAC80M_CLKEN_REG, TSENSOR_CLK_GATE_BIT);
    } else {
        hi_reg_clrbit(W_CTL_UART_MAC80M_CLKEN_REG, TSENSOR_CLK_GATE_BIT);
        hi_reg_setbit((TSENSOR_BASE_ADDRESS + TSENSOR_MAN_STS), 0);
        hi_reg_setbit((TSENSOR_BASE_ADDRESS + TSENSOR_AUTO_STS), 0);
    }

    hi_reg_write16(W_CTL_TSENSOR_DIV_REG, g_lp_regs_save.clk_div);
    hi_reg_write16((TSENSOR_BASE_ADDRESS + TSENSOR_CTRL), g_lp_regs_save.ctrl);
    hi_reg_write16((TSENSOR_BASE_ADDRESS + TSENSOR_AUTO_REFRESH_PERIOD), g_lp_regs_save.refresh_period);
    hi_reg_write16((TSENSOR_BASE_ADDRESS + TSENSOR_AUTO_REFRESH_CFG), g_lp_regs_save.refresh_en);

    hi_reg_write16(TSENSOR_BASE_ADDRESS + TSENSOR_START, g_lp_regs_save.start);
}

