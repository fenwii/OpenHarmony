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

#include "hal_wifiiot_i2c.h"
#include "hal_wifiiot_i2c_ex.h"
#include "wifiiot_i2c.h"
#include "wifiiot_i2c_ex.h"

unsigned int I2cWrite(WifiIotI2cIdx id, unsigned short deviceAddr, const WifiIotI2cData *i2cData)
{
    return HalI2cWrite((WifiIotI2cIdx)id, deviceAddr, (const HalWifiIotI2cData *)i2cData);
}

unsigned int I2cRead(WifiIotI2cIdx id, unsigned short deviceAddr, const WifiIotI2cData *i2cData)
{
    return HalI2cRead((HalWifiIotI2cIdx)id, deviceAddr, (const HalWifiIotI2cData *)i2cData);
}

unsigned int I2cInit(WifiIotI2cIdx id, unsigned int baudrate)
{
    return HalI2cInit((HalWifiIotI2cIdx)id, baudrate);
}

unsigned int I2cDeinit(WifiIotI2cIdx id)
{
    return HalI2cDeinit((HalWifiIotI2cIdx)id);
}

unsigned int I2cSetBaudrate(WifiIotI2cIdx id, unsigned int baudrate)
{
    return HalI2cSetBaudrate((HalWifiIotI2cIdx)id, baudrate);
}

unsigned int I2cWriteread(WifiIotI2cIdx id, unsigned short deviceAddr, const WifiIotI2cData *i2cData)
{
    return HalI2cWriteread((HalWifiIotI2cIdx)id, deviceAddr, (const HalWifiIotI2cData *)i2cData);
}

void I2cRegisterResetBusFunc(WifiIotI2cIdx id, WifiIotI2cFunc pfn)
{
    HalWifiIotI2cFunc halpfn;

    halpfn.resetFunc = pfn.resetFunc;
    halpfn.prepareFunc = pfn.prepareFunc;
    halpfn.restoreFunc = pfn.restoreFunc;

    HalI2cRegisterResetBusFunc((HalWifiIotI2cIdx)id, halpfn);
}

