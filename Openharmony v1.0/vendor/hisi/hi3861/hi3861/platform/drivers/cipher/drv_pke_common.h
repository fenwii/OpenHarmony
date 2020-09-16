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
 *
 * Description: head file of cipher pke common driver.
 */

#ifndef __DRV_PKE_COMMON_H__
#define __DRV_PKE_COMMON_H__

#include "hi_cipher.h"
#include "cipher.h"
#include "drv_osal_lib.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif  /* __cplusplus */

#define CRYPTO_PKE_ECC_SUPPORT

/* Define the offset of reg */
#define PKE_VERSION_DATE                 0x0
#define PKE_BUSY                         0x4
#define PKE_WORK_MODE                    0x8
#define PKE_START                        0xc
#define PKE_INT_ENABLE                   0x10
#define PKE_INT_STATUS                   0x14
#define PKE_INT_NOMASK_STATUS            0x18
#define PKE_KEY_CRC                      0x20
#define PKE_KEY_RANDOM_1                 0x24
#define PKE_KEY_RANDOM_2                 0x28
#define PKE_RESULT_FLAG                  0x24
#define PKE_FAILURE_FLAG                 0x28
#define PKE_OTP_KEY_SEL                  0x38
#define PKE_CFG_KEY_FLAG                 0x3c
#define PKE_NOISE_EN                     0x1C
#define PKE_MRAM                         0x200
#define PKE_PRAM                         0x300
#define PKE_NRAM                         0x600
#define PKE_KRAM                         0xa00
#define PKE_RRAM                         0xe00

#define HISC_COM_PKE_CLK_ENABLE          0x08

#define PKE_LOCK_TPP                     0x55
#define PKE_LOCK_HPP                     0x95  /* HSL */
#define PKE_LOCK_TEE                     0xA5
#define PKE_LOCK_REE                     0xAA

#define PKE_INT_VALID                    1
#define PKE_INT_INVALID                  0
#define PKE_INT_NOMASK_VALID             1
#define PKE_INT_NOMASK_INVALID           0
#define PKE_INT_ENABLE_VALID             1
#define PKE_INT_ENABLE_INVALID           0

#define PKE_RAM_SELECT_0                 0
#define PKE_RAM_SELECT_1                 1
#define PKE_RAM_SELECT_2                 2
#define PKE_RAM_SELECT_3                 3
#define PKE_RAM_SELECT_4                 4

/* Define the pke data len */
typedef enum {
    PKE_DATA_LEN_BYTE_32  = 4,
    PKE_DATA_LEN_BYTE_48  = 6,
    PKE_DATA_LEN_BYTE_64  = 8,
    PKE_DATA_LEN_BYTE_72  = 9,
    PKE_DATA_LEN_BYTE_128 = 16,
    PKE_DATA_LEN_BYTE_256 = 32,
    PKE_DATA_LEN_BYTE_384 = 48,
    PKE_DATA_LEN_BYTE_512 = 64,
} pke_data_len;

/* Define the ram sel for clear */
typedef enum {
    PKE_CLR_RAM_SEL_NONE = 0x00,
    PKE_CLR_RAM_SEL_MRAM = 0x01,
    PKE_CLR_RAM_SEL_NRAM = 0x02,
    PKE_CLR_RAM_SEL_KRAM = 0x04,
    PKE_CLR_RAM_SEL_RRAM = 0x08,
    PKE_CLR_RAM_SEL_RAM  = 0x10,
    PKE_CLR_RAM_SEL_ALL  = 0x1F,
} pke_clr_ram_sel;

/* Define the ram type */
typedef enum {
    PKE_RAM_TYPE_MRAM = 0,   /* 0x0200 ~ 0x05FF */
    PKE_RAM_TYPE_NRAM,       /* 0x0600 ~ 0x09FF */
    PKE_RAM_TYPE_KRAM,       /* 0x0a00 ~ 0x0dFF */
    PKE_RAM_TYPE_RRAM,       /* 0x0e00 ~ 0x11FF */
} pke_ram_type;

/* Define the operaion mode */
typedef enum {
    PKE_MODE_CLR_RAM        = 0x0,
    PKE_MODE_EXP_MOD        = 0x1,
    PKE_MODE_MUL_DOT        = 0x2,
    PKE_MODE_ADD_DOT        = 0x3,
    PKE_MODE_TIMES_DOT      = 0x4,
    PKE_MODE_ADD_MOD        = 0x5,
    PKE_MODE_SUB_MOD        = 0x6,
    PKE_MODE_MUL_MOD        = 0x7,
    PKE_MODE_MINV_MOD       = 0x8,
    PKE_MODE_MOD            = 0x9,
    PKE_MODE_MUL            = 0xa,
    PKE_MODE_KGEN_NO_E      = 0x10,
    PKE_MODE_KGEN_WITH_E    = 0x11,
    PKE_MODE_KTRANS         = 0x12,
} pke_mode;

/* Define the result flag */
typedef enum {
    PKE_RESULT_FLAG_FAIL  = 0x00,
    PKE_RESULT_FLAG_OK    = 0x01,
} pke_result_code;

