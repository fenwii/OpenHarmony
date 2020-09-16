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

#include "hal_wifiiot_spi.h"

#include <stdio.h>

#include "hi_spi.h"

unsigned int HalSpiSlaveWrite(HalWifiIotSpiIdx spiId, char *writeData, unsigned int byteLen, unsigned int timeOutMs)
{
    return hi_spi_slave_write((hi_spi_idx)spiId, writeData, byteLen, timeOutMs);
}

unsigned int HalSpiSlaveRead(HalWifiIotSpiIdx spiId, char *readData, unsigned int byteLen, unsigned int timeOutMs)
{
    return hi_spi_slave_read((hi_spi_idx)spiId, readData, byteLen, timeOutMs);
}

unsigned int HalSpiHostWrite(HalWifiIotSpiIdx spiId, char *writeData, unsigned int byteLen)
{
    return hi_spi_host_write((hi_spi_idx)spiId, writeData, byteLen);
}

unsigned int HalSpiHostRead(HalWifiIotSpiIdx spiId, char *readData, unsigned int byteLen)
{
    return hi_spi_host_read((hi_spi_idx)spiId, readData, byteLen);
}

unsigned int HalSpiHostWriteread(HalWifiIotSpiIdx spiId, char *writeData, char *readData, unsigned int byteLen)
{
    return hi_spi_host_writeread((hi_spi_idx)spiId, writeData, readData, byteLen);
}

unsigned int HalSpiSetBasicInfo(HalWifiIotSpiIdx spiId, const HalWifiIotSpiCfgBasicInfo *param)
{
    return hi_spi_set_basic_info((hi_spi_idx)spiId, (const hi_spi_cfg_basic_info *)param);
}

unsigned int HalSpiInit(HalWifiIotSpiIdx spiId, HalWifiIotSpiCfgInitParam initParam,
                        const HalWifiIotSpiCfgBasicInfo *param)
{
    hi_spi_cfg_init_param hiInitParam;
    hiInitParam.is_slave = initParam.isSlave;
    hiInitParam.pad = initParam.pad;
    return hi_spi_init((hi_spi_idx)spiId, hiInitParam, (const hi_spi_cfg_basic_info *)param);
}

unsigned int HalSpiDeinit(HalWifiIotSpiIdx spiId)
{
    return hi_spi_deinit((hi_spi_idx)spiId);
}

unsigned int HalSpiSetIrqMode(HalWifiIotSpiIdx spiId, unsigned char irqEn)
{
    return hi_spi_set_irq_mode((hi_spi_idx)spiId, irqEn);
}

unsigned int HalSpiSetDmaMode(HalWifiIotSpiIdx spiId, unsigned char dmaEn)
{
    return hi_spi_set_dma_mode((hi_spi_idx)spiId, dmaEn);
}

unsigned int HalSpiRegisterUsrFunc(HalWifiIotSpiIdx spiId, HalSpiIsrFunc prepareF, HalSpiIsrFunc restoreF)
{
    return hi_spi_register_usr_func((hi_spi_idx)spiId, prepareF, restoreF);
}

unsigned int HalSpiSetLoopBackMode(HalWifiIotSpiIdx spiId, unsigned char lbEn)
{
    return hi_spi_set_loop_back_mode((hi_spi_idx)spiId, lbEn);
}
