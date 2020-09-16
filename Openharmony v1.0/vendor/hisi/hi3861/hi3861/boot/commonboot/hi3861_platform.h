/*
 * @file hi_3861_platform.h
 *
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

#ifndef __HI3861_PLATFORM_H__
#define __HI3861_PLATFORM_H__

/* The CPU configuration memory size is 120KB, which cannot be modified. */
#define SRAM_LENGTH                 0x0001E000 /* CPU SRAM 0x100000-0x11DFFF 120KB */

/* Configure the memory start address. This value cannot be modified. */
#define SRAM_START_ADDR             0x00100000

#define CONFIG_CPU_CLOCK            160000000
#define CONFIG_UART_CLOCK           80000000

#define HI_CHIP_ID_1131SV200        0xFF /* Refresh after Asic */

#define CALI_PMU_32K_CLK_VAL        10
#define TCXO_CLK_40MHZ              40000000
#define TCXO_CLK_24MHZ              24000000
#define CONFIG_WDT_CLOCK            80000000

/* GLOBAL CONTROL REG */
#define GLB_CTL_BASE                        0x50000000
#define GLB_CTL_SYS_CTL_ID_REG              (GLB_CTL_BASE + 0x0)
#define GLB_CTL_AON_SOFT_RST_W_REG          (GLB_CTL_BASE + 0x20)
#define GLB_CTL_SOFT_RST_WCPU_REG           (GLB_CTL_BASE + 0x24)
#define GLB_CTL_SOFT_GLB_RESET_CFG          (GLB_CTL_BASE + 0x28)
#define GLB_CTL_GLB_WDT_RST_SEL_REG         (GLB_CTL_BASE + 0x30)
#define GLB_CTL_WDT_RST_SEL_REG             (GLB_CTL_BASE + 0x34)
#define GLB_CTL_AON_CKEN_REG                (GLB_CTL_BASE + 0x40)
#define GLB_CTL_GLB_AON_32K_CLKEN_REG       (GLB_CTL_BASE + 0x50)
#define GLB_CTL_A32K_DIV_REG                (GLB_CTL_BASE + 0x70)
#define GLB_CTL_TCXO_DIV_REG                (GLB_CTL_BASE + 0x74)
#define GLB_CTL_AON_PERP_CLKSEL_W_REG       (GLB_CTL_BASE + 0x90)
#define GLB_CTL_RC_32K_TCXO_SEL_REG         (GLB_CTL_BASE + 0x94)
#define GLB_CTL_AON_32K_SEL_REG             (GLB_CTL_BASE + 0x98)
#define GLB_CTL_SYS_TICK_CFG_REG            (GLB_CTL_BASE + 0xC0)
#define GLB_CTL_SYS_TICK_VALUE_0_REG        (GLB_CTL_BASE + 0xD0)
#define GLB_CTL_SYS_TICK_VALUE_1_REG        (GLB_CTL_BASE + 0xD4)
#define GLB_CTL_SYS_TICK_VALUE_2_REG        (GLB_CTL_BASE + 0xD8)
#define GLB_CTL_SYS_TICK_VALUE_3_REG        (GLB_CTL_BASE + 0xDC)
#define GLB_CTL_CLKMUX_STS_REG              (GLB_CTL_BASE + 0x110)
#define GLB_CTL_DEBUG_CLKEN_REG             (GLB_CTL_BASE + 0x170)
#define GLB_CTL_SOFT_INT_EN_REG             (GLB_CTL_BASE + 0x280)
#define GLB_CTL_SOFT_INT_SET_REG            (GLB_CTL_BASE + 0x284)
#define GLB_CTL_SOFT_INT_CLR_REG            (GLB_CTL_BASE + 0x288)
#define GLB_CTL_SOFT_INT_STS_REG            (GLB_CTL_BASE + 0x28C)
#define GLB_CTL_INT_SEL_REG                 (GLB_CTL_BASE + 0x290)
#define GLB_CTL_REFCLK_FEQ_STATUS_REG       (GLB_CTL_BASE + 0x358)
#define GLB_CTL_EXT_TSF_CTRL_REG            (GLB_CTL_BASE + 0x400)
#define GLB_CTL_CALI_32K_TCXO_CTL_REG       (GLB_CTL_BASE + 0x800)
#define GLB_CTL_CALI_32K_TCXO_CNT_L_REG     (GLB_CTL_BASE + 0x810)
#define GLB_CTL_CALI_32K_TCXO_CNT_H_REG     (GLB_CTL_BASE + 0x814)
#define GLB_CTL_CALI_32K_TCXO_RESULT_L_REG  (GLB_CTL_BASE + 0x818)
#define GLB_CTL_CALI_32K_TCXO_RESULT_H_REG  (GLB_CTL_BASE + 0x81C)
#define GLB_CTL_AON_ICM_PRIORITY_REG        (GLB_CTL_BASE + 0xF30)
#define GLB_CTL_MEM_CLK_FORCE_ON_REG        (GLB_CTL_BASE + 0xF50)
#define GLB_CTL_MARGIN_ADJ_REG              (GLB_CTL_BASE + 0xF54)
#define GLB_CTL_MARGIN_ADJ_AB               (GLB_CTL_BASE + 0xF58)
#define GLB_CTL_DEFAULT_SLV_EN_REG          (GLB_CTL_BASE + 0xF84)
#define GLB_CTL_DEFAULT_SLV_HIT_STATUS_REG  (GLB_CTL_BASE + 0xF88)
#define GLB_CTL_DEFAULT_SLV_HIT_CLR_REG     (GLB_CTL_BASE + 0xF8C)

