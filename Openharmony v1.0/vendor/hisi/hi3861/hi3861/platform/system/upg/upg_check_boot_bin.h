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

#ifndef __UPG_CHECK_BOOT_BIN_H__
#define __UPG_CHECK_BOOT_BIN_H__

#include <upg_common.h>
#include <brain_pool_p256r1.h>

#define RSA_4096_LENGTH 512
#define RSA_2048_LENGTH 256

#define SHA_256_LENGTH 32
#define ECC_32_BYTES   32
#define ECC_64_BYTES   64

#define BOOT_PREAMBLE   0x55AA55AA
#define BOOT_HEAD_MAGIC 0x33CC33CC
#define BOOT_TAIL_MAGIC 0x55AA55AA

#define DIE_ID_LENGTH 24

#define HI_HASH_ALG_SHA256 0
#define SUBKEY_ID_MAX      23
#define RSA_EXP_E_LENGTH   4
#define BOOT_VER_MAX       16

#define ROOTKEY_IV_BYTE_LENGTH 32
#define KEY_BYTE_LENGTH        32
#define CHECK_BYTE_LENGTH      32
#define KDF_ITERATION_CNT      1024

#define BOOT_MAX_LEN            0x13FC0 /* 80K - 0x40 */
#define BOOT_SECURE_MIN_LEN     0x01A0  /* 0x150(ecc header len) + 0x40(signature len) + 0x10(tail len) */
#define BOOT_NON_SECURE_MIN_LEN 0x0070  /* 0x40(sha256 header len) + 0x20(hash len) + 0x10(tail len) */
#define MAINTENANCE_KEY_TPYE    0x3C965AC3

#define NON_SECURE_FLAG   0x42
#define NON_ENCRYPT_FLAG  0x42
#define SUBKEY_RSIM_BYTES 0x3

static HI_CONST hi_u8 g_magic[IV_BYTE_LEN] = {
    0xE4, 0xEE, 0x10, 0x0E, 0x43, 0x4D, 0x94, 0x24,
    0xC7, 0x54, 0x6D, 0xFB, 0x15, 0xA1, 0x46, 0x97
};

typedef enum {
    SIGN_ALG_RSA_V15 = 0x00,
    SIGN_ALG_RSA_PSS = 0x01,
    SIGN_ALG_ECC = 0x10,
} sign_alg_type;

typedef struct {
    hi_u8 mod_n[RSA_4096_LENGTH];  /* Mod N */
    hi_u8 exp_e[RSA_EXP_E_LENGTH]; /* Exp E */
} root_rsa_pub_key;

typedef struct {
    hi_u32 version;                /* Default 1. */
    sign_alg_param sign_alg;       /* The signature algorithm. */
    hi_u32 category;               /* The category of SubKey, Used to distinguish different products or chips. */
    hi_u32 key_id;                 /* [4:0] SubKeyID, 0~31; [31:5] Reserved. */
    hi_u32 key_type;               /* 0x3C965AC3: Maintenance mode, should check die_id;
                                       other: normal mode, ignore die_id. */
    hi_u8 die_id[DIE_ID_LENGTH];   /* Die ID. 24Bytes */
    hi_u8 encrypt_flag;            /* 0x42: not encrypted; other: encryped. */
    hi_u8 boot_version;            /* boot version, range [0, 15] */
    hi_u8 pad[2];                  /* reserved 2 bytes. */
    hi_u8 boot_key[IV_BYTE_LEN];   /* part of key factor, 16 Bytes. */
    hi_u8 aes_iv[IV_BYTE_LEN];     /* AES-256 CBC mode, IV, 16 Bytes. */
    hi_u32 subkey_length;          /* Length of SubKey. RSA2048: 260 Bytes. */
    hi_u8 mod_n[RSA_2048_LENGTH];  /* Mod N */
    hi_u8 exp_e[RSA_EXP_E_LENGTH]; /* Exp E */
    hi_u8 sign[RSA_4096_LENGTH];   /* Signature of Subkey. */
} sub_rsa_key;

typedef struct {
    hi_u8 px[ECC_32_BYTES]; /* pubkey x */
    hi_u8 py[ECC_32_BYTES]; /* pubkey y */
} root_ecc_pub_key;

