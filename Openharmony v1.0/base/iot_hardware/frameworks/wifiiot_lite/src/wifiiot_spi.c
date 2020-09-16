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

#include "wifiiot_spi.h"
#include "hal_wifiiot_spi.h"

unsigned int SpiSlaveWrite(WifiIotSpiIdx spiId, char *writeData, unsigned int byteLen, unsigned int timeOutMs)
{
    return HalSpiSlaveWrite((HalWifiIotSpiIdx)spiId, writeData, byteLen, timeOutMs);
}

unsigned int SpiSlaveRead(WifiIotSpiIdx spiId, char *readData, unsigned int byteLen, unsigned int timeOutMs)
{
    return HalSpiSlaveRead((HalWifiIotSpiIdx)spiId, readData, byteLen, timeOutMs);
}

unsigned int SpiHostWrite(WifiIotSpiIdx spiId, char *writeData, unsigned int byteLen)
{
    return HalSpiHostWrite((HalWifiIotSpiIdx)spiId, writeData, byteLen);
}

unsigned int SpiHostRead(WifiIotSpiIdx spiId, char *readData, unsigned int byteLen)
{
    return HalSpiHostRead((HalWifiIotSpiIdx)spiId, readData, byteLen);
}

unsigned int SpiHostWriteread(WifiIotSpiIdx spiId, char *writeData, char *readData, unsigned int byteLen)
{
    return HalSpiHostWriteread((HalWifiIotSpiIdx)spiId, writeData, readData, byteLen);
}

unsigned int SpiSetBasicInfo(WifiIotSpiIdx spiId, const WifiIotSpiCfgBasicInfo *param)
{
    return HalSpiSetBasicInfo((HalWifiIotSpiIdx)spiId, (const HalWifiIotSpiCfgBasicInfo *)param);
}

unsigned int SpiInit(WifiIotSpiIdx spiId, WifiIotSpiCfgInitParam initParam, const WifiIotSpiCfgBasicInfo *param)
{
    HalWifiIotSpiCfgInitParam halInitParam;
    halInitParam.isSlave = initParam.isSlave;
    halInitParam.pad = initParam.pad;
    return HalSpiInit((HalWifiIotSpiIdx)spiId, halInitParam, (const HalWifiIotSpiCfgBasicInfo *)param);
}

unsigned int SpiDeinit(WifiIotSpiIdx spiId)
{
    return HalSpiDeinit((HalWifiIotSpiIdx)spiId);
}

unsigned int SpiSetIrqMode(WifiIotSpiIdx spiId, unsigned char irqEn)
{
    return HalSpiSetIrqMode((HalWifiIotSpiIdx)spiId, irqEn);
}

unsigned int SpiSetDmaMode(WifiIotSpiIdx spiId, unsigned char dmaEn)
{
    return HalSpiSetDmaMode((HalWifiIotSpiIdx)spiId, dmaEn);
}

unsigned int SpiRegisterUsrFunc(WifiIotSpiIdx spiId, SpiIsrFunc prepareF, SpiIsrFunc restoreF)
{
    return HalSpiRegisterUsrFunc((HalWifiIotSpiIdx)spiId, (HalSpiIsrFunc)prepareF, (HalSpiIsrFunc)restoreF);
}

unsigned int SpiSetLoopBackMode(WifiIotSpiIdx spiId, unsigned char lbEn)
{
    return HalSpiSetLoopBackMode((HalWifiIotSpiIdx)spiId, lbEn);
}
