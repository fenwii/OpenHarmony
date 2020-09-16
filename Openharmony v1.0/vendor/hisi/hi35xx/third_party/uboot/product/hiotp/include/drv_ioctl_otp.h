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

#ifndef __DRV_IOCTL_OTP_H__
#define __DRV_IOCTL_OTP_H__

#include <malloc.h>
#include "hi_type.h"
#include "hi_common_otp.h"

#ifdef __cplusplus
extern "C" {
#endif

/* word index number. */
#define WORD_IDX_0                      0
#define WORD_IDX_1                      1
#define WORD_IDX_2                      2
#define WORD_IDX_3                      3
#define WORD_IDX_4                      4
#define WORD_IDX_5                      5
#define WORD_IDX_6                      6
#define WORD_IDX_7                      7

/* byte bit witdh */
#define BYTE_BIT_WIDTH                  8

/* word byte width */
#define WORD_BYTE_WIDTH                 4


/* byte offset */
#define OFFSET_0_BYTE                   0
#define OFFSET_1_BYTE                   8
#define OFFSET_2_BYTE                   16
#define OFFSET_3_BYTE                   24

/* Boundary value 1. */
#define BOUND_VAL_1                     1

/* multiple value */
#define MUL_VAL_1                       1
#define MUL_VAL_2                       2
#define MUL_VAL_3                       3
#define MUL_VAL_4                       4

#define HI_ID_OTP                       98
#define UMAP_DEVNAME_OTP                "hi_otp"
#define UMAP_MIN_MINOR_OTP              50

#define OTP_PRODUCT_PV_MAX_NUM          500

/* ----------- 32/64bits compatibility ----------- */
typedef union {
    hi_void *p;                         /* virtual address */
    const hi_void *cp;                  /* const virtual address */
    unsigned long long phy;             /* physical address */
    unsigned int word[MUL_VAL_2];       /* double word of address */
} compat_addr;

#define addr_h32(addr)          addr.word[WORD_IDX_1]   /* High 32 bit of hi_u64 */
#define addr_l32(addr)          addr.word[WORD_IDX_0]   /* Low 32 bit of hi_u64 */
#define addr_u64(addr)          addr.phy                /* 64 bit of hi_u64 */
#define addr_via(addr)          addr.p                  /* buffer point */
#define addr_via_const(addr)    addr.cp                 /* const buffer point */

#define addr_p_h32(addr)        addr->word[WORD_IDX_1]         /* High 32 bit of hi_u64 */
#define addr_p_l32(addr)        addr->word[WORD_IDX_0]         /* Low 32 bit of hi_u64 */
#define addr_p_u64(addr)        addr->phy                      /* 64 bit of hi_u64 */
#define addr_p_via(addr)        addr->p                        /* buffer point */

/* ----------- IOCTL STRUCT CONFIG ----------- */
typedef struct {
    hi_char field_name[HI_OTP_FIELD_NAME_MAX_LEN];
    hi_u32 offset;
    compat_addr value;
    hi_u32 value_len;
} otp_user_data;

typedef struct {
    compat_addr pv;
    hi_u32 num;
} otp_product_pv;

typedef struct {
    hi_char field_name[HI_OTP_FIELD_NAME_MAX_LEN];
    hi_bool status;
} otp_key_verify_status;

/* ----------- IOCTL CMD CONFIG ----------- */
#define OTP_IOC_NA            0U
#define OTP_IOC_W             1U
#define OTP_IOC_R             2U
#define OTP_IOC_RW            3U

#define otp_ioc(dir, type, nr, size) \
        (((dir) << 30) | ((size) << 16) | ((type) << 8) | ((nr) << 0))

#define otp_ior(nr, size)    otp_ioc(OTP_IOC_R, HI_ID_OTP, (nr), size)
#define otp_iow(nr, size)    otp_ioc(OTP_IOC_W, HI_ID_OTP, (nr), size)
#define otp_iowr(nr, size)   otp_ioc(OTP_IOC_RW, HI_ID_OTP, (nr), size)

#define otp_ioc_dir(cmd)       (((cmd) >> 30) & 0x03)
#define otp_ioc_type(cmd)      (((cmd) >> 8) & 0xFF)
#define otp_ioc_nr(cmd)        (((cmd) >> 0) & 0xFF)
#define otp_ioc_size(cmd)      (((cmd) >> 16) & 0x3FFF)

#define CMD_OTP_SET_USER_DATA           otp_iow (0x00, sizeof(otp_user_data))
#define CMD_OTP_GET_USER_DATA           otp_iowr(0x01, sizeof(otp_user_data))
#define CMD_OTP_BURN_PRODUCT_PV         otp_iow (0x02, sizeof(otp_product_pv))
#define CMD_OTP_READ_PRODUCT_PV         otp_iowr(0x03, sizeof(otp_product_pv))
#define CMD_OTP_KEY_VERIFY_STATUS       otp_iowr(0x04, sizeof(otp_key_verify_status))
#define CMD_OTP_COUNT                   5

hi_s32 otp_memset(void *src, hi_u32 len1, int num, hi_u32 len2);
hi_s32 otp_memcpy(void *dst, hi_u32 len1, const void *src, hi_u32 len2);

hi_s32 drv_ioctl_otp(hi_u32 cmd, hi_void *argp);

#define otp_malloc                          malloc
#define otp_free                            free

#define otp_ioremap_nocache(addr, size)     (hi_void*)(addr)
#define otp_iounmap(addr, size)

#ifdef __cplusplus
}
#endif
#endif /* __DRV_IOCTL_OTP_H__ */
