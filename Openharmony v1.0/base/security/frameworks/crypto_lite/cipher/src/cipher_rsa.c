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
#include "base64.h"
#include "ctr_drbg.h"
#include "entropy.h"
#include "log.h"
#include "pk.h"
#include "platform.h"
#include "rsa.h"
#include "securec.h"

#define RSA_KEY_BYTE   66
#define NUM_FOUR       4
#define NUM_THREE      3

static char *RsaMallocPrivateKey(const unsigned char *key, size_t *keyLen)
{
    int32_t ret;
    const char start[] = "-----BEGIN RSA PRIVATE KEY-----\n";
    const char end[] = "\n-----END RSA PRIVATE KEY-----\n";
    size_t startLen = strlen(start);
    size_t endLen = strlen(end);
    size_t keyFinalLen = *keyLen + startLen + endLen + 1;

    char *privateKey = malloc(keyFinalLen);
    if (privateKey == NULL) {
        return NULL;
    }

    (void)memset_s(privateKey, keyFinalLen, 0, keyFinalLen);
    ret = memcpy_s(privateKey, keyFinalLen, start, startLen);
    if (ret) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "memcpy failed.");
        free(privateKey);
        return NULL;
    }

    ret = memcpy_s(privateKey + startLen, keyFinalLen - startLen, key, *keyLen);
    if (ret) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "memcpy failed.");
        free(privateKey);
        return NULL;
    }

    ret = memcpy_s(privateKey + startLen + *keyLen, keyFinalLen - startLen - *keyLen, end, endLen);
    if (ret) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "memcpy failed.");
        memset_s(privateKey, keyFinalLen, 0, keyFinalLen);
        free(privateKey);
        return NULL;
    }

    *keyLen = keyFinalLen;
    return privateKey;
}

static char *RsaMallocPublicKey(const unsigned char *key, size_t *keyLen)
{
    int32_t ret;
    const char start[] = "-----BEGIN PUBLIC KEY-----\n";
    const char end[] = "\n-----END PUBLIC KEY-----\n";
    size_t startLen = strlen(start);
    size_t endLen = strlen(end);
    size_t keyFinalLen = *keyLen + startLen + endLen + 1;

    char *pubKey = malloc(keyFinalLen);
    if (pubKey == NULL) {
        return NULL;
    }

    (void)memset_s(pubKey, keyFinalLen, 0, keyFinalLen);
    ret = memcpy_s(pubKey, keyFinalLen, start, startLen);
    if (ret) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "memcpy failed.");
        free(pubKey);
        return NULL;
    }

    ret = memcpy_s(pubKey + startLen, keyFinalLen - startLen, key, *keyLen);
    if (ret) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "memcpy failed.");
        free(pubKey);
        return NULL;
    }

    ret = memcpy_s(pubKey + startLen + *keyLen, keyFinalLen - startLen - *keyLen, end, endLen);
    if (ret) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "memcpy failed.");
        memset_s(pubKey, keyFinalLen, 0, keyFinalLen);
        free(pubKey);
        return NULL;
    }

    *keyLen = keyFinalLen;
    return pubKey;
}

static int32_t RsaLoadPrivateKey(int32_t mode, mbedtls_pk_context *pk, const unsigned char *key, size_t keyLen)
{
    int32_t ret;
    size_t finalKeyLen = keyLen;
    mbedtls_rsa_context *rsa = NULL;
    char *finalKey = RsaMallocPrivateKey(key, &finalKeyLen);
    if (finalKey == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "malloc private key error, final Key Length:%{public}zu.", finalKeyLen);
        return ERROR_CODE_GENERAL;
    }

    ret = mbedtls_pk_parse_key(pk, (const unsigned char *)finalKey, finalKeyLen, NULL, 0);
    if (ret != 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "parse private key error, mode:%{public}d ret:%{public}d.", mode, ret);
        goto ERROR;
    }

    rsa = mbedtls_pk_rsa(*pk);
    if (rsa == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "rsa error, mode:%{public}d.", mode);
        goto ERROR;
    }

    if (mbedtls_rsa_check_privkey(rsa) != 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "check private key failed.");
        goto ERROR;
    }

    /* set padding as OAEPWITHSHA256 */
    mbedtls_rsa_set_padding(rsa, MBEDTLS_RSA_PKCS_V21, MBEDTLS_MD_SHA256);
    memset_s(finalKey, finalKeyLen, 0, finalKeyLen);
    free(finalKey);
    return ERROR_SUCCESS;

