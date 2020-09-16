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
#ifndef OHOS_TYPES_H
#define OHOS_TYPES_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*
 * Defintion of basic data types.
 * The data types are applicable to both the application and kernel.
 */
typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned int            uint32;
typedef signed char             int8;
typedef short                   int16;
typedef int                     int32;

#ifndef _M_IX86
typedef unsigned long long      uint64;
typedef long long               int64;
#else
typedef unsigned __int64        uint64;
typedef __int64                 int64;
#endif

typedef int                     boolean;

typedef void                    *pHandle;

typedef unsigned int BOOL;

#ifndef TRUE
#define TRUE             1L
#endif

#ifndef FALSE
#define FALSE            0L
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0L
#else
#define NULL ((void*)0)
#endif
#endif

#define HOS_SUCCESS          0
#define HOS_FAILURE          (-1)

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* OHOS_TYPES_H */

