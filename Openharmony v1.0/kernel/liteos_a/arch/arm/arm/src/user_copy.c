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

#include "user_copy.h"
#include "arm_user_copy.h"
#include "securec.h"
#include "los_memory.h"
#include "los_vm_map.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

size_t arch_copy_from_user(void *dst, const void *src, size_t len)
{
    return LOS_ArchCopyFromUser(dst, src, len);
}

size_t LOS_ArchCopyFromUser(void *dst, const void *src, size_t len)
{
    if (!LOS_IsUserAddressRange((VADDR_T)(UINTPTR)src, len)) {
        return len;
    }

    return _arm_user_copy(dst, src, len);
}

size_t arch_copy_to_user(void *dst, const void *src, size_t len)
{
    return LOS_ArchCopyToUser(dst, src, len);
}

size_t LOS_ArchCopyToUser(void *dst, const void *src, size_t len)
{
    if (!LOS_IsUserAddressRange((VADDR_T)(UINTPTR)dst, len)) {
        return len;
    }

    return _arm_user_copy(dst, src, len);
}

INT32 LOS_CopyFromKernel(VOID *dest, UINT32 max, const VOID *src, UINT32 count)
{
    INT32 ret;

    if (!LOS_IsUserAddressRange((VADDR_T)(UINTPTR)dest, count)) {
        ret = memcpy_s(dest, max, src, count);
    } else {
        ret = ((max >= count) ? _arm_user_copy(dest, src, count) : ERANGE_AND_RESET);
    }

    return ret;
}

INT32 LOS_CopyToKernel(VOID *dest, UINT32 max, const VOID *src, UINT32 count)
{
    INT32 ret;

    if (!LOS_IsUserAddressRange((vaddr_t)(UINTPTR)src, count)) {
        ret = memcpy_s(dest, max, src, count);
    } else {
        ret = ((max >= count) ? _arm_user_copy(dest, src, count) : ERANGE_AND_RESET);
    }

    return ret;
}

INT32 LOS_UserMemClear(unsigned char *buf, UINT32 len)
{
    INT32 ret = 0;
    if (!LOS_IsUserAddressRange((vaddr_t)(UINTPTR)buf, len)) {
        (VOID)memset_s(buf, len, 0, len);
    } else {
        unsigned char *tmp = (unsigned char *)LOS_MemAlloc(OS_SYS_MEM_ADDR, len);
        if (tmp == NULL) {
            return -ENOMEM;
        }
        (VOID)memset_s(tmp, len, 0, len);
        if (_arm_user_copy(buf, tmp, len) != 0) {
            ret = -EFAULT;
        }
        LOS_MemFree(OS_SYS_MEM_ADDR, tmp);
    }
    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