typedef enum {
    PKE_FAIL_FLAG_MOD_INFINITY           = 0x01,
    PKE_FAIL_FLAG_INPUT_POINT_INVALID    = 0x02,
    PKE_FAIL_FLAG_OUTPUT_POINT_INVALID   = 0x04,
    PKE_FAIL_FLAG_DFX                    = 0x08,
} pke_fail_flag;

#define PKE_FAIL_FLAG_CNT  0x08
#define PKE_SECURE_TRUE    0x01
#define PKE_SECURE_FALSE   0x00

/* Define the union U_PKE_BUSY */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pke_busy              : 1; /* [0]  */
        unsigned int    reserved_0            : 31; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_busy;

/* Define the union U_PKE_WORK_MODE */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    mode_sel              : 4; /* [3..0]  */
        unsigned int    data_len              : 2; /* [5..4]  */
        unsigned int    reserved              : 26; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_work_mode;

/* Define the union U_PKE_START */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pke_start             : 1; /* [0]  */
        unsigned int    reserved_0            : 31; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_start;

/* Define the union U_PKE_INT_ENABLE */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pke_int_enable     : 1; /* [0]      */
        unsigned int    reserved_0         : 31; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_int_enable;

/* Define the union U_PKE_INT_STATUS */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pke_int               : 1; /* [0]  */
        unsigned int    reserved_0            : 31; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_int_status;

/* Define the union U_PKE_INT_NOMASK_STATUS */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pke_int_nomask        : 1; /* [0]  */
        unsigned int    reserved_0            : 31; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_int_nomask_status;

/* Define the union U_PKE_POWER_NOISE_LOCK */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    power_noise_lock      : 4; /* [3..0]  */
        unsigned int    reserved_0            : 28; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
}pke_power_noise_lock;

/* Define the union U_PKE_KEY_CRC */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    key_crc_in            : 16; /* [15..0]  */
        unsigned int    key_crc_out           : 16; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_key_crc;

/* Define the union U_PKE_RESULT_FLAG */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pke_result_flag       : 4; /* [3..0]  */
        unsigned int    reserved_0            : 28; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_result_flag;

/* Define the union U_PKE_FAILURE_FLAG */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pke_failure_flag      : 8; /* [7..0]  */
        unsigned int    reserved_0            : 24; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_failure_flag;

/* Define the union U_PKE_OTP_KEY_SEL */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    otp_key_sel           : 4; /* [3..0]  */
        unsigned int    reserved_0            : 28; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_otp_key_sel;

/* Define the union U_PKE_CFG_KEY_FLAG */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    key_cfg_flag          : 4; /* [3..0]  */
        unsigned int    reserved_0            : 28; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_cfg_key_flag;

/* Define the union U_PKE_POWER_EN */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    power_en              : 4; /* [3..0]  */
        unsigned int    reserved_0            : 28; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_power_on;

/* Define the union U_PKE_NOISE_EN */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pke_noise_en          : 1; /* [0]  */
        unsigned int    reserved_0            : 31; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_noise_en;

/* Define the union U_PKE_INT_EN */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pke_lock_int_en       : 1; /* [0]  */
        unsigned int    reserved_0            : 31; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_int_en;

/* Define the union U_PKE_LOCK_CTRL */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pke_lock              : 1; /* [0]  */
        unsigned int    pke_lock_type         : 1; /* [1]  */
        unsigned int    reserved_0            : 30; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_lock_ctrl;

/* Define the union U_PKE_LOCK_STATUS */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pke_lock_busy         : 1; /* [0]  */
        unsigned int    pke_unlock_fail       : 1; /* [1]  */
        unsigned int    reserved_0            : 2; /* [3..2]  */
        unsigned int    pke_lock_cnt          : 3; /* [6..4]  */
        unsigned int    reserved_1            : 1; /* [7]  */
        unsigned int    pke_lock_stat         : 8; /* [15..8]  */
        unsigned int    reserved_2            : 16; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_lock_status;

/* Define the union U_PKE_ERROR */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pke_access_err        : 1; /* [0]  */
        unsigned int    reserved_0            : 31; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} pke_error;

/* Define the union HISC_COM_PKE_CLK_ENABLE */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pke_clk_enable        : 1; /* [0]  */
        unsigned int    reserved_0            : 31; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
}hisc_com_pke_clk_enable;

/*************************** Pke Definition ****************************/
/*  Define the length of zero padding for mul-dot */
#define PKE_LEN_BLOCK_IN_WOED        0x02
#define PKE_LEN_BLOCK_IN_BYTE        0x08

#define REG_PKE_BASE                 0x40c06000

#define PKE_CLK_DISABLE              0x0
#define PKE_CLK_ENABLE               0x1
#define STEP_AUTH                    0x1

/* Define the union for pke block */
typedef union {
    hi_u8  byte[PKE_LEN_BLOCK_IN_BYTE];
    hi_u32 word[PKE_LEN_BLOCK_IN_WOED];
}pke_block;

