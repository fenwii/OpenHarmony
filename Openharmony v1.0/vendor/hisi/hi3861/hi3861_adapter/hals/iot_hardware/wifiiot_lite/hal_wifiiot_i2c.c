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

#include "hi_i2c.h"
#include "hal_wifiiot_i2c.h"
#include "hal_wifiiot_i2c_ex.h"

unsigned int HalI2cWrite(HalWifiIotI2cIdx id, unsigned short deviceAddr, const HalWifiIotI2cData *i2cData)
{
    return hi_i2c_write((hi_i2c_idx)id, deviceAddr, (const hi_i2c_data *)i2cData);
}

unsigned int HalI2cRead(HalWifiIotI2cIdx id, unsigned short deviceAddr, const HalWifiIotI2cData *i2cData)
{
    return hi_i2c_read((hi_i2c_idx)id, deviceAddr, (const hi_i2c_data *)i2cData);
}

unsigned int HalI2cInit(HalWifiIotI2cIdx id, unsigned int baudrate)
{
    return hi_i2c_init((hi_i2c_idx)id, baudrate);
}

unsigned int HalI2cDeinit(HalWifiIotI2cIdx id)
{
    return hi_i2c_deinit((hi_i2c_idx)id);
}

unsigned int HalI2cSetBaudrate(HalWifiIotI2cIdx id, unsigned int baudrate)
{
    return hi_i2c_set_baudrate((hi_i2c_idx)id, baudrate);
}

unsigned int HalI2cWriteread(HalWifiIotI2cIdx id, unsigned short deviceAddr, const HalWifiIotI2cData *i2cData)
{
    return hi_i2c_writeread((hi_i2c_idx)id, deviceAddr, (const hi_i2c_data *)i2cData);
}

void HalI2cRegisterResetBusFunc(HalWifiIotI2cIdx id, HalWifiIotI2cFunc pfn)
{
    hi_i2c_func hiFun;
    hiFun.prepare_func = pfn.prepareFunc;
    hiFun.reset_func = pfn.resetFunc;
    hiFun.restore_func = pfn.restoreFunc;
    return hi_i2c_register_reset_bus_func((hi_i2c_idx)id, hiFun);
}

