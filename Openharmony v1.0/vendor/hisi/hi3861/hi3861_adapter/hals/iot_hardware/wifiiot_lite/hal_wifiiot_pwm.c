/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
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

#include "hi_pwm.h"
#include "hi_errno.h"
#include "hal_wifiiot_errno.h"
#include "hal_wifiiot_pwm.h"

unsigned int HalPwmInit(HalWifiIotPwmPort port)
{
    if (hi_pwm_set_clock(PWM_CLK_160M) != HI_ERR_SUCCESS) {
        return (unsigned int)HAL_WIFI_IOT_FAILURE;
    }
    return hi_pwm_init((hi_pwm_port)port);
}

unsigned int HalPwmDeinit(HalWifiIotPwmPort port)
{
    return hi_pwm_deinit((hi_pwm_port)port);
}

unsigned int HalPwmStart(HalWifiIotPwmPort port, unsigned short duty, unsigned short freq)
{
    return hi_pwm_start((hi_pwm_port)port, duty, freq);
}

unsigned int HalPwmStop(HalWifiIotPwmPort port)
{
    return hi_pwm_stop((hi_pwm_port)port);
}

