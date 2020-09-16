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
 * Description   : drivers for rsa
 */

#include "cipher_adapt.h"
#include "drv_rng.h"
#include "drv_klad.h"

#ifdef RSA_ENABLE

CIPHER_MUTEX g_rsa_mutex_kernel;
static hi_void *g_rsa_reg_base  = HI_NULL;
static hi_void *g_rsa_reg_crg   = HI_NULL;
static hi_u32   g_rsa_done      = HI_FALSE;

#define cipher_rsa_return_invalid_param(param) \
    do { \
        if (param) { \
            hi_err_cipher("Invalid params!\n"); \
            return HI_ERR_CIPHER_INVALID_PARA; \
        } \
    } while (0)

#define RSA_INTERRUPT_ENABLE
#define RSA_IRQ_NUMBER                          136

#define CIPHER_RSA_REG_BASE_RSA                   g_rsa_reg_base
#define SEC_RSA_BUSY_REG                          (CIPHER_RSA_REG_BASE_RSA + 0x50)
#define SEC_RSA_MOD_REG                           (CIPHER_RSA_REG_BASE_RSA + 0x54)
#define SEC_RSA_WSEC_REG                          (CIPHER_RSA_REG_BASE_RSA + 0x58)
#define SEC_RSA_WDAT_REG                          (CIPHER_RSA_REG_BASE_RSA + 0x5c)
#define SEC_RSA_RPKT_REG                          (CIPHER_RSA_REG_BASE_RSA + 0x60)
#define SEC_RSA_RRSLT_REG                         (CIPHER_RSA_REG_BASE_RSA + 0x64)
#define SEC_RSA_START_REG                         (CIPHER_RSA_REG_BASE_RSA + 0x68)
#define SEC_RSA_ADDR_REG                          (CIPHER_RSA_REG_BASE_RSA + 0x6C)
#define SEC_RSA_ERROR_REG                         (CIPHER_RSA_REG_BASE_RSA + 0x70)
#define SEC_RSA_CRC16_REG                         (CIPHER_RSA_REG_BASE_RSA + 0x74)
#define SEC_RSA_KEY_RANDOM_1                      (CIPHER_RSA_REG_BASE_RSA + 0x7c)
#define SEC_RSA_INT_EN                            (CIPHER_RSA_REG_BASE_RSA + 0x80)
#define SEC_RSA_INT_STATUS                        (CIPHER_RSA_REG_BASE_RSA + 0x84)
#define SEC_RSA_INT_RAW                           (CIPHER_RSA_REG_BASE_RSA + 0x88)
#define SEC_RSA_INT_ERR_CLR                       (CIPHER_RSA_REG_BASE_RSA + 0x8c)
#define SEC_RSA_KEY_RANDOM_2                      (CIPHER_RSA_REG_BASE_RSA + 0x94)
#define SEC_RSA_VERSION                           (CIPHER_RSA_REG_BASE_RSA + 0x90)

#define RSA_DATA_CLR               (7 << 4)
#define RSA_DATA_CLR_KEY           (1 << 4)
#define RSA_DATA_CLR_INPUT         (2 << 4)
#define RSA_DATA_CLR_OUTPUT        (4 << 4)
#define RSA_MOD_SEL                (3 << 0)
#define RSA_MOD_SEL_OPT            (0 << 0)
#define RSA_MOD_SEL_KEY_UPDATA     (1 << 0)
#define RSA_MOD_SEL_RAM_CLAER      (2 << 0)
#define RSA_MOD_SEL_CRC16          (3 << 0)
#define RSA_BUSY                   (1 << 0)
#define RSA_START                  (1 << 0)

#define RSA_RTY_CNT             50000
#define RSA_TIME_OUT            1000

#define RSA_RETRY_CNT           3

#define CRC16_POLYNOMIAL        0x1021

typedef enum {
    CIPHER_RSA_DATA_TYPE_CONTEXT,
    CIPHER_RSA_DATA_TYPE_MODULE,
    CIPHER_RSA_DATA_TYPE_KEY,
} cipher_rsa_data_type_e;

typedef enum {
    CIPHER_RSA_KEY_WIDTH_1K   = 0x00,
    CIPHER_RSA_KEY_WIDTH_2K   = 0x01,
    CIPHER_RSA_KEY_WIDTH_4K   = 0x02,
    CIPHER_RSA_KEY_WIDTH_3K   = 0x03,
    CIPHER_RSA_KEY_WIDTH_BUTT = 0xff,
} cipher_rsa_key_width_e;

