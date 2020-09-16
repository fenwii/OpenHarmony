/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "los_typedef.h"
#pragma once

/*
 * @brief Copy data from userspace into kernelspace
 *
 * This function validates that usermode has access to src before copying the
 * data.
 *
 * @param dst The destination buffer.
 * @param src The source buffer.
 * @param len The number of bytes to copy.
 *
 * @return bytes not copied
 */
size_t LOS_ArchCopyFromUser(void *dst, const void *src, size_t len);

/*
 * @brief Copy data from kernelspace into userspace
 *
 * This function validates that usermode has access to dst before copying the
 * data.
 *
 * @param dst The destination buffer.
 * @param src The source buffer.
 * @param len The number of bytes to copy.
 *
 * @return bytes not copied
 */
size_t LOS_ArchCopyToUser(void *dst, const void *src, size_t len);

/*
 * @brief Copy data from src to dst
 *
 * This function will use different copy methods to copy src data to dst, according to
 * the different spaces (userspace or kernelspace) of dst data.
 *
 * @param dst The destination buffer, can be userspace address.
 * @param max The maxsimum number of bytes to copy.
 * @param src The source buffer.
 * @param len The number of bytes to copy.
 *
 * @return zero on success; non-zero on failure.
 */
INT32 LOS_CopyFromKernel(VOID *dest, UINT32 max, const VOID *src, UINT32 count);

/*
 * @brief Copy data from src to dst
 *
 * This function will use different copy methods to copy src data to dst, according to
 * the different spaces (userspace or kernelspace) of src data.
 *
 * @param dst The destination buffer.
 * @param max The maxsimum number of bytes to copy.
 * @param src The source buffer, can be userspace address.
 * @param len The number of bytes to copy.
 *
 * @return zero on success; non-zero on failure.
 */
INT32 LOS_CopyToKernel(VOID *dest, UINT32 max, const VOID *src, UINT32 count);

/*
 * @brief Clear data in buf
 *
 * This function will clear buf from buf to buf + len.
 *
 * @param buf The destination buffer, can be userspace address.
 * @param len The number of bytes to clear.
 *
 * @return zero on success; non-zero on failure.
 */
INT32 LOS_UserMemClear(unsigned char *buf, UINT32 len);
