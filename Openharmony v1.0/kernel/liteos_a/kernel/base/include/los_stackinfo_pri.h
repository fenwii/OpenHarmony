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

#ifndef _LOS_STACK_INFO_PRI_H
#define _LOS_STACK_INFO_PRI_H

#include "los_typedef.h"
#include "arch_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef struct {
    VOID *stackTop;
    UINT32 stackSize;
    CHAR *stackName;
} StackInfo;

#define OS_INVALID_WATERLINE 0xFFFFFFFF
#define OS_STACK_MAGIC_CHECK(topstack) (*(UINTPTR *)(topstack) == OS_STACK_MAGIC_WORD)  /* 1:magic valid 0:unvalid */

extern VOID OsExcStackInfo(VOID);
extern VOID OsExcStackInfoReg(const StackInfo *stackInfo, UINT32 stackNum);
extern VOID OsStackInit(VOID *stacktop, UINT32 stacksize);

/**
 * @ingroup  los_task
 * @brief Get stack waterline.
 *
 * @par Description:
 * This API is used to get stack waterline size and check stack whether overflow.
 *
 * @attention None
 *
 * @param  stackBottom [IN]  Type #const UINTPTR * pointer to stack bottom.
 * @param  stackTop    [IN]  Type #const UINTPTR * pointer to stack top.
 * @param  peakUsed    [OUT] Type #UINT32 * stack waterline.
 *
 * @retval #LOS_NOK        stack overflow
 * @retval #LOS_OK         stack is normal, not overflow
 * @par Dependency:
 * <ul><li>los_stackinfo_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern UINT32 OsStackWaterLineGet(const UINTPTR *stackBottom, const UINTPTR *stackTop, UINT32 *peakUsed);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_STACK_INFO_PRI_H */