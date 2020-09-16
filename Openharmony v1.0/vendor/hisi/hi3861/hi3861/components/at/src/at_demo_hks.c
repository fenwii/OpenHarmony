/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
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

#ifdef CONFIG_TEE_HUKS_DEMO_SUPPORT

#include "stdio.h"
#include "stdlib.h"
#include <hi_at.h>
#include "hks_client.h"
#include "hks_types.h"
#include "hks_errno.h"
#include <hi_mem.h>
#include <hi_stdlib.h>
#include "hi_flash.h"
#include "hi3861_platform_base.h"
#include "hi_partition_table.h"
#include "hi_nv.h"
#include "hi_efuse.h"
#include "hi_time.h"
#include "hi_wifi_api.h"

#define FLASH_BASE_ADDR 0x400000

#define CERT_STORE_START_ADDR 0
#define CERT_TOTAL_LEN (1024*12)
#define MAX_CERT_KEY_CNT 100
#define CERT_KEY_START_FLAG 0xDEADBEEF

#define KEY_STORE_START_ADDR (1024 * 12)
#define KEY_LEN 512
#define MAX_KEY_CNT 8
#define KEY_DATA_MAX_LEN 380
#define KYY_PARAM_MAX_LEN 128
#define LEN_BYTE 4
#define CIPHER_PLAIN_LEN_MIN_DIFF 16

#define USR_DATA_START_ADDR (1024 * 16)
#define USR_DATA_LEN (1024 * 4)

hi_void app_hks_get_cert_bin_start_store_addr(hi_u32 *addr, hi_u32 *size)
{
    hi_u32 usr_partion_addr;
    hi_u32 usr_partion_size;
    hi_get_usr_partition_table(&usr_partion_addr, &usr_partion_size);

    *addr = usr_partion_addr + CERT_STORE_START_ADDR;
    *size = CERT_TOTAL_LEN;
}

hi_u32 get_cert_text_addr(hi_u32 start_addr, hi_u32 *len_array, hi_u32 cert_index)
{
    int before_total_len = 0;
    for (hi_u32 i = 0; i < cert_index; i++) {
        before_total_len += len_array[i];
    }

    return (start_addr + before_total_len);
}

hi_u32 app_hks_get_cert_store_addr(hi_u32 *addr, hi_u32 *size, hi_u32 cert_index)
{
    if (addr == HI_NULL || size == HI_NULL) {
        return HI_ERR_FAILURE;
    }
    hi_u32 usr_partion_addr;
    hi_u32 usr_partion_size;
    hi_get_usr_partition_table(&usr_partion_addr, &usr_partion_size);

    hi_u32 cert_key_start_addr = 0;
    hi_u32 cert_bin_max_len = 0;
    app_hks_get_cert_bin_start_store_addr(&cert_key_start_addr, &cert_bin_max_len);

    hi_u32 start_flag = *((hi_u32 *)(HI_FLASH_BASE + cert_key_start_addr));
    if (start_flag != CERT_KEY_START_FLAG) {
        hi_at_printf("invalid cert:0x%x\r\n", start_flag);
        return HI_ERR_FAILURE;
    }

    hi_u32 cert_key_cnt = *((hi_u32 *)(HI_FLASH_BASE + cert_key_start_addr + 0x4));
    if (cert_index >= cert_key_cnt || cert_key_cnt > MAX_CERT_KEY_CNT) {
        hi_at_printf("invalid cert index or cert_key_cnt\r\n");
        return HI_ERR_FAILURE;
    }

    hi_u32 *cert_len_array = (hi_u32 *)malloc(cert_key_cnt * sizeof(hi_u32));
    if (cert_len_array == HI_NULL) {
        return HI_ERR_FAILURE;
    }
    for (hi_u32 i = 0; i < cert_key_cnt; i++) {
        cert_len_array[i] =  *((hi_u32 *)(HI_FLASH_BASE + cert_key_start_addr + 0x8 + i * 0x4));
    }

    hi_u32 cert_key_plain_size = cert_len_array[cert_index];
    hi_u32 cert_key_plain_addr = get_cert_text_addr(cert_key_start_addr + 0x8 + cert_key_cnt * 0x4, 
        &cert_len_array[0], cert_index);
    if (cert_key_plain_addr + cert_key_plain_size > cert_key_start_addr + cert_bin_max_len) {
        hi_at_printf("cert size invalid:%d\r\n", cert_index);
        free(cert_len_array);
        return HI_ERR_FAILURE;
    }

    *addr = cert_key_plain_addr;
    *size = cert_key_plain_size;

    free(cert_len_array);
    return HI_ERR_SUCCESS;
}

