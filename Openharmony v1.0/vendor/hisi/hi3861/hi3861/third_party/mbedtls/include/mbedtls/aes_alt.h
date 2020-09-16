/**
 * \file aes.h
 *
 * \brief   This file contains AES definitions and functions.
 *
 *          The Advanced Encryption Standard (AES) specifies a FIPS-approved
 *          cryptographic algorithm that can be used to protect electronic
 *          data.
 *
 *          The AES algorithm is a symmetric block cipher that can
 *          encrypt and decrypt information. For more information, see
 *          <em>FIPS Publication 197: Advanced Encryption Standard</em> and
 *          <em>ISO/IEC 18033-2:2006: Information technology -- Security
 *          techniques -- Encryption algorithms -- Part 2: Asymmetric
 *          ciphers</em>.
 *
 *          The AES-XTS block mode is standardized by NIST SP 800-38E
 *          <https://nvlpubs.nist.gov/nistpubs/legacy/sp/nistspecialpublication800-38e.pdf>
 *          and described in detail by IEEE P1619
 *          <https://ieeexplore.ieee.org/servlet/opac?punumber=4375278>.
 */

/*  Copyright (C) 2006-2018, Arm Limited (or its affiliates), All Rights Reserved.
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of Mbed TLS (https://tls.mbed.org)
 */

#ifndef MBEDTLS_AES_ALT_H
#define MBEDTLS_AES_ALT_H
#include "hi_cipher.h"
#include "securec.h"
/**
 * \brief The AES context-type definition.
 */
#define mbedtls_aes_context hi_cipher_aes_ctrl

#if defined(MBEDTLS_CIPHER_MODE_XTS)
typedef struct mbedtls_aes_xts_context
{
    mbedtls_aes_context crypt; /*!< The AES context to use for AES block
                                        encryption or decryption. */
    mbedtls_aes_context tweak; /*!< The AES context used for tweak
                                        computation. */
} mbedtls_aes_xts_context;

#endif /* MBEDTLS_CIPHER_MODE_XTS */

#endif /* aes_alt.h */
