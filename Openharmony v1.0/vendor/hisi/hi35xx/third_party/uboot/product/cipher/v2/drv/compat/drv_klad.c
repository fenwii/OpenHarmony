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
 * Description   : drivers for klad.
 */

#include "cipher_adapt.h"
#include "hal_otp.h"

#define KLAD_REG_BASE_ADDR                      g_klad_base
#define KLAD_REG_KLAD_CTRL                      (KLAD_REG_BASE_ADDR + 0x00)
#define KLAD_REG_DAT_IN                         (KLAD_REG_BASE_ADDR + 0x10)
#define KLAD_REG_ENC_OUT                        (KLAD_REG_BASE_ADDR + 0x20)
#define KLAD_KEY_LEN                            4
#define CIPHER_WAIT_IDEL_TIMES                  1000

static hi_void *g_klad_base = HI_NULL;

static hi_s32 hal_cipher_klad_config(hi_u32 chn_id,
                                     hi_u32 opt_id,
                                     hi_cipher_klad_target klad_target,
                                     hi_bool is_decrypt)
{
    hi_s32 ret;
    hi_u32 ctrl;

    /* Load efuse or OTP key to KLAD */
    ret = hal_efuse_otp_load_cipher_key(chn_id, opt_id);
    if (ret != HI_SUCCESS)
        return ret;

    ctrl  = chn_id << 16;               /* 16: klad channel id */
    ctrl |= (hi_u32)klad_target << 2;   /* 2: cipher klad */
    ctrl |= (hi_u32)is_decrypt << 1;    /* decrypt */
    ctrl |= 0x00;                       /* start */

    (hi_void)hal_cipher_write_reg(KLAD_REG_KLAD_CTRL, ctrl);

    return HI_SUCCESS;
}

static hi_void hal_cipher_start_klad(void)
{
    hi_u32 ctrl;

    /* start */
    (hi_void)hal_cipher_read_reg(KLAD_REG_KLAD_CTRL, &ctrl);
    ctrl |= 0x01;
    (hi_void)hal_cipher_write_reg(KLAD_REG_KLAD_CTRL, ctrl);
}

static hi_void hal_cipher_set_klad_data(hi_u32 *data_input, hi_u32 data_len)
{
    hi_u32 i;

    for (i = 0; i < data_len; i++)
        (hi_void)hal_cipher_write_reg(KLAD_REG_DAT_IN + i * KLAD_KEY_LEN, data_input[i]);
}

static hi_void hal_cipher_get_klad_data(hi_u32 *data_output)
{
    hi_u32 i;

    for (i = 0; i < KLAD_KEY_LEN; i++)
        (hi_void)hal_cipher_read_reg(KLAD_REG_ENC_OUT + i * KLAD_KEY_LEN, &data_output[i]);
}

static hi_s32 hal_cipher_wait_klad_done(void)
{
    hi_u32 try_count = 0;
    hi_u32 ctrl;

    do {
        hal_cipher_read_reg(KLAD_REG_KLAD_CTRL, &ctrl);
        if ((ctrl & 0x01) == 0x00)
            return HI_SUCCESS;
        try_count++;
    } while (try_count < CIPHER_WAIT_IDEL_TIMES);

    hi_err_cipher("Klad time out!\n");

    return HI_FAILURE;
}

static hi_void hal_klad_init(hi_void)
{
    hi_u32 crg_value;
    hi_u32 *sys_addr;

    sys_addr = cipher_ioremap_nocache(CIPHER_KLAD_CRG_ADDR_PHY, 0x100);
    if (sys_addr == HI_NULL) {
        hi_err_cipher("ERROR: sys_addr ioremap with nocache failed!!\n");
        return ;
    }

    hal_cipher_read_reg(sys_addr, &crg_value);
    crg_value |= KLAD_CRG_RESET_BIT;   /* reset */
    crg_value |= KLAD_CRG_CLOCK_BIT;   /* set the bit 0, clock opened */
    hal_cipher_write_reg(sys_addr, crg_value);

    /* clock select and cancel reset 0x30100 */
    crg_value &= (~KLAD_CRG_RESET_BIT); /* cancel reset */
    crg_value |= KLAD_CRG_CLOCK_BIT;    /* set the bit 0, clock opened */
    hal_cipher_write_reg(sys_addr, crg_value);

    cipher_iounmap(sys_addr);
}

