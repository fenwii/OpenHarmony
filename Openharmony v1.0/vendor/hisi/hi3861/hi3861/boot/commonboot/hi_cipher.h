/*
 * @file hi_cipher.h
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

/** @defgroup iot_cipher Cipher APIs
 * @ingroup iot_romboot
 */
#ifndef __HI_CIPHER_H__
#define __HI_CIPHER_H__

#include <hi_types.h>
#include <hi_boot_err.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif  /* __cplusplus */

#define PKE_LEN_32_BYTES             32
#define PKE_LEN_256_BYTES            256
#define PKE_LEN_384_BYTES            384
#define PKE_LEN_512_BYTES            512
#define RSA_KEY_LEN_2048             256
#define AES_MAX_KEY_IN_WORD          16
#define AES_IV_LEN_IN_WORD           4
#define KDF_KEY_LEN_IN_BYTES         32

/**
* @ingroup iot_cipher
* Rsa sign and veriry scheme
*/
typedef enum {
    HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256 = 0x00,   /* PKCS#1 RSASSA_PKCS1_V15_SHA256 signature */
    HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256,          /* PKCS#1 RSASSA_PKCS1_PSS_SHA256 signature */
    HI_CIPHER_RSA_SIGN_SCHEME_MAX,
    HI_CIPHER_RSA_SIGN_SCHEME_INVALID = 0xffffffff,
}hi_cipher_rsa_sign_scheme;

/**
* @ingroup iot_cipher
* Aes key from
*/
typedef enum {
    HI_CIPHER_AES_KEY_FROM_CPU = 0x00,
    HI_CIPHER_AES_KEY_FROM_KDF,
    HI_CIPHER_AES_KEY_FROM_MAX,
    HI_CIPHER_AES_KEY_FROM_INVALID = 0xffffffff,
}hi_cipher_aes_key_from;

/**
* @ingroup iot_cipher
* Aes work mode
*/
typedef enum {
    HI_CIPHER_AES_WORK_MODE_ECB = 0x00,    /* Electronic codebook (ECB) mode, ECB has been considered insecure and
                                               it is recommended not to use it. */
    HI_CIPHER_AES_WORK_MODE_CBC,            /* Cipher block chaining (CBC) mode. */
    HI_CIPHER_AES_WORK_MODE_CTR,            /* Counter (CTR) mode. */
    HI_CIPHER_AES_WORK_MODE_XTS,            /* XTS-AES (XTS) mode. */
    HI_CIPHER_AES_WORK_MODE_MAX,
    HI_CIPHER_AES_WORK_MODE_INVALID = 0xffffffff,
}hi_cipher_aes_work_mode;

/**
* @ingroup iot_cipher
* Aes key length
*/
typedef enum {
    HI_CIPHER_AES_KEY_LENGTH_128BIT  = 0x00,
    HI_CIPHER_AES_KEY_LENGTH_192BIT,
    HI_CIPHER_AES_KEY_LENGTH_256BIT,
    HI_CIPHER_AES_KEY_LENGTH_512BIT,             /* 512bit, just used for xts. */
    HI_CIPHER_AES_KEY_LENGTH_MAX,
    HI_CIPHER_AES_KEY_LENGTH_INVALID = 0xffffffff,
}hi_cipher_aes_key_length;

/**
* @ingroup iot_cipher
* Rsa public key verify
*/
typedef struct {
    hi_cipher_rsa_sign_scheme scheme;  /* The rsa sign type */
    hi_u8 *e;                          /* The public exponent */
    hi_u8 *n;                          /* The modulus */
    hi_u32 klen;                       /* The key length */
} hi_cipher_rsa_verify;

/**
* @ingroup iot_cipher
* Struct of ecc curves parameters
*/
typedef struct {
    const hi_u8 *p;   /* Finite field: equal to p in case of prime field curves or equal to 2^n in case of binary
                         field curves. */
    const hi_u8 *a;   /* Curve parameter a (q-3 in Suite B). */
    const hi_u8 *b;   /* Curve parameter b. */
    const hi_u8 *gx;  /* X coordinates of G which is a base point on the curve. */
    const hi_u8 *gy;  /* Y coordinates of G which is a base point on the curve. */
    const hi_u8 *n;   /* Prime which is the order of G point. */
    hi_u32 h;         /* Cofactor, which is the order of the elliptic curve divided by the order of the point G. For
                         the Suite B curves, h = 1. */
    hi_u32 ksize;     /* Ecc key size in bytes. It corresponds to the size in bytes of the prime, should be 32bytes. */
}hi_cipher_ecc_param;