static hi_void hal_rsa_start(hi_void)
{
    hal_cipher_write_reg(SEC_RSA_START_REG, 0x05);
}

static hi_s32 hal_rsa_wait_free(hi_void)
{
    hi_u32 value;
    hi_u32 try_count = 0;

    do {
        hal_cipher_read_reg(SEC_RSA_BUSY_REG, &value);
        if ((value & RSA_BUSY) == 0)
            return HI_SUCCESS;
        try_count++;
        cipher_msleep(1);
    } while (try_count < RSA_RTY_CNT);

    return HI_FAILURE;
}

static hi_void hal_rsa_clear_ram(hi_void)
{
    hi_u32 value;

    hal_cipher_read_reg(SEC_RSA_MOD_REG, &value);
    value &= 0x0c;
    value |= RSA_DATA_CLR_INPUT | RSA_DATA_CLR_OUTPUT | RSA_DATA_CLR_KEY | RSA_MOD_SEL_RAM_CLAER;
    hal_cipher_write_reg(SEC_RSA_MOD_REG, value);
}

static hi_void hal_rsa_config_mode(cipher_rsa_key_width_e ken_width)
{
    hi_u32 value;

    value = ((hi_u32)ken_width << 2) | RSA_MOD_SEL_OPT; /* 2 left shift */
    hal_cipher_write_reg(SEC_RSA_MOD_REG, value);
}

static hi_void hal_rsa_write_data(cipher_rsa_data_type_e data_type,
                                  hi_u8 *data,
                                  hi_u32 data_len,
                                  hi_u32 length,
                                  hi_u32 random[2]) /* 2 random size */
{
    hi_u32 *reg = HI_NULL;
    hi_u8 *pos = HI_NULL;
    hi_u32 i, value;
    hi_bool id = 0;

    if (data_type == CIPHER_RSA_DATA_TYPE_CONTEXT)
        reg = SEC_RSA_WDAT_REG;
    else
        reg = SEC_RSA_WSEC_REG;

    pos = data;
    for (i = 0; i < length; i += 4) { /* 4 groups */
        value  = (hi_u32)pos[0];
        value |= ((hi_u32)pos[1]) << 8;  /* 1 index, 8  left shift */
        value |= ((hi_u32)pos[2]) << 16; /* 2 index, 16 left shift */
        value |= ((hi_u32)pos[3]) << 24; /* 3 index, 24 left shift */
        if (data_type != CIPHER_RSA_DATA_TYPE_CONTEXT)
            value ^= random[id];

        hal_cipher_write_reg(reg, value);
        pos += 4; /* 4 groups */
        id = (hi_u32)id ^ 0x01;
    }
}

static hi_void hal_rsa_read_data(hi_u8 *data, hi_u32 data_len, hi_u32 klen)
{
    hi_u32 value;
    hi_u8 *pos = HI_NULL;
    hi_u32 i;

    pos = data;
    for (i = 0; i < klen; i += 4) { /* 4 groups */
        hal_cipher_read_reg(SEC_RSA_RRSLT_REG, &value);
        pos[0] = (hi_u8)(value & 0xFF);
        pos[1] = (hi_u8)((value >> 8) & 0xFF);  /* 1 index, 8  right shift */
        pos[2] = (hi_u8)((value >> 16) & 0xFF); /* 2 index, 16 right shift */
        pos[3] = (hi_u8)((value >> 24) & 0xFF); /* 3 index, 24 right shift */
        pos += 4; /* 4 groups */
    }
}

static hi_u32 hal_rsa_get_error_code(hi_void)
{
    hi_u32 value;

    hal_cipher_read_reg(SEC_RSA_ERROR_REG, &value);

    return value;
}

static hi_void hal_rsa_disable_int(hi_void)
{
    (hi_void)hal_cipher_write_reg(SEC_RSA_INT_EN, 0x00);
}

static hi_void hal_rsa_enable(hi_void)
{
    hi_u32 value;

    hal_cipher_read_reg(g_rsa_reg_crg, &value);
    hal_set_bit(value, 15); /* 15bit clock opened */
    hal_cipher_write_reg(g_rsa_reg_crg, value);
    cipher_msleep(1);

    hal_clear_bit(value, 14); /* 14bit cancel reset */
    hal_cipher_write_reg(g_rsa_reg_crg, value);
    cipher_msleep(1);

#ifdef INT_ENABLE
    hal_rsa_enable_int();
#endif
}

