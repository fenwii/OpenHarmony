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
#include "asm/dma.h"
#include "asm/io.h"
#include "los_bitmap.h"
#include "mmc/mmc_caps.h"
#include "sdhci/sdhci_reg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/************************************************************************/

#define MAX_MMC_NUM    2
#define USE_MMC0 1
#define USE_MMC1 1

#define MMC0    0
#define MMC1    1

// sdio0 & emmc
#define CONFIG_MMC0_CCLK_MIN    100000     // 100KHz

#ifdef LOSCFG_DRIVERS_EMMC_HS400
#define CONFIG_MMC0_CCLK_MAX    90000000  // 90MHz
#else
#define CONFIG_MMC0_CCLK_MAX    150000000  // 150MHz
#endif

// sdio1
#define CONFIG_MMC1_CCLK_MIN    100000     // 100KHz
#define CONFIG_MMC1_CCLK_MAX    50000000   // 200MHz


///// not exist
#define PERI_CRG86              (CRG_REG_BASE + 0x158)
#define PERI_CRG87              (CRG_REG_BASE + 0x15C)
#define PERI_CRG94              (CRG_REG_BASE + 0x178)
#define PERI_CRG95              (CRG_REG_BASE + 0x17C)
#define PERI_CRG96              (CRG_REG_BASE + 0x180)

#define PERI_CRG106             (CRG_REG_BASE + 0x1A8)
#define PERI_CRG117             (CRG_REG_BASE + 0x01D4)
#define PERI_CRG123             (CRG_REG_BASE + 0x1EC)
#define PERI_CRG133             (CRG_REG_BASE + 0x214)
#define PERI_CRG143             (CRG_REG_BASE + 0x23C)
//////

#define PERI_CRG125 (CRG_REG_BASE + 0x01F4)

// eMMC DRV DLL
#define PERI_CRG127 (CRG_REG_BASE + 0x01FC)
#define PERI_SAM_DRV_SHFT (24)
#define PERI_SAM_DRV_MASK (0x1f << 24)

// SDIO1 DRV DLL
#define PERI_CRG136 (CRG_REG_BASE + 0x0220)
#define PERI_CRG139 (CRG_REG_BASE + 0x022C)

#define PERI_SDIO0_SAMPLB_DLL_CTRL   (CRG_REG_BASE + 0x1f8)
#define PERI_SDIO1_SAMPLB_DLL_CTRL   (CRG_REG_BASE + 0x21c)
#define SDIO_SAMPLB_DLL_CLK_MASK    (0x1fU << 0)
#define SDIO_SAMPLB_SEL(phase)      ((phase) << 0)

#define PERI_SDIO0_DRV_DLL_CTRL   (CRG_REG_BASE + 0x210)
#define PERI_SDIO1_DRV_DLL_CTRL   (CRG_REG_BASE + 0x228)

#define SDIO_DRV_DLL_LOCK       (1U << 15)

#define PERI_SDIO0_SAMPL_DLL_STATUS   (CRG_REG_BASE + 0x208)
#define PERI_SDIO1_SAMPL_DLL_STATUS   (CRG_REG_BASE + 0x224)

#define SDIO_SAMPL_DLL_SLAVE_READY  (1)
#define SDIO_SAMPL_DLL_SLAVE_EN     (1U << 16)

#define PERI_CRG106_EMMC_CRG_REQ (1U << 27)
#define PERI_CRG106_EMMC_CKEN (1U << 28)
#define PERI_CRG106_EMMC_DLL_RST (1U << 29)
#define PERI_CRG106_EMMC_SAM_RST (1U << 30)

#define EMMC_PHY_BASE       IO_DEVICE_ADDR(0x12160000)

#define MMC_FREQ_100K       100000
#define MMC_FREQ_400K       400000
#define MMC_FREQ_25M        25000000
#define MMC_FREQ_50M        50000000
// only support for EMMC chip
#define MMC_FREQ_90M        90000000
#define MMC_FREQ_112P5M     112500000
#define MMC_FREQ_150M       150000000


#define MMC_FREQ_MASK       0x7
#define MMC_FREQ_SHIFT      24
#define SDIO0_CKEN          (1U << 28)
#define SDIO0_CLK_SEL_100K  (0)
#define SDIO0_CLK_SEL_400K  (7)
#define SDIO0_CLK_SEL_25M   (1)
#define SDIO0_CLK_SEL_50M   (2)
#define SDIO0_CLK_SEL_100M  (3)
#define SDIO0_CLK_SEL_125M  (4)
#define SDIO0_CLK_SEL_150M  (5)
#define SDIO0_CLK_SEL_200M  (6)


#define REG_CTRL_BASE           IO_DEVICE_ADDR(0x100C0040)

#define REG_CTRL_SDIO0_CLK      IO_DEVICE_ADDR(0x100C0040)
#define REG_CTRL_SDIO0_CMD      IO_DEVICE_ADDR(0x100C0044)
#define REG_CTRL_SDIO0_DATA0    IO_DEVICE_ADDR(0x100C0048)
#define REG_CTRL_SDIO0_DATA1    IO_DEVICE_ADDR(0x100C004C)
#define REG_CTRL_SDIO0_DATA2    IO_DEVICE_ADDR(0x100C0050)
#define REG_CTRL_SDIO0_DATA3    IO_DEVICE_ADDR(0x100C0054)

#define REG_CTRL_SDIO0_CD_DET IO_DEVICE_ADDR(0x100C005C)

#define REG_CTRL_SDIO0_CD_POW IO_DEVICE_ADDR(0x120C0020)

#ifdef LOSCFG_PLATFORM_HI3516EV200
#define REG_CTRL_SDIO1_CLK      IO_DEVICE_ADDR(0x112c0048)
#define REG_CTRL_SDIO1_CMD      IO_DEVICE_ADDR(0x112c004c)
#define REG_CTRL_SDIO1_DATA0    IO_DEVICE_ADDR(0x112c0064)
#define REG_CTRL_SDIO1_DATA1    IO_DEVICE_ADDR(0x112c0060)
#define REG_CTRL_SDIO1_DATA2    IO_DEVICE_ADDR(0x112c005c)
#define REG_CTRL_SDIO1_DATA3    IO_DEVICE_ADDR(0x112c0058)
#elif defined(LOSCFG_PLATFORM_HI3516EV300)
#define REG_CTRL_SDIO1_CLK      IO_DEVICE_ADDR(0x100C0060)
#define REG_CTRL_SDIO1_CMD      IO_DEVICE_ADDR(0x100C0064)
#define REG_CTRL_SDIO1_DATA0    IO_DEVICE_ADDR(0x100C0068)
#define REG_CTRL_SDIO1_DATA1    IO_DEVICE_ADDR(0x100C006C)
#define REG_CTRL_SDIO1_DATA2    IO_DEVICE_ADDR(0x100C0070)
#define REG_CTRL_SDIO1_DATA3    IO_DEVICE_ADDR(0x100C0074)
#elif defined(LOSCFG_PLATFORM_HI3518EV300)
#define REG_CTRL_SDIO1_CLK      IO_DEVICE_ADDR(0x112C0048)
#define REG_CTRL_SDIO1_CMD      IO_DEVICE_ADDR(0x112C004C)
#define REG_CTRL_SDIO1_DATA0    IO_DEVICE_ADDR(0x112C0064)
#define REG_CTRL_SDIO1_DATA1    IO_DEVICE_ADDR(0x112C0060)
#define REG_CTRL_SDIO1_DATA2    IO_DEVICE_ADDR(0x112C005C)
#define REG_CTRL_SDIO1_DATA3    IO_DEVICE_ADDR(0x112C0058)
#endif

#define REG_CTRL_EMMC_CLK       IO_DEVICE_ADDR(0x100C0014)
#define REG_CTRL_EMMC_CMD       IO_DEVICE_ADDR(0x100C0018)
#define REG_CTRL_EMMC_DATA0     IO_DEVICE_ADDR(0x100C0020)
#define REG_CTRL_EMMC_DATA1     IO_DEVICE_ADDR(0x100C001c)
#define REG_CTRL_EMMC_DATA2     IO_DEVICE_ADDR(0x100C0028)
#define REG_CTRL_EMMC_DATA3     IO_DEVICE_ADDR(0x100C0024)
#define REG_CTRL_EMMC_DATA4     IO_DEVICE_ADDR(0x100C0030)
#define REG_CTRL_EMMC_DATA5     IO_DEVICE_ADDR(0x100C0034)
#define REG_CTRL_EMMC_DATA6     IO_DEVICE_ADDR(0x100C0038)
#define REG_CTRL_EMMC_DATA7     IO_DEVICE_ADDR(0x100C003c)

#define REG_CTRL_EMMC_DS        IO_DEVICE_ADDR(0x100C0058)
#define REG_CTRL_EMMC_RST       IO_DEVICE_ADDR(0x100C005C)

// macro for io_mux
#define IO_CFG_SR               BIT(10)
#define IO_CFG_PULL_DOWN        BIT(9)
#define IO_CFG_PULL_UP          BIT(8)
#define IO_CFG_DRV_STR_MASK     (0xfU << 4)
#define IO_DRV_MASK             (0x7f0)

#define IO_DRV_STR_SEL(str)     ((str) << 4)

#define IO_MUX_CLK_TYPE_EMMC    0x0
#define IO_MUX_CLK_TYPE_SD      0x1
#define IO_MUX_SHIFT(type)      ((type) << 0)
#define IO_MUX_MASK             (0xfU << 0)

enum mmc_width_seletion_mode {
    /* The bus width is auto determined by capabilities of a card and host */
    MMC_WIDTH_SELCTION_AUTO = 0,
    /*
     * The bus width of host and card are both manually forced into 1 bit mode
     * whether the card and host supports 4-bit or not.
     */
    MMC_WIDTH_FORCED_1_BIT,
};

/*
 * Description:
 * This API is used to set the bus width selection mode of sd and sdio host devices.
 * Param: host_id [IN]  ranging from 0 to (MAX_MMC_NUM - 1). The types of hosts, either sd or sdio,
 *                      can be inqueried from user's guide according to the param host_id.
 * Param: type    [IN]  the width selection mode, either MMC_WIDTH_SELCTION_AUTO, or MMC_WIDTH_FORCED_1_BIT.
 *                      please refer to enum mmc_width_seletion_mode for more details.
 * Attention: The width selection mode is default auto mode if this API is not called.
 *            This API should be called before initial and registration of mmc driver.
 */
extern void mmc_width_seletion_mode_set(unsigned int host_id, enum mmc_width_seletion_mode type);

void SDHCI_EnableSample(void *base);
void SDHCI_CardClk(void *base, int action);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif

