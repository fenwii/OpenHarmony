/**
 * @file hks_client.h
 *
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved. \n
 * Description: Contains key generation, signature verify,
 * encryption and decryption, key derivation, key agreement, etc. \n
 * Author: Huawei \n
 * Create: 2019-06-19
 */

/**
 * @defgroup iot_hks
 * @ingroup hks
 */

#ifndef HKS_CLIENT_H
#define HKS_CLIENT_H

#include "hks_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @ingroup  iot_hks
* @brief Hks get sdk version.CNcomment:获取HKS sdk版本号。CNend
*
* @par 描述:
*           Hks get sdk version.CNcomment:获取HKS sdk版本号。CNend
*
* @attention None
* @param  sdk_version      [OUT] type #struct hks_blob *，get sdk version.CNcomment:HKS sdk版本号。CNend
*
* @retval None
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_get_sdk_version
*/
HKS_DLL_API_PUBLIC void hks_get_sdk_version(struct hks_blob *sdk_version);

/**
* @ingroup  iot_hks
* @brief Hks init.CNcomment:hks 初始化。CNend
*
* @par 描述:
*           Hks init.CNcomment:hks 初始化。CNend
*
* @attention None
* @param  None
*
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_init
*/
HKS_DLL_API_PUBLIC int32_t hks_init(void);

/**
* @ingroup  iot_hks
* @brief Hks destroy.CNcomment:销毁 hks。CNend
*
* @par 描述:
*           Hks destroy.CNcomment:销毁 hks。CNend
*
* @attention None
* @param  None
*
* @retval None
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_destroy
*/
HKS_DLL_API_PUBLIC void hks_destroy(void);

/**
* @ingroup  iot_hks
* @brief Refresh key info and root key info.CNcomment:刷新密钥信息和根密钥信息。CNend
*
* @par 描述:
*           Refresh key info and root key info.CNcomment:刷新密钥信息和根密钥信息。CNend
*
* @attention None
* @param  None
*
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_refresh_key_info
*/
HKS_DLL_API_PUBLIC int32_t hks_refresh_key_info(void);

/**
* @ingroup  iot_hks
* @brief Generate key Only ED25519 algorithm key pair generation is supported The number of local storage keys.
  CNcomment:生成密钥仅支持ED25519算法密钥对生成本地存储密钥。CNend
*
* @par 描述:
*           Generate key Only ED25519 algorithm key pair generation is supported The number of local storage keys
  (including generated ED25519 public-private key pairs imported ED25519 public keys) is limited to 16.
  CNcomment:生成密钥仅支持ED25519算法密钥对生成本地存储密钥
  （包括导入的ED25519公共密钥和私有ED25519生成的ED25519公共密钥对）的数量限制为16个。CNend
*
* @attention None
* @param  key_alias      [IN] type #const struct hks_blob *，key alias, constraint condition:key_alias->size <= 64.
  CNcomment:密钥别名，约束条件：key_alias-> size <= 64。CNend
* @param  key_param      [IN] type #const struct hks_key_param *，The parameter of the key which need to generate
  constraint condition: key_param cannot be NULL & key_param->key_type must be HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519.
  CNcomment:需要生成的密钥参数 约束条件：
  key_param不能为NULL ＆ key_param-> key_type必须为HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_generate_key
*/
HKS_DLL_API_PUBLIC int32_t hks_generate_key(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param);

/**
* @ingroup  iot_hks
* @brief Generate the X25519 algorithm key pair and return it to the caller. The generated key pair is not saved in HKS.
  CNcomment:生成X25519算法秘钥对并返回给调用者，生成的秘钥对不在hks保存。CNend
*
* @par 描述:
*           Generate the X25519 algorithm key pair and return it to the caller.
  The generated key pair is not saved in HKS.
  CNcomment:生成X25519算法秘钥对并返回给调用者，生成的秘钥对不在hks保存。CNend
*
* @attention None
* @param  key_param      [IN] type #const struct hks_key_param *，Used to specify related parameters that affect
  key generation, constraint condition: key_param.key_type must be HKS_KEY_TYPE_ECC_KEYPAIR_CURVE25519
  key_param.usage must be hks_alg_ecdh(HKS_ALG_SELECT_RAW).
  CNcomment:用于指定影响秘钥生成的相关参数, 约束条件：key_param.key_type必须为HKS_KEY_TYPE_ECC_KEYPAIR_CURVE25519
   key_param.usage必须为hks_alg_ecdh（HKS_ALG_SELECT_RAW）。CNend
* @param  pri_key        [OUT] type #struct hks_blob *，Used to save the generated private key
  CNcomment:用于保存生成的私钥。CNend
* @param  pub_key        [OUT] type #struct hks_blob *，Used to save the generated public key.
  CNcomment:用于保存生成的公钥。CNend
* @param
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_generate_asymmetric_key
*/
HKS_DLL_API_PUBLIC int32_t hks_generate_asymmetric_key(
    const struct hks_key_param *key_param, struct hks_blob *pri_key,
    struct hks_blob *pub_key);

