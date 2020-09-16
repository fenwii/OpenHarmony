/*
 * @file hi_upg_file.h
 *
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

/**
 * @defgroup upg Upgrade
 * @ingroup system
*/

#ifndef __HI_UPG_FILE_H__
#define __HI_UPG_FILE_H__

#include <hi_types.h>

/**
 *
 * Initial vector length.CNcomment:初始向量长度。CNend
 */
#define IV_BYTE_LEN   16

/**
 *
 * RSA2048 parameter length.CNcomment:RSA2048参数长度。CNend
 */
#define RSA_2048_LEN  256

/**
 *
 * RSA2048 parameter E length.CNcomment:RSA2048参数E长度。CNend
 */
#define RSA_EXP_E_LEN 4

/**
 *
 * ECC parameter length.CNcomment:ECC参数长度。CNend
 */
#define ECC_32_BYTES  32

/**
 *
 * SHA256 hash length.CNcomment:SHA256哈希值长度。CNend
 */
#define SHA_256_LEN   32

/**
 * @ingroup upg
 *
 * Parameter of sign algorithm.CNcomment:签名算法参数。CNend
 */
typedef struct {
    hi_u32 hash_alg : 16; /**< HASH algorithm:0:SHA256.CNcomment:HASH算法。CNend */
    hi_u32 sign_alg : 6; /**< Sign algorithm:0:RSA-PKCS;1:RSA-PSS;0x10:ECDSA256;0x3F:SHA256.CNcomment:签名算法。CNend */
    hi_u32 sign_param : 10; /**< Sign parameter, default '0'.CNcomment:HASH算法。CNend */
} sign_alg_param;

typedef struct {
    hi_u8 mod_n[RSA_2048_LEN];  /**< Mod N.CNcomment:RSA参数N。CNend */
    hi_u8 exp_e[RSA_EXP_E_LEN]; /**< Exp E.CNcomment:RSA参数E。CNend */
    hi_u8 padding[28];          /**< Padding field:28.CNcomment:填充字段。CNend */
} upg_rsa_key;

typedef struct {
    hi_u8 sign[RSA_2048_LEN]; /**< RSA signature.CNcomment:RSA签名。CNend */
} upg_rsa_sign;

typedef struct {
    hi_u8 px[ECC_32_BYTES]; /**< Pubkey x.CNcomment:ECC密钥x。CNend */
    hi_u8 py[ECC_32_BYTES]; /**< Pubkey y.CNcomment:ECC密钥y。CNend */
    hi_u8 padding[224];     /**< Padding field:224. CNcomment:填充字段。CNend */
} upg_ecc_key;

typedef struct {
    hi_u8 r[ECC_32_BYTES]; /**< Signature of ECC.CNcomment:ECC签名信息r。CNend */
    hi_u8 s[ECC_32_BYTES]; /**< Signature of ECC.CNcomment:ECC签名信息s。CNend */
    hi_u8 padding[192];    /**< Padding field:192.CNcomment:填充字段。CNend */
} upg_ecc_sign;

typedef struct {
    hi_u8 padding[288]; /**< Padding field:288.CNcomment:填充字段。CNend */
} upg_sha256_key;

typedef struct {
    hi_u8 check_sum[SHA_256_LEN]; /**< Hash value of SHA256.CNcomment:SHA256算法哈希值。CNend */
    hi_u8 padding[224];           /**< Padding field:224.CNcomment:填充字段。CNend */
} upg_sha256_sign;

/**
 * @ingroup upg
 *
 * Parameters of user-defined fields.CNcomment:用户自定义字段。CNend
 */
typedef struct {
    hi_u8 reserved[32];    /**< 32:Reserved for user.CNcomment:用户自定义字段。CNend */
}hi_upg_user_info;

typedef struct {
    hi_u32 image_id;       /**< Identity of upgrade file Key Area.CNcomment:升级文件魔术字。CNend */
    hi_u32 struct_version; /**< The structure of upgrade file version.CNcomment:升级文件结构体版本号。CNend */
    hi_u32 section_offset; /**< Offset of upgrade Section.CNcomment:Section段偏移。CNend */
    hi_u32 section_len;    /**< Length of upgrade Section.CNcomment:Section段长度。CNend */
    hi_upg_user_info user_info; /**< Reserved for user.CNcomment:用户自定义字段。CNend */
    hi_u8 file_type;       /**< Upgrade file type:0xF0: kernel file; 0xE1: boot file.CNcomment:升级文件类型。CNend */
    hi_u8 file_version;    /**< File Version, for anti-rollback. [0, 16] for boot file and [0, 48] for kernel file.
                                CNcomment:升级文件结构体版本号。CNend */
    hi_u8 encrypt_flag;    /**< 0x42: Section Area is not encrypted; other: Section Area is encrypted.
                                CNcomment:Section段加密标志。CNend */
    hi_u8 file_attr;            /**< File Attributes.CNcomment:文件属性。CNend */
    hi_u32 file_len;            /**< Entire file length.CNcomment:升级文件长度。CNend */
    hi_u32 key_len;             /**< Length of Key(288Bytes).True length:RSA2048: 272 Bytes, ECDSA: 64Bytes.
                                     CNcomment:密钥长度。CNend */
    sign_alg_param param;       /**< Parma of the signature algorithm.CNcomment:签名算法参数。CNend */
    hi_u8 aes_key[IV_BYTE_LEN]; /**< Part of key factor.CNcomment:AES密钥。CNend */
    hi_u8 aes_iv[IV_BYTE_LEN];  /**< The IV (AES-256 CBC-mode) to encrypt Section.CNcomment:AES初始向量。CNend */
} hi_upg_common_head;

typedef struct {
    hi_u32 image_id;           /**< Identity of upgrade file Key Area.CNcomment:升级文件魔术字。CNend */
    hi_u32 struct_version;     /**< The structure of upgrade file Section Area.CNcomment:升级文件结构体版本号。CNend */
    sign_alg_param param;      /**< The signature algorithm.CNcomment:签名算法参数。CNend */
    hi_u8 section_count;       /**< The number of sections.CNcomment:Section段个数。CNend */
    hi_u8 reserved[27];        /**< 27 bytes reserved.CNcomment:保留字段。CNend */
    hi_u8 section0_compress;   /**< Whether section 0 is compressed.CNcomment:Section0是否压缩。CNend */
    hi_u8 pad0[3];             /**< 3 bytes padding.CNcomment:填充字段。CNend */
    hi_u32 section0_offset;    /**< Offset of Section0.CNcomment:Section0段偏移。CNend */
    hi_u32 section0_len;       /**< Length of Section0, aligned to 16 bytes.CNcomment:Section0段长度。CNend */
    hi_u8 section1_compress;   /**< Whether section 1 is compressed.CNcomment:Section1是否压缩Nend */
    hi_u8 pad1[3];             /**< 3 bytes padding.CNcomment:填充字段。CNend */
    hi_u32 section1_offset;    /**< Offset of Section1.CNcomment:Section1段偏移。CNend */
    hi_u32 section1_len;       /**< Length of Section1, aligned to 16 bytes.CNcomment:Section1段长度。CNend */
} hi_upg_section_head;

typedef struct {
    upg_rsa_key key;    /**< Key of rsa.CNcomment:RSA算法密钥。CNend */
    upg_rsa_sign sign;  /**< Sign of rsa.CNcomment:RSA算法签名。CNend */
} hi_upg_rsa_alg;

typedef struct {
    upg_ecc_key key;    /**< Key of ecc.CNcomment:ECC算法密钥。CNend */
    upg_ecc_sign sign;  /**< Sign of ecc.CNcomment:ECC算法签名。CNend */
} hi_upg_ecc_alg;

typedef struct {
    upg_sha256_key key;    /**< Padding field.CNcomment:填充字段。CNend */
    upg_sha256_sign sign;  /**< Hash of sha256.CNcomment:SHA256算法哈希值。CNend */
} hi_upg_sha256_alg;

typedef struct {
    union {
        upg_rsa_key rsa;    /**< Key of rsa.CNcomment:rsa密钥。CNend */
        upg_ecc_key ecc;    /**< Key of ecc.CNcomment:ecc密钥。CNend */
        upg_sha256_key sha; /**< Padding field.CNcomment:填充字段。CNend */
    } key;
}hi_upg_key;

typedef struct {
    union {
        upg_rsa_sign rsa; /**< Sign of rsa.CNcomment:rsa签名。CNend */
        upg_ecc_sign ecc; /**< Sign of ecc.CNcomment:ecc签名。CNend */
        upg_sha256_sign sha; /**< Hash of sha256.CNcomment:SHA256哈希。CNend */
    } sign;
}hi_upg_sign;

typedef struct {
    hi_upg_common_head common; /**< Common head of upg file.CNcomment:公共文件头。CNend */
    union {
        hi_upg_rsa_alg rsa; /**< Key and sign of RSA.CNcomment:RSA密钥及签名信息。CNend */
        hi_upg_ecc_alg ecc; /**< Key and sign of ECC.CNcomment:ECC密钥及签名信息。CNend */
        hi_upg_sha256_alg sha;/**< Key and sign of SHA256.CNcomment:SHA256密钥及签名信息。CNend */
    } sign_alg;
} hi_upg_head;

typedef struct {
    hi_upg_common_head common; /**< Common head of upg file.CNcomment:公共文件头。CNend */
    union {
        hi_upg_rsa_alg rsa; /**< Key and sign of RSA.CNcomment:RSA密钥及签名信息。CNend */
        hi_upg_ecc_alg ecc; /**< Key and sign of ECC.CNcomment:ECC密钥及签名信息。CNend */
        hi_upg_sha256_alg sha; /**< Key and sign of SHA256.CNcomment:SHA256密钥及签名信息。CNend */
    } sign_alg;
    hi_upg_section_head section; /**< Head of code section.CNcomment:Code段头信息。CNend */
    hi_upg_sign section_sign;  /**< Sign of code section.CNcomment:Code段签名信息。CNend */
} hi_upg_file_head;

#endif
