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

#include "hi_mpi_otp.h"
#include "sys_otp.h"
#include "user_osal_lib.h"
#include "drv_ioctl_otp.h"

static hi_s32 g_otp_init_counter = -1;
hi_s32 g_otp_dev_fd = -1;

#define OTP_INIT_MAX_NUM     0x7FFFFFFF

#define mpi_check_otp_not_init() \
    do { \
        if (g_otp_dev_fd < 0) { \
            hi_otp_err("otp module isn't init!\n"); \
            return HI_ERR_OTP_NOT_INIT; \
        } \
    } while (0)

hi_s32 hi_mpi_otp_init(hi_void)
{
    if (g_otp_init_counter >= OTP_INIT_MAX_NUM) {
        return HI_ERR_OTP_FAILED_INIT;
    } else if (g_otp_init_counter >= 0) {
        g_otp_init_counter++;
    } else {
        g_otp_dev_fd = otp_open("/dev/"UMAP_DEVNAME_OTP, O_RDWR, 0);
        if (g_otp_dev_fd < 0) {
            hi_otp_err("open device /dev/%s failed\n", UMAP_DEVNAME_OTP);
            return HI_ERR_OTP_FAILED_INIT;
        }
        g_otp_init_counter = 0;
    }

    return HI_SUCCESS;
}

hi_s32 hi_mpi_otp_deinit(hi_void)
{
    if (g_otp_init_counter > 0) {
        g_otp_init_counter--;
    } else if (g_otp_init_counter == 0) {
        if (otp_close(g_otp_dev_fd) != 0) {
            hi_otp_err("close device /dev/%s failed\n", UMAP_DEVNAME_OTP);
            g_otp_dev_fd = -1;
            g_otp_init_counter = -1;
            return HI_ERR_OTP_FAILED_INIT;
        }
        g_otp_dev_fd = -1;
        g_otp_init_counter = -1;
    }

    return HI_SUCCESS;
}

hi_s32 hi_mpi_otp_set_user_data(const hi_char *field_name,
    hi_u32 offset, const hi_u8 *value, hi_u32 value_len)
{
    hi_s32 ret;

    mpi_check_otp_not_init();

    hi_otp_check_formula_fail(field_name == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(
        strlen(field_name) >= HI_OTP_FIELD_NAME_MAX_LEN, HI_ERR_OTP_INVALID_FIELD_NAME);
    hi_otp_check_formula_fail(value == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(value_len == 0, HI_ERR_OTP_INVALID_PARAM);

    ret = sys_otp_set_user_data(field_name, offset, value, value_len);
    hi_otp_func_fail_return(sys_otp_set_user_data, ret != HI_SUCCESS, ret);

    return ret;
}

hi_s32 hi_mpi_otp_get_user_data(const hi_char *field_name,
    hi_u32 offset, hi_u8 *value, hi_u32 value_len)
{
    hi_s32 ret;

    mpi_check_otp_not_init();

    hi_otp_check_formula_fail(field_name == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(
        strlen(field_name) >= HI_OTP_FIELD_NAME_MAX_LEN, HI_ERR_OTP_INVALID_FIELD_NAME);
    hi_otp_check_formula_fail(value == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(value_len == 0, HI_ERR_OTP_INVALID_PARAM);

    ret = sys_otp_get_user_data(field_name, offset, value, value_len);
    hi_otp_func_fail_return(sys_otp_get_user_data, ret != HI_SUCCESS, ret);

    return ret;
}

hi_s32 hi_mpi_otp_burn_product_pv(const hi_otp_burn_pv_item *pv, hi_u32 num)
{
    hi_s32 ret;
    hi_u32 i;

    mpi_check_otp_not_init();

    hi_otp_check_formula_fail(pv == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(num == 0 || num > OTP_PRODUCT_PV_MAX_NUM, HI_ERR_OTP_INVALID_PARAM);

    for (i = 0; i < num; i++) {
        hi_otp_check_formula_fail(
            strlen(pv[i].field_name) >= HI_OTP_FIELD_NAME_MAX_LEN, HI_ERR_OTP_INVALID_FIELD_NAME);
        hi_otp_check_formula_fail(pv[i].burn != HI_TRUE, HI_ERR_OTP_INVALID_PARAM);
        hi_otp_check_formula_fail(pv[i].value_len == 0, HI_ERR_OTP_INVALID_PARAM);
        hi_otp_check_formula_fail(pv[i].lock != HI_TRUE && pv[i].lock != HI_FALSE, HI_ERR_OTP_INVALID_PARAM);
    }

    ret = sys_otp_burn_product_pv(pv, num);
    hi_otp_func_fail_return(sys_otp_burn_product_pv, ret != HI_SUCCESS, ret);

    return ret;
}

hi_s32 hi_mpi_otp_read_product_pv(hi_otp_burn_pv_item *pv, hi_u32 num)
{
    hi_s32 ret;
    hi_u32 i;

    mpi_check_otp_not_init();

    hi_otp_check_formula_fail(pv == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(num == 0 || num > OTP_PRODUCT_PV_MAX_NUM, HI_ERR_OTP_INVALID_PARAM);

    for (i = 0; i < num; i++) {
        hi_otp_check_formula_fail(
            strlen(pv[i].field_name) >= HI_OTP_FIELD_NAME_MAX_LEN, HI_ERR_OTP_INVALID_FIELD_NAME);
        hi_otp_check_formula_fail(pv[i].burn != HI_FALSE, HI_ERR_OTP_INVALID_PARAM);
        hi_otp_check_formula_fail(pv[i].value_len == 0, HI_ERR_OTP_INVALID_PARAM);
    }

    ret = sys_otp_read_product_pv(pv, num);
    hi_otp_func_fail_return(sys_otp_read_product_pv, ret != HI_SUCCESS, ret);

    return ret;
}

hi_s32 hi_mpi_otp_get_key_verify_status(const hi_char *key_name, hi_bool *status)
{
    hi_s32 ret;

    mpi_check_otp_not_init();

    hi_otp_check_formula_fail(key_name == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(
        strlen(key_name) >= HI_OTP_FIELD_NAME_MAX_LEN, HI_ERR_OTP_INVALID_FIELD_NAME);
    hi_otp_check_formula_fail(status == HI_NULL, HI_ERR_OTP_NULL_PTR);

    ret = sys_otp_get_key_verify_status(key_name, status);
    hi_otp_func_fail_return(sys_otp_get_key_verify_status, ret != HI_SUCCESS, ret);

    return ret;
}


