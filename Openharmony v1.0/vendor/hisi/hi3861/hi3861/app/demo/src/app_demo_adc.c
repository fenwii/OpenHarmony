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

#define APP_DEMO_ADC
#ifdef APP_DEMO_ADC
#include <app_demo_adc.h>

hi_u16 g_adc_buf[ADC_TEST_LENGTH] = { 0 };

hi_void test_para(hi_void)
{
    hi_u32 ret;
    hi_u16 data = 0;
    printf("********ADC Test Para Set Start********\n");
    ret = hi_adc_read(HI_ADC_CHANNEL_BUTT, &data, HI_ADC_EQU_MODEL_1, HI_ADC_CUR_BAIS_DEFAULT, 0);
    if (ret == HI_ERR_ADC_PARAMETER_WRONG) {
        printf("ADC TEST WRONG Channel SUCCESS!\n");
    }
    ret = hi_adc_read(HI_ADC_CHANNEL_7, HI_NULL, HI_ADC_EQU_MODEL_1, HI_ADC_CUR_BAIS_DEFAULT, 0);
    if (ret == HI_ERR_ADC_PARAMETER_WRONG) {
        printf("ADC TEST WRONG Data point SUCCESS!\n");
    }
    ret = hi_adc_read(HI_ADC_CHANNEL_7, &data, HI_ADC_EQU_MODEL_BUTT, HI_ADC_CUR_BAIS_DEFAULT, 0);
    if (ret == HI_ERR_ADC_PARAMETER_WRONG) {
        printf("ADC TEST WRONG Average Algorithm SUCCESS!\n");
    }
    ret = hi_adc_read(HI_ADC_CHANNEL_7, &data, HI_ADC_EQU_MODEL_1, HI_ADC_CUR_BAIS_BUTT, 0);
    if (ret == HI_ERR_ADC_PARAMETER_WRONG) {
        printf("ADC TEST WRONG Analog Power Control SUCCESS!\n");
    }
    ret = hi_adc_read(HI_ADC_CHANNEL_7, &data, HI_ADC_EQU_MODEL_1, HI_ADC_CUR_BAIS_DEFAULT, 0xFFF);
    if (ret == HI_ERR_ADC_PARAMETER_WRONG) {
        printf("ADC TEST WRONG Reset Count SUCCESS!\n");
    }
}

/* asic adc test  */
hi_void convert_to_voltage(hi_u32 data_len)
{
    hi_u32 i;
    float vlt_max = 0;
    float vlt_min = VLT_MIN;
    hi_u16 vlt;
    for (i = 0; i < data_len; i++) {
        vlt = g_adc_buf[i];
        float voltage = (float)vlt * 1.8 * 4 / 4096.0;  /* vlt * 1.8 * 4 / 4096.0: Convert code into voltage */
        vlt_max = (voltage > vlt_max) ? voltage : vlt_max;
        vlt_min = (voltage < vlt_min) ? voltage : vlt_min;
    }
    printf("vlt_min:%.3f, vlt_max:%.3f \n", vlt_min, vlt_max);
}

hi_void app_demo_adc_test(hi_void)
{
    hi_u32 ret, i;
    hi_u16 data;  /* 10 */
    printf("ADC Test Start\n");

    memset_s(g_adc_buf, sizeof(g_adc_buf), 0x0, sizeof(g_adc_buf));
    for (hi_u8 ch = 0; ch < HI_ADC_CHANNEL_BUTT; ch++) {
        for (i = 0; i < ADC_TEST_LENGTH; i++) {
            ret = hi_adc_read((hi_adc_channel_index)ch, &data, HI_ADC_EQU_MODEL_1, HI_ADC_CUR_BAIS_DEFAULT, 0);
            if (ret != HI_ERR_SUCCESS) {
                printf("ADC Read Fail\n");
                return;
            }
            g_adc_buf[i] = data;
        }
        convert_to_voltage(ADC_TEST_LENGTH);
    }
    printf("ADC Test Channels End\n");

    memset_s(g_adc_buf, sizeof(g_adc_buf), 0x0, sizeof(g_adc_buf));
    for (hi_u8 em = 0; em < HI_ADC_EQU_MODEL_BUTT; em++) {
        for (i = 0; i < ADC_TEST_LENGTH; i++) {
            ret = hi_adc_read(HI_ADC_CHANNEL_7, &data, (hi_adc_equ_model_sel)em, HI_ADC_CUR_BAIS_DEFAULT, 0);
            if (ret != HI_ERR_SUCCESS) {
                printf("ADC Read Fail\n");
                return;
            }
            g_adc_buf[i] = data;
        }
        convert_to_voltage(ADC_TEST_LENGTH);
    }
    printf("ADC Test Average Mode End\n");

    memset_s(g_adc_buf, sizeof(g_adc_buf), 0x0, sizeof(g_adc_buf));
    for (hi_u16 rc = 0; rc <= 0xFF0; rc += 0xF) {
        for (i = 0; i < ADC_TEST_LENGTH; i++) {
            ret = hi_adc_read(HI_ADC_CHANNEL_7, &data, HI_ADC_EQU_MODEL_8, HI_ADC_CUR_BAIS_DEFAULT, rc);
            if (ret != HI_ERR_SUCCESS) {
                printf("ADC Read Fail\n");
                return;
            }
            g_adc_buf[i] = data;
        }
        convert_to_voltage(ADC_TEST_LENGTH);
    }
    printf("ADC Test Reset Count End\n");

    test_para();

    printf("ADC Test End!\n");
}

#endif
