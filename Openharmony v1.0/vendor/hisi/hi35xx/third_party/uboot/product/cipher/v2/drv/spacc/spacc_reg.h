/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
*
* This program is free software; you can redistribute  it and/or modify it
* under  the terms of  the GNU General Public License as published by the
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
 * Description   : head file for spacc reg config
 */

#ifndef _SPACC_REG_H_
#define _SPACC_REG_H_

#define CHN_0_CIPHER_IV                             (g_spacc_reg_base + 0x0000)
#define chn_n_cipher_iv_out(id)                     (g_spacc_reg_base + 0x0000 + (id) * 0x10)
#define CHN_0_CIPHER_DOUT                           (g_spacc_reg_base + 0x0080)
#define cipher_key(id)                              (g_spacc_reg_base + 0x0100 + (id) * 0x20)
#define sm1_sk(id)                                  (g_spacc_reg_base + 0x0200 + (id) * 0x10)
#define ODD_EVEN_KEY_SEL                            (g_spacc_reg_base + 0x0290)
#define HDCP_MODE_CTRL                              (g_spacc_reg_base + 0x0300)
#define SEC_CHN_CFG                                 (g_spacc_reg_base + 0x0304)
#define CALC_ERR                                    (g_spacc_reg_base + 0x0320)
#define CHN_0_CIPHER_CTRL                           (g_spacc_reg_base + 0x0400)
#define CIPHER_INT_STATUS                           (g_spacc_reg_base + 0x0404)
#define CIPHER_INT_EN                               (g_spacc_reg_base + 0x0408)
#define CIPHER_INT_RAW                              (g_spacc_reg_base + 0x040c)
#define CIPHER_IN_SMMU_EN                           (g_spacc_reg_base + 0x0410)
#define OUT_SMMU_EN                                 (g_spacc_reg_base + 0x0414)
#define CHN_0_CIPHER_DIN                            (g_spacc_reg_base + 0x0420)
#define NORM_SMMU_START_ADDR                        (g_spacc_reg_base + 0x0440)
#define SEC_SMMU_START_ADDR                         (g_spacc_reg_base + 0x0444)
#define chn_n_cipher_ctrl(id)                       (g_spacc_reg_base + 0x0400 + (id) * 0x80)
#define chn_n_cipher_in_node_cfg(id)                (g_spacc_reg_base + 0x0404 + (id) * 0x80)
#define chn_n_cipher_in_node_start_addr(id)         (g_spacc_reg_base + 0x0408 + (id) * 0x80)
#define chn_n_cipher_in_buf_rptr(id)                (g_spacc_reg_base + 0x040C + (id) * 0x80)
#define chn_n_cipher_out_node_cfg(id)               (g_spacc_reg_base + 0x0430 + (id) * 0x80)
#define chn_n_cipher_out_node_start_addr(id)        (g_spacc_reg_base + 0x0434 + (id) * 0x80)
#define chn_n_cipher_out_buf_rptr(id)               (g_spacc_reg_base + 0x0438 + (id) * 0x80)
#define chn_n_cipher_in_node_start_addr_high(id)    (g_spacc_reg_base + 0x0460 + (id) * 0x80)
#define chn_n_cipher_out_node_start_addr_high(id)   (g_spacc_reg_base + 0x0470 + (id) * 0x80)

#define CHN_0_HASH_CTRL                             (g_spacc_reg_base + 0x0800)
#define HASH_INT_STATUS                             (g_spacc_reg_base + 0x0804)
#define HASH_INT_EN                                 (g_spacc_reg_base + 0x0808)
#define HASH_INT_RAW                                (g_spacc_reg_base + 0x080C)
#define HASH_IN_SMMU_EN                             (g_spacc_reg_base + 0x0810)
#define CHN_0_HASH_DAT_IN                           (g_spacc_reg_base + 0x0818)
#define CHN_0_HASH_TOTAL_DAT_LEN                    (g_spacc_reg_base + 0x081C)
#define chn_n_hash_ctrl(id)                         (g_spacc_reg_base + 0x0800 + (id) * 0x80)
#define chn_n_hash_in_node_cfg(id)                  (g_spacc_reg_base + 0x0804 + (id) * 0x80)
#define chn_n_hash_in_node_start_addr(id)           (g_spacc_reg_base + 0x0808 + (id) * 0x80)
#define chn_n_hash_in_buf_rptr(id)                  (g_spacc_reg_base + 0x080C + (id) * 0x80)
#define chn_n_hash_state_val(id)                    (g_spacc_reg_base + 0x0340 + (id) * 0x08)
#define chn_n_hash_state_val_addr(id)               (g_spacc_reg_base + 0x0344 + (id) * 0x08)
#define chn_n_hash_in_node_start_addr_high(id)      (g_spacc_reg_base + 0x820  + (id) * 0x80)

#define spacc_read(addr)        *(volatile unsigned int *)(addr)
#define spacc_write(addr, val)  *(volatile unsigned int *)(addr) = (val)

#endif

