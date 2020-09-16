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

#ifndef _UPG_START_UP_H_
#define _UPG_START_UP_H_

#include <upg_common.h>

#ifndef offsetof
#define offsetof(type, member) ((hi_u32) & ((type *)0)->member)
#endif

#define ENV_REFRESH_NV 0x55
#define ENV_REFRESH_NV_WAIT 0x56

hi_u32 upg_get_start_up_nv(hi_nv_ftm_startup_cfg *cfg);
hi_u32 upg_save_start_up_nv(hi_nv_ftm_startup_cfg *cfg);

hi_u32 upg_get_wait_mode_nv(hi_nv_ftm_upg_wait_mode *cfg);
hi_u32 upg_save_wait_mode_nv(hi_nv_ftm_upg_wait_mode *cfg);

#endif /* _UPG_START_UP_H_ */
