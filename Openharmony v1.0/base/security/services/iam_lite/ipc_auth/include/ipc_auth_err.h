/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PERM_ERROR_CODE_H
#define PERM_ERROR_CODE_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

enum IpcAuthErrorCode {
    AUTH_ERRORCODE_SUCCESS = 0,
    AUTH_ERRORCODE_ACCESS_DENIED = -1,
    AUTH_ERRORCODE_NO_POLICY_SET = -2,
    AUTH_ERRORCODE_INVALID_UID = 100,
    AUTH_ERRORCODE_INVALID_BUNDLENAME = 101,
    AUTH_ERRORCODE_GET_BUNDLEINFO_ERROR = 102,
    AUTH_ERRORCODE_MALLOC_FAIL = 103,
    AUTH_ERRORCODE_MEMSET_FAIL = 104,
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // PERM_ERROR_CODE_H