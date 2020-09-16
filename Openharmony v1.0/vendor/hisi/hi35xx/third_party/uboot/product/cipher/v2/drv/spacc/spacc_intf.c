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
 * Description   : drivers for spacc interface
 */

#include <cpu_func.h>
#include "cipher_adapt.h"
#include "spacc_body.h"
#include "spacc_union_define.h"
#include "drv_klad.h"

#define intf_func_fail_return(val, ret, func) \
    do { \
        if (val) { \
            hi_err_cipher("%s[%d]: call %s failed\n", __FUNCTION__, __LINE__, #func); \
            return ret; \
        } \
    } while (0)

#define intf_param_invalid_return(val) \
    do { \
        if (val) { \
            hi_err_cipher("%s[%d]: param is invalid\n", __FUNCTION__, __LINE__); \
            return HI_ERR_CIPHER_INVALID_PARA; \
        } \
    } while (0)

#define SPACC_MAX_CHN                   8
#define AES_BLOCK_SIZE                  16
#define SPACC_TIME_OUT                  100000
#define SPACC_PAD_BUF_SIZE              128
#define HASH_RESULT_MAX_LEN             64

#define CHN_0_CIPHER_IV                 (g_cipher_reg_base + 0x0000)
#define CHN_0_CIPHER_DOUT               (g_cipher_reg_base + 0x0080)
#define CHN_0_CIPHER_KEY                (g_cipher_reg_base + 0x0100)
#define CHN_0_SM1_SK                    (g_cipher_reg_base + 0x0200)
#define ODD_EVEN_KEY_SEL                (g_cipher_reg_base + 0x0290)
#define HDCP_MODE_CTRL                  (g_cipher_reg_base + 0x0300)
#define SEC_CHN_CFG                     (g_cipher_reg_base + 0x0304)
#define CALC_ST0                        (g_cipher_reg_base + 0x0318)
#define CALC_ERR                        (g_cipher_reg_base + 0x0320)
#define CHN_0_CCM_GCM_TAG               (g_cipher_reg_base + 0x0380)
#define CHN_0_CIPHER_CTRL               (g_cipher_reg_base + 0x0400)
#define CIPHER_INT_RAW                  (g_cipher_reg_base + 0x040c)
#define CHN_0_CIPHER_DIN                (g_cipher_reg_base + 0x0420)

#define SYMC_INT_LEVEL                  100 /* (SPACC_MAX_DEPTH / 2) */

typedef hi_void (*func_cipher_callback)(hi_u32);

typedef struct {
    cipher_mmz_buf_t mmz_buf;
} spacc_env_s;

typedef struct {
    hi_u8 *src_vir;
    hi_u8 *dest_vir;
    hi_u8 *aad_vir;

    cipher_mmz_buf_t src_mmz_buf;
    cipher_mmz_buf_t dest_mmz_buf;
    cipher_mmz_buf_t aad_mmz_buf;
} spacc_mmz_s;

typedef struct {
    hi_bool is_open;
    hi_u32 hard_num;
    hi_u32 block_size;

    hi_bool symc_done;
    CIPHER_QUEUE_HEAD queue;

    hi_cipher_data *node_list;
    hi_u32 node_num;
    hi_u32 node_cur;
    hi_u32 total_len;

    hi_u8 *pad_vir_addr;
    hi_size_t pad_phy_addr;

    hi_u32 data_size;
    hi_void* which_file;

    cipher_config_ctrl_ex_s ctrl_ex;

    func_cipher_callback callback;
} spacc_symc_chn_s;

typedef struct {
    hi_bool is_open;
    hi_u32 hard_num;
    hi_u32 node_num;
    hi_u32 node_cur;
    hi_u32 block_size;

    hi_bool digest_done;
    CIPHER_QUEUE_HEAD queue;

    func_cipher_callback callback;

    hi_u32 data_size;
    hi_void* which_file;
} spacc_digest_chn_s;

typedef struct {
    hi_u32 src_phys_addr;
    hi_u32 dst_phys_addr;
    hi_u32 byte_length;
    hi_bool is_use_odd_key;
} cipher_data_compat_s;

CIPHER_MUTEX                g_symc_mutex;
CIPHER_MUTEX                g_digest_mutex;
static spacc_env_s          g_spacc_env;
static spacc_symc_chn_s     g_symc_chn[SPACC_MAX_CHN];
static spacc_digest_chn_s   g_digest_chn[SPACC_MAX_CHN];
static hi_void*             g_cipher_reg_base;

static hi_s32 spacc_check_handle(hi_handle ci_handle)
{
    if ((hi_handle_get_mod_id(ci_handle) != HI_ID_CIPHER) || \
        (hi_handle_get_pri_data(ci_handle) != 0)) {
        hi_err_cipher("invalid cipher handle 0x%x\n", ci_handle);
        cipher_mutex_unlock(&g_symc_mutex);
        return HI_ERR_CIPHER_INVALID_HANDLE;
    }
    if (hi_handle_get_chn_id(ci_handle) >= SPACC_MAX_CHN) {
        hi_err_cipher("chan %d is too large, max: %d\n", \
            hi_handle_get_chn_id(ci_handle), SPACC_MAX_CHN);
        cipher_mutex_unlock(&g_symc_mutex);
        return HI_ERR_CIPHER_INVALID_HANDLE;
    }
    if (g_symc_chn[hi_handle_get_chn_id(ci_handle)].is_open == HI_FALSE) {
        hi_err_cipher("chan %d is not open\n", hi_handle_get_chn_id(ci_handle));
        cipher_mutex_unlock(&g_symc_mutex);
        return HI_ERR_CIPHER_INVALID_HANDLE;
    }
    return HI_SUCCESS;
}

#ifdef INT_ENABLE
CIPHER_IRQRETURN_T drv_cipher_isr(hi_s32 irq, hi_void *dev_id)
{
    hi_u32 chn_mask, i;

    chn_mask = spacc_symc_done_notify();
    hi_info_cipher("SPACC ISR IRQ: %d, chn_mask 0x%x\n", irq, chn_mask);

    for (i = CIPHER_PKG_N_CHN_MIN; i <= CIPHER_PKG_N_CHN_MAX; i++) {
        if ((chn_mask >> i) & 0x01) {
            if (g_symc_chn[i].callback) {
                g_symc_chn[i].callback(i);
            } else {
                g_symc_chn[i].symc_done = HI_TRUE;
                hi_info_cipher("chn %d wake up\n", i);
                cipher_queue_wait_up(&g_symc_chn[i].queue);
            }
        }
    }

    chn_mask = spacc_digest_done_notify();
    for (i = CIPHER_PKG_N_CHN_MIN; i <= CIPHER_PKG_N_CHN_MAX; i++) {
        if ((chn_mask >> i) & 0x01) {
            if (g_digest_chn[i].callback) {
                g_digest_chn[i].callback(i);
            } else {
                g_digest_chn[i].digest_done = HI_TRUE;
                cipher_queue_wait_up(&g_digest_chn[i].queue);
            }
        }
    }

    return CIPHER_IRQ_HANDLED;
}
#endif

static hi_s32 drv_cipher_reset(hi_void)
{
    hi_u32 *pvirt = HI_NULL;
    hi_u32 spacc_stat = 0;

    pvirt = cipher_ioremap_nocache(CIPHER_SPACC_CRG_ADDR_PHY, 16); /* 16 */
    if (pvirt == HI_NULL) {
        hi_err_cipher("ioremap_nocache phy addr err:%x.\n", CIPHER_SPACC_CRG_ADDR_PHY);
        return HI_FAILURE;
    }

    /* open clock, reset */
    hal_cipher_read_reg(CIPHER_SPACC_CRG_ADDR_PHY, &spacc_stat);
    spacc_stat |= SPACC_CRG_CLOCK_BIT;
    spacc_stat |= SPACC_CRG_RESET_BIT;
    hal_cipher_write_reg(CIPHER_SPACC_CRG_ADDR_PHY, spacc_stat);
    cipher_msleep(5); /* 5ms */

    /* cancel reset */
    spacc_stat &= ~SPACC_CRG_RESET_BIT;
    hal_cipher_write_reg(CIPHER_SPACC_CRG_ADDR_PHY, spacc_stat);

    cipher_iounmap(pvirt);
    pvirt = HI_NULL;

    return HI_SUCCESS;
}

hi_s32 drv_cipher_init(hi_void)
{
    hi_s32 ret;
    hi_size_t size_addr = 0;
    hi_u32 i;
    u_sec_chn_cfg sec_cfg;

    cipher_mutex_init(&g_symc_mutex);

    g_cipher_reg_base = cipher_ioremap_nocache(CIPHER_CIPHER_REG_BASE_ADDR_PHY, 0x2000);
    intf_func_fail_return(g_cipher_reg_base == HI_NULL, HI_FAILURE, cipher_ioremap_nocache);

    ret = drv_cipher_reset();
    intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_reset);

    crypto_memset(&g_spacc_env, sizeof(g_spacc_env), 0, sizeof(spacc_env_s));
    crypto_memset(&g_symc_chn, sizeof(g_symc_chn), 0, sizeof(g_symc_chn));
    crypto_memset(&g_digest_chn, sizeof(g_digest_chn), 0, sizeof(g_digest_chn));

    g_spacc_env.mmz_buf.mmz_size = spacc_get_node_list_size() + SPACC_PAGE_SIZE;
    ret = cipher_mmz_alloc_remap("CIPHER_ChnBuf", &g_spacc_env.mmz_buf);
    intf_func_fail_return(ret != HI_SUCCESS, ret, cipher_mmz_alloc_remap);

    for (i = CIPHER_PKG_N_CHN_MIN; i <= CIPHER_PKG_N_CHN_MAX; i++) {
        cipher_queue_init(&g_symc_chn[i].queue);
        cipher_queue_init(&g_digest_chn[i].queue);
        g_symc_chn[i].pad_phy_addr = g_spacc_env.mmz_buf.start_phy_addr + SPACC_PAD_BUF_SIZE * i;
        g_symc_chn[i].pad_vir_addr = g_spacc_env.mmz_buf.start_vir_addr + SPACC_PAD_BUF_SIZE * i;
        g_symc_chn[i].hard_num = i;
        g_digest_chn[i].hard_num = i;
    }

    ret = spacc_init(g_cipher_reg_base, size_addr,
                     g_spacc_env.mmz_buf.start_phy_addr + SPACC_PAGE_SIZE,
                     g_spacc_env.mmz_buf.start_vir_addr + SPACC_PAGE_SIZE);
    if (ret != HI_SUCCESS)
        goto unmap_mmz;

    hal_cipher_read_reg(SEC_CHN_CFG, &sec_cfg.u32);
    sec_cfg.bits.cipher_sec_chn_cfg |= 0x01;
    sec_cfg.bits.hash_sec_chn_cfg |= 0x01;
    hal_cipher_write_reg(SEC_CHN_CFG, sec_cfg.u32);

#ifdef INT_ENABLE
    ret = cipher_request_irq(CIPHER_IRQ_NUMBER, drv_cipher_isr, "cipher");
    if (ret != HI_SUCCESS) {
        hi_err_cipher("Irq request failure, ret=%d, irq = %d", ret, CIPHER_IRQ_NUMBER);
        goto unmap_mmz;
    }
#endif
    return ret;

unmap_mmz:
    cipher_mmz_release_unmap(&g_spacc_env.mmz_buf);
    return ret;
}

hi_void drv_cipher_deinit(hi_void)
{
    if (spacc_deinit() != HI_SUCCESS)
        hi_err_cipher("spacc deinit failed.\n");

#ifdef INT_ENABLE
    cipher_free_irq(CIPHER_IRQ_NUMBER, "cipher");
#endif

    cipher_mmz_release_unmap(&g_spacc_env.mmz_buf);

    cipher_iounmap(g_cipher_reg_base);

    return;
}

