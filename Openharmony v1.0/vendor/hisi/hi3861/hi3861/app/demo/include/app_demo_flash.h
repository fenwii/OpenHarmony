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

#ifndef __APP_DEMO_FLASH_H__
#define __APP_DEMO_FLASH_H__

#include <hi_types_base.h>

#ifdef TEST_KERNEL_FLASH

#include <hi_flash.h>
#include <hi_task.h>
#include <hi_stdlib.h>
#include <hi_watchdog.h>
#include <hi_early_debug.h>
#include <hi_time.h>

#define TEST_SIZE 0x1000
#define TEST_FLASH_OFFSET 0x1FF000

hi_void cmd_test_flash(hi_u32 test_time, hi_u32 test_mode);
#endif
#endif