/**
* @ingroup  iot_hks
* @brief Associate the ED25519 algorithm public key and the parameters of the public key with the alias and
  import it into HKS to save. CNcomment:将ED25519算法公钥以及公钥的参数与别名关联并导入到hks中保存。CNend
*
* @par 描述:
*           Associate the ED25519 algorithm public key and the parameters of the public key with the alias and
  import it into HKS to save. CNcomment:将ED25519算法公钥以及公钥的参数与别名关联并导入到hks中保存。CNend
*
* @attention None
* @param  key_alias      [IN] type #const struct hks_blob *，Alias to specify to save the ED25519 public key.
  CNcomment:用于指定保存ED25519公钥的别名。CNend
* @param  key_param      [IN] type #const struct hks_key_param *，The key parameters associated with
  the public key are saved to the HKS together with the public key, constraint condition: key_param.key_type must be
  HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519
  CNcomment:和公钥关联的秘钥参数，与公钥一起保存到hks中, 约束条件：key_param.key_type必须为
  HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519。CNend
* @param  key           [IN] type #const struct hks_blob *，Public key to be imported into hks.
  CNcomment:需要导入到hks中的公钥。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_import_public_key
*/
HKS_DLL_API_PUBLIC int32_t hks_import_public_key(
    const struct hks_blob *key_alias,
    const struct hks_key_param *key_param, const struct hks_blob *key);

/**
* @ingroup  iot_hks
* @brief Export the public key associated with the file name saved in the HKS system.
  CNcomment:导出保存在hks系统中与文件名关联的公钥。CNend
*
* @par 描述:
*           Export the public key associated with the file name saved in the HKS system.
  CNcomment:导出保存在hks系统中与文件名关联的公钥。CNend
*
* @attention None
* @param  key_alias    [IN] type #const struct hks_blob * Alias used to associate with the exported public key,
  constraint condition: key_alias->size <= 64.
  CNcomment:用于与导出公钥关联的别名, 约束条件：key_alias-> size <= 64。CNend
* @param  key          [OUT] type #struct hks_blob * Cache of hks public key.CNcomment:存放 hks公钥的缓存。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_export_public_key
*/
HKS_DLL_API_PUBLIC int32_t hks_export_public_key(
    const struct hks_blob *key_alias, struct hks_blob *key);

/**
* @ingroup  iot_hks
* @brief Delete the public key associated with the alias saved in the HKS system.
  CNcomment:删除保存在hks系统中与别名关联的公钥。CNend
*
* @par 描述:
*           Delete the public key associated with the alias saved in the HKS system.
  CNcomment:删除保存在hks系统中与别名关联的公钥。CNend
*
* @attention None
* @param  key_alias    [IN] type #const struct hks_blob * The alias associated with the delete key,
  constraint condition: key_alias->size <= 64.
  CNcomment:与删除秘钥关联的别名, 约束条件：key_alias-> size <= 64。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_delete_key
*/
HKS_DLL_API_PUBLIC int32_t hks_delete_key(const struct hks_blob *key_alias);

