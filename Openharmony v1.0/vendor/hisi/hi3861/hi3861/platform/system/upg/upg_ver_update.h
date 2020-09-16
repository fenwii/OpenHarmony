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

#ifndef _UPG_VER_UPDATE_H_
#define _UPG_VER_UPDATE_H_

#include "hi_types.h"

#define UPG_NMI_BASE_ADDRESS 0x40010000
#define UPG_NMI_CTRL         0x0258
#define UPG_NMI_INT_MOD_DONE_EN_POS 0

#define UPG_UPDATE_VER_NONE     0
#define UPG_UPDATE_VER_FIRMARE  1
#define UPG_UPDATE_VER_BOOT     2
hi_bool upg_update_ver(hi_void);
hi_u32 upg_start_and_wait_update_ver(hi_u8 update_ver_type);

#endif /* _UPG_VER_UPDATE_H_ */