static hi_void hal_rsa_disable(hi_void)
{
    hi_u32 value;

    hal_cipher_read_reg(g_rsa_reg_crg, &value);

    hal_set_bit(value, 14); /* 14bit reset */
    hal_cipher_write_reg(g_rsa_reg_crg, value);
    cipher_msleep(1);

    hal_clear_bit(value, 15); /* 15bit clock closed */
    hal_cipher_write_reg(g_rsa_reg_crg, value);
}

#ifdef RSA_RAND_MASK

static hi_u16 g_crc_table[256]; /* 256 table size */

static hi_void drv_rsa_crc16_init(hi_void)
{
    hi_u16 remainder;
    hi_u16 n, m;
    hi_u16 *table = g_crc_table;

    for (n = 0; n < 256; n++) { /* 256 */
        remainder = (hi_u16)n << 8; /* 8 left shift */
        for (m = 8; m > 0; m--) { /* 8 */
            if (remainder & 0x8000)
                remainder = (remainder << 1) ^ CRC16_POLYNOMIAL;
            else
                remainder = (remainder << 1);
        }
        *(table + n) = remainder;
    }
}

static hi_u16 drv_rsa_crc16_block(hi_u16 crc, hi_u8 block[8], hi_u8 random[8]) /* 8 */
{
    hi_u8 i, j;
    hi_u8 val;

    for (i = 0; i < 2; i++) { /* 2 */
        for (j = 0; j < 4; j++) { /* 4 */
            val = block[i * 4 + 3 - j] ^ random[i * 4 + 3 - j]; /* 4, 3 */
            crc = (crc << 8) ^ g_crc_table[((crc >> 8) ^ val) & 0xFF]; /* 8 right shift */
        }
    }

    return crc;
}

static hi_u16 drv_rsa_key_crc(hi_u8 *rsa_n, hi_u8 *rsa_k, hi_u32 klen, hi_u32 random[2]) /* 2 */
{
    hi_u32 i;
    hi_u16 crc = 0;

    for (i = 0; i < klen; i += 8) /* 8 */
        crc = drv_rsa_crc16_block(crc, rsa_n + i, (hi_u8*)random);

    for (i = 0; i < klen; i += 8) /* 8 */
        crc = drv_rsa_crc16_block(crc, rsa_k + i, (hi_u8*)random);

    return crc;
}
#endif

CIPHER_QUEUE_HEAD g_rsa_wait_queue;
#ifdef INT_ENABLE
static CIPHER_IRQRETURN_T drv_rsa_isr(hi_s32 irq, hi_void *dev_id)
{
    hi_u32 int_stat;

    int_stat = hal_rsa_get_int();

    hi_info_cipher("RSA INT: 0x%x\n", int_stat);

    if (int_stat & 0x01) {
        g_rsa_done = HI_TRUE;
        hi_info_cipher("RSA Done\n");
        cipher_queue_wait_up(&g_rsa_wait_queue);
    }

    hal_rsa_clr_int();

    return CIPHER_IRQ_HANDLED;
}
#endif

hi_s32 drv_rsa_init(hi_void)
{
    hi_u32 rsa_stat = 0;
    hi_u32 rng_stat = 0;
#ifdef INT_ENABLE
    hi_s32 ret;
#endif

    cipher_mutex_init(&g_rsa_mutex_kernel);
    cipher_queue_init(&g_rsa_wait_queue);

    g_rsa_reg_crg = cipher_ioremap_nocache(CIPHER_RSA_CRG_ADDR_PHY, 16); /* 16 */
    if (g_rsa_reg_crg == 0) {
        hi_err_cipher("ioremap_nocache phy addr err:%x.\n", CIPHER_RSA_CRG_ADDR_PHY);
        return HI_FAILURE;
    }

    /* rng reset and clock */
    hal_cipher_read_reg(CIPHER_RNG_CRG_ADDR_PHY, &rng_stat);
    rng_stat |= RNG_CRG_CLOCK_BIT;
    rng_stat &= ~RNG_CRG_RESET_BIT;
    hal_cipher_write_reg(CIPHER_RNG_CRG_ADDR_PHY, rng_stat);
    cipher_msleep(5); /* sleep 5ms */

    /* rsa reset and clock */
    hal_cipher_read_reg(CIPHER_RSA_CRG_ADDR_PHY, &rsa_stat);
    rsa_stat |= RSA_CRG_CLOCK_BIT;
    rsa_stat |= RSA_CRG_RESET_BIT;
    hal_cipher_write_reg(CIPHER_RSA_CRG_ADDR_PHY, rsa_stat);
    cipher_msleep(5); /* sleep 5ms */

    /* rsa cancel reset */
    rsa_stat &= ~RSA_CRG_RESET_BIT;
    hal_cipher_write_reg(CIPHER_RSA_CRG_ADDR_PHY, rsa_stat);

    cipher_iounmap(g_rsa_reg_crg);
    g_rsa_reg_crg = HI_NULL;

    g_rsa_reg_base = cipher_ioremap_nocache(CIPHER_RSA_REG_BASE_ADDR_PHY, 0x1000);
    if (g_rsa_reg_base == HI_NULL) {
        hi_err_cipher("ioremap_nocache rsa Reg failed\n");
        return HI_FAILURE;
    }

#ifdef INT_ENABLE
    /* request irq */
    ret = cipher_request_irq(RSA_IRQ_NUMBER, drv_rsa_isr, "rsa");
    if (ret != HI_SUCCESS) {
        hal_rsa_disable_int();
        hi_err_cipher("Irq request failure, ret=%#x.\n", ret);
        return HI_FAILURE;
    }
    hal_rsa_enable_int();
#endif

#ifdef RSA_RAND_MASK
    drv_rsa_crc16_init();
#endif

    return HI_SUCCESS;
}

hi_void drv_rsa_deinit(hi_void)
{
    hal_rsa_disable_int();

#ifdef INT_ENABLE
    cipher_free_irq(RSA_IRQ_NUMBER, "rsa");
#endif

    if (g_rsa_reg_base != HI_NULL) {
        cipher_iounmap(g_rsa_reg_base);
        g_rsa_reg_base = HI_NULL;
    }
}

