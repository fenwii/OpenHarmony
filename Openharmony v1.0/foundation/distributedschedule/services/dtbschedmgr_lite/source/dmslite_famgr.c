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

#include "dmslite_famgr.h"

#include "distributed_service_interface.h"
#include "dmslite_log.h"

#include "ability_manager.h"
#include "ability_service_interface.h"
#include "iproxy_client.h"
#include "iunknown.h"
#include "liteipc_adapter.h"
#include "ohos_errno.h"
#include "samgr_lite.h"
#include "securec.h"

#define INVALID_IPC_TOKEN 0
#define INVALID_IPC_HANDLE (-1)

static SvcIdentity g_serviceIdentity = {
    .handle = INVALID_IPC_HANDLE,
    .token = INVALID_IPC_TOKEN
};

static StartAbilityCallback g_onStartAbilityDone = NULL;

static int32_t AmsResultCallback(const IpcContext* context, void *ipcMsg, IpcIo *io, void *arg)
{
    /* Notice: must free ipcMsg, for we don't need ipcMsg here, just free it at first */
    FreeBuffer(context, ipcMsg);

    HILOGD("[AmsResultCallback called]");
    if (g_onStartAbilityDone == NULL) {
        return LITEIPC_EINVAL;
    }

    ElementName elementName;
    if (memset_s(&elementName, sizeof(ElementName), 0x00, sizeof(ElementName)) != EOK) {
        HILOGE("[elementName memset failed]");
        return LITEIPC_EINVAL;
    }

    /* the element is not used so far, and deserialize element first before we can get the errcode from io */
    if (!DeserializeElement(&elementName, io)) {
        return LITEIPC_EINVAL;
    }
    ClearElement(&elementName);

    int8_t errCode = DMS_EC_START_ABILITY_ASYNC_FAILURE;
    if (IpcIoPopInt32(io) == EC_SUCCESS) {
        /* this means that FA starts and shows on screen successfully */
        errCode = DMS_EC_START_ABILITY_ASYNC_SUCCESS;
    }
    g_onStartAbilityDone(errCode);

    return LITEIPC_OK;
}

static bool GetAmsInterface(struct AmsInterface **amsInterface)
{
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(AMS_SERVICE, AMS_FEATURE);
    if (iUnknown == NULL) {
        HILOGE("[GetFeatureApi failed]");
        return false;
    }

    int32_t errCode = iUnknown->QueryInterface(iUnknown, DEFAULT_VERSION, (void**) amsInterface);
    if (errCode != EC_SUCCESS) {
        HILOGE("[QueryInterface failed]");
        return false;
    }

    return true;
}

static int8_t FillWant(Want *want, const char *bundleName, const char *abilityName)
{
    if (memset_s(want, sizeof(Want), 0x00, sizeof(Want)) != EOK) {
        HILOGE("[want memset failed]");
        return DMS_EC_FAILURE;
    }
    ElementName element;
    if (memset_s(&element, sizeof(ElementName), 0x00, sizeof(ElementName)) != EOK) {
        HILOGE("[elementName memset failed]");
        return DMS_EC_FAILURE;
    }

    if (!(SetElementBundleName(&element, bundleName)
        && SetElementAbilityName(&element, abilityName)
        && SetWantElement(want, element)
        && SetWantSvcIdentity(want, g_serviceIdentity))) {
        HILOGE("[Fill want failed]");
        ClearElement(&element);
        ClearWant(want);
        return DMS_EC_FAILURE;
    }
    ClearElement(&element);

    return DMS_EC_SUCCESS;
}

static int8_t StartAbilityFromRemoteInner(const char *bundleName, const char *abilityName)
{
    Want want; /* NOTICE: must call ClearWant if filling want sucessfully */
    if (FillWant(&want, bundleName, abilityName) != DMS_EC_SUCCESS) {
        return DMS_EC_FILL_WANT_FAILURE;
    }

    int32_t errCode;
    uid_t callerUid = getuid();
    if (callerUid == FOUNDATION_UID) {
        /* inner-process mode */
        struct AmsInterface *amsInterface = NULL;
        if (!GetAmsInterface(&amsInterface)) {
            HILOGE("[GetAmsInterface query null]");
            ClearWant(&want);
            return DMS_EC_GET_AMS_FAILURE;
        }
        errCode = amsInterface->StartAbility(&want);
    } else if (callerUid == SHELL_UID) {
        /* inter-process mode (mainly called in xts testsuit process started by shell) */
        errCode = StartAbility(&want);
    } else {
        errCode = EC_FAILURE;
    }
    ClearWant(&want);

    if (errCode != EC_SUCCESS) {
        HILOGE("[Call ams StartAbility failed errCode = %d]", errCode);
        return DMS_EC_START_ABILITY_SYNC_FAILURE;
    }
    /* this just means we send to the ams a request of starting FA successfully */
    return DMS_EC_START_ABILITY_SYNC_SUCCESS;
}

int8_t StartAbilityFromRemote(const char *bundleName, const char *abilityName,
    StartAbilityCallback onStartAbilityDone)
{
    if (bundleName == NULL || abilityName == NULL) {
        HILOGE("[Invalid parameters]");
        return DMS_EC_FAILURE;
    }

    if (g_serviceIdentity.token == INVALID_IPC_TOKEN) {
        /* register a callback for notification when ams starts ability successfully */
        IpcCbMode mode = ONCE;
        if (RegisteIpcCallback(AmsResultCallback, mode, IPC_WAIT_FOREVER,
            &g_serviceIdentity, NULL) != EC_SUCCESS) {
            HILOGE("[RegisteIpcCallback failed]");
            return DMS_EC_REGISTE_IPC_CALLBACK_FAILURE;
        }
    }
    if (g_onStartAbilityDone == NULL) {
        g_onStartAbilityDone = onStartAbilityDone;
    }

    return StartAbilityFromRemoteInner(bundleName, abilityName);
}