/**
* @ingroup iot_cipher
* Struct of ecc verify
*/
typedef struct {
    const hi_u8 *px;   /* Ecdh X coordinates of the generated public key, the caller ensures it is padded with leading
                          zeros if the effective size of this key is smaller than ecc key size. */
    const hi_u8 *py;   /* Ecdh Y coordinates of the generated public key, the caller ensures it is padded with leading
                          zeros if the effective size of this key is smaller than ecc key size. */
    const hi_u8 *hash; /* Input hash data for ecc verify. */
    hi_u32 hash_len;   /* The length of hash data, just 32 bytes is valid data. */
    const hi_u8 *r;    /* Output ecc sign result R, its length is ecc key size. */
    const hi_u8 *s;    /* Output ecc sign result S, its length is ecc key size. */
    hi_u8 *out_r;      /* Output verify r data for security. */
}hi_cipher_ecc_verify;

/**
* @ingroup iot_cipher
* Struct of rsa verify
*/
typedef struct {
    hi_u8 *hash;        /* The input hash value will be changed after hi_cipher_rsa_verify_hash execution,
                           the correct value should be input before each verification */
    hi_u8 *out_hash;
    hi_u32 hash_len;
    const hi_u8 *sign;
    hi_u32 sign_len;
} hi_cipher_rsa_data;

/**
* @ingroup iot_cipher
* Aes ctrl struct
*/
typedef struct {
    hi_u32 key[AES_MAX_KEY_IN_WORD];     /* Key input. */
    hi_u32 iv[AES_IV_LEN_IN_WORD];       /* Initialization vector (IV). */
    hi_bool random_en;                   /* Enable random delay or not. */
    hi_cipher_aes_key_from key_from;     /* Key from, When using kdf key, no nead to configure the input key. */
    hi_cipher_aes_work_mode work_mode;   /* Work mode. */
    hi_cipher_aes_key_length key_len;    /* Key length. aes-ecb/cbc/ctr support 128/192/256 bits key, ccm just support
                                            128 bits key, xts just support 256/512 bits key. */
}hi_cipher_aes_ctrl;

/**
* @ingroup iot_cipher
* Kdf key type
*/
typedef enum {
    HI_CIPHER_SSS_KDF_KEY_DEVICE  = 0x0, /* kdf device key derivation. */
    HI_CIPHER_SSS_KDF_KEY_STORAGE,       /* kdf storage key derivation. */
    HI_CIPHER_SSS_KDF_KEY_MAX,
    HI_CIPHER_SSS_KDF_KEY_INVALID = 0xFFFFFFFF,
}hi_cipher_kdf_mode;

/**
* @ingroup iot_cipher
* Kdf ctrl struct
*/
typedef struct {
    const hi_u8 *salt;                   /* salt for kdf key derivation. */
    hi_u32 salt_len;                     /* salt_len should be 16 bytes for kdf device key derivation,
                                            32 bytes for kdf storage key derivation. */
    hi_u8 key[KDF_KEY_LEN_IN_BYTES];     /* just used for kdf device key. */
    hi_cipher_kdf_mode kdf_mode;         /* kdf mode for key derivation. */
    hi_u32 kdf_cnt;                      /**< kdf cnt for iteration.It is recommended that the number of iterations be
        not less than 10000 times, if performance requirement, no less than 1000
        times,  and not more than 0xffff times. */
    hi_u8 result[KDF_KEY_LEN_IN_BYTES];  /* output for kdf device key derivation. */
}hi_cipher_kdf_ctrl;

/**
* @ingroup        iot_cipher
* @brief          Initializes the Cipher module. CNcomment:Cipher 模块初始化。CNend
*
* @par 描述:
*                 Initializes the Cipher module.
CNcomment:Cipher模块初始化。CNend
*
* @attention      This function must be called before using cipher module.
CNcomment:使用Cipher模块算法前调用本接口初始化。CNend
* @param          None
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*                 @li hi_cipher.h：Describes Cipher module APIs.
CNcomment:文件用于描述Cipher模块相关接口。CNend
* @see            hi_cipher_init。
*/
hi_u32 hi_cipher_init(hi_void);