/**
* @ingroup  iot_hks
* @brief Export key attributes associated with aliases stored in the HKS system.
  CNcomment:导出保存在hks系统中与别名关联的秘钥属性。CNend
*
* @par 描述:
*           Export key attributes associated with aliases stored in the HKS system.
  CNcomment:导出保存在hks系统中与别名关联的秘钥属性。CNend
*
* @attention None
* @param  key_alias    [IN] type #const struct hks_blob * Alias used to associate with the exported public key,
  constraint condition: key_alias->size <= 64.
  CNcomment:用于与导出公钥关联的别名, 约束条件：key_alias-> size <= 64。CNend
* @param  key_param    [OUT] type #struct hks_key_param * Pointer to key attribute. CNcomment:存放秘钥属性的指针。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_get_key_param
*/
HKS_DLL_API_PUBLIC int32_t hks_get_key_param(const struct hks_blob *key_alias,
    struct hks_key_param *key_param);

/**
* @ingroup  iot_hks
* @brief Determine if there is a public or secret key pair associated with the alias in hks.
  CNcomment:判断hks中是否存在与别名关联的公钥或秘钥对。CNend
*
* @par 描述:
*           Determine if there is a public or secret key pair associated with the alias in hks.
  CNcomment:判断hks中是否存在与别名关联的公钥或秘钥对。CNend
*
* @attention None
* @param  key_alias    [IN] type #const struct hks_blob * The alias associated with the delete key,
  constraint condition: key_alias->size <= 64.
  CNcomment:与删除秘钥关联的别名, 约束条件：key_alias-> size <= 64。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_is_key_exist
*/
HKS_DLL_API_PUBLIC int32_t hks_is_key_exist(const struct hks_blob *key_alias);

/**
* @ingroup  iot_hks
* @brief Generate a secure random number, no longer than 1024 bytes. CNcomment:生成安全随机数,长度不超过1024字节。CNend
*
* @par 描述:
*           Generate a secure random number, no longer than 1024 bytes.
  CNcomment:生成安全随机数,长度不超过1024字节。CNend
*
* @attention None
* @param  random    [OUT] type #struct hks_blob * Used to save generated random numbers,
  random->size must be specified by the caller ,constraint condition: random->size <= 1024.
  CNcomment:用于保存生成的随机数, random-> size必须由调用方指定，约束条件：random-> size <= 1024。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_generate_random
*/
HKS_DLL_API_PUBLIC int32_t hks_generate_random(struct hks_blob *random);

/**
* @ingroup  iot_hks
* @brief Generate a data signature using the ED25519 private key associated with the alias in hks.
  CNcomment:使用hks中与别名关联的ED25519私钥生成数据签名。CNend
*
* @par 描述:
*           Generate a data signature using the ED25519 private key associated with the alias in hks.
  CNcomment:使用hks中与别名关联的ED25519私钥生成数据签名。CNend
*
* @attention None
* @param  key_alias    [IN] type #const struct hks_blob * Sign using alias of secret key,
  constraint condition: key_alias->size <= 64.
  CNcomment:签名使用秘钥的别名, 约束条件：key_alias-> size <= 64。CNend
* @param  key_param    [IN] type #const struct hks_key_param *，Attributes of the key associated with key_alias.
  CNcomment:与key_alias关联的秘钥的属性。CNend
* @param  hash         [IN]  type #const struct hks_blob *，Data to be signed. CNcomment:待签名的数据。CNend
* @param  signature    [OUT] type #struct hks_blob *，Output data signature, constraint condition:
  signature->size bigger & equal  64。
  CNcomment:输出的数据签名,约束条件：签名大小> = 64。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_asymmetric_sign
*/
HKS_DLL_API_PUBLIC int32_t hks_asymmetric_sign(
    const struct hks_blob *key_alias,
    const struct hks_key_param *key_param, const struct hks_blob *hash,
    struct hks_blob *signature);

/**
* @ingroup  iot_hks
* @brief Verify data signature using ED25519 public key. CNcomment:使用ED25519公钥验证数据签名。CNend
*
* @par 描述:
*           Verify data signature using ED25519 public key. CNcomment:使用ED25519公钥验证数据签名。CNend
*
* @attention None
* @param  key        [IN] type #const struct hks_blob * The alias or ED25519 public key associated with the ED25519 key.
  CNcomment:与ED25519秘钥关联的别名或ED25519公钥。CNend
* @param  key_param  [IN] type #const struct hks_key_param *，The attributes of the key associated with the key.
  CNcomment:与key关联的秘钥的属性。CNend
* @param  hash       [IN]  type #const struct hks_blob *，Signed data. CNcomment:签名的数据。CNend
* @param  signature  [IN]  type #const struct hks_blob *，Data signature,constraint condition:
  signature->size  bigger & equal  64。
  CNcomment:数据签名, 约束条件：签名大小> = 64。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_asymmetric_verify
*/
HKS_DLL_API_PUBLIC int32_t hks_asymmetric_verify(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_blob *hash,
    const struct hks_blob *signature);

