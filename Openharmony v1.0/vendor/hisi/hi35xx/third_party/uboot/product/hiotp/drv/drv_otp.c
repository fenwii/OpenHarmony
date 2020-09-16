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
 */

#include "drv_otp.h"
#include "drv_osal_lib.h"
#include "hal_otp.h"
#include "drv_osal_chip.h"

#define hal_otp_read_sta0(sta)              hal_otp_read_word(OTP_USER_LOCK_STA0, sta)
#define hal_otp_read_rev_data(data)         hal_otp_read_word(OTP_USER_REV_RDATA, data)

#define hal_otp_set_rev_addr(offset)        hal_otp_write_word(OTP_USER_REV_ADDR, offset)
#define hal_otp_set_rev_data(data)          hal_otp_write_word(OTP_USER_REV_WDATA, data)
#define hal_otp_set_work_mode(mode)         hal_otp_write_word(OTP_USER_WORK_MODE, mode)
#define hal_otp_set_key_index(idx)          hal_otp_write_word(OTP_USER_KEY_INDEX, idx);
#define hal_otp_set_flag_index(idx)         hal_otp_write_word(OTP_USER_FLAG_INDEX, idx);
#define hal_otp_set_flag_value(value)       hal_otp_write_word(OTP_USER_FLAG_VALUE, value);
#define hal_otp_op_start()                  hal_otp_write_word(OTP_USER_OP_START, OTP_OP_START_VAL)

static hi_s32 hal_otp_wait_op_free(hi_void)
{
    hi_s32 ret;
    hi_u32 time_out_cnt = OTP_WAIT_TIME_OUT;
    hi_u32 sta;

    while (time_out_cnt--) {
        ret = hal_otp_read_word(OTP_USER_CTRL_STA, &sta);
        hi_otp_func_fail_return(hal_otp_read_word, ret != HI_SUCCESS, ret);

        if (((sta >> OTP_CTRL_STA_OP_BUSY) & 0x01) == 0) {
            return HI_SUCCESS;
        }
    }
    hi_otp_err("otp wait op timeout!\n");
    return HI_ERR_OTP_BUSY;
}

/*
 * if you want flag, please ensure that (offset != OTP_CTRL_STA_INVALID && flag != HI_NULL)
 */
static hi_s32 hal_otp_wait_cmd_finish(otp_user_ctrl_sta offset, hi_bool *flag)
{
    hi_s32 ret;
    hi_u32 time_out_cnt = OTP_WAIT_TIME_OUT;
    hi_u32 sta;

    while (time_out_cnt--) {
        ret = hal_otp_read_word(OTP_USER_CTRL_STA, &sta);
        hi_otp_func_fail_return(hal_otp_read_word, ret != HI_SUCCESS, ret);

        if (((sta >> OTP_CTRL_STA_USER_CMD_FINISH) & 0x01) == 1) {
            break;
        }
    }

    if (time_out_cnt == 0) {
        hi_otp_err("otp wait op timeout!\n");
        return HI_ERR_OTP_WAIT_TIMEOUT;
    }

    if (offset != OTP_CTRL_STA_INVALID && flag != HI_NULL) {
        *flag = ((sta >> (hi_u32)offset) & 0x01);
    }

    return HI_SUCCESS;
}

hi_s32 hal_otp_get_user_lock_sta0(hi_u32 *sta0)
{
    hi_s32 ret;

    hi_otp_enter();

    /* 1. wait otp ctrl free */
    ret = hal_otp_wait_op_free();
    hi_otp_func_fail_return(hal_otp_wait_op_free, ret != HI_SUCCESS, ret);

    /* 2. set work mode to read lock sta */
    hal_otp_set_work_mode(OTP_WORK_MODE_READ_LOCK_STA);

    /* 3. start otp ctrl */
    hal_otp_op_start();

    /* 4. wait user cmd finish */
    ret = hal_otp_wait_cmd_finish(OTP_CTRL_STA_INVALID, HI_NULL);
    hi_otp_func_fail_return(hal_otp_wait_cmd_finish, ret != HI_SUCCESS, ret);

    /* 5. read lock sta */
    hal_otp_read_sta0(sta0);

    hi_otp_exit();

    return ret;
}