hi_s32 hi_drv_cipher_create_handle(cipher_handle_s *ci_handle, hi_void* file)
{
    hi_u32 i;
    hi_s32 ret = HI_SUCCESS;

    if (ci_handle == HI_NULL) {
        hi_err_cipher("Invalid params!\n");
        return HI_FAILURE;
    }

    if (ci_handle->cipher_atts.cipher_type > HI_CIPHER_TYPE_COPY_AVOID) {
        hi_err_cipher("Invalid cipher type!\n");
        return HI_FAILURE;
    }

    if (cipher_mutex_lock(&g_symc_mutex)) {
        hi_err_cipher("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    if (ci_handle->cipher_atts.cipher_type == HI_CIPHER_TYPE_COPY_AVOID) {
        if (g_symc_chn[0].is_open == HI_FALSE)
            i = 0;
        else
            i = SPACC_MAX_CHN;
    } else {
        for (i = CIPHER_PKG_N_CHN_MIN; i <= CIPHER_PKG_N_CHN_MAX; i++) {
            if (g_symc_chn[i].is_open == HI_FALSE)
                break;
        }
    }

    if (i <= CIPHER_PKG_N_CHN_MAX) {
        g_symc_chn[i].is_open = HI_TRUE;
        g_symc_chn[i].which_file = file;
        g_symc_chn[i].callback = HI_NULL;
        g_symc_chn[i].node_list = HI_NULL;
        g_symc_chn[i].node_num = 0;
        ci_handle->ci_handle = hi_handle_make_handle(HI_ID_CIPHER, 0, i);
    } else {
        hi_err_cipher("No more cipher chan left.\n");
        ret = HI_FAILURE;
    }

    cipher_mutex_unlock(&g_symc_mutex);

    return ret;
}

static hi_s32 drv_cipher_param_check(symc_alg_en symc_alg,
                                     symc_mode_en symc_mode,
                                     symc_dat_width_en symc_width,
                                     hi_cipher_sm1_round sm1_round)
{
   /* the mode depend on alg, which limit to hardware
    * des/3des support ecb/cbc/cfb/ofb
    * aes support ecb/cbc/cfb/ofb/ctr/ccm/gcm
    * sm1 support ecb/cbc/cfb/ofb
    * sm4 support ecb/cbc/ctr
    */
    if ((symc_alg == SYMC_ALG_DES) || (symc_alg == SYMC_ALG_3DES) || (symc_alg == SYMC_ALG_SM1)) {
        if ((symc_mode != SYMC_MODE_ECB) && (symc_mode != SYMC_MODE_CBC) &&
            (symc_mode != SYMC_MODE_CFB) && (symc_mode != SYMC_MODE_OFB)) {
            hi_err_cipher("Invalid alg %d and mode: %d\n", symc_alg, symc_mode);
            return HI_ERR_CIPHER_INVALID_PARA;
         }
    } else if (symc_alg == SYMC_ALG_SM4) {
        if ((symc_mode != SYMC_MODE_ECB) && (symc_mode != SYMC_MODE_CBC) && (symc_mode != SYMC_MODE_CTR)) {
            hi_err_cipher("Invalid alg %d and mode %d\n", symc_alg, symc_mode);
            return HI_ERR_CIPHER_INVALID_PARA;
         }
    }

   /* the bit width depend on alg and mode, which limit to hardware
    * des/3des with cfb/ofb support bit1, bit8, bit 64.
    * aes with cfb/ofb only support bit128.
    * sm1 with ofb only support bit128, cfb support bit1, bit8, bit 64.
    */
    if ((symc_alg == SYMC_ALG_DES) || (symc_alg == SYMC_ALG_3DES)) {
        if ((symc_mode == SYMC_MODE_CFB) || (symc_mode == SYMC_MODE_OFB)) {
            if (symc_width != SYMC_DAT_WIDTH_64 &&
                symc_width != SYMC_DAT_WIDTH_8 && symc_width != SYMC_DAT_WIDTH_1) {
                hi_err_cipher("Invalid mode %d and bit width %d\n", symc_mode, symc_width);
                return HI_ERR_CIPHER_INVALID_PARA;
            }
        }
    }

    if (symc_alg == SYMC_ALG_AES) {
        if (((symc_mode == SYMC_MODE_CFB) && (symc_width >= SYMC_DAT_WIDTH_COUNT)) ||
            ((symc_mode == SYMC_MODE_OFB) && (symc_width != SYMC_DAT_WIDTH_128))) {
            hi_err_cipher("Invalid alg %d mode %d and width %d\n", symc_alg, symc_mode, symc_width);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    if (symc_alg == SYMC_ALG_SM1) {
        if (((symc_mode == SYMC_MODE_OFB) && (symc_width != SYMC_DAT_WIDTH_128)) ||
            ((symc_mode == SYMC_MODE_CFB) && (symc_width >= SYMC_DAT_WIDTH_COUNT))) {
            hi_err_cipher("Invalid alg %d mode %d and width %d\n", symc_alg, symc_mode, symc_width);
            return HI_ERR_CIPHER_INVALID_PARA;
        }

        if (sm1_round >= HI_CIPHER_SM1_ROUND_BUTT) {
            hi_err_cipher("Invalid alg %d and Sm1Round %d\n", symc_alg, sm1_round);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    return HI_SUCCESS;
}

static hi_s32 drv_cipher_match_alg(cipher_config_ctrl_ex_s *config, symc_alg_en *symc_alg, hi_u32 *block_size)
{
    /* set alg and block size */
    switch (config->ci_alg) {
        case HI_CIPHER_ALG_AES:
            *symc_alg = SYMC_ALG_AES;
            *block_size = 16; /* 16 block size */
            break;
        case HI_CIPHER_ALG_DMA:
            *symc_alg = SYMC_ALG_NULL_CIPHER;
            *block_size = 16; /* 16 block size */
            break;
        case HI_CIPHER_ALG_SM1:
            *symc_alg = SYMC_ALG_SM1;
            *block_size = 16; /* 16 block size */
            break;
        case HI_CIPHER_ALG_SM4:
            *symc_alg = SYMC_ALG_SM4;
            *block_size = 16; /* 16 block size */
            break;
        default:
            hi_err_cipher("Invalid alg: 0x%x\n", config->ci_alg);
            return HI_ERR_CIPHER_INVALID_PARA;
    }

    return HI_SUCCESS;
}

static hi_s32 drv_cipher_match_work_mode(cipher_config_ctrl_ex_s *config, symc_mode_en *symc_mode)
{
    switch (config->work_mode) {
        case HI_CIPHER_WORK_MODE_ECB:
            *symc_mode = SYMC_MODE_ECB;
            break;
        case HI_CIPHER_WORK_MODE_CBC:
            *symc_mode = SYMC_MODE_CBC;
            break;
        case HI_CIPHER_WORK_MODE_CFB:
            *symc_mode = SYMC_MODE_CFB;
            break;
        case HI_CIPHER_WORK_MODE_OFB:
            *symc_mode = SYMC_MODE_OFB;
            break;
        case HI_CIPHER_WORK_MODE_CTR:
            *symc_mode = SYMC_MODE_CTR;
            break;
        case HI_CIPHER_WORK_MODE_CCM:
            *symc_mode = SYMC_MODE_CCM;
            break;
        case HI_CIPHER_WORK_MODE_GCM:
            *symc_mode = SYMC_MODE_GCM;
            break;
        default:
            hi_err_cipher("Invalid mode: 0x%x\n", config->work_mode);
            return HI_ERR_CIPHER_INVALID_PARA;
    }

    return HI_SUCCESS;
}

static hi_s32 drv_cipher_match_bit_width(cipher_config_ctrl_ex_s *config, symc_dat_width_en *symc_width)
{
    /* set the bit width which depend on alg and mode */
    if ((config->work_mode == HI_CIPHER_WORK_MODE_CFB) ||
        (config->work_mode == HI_CIPHER_WORK_MODE_OFB)) {
        switch (config->bit_width) {
            case HI_CIPHER_BIT_WIDTH_64BIT:
                *symc_width = SYMC_DAT_WIDTH_64;
                break;
            case HI_CIPHER_BIT_WIDTH_8BIT:
                *symc_width = SYMC_DAT_WIDTH_8;
                break;
            case HI_CIPHER_BIT_WIDTH_1BIT:
                *symc_width = SYMC_DAT_WIDTH_1;
                break;
            case HI_CIPHER_BIT_WIDTH_128BIT:
                *symc_width = SYMC_DAT_WIDTH_128;
                break;
            default:
                hi_err_cipher("Invalid width: 0x%x, mode 0x%x, alg 0x%x\n",
                    config->bit_width, config->work_mode, config->ci_alg);
                return HI_ERR_CIPHER_INVALID_PARA;
        }
    } else {
        *symc_width = SYMC_DAT_WIDTH_128;
    }

    return HI_SUCCESS;
}

static hi_s32 drv_cipher_match_key_len(cipher_config_ctrl_ex_s *config, hi_u32 *key_len)
{
    if (config->ci_alg == HI_CIPHER_ALG_AES) {
        switch (config->key_len) {
            case HI_CIPHER_KEY_AES_128BIT:
                *key_len = 16; /* 16 key len */
                break;
            case HI_CIPHER_KEY_AES_192BIT:
                *key_len = 24; /* 24 key len */
                break;
            case HI_CIPHER_KEY_AES_256BIT:
                *key_len = 32; /* 32 key len */
                break;
            default:
                hi_err_cipher("Invalid key len: 0x%x\n", config->key_len);
                return HI_ERR_CIPHER_INVALID_PARA;
        }
    } else if (config->ci_alg == HI_CIPHER_ALG_SM1) {
        *key_len = 48; /* 48 key len */
    } else if (config->ci_alg == HI_CIPHER_ALG_SM4) {
        *key_len = 16; /* 16 key len */
    } else {
        hi_err_cipher("Invalid cipher alg: %d\n", config->ci_alg);
        return HI_ERR_CIPHER_INVALID_PARA;
    }
    return HI_SUCCESS;
}

/* change the unf params to drive params */
static hi_s32 drv_cipher_param(cipher_config_ctrl_ex_s *config,
    spacc_symc_config_s *symc_cfg, hi_u32 *block_size)
{
    hi_s32 ret;

    /* set alg and block size */
    ret = drv_cipher_match_alg(config, &symc_cfg->symc_alg, block_size);
    intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_match_alg);

    /* set the mode which depend on alg */
    ret = drv_cipher_match_work_mode(config, &symc_cfg->symc_mode);
    intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_match_work_mode);

    /* set the bit width which depend on alg and mode */
    ret = drv_cipher_match_bit_width(config, &symc_cfg->symc_width);
    intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_match_bit_width);

   /* set the key length depend on alg
    * des/3des support 2key and 3key
    * aes support 128, 192, and 256
    * sm1 support ak/ek/sk
    * sm4 support 128
    */
    ret = drv_cipher_match_key_len(config, &symc_cfg->key_len);
    intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_match_key_len);

    if (config->change_flags.bits_iv > HI_CIPHER_IV_CHG_ALL_PKG) {
        hi_err_cipher("Invalid IV Change Flags: 0x%x\n", config->change_flags.bits_iv);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ((config->change_flags.bits_iv == HI_CIPHER_IV_CHG_ALL_PKG) &&
        ((config->work_mode == HI_CIPHER_WORK_MODE_CCM) ||
        (config->work_mode == HI_CIPHER_WORK_MODE_GCM))) {
        hi_err_cipher("Invalid IV Change Flags: 0x%x\n", config->change_flags.bits_iv);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (config->key_by_ca && (config->ca_type >= HI_CIPHER_KEY_SRC_BUTT)) {
        hi_err_cipher("Invalid CA Type: 0x%x\n", config->ca_type);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    return drv_cipher_param_check(symc_cfg->symc_alg,
        symc_cfg->symc_mode, symc_cfg->symc_width, config->sm1_round);
}

static hi_s32 drv_cipher_config_ccm(cipher_config_ctrl_ex_s *config,
    hi_u32 *iv, hi_u32 ilen, hi_u32 *real_ilen)
{
    hi_u8 *buf = HI_NULL;

    /* The octet lengths of N are denoted  n,
     * The octet length of the binary represen tation of the
     * octet length of the payload denoted q,
     * n is an element of {7, 8, 9, 10, 11, 12, 13},
     * equation: n + q = 15
     * here the string of N  is config->iv, and n is config->iv_len.
     */
    if ((config->iv_len < 7) || (config->iv_len > 13)) { /* 7, 13 iv len range */
        hi_err_cipher("Invalid IV LEN: 0x%x\n", config->iv_len);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /* the parameter t denotes the octet length of T(tag)
     * t is an element of  { 4, 6, 8, 10, 12, 14, 16}
     * here t is config->tag_len
     */
    if ((config->tag_len & 0x01) || (config->tag_len < 4) || (config->tag_len > 16)) { /* 4, 16 tag len value */
        hi_err_cipher("Invalid TAG LEN: 0x%x\n", config->tag_len);
        return HI_ERR_CIPHER_INVALID_PARA;
    }
    /* Formatting of the Counter Blocks(IV for CTR)
     *
     * According to the CCM spec, the counter is equivalent to
     * a formatting of the counter index i into a complete data block.
     * The counter blocks Ctri are formatted as shown below:
     * | Octet number:  0    1 ... 15-q    16-q ... 15
     * | Contents:     Flags     N             [i]
     * Within each block Ctri, the N is get from config->iv, n + q = 15,
     * so the q equal to 15 - config->iv_len.
     * the [i] is the block conut start with 0,
     * In the Flags field, Bits 0, 1, and 2 contain the encoding of q - 1,
     * others bits shall be set to 0.
     * so the first byte of IV shall be q -1, that is 15 - config->iv_len - 1
     */
    buf = (hi_u8 *)iv;
    crypto_memset(buf, ilen, 0, ilen);
    buf[0] = 14 - config->iv_len; /* equation: IV[0] = q - 1 = 15 - n - 1, 14 */
    crypto_memcpy(buf + 1, 16 - 1, config->iv, config->iv_len); /* 16 buf size */
    *real_ilen = config->iv_len + 1;

    return HI_SUCCESS;
}

static hi_s32 drv_cipher_config_gcm(cipher_config_ctrl_ex_s *config,
    hi_u32 *iv, hi_u32 ilen, hi_u32 *real_ilen)
{
    /* According to the GCM spec, the IVLen >= 1, typical equal to 12,
     * but limit to hard logic devising, the IVLen can't large than 16.
     */
    if (config->iv_len > ilen) {
        hi_err_cipher("Invalid IV LEN: 0x%x\n", config->iv_len);
        return HI_ERR_CIPHER_INVALID_PARA;
    }
    crypto_memcpy(iv, ilen, config->iv, config->iv_len);
    *real_ilen = config->iv_len;
    return HI_SUCCESS;
}

static hi_s32 drv_cipher_config_chn_0(spacc_symc_chn_s *channel,
    cipher_config_ctrl_ex_s *config, spacc_symc_config_s *symc_cfg, hi_u32 *iv, hi_u32 iv_len)
{
    u_chan0_cipher_ctrl chn0_ctrl;
    hi_u32 klen = 0;
    hi_u32 i;
    hi_s32 ret = HI_SUCCESS;

    hal_cipher_write_reg(ODD_EVEN_KEY_SEL, 0x00);
    if (config->key_by_ca == HI_FALSE) {
        for (i = 0; i < 8; i++) /* 8 */
            hal_cipher_write_reg(CHN_0_CIPHER_KEY + i * 4, config->key[i]); /* 4 */
    } else {
        ret = drv_cipher_klad_load_key(0, channel->ctrl_ex.ca_type,
            HI_CIPHER_KLAD_TARGET_AES, (hi_u8 *)config->key, 16); /* 16 */
        intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_klad_load_key);
    }

    if (symc_cfg->symc_alg == SYMC_ALG_SM1) {
        for (i = 0; i < 4; i++) /* 4 */
            hal_cipher_write_reg(CHN_0_SM1_SK + i * 4, config->key[i + 8]); /* 4, 8 */
    }
    for (i = 0; i < 4; i++) /* 4 */
        hal_cipher_write_reg(CHN_0_CIPHER_IV + i * 4, iv[i]); /* 4 */

    if (symc_cfg->symc_alg == SYMC_ALG_AES)
        klen = symc_cfg->key_len / 8 - 2; /* 8, 2 */
    else if (symc_cfg->symc_alg == SYMC_ALG_3DES)
        klen = (symc_cfg->key_len == 16 ? 3 : 2); /* 16, 3, 2 */

    chn0_ctrl.u32 = 0x00;
    chn0_ctrl.bits.sym_ch0_sm1_round_num = config->sm1_round;
    chn0_ctrl.bits.sym_ch0_ivin_sel = 0x01;
    chn0_ctrl.bits.sym_ch0_key_sel = config->key_by_ca;
    chn0_ctrl.bits.sym_ch0_key_length = klen;
    chn0_ctrl.bits.sym_ch0_dat_width = symc_cfg->symc_width;
    chn0_ctrl.bits.sym_ch0_alg_sel = symc_cfg->symc_alg;
    chn0_ctrl.bits.sym_ch0_alg_mode = symc_cfg->symc_mode;
    if (config->work_mode == HI_CIPHER_WORK_MODE_GCM)
        chn0_ctrl.bits.sym_ch0_gcm_iv_len = config->iv_len - 1;
    hal_cipher_write_reg(CHN_0_CIPHER_CTRL, chn0_ctrl.u32);

    return ret;
}

static hi_s32 drv_cipher_config_chn_n(spacc_symc_chn_s *channel, cipher_config_ctrl_ex_s *config,
    spacc_symc_config_s *symc_cfg, hi_u32 *iv, hi_u32 iv_len)
{
    hi_s32 ret;

    ret = spacc_symc_config(channel->hard_num, symc_cfg, config->sm1_round, config->key_by_ca);
    intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_config);

    if (config->key_by_ca == HI_FALSE) { /* HI_CIPHER_KEY_SRC_USER, CPU config key */
        ret = spacc_symc_setkey(channel->hard_num, config->key, config->odd_key, symc_cfg->key_len);
        intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_setkey);
#ifdef CIPHER_KLAD_SUPPORT
    } else { /* HI_CIPHER_KEY_SRC_KLAD, KLAD load key */
        ret = drv_cipher_klad_load_key(channel->hard_num, channel->ctrl_ex.ca_type,
            HI_CIPHER_KLAD_TARGET_AES, (hi_u8 *)config->key, 16); /* 16 key len */
        intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_klad_load_key);
#endif
    }

    ret = spacc_symc_setiv(channel->hard_num, (hi_u8*)iv, iv_len);
    intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_setiv);
    return ret;
}

