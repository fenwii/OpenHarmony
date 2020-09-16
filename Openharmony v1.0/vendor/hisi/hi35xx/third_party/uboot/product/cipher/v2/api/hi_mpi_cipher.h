/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Description   : head file for mpi layout
 */

#ifndef __HI_CIPHER_H__
#define __HI_CIPHER_H__

#include "hi_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/* CIPHER set IV for first package */
#define HI_CIPHER_IV_CHG_ONE_PKG           1

/* CIPHER set IV for all package */
#define HI_CIPHER_IV_CHG_ALL_PKG           2

#define HI_CIPHER_MAX_IV_SIZE_IN_WORD       4
#define HI_CIPHER_MAX_KEY_SIZE_IN_WORD      8
#define HI_CIPHER_SM1_KEY_SIZE_IN_WORD      4
#define HI_CIPHER_SM4_KEY_SIZE_IN_WORD      4

/* enum typedef */
/* Cipher work mode. */
typedef enum {
    HI_CIPHER_WORK_MODE_ECB     = 0x0,  /* Electronic codebook (ECB) mode, ECB has been considered insecure and it is
                                           recommended not to use it. */
    HI_CIPHER_WORK_MODE_CBC,            /* Cipher block chaining (CBC) mode. */
    HI_CIPHER_WORK_MODE_CFB,            /* Cipher feedback (CFB) mode. */
    HI_CIPHER_WORK_MODE_OFB,            /* Output feedback (OFB) mode. */
    HI_CIPHER_WORK_MODE_CTR,            /* Counter (CTR) mode. */
    HI_CIPHER_WORK_MODE_CCM,            /* Counter (CCM) mode. */
    HI_CIPHER_WORK_MODE_GCM,            /* Counter (GCM) mode. */
    HI_CIPHER_WORK_MODE_CBC_CTS,        /* Cipher block chaining CipherStealing mode. */
    HI_CIPHER_WORK_MODE_BUTT,
    HI_CIPHER_WORK_MODE_INVALID = 0xffffffff,
} hi_cipher_work_mode;

/* Cipher algorithm. */
typedef enum {
    HI_CIPHER_ALG_AES           = 0x0,  /* Advanced encryption standard (AES) algorithm */
    HI_CIPHER_ALG_SM1           = 0x1,  /* SM1 algorithm. */
    HI_CIPHER_ALG_SM4           = 0x2,  /* SM4 algorithm. */
    HI_CIPHER_ALG_DMA           = 0x3,  /* DMA copy. */
    HI_CIPHER_ALG_BUTT          = 0x4,
    HI_CIPHER_ALG_INVALID       = 0xffffffff,
} hi_cipher_alg;

/* Key length. */
typedef enum {
    HI_CIPHER_KEY_DEFAULT       = 0x0,  /* Default key length, AES-16, SM1-48, SM4-16 */
    HI_CIPHER_KEY_AES_128BIT    = 0x0,  /* 128-bit key for the AES algorithm */
    HI_CIPHER_KEY_AES_192BIT    = 0x1,  /* 192-bit key for the AES algorithm */
    HI_CIPHER_KEY_AES_256BIT    = 0x2,  /* 256-bit key for the AES algorithm */
    HI_CIPHER_KEY_LEN_BUTT      = 0x3,
    HI_CIPHER_KEY_INVALID       = 0xffffffff,
} hi_cipher_key_len;

/* Cipher bit width. */
typedef enum {
    HI_CIPHER_BIT_WIDTH_128BIT  = 0x0,  /* 128-bit width */
    HI_CIPHER_BIT_WIDTH_64BIT   = 0x1,  /* 64-bit width */
    HI_CIPHER_BIT_WIDTH_8BIT    = 0x2,  /* 8-bit width */
    HI_CIPHER_BIT_WIDTH_1BIT    = 0x3,  /* 1-bit width */
    HI_CIPHER_BIT_WIDTH_BUTT    = 0x4,
    HI_CIPHER_BIT_WIDTH_INVALID = 0xffffffff,
} hi_cipher_bit_width;

/* Key ladder selecting parameters. */
typedef enum {
    HI_CIPHER_KEY_SRC_USER      = 0x0,  /* User Key. */
    HI_CIPHER_KEY_SRC_KLAD_1,           /* KLAD Key 1. */
    HI_CIPHER_KEY_SRC_KLAD_2,           /* KLAD Key 2. */
    HI_CIPHER_KEY_SRC_KLAD_3,           /* KLAD Key 3. */
    HI_CIPHER_KEY_SRC_BUTT,
    HI_CIPHER_KEY_SRC_INVALID   = 0xffffffff,
} hi_cipher_ca_type;

/* Klad target. */
typedef enum {
    HI_CIPHER_KLAD_TARGET_AES   = 0x0,  /* Klad for AES. */
    HI_CIPHER_KLAD_TARGET_RSA,          /* Klad for RSA. */
    HI_CIPHER_KLAD_TARGET_BUTT,
} hi_cipher_klad_target;

/* Encryption/Decryption type selecting. */
typedef enum {
    HI_CIPHER_TYPE_NORMAL       = 0x0,
    HI_CIPHER_TYPE_COPY_AVOID,
    HI_CIPHER_TYPE_BUTT,
    HI_CIPHER_TYPE_INVALID      = 0xffffffff,
} hi_cipher_type;

/* SM1 round config */
typedef enum {
    HI_CIPHER_SM1_ROUND_08      = 0x00, /* SM1 round 08. */
    HI_CIPHER_SM1_ROUND_10      = 0x01, /* SM1 round 10. */
    HI_CIPHER_SM1_ROUND_12      = 0x02, /* SM1 round 12. */
    HI_CIPHER_SM1_ROUND_14      = 0x03, /* SM1 round 14. */
    HI_CIPHER_SM1_ROUND_BUTT,
    HI_CIPHER_SM1_ROUND_INVALID = 0xffffffff,
} hi_cipher_sm1_round;

/* Hash algrithm type. */
typedef enum {
    HI_CIPHER_HASH_TYPE_SHA1,
    HI_CIPHER_HASH_TYPE_SHA224,
    HI_CIPHER_HASH_TYPE_SHA256,
    HI_CIPHER_HASH_TYPE_SHA384,
    HI_CIPHER_HASH_TYPE_SHA512,
    HI_CIPHER_HASH_TYPE_HMAC_SHA1,
    HI_CIPHER_HASH_TYPE_HMAC_SHA224,
    HI_CIPHER_HASH_TYPE_HMAC_SHA256,
    HI_CIPHER_HASH_TYPE_HMAC_SHA384,
    HI_CIPHER_HASH_TYPE_HMAC_SHA512,
    HI_CIPHER_HASH_TYPE_SM3,
    HI_CIPHER_HASH_TYPE_BUTT,
    HI_CIPHER_HASH_TYPE_INVALID = 0xffffffff,
} hi_cipher_hash_type;

/* Rsa encrypt and decrypt scheme. */
typedef enum {
    HI_CIPHER_RSA_ENCRYPT_SCHEME_NO_PADDING  = 0x00, /* without padding. */
    HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_0,       /* PKCS#1 block type 0 padding. */
    HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_1,       /* PKCS#1 block type 1padding. */
    HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_2,       /* PKCS#1 block type 2 padding. */
    HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA1,    /* PKCS#1 RSAES-OAEP-SHA1 padding. */
    HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA224,  /* PKCS#1 RSAES-OAEP-SHA224 padding. */
    HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA256,  /* PKCS#1 RSAES-OAEP-SHA256   padding. */
    HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA384,  /* PKCS#1 RSAES-OAEP-SHA384   padding. */
    HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA512,  /* PKCS#1 RSAES-OAEP-SHA512   padding. */
    HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_PKCS1_V1_5,   /* PKCS#1 RSAES-PKCS1_V1_5    padding. */
    HI_CIPHER_RSA_ENCRYPT_SCHEME_BUTT,
    HI_CIPHER_RSA_ENCRYPT_SCHEME_INVALID    = 0xffffffff,
} hi_cipher_rsa_encrypt_scheme;