typedef struct {
    hi_u32 version;              /* Default 1. */
    sign_alg_param sign_alg;     /* The signature algorithm. */
    hi_u32 category;             /* The category of SubKey, Used to distinguish different products or chips. */
    hi_u32 key_id;               /* [4:0] SubKeyID, 0~31; [31:5] Reserved. */
    hi_u32 key_type;             /* 0x3C965AC3: Maintenance mode, should check die_id;
                                       other: normal mode, ignore die_id. */
    hi_u8 die_id[DIE_ID_LENGTH]; /* Die ID. 24Bytes */
    hi_u8 encrypt_flag;          /* 0x42: not encrypted; other: encryped. */
    hi_u8 boot_version;          /* boot version, range [0, 16] */
    hi_u8 pad[2];                /* reserved 2 bytes. */
    hi_u8 boot_key[IV_BYTE_LEN]; /* part of key factor, 16 Bytes. */
    hi_u8 aes_iv[IV_BYTE_LEN];   /* AES-256 CBC mode, IV, 16 Bytes. */
    hi_u32 subkey_length;        /* Length of SubKey. ECDSA256: 64 Bytes. */
    hi_u8 px[ECC_32_BYTES];      /* X */
    hi_u8 py[ECC_32_BYTES];      /* Y */
    hi_u8 r[ECC_32_BYTES];       /* Signature of Subkey. */
    hi_u8 s[ECC_32_BYTES];       /* Signature of Subkey. */
} sub_ecc_key;

typedef struct {
    hi_u32 version;              /* Default 1. */
    sign_alg_param sign_alg;     /* The signature algorithm. */
    hi_u32 category;             /* The category of SubKey, Used to distinguish different products or chips. */
    hi_u32 key_id;               /* [4:0] SubKeyID, 0~31; [31:5] Reserved. */
    hi_u32 key_type;             /* 0x3C965AC3: Maintenance mode, should check die_id;
                                       other: normal mode, ignore die_id. */
    hi_u8 die_id[DIE_ID_LENGTH]; /* Die ID. 24Bytes */
    hi_u8 encrypt_flag;          /* 0x42: not encrypted; other: encryped. */
    hi_u8 boot_version;          /* boot version, range [0, 16] */
    hi_u8 pad[2];                /* reserved 2 bytes. */
    hi_u8 boot_key[IV_BYTE_LEN]; /* part of key factor, 16 Bytes. */
    hi_u8 aes_iv[IV_BYTE_LEN];   /* AES-256 CBC mode, IV, 16 Bytes. */
    hi_u32 subkey_length;
} sub_key_common;

typedef struct {
    hi_u32 preamble;           /* Head information preamble code 0x55AA55AA, Validated at secure startup. */
    hi_u32 head_length;        /* Head information total length, sizeof(BOOT_HEADER_S). */
    hi_u32 root_pubk_alg;      /* RootPubK algorithm. 0: RSA_PKCS1; 1: RSA_PSS; 0x10: ECC; other: reserved. */
    hi_u32 root_pubk_offset;   /* Offset of RootPubK, based on Bootloader head. */
    hi_u32 root_pubk_length;   /* RootPubK length. , value is 1024, ECC, value is 64. */
    hi_u32 root_pubk_hash_alg; /* RootPubK HASH algorithm. 0: SHA256, other: reserved. */

    hi_u32 sub_key_offset; /* Offset of SubKeyCert, based on Bootloader head. */
    hi_u32 sub_key_length; /* Length of SubKeyCert. */

    hi_u32 code_section_offset; /* Offset of Bootloader Code Section. */
    hi_u32 code_section_length; /* Length of Bootloader Code Section. */

    sign_alg_param sign_alg; /* The signature algorithm. */

    hi_u32 sign_offset; /* Offset of Bootloader Code Section Signature. */
    hi_u32 sign_length; /* Length of Bootloader Code Section Signature. */

    hi_u32 head_magic; /* Head information over. Magic is 0x33CC33CC.
                                       BootROM should check HeadMagic & Preamble at first. */
} boot_header;

typedef struct {
    hi_u32 pad[2];     /* reserved 2 words. */
    hi_u32 boot_len;   /* flashboot len, include head,code,tail */
    hi_u32 tail_magic; /* tail magic:0x55AA55AA */
} boot_tail;

hi_u32 upg_check_boot_file(hi_u32 addr, hi_u32 len);

#endif /* __UPG_CHECK_BOOT_BIN_H__ */

