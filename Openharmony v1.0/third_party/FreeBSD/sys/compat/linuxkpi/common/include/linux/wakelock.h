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

#ifndef __LINUX_WAKELOCK_H__
#define __LINUX_WAKELOCK_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

enum {
    WAKE_LOCK_SUSPEND, /* Prevent suspend */
    WAKE_LOCK_IDLE
};

struct wakeup_source {
    const char  *name;
};

struct wake_lock {
    struct wakeup_source ws;
    unsigned int bitmap_pos;
};

/**
 * @ingroup  wakelock
 * @brief Activate the wake lock.
 *
 * @par Description:
 * This API is used to activate the wake lock.
 *
 * @attention
 * <ul>
 * <li>Use this function,you must run wake_lock_init first !</li>
 * <li>please make sure the parameter lock is valid,otherwise the system maybe crash!</li>
 * </ul>
 *
 * @param  lock [IN] Type #struct wake_lock   struct of the lock.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>Wakelock.h: the header file that contains the API declaration.</li></ul>
 * @see wake_unlock.
 */
void linux_wake_lock(struct wake_lock *lock);

/**
 * @ingroup  wakelock
 * @brief Unlock the wake lock.
 *
 * @par Description:
 * This API is used to Unlock the wake lock,and make it invalid.
 *
 * @attention
 * <ul>
 * <li>Use this function,you must run wake_lock_init first !</li>
 * <li>please make sure the parameter lock is valid,otherwise the system maybe crash!</li>
 * </ul>
 *
 * @param  lock [IN] Type #struct wake_lock   struct of the lock.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>Wakelock.h: the header file that contains the API declaration.</li></ul>
 * @see wake_lock.
 */
void linux_wake_unlock(struct wake_lock *lock);

/**
 * @ingroup  wakelock
 * @brief judge whether the wake lock is active or not.
 *
 * @par Description:
 * This API is used to judge whether the wake lock is active or not.
 *
 * @attention
 * <ul>
 * <li>Use this function,you must run wake_lock_init first !</li>
 * <li>please make sure the parameter lock is valid,otherwise the system maybe crash!</li>
 * </ul>
 *
 * @param  lock [IN] Type #struct wake_lock   struct of the lock.
 *
 * @retval #1 the wake lock is active.
 * @retval #0 the wake lock is not active.
 * @par Dependency:
 * <ul><li>Wakelock.h: the header file that contains the API declaration.</li></ul>
 * @see none.
 */
int linux_wake_lock_active(struct wake_lock *lock);

/**
 * @ingroup  wakelock
 * @brief initial a new wakelock.
 *
 * @par Description:
 * This API is used to initial a wakelock.
 *
 * @attention
 * <ul>
 * <li>DO NOT init more than 32 wack_lock!.</li>
 * <li>please make sure the parameter lock type name are valid,otherwise the system maybe crash!</li>
 * </ul>
 *
 * @param  lock [IN] Type #struct wake_lock   struct of the lock.
 * @param  type [IN] Type #int   type of the new wakelock,not supported now.
 * @param  name [IN] Type #const char   name of the new wakelock.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>Wakelock.h: the header file that contains the API declaration.</li></ul>
 * @see none.
 */
void linux_wake_lock_init(struct wake_lock *lock, int type, const char *name);

#define wake_lock(lock)    \
    linux_wake_lock(lock)

#define wake_unlock(lock)    \
    linux_wake_unlock(lock)

#define wake_lock_active(lock)    \
    linux_wake_lock_active(lock)

#define wake_lock_init(lock, type, name)    \
    linux_wake_lock_init(lock, type, name)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* __LINUX_WAKELOCK_H__ */
