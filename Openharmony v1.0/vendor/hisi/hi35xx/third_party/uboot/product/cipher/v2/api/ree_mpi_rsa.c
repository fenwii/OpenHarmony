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
 * Description   : mpi rsa api.
 */

#include "cipher_osal.h"

#define rsa_var_null_goto_lab(var, ret, lab) \
    do { \
        if ((var) == HI_NULL) { \
            hi_err_cipher("%s-%d: %s is null\n", __FUNCTION__, __LINE__, #var); \
            ret = HI_ERR_CIPHER_INVALID_POINT; \
            goto lab; \
        } \
    } while (0);

#define rsa_ret_fail_goto_lab(ret, lab) \
    do { \
        if ((ret) != HI_SUCCESS) { \
            hi_err_cipher("%s-%d: ret 0x%x\n", __FUNCTION__, __LINE__, ret); \
            goto lab; \
        } \
    } while (0);

#define rsa_func_fail_return(val, ret, func) \
    do { \
        if (val) { \
            hi_err_cipher("%s-%d: call %s failed, ret 0x%x\n", __FUNCTION__, __LINE__, #func, ret); \
            return ret; \
        } \
    } while (0)

#define rsa_not_equal_return(var, val, ret) \
    do { \
        if ((var) != (val)) { \
            hi_err_cipher("%s(0x%x) isn't equal 0x%x\n", #var, var, val); \
            return ret; \
        } \
    } while (0)

typedef struct {
    hi_cipher_hash_type hash_type;
    hi_u32 hlen;
    hi_u32 klen;
    hi_u32 em_bit;
    hi_u8 key_bt;
    hi_u8 *in_data;
    hi_u32 in_len;
    hi_u8 *out_data;
    hi_u32 out_len;
} rsa_padding_s;

typedef struct {
    hi_u8 *masked_db;
    hi_u8 *masked_seed;
    hi_u8 salt[CIPHER_MAX_RSA_KEY_LEN];
    hi_u32 msb_bits;
    hi_u32 slen;
    hi_u32 key_len;
} rsa_pkcs1_pss_s;

typedef struct {
    hi_u8 arr_em[CIPHER_MAX_RSA_KEY_LEN];
    hi_u8 sign_hash[HASH_RESULT_MAX_LEN];
} rsa_sign_buf;

#define RSA_SIGN                1
#define ASN1_HASH_SHA1      "\x30\x21\x30\x09\x06\x05\x2b\x0e\x03\x02\x1a\x05\x00\x04\x14"
#define ASN1_HASH_SHA224    "\x30\x2D\x30\x0d\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x04\x05\x00\x04\x1C"
#define ASN1_HASH_SHA256    "\x30\x31\x30\x0d\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x01\x05\x00\x04\x20"
#define ASN1_HASH_SHA384    "\x30\x41\x30\x0d\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x02\x05\x00\x04\x30"
#define ASN1_HASH_SHA512    "\x30\x51\x30\x0d\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x03\x05\x00\x04\x40"

static const hi_s8 g_empty_l_sha1[] =
    "\xda\x39\xa3\xee\x5e\x6b\x4b\x0d"
    "\x32\x55\xbf\xef\x95\x60\x18\x90"
    "\xaf\xd8\x07\x09";

static const hi_s8 g_empty_l_sha224[] =
    "\xd1\x4a\x02\x8c\x2a\x3a\x2b\xc9"
    "\x47\x61\x02\xbb\x28\x82\x34\xc4"
    "\x15\xa2\xb0\x1f\x82\x8e\xa6\x2a"
    "\xc5\xb3\xe4\x2f";

static const hi_s8 g_empty_l_sha256[] =
    "\xe3\xb0\xc4\x42\x98\xfc\x1c\x14"
    "\x9a\xfb\xf4\xc8\x99\x6f\xb9\x24"
    "\x27\xae\x41\xe4\x64\x9b\x93\x4c"
    "\xa4\x95\x99\x1b\x78\x52\xb8\x55";

static const hi_s8 g_empty_l_sha384[] =
    "\x38\xb0\x60\xa7\x51\xac\x96\x38"
    "\x4c\xd9\x32\x7e\xb1\xb1\xe3\x6a"
    "\x21\xfd\xb7\x11\x14\xbe\x07\x43"
    "\x4c\x0c\xc7\xbf\x63\xf6\xe1\xda"
    "\x27\x4e\xde\xbf\xe7\x6f\x65\xfb"
    "\xd5\x1a\xd2\xf1\x48\x98\xb9\x5b";

static const hi_s8 g_empty_l_sha512[] =
    "\xcf\x83\xe1\x35\x7e\xef\xb8\xbd"
    "\xf1\x54\x28\x50\xd6\x6d\x80\x07"
    "\xd6\x20\xe4\x05\x0b\x57\x15\xdc"
    "\x83\xf4\xa9\x21\xd3\x6c\xe9\xce"
    "\x47\xd0\xd1\x3c\x5d\x85\xf2\xb0"
    "\xff\x83\x18\xd2\x87\x7e\xec\x2f"
    "\x63\xb9\x31\xbd\x47\x41\x7a\x81"
    "\xa5\x38\x32\x7a\xf9\x27\xda\x3e";

static hi_s32 rsa_private(const hi_cipher_rsa_private_key *pri_key,
    hi_cipher_ca_type ca_type, const hi_u8 *input, hi_u8 *output)
{
    cipher_rsa_data_s rsa_data;

    inlet_var_is_null_return(pri_key);
    inlet_var_is_null_return(pri_key->d);
    inlet_var_is_null_return(pri_key->n);
    inlet_var_is_null_return(input);
    inlet_var_is_null_return(output);

    rsa_data.rsa_n = pri_key->n;
    rsa_data.rsa_k = pri_key->d;
    rsa_data.rsa_n_len = pri_key->n_len;
    rsa_data.rsa_k_len = pri_key->d_len;
    rsa_data.input_data = (hi_u8 *)input;
    rsa_data.output_data = output;
    rsa_data.data_len = pri_key->n_len;
    rsa_data.ca_type = HI_CIPHER_KEY_SRC_USER;

    return cipher_ioctl(g_cipher_dev_fd, CMD_CIPHER_CALCRSA, &rsa_data);
}

static hi_s32 rsa_public(const hi_cipher_rsa_pub_key *pub_key, const hi_u8 *input, hi_u8 *output)
{
    cipher_rsa_data_s rsa_data;

    inlet_var_is_null_return(pub_key);
    inlet_var_is_null_return(pub_key->n);
    inlet_var_is_null_return(pub_key->e);
    inlet_var_is_null_return(input);
    inlet_var_is_null_return(output);

    rsa_data.rsa_n = pub_key->n;
    rsa_data.rsa_k = pub_key->e;
    rsa_data.rsa_n_len = pub_key->n_len;
    rsa_data.rsa_k_len = pub_key->e_len;
    rsa_data.input_data = (hi_u8 *)input;
    rsa_data.output_data = output;
    rsa_data.data_len = pub_key->n_len;
    rsa_data.ca_type = HI_CIPHER_KEY_SRC_USER;
    return cipher_ioctl(g_cipher_dev_fd, CMD_CIPHER_CALCRSA, &rsa_data);
}

static hi_s32 rsa_get_attr(hi_u32 scheme, hi_u16 rsa_n_len, rsa_padding_s *pad)
{
    hi_s32 ret = HI_SUCCESS;

    inlet_var_over_max_return(rsa_n_len, 512); /* 512 rsa n length */

    pad->klen = rsa_n_len;

    switch (scheme) {
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_NO_PADDING:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_0:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_1:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_2:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_PKCS1_V1_5:
            pad->hlen = 0; /* 0 pad hlen */
            pad->hash_type = HI_CIPHER_HASH_TYPE_BUTT;
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA1:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA1:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA1:
            pad->hlen = 20; /* 20 pad hlen */
            pad->hash_type = HI_CIPHER_HASH_TYPE_SHA1;
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA224:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA224:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA224:
            pad->hlen = 28; /* 28 pad hlen */
            pad->hash_type = HI_CIPHER_HASH_TYPE_SHA224;
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA256:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256:
            pad->hlen = 32; /* 32 pad hlen */
            pad->hash_type = HI_CIPHER_HASH_TYPE_SHA256;
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA384:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA384:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA384:
            pad->hlen = 48; /* 48 pad hlen */
            pad->hash_type = HI_CIPHER_HASH_TYPE_SHA384;
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA512:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA512:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA512:
            pad->hlen = 64; /* 64 pad hlen */
            pad->hash_type = HI_CIPHER_HASH_TYPE_SHA512;
            break;
        default:
            hi_err_cipher("RSA scheme (0x%x) is invalid.\n", scheme);
            ret = HI_ERR_CIPHER_INVALID_PARA;
    }

    return ret;
}

static hi_s32 rsa_pkcs1_mgf1_get_md_len(hi_cipher_hash_type hash_type, hi_u32 *md_len)
{
    switch (hash_type) {
        case HI_CIPHER_HASH_TYPE_SHA1:
            *md_len = 20; /* 20 md len */
            break;
        case HI_CIPHER_HASH_TYPE_SHA224:
            *md_len = 28; /* 28 md len */
            break;
        case HI_CIPHER_HASH_TYPE_SHA256:
            *md_len = 32; /* 32 md len */
            break;
        case HI_CIPHER_HASH_TYPE_SHA384:
            *md_len = 48; /* 48 md len */
            break;
        case HI_CIPHER_HASH_TYPE_SHA512:
            *md_len = 64; /* 64 md len */
            break;
        default:
            *md_len = 0;
            hi_err_cipher("hash type is invalid.\n");
            return HI_ERR_CIPHER_INVALID_PARA;
    }
    return HI_SUCCESS;
}

static hi_s32 rsa_pkcs1_mgf1(hi_cipher_hash_type hash_type,
    hi_u8 *seed, hi_u32 seed_len, hi_u8 *mask, hi_u32 mask_len)
{
    hi_s32 ret = HI_FAILURE;
    hi_u32 i, out_len;
    hi_cipher_hash_attr hash_attr;
    hi_u8 *ptr_cnt = HI_NULL;
    hi_u8 *ptr_md = HI_NULL;
    hi_u8 *ptr_seed = HI_NULL;

    ptr_cnt = (hi_u8 *)memalign(ARCH_DMA_MINALIGN, 4); /* 4 align */
    if (ptr_cnt == HI_NULL) {
        hi_err_cipher("memalign for ptr_cnt invalid.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    ptr_md = (hi_u8 *)memalign(ARCH_DMA_MINALIGN, HASH_RESULT_MAX_LEN);
    rsa_var_null_goto_lab(ptr_md, ret, free_ptr_cnt);

    ptr_seed = (hi_u8 *)memalign(ARCH_DMA_MINALIGN, seed_len);
    rsa_var_null_goto_lab(ptr_md, ret, free_ptr_md);

    crypto_memset(ptr_cnt, 4, 0, 4); /* 4 ptr_cnt size */
    crypto_memset(ptr_md, HASH_RESULT_MAX_LEN, 0, HASH_RESULT_MAX_LEN);
    crypto_memcpy(ptr_seed, seed_len, seed, seed_len);

    /* PKCS#1 V2.1 only use sha1 function, Others allow for future expansion */
    hash_attr.sha_type = hash_type;
    for (i = 0, out_len = 0; out_len < mask_len; i++) {
        hi_handle hash_handle;
        hi_u32 j, md_len;

        ret = rsa_pkcs1_mgf1_get_md_len(hash_type, &md_len);
        rsa_ret_fail_goto_lab(ret, free_ptr_seed);

        ptr_cnt[0] = (hi_u8)((i >> 24) & 0xFF); /* 0 ptr_cnt index, 24 right shift */
        ptr_cnt[1] = (hi_u8)((i >> 16) & 0xFF); /* 1 ptr_cnt index, 16 right shift */
        ptr_cnt[2] = (hi_u8)((i >>  8) & 0xFF); /* 2 ptr_cnt index, 8  right shift */
        ptr_cnt[3] = (hi_u8)(i & 0xFF);         /* 3 ptr_cnt index */

        ret = hi_mpi_cipher_hash_init(&hash_attr, &hash_handle) ||
              hi_mpi_cipher_hash_update(hash_handle, ptr_seed, seed_len) ||
              hi_mpi_cipher_hash_update(hash_handle, ptr_cnt, 4) || /* 4 ptr_cnt size */
              hi_mpi_cipher_hash_final(hash_handle, ptr_md);
        rsa_ret_fail_goto_lab(ret, free_ptr_seed);

        for (j = 0; (j < md_len) && (out_len < mask_len); j++)
            mask[out_len++] ^= ptr_md[j];
    }

free_ptr_seed:
    free(ptr_seed);
    ptr_seed = HI_NULL;

free_ptr_md:
    free(ptr_md);
    ptr_md = HI_NULL;

free_ptr_cnt:
    free(ptr_cnt);
    ptr_cnt = HI_NULL;
    return ret;
}

static hi_s32 mbedtls_get_random_number(hi_void *param, hi_u8 *rand, size_t size)
{
    hi_u32 i;
    hi_s32 ret;
    hi_u32 randnum, left_size;

    crypto_memset(rand, size, 0, size);
    for (i = 0; i < size; i += 4) { /* 4 word bytes */
        ret = mpi_cipher_get_random_number(&randnum, -1);
        rsa_func_fail_return(ret != HI_SUCCESS, ret, mpi_cipher_get_random_number);

        left_size = (size - i) > 4 ? 4 : (size - i); /* 4 word bytes */
        switch (left_size) {
            case 4: /* left 4 */
                rand[i + 3] = (hi_u8)(randnum >> 24) & 0xFF; /* 3 rand index, 24 right shift */
                /* fall through */
            case 3: /* left 3 */
                rand[i + 2] = (hi_u8)(randnum >> 16) & 0xFF; /* 2 rand index, 16 right shift */
                /* fall through */
            case 2: /* left 2 */
                rand[i + 1] = (hi_u8)(randnum >> 8) & 0xFF; /* 1 rand index, 8  right shift */
                /* fall through */
            case 1: /* left 1 */
                rand[i + 0] = (hi_u8)(randnum >> 0) & 0xFF; /* 0 rand index */
                break;
            default:
                hi_err_cipher("left size %u is error\n", left_size);
                return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    /* non-zero random octet string */
    for (i = 0; i < size; i++) {
        if (rand[i] != 0x00)
            continue;

        ret = mpi_cipher_get_random_number(&randnum, -1);
        rsa_func_fail_return(ret != HI_SUCCESS, ret, mpi_cipher_get_random_number);
        rand[i] = (hi_u8)(randnum) & 0xFF;
        i = 0;
    }

    return HI_SUCCESS;
}

static hi_u32 rsa_get_bit_num(hi_u8 *big_num, hi_u32 num_len)
{
    static const hi_s8 bits[16] = {0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4}; /* 16 bits size */
    hi_u32 i;

    inlet_var_is_null_return(big_num);

    for (i = 0; i < num_len; i++) {
        hi_u32 num;
        num = bits[(big_num[i] & 0xF0) >> 4]; /* 4 right shift */

        if (num > 0)
            return (num_len - i - 1) * 8 + num + 4; /* 8, 4 */

        num = bits[big_num[i] & 0xF];
        if (num > 0)
            return (num_len - i - 1) * 8 + num; /* 8 */
    }
    return 0;
}

/* PKCS #1: EME-OAEP encoding */
/* ************************************************************
                    +----------+---------+--+-------+
               DB = |  lHash   |    PS   |01|   M   |
                    +----------+---------+--+-------+
                                   |
         +----------+              V
         |   ptr_seed   |--> MGF ---> xor
         +----------+              |
               |                   |
      +--+     V                   |
      |00|    xor <----- MGF <-----|
      +--+     |                   |
        |      |                   |
        V      V                   V
      +--+----------+----------------------------+
EM =  |00|maskedSeed|          maskedDB          |
      +--+----------+----------------------------+
       1     hlen              k - hlen- 1

so: PS_LEN = k - hlen - 1 -  (hlen  + mlen + 1) = k - 2hlen - mlen - 2 > 0
so: mlen < k - 2hlen - 2
************************************************************ */
static hi_s32 rsa_padding_add_pkcs1_oaep(rsa_padding_s *pad)
{
    hi_s32 ret;
    hi_u32 db_len;
    hi_u8 *ptr_db = HI_NULL;
    hi_u8 *ptr_seed = HI_NULL;
    const hi_s8 *l_hash = g_empty_l_sha1;

    /* In the v2.1 of PKCS #1, L is the empty string;    */
    /* other uses outside the scope of rsa specifications */
    if (pad->hash_type == HI_CIPHER_HASH_TYPE_SHA224) {
        l_hash = g_empty_l_sha224;
    } else if (pad->hash_type == HI_CIPHER_HASH_TYPE_SHA256) {
        l_hash = g_empty_l_sha256;
    } else if (pad->hash_type == HI_CIPHER_HASH_TYPE_SHA384) {
        l_hash = g_empty_l_sha384;
    } else if (pad->hash_type == HI_CIPHER_HASH_TYPE_SHA512) {
        l_hash = g_empty_l_sha512;
    }

    if (pad->in_len > pad->klen - 2 * pad->hlen - 2) { /* 2 */
        hi_err_cipher("input_len is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    pad->out_data[0] = 0;
    ptr_seed = pad->out_data + 1;
    ptr_db = pad->out_data + pad->hlen + 1;
    db_len = pad->klen - pad->hlen - 1;

    /* set lHash */
    crypto_memcpy(ptr_db, db_len, l_hash, pad->hlen);

    /* set PS with 0x00 */
    crypto_memset(&ptr_db[pad->hlen], db_len - pad->hlen, 0, db_len - pad->in_len - pad->hlen - 1);

    /* set 0x01 after PS */
    ptr_db[db_len - pad->in_len - 1] = 0x01;

    /* set M */
    crypto_memcpy(&ptr_db[db_len - pad->in_len], pad->in_len, pad->in_data, pad->in_len);

    /* compute maskedDB */
    ret = mbedtls_get_random_number(HI_NULL, ptr_seed, pad->hlen);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, mbedtls_get_random_number);

    ret = rsa_pkcs1_mgf1(pad->hash_type, ptr_seed, pad->hlen, ptr_db, pad->klen - pad->hlen - 1);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_pkcs1_mgf1);

    /* compute maskedSeed */
    ret = rsa_pkcs1_mgf1(pad->hash_type, ptr_db, pad->klen - pad->hlen - 1, ptr_seed, pad->hlen);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_pkcs1_mgf1);

    pad->out_len = pad->klen;

    return ret;
}

/* PKCS #1: RSAES-PKCS1-V1_5-ENCRYPT */
/*************************************************
formula: EM = 0x00 || 0x02 || PS || 0x00 || M

formula: PS_LEN > 8, mlen < klen - 11
*************************************************/
static hi_s32 rsa_padding_add_pkcs1_v15(rsa_padding_s *pad)
{
    hi_u32 index = 0;
    hi_s32 ret;

    if (pad->in_len > pad->klen - 11) { /* 11 */
        hi_err_cipher("input_len is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    pad->out_data[index++] = 0x00;
    pad->out_data[index++] = 0x02;
    ret = mbedtls_get_random_number(HI_NULL, &pad->out_data[index], pad->klen - pad->in_len - 3); /* 3 */
    rsa_func_fail_return(ret != HI_SUCCESS, ret, mbedtls_get_random_number);

    index += pad->klen - pad->in_len - 3; /* 3 */
    pad->out_data[index++] = 0x00;
    crypto_memcpy(&pad->out_data[index], pad->klen - index, pad->in_data, pad->in_len);

    pad->out_len = pad->klen;

    return HI_SUCCESS;
}

/* PKCS #1: block type 0,1,2 message padding */
/* ************************************************
formula: EB = 00 || BT || PS || 00 || D

formula: PS_LEN >= 8, mlen < klen - 11
************************************************ */
static hi_s32 rsa_padding_add_pkcs1_type(rsa_padding_s *pad)
{
    hi_u32 pad_len;
    hi_u8 *key_eb = HI_NULL;
    hi_s32 ret;

    if (pad->in_len > pad->klen - 11) { /* 11 */
        hi_err_cipher("input_len is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    key_eb = pad->out_data;

    *(key_eb++) = 0;
    *(key_eb++) = pad->key_bt; /* Private Key BT (Block Type) */

    /* pad out with 0xff data */
    pad_len = pad->klen - 3 - pad->in_len; /* 3 */
    if (pad->key_bt == 0x00) {
        crypto_memset(key_eb, pad->klen - (hi_u32)(key_eb - pad->out_data), 0x00, pad_len);
    } else if (pad->key_bt == 0x01) {
        crypto_memset(key_eb, pad->klen - (hi_u32)(key_eb - pad->out_data), 0xFF, pad_len);
    } else if (pad->key_bt == 0x02) {
        ret = mbedtls_get_random_number(HI_NULL, key_eb, pad_len);
        rsa_func_fail_return(ret != HI_SUCCESS, ret, mbedtls_get_random_number);
    } else {
        hi_err_cipher("BT(0x%x) is invalid.\n", pad->key_bt);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    key_eb += pad_len;
    *(key_eb++) = 0x00;
    crypto_memcpy(key_eb, pad->klen - (hi_u32)(key_eb - pad->out_data), pad->in_data, pad->in_len);
    pad->out_len = pad->klen;

    return HI_SUCCESS;
}

/* PKCS #1: RSAES-PKCS1-V1_5-Signature */
/* ********************************************************
formula: EM = 0x00 || 0x01 || PS || 0x00 || T

T ::= SEQUENCE {
          digestAlgorithm AlgorithmIdentifier,
          digest OCTET STRING
      }
The first field identifies the hash function and the second
contains the hash value
********************************************************* */
static hi_void rsa_padding_add_emsa_pkcs1_v15_sha1(rsa_padding_s *pad, hi_u8 *p)
{
    hi_u32 pad_len, buf_len;

    pad_len = pad->klen - 3 - 35; /* 3, 35 */
    buf_len = pad->klen - (hi_u32)(p - pad->out_data);
    crypto_memset(p, buf_len, 0xFF, pad_len);
    p += pad_len;
    *p++ = 0;
    buf_len = pad->klen - (hi_u32)(p - pad->out_data);
    crypto_memcpy(p, buf_len, ASN1_HASH_SHA1, 15); /* 15 copy size */
    p += 15; /* 15 p shift */
    buf_len = pad->klen - (hi_u32)(p - pad->out_data);
    crypto_memcpy(p, buf_len, pad->in_data, pad->in_len);
}

static hi_void rsa_padding_add_emsa_pkcs1_v15_sha224(rsa_padding_s *pad, hi_u8 *p)
{
    hi_u32 pad_len, buf_len;

    pad_len = pad->klen - 3 - 19 - pad->in_len; /* 3, 19 */
    buf_len = pad->klen - (hi_u32)(p - pad->out_data);
    crypto_memset(p, buf_len, 0xFF, pad_len);
    p += pad_len;
    *p++ = 0;
    buf_len = pad->klen - (hi_u32)(p - pad->out_data);
    crypto_memcpy(p, buf_len, ASN1_HASH_SHA224, 19); /* 19 copy size */
    p += 19; /* 19 p shift */
    buf_len = pad->klen - (hi_u32)(p - pad->out_data);
    crypto_memcpy(p, buf_len, pad->in_data, pad->in_len);
}

static hi_void rsa_padding_add_emsa_pkcs1_v15_sha256(rsa_padding_s *pad, hi_u8 *p)
{
    hi_u32 pad_len, buf_len;

    pad_len = pad->klen - 3 - 19 - pad->in_len; /* 3, 19 */
    buf_len = pad->klen - (hi_u32)(p - pad->out_data);
    crypto_memset(p, buf_len, 0xFF, pad_len);
    p += pad_len;
    *p++ = 0;
    buf_len = pad->klen - (hi_u32)(p - pad->out_data);
    crypto_memcpy(p, buf_len, ASN1_HASH_SHA256, 19); /* 19 copy size */
    p += 19; /* 19 p shift */
    buf_len = pad->klen - (hi_u32)(p - pad->out_data);
    crypto_memcpy(p, buf_len, pad->in_data, pad->in_len);
}

static hi_void rsa_padding_add_emsa_pkcs1_v15_sha384(rsa_padding_s *pad, hi_u8 *p)
{
    hi_u32 pad_len, buf_len;

    pad_len = pad->klen - 3 - 19 - pad->in_len; /* 3, 19 */
    buf_len = pad->klen - (hi_u32)(p - pad->out_data);
    crypto_memset(p, buf_len, 0xFF, pad_len);
    p += pad_len;
    *p++ = 0;
    buf_len = pad->klen - (hi_u32)(p - pad->out_data);
    crypto_memcpy(p, buf_len, ASN1_HASH_SHA384, 19); /* 19 copy size */
    p += 19; /* 19 p shift */
    buf_len = pad->klen - (hi_u32)(p - pad->out_data);
    crypto_memcpy(p, buf_len, pad->in_data, pad->in_len);
}

static hi_void rsa_padding_add_emsa_pkcs1_v15_sha512(rsa_padding_s *pad, hi_u8 *p)
{
    hi_u32 pad_len, buf_len;

    pad_len = pad->klen - 3 - 19 - pad->in_len; /* 3, 19 */
    buf_len = pad->klen - (hi_u32)(p - pad->out_data);
    crypto_memset(p, buf_len, 0xFF, pad_len);

    p += pad_len;
    *p++ = 0;
    crypto_memcpy(p, pad->klen, ASN1_HASH_SHA512, 19); /* 19 copy size */

    p += 19; /* 19 p shift */
    buf_len = pad->klen - (hi_u32)(p - pad->out_data);
    crypto_memcpy(p, buf_len, pad->in_data, pad->in_len);
}

static hi_s32 rsa_padding_add_emsa_pkcs1_v15(rsa_padding_s *pad)
{
    hi_u8 *p = pad->out_data;

    pad->out_len = pad->klen;
    *p++ = 0;
    *p++ = RSA_SIGN;

    switch (pad->hash_type) {
        case HI_CIPHER_HASH_TYPE_SHA1:
            rsa_padding_add_emsa_pkcs1_v15_sha1(pad, p);
            break;
        case HI_CIPHER_HASH_TYPE_SHA224:
            rsa_padding_add_emsa_pkcs1_v15_sha224(pad, p);
            break;
        case HI_CIPHER_HASH_TYPE_SHA256:
            rsa_padding_add_emsa_pkcs1_v15_sha256(pad, p);
            break;
        case HI_CIPHER_HASH_TYPE_SHA384:
            rsa_padding_add_emsa_pkcs1_v15_sha384(pad, p);
            break;
        case HI_CIPHER_HASH_TYPE_SHA512:
            rsa_padding_add_emsa_pkcs1_v15_sha512(pad, p);
            break;
        default:
            hi_err_cipher("RSA unsuporrt hash type: 0x%x.\n", pad->hash_type);
            return HI_ERR_CIPHER_INVALID_PARA;
    }

    return HI_SUCCESS;
}

/* *****************************************************************
                                  +-----------+
                                  |     M     |
                                  +-----------+
                                        |
                                        V
                                       Hash
                                        |
                                        V
                         +--------+----------+----------+
                   M' =  |Padding1|  mHash   |   salt   |
                         +--------+----------+----------+
                                        |
            +--------+----------+       V
     DB =   |Padding2|maskedseed|      Hash
            +--------+----------+       |
                    |                    |
                    V                    |      +--+
                    xor <----- MGF <----|      |bc|
                    |                    |      +--+
                    |                    |      |
                    V                    V      V
            +-------------------+----- -------+--+
    EM =    |    maskedDB       |  maskedseed |bc|
            +-------------------+-------------+--+
 ***************************************************************** */
static hi_s32 rsa_padding_add_pkcs1_pss_hash(rsa_padding_s *pad, rsa_pkcs1_pss_s *pss)
{
    hi_s32 ret;
    hi_u32 mlen, index;
    hi_u8 *ptr_m = HI_NULL;
    hi_handle hash_handle = 0;
    hi_cipher_hash_attr hash_attr;

    mlen = pss->slen + pad->hlen + 8; /* 8 */
    ptr_m = (hi_u8 *)memalign(ARCH_DMA_MINALIGN, mlen);
    rsa_func_fail_return(ptr_m == HI_NULL, HI_ERR_CIPHER_INVALID_POINT, memalign);

    /* M' = (0x)00 00 00 00 00 00 00 00 || mHash || salt */
    index = 0;
    crypto_memset(ptr_m, mlen, 0x00, 8); /* 8 clean size */
    index += 8; /* 8 */
    crypto_memcpy(&ptr_m[index], mlen - index, pad->in_data, pad->in_len);
    index += pad->in_len;
    crypto_memcpy(&ptr_m[index], mlen - index, pss->salt, pss->slen);
    index += pss->slen;

    crypto_memset(&hash_attr, sizeof(hash_attr), 0, sizeof(hi_cipher_hash_attr));
    hash_attr.sha_type = pad->hash_type;
    ret = hi_mpi_cipher_hash_init(&hash_attr, &hash_handle) ||
          hi_mpi_cipher_hash_update(hash_handle, ptr_m, index) ||
          hi_mpi_cipher_hash_final(hash_handle, pss->masked_seed);
    free(ptr_m); /* Must free ptr_m befort return */
    ptr_m = HI_NULL;
    rsa_func_fail_return(ret != HI_SUCCESS, ret, hi_mpi_cipher_hash_final);

    /* formula: maskedDB = DB xor dbMask, DB = PS || 0x01 || salt */
    index = 0;
    crypto_memset(&pss->masked_db[index],
        pss->key_len - index, 0x00, pss->key_len - pss->slen - pad->hlen - 2); /* 2 */
    index += pss->key_len - pss->slen - pad->hlen - 2; /* 2 */
    pss->masked_db[index++] = 0x01;
    crypto_memcpy(&pss->masked_db[index], pss->key_len - index, pss->salt, pss->slen);
    ret = rsa_pkcs1_mgf1(pad->hash_type,
        pss->masked_seed, pad->hlen, pss->masked_db, pss->key_len - pad->hlen - 1);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_pkcs1_mgf1);

    pad->out_data[pss->key_len - 1] = 0xBC;

    if (pss->msb_bits)
        pad->out_data[0] &= 0xFF >> (8 - pss->msb_bits); /* 8 */

    return ret;
}

static hi_s32 rsa_padding_add_pkcs1_pss(rsa_padding_s *pad)
{
    rsa_pkcs1_pss_s pss;
    hi_s32 ret;

    crypto_memset(&pss, sizeof(rsa_pkcs1_pss_s), 0, sizeof(rsa_pkcs1_pss_s));
    pss.slen = pad->hlen;
    pss.key_len = (pad->em_bit + 7) / 8; /* 7, 8 */
    pss.msb_bits = (pad->em_bit - 1) & 0x07;

    pad->out_len = pss.key_len;

    if (pss.key_len < (pad->hlen + pss.slen + 2)) { /* 2 */
        hi_err_cipher("message too long\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (pss.msb_bits == 0) {
        *pad->out_data++ = 0;
        pss.key_len--;
    }

    pss.masked_db = pad->out_data;
    pss.masked_seed = pad->out_data + pss.key_len - pad->hlen - 1;

    /* Generate a random octet string salt of length sLen */
    ret = mbedtls_get_random_number(HI_NULL, pss.salt, pss.slen);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, mbedtls_get_random_number);

    return rsa_padding_add_pkcs1_pss_hash(pad, &pss);
}

static hi_s32 rsa_padding_check_pkcs1_oaep(rsa_padding_s *pad)
{
    hi_s32 ret;
    hi_u32 i;
    const hi_s8 *l_hash = g_empty_l_sha1;
    hi_u8 *ptr_seed = HI_NULL;
    hi_u8 *ptr_db = HI_NULL;
    hi_u8 *masked_db = HI_NULL;

    if (pad->hash_type == HI_CIPHER_HASH_TYPE_SHA224) {
        l_hash = g_empty_l_sha224;
    } else if (pad->hash_type == HI_CIPHER_HASH_TYPE_SHA256) {
        l_hash = g_empty_l_sha256;
    } else if (pad->hash_type == HI_CIPHER_HASH_TYPE_SHA384) {
        l_hash = g_empty_l_sha384;
    } else if (pad->hash_type == HI_CIPHER_HASH_TYPE_SHA512) {
        l_hash = g_empty_l_sha512;
    }

    if (pad->klen < 2 * pad->hlen + 2) { /* 2 */
        hi_err_cipher("input_len is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (pad->in_data[0] != 0x00) {
        hi_err_cipher("EM[0] != 0.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    pad->out_len = 0;
    masked_db = pad->in_data + pad->hlen + 1;
    ptr_seed = pad->in_data + 1;
    ptr_db = pad->in_data + pad->hlen + 1;
    ret = rsa_pkcs1_mgf1(pad->hash_type, masked_db, pad->klen - pad->hlen - 1, ptr_seed, pad->hlen);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_pkcs1_mgf1);

    ret = rsa_pkcs1_mgf1(pad->hash_type, ptr_seed, pad->hlen, ptr_db, pad->klen - pad->hlen - 1);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_pkcs1_mgf1);

    ret = memcmp(ptr_db, l_hash, pad->hlen);
    rsa_func_fail_return(ret != 0, HI_ERR_CIPHER_FAILED_DECRYPT, memcmp);

    for (i = pad->hlen; i < pad->klen - pad->hlen - 1; i++) {
        if ((ptr_db[i] == 0x01)) {
            crypto_memcpy(pad->out_data, pad->klen, ptr_db + i + 1, pad->klen - pad->hlen - i - 2); /* 2 */
            pad->out_len = pad->klen - pad->hlen - i - 2; /* 2 */
            break;
        }
    }
    if (i >= pad->klen - pad->hlen - 1) {
        hi_err_cipher("PS error.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    return HI_SUCCESS;
}

static hi_s32 rsa_padding_check_pkcs1_v15(rsa_padding_s *pad)
{
    hi_u32 index = 0;

    if (pad->klen < 11) { /* 11 pad->klen max size */
        hi_err_cipher("input_len is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (pad->in_data[index] != 0x00) {
        hi_err_cipher("EM[0] != 0x00.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    index++;
    if (pad->in_data[index] != 0x02) {
        hi_err_cipher("EM[1] != 0x02.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    index++;
    for (; index < pad->klen; index++) {
        /* The length of PS is large than 8 octets */
        if ((index >= 10) && (pad->in_data[index] == 0x00)) { /* 10 */
            crypto_memcpy(pad->out_data, pad->klen, &pad->in_data[index + 1], pad->klen - 1 - index);
            pad->out_len = pad->klen - 1 - index;
            break;
        }
    }

    if (index >= pad->klen) {
        hi_err_cipher("PS error.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    return HI_SUCCESS;
}

static hi_s32 rsa_padding_check_pkcs1_type(rsa_padding_s *pad)
{
    hi_u8 *key_eb = pad->in_data;

    if (*key_eb != 0x00) {
        hi_err_cipher("EB[0] != 0x00.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    key_eb++;
    if (*key_eb != pad->key_bt) {
        hi_err_cipher("EB[1] != BT(0x%x).\n", pad->key_bt);
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    key_eb++;
    if (pad->key_bt == 0x00) {
        for (; key_eb < pad->in_data + pad->in_len - 1; key_eb++) {
            if ((*key_eb == 0x00) && (*(key_eb + 1) != 0))
                break;
        }
    } else if (pad->key_bt == 0x01) {
        for (; key_eb < pad->in_data + pad->in_len - 1; key_eb++) {
            if (*key_eb == 0xFF) {
                continue;
            } else if (*key_eb == 0x00) {
                break;
            } else {
                key_eb = pad->in_data + pad->in_len - 1;
                break;
            }
        }
    } else if (pad->key_bt == 0x02) {
        for (; key_eb < pad->in_data + pad->in_len - 1; key_eb++) {
            if (*key_eb == 0x00)
                break;
        }
    } else {
        hi_err_cipher("BT(0x%x) is invalid.\n", pad->key_bt);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (key_eb >= (pad->in_data + pad->in_len - 1)) {
        hi_err_cipher("PS Error.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    key_eb++;
    pad->out_len = pad->in_data + pad->klen - key_eb;
    crypto_memcpy(pad->out_data, pad->klen, key_eb, pad->out_len);

    return HI_SUCCESS;
}

static hi_s32 rsa_padding_check_emsa_pkcs1_v15_type(rsa_padding_s *pad, hi_u8 *p)
{
    hi_s32 ret;
    hi_u32 len;

    len = pad->klen - (hi_u32)(p - pad->in_data);

    switch (pad->hash_type) {
        case HI_CIPHER_HASH_TYPE_SHA1:
            rsa_not_equal_return(len, 35, HI_FAILURE); /* 35 len size */
            ret = memcmp(p, ASN1_HASH_SHA1, 15); /* 15 compare size */
            rsa_func_fail_return(ret != 0, HI_FAILURE, memcmp);
            crypto_memcpy(pad->out_data, pad->klen, p + 15, pad->hlen); /* 15 copy shift */
            break;
        case HI_CIPHER_HASH_TYPE_SHA224:
            rsa_not_equal_return(len, (19 + pad->hlen), HI_FAILURE); /* len size: 19 + pad->hlen */
            ret = memcmp(p, ASN1_HASH_SHA224, 19); /* 19 compare size */
            rsa_func_fail_return(ret != 0, HI_FAILURE, memcmp);
            crypto_memcpy(pad->out_data, pad->klen, p + 19, pad->hlen); /* 19 copy shift */
            break;
        case HI_CIPHER_HASH_TYPE_SHA256:
            rsa_not_equal_return(len, (19 + pad->hlen), HI_FAILURE); /* len size: 19 + pad->hlen */
            ret = memcmp(p, ASN1_HASH_SHA256, 19); /* 19 compare size */
            rsa_func_fail_return(ret != 0, HI_FAILURE, memcmp);
            crypto_memcpy(pad->out_data, pad->klen, p + 19, pad->hlen); /* 19 copy shift */
            break;
        case HI_CIPHER_HASH_TYPE_SHA384:
            rsa_not_equal_return(len, (19 + pad->hlen), HI_FAILURE); /* len size: 19 + pad->hlen */
            ret = memcmp(p, ASN1_HASH_SHA384, 19); /* 19 compare size */
            rsa_func_fail_return(ret != 0, HI_FAILURE, memcmp);
            crypto_memcpy(pad->out_data, pad->klen, p + 19, pad->hlen); /* 19 copy shift */
            break;
        case HI_CIPHER_HASH_TYPE_SHA512:
            rsa_not_equal_return(len, (19 + pad->hlen), HI_FAILURE); /* len size: 19 + pad->hlen */
            ret = memcmp(p, ASN1_HASH_SHA512, 19); /* 19 compare size */
            rsa_func_fail_return(ret != 0, HI_FAILURE, memcmp);
            crypto_memcpy(pad->out_data, pad->klen, p + 19, pad->hlen); /* 19 copy shift */
            break;
        default:
            hi_err_cipher("RSA unsuporrt hash type: 0x%x.\n", pad->hash_type);
            return HI_ERR_CIPHER_INVALID_PARA;
    }
    return ret;
}

static hi_s32 rsa_padding_check_emsa_pkcs1_v15(rsa_padding_s *pad)
{
    hi_u8 *p = pad->in_data;

    pad->out_len = pad->hlen;

    /* formula: EM = 01 || PS || 00 || T */
    if (*p++ != 0) {
        hi_err_cipher("RSA EM[0] must be 0\n");
        return HI_FAILURE;
    }

    if (*p++ != RSA_SIGN) {
        hi_err_cipher("RSA EM PS error\n");
        return HI_FAILURE;
    }

    while (*p != 0) {
        if (p >= pad->in_data + pad->klen - 1 || *p != 0xFF) {
            hi_err_cipher("RSA PS error\n");
            return HI_FAILURE;
        }
        p++;
    }
    p++; // skip 0x00

    return rsa_padding_check_emsa_pkcs1_v15_type(pad, p);
}

static hi_s32 rsa_padding_check_pkcs1_pss_hash(rsa_padding_s *pad, hi_u8 *mhash, rsa_pkcs1_pss_s *pss)
{
    hi_s32 ret;
    hi_u32 mlen;
    hi_u8 *ptr_m = HI_NULL;
    hi_handle hash_handle = 0;
    hi_cipher_hash_attr hash_attr;
    hi_u8 arr_h[HASH_RESULT_MAX_LEN] = {0};

    mlen = pss->slen + pad->hlen + 8; /* 8 */
    ptr_m = (hi_u8 *)cipher_malloc(mlen);
    rsa_func_fail_return(ptr_m == HI_NULL, HI_ERR_CIPHER_INVALID_POINT, cipher_malloc);
    crypto_memset(ptr_m, mlen, 0, mlen);

    /* M' = (0x)00 00 00 00 00 00 00 00 || mHash || salt */
    crypto_memset(ptr_m, mlen, 0x00, 8); /* 8, 0 counts */
    crypto_memcpy(&ptr_m[8], mlen - 8, mhash, pad->hlen); /* 8, 0 counts */
    crypto_memcpy(&ptr_m[8 + pad->hlen], mlen - 8 - pad->hlen, pss->salt, pss->slen); /* 8, 0 counts */

    crypto_memset(&hash_attr, sizeof(hash_attr), 0, sizeof(hi_cipher_hash_attr));
    hash_attr.sha_type = pad->hash_type;
    ret = hi_mpi_cipher_hash_init(&hash_attr, &hash_handle) ||
          hi_mpi_cipher_hash_update(hash_handle, ptr_m, mlen) ||
          hi_mpi_cipher_hash_final(hash_handle, arr_h);
    free(ptr_m); /* Must free ptr_m befort return */
    ptr_m = HI_NULL;
    rsa_func_fail_return(ret != HI_SUCCESS, ret, hi_mpi_cipher_hash_final);

    ret = crypto_memcmp(arr_h, pss->masked_seed, pad->hlen);
    rsa_func_fail_return(ret != 0, HI_FAILURE, crypto_memcmp);

    return ret;
}

static hi_s32 rsa_padding_check_pkcs1_pss(rsa_padding_s *pad, hi_u8 *mhash)
{
    hi_u32 ret;
    hi_u32 index, tmp_len;
    rsa_pkcs1_pss_s pss;

    crypto_memset(&pss, sizeof(rsa_pkcs1_pss_s), 0, sizeof(rsa_pkcs1_pss_s));
    pss.slen = pad->hlen;
    pss.key_len = (pad->em_bit + 7) / 8; /* 7, 8 */
    pss.msb_bits = (pad->em_bit - 1) & 0x07;

    if (pss.key_len < (pad->hlen + pss.slen + 2)) { /* 2 */
        hi_err_cipher("message too long\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (pad->in_data[0] & (0xFF << pss.msb_bits)) {
        hi_err_cipher("inconsistent, EM[0] invalid\n");
        return HI_FAILURE;
    }

    if (pss.msb_bits == 0) {
        pad->in_data++;
        pss.key_len--;
    }

    pss.masked_db = pad->in_data;
    pss.masked_seed = pad->in_data + pss.key_len - pad->hlen - 1;

    if (pad->in_data[pss.key_len - 1] != 0xBC) {
        hi_err_cipher("inconsistent, EM[key_len - 1] != 0xBC\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /* formula: maskedDB = DB xor dbMask, DB = PS || 0x01 || salt */
    ret = rsa_pkcs1_mgf1(pad->hash_type, pss.masked_seed,
        pad->hlen, pss.masked_db, pss.key_len - pad->hlen - 1);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_pkcs1_mgf1);

    if (pss.msb_bits)
        pss.masked_db[0] &= 0xFF >> (8 - pss.msb_bits); /* 8 */

    tmp_len = pss.key_len - pss.slen - pad->hlen - 2; /* 2 */
    if (tmp_len >= CIPHER_MAX_RSA_KEY_LEN - 1) { /* -1 is for index++, avoid masked_db overflow */
        hi_err_cipher("operate masked_db maybe overflow %u\n", tmp_len);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    for (index = 0; index < tmp_len; index++) {
        if (pss.masked_db[index] != 0x00) {
            break;
        }
    }
    pss.slen = pss.key_len - pad->hlen - index - 2;

    rsa_not_equal_return(pss.masked_db[index], 0x01, HI_FAILURE);
    index++;
    crypto_memcpy(pss.salt, sizeof(pss.salt), &pss.masked_db[index], pss.slen);

    return rsa_padding_check_pkcs1_pss_hash(pad, mhash, &pss);
}

static hi_s32 rsa_pub_enc_pad_init(rsa_padding_s *pad, const hi_cipher_rsa_pub_encrypt *rsa_enc,
    hi_cipher_rsa_crypt *rsa_crypt, hi_u8 *arr_em, hi_u32 em_len)
{
    hi_s32 ret;

    if (em_len < rsa_crypt->in_len) {
        hi_err_cipher("buf len %u < in len %u\n", em_len, rsa_crypt->in_len);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    crypto_memset(pad, sizeof(rsa_padding_s), 0, sizeof(rsa_padding_s));
    pad->in_data = (hi_u8 *)rsa_crypt->in;
    pad->in_len = rsa_crypt->in_len;
    pad->out_data = arr_em;
    ret = rsa_get_attr(rsa_enc->scheme, rsa_enc->pub_key.n_len, pad);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_get_attr);
    inlet_var_over_max_return(pad->in_len, pad->klen);

    return ret;
}

static hi_s32 rsa_pri_dec_pad_init(rsa_padding_s *pad, const hi_cipher_rsa_private_encrypt *rsa_decrypt,
    hi_cipher_rsa_crypt *rsa_crypt, hi_u8 *arr_em, hi_u32 em_len)
{
    hi_s32 ret;

    if (em_len < rsa_crypt->in_len) {
        hi_err_cipher("buf len %u < in len %u\n", em_len, rsa_crypt->in_len);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    crypto_memset(pad, sizeof(rsa_padding_s), 0, sizeof(rsa_padding_s));
    pad->in_data = arr_em;
    pad->in_len = rsa_crypt->in_len;
    pad->out_data = rsa_crypt->out;
    ret = rsa_get_attr(rsa_decrypt->scheme, rsa_decrypt->private_key.n_len, pad);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_get_attr);
    rsa_not_equal_return(pad->in_len, pad->klen, HI_ERR_CIPHER_INVALID_PARA);

    return ret;
}

static hi_s32 rsa_pri_enc_pad_init(rsa_padding_s *pad, const hi_cipher_rsa_private_encrypt *rsa_encrypt,
    hi_cipher_rsa_crypt *rsa_crypt, hi_u8 *arr_em, hi_u32 em_len)
{
    hi_s32 ret;

    if (em_len < rsa_crypt->in_len) {
        hi_err_cipher("buf len %u < in len %u\n", em_len, rsa_crypt->in_len);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    crypto_memset(pad, sizeof(rsa_padding_s), 0, sizeof(rsa_padding_s));
    pad->in_data = (hi_u8 *)rsa_crypt->in;
    pad->in_len = rsa_crypt->in_len;
    pad->out_data = arr_em;
    ret = rsa_get_attr(rsa_encrypt->scheme, rsa_encrypt->private_key.n_len, pad);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_get_attr);
    inlet_var_over_max_return(pad->in_len, pad->klen);

    return ret;
}

static hi_s32 rsa_pub_dec_pad_init(rsa_padding_s *pad, const hi_cipher_rsa_pub_encrypt *rsa_decrypt,
    hi_cipher_rsa_crypt *rsa_crypt, hi_u8 *arr_em, hi_u32 em_len)
{
    hi_s32 ret;

    if (em_len < rsa_crypt->in_len) {
        hi_err_cipher("buf len %u < in len %u\n", em_len, rsa_crypt->in_len);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    crypto_memset(pad, sizeof(rsa_padding_s), 0, sizeof(rsa_padding_s));
    pad->in_data = arr_em;
    pad->in_len = rsa_crypt->in_len;
    pad->out_data = rsa_crypt->out;
    ret = rsa_get_attr(rsa_decrypt->scheme, rsa_decrypt->pub_key.n_len, pad);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_get_attr);
    rsa_not_equal_return(pad->in_len, pad->klen, HI_FAILURE);

    return ret;
}

static hi_s32 rsa_sign_pad_init(rsa_padding_s *pad,
    const hi_cipher_rsa_sign *rsa_sign, hi_cipher_sign_data *sign_data, rsa_sign_buf *sign_buf)
{
    hi_s32 ret;
    hi_cipher_hash_attr hash_attr;
    hi_handle hash_handle;

    crypto_memset(pad, sizeof(rsa_padding_s), 0, sizeof(rsa_padding_s));
    ret = rsa_get_attr(rsa_sign->scheme, rsa_sign->private_key.n_len, pad);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_get_attr);
    pad->out_data = sign_buf->arr_em;
    pad->in_len = pad->hlen;

    /* hash is NULl, need to calc by self */
    if (sign_data->hash_data != HI_NULL) {
        pad->in_data = (hi_u8 *)sign_data->hash_data;
    } else {
        hash_attr.sha_type = pad->hash_type;
        ret = hi_mpi_cipher_hash_init(&hash_attr, &hash_handle) ||
              hi_mpi_cipher_hash_update(hash_handle, (hi_u8 *)sign_data->in, sign_data->in_len) ||
              hi_mpi_cipher_hash_final(hash_handle, sign_buf->sign_hash);
        rsa_func_fail_return(ret != HI_SUCCESS, ret, hi_mpi_cipher_hash_final);
        pad->in_data = sign_buf->sign_hash;
    }

    return ret;
}

static hi_s32 rsa_verify_pad_init(rsa_padding_s *pad, const hi_cipher_rsa_verify *rsa_verify,
    hi_cipher_verify_data *verify_data, rsa_sign_buf *sign_buf)
{
    hi_s32 ret;

    crypto_memset(pad, sizeof(rsa_padding_s), 0, sizeof(rsa_padding_s));
    ret = rsa_get_attr(rsa_verify->scheme, rsa_verify->pub_key.n_len, pad);
    pad->in_data = sign_buf->arr_em;
    pad->in_len = verify_data->sign_len;
    pad->out_data = sign_buf->sign_hash;
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_get_attr);
    rsa_not_equal_return(verify_data->sign_len, pad->klen, HI_FAILURE);

    ret = rsa_public(&rsa_verify->pub_key, verify_data->sign, pad->in_data);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_public);

    return ret;
}

static hi_u8 *rsa_verify_get_hash(hi_cipher_verify_data *verify_data,
    hi_u8 *arr_hash, hi_u32 hash_len, hi_cipher_hash_type hash_type)
{
    hi_u8 *ptr_hash = HI_NULL;
    hi_cipher_hash_attr hash_attr;
    hi_handle hash_handle;

    if (verify_data->hash_data != HI_NULL) {
        ptr_hash = (hi_u8 *)verify_data->hash_data;
    } else {
        hi_s32 ret;

        crypto_memset(&hash_attr, sizeof(hash_attr), 0, sizeof(hi_cipher_hash_attr));
        hash_attr.sha_type = hash_type;
        ret = hi_mpi_cipher_hash_init(&hash_attr, &hash_handle) ||
              hi_mpi_cipher_hash_update(hash_handle, (hi_u8 *)verify_data->in, verify_data->in_len) ||
              hi_mpi_cipher_hash_final(hash_handle, arr_hash);
        if (ret != HI_SUCCESS) {
            hi_err_cipher("Calucate hash failed.\n");
            return HI_NULL;
        }
        ptr_hash = arr_hash;
    }

    return ptr_hash;
}

hi_s32 hi_mpi_cipher_rsa_pub_encrypt(
    const hi_cipher_rsa_pub_encrypt *rsa_enc, hi_cipher_rsa_crypt *rsa_crypt)
{
    hi_s32 ret;
    rsa_padding_s pad;
    hi_u8 arr_em[CIPHER_MAX_RSA_KEY_LEN] = {0};

    check_cipher_not_open_return();
    inlet_var_is_null_return(rsa_enc);
    inlet_var_is_null_return(rsa_crypt);
    inlet_var_is_null_return(rsa_crypt->in);
    inlet_var_is_zero_return(rsa_crypt->in_len);
    inlet_var_is_null_return(rsa_crypt->out);
    inlet_var_is_null_return(rsa_crypt->out_len);

    ret = rsa_pub_enc_pad_init(&pad, rsa_enc, rsa_crypt, arr_em, sizeof(arr_em));
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_pub_enc_pad_init);

    switch (rsa_enc->scheme) {
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_NO_PADDING:
            /* if input_len < klen, padding 0 before input data */
            pad.out_len = pad.klen;
            crypto_memcpy(pad.out_data + (pad.klen - pad.in_len),
                CIPHER_MAX_RSA_KEY_LEN - (pad.klen - pad.in_len), pad.in_data, pad.in_len);
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_0:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_1:
            hi_err_cipher("RSA padding mode error, mode = 0x%x.\n", rsa_enc->scheme);
            hi_err_cipher("For a public key encryption operation, the block type shall be 02.\n");
            return HI_ERR_CIPHER_INVALID_PARA;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_2:
            pad.key_bt = (hi_u8)(rsa_enc->scheme - HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_0);
            ret = rsa_padding_add_pkcs1_type(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_add_pkcs1_type);
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA1:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA224:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA256:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA384:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA512:
            ret = rsa_padding_add_pkcs1_oaep(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_add_pkcs1_oaep);
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_PKCS1_V1_5:
            ret = rsa_padding_add_pkcs1_v15(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_add_pkcs1_v15);
            break;
        default:
            hi_err_cipher("RSA padding mode error, mode = 0x%x.\n", rsa_enc->scheme);
            return HI_ERR_CIPHER_INVALID_PARA;
    }

    *rsa_crypt->out_len = pad.out_len;
    return rsa_public(&rsa_enc->pub_key, pad.out_data, rsa_crypt->out);
}

hi_s32 hi_mpi_cipher_rsa_private_decrypt(
    const hi_cipher_rsa_private_encrypt *rsa_decrypt, hi_cipher_rsa_crypt *rsa_crypt)
{
    hi_s32 ret;
    hi_u8 arr_em[CIPHER_MAX_RSA_KEY_LEN] = {0};
    rsa_padding_s pad;

    check_cipher_not_open_return();
    inlet_var_is_null_return(rsa_decrypt);
    inlet_var_is_null_return(rsa_crypt->in);
    inlet_var_is_null_return(rsa_crypt->out);
    inlet_var_is_null_return(rsa_crypt->out_len);

    ret = rsa_pri_dec_pad_init(&pad, rsa_decrypt, rsa_crypt, arr_em, sizeof(arr_em));
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_pri_dec_pad_init);

    ret = rsa_private(&rsa_decrypt->private_key, rsa_decrypt->ca_type, rsa_crypt->in, pad.in_data);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_private);

    switch (rsa_decrypt->scheme) {
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_NO_PADDING:
            pad.out_len = pad.in_len;
            crypto_memcpy(pad.out_data, pad.klen, pad.in_data, pad.klen);
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_0:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_1:
            hi_err_cipher("RSA padding mode error, mode = 0x%x.\n", rsa_decrypt->scheme);
            hi_err_cipher("For a private key decryption operation, the block type shall be 02.\n");
            return HI_ERR_CIPHER_INVALID_PARA;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_2:
            pad.key_bt = (hi_u8)(rsa_decrypt->scheme - HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_0);
            ret = rsa_padding_check_pkcs1_type(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_check_pkcs1_type);
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA1:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA224:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA256:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA384:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA512:
            ret = rsa_padding_check_pkcs1_oaep(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_check_pkcs1_oaep);
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_PKCS1_V1_5:
            ret = rsa_padding_check_pkcs1_v15(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_check_pkcs1_oaep);
            break;
        default:
            hi_err_cipher("RSA scheme error, scheme = 0x%x.\n", rsa_decrypt->scheme);
            return HI_ERR_CIPHER_INVALID_PARA;
    }

    *rsa_crypt->out_len = pad.out_len;
    return ret;
}

hi_s32 hi_mpi_cipher_rsa_private_encrypt(
    const hi_cipher_rsa_private_encrypt *rsa_encrypt, hi_cipher_rsa_crypt *rsa_crypt)
{
    hi_s32 ret;
    rsa_padding_s pad;
    hi_u8 arr_em[CIPHER_MAX_RSA_KEY_LEN] = {0};

    check_cipher_not_open_return();
    inlet_var_is_null_return(rsa_encrypt);
    inlet_var_is_null_return(rsa_crypt->in);
    inlet_var_is_zero_return(rsa_crypt->in_len);
    inlet_var_is_null_return(rsa_crypt->out);
    inlet_var_is_null_return(rsa_crypt->out_len);

    ret = rsa_pri_enc_pad_init(&pad, rsa_encrypt, rsa_crypt, arr_em, sizeof(arr_em));
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_pri_enc_pad_init);

    switch (rsa_encrypt->scheme) {
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_NO_PADDING:
            /* if input_len < klen, padding 0 before input data */
            pad.out_len = pad.klen;
            crypto_memcpy(pad.out_data + (pad.klen - pad.in_len),
                CIPHER_MAX_RSA_KEY_LEN - (pad.klen - pad.in_len), pad.in_data, pad.in_len);
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_0:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_1:
            pad.key_bt = (hi_u8)(rsa_encrypt->scheme - HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_0);
            ret = rsa_padding_add_pkcs1_type(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_add_pkcs1_type);
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_2:
            hi_err_cipher("RSA padding mode error, mode = 0x%x.\n", rsa_encrypt->scheme);
            return HI_ERR_CIPHER_INVALID_PARA;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA1:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA224:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA256:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA384:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA512:
            ret = rsa_padding_add_pkcs1_oaep(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_add_pkcs1_oaep);
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_PKCS1_V1_5:
            pad.key_bt = 0x01;
            ret = rsa_padding_add_pkcs1_type(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_add_pkcs1_type);
            break;
        default:
            hi_err_cipher("RSA padding mode error, mode = 0x%x.\n", rsa_encrypt->scheme);
            return HI_ERR_CIPHER_INVALID_PARA;
    }

    rsa_not_equal_return(pad.out_len, pad.klen, HI_FAILURE);
    *rsa_crypt->out_len = pad.out_len;

    return rsa_private(&rsa_encrypt->private_key, rsa_encrypt->ca_type, pad.out_data, rsa_crypt->out);
}

hi_s32 hi_mpi_cipher_rsa_pub_decrypt(
    const hi_cipher_rsa_pub_encrypt *rsa_decrypt, hi_cipher_rsa_crypt *rsa_crypt)
{
    hi_s32 ret;
    hi_u8 arr_em[CIPHER_MAX_RSA_KEY_LEN] = {0};
    rsa_padding_s pad;

    check_cipher_not_open_return();
    inlet_var_is_null_return(rsa_decrypt);
    inlet_var_is_null_return(rsa_crypt->in);
    inlet_var_is_zero_return(rsa_crypt->in_len);
    inlet_var_is_null_return(rsa_crypt->out);
    inlet_var_is_null_return(rsa_crypt->out_len);

    ret = rsa_pub_dec_pad_init(&pad, rsa_decrypt, rsa_crypt, arr_em, sizeof(arr_em));
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_pub_dec_pad_init);

    ret = rsa_public(&rsa_decrypt->pub_key, rsa_crypt->in, pad.in_data);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_public);

    switch (rsa_decrypt->scheme) {
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_NO_PADDING:
            pad.out_len = pad.in_len;
            crypto_memcpy(pad.out_data, pad.klen, pad.in_data, pad.klen);
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_0:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_1:
            pad.key_bt = (hi_u8)(rsa_decrypt->scheme - HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_0);
            ret = rsa_padding_check_pkcs1_type(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_check_pkcs1_type);
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_BLOCK_TYPE_2:
            hi_err_cipher("RSA padding mode error, mode = 0x%x.\n", rsa_decrypt->scheme);
            return HI_ERR_CIPHER_INVALID_PARA;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA1:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA224:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA256:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA384:
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_OAEP_SHA512:
            ret = rsa_padding_check_pkcs1_oaep(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_check_pkcs1_oaep);
            break;
        case HI_CIPHER_RSA_ENCRYPT_SCHEME_RSAES_PKCS1_V1_5:
            pad.key_bt = 0x01;
            ret = rsa_padding_check_pkcs1_type(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_check_pkcs1_type);
            break;
        default:
            hi_err_cipher("RSA scheme error, scheme = 0x%x.\n", rsa_decrypt->scheme);
            return HI_ERR_CIPHER_INVALID_PARA;
    }

    *rsa_crypt->out_len = pad.out_len;
    return ret;
}

hi_s32 hi_mpi_cipher_rsa_sign(
    const hi_cipher_rsa_sign *rsa_sign, hi_cipher_sign_data *sign_data)
{
    hi_s32 ret;
    rsa_padding_s pad;
    rsa_sign_buf sign_buf;

    check_cipher_not_open_return();
    inlet_var_is_null_return(rsa_sign);
    inlet_var_is_null_return(sign_data->sign);
    inlet_var_is_null_return(sign_data->sign_len);
    inlet_var_is_null_return(rsa_sign->private_key.n);

    if ((sign_data->in == HI_NULL || sign_data->in_len == 0) && (sign_data->hash_data == HI_NULL)) {
        hi_err_cipher("Invalid param\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    memset(&sign_buf, 0, sizeof(rsa_sign_buf));
    ret = rsa_sign_pad_init(&pad, rsa_sign, sign_data, &sign_buf);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_sign_pad_init);

    switch (rsa_sign->scheme) {
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA1:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA224:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA384:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA512:
            ret = rsa_padding_add_emsa_pkcs1_v15(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_add_emsa_pkcs1_v15);
            break;
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA1:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA224:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA384:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA512:
            pad.em_bit = rsa_get_bit_num(rsa_sign->private_key.n, pad.klen);
            ret = rsa_padding_add_pkcs1_pss(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_add_pkcs1_pss);
            break;
        default:
            hi_err_cipher("invalid scheme; 0x%x\n", rsa_sign->scheme);
            return HI_ERR_CIPHER_INVALID_PARA;
    }

    rsa_not_equal_return(pad.out_len, pad.klen, HI_FAILURE);
    *sign_data->sign_len = pad.out_len;

    return rsa_private(&rsa_sign->private_key, rsa_sign->ca_type, pad.out_data, sign_data->sign);
}

hi_s32 hi_mpi_cipher_rsa_verify(
    const hi_cipher_rsa_verify *rsa_verify, hi_cipher_verify_data *verify_data)
{
    hi_s32 ret;
    rsa_padding_s pad;
    hi_u8 *ptr_hash = HI_NULL;
    rsa_sign_buf sign_buf;
    hi_u8 arr_hash[HASH_RESULT_MAX_LEN] = {0};

    check_cipher_not_open_return();
    inlet_var_is_null_return(rsa_verify);
    inlet_var_is_null_return(verify_data->sign);

    if ((verify_data->in == HI_NULL || verify_data->in_len == 0) && (verify_data->hash_data == HI_NULL)) {
        hi_err_cipher("Invalid param\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    memset(&sign_buf, 0, sizeof(rsa_sign_buf));
    ret = rsa_verify_pad_init(&pad, rsa_verify, verify_data, &sign_buf);
    rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_verify_pad_init);

    ptr_hash = rsa_verify_get_hash(verify_data, arr_hash, sizeof(arr_hash), pad.hash_type);
    rsa_func_fail_return(ptr_hash == HI_NULL, HI_ERR_CIPHER_INVALID_POINT, rsa_verify_get_hash);

    switch (rsa_verify->scheme) {
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA1:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA224:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA384:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA512:
            ret = rsa_padding_check_emsa_pkcs1_v15(&pad);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_check_emsa_pkcs1_v15);
            ret = memcmp(ptr_hash, pad.out_data, pad.hlen);
            rsa_func_fail_return(ret != 0, HI_ERR_CIPHER_FAILED_DECRYPT, memcmp);
            break;
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA1:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA224:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA384:
        case HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA512:
            pad.em_bit = rsa_get_bit_num(rsa_verify->pub_key.n, pad.klen);
            ret = rsa_padding_check_pkcs1_pss(&pad, ptr_hash);
            rsa_func_fail_return(ret != HI_SUCCESS, ret, rsa_padding_check_pkcs1_pss);
            break;
        default:
            hi_err_cipher("invalid scheme; 0x%x\n", rsa_verify->scheme);
            return HI_ERR_CIPHER_INVALID_PARA;
    }

    return ret;
}
