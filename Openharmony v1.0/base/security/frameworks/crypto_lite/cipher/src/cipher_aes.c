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

#include "cipher.h"
#include <stdlib.h>
#include "aes.h"
#include "base64.h"
#include "log.h"
#include "md.h"
#include "md_internal.h"
#include "pkcs5.h"
#include "securec.h"

#define  AES_BYTE_SIZE  256

static int32_t PaddingPkcs5(char *data, size_t inSize)
{
    if (inSize % AES_BLOCK_SIZE == 0) {
        return strlen((const char *)(uintptr_t)data);
    }

    int32_t paddingLen = AES_BLOCK_SIZE - inSize % AES_BLOCK_SIZE;
    int32_t needLen = paddingLen + inSize;
    for (int32_t i = 0; i < paddingLen; i++) {
        data[inSize + i] = paddingLen;
    }

    return needLen;
}

static int32_t UnpaddingPkcs5(char *data, size_t dataLen)
{
    int32_t padLen = data[dataLen - 1];

    if (padLen <= 0 || padLen >= AES_BLOCK_SIZE) {
        return ERROR_CODE_GENERAL;
    }

    for (int32_t i = 0; i < padLen; i++) {
        if (data[dataLen - 1 - i] != padLen) {
            return ERROR_CODE_GENERAL;
        }
        data[dataLen - 1 - i] = '\0';
    }
    return (dataLen - padLen);
}

static char *MallocDecodeData(const char *text, size_t *olen)
{
    size_t decodeLen = 0;
    int32_t ret = mbedtls_base64_decode(NULL, 0, &decodeLen, (const unsigned char *)(text), strlen(text));
    if (ret != MBEDTLS_ERR_BASE64_BUFFER_TOO_SMALL) {
        return NULL;
    }

    if ((decodeLen + 1) <= 0) {
        return NULL;
    }
    char *decData = (char *)malloc(decodeLen + 1);
    if (decData == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "malloc failed, length:%{public}d.", (int32_t)(decodeLen + 1));
        return NULL;
    }
    memset_s(decData,  decodeLen + 1, 0, decodeLen + 1);
    if (mbedtls_base64_decode((unsigned char *)decData, decodeLen + 1, olen,
        (const unsigned char *)text, strlen(text)) != 0) {
        free(decData);
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "decode data failed, text:%s.", text);
        return NULL;
    }
    return decData;
}

static char *MallocEncodeData(const unsigned char *text, size_t *olen)
{
    size_t dataLen = 0;
    int32_t ret = mbedtls_base64_encode(NULL, 0, &dataLen, text, *olen);
    if (ret != MBEDTLS_ERR_BASE64_BUFFER_TOO_SMALL) {
        return NULL;
    }

    if ((dataLen + 1) <= 0) {
        return NULL;
    }
    char *encData = (char *)malloc(dataLen + 1);
    if (encData == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "malloc data failed, expect len:%{public}zu.", dataLen);
        return NULL;
    }
    memset_s(encData, dataLen, 0, dataLen);
    if (mbedtls_base64_encode((unsigned char *)(encData), dataLen, olen, text, *olen) != 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "encode data failed.");
        free(encData);
        return NULL;
    }
    return encData;
}

static int32_t SetIv(const char *ivBuf, int32_t ivBufLen, AesCryptContext *ctx)
{
    if ((ivBuf == NULL) || (ctx == NULL)) {
        return ERROR_CODE_GENERAL;
    }

    if ((ivBufLen < (ctx->iv.ivOffset + ctx->iv.ivLen)) || (ctx->iv.ivOffset < 0) || (ctx->iv.ivLen <= 0)) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "ivLen or ivOffset err.");
        return ERROR_CODE_GENERAL;
    }
    ctx->iv.ivBuf = malloc(ctx->iv.ivLen);
    if (ctx->iv.ivBuf == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "malloc failed.");
        return ERROR_CODE_GENERAL;
    }

    (void)memset_s(ctx->iv.ivBuf, ctx->iv.ivLen, 0, ctx->iv.ivLen);
    int32_t ret = memcpy_s(ctx->iv.ivBuf, ctx->iv.ivLen, ivBuf + ctx->iv.ivOffset, ctx->iv.ivLen);
    if (ret) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "memcpy failed, ret:%{public}d.", ret);
        free(ctx->iv.ivBuf);
        ctx->iv.ivBuf = NULL;
        return ERROR_CODE_GENERAL;
    }

    return ERROR_SUCCESS;
}

