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
#include "aes_gcm.h"

#include <securec.h>

#include "hks_client.h"
#include "mbedtls/gcm.h"

#include "data_bus_error.h"
#include "os_adapter.h"

static mbedtls_gcm_context g_aesContext;

unsigned char* GenerateRandomIv(void)
{
    unsigned char *randomIv = malloc(IV_LEN);
    if (randomIv == NULL) {
        return NULL;
    }

    struct hks_blob blob = {HKS_BLOB_TYPE_IV, randomIv, IV_LEN};

    int ret = hks_generate_random(&blob);
    if (ret != 0) {
        SOFTBUS_PRINT("[TRANS] EncryptTransData hks_generate_random fail\n");
        free(randomIv);
        return NULL;
    }
    return randomIv;
}

int EncryptTransData(const AesGcmCipherKey *cipherkey, const unsigned char* plainText, unsigned int plainTextSize,
    unsigned char* cipherText, unsigned int cipherTextLen)
{
    if ((cipherkey == NULL) || (plainText == NULL) || (plainTextSize == 0) || cipherText == NULL ||
        (cipherTextLen < plainTextSize + OVERHEAD_LEN)) {
        SOFTBUS_PRINT("[TRANS] EncryptTransData invalid para\n");
        return -DBE_AES_CALC_ERROR;
    }

    int ret;
    unsigned char tagBuf[TAG_LEN] = {0};

    mbedtls_gcm_init(&g_aesContext);
    ret = mbedtls_gcm_setkey(&g_aesContext, MBEDTLS_CIPHER_ID_AES, cipherkey->key, cipherkey->keybits);
    if (ret != 0) {
        mbedtls_gcm_free(&g_aesContext);
        return -DBE_AES_CALC_ERROR;
    }

    ret = mbedtls_gcm_crypt_and_tag(&g_aesContext, MBEDTLS_GCM_ENCRYPT, plainTextSize, cipherkey->iv,
        IV_LEN, NULL, 0, plainText, cipherText + IV_LEN, TAG_LEN, tagBuf);
    if (ret != 0) {
        mbedtls_gcm_free(&g_aesContext);
        return -DBE_AES_CALC_ERROR;
    }

    if (memcpy_s(cipherText, IV_LEN, cipherkey->iv, IV_LEN) != 0) {
        mbedtls_gcm_free(&g_aesContext);
        return -DBE_AES_CALC_ERROR;
    }

    if (memcpy_s(cipherText + IV_LEN + plainTextSize, TAG_LEN, tagBuf, TAG_LEN) != 0) {
        mbedtls_gcm_free(&g_aesContext);
        return -DBE_AES_CALC_ERROR;
    }

    mbedtls_gcm_free(&g_aesContext);
    return (plainTextSize + OVERHEAD_LEN);
}

int DecryptTransData(const AesGcmCipherKey *cipherkey, const unsigned char* cipherText, unsigned int cipherTextSize,
    unsigned char* plain, unsigned int plainLen)
{
    if ((cipherkey == NULL) || (cipherText == NULL) || (cipherTextSize <= OVERHEAD_LEN) || plain == NULL ||
        (plainLen < cipherTextSize - OVERHEAD_LEN)) {
        SOFTBUS_PRINT("[TRANS] DecryptTransData invalid para\n");
        return -DBE_AES_CALC_ERROR;
    }

    mbedtls_gcm_init(&g_aesContext);
    int ret = mbedtls_gcm_setkey(&g_aesContext, MBEDTLS_CIPHER_ID_AES, cipherkey->key, cipherkey->keybits);
    if (ret != 0) {
        SOFTBUS_PRINT("[TRANS] DecryptTransData mbedtls_gcm_setkey fail\n");
        mbedtls_gcm_free(&g_aesContext);
        return -DBE_AES_CALC_ERROR;
    }

    int actualPlainLen = cipherTextSize - OVERHEAD_LEN;
    ret = mbedtls_gcm_auth_decrypt(&g_aesContext, cipherTextSize - OVERHEAD_LEN,
        cipherkey->iv, IV_LEN, NULL, 0, cipherText + actualPlainLen + IV_LEN, TAG_LEN, cipherText + IV_LEN, plain);
    if (ret != 0) {
        SOFTBUS_PRINT("[TRANS] DecryptTransData mbedtls_gcm_auth_decrypt fail\n");
        mbedtls_gcm_free(&g_aesContext);
        return -DBE_AES_CALC_ERROR;
    }

    mbedtls_gcm_free(&g_aesContext);
    return actualPlainLen;
}
