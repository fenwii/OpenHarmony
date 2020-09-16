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

#ifndef __BOOT_START_H__
#define __BOOT_START_H__

#include <boot_upg_start_up.h>

hi_void boot_kernel(uintptr_t kaddr);
hi_void execute_upg_boot(hi_void);
hi_void boot_upg_init_verify_addr(const hi_nv_ftm_startup_cfg *cfg);

#endif
