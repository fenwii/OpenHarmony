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


#include "wifiiot_i2s.h"
#include "hal_wifiiot_i2s.h"

unsigned int I2sInit(const WifiIotI2sAttribute *i2sAttribute)
{
    return HalI2sInit((const HalWifiIotI2sAttribute *)i2sAttribute);
}

unsigned int I2sDeinit(void)
{
    return HalI2sDeinit();
}

unsigned int I2sWrite(unsigned char *wrData, unsigned int wrLen, unsigned int timeOutMs)
{
    return HalI2sWrite(wrData, wrLen, timeOutMs);
}

unsigned int I2sRead(unsigned char *rdData, unsigned int rdLen, unsigned int timeOutMs)
{
    return HalI2sRead(rdData, rdLen, timeOutMs);
}