/**
* @ingroup        iot_cipher
* @brief          Deinitializes the Cipher module. CNcomment:Cipher 模块去初始化。CNend
*
* @par 描述:
*                 Deinitializes the Cipher module, does NOT support multi-tasks.
CNcomment:Cipher模块去初始化,不支持多任务。CNend
*
* @attention      This function could be called after using Cipher module finished.
CNcomment:结束使用Cipher模块算法后调用本接口去初始化。CNend
* @param          None
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*                 @li hi_cipher.h：Describes Cipher module APIs.
CNcomment:文件用于描述Cipher模块相关接口。CNend
* @see            hi_cipher_deinit。
*/
hi_u32 hi_cipher_deinit(hi_void);

/**
* @ingroup        iot_cipher
* @brief          Settings of AES. CNcomment:AES算法参数配置。CNend
*
* @par 描述:
*                 Configure of AES. CNcomment:AES算法参数配置。CNend
*
* @attention      None
* @param          ctrl        [IN]  type #hi_cipher_aes_ctrl *，AES parameters. CNcomment:AES算法参数配置。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*                 @li hi_cipher.h：Describes Cipher module APIs.
CNcomment:文件用于描述Cipher模块相关接口。CNend
* @see            hi_cipher_aes_config。
*/
hi_u32 hi_cipher_aes_config(hi_cipher_aes_ctrl *ctrl);

/**
* @ingroup        iot_cipher
* @brief          Encryption/Decryption of AES, if execution fails, hi_cipher_aes_destroy_config must be called to
release resources.
CNcomment:AES算法加解密，如果执行失败，必须调用hi_cipher_aes_destroy_config接口释放资源。CNend
*
* @par 描述:
*                 Encryption/Decryption of AES. CNcomment:AES算法加解密。CNend
*
* @attention      无。
* @param          src_addr    [IN]  type #uintptr_t，Input data source address.
CNcomment:待加密或解密的源数据物理地址，地址要求4对齐。CNend
* @param          dest_addr   [OUT] type #uintptr_t，output data physical address, the address must be
aligned in 4 bytes.
CNcomment:加密或解密结果数据物理地址，地址要求4对齐。CNend
* @param          length      [IN]  type #hi_u32，data length, ECB/CBC/CTR/XTS must be aligned in 16 bytes.
CNcomment:数据长度， ECB/CBC/CTR/XTS要求16bytes对齐。CNend
* @param          encrypt     [IN]  type #hi_bool，options of encryption/decryption, HI_TRUE is for encryption,
HI_FALSE is for decryption.CNcomment:加解密配置选项，配置HI_TRUE为加密，配置HI_FALSE为解密。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*                 @li hi_cipher.h：Describes Cipher module APIs.
CNcomment:文件用于描述Cipher模块相关接口。CNend
* @see            hi_cipher_aes_crypto。
*/
hi_u32 hi_cipher_aes_crypto(uintptr_t src_addr, uintptr_t dest_addr, hi_u32 length, hi_bool encrypt);

/**
* @ingroup        iot_cipher
* @brief          Destory AES configures. CNcomment:AES算法销毁配置的参数CNend
*
* @par 描述:
*                 Destory AES configures. CNcomment:AES算法销毁配置的参数CNend
*
* @attention      In pair with hi_cipher_aes_config.CNcomment:与参数配置成对使用CNend
* @param          None

* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*                 @li hi_cipher.h：Describes Cipher module APIs.
CNcomment:文件用于描述Cipher模块相关接口。CNend
* @see            hi_cipher_aes_destroy_config。
*/
hi_u32 hi_cipher_aes_destroy_config(hi_void);

/**
* @ingroup        iot_cipher
* @brief          Settings of HASH.CNcomment:HASH算法参数配置CNend
*
* @par 描述:
*                 Settings of HASH, this function should be called before calculating.
CNcomment:HASH算法参数配置，HASH计算前调用
*
* @attention      None
* @param  atts    [IN]        type #const hi_cipher_hash_atts *，HASH attribute.CNcomment:HASH算法类型配置。CNend

* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*                 @li hi_cipher.h：Describes Cipher module APIs.
CNcomment:文件用于描述Cipher模块相关接口。CNend
* @see            hi_cipher_hash_start。
*/
hi_u32 hi_cipher_hash_start(hi_void);

