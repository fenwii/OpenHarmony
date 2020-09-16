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

#include <stdlib.h>
#include "wifi_module.h"

#if __cplusplus
extern "C" {
#endif

struct WifiFeature *GetFeature(const struct WifiModule *module, uint16_t featureType)
{
    if ((module == NULL) || (featureType >= HDF_WIFI_FEATURE_NUM) || (module->feList == NULL)) {
        return NULL;
    }
    return module->feList->fe[featureType];
}

int32_t AddFeature(struct WifiModule *module, uint16_t featureType, struct WifiFeature *featureData)
{
    if ((module == NULL) || (featureData == NULL) || (featureType >= HDF_WIFI_FEATURE_NUM)
        || (module->feList == NULL)) {
        HDF_LOGE("%s: para error", __func__);
        return HDF_FAILURE;
    }
    module->feList->fe[featureType] = (struct WifiFeature *)featureData;
    if (featureData->init != NULL) {
        return featureData->init(featureData);
    }

    HDF_LOGE("%s: featureData null", __func__);
    return HDF_FAILURE;
}

int32_t DelFeature(struct WifiModule *module, uint16_t featureType)
{
    struct WifiFeature *featureData = NULL;
    if ((module == NULL) || (featureType >= HDF_WIFI_FEATURE_NUM) || (module->feList == NULL)) {
        HDF_LOGE("%s: para error", __func__);
        return HDF_FAILURE;
    }

    featureData = module->feList->fe[featureType];
    if ((featureData != NULL) && (featureData->deInit != NULL)) {
        featureData->deInit(module->feList->fe[featureType]);
        featureData = NULL;
        return HDF_SUCCESS;
    }
    return HDF_FAILURE;
}

int32_t DeInitFeatures(struct WifiModule *module)
{
    if ((module == NULL) || (module->feList == NULL)) {
        HDF_LOGE("%s: no  module", __func__);
        return HDF_FAILURE;
    }
    // make sure the features should be free firstly
    for (int32_t i = 0; i < HDF_WIFI_FEATURE_NUM; i++) {
        if ((module->feList->fe[i] != NULL) && (module->feList->fe[i]->deInit != NULL)) {
            module->feList->fe[i]->deInit(module->feList->fe[i]);
        }
    }

    return HDF_SUCCESS;
}

#ifdef __cplusplus
}
#endif