/* Rsa sign and verify scheme. */
typedef enum {
    HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA1 = 0x100, /* PKCS#1 RSASSA_PKCS1_V15_SHA1 signature. */
    HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA224,       /* PKCS#1 RSASSA_PKCS1_V15_SHA224 signature. */
    HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256,       /* PKCS#1 RSASSA_PKCS1_V15_SHA256 signature. */
    HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA384,       /* PKCS#1 RSASSA_PKCS1_V15_SHA384 signature. */
    HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA512,       /* PKCS#1 RSASSA_PKCS1_V15_SHA512 signature. */
    HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA1,         /* PKCS#1 RSASSA_PKCS1_PSS_SHA1 signature. */
    HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA224,       /* PKCS#1 RSASSA_PKCS1_PSS_SHA224 signature. */
    HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256,       /* PKCS#1 RSASSA_PKCS1_PSS_SHA256 signature. */
    HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA384,       /* PKCS#1 RSASSA_PKCS1_PSS_SHA1 signature. */
    HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA512,       /* PKCS#1 RSASSA_PKCS1_PSS_SHA256 signature. */
    HI_CIPHER_RSA_SIGN_SCHEME_BUTT,
    HI_CIPHER_RSA_SIGN_SCHEME_INVALID               = 0xffffffff,
} hi_cipher_rsa_sign_scheme;

/* struct define. */
/* Cipher control parameters. */
typedef struct {
    /* Initial Vector change flag, 0-don't set, 1-set IV for first package, 2-set IV for each package.  */
    hi_u32 bits_iv      : 2;
    hi_u32 bits_resv    : 30;             /* Reserved. */
} hi_cipher_ctrl_chg_flag;

/* Structure of the cipher type */
typedef struct {
    hi_cipher_type cipher_type;
} hi_cipher_attr;

/* Structure of the cipher control information */
typedef struct {
    hi_u32 key[HI_CIPHER_MAX_KEY_SIZE_IN_WORD];   /* Key input */
    hi_u32 iv[HI_CIPHER_MAX_IV_SIZE_IN_WORD];     /* Initialization vector (IV) */
    hi_bool key_by_ca;                  /* Encryption using advanced conditional access (CA) or decryption using keys */
    hi_cipher_ca_type ca_type;          /* Select keyladder type when using advanced CA */
    hi_cipher_alg alg;                  /* Cipher algorithm */
    hi_cipher_bit_width bit_width;      /* Bit width for encryption or decryption */
    hi_cipher_work_mode work_mode;      /* Operating mode */
    hi_cipher_key_len key_len;          /* Key length */
    hi_cipher_ctrl_chg_flag chg_flags;  /* control information exchange choices, we default all woulde be change
                                                except they have been in the choices */
} hi_cipher_ctrl;

/* Structure of the cipher AES control information */
typedef struct {
    hi_u32 even_key[HI_CIPHER_MAX_KEY_SIZE_IN_WORD];   /* Key input, default use this key. */
    hi_u32 odd_key[HI_CIPHER_MAX_KEY_SIZE_IN_WORD];    /* Key input, only valid for Multi encrypt/decrypt. */
    hi_u32 iv[HI_CIPHER_MAX_IV_SIZE_IN_WORD];          /* Initialization vector (IV) */
    hi_cipher_bit_width bit_width;           /* Bit width for encryption or decryption */
    hi_cipher_key_len key_len;               /* Key length */
    hi_cipher_ctrl_chg_flag chg_flags;       /* control information exchange choices, we default all woulde be change
                                                except they have been in the choices */
} hi_cipher_ctrl_aes;

/* Structure of the cipher AES CCM/GCM control information */
typedef struct {
    hi_u32 key[HI_CIPHER_MAX_KEY_SIZE_IN_WORD];    /* Key input */
    hi_u32 iv[HI_CIPHER_MAX_IV_SIZE_IN_WORD];      /* Initialization vector (IV) */
    hi_cipher_key_len key_len;           /* Key length */
    hi_u32 iv_len;                       /* IV lenght for CCM/GCM, which is an element of {7, 8, 9, 10, 11, 12, 13}
                                            for CCM, and is an element of [1-16] for GCM. */
    hi_u32 tag_len;                      /* Tag lenght for CCM which is an element of {4, 6, 8, 10, 12, 14, 16}. */
    hi_u32 aad_len;                      /* Associated data for CCM and GCM. */
    hi_phys_addr_t aad_phys_addr;        /* Physical address of Associated data  for CCM and GCM. */
} hi_cipher_ctrl_aes_ccm_gcm;

