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
#include "iunknown.h"
#include "common.h"

#define OLD_VERSION 0

int IUNKNOWN_AddRef(IUnknown *iUnknown)
{
    if (iUnknown == NULL) {
        return EC_INVALID;
    }

    IUnknownEntry *entry = GET_OBJECT(iUnknown, IUnknownEntry, iUnknown);
    entry->ref++;
    return entry->ref;
}

int IUNKNOWN_QueryInterface(IUnknown *iUnknown, int ver, void **target)
{
    if (iUnknown == NULL || target == NULL) {
        return EC_INVALID;
    }

    IUnknownEntry *entry = GET_OBJECT(iUnknown, IUnknownEntry, iUnknown);
    if ((entry->ver & (uint16)ver) != ver) {
        return EC_INVALID;
    }

    if (ver == OLD_VERSION &&
        entry->ver != OLD_VERSION &&
        (entry->ver & (uint16)DEFAULT_VERSION) != DEFAULT_VERSION) {
        return EC_INVALID;
    }

    *target = iUnknown;
    iUnknown->AddRef(iUnknown);
    return EC_SUCCESS;
}

int IUNKNOWN_Release(IUnknown *iUnknown)
{
    if (iUnknown == NULL) {
        return EC_INVALID;
    }

    IUnknownEntry *entry = GET_OBJECT(iUnknown, IUnknownEntry, iUnknown);
    int ref = entry->ref - 1;
    if (ref < 0) {
        // The iUnknown is already freed, there is some exception;
    } else {
        if (ref == 0) {
            // Nobody reference to the iUnknown, should delete it.
            // But iUnknown may be global variable, so the default version don`t delete it.
        } else {
            entry->ref = ref;
        }
    }
    return ref;
}