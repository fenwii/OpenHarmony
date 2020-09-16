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

#ifndef SECURITY_APP_VERIFY_HAP_H
#define SECURITY_APP_VERIFY_HAP_H

#include "app_centraldirectory.h"
#include "app_common.h"
#include "app_file.h"
#include "app_verify.h"
#include "app_verify_pub.h"
#include "mbedtls/pk.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define ALGORITHM_MASK 0x000f
#define ALGORITHM_SHA256 0x01
#define ALGORITHM_SHA384 0x02
#define ALGORITHM_SHA512 0x03
#define ALGORITHM_PKCS1_SHA256 0x04
#define ALGORITHM_PKCS1_SHA384 0x05
#define ALGORITHM_PKCS1_SHA512 0x06

#define HAP_DIGEST_PRIFIX_LEN 5
#define MAX_OID_LENGTH 128
#define HASH_BLOB_LEN (1024 * 1024)
#define ONCE_READ_LEN (1024 * 64)
#define HASH_ALG_SHA256     MBEDTLS_MD_SHA256 /* sha256 */
#define HASH_ALG_SHA384     MBEDTLS_MD_SHA384 /* sha384 */
#define HASH_ALG_SHA512     MBEDTLS_MD_SHA512 /* sha512 */

bool VerifyIntegrityChunk(int digestAlgorithm, int fp, const SignatureInfo *signInfo, const HapBuf *actualDigest);
int GetDigestAlgorithmId(unsigned int signAlgorithm);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