/**
* @ingroup        iot_cipher
* @brief          Calculating by HASH.CNcomment:HASH计算CNend
*
* @par 描述:
*                 Hash calculation. Multiple segments can be calculated，Maximum 10KB per segment.
CNcomment:HASH计算，支持多段计算，每段最长10KB。CNend
*
* @attention      None
* @param          src_addr    [IN]  type #uintptr_t，Data address to be calculated by HASH.
CNcomment:待HASH计算的数据地址。CNend
* @param          length      [IN]  type #hi_u32，Data length to be calculated by HASH，maximum is 10KB.
CNcomment:待HASH计算的数据长度,最长10KB。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*                 @li hi_cipher.h：Describes Cipher module APIs.
CNcomment:文件用于描述Cipher模块相关接口。CNend
* @see            hi_cipher_hash_update。
*/
hi_u32 hi_cipher_hash_update(uintptr_t src_addr, hi_u32 length);

/**
* @ingroup        iot_cipher
* @brief          HASH calculation finished.CNcomment:HASH计算结束CNend
*
* @par 描述:
*                 Ouput results after HASH finished calculating.CNcomment:HASH计算结束，
输出计算结果。CNend
*
* @attention      None
*
* @param          out          [OUT]  type #hi_u8 *，Pointer to the output of the HASH calculation result.
CNcomment:HASH计算结果输出指针。CNend
* @param          out_len      [IN]   type #hi_u32，HASH The output pointer of the calculation result points to
*                              the space length. The output length must be greater than or equal to 32 bytes.
CNcomment:HASH计算结果输出指针指向空间长度,要求输出长度满足不小于32bytes。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*                 @li hi_cipher.h：Describes Cipher module APIs.
CNcomment:文件用于描述Cipher模块相关接口。CNend
* @see            hi_cipher_hash_final。
*/
hi_u32 hi_cipher_hash_final(hi_u8 *out, hi_u32 out_len);

/**
* @ingroup        iot_cipher
* @brief          HASH calculation.CNcomment:HASH计算CNend
*
* @par 描述:
*                 Performs hash calculation on a segment of data and outputs the hash result.
CNcomment:对一段数据做HASH计算，并输出HASH结果。CNend
*
* @attention      None
*
* @param          input        [IN]  type #uintptr_t，Enter the data address. The address must be 4-bytes-aligned.
CNcomment:输入数据地址，地址要求4对齐。CNend
* @param          input_len    [IN]  type #hi_u32， Input data length.CNcomment:输入数据长度。CNend
* @param          hash         [OUT] type #hi_u8 *，Output the hash result. The length is 32 bytes.
CNcomment:输出HASH结果， 长度为 32 bytes。CNend
* @param          hash_len     [IN]  type #hi_u32， BUF length of the hash result. The value must be greater than or
*                              equal to 32 bytes.CNcomment:输出HASH结果的BUF长度，需要满足不小于32bytes。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*                 @li hi_cipher.h：Describes Cipher module APIs.
CNcomment:文件用于描述Cipher模块相关接口。CNend
* @see            hi_cipher_hash_sha256。
*/
hi_u32 hi_cipher_hash_sha256(uintptr_t input, hi_u32 input_len, hi_u8 *hash, hi_u32 hash_len);

/**
* @ingroup        iot_cipher
* @brief          KDF calculation.CNcomment:KDF算法计算。CNend
*
* @par 描述:
*                 KDF calculation.CNcomment:KDF算法计算。CNend
*
* @attention      None
* @param          ctrl        [IN] type  #hi_cipher_kdf_ctrl*，Poninter to KDF algorithm parameter configuration
                              control structure.CNcomment:KDF算法参数配置控制结构体。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*                 @li hi_cipher.h：Describes Cipher module APIs.
CNcomment:文件用于描述Cipher模块相关接口。CNend
* @see            hi_cipher_kdf_key_derive。
*/
hi_u32 hi_cipher_kdf_key_derive(hi_cipher_kdf_ctrl *ctrl);

