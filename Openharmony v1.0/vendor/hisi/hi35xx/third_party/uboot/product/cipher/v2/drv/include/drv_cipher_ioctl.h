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
 * Description   : head file for cipher ioctl
 */

#ifndef __REE_DRV_CIPHER_IOCTL_H__
#define __REE_DRV_CIPHER_IOCTL_H__

#include "hi_types.h"
#include "hi_mpi_cipher.h"

hi_s32 cipher_module_init(hi_void);
hi_void cipher_module_exit(hi_void);
hi_s32 drv_cipher_ioctl(hi_u32 cmd, hi_void *argp, hi_void *private_data);

typedef struct {
    hi_u32 chn_id;
    hi_char *open_status;
    hi_char *alg;
    hi_char *mode;
    hi_u32 key_len;
    hi_char *key_from;
    hi_bool is_decrypt;
    hi_u32 data_in_size;
    hi_u32 data_in_addr;
    hi_u32 data_out_size;
    hi_u32 data_out_addr;
    hi_bool in_int_all_en;
    hi_bool in_int_en;
    hi_bool in_int_raw;
    hi_bool out_int_en;
    hi_bool out_int_raw;
    hi_u32 out_int_count;       /* CHANn_INT_OCNTCFG */
    char iv_string[33];         /* 33 iv string size */
} cipher_chn_status_s;

#define REE_CIPHER_IOC_NA   0U
#define REE_CIPHER_IOC_W    1U
#define REE_CIPHER_IOC_R    2U
#define REE_CIPHER_IOC_RW   3U

#define ree_cipher_ioc(dir, type, nr, size) (((dir) << 30) | ((size) << 16) | ((type) << 8) | ((nr) << 0))

#define ree_cipher_ior(type,  nr, size) ree_cipher_ioc(REE_CIPHER_IOC_R,  (type), (nr), sizeof(size))
#define ree_cipher_iow(type,  nr, size) ree_cipher_ioc(REE_CIPHER_IOC_W,  (type), (nr), sizeof(size))
#define ree_cipher_iowr(type, nr, size) ree_cipher_ioc(REE_CIPHER_IOC_RW, (type), (nr), sizeof(size))

#define ree_cipher_ioc_dir(nr)  (((nr) >> 30) & 0x03)
#define ree_cipher_ioc_type(nr) (((nr) >> 8)  & 0xFF)
#define ree_cipher_ioc_nr(nr)   (((nr) >> 0)  & 0xFF)
#define ree_cipher_ioc_size(nr) (((nr) >> 16) & 0x3FFF)

#define HI_ID_CIPHER 100

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


#define CMD_CIPHER_CREATEHANDLE          ree_cipher_iowr(HI_ID_CIPHER, 0x1,  cipher_handle_s)
#define CMD_CIPHER_DESTROYHANDLE         ree_cipher_iow(HI_ID_CIPHER,  0x2,  hi_u32)
#define CMD_CIPHER_CONFIGHANDLE          ree_cipher_iow(HI_ID_CIPHER,  0x3,  cipher_config_ctrl_s)
#define CMD_CIPHER_ENCRYPT               ree_cipher_iow(HI_ID_CIPHER,  0x4,  cipher_data_s)
#define CMD_CIPHER_DECRYPT               ree_cipher_iow(HI_ID_CIPHER,  0x5,  cipher_data_s)
#define CMD_CIPHER_DECRYPTMULTI          ree_cipher_iow(HI_ID_CIPHER,  0x6,  cipher_pkg_s)
#define CMD_CIPHER_ENCRYPTMULTI          ree_cipher_iow(HI_ID_CIPHER,  0x7,  cipher_pkg_s)
#define CMD_CIPHER_GETRANDOMNUMBER       ree_cipher_iowr(HI_ID_CIPHER, 0x8,  cipher_rng_s)
#define CMD_CIPHER_GETHANDLECONFIG       ree_cipher_iowr(HI_ID_CIPHER, 0x9,  cipher_config_ctrl_s)
#define CMD_CIPHER_CALCHASHINIT          ree_cipher_iowr(HI_ID_CIPHER, 0xa,  cipher_hash_data_s)
#define CMD_CIPHER_CALCHASHUPDATE        ree_cipher_iowr(HI_ID_CIPHER, 0xb,  cipher_hash_data_s)
#define CMD_CIPHER_CALCHASHFINAL         ree_cipher_iowr(HI_ID_CIPHER, 0xc,  cipher_hash_data_s)
#define CMD_CIPHER_CALCRSA               ree_cipher_iowr(HI_ID_CIPHER, 0x10, cipher_rsa_data_s)
#define CMD_CIPHER_GETTAG                ree_cipher_iowr(HI_ID_CIPHER, 0x11, cipher_tag_s)
#define CMD_CIPHER_CONFIGHANDLE_EX       ree_cipher_iowr(HI_ID_CIPHER, 0x23, cipher_config_ctrl_ex_s)
#define CMD_CIPHER_GETHANDLECONFIG_EX    ree_cipher_iowr(HI_ID_CIPHER, 0x24, cipher_config_ctrl_ex_s)
#define CMD_CIPHER_KLAD_KEY              ree_cipher_iowr(HI_ID_CIPHER, 0x12, cipher_klad_key_s)

#ifdef CONFIG_COMPAT
#define CMD_CIPHER_COMPAT_DECRYPTMULTI   ree_cipher_iow(HI_ID_CIPHER,  0x6,  cipher_compat_pkg_s)
#define CMD_CIPHER_COMPAT_ENCRYPTMULTI   ree_cipher_iow(HI_ID_CIPHER,  0x7,  cipher_compat_pkg_s)
#define CMD_CIPHER_COMPAT_CALCRSA        ree_cipher_iowr(HI_ID_CIPHER, 0x10, cipher_compat_rsa_data_s)
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of #ifndef __DRV_CIPHER_IOCTL_H__ */
