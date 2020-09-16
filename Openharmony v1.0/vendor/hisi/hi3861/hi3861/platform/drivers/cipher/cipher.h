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
 *
 * Description: head file of cipher
 */

#ifndef __CIPHER_H__
#define __CIPHER_H__
#include <hi_types.h>
#include <hi3861_platform_base.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif  /* __cplusplus */

hi_u32 cipher_init(hi_bool is_liteos);
hi_u32 cipher_deinit(hi_void);
hi_void cipher_clk_switch(hi_bool enable);
hi_bool cipher_get_clk_ctrl(hi_void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif  /* __cplusplus */

#endif  /* __CIPHER_H__ */