static int32_t InitAesCryptContext(const char *key, const AesIvMode *iv, AesCryptContext *ctx)
{
    int32_t ret;

    if (iv == NULL || ctx == NULL || key == NULL) {
        return ERROR_CODE_GENERAL;
    }

    if ((iv->transformation != NULL) && (strcmp(iv->transformation, "AES/CBC/PKCS5Padding"))) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "transformation err.");
        return ERROR_CODE_GENERAL;
    }
    ctx->mode = CIPHER_AES_CBC;
    ctx->iv.ivOffset = iv->ivOffset;

    if ((iv->ivLen >= 0) && (iv->ivLen != AES_BLOCK_SIZE)) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "ivLen:%{public}d error, need be %{public}d Bytes.",
            iv->ivLen, AES_BLOCK_SIZE);
        return ERROR_CODE_GENERAL;
    }
    ctx->iv.ivLen = AES_BLOCK_SIZE;

    if (iv->ivBuf != NULL) {
        size_t ivBufLen = strlen((const char *)(uintptr_t)iv->ivBuf);
        char* ivBuf = MallocDecodeData(iv->ivBuf, &ivBufLen);
        if (ivBuf == NULL) {
            HILOG_ERROR(HILOG_MODULE_HIVIEW, "base64 decode failed.");
            return ERROR_CODE_GENERAL;
        }
        ret = SetIv((const char *)ivBuf, strlen((const char *)(uintptr_t)ivBuf), ctx);
        if (ret == ERROR_CODE_GENERAL) {
            free(ivBuf);
            HILOG_ERROR(HILOG_MODULE_HIVIEW, "SetIv failed.");
            return ERROR_CODE_GENERAL;
        }
        free(ivBuf);
    } else {
        ret = SetIv(ctx->data.key, strlen((const char *)(uintptr_t)ctx->data.key), ctx);
        if (ret == ERROR_CODE_GENERAL) {
            HILOG_ERROR(HILOG_MODULE_HIVIEW, "SetIv failed.");
            return ERROR_CODE_GENERAL;
        }
    }

    return ERROR_SUCCESS;
}

static int32_t InitAesData(const char *action, const char *key, const char *text, CryptData *data)
{
    if (action == NULL || text == 0 || data == NULL || key == NULL) {
        return ERROR_CODE_GENERAL;
    }
    if (!strcmp(action, "encrypt")) {
        data->action = MBEDTLS_AES_ENCRYPT;
        if (strlen(text) % AES_BLOCK_SIZE) {
            data->textLen =  (strlen(text) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE + AES_BLOCK_SIZE;
        } else {
            data->textLen = strlen(text);
        }
        if ((data->textLen + 1) <= 0) {
            return ERROR_CODE_GENERAL;
        }
        data->text = malloc(data->textLen + 1);
        if (data->text == NULL) {
            return ERROR_CODE_GENERAL;
        }
        (void)memset_s(data->text, data->textLen + 1, 0, data->textLen + 1);
        if (memcpy_s(data->text, data->textLen + 1, text, strlen(text))) {
            goto ERROR;
        }
        data->textLen = PaddingPkcs5(data->text, strlen(text));
    } else if (!strcmp(action, "decrypt")) {
        data->action = MBEDTLS_AES_DECRYPT;
        data->text = MallocDecodeData(text, (size_t *)&data->textLen);
        if (data->text == NULL) {
            return ERROR_CODE_GENERAL;
        }
        data->textLen -= data->textLen % AES_BLOCK_SIZE;
    } else {
        return ERROR_CODE_GENERAL;
    }
    data->key = MallocDecodeData(key, (size_t *)&data->keyLen);
    if (data->key == NULL) {
        goto ERROR;
    }
    if (data->keyLen != KEY_LEN) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "key length:%{public}d error, need be %{public}d Bytes.",
            data->keyLen, KEY_LEN);
        memset_s(data->key, data->keyLen, 0, data->keyLen);
        free(data->key);
        data->key = NULL;
        goto ERROR;
    }
    return ERROR_SUCCESS;

