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

#if defined(_STD_LIB_SOUTH_) & defined(_HILINK_PRODUCT_)
#include "hks_hardware_random.h"

#include <stdint.h>

#include <mbedtls/entropy.h>

#include "securec.h"
#include "base/security_random.h"

#include "hks_errno.h"
#include "hks_types.h"

#define ITERATION_NUM_PADDING 3

int hilink_hardware_random(unsigned char *buf, unsigned int byte_count)
{
    if (buf == NULL)
        return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
    int result = HKS_SUCCESS;
    size_t iter_num = (byte_count + ITERATION_NUM_PADDING) / sizeof(unsigned int);
    size_t remain_len = byte_count % sizeof(unsigned int);

    for (size_t i = 0; i < iter_num; i++) {
        unsigned int rand_num = hilink_rand();

        if ((remain_len != 0) && (i == iter_num - 1)) {
            if (memcpy_s((buf + sizeof(unsigned int) * i),
                remain_len, &rand_num, remain_len) != EOK) {
                result = MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
                break;
            }
        } else {
            if (memcpy_s((buf + sizeof(unsigned int) * i),
                sizeof(unsigned int), &rand_num,
                sizeof(rand_num)) != EOK) {
                result = MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
                break;
            }
        }
    }
    return result;
}

int hilink_hardware_poll(void *p_rng, unsigned char *output, size_t len)
{
    ((void) p_rng);
    if ((output == NULL) || (len > HKS_RANDOM_MAX_LEN) || (len == 0))
        return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
    if (hilink_hardware_random(output, len) == HKS_SUCCESS)
        return HKS_SUCCESS;

    return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
}

int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len,
    size_t *olen)
{
    int ret = hilink_hardware_poll(data, output, len);

    if (ret != HKS_SUCCESS)
        return ret;
    *olen = len;

    return ret;
}
#endif