static hi_s32 drv_cipher_config_chn(hi_u32 soft_chn_id, cipher_config_ctrl_ex_s *config)
{
    hi_s32 ret;
    hi_u32 iv[4]; /* 4 iv arr size */
    hi_u32 real_ilen = 0;
    hi_cipher_ctrl_chg_flag change_flags;
    spacc_symc_config_s symc_cfg;
    spacc_symc_chn_s *channel = &g_symc_chn[soft_chn_id];

    crypto_memset(iv, sizeof(iv), 0, sizeof(iv));
    crypto_memset(&symc_cfg, sizeof(symc_cfg), 0, sizeof(symc_cfg));
    crypto_memset(&change_flags, sizeof(change_flags), 0, sizeof(change_flags));

    change_flags.bits_iv = channel->ctrl_ex.change_flags.bits_iv;

    crypto_memcpy(&channel->ctrl_ex, sizeof(channel->ctrl_ex), config, sizeof(cipher_config_ctrl_ex_s));
    if (channel->ctrl_ex.key_by_ca == HI_TRUE)
        channel->ctrl_ex.change_flags.bits_iv = change_flags.bits_iv;

    ret = drv_cipher_param(config, &symc_cfg, &channel->block_size);
    intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_param);

    if (config->work_mode == HI_CIPHER_WORK_MODE_CCM) {
        ret = drv_cipher_config_ccm(config, iv, sizeof(iv), &real_ilen);
        intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_config_ccm);
    } else if (config->work_mode == HI_CIPHER_WORK_MODE_GCM) {
        ret = drv_cipher_config_gcm(config, iv, sizeof(iv), &real_ilen);
        intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_config_gcm);
    } else if (config->work_mode <= HI_CIPHER_WORK_MODE_CTR) {
        /* IV length, 16 for aes, 8 for des/3des */
        crypto_memcpy(iv, sizeof(iv), config->iv, sizeof(config->iv));
        real_ilen = sizeof(config->iv);
    } else {
        hi_err_cipher("Invalid mode: 0x%x\n", config->work_mode);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /* chn 1~7, data transferred by DMA */
    if (soft_chn_id != 0) {
        ret = drv_cipher_config_chn_n(channel, config, &symc_cfg, iv, real_ilen);
        intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_config_chn_n);
    } else {     /* chn 0, data transferred by CPU, spacc_body do not drvie chn0 */
        ret = drv_cipher_config_chn_0(channel, config, &symc_cfg, iv, sizeof(iv));
        intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_config_chn_0);
    }

    return HI_SUCCESS;
}

