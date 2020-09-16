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

#ifndef HKS_STATIC_ST_HKS_HARDWARE_RANDOM_H
#define HKS_STATIC_ST_HKS_HARDWARE_RANDOM_H

#if defined(_STD_LIB_SOUTH_) & defined(_HILINK_PRODUCT_)
#include "mbedtls/entropy_poll.h"

int hilink_hardware_random(unsigned char *buf, unsigned int byte_count);

int hilink_hardware_poll(void *p_rng, unsigned char *output, size_t len);
#endif

#endif /* HKS_STATIC_ST_HKS_HARDWARE_RANDOM_H */
