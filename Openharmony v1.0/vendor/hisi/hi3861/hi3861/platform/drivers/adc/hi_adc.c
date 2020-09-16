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

#include <hi_isr.h>
#include <hi_time.h>
#include <hi_clock.h>

#include "adc_drv.h"

#define CHECK_EMPTY_MAX_TIME_US  3000 /* 344ns * (0xfff + 18) * 2 = 2.8ms ，reserved 3ms */

HI_ALWAYS_STAIC_INLINE hi_bool check_adc_fifo_empty(hi_void)
{
    hi_u32 reg_val = hi_reg_read_val32(REG_ADC_SR);
    if (reg_val & ADC_SR_RNE) {
        return HI_FALSE;
    }
    return HI_TRUE;
}

HI_ALWAYS_STAIC_INLINE hi_void wait_adc_fifo_empty(hi_void)
{
    hi_u32 timeout = CHECK_EMPTY_MAX_TIME_US;
    while ((check_adc_fifo_empty() == HI_FALSE) && (timeout > 0)) {
        (hi_void)hi_reg_read_val32(REG_ADC_DR);
        hi_udelay(1);
        timeout--;
    }
}

HI_ALWAYS_STAIC_INLINE hi_u32 adc_check_parameter(hi_adc_channel_index channel, hi_u16 *data,
    hi_adc_equ_model_sel equ_model, hi_adc_cur_bais cur_bais, hi_u16 delay_cnt)
{
    if ((channel > HI_ADC_CHANNEL_7) || (data == HI_NULL) || (equ_model > HI_ADC_EQU_MODEL_8) ||
        (cur_bais > HI_ADC_CUR_BAIS_3P3V) || (delay_cnt > 0xFF0)) {
        return HI_ERR_ADC_PARAMETER_WRONG;
    }
    return HI_ERR_SUCCESS;
}

hi_u32 hi_adc_read(hi_adc_channel_index channel, hi_u16 *data, hi_adc_equ_model_sel equ_model,
    hi_adc_cur_bais cur_bais, hi_u16 delay_cnt)
{
    hi_u16 reg_val, int_value;
    hi_u32 timeout_cnt = 0;
    adc_cfg_reg_s adc_ctl = {0};
    if (adc_check_parameter(channel, data, equ_model, cur_bais, delay_cnt) != HI_ERR_SUCCESS) {
        return HI_ERR_ADC_PARAMETER_WRONG;
    }

    hi_xtal_clock clock = hi_get_xtal_clock();
    hi_reg_read16(LS_ADC_CLK_DIV1_REG, reg_val);
    reg_val &= ~(0xF << LS_ADC_CLK_DIV1_OFFSET);
    if (clock == HI_XTAL_CLOCK_24M) {
        reg_val |= (0x7 << LS_ADC_CLK_DIV1_OFFSET);
    } else if (clock == HI_XTAL_CLOCK_40M) {
        reg_val |= (0xC << LS_ADC_CLK_DIV1_OFFSET);
    }
    hi_reg_write16(LS_ADC_CLK_DIV1_REG, reg_val);
    int_value = hi_int_lock();
    hi_reg_write32(REG_ADC_EN, ADC_POWER_ON);

    adc_ctl.ch_vld = (hi_u32)(1 << (hi_u32)channel);
    adc_ctl.equ_model = equ_model;
    adc_ctl.cur_bais = cur_bais;
    adc_ctl.delay_cnt = delay_cnt + 0xF;
    hi_reg_write32(REG_ADC_CFG, *(volatile hi_u32 *)&adc_ctl);

    hi_reg_write32(REG_ADC_START, ADC_SCAN_START);

    while (timeout_cnt < ADC_PER_DATA_TIMEOUT_CNT) {
        if (!check_adc_fifo_empty()) {
            *data = (hi_u16)hi_reg_read_val32(REG_ADC_DR);
            if ((*data >> ADC_DATA_BIT_WIDTH) == channel) {
                *data = *data & 0xFFF;
                break;
            }
        }
        hi_udelay(ADC_LOOP_DELAY_US);
        timeout_cnt++;
    }
    if (timeout_cnt >= ADC_PER_DATA_TIMEOUT_CNT) {
        hi_int_restore(int_value);
        return HI_ERR_ADC_TIMEOUT;
    }
    hi_reg_write32(REG_ADC_STOP, ADC_SCAN_STOP);
    hi_reg_write32(REG_ADC_IMSC, ADC_ISR_DISABLE);
    wait_adc_fifo_empty();
    hi_reg_write32(REG_ADC_EN, ADC_POWER_OFF);
    hi_int_restore(int_value);
    return HI_ERR_SUCCESS;
}

hi_float hi_adc_convert_to_voltage(hi_u16 data)
{
    float voltage = (float)data * 1.8 * 4 / 4096; /* adc code equals: voltage/4/1.8*4096  */
    return voltage;
}

