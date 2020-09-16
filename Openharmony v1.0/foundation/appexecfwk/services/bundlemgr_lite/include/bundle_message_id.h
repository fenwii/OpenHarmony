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

#ifndef OHOS_BUNDLE_MESSAGE_ID_H
#define OHOS_BUNDLE_MESSAGE_ID_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

enum BmsMsgType {
    COMMU_TX_PACKET = 257,
    BMS_STARTNUMBER = 0x1000,
    BUNDLE_SERVICE_INITED = BMS_STARTNUMBER,
    BUNDLE_INSTALLED,
    BUNDLE_UPDATED,
    BUNDLE_UNINSTALLED,
    BUNDLE_CHANGE_CALLBACK,
    BUNDLE_LIST_CHANGED = 0x1010,
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // OHOS_BUNDLE_MESSAGE_ID_H