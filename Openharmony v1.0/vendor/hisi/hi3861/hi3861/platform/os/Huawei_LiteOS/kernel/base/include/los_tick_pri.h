/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2018. All rights reserved.
 * Description: Tick
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
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
 * --------------------------------------------------------------------------- */

#ifndef _LOS_TICK_PRI_H
#define _LOS_TICK_PRI_H

#include "los_tick.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define SYSTEM_CLOCK_FREQ_24M    24
#define SYSTEM_CLOCK_FREQ_40M    40

/**
 * @ingroup los_tick
 * Count of Ticks
 */
extern UINT64 g_tickCount;

/**
 * @ingroup los_tick
 * Ticks per second
 */
extern UINT32 g_ticksPerSec;

/**
 * @ingroup los_tick
 * Cycles per Tick
 */
extern UINT32 g_cyclesPerTick;

extern UINT32 g_sysClock;
/**
 * @ingroup  los_tick
 * @brief Handle the system tick timeout.
 *
 * @par Description:
 * This API is called when the system tick timeout and triggers the interrupt.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param none.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>los_tick_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID OsTickHandler(VOID);
extern UINT32 OsTimerInit(VOID);
extern VOID OsTimerDisable(VOID);
extern VOID OsTimerStop(VOID);
extern VOID OsTimerStart(VOID);
extern LITE_OS_RAM_SECTION VOID OsPlatformTickHandler(VOID);
extern VOID OsPlatformGetCycle(UINT32 *cntHigh, UINT32 *cntLow);
extern UINT32* OsTimerGetFirstTick(VOID);
extern UINT32 OsTimerGetReloadValue(VOID);
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_TICK_PRI_H */