/* Structure of the cipher SM1 control information */
typedef struct {
    hi_u32 ek[HI_CIPHER_SM1_KEY_SIZE_IN_WORD];         /* Key of EK input */
    hi_u32 ak[HI_CIPHER_SM1_KEY_SIZE_IN_WORD];         /* Key of AK input */
    hi_u32 sk[HI_CIPHER_SM1_KEY_SIZE_IN_WORD];         /* Key of SK input */
    hi_u32 iv[HI_CIPHER_MAX_IV_SIZE_IN_WORD];          /* Initialization vector (IV) */
    hi_cipher_bit_width bit_width;           /* Bit width for encryption or decryption */
    hi_cipher_sm1_round sm1_round;           /* SM1 round number, should be 8, 10, 12 or 14. */
    hi_cipher_ctrl_chg_flag chg_flags;       /* control information exchange choices, we default all woulde be change
                                                except they have been in the choices */
} hi_cipher_ctrl_sm1;

/* Structure of the cipher SM4 control information */
typedef struct {
    hi_u32 key[HI_CIPHER_SM4_KEY_SIZE_IN_WORD];        /* Key input */
    hi_u32 iv[HI_CIPHER_MAX_IV_SIZE_IN_WORD];          /* Initialization vector (IV) */
    hi_cipher_ctrl_chg_flag chg_flags;       /* control information exchange choices, we default all woulde be change
                                                except they have been in the choices */
} hi_cipher_ctrl_sm4;

/* Expand Structure of the cipher control information */
typedef struct {
    hi_cipher_alg alg;              /* Cipher algorithm */
    hi_cipher_work_mode work_mode;  /* Operating mode */
    hi_bool key_by_ca;              /* Encryption using advanced conditional access (CA) or decryption using keys */
    /*  Parameter for special algorithm
        for AES, the pointer should point to hi_cipher_ctrl_aes;
        for AES_CCM or AES_GCM, the pointer should point to hi_cipher_ctrl_aes_ccm_gcm;
        for SM1, the pointer should point to hi_cipher_ctrl_sm1;
        for SM4, the pointer should point to hi_cipher_ctrl_sm4;
    */
    hi_void *param;
    hi_u32 param_size;
} hi_cipher_ctrl_ex;

/* Cipher data */
typedef struct {
    hi_phys_addr_t src_phys_addr;   /* phy address of the original data */
    hi_phys_addr_t dst_phys_addr;   /* phy address of the purpose data */
    hi_u32 byte_len;                /* Cigher data length. */
    hi_bool odd_key;                /* Use odd key or even key. */
} hi_cipher_data;

/* Hash init struct input */
typedef struct {
    hi_u8 *hmac_key;
    hi_u32 hmac_key_len;
    hi_cipher_hash_type sha_type;
} hi_cipher_hash_attr;

/* RSA public key struct */
typedef struct {
    hi_u8 *n;         /* Point to public modulus N */
    hi_u8 *e;         /* Point to public exponent E */
    hi_u16 n_len;     /* Length of public modulus N, max value is 512Byte */
    hi_u16 e_len;     /* Length of public exponent E, max value is 512Byte */
} hi_cipher_rsa_pub_key;

/* RSA private key struct */
typedef struct {
    hi_u8 *n;         /* Public modulus N. */
    hi_u8 *e;         /* Public exponent E. */
    hi_u8 *d;         /* Private exponent D. */
    hi_u8 *p;         /* 1st prime factor P. */
    hi_u8 *q;         /* 2nd prime factor Q. */
    hi_u8 *dp;        /* descript:d % (p - 1) is DP. */
    hi_u8 *dq;        /* descript:d % (q - 1) is DQ. */
    hi_u8 *qp;        /* descript:1 / (q % p) is QP. */
    hi_u16 n_len;     /* Length of public modulus */
    hi_u16 e_len;     /* Length of public exponent */
    hi_u16 d_len;     /* Length of private exponent */
    hi_u16 p_len;     /* Length of 1st prime factor,should be half of n_len */
    hi_u16 q_len;     /* Length of 2nd prime factor,should be half of n_len */
    hi_u16 dp_len;    /* Length of D % (P - 1),should be half of n_len */
    hi_u16 dq_len;    /* Length of D % (Q - 1),should be half of n_len */
    hi_u16 qp_len;    /* Length of 1 / (Q % P),should be half of n_len */
} hi_cipher_rsa_private_key;

/* RSA public key encryption struct input */
typedef struct {
    hi_cipher_rsa_encrypt_scheme scheme;    /* RSA encryption scheme */
    hi_cipher_rsa_pub_key pub_key;          /* RSA public key struct */
} hi_cipher_rsa_pub_encrypt;

