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

#ifndef __MTD_COMMON_H__
#define __MTD_COMMON_H__

#include "fs/fs.h"

const struct file_operations_vfs *GetMtdCharFops(void);
const struct block_operations *GetDevSpinorOps(void);
const struct block_operations *GetDevNandOps(void);

#endif /* End of __MTD_COMMON_H__ */