static hi_s32 drv_rsa_wait_done(hi_void)
{
#ifdef INT_ENABLE
    if (cipher_queue_wait_timeout(&g_rsa_wait_queue, &g_rsa_done, RSA_TIME_OUT) == 0) {
        hi_err_cipher("RSA time out! \n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
#else
    return hal_rsa_wait_free();
#endif
}

static hi_s32 drv_cipher_check_rsa_data(hi_u8 *rsa_n, hi_u8 *rsa_e, hi_u8 *rsa_mc, hi_u32 length)
{
    hi_u32 i;

    /* formula: rsa_mc > 0 */
    for (i = 0; i < length; i++) {
        if (rsa_mc[i] > 0)
            break;
    }
    if (i >= length) {
        hi_err_cipher("RSA M/C is zero, error!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /* formula: rsa_mc < rsa_n */
    for (i = 0; i < length; i++) {
        if (rsa_mc[i] < rsa_n[i])
            break;
    }
    if (i >= length) {
        hi_err_cipher("RSA M/C is larger than rsa_n, error!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /* formula: rsa_e >= 1 */
    for (i = 0; i < length; i++) {
        if (rsa_e[i] > 0)
            break;
    }
    if (i >= length) {
        hi_err_cipher("RSA D/rsa_e is zero, error!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    return HI_SUCCESS;
}

static hi_s32 drv_cipher_clear_rsa_ram(hi_void)
{
    if (hal_rsa_wait_free() != HI_SUCCESS) {
        hi_err_cipher("RSA is busy and timeout,error!\n");
        return HI_FAILURE;
    }

    g_rsa_done = HI_FALSE;

    hal_rsa_clear_ram();
    hal_rsa_start();

    if (drv_rsa_wait_done() != HI_SUCCESS) {
        hi_err_cipher("RSA is busy and timeout,error!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static hi_u8 g_rsa_n[CIPHER_MAX_RSA_KEY_LEN];
static hi_u8 g_rsa_k[CIPHER_MAX_RSA_KEY_LEN];
static hi_u8 g_rsa_m[CIPHER_MAX_RSA_KEY_LEN];

static hi_void drv_rsa_rand_mask(cipher_rsa_data_s *rsa_data,
                                 hi_u32 key_len,
                                 hi_u32 *random)
{
#ifdef RSA_RAND_MASK
    hi_u16 crc;

    random[0] = drv_cipher_rand();
    random[1] = drv_cipher_rand();
    crc = drv_rsa_key_crc(rsa_data->rsa_n, rsa_data->rsa_k, key_len, random);
    hi_info_cipher("CRC16: 0x%x\n", crc);
    hal_rsa_set_random(random);
    hal_rsa_set_crc(crc);
#endif
}

static hi_s32 drv_rsa_cipher_klad(cipher_rsa_data_s *rsa_data,
                                  hi_u32 key_len,
                                  hi_u32 *random)
{
    hi_s32 ret = HI_SUCCESS;
#ifdef CIPHER_KLAD_SUPPORT
    if (rsa_data->ca_type != HI_CIPHER_KEY_SRC_USER) {
        drv_cipher_klad_load_key(0, rsa_data->ca_type,
            HI_CIPHER_KLAD_TARGET_RSA, rsa_data->rsa_k, rsa_data->rsa_k_len);
        if (ret != HI_SUCCESS) {
            hi_err_cipher("drv_cipher_klad_load_key, error!\n");
            return ret;
        }
    } else {
        hal_rsa_write_data(CIPHER_RSA_DATA_TYPE_KEY, rsa_data->rsa_k,
            rsa_data->rsa_n_len, key_len, random);
    }
#else
    hal_rsa_write_data(CIPHER_RSA_DATA_TYPE_KEY, rsa_data->rsa_k,
        rsa_data->rsa_n_len, key_len, random);
#endif
    return ret;
}

static hi_s32 drv_rsa_key_info(cipher_rsa_data_s *rsa_data,
                               hi_u32 *key_len,
                               cipher_rsa_key_width_e *key_width)
{
    hi_u8 *p = HI_NULL;

    /* Only support the key width of 1024, 2048 and 4096 */
    if (rsa_data->rsa_n_len <= 128) { /* key n size 128 */
        *key_len = 128; /* key n size 128 */
        *key_width = CIPHER_RSA_KEY_WIDTH_1K;
    } else if (rsa_data->rsa_n_len <= 256) { /* key n size 256 */
        *key_len = 256; /* key n size 256 */
        *key_width = CIPHER_RSA_KEY_WIDTH_2K;
    } else if (rsa_data->rsa_n_len <= 384) { /* key n size 384 */
        *key_len = 384; /* key n size 384 */
        *key_width = CIPHER_RSA_KEY_WIDTH_3K;
    } else if (rsa_data->rsa_n_len <= 512) { /* key n size 512 */
        *key_len = 512; /* key n size 512 */
        *key_width = CIPHER_RSA_KEY_WIDTH_4K;
    } else {
        hi_err_cipher("rsa_n_len(0x%x) is invalid\n", rsa_data->rsa_n_len);
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    /* if dataLen < key_len, padding 0 before data */
    p = g_rsa_n + (*key_len - rsa_data->rsa_n_len);
    if (cipher_copy_from_user(p, rsa_data->rsa_n, rsa_data->rsa_n_len)) {
        hi_err_cipher("copy data from user fail!\n");
        return HI_FAILURE;
    }

    p = g_rsa_k + (*key_len - rsa_data->rsa_k_len);
    if (cipher_copy_from_user(p, rsa_data->rsa_k, rsa_data->rsa_k_len)) {
        hi_err_cipher("copy data from user fail!\n");
        return HI_FAILURE;
    }

    p = g_rsa_m + (*key_len - rsa_data->data_len);
    if (cipher_copy_from_user(p, rsa_data->input_data, rsa_data->data_len)) {
        hi_err_cipher("copy data from user fail!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static hi_s32 drv_cipher_calc_rsa_ex(cipher_rsa_data_s *rsa_data,
                                     hi_u32 key_len,
                                     cipher_rsa_key_width_e key_width)
{
    hi_u8 err_cnt;
    hi_s32 ret;
    hi_u32 err_code;
    hi_u64 random = 0;

    ret = drv_cipher_check_rsa_data(rsa_data->rsa_n, rsa_data->rsa_k, rsa_data->input_data, key_len);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("RSA data invalid!\n");
        return ret;
    }

    g_rsa_done = HI_FALSE;

    for (err_cnt = 0; err_cnt < RSA_RETRY_CNT; err_cnt++) {
        hal_rsa_enable();

        ret = hal_rsa_wait_free();
        if (ret != HI_SUCCESS) {
            hi_err_cipher("RSA is busy!\n");
            return ret;
        }

        /* Config Mode */
        hal_rsa_config_mode(key_width);

        drv_rsa_rand_mask(rsa_data, key_len, (hi_u32 *)&random);

        /* Write rsa_n, rsa_e, rsa_m */
        hal_rsa_write_data(CIPHER_RSA_DATA_TYPE_MODULE,
            rsa_data->rsa_n, rsa_data->rsa_n_len, key_len, (hi_u32 *)&random);

        ret = drv_rsa_cipher_klad(rsa_data, key_len, (hi_u32 *)&random);
        if (ret != HI_SUCCESS)
            return ret;

        hal_rsa_write_data(CIPHER_RSA_DATA_TYPE_CONTEXT,
            rsa_data->input_data, rsa_data->rsa_n_len, key_len, (hi_u32 *)&random);

        /* Sart */
        hal_rsa_start();

        ret = drv_rsa_wait_done();
        if (ret != HI_SUCCESS) {
            hi_err_cipher("RSA is busy and timeout,error!\n");
            return ret;
        }

        /* Get result */
        hal_rsa_read_data(rsa_data->output_data, rsa_data->rsa_n_len, key_len);

        if (drv_cipher_clear_rsa_ram() != HI_SUCCESS)
            return HI_FAILURE;

        err_code = hal_rsa_get_error_code();

        hal_rsa_disable();

        if (err_code == 0)
            return HI_SUCCESS;
        else
            continue;
    }

    hi_err_cipher("RSA is err: chipset error code: 0x%x!\n", err_code);
    return HI_FAILURE;
}
#endif

static hi_s32 drv_cipher_calc_rsa(cipher_rsa_data_s *rsa_data)
{
    hi_s32 ret;
    hi_u32 key_len = 0;
    cipher_rsa_data_s cipher_rsa_data;
    cipher_rsa_key_width_e key_width = CIPHER_RSA_KEY_WIDTH_BUTT;

    cipher_rsa_return_invalid_param(rsa_data == HI_NULL);
    cipher_rsa_return_invalid_param(rsa_data->input_data == HI_NULL);
    cipher_rsa_return_invalid_param(rsa_data->output_data == HI_NULL);
    cipher_rsa_return_invalid_param(rsa_data->rsa_n == HI_NULL);
    cipher_rsa_return_invalid_param(rsa_data->rsa_k == HI_NULL);
    cipher_rsa_return_invalid_param(rsa_data->data_len != rsa_data->rsa_n_len);
    cipher_rsa_return_invalid_param(rsa_data->rsa_k_len > rsa_data->rsa_n_len);

    crypto_memset(g_rsa_n, sizeof(g_rsa_n), 0, sizeof(g_rsa_n));
    crypto_memset(g_rsa_k, sizeof(g_rsa_k), 0, sizeof(g_rsa_k));
    crypto_memset(g_rsa_m, sizeof(g_rsa_m), 0, sizeof(g_rsa_m));

    ret = drv_rsa_key_info(rsa_data, &key_len, &key_width);
    if (ret != HI_SUCCESS)
        return ret;

    crypto_memset(&cipher_rsa_data, sizeof(cipher_rsa_data), 0, sizeof(cipher_rsa_data_s));
    cipher_rsa_data.rsa_n = g_rsa_n;
    cipher_rsa_data.rsa_k = g_rsa_k;
    cipher_rsa_data.rsa_n_len = key_len;
    cipher_rsa_data.rsa_k_len = key_len;
    cipher_rsa_data.input_data = g_rsa_m;
    cipher_rsa_data.data_len = key_len;
    cipher_rsa_data.output_data = g_rsa_m;
    cipher_rsa_data.ca_type = rsa_data->ca_type;

    ret = drv_cipher_calc_rsa_ex(&cipher_rsa_data, key_len, key_width);
    if (ret != HI_SUCCESS)
        return HI_FAILURE;

    if (cipher_copy_to_user(rsa_data->output_data,
        g_rsa_m + (key_len - rsa_data->rsa_n_len), rsa_data->rsa_n_len)) {
        hi_err_cipher("copy data to user fail!\n");
        return HI_FAILURE;
    }

    return ret;
}

hi_s32 hi_drv_cipher_calc_rsa(cipher_rsa_data_s *rsa_data)
{
    hi_s32 ret;

    if (rsa_data == HI_NULL) {
        hi_err_cipher("Invalid params!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (cipher_mutex_lock(&g_rsa_mutex_kernel)) {
        hi_err_cipher("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    ret = drv_cipher_calc_rsa(rsa_data);

    cipher_mutex_unlock(&g_rsa_mutex_kernel);

    return ret;
}

