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
 * Description   : drivers for read/write reg
 */

#include <cpu_func.h>
#include "cipher_adapt.h"
#include "spacc_union_define.h"
#include "spacc_body.h"
#include "spacc_reg.h"

#define spacc_point_return_if_null(p) \
    do { \
        if (!(p)) \
            return SPACC_ERR_NULL_POINT; \
    } while (0)

#define spacc_value_return_if_max(val, max) \
    do { \
        if ((val) >= (max)) \
            return SPACC_ERR_INVALID_PARAM; \
    } while (0)

#if 0
#define SAPCC_SYMC_IN_ENTRY_TOTAL_SIZE \
    (sizeof(struct spacc_symc_in_entry_t) * SPACC_MAX_DEPTH)
#define SAPCC_SYMC_OUT_ENTRY_TOTAL_SIZE \
    (sizeof(struct spacc_symc_out_entry_t) * SPACC_MAX_DEPTH)
#define SAPCC_SYMC_ENTRY_TOTAL_SIZE \
    (SAPCC_SYMC_IN_ENTRY_TOTAL_SIZE + SAPCC_SYMC_OUT_ENTRY_TOTAL_SIZE)
#define SAPCC_DIGEST_IN_ENTRY_TOTAL_SIZE \
    (sizeof(struct spacc_digest_in_entry_t) * SPACC_MAX_DEPTH)
#else
#define SAPCC_SYMC_IN_ENTRY_TOTAL_SIZE      (SPACC_PAGE_SIZE)
#define SAPCC_SYMC_OUT_ENTRY_TOTAL_SIZE     (SPACC_PAGE_SIZE)
#define SAPCC_DIGEST_IN_ENTRY_TOTAL_SIZE    (SPACC_PAGE_SIZE)
#endif