#define HASH_LEN_256                 32
#define PKE_KEY_LEN_IN_BYTE          32

typedef enum {
    ROTATE_DIABLE,
    ROTATE_ENABLE
}rotate_type;

typedef enum {
    PKE_WIDTH_256BIT = 0x00,
    PKE_WIDTH_2048BIT,
    PKE_WIDTH_3072BIT,
    PKE_WIDTH_4096BIT,
}pke_width;

typedef struct {
    const hi_u8 *a;
    const hi_u8 *b;
    const hi_u8 *p;
    hi_u8 *c;
    hi_u32 klen;
}pke_add_mod;

typedef struct {
    const hi_u8 *n;
    const hi_u8 *e;
    const hi_u8 *m;
    hi_u8 *c;
    hi_u32 klen;
}rsa_exp_mod;

typedef struct {
    const hi_u8 *a;
    const hi_u8 *b;
    const hi_u8 *p;
    hi_u8 *c;
    hi_u32 klen;
}pke_mul_mod;

typedef struct {
    const hi_u8 *k;
    const hi_u8 *px;
    const hi_u8 *py;
    hi_u8 *rx;
    hi_u8 *ry;
    hi_u32 klen;
}pke_mul_dot;

typedef struct {
    const hi_u8 *sx;
    const hi_u8 *sy;
    const hi_u8 *rx;
    const hi_u8 *ry;
    hi_u8 *cx;
    hi_u8 *cy;
    hi_u32 klen;
}pke_add_dot;

typedef struct {
    const hi_u8 *sx;
    const hi_u8 *sy;
    hi_u8 *cx;
    hi_u8 *cy;
    hi_u32 klen;
}pke_double_dot;

typedef struct {
    hi_u32 power;
    const hi_u8 *p;
    hi_u8 *c;
    hi_u32 klen;
}pke_mod_block;

typedef struct {
    hi_bool is_liteos;
    hi_bool pke_initialize;
    hi_bool clk_initialize;
    hi_u8 resv;
}pke_init_ctx;

/**
\brief  Initialize the pke module.
\retval     On success, HI_ERR_SUCCESS is returned. On error, HI_ERR_FAILURE is returned.
*/
hi_u32 drv_pke_init(hi_bool is_liteos);

/**
\brief  Deinitialize the pke module.
\retval     On success, HI_ERR_SUCCESS is returned. On error, HI_ERR_FAILURE is returned.
*/
hi_u32 drv_pke_deinit(hi_void);

hi_void pke_enable(hi_void);

hi_void pke_disable(hi_void);

pke_init_ctx *drv_pke_get_pke_init(hi_void);
crypto_mutex_ctx *drv_pke_get_mutex(hi_void);

hi_u32 drv_pke_inv_mod(const hi_u8 *a, const hi_u8 *p, hi_u8 *c, hi_u32 klen, rotate_type rotate);

/* c=m^e mod n */
hi_u32 drv_ifep_rsa_exp_mod(const rsa_exp_mod *exp, rotate_type rotate);

/**
\brief  clean pke ram .
*/
hi_u32 drv_pke_clean_ram(hi_void);

hi_u32 drv_pke_rsa_check_rsa_data(const hi_u8 *n, const hi_u8 *e, const hi_u8 *mc, hi_u32 mc_len, hi_u32 keylen);

#ifdef CRYPTO_PKE_ECC_SUPPORT
hi_bool drv_pke_ecc_is_zero(const hi_void *val, hi_u32 klen);

/* descript: c = a mod p */
hi_u32 drv_pke_mod(const hi_u8 *a, const hi_u8 *p, hi_u8 *c, hi_u32 klen, rotate_type rotate);

/* descript: c = a * b */
hi_u32 drv_pke_mul(const hi_u8 *a, const hi_u8 *b, hi_u8 *c, hi_u32 klen, rotate_type rotate);

/* descript: c = a + b mod p */
hi_u32 drv_pke_add_mod(const pke_add_mod *para, rotate_type rotate);

/* descript: c = a - b mod p */
hi_u32 drv_pke_sub_mod(const pke_add_mod *para, rotate_type rotate);

/* descript: c = a * b mod p */
hi_u32 drv_pke_mul_mod(const pke_mul_mod *para, rotate_type rotate);

/* descript: R = k . P(x,y) */
hi_u32 drv_pke_mul_dot(const pke_mul_dot *para, const hi_cipher_ecc_param *ecp_id, rotate_type rotate);

/* descript: C = S(x,y) + R(x,y) */
hi_u32 drv_pke_add_dot(const pke_add_dot *para, const hi_cipher_ecc_param *ecp_id, rotate_type rotate);

/* descript: C = S(x,y) + S(x,y) */
hi_u32 drv_pke_double_dot(const pke_double_dot *para, const hi_cipher_ecc_param *ecp_id, rotate_type rotate);

/* descript: c = 2^power mod p */
hi_u32 drv_pke_mod_block(const pke_block *a, const pke_mod_block *para, rotate_type rotate);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __DRV_PKE_COMMON_H__ */

