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

#include <app_demo_tsensor.h>

hi_u32 g_tsensor_loop_count = 0;

static hi_void tensor_collect_finish_irq(hi_s16 irq_temperature)
{
    hi_u64 cnt;

    cnt = hi_systick_get_cur_tick();
    printf("cnt = %lld\n", cnt);
    printf("read temperature: %d\n", irq_temperature);
    if (g_tsensor_loop_count > TSENSOR_TEST_LOOP) {
        g_tsensor_loop_count = 0;

        hi_tsensor_stop();
        printf("*********stop tsensor***********\n");
        printf("**** End of reading temperature by interrupt mode****\r\n");
    }

    g_tsensor_loop_count++;
}

static hi_void tensor_outtemp_irq(hi_s16 irq_temperature)
{
    hi_s16 temperature;
    temperature = irq_temperature;

    printf("temperature: %d is outtemp!!\n", temperature);
    hi_tsensor_stop();
    printf("*********stop tsensor***********\n");
}

static hi_void tensor_overtemp_irq(hi_s16 irq_temperature)
{
    hi_s16 temperature;
    temperature = irq_temperature;

    printf("temperature: %d is overtemp!!\n", temperature);
    hi_tsensor_destroy();
    printf("*********destroy tsensor***********\n");
}

static hi_void read_temprature_none_irq_single(hi_void)
{
    hi_s32 i;

    for (i = 0; i < TSENSOR_TEST_LOOP; i++) {
        hi_udelay((hi_u32)TSENSOR_GET_TEMPERRATURE_INTERVAL);
        hi_s16 temperature = 0;
        if (hi_tsensor_read_temperature(&temperature) == HI_ERR_SUCCESS) {
            printf("Read success: temperature = %d\n", temperature);
        } else {
            printf("Read fail, continue!\n");
        }
    }

    hi_sleep(TSENSOR_TEST_INTERVAL);
}

/*
 * This demo simply shows how to set temperature protect threshold and read temperature by polling or interrupt mode.
 */
hi_void tsensor_demo(hi_void)
{
    hi_u32 ret;

    hi_sleep(TSENSOR_TEST_INTERVAL);
    printf("\n**** set temperature threshold ****\n");
    /* Set power down temperature threshold. */
    ret = hi_tsensor_set_pdtemp_threshold(TEMPERRATURE_POWER_DOWN_THRESHOLD);
    if (ret != HI_ERR_SUCCESS) {
        printf("Failed to set power down temperature threshold! Err code = %X\n", ret);
        return;
    }

    /* Set over temperature threshold and register callback function. */
    hi_tsensor_set_overtemp_threshold(TEMPERRATURE_OVER_THRESHOLD, tensor_overtemp_irq);
    if (ret != HI_ERR_SUCCESS) {
        printf("Failed to set overtemp temperature threshold! Err code = %X\n", ret);
        return;
    }

    /* Set out temperature threshold and register callback function. */
    hi_tsensor_set_outtemp_threshold(TEMPERRATURE_OUT_THRESHOLD_LOW,
                                     TEMPERRATURE_OUT_THRESHOLD_HIGH, tensor_outtemp_irq);
    if (ret != HI_ERR_SUCCESS) {
        printf("Failed to set outtemp temperature threshold! Err code = %X\n", ret);
        return;
    }
    hi_tsensor_start(HI_TSENSOR_MODE_16_POINTS_SINGLE, TSENSOR_PERIOD_VALUE);
    hi_sleep(TSENSOR_TEST_INTERVAL);
    printf("**** End of setting temperature threshold ****\n");

    printf("\n**** read temperature by polling mode****\n");
    hi_tsensor_start(HI_TSENSOR_MODE_16_POINTS_SINGLE, TSENSOR_PERIOD_VALUE);
    /* Read temperature by polling mode. */
    read_temprature_none_irq_single();
    hi_tsensor_stop();
    printf("**** End of reading temperature by polling mode****\n");

    printf("\n**** read temperature by interrupt mode****\n");
    /* Read temperature by interrupt mode. */
    hi_tsensor_register_temp_collect_finish_int_callback(tensor_collect_finish_irq);
    if (ret != HI_ERR_SUCCESS) {
        return;
    }
    hi_tsensor_start(HI_TSENSOR_MODE_16_POINTS_SINGLE, TSENSOR_PERIOD_VALUE);
}