#define spacc_err(fmt, ...)     \
    HI_PRINT("\033[0;31m%s-%03d"fmt"\033[0m;", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define spacc_dbg(fmt...)       // HI_PRINT(fmt)

/* spacc symc int entry struct which is defined by hardware, you can't change it */
struct spacc_symc_in_entry_t {
    unsigned int spacc_cmd: 2;
    unsigned int rev1: 6;
    unsigned int sym_ctrl: 7;
    unsigned int rev2: 1;
    unsigned int gcm_iv_len: 4;
    unsigned int rev3: 12;
    unsigned int sym_start_addr_high;
    unsigned int sym_start_addr;
    unsigned int sym_alg_length;
    unsigned int symc_iv[4]; /* 4 iv len */
};

/* spacc digest in entry struct which is defined by hardware, you can't change it */
struct spacc_digest_in_entry_t {
    unsigned int spacc_cmd: 2;
    unsigned int rev1: 6;
    unsigned int hash_ctrl: 6;
    unsigned int rev2: 18;
    unsigned int hash_start_addr;
    unsigned int hash_alg_length;
    unsigned int hash_start_addr_high;
};

/* spacc symc out entry struct which is defined by hardware, you can't change it */
struct spacc_symc_out_entry_t {
    unsigned int rev1: 8;
    unsigned int aes_ctrl: 4;
    unsigned int rev2: 20;
    unsigned int sym_start_addr;
    unsigned int sym_alg_length;
    unsigned int hash_rslt_start_addr;
    unsigned int tag[4]; /* 4 tag len */
};

struct spacc_symc_context {
    symc_alg_en  symc_alg;
    symc_mode_en symc_mode;
    unsigned int symc_iv[4]; /* 4 iv len */
    unsigned int symc_ivlen;

    unsigned int *pad_vir_addr;
    unsigned int pad_phy_addr;

    struct spacc_symc_in_entry_t*   entry_symc_in;
    struct spacc_symc_out_entry_t*  entry_symc_out;
    struct spacc_digest_in_entry_t* entry_digest_in;

    unsigned int entry_symc_in_depth;
    unsigned int entry_symc_out_depth;
    unsigned int symc_cur_in_nodes;
    unsigned int symc_cur_out_nodes;
};

struct spacc_digest_context {
    digest_alg_en  digest_alg;
    digest_mode_en digest_mode;
    unsigned int digest_key[SPACC_MAX_HMAC_KEY_LEN / 4]; /* 4 */
    unsigned int digest_klen;
    unsigned int digest_len;
    unsigned int digest_blen;

    struct spacc_digest_in_entry_t* entry_digest_in;
    unsigned int entry_digest_in_depth;
    unsigned int digest_cur_in_nodes;

    unsigned int hard_key;
};

void *g_spacc_reg_base = 0;
static struct spacc_symc_context   g_symc_context[SPACC_LOGIC_MAX_CHN];
static struct spacc_digest_context g_digest_context[SPACC_LOGIC_MAX_CHN];

static hi_void spacc_secure_chn_enable(hi_void)
{
    u_sec_chn_cfg sec_chn_cfg;

    sec_chn_cfg.u32 = spacc_read(SEC_CHN_CFG);
    sec_chn_cfg.bits.cipher_sec_chn_cfg |= SPACC_CHN_MASK;
    sec_chn_cfg.bits.hash_sec_chn_cfg |= SPACC_CHN_MASK;
    spacc_write(SEC_CHN_CFG, sec_chn_cfg.u32);
    spacc_dbg("SEC_CHN_CFG[%p]: 0x%x\n", SEC_CHN_CFG, sec_chn_cfg.u32);
    hal_cipher_read_reg(SEC_CHN_CFG, &sec_chn_cfg.u32);
}

static hi_void spacc_smmu_enable(unsigned int mmu_table_addr)
{
#ifdef SMMU_ENABLE
    u_cipher_in_smmu_en cipher_in_smmu_en;
    u_out_smmu_en out_smmu_en;
    u_hash_in_smmu_en hash_in_smmu_en;

    cipher_in_smmu_en.u32 = spacc_read(CIPHER_IN_SMMU_EN);
    out_smmu_en.u32 = spacc_read(OUT_SMMU_EN);
    hash_in_smmu_en.u32 = spacc_read(HASH_IN_SMMU_EN);

    cipher_in_smmu_en.bits.cipher_in_chan_rd_dat_smmu_en  |= SPACC_CHN_MASK >> 1;
    cipher_in_smmu_en.bits.cipher_in_chan_rd_node_smmu_en |= SPACC_CHN_MASK >> 1;

    out_smmu_en.bits.out_chan_wr_dat_smmu_en  |= SPACC_CHN_MASK >> 1;
    out_smmu_en.bits.out_chan_rd_node_smmu_en |= SPACC_CHN_MASK >> 1;

    hash_in_smmu_en.bits.hash_in_chan_rd_dat_smmu_en |= SPACC_CHN_MASK >> 1;
    hash_in_smmu_en.bits.hash_in_chan_rd_node_smmu_en |= SPACC_CHN_MASK >> 1;

    spacc_write(CIPHER_IN_SMMU_EN, cipher_in_smmu_en.u32);
    spacc_write(OUT_SMMU_EN, out_smmu_en.u32);
    spacc_write(HASH_IN_SMMU_EN, hash_in_smmu_en.u32);

    spacc_dbg("CIPHER_IN_SMMU_EN[%p]: 0x%x\n", CIPHER_IN_SMMU_EN, cipher_in_smmu_en.u32);
    spacc_dbg("OUT_SMMU_EN[%p]      : 0x%x\n", OUT_SMMU_EN, out_smmu_en.u32);
    spacc_dbg("HASH_IN_SMMU_EN[%p]  : 0x%x\n", HASH_IN_SMMU_EN, hash_in_smmu_en.u32);
#ifdef REE_NONSECURE_ENABLE
    spacc_write(NORM_SMMU_START_ADDR, mmu_table_addr);
#else
    spacc_write(SEC_SMMU_START_ADDR, mmu_table_addr);
#endif
#endif // SMMU_ENABLE
}

static hi_void spacc_int_enable(hi_void)
{
#ifdef INT_ENABLE
    u_cipher_int_en cipher_int_en;
    u_hash_int_en hash_int_en;

    cipher_int_en.u32 = spacc_read(CIPHER_INT_EN);
    hash_int_en.u32 = spacc_read(HASH_INT_EN);

    cipher_int_en.bits.cipher_chn_obuf_en |= SPACC_CHN_MASK;
    hash_int_en.bits.hash_chn_oram_en |= SPACC_CHN_MASK;

    cipher_int_en.bits.cipher_nsec_int_en = 1;
    hash_int_en.bits.hash_int_en = 1;

    spacc_write(CIPHER_INT_EN, cipher_int_en.u32);
    spacc_write(HASH_INT_EN, hash_int_en.u32);
    spacc_dbg("CIPHER_INT_EN: 0x%x\n", cipher_int_en.u32);
    spacc_dbg("HASH_INT_EN: 0x%x\n", hash_int_en.u32);
#endif
}

static hi_void spacc_config_start_addr(unsigned long entry_phy_addr, hi_void *entry_via_addr)
{
    unsigned int i;
    hi_size_t page_phy;
    hi_void *page_via = HI_NULL;

    page_phy = entry_phy_addr;
    page_via = entry_via_addr;

    for (i = CIPHER_PKG_N_CHN_MIN; i <= CIPHER_PKG_N_CHN_MAX; i++) {
        u_chann_cipher_in_node_cfg cipher_in_cfg;
        u_chann_cipher_out_node_cfg cipher_out_cfg;
        u_chann_hash_in_node_cfg hash_in_cfg;

        /* set total num and start addr for cipher in node */
        cipher_in_cfg.u32  = spacc_read(chn_n_cipher_in_node_cfg(i));
        cipher_in_cfg.bits.cipher_in_node_total_num = SPACC_MAX_DEPTH;
        spacc_write(chn_n_cipher_in_node_cfg(i), cipher_in_cfg.u32);
        spacc_write(chn_n_cipher_in_node_start_addr(i), get_ulong_low(page_phy));
        spacc_write(chn_n_cipher_in_node_start_addr_high(i), get_ulong_high(page_phy));
        spacc_dbg("chn_n_cipher_in_node_cfg[%p]: \t0x%x, PHY: 0x%zx, VIA %p\n",
            chn_n_cipher_in_node_cfg(i), cipher_in_cfg.u32, page_phy, page_via);
        g_symc_context[i].entry_symc_in = (struct spacc_symc_in_entry_t*)page_via;
        g_symc_context[i].symc_cur_in_nodes = cipher_in_cfg.bits.cipher_in_node_wptr;
        g_symc_context[i].entry_symc_in_depth = 0;
        page_via += SAPCC_SYMC_IN_ENTRY_TOTAL_SIZE;
        page_phy += SAPCC_SYMC_IN_ENTRY_TOTAL_SIZE;

        /* set total num and start addr for cipher out node */
        cipher_out_cfg.u32 = spacc_read(chn_n_cipher_out_node_cfg(i));
        cipher_out_cfg.bits.cipher_out_node_total_num = SPACC_MAX_DEPTH;
        spacc_write(chn_n_cipher_out_node_cfg(i), cipher_out_cfg.u32);
        spacc_write(chn_n_cipher_out_node_start_addr(i), get_ulong_low(page_phy));
        spacc_write(chn_n_cipher_out_node_start_addr_high(i), get_ulong_high(page_phy));
        spacc_dbg("chn_n_cipher_out_node_cfg[%p]: \t0x%x, PHY: 0x%zx, VIA %p\n",
            chn_n_cipher_out_node_cfg(i), cipher_out_cfg.u32, page_phy, page_via);
        g_symc_context[i].entry_symc_out = (struct spacc_symc_out_entry_t*)page_via;
        g_symc_context[i].symc_cur_out_nodes = cipher_out_cfg.bits.cipher_out_node_wptr;
        g_symc_context[i].entry_symc_out_depth = 0;
        page_via += SAPCC_SYMC_OUT_ENTRY_TOTAL_SIZE;
        page_phy += SAPCC_SYMC_OUT_ENTRY_TOTAL_SIZE;

        /* set total num and start addr for hash in node */
        hash_in_cfg.u32 = spacc_read(chn_n_hash_in_node_cfg(i));
        hash_in_cfg.bits.hash_in_node_total_num = SPACC_MAX_DEPTH;
        spacc_write(chn_n_hash_in_node_cfg(i), hash_in_cfg.u32);
        spacc_write(chn_n_hash_in_node_start_addr(i), get_ulong_low(page_phy));
        spacc_write(chn_n_hash_in_node_start_addr_high(i), get_ulong_high(page_phy));
        spacc_dbg("chn_n_hash_in_node_cfg[%p]: \t0x%x, PHY: 0x%zx, VIA %p\n",
            chn_n_hash_in_node_cfg(i), hash_in_cfg.u32, page_phy, page_via);
        g_digest_context[i].entry_digest_in = (struct spacc_digest_in_entry_t*)page_via;
        g_digest_context[i].digest_cur_in_nodes = hash_in_cfg.bits.hash_in_node_wptr;
        g_digest_context[i].entry_digest_in_depth = 0;
        page_via += SAPCC_DIGEST_IN_ENTRY_TOTAL_SIZE;
        page_phy += SAPCC_DIGEST_IN_ENTRY_TOTAL_SIZE;
    }
}

/**
 * spacc_init - spacc hardware initialization.
 * @reg_base: virtual address of spacc module which be accessed by CPU
 * @mmu_table_addr: mmu base table physical addr, if disable mmu, set it to 0
 * @entry_phy_addr: a consecutive physical memory, used for nodes
 *                  list of symc-in, symc-out and hash-in, the size
 *                   must large than spacc_get_node_list_size().
 * @entry_via_addr: virtual address of entry_phy_addr.
 *
 * Description:
 *   spacc hardware initialization as follows:
 *   - reset global var.
 *   - enable interrupt
 *   - set nodes list addr
 *   - set mmu table addr
 *   - configureure hardware register
 *
 * Context:
 *   this function must be called one time in the beginning.
 */
int spacc_init(hi_void *reg_base, unsigned int mmu_table_addr,
               unsigned long entry_phy_addr, hi_void *entry_via_addr)
{
    spacc_point_return_if_null(reg_base);
    spacc_point_return_if_null(entry_via_addr);

    crypto_memset(&g_symc_context, sizeof(g_symc_context), 0, sizeof(g_symc_context));
    crypto_memset(&g_digest_context, sizeof(g_digest_context), 0, sizeof(g_digest_context));
    crypto_memset(entry_via_addr, spacc_get_node_list_size(), 0, spacc_get_node_list_size());

    g_spacc_reg_base = reg_base;

    spacc_secure_chn_enable();
    spacc_smmu_enable(mmu_table_addr);
    spacc_int_enable();

    /* configure start addr for in-node and out-node */
    spacc_config_start_addr(entry_phy_addr, entry_via_addr);

    return SPACC_OK;
}

/**
 * spacc_deinit - spacc hardware deinit.
 */
int spacc_deinit(void)
{
    return SPACC_OK;
}

/**
 * spacc_get_node_list_size - return the total size of nodes lists memory required by the drive.
 */
unsigned int spacc_get_node_list_size(void)
{
    /*********************************************************************
    symc in node page x1| symc out node page x0.5 | hash in node page x0.5
    *********************************************************************/
    return (SPACC_PAGE_SIZE * 3) * (CIPHER_PKG_N_CHN_MAX - CIPHER_PKG_N_CHN_MIN + 1); /* 3 */
}

int spacc_symc_getiv(unsigned int chn_num, unsigned int *iv, unsigned int ivsize)
{
    unsigned int i;

    spacc_value_return_if_max(chn_num, SPACC_LOGIC_MAX_CHN);

    for (i = 0; i < 4; i++) /* 4 iv len */
        iv[i] = spacc_read(chn_n_cipher_iv_out(chn_num));

    return SPACC_OK;
}

/*
 * spacc_symc_gettag - get the tag for CCM/GCM.
 */
int spacc_symc_gettag(unsigned int chn_num, unsigned char *tag)
{
    struct spacc_symc_context *info = &g_symc_context[chn_num];
    u_chann_cipher_out_node_cfg out_node_cfg;
    unsigned int last;

    spacc_value_return_if_max(chn_num, SPACC_LOGIC_MAX_CHN);

    out_node_cfg.u32 = spacc_read(chn_n_cipher_out_node_cfg(chn_num));
    last = out_node_cfg.bits.cipher_out_node_wptr;
    last = (last == 0) ? (SPACC_MAX_DEPTH - 1) : (last - 1);

    flush_cache(cipher_align_down((hi_size_t)(uintptr_t)info->entry_symc_out),
        cipher_align_size((hi_size_t)(uintptr_t)info->entry_symc_out, SPACC_PAGE_SIZE));

    crypto_memcpy(tag, 16, /* 16 tag size */
        info->entry_symc_out[last].tag, sizeof(info->entry_symc_out[last].tag));

    return SPACC_OK;
}

/**
 * spacc_symc_setkey - set even key and odd key for symc.
 * @chn_num: the logic channel number, must 1~7.
 * @even_key: even key
 * @odd_key:  odd key
 * @klen:     length of key.
 *
 * Description:
 *   the odd key only valid for aes ecb/cbc/ofb/cfb/ctr, and the data to encrypt/decprypt
 *   must be aligned with 64.
 *
 */
int spacc_symc_setkey(unsigned int chn_num, unsigned int *even_key, unsigned int *odd_key, unsigned int klen)
{
    struct spacc_symc_context *info = &g_symc_context[chn_num];
    unsigned int i;

    spacc_value_return_if_max(chn_num, SPACC_LOGIC_MAX_CHN);

    spacc_point_return_if_null(even_key);
    spacc_point_return_if_null(odd_key);
    spacc_value_return_if_max(klen, 49); /* 49 klen max */
    /* Set even key */
    spacc_write(ODD_EVEN_KEY_SEL, 0x00);
    for (i = 0; (i < klen / 4) && (i < 8); i++) { /* 4, 8 */
        spacc_write(cipher_key(chn_num) + i * 4, even_key[i]); /* 4 */
        spacc_dbg("EVEN key[%p]: 0x%x\n", cipher_key(chn_num) + i * 4, even_key[i]); /* 4 */
    }

    if (info->symc_alg == SYMC_ALG_SM1) {
        for (i = 0; i < 4; i++) { /* 4  */
            spacc_write(sm1_sk(chn_num) + i * 4, even_key[i + 8]); /* 4, 8 */
            spacc_dbg("SK[%p]: 0x%x\n", sm1_sk(chn_num) + i * 4, even_key[i + 8]); /* 4, 8 */
        }
    }

    return SPACC_OK;
}

/**
 * spacc_symc_setiv - set iv for symc.
 * @chn_num: the logic channel number, must 1~7.
 * @iv: the initialization vector
 * @ivlen:  length of iv.
 *
 * Description:
 *   here store the iv to global structure of channel, don't set to logic,
 *   because the IV must be set in the nodes list.
 *
 */
int spacc_symc_setiv(unsigned int chn_num, unsigned char *iv, unsigned int ivlen)
{
    struct spacc_symc_context *info = &g_symc_context[chn_num];

    spacc_value_return_if_max(chn_num, SPACC_LOGIC_MAX_CHN);
    spacc_point_return_if_null(iv);
    spacc_value_return_if_max(ivlen, 33); /* 33 iv max size */

    crypto_memset(info->symc_iv, sizeof(info->symc_iv), 0, sizeof(info->symc_iv));
    crypto_memcpy(info->symc_iv, sizeof(info->symc_iv), iv, ivlen);
    info->symc_ivlen = ivlen;

    return SPACC_OK;
}

/*
 * spacc_symc_addbuf - filling the buf addr and length of
 *   encrypt/decrypt data into nodes list.
 */
int spacc_symc_addbuf(unsigned int chn_num, unsigned long buf_phy,
    unsigned int buf_size, spacc_buf_type_en type, unsigned int ctrl)
{
    struct spacc_symc_context *info = &g_symc_context[chn_num];
    unsigned int id, size;
    void *addr = HI_NULL;

    spacc_value_return_if_max(chn_num, SPACC_LOGIC_MAX_CHN);
    switch (type) {
        case SPACC_BUF_TYPE_SYMC_IN:
            id = info->symc_cur_in_nodes++;
            addr = &info->entry_symc_in[id];
            size = sizeof(struct spacc_symc_in_entry_t);
            crypto_memset(addr, sizeof(info->entry_symc_in[id]), 0, size);
            info->entry_symc_in[id].spacc_cmd = 0x00;
            info->entry_symc_in[id].sym_start_addr = get_ulong_low(buf_phy);
            info->entry_symc_in[id].sym_start_addr_high = get_ulong_high(buf_phy);
            info->entry_symc_in[id].sym_alg_length = buf_size;
            info->entry_symc_in[id].sym_ctrl = ctrl;
            info->entry_symc_in_depth++;
            info->symc_cur_in_nodes %= SPACC_MAX_DEPTH;
            spacc_dbg("chn %d, add symc in buf: id %d, addr 0x%zx, len 0x%x, ctrl 0x%x\n",
                chn_num, id, buf_phy, buf_size, ctrl);
            break;
        case SPACC_BUF_TYPE_SYMC_OUT:
            id = info->symc_cur_out_nodes++;
            addr = &info->entry_symc_out[id];
            size = sizeof(struct spacc_symc_out_entry_t);
            crypto_memset(addr, sizeof(info->entry_symc_out[id]), 0, size);
            info->entry_symc_out[id].sym_start_addr = get_ulong_low(buf_phy);
            info->entry_symc_out[id].tag[0] = get_ulong_high(buf_phy);
            info->entry_symc_out[id].sym_alg_length = buf_size;
            info->entry_symc_out[id].aes_ctrl = ctrl;
            info->entry_symc_out_depth++;
            info->symc_cur_out_nodes %= SPACC_MAX_DEPTH;
            spacc_dbg("chn %d, add symc out buf: id %d, addr 0x%zx, len 0x%x\n", chn_num, id, buf_phy, buf_size);
            break;
        default:
            return SPACC_ERR_INVALID_PARAM;
    }

    flush_cache(cipher_align_down(buf_phy), cipher_align_size(buf_phy, buf_size));

    return SPACC_OK;
}

/*
 * spacc_symc_addbuf - add a flags to the last valid nodes.
 */
int spacc_symc_addctrl(unsigned int chn_num, spacc_buf_type_en type, unsigned int ctrl)
{
    struct spacc_symc_context *info = &g_symc_context[chn_num];
    unsigned int id;

    spacc_value_return_if_max(chn_num, SPACC_LOGIC_MAX_CHN);

    switch (type) {
        case SPACC_BUF_TYPE_SYMC_IN:
            id = (info->symc_cur_in_nodes == 0) ? SPACC_MAX_DEPTH - 1 : info->symc_cur_in_nodes - 1;
            info->entry_symc_in[id].sym_ctrl |= ctrl;
            break;
        case SPACC_BUF_TYPE_SYMC_OUT:
            id = (info->symc_cur_out_nodes == 0) ? SPACC_MAX_DEPTH - 1 : info->symc_cur_out_nodes - 1;
            info->entry_symc_out[id].aes_ctrl |= ctrl;
            break;
        default:
            return SPACC_ERR_INVALID_PARAM;
    }

    return SPACC_OK;
}

/*
 * spacc_symc_configure - configure logic register, such as alg, mode, key len and so on.
 */
int spacc_symc_config(unsigned int chn_num, spacc_symc_config_s *symc_cfg,
    unsigned char sm1_round_num, unsigned char hard_key)
{
    struct spacc_symc_context *info = &g_symc_context[chn_num];
    u_chann_cipher_ctrl cipher_ctrl;
    unsigned int symc_klen = 0;

    spacc_value_return_if_max(chn_num, SPACC_LOGIC_MAX_CHN);
    spacc_value_return_if_max(symc_cfg->symc_alg, SYMC_ALG_COUNT);
    spacc_value_return_if_max(symc_cfg->symc_mode, SYMC_MODE_COUNT);
    spacc_value_return_if_max(symc_cfg->symc_width, SYMC_DAT_WIDTH_COUNT);

    if (symc_cfg->symc_alg == SYMC_ALG_AES)
        symc_klen = symc_cfg->key_len / 8 - 2; /* 8, 2 */
    else if (symc_cfg->symc_alg == SYMC_ALG_3DES)
        symc_klen = (symc_cfg->key_len == 16 ? 3 : 2); /* 16, 3, 2 */

    cipher_ctrl.u32 = spacc_read(chn_n_cipher_ctrl(chn_num));
    cipher_ctrl.bits.sym_chn_sm1_round_num = sm1_round_num;
    cipher_ctrl.bits.sym_chn_key_sel = hard_key;
    cipher_ctrl.bits.sym_chn_key_length = symc_klen;
    cipher_ctrl.bits.sym_chn_dat_width = symc_cfg->symc_width;
    cipher_ctrl.bits.sym_chn_decrypt = 0x00;
    cipher_ctrl.bits.sym_chn_alg_sel = symc_cfg->symc_alg;
    cipher_ctrl.bits.sym_chn_alg_mode = symc_cfg->symc_mode;
    spacc_write(chn_n_cipher_ctrl(chn_num), cipher_ctrl.u32);
    spacc_dbg("chn_n_cipher_ctrl(%d): 0x%x\n", chn_num, cipher_ctrl.u32);

    info->symc_alg = symc_cfg->symc_alg;
    info->symc_mode = symc_cfg->symc_mode;
    info->entry_symc_in_depth = 0;
    info->entry_symc_out_depth = 0;

    return SPACC_OK;
}

static int spacc_config_out_node(unsigned int chn_num, struct spacc_symc_context *info)
{
    u_chann_cipher_out_node_cfg out_node_cfg;
    unsigned int ptr;

    out_node_cfg.u32 = spacc_read(chn_n_cipher_out_node_cfg(chn_num));
    if (out_node_cfg.bits.cipher_out_node_wptr != out_node_cfg.bits.cipher_out_node_rptr) {
        spacc_err("Error, chn %d is busy.\n", chn_num);
        return SPACC_ERR_BUSY;
    }
    ptr = out_node_cfg.bits.cipher_out_node_wptr + info->entry_symc_out_depth;
    out_node_cfg.bits.cipher_out_node_wptr = ptr % SPACC_MAX_DEPTH;
    out_node_cfg.bits.cipher_out_node_mpackage_int_level = info->entry_symc_out_depth;
    spacc_write(chn_n_cipher_out_node_cfg(chn_num), out_node_cfg.u32);
    spacc_dbg("chn_n_cipher_out_node_cfg: 0x%x\n", out_node_cfg.u32);

    return SPACC_OK;
}

static void spacc_config_in_node(unsigned int chn_num, struct spacc_symc_context *info)
{
    u_chann_cipher_in_node_cfg in_node_cfg;
    unsigned int ptr;

    in_node_cfg.u32 = spacc_read(chn_n_cipher_in_node_cfg(chn_num));
    ptr = in_node_cfg.bits.cipher_in_node_wptr + info->entry_symc_in_depth;
    in_node_cfg.bits.cipher_in_node_wptr = ptr % SPACC_MAX_DEPTH;
    in_node_cfg.bits.cipher_in_node_mpackage_int_level = info->entry_symc_in_depth;

    spacc_dbg("chn_n_cipher_in_node_cfg: 0x%x\n", in_node_cfg.u32);
    spacc_dbg("chn %d, start 0x%x from 0x%x to 0x%x\n", chn_num, info->entry_symc_in_depth,
        in_node_cfg.bits.cipher_in_node_rptr, in_node_cfg.bits.cipher_in_node_wptr);

    /* move forward the in-node ptr to action the symc working */
    spacc_write(chn_n_cipher_in_node_cfg(chn_num), in_node_cfg.u32);
}

static void spacc_cipher_chn_crypt(unsigned int chn_num, unsigned int decrypt)
{
    u_chann_cipher_ctrl cipher_ctrl;

    cipher_ctrl.u32 = spacc_read(chn_n_cipher_ctrl(chn_num));
    cipher_ctrl.bits.sym_chn_decrypt = decrypt;
    spacc_write(chn_n_cipher_ctrl(chn_num), cipher_ctrl.u32);
}

/*
 * spacc_symc_start - action the symc start to processing the node list.
 */
int spacc_symc_start(unsigned int chn_num, unsigned int decrypt, unsigned int iv_set_flag)
{
    unsigned int cur, i, j, node;
    u_chann_cipher_in_node_cfg in_node_cfg;
    struct spacc_symc_context *info = &g_symc_context[chn_num];

    spacc_value_return_if_max(chn_num, SPACC_LOGIC_MAX_CHN);

    in_node_cfg.u32 = spacc_read(chn_n_cipher_in_node_cfg(chn_num));
    cur = in_node_cfg.bits.cipher_in_node_rptr;
    spacc_dbg("cur %d, depth %d, symc_iv Len %d\n", cur, info->entry_symc_in_depth, info->symc_ivlen);
    for (j = 0; j < info->entry_symc_in_depth; j++) {
        if (info->symc_ivlen > 0) {
            /* Write iv to all nodes */
            node = (cur + j) % SPACC_MAX_DEPTH;
            for (i = 0; i < 4; i++) { /* 4 iv len */
                info->entry_symc_in[node].symc_iv[i] = info->symc_iv[i];
                spacc_dbg("symc_iv[%d]: 0x%x\n", i, info->symc_iv[i]);
            }

            /* Set iv len for GCM */
            if (info->symc_mode == SYMC_MODE_GCM)
                info->entry_symc_in[node].gcm_iv_len = info->symc_ivlen - 1;
            else
                info->entry_symc_in[node].gcm_iv_len = 0;

            /* IV only be set for first node. */
            if (iv_set_flag == HI_CIPHER_IV_CHG_ONE_PKG) {
                info->entry_symc_in[node].sym_ctrl |= SPACC_CTRL_SYMC_IN_FIRST;
                iv_set_flag = 0;
            } else if ((iv_set_flag == HI_CIPHER_IV_CHG_ALL_PKG) &&
                (info->symc_mode != SYMC_MODE_CCM) && (info->symc_mode != SYMC_MODE_GCM)) {
                /* IV will be set for each node. */
                info->entry_symc_in[node].sym_ctrl |= SPACC_CTRL_SYMC_IN_FIRST | SPACC_CTRL_SYMC_IN_LAST;
            }
        }
    }

    if (spacc_config_out_node(chn_num, info) != SPACC_OK)
        return SPACC_ERR_BUSY;

    /* encrypt or decrypt */
    spacc_cipher_chn_crypt(chn_num, decrypt);

    flush_cache(cipher_align_down((hi_size_t)(uintptr_t)info->entry_symc_in),
        cipher_align_size((hi_size_t)(uintptr_t)info->entry_symc_in, SPACC_PAGE_SIZE));
    flush_cache(cipher_align_down((hi_size_t)(uintptr_t)info->entry_symc_out),
        cipher_align_size((hi_size_t)(uintptr_t)info->entry_symc_out, SPACC_PAGE_SIZE));

    /* spacc_config_in_node must be placed after flush_cache, otherwwise it may be crypt timeout */
    spacc_config_in_node(chn_num, info);

    /* all the nodes are processing, reset the depth to 0 */
    info->entry_symc_in_depth = 0;
    info->entry_symc_out_depth = 0;

    return SPACC_OK;
}

/*
 * spacc_symc_restart - continue to action the symc to processing the node list.
 */
void spacc_symc_restart(unsigned int chn_num, unsigned int iv_set_flag)
{
    unsigned int cur, i, j, node;
    u_chann_cipher_in_node_cfg in_node_cfg;
    struct spacc_symc_context *info = &g_symc_context[chn_num];

    if (info->entry_symc_in_depth == 0)
        return;

    in_node_cfg.u32 = spacc_read(chn_n_cipher_in_node_cfg(chn_num));
    if ((iv_set_flag == HI_CIPHER_IV_CHG_ALL_PKG) &&
        (info->symc_mode != SYMC_MODE_CCM) && (info->symc_mode != SYMC_MODE_GCM)) {
        cur = in_node_cfg.bits.cipher_in_node_wptr;
        for (j = 0; j < info->entry_symc_in_depth; j++) {
            if (info->symc_ivlen == 0)
                continue;

            node = (cur + j) % SPACC_MAX_DEPTH;
            for (i = 0; i < 4; i++) { /* 4 iv len */
                info->entry_symc_in[node].symc_iv[i] = info->symc_iv[i];
                spacc_dbg("symc_iv[%d]: 0x%x\n", i, info->symc_iv[i]);
            }
            info->entry_symc_in[node].sym_ctrl |= 0x01;
        }
    }

    if (spacc_config_out_node(chn_num, info) != SPACC_OK)
        return;
    spacc_config_in_node(chn_num, info);

    flush_cache(cipher_align_down((hi_size_t)(uintptr_t)info->entry_symc_in),
        cipher_align_size((hi_size_t)(uintptr_t)info->entry_symc_in, SPACC_PAGE_SIZE));
    flush_cache(cipher_align_down((hi_size_t)(uintptr_t)info->entry_symc_out),
        cipher_align_size((hi_size_t)(uintptr_t)info->entry_symc_out, SPACC_PAGE_SIZE));

    info->entry_symc_in_depth = 0;
    info->entry_symc_out_depth = 0;
}

/*
 * spacc_symc_get_free_nodes - get the num of free spacc nodes.
 */
unsigned int spacc_symc_get_free_nodes(unsigned int chn_num)
{
    unsigned int read, write, node;
    u_chann_cipher_in_node_cfg in_node_cfg;
    struct spacc_symc_context *info = &g_symc_context[chn_num];

    in_node_cfg.u32 = spacc_read(chn_n_cipher_in_node_cfg(chn_num));
    read  = in_node_cfg.bits.cipher_in_node_rptr;
    write = in_node_cfg.bits.cipher_in_node_wptr;

    node = (read + SPACC_MAX_DEPTH - write - 1) % SPACC_MAX_DEPTH;

    return (node - info->entry_symc_in_depth);
}

/*
 * spacc_symc_done_try - get the int status of symc.
 */
unsigned int spacc_symc_done_notify(void)
{
    u_cipher_int_raw int_raw;
    unsigned int chn_mask;

    int_raw.u32 = spacc_read(CIPHER_INT_RAW);
    int_raw.bits.cipher_chn_obuf_raw &= SPACC_CHN_MASK;
    chn_mask = int_raw.bits.cipher_chn_obuf_raw;
    spacc_write(CIPHER_INT_RAW, int_raw.u32);

    return chn_mask;
}

/*
 * spacc_symc_done_try - test the int status of symc channel.
 */
unsigned int spacc_symc_done_try(unsigned int chn_num)
{
    u_cipher_int_raw int_raw;
    unsigned int chn_mask;

    int_raw.u32 = spacc_read(CIPHER_INT_RAW);
    int_raw.bits.cipher_chn_obuf_raw &= 0x01 << chn_num;
    chn_mask = int_raw.bits.cipher_chn_obuf_raw;

    /* Clean raw int */
    int_raw.u32 = 0x00;
    int_raw.bits.cipher_chn_obuf_raw = chn_mask;
    spacc_write(CIPHER_INT_RAW, int_raw.u32);

    return chn_mask ? 1 : 0;
}

/*
 * spacc_symc_get_err_code - get the error code of symc.
 */
unsigned int spacc_symc_get_err_code(unsigned int chn_num,
                                     unsigned int *src_addr,
                                     unsigned int *dst_addr)
{
    *src_addr = spacc_read(chn_n_cipher_in_buf_rptr(chn_num));
    *dst_addr = spacc_read(chn_n_cipher_out_buf_rptr(chn_num));

    return spacc_read(CALC_ERR);
}

/*
 * spacc_digest_configure - configure the hash ctrl register.
 */
int spacc_digest_config(unsigned int chn_num,
                        digest_alg_en digest_alg,
                        digest_mode_en digest_mode,
                        unsigned char hard_key)
{
    struct spacc_digest_context *info = &g_digest_context[chn_num];
    u_chann_hash_ctrl hash_ctrl;

    spacc_value_return_if_max(chn_num, SPACC_LOGIC_MAX_CHN);
    spacc_value_return_if_max(digest_alg, DIGEST_ALG_COUNT);
    spacc_value_return_if_max(digest_mode, DIGEST_MODE_COUNT);

    info->digest_alg = digest_alg;
    info->digest_mode = digest_mode;

    switch (digest_alg) {
        case DIGEST_ALG_SHA1:
            info->digest_len = 20;   /* 20 sha1 digest len */
            info->digest_blen = 64;  /* 64 sha1 digest blen */
            break;
        case DIGEST_ALG_SHA224:
            info->digest_len = 28;   /* 28 sha1 digest len */
            info->digest_blen = 64;  /* 64 sha1 digest blen */
            break;
        case DIGEST_ALG_SM3:
        case DIGEST_ALG_SHA256:
            info->digest_len = 32;   /* 32 sha1 digest len */
            info->digest_blen = 64;  /* 64 sha1 digest blen */
            break;
        case DIGEST_ALG_SHA384:
            info->digest_len = 48;   /* 48 sha1 digest len */
            info->digest_blen = 128; /* 128 sha1 digest blen */
            break;
        case DIGEST_ALG_SHA512:
            info->digest_len = 64;   /* 64 sha1 digest len */
            info->digest_blen = 128; /* 128 sha1 digest blen */
            break;
        default:
            return SPACC_ERR_INVALID_PARAM;
    }

    hash_ctrl.u32 = spacc_read(chn_n_hash_ctrl(chn_num));
    hash_ctrl.bits.hash_chn_mode = digest_mode;
    hash_ctrl.bits.hash_chn_agl_sel = digest_alg;
    spacc_write(chn_n_hash_ctrl(chn_num), hash_ctrl.u32);
    spacc_dbg("CTRL: 0x%X\n", hash_ctrl.u32);

    info->entry_digest_in_depth = 0;
    info->hard_key = hard_key;

    return SPACC_OK;
}

/**
 * spacc_digest_addbuf - filling the buf addr and length of
 *   data into nodes list.
 *
 */
int spacc_digest_addbuf(unsigned int chn_num,
                        unsigned long buf_phy,
                        unsigned int buf_size,
                        unsigned int ctrl)
{
    struct spacc_digest_context *info = &g_digest_context[chn_num];
    unsigned int id, size;
    void *addr = HI_NULL;

    spacc_value_return_if_max(chn_num, SPACC_LOGIC_MAX_CHN);

    id = info->digest_cur_in_nodes++;
    addr = &info->entry_digest_in[id];
    size = sizeof(struct spacc_digest_in_entry_t);
    crypto_memset(addr, sizeof(info->entry_digest_in[id]), 0, size);
    info->entry_digest_in[id].spacc_cmd = 0x00;
    info->entry_digest_in[id].hash_start_addr = get_ulong_low(buf_phy);
    info->entry_digest_in[id].hash_alg_length = buf_size;
    info->entry_digest_in[id].hash_ctrl = ctrl;
    info->entry_digest_in[id].hash_start_addr_high = get_ulong_high(buf_phy);
    info->entry_digest_in_depth++;
    info->digest_cur_in_nodes %= SPACC_MAX_DEPTH;
    spacc_dbg("add digest in buf: id %d, addr 0x%zx, len 0x%x, ctrl 0x%x\n", id, buf_phy, buf_size, ctrl);

    flush_cache (cipher_align_down(buf_phy), cipher_align_size(buf_phy, buf_size));

    return SPACC_OK;
}

/**
 * spacc_digest_addctrl - add a flags to the last valid nodes.
 *
 */
int spacc_digest_addctrl(unsigned int chn_num, unsigned int ctrl)
{
    struct spacc_digest_context *info = &g_digest_context[chn_num];
    unsigned int id;

    spacc_value_return_if_max(chn_num, SPACC_LOGIC_MAX_CHN);

    id = (info->digest_cur_in_nodes == 0) ? SPACC_MAX_DEPTH - 1 : info->digest_cur_in_nodes - 1;
    info->entry_digest_in[id].hash_ctrl |= ctrl;

    return SPACC_OK;
}

/**
 * spacc_digest_get - get hash result.
 *
 */
int spacc_digest_get(unsigned int chn_num, unsigned int *digest)
{
    unsigned int i;

    spacc_value_return_if_max(chn_num, SPACC_LOGIC_MAX_CHN);

    for (i = 0; i < HASH_RESULT_MAX_SIZE_IN_WORD; i++) {
        spacc_write(chn_n_hash_state_val_addr(chn_num), i);
        digest[i] = spacc_read(chn_n_hash_state_val(chn_num));
        spacc_dbg("digest[%d]: 0x%x\n", i, digest[i]);
    }

    return SPACC_OK;
}

/*
 * spacc_digest_start - action the hash start to processing the node list.
 */
int spacc_digest_start(unsigned int chn_num, spacc_ctrl_en spacc_ctrl, unsigned int *state)
{
    unsigned int i;
    u_chann_hash_in_node_cfg in_node_cfg;
    struct spacc_digest_context *info = &g_digest_context[chn_num];
    unsigned int ptr;

    spacc_value_return_if_max(chn_num, SPACC_LOGIC_MAX_CHN);

    spacc_dbg("chn %d, digest_mode %d, ctrl %d\n", chn_num, info->digest_mode, spacc_ctrl);

    /* Write last state */
    for (i = 0; i < HASH_RESULT_MAX_SIZE_IN_WORD; i++) {
        spacc_write(chn_n_hash_state_val_addr(chn_num), i);
        spacc_write(chn_n_hash_state_val(chn_num), state[i]);
        spacc_dbg("state: 0x%x\n", state[i]);
    }

    if (info->entry_digest_in_depth == 0)
        return SPACC_OK;

    /* configure in-node */
    in_node_cfg.u32 = spacc_read(chn_n_hash_in_node_cfg(chn_num));
    if (in_node_cfg.bits.hash_in_node_wptr != in_node_cfg.bits.hash_in_node_rptr) {
        spacc_err("Error, chn %d is busy.\n", chn_num);
        return SPACC_ERR_BUSY;
    }
    ptr = in_node_cfg.bits.hash_in_node_wptr + info->entry_digest_in_depth;
    in_node_cfg.bits.hash_in_node_wptr = ptr % SPACC_MAX_DEPTH;
    in_node_cfg.bits.hash_in_node_mpackage_int_level = 1;

    flush_cache(cipher_align_down((hi_size_t)(uintptr_t)info->entry_digest_in), \
        cipher_align_size((hi_size_t)(uintptr_t)info->entry_digest_in, SPACC_PAGE_SIZE));

    /* Start */
    spacc_write(chn_n_hash_in_node_cfg(chn_num), in_node_cfg.u32);
    spacc_dbg("chn_n_hash_in_node_cfg: 0x%x\n", in_node_cfg.u32);

    return SPACC_OK;
}

/*
 * spacc_digest_done_notify - get the int status of hash.
 */
unsigned int spacc_digest_done_notify(void)
{
    u_hash_int_raw int_raw;
    unsigned int chn_mask;

    int_raw.u32 = spacc_read(HASH_INT_RAW);
    int_raw.bits.hash_chn_oram_raw &= SPACC_CHN_MASK;
    chn_mask = int_raw.bits.hash_chn_oram_raw;

    /* Clean raw int */
    spacc_write(HASH_INT_RAW, int_raw.u32);

    return chn_mask;
}

/*
 * spacc_digest_done_try - test the int status of hash channel.
 */
unsigned int spacc_digest_done_try(unsigned int chn_num)
{
    u_hash_int_raw int_raw;
    unsigned int chn_mask;

    int_raw.u32 = spacc_read(HASH_INT_RAW);
    int_raw.bits.hash_chn_oram_raw &= 0x01 << chn_num;
    chn_mask = int_raw.bits.hash_chn_oram_raw;

    /* Clean raw int */
    spacc_write(HASH_INT_RAW, int_raw.u32);

    return chn_mask;
}

/*
 * spacc_digest_get_err_code - get the error code of hash.
 */
unsigned int spacc_digest_get_err_code(unsigned int chn_num, unsigned int *src_addr)
{
    *src_addr = spacc_read(chn_n_hash_in_buf_rptr(chn_num));

    return spacc_read(CALC_ERR);
}

/******************* proc function begin *******************/
#ifndef DISABLE_DEBUG_INFO
static hi_void spacc_symc_proc_alg_sel(hi_u32 chn,
                                       cipher_chn_status_s *cipher_status,
                                       u_chann_cipher_ctrl cipher_ctrl)
{
    switch (cipher_ctrl.bits.sym_chn_alg_sel) {
        case HI_CIPHER_ALG_AES:
            cipher_status[chn].alg = "AES ";
            break;
        case HI_CIPHER_ALG_SM1:
            cipher_status[chn].alg = "SM1 ";
            break;
        case HI_CIPHER_ALG_SM4:
            cipher_status[chn].alg = "SM4 ";
            break;
        case HI_CIPHER_ALG_DMA:
            cipher_status[chn].alg = "DMA ";
            break;
        default:
            cipher_status[chn].alg = "BUTT";
            break;
    }
}

static hi_void spacc_symc_proc_alg_mode(hi_u32 chn,
                                        cipher_chn_status_s *cipher_status,
                                        u_chann_cipher_ctrl cipher_ctrl)
{
    switch (cipher_ctrl.bits.sym_chn_alg_mode) {
        case HI_CIPHER_WORK_MODE_ECB:
            cipher_status[chn].mode = "ECB ";
            break;
        case HI_CIPHER_WORK_MODE_CBC:
            cipher_status[chn].mode = "CBC ";
            break;
        case HI_CIPHER_WORK_MODE_CFB:
            cipher_status[chn].mode = "CFB ";
            break;
        case HI_CIPHER_WORK_MODE_OFB:
            cipher_status[chn].mode = "OFB ";
            break;
        case HI_CIPHER_WORK_MODE_CTR:
            cipher_status[chn].mode = "CTR ";
            break;
        case HI_CIPHER_WORK_MODE_CCM:
            cipher_status[chn].mode = "CCM ";
            break;
        case HI_CIPHER_WORK_MODE_GCM:
            cipher_status[chn].mode = "GCM ";
            break;
        default:
            cipher_status[chn].mode = "BUTT";
            break;
    }
}

static hi_void spacc_symc_proc_key_len(hi_u32 chn,
                                       cipher_chn_status_s *cipher_status,
                                       u_chann_cipher_ctrl cipher_ctrl)
{
    if (cipher_ctrl.bits.sym_chn_alg_sel == HI_CIPHER_ALG_AES) {
        switch (cipher_ctrl.bits.sym_chn_key_length) {
            case HI_CIPHER_KEY_AES_128BIT:
                cipher_status[chn].key_len = 128; /* 128 key len */
                break;
            case HI_CIPHER_KEY_AES_192BIT:
                cipher_status[chn].key_len = 192; /* 192 key len */
                break;
            case HI_CIPHER_KEY_AES_256BIT:
                cipher_status[chn].key_len = 256; /* 256 key len */
                break;
            default:
                cipher_status[chn].key_len = 0;
                break;
        }
    } else if(cipher_ctrl.bits.sym_chn_alg_sel == HI_CIPHER_ALG_SM1) {
        cipher_status[chn].key_len = 384; /* 384 key len */
    } else if(cipher_ctrl.bits.sym_chn_alg_sel == HI_CIPHER_ALG_SM4) {
        cipher_status[chn].key_len = 128; /* 128 key len */
    } else {
        cipher_status[chn].key_len = 0;
    }
}

static hi_void spacc_symc_proc_int_info(hi_u32 chn, cipher_chn_status_s *cipher_status)
{
    u_cipher_int_raw int_raw;
    u_cipher_int_en int_en;
    u_chann_cipher_in_node_cfg in_node;
    hi_u32 *reg_addr = HI_NULL;

    /* get INT RAW status */
    int_raw.u32 = spacc_read(CIPHER_INT_RAW);
    cipher_status[chn].in_int_raw = (int_raw.bits.cipher_chn_ibuf_raw >> chn) & 0x1;
    cipher_status[chn].out_int_raw = (int_raw.bits.cipher_chn_obuf_raw >> chn) & 0x1;

    /* get INT EN status */
    int_en.u32 = spacc_read(CIPHER_INT_EN);
    cipher_status[chn].in_int_en = int_en.bits.cipher_nsec_int_en;
    cipher_status[chn].out_int_en = (int_en.bits.cipher_chn_ibuf_en >> chn) & 0x1;
    cipher_status[chn].in_int_all_en = (int_en.bits.cipher_chn_obuf_en >> chn) & 0x1;

    /* get INT_OINTCFG */
    reg_addr = chn_n_cipher_in_node_cfg(chn);
    in_node.u32 = spacc_read(reg_addr);
    cipher_status[chn].out_int_count = in_node.bits.cipher_in_node_mpackage_int_level;
}

hi_s32 spacc_symc_proc_status(cipher_chn_status_s *cipher_status)
{
    hi_u32 *reg_addr = 0;
    u_chann_cipher_ctrl cipher_ctrl;
    hi_u32 value;
    hi_u32 i, j;

    if (cipher_status == NULL) {
        hi_err_cipher("HAL_CIPHER_ProcGetStatus failed!\n");
        return HI_FAILURE;
    }

    for (i = 0; i < 8; i++) { /* 8 max channel number */
        if (i != 0)
            reg_addr = chn_n_cipher_ctrl(i);
        else
            reg_addr = CHN_0_CIPHER_CTRL;

        /* get cipher ctrl */
        cipher_ctrl.u32 = spacc_read(reg_addr);
        cipher_status[i].is_decrypt = cipher_ctrl.bits.sym_chn_decrypt;

        spacc_symc_proc_alg_sel(i, cipher_status, cipher_ctrl); /* get alg sel */
        spacc_symc_proc_alg_mode(i, cipher_status, cipher_ctrl); /* get alg mode */
        spacc_symc_proc_key_len(i, cipher_status, cipher_ctrl); /* get key len */

        /* get key sel */
        if (cipher_ctrl.bits.sym_chn_key_sel)
            cipher_status[i].key_from = "HW";
        else
            cipher_status[i].key_from = "SW";

        /* get data in */
        if (i != 0) {
            reg_addr = chn_n_cipher_in_buf_rptr(i);
            cipher_status[i].data_in_addr = spacc_read(reg_addr);
        } else {
            cipher_status[0].data_in_addr = CIPHER_CIPHER_REG_BASE_ADDR_PHY + 0x420;
        }

        /* get data out */
        if (i != 0) {
            reg_addr = chn_n_cipher_out_buf_rptr(i);
            cipher_status[i].data_out_addr = spacc_read(reg_addr);
        } else {
            cipher_status[0].data_out_addr = CIPHER_CIPHER_REG_BASE_ADDR_PHY + 0x80;
        }

        for (j = 0; j < 4; j++) { /* 4 */
            value = spacc_read(chn_n_cipher_iv_out(i) + j * 4); /* 4 */
            hex2str(cipher_status[i].iv_string + j * 8, (hi_u8)(value & 0xFF)); /* 8 */
            hex2str(cipher_status[i].iv_string + j * 8 + 2, (hi_u8)((value >> 8) & 0xFF)); /* 8, 2 */
            hex2str(cipher_status[i].iv_string + j * 8 + 4, (hi_u8)((value >> 16) & 0xFF)); /* 8, 4, 16 */
            hex2str(cipher_status[i].iv_string + j * 8 + 6, (hi_u8)((value >> 24) & 0xFF)); /* 8, 6, 24 */
        }

        spacc_symc_proc_int_info(i, cipher_status);
    }

    return HI_SUCCESS;
}
#endif