/**
* @ingroup  iot_hks
* @brief Data encryption using AES-128-GCM algorithm. CNcomment:使用AES-128-GCM算法对数据加密。CNend
*
* @par 描述:
*           Data encryption using AES-128-GCM algorithm. CNcomment:使用AES-128-GCM算法对数据加密。CNend
*
* @attention None
* @param  key         [IN] type #const struct hks_blob *，The key used to encrypt the plaintext.
  CNcomment:用于加密明文的秘钥。CNend
* @param  key_param   [IN] type #const struct hks_key_param *，The attributes of the key associated with the key.
  constraint condition: key_param.key_type is HKS_KEY_TYPE_AES, key_param.key_len is 128 or 192 or 256;
  key_param.key_usage is HKS_KEY_USAGE_ENCRYPT, key_param.key_mode is HKS_ALG_GCM;
  key_param.key_pad is HKS_PADDING_NONE
  CNcomment:与key关联的秘钥的属性,约束条件：key_param.key_type为HKS_KEY_TYPE_AES，key_param.key_len为128或192或256；
  key_param.key_usage是HKS_KEY_USAGE_ENCRYPT，key_param.key_mode是HKS_ALG_GCM；
  key_param.key_pad为HKS_PADDING_NONE。CNend
* @param  crypt_param      [IN]  type #const struct hks_crypt_param *，Vectors and additional data used for encryption.
  CNcomment:加密使用的向量和附加数据。CNend
* @param  plain_text       [IN]  type #const struct hks_blob *，Data plaintext。CNcomment:数据明文。CNend
* @param  cipher_text_with_tag    [OUT]  type #struct hks_blob *，Data ciphertext CNcomment:数据密文。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_aead_encrypt
*/
HKS_DLL_API_PUBLIC int32_t hks_aead_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text,
    struct hks_blob *cipher_text_with_tag);

/**
* @ingroup  iot_hks
* @brief Decrypt ciphertext using AES-128-GCM algorithm. CNcomment:使用AES-128-GCM算法对密文解密。CNend
*
* @par 描述:
*           Decrypt ciphertext using AES-128-GCM algorithm. CNcomment:使用AES-128-GCM算法对密文解密。CNend
*
* @attention None
* @param  key         [IN] type #const struct hks_blob *，Secret key for decryption. CNcomment:用于解密的秘钥。CNend
* @param  key_param   [IN] type #const struct hks_key_param *，The attributes of the key associated with the key.
  constraint condition: key_param.key_type is HKS_KEY_TYPE_AES, key_param.key_len is 128 or 192 or 256;
  key_param.key_usage is HKS_KEY_USAGE_DECRYPT, key_param.key_mode is HKS_ALG_GCM;
  key_param.key_pad is HKS_PADDING_NONE;
  CNcomment:与key关联的秘钥的属性,约束条件：key_param.key_type为HKS_KEY_TYPE_AES，key_param.key_len为128或192或256；
   key_param.key_usage是HKS_KEY_USAGE_DECRYPT，key_param.key_mode是HKS_ALG_GCM；
   key_param.key_pad为HKS_PADDING_NONE。CNend
* @param  crypt_param      [IN]  type #const struct hks_crypt_param *，Vector and additional data used for decryption.
  CNcomment:解密使用的向量和附加数据。CNend
* @param  plain_text       [OUT]  type #struct hks_blob *，Data plaintext。CNcomment:数据明文。CNend
* @param  cipher_text_with_tag    [IN]  type #const struct hks_blob *，Data ciphertext CNcomment:数据密文。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_aead_decrypt
*/
HKS_DLL_API_PUBLIC int32_t hks_aead_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    struct hks_blob *plain_text,
    const struct hks_blob *cipher_text_with_tag);