hi_s32 hi_drv_cipher_config_chn_ex(hi_handle ci_handle, cipher_config_ctrl_ex_s *config)
{
    hi_s32 ret;
    hi_u32 soft_chn_id;

    if (config == HI_NULL) {
        hi_err_cipher("Invalid params!\n");
        return HI_FAILURE;
    }

    if (cipher_mutex_lock(&g_symc_mutex)) {
        hi_err_cipher("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    ret = spacc_check_handle(ci_handle);
    if (ret != HI_SUCCESS)
        return ret;

    soft_chn_id = hi_handle_get_chn_id(ci_handle);
    ret = drv_cipher_config_chn(soft_chn_id, config);

    cipher_mutex_unlock(&g_symc_mutex);

    return ret;
}

hi_s32 hi_drv_cipher_destory_handle(hi_handle cipher_chn)
{
    hi_u32 soft_chn_id;
    hi_s32 ret;

    if (cipher_mutex_lock(&g_symc_mutex)) {
        hi_err_cipher("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    ret = spacc_check_handle(cipher_chn);
    if (ret != HI_SUCCESS)
        return ret;
    soft_chn_id = hi_handle_get_chn_id(cipher_chn);

    g_symc_chn[soft_chn_id].is_open = HI_FALSE;

    cipher_mutex_unlock(&g_symc_mutex);

    return ret;
}

/* check error code
 * bit0: klad_key_use_err
 * bit1: alg_len_err
 * bit2: smmu_page_unvlid
 */
static hi_s32 drv_cipher_check_error_code(hi_u32 hard_num, hi_u32 wait, hi_u32 src_addr)
{
    hi_s32 ret = HI_SUCCESS;

    if (wait & 0x01) {
        hi_err_cipher("hash error: klad_key_use_err, chn %d !!!\n", hard_num);
        ret = HI_FAILURE;
    }
    if (wait & 0x02) {
        hi_err_cipher("hash error: alg_len_err, chn %d !!!\n", hard_num);
        ret = HI_FAILURE;
    }
    if (wait & 0x04) {
        hi_err_cipher("hash error: smmu_page_unvlid, chn %d !!!\n", hard_num);
        hi_err_cipher("SRC ADDR: 0x%x\n", src_addr);
        ret = HI_FAILURE;
    }
    return ret;
}

static hi_s32 drv_cipher_symc_wait_done(spacc_symc_chn_s *channel, hi_u32 time_out)
{
    hi_s32 ret = HI_SUCCESS;
    hi_u32 wait;
    hi_u32 src_addr, dst_addr;

#ifdef INT_ENABLE
    if (cipher_queue_wait_timeout(&channel->queue,  &channel->symc_done, time_out) != HI_SUCCESS) {
        hi_err_cipher("Encrypt time out! Chn %d, CIPHER_IRQ_NUMBER: %d\n", channel->hard_num, CIPHER_IRQ_NUMBER);
        ret = HI_FAILURE;
    }
#else
    time_out = 0;
    while (time_out++ < SPACC_TIME_OUT) {
        if (spacc_symc_done_try(channel->hard_num))
            break;
        cipher_msleep(1);
    }
    if (time_out >= SPACC_TIME_OUT) {
        hi_err_cipher("symc time out!\n");
        ret = HI_FAILURE;
    }
#endif

    wait = spacc_symc_get_err_code(channel->hard_num, &src_addr, &dst_addr);
    if (drv_cipher_check_error_code(channel->hard_num, wait, src_addr) != HI_SUCCESS)
        ret = HI_FAILURE;

    return ret;
}

static hi_s32 drv_cipher_digest_wait_done(spacc_digest_chn_s *channel)
{
    hi_s32 ret = HI_SUCCESS;
    hi_u32 wait;
    hi_u32 time_out = SPACC_TIME_OUT;
    hi_u32 src_addr;

#ifdef INT_ENABLE
    if (channel->data_size > 100 * 1024) { /* 100, 1024 */
        ret = cipher_queue_wait_timeout(&channel->queue, &channel->digest_done, time_out);
        if (ret <= 0) {
            hi_err_cipher("hash time out! CIPHER_IRQ_NUMBER: %d\n", CIPHER_IRQ_NUMBER);
            ret = HI_FAILURE;
        }
    } else {
        time_out = 0;
        while (time_out++ < SPACC_TIME_OUT) {
            if (channel->digest_done != HI_FALSE)
                break;
            cipher_msleep(1);
        }
        if (time_out >= SPACC_TIME_OUT) {
            hi_err_cipher("hash time out!\n");
            ret = HI_FAILURE;
        }
    }
#else
    time_out = 0;
    while (time_out++ < SPACC_TIME_OUT) {
        if (spacc_digest_done_try(channel->hard_num))
            break;
        cipher_msleep(1);
    }
    if (time_out >= SPACC_TIME_OUT) {
        hi_err_cipher("hash time out!\n");
        ret = HI_FAILURE;
    }
#endif

   /* check error code
    * bit0: klad_key_use_err
    * bit1: alg_len_err
    * bit2: smmu_page_unvlid
    */
    wait = spacc_digest_get_err_code(channel->hard_num, &src_addr);
    if (drv_cipher_check_error_code(channel->hard_num, wait, src_addr) != HI_SUCCESS)
        ret = HI_FAILURE;

    return ret;
}

static hi_s32 drv_cipher_ccm_head_format(spacc_symc_chn_s *channel,
    hi_u32 enc_len, hi_u8 *arr_b, hi_u32 blen, hi_u32 *b1_len)
{
    hi_u8 *pbuf = HI_NULL;
    hi_u32 index;

    /* Format B0 */
    /* The leading octet of the first block of the formatting, B0,
     * contains four flags for control information: two single bits,
     * called  Reserved  and  Adata, and two strings of three bits,
     * to encode the values t and q.  The encoding of t is [(t -2)/2],
     * and the encoding of q is [ q-1].
     * The ordering of the flags with in the octet is given:
     *  _____________________________________________________
     * |Bit number  7     |   6   | 5  4  3     |  2  1  0   |
     * |Contents  Reserved  Adata   [( t -2)/2] |  [q-1]     |
     *  -----------------------------------------------------
     * The remaining 15 octets of the first block of  the formatting are
     * devoted to the nonce and the binary representation of
     * the message length in  q octets, as given:
     *  _____________________________________________
     * |Octet number  0   | 1 ... 15-q | 16-q ... 15 |
     * |Contents    Flags |      N     |      Q      |
     *  ---------------------------------------------
    */
    pbuf = arr_b;
    index = 0;
    crypto_memset(pbuf, AES_BLOCK_SIZE, 0, AES_BLOCK_SIZE);
    pbuf[index]  = (channel->ctrl_ex.alen > 0 ? 1 : 0) << 6; /* Adata, 6 left shift */
    pbuf[index] |= ((channel->ctrl_ex.tag_len - 2) / 2) << 3; /* formula: (t - 2) / 2, 3 left shift */
    pbuf[index] |= ((15 - channel->ctrl_ex.iv_len) - 1); /* formula: q - 1, n + q = 15 */
    index++;
    crypto_memcpy(&pbuf[index], AES_BLOCK_SIZE - index, channel->ctrl_ex.iv, channel->ctrl_ex.iv_len);
    index += channel->ctrl_ex.iv_len;
    if (index <= 12) { /* 12 index */
        index = 12; /* 12 index */
        pbuf[index++] = (hi_u8)(enc_len >> 24); /* 24 right shift */
        pbuf[index++] = (hi_u8)(enc_len >> 16); /* 16 right shift */
        pbuf[index++] = (hi_u8)(enc_len >> 8);  /* 8  right shift */
        pbuf[index++] = (hi_u8)(enc_len);
    } else if ((index == 13) && (enc_len <= 0xFFFFFF)) { /* 13 index */
        pbuf[index++] = (hi_u8)(enc_len >> 16); /* 16 right shift */
        pbuf[index++] = (hi_u8)(enc_len >> 8);  /* 8  right shift */
        pbuf[index++] = (hi_u8)(enc_len);
    } else if ((index == 14) && (enc_len <= 0xFFFF)) { /* 14 index */
        pbuf[index++] = (hi_u8)(enc_len >> 8); /* 8  right shift */
        pbuf[index++] = (hi_u8)(enc_len);
    } else {
        hi_err_cipher("Invalid Mlen: 0x%x, q: 0x%x!\n", enc_len, 16 - index); /* 16 */
        return HI_FAILURE;
    }

   /* Formatting of the Associated Data in B1, the length of A denotes as a */
   /* The value a is encoded according to the following three cases:
    * If 0 < a < 2^16 - 2^8, then a  is encoded as a[0..15], i.e., two octets.
    * If 2^16 - 2^8 <= a < 2^32, then a  is encoded as 0xff || 0xfe || a[0..31], i.e., six octets.
    * If 2^32 <= a < 2^64, then  a is encoded as 0xff || 0xff || a[0..63], i.e., ten octets.
    * For example, if a=2^16, the encoding of a  is
    * 11111111 11111110 00000000 00000001 00000000 00000000.
    */
    pbuf = arr_b + 16; /* 16 offset */
    index = 0;
    if (channel->ctrl_ex.alen > 0) {
        if (channel->ctrl_ex.alen < (0x10000 - 0x100)) {
            pbuf[index++] = (hi_u8)(channel->ctrl_ex.alen >> 8); /* 8 right shift */
            pbuf[index++] = (hi_u8)(channel->ctrl_ex.alen);
        } else {
            pbuf[index++] = 0xFF;
            pbuf[index++] = 0xFE;
            pbuf[index++] = (hi_u8)(channel->ctrl_ex.alen >> 24); /* 24 right shift */
            pbuf[index++] = (hi_u8)(channel->ctrl_ex.alen >> 16); /* 16 right shift */
            pbuf[index++] = (hi_u8)(channel->ctrl_ex.alen >> 8); /* 8 right shift */
            pbuf[index++] = (hi_u8)channel->ctrl_ex.alen;
        }
    }
    *b1_len = index;

    return HI_SUCCESS;
}

static hi_void drv_cipher_cpu_input(hi_u8 *input, hi_u8 *output, hi_u32 length,
                                    hi_u32 block_size, hi_u32 ctrl, hi_bool set_last)
{
    hi_u32 offset = 0;
    hi_u32 buf[4]; /* 4 buf arr size */
    hi_u32 size;
    u_chan0_cipher_ctrl chn0_ctrl;
    u_cipher_int_raw int_raw;

    chn0_ctrl.u32 = ctrl;

    while (offset < length) {
        hi_u32 i;
        hi_u32 time = 0;

        /* Compute one block, if less than one block, padding with 0 */
        size = (offset + block_size) < length ? block_size : length - offset;
        crypto_memset(buf, sizeof(buf), 0, sizeof(buf));
        crypto_memcpy(buf, sizeof(buf), &input[offset], size);
        for (i = 0; i < block_size / 4; i++) /* 4 */
            hal_cipher_write_reg(CHN_0_CIPHER_DIN + i * 4, buf[i]); /* 4 */

        /* may be needs set last flag when compute last block */
        if (((offset + block_size) >= length) && set_last)
            chn0_ctrl.bits.sym_ch0_ccm_gcm_pc_last = 0x01;
        hal_cipher_write_reg(CHN_0_CIPHER_CTRL, chn0_ctrl.u32);

        /* start working */
        hal_cipher_write_reg(CHN_0_CIPHER_CTRL, chn0_ctrl.u32 | 0x01);

        /* Waiting compute finished */
        hal_cipher_read_reg(CIPHER_INT_RAW, &int_raw.u32);
        while (!(int_raw.bits.cipher_chn_obuf_raw & 0x01) && (time++ < SPACC_TIME_OUT))
            hal_cipher_read_reg(CIPHER_INT_RAW, &int_raw.u32);

        if (time >= SPACC_TIME_OUT) {
            hi_err_cipher("Chn 0 time out!\n");
            return;
        }

        /* Clean raw interrupt */
        int_raw.u32 = 0x00;
        int_raw.bits.cipher_chn_obuf_raw = 0x01;
        hal_cipher_write_reg(CIPHER_INT_RAW, int_raw.u32);

        /* May be needs read output data */
        if (output != HI_NULL) {
            for (i = 0; i < block_size / 4; i++) /* 4 */
                hal_cipher_read_reg(CHN_0_CIPHER_DOUT + i * 4, &buf[i]); /* 4 */
            crypto_memcpy(&output[offset], length, (hi_u8*)buf, size);
        }

        /* prepare compute next block */
        offset += block_size;
        chn0_ctrl.u32 &= ~(0x01 << 15); /* 15 iv set */
    }
}

static hi_s32 drv_cipher_cpu_mmz_map(spacc_symc_chn_s *channel,
    cipher_data_s *ci_data, spacc_mmz_s *spacc_mmz)
{
    hi_s32 ret;

    /* mapping phy address of SRC */
    spacc_mmz->src_mmz_buf.mmz_size = ci_data->data_length;
    spacc_mmz->src_mmz_buf.start_phy_addr =
        make_ulong(ci_data->src_phy_addr, ci_data->src_phy_addr_high);
    ret = cipher_mmz_map(&spacc_mmz->src_mmz_buf);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("DRV SRC MMZ MAP ERROR!, addr = 0x%x!\n", ci_data->src_phy_addr);
        return ret;
    }
    spacc_mmz->src_vir = spacc_mmz->src_mmz_buf.start_vir_addr;

    /* mapping phy address of DST */
    spacc_mmz->dest_mmz_buf.mmz_size = ci_data->data_length;
    spacc_mmz->dest_mmz_buf.start_phy_addr =
        make_ulong(ci_data->dest_phy_addr, ci_data->dest_phy_addr_high);
    ret = cipher_mmz_map(&spacc_mmz->dest_mmz_buf);
    if (ret !=  HI_SUCCESS) {
        hi_err_cipher("DRV DEST MMZ MAP ERROR! addr = 0x%x!\n", ci_data->dest_phy_addr);
        cipher_mmz_unmap(&spacc_mmz->src_mmz_buf);
        return ret;
    }
    spacc_mmz->dest_vir = spacc_mmz->dest_mmz_buf.start_vir_addr;

    /* mapping phy address of A for CCM/GCM */
    if ((channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_CCM) ||
        (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_GCM)) {
        spacc_mmz->aad_mmz_buf.mmz_size = channel->ctrl_ex.alen;
        spacc_mmz->aad_mmz_buf.start_phy_addr =
            make_ulong(channel->ctrl_ex.aphy_addr, channel->ctrl_ex.aphy_addr_high);
        ret = cipher_mmz_map(&spacc_mmz->aad_mmz_buf);
        if (ret != HI_SUCCESS) {
            hi_err_cipher("DRV AD MMZ MAP ERROR!, addr = 0x%x!\n", channel->ctrl_ex.aphy_addr);
            cipher_mmz_unmap(&spacc_mmz->src_mmz_buf);
            cipher_mmz_unmap(&spacc_mmz->dest_mmz_buf);
            return ret;
        }
        spacc_mmz->aad_vir = spacc_mmz->aad_mmz_buf.start_vir_addr;
    }
    return ret;
}

static hi_void drv_cipher_cpu_mmz_unmap(spacc_symc_chn_s *channel, spacc_mmz_s *spacc_mmz)
{
    cipher_mmz_unmap(&spacc_mmz->src_mmz_buf);
    cipher_mmz_unmap(&spacc_mmz->dest_mmz_buf);

    if ((channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_CCM) ||
        (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_GCM))
        cipher_mmz_unmap(&spacc_mmz->aad_mmz_buf);
}

static hi_s32 drv_cipher_cpu_enc_ccm(spacc_symc_chn_s *channel,
    cipher_data_s *ci_data, u_chan0_cipher_ctrl *chn0_ctrl, spacc_mmz_s *spacc_mmz)
{
    hi_u8 arr_b[32] = {0}; /* 32 arr size */
    hi_s32 ret;
    hi_u32 value;
    hi_u32 offset = 0;
    hi_bool set_last;

    /* Format N and A */
    ret = drv_cipher_ccm_head_format(channel, ci_data->data_length, arr_b, sizeof(arr_b), &offset);
    intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_ccm_head_format);

    /* Set last block size */
    chn0_ctrl->bits.sym_ccm_gcm_last_block = (ci_data->data_length + 15) % 16; /* 15, 16 */

    /* Set flag N */
    chn0_ctrl->bits.sym_ch0_ccm_gcm_input_flag = 0x00; // N

    /* Compute B0, contains N */
    set_last = (channel->ctrl_ex.alen + ci_data->data_length == 0) ? HI_TRUE : HI_FALSE;
    drv_cipher_cpu_input(arr_b, HI_NULL, 16, 16, chn0_ctrl->u32, set_last); /* 16 */

    /* Don't update IV any more */
    chn0_ctrl->bits.sym_ch0_ivin_sel = 0x00;

    /* Compute A */
    value = channel->ctrl_ex.alen + offset;
    if (value > 16) { /* 16, a can't puts in one block */
        /* Set flag A */
        chn0_ctrl->bits.sym_ch0_ccm_gcm_input_flag = 0x01; // A

        /* Fill head of A to B1 split joint 16 byets */
        crypto_memcpy(arr_b + 16 + offset, sizeof(arr_b) - 16 - offset, /* 16 */
            spacc_mmz->aad_vir, 16 - offset); /* 16 */

        /* Compute B1, contains the coding of a and head of A */
        drv_cipher_cpu_input(arr_b + 16, HI_NULL, 16, 16, chn0_ctrl->u32, HI_FALSE); /* 16 */

        /* Compute the left data of A */
        set_last = (ci_data->data_length == 0) ? HI_TRUE : HI_FALSE;
        drv_cipher_cpu_input(spacc_mmz->aad_vir + 16 - offset, HI_NULL, /* 16 */
            channel->ctrl_ex.alen - (16 - offset), 16, chn0_ctrl->u32, set_last); /* 16 */
    } else if (value > 0) { /* A and a can puts in one block */
        /* Set flag A */
        chn0_ctrl->bits.sym_ch0_ccm_gcm_input_flag = 0x01; // A

        /* Fill A to B1 split joint 16 byets */
        crypto_memcpy(arr_b + 16 + offset, sizeof(arr_b) - 16 - offset, /* 16 */
            spacc_mmz->aad_vir, channel->ctrl_ex.alen);

        /* Compute B1, contains the coding of a and A */
        set_last = (ci_data->data_length == 0) ? HI_TRUE : HI_FALSE;
        drv_cipher_cpu_input(arr_b + 16, HI_NULL, 16, 16, chn0_ctrl->u32, set_last); /* 16 */
    }

    /* Next, compute the P */
    chn0_ctrl->bits.sym_ch0_ccm_gcm_input_flag = 0x02; // P

    return ret;
}

static hi_void drv_cipher_cpu_enc_gcm(spacc_symc_chn_s *channel, cipher_data_s *ci_data,
    u_chan0_cipher_ctrl *chn0_ctrl, spacc_mmz_s *spacc_mmz, hi_u32 block_size)
{
    hi_bool set_last;

    /* Set last block size */
    chn0_ctrl->bits.sym_ccm_gcm_last_block = (ci_data->data_length + 15) % 16; /* 15, 16 */

    /* Compute A */
    if (channel->ctrl_ex.alen > 0) {
        /* Set flag A */
        chn0_ctrl->bits.sym_ch0_ccm_gcm_input_flag = 0x00; // A

        /* Compute A */
        set_last = (ci_data->data_length == 0) ? HI_TRUE : HI_FALSE;
        drv_cipher_cpu_input(spacc_mmz->aad_vir, HI_NULL,
            channel->ctrl_ex.alen, block_size, chn0_ctrl->u32, set_last);

        chn0_ctrl->bits.sym_ch0_ivin_sel = 0x00;
    }

    /* Don't update IV any more */
    chn0_ctrl->bits.sym_ch0_ccm_gcm_input_flag = 0x01; // P
}

static hi_s32 drv_cipher_cpu_enc_phy(cipher_data_s *ci_data, hi_u32 block_size, hi_bool is_decrypt)
{
    hi_u32 ret;
    u_chan0_cipher_ctrl chn0_ctrl;
    hi_u8 arr_b[32]; /* 32 arr size */
    spacc_mmz_s spacc_mmz;

    spacc_symc_chn_s *channel = &g_symc_chn[0];

    ret = drv_cipher_cpu_mmz_map(channel, ci_data, &spacc_mmz);
    intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_cpu_mmz_map);

    /* Decrypt or encrypt */
    hal_cipher_read_reg(CHN_0_CIPHER_CTRL, &chn0_ctrl.u32);
    chn0_ctrl.bits.sym_ch0_decrypt = is_decrypt;
    hal_cipher_write_reg(CHN_0_CIPHER_CTRL, chn0_ctrl.u32);

    if (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_CCM) {
        ret = drv_cipher_cpu_enc_ccm(channel, ci_data, &chn0_ctrl, &spacc_mmz);
        if (ret != HI_SUCCESS) {
            drv_cipher_cpu_mmz_unmap(channel, &spacc_mmz);
            return ret;
        }
    } else if (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_GCM) {
        drv_cipher_cpu_enc_gcm(channel, ci_data, &chn0_ctrl, &spacc_mmz, block_size);
    }

    /* Compute P */
    if (ci_data->data_length > 0) {
        drv_cipher_cpu_input(spacc_mmz.src_vir, spacc_mmz.dest_vir,
            ci_data->data_length, block_size, chn0_ctrl.u32, HI_TRUE);

        /* Don't update IV any more */
        chn0_ctrl.bits.sym_ch0_ivin_sel = 0x00;
    }

    /* Compute LEN(C) for GCM */
    if (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_GCM) {
        /* Set flag LEN(C) */
        crypto_memset(arr_b, sizeof(arr_b), 0, sizeof(arr_b));
        chn0_ctrl.bits.sym_ch0_ccm_gcm_input_flag = 0x02; // LEN

        /* Format LEN(C) = LEN(A) || LEN(P), coding in bits */
        arr_b[3] = (hi_u8)((channel->ctrl_ex.alen >> 29) & 0x07); /* 3 index, 29 shift bits */
        arr_b[4] = (hi_u8)((channel->ctrl_ex.alen >> 21) & 0xff); /* 4 index, 21 shift bits */
        arr_b[5] = (hi_u8)((channel->ctrl_ex.alen >> 13) & 0xff); /* 5 index, 13 shift bits */
        arr_b[6] = (hi_u8)((channel->ctrl_ex.alen >> 5)  & 0xff); /* 6 index, 5  shift bits */
        arr_b[7] = (hi_u8)((channel->ctrl_ex.alen << 3)  & 0xff); /* 7 index, 3  shift bits */

        arr_b[11] = (hi_u8)((ci_data->data_length >> 29) & 0x07); /* 11 index, 29 shift bits */
        arr_b[12] = (hi_u8)((ci_data->data_length >> 21) & 0xff); /* 12 index, 21 shift bits */
        arr_b[13] = (hi_u8)((ci_data->data_length >> 13) & 0xff); /* 13 index, 13 shift bits */
        arr_b[14] = (hi_u8)((ci_data->data_length >> 5)  & 0xff); /* 14 index, 5  shift bits */
        arr_b[15] = (hi_u8)((ci_data->data_length << 3)  & 0xff); /* 15 index, 3  shift bits */

        /* Compute LEN(C) */
        drv_cipher_cpu_input(arr_b, HI_NULL, 16, 16, chn0_ctrl.u32, HI_FALSE);  /* 16 */
    }

    drv_cipher_cpu_mmz_unmap(channel, &spacc_mmz);

    return ret;
}

static hi_s32 drv_cipher_ccm_na(spacc_symc_chn_s *channel, hi_u32 enc_len)
{
    hi_s32 ret;
    hi_u8 *pbuf = HI_NULL;
    hi_u32 index = 0;
    hi_u32 alen = 0;
    hi_u32 count, flag;

    pbuf = channel->pad_vir_addr;
    crypto_memset(pbuf, SPACC_PAD_BUF_SIZE, 0, 32);  /* 32 memset size */

    /* Format B0 and head of B1 */
    ret = drv_cipher_ccm_head_format(channel, enc_len, pbuf, 32, &alen);  /* 32 */
    intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_ccm_head_format);

    /* B0 contains the N, set flag N, for N, A, P, must set the first and last flag. */
    flag = SPACC_CTRL_SYMC_IN_CCM_N | SPACC_CTRL_SYMC_IN_LAST | SPACC_CTRL_SYMC_IN_FIRST;
    if ((channel->ctrl_ex.alen == 0) && (enc_len == 0))
        flag |= SPACC_CTRL_SYMC_CCM_LAST;

    ret = spacc_symc_addbuf(channel->hard_num, channel->pad_phy_addr, 16, SPACC_BUF_TYPE_SYMC_IN, flag); /* 16 */
    intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);
    index += 16; /* 16 */

    /* a > 0, add the phy of A into node list */
    if (alen) {
        /* 1st. add the phy of B1 into node list, which contains the coding of a */
        ret = spacc_symc_addbuf(channel->hard_num, channel->pad_phy_addr + 16, /* 16 */
            alen, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_CCM_A);
        intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);
        index += alen;

        /* 2nd. add the phy of A into node list */
        ret = spacc_symc_addbuf(channel->hard_num, channel->ctrl_ex.aphy_addr,
            channel->ctrl_ex.alen, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_CCM_A);
        intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);
    }

    /* if alen + Alen do not aligned with 16, padding 0 to the tail */
    count = (channel->ctrl_ex.alen + alen) % AES_BLOCK_SIZE;
    if (count != 0) {
        /* Compute the padding length */
        count = AES_BLOCK_SIZE - count;

        /* Set zero */
        crypto_memset(&pbuf[index], SPACC_PAD_BUF_SIZE - index, 0, 16); /* 16 clean numbers */

        /* add the padding phy of A into node list */
        ret = spacc_symc_addbuf(channel->hard_num, channel->pad_phy_addr + index,
            count, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_CCM_A);
        intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);
    }

    flag = SPACC_CTRL_SYMC_IN_LAST;
    if (enc_len == 0) /* if do not contains the P, set CCM last flag signal to hardware */
        flag |= SPACC_CTRL_SYMC_CCM_LAST;
    spacc_symc_addctrl(channel->hard_num, SPACC_BUF_TYPE_SYMC_IN, flag);

    return HI_SUCCESS;
}

