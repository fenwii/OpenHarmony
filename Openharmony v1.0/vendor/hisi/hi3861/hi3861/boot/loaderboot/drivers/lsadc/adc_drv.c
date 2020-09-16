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

#include "adc_drv.h"

#include <hi_boot_rom.h>

hi_bool adc_fifo_is_empty(hi_void)
{
    hi_u32 reg_val = hi_reg_read_val32(REG_ADC_SR);
    if (reg_val & ADC_SR_RNE) {
        return HI_FALSE;
    }
    return HI_TRUE;
}

hi_void adc_scan_stop(hi_void)
{
    hi_reg_write(REG_ADC_STOP, ADC_SCAN_STOP);
    hi_reg_write(REG_ADC_IMSC, ADC_ISR_DISABLE);
    while (adc_fifo_is_empty() == HI_FALSE) {
        (hi_void)hi_reg_read_val32(REG_ADC_DR);
    }
}

#define hi_reg_getbits16(addr, pos, bits) ((hi_reg_read_val16(addr) >> (pos)) & (((unsigned short)1 << (bits)) - 1))
#define GLB_CTL_REFCLK_FEQ_START_BIT       0
#define GLB_CTL_REFCLK_FEQ_BITS            1


hi_u32 get_ref_voltage(hi_u16 *voltage)
{
    hi_u16 data = 0;
    hi_u16 reg_val;
    hi_u16 timeout_cnt = 0;
    /* set adc clk div */
    hi_reg_read16(LS_ADC_CLK_DIV1_REG, reg_val);
    reg_val &= ~(0xF << LS_ADC_CLK_DIV1_OFFSET);
    if (hi_reg_getbits16(GLB_CTL_REFCLK_FEQ_STATUS_REG, GLB_CTL_REFCLK_FEQ_START_BIT, GLB_CTL_REFCLK_FEQ_BITS)) {
        reg_val |= (0x7 << LS_ADC_CLK_DIV1_OFFSET);
    } else {
        reg_val |= (0xC << LS_ADC_CLK_DIV1_OFFSET);
    }
    hi_reg_write16(LS_ADC_CLK_DIV1_REG, reg_val);
    /* adc power on */
    hi_reg_write(REG_ADC_EN, ADC_POWER_OFF);
    udelay(1);
    hi_reg_write(REG_ADC_EN, ADC_POWER_ON);
    /* set basic info */
    /*
     channel: 0x80 << 0
     equ_model_sel: 0x2 << 8
     rst_cnt: 0xF << 12
     adc_cfg->cur_bais: 0 << 24
     fifo_water_line: 0x6
    */
    hi_reg_write(REG_ADC_CFG, 0xf280); /* 0xf280 */
    hi_reg_write(REG_ADC_FIFO_CFG, 0x6);
    /* determine is busy */
    if (hi_reg_read_val32(REG_ADC_SR) & ADC_SR_BSY) {
        adc_scan_stop();
    }
    /* start scan */
    hi_reg_write(REG_ADC_START, ADC_SCAN_START);
    while (timeout_cnt < ADC_PER_DATA_TIMEOUT_CNT) {
        if (!adc_fifo_is_empty()) {
            data = (hi_u16)hi_reg_read_val32(REG_ADC_DR);
            break;
        }
        timeout_cnt++;
        udelay(ADC_LOOP_DELAY_US);
    }
    adc_scan_stop();
    hi_reg_write(REG_ADC_EN, ADC_POWER_OFF); /* POWER DOWN */
    if (timeout_cnt >= ADC_PER_DATA_TIMEOUT_CNT) {
        return HI_ERR_TIMEOUT;
    }
    data = data & 0xFFF; /* 0xFFF Obtains the lower 12 bits.CNcomment:获取低12bit数据位 */
    *voltage = ((hi_u32)data * 180) >> 10;   /* bypass:180, flashLDO: 171 = 180*0.95,coefficients: 10  Units: 0.01V */
    return HI_ERR_SUCCESS;
}

hi_u32 get_average_ref_vlt(hi_u16 *voltage)
{
    hi_u32 ret;
    hi_u16 vlt;
    hi_u32 vlt_total = 0;
    ret = get_ref_voltage(&vlt);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    vlt_total += vlt;
    ret = get_ref_voltage(&vlt);
    if (ret != HI_ERR_SUCCESS) {
        *voltage = (hi_u16) vlt_total;
        return HI_ERR_SUCCESS;
    }
    vlt_total += vlt;
    ret = get_ref_voltage(&vlt);
    if (ret != HI_ERR_SUCCESS) {
        *voltage = (hi_u16) (vlt_total>>1);
        return HI_ERR_SUCCESS;
    }
    vlt_total += vlt;
    *voltage = (hi_u16) ((vlt_total) / 3); /* 3 */
    return HI_ERR_SUCCESS;
}