/* CLDO CONTROL REG */
#define CLDO_CTL_RB_BASE            0x40010000
#define CLDO_CTL_SOFT_RESET_REG     (CLDO_CTL_RB_BASE + 0x20)
#define CLDO_CTL_WDG_RST_SEL_REG    (CLDO_CTL_RB_BASE + 0x28)
#define CLDO_CTL_RB_CLKEN_REG       (CLDO_CTL_RB_BASE + 0x30)
#define CLDO_CTL_CLK_SEL_REG        (CLDO_CTL_RB_BASE + 0x38)
#define CLDO_CTL_SOFT_RESET2_REG    (CLDO_CTL_RB_BASE + 0x3C)
#define CLDO_CTL_WDG_RST_SEL1_REG   (CLDO_CTL_RB_BASE + 0x4C)
#define CLDO_CTL_CLKMUX_STS_REG     (CLDO_CTL_RB_BASE + 0x64)
#define CLDO_CTL_CLK_DIV1_REG       (CLDO_CTL_RB_BASE + 0x78)
#define CLDO_CTL_PKT_CPU_MEM_SEL    (CLDO_CTL_RB_BASE + 0x100)
#define CLDO_CTL_UART_JTAG_CFG_REG  (CLDO_CTL_RB_BASE + 0x250)

#define EFUSE_RST_BIT               9
#define JTAG_SWE_ENABLE             (1<<3)  /* [3] jtag ctrl */
#define UART0_SWE_ENABLE            (1<<0)  /* [0] uart0 ctrl */
#define UART1_SWE_ENABLE            (1<<1)  /* [1] uart1 ctrl */
#define UART2_SWE_ENABLE            (1<<2)  /* [2] uart2 ctrl */

