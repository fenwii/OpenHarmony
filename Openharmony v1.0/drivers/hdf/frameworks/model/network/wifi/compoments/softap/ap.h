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

#ifndef HDFLITE_AP_H
#define HDFLITE_AP_H

#include "wifi_base.h"

#ifdef __cplusplus
extern "C" {
#endif

enum WifiAPFeatureType {
    HDF_WIFI_AP_NOT_SUPPORT,
    HDF_WIFI_AP_SOFTAP,
    HDF_WIFI_AP_END,
};

struct WifiApFeatureOps {
    uint32_t (*startAp)(struct NetDevice *dev, WifiApSetting *settings);
    uint32_t (*stopAp)(struct NetDevice *dev);
    uint32_t (*delStation)(struct NetDevice *dev, struct StationDelParameters *params);
    uint32_t (*changeBeacon)(struct NetDevice *dev, WifiApSetting *apSettings);
};

struct WifiApFeature {
    struct WifiFeature fe;
    struct WifiApFeatureOps ops;
};

struct WifiApFeature *WifiApGetFeature(const struct WifiModule *module);

struct WifiFeature *GetWifiApFeatureDelc(void);

#ifdef __cplusplus
}
#endif
#endif // HDFLITE_AP_H
