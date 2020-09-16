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

#ifndef HKS_FILE_H
#define HKS_FILE_H

#include <stdint.h>

#include "hks_file_api.h"
#include "hks_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* the base offset of file */
#define HKS_FILE_OFFSET_BASE 0

int32_t hks_file_register_callbacks(const struct hks_file_callbacks *callbacks);

int32_t hks_file_read(const char *file_name, uint32_t offset,
    uint8_t *buf, uint32_t buf_len, int32_t *len);

int32_t hks_file_write(const char *file_name, uint32_t offset,
    const uint8_t *buf, uint32_t len);

int32_t hks_file_size(const char *file_name, uint32_t *size);

/*
 * cancel callbacks
 * parameter: none
 * return value: none
 */
void hks_file_cancel_callbacks(void);

/*
 * delete file safely
 * parameter:
 *     file_name - [in] - file name
 * return value: none
 */
void hks_file_del_s(const char *file_name);

#ifdef _SECURE_ENVIREMENT_NMI_
void hks_file_liteos_init(void);

#endif

#ifdef __cplusplus
}
#endif
#endif /* HKS_FILE_H */
