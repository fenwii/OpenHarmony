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

#include "linux/timer.h"
#include "los_swtmr.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

void linux_init_timer(struct timer_list *timer)
{
    UINT32 intSave;

    if (timer == NULL) {
        PRINTK("init_timer<error> timer is NULL\n");
        return;
    }
    LOS_SpinInit(&timer->lock);
    LOS_SpinLockSave(&timer->lock, &intSave);
    timer->flag = TIMER_UNVALID;
    LOS_SpinUnlockRestore(&timer->lock, intSave);
}

STATIC UINT32 DoDeleteTimer(struct timer_list *timer)
{
    UINT32 ret;

    ret = LOS_SwtmrDelete(timer->timerid);
    if (ret == LOS_OK) {
        timer->flag = TIMER_UNVALID;
    }
    return ret;
}

STATIC UINT32 DoAddTimer(struct timer_list *timer)
{
    UINT32 ret;

    ret = LOS_SwtmrCreate(timer->expires, LOS_SWTMR_MODE_NO_SELFDELETE, (SWTMR_PROC_FUNC)timer->function,
                          &timer->timerid, timer->data);
    if (ret != LOS_OK) {
        PRINTK("add_timer<error> timer create failed: %u \n", ret);
        return ret;
    }
    ret = LOS_SwtmrStart(timer->timerid);
    if (ret != LOS_OK) {
        PRINTK("add_timer<error> timer start failed: %u \n", ret);
    }
    return ret;
}

void linux_add_timer(struct timer_list *timer)
{
    UINT32 intSave;

    if (timer == NULL) {
        PRINTK("add_timer<error> timer is NULL\n");
        return;
    }

    LOS_SpinLockSave(&timer->lock, &intSave);
    if (timer->flag == TIMER_VALID) {
        if (DoDeleteTimer(timer) != LOS_OK) {
            goto ERROUT;
        }
    }

    if (DoAddTimer(timer) != LOS_OK) {
        goto ERROUT;
    }
    timer->flag = TIMER_VALID;
ERROUT:
    LOS_SpinUnlockRestore(&timer->lock, intSave);
    return;
}

int linux_del_timer(struct timer_list *timer)
{
    UINT32 intSave;
    INT32 ret = 0;

    if (timer == NULL) {
        PRINTK("del_timer<error> timer is NULL\n");
        return ret;
    }

    LOS_SpinLockSave(&timer->lock, &intSave);
    if (timer->flag == TIMER_VALID) {
        ret = (DoDeleteTimer(timer) == LOS_OK) ? 1 : 0;
    }
    LOS_SpinUnlockRestore(&timer->lock, intSave);

    return ret;
}

int linux_mod_timer(struct timer_list *timer, unsigned long expires)
{
    INT32 ret = 0;
    UINT32 intSave;

    if (timer == NULL) {
        return ret;
    }

    LOS_SpinLockSave(&timer->lock, &intSave);
    if (timer->flag == TIMER_VALID) {
        if (DoDeleteTimer(timer) != LOS_OK) {
            goto ERROUT;
        }
        timer->expires = expires;
        if (DoAddTimer(timer) == LOS_OK) {
            timer->flag = TIMER_VALID;
            ret = 1;
        }
    }
ERROUT:
    LOS_SpinUnlockRestore(&timer->lock, intSave);
    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif