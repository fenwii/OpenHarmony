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
 * Description   : head file for cipher drv api
 */

#ifndef __HI_DRV_CIPHER_H__
#define __HI_DRV_CIPHER_H__

#include "hi_types.h"
#include "hi_mpi_cipher.h"

#ifdef __cplusplus
extern "C" {
#endif    /* __cplusplus */

#define MAX_MULTI_PKG_NUM           128
#define CIPHER_SOFT_CHAN_NUM        8
#define CIPHER_INVALID_CHN          0xffffffff
#define CIPHER_MAX_NODE_BUF_SIZE    0xFFFF0   /* 1M-16 */
#define CIPHER_MAX_RSA_KEY_LEN      512
#define HASH_OUTPUT_SIZE_WORD       (1600 / 8 / 4)    /* sha3 state */

#define HDCP_KEY_RAM_SIZE           320
#define HDCP_KEY_PRIME_SIZE         320
#define HDCP_KEY_TOOL_FILE_SIZE     384
#define HDCP_KEY_CHIP_FILE_SIZE     (HDCP_KEY_RAM_SIZE + 12)

#define HASH_ALG_SHA2               0x01
#define HASH_ALG_SHA3               0x02
#define HASH_ALG_SM3                0x03

#define HASH_MODE_RAW               0x01
#define HASH_MODE_MAC               0x02
#define HASH_MODE_SHAKE             0x03

#define CPU_BIT_WIDTH_32            32
#define CPU_BIT_WIDTH_64            64
#define MY_CPU_BIT_WIDTH            sizeof(hi_size_t)

typedef enum {
    HI_DRV_HASH_STEP_UPDATE = 0x0,
    HI_DRV_HASH_STEP_INIT   = 0x01,
    HI_DRV_HASH_STEP_FINAL  = 0x02,
} hi_drv_hash_step_e;

typedef struct {
    hi_handle ci_handle;
    hi_cipher_attr cipher_atts;
} cipher_handle_s;

typedef struct {
    hi_handle ci_handle;
    hi_u32 src_phy_addr;
    hi_u32 src_phy_addr_high;
    hi_u32 dest_phy_addr;
    hi_u32 dest_phy_addr_high;
    hi_u32 data_length;
} cipher_data_s;

typedef struct {
    hi_handle ci_handle;
    hi_u32 pkg_num;
    hi_u32 user_bit_width;
    hi_cipher_data* cipher_data;
} cipher_pkg_s;

typedef struct {
    hi_handle ci_handle;
    hi_cipher_ctrl cipher_ctrl;
} cipher_config_ctrl_s;

typedef struct {
    hi_handle ci_handle;
    hi_u32 time_out;
} cipher_wait_done_s;

typedef struct {
    hi_handle ci_handle;
    hi_u32 key[12];                                 /* Key input, EK||AK||SK for SM1, 12 */
    hi_u32 odd_key[8];                              /* Key input, Old Key, 8 */
    hi_u32 iv[4];                                   /* Initialization vector (IV), 4 */
    /* Encryption using advanced conditional access (CA) or decryption using keys */
    hi_bool key_by_ca;
    hi_cipher_ca_type ca_type;                /* Select keyladder type when using advanced CA */
    hi_cipher_alg ci_alg;                     /* Cipher algorithm */
    hi_cipher_bit_width bit_width;            /* Bit width for encryption or decryption */
    hi_cipher_work_mode work_mode;            /* Operating mode */
    hi_cipher_key_len key_len;             /* Key length */
    /* control information exchange choices,
     * we default all woulde be change except they have been in the choices */
    hi_cipher_ctrl_chg_flag change_flags;
    hi_cipher_sm1_round sm1_round;            /* SM1 round number, should be 8, 10, 12 or 14 */
    /* IV lenght for CCM/GCM, which is an element of {4, 6, 8, 10, 12, 14, 16} for CCM,
     * and is an element of [1-16] for GCM */
    hi_u32 iv_len;
    /* Tag lenght for CCM which is an element of {4, 6, 8, 10, 12, 14, 16} */
    hi_u32 tag_len;
    hi_u32 alen;                                    /* Associated data for CCM and GCM */
    hi_u32 aphy_addr;
    hi_u32 aphy_addr_high;                          /* Physical address of Associated data for CCM and GCM */
} cipher_config_ctrl_ex_s;

typedef struct {
    hi_cipher_hash_type sha_type;
    hi_u32 hard_chn;
    hi_u32 sha_val[16]; /* 16 size */
    hi_u32 data_phy;
    hi_u32 data_phy_high;
    hi_u32 data_len;
} cipher_hash_data_s;

typedef struct {
    hi_cipher_hash_attr hash_attr;
    hi_handle hash_handle;
} cipher_hash_init_s;

typedef struct {
    hi_handle hash_handle;
    hi_u8 *input_data;
    hi_u32 input_data_len;
} cipher_hash_update_s;

typedef struct {
    hi_handle hash_handle;
    hi_u8 *output_hash;
} cipher_hash_finish_s;

typedef struct {
    hi_u32 time_out_us;
    hi_u32 ci_rng;
} cipher_rng_s;

typedef struct {
    hi_handle ci_handle;
    hi_u32 tag_len;
    hi_u32 tag[4]; /* 4 tag size */
} cipher_tag_s;

typedef struct {
    hi_u8 *input_data;
    hi_u8 *output_data;
    hi_u32 data_len;
    hi_u8 *rsa_n;
    hi_u8 *rsa_k;
    hi_u16 rsa_n_len;
    hi_u16 rsa_k_len;
    hi_cipher_ca_type ca_type;               /* Select keyladder type when using advanced CA */
} cipher_rsa_data_s;

/** RSA private key struct */
typedef struct {
    hi_u8 *rsa_n;                      /*!<  public modulus    */
    hi_u8 *rsa_e;                      /*!<  public exponent   */
    hi_u8 *rsa_d;                      /*!<  private exponent  */
    hi_u8 *rsa_p;                      /*!<  1st prime factor  */
    hi_u8 *rsa_q;                      /*!<  2nd prime factor  */
    hi_u8 *rsa_dp;                     /*!<  D % (P - 1)       */
    hi_u8 *rsa_dq;                     /*!<  D % (Q - 1)       */
    hi_u8 *rsa_qp;                     /*!<  1 / (Q % P)       */
    hi_u16 rsa_n_len;                   /* length of public modulus */
    hi_u16 rsa_e_len;                   /* length of public exponent */
    hi_u16 rsa_d_len;                   /* length of private exponent */
    hi_u16 rsa_p_len;                   /* length of 1st prime factor */
    hi_u16 rsa_q_len;                   /* length of 2nd prime factor */
    hi_u16 rsa_dp_len;                  /* length of D % (P - 1) */
    hi_u16 rsa_dq_len;                  /* length of D % (Q - 1) */
    hi_u16 rsa_qp_len;                  /* length of 1 / (Q % P) */
} cipher_rsa_pri_key_s;

typedef struct {
    cipher_rsa_pri_key_s pri_key;
    hi_u32 num_bits;
    hi_u32 exponent;
} cipher_rsa_key_s;

typedef enum {
    CIPHER_TEST_PRINT_PHY = 0x01,
    CIPHER_TEST_PRINT_VIA,
    CIPHER_TEST_MEMSET,
    CIPHER_TEST_MEMCMP,
    CIPHER_TEST_MEMCPY,
    CIPHER_TEST_MEMCMP_PHY,
    CIPHER_TEST_READ_REG,
    CIPHER_TEST_WRITE_REG,
    CIPHER_TEST_AES  = 0x10,
    CIPHER_TEST_HMAC,
    CIPHER_TEST_RSA,
    CIPHER_TEST_HASH,
    CIPHER_TEST_DES,
    CIPHER_TEST_RSA_PRIM,
    CIPHER_TEST_RSA_KG,
    CIPHER_TEST_RND,
    CIPHER_TEST_BUTT,
} cipher_test_e;

#ifdef CONFIG_COMPAT
typedef struct {
    hi_handle ci_handle;
    hi_u32 pkg_num;
    hi_u32 pkg_via;
} cipher_compat_pkg_s;

typedef struct {
    hi_u32 input_via;
    hi_u32 output_via;
    hi_u32 data_len;
    hi_u32 rsa_n_via;
    hi_u32 rsa_k_via;
    hi_u16 rsa_n_len;
    hi_u16 rsa_k_len;
} cipher_compat_rsa_data_s;
#endif

typedef struct {
    hi_cipher_ca_type root_key;
    hi_cipher_klad_target klad_target;
    hi_u32 clean_key[4];   /* 4 key size */
    hi_u32 encrypt_key[4]; /* 4 key size */
    hi_u32 key_len;
} cipher_klad_key_s;

hi_s32 hi_drv_cipher_create_handle(cipher_handle_s *ci_handle, hi_void *file);
hi_s32 hi_drv_cipher_config_chn(hi_u32 soft_chn_id, hi_cipher_ctrl *config);
hi_s32 hi_drv_cipher_config_chn_ex(hi_handle ci_handle, cipher_config_ctrl_ex_s *config);
hi_s32 hi_drv_cipher_get_handle_config(cipher_config_ctrl_s *cipher_config);
hi_s32 hi_drv_cipher_get_handle_config_ex(cipher_config_ctrl_ex_s *cipher_config);
hi_s32 hi_drv_cipher_get_iv(hi_u32 chn_id, hi_u32 iv[4]); /* 4 iv size */
hi_s32 hi_drv_cipher_destory_handle(hi_handle cipher_chn);
hi_s32 hi_drv_cipher_encrypt(cipher_data_s *ci_data);
hi_s32 hi_drv_cipher_decrypt(cipher_data_s *ci_data);
hi_s32 hi_drv_cipher_encrypt_multi(cipher_pkg_s *pkg);
hi_s32 hi_drv_cipher_decrypt_multi(cipher_pkg_s *pkg);
hi_s32 hi_drv_cipher_encrypt_multi_asyn(cipher_pkg_s *pkg);
hi_s32 hi_drv_cipher_decrypt_multi_asyn(cipher_pkg_s *pkg);
hi_s32 hi_drv_cipher_wait_done(cipher_wait_done_s *wait_done);
hi_s32 hi_drv_cipher_hash_wait_done(hi_handle handle);
hi_s32 hi_drv_cipher_get_random_number(cipher_rng_s *rng);
hi_s32 hi_drv_cipher_soft_reset(hi_void);
hi_s32 hi_drv_cipher_calc_hash_init(cipher_hash_data_s *cipher_hash_data);
hi_s32 hi_drv_cipher_calc_hash_update(cipher_hash_data_s *cipher_hash_data);
hi_s32 hi_drv_cipher_calc_hash_final(cipher_hash_data_s *cipher_hash_data);
hi_s32 hi_drv_cipher_get_tag(cipher_tag_s *tag);
hi_s32 hi_drv_cipher_calc_rsa(cipher_rsa_data_s *cipher_rsa_data);
hi_s32 hi_drv_cipher_klad_encrypt_key(cipher_klad_key_s *klad_key);

hi_void hi_drv_cipher_suspend(hi_void);
hi_s32 hi_drv_cipher_resume(hi_void);

#ifdef __cplusplus
}
#endif    /* __cplusplus */

#endif    /* End of #ifndef __HI_DRV_CIPHER_H__ */

