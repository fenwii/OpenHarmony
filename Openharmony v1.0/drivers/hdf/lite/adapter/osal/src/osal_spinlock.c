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

#include "osal_spinlock.h"
#include "linux/spinlock.h"
#include "hdf_log.h"
#include "osal_mem.h"

#define HDF_LOG_TAG osal_spinlock

int32_t OsalSpinInit(OsalSpinlock *spinlock)
{
    spinlock_t *spin = NULL;

    spin = (spinlock_t *)OsalMemCalloc(sizeof(*spin));
    if (spin == NULL) {
        HDF_LOGE("%s malloc fail", __func__);
        spinlock->realSpinlock = NULL;
        return HDF_ERR_MALLOC_FAIL;
    }

    spin_lock_init(spin);
    spinlock->realSpinlock = spin;

    return HDF_SUCCESS;
}

int32_t OsalSpinDestroy(OsalSpinlock *spinlock)
{
    if (spinlock == NULL || spinlock->realSpinlock == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    OsalMemFree(spinlock->realSpinlock);
    spinlock->realSpinlock = NULL;

    return HDF_SUCCESS;
}

int32_t OsalSpinLock(OsalSpinlock *spinlock)
{
    if (spinlock == NULL || spinlock->realSpinlock == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    spin_lock((spinlock_t *)spinlock->realSpinlock);

    return HDF_SUCCESS;
}

int32_t OsalSpinUnlock(OsalSpinlock *spinlock)
{
    if (spinlock == NULL || spinlock->realSpinlock == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    spin_unlock((spinlock_t *)spinlock->realSpinlock);

    return HDF_SUCCESS;
}

int32_t OsalSpinLockIrq(OsalSpinlock *spinlock)
{
#if (LOSCFG_KERNEL_SMP == YES)
    if (spinlock == NULL || spinlock->realSpinlock == NULL) {
        HDF_LOGE("%s invalid param %d", __func__, __LINE__);
        return HDF_ERR_INVALID_PARAM;
    }

    LOS_IntLock();
    LOS_SpinLock((spinlock_t *)spinlock->realSpinlock);
#else
    (void)spinlock;
    LOS_IntLock();
#endif
    return HDF_SUCCESS;
}

int32_t OsalSpinUnlockIrq(OsalSpinlock *spinlock)
{
#if (LOSCFG_KERNEL_SMP == YES)
    if (spinlock == NULL || spinlock->realSpinlock == NULL) {
        HDF_LOGE("%s invalid param %d", __func__, __LINE__);
        return HDF_ERR_INVALID_PARAM;
    }

    LOS_SpinUnlock((spinlock_t *)spinlock->realSpinlock);
    LOS_IntUnLock();
#else
    (void)spinlock;
    LOS_IntUnLock();
#endif

    return HDF_SUCCESS;
}

int32_t OsalSpinLockIrqSave(OsalSpinlock *spinlock, uint32_t *flags)
{
    if (spinlock == NULL || spinlock->realSpinlock == NULL || flags == NULL) {
        HDF_LOGE("%s invalid param %d", __func__, __LINE__);
        return HDF_ERR_INVALID_PARAM;
    }
    spin_lock_irqsave((spinlock_t *)spinlock->realSpinlock, *flags);

    return HDF_SUCCESS;
}

int32_t OsalSpinUnlockIrqRestore(OsalSpinlock *spinlock, uint32_t *flags)
{
    if (spinlock == NULL || spinlock->realSpinlock == NULL || flags == NULL) {
        HDF_LOGE("%s invalid param %d", __func__, __LINE__);
        return HDF_ERR_INVALID_PARAM;
    }
    spin_unlock_irqrestore((spinlock_t *)spinlock->realSpinlock, *flags);

    return HDF_SUCCESS;
}

