/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
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

#ifndef __HISOC_TIMER_H__
#define __HISOC_TIMER_H__

#include "asm/platform.h"
#include "los_bitmap.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define TIMER_LOAD              0x0
#define TIMER_VALUE             0x4
#define TIMER_CONTROL           0x8
#define TIMER_INT_CLR           0xc
#define TIMER_RIS               0x10
#define TIMER_MIS               0x14
#define TIMER_BGLOAD            0x18

#define TIMER0_ENABLE   BIT(16)
#define TIMER1_ENABLE   BIT(17)
#define TIMER2_ENABLE   BIT(18)
#define TIMER3_ENABLE   BIT(19)
#define TIMER4_ENABLE   BIT(20)
#define TIMER5_ENABLE   BIT(21)
#define TIMER6_ENABLE   BIT(22)
#define TIMER7_ENABLE   BIT(23)
#define TIMER8_ENABLE   BIT(24)
#define TIMER9_ENABLE   BIT(25)
#define TIMER10_ENABLE   BIT(26)
#define TIMER11_ENABLE   BIT(27)

unsigned int arch_timer_rollback(void);
VOID LOS_Udelay(UINT32 usecs);
VOID LOS_Mdelay(UINT32 msecs);
VOID reset_timer_masked(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif

