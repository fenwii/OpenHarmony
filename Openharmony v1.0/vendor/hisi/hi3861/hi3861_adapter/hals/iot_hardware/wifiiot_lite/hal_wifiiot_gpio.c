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

#include <stdio.h>
#include "hal_wifiiot_gpio.h"
#include "hal_wifiiot_gpio_ex.h"
#include "hi_gpio.h"
#include "hi_io.h"
#include "hal_wifiiot_errno.h"

unsigned int HalGpioInit(void)
{
    return hi_gpio_init();
}

unsigned int HalGpioSetDir(HalWifiIotGpioIdx id, HalWifiIotGpioDir dir)
{
    return hi_gpio_set_dir((hi_gpio_idx)id, (hi_gpio_dir)dir);
}

unsigned int HalGpioGetDir(HalWifiIotGpioIdx id, HalWifiIotGpioDir *dir)
{
    return hi_gpio_get_dir((hi_gpio_idx)id, (hi_gpio_dir *)dir);
}

unsigned int HalGpioSetOutputVal(HalWifiIotGpioIdx id, HalWifiIotGpioValue val)
{
    return hi_gpio_set_ouput_val((hi_gpio_idx)id, (hi_gpio_value)val);
}

unsigned int HalGpioGetOutputVal(HalWifiIotGpioIdx id, HalWifiIotGpioValue *val)
{
    return hi_gpio_get_output_val((hi_gpio_idx)id, (hi_gpio_value *)val);
}

unsigned int HalGpioGetInputVal(HalWifiIotGpioIdx id, HalWifiIotGpioValue *val)
{
    return hi_gpio_get_input_val((hi_gpio_idx)id, (hi_gpio_value *)val);
}

unsigned int HalGpioRegisterIsrFunc(HalWifiIotGpioIdx id, HalWifiIotGpioIntType intType,
                                    HalWifiIotGpioIntPolarity intPolarity, HalGpioIsrCallbackFunc func, char *arg)
{
    return hi_gpio_register_isr_function((hi_gpio_idx)id, (hi_gpio_int_type)intType, (hi_gpio_int_polarity)intPolarity,
                                         (gpio_isr_callback)func, arg);
}

unsigned int HalGpioUnregisterIsrFunc(HalWifiIotGpioIdx id)
{
    return hi_gpio_unregister_isr_function((hi_gpio_idx)id);
}

unsigned int HalGpioSetIsrMask(HalWifiIotGpioIdx id, unsigned char mask)
{
    return hi_gpio_set_isr_mask((hi_gpio_idx)id, (hi_bool)mask);
}

unsigned int HalGpioSetIsrMode(HalWifiIotGpioIdx id, HalWifiIotGpioIntType intType,
                               HalWifiIotGpioIntPolarity intPolarity)
{
    return hi_gpio_set_isr_mode((hi_gpio_idx)id, (hi_gpio_int_type)intType, (hi_gpio_int_polarity)intPolarity);
}

unsigned int HalGpioDeinit(void)
{
    return hi_gpio_deinit();
}

unsigned int HalIoSetPull(HalWifiIotIoName id, HalWifiIotIoPull val)
{
    if (id == HAL_WIFI_IOT_IO_NAME_MAX) {
        return HAL_WIFI_IOT_ERR_GPIO_INVALID_PARAMETER;
    }
    return hi_io_set_pull((hi_io_name)id, (hi_io_pull)val);
}

unsigned int HalIoSetFunc(HalWifiIotIoName id, unsigned char val)
{
    if (id == HAL_WIFI_IOT_IO_NAME_MAX) {
        return HAL_WIFI_IOT_ERR_GPIO_INVALID_PARAMETER;
    }
    return hi_io_set_func((hi_io_name)id, val);
}

unsigned int HalIoGetPull(HalWifiIotIoName id, HalWifiIotIoPull *val)
{
    if (id == HAL_WIFI_IOT_IO_NAME_MAX) {
        return HAL_WIFI_IOT_ERR_GPIO_INVALID_PARAMETER;
    }
    return hi_io_get_pull((hi_io_name)id, (hi_io_pull *)val);
}

unsigned int HalIoGetFunc(HalWifiIotIoName id, unsigned char *val)
{
    if (id == HAL_WIFI_IOT_IO_NAME_MAX) {
        return HAL_WIFI_IOT_ERR_GPIO_INVALID_PARAMETER;
    }
    return hi_io_get_func((hi_io_name)id, val);
}

unsigned int HalIOGetDriverStrength(HalWifiIotIoName id, HalWifiIotIoDriverStrength *val)
{
    if (id == HAL_WIFI_IOT_IO_NAME_MAX) {
        return HAL_WIFI_IOT_ERR_GPIO_INVALID_PARAMETER;
    }
    return hi_io_get_driver_strength((hi_io_name)id, (hi_io_driver_strength *)val);
}

unsigned int HalIOSetDriverStrength(HalWifiIotIoName id, HalWifiIotIoDriverStrength val)
{
    if (id == HAL_WIFI_IOT_IO_NAME_MAX) {
        return HAL_WIFI_IOT_ERR_GPIO_INVALID_PARAMETER;
    }
    return hi_io_set_driver_strength((hi_io_name)id, (hi_io_driver_strength)val);
}

