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

#ifndef OHOS_BUNDLE_DAEMON_INTERFACE_H
#define OHOS_BUNDLE_DAEMON_INTERFACE_H

#include "iproxy_server.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

const char BDS_SERVICE[] = "bundle_daemon";

enum BmsCmd {
    EXTRACT_HAP = 0, // extract hap to code path
    RENAME_DIR,     // rename code path or json path
    CREATE_PERMISSION_DIR, // create permission dir
    CREATE_DATA_DIRECTORY, // create data path
    STORE_CONTENT_TO_FILE, // store content to json path
    REMOVE_FILE,            // delete json path
    REMOVE_INSTALL_DIRECTORY, // clear app data path and code path
    BDS_CMD_END,
    REGISTER_CALLBACK,    // register bundle_daemon callback
    BDS_CALLBACK          // callback message
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* OHOS_BUNDLE_DAEMON_INTERFACE_H */