/**
* @ingroup  iot_hks
* @brief Key negotiation using X25519 algorithm. CNcomment:使用X25519算法进行秘钥协商。CNend
*
* @par 描述:
*           Key negotiation using X25519 algorithm. CNcomment:使用X25519算法进行秘钥协商。CNend
*
* @attention None
* @param  agreed_key         [OUT] type #struct hks_blob *，Negotiation key calculated through X25519.
  CNcomment:通过X25519计算出来的协商秘钥。CNend
* @param  private_key_param  [IN]  type #const struct hks_key_param *，Local private key private_key attributes.
  constraint condition:private_key_param.key_type is HKS_KEY_TYPE_ECC_KEYPAIR_CURVE25519
  private_key_param.key_usage is HKS_KEY_USAGE_DERIVE
  private_key_param.key_mode is the same as agreement_alg
  CNcomment:本端私钥private_key的属性,约束条件：private_key_param.key_type为HKS_KEY_TYPE_ECC_KEYPAIR_CURVE25519
   private_key_param.key_usage是HKS_KEY_USAGE_DERIVE
   private_key_param.key_mode与Agreement_alg相同。CNend
* @param  agreement_alg      [IN]  type #const uint32_t，
  Algorithm for further deriving secret key based on negotiation secret key.
  CNcomment:基于协商秘钥进一步派生秘钥的算法。CNend
* @param  private_key        [IN]  type #const struct hks_blob *，Local X25519 private key。
  CNcomment:本端X25519私钥。CNend
* @param  peer_public_key    [IN]  type #const struct hks_blob *，Peer X25519 public key
  CNcomment:对端X25519公钥。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_key_agreement
*/
HKS_DLL_API_PUBLIC int32_t hks_key_agreement(struct hks_blob *agreed_key,
    const struct hks_key_param *private_key_param,
    const uint32_t agreement_alg, const struct hks_blob *private_key,
    const struct hks_blob *peer_public_key);

/**
* @ingroup  iot_hks
* @brief Key derivation. CNcomment:秘钥派生。CNend
*
* @par 描述:
*           Derive the key using HKD512 algorithm based on SHA512.
  The currently derived key is only used for AES encryption and decryption.
  CNcomment:使用基于SHA512的HKDF算法派生秘钥，当前派生的秘钥仅用于AES加解密。CNend
*
* @attention None
* @param  derived_key   [OUT] type #struct hks_blob *，Derived key calculated through HKDF ，
  derived_key and data cannot be null, and size >= 16.
  CNcomment:通过HKDF计算出来的派生秘钥 named_key和data不能为null，且大小> = 16。CNend
* @param  key_param     [IN]  type #const struct hks_key_param *，Properties for derived keys constraint condition:
  key_param.key_type is HKS_KEY_TYPE_DERIVE，key_param.key_usage is HKS_KEY_USAGE_DERIVE
  key_param.key_mode is hks_alg_hkdf(HKS_ALG_HASH_SHA_256) or hks_alg_hkdf(HKS_ALG_HASH_SHA_512)
  key_param.key_len is 128 or 256.
  CNcomment:派生秘钥对应的属性，约束条件：
   key_param.key_type为HKS_KEY_TYPE_DERIVE，key_param.key_usage为HKS_KEY_USAGE_DERIVE
   key_param.key_mode为hks_alg_hkdf（HKS_ALG_HASH_SHA_256）或hks_alg_hkdf（HKS_ALG_HASH_SHA_512）
   key_param.key_len是128或256。。CNend
* @param  kdf_key       [IN]  type #const struct hks_blob *，The base key used to derive the key.
  CNcomment:用于派生秘钥的基础秘钥。CNend
* @param  salt          [IN]  type #const struct hks_blob *，
  Derived salt value,salt.size must be greater than or equal to 16。
  CNcomment:派生使用的盐值,salt.size必须大于或等于16。CNend
* @param  label         [IN]  type #const struct hks_blob *，Derived label，constraint condition:
  lable.size must be greater than or equal to 16
  CNcomment:派生使用的label，约束条件：lable.size必须大于或等于16。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_key_derivation
*/
HKS_DLL_API_PUBLIC int32_t hks_key_derivation(struct hks_blob *derived_key,
    const struct hks_key_param *key_param, const struct hks_blob *kdf_key,
    const struct hks_blob *salt, const struct hks_blob *label);

