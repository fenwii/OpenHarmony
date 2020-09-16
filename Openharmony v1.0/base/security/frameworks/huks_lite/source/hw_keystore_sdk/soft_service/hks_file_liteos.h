/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __HKS_FILE_LITEOS_H_
#define __HKS_FILE_LITEOS_H_

#include "hks_types.h"

#ifdef _SECURE_ENVIREMENT_NMI_

int32_t hks_file_liteos_read(const char *file_name, uint32_t offset, uint8_t *buf, uint32_t len);

int32_t hks_file_liteos_write(const char *file_name, uint32_t offset, const uint8_t *buf, uint32_t len);

int32_t hks_file_liteos_size(const char *file_name);

#endif /* _SECURE_ENVIREMENT_NMI_ */

#endif /* __HKS_FILE_LITEOS_H_ */