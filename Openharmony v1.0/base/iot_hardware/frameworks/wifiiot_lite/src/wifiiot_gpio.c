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

#include "wifiiot_gpio.h"
#include "hal_wifiiot_gpio.h"
#include "hal_wifiiot_gpio_ex.h"
#include "wifiiot_errno.h"
#include "wifiiot_gpio_ex.h"

unsigned int GpioInit(void)
{
    return HalGpioInit();
}

unsigned int GpioSetDir(WifiIotGpioIdx id, WifiIotGpioDir dir)
{
    return HalGpioSetDir((HalWifiIotGpioIdx)id, (HalWifiIotGpioDir)dir);
}

unsigned int GpioGetDir(WifiIotGpioIdx id, WifiIotGpioDir *dir)
{
    return HalGpioGetDir((HalWifiIotGpioIdx)id, (HalWifiIotGpioDir *)dir);
}

unsigned int GpioSetOutputVal(WifiIotGpioIdx id, WifiIotGpioValue val)
{
    return HalGpioSetOutputVal((HalWifiIotGpioIdx)id, (HalWifiIotGpioValue)val);
}

unsigned int GpioGetOutputVal(WifiIotGpioIdx id, WifiIotGpioValue *val)
{
    return HalGpioGetOutputVal((HalWifiIotGpioIdx)id, (HalWifiIotGpioValue *)val);
}

unsigned int GpioGetInputVal(WifiIotGpioIdx id, WifiIotGpioValue *val)
{
    return HalGpioGetInputVal((HalWifiIotGpioIdx)id, (HalWifiIotGpioValue *)val);
}

unsigned int GpioRegisterIsrFunc(WifiIotGpioIdx id, WifiIotGpioIntType intType, WifiIotGpioIntPolarity intPolarity,
                                 GpioIsrCallbackFunc func, char *arg)
{
    return HalGpioRegisterIsrFunc((HalWifiIotGpioIdx)id, (HalWifiIotGpioIntType)intType,
                                  (HalWifiIotGpioIntPolarity)intPolarity, (HalGpioIsrCallbackFunc)func, arg);
}

unsigned int GpioUnregisterIsrFunc(WifiIotGpioIdx id)
{
    return HalGpioUnregisterIsrFunc((HalWifiIotGpioIdx)id);
}

unsigned int GpioSetIsrMask(WifiIotGpioIdx id, unsigned char mask)
{
    return HalGpioSetIsrMask((HalWifiIotGpioIdx)id, mask);
}

unsigned int GpioSetIsrMode(WifiIotGpioIdx id, WifiIotGpioIntType intType, WifiIotGpioIntPolarity intPolarity)
{
    return HalGpioSetIsrMode((HalWifiIotGpioIdx)id, (HalWifiIotGpioIntType)intType,
                             (HalWifiIotGpioIntPolarity)intPolarity);
}

unsigned int GpioDeinit(void)
{
    return HalGpioDeinit();
}

unsigned int IoSetPull(WifiIotIoName id, WifiIotIoPull val)
{
    return HalIoSetPull((HalWifiIotIoName)id, (HalWifiIotIoPull)val);
}

unsigned int IoSetFunc(WifiIotIoName id, unsigned char val)
{
    return HalIoSetFunc((HalWifiIotIoName)id, val);
}

unsigned int IoGetPull(WifiIotIoName id, WifiIotIoPull *val)
{
    return HalIoGetPull((HalWifiIotIoName)id, (HalWifiIotIoPull *)val);
}

unsigned int IoGetFunc(WifiIotIoName id, unsigned char *val)
{
    return HalIoGetFunc((HalWifiIotIoName)id, val);
}

unsigned int IOGetDriverStrength(WifiIotIoName id, WifiIotIoDriverStrength *val)
{
    return HalIOGetDriverStrength((HalWifiIotIoName)id, (HalWifiIotIoDriverStrength *)val);
}

unsigned int IOSetDriverStrength(WifiIotIoName id, WifiIotIoDriverStrength val)
{
    return HalIOSetDriverStrength((HalWifiIotIoName)id, (HalWifiIotIoDriverStrength)val);
}