/*
 * Note:
 * write key: Writes key from a high address to a low address by word
 * calculate crc: calculate crc according to the key write sequence by byte
 */
hi_s32 hal_otp_write_key_data(const hi_u8 *u8_key, hi_u32 u8_klen)
{
    hi_s32 ret;
    hi_u32 u32_key[OTP_USER_KEY_MAX_WORDS];
    hi_u8 u8_tmp[OTP_USER_KEY_MAX_BYTES];
    hi_u32 crc, i, u32_klen;

    hi_otp_check_formula_fail(!align_word(u8_klen), HI_ERR_OTP_INVALID_PARAM);

    (hi_void)otp_memset(u32_key, sizeof(u32_key), 0, sizeof(u32_key));
    (hi_void)otp_memset(u8_tmp, sizeof(u8_tmp), 0, sizeof(u8_tmp));

    hi_otp_print_arr_u8("u8_key", u8_key, u8_klen);

    u32_klen = u8_klen / WORD_BYTE_WIDTH;

    ret = otp_memcpy((hi_u8 *)u32_key, sizeof(u32_key), u8_key, u8_klen);
    hi_otp_func_fail_return(otp_memcpy, ret != EOK, HI_ERR_OTP_FAILED_SEC_FUNC);

    for (i = 0; i < u32_klen; i++) {
        hal_otp_write_word(OTP_USER_KEY_DATA0 + i * WORD_BYTE_WIDTH, u32_key[i]);

        ret = hi_otp_word_big_endian(u32_key[i], &u8_tmp[i * WORD_BYTE_WIDTH], WORD_BYTE_WIDTH);
        hi_otp_func_fail_return(hi_otp_word_big_endian, ret != HI_SUCCESS, ret);
    }
    hi_otp_print_arr_u8("u8_tmp", u8_tmp, u8_klen);

    crc = (0x0000ffff & hi_otp_crc16_modbus(u8_tmp, u8_klen));
    hal_otp_write_word(OTP_USER_KEY_DATA0 + i * WORD_BYTE_WIDTH, crc);

    hi_otp_info("crc value %x\n", crc);

    return HI_SUCCESS;
}

static hi_s32 hal_otp_check_key_sta(otp_user_key_index key_index, hi_u32 key_len)
{
    hi_s32 ret;
    otp_user_lock_sta0 sta0;

    ret = hal_otp_get_user_lock_sta0(&sta0.u32);
    hi_otp_func_fail_return(hal_otp_get_user_lock_sta0, ret != HI_SUCCESS, ret);

    if ((key_index == OTP_USER_KEY0 && sta0.bits.key0_lock == 1) ||
        (key_index == OTP_USER_KEY1 && sta0.bits.key1_lock == 1) ||
        (key_index == OTP_USER_KEY2 && sta0.bits.key2_lock == 1) ||
        (key_index == OTP_USER_KEY3 && sta0.bits.key3_lock == 1) ||
        (key_index == OTP_USER_KEY_JTAG_PW_ID && sta0.bits.jtag_pw_id_lock == 1) ||
        (key_index == OTP_USER_KEY_JTAG_PW && sta0.bits.jtag_pw_lock == 1) ||
        (key_index == OTP_USER_KEY_ROOTKEY && sta0.bits.root_key_lock == 1) ||
        (key_index == OTP_USER_KEY_HMACKEY && sta0.bits.hmac_key_lock == 1)) {
        hi_otp_err("key slot %u had locked, sta0 %08x\n", key_index, sta0.u32);
        return HI_ERR_OTP_ZONE_ALREADY_SET;
    }
    return HI_SUCCESS;
}