/* RSA private key decryption struct input */
typedef struct {
    hi_cipher_rsa_encrypt_scheme scheme;    /* RSA encryption scheme */
    hi_cipher_rsa_private_key private_key;  /* RSA private key struct */
    hi_cipher_ca_type ca_type;              /* CA type */
} hi_cipher_rsa_private_encrypt;

typedef struct {
    const hi_u8 *in;                        /* Input data to be cryption. */
    hi_u32 in_len;                          /* Length of input data. */
    hi_u8 *out;                             /* Output data. */
    hi_u32 out_buf_len;                     /* Length of output buffer. */
    hi_u32 *out_len;                        /* Length of output valid data. */
} hi_cipher_rsa_crypt;

/* RSA signature struct input */
typedef struct {
    hi_cipher_rsa_sign_scheme scheme;       /* RSA signature scheme */
    hi_cipher_rsa_private_key private_key;  /* RSA private key struct */
    hi_cipher_ca_type ca_type;              /* CA type */
} hi_cipher_rsa_sign;

/* RSA signature verify struct input */
typedef struct {
    hi_cipher_rsa_sign_scheme scheme;       /* RSA signature scheme */
    hi_cipher_rsa_pub_key pub_key;          /* RSA public key struct */
} hi_cipher_rsa_verify;

typedef struct {
    const hi_u8 *in;                    /* Input data to be cryption. */
    hi_u32 in_len;                      /* Length of input data. */
    const hi_u8 *hash_data;             /* Hash data. */
    hi_u32 hash_data_len;               /* Length of hash data. */
    hi_u8 *sign;                        /* Sign output data. */
    hi_u32 sign_buf_len;                /* Length of sign output buffer. */
    hi_u32 *sign_len;                   /* Length of sign output valid data. */
} hi_cipher_sign_data;

typedef struct {
    const hi_u8 *in;                    /* Input data to be cryption. */
    hi_u32 in_len;                      /* Length of input data. */
    const hi_u8 *hash_data;             /* Hash data. */
    hi_u32 hash_data_len;               /* Length of hash data. */
    hi_u8 *sign;                        /* Input sign data. */
    hi_u32 sign_len;                    /* Length of input sign data. */
} hi_cipher_verify_data;

/******************************* API Declaration *****************************/
/** \addtogroup      CIPHER */
/** @{ */  /** <!-- [CIPHER] */
/* ---CIPHER---*/
/**
\attention
This API is used to start the cipher device.

\param N/A
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.
\retval ::HI_ERR_CIPHER_FAILED_INIT  The cipher device fails to be initialized.
\see
N/A
*/
hi_s32 hi_mpi_cipher_init(hi_void);

/**
\brief  Deinit the cipher device.
\attention \n
This API is used to stop the cipher device.
If this API is called repeatedly, HI_SUCCESS is returned, but only the first operation takes effect.
\param N/A
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.
\see \n
N/A
*/
hi_s32 hi_mpi_cipher_deinit(hi_void);

/**
\brief Obtain a cipher handle for encryption and decryption.

\param[in] cipher attributes
\param[out] phCipher Cipher handle
\retval ::HI_SUCCESS Call this API successful.
\retval ::HI_FAILURE Call this API fails.
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.
\retval ::HI_ERR_CIPHER_INVALID_POINT  The pointer is null.
\retval ::HI_ERR_CIPHER_FAILED_GETHANDLE  The cipher handle fails to be obtained,
                                          because there are no available cipher handles.
\see \n
N/A
*/
hi_s32 hi_mpi_cipher_create_handle(hi_handle* handle, const hi_cipher_attr *cipher_attr);

/**
\attention \n
This API is used to destroy existing cipher handles.

\param[in] hCipher Cipher handle
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.
\see \n
N/A
*/
hi_s32 hi_mpi_cipher_destroy_handle(hi_handle handle);