static hi_s32 drv_cipher_gcm_a(spacc_symc_chn_s *channel)
{
    hi_s32 ret;
    hi_u32 count;
    hi_u32 index = 0;
    hi_u8 *pbuf = HI_NULL;

    if (channel->ctrl_ex.alen == 0)
        return HI_SUCCESS;

    pbuf = channel->pad_vir_addr;

    /* Add phy of A into node list */
    ret = spacc_symc_addbuf(channel->hard_num,
        make_ulong(channel->ctrl_ex.aphy_addr, channel->ctrl_ex.aphy_addr_high),
        channel->ctrl_ex.alen, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_GCM_A);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("spacc add A buf failed, ret = 0x%x.\n", ret);
        return HI_FAILURE;
    }

    /* if Alen do not aligned with 16, padding 0 to the tail */
    count = channel->ctrl_ex.alen % AES_BLOCK_SIZE;
    if (count != 0) {
        /* Compute the padding length */
        count = AES_BLOCK_SIZE - count;

        /* Set zero */
        crypto_memset(&pbuf[index], SPACC_PAD_BUF_SIZE - index, 0, 16); /* 16 clean size */

        /* add the padding phy of A into node list */
        ret = spacc_symc_addbuf(channel->hard_num,
            channel->pad_phy_addr + index, count,
            SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_GCM_A);
        if (ret != HI_SUCCESS) {
            hi_err_cipher("spacc add A PAD buf failed, ret = 0x%x.\n", ret);
            return HI_FAILURE;
        }
    }

    /* Set A last flag */
    spacc_symc_addctrl(channel->hard_num, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_LAST);

    return HI_SUCCESS;
}

