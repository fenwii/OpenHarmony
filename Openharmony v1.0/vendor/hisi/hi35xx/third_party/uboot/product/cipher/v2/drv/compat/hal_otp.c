/*
 * hal_otp.c
 *
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
 * Description   : The OTP Driver
 */

#include "hal_otp.h"
#include "cipher_adapt.h"

#ifdef OTP_SUPPORT

typedef enum {
	OTP_USER_LOCK_STA0_TYPE,
	OTP_USER_LOCK_STA1_TYPE,
	OTP_USER_LOCK_UNKNOWN_STA,
} opt_lock_sta_type_e;

typedef enum {
	OTP_READ_LOCK_STA_MODE,
	OTP_LOCK_CIPHER_KEY_MODE,
	OTP_WRITE_KEY_ID_OR_PASSWD_MODE,
	OTP_KEY_ID_OR_PASSWD_CRC_MODE,
	OTP_SET_FLAG_ENABLE_MODE,
	OTP_WRITE_USER_ROOM_MODE,
	OTP_READ_USER_ROOM_MODE,
	OTP_UNKOOWN_MODE,
} otp_user_work_mode_e;

typedef enum {
	OTP_USER_KEY0,
	OTP_USER_KEY1,
	OTP_USER_KEY2,
	OTP_USER_KEY3,
	OTP_USER_KEY_JTAG_PW_ID,
	OTP_USER_KEY_JTAG_PW,
	OTP_USER_KEY_ROOTKEY,
	OTP_USER_KEY_UNKNOWN,
} otp_user_key_index_e;

typedef enum {
	OTP_KEY_LENGTH_64BIT,
	OTP_KEY_LENGTH_128BIT,
	OTP_KEY_LENGTH_256BIT,
	OTP_KEY_LENGTH_UNSUPPORT,
} otp_user_key_length_e;

hi_void *g_efuse_otp_reg_base = HI_NULL;

/* OTP init */
hi_s32 hal_efuse_otp_init(hi_void)
{
	hi_u32 crg_value = 0;
	hi_u32 *sys_addr = HI_NULL;

	sys_addr = cipher_ioremap_nocache(REG_SYS_OTP_CLK_ADDR_PHY, 0x100);
	if (sys_addr == HI_NULL) {
		hi_err_cipher("ERROR: sys_addr ioremap with nocache failed!!\n");
		return HI_FAILURE;
	}

	hal_cipher_read_reg(sys_addr, &crg_value);
#ifdef OTP_CRG_RESET_SUPPORT
	crg_value |= OTP_CRG_RESET_BIT;   /* reset */
	crg_value |= OTP_CRG_CLOCK_BIT;   /* set the bit 0, clock opened */
	hal_cipher_write_reg(sys_addr, crg_value);

	/* clock select and cancel reset 0x30100 */
	crg_value &= (~OTP_CRG_RESET_BIT); /* cancel reset */
#endif
	crg_value |= OTP_CRG_CLOCK_BIT;   /* set the bit 0, clock opened */
	hal_cipher_write_reg(sys_addr, crg_value);

	cipher_iounmap(sys_addr);
	sys_addr = HI_NULL;

	g_efuse_otp_reg_base = cipher_ioremap_nocache(CIPHER_OTP_REG_BASE_ADDR_PHY, 0x100);
	if (g_efuse_otp_reg_base == HI_NULL) {
		hi_err_cipher("ERROR: osal_ioremap_nocache for OTP failed!!\n");
		return HI_FAILURE;
	}

	return HI_SUCCESS;
}

static hi_s32 hal_otp_wait_free(hi_void)
{
	hi_u32 timeout_cnt = 0;
	hi_u32 reg_value = 0;

	while (1) {
		hal_cipher_read_reg(OTP_USER_CTRL_STA, &reg_value);
		if ((reg_value & 0x1) == 0) /* bit0:otp_op_busy 0:idle, 1:busy */
			return HI_SUCCESS;

		timeout_cnt++;
		if (timeout_cnt >= 10000) { /* 10000 count */
			hi_err_cipher("OTP_WaitFree TimeOut!\n");
			break;
		}
	}
	return HI_FAILURE;
}

static hi_s32 hal_otp_set_mode(otp_user_work_mode_e otp_mode)
{
	hi_u32 reg_value = otp_mode;

	if (otp_mode >= OTP_UNKOOWN_MODE) {
		hi_err_cipher("Mode Unknown!\n");
		return  HI_FAILURE;
	}

	(hi_void)hal_cipher_write_reg(OTP_USER_WORK_MODE, reg_value);
	return HI_SUCCESS;
}

static hi_void hal_otp_op_start(hi_void)
{
	hi_u32 reg_value = 0x1acce551;
	(hi_void)hal_cipher_write_reg(OTP_USER_OP_START, reg_value);
}

static hi_s32 hal_otp_wait_op_done(hi_void)
{
	hi_u32 timeout_cnt = 0;
	hi_u32 reg_value = 0;

	while (1) {
		hal_cipher_read_reg(OTP_USER_CTRL_STA, &reg_value);
		if (reg_value & 0x2) {
			return HI_SUCCESS;
		}

		timeout_cnt++;
		if (timeout_cnt >= 10000) { /* 10000 count */
			hi_err_cipher("OTP_Wait_OP_done TimeOut!\n");
			break;
		}
	}
	return HI_FAILURE;
}

static hi_void hal_choose_otp_key(otp_user_key_index_e which_key)
{
	hi_u32 reg_value;

	reg_value = which_key;
	(hi_void)hal_cipher_write_reg(OTP_USER_KEY_INDEX, reg_value);
}

/* set otp key to klad */
hi_s32 hal_efuse_otp_load_cipher_key(hi_u32 chn_id, hi_u32 opt_id)
{
	if (opt_id > OTP_USER_KEY3)
		opt_id = OTP_USER_KEY0;

	if (HI_FAILURE == hal_otp_wait_free())
		return HI_FAILURE;
	hal_choose_otp_key(opt_id);

	if (hal_otp_set_mode(OTP_LOCK_CIPHER_KEY_MODE))
		return HI_FAILURE;

	hal_otp_op_start();

	if (HI_FAILURE == hal_otp_wait_op_done())
		return HI_FAILURE;

	return  HI_SUCCESS;
}
#endif