ERROR:
    memset_s(finalKey, finalKeyLen, 0, finalKeyLen);
    free(finalKey);
    return ERROR_CODE_GENERAL;
}

static int32_t RsaLoadPublicKey(int32_t mode, mbedtls_pk_context *pk, const unsigned char *key, size_t keyLen)
{
    int32_t ret;
    size_t finalKeyLen = keyLen;
    mbedtls_rsa_context *rsa = NULL;
    char* finalKey = RsaMallocPublicKey(key, &finalKeyLen);
    if (finalKey == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "malloc public key error, final Key Length:%{public}zu.", finalKeyLen);
        return ERROR_CODE_GENERAL;
    }

    ret = mbedtls_pk_parse_public_key(pk, (const unsigned char *)finalKey, finalKeyLen);
    if (ret != 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "parse public key error, mode:%{public}d ret:%{public}d.", mode, ret);
        goto ERROR;
    }

    rsa = mbedtls_pk_rsa(*pk);
    if (rsa == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "pk rsa error, mode:%{public}d.", mode);
        goto ERROR;
    }

    if (mbedtls_rsa_check_pubkey(rsa)) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "check public key failed.");
        goto ERROR;
    }
    /* set padding as OAEPWITHSHA256 */
    mbedtls_rsa_set_padding(rsa, MBEDTLS_RSA_PKCS_V21, MBEDTLS_MD_SHA256);
    memset_s(finalKey, finalKeyLen, 0, finalKeyLen);
    free(finalKey);
    return ERROR_SUCCESS;

ERROR:
    memset_s(finalKey, finalKeyLen, 0, finalKeyLen);
    free(finalKey);
    return ERROR_CODE_GENERAL;
}

static int32_t RsaLoadKey(int32_t mode, mbedtls_pk_context *pk, const unsigned char *key, size_t keyLen)
{
    if (mode == MBEDTLS_RSA_PUBLIC) {
        return RsaLoadPublicKey(mode, pk, key, keyLen);
    } else {
        return RsaLoadPrivateKey(mode, pk, key, keyLen);
    }
}

static void RsaInit(mbedtls_ctr_drbg_context *ctrDrbg, mbedtls_entropy_context *entropy)
{
    mbedtls_ctr_drbg_init(ctrDrbg);
    mbedtls_entropy_init(entropy);
    (void)mbedtls_ctr_drbg_seed(ctrDrbg, mbedtls_entropy_func, entropy, NULL, 0);
}

static void RsaDeinit(mbedtls_ctr_drbg_context *ctrDrbg, mbedtls_entropy_context *entropy)
{
    mbedtls_ctr_drbg_free(ctrDrbg);
    mbedtls_entropy_free(entropy);
}

static int32_t RsaEncryptBase64Encode(int32_t cipherTotalLen, char *cipherText, int32_t cipherTextLen)
{
    if (cipherTotalLen <= 0) {
        return ERROR_CODE_GENERAL;
    }

    char *tempBuf = malloc(cipherTotalLen);
    if (tempBuf == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "RsaEncrypt Base64Encode malloc fail.");
        return ERROR_CODE_GENERAL;
    }

    (void)memset_s(tempBuf, cipherTotalLen, 0, cipherTotalLen);
    int32_t ret = memcpy_s(tempBuf, cipherTotalLen, cipherText, cipherTotalLen);
    if (ret) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "memcpy fail.");
        free(tempBuf);
        return ERROR_CODE_GENERAL;
    }

    (void)memset_s(cipherText, cipherTextLen, 0, cipherTextLen);
    size_t dataLen = 0;
    ret = mbedtls_base64_encode(NULL, 0, &dataLen, (const unsigned char *)tempBuf, cipherTotalLen);
    if (ret != MBEDTLS_ERR_BASE64_BUFFER_TOO_SMALL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "base64_encode fail.");
        free(tempBuf);
        return ERROR_CODE_GENERAL;
    }

    ret = mbedtls_base64_encode((unsigned char *)cipherText, cipherTextLen, &dataLen,
        (const unsigned char *)tempBuf, cipherTotalLen);
    if (ret) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "base64_encode fail.");
        free(tempBuf);
        return ERROR_CODE_GENERAL;
    }
    free(tempBuf);
    return ERROR_SUCCESS;
}

