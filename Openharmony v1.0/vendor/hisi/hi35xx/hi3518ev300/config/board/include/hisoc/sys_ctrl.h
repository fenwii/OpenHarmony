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

#ifndef __HISOC_SYS_CTRL_H__
#define __HISOC_SYS_CTRL_H__

#include "asm/platform.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define REG_SC_CTRL            0
#define REG_SC_SYSRES            0x4
#define PERIPHCTRL24            0x94

#define REG_SC_GEN0            0x0138
#define REG_SC_GEN1            0x013c
#define REG_SC_GEN2            0x0140
#define REG_SC_GEN3            0x0144
#define REG_SC_GEN4            0x0148

#define REG_SC_DDRT0            0x0090
#define NORMAL_BOOTMODE_OFFSET        9
#define NORMAL_BOOTMODE_MASK        3

/********** Communication Register and flag used by bootrom *************/
#define REG_START_FLAG         (SYS_CTRL_REG_BASE + REG_SC_GEN1)
#define CONFIG_START_MAGIC     (0x444f574e)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif

