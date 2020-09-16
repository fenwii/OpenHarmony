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

#ifndef __ADC_DRV_H__
#define __ADC_DRV_H__
#include <hi_types.h>
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif  /* __cplusplus */


#define LS_ADC_CLK_DIV1_REG     CLDO_CTL_CLK_DIV1_REG
#define LS_ADC_CLK_DIV1_OFFSET  9

#define HI_LS_ADC_REG_BASE      0x40070000 /* LD ADC base address */
#define REG_ADC_CFG      (HI_LS_ADC_REG_BASE + 0x00)
#define REG_ADC_FIFO_CFG (HI_LS_ADC_REG_BASE + 0x04)
#define REG_ADC_IMSC     (HI_LS_ADC_REG_BASE + 0x08)
#define REG_ADC_CR       (HI_LS_ADC_REG_BASE + 0x0C)
#define REG_ADC_SR       (HI_LS_ADC_REG_BASE + 0x10)
#define REG_ADC_RIS      (HI_LS_ADC_REG_BASE + 0x14)
#define REG_ADC_MIS      (HI_LS_ADC_REG_BASE + 0x18)
#define REG_ADC_START    (HI_LS_ADC_REG_BASE + 0x1C)
#define REG_ADC_STOP     (HI_LS_ADC_REG_BASE + 0x20)
#define REG_ADC_DR       (HI_LS_ADC_REG_BASE + 0x24)
#define REG_ADC_CTRL     (HI_LS_ADC_REG_BASE + 0x28)
#define REG_ADC_EN       (HI_LS_ADC_REG_BASE + 0x2C)

#define ADC_INT_FIFO_WATER_LINE (1 << 1)
#define ADC_INT_FIFO_OVER_FLOW  (1 << 0)

#define ADC_SR_RNE (1 << 0) /* FIFO not empty flag: 0:empty 1:not empty */
#define ADC_SR_RFF (1 << 1) /* FIFO full flag 0:not full 1:full */
#define ADC_SR_BSY (1 << 2) /* ADC busy flag 0:idle 1:busy */

#define ADC_SCAN_START  1
#define ADC_SCAN_STOP   1
#define ADC_POWER_ON    0
#define ADC_POWER_OFF   1
#define ADC_ISR_DISABLE 0

/*
 * The longest time to get 1 data is ((0xfff+(18*8)+3)*334)ns
 * The unit of this cnt is about 5us
 */
#define ADC_PER_DATA_TIMEOUT_CNT 500
#define ADC_LOOP_DELAY_US        5
hi_u32 get_average_ref_vlt(hi_u16 *voltage);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif  /* __cplusplus */

#endif