/**
\brief Configures the cipher control information.
\attention \n
Before encryption or decryption, you must call this API to configure the cipher control information.
The first 64-bit data and the last 64-bit data should not be the same when using TDES algorithm.

\param[in] hCipher Cipher handle.
\param[in] pstCtrl Cipher control information.
\retval ::HI_SUCCESS Call this API successful.
\retval ::HI_FAILURE Call this API fails.
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.
\retval ::HI_ERR_CIPHER_INVALID_POINT  The pointer is null.
\retval ::HI_ERR_CIPHER_INVALID_PARA  The parameter is invalid.
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  The handle is invalid.
\see \n
N/A
*/
hi_s32 hi_mpi_cipher_config_handle(hi_handle handle, hi_cipher_ctrl* cipher_ctrl);

/**
\brief Configures the cipher control information.
\attention \n
Before encryption or decryption, you must call this API to configure the cipher control information.
The first 64-bit data and the last 64-bit data should not be the same when using TDES algorithm.

\param[in] hCipher Cipher handle.
\param[in] pstExCtrl Cipher control information.
\retval ::HI_SUCCESS Call this API successful.
\retval ::HI_FAILURE Call this API fails.
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.
\retval ::HI_ERR_CIPHER_INVALID_POINT  The pointer is null.
\retval ::HI_ERR_CIPHER_INVALID_PARA  The parameter is invalid.
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  The handle is invalid.
\see \n
N/A
*/
hi_s32 hi_mpi_cipher_config_handle_ex(hi_handle handle, hi_cipher_ctrl_ex* ctrl_ex);

/**
\brief Performs encryption.

\attention \n
This API is used to perform encryption by using the cipher module.
The length of the encrypted data should be a multiple of 8 in TDES mode and 16 in AES mode.
Besides, the length can not be bigger than 0xFFFFF.After this operation, the result will affect next operation.
If you want to remove vector,
you need to config IV(config pstCtrl->chg_flags.bit1IV with 1) by transfering hi_mpi_cipher_config_handle.
\param[in] hCipher Cipher handle
\param[in] u32SrcPhyAddr Physical address of the source data
\param[in] u32DestPhyAddr Physical address of the target data
\param[in] u32ByteLength   Length of the encrypted data
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.
\retval ::HI_ERR_CIPHER_INVALID_PARA  The parameter is invalid.
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  The handle is invalid.
\see \n
N/A
*/
hi_s32 hi_mpi_cipher_encrypt(hi_handle handle, hi_size_t src_phy_addr, hi_size_t dest_phy_addr, hi_u32 byte_len);

/**
\brief Performs decryption.

\attention \n
This API is used to perform decryption by using the cipher module.
The length of the decrypted data should be a multiple of 8 in TDES mode and 16 in AES mode.
Besides, the length can not be bigger than 0xFFFFF.
After this operation, the result will affect next operation.
If you want to remove vector,
you need to config IV(config pstCtrl->chg_flags.bit1IV with 1) by transfering hi_mpi_cipher_config_handle.
\param[in] hCipher Cipher handle.
\param[in] u32SrcPhyAddr Physical address of the source data.
\param[in] u32DestPhyAddr Physical address of the target data.
\param[in] u32ByteLength Length of the decrypted data
\retval ::HI_SUCCESS Call this API successful.
\retval ::HI_FAILURE Call this API fails.
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.
\retval ::HI_ERR_CIPHER_INVALID_PARA  The parameter is invalid.
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  The handle is invalid.
\see \n
N/A
*/
hi_s32 hi_mpi_cipher_decrypt(hi_handle handle, hi_size_t src_phy_addr, hi_size_t dest_phy_addr, hi_u32 byte_len);

/**
\brief Encrypt multiple packaged data.
\attention \n
You can not encrypt more than 128 data package one time.
When HI_ERR_CIPHER_BUSY return, the data package you send will not be deal,
the customer should decrease the number of data package or run cipher again.
Note: When encrypting more than one packaged data,
every one package will be calculated using initial vector configured by hi_mpi_cipher_config_handle.
Previous result will not affect the later result.
\param[in] hCipher cipher handle
\param[in] pstDataPkg data package ready for cipher
\param[in] u32DataPkgNum  number of package ready for cipher
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.
\retval ::HI_ERR_CIPHER_NOT_INIT  cipher device have not been initialized
\retval ::HI_ERR_CIPHER_INVALID_PARA  parameter error
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  handle invalid
\retval ::HI_ERR_CIPHER_BUSY  hardware is busy, it can not deal with all data package once time
\see \n
N/A
*/
hi_s32 hi_mpi_cipher_encrypt_multi_pack(hi_handle handle, hi_cipher_data *data_pkg, hi_u32 data_pkg_num);