static int32_t RsaEncryptMultipleBlock(mbedtls_rsa_context *rsa, const char *plainText,
    char *cipherText, int32_t cipherTextLen)
{
    mbedtls_ctr_drbg_context ctrDrbg;
    mbedtls_entropy_context entropy;
    int32_t rsaLen = mbedtls_rsa_get_len(rsa);
    int32_t rsaContentLen = rsaLen - RSA_KEY_BYTE;
    if ((rsaContentLen <= 0) || (rsaLen <= 0)) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "rsa content len:%{public}d, rsaLen:%{public}d.", rsaContentLen, rsaLen);
        return ERROR_CODE_GENERAL;
    }
    int32_t count = strlen((const char *)(uintptr_t)plainText) / rsaContentLen;
    int32_t remain = strlen((const char *)(uintptr_t)plainText) % rsaContentLen;
    int32_t cipherTotalLen = 0;
    unsigned char *buf = (unsigned char *)malloc(rsaLen);
    if (buf == NULL) {
        return ERROR_CODE_GENERAL;
    }
    RsaInit(&ctrDrbg, &entropy);
    for (int32_t i = 0; i < count; i++) {
        (void)memset_s(buf, rsaLen, 0, rsaLen);
        if (mbedtls_rsa_pkcs1_encrypt(rsa, mbedtls_ctr_drbg_random, &ctrDrbg,
            MBEDTLS_RSA_PUBLIC, rsaContentLen, (const unsigned char *)(plainText + i * rsaContentLen), buf)) {
            goto ERROR;
        }
        if (memcpy_s(cipherText + i * rsaLen, cipherTextLen - i * rsaLen, buf, rsaLen)) {
            goto ERROR;
        }
        cipherTotalLen += rsaLen;
    }
    if (remain > 0) {
        (void)memset_s(buf, rsaLen, 0, rsaLen);
        if (mbedtls_rsa_pkcs1_encrypt(rsa, mbedtls_ctr_drbg_random, &ctrDrbg,
            MBEDTLS_RSA_PUBLIC, remain, (const unsigned char *)(plainText + count * rsaContentLen), buf)) {
            goto ERROR;
        }
        if (memcpy_s(cipherText + count * rsaLen, cipherTextLen - count * rsaLen, buf, rsaLen)) {
            goto ERROR;
        }
        cipherTotalLen += rsaLen;
    }
    if (RsaEncryptBase64Encode(cipherTotalLen, cipherText, cipherTextLen)) {
        goto ERROR;
    }
    free(buf);
    RsaDeinit(&ctrDrbg, &entropy);
    return ERROR_SUCCESS;

ERROR:
    free(buf);
    RsaDeinit(&ctrDrbg, &entropy);
    return ERROR_CODE_GENERAL;
}

static int32_t RsaEncrypt(RsaKeyData *key, const RsaData *plain, RsaData *cipher)
{
    if ((key->trans != NULL) && (strcmp(key->trans, "RSA/None/OAEPWithSHA256AndMGF1Padding"))) {
        return ERROR_CODE_GENERAL;
    }

    mbedtls_pk_context pk;
    mbedtls_pk_init(&pk);
    if (RsaLoadKey(MBEDTLS_RSA_PUBLIC, &pk, (const unsigned char *)key->key, key->keyLen) != 0) {
        mbedtls_pk_free(&pk);
        return ERROR_CODE_GENERAL;
    }

    mbedtls_rsa_context *rsa = mbedtls_pk_rsa(pk);
    if (rsa == NULL) {
        mbedtls_pk_free(&pk);
        return ERROR_CODE_GENERAL;
    }

    int32_t rsaLen = mbedtls_rsa_get_len(rsa);
    int32_t rsaContentLen = rsaLen - RSA_KEY_BYTE;
    if (rsaContentLen <= 0) {
        mbedtls_pk_free(&pk);
        return ERROR_CODE_GENERAL;
    }

    int32_t count = plain->length / rsaContentLen;
    int32_t remain = plain->length % rsaContentLen;
    if (cipher->data == NULL) {
        cipher->length = rsaLen * count + (remain ? rsaLen : 0);
        cipher->length = (cipher->length / NUM_THREE + 1) * NUM_FOUR + 1;
        mbedtls_pk_free(&pk);
        return ERROR_SUCCESS;
    }

    if (RsaEncryptMultipleBlock(rsa, plain->data, cipher->data, cipher->length) != 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "Rsa encrypt block error.");
        mbedtls_pk_free(&pk);
        return ERROR_CODE_GENERAL;
    }

    mbedtls_pk_free(&pk);
    return ERROR_SUCCESS;
}