/* PMU CMU CONTROL REG */
#define PMU_CMU_CTL_BASE                            0x50002000
#define PMU_CMU_CTL_UDSLEEP_BUTTON_CTRL_REG         (PMU_CMU_CTL_BASE + 0x020)
#define PMU_CMU_CTL_UDSLEEP_BUTTON_RPT_REG          (PMU_CMU_CTL_BASE + 0x024)
#define PMU_CMU_CTL_OSC_TRIM_REG                    (PMU_CMU_CTL_BASE + 0x028)
#define PMU_CMU_CTL_PMU_MAN_CLR_0_REG               (PMU_CMU_CTL_BASE + 0x104)
#define PMU_CMU_CTL_FLASHLDO_CFG_1_REG              (PMU_CMU_CTL_BASE + 0x260)
#define PMU_CMU_CTL_GATE_TSENSOR_VDDIO_REG          (PMU_CMU_CTL_BASE + 0x350)
#define PMU_CMU_CTL_CMU_DBG_SEL_REG                 (PMU_CMU_CTL_BASE + 0x414)
#define PMU_CMU_CTL_CLK_480M_GT_REG                 (PMU_CMU_CTL_BASE + 0x420)
#define PMU_CMU_CTL_CLK_192M_GT_REG                 (PMU_CMU_CTL_BASE + 0x42C)
#define PMU_CMU_CTL_CLK_960M_GT_REG                 (PMU_CMU_CTL_BASE + 0x430)
#define PMU_CMU_CTL_REFDIV_REG                      (PMU_CMU_CTL_BASE + 0x500)
#define PMU_CMU_CTL_FBDIV_REG                       (PMU_CMU_CTL_BASE + 0x504)
#define PMU_CMU_CTL_FRAC_L_REG                      (PMU_CMU_CTL_BASE + 0x508)
#define PMU_CMU_CTL_FRAC_H_REG                      (PMU_CMU_CTL_BASE + 0x50C)
#define PMU_CMU_CTL_CMU_MISC_PD_REG                 (PMU_CMU_CTL_BASE + 0x514)
#define PMU_CMU_CTL_CMU_CLK_SEL_REG                 (PMU_CMU_CTL_BASE + 0x518)
#define PMU_CMU_CTL_CMU_STATUS_RAW_REG              (PMU_CMU_CTL_BASE + 0x600)
#define PMU_CMU_CTL_SYS_STATUS_REG                  (PMU_CMU_CTL_BASE + 0x804)
#define PMU_CMU_CTL_WLAN_STA0_ALLOW_TO_SLEEP_REG    (PMU_CMU_CTL_BASE + 0x900)
#define PMU_CMU_CTL_WLAN_STA1_ALLOW_TO_SLEEP_REG    (PMU_CMU_CTL_BASE + 0x904)
#define PMU_CMU_CTL_WLAN_AP0_ALLOW_TO_SLEEP_REG     (PMU_CMU_CTL_BASE + 0x908)
#define PMU_CMU_CTL_WLAN_PF_ALLOW_TO_SLEEP_REG      (PMU_CMU_CTL_BASE + 0x90C)
#define PMU_CMU_CTL_WLAN_HOST_ALLOW_TO_SLEEP_REG    (PMU_CMU_CTL_BASE + 0x910)
#define PMU_CMU_CTL_WLAN_SLP_EVT_EN_REG             (PMU_CMU_CTL_BASE + 0x920)
#define PMU_CMU_CTL_WLAN_SLP_EVT_CLR_REG            (PMU_CMU_CTL_BASE + 0x924)
#define PMU_CMU_CTL_WLAN_SLP_INT_CLR_REG            (PMU_CMU_CTL_BASE + 0x934)
#define PMU_CMU_CTL_WLAN_WKUP_EVT_EN_REG            (PMU_CMU_CTL_BASE + 0x940)
#define PMU_CMU_CTL_WLAN_WKUP_EVT_CLR_REG           (PMU_CMU_CTL_BASE + 0x944)
#define PMU_CMU_CTL_WLAN_WKUP_INT_EN_REG            (PMU_CMU_CTL_BASE + 0x950)
#define PMU_CMU_CTL_WLAN_WKUP_INT_CLR_REG           (PMU_CMU_CTL_BASE + 0x954)

/* WLAN CONTROL REG */
#define W_CTL_BASE_ADDR                     0x40028000
#define W_CTL_MAC_WDT_RST_SEL_REG           (W_CTL_BASE_ADDR + 0x0034)
#define W_CTL_PHY_WDT_RST_SEL_REG           (W_CTL_BASE_ADDR + 0x0038)
#define W_CTL_WDT_RST_SEL_REG               (W_CTL_BASE_ADDR + 0x003C)
#define W_CTL_CPU_MAC_CLK_DIV_REG           (W_CTL_BASE_ADDR + 0x0070)
#define W_CTL_UART01_CKDIV_OFFSET           (W_CTL_BASE_ADDR + 0x0074)
#define W_CTL_UART2_CKDIV_OFFSET            (W_CTL_BASE_ADDR + 0x0090)
#define W_CTL_W_TCXO_SEL_REG                (W_CTL_BASE_ADDR + 0x0118)
#define W_CTL_CLKMUX_STS_DIV_STS_REG        (W_CTL_BASE_ADDR + 0x0130)

/* DIAG CTL REG */
#define DIAG_CTL_BASE               0x40060000
#define DIAG_CTL_GP_REG0_REG        (DIAG_CTL_BASE + 0x010) /* used to save rsa key */
#define DIAG_CTL_GP_REG1_REG        (DIAG_CTL_BASE + 0x014) /* used to save rsa key */
#define DIAG_CTL_GP_REG2_REG        (DIAG_CTL_BASE + 0x018) /* used to save ecc key */
#define DIAG_CTL_GP_REG3_REG        (DIAG_CTL_BASE + 0x01C) /* used to save ecc key */

/* DEVICE REG */
#define HI_WDG_REG_BASE             0x40000000
#define HI_GPIO_REG_BASE            0x50006000
#define HI_IOCFG_REG_BASE           0x5000A000
#define HI_EFUSE_REG_BASE           0x40078000
#define HI_SFC_REG_BASE             0x40800000

#define HI_UART0_REG_BASE           0x40008000
#define HI_UART1_REG_BASE           0x40009000
#define HI_UART2_REG_BASE           0x4000a000

#endif