/**
\brief Decrypt multiple packaged data.
\attention \n
You can not decrypt more than 128 data package one time.
When HI_ERR_CIPHER_BUSY return, the data package you send will not be deal,
the custmer should decrease the number of data package or run cipher again.
Note: When decrypting more than one packaged data,
every one package will be calculated using initial vector configured by hi_mpi_cipher_config_handle.
Previous result will not affect the later result.
\param[in] hCipher cipher handle
\param[in] pstDataPkg data package ready for cipher
\param[in] u32DataPkgNum  number of package ready for cipher
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.
\retval ::HI_ERR_CIPHER_NOT_INIT  cipher device have not been initialized
\retval ::HI_ERR_CIPHER_INVALID_PARA  parameter error
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  handle invalid
\retval ::HI_ERR_CIPHER_BUSY  hardware is busy, it can not deal with all data package once time
\see \n
N/A
*/
hi_s32 hi_mpi_cipher_decrypt_multi_pack(hi_handle handle, hi_cipher_data *data_pkg, hi_u32 data_pkg_num);

/**
\brief Get the cipher control information.

\param[in] hCipher Cipher handle.
\param[in] pstCtrl Cipher control information.
\retval ::HI_SUCCESS Call this API successful.
\retval ::HI_FAILURE Call this API fails.
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.
\retval ::HI_ERR_CIPHER_INVALID_POINT  The pointer is null.
\retval ::HI_ERR_CIPHER_INVALID_PARA  The parameter is invalid.
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  The handle is invalid.
\see \n
N/A
*/
hi_s32 hi_mpi_cipher_get_handle_cfg(hi_handle handle, hi_cipher_ctrl* cipher_ctrl);

/**
\brief Get the tag data of CCM/GCM.

\attention \n
This API is used to get the tag data of CCM/GCM.
\param[in] hCipher cipher handle
\param[out] pu8Tag tag data of CCM/GCM
\retval ::HI_SUCCESS  Call this API succussful.
\retval ::HI_FAILURE  Call this API fails.
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.
\retval ::HI_ERR_CIPHER_INVALID_PARA  The parameter is invalid.
\see \n
N/A
*/
hi_s32 hi_mpi_cipher_get_tag(hi_handle handle, hi_u8 *tag, hi_u32 *tag_len);

/**
\brief Encrypt the clean key data by KLAD.
\attention \n
N/A
\param[in] enRootKey klad root key.
\param[in] pu8CleanKey clean key.
\param[in] enTarget the module who to use this key.
\param[out] pu8EcnryptKey encrypt key.
\param[in] u32KeyLen clean key.
\retval ::HI_SUCCESS Call this API successful.
\retval ::HI_FAILURE Call this API fails.
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.
\retval ::HI_ERR_CIPHER_INVALID_POINT  The pointer is null.
\retval ::HI_ERR_CIPHER_INVALID_PARA  The parameter is invalid.
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  The handle is invalid.
\see \n
N/A
*/
hi_s32 hi_mpi_cipher_klad_encrypt_key(hi_cipher_ca_type root_key,
                                      hi_cipher_klad_target klad_target,
                                      hi_u8 *clean_key,
                                      hi_u8* enc_key,
                                      hi_u32 key_len);

/**
\brief Get the random number.

\attention \n
This API is used to obtain the random number from the hardware.

\param[out] pu32RandomNumber Point to the random number.
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.

\see \n
N/A
*/
hi_s32 hi_mpi_cipher_get_random_number(hi_u32 *random_number);

/**
\brief Init the hash module, if other program is using the hash module, the API will return failure.

\attention \n
N/A

\param[in] pstHashAttr: The hash calculating structure input.
\param[out] pHashHandle: The output hash handle.
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.

\see \n
N/A
*/
hi_s32 hi_mpi_cipher_hash_init(hi_cipher_hash_attr *hash_attr, hi_handle *hash_handle);

/**
\brief Calculate the hash, if the size of the data to be calculated is very big and the DDR ram is not enough,
       this API can calculate the data one block by one block.
       Attention: The input block length must be 64bytes aligned except for the last block.

\attention \n
N/A

\param[in] hHashHandl:  Hash handle.
\param[in] pu8InputData:  The input data buffer.
\param[in] u32InputDataLen:  The input data length.
                             Attention: the block length input must be 64bytes aligned except the last block!
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.

\see \n
N/A
*/
hi_s32 hi_mpi_cipher_hash_update(hi_handle hash_handle, hi_u8 *input_data, hi_u32 input_data_len);

