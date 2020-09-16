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

#ifndef __ES8311_CODEC_H__
#define __ES8311_CODEC_H__

/*
*    ES8311_REGISTER NAME_REG_REGISTER ADDRESS
*/
#define ES8311_RESET_REG00              0x00      /* reset digital,csm,clock manager etc. */

/*
* Clock Scheme Register definition
*/
#define ES8311_CLK_MANAGER_REG01        0x01    /* select clk src for mclk, enable clock for codec */
#define ES8311_CLK_MANAGER_REG02        0x02    /* clk divider and clk multiplier */
#define ES8311_CLK_MANAGER_REG03        0x03    /* adc fsmode and osr  */
#define ES8311_CLK_MANAGER_REG04        0x04    /* dac osr */
#define ES8311_CLK_MANAGER_REG05        0x05    /* clk divier for adc and dac */
#define ES8311_CLK_MANAGER_REG06        0x06    /* bclk inverter and divider */
#define ES8311_CLK_MANAGER_REG07        0x07    /* tri-state, lrck divider */
#define ES8311_CLK_MANAGER_REG08        0x08    /* lrck divider */
#define ES8311_SDPIN_REG09              0x09      /* dac serial digital port */
#define ES8311_SDPOUT_REG0A             0x0A     /* adc serial digital port */
#define ES8311_SYSTEM_REG0B             0x0B     /* system */
#define ES8311_SYSTEM_REG0C             0x0C     /* system */
#define ES8311_SYSTEM_REG0D             0x0D     /* system, power up/down */
#define ES8311_SYSTEM_REG0E             0x0E     /* system, power up/down */
#define ES8311_SYSTEM_REG0F             0x0F     /* system, low power */
#define ES8311_SYSTEM_REG10             0x10     /* system */
#define ES8311_SYSTEM_REG11             0x11     /* system */
#define ES8311_SYSTEM_REG12             0x12     /* system, Enable DAC */
#define ES8311_SYSTEM_REG13             0x13     /* system */
#define ES8311_SYSTEM_REG14             0x14     /* system, select DMIC, select analog pga gain */
#define ES8311_ADC_REG15                0x15        /* ADC, adc ramp rate, dmic sense */
#define ES8311_ADC_REG16                0x16        /* ADC */
#define ES8311_ADC_REG17                0x17        /* ADC, volume */
#define ES8311_ADC_REG18                0x18        /* ADC, alc enable and winsize */
#define ES8311_ADC_REG19                0x19        /* ADC, alc maxlevel */
#define ES8311_ADC_REG1A                0x1A        /* ADC, alc automute */
#define ES8311_ADC_REG1B                0x1B        /* ADC, alc automute, adc hpf s1 */
#define ES8311_ADC_REG1C                0x1C        /* ADC, equalizer, hpf s2 */
#define ES8311_DAC_REG31                0x31        /* DAC, mute */
#define ES8311_DAC_REG32                0x32        /* DAC, volume */
#define ES8311_DAC_REG33                0x33        /* DAC, offset */
#define ES8311_DAC_REG34                0x34        /* DAC, drc enable, drc winsize */
#define ES8311_DAC_REG35                0x35        /* DAC, drc maxlevel, minilevel */
#define ES8311_DAC_REG37                0x37        /* DAC, ramprate */
#define ES8311_GPIO_REG44               0x44       /* GPIO, dac2adc for test */
#define ES8311_GP_REG45                 0x45     /* GP CONTROL */
#define ES8311_CHD1_REGFD               0xFD       /* CHIP ID1 */
#define ES8311_CHD2_REGFE               0xFE       /* CHIP ID2 */
#define ES8311_CHVER_REGFF              0xFF      /* VERSION */

#define ES8311_MAX_REGISTER             0xFF

#define ES8311_PDN_DAC_BIT              (1 << 1)

#define CODEC_DEVICE_ADDR               0x30        /* 0011 00x */

typedef enum {
    HI_CODEC_SAMPLE_RATE_8K = 8,
    HI_CODEC_SAMPLE_RATE_16K = 16,
    HI_CODEC_SAMPLE_RATE_32K = 32,
    HI_CODEC_SAMPLE_RATE_48K = 48,
} hi_codec_sample_rate;

typedef enum {
    HI_CODEC_RESOLUTION_16BIT = 16,
    HI_CODEC_RESOLUTION_24BIT = 24,
} hi_codec_resolution;

typedef struct {
    hi_codec_sample_rate sample_rate;
    hi_codec_resolution resolution;
} hi_codec_attribute;

hi_u32 hi_codec_init(const hi_codec_attribute *codec_attr);

#endif
