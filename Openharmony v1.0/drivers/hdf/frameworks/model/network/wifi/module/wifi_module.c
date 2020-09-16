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

#include "wifi_module.h"
#include "wifi_base.h"
#include "hdf_wifi_product.h"
#include "securec.h"
#if __cplusplus
extern "C" {
#endif

struct WifiModule *HdfGetWifiModule(void)
{
    struct HdfWifiProductData *productData = HdfWifiGetProduct();

    if (productData == NULL) {
        return NULL;
    }
    return productData->module;
}

int32_t UpdateWiFiModule(struct WifiModule *module)
{
    (void)module;
    return HDF_SUCCESS;
}

void WifiModuleDelete(struct WifiModule *module)
{
    if (module == NULL) {
        return;
    }
    if ((module->iface != NULL) && (module->iface->deInit != NULL)) {
        module->iface->deInit(module);
        OsalMemFree(module->iface);
    }

    OsalMemFree(module);
    return;
}

struct WifiModule *WifiModuleCreate(const struct HdfConfigWifiModuleConfig *config)
{
    int32_t ret;
    struct WifiModuleIface *iface = NULL;
    struct WifiModule *module = OsalMemAlloc(sizeof(*module));
    if (module == NULL) {
        HDF_LOGE("%s: no memory for module", __func__);
        goto error;
    }
    (void)memset_s(module, sizeof(*module), 0, sizeof(*module));

    iface = OsalMemAlloc(sizeof(*iface));
    if (iface == NULL) {
        HDF_LOGE("%s: no memory for module iface", __func__);
        goto error;
    }

    iface->init = InitFeatures;
    iface->deInit = DeInitFeatures;
    iface->updateModule = UpdateWiFiModule;
    iface->addFeature = AddFeature;
    iface->delFeature = DelFeature;
    module->modulePrivate = NULL;
    module->iface = iface;
    module->moduleConfig.hslConfig = config;

    ret = module->iface->init(module);
    if (ret != 0) {
        HDF_LOGE("%s: module int error ret=%d", __func__, ret);
        goto error;
    }
    return module;
error:
    WifiModuleDelete(module);
    return NULL;
}

#ifdef __cplusplus
}
#endif