/**
\brief Get the final hash value, after calculate all of the data,
       call this API to get the final hash value and close the handle.
       If there is some reason need to interrupt the calculation,
       this API should also be call to close the handle.

\attention \n
N/A

\param[in] hHashHandle:  Hash handle.
\param[out] pu8OutputHash:  The final output hash value.

\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.

\see \n
N/A
*/
hi_s32 hi_mpi_cipher_hash_final(hi_handle hash_handle, hi_u8 *output_hash);

/*
 * brief RSA encryption a plaintext with a RSA public key.
 *
 * attention \n
 * N/A
 *
 * param[in]  rsa_encrypt:    encryption struct.
 * param[in]  rsa_data:       rsa data struct.
 * retval ::HI_SUCCESS        Call this API successful.
 * retval ::HI_FAILURE        Call this API fails.
 *
 * see \n
 * N/A
 */
hi_s32 hi_mpi_cipher_rsa_pub_encrypt(const hi_cipher_rsa_pub_encrypt *rsa_encrypt,
                                     hi_cipher_rsa_crypt *rsa_data);

/*
 * brief RSA decryption a ciphertext with a RSA private key.
 *
 * attention \n
 * N/A
 *
 * param[in]  rsa_decrypt:    decryption struct.
 * param[in]  rsa_data:       rsa data struct.
 * retval ::HI_SUCCESS        Call this API successful.
 * retval ::HI_FAILURE        Call this API fails.
 *
 * see \n
 * N/A
 */
hi_s32 hi_mpi_cipher_rsa_private_decrypt(const hi_cipher_rsa_private_encrypt *rsa_decrypt,
                                         hi_cipher_rsa_crypt *rsa_data);

/*
 * brief RSA signature a context with appendix, where a signer's RSA private key is used.
 *
 * attention \n
 * N/A
 * param[in]  rsa_sign:       signature struct.
 * param[in]  sign_data:      sign data struct.
 * retval ::HI_SUCCESS        Call this API successful.
 * retval ::HI_FAILURE        Call this API fails.
 * see \n
 * N/A
 */
hi_s32 hi_mpi_cipher_rsa_sign(const hi_cipher_rsa_sign *rsa_sign,
                              hi_cipher_sign_data *sign_data);

/*
 * brief RSA signature verification a context with appendix, where a signer's RSA public key is used.
 *
 * attention \n
 * N/A
 *
 * param[in] rsa_verify:      signature verification struct.
 * param[in] verify_data:     verify data struct;
 * retval ::HI_SUCCESS        Call this API successful.
 * retval ::HI_FAILURE        Call this API fails.
 *
 * see \n
 * N/A
 */
hi_s32 hi_mpi_cipher_rsa_verify(const hi_cipher_rsa_verify *rsa_verify,
                                hi_cipher_verify_data *verify_data);

/*
 * brief RSA encryption a plaintext with a RSA private key.
 *
 * attention \n
 * N/A
 *
 * param[in]  rsa_encrypt:    encryption struct.
 * param[in]  rsa_data:       rsa data struct.
 * retval ::HI_SUCCESS        Call this API successful.
 * retval ::HI_FAILURE        Call this API fails.
 *
 * see \n
 * N/A
 */
hi_s32 hi_mpi_cipher_rsa_private_encrypt(const hi_cipher_rsa_private_encrypt *rsa_encrypt,
                                         hi_cipher_rsa_crypt *rsa_data);

/*
 * brief RSA decryption a ciphertext with a RSA public key.
 *
 * attention \n
 * N/A
 *
 * param[in]  rsa_decrypt:    decryption struct.
 * param[in]  rsa_data:       rsa data struct.
 * retval ::HI_SUCCESS        Call this API successful.
 * retval ::HI_FAILURE        Call this API fails.
 *
 * see \n
 * N/A
 */
hi_s32 hi_mpi_cipher_rsa_pub_decrypt(const hi_cipher_rsa_pub_encrypt *rsa_decrypt,
                                     hi_cipher_rsa_crypt *rsa_data);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_CIPHER_H__ */

