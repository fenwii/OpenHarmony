/*
 * @file hi_ver.h
 *
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
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

/** @defgroup iot_ver Soft ver
 * @ingroup system
 */

#ifndef __HI_VER_H__
#define __HI_VER_H__
#include <hi_types.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
* @ingroup  iot_ver
* @brief  Obtains SDK version information. CNcomment:获取SDK版本信息CNend
*
* @par 描述:
*         Obtains SDK version information. CNcomment:获取SDK版本信息CNend
* @attention None
* @retval #hi_char*     SDK version information string. CNcomment:SDK版本信息字符串CNend
*
* @par Dependency:
*      @li hi_ver.h: This file describes version information APIs.CNcomment:文件用于描述系统相关接口.CNend
* @see  None
*/
const hi_char *hi_get_sdk_version(hi_void);

/**
* @ingroup  iot_ver
* @brief  Obtains boot version in secure boot mode. CNcomment:安全启动模式下，获取BOOT版本号CNend
*
* @par 描述:
*         Obtains boot version in secure boot mode. CNcomment:安全启动模式下，获取BOOT版本号CNend
* @attention Ver always be 0 in non-secure boot mode. CNcomment: 非安全启动模式下，该版本号始终为0。CNend
* @retval #hi_u8     boot ver num, value from 0-16, Return 0xFF means get boot ver fail.
CNcomment:boot版本号，有效值为0-16，返回0xFF表示获取BOOT版本号失败CNend
* @par Dependency:
*      @li hi_ver.h: This file describes version information APIs.CNcomment:文件用于描述系统相关接口.CNend
* @see  None
*/
hi_u8 hi_get_boot_ver(hi_void);

/**
* @ingroup  iot_ver
* @brief  Obtains kernel version in secure boot mode. CNcomment:安全启动模式下，获取kernel版本号CNend
*
* @par 描述:
*         Obtains kernel version in secure boot mode. CNcomment:安全启动模式下，获取kernel版本号CNend
* @attention Ver always be 0 in non-secure boot mode. CNcomment:非安全启动模式下，该版本号始终为0。CNend
* @retval #hi_u8     kernel ver num, value from 0-48, Return 0xFF means get kernel ver fail.
CNcomment:kernel版本号，有效值为0-48，返回0xFF表示获取kernel版本号失败CNend
*
* @par Dependency:
*      @li hi_ver.h: This file describes version information APIs.CNcomment:文件用于描述系统相关接口.CNend
* @see  None
*/
hi_u8 hi_get_kernel_ver(hi_void);

#ifdef __cplusplus
}
#endif
#endif
