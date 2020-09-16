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

#include <boot_upg_common.h>

hi_bool boot_upg_tool_bit_test(const hi_u8 *data, hi_u16 pos)
{
    hi_u16 base = pos / BIT_U8;
    hi_u16 i = pos % BIT_U8;
    return (hi_bool)bit_get(data[base], i);
}

hi_void boot_upg_tool_bit_set(hi_u8 *data, hi_u16 pos, hi_u8 val)
{
    hi_u16 base = pos / BIT_U8;
    hi_u16 i = pos % BIT_U8;

    bit_set(data[base], i, val);
}