hi_s32 hal_otp_burn_key(const hi_otp_burn_pv_item *pv_item, const otp_data_item *data_item)
{
    hi_s32 ret;

    hi_otp_enter();

    /* 1. check user key status */
    ret = hal_otp_check_key_sta(data_item->index, pv_item->value_len);
    hi_otp_func_fail_return(hal_otp_check_key_sta, ret != HI_SUCCESS, ret);

    /* 2. wait otp ctrl free */
    ret = hal_otp_wait_op_free();
    hi_otp_func_fail_return(hal_otp_wait_op_free, ret != HI_SUCCESS, ret);

    /* 3. set user key index */
    hal_otp_set_key_index(data_item->index);

    /* 4. write key data */
    ret = hal_otp_write_key_data(pv_item->value, pv_item->value_len);
    hi_otp_func_fail_return(hal_otp_write_key_data, ret != HI_SUCCESS, ret);

    /* 5. set work mode */
    hal_otp_set_work_mode(OTP_WORK_MODE_BURN_KEY);

    /* 6. start otp ctrl */
    hal_otp_op_start();

    /* 7. wait user cmd finish */
    ret = hal_otp_wait_cmd_finish(OTP_CTRL_STA_INVALID, HI_NULL);
    hi_otp_func_fail_return(hal_otp_wait_cmd_finish, ret != HI_SUCCESS, ret);

    hi_otp_exit();

    return ret;
}

hi_s32 hal_otp_verify_key(otp_user_key_index key_index, hi_bool *flag)
{
    hi_s32 ret;

    hi_otp_enter();

    /* 1. wait otp ctrl free */
    ret = hal_otp_wait_op_free();
    hi_otp_func_fail_return(hal_otp_wait_op_free, ret != HI_SUCCESS, ret);

    /* 2. set key index */
    hal_otp_set_key_index(key_index);

    /* 3. set work mode to verify key crc */
    hal_otp_set_work_mode(OTP_WORK_MODE_VERIFY_KEY_CRC);

    /* 4. start otp ctrl */
    hal_otp_op_start();

    /* 5. wait user cmd finish & check key crc flag */
    ret = hal_otp_wait_cmd_finish(OTP_CTRL_STA_KEY_CRC_CHECK_OK_FLAG, flag);
    hi_otp_func_fail_return(hal_otp_wait_cmd_finish, ret != HI_SUCCESS, ret);

    if (*flag == 1) {
        hi_otp_info("verify key crc %d ok\n", key_index);
    } else {
        hi_otp_info("verify key crc %d failed\n", key_index);
    }

    hi_otp_exit();

    return ret;
}

hi_s32 hal_otp_load_key_to_klad(otp_user_key_index key_index)
{
    hi_s32 ret;

    hi_otp_enter();

    /* 1. wait otp ctrl free */
    ret = hal_otp_wait_op_free();
    hi_otp_func_fail_return(hal_otp_wait_op_free, ret != HI_SUCCESS, ret);

    /* 2. set key index */
    hal_otp_set_key_index(key_index);

    /* 3. set work mode to load key */
    hal_otp_set_work_mode(OTP_WORK_MODE_LOAD_CIPHER_KEY);

    /* 4. start otp ctrl */
    hal_otp_op_start();

    /* 5. wait user cmd finish */
    ret = hal_otp_wait_cmd_finish(OTP_CTRL_STA_INVALID, HI_NULL);
    hi_otp_func_fail_return(hal_otp_wait_cmd_finish, ret != HI_SUCCESS, ret);

    hi_otp_exit();

    return ret;
}

