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

#ifndef    __HISOC_CPU_H__
#define    __HISOC_CPU_H__

#include "asm/platform.h"
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#define ARM_GIC_CPU_CTRL                    0x00
#define ARM_GIC_CPU_PRIMASK                 0x04
#define ARM_GIC_CPU_BINPOINT                0x08
#define ARM_GIC_CPU_INTACK                  0x0c
#define ARM_GIC_CPU_EOI                     0x10
#define ARM_GIC_CPU_RUNNINGPRI              0x14
#define ARM_GIC_CPU_HIGHPRI                 0x18

#define ARM_GIC_DIST_CTRL                   0x000
#define ARM_GIC_DIST_CTR                    0x004
#define ARM_GIC_DIST_ENABLE_SET             0x100
#define ARM_GIC_DIST_ENABLE_CLEAR           0x180
#define ARM_GIC_DIST_PENDING_SET            0x200
#define ARM_GIC_DIST_PENDING_CLEAR          0x280
#define ARM_GIC_DIST_ACTIVE_BIT             0x300
#define ARM_GIC_DIST_PRI                    0x400
#define ARM_GIC_DIST_TARGET                 0x800
#define ARM_GIC_DIST_CONFIG                 0xc00
#define ARM_GIC_DIST_SOFTINT                0xf00


#define REG_A7_PERI_GIC_DIST                0x1000
#define REG_A7_PERI_GIC_CPU                 0x2000
#define REG_BASE_A7_PERI                    ARM_REG_BASE
#define CFG_ARM_GIC_CPU_BASE                (IO_ADDRESS(REG_BASE_A7_PERI) + REG_A7_PERI_GIC_CPU)
#define CFG_ARM_GIC_DIST_BASE               (IO_ADDRESS(REG_BASE_A7_PERI) + REG_A7_PERI_GIC_DIST)
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