static hi_s32 drv_cipher_gcm_len(spacc_symc_chn_s *channel, hi_u32 enc_len)
{
    hi_s32 ret;
    hi_u8 *pbuf;
    hi_u32 index = 32;

    /* Format len(C), 16 byets, coding in bits.
     * Byet0~7:  bits number of Add
     * Byet8~15: bits number of P
     */
    pbuf = channel->pad_vir_addr;

    pbuf[index + 0]  = 0x00; /* 0 arr index */
    pbuf[index + 1]  = 0x00; /* 1 arr index */
    pbuf[index + 2]  = 0x00; /* 2 arr index */
    pbuf[index + 3]  = (hi_u8)((channel->ctrl_ex.alen >> 29) & 0x07); /* 3 arr index, 29 shift bits */
    pbuf[index + 4]  = (hi_u8)((channel->ctrl_ex.alen >> 21) & 0xff); /* 4 arr index, 21 shift bits */
    pbuf[index + 5]  = (hi_u8)((channel->ctrl_ex.alen >> 13) & 0xff); /* 5 arr index, 13 shift bits */
    pbuf[index + 6]  = (hi_u8)((channel->ctrl_ex.alen >> 5)  & 0xff); /* 6 arr index, 5  shift bits */
    pbuf[index + 7]  = (hi_u8)((channel->ctrl_ex.alen << 3)  & 0xff); /* 7 arr index, 3 shift bits */
    pbuf[index + 8]  = 0x00; /* 8 arr index */
    pbuf[index + 9]  = 0x00; /* 9 arr index */
    pbuf[index + 10] = 0x00; /* 10 arr index */
    pbuf[index + 11] = (hi_u8)((enc_len >> 29) & 0x07); /* 11 arr index, 29 shift bits */
    pbuf[index + 12] = (hi_u8)((enc_len >> 21) & 0xff); /* 12 arr index, 21 shift bits */
    pbuf[index + 13] = (hi_u8)((enc_len >> 13) & 0xff); /* 13 arr index, 13 shift bits */
    pbuf[index + 14] = (hi_u8)((enc_len >> 5)  & 0xff); /* 14 arr index, 5 shift bits */
    pbuf[index + 15] = (hi_u8)((enc_len << 3)  & 0xff); /* 15 arr index, 3 shift bits */

    /* Add to nodes list */
    ret = spacc_symc_addbuf(channel->hard_num, channel->pad_phy_addr + index,
        16, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_GCM_LEN | SPACC_CTRL_SYMC_IN_LAST); /* 16 */
    if (ret != HI_SUCCESS) {
        hi_err_cipher("spacc add P buf failed, ret = 0x%x.\n", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static hi_s32 drv_cipher_enc_ccm(spacc_symc_chn_s *channel,
    cipher_data_s *ci_data, hi_size_t src_phy_addr, hi_size_t dst_phys_addr)
{
    hi_s32 ret;

    /* format N and A, add to node list */
    ret = drv_cipher_ccm_na(channel, ci_data->data_length);
    intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_ccm_na);

    /* Add the phy of P into node list */
    if (ci_data->data_length > 0) {
        /* Add in buffer */
        ret = spacc_symc_addbuf(channel->hard_num, src_phy_addr, ci_data->data_length,
            SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_CCM_P | SPACC_CTRL_SYMC_IN_LAST);
        intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);

        /* Add out buffer */
        ret = spacc_symc_addbuf(channel->hard_num, dst_phys_addr, ci_data->data_length,
            SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_SYMC_OUT_LAST);
        intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);
    } else {
        /* If P is null, must add a empty node into node list, limit to hardware devising */
        ret = spacc_symc_addbuf(channel->hard_num, 0x00, 0x00,
            SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_SYMC_OUT_LAST);
        intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);
    }

    /* Set CCM last flag */
    spacc_symc_addctrl(channel->hard_num, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_CCM_LAST);

    return ret;
}

static hi_s32 drv_cipher_enc_gcm(spacc_symc_chn_s *channel,
    cipher_data_s *ci_data, hi_size_t src_phy_addr, hi_size_t dest_phy_addr)
{
    hi_s32 ret;

    /* format N, add to node list */
    ret = drv_cipher_gcm_a(channel);
    intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_gcm_a);

    /* Add the phy of P into node list */
    if (ci_data->data_length > 0) {
        /* Add in buffer */
        ret = spacc_symc_addbuf(channel->hard_num, src_phy_addr, ci_data->data_length,
            SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_GCM_P | SPACC_CTRL_SYMC_IN_LAST);
        intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);

        /* Add out buffer */
        ret = spacc_symc_addbuf(channel->hard_num, dest_phy_addr, ci_data->data_length,
            SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_NONE);
        intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);
    }

    /* At the and of GCM, must add a empty node to nodes list, limit to hardware devising */
    ret = spacc_symc_addbuf(channel->hard_num, 0x00, 0x00,
        SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_SYMC_OUT_LAST);
    intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);

    /* Format the length fields of C and add to nodes list */
    ret = drv_cipher_gcm_len(channel, ci_data->data_length);
    intf_func_fail_return(ret != HI_SUCCESS, ret, spacc_symcdrv_cipher_gcm_len_addbuf);

    return ret;
}

/* except ccm/gcm */
static hi_s32 drv_cipher_enc_others(spacc_symc_chn_s *channel,
    cipher_data_s *ci_data, hi_size_t src_phy_addr, hi_size_t dest_phy_addr)
{
    hi_s32 ret;

    /* except ccm/gcm, the data length must not zero */
    if (ci_data->data_length == 0) {
        hi_err_cipher("Invalid data len 0x%x.\n", ci_data->data_length);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /* The length of data depend on alg and mode, which limit to hardware
     * for ecb/cbc/ofb/cfb, the data length must aligned with block size.
     * for ctr/ccm/gcm, support any data length.
     */
    if (((channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_ECB) ||
         (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_CBC) ||
         (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_OFB) ||
         (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_CFB)) &&
         (channel->ctrl_ex.ci_alg != HI_CIPHER_ALG_DMA)) {
        if (ci_data->data_length % channel->block_size != 0) {
            hi_err_cipher("Invalid data len 0x%x.\n", ci_data->data_length);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    /* Add in buffer */
    ret = spacc_symc_addbuf(channel->hard_num, src_phy_addr, ci_data->data_length,
        SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_LAST);
    intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);

    /* Add out buffer */
    ret = spacc_symc_addbuf(channel->hard_num, dest_phy_addr, ci_data->data_length,
        SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_SYMC_OUT_LAST);
    intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);

    return ret;
}

static hi_s32 drv_cipher_crypto(cipher_data_s *ci_data, hi_bool is_decrypt)
{
    hi_s32 ret;
    spacc_symc_chn_s *channel;
    hi_u32 soft_chn_id;
    hi_size_t src_phy_addr, dest_phy_addr;

    src_phy_addr = make_ulong(ci_data->src_phy_addr, ci_data->src_phy_addr_high);
    dest_phy_addr = make_ulong(ci_data->dest_phy_addr, ci_data->dest_phy_addr_high);

    soft_chn_id = hi_handle_get_chn_id(ci_data->ci_handle);
    channel = &g_symc_chn[soft_chn_id];

    if (soft_chn_id != 0) {
        if (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_CCM) {
            ret = drv_cipher_enc_ccm(channel, ci_data, src_phy_addr, dest_phy_addr);
            intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_enc_ccm);
        } else if (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_GCM) {
            ret = drv_cipher_enc_gcm(channel, ci_data, src_phy_addr, dest_phy_addr);
            intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_enc_gcm);
        } else { /* ECB/CBC/CBF/OFB/CTR */
            ret = drv_cipher_enc_others(channel, ci_data, src_phy_addr, dest_phy_addr);
            intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_enc_others);
        }

        channel->symc_done = HI_FALSE;

        /* Start working */
        spacc_symc_start(channel->hard_num, is_decrypt, channel->ctrl_ex.change_flags.bits_iv);

        if (channel->ctrl_ex.change_flags.bits_iv == HI_CIPHER_IV_CHG_ONE_PKG)
            channel->ctrl_ex.change_flags.bits_iv = 0; /* only update IV for first pkg */

        /* Waiting hardware computing finished */
        ret = drv_cipher_symc_wait_done(channel, SPACC_TIME_OUT);
        intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_symc_wait_done);

        flush_cache(cipher_align_down(dest_phy_addr), cipher_align_size(dest_phy_addr, ci_data->data_length));
    } else {
        /* Chn 0, CPU mode */
        ret = drv_cipher_cpu_enc_phy(ci_data, channel->block_size, is_decrypt);
        intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_cpu_enc_phy);
    }

    /* Save IV */
    if (channel->ctrl_ex.change_flags.bits_iv == HI_CIPHER_IV_CHG_ONE_PKG)
        spacc_symc_getiv(channel->hard_num, channel->ctrl_ex.iv, sizeof(channel->ctrl_ex.iv));

    flush_cache(cipher_align_down(dest_phy_addr), cipher_align_size(dest_phy_addr, ci_data->data_length));

    return ret;
}

