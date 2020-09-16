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

#ifndef __UPG_USER_VERIFY_H__
#define __UPG_USER_VERIFY_H__

#include "upg_common.h"

typedef struct {
    hi_u32 (*upg_file_check_fn)(const hi_upg_user_info *info, hi_void *param);
    hi_void *user_param;
} upg_user_verify_inf;

hi_u32 upg_user_define_verify(const hi_upg_user_info *info);

#endif /* __UPG_USER_VERIFY_H__ */