/**
* @ingroup  iot_hks
* @brief Generate message authentication code (MAC) based on SHA256 or SHA512.
  CNcomment:基于SHA256或SHA512生成消息验证码(MAC)。CNend
*
* @par 描述:
*           Generate message authentication code (MAC) based on SHA256 or SHA512.
  CNcomment:基于SHA256或SHA512生成消息验证码(MAC)。CNend
*
* @attention None
* @param  key         [IN]  type #const struct hks_blob *，Keys involved in calculating HMAC,
  data cannot be null,and size > 0.
  CNcomment:参与计算HMAC的秘钥,数据不能为null，大小> 0。CNend
* @param  alg         [IN]  type #const uint32_t，HMAC algorithm hks_alg_hmac(HKS_ALG_HASH_SHA_256) or
  (HKS_ALG_HASH_SHA_512).
  CNcomment:HMAC算法, hks_alg_hmac（HKS_ALG_HASH_SHA_256）或 （HKS_ALG_HASH_SHA_512）。CNend
* @param  src_data    [IN]  type #const struct hks_blob *，src data data cannot be null, and size > 0.
  CNcomment:源数据，数据不能为null，大小> 0。CNend
* @param  output      [OUT]  type #struct hks_blob *，Generated message verification code,
  output and output->data cannot be null constraint condition:
  when alg is hks_alg_hmac(HKS_ALG_HASH_SHA_256), output->size must be greater than or
  equal to 32 when alg is hks_alg_hmac(HKS_ALG_HASH_SHA_512), output->size must be greater than or equal to 64
  CNcomment:生成的消息验证码,输出和输出->数据不能为空约束条件：
   当alg为hks_alg_hmac（HKS_ALG_HASH_SHA_256）时，output-> size必须大于或
   当alg为hks_alg_hmac（HKS_ALG_HASH_SHA_512）时等于32，则output-> size必须大于或等于64。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_hmac
*/
HKS_DLL_API_PUBLIC int32_t hks_hmac(const struct hks_blob *key,
    const uint32_t alg, const struct hks_blob *src_data,
    struct hks_blob *output);

/**
* @ingroup  iot_hks
* @brief Calculate the hash value of the data based on SHA256 or SHA512.
  CNcomment:基于SHA256或SHA512计算数据的散列值。CNend
*
* @par 描述:
*           Calculate the hash value of the data based on SHA256 or SHA512.
  CNcomment:基于SHA256或SHA512计算数据的散列值。CNend
*
* @attention None
* @param  alg         [IN]  type #const uint32_t，Hash algorithm, Only spuuort SHA256/SHA512.
  CNcomment:哈希算法，仅支持SHA256 / SHA512。CNend
* @param  src_data    [IN]  type #const struct hks_blob *，src data data cannot be null, and size > 0.
  CNcomment:源数据，数据不能为null，大小> 0。CNend
* @param  hash        [OUT]  type #struct hks_blob *，Generated message verification code ,
  hash and hash->data cannot be null constraint condition:
  when alg is HKS_ALG_HASH_SHA_256, hash->size must be greater than or equal to 32 when alg is HKS_ALG_HASH_SHA_512,
  hash->size must be greater than or equal to 64.
  CNcomment:生成的消息验证码,hash和hash-> data不能为null约束条件：当alg为HKS_ALG_HASH_SHA_256时，
  当alg为HKS_ALG_HASH_SHA_512时，hash-> size必须大于或等于32，hash-> size必须大于或等于64。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_hash
*/
HKS_DLL_API_PUBLIC int32_t hks_hash(const uint32_t alg,
    const struct hks_blob *src_data, struct hks_blob *hash);