ERROR:
    free(data->text);
    data->text = NULL;
    return ERROR_CODE_GENERAL;
}

void DeinitAesCryptData(AesCryptContext *ctx)
{
    if (ctx == NULL) {
        return;
    }

    if (ctx->iv.ivBuf != NULL) {
        free(ctx->iv.ivBuf);
        ctx->iv.ivBuf = NULL;
    }

    if (ctx->data.key != NULL) {
        memset_s(ctx->data.key, ctx->data.keyLen, 0, ctx->data.keyLen);
        free(ctx->data.key);
        ctx->data.key = NULL;
    }

    if (ctx->data.text != NULL) {
        free(ctx->data.text);
        ctx->data.text = NULL;
    }
}

static int32_t DoAesCbcEncrypt(mbedtls_aes_context *aesCtx, AesCryptContext *ctx)
{
    int32_t ret;
    if (ctx->data.action == MBEDTLS_AES_ENCRYPT) {
        ret = mbedtls_aes_setkey_enc(aesCtx, (const unsigned char *)ctx->data.key, AES_BYTE_SIZE);
    } else {
        ret = mbedtls_aes_setkey_dec(aesCtx, (const unsigned char *)ctx->data.key, AES_BYTE_SIZE);
    }
    if (ret != 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "aes setkey error.");
        return ERROR_CODE_GENERAL;
    }

    ret = mbedtls_aes_crypt_cbc(aesCtx, ctx->data.action, ctx->data.textLen,
        (unsigned char *)ctx->iv.ivBuf, (const unsigned char *)ctx->data.text, (unsigned char *)ctx->data.text);
    if (ret != 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "aes crypt cbc error, ret:%{public}d.", ret);
        return ERROR_CODE_GENERAL;
    }

    if (ctx->data.action == MBEDTLS_AES_ENCRYPT) {
        char *out = MallocEncodeData((const unsigned char *)ctx->data.text, (size_t *)&ctx->data.textLen);
        free(ctx->data.text);
        ctx->data.text = out;
        if (out == NULL) {
            return ERROR_CODE_GENERAL;
        }
    } else {
        ctx->data.textLen = UnpaddingPkcs5(ctx->data.text, ctx->data.textLen);
        if (ctx->data.textLen < 0) {
            return ERROR_CODE_GENERAL;
        }
    }

    return ERROR_SUCCESS;
}

int32_t InitAesCryptData(const char *action, const char *text, const char *key, const AesIvMode *iv,
    AesCryptContext *aesCryptCxt)
{
    if (action == NULL || text == NULL || key == NULL || iv == NULL || aesCryptCxt == NULL) {
        return ERROR_CODE_GENERAL;
    }

    int32_t ret = InitAesData(action, key, text, &(aesCryptCxt->data));
    if (ret != 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "fill aes crypt data failed.");
        DeinitAesCryptData(aesCryptCxt);
        return ERROR_CODE_GENERAL;
    }

    ret = InitAesCryptContext(key, iv, aesCryptCxt);
    if (ret != 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "fill aes crypt context failed.");
        return ERROR_CODE_GENERAL;
    }
    return ERROR_SUCCESS;
}

int32_t AesCrypt(AesCryptContext* aesCryptCxt)
{
    if (aesCryptCxt == NULL) {
        return ERROR_CODE_GENERAL;
    }

    if (aesCryptCxt->mode == CIPHER_AES_CBC) {
        mbedtls_aes_context aes;
        mbedtls_aes_init(&aes);
        int32_t ret = DoAesCbcEncrypt(&aes, aesCryptCxt);
        if (ret != ERROR_SUCCESS) {
            HILOG_ERROR(HILOG_MODULE_HIVIEW, "Aes cbc encrypt failed.");
            mbedtls_aes_free(&aes);
            return ERROR_CODE_GENERAL;
        }
        mbedtls_aes_free(&aes);
        return ERROR_SUCCESS;
    } else {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "crypt mode not support.");
        return ERROR_CODE_GENERAL;
    }
}