static int32_t RsaPkcs1Decrypt(mbedtls_rsa_context *rsa, size_t rsaLen, RsaData *cipher, RsaData *plain)
{
    size_t plainLen = 0;
    int32_t totalPlainLen = 0;

    if ((rsaLen <= 0) || (cipher->length <= 0)) {
        return ERROR_CODE_GENERAL;
    }

    unsigned char *buf = (unsigned char*)malloc(rsaLen);
    if (buf == NULL) {
        return ERROR_CODE_GENERAL;
    }

    unsigned char *tembuf = (unsigned char*)malloc(cipher->length);
    if (tembuf == NULL) {
        free(buf);
        return ERROR_CODE_GENERAL;
    }

    (void)memset_s(tembuf, cipher->length, 0, cipher->length);
    mbedtls_ctr_drbg_context ctrDrbg;
    mbedtls_entropy_context entropy;
    RsaInit(&ctrDrbg, &entropy);
    size_t dataLen;
    if (mbedtls_base64_decode(tembuf, cipher->length, &dataLen, (const unsigned char *)cipher->data, cipher->length)) {
        goto ERROR;
    }
    int32_t count = dataLen / rsaLen;
    for (int32_t i = 0; i < count; i++) {
        memset_s(buf, rsaLen, 0, rsaLen);
        if (mbedtls_rsa_pkcs1_decrypt(rsa, mbedtls_ctr_drbg_random, &ctrDrbg,
            MBEDTLS_RSA_PRIVATE, &plainLen, tembuf + i * rsaLen, buf, rsaLen)) {
            goto ERROR;
        }
        if (memcpy_s(plain->data + totalPlainLen, plain->length - totalPlainLen, buf, plainLen)) {
            goto ERROR;
        }
        totalPlainLen += plainLen;
    }
    plain->length = totalPlainLen;
    RsaDeinit(&ctrDrbg, &entropy);
    free(tembuf);
    free(buf);
    return ERROR_SUCCESS;

ERROR:
    RsaDeinit(&ctrDrbg, &entropy);
    free(tembuf);
    free(buf);
    return ERROR_CODE_GENERAL;
}

static int32_t RsaDecrypt(RsaKeyData *key, RsaData *cipher, RsaData *plain)
{
    if ((key->trans != NULL) && (strcmp(key->trans, "RSA/None/OAEPWithSHA256AndMGF1Padding"))) {
        return ERROR_CODE_GENERAL;
    }

    if (plain->data == NULL) {
        plain->length = cipher->length;
        return ERROR_SUCCESS;
    }

    mbedtls_pk_context pk;
    mbedtls_pk_init(&pk);
    if (RsaLoadKey(MBEDTLS_RSA_PRIVATE, &pk, (const unsigned char *)key->key, key->keyLen) != 0) {
        mbedtls_pk_free(&pk);
        return ERROR_CODE_GENERAL;
    }

    mbedtls_rsa_context *rsa = mbedtls_pk_rsa(pk);
    size_t rsaLen = mbedtls_rsa_get_len(rsa);
    int32_t ret = RsaPkcs1Decrypt(rsa, rsaLen, cipher, plain);
    if (ret != ERROR_SUCCESS) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "Rsa pkcs1 decrypt failed.");
        mbedtls_pk_free(&pk);
        return ERROR_CODE_GENERAL;
    }

    mbedtls_pk_free(&pk);
    return ERROR_SUCCESS;
}

int32_t RsaCrypt(RsaKeyData *key, RsaData *inData, RsaData *outData)
{
    if (key == NULL || inData == NULL || outData == NULL) {
        return ERROR_CODE_GENERAL;
    }

    if ((key->action == NULL) || (key->key == NULL) || (inData->data == NULL)) {
        return ERROR_CODE_GENERAL;
    }

    if (!strcmp(key->action, "encrypt")) {
        return RsaEncrypt(key, inData, outData);
    } else if (!strcmp(key->action, "decrypt")) {
        return RsaDecrypt(key, inData, outData);
    } else {
        return ERROR_CODE_GENERAL;
    }
}