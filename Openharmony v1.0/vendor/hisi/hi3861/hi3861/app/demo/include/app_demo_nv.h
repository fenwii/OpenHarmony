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

#ifndef __APP_DEMO_NV_H__
#define __APP_DEMO_NV_H__

#include <hi_types_base.h>
#include <hi_stdlib.h>
#include <hi_early_debug.h>
#include <hi_nv.h>
#include <hi_flash.h>
#include <hi_partition_table.h>

#define  HI_NV_DEMO_RST_CFG_ID  0x22
#define  HI_FACTORY_NV_DEMO_ID  0x1

typedef struct {
    hi_u32 nv_demo_test_num0;
    hi_u32 nv_demo_test_num1;
    hi_u32 nv_demo_test_num2;
    hi_u32 nv_demo_test_num3;
} hi_nv_demo_tset_cfg;

typedef struct {
    hi_s32 nv_factory_demo_test_num0;
    hi_s32 nv_factory_demo_test_num1;
    hi_s32 nv_factory_demo_test_num2;
} hi_factory_nv_demo_tset_cfg;

hi_void nv_demo(hi_void);
hi_void factory_nv_demo(hi_void);

#endif