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

#ifndef    __HISOC_CLOCK_H__
#define    __HISOC_CLOCK_H__

#include "asm/platform.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define    PERI_CRG12        (CRG_REG_BASE + 0x30)

/*-----------------------------------------------------------------------
 * cpu_init configuration
 * if bit[13:12] = 1b, AXI = 200M
 *----------------------------------------------------------------------*/
/*lint -e160 */
#define get_bus_clk() 50000000
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