/**
* @ingroup        iot_cipher
* @brief          Rsa Signature Verification.CNcomment:Rsa 签名结果校验CNend
*
* @par 描述:
*                 Rsa Signature Verification.CNcomment:Rsa 签名结果校验。CNend
*
* @attention      None
* @param          rsa_verify  [IN]   type #hi_cipher_rsa_verify *，Structure of the Rsa signature result
*                              verification algorithm.CNcomment:Rsa签名结果校验算法结构体。CNend
* @param          hash        [IN]   type #const hi_u8 *，Hash data to be checked.
CNcomment:待校验的HASH数据。CNend
* @param          hash_len    [IN]   type #hi_u32， Indicates the length of the hash data to be verified.
*                              The value is 32 bytes valid data.
CNcomment:待校验的HASH数据的长度，为32bytes有效数据。CNend
* @param          sign        [IN]   type #const hi_u8 *，Signature input pointer.CNcomment:签名输入指针。CNend
* @param          sign_len    [IN]   type #hi_u32，Length of the signature result. The length is the same as the
*                              length of the key.CNcomment:签名结果长度, 长度与key的长度相同。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*                 @li hi_cipher.h：Describes Cipher module APIs.
CNcomment:文件用于描述Cipher模块相关接口。CNend
* @see            hi_cipher_rsa_verify_hash。
*/
hi_u32 hi_cipher_rsa_verify_hash(const hi_cipher_rsa_verify *rsa_verify, hi_cipher_rsa_data *pack);

/**
* @ingroup        iot_cipher
* @brief          Ecdsa Signature Verification.CNcomment:Ecdsa 签名结果校验CNend
*
* @par 描述:
*                 Ecdsa Signature Verification.CNcomment:Ecdsa 签名结果校验。CNend
*
* @attention      None
* @param          ecc          [IN]   type #const hi_cipher_ecc_param *，ECC elliptic curve parameter. If the length
*                              is less than the size of the key, add 0 before the key.
CNcomment:ECC椭圆曲线参数，长度不足Key的大小，前面补0。CNend
* @param          verify       [IN]   type #const hi_cipher_ecc_verify *，Pointer to structure of the ECC public key
*                              verification parameter.CNcomment:ECC公钥验证参数结构体。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*                 @li hi_cipher.h：Describes Cipher module APIs.
CNcomment:文件用于描述Cipher模块相关接口。CNend
* @see            hi_cipher_ecc_sign_hash。
*/
hi_u32 hi_cipher_ecc_verify_hash(hi_cipher_ecc_param *ecc, hi_cipher_ecc_verify *verify);

/**
* @ingroup        iot_cipher
* @brief          TRNG Obtain a random number.CNcomment:TRNG获取随机数CNend
*
* @par 描述:
*                 TRNG Obtain a random number. Only one word size can be obtained at a time.
CNcomment:TRNG获取随机数，每次只能获取一个WORD大小的随机数。CNend
*
* @attention      None
* @param          randnum      [OUT]  type #hi_u32 *，Random number output pointer.
CNcomment:随机数输出指针。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*                 @li hi_cipher.h：Describes Cipher module APIs.
CNcomment:文件用于描述Cipher模块相关接口。CNend
* @see            hi_cipher_trng_get_random。
*/
hi_u32 hi_cipher_trng_get_random(hi_u32 *randnum);

/**
* @ingroup        iot_cipher
* @brief          TRNG Obtain a random number.CNcomment:TRNG获取随机数CNend
*
* @par 描述:
*                 The TRNG obtains the random number and obtains the random number of multiple bytes at a time.
CNcomment:TRNG获取随机数，每次获取多个byte的随机数。CNend
*
* @attention      None
* @param          randbyte     [OUT]  type #hi_u8 *，Random number output pointer.
CNcomment:随机数输出指针。CNend
* @param          size         [IN]   type #hi_u32，Length of the obtained random number.
CNcomment:获取的随机数长度。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*                 @li hi_cipher.h：Describes Cipher module APIs.
CNcomment:文件用于描述Cipher模块相关接口。CNend
* @see            hi_cipher_trng_get_random。
*/
hi_u32 hi_cipher_trng_get_random_bytes(hi_u8 *randbyte, hi_u32 size);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif  /* __cplusplus */

#endif /* __HI_CIPHER_H__ */