hi_u32 app_hks_get_key_store_addr(hi_u32 *addr, hi_u32 *size, hi_u32 key_index)
{
    if (addr == HI_NULL || size == HI_NULL) {
        return HI_ERR_FAILURE;
    }
    hi_u32 usr_partion_addr;
    hi_u32 usr_partion_size;
    hi_get_usr_partition_table(&usr_partion_addr, &usr_partion_size);
    if (key_index >= MAX_KEY_CNT) {
        return HI_ERR_FAILURE;
    }

    *addr = usr_partion_addr + KEY_STORE_START_ADDR + key_index * KEY_LEN;
    *size = KEY_LEN;

    return HI_ERR_SUCCESS;
}

hi_u32 app_hks_get_usr_data_store_addr(hi_u32 *addr, hi_u32 *size)
{
    if (addr == HI_NULL || size == HI_NULL) {
        return HI_ERR_FAILURE;
    }

    hi_u32 usr_partion_addr;
    hi_u32 usr_partion_size;
    hi_get_usr_partition_table(&usr_partion_addr, &usr_partion_size);

    *addr = usr_partion_addr + USR_DATA_START_ADDR;
    *size = USR_DATA_LEN;

    return HI_ERR_SUCCESS;
}

#define ENC_PARAM_NONCE_LEN 16
#define ENC_PARAM_AAD_LEN 12

typedef struct encrypt_param_ {
    hi_u16 nonce_size;
    hi_u16 aad_size;
    hi_u8 nonce[ENC_PARAM_NONCE_LEN];
    hi_u8 aad[ENC_PARAM_AAD_LEN];
} encrypt_param;

hi_u32 hks_set_blob(hi_u8 type, hi_u32 size, hi_char *data, struct hks_blob *hks_blob_param)
{
    hi_u32 ret = HI_ERR_SUCCESS;

    hks_blob_param->type = type;
    hks_blob_param->size = size;

    if (hks_blob_param->data != HI_NULL) {
        /* free mem before malloc again */
        free(hks_blob_param->data);
        hks_blob_param->data = HI_NULL;
    }

    hks_blob_param->data = malloc(hks_blob_param->size + 1);
    if (hks_blob_param->data == HI_NULL) {
        printf("blob malloc fail\r\n");
        return HI_ERR_FAILURE;
    }

    if (data != HI_NULL && hks_blob_param->size != 0) {
        ret = memcpy_s(hks_blob_param->data, hks_blob_param->size, data, size);
        if (ret != HI_ERR_SUCCESS) {
            free(hks_blob_param->data);
            hks_blob_param->data = HI_NULL;
        }
    }

    return ret;
}

hi_void hks_get_key_data(hi_u32 flash_addr, struct hks_blob *blob_key_data)
{
    blob_key_data->type = HKS_BLOB_TYPE_ENCRYPTED_KEY;
    blob_key_data->data = (hi_u8*)(FLASH_BASE_ADDR + flash_addr + KYY_PARAM_MAX_LEN + LEN_BYTE);
    blob_key_data->size = *((hi_u32 *)(FLASH_BASE_ADDR + flash_addr + KYY_PARAM_MAX_LEN));
}

hi_u32 hks_get_enc_param(hi_u32 flash_addr, encrypt_param *enc_param, struct hks_crypt_param *hks_encry_param)
{
    hi_u32 ret;

    ret = hi_flash_read(flash_addr, sizeof(encrypt_param), (hi_u8 *)enc_param);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    hks_encry_param->nonce.data = enc_param->nonce;
    hks_encry_param->nonce.size = enc_param->nonce_size;
    hks_encry_param->aad.data = enc_param->aad;
    hks_encry_param->aad.size = enc_param->aad_size;

    return ret;
}

#define CONN_DATA_KEY_LEN 64
#define CONN_DATA_CIPHER_DATA_MAX_LEN 220
#define CONN_DATA_ENC_PARAM_NONCE_SIZE 13

typedef struct encrypt_data_ {
    hi_u32 cipher_data_size;
    hi_u8 cipher_data[CONN_DATA_CIPHER_DATA_MAX_LEN];
} encrypt_cipher_data;