hi_s32 drv_klad_init(hi_void)
{
    hi_s32 ret;

    g_klad_base = cipher_ioremap_nocache(CIPHER_KLAD_REG_BASE_ADDR_PHY, 0x100);
    if (g_klad_base == HI_NULL) {
        hi_err_cipher("ERROR: osal_ioremap_nocache for KLAD failed!!\n");
        return HI_FAILURE;
    }

    ret = hal_efuse_otp_init();
    if (ret != HI_SUCCESS) {
        cipher_iounmap(g_klad_base);
        return ret;
    }

    hal_klad_init();

    return HI_SUCCESS;
}

hi_void drv_klad_deinit(hi_void)
{
    if (g_klad_base != HI_NULL) {
        cipher_iounmap(g_klad_base);
        g_klad_base = HI_NULL;
    }
    if (g_efuse_otp_reg_base != HI_NULL) {
        cipher_iounmap(g_efuse_otp_reg_base);
        g_efuse_otp_reg_base = HI_NULL;
    }
    return ;
}

static hi_void drv_cipher_invbuf(hi_u8 *buf, hi_u32 u32len)
{
    hi_u32 i;
    hi_u8 ch;

    for (i = 0; i < u32len / 2; i++) { /* 2 */
        ch = buf[i];
        buf[i] = buf[u32len - i - 1];
        buf[u32len - i - 1] = ch;
    }
}

hi_s32 drv_cipher_klad_load_key(hi_u32 chn_id,
                                hi_cipher_ca_type root_key,
                                hi_cipher_klad_target klad_target,
                                hi_u8 *data_input,
                                hi_u32 key_len)
{
    hi_s32 ret;
    hi_u32 i, opt_id;
    hi_u32 key[KLAD_KEY_LEN] = {0};

    crypto_memset(key, sizeof(key), 0, sizeof(key));

    if ((root_key < HI_CIPHER_KEY_SRC_KLAD_1) ||
        (root_key > HI_CIPHER_KEY_SRC_KLAD_3)) {
        hi_err_cipher("Error: Invalid Root Key src 0x%x!\n", root_key);
        return HI_FAILURE;
    }

    if (((key_len % 16) != 0) || (key_len == 0)) { /* key 16 align */
        hi_err_cipher("Error: Invalid key len 0x%x!\n", key_len);
        return HI_FAILURE;
    }

    opt_id = root_key - HI_CIPHER_KEY_SRC_KLAD_1 + 1;

    ret = hal_cipher_klad_config(chn_id, opt_id, klad_target, HI_TRUE);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("Error: cipher klad config failed!\n");
        return HI_FAILURE;
    }

    for (i = 0; i < key_len / 16; i++) { /* key 16 align */
        crypto_memcpy(key, 16, data_input + i * 16, 16); /* key 16 align */
        hal_cipher_set_klad_data(key, KLAD_KEY_LEN);
        hal_cipher_start_klad();
        ret = hal_cipher_wait_klad_done();
        if (ret != HI_SUCCESS) {
            hi_err_cipher("Error: cipher klad wait done failed!\n");
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;

}

hi_s32 drv_cipher_klad_encrypt_key(hi_cipher_ca_type root_key,
    hi_cipher_klad_target klad_target, hi_u32 *clean_key, hi_u32 *encrypt_key)
{
    hi_s32 ret;
    hi_u32 opt_id;

    if ((root_key < HI_CIPHER_KEY_SRC_KLAD_1) ||
        (root_key >= HI_CIPHER_KEY_SRC_BUTT)) {
        hi_err_cipher("Error: Invalid Root Key src 0x%x!\n", root_key);
        return HI_FAILURE;
    }

    if ((clean_key == HI_NULL) || (encrypt_key == HI_NULL)) {
        hi_err_cipher("Clean key or encrypt key is null.\n");
        return HI_FAILURE;
    }

    opt_id = root_key - HI_CIPHER_KEY_SRC_KLAD_1 + 1;

    ret = hal_cipher_klad_config(0, opt_id, HI_CIPHER_KLAD_TARGET_AES, HI_FALSE);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("Error: cipher klad config failed!\n");
        return HI_FAILURE;
    }

    if (klad_target == HI_CIPHER_KLAD_TARGET_RSA)
        drv_cipher_invbuf((hi_u8*)clean_key, 16); /* 16 clean key len */

    hal_cipher_set_klad_data(clean_key, KLAD_KEY_LEN);
    hal_cipher_start_klad();
    ret = hal_cipher_wait_klad_done();
    if (ret != HI_SUCCESS) {
        hi_err_cipher("Error: cipher klad wait done failed!\n");
        return HI_FAILURE;
    }
    hal_cipher_get_klad_data(encrypt_key);

    return HI_SUCCESS;
}

