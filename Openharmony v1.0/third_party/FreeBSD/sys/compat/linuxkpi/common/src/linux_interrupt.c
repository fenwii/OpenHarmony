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

#include "linux/interrupt.h"
#include "los_hwi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

int linux_request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags,
                const char *name, void *dev)
{
    UINT32 ret;
    HwiIrqParam irqParam;

    if (OS_INT_ACTIVE) {
        return OS_ERRNO_HWI_INTERR;
    }

    irqParam.swIrq = (INT32)irq;
    irqParam.pDevId = dev;
    irqParam.pName = name;

    ret = LOS_HwiCreate(irq, IRQ_DEFAULT_PRIORITY, (HWI_MODE_T)flags, (HWI_PROC_FUNC)handler, &irqParam);
    if (ret == LOS_OK) {
        HalIrqUnmask(irq);
    }
    return (INT32)ret;
}

void linux_free_irq(unsigned int irq, void *devID)
{
    HwiIrqParam irqParam;

    if (OS_INT_ACTIVE) {
        return;
    }

    irqParam.swIrq = (INT32)irq;
    irqParam.pDevId = devID;

    (VOID)LOS_HwiDelete(irq, &irqParam);
    return;
}

void linux_enable_irq(unsigned int irq)
{
    HalIrqUnmask(irq);
}

void linux_disable_irq(unsigned int irq)
{
    HalIrqMask(irq);
}

#ifdef WORKQUEUE_SUPPORT_PRIORITY
bool irq_bottom_half(struct workqueue_struct *workQueue, irq_bottom_half_handler_t handler, void *data,
                     unsigned int pri)
#else
bool irq_bottom_half(struct workqueue_struct *workQueue, irq_bottom_half_handler_t handler, void *data)
#endif
{
    struct work_struct *work = NULL;

    if ((workQueue == NULL) || (handler == NULL)) {
        return FALSE;
    }

#ifdef WORKQUEUE_SUPPORT_PRIORITY
    if ((pri >= OS_WORK_PRIORITY_DEFAULT) || (pri >= OS_WORK_PRIORITY_LOWEST)) {
        return FALSE;
    }
#endif

    work = (struct work_struct *)LOS_MemAlloc(m_aucSysMem0, sizeof(struct work_struct));
    if (work == NULL) {
        return FALSE;
    }

    INIT_WORK(work, handler);

    work->data = (atomic_long_t)data;
#ifdef WORKQUEUE_SUPPORT_PRIORITY
    work->work_pri = pri;
#endif
    if (!(queue_work(workQueue, work))) {
        (VOID)LOS_MemFree(m_aucSysMem0, work);
        return FALSE;
    }
    return TRUE;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
