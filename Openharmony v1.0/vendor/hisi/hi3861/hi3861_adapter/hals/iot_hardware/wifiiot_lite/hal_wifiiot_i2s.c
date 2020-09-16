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

#include "hi_types_base.h"
#include "hi_i2s.h"
#include "hal_wifiiot_i2s.h"

unsigned int HalI2sInit(const HalWifiIotI2sAttribute *i2sAttribute)
{
    return hi_i2s_init((const hi_i2s_attribute *)i2sAttribute);
}

unsigned int HalI2sDeinit(void)
{
    return hi_i2s_deinit();
}

unsigned int HalI2sWrite(unsigned char *wrData, unsigned int wrLen, unsigned int timeOutMs)
{
    return hi_i2s_write(wrData, wrLen, timeOutMs);
}

unsigned int HalI2sRead(unsigned char *rdData, unsigned int rdLen, unsigned int timeOutMs)
{
    return hi_i2s_read(rdData, rdLen, timeOutMs);
}

