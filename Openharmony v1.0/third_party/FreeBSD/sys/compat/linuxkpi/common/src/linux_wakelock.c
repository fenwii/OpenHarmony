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

#include "linux/wakelock.h"
#include "los_spinlock.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define SET_BIT(bitmap, pos) ((bitmap) |= (1u << (pos)))
#define CLEAR_BIT(bitmap, pos) ((bitmap) &= ~(1u << (pos)))
#define CHECK_BIT(bitmap, pos) (((bitmap) & (1u << (pos))) ? 1 : 0)

#define WAKELOCK_BITMAP_CNT 32

/* spinlock for wake lock module only available on SMP mode */
LITE_OS_SEC_BSS SPIN_LOCK_INIT(g_wakeLockSpin);

typedef struct {
    UINT32 lock; /* Indicate which bit is locked */
    UINT32 used; /* Indicate used bit */
} WakeLockBitmap;

STATIC WakeLockBitmap g_wlBitmap;

STATIC INT32 FindEmptyBit(UINT32 bitmap)
{
    UINT32 t = 1;
    INT32 i;
    for (i = 0; i < WAKELOCK_BITMAP_CNT; i++) {
        if (!(t & bitmap)) {
            break;
        } else {
            t <<= 1;
        }
    }

    if (i == WAKELOCK_BITMAP_CNT) {
        return -1;
    }
    return i;
}

/*
 * Initial a wakelock
 * Attention: DO NOT init more than 32 wakelock!
 */
void linux_wake_lock_init(struct wake_lock *lock, int type, const char *name)
{
    UINT32 intSave;
    INT32 pos;
    (VOID)type;

    if (lock == NULL) {
        PRINT_ERR("%s : invalid parameter!\n", __FUNCTION__);
        return;
    }

    lock->ws.name = name;

    LOS_SpinLockSave(&g_wakeLockSpin, &intSave);
    pos = FindEmptyBit(g_wlBitmap.used);
    if (pos != -1) {
        lock->bitmap_pos = (UINT32)pos;
        SET_BIT(g_wlBitmap.used, lock->bitmap_pos);
        CLEAR_BIT(g_wlBitmap.lock, lock->bitmap_pos);
    } else {
        LOS_SpinUnlockRestore(&g_wakeLockSpin, intSave);
        PRINT_ERR("%s : wakelock count exceeds 32!\n", __FUNCTION__);
        return;
    }

    LOS_SpinUnlockRestore(&g_wakeLockSpin, intSave);
}

void linux_wake_lock(struct wake_lock *lock)
{
    UINT32 intSave;
    if (lock == NULL) {
        return;
    }

    LOS_SpinLockSave(&g_wakeLockSpin, &intSave);
    SET_BIT(g_wlBitmap.lock, lock->bitmap_pos);
    LOS_SpinUnlockRestore(&g_wakeLockSpin, intSave);
}

void linux_wake_unlock(struct wake_lock *lock)
{
    UINT32 intSave;
    if (lock == NULL) {
        return;
    }

    LOS_SpinLockSave(&g_wakeLockSpin, &intSave);
    CLEAR_BIT(g_wlBitmap.lock, lock->bitmap_pos);
    LOS_SpinUnlockRestore(&g_wakeLockSpin, intSave);
}

/* Judge whether the wake lock is active or not */
int linux_wake_lock_active(struct wake_lock *lock)
{
    INT32 ret;
    UINT32 intSave;
    if (lock == NULL) {
        return -1;
    }
    LOS_SpinLockSave(&g_wakeLockSpin, &intSave);
    ret = CHECK_BIT(g_wlBitmap.lock, lock->bitmap_pos);
    LOS_SpinUnlockRestore(&g_wakeLockSpin, intSave);
    return ret;
}

void linux_wake_lock_destroy(struct wake_lock *lock)
{
    UINT32 intSave;
    if (lock == NULL) {
        return;
    }
    LOS_SpinLockSave(&g_wakeLockSpin, &intSave);
    CLEAR_BIT(g_wlBitmap.used, lock->bitmap_pos);
    CLEAR_BIT(g_wlBitmap.lock, lock->bitmap_pos);
    LOS_SpinUnlockRestore(&g_wakeLockSpin, intSave);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