static hi_s32 hal_otp_check_flag_sta(otp_user_flag_index flag_index)
{
    hi_s32 ret;
    otp_user_lock_sta0 sta0;

    ret = hal_otp_get_user_lock_sta0(&sta0.u32);
    hi_otp_func_fail_return(hal_otp_get_user_lock_sta0, ret != HI_SUCCESS, ret);

    if ((flag_index == OTP_USER_FLAG_SECURE_BOOT_EN && sta0.bits.secure_boot_en_lock == 1) ||
        (flag_index == OTP_USER_FLAG_DDR_CA_EN && sta0.bits.ddr_ca_en_lock == 1) ||
        (flag_index == OTP_USER_FLAG_JTAG_CA_EN && sta0.bits.jtag_ca_en_lock == 1) ||
        (flag_index == OTP_USER_FLAG_JTAG_PRT_MODE && sta0.bits.jtag_prt_mode_lock == 1) ||
        (flag_index == OTP_USER_FLAG_UBOOT_REDUNDANCE && sta0.bits.uboot_redundance_lock == 1)) {
        hi_otp_err("flag %u had locked!!!\n", flag_index);
        return HI_ERR_OTP_ZONE_ALREADY_SET;
    }

    return HI_SUCCESS;
}

hi_s32 hal_otp_write_flag_value(otp_user_flag_index flag_index, hi_u32 value, hi_u32 lock)
{
    otp_user_flag_value flag_value;

    flag_value.u32 = 0;

    if (flag_index == OTP_USER_FLAG_JTAG_PRT_MODE) {
        hi_otp_check_formula_fail(value > 0x03, HI_ERR_OTP_INVALID_PARAM);

        flag_value.bits.jtag_prt_mode = value;
        if (lock == HI_TRUE) {
            flag_value.bits.jtag_prt_mode_lock_en = 1;
        }
    } else {
        hi_otp_check_formula_fail(value > 0x01, HI_ERR_OTP_INVALID_PARAM);
        switch (flag_index) {
            case OTP_USER_FLAG_SECURE_BOOT_EN:
                flag_value.bits.secure_boot_en = value;
                break;
            case OTP_USER_FLAG_DDR_CA_EN:
                flag_value.bits.ddr_ca_en = value;
                break;
            case OTP_USER_FLAG_JTAG_CA_EN:
                flag_value.bits.jtag_ca_en = value;
                break;
            case OTP_USER_FLAG_UBOOT_REDUNDANCE:
                flag_value.bits.uboot_redundance = value;
                break;
            default:
                hi_otp_err("flag index %d is invalid\n", flag_index);
                return HI_ERR_OTP_INVALID_PARAM;
        }
    }
    hal_otp_set_flag_value(flag_value.u32);

    return HI_SUCCESS;
}

hi_s32 hal_otp_enable_flag(const hi_otp_burn_pv_item *pv_item, const otp_data_item *data_item)
{
    hi_s32 ret;

    hi_otp_enter();

    /* 1. check flag status */
    ret = hal_otp_check_flag_sta(data_item->index);
    hi_otp_func_fail_return(hal_otp_check_flag_sta, ret != HI_SUCCESS, ret);

    /* 2. wait otp ctrl free */
    ret = hal_otp_wait_op_free();
    hi_otp_func_fail_return(hal_otp_wait_op_free, ret != HI_SUCCESS, ret);

    /* 3. set flag index */
    hal_otp_set_flag_index(data_item->index);

    /* 4. set flag value */
    ret = hal_otp_write_flag_value(data_item->index, pv_item->value[0], pv_item->lock);
    hi_otp_func_fail_return(hal_otp_write_flag_value, ret != HI_SUCCESS, ret);

    /* 5. set work mode to enable flag config */
    hal_otp_set_work_mode(OTP_WORK_MODE_ENABLE_FLAG_CFG);

    /* 6. start otp ctrl */
    hal_otp_op_start();

    /* 7. wait user cmd finish */
    ret = hal_otp_wait_cmd_finish(OTP_CTRL_STA_INVALID, HI_NULL);
    hi_otp_func_fail_return(hal_otp_wait_cmd_finish, ret != HI_SUCCESS, ret);

    hi_otp_exit();

    return ret;
}

