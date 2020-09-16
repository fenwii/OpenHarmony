/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
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

#ifndef CIPHER_H
#define CIPHER_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define KEY_LEN              32
#define AES_BLOCK_SIZE       16
#define ERROR_CODE_GENERAL   -1
#define ERROR_SUCCESS         0

typedef enum {
    CIPHER_AES_ECB,
    CIPHER_AES_CBC
} CipherAesMode;

typedef struct {
    char *text;
    char *key;
    int32_t action;
    int32_t textLen;
    int32_t keyLen;
} CryptData;

typedef struct {
    char *transformation;
    char *ivBuf;
    int32_t ivOffset;
    int32_t ivLen;
} AesIvMode;

typedef struct {
    CryptData data;
    CipherAesMode mode;
    AesIvMode iv;
} AesCryptContext;

typedef struct {
    char *data;
    size_t length;
} RsaData;

typedef struct {
    char *trans;
    char *action;
    char *key;
    size_t keyLen;
} RsaKeyData;

int32_t InitAesCryptData(const char *action, const char *text, const char *key,
    const AesIvMode *iv, AesCryptContext *aesCryptCxt);
int32_t AesCrypt(AesCryptContext *aesCryptCxt);
void DeinitAesCryptData(AesCryptContext *aesCryptCxt);
int32_t RsaCrypt(RsaKeyData *key, RsaData *inData, RsaData *outData);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif // CIPHER_H