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

#ifndef AES_GCM_H
#define AES_GCM_H

#define SESSION_KEY_LENGTH        32
#define IV_LEN                    12
#define TAG_LEN                   16
#define OVERHEAD_LEN              (IV_LEN + TAG_LEN)

#define GCM_KEY_BITS_LEN_128      128
#define GCM_KEY_BITS_LEN_256      256

typedef struct {
    unsigned int keybits;
    unsigned char key[SESSION_KEY_LENGTH];
    unsigned char iv[IV_LEN];
} AesGcmCipherKey;

unsigned char* GenerateRandomIv(void);
int EncryptTransData(const AesGcmCipherKey *cipherkey, const unsigned char* plainText, unsigned int plainTextSize,
    unsigned char* cipherText, unsigned int cipherTextLen);
int DecryptTransData(const AesGcmCipherKey *cipherkey, const unsigned char* cipherText, unsigned int cipherTextSize,
    unsigned char* plain, unsigned int plainLen);
#endif // AES_GCM_H
