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

#include <hi_types_base.h>
#include <hi_time.h>
#include <hi_i2c.h>
#include "es8311_codec.h"

#define CODEC_DEBUG
#ifdef CODEC_DEBUG
#define codec_print(ftm...) do { printf(ftm); printf("\r\n"); } while (0);
#else
#define codec_print(ftm...)
#endif

hi_u32 codec_write_reg(hi_u8 reg, hi_u8 val)
{
    hi_i2c_data i2c_data;
    hi_u8 send_data[2] = { reg, val }; /* size 2 */

    i2c_data.send_buf = send_data;
    i2c_data.send_len = 2;             /* send_len is 2 */

    return hi_i2c_write(HI_I2C_IDX_1, CODEC_DEVICE_ADDR, &i2c_data);
}

hi_u32 codec_read_reg(hi_u8 reg, hi_u8 *val)
{
    hi_i2c_data i2c_data;

    i2c_data.send_buf = (hi_u8*)&reg;
    i2c_data.send_len = 1;
    i2c_data.receive_len = 1;
    i2c_data.receive_buf = val;
    return hi_i2c_writeread(HI_I2C_IDX_1, CODEC_DEVICE_ADDR, &i2c_data);
}

static hi_u32 codec_set_gain(hi_void)
{
    hi_u32 ret = HI_ERR_SUCCESS;
    /* set low or normal power mode */
    ret |= codec_write_reg(ES8311_SYSTEM_REG0E, 0x02);  /* enable analog pga/adc modulator */
    /* normal power mode */
    ret |= codec_write_reg(ES8311_SYSTEM_REG0F, 0x44);
    /* set adc */
    ret |= codec_write_reg(ES8311_ADC_REG15, 0x40);     /* set softramp->00 */
    ret |= codec_write_reg(ES8311_ADC_REG1B, 0x0A);     /* set adc hpf */
    ret |= codec_write_reg(ES8311_ADC_REG1C, 0x6A);     /* set adc hpf,ADC_EQ bypass */
    ret |= codec_write_reg(ES8311_ADC_REG17, 0xBF);     /* set adc digtal vol */
    /* set dac */
    ret |= codec_write_reg(ES8311_DAC_REG37, 0x48);     /* set dac softramp,disable DAC_EQ */
    ret |= codec_write_reg(ES8311_DAC_REG32, 0xBF);

    /* only set adc alc funtion for amic record */
    ret |= codec_write_reg(ES8311_ADC_REG16, 0x22);     /* set adc gain scale up */
    ret |= codec_write_reg(ES8311_ADC_REG17, 0xDF);     /* set adc alc maxgain */
    ret |= codec_write_reg(ES8311_ADC_REG18, 0x87);     /* adc alc enable,alc_winsize  ->00 */
    ret |= codec_write_reg(ES8311_ADC_REG19, 0xFB);     /* set alc target level */
    ret |= codec_write_reg(ES8311_ADC_REG1A, 0x03);     /* set adc_automute noise gate */
    ret |= codec_write_reg(ES8311_ADC_REG1B, 0xEA);     /* set adc_automute vol */

    return ret;
}

hi_u32 hi_codec_init(const hi_codec_attribute *codec_attr)
{
    if (codec_attr == HI_NULL) {
        return HI_ERR_FAILURE;
    }

    hi_u32 ret;

    /* set adc/dac data form */
    codec_write_reg(ES8311_GPIO_REG44, 0x08);    /* adc to dac disable,ADCDATA=ADC(L)+ADC(R) */
    hi_udelay(5000);  /* 5000us */

    ret = codec_write_reg(ES8311_DAC_REG31, 0x40);      /* mute DAC state machine */
    ret |= codec_write_reg(ES8311_RESET_REG00, 0x1F);   /* Reset the clock and slave mode. */

    ret |= codec_write_reg(ES8311_GP_REG45, 0x00);      /* Pull up the BCLK/LRCK. */

    ret |= codec_write_reg(ES8311_CLK_MANAGER_REG01, 0x30);     /* MCLK and BCLK are enabled. */

    ret |= codec_write_reg(ES8311_CLK_MANAGER_REG02, 0x10);     /* Time required for completing AD/DA conversion: 0x10
                                                                   dig_mclk = mclk_prediv*4 */

    if (codec_attr->sample_rate == HI_CODEC_SAMPLE_RATE_8K) {
        ret |= codec_write_reg(ES8311_CLK_MANAGER_REG02, 0xA0);     /* 0 - dig_mclk=mclk_prediv*1 (default) */
    } else if (codec_attr->sample_rate == HI_CODEC_SAMPLE_RATE_16K) {
        ret |= codec_write_reg(ES8311_CLK_MANAGER_REG02, 0x40);     /* 0 - dig_mclk=mclk_prediv*1 (default) */
    } else if (codec_attr->sample_rate == HI_CODEC_SAMPLE_RATE_32K) {
        ret |= codec_write_reg(ES8311_CLK_MANAGER_REG02, 0x48);     /* 0 - dig_mclk=mclk_prediv*1 (default) */
    } else if (codec_attr->sample_rate == HI_CODEC_SAMPLE_RATE_48K) {
        ret |= codec_write_reg(ES8311_CLK_MANAGER_REG02, 0x00);     /* 0 - dig_mclk=mclk_prediv*1 (default) */
    }

    ret |= codec_write_reg(ES8311_CLK_MANAGER_REG03, 0x10);     /* 16 - 64 * fs(ss) / 32 * fs(ds) (default) */

    ret |= codec_write_reg(ES8311_ADC_REG16, 0x24);             /* ADC gain 4 - 24dB (default) */
    ret |= codec_write_reg(ES8311_CLK_MANAGER_REG04, 0x10);     /* DAC over sample rate : 16 - 64 * fs (default) */
    ret |= codec_write_reg(ES8311_CLK_MANAGER_REG05, 0x00);     /* Frequency division coefficient of the ADC and
                                         DAC clocks, which determines the working frequencies of the ADC and DAC */

    ret |= codec_write_reg(ES8311_SYSTEM_REG0B, 0x00);  /* Determines the power-up duration. */
    ret |= codec_write_reg(ES8311_SYSTEM_REG0C, 0x00);  /* Determines the power-up duration. */
    ret |= codec_write_reg(ES8311_SYSTEM_REG10, 0x1F);  /* Bias setting */
    ret |= codec_write_reg(ES8311_SYSTEM_REG11, 0x7F);  /* internal use */

    /*
     * Set Codec in Slave mode
     */
    ret |= codec_write_reg(ES8311_RESET_REG00, 0x80);   /* csm power on */

    hi_udelay(50000);  /* 50000us */

    ret |= codec_write_reg(ES8311_SYSTEM_REG0D, 0x01);  /*  1 - start up vmid normal speed charge */
    /*
     * select clock source for internal mclk
     */
    ret |= codec_write_reg(ES8311_CLK_MANAGER_REG01, 0x3F);     /* Starts the sampling working clock. */

    /* Selects mic channel 1, select Mic1p-Mic1n ; ADC PGA gain:4 - 12dB */
    ret |= codec_write_reg(ES8311_SYSTEM_REG14, 0x18);
    /* set dac */
    ret |= codec_write_reg(ES8311_SYSTEM_REG12, 0x00);  /*   0 - enable DAC */
    /* enable HP drive */
    ret |= codec_write_reg(ES8311_SYSTEM_REG13, 0x10);  /*  1 - enable output to HP drive */

    if ((codec_attr->resolution == HI_CODEC_RESOLUTION_16BIT)) {
        /* set adc/dac data format */
        ret |= codec_write_reg(ES8311_SDPIN_REG09, 0x0C);   /* set dac format=16bit i2s */
        ret |= codec_write_reg(ES8311_SDPOUT_REG0A, 0x0C);  /* set adc format=16bit i2s */
    } else {
        /* set adc/dac data format */
        ret |= codec_write_reg(ES8311_SDPIN_REG09, 0x00);   /* set dac format=24bit i2s */
        ret |= codec_write_reg(ES8311_SDPOUT_REG0A, 0x00);  /* set adc format=24bit i2s */
    }

    ret |= codec_set_gain();
    ret |= codec_write_reg(ES8311_DAC_REG31, 0x00);     /* unmute DAC state machine */

    return ret;
}
