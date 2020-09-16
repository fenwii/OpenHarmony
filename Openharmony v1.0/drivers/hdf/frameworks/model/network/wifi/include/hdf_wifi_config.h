/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef HDF_WIFI_CONFIG_HEADER_H
#define HDF_WIFI_CONFIG_HEADER_H

#include <stdint.h>
#include "device_resource_if.h"

#define WIFI_CONFIG_NAME_MAX 20
#define WIFI_CHIP_MAX 3
#define GPIO_PRAM_COUNT 2
#define BUS_REG_COUNT 2
#define BUS_FUNC_MAX 1
#define GPIO_ARGS_COUNT 3

struct HdfConfigWifiStation {
    const char *name;
    uint8_t mode;
};

struct HdfConfigWifiHostAp {
    const char *name;
    uint8_t mode;
    uint8_t vapResNum;
    uint8_t userResNum;
};

struct HdfConfigWifiP2P {
    const char *name;
    uint8_t mode;
};

struct HdfConfigWifiMac80211 {
    uint8_t mode;
};

struct HdfConfigWifiPhy {
    uint8_t mode;
};

struct HdfConfigWifiModuleConfig {
    uint32_t featureMap;
    const char *msgName;
    struct HdfConfigWifiStation station;
    struct HdfConfigWifiHostAp hostAp;
    struct HdfConfigWifiP2P p2p;
    struct HdfConfigWifiMac80211 mac80211;
    struct HdfConfigWifiPhy Phy;
};

struct HdfConfigWifiBus {
    uint8_t busType;
    uint8_t funcNum[BUS_FUNC_MAX];
    uint32_t funcNumSize;
    uint16_t vendorId;
    uint16_t deviceId;
    uint16_t timeout;
    uint16_t blockSize;
};

struct HdfConfigWifiChip {
    const char *chipName;
    uint8_t chipId;
    uint32_t featureMap;
    uint8_t powerType;
    uint8_t irqNo;
    struct HdfConfigWifiBus bus;
};

struct HdfConfigWifiDeviceList {
    struct HdfConfigWifiChip chip[WIFI_CHIP_MAX];
    uint16_t chipSize;
};

struct HdfConfigWifiBusRegs {
    uint32_t cclkOut[BUS_REG_COUNT];
    uint32_t ccmd[BUS_REG_COUNT];
    uint32_t cdata0[BUS_REG_COUNT];
    uint32_t cdata1[BUS_REG_COUNT];
    uint32_t cdata2[BUS_REG_COUNT];
    uint32_t cdata3[BUS_REG_COUNT];
};

struct HdfConfigWifiBoard {
    const char *boardName;
    uint8_t busType;
    uint8_t busIdx;
    uint8_t reset[GPIO_PRAM_COUNT];
    uint8_t gpioArgs[GPIO_ARGS_COUNT];
    struct HdfConfigWifiBusRegs busRegs;
};

struct HdfConfigWifiWifiConfig {
    struct HdfConfigWifiModuleConfig moduleConfig;
    struct HdfConfigWifiDeviceList deviceList;
    struct HdfConfigWifiBoard board;
};

struct HdfConfigWifiRoot {
    struct HdfConfigWifiWifiConfig wifiConfig;
};

struct HdfConfigWifiRoot* HdfWifiGetModuleConfigRoot(void);
int32_t HdfParseWifiConfig(const struct DeviceResourceNode *node);

#endif // HDF_WIFI_CONFIG_HEADER_H