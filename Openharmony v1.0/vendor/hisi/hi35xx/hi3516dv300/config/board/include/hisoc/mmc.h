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

#ifndef __HISOC_MMC_H_
#define __HISOC_MMC_H_

/************************************************************************/

#include "asm/platform.h"
#include "asm/io.h"
#include "himci_v200/himci_reg.h"
#include "mmc/mmc_caps.h"
#include "hal_timer.h"
#include "los_printf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/************************************************************************/
#define EMMC_DDR50
#define EMMC_HS200

#define MMC0    0
#define MMC1    1
#define MMC2    2

#define MAX_MMC_NUM    3


/**
 * MMC HOST usable
 * Set to 1: usable
 * Set to 0: not usable
 * sdio0=1, sdio1=2, EMMC=0
 **/
#ifdef LOSCFG_DRIVERS_EMMC
#define USE_MMC0    1
#else
#define USE_MMC0    0
#endif
#define USE_MMC1    1
#define USE_MMC2    1


#define MMC_FREQ_150M    (150000000)
#define MMC_FREQ_100M    (100000000)
#define MMC_FREQ_50M     (50000000)
#define MMC_FREQ_25M     (25000000)

#define CONFIG_MMC0_CCLK_MIN    50000
#define CONFIG_MMC0_CCLK_MAX    MMC_FREQ_100M
#define CONFIG_MMC1_CCLK_MIN    50000
#define CONFIG_MMC1_CCLK_MAX    MMC_FREQ_100M
#define CONFIG_MMC2_CCLK_MIN    50000
#define CONFIG_MMC2_CCLK_MAX    MMC_FREQ_100M


#define CONFIG_MMC0_CLK        MMC_FREQ_50M
#define CONFIG_MMC1_CLK        MMC_FREQ_50M
#define CONFIG_MMC2_CLK        MMC_FREQ_100M


#define CONFIG_MAX_BLK_COUNT    2048
#define CONFIG_MAX_BLK_SIZE     512

#define HIMMC_PAGE_SIZE    4096

/* register mapping */
#define PERI_CRG49              (CRG_REG_BASE + 0xC4)
#define PERI_CRG50              (CRG_REG_BASE + 0xC8)

#define PERI_CRG82              (CRG_REG_BASE + 0x0148)
#define PERI_CRG83              (CRG_REG_BASE + 0x014C)
#define PERI_CRG84              (CRG_REG_BASE + 0x0150)
#define PERI_CRG85              (CRG_REG_BASE + 0x0154)

#define PERI_CRG86       (CRG_REG_BASE + 0x0158)
#define PERI_CRG87       (CRG_REG_BASE + 0x015C)
#define PERI_CRG88       (CRG_REG_BASE + 0x0160)
#define PERI_CRG89       (CRG_REG_BASE + 0x0164)
#define PERI_CRG90       (CRG_REG_BASE + 0x0168)

/* sdio2:eMMC pad ctrl reg */
#define REG_CTRL_EMMC_CCLK    (IO_CTL_REG_BASE + 0)
#define REG_CTRL_EMMC_CCMD    (IO_CTL_REG_BASE + 4)
#define REG_CTRL_EMMC_CDATA0  (IO_CTL_REG_BASE + 8)
#define REG_CTRL_EMMC_CDATA1  (IO_CTL_REG_BASE + 0xc)
#define REG_CTRL_EMMC_CDATA2  (IO_CTL_REG_BASE + 0x10)
#define REG_CTRL_EMMC_CDATA3  (IO_CTL_REG_BASE + 0x14)

#define EMMC_CLK_DS_1V8         0xc0
#define EMMC_CMD_DS_1V8         0x150
#define EMMC_DATA0_DS_1V8       0x1d0
#define EMMC_DATA1_DS_1V8       0x1d0
#define EMMC_DATA2_DS_1V8       0x1d0
#define EMMC_DATA3_DS_1V8       0x1d0

#define SDIO_CLK_SEL_MASK      (3U << 2)
#define SDIO_CLK_SEL_100M      (1U << 2)
#define SDIO_CLK_SEL_50M       (2U << 2)
#define SDIO_CLK_SEL_25M       (3U << 2)
#define SDIO_CKEN              (1U << 1)
#define SDIO_RESET             (1U << 0)

#define SDIO1_CLK_OFFSET    (2)
#define SDIO0_CLK_OFFSET    (10)

#define PHASE_SHIFT        0x2030000
#define READ_THRESHOLD_SIZE    0x2000005
#define DRV_PHASE_SHIFT             (0x4)
#define SMPL_PHASE_SHIFT            (0x1)

#define DDR50_DRV_PHASE_CFG      (0x2)
#define SDR104_DRV_PHASE_CFG     (0x3)

#define HIMCI_EDGE_TUNING
#define HIMCI_PHASE_SCALE 8
#define TUNING_START_PHASE  0
#define TUNING_END_PHASE    7

#define PHASE_NOT_FOUND -1

#define hi_mci_detect_polarity_cfg(mmc_num)    do { } while (0)

/* EMMC=PERI_CRG82, sdio0=PERI_CRG88, sdio1=PERI_CRG85 */
#define hi_mci_soft_reset(mmc_num) do { \
    unsigned int regs[] = {PERI_CRG82, PERI_CRG88, PERI_CRG85}; \
    unsigned int val = 0; \
    if ((int)mmc_num >= 0 && mmc_num <= 2) { \
        val = readl((uintptr_t)regs[mmc_num]); \
        PRINT_DEBUG("0x%x:0x%x\n", regs[mmc_num], val); \
        HalDelayUs(1000); \
        writel(val | 1, (uintptr_t)regs[mmc_num]); \
        val &= ~1; \
        writel(val, (uintptr_t)regs[mmc_num]); \
        PRINT_DEBUG("0x%x:0x%x\n", regs[mmc_num], val); \
    } \
} while (0)


/* MCI_FIFOTH(0x4c) details */
#define BURST_SIZE      (0x6 << 28)
#define RX_WMARK        (0x7f << 16)
#define TX_WMARK        0x80
#define MCI_BMOD_VALUE  (BURST_INCR | BURST_16)

void himci_cfg_phase(unsigned int devid, void *base, enum mmc_bus_timing timing);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif

