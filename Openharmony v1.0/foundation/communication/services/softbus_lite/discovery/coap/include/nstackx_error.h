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
#ifndef NSTACKX_ERROR_H
#define NSTACKX_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

#define NSTACKX_EOK 0 /* OK */
#define NSTACKX_EFAILED (-1) /* Operation failed */
#define NSTACKX_EINVAL (-2) /* Invalid argument */
#define NSTACKX_EINPROGRESS (-3) /* Operation now in progress */
#define NSTACKX_EBUSY (-4) /* Device or resource busy */
#define NSTACKX_ENOMEM (-5) /* Out of memory */
#define NSTACKX_EEXIST (-6) /* Resource already exist */
#define NSTACKX_EAGAIN (-7) /* Try again */
#define NSTACKX_ETIMEOUT (-8) /* Timeout */
#define NSTACKX_OVERFLOW (-9) /* Overflow */
#define NSTACKX_NOEXIST (-10) /* Not exist */
#define NSTACKX_TRUE 1
#define NSTACKX_FALSE 0

#ifdef __cplusplus
}
#endif

#endif // NSTACKX_ERROR_H