hi_s32 hi_drv_cipher_get_tag(cipher_tag_s *tag)
{
    hi_u32 soft_chn_id;
    spacc_symc_chn_s *channel = HI_NULL;
    hi_u32 i;
    hi_s32 ret;

    if (tag ==  HI_NULL) {
        hi_err_cipher("Invalid params!\n");
        return HI_FAILURE;
    }
    if (cipher_mutex_lock(&g_symc_mutex)) {
        hi_err_cipher("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    ret = spacc_check_handle(tag->ci_handle);
    if (ret != HI_SUCCESS)
        return ret;

    soft_chn_id = hi_handle_get_chn_id(tag->ci_handle);
    channel = &g_symc_chn[soft_chn_id];

    if ((channel->ctrl_ex.work_mode != HI_CIPHER_WORK_MODE_CCM) &&
        (channel->ctrl_ex.work_mode != HI_CIPHER_WORK_MODE_GCM)) {
        hi_err_cipher("Invalid mode %d!\n", channel->ctrl_ex.work_mode);
        cipher_mutex_unlock(&g_symc_mutex);
        return HI_FAILURE;
    }
    tag->tag_len = channel->ctrl_ex.tag_len;

    /* Read tag for CCM/GCM */
    if (soft_chn_id == 0) {
        for (i = 0; i < 4; i++) /* 4 loop count */
            hal_cipher_read_reg(CHN_0_CCM_GCM_TAG + i * 4, &tag->tag[i]); /* 4 */
    } else {
        spacc_symc_gettag(channel->hard_num, (hi_u8*)tag->tag);
    }

    cipher_mutex_unlock(&g_symc_mutex);

    return HI_SUCCESS;
}

hi_s32 hi_drv_cipher_encrypt(cipher_data_s *ci_data)
{
    hi_s32 ret;

    if (ci_data == HI_NULL) {
        hi_err_cipher("Invalid point!\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if (cipher_mutex_lock(&g_symc_mutex)) {
        hi_err_cipher("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    ret = spacc_check_handle(ci_data->ci_handle);
    if (ret != HI_SUCCESS)
        return ret;

    ret = drv_cipher_crypto(ci_data, HI_FALSE);
    cipher_mutex_unlock(&g_symc_mutex);

    return ret;
}

hi_s32 hi_drv_cipher_decrypt(cipher_data_s *ci_data)
{
    hi_s32 ret;

    if (ci_data ==  HI_NULL) {
        hi_err_cipher("Invalid point!\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if (cipher_mutex_lock(&g_symc_mutex)) {
        hi_err_cipher("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    ret = spacc_check_handle(ci_data->ci_handle);
    if (ret != HI_SUCCESS)
        return ret;

    ret = drv_cipher_crypto(ci_data, HI_TRUE);
    cipher_mutex_unlock(&g_symc_mutex);

    return ret;
}

/* Get odd/even key flag and P flag */
static hi_u32 drv_cipher_get_pay_load_ctrl(hi_bool odd_key, hi_cipher_work_mode mode)
{
    hi_u32 ctrl;

    ctrl = odd_key ? SPACC_CTRL_SYMC_ODD_KEY : SPACC_CTRL_SYMC_EVEN_KEY;

    if (mode == HI_CIPHER_WORK_MODE_CCM)
        ctrl |= SPACC_CTRL_SYMC_IN_CCM_P;
    else if (mode == HI_CIPHER_WORK_MODE_GCM)
        ctrl |= SPACC_CTRL_SYMC_IN_GCM_P;

    return ctrl;
}

static hi_s32 drv_cipher_block_align(spacc_symc_chn_s *channel, hi_u32 total, hi_u32 node_cur)
{
    hi_s32 ret = HI_SUCCESS;
    hi_u32 ctrl;

    /* Compute the tail length */
    total %= channel->block_size;
    if (total > 0)
        total = channel->block_size - total;

    /* if the total length don't aligned with block size, split joint the follow nodes */
    while ((total > 0) && (channel->node_cur < channel->node_num)) {
        /* The next node large than tail size, just split it to 2 nodes */
        if (channel->node_list[node_cur].byte_len > total) {
            /* Add P in */
            ctrl = drv_cipher_get_pay_load_ctrl(channel->node_list[node_cur].odd_key, channel->ctrl_ex.work_mode);
            ret = spacc_symc_addbuf(channel->hard_num, channel->node_list[node_cur].src_phys_addr,
                total, SPACC_BUF_TYPE_SYMC_IN, ctrl);
            intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);

            /* Add P out */
            ret = spacc_symc_addbuf(channel->hard_num, channel->node_list[node_cur].dst_phys_addr,
                total, SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_NONE);
            intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);

            /* Let next node skip the tail size */
            channel->node_list[node_cur].src_phys_addr  += total;
            channel->node_list[node_cur].dst_phys_addr += total;
            channel->node_list[node_cur].byte_len -= total;
            total = 0;
        } else {
            /* The next node less than tail size, add it to nodes list */
            /* Add P in */
            ctrl = drv_cipher_get_pay_load_ctrl(channel->node_list[node_cur].odd_key, channel->ctrl_ex.work_mode);
            ret = spacc_symc_addbuf(channel->hard_num, channel->node_list[node_cur].src_phys_addr,
                channel->node_list[node_cur].byte_len, SPACC_BUF_TYPE_SYMC_IN, ctrl);
            intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);

            /* Add P out */
            ret = spacc_symc_addbuf(channel->hard_num, channel->node_list[node_cur].dst_phys_addr,
                channel->node_list[node_cur].byte_len, SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_NONE);
            intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);

            /* re-compute the tail size */
            total -= channel->node_list[node_cur].byte_len;

            /* Process next node */
            node_cur++;
            channel->node_cur++;
        }
    }

    return ret;
}

static hi_s32 drv_cipher_add_nodes(spacc_symc_chn_s *channel, hi_u32 int_level)
{
    hi_u32 i;
    hi_s32 ret = HI_SUCCESS;
    hi_u32 nodes, node_cur, ctrl, total;

    if (channel->node_cur < channel->node_num) {
        nodes = cipher_min(int_level, channel->node_num - channel->node_cur);
        node_cur = channel->node_cur;
        total = 0;
        for (i = 0; i < nodes; i++) {
            /* Get odd/even key flag and P flag */
            ctrl = drv_cipher_get_pay_load_ctrl(channel->node_list[node_cur].odd_key, channel->ctrl_ex.work_mode);

            /* Add P in */
            ret = spacc_symc_addbuf(channel->hard_num, channel->node_list[node_cur].src_phys_addr,
                channel->node_list[node_cur].byte_len, SPACC_BUF_TYPE_SYMC_IN, ctrl);
            intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);

            /* Add P out */
            ret = spacc_symc_addbuf(channel->hard_num, channel->node_list[node_cur].dst_phys_addr,
                channel->node_list[node_cur].byte_len, SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_NONE);
            intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);

            total += channel->node_list[node_cur].byte_len;
            channel->node_cur++;
            node_cur++;
        }

       /* For each compute, the total length of valid nodes list
        * must aligned with block size, otherwise can't recv interrupt,
        * which limit to hardware devising.
        */
        ret = drv_cipher_block_align(channel, total, node_cur);
        intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_block_align);
    }

    if (channel->node_cur == channel->node_num) { /* Set last flag */
        if (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_CCM) {
            /* Set CCM last flag */
            spacc_symc_addctrl(channel->hard_num, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_CCM_LAST);
        } else if (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_GCM) {
            /* Set GCM last flag */
            spacc_symc_addctrl(channel->hard_num, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_LAST);

            /* At the and of GCM, must add a empty P node to nodes list, limit to hardware devising */
            ret = spacc_symc_addbuf(channel->hard_num, 0x00, 0x00,
                SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_SYMC_OUT_LAST);
            intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, spacc_symc_addbuf);

            /* After compute P, compute LEN(C) for GCM */
            ret = drv_cipher_gcm_len(channel, channel->total_len);
            intf_func_fail_return(ret != HI_SUCCESS, ret, spacc_symc_addbuf);
        }

        /* Set symc last flag */
        spacc_symc_addctrl(channel->hard_num, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_LAST);
        spacc_symc_addctrl(channel->hard_num, SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_SYMC_OUT_LAST);
    }

    return HI_SUCCESS;
}

static hi_void drv_cipher_callback(hi_u32 chn_id)
{
    hi_s32 ret;
    spacc_symc_chn_s *channel = HI_NULL;

    if (chn_id >= SPACC_MAX_CHN) {
        hi_err_cipher("invalid chn_id %u\n", chn_id);
        return;
    }
    channel = &g_symc_chn[chn_id];

    /* Compute the follow nodes */
    if (channel->node_cur < channel->node_num) {
        ret = drv_cipher_add_nodes(channel, SYMC_INT_LEVEL);
        if (ret == HI_SUCCESS)
            spacc_symc_restart(channel->hard_num, channel->ctrl_ex.change_flags.bits_iv);
    } else {
        /* All the nodes compute finished, wake up user */
        channel->symc_done = HI_TRUE;
        hi_info_cipher("chn %d wake up\n", channel->hard_num);
        cipher_queue_wait_up(&channel->queue);
    }
}

static hi_s32 drv_cipher_enc_prepare(spacc_symc_chn_s *channel)
{
    hi_s32 ret = HI_SUCCESS;

    /* Before compute P, compute N and A for CCM firstly */
    if (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_CCM) {
        /* Format N and A, add to node list */
        ret = drv_cipher_ccm_na(channel, channel->total_len);
        intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_ccm_na);

        if (channel->total_len == 0) {
            /* If P is null, must add a empty node into node list, limit to hardware devising */
            ret = spacc_symc_addbuf(channel->hard_num, 0x00, 0x00,
                SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_SYMC_OUT_LAST);
            intf_func_fail_return(ret != SPACC_OK, HI_FAILURE, drv_cipher_ccm_na);
        }
    } else if (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_GCM) {
        /* Before compute P, compute A for GCM firstly */
        ret = drv_cipher_gcm_a(channel);
        intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_gcm_a);
    } else if ((channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_ECB) ||
              (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_CBC) ||
              (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_CFB) ||
              (channel->ctrl_ex.work_mode == HI_CIPHER_WORK_MODE_OFB)) {
       /* The length of data depend on alg and mode, which limit to hardware
        * for ecb/cbc/ofb/cfb, the total data length must aligned with block size.
        * for ctr/ccm/gcm, support any data length.
        */
        if (channel->total_len % channel->block_size != 0) {
            hi_err_cipher("PKG len must align with 16.\n");
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    return ret;
}

static hi_s32 drv_cipher_encrypt_multi(cipher_pkg_s *pkg, hi_bool is_decrypt)
{
    hi_s32 ret;
    hi_u32 i, soft_chn_id, remainder;
    spacc_symc_chn_s *channel = HI_NULL;
    cipher_data_compat_s *cipher_data = HI_NULL;

    intf_param_invalid_return((pkg->pkg_num == 0) || (pkg->pkg_num > MAX_MULTI_PKG_NUM));

    soft_chn_id = hi_handle_get_chn_id(pkg->ci_handle);
    channel = &g_symc_chn[soft_chn_id];

    hi_info_cipher("pkg_num %d\n", pkg->pkg_num);
    channel->node_list = cipher_malloc(pkg->pkg_num * sizeof(hi_cipher_data));
    intf_func_fail_return(channel->node_list == HI_NULL, HI_ERR_CIPHER_INVALID_POINT, cipher_malloc);

    cipher_data = (cipher_data_compat_s *)channel->node_list;

    /* copy node list from user space to kernel */
    ret = cipher_copy_from_user(channel->node_list,
        pkg->cipher_data, pkg->pkg_num * sizeof(hi_cipher_data));
    intf_func_fail_return(ret != 0, HI_FAILURE, cipher_copy_from_user);

    /* Compute and check the nodes length */
    channel->total_len = 0;

    for (i = pkg->pkg_num; i > 0; i--) {
        if (pkg->user_bit_width != MY_CPU_BIT_WIDTH) {
            channel->node_list[i - 1].byte_len = cipher_data[i - 1].byte_length;
            channel->node_list[i - 1].dst_phys_addr = cipher_data[i - 1].dst_phys_addr;
            channel->node_list[i - 1].src_phys_addr = cipher_data[i - 1].src_phys_addr;
        }

        /* Can't used the odd key */
        if (channel->node_list[i - 1].odd_key) {
            hi_err_cipher("Odd key unsupport.\n");
            return HI_FAILURE;
        }

        /* each node length can't be zero */
        if (channel->node_list[i - 1].byte_len == 0) {
            hi_err_cipher("PKG len must large than 0.\n");
            return HI_ERR_CIPHER_INVALID_PARA;
        }

        channel->total_len += channel->node_list[i - 1].byte_len;
    }

    ret = drv_cipher_enc_prepare(channel);
    intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_enc_prepare);

    channel->node_num = pkg->pkg_num;
    channel->node_cur = 0;

    /* For one time compute, the max nodes is 127, but 126 for first time,
     * here we compute 100 nodes firstly,
     * Because under each compute, the total length of valid nodes list
     * must aligned with block size, otherwise can't recv interrupt.
     * if the total length don't aligned with block size, we must
     * split joint the follow nodes with current nodes to multiple block size.
     * so it follows that, the nodes num for this time compute may be larger than 100,
     * The worst is that we need add 15 nodes(each node only carry 1 bye data)
     * within this time, that is the SYMC_INT_LEVEL must less than 127 - 16 - 1= 110.
     */
    remainder = cipher_min(pkg->pkg_num, SYMC_INT_LEVEL);
    ret = drv_cipher_add_nodes(channel, remainder);
    intf_func_fail_return(ret != HI_SUCCESS, ret, drv_cipher_add_nodes);

    channel->callback = drv_cipher_callback;
    channel->symc_done = HI_FALSE;
    spacc_symc_start(channel->hard_num, is_decrypt, channel->ctrl_ex.change_flags.bits_iv);
    return ret;
}