hi_u32 hks_set_conn_key_param(hi_u32 key_usage, struct hks_key_param *key_param)
{
    key_param->key_type = HKS_KEY_TYPE_AES;
    key_param->key_len = HKS_MAX_KEY_LEN_128;
    key_param->key_usage = key_usage;
    key_param->key_pad = 1;
    key_param->key_mode = HKS_ALG_GCM;
    key_param->key_domain = 0;
    key_param->key_role = 0;

    key_param->key_auth_id.type = 0;
    key_param->key_auth_id.size = 0;

    if (key_param->key_auth_id.data != HI_NULL) {
        /* free mem before malloc again */
        free(key_param->key_auth_id.data);
        key_param->key_auth_id.data = HI_NULL;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 hks_encrypt_conn_para(struct hks_crypt_param *crypt_param_conn, struct hks_blob *plain_text,
    struct hks_blob *cipher_text)
{
    hi_u32 ret;

    hi_u32 key_save_partition_addr = 0;
    hi_u32 key_save_partition_size = 0;
    ret = app_hks_get_key_store_addr(&key_save_partition_addr, &key_save_partition_size, 0);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    /* get key param */
    struct hks_key_param key_param = {0};
    ret = hi_flash_read(key_save_partition_addr, sizeof(key_param), (hi_u8 *)&key_param);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    key_param.key_usage = HKS_KEY_USAGE_ENCRYPT;

    /* get key data */
    struct hks_blob key_data_blob = {0};
    hi_u32 key_size = 0;
    ret = hi_flash_read(key_save_partition_addr + KYY_PARAM_MAX_LEN, LEN_BYTE, (hi_u8 *)&key_size);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    hi_u8 key_data[KEY_DATA_MAX_LEN] = {0}; /* The data on the flash memory cannot be directly used here. */
    ret = hi_flash_read(key_save_partition_addr + KYY_PARAM_MAX_LEN + LEN_BYTE, key_size, &key_data[0]);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    key_data_blob.type = HKS_BLOB_TYPE_ENCRYPTED_KEY;
    key_data_blob.data = &key_data[0];
    key_data_blob.size = key_size;

    /* encrypt */
    ret = hks_symmetric_encrypt(&key_data_blob, &key_param, crypt_param_conn, plain_text, cipher_text);
    if (ret != HI_ERR_SUCCESS) {
        printf("hks_symmetric_encrypt ret = %d\n", ret);
        return ret;
    }

    return ret;
}

hi_void hks_create_conn_enc_param(encrypt_param *enc_param, struct hks_crypt_param *blob_enc_param)
{
    hi_char nonce_data[CONN_DATA_ENC_PARAM_NONCE_SIZE] = "1234";
    hi_char* aad_data = "a";
    memcpy_s(enc_param->nonce, sizeof(enc_param->nonce), nonce_data, sizeof(nonce_data));
    enc_param->nonce_size = sizeof(nonce_data);
    memcpy_s(enc_param->aad, sizeof(enc_param->aad), aad_data, strlen(aad_data));
    enc_param->aad_size = strlen(aad_data);
    blob_enc_param->nonce.data = enc_param->nonce;
    blob_enc_param->nonce.size = enc_param->nonce_size;
    blob_enc_param->aad.data = enc_param->aad;
    blob_enc_param->aad.size = enc_param->aad_size;
}


hi_void hks_get_conn_cipher_data(hi_u32 flash_addr, struct hks_blob *blob_cipher_data)
{
    hi_u32 cipher_data_size = *((hi_u32*)(FLASH_BASE_ADDR + flash_addr + sizeof(encrypt_param)));
    hi_u8 *cipher_data = (hi_u8*)(FLASH_BASE_ADDR + flash_addr + sizeof(encrypt_param) + LEN_BYTE);
    blob_cipher_data->data = cipher_data;
    blob_cipher_data->size = cipher_data_size;
}

hi_u32 app_hks_generate_conn_key(void)
{
    hi_u32 ret;
    hi_u8 *flash_write_buffer = HI_NULL;

    hi_u32 key_save_partition_addr = 0;
    hi_u32 key_save_partition_size = 0;
    struct hks_key_param conn_key_param = {0};
    struct hks_blob blob_key = {0};

    ret = app_hks_get_key_store_addr(&key_save_partition_addr, &key_save_partition_size, 0);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    /* set key param */
    ret = hks_set_conn_key_param(HKS_KEY_USAGE_ENCRYPT, &conn_key_param);
    if (ret != HI_ERR_SUCCESS) {
        printf("hks_set_key_param fail!\r\n");
        return ret;
    }

    /* set key blob */
    ret = hks_set_blob(HKS_BLOB_TYPE_BUFFER, CONN_DATA_KEY_LEN, "123", &blob_key);
    if (ret != HI_ERR_SUCCESS) {
        printf("hks_set_blob fail!\r\n");
        return ret;
    }

    /* generate key */
    ret = hks_generate_symmetric_key(&blob_key, &conn_key_param);
    if (ret != HI_ERR_SUCCESS) {
        free(blob_key.data);
        printf("hks_generate_symmetric_key ret = %d\n", ret);
        return ret;
    }

    /* save key param */
    ret = hi_flash_write(key_save_partition_addr, sizeof(conn_key_param), (const hi_u8*)&conn_key_param, HI_TRUE);
    if (ret != HI_ERR_SUCCESS) {
        free(blob_key.data);
        printf("save key param fail, ret:0x%x\r\n", ret);
        return ret;
    }

    /* save key data */
    flash_write_buffer = malloc(blob_key.size + sizeof(uint32_t));
    if (flash_write_buffer == HI_NULL) {
        free(blob_key.data);
        return HI_ERR_FAILURE;
    }

    ret = memcpy_s(flash_write_buffer, sizeof(uint32_t), &(blob_key.size), sizeof(uint32_t));
    ret |= memcpy_s(flash_write_buffer + sizeof(uint32_t), key_save_partition_size, blob_key.data, blob_key.size);
    ret |= hi_flash_write(key_save_partition_addr + KYY_PARAM_MAX_LEN, blob_key.size + sizeof(uint32_t),
        flash_write_buffer, HI_TRUE);
    free(flash_write_buffer);
    free(blob_key.data);

    if (ret != HI_ERR_SUCCESS) {
        printf("save key data fail, ret:0x%x\r\n", ret);
    }

    return ret;
}

hi_u32 app_hks_encrypt_conn_para(hi_wifi_assoc_request *req)
{
    hi_u32 ret;
    struct hks_crypt_param blob_crypt_param_conn = {0};
    struct hks_blob blob_plain_text = {0};
    struct hks_blob blob_cipher_text_with_tag = {0};

    hi_u32 encrpt_param_data_save_partition_addr = 0;
    hi_u32 encrpt_param_data_save_partition_size = 0;
    ret = app_hks_get_usr_data_store_addr(&encrpt_param_data_save_partition_addr,
        &encrpt_param_data_save_partition_size);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    /* get plain connect data */
    blob_plain_text.data = (hi_u8 *)req;
    blob_plain_text.size = sizeof(hi_wifi_assoc_request);

    /* create enc param */
    encrypt_param enc_param = {0};
    hks_create_conn_enc_param(&enc_param, &blob_crypt_param_conn);

    /* create cipher blob */
    ret = hks_set_blob(0, sizeof(hi_wifi_assoc_request) + CIPHER_PLAIN_LEN_MIN_DIFF, "1234",
        &blob_cipher_text_with_tag);
    if (ret != HI_ERR_SUCCESS) {
        printf("set_value_of_hks_blob fail!\r\n");
        return ret;
    }

    /* start encrypt */
    ret = hks_encrypt_conn_para(&blob_crypt_param_conn, &blob_plain_text, &blob_cipher_text_with_tag);
    if (ret != HI_ERR_SUCCESS) {
        free(blob_cipher_text_with_tag.data);
        printf("hks_encrypt conn para fail!\r\n");
        return HI_ERR_FAILURE;
    }

    if (blob_cipher_text_with_tag.size > (sizeof(encrypt_cipher_data) - sizeof(hi_u32))) {
        free(blob_cipher_text_with_tag.data);
        printf("cipher text too long\r\n");
        return HI_ERR_FAILURE;
    }

    /* save enc param and cipher conn data */
    ret = hi_flash_write(encrpt_param_data_save_partition_addr, sizeof(enc_param), (const hi_u8*)&enc_param, HI_TRUE);

    encrypt_cipher_data enc_data = {0};
    enc_data.cipher_data_size = blob_cipher_text_with_tag.size;
    ret |= memcpy_s(enc_data.cipher_data, sizeof(enc_data.cipher_data), blob_cipher_text_with_tag.data,
        blob_cipher_text_with_tag.size);
    ret |= hi_flash_write(encrpt_param_data_save_partition_addr + sizeof(encrypt_param),
        sizeof(hi_u32) + blob_cipher_text_with_tag.size, (const hi_u8*)&enc_data, HI_TRUE);

    free(blob_cipher_text_with_tag.data);

    return ret;
}

hi_u32 app_hks_decrypt_conn_param(hi_wifi_assoc_request *req)
{
    if (req == HI_NULL) {
        return HI_ERR_FAILURE;
    }

    hi_u32 ret;
    hi_u32 key_save_partition_addr = 0;
    hi_u32 key_save_partition_size = 0;
    ret = app_hks_get_key_store_addr(&key_save_partition_addr, &key_save_partition_size, 0);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    /* get key param */
    struct hks_key_param key_param = {0};
    ret = hi_flash_read(key_save_partition_addr, sizeof(key_param), (hi_u8 *)&key_param);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    key_param.key_usage = HKS_KEY_USAGE_DECRYPT;

    /* get key data */
    struct hks_blob key_data_blob = {0};
    hks_get_key_data(key_save_partition_addr, &key_data_blob);

    hi_u32 cipher_data_save_addr = 0;
    hi_u32 cipher_data_partition_size = 0;
    ret = app_hks_get_usr_data_store_addr(&cipher_data_save_addr, &cipher_data_partition_size);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    /* get enc param */
    encrypt_param enc_param = {0};
    struct hks_crypt_param hks_encry_param = {0};
    ret = hks_get_enc_param(cipher_data_save_addr, &enc_param, &hks_encry_param);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    /* get cipher data */
    struct hks_blob cipher_text_blob = {0};
    hks_get_conn_cipher_data(cipher_data_save_addr, &cipher_text_blob);

    /* start decrypt */
    struct hks_blob plain_text_blob = {0};
    plain_text_blob.size = cipher_text_blob.size - CIPHER_PLAIN_LEN_MIN_DIFF;
    plain_text_blob.data = (hi_u8 *)req;

    ret = hks_symmetric_decrypt(&key_data_blob, &key_param, &hks_encry_param, &plain_text_blob, &cipher_text_blob);
    if (ret != HI_ERR_SUCCESS) {
        printf("hks_symmetric_decrypt ret = %d\r\n", ret);
        return ret;
    }

    return ret;
}

#define CERT_KEY_LEN 64
#define CERT_ENC_PARAM_NONCE_SIZE 13

hi_u32 hks_set_cert_key_param(hi_u32 key_usage, struct hks_key_param *key_param)
{
    key_param->key_type = HKS_KEY_TYPE_AES;
    key_param->key_len = HKS_MAX_KEY_LEN_128;
    key_param->key_usage = key_usage;
    key_param->key_pad = 1;
    key_param->key_mode = HKS_ALG_GCM;
    key_param->key_domain = 0;
    key_param->key_role = 0;

    key_param->key_auth_id.type = 0;
    key_param->key_auth_id.size = 0;

    if (key_param->key_auth_id.data != HI_NULL) {
        free(key_param->key_auth_id.data);
        key_param->key_auth_id.data = HI_NULL;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 hks_encrypt_cert(struct hks_crypt_param *crypt_param_conn, struct hks_blob *plain_text,
    struct hks_blob *cipher_text)
{
    hi_u32 ret;

    hi_u32 key_save_partition_addr = 0;
    hi_u32 key_save_partition_size = 0;
    ret = app_hks_get_key_store_addr(&key_save_partition_addr, &key_save_partition_size, 1);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    /* get key param */
    struct hks_key_param key_param = {0};
    ret = hi_flash_read(key_save_partition_addr, sizeof(key_param), (hi_u8 *)&key_param);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    key_param.key_usage = HKS_KEY_USAGE_ENCRYPT;

    /* get key data */
    struct hks_blob key_data_blob = {0};
    hi_u32 key_size = 0;
    hi_flash_read(key_save_partition_addr + KYY_PARAM_MAX_LEN, LEN_BYTE, (hi_u8 *)&key_size);
    hi_u8 key_data[KEY_DATA_MAX_LEN] = {0};  /* 此处不能直接使用flash上数据 */
    ret = hi_flash_read(key_save_partition_addr + KYY_PARAM_MAX_LEN + LEN_BYTE, key_size, &key_data[0]);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    key_data_blob.type = HKS_BLOB_TYPE_ENCRYPTED_KEY;
    key_data_blob.data = &key_data[0];
    key_data_blob.size = key_size;

    /* encrypt */
    ret = hks_symmetric_encrypt(&key_data_blob, &key_param, crypt_param_conn, plain_text, cipher_text);
    if (ret != HI_ERR_SUCCESS) {
        hi_at_printf("hks_symmetric_encrypt ret = %d\n", ret);
        return ret;
    }

    return ret;
}

hi_void hks_create_cert_enc_param(encrypt_param *enc_param, struct hks_crypt_param *blob_enc_param)
{
    hi_char nonce_data[CONN_DATA_ENC_PARAM_NONCE_SIZE] = "1234";
    hi_char* aad_data = "a";
    memcpy_s(enc_param->nonce, sizeof(enc_param->nonce), nonce_data, sizeof(nonce_data));
    enc_param->nonce_size = sizeof(nonce_data);
    memcpy_s(enc_param->aad, sizeof(enc_param->aad), aad_data, strlen(aad_data));
    enc_param->aad_size = strlen(aad_data);
    blob_enc_param->nonce.data = enc_param->nonce;
    blob_enc_param->nonce.size = enc_param->nonce_size;
    blob_enc_param->aad.data = enc_param->aad;
    blob_enc_param->aad.size = enc_param->aad_size;
}

hi_void hks_get_cert_cipher_data(hi_u32 flash_addr, struct hks_blob *blob_cipher_data, hi_u32 cipher_data_size)
{
    hi_u8 *cipher_data = (hi_u8*)(FLASH_BASE_ADDR + flash_addr + sizeof(encrypt_param));
    blob_cipher_data->data = cipher_data;
    blob_cipher_data->size = cipher_data_size - sizeof(encrypt_param);
}

hi_u32 hks_encrypt_cert_get_cipher(struct hks_crypt_param *param, struct hks_blob *plain_blob,
    struct hks_blob *cipher_blob, hi_u32 cert_index)
{
    hi_u32 ret;
    /* create cipher blob */
    ret = hks_set_blob(0, plain_blob->size + CIPHER_PLAIN_LEN_MIN_DIFF, "1234", cipher_blob);
    if (ret != HI_ERR_SUCCESS) {
        hi_at_printf("cipher set blob fail:%d\r\n", cert_index);
        return ret;
    }

    /* start encrypt */
    ret = hks_encrypt_cert(param, plain_blob, cipher_blob);
    if (ret != HI_ERR_SUCCESS) {
        free(cipher_blob->data);
        cipher_blob->data = HI_NULL;
        hi_at_printf("encrypt cert fail:%d\r\n", cert_index);
        return ret;
    }

    return HI_ERR_SUCCESS;
}

hi_void free_ciphert_text_blob(struct hks_blob *blob_cipher_text_cert1, struct hks_blob *blob_cipher_text_cert2,
    struct hks_blob *blob_cipher_text_key3)
{
    if (blob_cipher_text_cert1->data != HI_NULL) {
        free(blob_cipher_text_cert1->data);
        blob_cipher_text_cert1->data = HI_NULL;
    }
    if (blob_cipher_text_cert2->data != HI_NULL) {
        free(blob_cipher_text_cert2->data);
        blob_cipher_text_cert2->data = HI_NULL;
    }
    if (blob_cipher_text_key3->data != HI_NULL) {
        free(blob_cipher_text_key3->data);
        blob_cipher_text_key3->data = HI_NULL;
    }
}

hi_u32 write_cert_text_to_flash(hi_u32 base_addr, encrypt_param *param, struct hks_blob *cipher_blob,
    hi_u32 *size_array, hi_u32 cert_index)
{
    hi_u32 ret = HI_ERR_SUCCESS;

    hi_u32 cert_write_addr = base_addr;
    if (cert_index != 0) {
        int before_total_len = 0;
        for (hi_u32 i = 0; i < cert_index; i++) {
            before_total_len += size_array[i];
        }
        cert_write_addr += before_total_len;
    }

    ret |= hi_flash_write(cert_write_addr, sizeof(encrypt_param), (const hi_u8 *)param, HI_TRUE);
    ret |= hi_flash_write(cert_write_addr + sizeof(encrypt_param), cipher_blob->size, cipher_blob->data, HI_TRUE);

    return ret;
}

hi_u32 hks_encrypt_init_plain_blob(struct hks_blob *plain1, struct hks_blob *plain2, struct hks_blob *plain3)
{
    hi_u32 ret;
    /* get plain cert store addr */
    hi_u32 cert1_partition_addr, cert1_partition_size, cert2_partition_addr, cert2_partition_size;
    hi_u32 key3_partition_addr, key3_partition_size;
    ret = app_hks_get_cert_store_addr(&cert1_partition_addr, &cert1_partition_size, 0x0);
    ret |= app_hks_get_cert_store_addr(&cert2_partition_addr, &cert2_partition_size, 0x1);
    ret |= app_hks_get_cert_store_addr(&key3_partition_addr, &key3_partition_size, 0x2);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    /* get plain cert */
    hi_u32 cert1_plain_addr = FLASH_BASE_ADDR + cert1_partition_addr;
    hi_u32 cert2_plain_addr = FLASH_BASE_ADDR + cert2_partition_addr;
    hi_u32 key3_plain_addr = FLASH_BASE_ADDR + key3_partition_addr;

    plain1->data = (hi_u8 *)cert1_plain_addr;
    plain1->size = cert1_partition_size;
    plain2->data = (hi_u8 *)cert2_plain_addr;
    plain2->size = cert2_partition_size;
    plain3->data = (hi_u8 *)key3_plain_addr;
    plain3->size = key3_partition_size;

    return HI_ERR_SUCCESS;
}

hi_u32 app_hks_generate_cert_key(void)
{
    hi_u32 ret;
    hi_u8 *flash_write_buffer = HI_NULL;

    struct hks_key_param conn_key_param = {0};
    struct hks_blob blob_key = {0};

    hi_u32 key_save_partition_addr = 0;
    hi_u32 key_save_partition_size = 0;
    ret = app_hks_get_key_store_addr(&key_save_partition_addr, &key_save_partition_size, 1);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    /* set key param */
    ret = hks_set_cert_key_param(HKS_KEY_USAGE_ENCRYPT, &conn_key_param);
    if (ret != HI_ERR_SUCCESS) {
        printf("hks_set_key_param fail!\r\n");
        return ret;
    }

    /* set key blob */
    ret = hks_set_blob(HKS_BLOB_TYPE_BUFFER, CERT_KEY_LEN, "123", &blob_key);
    if (ret != HI_ERR_SUCCESS) {
        printf("hks_set_blob fail!\r\n");
        return ret;
    }

    /* generate key */
    ret = hks_generate_symmetric_key(&blob_key, &conn_key_param);
    if (ret != HI_ERR_SUCCESS) {
        free(blob_key.data);
        printf("hks_generate_symmetric_key ret = %d\n", ret);
        return ret;
    }

    /* save key param */
    ret = hi_flash_write(key_save_partition_addr, sizeof(conn_key_param), (const hi_u8*)&conn_key_param, HI_TRUE);
    if (ret != HI_ERR_SUCCESS) {
        free(blob_key.data);
        printf("save key param fail, ret:0x%x\r\n", ret);
        return ret;
    }

    /* save key data */
    flash_write_buffer = malloc(blob_key.size + sizeof(uint32_t));
    if (flash_write_buffer == HI_NULL) {
        free(blob_key.data);
        return HI_ERR_FAILURE;
    }
    memcpy_s(flash_write_buffer, sizeof(uint32_t), &(blob_key.size), sizeof(uint32_t));
    memcpy_s(flash_write_buffer + sizeof(uint32_t), key_save_partition_size, blob_key.data, blob_key.size);
    ret = hi_flash_write(key_save_partition_addr + KYY_PARAM_MAX_LEN, blob_key.size + sizeof(uint32_t),
        flash_write_buffer, HI_TRUE);
    free(flash_write_buffer);
    free(blob_key.data);
    if (ret != HI_ERR_SUCCESS) {
        printf("save key data fail, ret:0x%x\r\n", ret);
    }

    return ret;
}

hi_u32 app_hks_encrypt_cert(hi_void)
{
    hi_u32 ret;

    struct hks_blob blob_plain1 = {0};
    struct hks_blob blob_plain2 = {0};
    struct hks_blob blob_plain3 = {0};
    ret = hks_encrypt_init_plain_blob(&blob_plain1, &blob_plain2, &blob_plain3);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    struct hks_blob blob_cipher1 = {0};
    struct hks_blob blob_cipher2 = {0};
    struct hks_blob blob_cipher3 = {0};

    /* create enc param */
    encrypt_param enc_param = {0};
    struct hks_crypt_param blob_crypt_param_cert = {0};
    hks_create_cert_enc_param(&enc_param, &blob_crypt_param_cert);

    /* start encrypt */
    ret = hks_encrypt_cert_get_cipher(&blob_crypt_param_cert, &blob_plain1, &blob_cipher1, 0x0);
    ret |= hks_encrypt_cert_get_cipher(&blob_crypt_param_cert, &blob_plain2, &blob_cipher2, 0x1);
    ret |= hks_encrypt_cert_get_cipher(&blob_crypt_param_cert, &blob_plain3, &blob_cipher3, 0x2);
    if (ret != HI_ERR_SUCCESS) {
        free_ciphert_text_blob(&blob_cipher1, &blob_cipher2, &blob_cipher3);
        return ret;
    }

    hi_u32 cipher_size_array[0x3] = {blob_cipher1.size, blob_cipher2.size, blob_cipher3.size};
    hi_u32 cipher_text_total_len = cipher_size_array[0x0] + cipher_size_array[0x1] + cipher_size_array[0x2];

    hi_u32 cipher_store_addr = 0;
    hi_u32 cipher_store_size = 0;
    app_hks_get_cert_bin_start_store_addr(&cipher_store_addr, &cipher_store_size);
    if (cipher_text_total_len > (cipher_store_size - 0x5 * sizeof(hi_u32))) {
        hi_at_printf("cipher total len bigger than:%d", cipher_store_size);
        free_ciphert_text_blob(&blob_cipher1, &blob_cipher2, &blob_cipher3);
        return HI_ERR_FAILURE;
    }

    /* overwrite cipher cert to plain cert */
    /* Write Header Structure.CNcomment:写入头结构 */
    hi_u32 cert_start_flag = CERT_KEY_START_FLAG;
    hi_u32 cert_total_cnt = 0x3;
    ret = hi_flash_write(cipher_store_addr, sizeof(hi_u32), (const hi_u8*)&cert_start_flag, HI_TRUE);
    ret = hi_flash_write(cipher_store_addr + sizeof(hi_u32), sizeof(hi_u32), (const hi_u8*)&cert_total_cnt, HI_TRUE);
    for (hi_u32 i = 0; i < cert_total_cnt; i++) {
        cipher_size_array[i] += sizeof(encrypt_param);
    }
    ret = hi_flash_write(cipher_store_addr + 0x2 * sizeof(hi_u32), 0x3 * sizeof(hi_u32),
        (const hi_u8*)&cipher_size_array, HI_TRUE);

    /* Writing the Ciphertext Certificate/Key Content.CNcomment:写入密文证书/秘钥内容 */
    hi_u32 cert_text_write_addr = cipher_store_addr + 0x5 * sizeof(hi_u32);
    /* write cert1 */
    ret = write_cert_text_to_flash(cert_text_write_addr, &enc_param, &blob_cipher1, &cipher_size_array[0], 0x0);
    /* write cert2 */
    ret |= write_cert_text_to_flash(cert_text_write_addr, &enc_param, &blob_cipher2, &cipher_size_array[0], 0x1);
    /* write cert3 */
    ret |= write_cert_text_to_flash(cert_text_write_addr, &enc_param, &blob_cipher3, &cipher_size_array[0], 0x2);

    free_ciphert_text_blob(&blob_cipher1, &blob_cipher2, &blob_cipher3);

    return ret;
}

hi_u32 app_hks_decrypt_cert(hi_u32 *plain_size, hi_u8 *plain_data)
{
    hi_u32 ret;

    if (plain_data == HI_NULL) {
        return HI_ERR_FAILURE;
    }

    hi_u32 key_save_partition_addr = 0;
    hi_u32 key_save_partition_size = 0;
    ret = app_hks_get_key_store_addr(&key_save_partition_addr, &key_save_partition_size, 1);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    /* get key param */
    struct hks_key_param key_param = {0};
    ret = hi_flash_read(key_save_partition_addr, sizeof(key_param), (hi_u8 *)&key_param);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    key_param.key_usage = HKS_KEY_USAGE_DECRYPT;

    /* get key data */
    struct hks_blob key_data_blob = {0};
    hks_get_key_data(key_save_partition_addr, &key_data_blob);

    /* get cipher text addr and size */
    /* The demo decrypts only the first certificate file.CNcomment:demo仅解密第1个证书文件 */
    hi_u32 cipher_data_save_addr = 0;
    hi_u32 cipher_data_size = 0;
    ret = app_hks_get_cert_store_addr(&cipher_data_save_addr, &cipher_data_size, 0);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    /* get enc param */
    encrypt_param enc_param = {0};
    struct hks_crypt_param hks_encry_param = {0};
    ret = hks_get_enc_param(cipher_data_save_addr, &enc_param, &hks_encry_param);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    /* get cipher data */
    struct hks_blob cipher_text_blob = {0};
    hks_get_cert_cipher_data(cipher_data_save_addr, &cipher_text_blob, cipher_data_size);

    /* start decrypt */
    struct hks_blob plain_text_blob = {0};
    plain_text_blob.size = cipher_text_blob.size - CIPHER_PLAIN_LEN_MIN_DIFF;
    if ((*plain_size) < plain_text_blob.size) {
        hi_at_printf("plain_size too small\r\n");
        return HI_ERR_FAILURE;
    }
    plain_text_blob.data = plain_data;

    ret = hks_symmetric_decrypt(&key_data_blob, &key_param, &hks_encry_param, &plain_text_blob, &cipher_text_blob);
    if (ret != HI_ERR_SUCCESS) {
        hi_at_printf("hks_symmetric_decrypt ret = %d\r\n", ret);
        return ret;
    }
    *plain_size = plain_text_blob.size;

    return HI_ERR_SUCCESS;
}

#endif