hi_s32 hal_otp_set_user_data_word(hi_u32 index, hi_u32 value)
{
    hi_s32 ret;
    hi_bool lock;

    /* 1. wait otp ctrl free */
    ret = hal_otp_wait_op_free();
    hi_otp_func_fail_return(hal_otp_wait_op_free, ret != HI_SUCCESS, ret);

    /* 2. set rev addr */
    hal_otp_set_rev_addr(index);

    /* 3. write rev data */
    hal_otp_set_rev_data(value);

    /* 4. set work mode to write user room */
    hal_otp_set_work_mode(OTP_WORK_MODE_WRITE_USER_ROOM);

    /* 5. start otp ctrl */
    hal_otp_op_start();

    /* 6. wait user cmd finish */
    ret = hal_otp_wait_cmd_finish(OTP_CTRL_STA_USER_LOCK_ERR, &lock);
    hi_otp_func_fail_return(hal_otp_wait_cmd_finish, ret != HI_SUCCESS, ret);

    if (lock == 1) {
        hi_otp_err("index %u has locked\n", index);
        return HI_ERR_OTP_ZONE_LOCKED;
    }
    return ret;
}

hi_s32 hal_otp_get_user_data_word(hi_u32 index, hi_u32 *value)
{
    hi_s32 ret;

    /* 1. wait otp ctrl free */
    ret = hal_otp_wait_op_free();
    hi_otp_func_fail_return(hal_otp_wait_op_free, ret != HI_SUCCESS, ret);

    /* 2. set rev addr */
    hal_otp_set_rev_addr(index);

    /* 3. set work mode to read user room */
    hal_otp_set_work_mode(OTP_WORK_MODE_READ_USER_ROOM);

    /* 4. start otp ctrl */
    hal_otp_op_start();

    /* 5. wait user cmd finish */
    ret = hal_otp_wait_cmd_finish(OTP_CTRL_STA_INVALID, HI_NULL);
    hi_otp_func_fail_return(hal_otp_wait_cmd_finish, ret != HI_SUCCESS, ret);

    /* 6. read rev data */
    hal_otp_read_rev_data(value);

    return ret;
}

otp_data_item *drv_otp_match_field_name(const hi_char *field_name)
{
    hi_u32 i;

    for (i = 0; i < array_size(g_otp_data_item); i++) {
        if ((strlen(field_name) != strlen(g_otp_data_item[i].field_name)) ||
            (memcmp(g_otp_data_item[i].field_name, field_name, strlen(field_name)) != 0)) {
                continue;
        }

        hi_otp_log("match %d field name %s\n", i, field_name);
        return &g_otp_data_item[i];
    }
    hi_otp_err("field name %s don't match\n", field_name);
    return HI_NULL;
}