hi_s32 hi_drv_cipher_encrypt_multi(cipher_pkg_s *pkg)
{
    hi_s32 ret;
    hi_u32 soft_chn_id;
    spacc_symc_chn_s *channel = HI_NULL;

    if (pkg == HI_NULL) {
        hi_err_cipher("Invalid pkg.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if (cipher_mutex_lock(&g_symc_mutex)) {
        hi_err_cipher("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    ret = spacc_check_handle(pkg->ci_handle);
    if (ret != HI_SUCCESS)
        return ret;
    soft_chn_id = hi_handle_get_chn_id(pkg->ci_handle);
    channel = &g_symc_chn[soft_chn_id];

    ret = drv_cipher_encrypt_multi(pkg, HI_FALSE);
    if (ret != HI_SUCCESS) {
        if (channel->node_list != HI_NULL) {
            cipher_free(channel->node_list);
            channel->node_list = HI_NULL;
        }
        cipher_mutex_unlock(&g_symc_mutex);
        return ret;
    }

    ret = drv_cipher_symc_wait_done(channel, SPACC_TIME_OUT);
    if (ret != HI_SUCCESS)
        hi_err_cipher("spacc symc active failed, ret = 0x%x.\n", ret);

    if (channel->node_list != HI_NULL) {
        cipher_free(channel->node_list);
        channel->node_list = HI_NULL;
    }

    if (channel->ctrl_ex.change_flags.bits_iv == HI_CIPHER_IV_CHG_ONE_PKG)
        spacc_symc_getiv(channel->hard_num, channel->ctrl_ex.iv, sizeof(channel->ctrl_ex.iv));
    cipher_mutex_unlock(&g_symc_mutex);

    return ret;
}

hi_s32 hi_drv_cipher_decrypt_multi(cipher_pkg_s *pkg)
{
    hi_s32 ret;
    hi_u32 soft_chn_id;
    spacc_symc_chn_s *channel = HI_NULL;

    if (pkg == HI_NULL) {
        hi_err_cipher("Invalid pkg.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if (cipher_mutex_lock(&g_symc_mutex)) {
        hi_err_cipher("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    ret = spacc_check_handle(pkg->ci_handle);
    if (ret != HI_SUCCESS)
        return ret;
    soft_chn_id = hi_handle_get_chn_id(pkg->ci_handle);
    channel = &g_symc_chn[soft_chn_id];

    ret = drv_cipher_encrypt_multi(pkg, HI_TRUE);
    if (ret != HI_SUCCESS) {
        if (channel->node_list != HI_NULL) {
            cipher_free(channel->node_list);
            channel->node_list = HI_NULL;
        }
        cipher_mutex_unlock(&g_symc_mutex);
        return ret;
    }

    ret = drv_cipher_symc_wait_done(channel, SPACC_TIME_OUT);
    if (ret != HI_SUCCESS)
        hi_err_cipher("spacc symc active failed, ret = 0x%x.\n", ret);

    if (channel->node_list != HI_NULL) {
        cipher_free(channel->node_list);
        channel->node_list = HI_NULL;
    }

    if (channel->ctrl_ex.change_flags.bits_iv == HI_CIPHER_IV_CHG_ONE_PKG)
        spacc_symc_getiv(channel->hard_num, channel->ctrl_ex.iv, sizeof(channel->ctrl_ex.iv));
    cipher_mutex_unlock(&g_symc_mutex);

    return ret;
}

static hi_s32 drv_digest_config(cipher_hash_data_s *cipher_hash_data, spacc_ctrl_en *spacc_ctrl)
{
    hi_s32 ret;
    digest_alg_en digest_alg;
    digest_mode_en digest_mode;

    *spacc_ctrl = SPACC_CTRL_NONE;

    switch (cipher_hash_data->sha_type) {
        case HI_CIPHER_HASH_TYPE_SHA1:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA1:
            digest_alg = DIGEST_ALG_SHA1;
            digest_mode = DIGEST_MODE_HASH;
            break;
        case HI_CIPHER_HASH_TYPE_SHA224:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA224:
            digest_alg = DIGEST_ALG_SHA224;
            digest_mode = DIGEST_MODE_HASH;
            break;
        case HI_CIPHER_HASH_TYPE_SHA256:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA256:
            digest_alg = DIGEST_ALG_SHA256;
            digest_mode = DIGEST_MODE_HASH;
            break;
        case HI_CIPHER_HASH_TYPE_SHA384:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA384:
            digest_alg = DIGEST_ALG_SHA384;
            digest_mode = DIGEST_MODE_HASH;
            break;
        case HI_CIPHER_HASH_TYPE_SHA512:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA512:
            digest_alg = DIGEST_ALG_SHA512;
            digest_mode = DIGEST_MODE_HASH;
            break;
        case HI_CIPHER_HASH_TYPE_SM3:
            digest_alg = DIGEST_ALG_SM3;
            digest_mode = DIGEST_MODE_HASH;
            break;
        default:
            hi_err_cipher("Invalid hash type: 0x%x\n", cipher_hash_data->sha_type);
            return HI_ERR_CIPHER_INVALID_PARA;
    }

    ret = spacc_digest_config(cipher_hash_data->hard_chn, digest_alg, digest_mode, HI_FALSE);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("spacc set digest mode failed, chn %d, alg %d, mode %d.\n",
            cipher_hash_data->hard_chn, digest_alg, digest_mode);
        return HI_FAILURE;
    }

    *spacc_ctrl = ((hi_u32)*spacc_ctrl) | SPACC_CTRL_HASH_IN_FIRST;
    *spacc_ctrl = ((hi_u32)*spacc_ctrl) | SPACC_CTRL_HASH_IN_LAST;

    return HI_SUCCESS;

}

hi_s32 hi_drv_cipher_calc_hash_init(cipher_hash_data_s *cipher_hash_data)
{
    return HI_SUCCESS;
}

hi_s32 hi_drv_cipher_calc_hash_update(cipher_hash_data_s *cipher_hash_data)
{
    hi_s32 ret;
    spacc_ctrl_en spacc_ctrl;
    spacc_digest_chn_s *channel = HI_NULL;

    intf_param_invalid_return(cipher_hash_data->hard_chn >= SPACC_MAX_CHN);
    channel = &g_digest_chn[cipher_hash_data->hard_chn];

    /* configure hash register */
    ret = drv_digest_config(cipher_hash_data, &spacc_ctrl);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("cipher config failed, ret = 0x%x.\n", ret);
        return HI_FAILURE;
    }

    /* Add the phy of data to nodes list */
    ret = spacc_digest_addbuf(cipher_hash_data->hard_chn, make_ulong(cipher_hash_data->data_phy,
        cipher_hash_data->data_phy_high), cipher_hash_data->data_len, spacc_ctrl);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("spacc add in buf failed, ret = 0x%x.\n", ret);
        return HI_FAILURE;
    }

    channel->data_size = cipher_hash_data->data_len;
    channel->digest_done = HI_FALSE;

    /* Start working */
    ret = spacc_digest_start(cipher_hash_data->hard_chn, spacc_ctrl, cipher_hash_data->sha_val);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("spacc add in buf failed, ret = 0x%x.\n", ret);
        return HI_FAILURE;
    }

    /* Waiting hardware computing finished */
    ret = drv_cipher_digest_wait_done(channel);
    if (ret == HI_SUCCESS) /* Read hash result */
        spacc_digest_get(cipher_hash_data->hard_chn, cipher_hash_data->sha_val);

    return ret;
}

hi_s32 hi_drv_cipher_calc_hash_final(cipher_hash_data_s *cipher_hash_data)
{
    return hi_drv_cipher_calc_hash_update(cipher_hash_data);
}

hi_s32 hi_drv_cipher_get_handle_config_ex(cipher_config_ctrl_ex_s *config_ctrl)
{
    spacc_symc_chn_s *channel = HI_NULL;
    hi_u32 soft_chn_id;
    hi_s32 ret;

    if (config_ctrl == HI_NULL) {
        hi_err_cipher("Invalid params!\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if (cipher_mutex_lock(&g_symc_mutex)) {
        hi_err_cipher("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    ret = spacc_check_handle(config_ctrl->ci_handle);
    if (ret != HI_SUCCESS)
        return ret;
    soft_chn_id = hi_handle_get_chn_id(config_ctrl->ci_handle);
    channel = &g_symc_chn[soft_chn_id];

    crypto_memcpy(config_ctrl, sizeof(cipher_config_ctrl_ex_s), &channel->ctrl_ex, sizeof(channel->ctrl_ex));
    cipher_mutex_unlock(&g_symc_mutex);

    return ret;
}

hi_s32 hi_drv_cipher_get_iv(hi_u32 chn_id, hi_u32 iv[4]) /* 4 iv arr size */
{
    return spacc_symc_getiv(chn_id, iv, 16); /* 16 iv size */
}

#ifdef CIPHER_KLAD_SUPPORT
hi_s32 hi_drv_cipher_klad_encrypt_key(cipher_klad_key_s *klad_key)
{
    hi_s32 ret;

    if (klad_key == HI_NULL) {
        hi_err_cipher("Invalid params!\n");
        return HI_FAILURE;
    }

    if (cipher_mutex_lock(&g_symc_mutex)) {
        hi_err_cipher("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    ret = drv_cipher_klad_encrypt_key(klad_key->root_key,
        klad_key->klad_target, klad_key->clean_key, klad_key->encrypt_key);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("KladEncryptKey failed!\n");
        cipher_mutex_unlock(&g_symc_mutex);
        return ret;
    }

    cipher_mutex_unlock(&g_symc_mutex);

    return ret;
}
#endif