/**
* @ingroup  iot_hks
* @brief Unsigned large integer modulo operation. CNcomment:无符号大整数模运算。CNend
*
* @par 描述:
*           Unsigned large integer modulo operation. CNcomment:无符号大整数模运算。CNend
*
* @attention None
* @param  x    [OUT] type #struct hks_blob *，Modular result,x and x->data cannot be null, x->size >= n.size.
  CNcomment:模运算结果,x和x-> data不能为null，x-> size> = n.size。CNend
* @param  a    [IN]  type #const struct hks_blob *，Base data data cannot be null, size > 0.
  CNcomment:底数, 数据不能为null，大小> 0。CNend
* @param  e    [IN]  type #const struct hks_blob *，data cannot be null, size > 0.
  CNcomment:幂, 数据不能为null，大小> 0。CNend
* @param  n    [IN]  type #const struct hks_blob *，Modulus, data cannot be null, size > 0.
  CNcomment:模数, 数据不能为null，大小> 0。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_bn_exp_mod
*/
HKS_DLL_API_PUBLIC int32_t hks_bn_exp_mod(struct hks_blob *x,
    const struct hks_blob *a, const struct hks_blob *e,
    const struct hks_blob *n);

/**
* @ingroup  iot_hks
* @brief Get public key alias list Interface. CNcomment:获取公钥别名列表接口。CNend
*
* @par 描述:
*           Get public key alias list Interface. CNcomment:获取公钥别名列表接口。CNend
*
* @attention None
* @param  key_alias_list    [OUT] type #struct hks_blob *，struct hks_blob array, alloc and free memory by the caller.
  CNcomment:用于存放别名,struct hks_blob数组，调用者分配和释放内存。CNend
* @param  list_count        [IN] type #uint32_t *，Indicates the number of available hks_blob_t caches,
  public key alias number, alloc and free memory by the caller.
  CNcomment:表示可用的hks_blob_t缓存数量,调用方的公钥别名号，分配和可用内存。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_get_pub_key_alias_list
*/
HKS_DLL_API_PUBLIC int32_t hks_get_pub_key_alias_list(
    struct hks_blob *key_alias_list, uint32_t *list_count);

/**
* @ingroup  iot_hks
* @brief generate symmetric key. CNcomment:生成对称密钥。CNend
*
* @par 描述:
*           generate symmetric key，Only AES-128/AES-192/AES-256 key generation is supported.
  CNcomment:生成对称密钥，仅支持AES-128 / AES-192 / AES-256密钥生成。CNend
*
* @attention None
* @param  output_key    [OUT] type #struct hks_blob *，Key obtained.CNcomment:获取的key。CNend
* @param  key_param     [IN] type #const struct hks_key_param *，Need to generate key parameters.
  CNcomment:需要生成key的参数。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_generate_symmetric_key
*/
HKS_DLL_API_PUBLIC int32_t hks_generate_symmetric_key(struct hks_blob *output_key,
    const struct hks_key_param *key_param);

/**
* @ingroup  iot_hks
* @brief AES encryption, requires the use of the AES symmetric key generated above as an input parameter,
  supports GCM CCM CBC mode, key length 128/192/256.
  CNcomment:AES加密，要求使用上述生成AES对称的密钥作为入参，支持GCM CCM CBC模式，key长度128/192/256。CNend
*
* @par 描述:
*           AES encryption, requires the use of the AES symmetric key generated above as an input parameter,
  supports GCM CCM CBC mode, key length 128/192/256.
  CNcomment:AES加密，要求使用上述生成AES对称的密钥作为入参，支持GCM CCM CBC模式，key长度128/192/256。CNend
*
* @attention None
* @param  key            [IN] type #const struct hks_blob *，The key required for encryption,
  the key to generate the AES symmetric key output as an input parameter.
  CNcomment:加密所需密钥，需要为生成AES对称密钥输出的key作为入参。CNend
* @param  key_param      [IN] type #const struct hks_key_param *，Encryption key parameters.
  CNcomment:加密密钥参数。CNend
* @param  crypt_param    [IN] type #const struct hks_crypt_param *，Encrypted information. CNcomment:加密信息。CNend
* @param  plain_text     [IN] type #const struct hks_blob *，plain_text.CNcomment:明文。CNend
* @param  cipher_text_with_tag     [OUT] type #struct hks_blob *，Encrypted ciphertext.CNcomment:加密后密文。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_symmetric_encrypt
*/
HKS_DLL_API_PUBLIC int32_t hks_symmetric_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text, struct hks_blob *cipher_text_with_tag);