hi_s32 drv_otp_set_user_data(const hi_char *field_name,
    hi_u32 offset, const hi_u8 *value, hi_u32 value_len)
{
    hi_s32 ret;
    hi_u32 *word = HI_NULL;
    hi_u32 i, word_len, byte_len;
    const otp_data_item *item = HI_NULL;

    hi_otp_enter();

    hi_otp_check_formula_fail(field_name == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(value == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(value_len == 0, HI_ERR_OTP_INVALID_PARAM);
    hi_otp_check_formula_fail(!align_word(offset), HI_ERR_OTP_INVALID_PARAM);

    /* match field name */
    item = drv_otp_match_field_name(field_name);
    hi_otp_func_fail_return(drv_otp_match_field_name, item == HI_NULL, HI_ERR_OTP_INVALID_FIELD_NAME);

    /* avoid a + b overflow */
    hi_otp_check_formula_fail(offset + value_len < value_len, HI_ERR_OTP_INVALID_PARAM);

    /* check user name real max size: offset + value_len can't longer than max size */
    hi_otp_check_formula_fail(offset + value_len > item->value_len, HI_ERR_OTP_INVALID_PARAM);

    word_len = word_number(value_len);
    byte_len = word_len * WORD_BYTE_WIDTH;

    word = otp_malloc(byte_len);
    hi_otp_func_fail_return(otp_malloc, word == HI_NULL, HI_ERR_OTP_FAILED_MEM);

    (hi_void)otp_memset(word, byte_len, 0, byte_len);
    ret = otp_memcpy(word, byte_len, value, value_len);
    hi_otp_func_fail_goto(otp_memcpy, ret != EOK, HI_ERR_OTP_FAILED_SEC_FUNC);

    hi_otp_print_arr_u32("set user data", word, word_len);

    if (item->attr & OTP_ATTR_RESERVED_DATA) {
        for (i = 0; i < word_len; i++) {
            ret = hal_otp_set_user_data_word(offset / WORD_BYTE_WIDTH + i, word[i]);
            hi_otp_func_fail_goto(hal_otp_get_user_data_word, ret != HI_SUCCESS, ret);
        }
    } else {
        hi_otp_err("%s don't match attribution %x\n", item->field_name, item->attr);
        ret = HI_ERR_OTP_INVALID_FIELD_NAME;
        goto otp_exit;
    }

otp_exit:
    if (word != HI_NULL) {
        otp_free(word);
        word = HI_NULL;
    }
    hi_otp_exit();
    return ret;
}

hi_s32 drv_otp_get_user_data(const hi_char *field_name,
    hi_u32 offset, hi_u8 *value, hi_u32 value_len)
{
    hi_s32 ret;
    hi_u32 *word = HI_NULL;
    hi_u32 i, word_len, byte_len;
    const otp_data_item *item = HI_NULL;

    hi_otp_enter();

    hi_otp_check_formula_fail(!align_word(offset), HI_ERR_OTP_INVALID_PARAM);
    hi_otp_check_formula_fail(field_name == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(value == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(value_len == 0, HI_ERR_OTP_INVALID_PARAM);

    /* match field name */
    item = drv_otp_match_field_name(field_name);
    hi_otp_func_fail_return(drv_otp_match_field_name, item == HI_NULL, HI_ERR_OTP_INVALID_FIELD_NAME);

    /* avoid a + b overflow */
    hi_otp_check_formula_fail(offset + value_len < value_len, HI_ERR_OTP_INVALID_PARAM);

    /* check user name real max size: offset + value_len can't longer than max size */
    hi_otp_check_formula_fail(offset + value_len > item->value_len, HI_ERR_OTP_INVALID_PARAM);

    word_len = word_number(value_len);
    byte_len = word_len * WORD_BYTE_WIDTH;

    word = otp_malloc(byte_len);
    hi_otp_func_fail_return(otp_malloc, word == HI_NULL, HI_ERR_OTP_FAILED_MEM);

    (hi_void)otp_memset(word, byte_len, 0, byte_len);

    if (item->attr & OTP_ATTR_RESERVED_DATA) {
        for (i = 0; i < word_len; i++) {
            ret = hal_otp_get_user_data_word(offset / WORD_BYTE_WIDTH + i, &word[i]);
            hi_otp_func_fail_goto(hal_otp_get_user_data_word, ret != HI_SUCCESS, ret);
        }
    } else {
        hi_otp_err("%s don't match attribution %x\n", item->field_name, item->attr);
        ret = HI_ERR_OTP_INVALID_FIELD_NAME;
        goto otp_exit;
    }

    ret = otp_memcpy(value, value_len, (hi_u8 *)word, value_len);
    hi_otp_func_fail_goto(otp_memcpy, ret != EOK, HI_ERR_OTP_FAILED_SEC_FUNC);

otp_exit:
    if (word != HI_NULL) {
        otp_free(word);
        word = HI_NULL;
    }
    hi_otp_exit();
    return ret;
}

hi_s32 drv_otp_burn_product_pv(const hi_otp_burn_pv_item *pv, hi_u32 num)
{
    hi_s32 ret;
    hi_u32 i;
    const otp_data_item *item = HI_NULL;

    hi_otp_check_formula_fail(pv == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(num == 0, HI_ERR_OTP_INVALID_PARAM);

    for (i = 0; i < num; i++) {
        item = drv_otp_match_field_name(pv[i].field_name);
        hi_otp_func_fail_return(drv_otp_match_field_name, item == HI_NULL, HI_ERR_OTP_INVALID_FIELD_NAME);

        /* check pv param */
        hi_otp_check_formula_fail(pv[i].burn != HI_TRUE, HI_ERR_OTP_INVALID_PARAM);
        hi_otp_check_formula_fail(pv[i].value_len != item->value_len, HI_ERR_OTP_INVALID_PARAM);
        hi_otp_check_formula_fail(pv[i].lock != HI_TRUE && pv[i].lock != HI_FALSE, HI_ERR_OTP_INVALID_PARAM);

        if (item->attr & OTP_ATTR_BURN_KEY) {
            ret = hal_otp_burn_key(pv, item);
            hi_otp_func_fail_return(hal_otp_burn_key, ret != HI_SUCCESS, ret);
        } else if (item->attr & OTP_ATTR_ENABLE_FLAG) {
            ret = hal_otp_enable_flag(pv, item);
            hi_otp_func_fail_return(hal_otp_enable_flag, ret != HI_SUCCESS, ret);
        } else {
            hi_otp_err("%s don't match attribution %x\n", item->field_name, item->attr);
            return HI_ERR_OTP_INVALID_FIELD_NAME;
        }
    }
    return ret;
}

hi_s32 drv_otp_read_product_pv(hi_otp_burn_pv_item *pv, hi_u32 num)
{
    hi_u32 i;
    const otp_data_item *item = HI_NULL;

    hi_otp_check_formula_fail(pv == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(num == 0, HI_ERR_OTP_INVALID_PARAM);

    for (i = 0; i < num; i++) {
        item = drv_otp_match_field_name(pv[i].field_name);
        hi_otp_func_fail_return(drv_otp_match_field_name, item == HI_NULL, HI_ERR_OTP_INVALID_FIELD_NAME);

        hi_otp_check_formula_fail(pv[i].burn != HI_FALSE, HI_ERR_OTP_INVALID_PARAM);
        hi_otp_check_formula_fail(pv[i].value_len != item->value_len, HI_ERR_OTP_INVALID_PARAM);

        hi_otp_err("%s don't match attribution %x\n", item->field_name, item->attr);
        return HI_ERR_OTP_INVALID_FIELD_NAME;
    }
    return HI_SUCCESS;
}

hi_s32 drv_otp_get_key_verify_status(const hi_char *key_name, hi_bool *status)
{
    hi_s32 ret;
    const otp_data_item *item = HI_NULL;

    hi_otp_check_formula_fail(key_name == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(status == HI_NULL, HI_ERR_OTP_NULL_PTR);

    item = drv_otp_match_field_name(key_name);
    hi_otp_func_fail_return(drv_otp_match_field_name, item == HI_NULL, HI_ERR_OTP_INVALID_FIELD_NAME);

    if (item->attr & OTP_ATTR_VERIFY_KEY) {
        ret = hal_otp_verify_key(item->index, status);
        hi_otp_func_fail_return(hal_otp_verify_key, ret != HI_SUCCESS, ret);
    } else {
        hi_otp_err("%s don't match attribution %x\n", item->field_name, item->attr);
        return HI_ERR_OTP_INVALID_FIELD_NAME;
    }

    return HI_SUCCESS;
}

hi_s32 drv_otp_load_key_to_klad(const hi_char *key_name)
{
    hi_s32 ret;
    const otp_data_item *item = HI_NULL;

    hi_otp_check_formula_fail(key_name == HI_NULL, HI_ERR_OTP_NULL_PTR);

    item = drv_otp_match_field_name(key_name);
    hi_otp_func_fail_return(drv_otp_match_field_name, item == HI_NULL, HI_ERR_OTP_INVALID_FIELD_NAME);

    if (item->attr & OTP_ATTR_LOAD_KEY) {
        ret = hal_otp_load_key_to_klad(item->index);
        hi_otp_func_fail_return(drv_otp_match_field_name, ret != HI_SUCCESS, ret);
    } else {
        hi_otp_err("%s don't match attribution %x\n", item->field_name, item->attr);
        return HI_ERR_OTP_INVALID_FIELD_NAME;
    }

    return ret;
}

