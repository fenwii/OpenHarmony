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

#include "hks_bn.h"

void hks_bn_init(mbedtls_mpi *bn)
{
    mbedtls_mpi_init(bn);
}

void hks_bn_free(mbedtls_mpi *bn)
{
    mbedtls_mpi_free(bn);
}

int32_t hks_bn_import(mbedtls_mpi *bn, const unsigned char *data, size_t size)
{
    return mbedtls_mpi_read_binary(bn, data, size);
}

int32_t hks_bn_export(const mbedtls_mpi *bn, unsigned char *data, size_t size)
{
    return mbedtls_mpi_write_binary(bn, data, size);
}

int32_t hks_bn_write_string(const mbedtls_mpi *bn, int radix,
    char *buf, size_t buf_len, size_t *o_len)
{
    return mbedtls_mpi_write_string(bn, radix, buf, buf_len, o_len);
}

int32_t hks_bn_mpi_exp_mod(mbedtls_mpi *x, const mbedtls_mpi *a,
    const mbedtls_mpi *e, const mbedtls_mpi *n)
{
    return mbedtls_mpi_exp_mod(x, a, e, n, NULL);
}