/**
* @ingroup  iot_hks
* @brief AES decryption, requires the use of the above generated AES symmetric key as an input parameter,
  supports GCM CCM CBC mode, key length 128/192/256.
  CNcomment:AES解密，要求使用上述生成AES对称的密钥作为入参，支持GCM CCM CBC模式，key长度128/192/256。CNend
*
* @par 描述:
*           AES decryption, requires the use of the above generated AES symmetric key as an input parameter,
  supports GCM CCM CBC mode, key length 128/192/256.
  CNcomment:AES解密，要求使用上述生成AES对称的密钥作为入参，支持GCM CCM CBC模式，key长度128/192/256。CNend
*
* @attention None
* @param  key            [IN] type #const struct hks_blob *，The key required for decryption needs to be the
  input key for generating the AES symmetric key output.
  CNcomment:解密所需密钥，需要为生成AES对称密钥输出的key作为入参。CNend
* @param  key_param      [IN] type #const struct hks_key_param *，decrypt key parameters.
  CNcomment:解密密钥参数。CNend
* @param  crypt_param    [IN] type #const struct hks_crypt_param *，Decrypt information. CNcomment:解密信息。CNend
* @param  plain_text     [OUT] type #const struct hks_blob *，Plaintext after decryption.CNcomment:解密后明文。CNend
* @param  cipher_text_with_tag   [IN] type #struct hks_blob *，Ciphertext.CNcomment:密文。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_symmetric_encrypt
*/
HKS_DLL_API_PUBLIC int32_t hks_symmetric_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_crypt_param *crypt_param,
    struct hks_blob *plain_text, const struct hks_blob *cipher_text_with_tag);

/**
* @ingroup  iot_hks
* @brief get security capabilites. CNcomment:获得安全功能。CNend
*
* @par 描述:
*           Get device security attributes, output as a json string, you can get information such as the
  algorithm type supported by the device certificate.
  CNcomment:获取设备安全属性，输出为json串，可以获取设备证书支持的算法类型等信息。CNend
*
* @attention None
* @param  flag             [IN] type #uint32_t，Reserved field, no assignment is required.
  CNcomment:预留字段，当前不需要赋值。CNend
* @param  capabilities     [OUT] type #struct hks_blob *，Information obtained.CNcomment:获取到的信息。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_get_security_capabilites
*/
HKS_DLL_API_PUBLIC int32_t hks_get_security_capabilites(uint32_t flag, struct hks_blob *capabilities);

/**
* @ingroup  iot_hks
* @brief export device certs. CNcomment:导出设备证书。CNend
*
* @par 描述:
*           export device certs. CNcomment:导出设备证书。CNend
*
* @attention None
* @param  key_id         [IN] type #uint8_t，Array index of device_identity field obtained with
  hks_get_security_capabilites.
  CNcomment:使用hks_get_security_capabilites获取的device_identity字段的数组下标。CNend
* @param  cert_chain     [OUT] type #hks_cert_chain *，Export certificate information.
  CNcomment:导出证书信息。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_export_device_certs
*/
HKS_DLL_API_PUBLIC int32_t hks_export_device_certs(uint8_t key_id, struct hks_cert_chain *cert_chain);

/**
* @ingroup  iot_hks
* @brief sign with device key. CNcomment:用设备私钥签名。CNend
*
* @par 描述:
*           sign with device key. CNcomment:用设备私钥签名。CNend
*
* @attention None
* @param  key_id       [IN] type #uint8_t，Array index of device_identity field obtained with
  hks_get_security_capabilites.
  CNcomment:使用hks_get_security_capabilites获取的device_identity字段的数组下标。CNend
* @param  usage        [IN] type #const struct hks_usage_spec *，Signing required parameters.
  CNcomment:签名所需参数。CNend
* @param  challenge    [IN] type #const struct hks_blob *，Data to be signed.
  CNcomment:待签名的数据。CNend
* @param  signature    [OUT] type #struct hks_blob *，Output data signature.
  CNcomment:输出的数据签名。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_sign_with_device_key
*/
HKS_DLL_API_PUBLIC int32_t hks_sign_with_device_key(uint8_t key_id,
    const struct hks_usage_spec *usage, const struct hks_blob *challenge, struct hks_blob *signature);


#ifdef __cplusplus
}
#endif

#endif /* HKS_CLIENT_H */
