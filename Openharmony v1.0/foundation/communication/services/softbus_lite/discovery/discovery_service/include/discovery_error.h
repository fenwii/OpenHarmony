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
#ifndef DISCOVERY_ERROR_H
#define DISCOVERY_ERROR_H

#ifdef  _cplusplus
extern "C" {
#endif

#define ERROR_SUCCESS  0
#define ERROR_FAIL     -1
#define ERROR_INVALID  (-2)
#define ERROR_NONEXIST (-3)
#define ERROR_NOMEMORY (-4)
#define ERROR_CAPABLITY_FAIL (-5)
#define ERROR_SERVICEDATA_FAIL (-6)
#define ERROR_CREATE_SOCKET_FAIL (-7)
#define ERROR_CONNECT_SOCKET_FAIL (-8)
#define ERROR_BIND_SOCKET_FAIL (-9)
#define ERROR_GET_SOCK_FAIL (-10)
#define ERROR_CREATE_THREAD_FAIL (-10)
#define ERROR_NOT_SUPPORT_MEDIUM (-11)

#ifdef __cplusplus
}
#endif

#endif // DISCOVERY_ERROR_H

