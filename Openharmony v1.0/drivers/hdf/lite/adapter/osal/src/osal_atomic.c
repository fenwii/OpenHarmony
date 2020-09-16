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

#include "osal_atomic.h"
#include "los_hwi.h"
#include "hdf_log.h"

#define HDF_LOG_TAG osal_atomic

#define OSAL_BITS_PER_LONG 32
#define OSAL_BIT_MASK(nr) (1UL << ((nr) % OSAL_BITS_PER_LONG))
#define OSAL_BIT_WORD(nr) ((nr) / OSAL_BITS_PER_LONG)
#define OSAL_BITOP_WORD(nr) ((nr) / OSAL_BITS_PER_LONG)

static inline void OsalAtomicAdd(int32_t i, OsalAtomic *v)
{
    uint32_t irq_status;

    irq_status = LOS_IntLock();
    v->counter += i;
    LOS_IntRestore(irq_status);
}

static inline void OsalAtomicSub(int32_t i, OsalAtomic *v)
{
    uint32_t irq_status;

    irq_status = LOS_IntLock();
    v->counter -= i;
    LOS_IntRestore(irq_status);
}

int32_t OsalAtomicRead(const OsalAtomic *v)
{
    if (v == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return -1;
    }
    return v->counter;
}

void OsalAtomicSet(OsalAtomic *v, int32_t counter)
{
    uint32_t irq_status;

    if (v == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return;
    }

    irq_status = LOS_IntLock();
    v->counter = counter;
    LOS_IntRestore(irq_status);
}

void OsalAtomicInc(OsalAtomic *v)
{
    if (v == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return;
    }

    OsalAtomicAdd(1, v);
}

void OsalAtomicDec(OsalAtomic *v)
{
    if (v == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return;
    }

    OsalAtomicSub(1, v);
}

int32_t OsalTestBit(unsigned long nr, const volatile unsigned long *addr)
{
    if (addr == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return -1;
    }

    return (1UL & (addr[OSAL_BIT_WORD(nr)] >> (nr & (OSAL_BITS_PER_LONG - 1))));
}

int32_t OsalTestSetBit(unsigned long nr, volatile unsigned long *addr)
{
    uint32_t intSave;

    if (addr == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return -1;
    }

    intSave = LOS_IntLock();

    const unsigned long mask = OSAL_BIT_MASK(nr);
    unsigned long *p = ((unsigned long *)addr) + OSAL_BIT_WORD(nr);
    unsigned long old = *p;
    *p = old | mask;

    LOS_IntRestore(intSave);
    return ((old & mask) != 0);
}

int32_t OsalTestClearBit(unsigned long nr, volatile unsigned long *addr)
{
    uint32_t intSave;

    if (addr == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return -1;
    }

    intSave = LOS_IntLock();

    const unsigned long mask = OSAL_BIT_MASK(nr);
    unsigned long *p = ((unsigned long *)addr) + OSAL_BIT_WORD(nr);
    unsigned long old = *p;
    *p = old & ~mask;

    LOS_IntRestore(intSave);
    return ((old & mask) != 0);
}

void OsalClearBit(unsigned long nr, volatile unsigned long *addr)
{
    uint32_t intSave;

    if (addr == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return;
    }

    intSave = LOS_IntLock();

    const unsigned long mask = OSAL_BIT_MASK(nr);
    unsigned long *p = ((unsigned long *)addr) + OSAL_BIT_WORD(nr);
    *p &= ~mask;

    LOS_IntRestore(intSave);
}

