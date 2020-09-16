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

#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Read token value form device.
 *
 * @param token The token value, len The token len.
 * @returns 0 if it succeeds and get the update area token,
 *          1 if it succeeds and get the pre-made token,
 *         -1 if it fails, -2 if it no pre-made token.
 */
int ReadToken(char *token, unsigned int len);

/**
 * @brief Write token value to device.
 *
 * @param token The token value, len The token len.
 * @returns 0 if it succeeds, -1 if it fails.
 */
int WriteToken(const char *token, unsigned int len);

/**
 * @brief Get AcKey value form device.
 *
 * @param acKey The acKey value, len The acKey len.
 * @returns 0 if it succeeds, -1 if it fails.
 */
int GetAcKey(char *acKey, unsigned int len);

/**
 * @brief Get ProdId value form device.
 *
 * @param productId[] The productId value, len The productId len.
 * @returns 0 if it succeeds, -1 if it fails.
 */
int GetProdId(char productId[], size_t len);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif