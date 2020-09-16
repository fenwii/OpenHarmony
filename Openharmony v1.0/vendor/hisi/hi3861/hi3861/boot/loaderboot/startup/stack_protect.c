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

#include "hi_boot_rom.h"

unsigned long __stack_chk_guard = 0xd00a0dff;

void __stack_chk_fail(void)
{
    boot_msg1("stack-protector:corrupted in:", (uintptr_t)__builtin_return_address(0));
    udelay(2000); /* delay 2000 us to reset */
    global_reset();
}