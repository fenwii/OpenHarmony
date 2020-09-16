/**
 * @file hi_crc.h
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

/**
 * @defgroup iot_crc  CRC Verification
 * @ingroup system
 */

#ifndef __HI_CRC_H__
#define __HI_CRC_H__
#include <hi_types_base.h>

/**
* @ingroup  iot_crc
* @brief  Generates a 16-bit CRC value.CNcomment:生成16位CRC校验值。CNend
*
* @par 描述:
*           Generates a 16-bit CRC value.CNcomment:生成16位CRC校验值。CNend
*
* @attention None
* @param  crc_start         [IN] type #hi_u16，The CRC initial value.CNcomment:CRC初始值。CNend
* @param  buf               [IN] type #const hi_u8*，Pointer to the buffer to be verified.
CNcomment:被校验Buffer指针。CNend
* @param  len               [IN] type #hi_u32，Length of the buffer to be verified (unit: Byte).
CNcomment:被校验Buffer长度（单位：byte）。CNend
* @param  crc_result        [OUT]type #hi_u16*，CRC calculation result.CNcomment:CRC计算结果。CNend
*
* @retval #0     Success.
* @retval #Other Failure.
*
* @par 依赖:
*            @li hi_crc.h：Describes CRC APIs.CNcomment:文件包含CRC校验接口。CNend
* @see  None
*/
hi_u32 hi_crc16(hi_u16 crc_start, const hi_u8 *buf, hi_u32 len, hi_u16 *crc_result);

/**
* @ingroup  iot_crc
* @brief  Generates a 32-bit CRC value.CNcomment:生成32位CRC校验值。CNend
*
* @par 描述:
*          Generates a 32-bit CRC value.CNcomment:生成32位CRC校验值。CNend
*
* @attention None
* @param  crc_start         [IN] type #hi_u32，The CRC initial value.CNcomment:CRC初始值。CNend
* @param  buf               [IN] type #const hi_u8*，Pointer to the buffer to be verified.
CNcomment:被校验Buffer指针。CNend
* @param  len               [IN] type #hi_u32，Length of the buffer to be verified (unit: Byte).
CNcomment:被校验Buffer长度（单位：byte）。CNend
* @param  crc_result        [OUT]type #hi_u32*，CRC calculation result.CNcomment:CRC计算结果。CNend
*
* @retval #0     Success.
* @retval #Other Failure.
*
* @par 依赖:
*            @li hi_crc.h：Describes CRC APIs.CNcomment:文件包含CRC校验接口。CNend
* @see  None
*/
hi_u32 hi_crc32(hi_u32 crc_start, const hi_u8 *buf, hi_u32 len, hi_u32 *crc_result);

#endif

