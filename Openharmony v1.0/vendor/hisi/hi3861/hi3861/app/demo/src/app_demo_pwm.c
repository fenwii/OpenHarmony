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

#include <app_demo_pwm.h>

hi_void pwm_0_demo(hi_void)
{
    hi_pwm_init(HI_PWM_PORT_PWM0);
    hi_pwm_set_clock(PWM_CLK_160M);
    hi_pwm_start(HI_PWM_PORT_PWM0, 750, 1500); /* duty: 750 freq:1500 */
}

hi_void pwm_1_demo(hi_void)
{
    hi_pwm_init(HI_PWM_PORT_PWM1);
    hi_pwm_set_clock(PWM_CLK_160M);
    hi_pwm_start(HI_PWM_PORT_PWM1, 750, 1500); /* duty: 750 freq:1500 */
}

hi_void pwm_2_demo(hi_void)
{
    hi_pwm_init(HI_PWM_PORT_PWM2);
    hi_pwm_set_clock(PWM_CLK_160M);
    hi_pwm_start(HI_PWM_PORT_PWM2, 750, 1500); /* duty: 750 freq:1500 */
}

hi_void pwm_3_demo(hi_void)
{
    hi_pwm_init(HI_PWM_PORT_PWM3);
    hi_pwm_set_clock(PWM_CLK_160M);
    hi_pwm_start(HI_PWM_PORT_PWM3, 750, 1500); /* duty: 750 freq:1500 */
}

hi_void pwm_4_demo(hi_void)
{
    hi_pwm_init(HI_PWM_PORT_PWM4);
    hi_pwm_set_clock(PWM_CLK_160M);
    hi_pwm_start(HI_PWM_PORT_PWM4, 750, 1500); /* duty: 750 freq:1500 */
}

hi_void pwm_5_demo(hi_void)
{
    hi_pwm_init(HI_PWM_PORT_PWM5);
    hi_pwm_set_clock(PWM_CLK_160M);
    hi_pwm_start(HI_PWM_PORT_PWM5, 750, 1500); /* duty: 750 freq:1500 */
}

hi_void app_demo_pwm(hi_void)
{
    printf("start test pwm");

    pwm_0_demo();
    pwm_1_demo();
    pwm_2_demo();
    pwm_3_demo();
    pwm_4_demo();
    pwm_5_demo();

    printf("please use an oscilloscope to check the output waveform!");
}

