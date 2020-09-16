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

#ifndef HKS_RKC_H
#define HKS_RKC_H

#include "hks_types.h"
#include "common/hks_utility.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* the state of root key component */
enum hks_rkc_state {
    HKS_RKC_STATE_INIT = 0,
    HKS_RKC_STATE_ON_INIT = 1,
    HKS_RKC_STATE_FAIL = 2,
    HKS_RKC_STATE_RUNNING = 3,
    HKS_RKC_STATE_ON_DEL = 4
};

/* the storage type of root key component */
enum hks_rkc_storage_type {
    /* file system */
    HKS_RKC_STORAGE_FILE_SYS = 0,
    /* flash */
    HKS_RKC_STORAGE_FLASH = 1
};

/* the keystore file number of root key component */
#define HKS_RKC_KSF_NUM 2
/* the keystore file number of root key component in hilink product */
#define HKS_RKC_KSF_NUM_HILINK 1

/* the max length of keystore filename */
#define HKS_RKC_KSF_NAME_LEN_MAX 256
/* the length of keystore buffer */
#define HKS_RKC_KSF_BUF_LEN 258

/* the length of keystore file flag */
#define HKS_RKC_KSF_FLAG_LEN 8

/* the source number of keystore file */
#define HKS_RKC_KSF_HASH_SRC_NUM 1

/* the material number of root key component */
#define HKS_RKC_MATERIAL_NUM 2

/* the hash source number of root key component material */
#define HKS_RKC_MATERIAL_HASH_SRC_NUM 4
#define HKS_RKC_MATERIAL_HASH_SRC_NUM_NO_E 3

/* the index of sequence number */
#define HKS_RKC_MATERIAL_HASH_SRC_SN 0
/* the index of random number #1 */
#define HKS_RKC_MATERIAL_HASH_SRC_R1 1
/* the index of random number #2 */
#define HKS_RKC_MATERIAL_HASH_SRC_R2 2
/* the index of external entropy */
#define HKS_RKC_MATERIAL_HASH_SRC_E 3

/* the index of material1 */
#define HKS_RKC_HASH_RESULT_MATERIAL1 0
/* the index of material2 */
#define HKS_RKC_HASH_RESULT_MATERIAL2 1

/* the sequence number of material1 */
#define HKS_RKC_MATERIAL1_SN 1
/* the sequence number of material2 */
#define HKS_RKC_MATERIAL2_SN 2

/* the material length of root key component */
#define HKS_RKC_MATERIAL_LEN 32

/* the raw key length of root key component */
#define HKS_RKC_RAW_KEY_LEN 64

/* the IV length of root key component */
#define HKS_RKC_IV_LEN 32

/* the salt length of root key component */
#define HKS_RKC_SALT_LEN 32

/* the hash value length of root key component */
#define HKS_RKC_HASH_LEN 32

/* the iterator number of times which derive Root Master Key */
#define HKS_RKC_RMK_ITER 1
#define HKS_RKC_RMK_ITER_MAX 10000

/* the hash algorithm which derive Root Master Key */
#define HKS_RKC_RMK_HMAC_SHA256 1

/* the version of root key component */
#define HKS_RKC_VER 1

/* the length of root master key */
#define HKS_RKC_RMK_LEN 64

/* the encryption key length of root master key */
#define HKS_RKC_RMK_EK_LEN 32
/* the integrity key length of root master key */
#define HKS_RKC_RMK_IK_LEN 32

/* the HMAC flag of root master key */
#define HKS_RKC_RMK_HMAC_FLAG 1

/* the max length of external entropy */
#define HKS_RKC_ENTROPY_LEN_MAX 256

/* the reserve length of the system configuration */
#define HKS_RKC_CFG_RSV_LEN 32

/* the reserve length of the keystore file data */
#define HKS_RKC_KSF_DATA_RSV_LEN 8

/* the delete flag of the keystore file */
#define HKS_RKC_KSF_NO_DEL_FLAG 0
#define HKS_RKC_KSF_DEL_FLAG 1

/* the length of master key */
#define HKS_RKC_MK_LEN 32

/* the encrypt algorithm of master key */
#define HKS_RKC_MK_CRYPT_ALG_AES256_GCM 1
/* the cipher length of master key */
#define HKS_RKC_MK_CIPHERTEXT_LEN 48
/* the tag length of master key */
#define HKS_RKC_MK_TAG_LEN 16
/* the tag length of master key */
#define HKS_RKC_MK_IV_LEN 16
/* the additional data length of master key */
#define HKS_RKC_MK_ADD_DATA_LEN 8

/* the max length of salt for key-encrypting key */
#define HKS_RKC_KEK_SALT_LEN_MAX 32
/* the min length of salt for key-encrypting key */
#define HKS_RKC_KEK_SALT_LEN_MIN 8
/* the length of key-encrypting key */
#define HKS_RKC_KEK_LEN 32
/* the iterator number for key-encrypting key */
#define HKS_RKC_KEK_ITER 1

/* the crypt operation */
#define HKS_RKC_ENCRYPT 0
#define HKS_RKC_DECRYPT 1

/* the length of root key */
#define HKS_ROOT_KEY_LEN 32

/* the attribute of keystore file */
struct hks_rkc_ksf_attr {
    uint8_t num;
    char *name[HKS_RKC_KSF_NUM];
};

/* the initialization parameter of root key component */
struct hks_rkc_init_para {
    /* the version of root key component */
    uint16_t version;
    /* the storage type of root key component */
    uint8_t storage_type;
    /* the attribute of keystore file */
    struct hks_rkc_ksf_attr ksf_attr;
    /* the iterator number of times which derive Root Master Key */
    uint32_t rmk_iter;
    /* the hash algorithm which derive Root Master Key */
    uint32_t rmk_hash_alg;
    /* external entropy, optionally, it could be empty */
    uint8_t *entropy;
    /* the length external entropy */
    uint32_t entropy_len;
    /* the encrption algorithm of master key */
    uint32_t mk_encrypt_alg;
    /* the hash algorithm for key-encrypting key */
    uint32_t kek_hash_alg;
    /* the iterator number for key-encrypting key */
    uint32_t kek_iter;
};

/* master key */
struct hks_rkc_mk {
    /* whether master key is valid */
    uint8_t is_valid;
    /* the created time of master key */
    struct hks_time mk_created_time;
    /* the expired time of master key */
    struct hks_time mk_expired_time;
    /* the master key with mask */
    uint8_t mk_with_mask[HKS_RKC_MK_LEN];
};

/* the configuration of root key component */
struct hks_rkc_cfg {
    /* system state */
    uint8_t state;
    /* the version of root key component */
    uint16_t version;
    /* the storage type of root key component */
    uint8_t storage_type;
    /* the created time of rook key */
    struct hks_time rk_created_time;
    /* the expired time of rook key */
    struct hks_time rk_expired_time;
    /* the attribute of keystore file */
    struct hks_rkc_ksf_attr ksf_attr;
    /* the iterator number of times which derive Root Master Key */
    uint32_t rmk_iter;
    /* the hash algorithm which derive Root Master Key */
    uint32_t rmk_hash_alg;
    /* external entropy */
    uint8_t *entropy;
    /* the length external entropy */
    uint32_t entropy_len;
    /* the mask of master key */
    uint8_t mk_mask[HKS_RKC_MK_LEN];
    /* the encrption algorithm of master key */
    uint32_t mk_encrypt_alg;
    /* the hash algorithm for key-encrypting key */
    uint32_t kek_hash_alg;
    /* the iterator number for key-encrypting key */
    uint32_t kek_iter;
    /* reserve data, 32 byte */
    uint8_t reserve[HKS_RKC_CFG_RSV_LEN];
};

/* the keystore file data of root key component */
struct hks_rkc_ksf_data {
    /* version */
    uint16_t version;
    /* the created time of rook key */
    struct hks_time rk_created_time;
    /* the expired time of rook key */
    struct hks_time rk_expired_time;
    /* the first material of root key */
    uint8_t rk_material1[HKS_RKC_MATERIAL_LEN];
    /* the second material of root key */
    uint8_t rk_material2[HKS_RKC_MATERIAL_LEN];
    /* the iterator number of times which derive root master key */
    uint32_t rmk_iter;
    /* the salt which derive root master key */
    uint8_t rmk_salt[HKS_RKC_SALT_LEN];
    /* the hash algorithm which derive root master key */
    uint32_t rmk_hash_alg;
    /* mk_rsv data for root key, 32 byte */
    uint8_t rk_rsv[HKS_RKC_KSF_DATA_RSV_LEN];
    /* the created time of master key */
    struct hks_time mk_created_time;
    /* the expired time of master key */
    struct hks_time mk_expired_time;
    /* the encrption algorithm of master key */
    uint32_t mk_encrypt_alg;
    /* the IV of master key */
    uint8_t mk_iv[HKS_RKC_MK_IV_LEN];
    /* the ciphertext of master key */
    uint8_t mk_ciphertext[HKS_RKC_MK_CIPHERTEXT_LEN];
    /* mk_rsv data for master key, 32 byte */
    uint8_t mk_rsv[HKS_RKC_KSF_DATA_RSV_LEN];
};

/* the keystore file data size of root key component */
#define HKS_RKC_KSF_DATA_SIZE (sizeof(struct hks_rkc_ksf_data))

/* the root master key */
struct hks_rkc_rmk {
    /* the encryption key */
    uint8_t ek[HKS_RKC_RMK_EK_LEN];
    /* the integrity key */
    uint8_t ik[HKS_RKC_RMK_EK_LEN];
};

/*
 * root key component - initialize
 * parameter:
 *     init_para          - [in] - the system initialize parameter.
 *     is_key_info_exist  - [in] - is key info exist.
 * return value:
 *     success or error code
 */
int32_t hks_rkc_init(const struct hks_rkc_init_para *init_para,
    int32_t is_key_info_exist);

/*
 * root key component - destroy
 * parameter: none
 * return value: none
 */
void hks_rkc_destroy(void);

/*
 * root key component - clear memory
 * parameter: none
 * return value: none
 */
void hks_rkc_clear_mem(void);

/*
 * root key component - get the key-encrypting key
 * parameter:
 *     salt      - [in]  - salt,
 *     kek       - [out] - key-encrypting key,
 *                         it must be cleared by caller after use.
 * return value:
 *     success or error code
 */
int32_t hks_rkc_get_kek(const struct hks_blob *salt, struct hks_blob *kek);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HKS_RKC_H */
