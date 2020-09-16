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
 * Description   : mpi hash api.
 */

#include "cipher_osal.h"

#define HASH_MAX_BLOCK_SIZE     256
#define SHA1_RESULT_SIZE        20
#define SHA224_RESULT_SIZE      28
#define SHA256_RESULT_SIZE      32
#define SHA384_RESULT_SIZE      48
#define SHA512_RESULT_SIZE      64

#define SPACC_HASH_CHN          1
#define HASH_CHANNAL_MAX_NUM    8

#define SHA1_H0                 0x67452301
#define SHA1_H1                 0xefcdab89
#define SHA1_H2                 0x98badcfe
#define SHA1_H3                 0x10325476
#define SHA1_H4                 0xc3d2e1f0

#define SHA224_H0               0xc1059ed8
#define SHA224_H1               0x367cd507
#define SHA224_H2               0x3070dd17
#define SHA224_H3               0xf70e5939
#define SHA224_H4               0xffc00b31
#define SHA224_H5               0x68581511
#define SHA224_H6               0x64f98fa7
#define SHA224_H7               0xbefa4fa4

#define SHA256_H0               0x6a09e667
#define SHA256_H1               0xbb67ae85
#define SHA256_H2               0x3c6ef372
#define SHA256_H3               0xa54ff53a
#define SHA256_H4               0x510e527f
#define SHA256_H5               0x9b05688c
#define SHA256_H6               0x1f83d9ab
#define SHA256_H7               0x5be0cd19

#define SHA384_H0               0xcbbb9d5dc1059ed8ULL
#define SHA384_H1               0x629a292a367cd507ULL
#define SHA384_H2               0x9159015a3070dd17ULL
#define SHA384_H3               0x152fecd8f70e5939ULL
#define SHA384_H4               0x67332667ffc00b31ULL
#define SHA384_H5               0x8eb44a8768581511ULL
#define SHA384_H6               0xdb0c2e0d64f98fa7ULL
#define SHA384_H7               0x47b5481dbefa4fa4ULL

#define SHA512_H0               0x6a09e667f3bcc908ULL
#define SHA512_H1               0xbb67ae8584caa73bULL
#define SHA512_H2               0x3c6ef372fe94f82bULL
#define SHA512_H3               0xa54ff53a5f1d36f1ULL
#define SHA512_H4               0x510e527fade682d1ULL
#define SHA512_H5               0x9b05688c2b3e6c1fULL
#define SHA512_H6               0x1f83d9abfb41bd6bULL
#define SHA512_H7               0x5be0cd19137e2179ULL

#define SM3_H0                  0x7380166F
#define SM3_H1                  0x4914B2B9
#define SM3_H2                  0x172442D7
#define SM3_H3                  0xDA8A0600
#define SM3_H4                  0xA96F30BC
#define SM3_H5                  0x163138AA
#define SM3_H6                  0xE38DEE4D
#define SM3_H7                  0xB0FB0E4E


typedef struct {
    hi_handle handle;
    hi_cipher_hash_type sha_type;

    hi_u8 is_used;
    hi_u8 block_size;
    hi_u8 sha_len;
    hi_u8 last_block_size;

    hi_u32 total_data_len;
    hi_u32 sha_val[HASH_RESULT_MAX_LEN_IN_WORD];
    hi_u8 last_block[HASH_MAX_BLOCK_SIZE];
    hi_u8 mac[HASH_MAX_BLOCK_SIZE];
} hash_info_s;

#define HI_ID_HASH              101
static hash_info_s g_cipher_hash_data[HASH_CHANNAL_MAX_NUM];

static hi_s32 hash_check_handle(hi_handle hash_handle)
{
    if ((hi_handle_get_mod_id(hash_handle)) != HI_ID_HASH ||
        (hi_handle_get_pri_data(hash_handle) != 0)) {
        hi_err_cipher("invalid cipher handle 0x%x\n", hash_handle);
        return HI_ERR_CIPHER_INVALID_HANDLE;
    }

    if (hi_handle_get_chn_id(hash_handle) >= HASH_CHANNAL_MAX_NUM) {
        hi_err_cipher("chan %d is too large, max: %d\n",
            hi_handle_get_chn_id(hash_handle), HASH_CHANNAL_MAX_NUM);
        return HI_ERR_CIPHER_INVALID_HANDLE;
    }

    if (g_cipher_hash_data[hi_handle_get_chn_id(hash_handle)].is_used == HI_FALSE) {
        hi_err_cipher("chan %d is not open\n", hi_handle_get_chn_id(hash_handle));
        return HI_ERR_CIPHER_INVALID_HANDLE;
    }
    return HI_SUCCESS;
}

static hi_u32 hash_msg_padding(hi_u8 *msg, hi_u32 byte_len, hi_u32 total_len, hi_u32 block_size)
{
    hi_u32 tmp;
    hi_u32 padding_len;

    if (block_size == 0) {
        hi_err_cipher("Bloc size is zero !\n");
        return HI_FAILURE;
    }

    tmp = total_len % block_size;
    if (block_size == 64) { /* 64 block size */
        padding_len = (tmp < 56) ? (56 - tmp) : (120 - tmp); /* 56, 120 */
        padding_len += 8; /* 8 padding len */
    } else {
        padding_len = (tmp < 112) ? (112 - tmp) : (240 - tmp); /* 112, 240 */
        padding_len += 16; /* 16 padding len */
    }

    /* Format(binary): {data|1000...00| fix_data_len(bits)} */
    msg[byte_len++] = 0x80;
    crypto_memset(&msg[byte_len], HASH_BLOCK_SIZE * 2, 0, padding_len - 1 - 8); /* 2, 8 */
    byte_len += padding_len - 1 - 8; /* 8 */

    /* write 8 bytes fix data length */
    msg[byte_len++] = 0x00;
    msg[byte_len++] = 0x00;
    msg[byte_len++] = 0x00;
    msg[byte_len++] = (hi_u8)((total_len >> 29) & 0x07); /* 29 right shift */
    msg[byte_len++] = (hi_u8)((total_len >> 21) & 0xff); /* 21 right shift */
    msg[byte_len++] = (hi_u8)((total_len >> 13) & 0xff); /* 13 right shift */
    msg[byte_len++] = (hi_u8)((total_len >> 5) & 0xff);  /* 5  right shift */
    msg[byte_len++] = (hi_u8)((total_len << 3) & 0xff);  /* 3  right shift */

    return byte_len;
}

static hi_void hash_config_info_sha1(cipher_hash_data_s *hash_data, hash_info_s *hash_info)
{
    hash_data->sha_type = HI_CIPHER_HASH_TYPE_SHA1;
    hash_info->sha_len = SHA1_RESULT_SIZE;
    hash_info->block_size = 64; /* 64 sha1 block size */
    hash_info->sha_val[0] = cipher_cpu_to_be32(SHA1_H0); /* 0 sha1 index */
    hash_info->sha_val[1] = cipher_cpu_to_be32(SHA1_H1); /* 1 sha1 index */
    hash_info->sha_val[2] = cipher_cpu_to_be32(SHA1_H2); /* 2 sha1 index */
    hash_info->sha_val[3] = cipher_cpu_to_be32(SHA1_H3); /* 3 sha1 index */
    hash_info->sha_val[4] = cipher_cpu_to_be32(SHA1_H4); /* 4 sha1 index */
}

static hi_void hash_config_info_sha224(cipher_hash_data_s *hash_data, hash_info_s *hash_info)
{
    hash_data->sha_type = HI_CIPHER_HASH_TYPE_SHA224;
    hash_info->sha_len = SHA224_RESULT_SIZE;
    hash_info->block_size = 64; /* 64 sha224 block size */
    hash_info->sha_val[0] = cipher_cpu_to_be32(SHA224_H0); /* 0 sha224 index */
    hash_info->sha_val[1] = cipher_cpu_to_be32(SHA224_H1); /* 1 sha224 index */
    hash_info->sha_val[2] = cipher_cpu_to_be32(SHA224_H2); /* 2 sha224 index */
    hash_info->sha_val[3] = cipher_cpu_to_be32(SHA224_H3); /* 3 sha224 index */
    hash_info->sha_val[4] = cipher_cpu_to_be32(SHA224_H4); /* 4 sha224 index */
    hash_info->sha_val[5] = cipher_cpu_to_be32(SHA224_H5); /* 5 sha224 index */
    hash_info->sha_val[6] = cipher_cpu_to_be32(SHA224_H6); /* 6 sha224 index */
    hash_info->sha_val[7] = cipher_cpu_to_be32(SHA224_H7); /* 7 sha224 index */
}

static hi_void hash_config_info_sha256(cipher_hash_data_s *hash_data, hash_info_s *hash_info)
{
    hash_data->sha_type = HI_CIPHER_HASH_TYPE_SHA256;
    hash_info->sha_len = SHA256_RESULT_SIZE;
    hash_info->block_size = 64; /* 64 sha256 block size */
    hash_info->sha_val[0] = cipher_cpu_to_be32(SHA256_H0); /* 0 sha256 index */
    hash_info->sha_val[1] = cipher_cpu_to_be32(SHA256_H1); /* 1 sha256 index */
    hash_info->sha_val[2] = cipher_cpu_to_be32(SHA256_H2); /* 2 sha256 index */
    hash_info->sha_val[3] = cipher_cpu_to_be32(SHA256_H3); /* 3 sha256 index */
    hash_info->sha_val[4] = cipher_cpu_to_be32(SHA256_H4); /* 4 sha256 index */
    hash_info->sha_val[5] = cipher_cpu_to_be32(SHA256_H5); /* 5 sha256 index */
    hash_info->sha_val[6] = cipher_cpu_to_be32(SHA256_H6); /* 6 sha256 index */
    hash_info->sha_val[7] = cipher_cpu_to_be32(SHA256_H7); /* 7 sha256 index */
}

static hi_void hash_config_info_sha384(cipher_hash_data_s *hash_data, hash_info_s *hash_info)
{
    hi_u64 hash_h;

    hash_data->sha_type = HI_CIPHER_HASH_TYPE_SHA384;
    hash_info->sha_len = SHA384_RESULT_SIZE;
    hash_info->block_size = 128; /* 128 sha384 block size */
    hash_h = cipher_cpu_to_be64(SHA384_H0);
    crypto_memcpy(&hash_info->sha_val[0], sizeof(hi_u64), &hash_h, sizeof(hi_u64));  /* 0  sha384 index */
    hash_h = cipher_cpu_to_be64(SHA384_H1);
    crypto_memcpy(&hash_info->sha_val[2], sizeof(hi_u64), &hash_h, sizeof(hi_u64));  /* 2  sha384 index */
    hash_h = cipher_cpu_to_be64(SHA384_H2);
    crypto_memcpy(&hash_info->sha_val[4], sizeof(hi_u64), &hash_h, sizeof(hi_u64));  /* 4  sha384 index */
    hash_h = cipher_cpu_to_be64(SHA384_H3);
    crypto_memcpy(&hash_info->sha_val[6], sizeof(hi_u64), &hash_h, sizeof(hi_u64));  /* 6  sha384 index */
    hash_h = cipher_cpu_to_be64(SHA384_H4);
    crypto_memcpy(&hash_info->sha_val[8], sizeof(hi_u64), &hash_h, sizeof(hi_u64));  /* 8  sha384 index */
    hash_h = cipher_cpu_to_be64(SHA384_H5);
    crypto_memcpy(&hash_info->sha_val[10], sizeof(hi_u64), &hash_h, sizeof(hi_u64)); /* 10 sha384 index */
    hash_h = cipher_cpu_to_be64(SHA384_H6);
    crypto_memcpy(&hash_info->sha_val[12], sizeof(hi_u64), &hash_h, sizeof(hi_u64)); /* 12 sha384 index */
    hash_h = cipher_cpu_to_be64(SHA384_H7);
    crypto_memcpy(&hash_info->sha_val[14], sizeof(hi_u64), &hash_h, sizeof(hi_u64)); /* 14 sha384 index */
}

static hi_void hash_config_info_sha512(cipher_hash_data_s *hash_data, hash_info_s *hash_info)
{
    hi_u64 hash_h;

    hash_data->sha_type = HI_CIPHER_HASH_TYPE_SHA512;
    hash_info->sha_len = SHA512_RESULT_SIZE;
    hash_info->block_size = 128; /* 128 sha384 block size */
    hash_h = cipher_cpu_to_be64(SHA512_H0);
    crypto_memcpy(&hash_info->sha_val[0], sizeof(hi_u64), &hash_h, sizeof(hi_u64));  /* 0  sha384 index */
    hash_h = cipher_cpu_to_be64(SHA512_H1);
    crypto_memcpy(&hash_info->sha_val[2], sizeof(hi_u64), &hash_h, sizeof(hi_u64));  /* 2  sha384 index */
    hash_h = cipher_cpu_to_be64(SHA512_H2);
    crypto_memcpy(&hash_info->sha_val[4], sizeof(hi_u64), &hash_h, sizeof(hi_u64));  /* 4  sha384 index */
    hash_h = cipher_cpu_to_be64(SHA512_H3);
    crypto_memcpy(&hash_info->sha_val[6], sizeof(hi_u64), &hash_h, sizeof(hi_u64));  /* 6  sha384 index */
    hash_h = cipher_cpu_to_be64(SHA512_H4);
    crypto_memcpy(&hash_info->sha_val[8], sizeof(hi_u64), &hash_h, sizeof(hi_u64));  /* 8  sha384 index */
    hash_h = cipher_cpu_to_be64(SHA512_H5);
    crypto_memcpy(&hash_info->sha_val[10], sizeof(hi_u64), &hash_h, sizeof(hi_u64)); /* 10 sha384 index */
    hash_h = cipher_cpu_to_be64(SHA512_H6);
    crypto_memcpy(&hash_info->sha_val[12], sizeof(hi_u64), &hash_h, sizeof(hi_u64)); /* 12 sha384 index */
    hash_h = cipher_cpu_to_be64(SHA512_H7);
    crypto_memcpy(&hash_info->sha_val[14], sizeof(hi_u64), &hash_h, sizeof(hi_u64)); /* 14 sha384 index */
}

static hi_void hash_config_info_sm3(cipher_hash_data_s *hash_data, hash_info_s *hash_info)
{
    hash_data->sha_type = HI_CIPHER_HASH_TYPE_SM3;
    hash_info->sha_len = SHA256_RESULT_SIZE;
    hash_info->block_size = 64; /* 64 sm3 block size */
    hash_info->sha_val[0] = cipher_cpu_to_be32(SM3_H0); /* 0 sm3 index */
    hash_info->sha_val[1] = cipher_cpu_to_be32(SM3_H1); /* 1 sm3 index */
    hash_info->sha_val[2] = cipher_cpu_to_be32(SM3_H2); /* 2 sm3 index */
    hash_info->sha_val[3] = cipher_cpu_to_be32(SM3_H3); /* 3 sm3 index */
    hash_info->sha_val[4] = cipher_cpu_to_be32(SM3_H4); /* 4 sm3 index */
    hash_info->sha_val[5] = cipher_cpu_to_be32(SM3_H5); /* 5 sm3 index */
    hash_info->sha_val[6] = cipher_cpu_to_be32(SM3_H6); /* 6 sm3 index */
    hash_info->sha_val[7] = cipher_cpu_to_be32(SM3_H7); /* 7 sm3 index */
}

static hi_s32 hash_config_info(hi_cipher_hash_type sha_type,
    cipher_hash_data_s *hash_data, hash_info_s *hash_info)
{
    switch (sha_type) {
        case HI_CIPHER_HASH_TYPE_SHA1:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA1:
            hash_config_info_sha1(hash_data, hash_info);
            break;
        case HI_CIPHER_HASH_TYPE_SHA224:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA224:
            hash_config_info_sha224(hash_data, hash_info);
            break;
        case HI_CIPHER_HASH_TYPE_SHA256:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA256:
            hash_config_info_sha256(hash_data, hash_info);
            break;
        case HI_CIPHER_HASH_TYPE_SHA384:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA384:
            hash_config_info_sha384(hash_data, hash_info);
            break;
        case HI_CIPHER_HASH_TYPE_SHA512:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA512:
            hash_config_info_sha512(hash_data, hash_info);
            break;
        case HI_CIPHER_HASH_TYPE_SM3:
            hash_config_info_sm3(hash_data, hash_info);
            break;
        default:
            hi_err_cipher("Invaid sha type %d\n", sha_type);
            return HI_FAILURE;
    }
    return HI_SUCCESS;
}

static hi_s32 cipher_hash_init(hi_cipher_hash_attr *hash_attr, hi_handle *hash_handle)
{
    hi_s32 ret;
    cipher_hash_data_s hash_data;
    hi_u32 soft_id;
    hash_info_s *hash_info = NULL;

    for (soft_id = 0; soft_id < HASH_CHANNAL_MAX_NUM; soft_id++) {
        if (!g_cipher_hash_data[soft_id].is_used)
            break;
    }

    if (soft_id >= HASH_CHANNAL_MAX_NUM) {
        hi_err_cipher("Hash module is busy!\n");
        return HI_FAILURE;
    }

    hash_info = &g_cipher_hash_data[soft_id];
    crypto_memset(hash_info, sizeof(hash_info_s), 0, sizeof(hash_info_s));
    crypto_memset(&hash_data, sizeof(hash_data), 0, sizeof(cipher_hash_data_s));
    hash_info->sha_type = hash_attr->sha_type;
    hash_data.hard_chn = SPACC_HASH_CHN;
    ret = hash_config_info(hash_info->sha_type, &hash_data, hash_info);
    if (ret != HI_SUCCESS)
        return ret;

    ret = cipher_ioctl(g_cipher_dev_fd, CMD_CIPHER_CALCHASHINIT, &hash_data);
    if (ret == HI_SUCCESS) {
        hash_info->is_used = HI_TRUE;
        *hash_handle = hi_handle_make_handle(HI_ID_HASH, 0, soft_id);
    }

    return ret;
}

static hi_s32 cipher_hash_update_block(hash_info_s *hash_info, hi_u8 *input_data, hi_u32 input_data_len)
{
    hi_s32 ret;
    cipher_hash_data_s hash_data;

    crypto_memset(&hash_data, sizeof(hash_data), 0, sizeof(hash_data));
    hash_data.sha_type = hash_info->sha_type;
    hash_data.hard_chn = SPACC_HASH_CHN;
    crypto_memcpy(&hash_data.sha_val, sizeof(hash_data.sha_val), hash_info->sha_val, sizeof(hash_info->sha_val));

    hash_data.data_len = input_data_len;
    hash_data.data_phy = get_ulong_low((hi_size_t)(uintptr_t)input_data);
    hash_data.data_phy_high = get_ulong_high((hi_size_t)(uintptr_t)input_data);
    ret = cipher_ioctl(g_cipher_dev_fd, CMD_CIPHER_CALCHASHUPDATE, &hash_data);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("Error, ioctl for hash update failed!\n");
        hash_info->is_used = HI_FALSE;
        return ret;
    }

    crypto_memcpy(hash_info->sha_val, sizeof(hash_info->sha_val), &hash_data.sha_val, sizeof(hash_data.sha_val));

    return HI_SUCCESS;
}

static hi_s32 cipher_hash_updata_tail(hash_info_s *hash_info,
    hi_u8 *data_phy, hi_u8 *input_data, hi_u32 input_data_len)
{
    hi_s32 ret = HI_SUCCESS;

    /* process the tail of last update */
    if (hash_info->last_block_size > 0) {
        crypto_memcpy(hash_info->last_block + hash_info->last_block_size, HASH_BLOCK_SIZE,
            input_data, hash_info->block_size - hash_info->last_block_size);
        crypto_memcpy(data_phy, hash_info->block_size, hash_info->last_block, hash_info->block_size);
        ret = cipher_hash_update_block(hash_info, data_phy, hash_info->block_size);
        if (ret != HI_SUCCESS) {
            hi_err_cipher("Error, ioctl for hash update failed!\n");
            return ret;
        }
        input_data_len -= hash_info->block_size - hash_info->last_block_size;
        input_data += hash_info->block_size - hash_info->last_block_size;
    }

    if (input_data_len >= hash_info->block_size) {
        hi_u32 size;
        size = input_data_len - (input_data_len % hash_info->block_size);
        ret = cipher_hash_update_block(hash_info, input_data, size);
        if (ret != HI_SUCCESS) {
            hi_err_cipher("Error, ioctl for hash update failed!\n");
            return ret;
        }
        input_data_len -= size;
        input_data += size;
    }

    /* save tail data */
    crypto_memset(hash_info->last_block, HASH_MAX_BLOCK_SIZE, 0, HASH_MAX_BLOCK_SIZE);
    hash_info->last_block_size = input_data_len;
    crypto_memcpy(hash_info->last_block, HASH_BLOCK_SIZE, input_data, input_data_len);

    return ret;
}

static hi_s32 cipher_hash_update(hi_handle ci_hash_id, hi_u8 *input_data, hi_u32 input_data_len)
{
    hi_s32 ret = HI_SUCCESS;
    hash_info_s *hash_info = HI_NULL;
    hi_u8 *data_phy = HI_NULL;
    hi_u32 size, hash_handle;

    inlet_var_is_null_return(input_data);

    if (input_data_len == 0)
        return HI_SUCCESS;

    if (hash_check_handle(ci_hash_id) != HI_SUCCESS)
        return HI_ERR_CIPHER_INVALID_HANDLE;
    hash_handle = hi_handle_get_chn_id(ci_hash_id);
    hash_info = (hash_info_s *)&g_cipher_hash_data[hash_handle];
    if ((input_data_len + hash_info->total_data_len < input_data_len) ||
        (input_data_len + hash_info->last_block_size < input_data_len)) {
        hi_err_cipher("Error, input len is too large!\n");
        return HI_FAILURE;
    }

    data_phy = (hi_u8 *)memalign(ARCH_DMA_MINALIGN, HASH_MAX_BLOCK_SIZE);
    if (data_phy == HI_NULL) {
        hi_err_cipher("Error, memalign for data_phy failed!\n");
        hash_info->is_used = HI_FALSE;
        return HI_FAILURE;
    }
    crypto_memset(data_phy, HASH_MAX_BLOCK_SIZE, 0, HASH_MAX_BLOCK_SIZE);

    hash_info->total_data_len += input_data_len;
    size = hash_info->last_block_size + input_data_len;
    if (size < hash_info->block_size) {
        crypto_memcpy(hash_info->last_block + hash_info->last_block_size,
            HASH_BLOCK_SIZE, input_data, input_data_len);
        hash_info->last_block_size += input_data_len;
        goto free_data_phy;
    }

    ret = cipher_hash_updata_tail(hash_info, data_phy, input_data, input_data_len);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("updata tail failed, ret %d\n", ret);
        hash_info->is_used = HI_FALSE;
    }

free_data_phy:
    free(data_phy);
    data_phy = HI_NULL;
    return ret;
}

static hi_s32 cipher_hash_final(hi_handle ci_hash_id, hi_u8 *output_hash)
{
    hi_s32 ret;
    hash_info_s *hash_info = HI_NULL;
    cipher_hash_data_s hash_data;
    hi_u32 tmp;
    hi_u8 *data_phy = HI_NULL;
    hi_u32 hash_handle;

    inlet_var_is_null_return(output_hash);

    if (hash_check_handle(ci_hash_id) != HI_SUCCESS)
        return HI_ERR_CIPHER_INVALID_HANDLE;
    hash_handle = hi_handle_get_chn_id(ci_hash_id);
    hash_info = (hash_info_s *)&g_cipher_hash_data[hash_handle];

    data_phy = (hi_u8 *)memalign(ARCH_DMA_MINALIGN, HASH_MAX_BLOCK_SIZE);
    if (data_phy == NULL) {
        hi_err_cipher("memalign for data phy failed!\n");
        hash_info->is_used = HI_FALSE;
        return HI_ERR_CIPHER_INVALID_POINT;
    }
    crypto_memset(data_phy, HASH_MAX_BLOCK_SIZE, 0, HASH_MAX_BLOCK_SIZE);

    crypto_memset(&hash_data, sizeof(cipher_hash_data_s), 0, sizeof(cipher_hash_data_s));

    tmp = hash_msg_padding(hash_info->last_block,
        hash_info->last_block_size, hash_info->total_data_len, hash_info->block_size);

    crypto_memcpy(data_phy, tmp, hash_info->last_block, tmp);

    hash_data.sha_type = hash_info->sha_type;
    hash_data.data_len = tmp;
    hash_data.data_phy = get_ulong_low((hi_size_t)(uintptr_t)data_phy);
    hash_data.data_phy_high = get_ulong_high((hi_size_t)(uintptr_t)data_phy);
    crypto_memcpy(hash_data.sha_val, sizeof(hash_data.sha_val),
        hash_info->sha_val, sizeof(hash_info->sha_val));
    hash_data.hard_chn = SPACC_HASH_CHN;

    ret = cipher_ioctl(g_cipher_dev_fd, CMD_CIPHER_CALCHASHFINAL, &hash_data);
    crypto_memcpy(output_hash, HASH_RESULT_MAX_LEN, hash_data.sha_val, hash_info->sha_len);
    hash_info->is_used = HI_FALSE;

    free(data_phy);
    data_phy = HI_NULL;

    return ret;
}

static hi_s32 cipher_hmac_key_init(hi_cipher_hash_attr *hash_attr,
                                   hi_u8 hmac_key[HASH_MAX_BLOCK_SIZE])
{
    hi_handle hash_handle = 0;
    hi_s32 ret;

    if ((hash_attr->sha_type == HI_CIPHER_HASH_TYPE_HMAC_SHA384) ||
        (hash_attr->sha_type == HI_CIPHER_HASH_TYPE_HMAC_SHA512)) {
        if (hash_attr->hmac_key_len <= 128) { /* key length is less than 128bytes, copy directly */
            crypto_memcpy(hmac_key, HASH_MAX_BLOCK_SIZE, hash_attr->hmac_key, hash_attr->hmac_key_len);
            return HI_SUCCESS;
        }
    } else {
        if (hash_attr->hmac_key_len <= 64) { /* key length is less than 64bytes, copy directly */
            crypto_memcpy(hmac_key, HASH_MAX_BLOCK_SIZE, hash_attr->hmac_key, hash_attr->hmac_key_len);
            return HI_SUCCESS;
        }
    }

    /* key length more than 64bytes, calcute the hash result */
    ret = cipher_hash_init(hash_attr, &hash_handle) ||
          cipher_hash_update(hash_handle, hash_attr->hmac_key, hash_attr->hmac_key_len) ||
          cipher_hash_final(hash_handle, hmac_key);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("hash final failed\n");
        return ret;
    }
    return ret;
}

static hi_s32 cipher_hmac_init(hi_cipher_hash_attr *hash_attr, hi_handle *hash_handle)
{
    hi_s32 ret;
    hi_u32 i, soft_id;
    hi_u8 *key_pad = HI_NULL;
    hash_info_s *hash_info = NULL;

    inlet_var_is_null_return(hash_attr->hmac_key);
    inlet_var_is_zero_return(hash_attr->hmac_key_len);

    key_pad = (hi_u8 *)memalign(ARCH_DMA_MINALIGN, HASH_MAX_BLOCK_SIZE);
    if (key_pad == HI_NULL) {
        hi_err_cipher("memalign for key_pad failed!\n");
        return HI_FAILURE;
    }

    memset(key_pad, 0, HASH_MAX_BLOCK_SIZE);

    /* Init hmac key */
    ret = cipher_hmac_key_init(hash_attr, key_pad);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("Hmac key initial failed!\n");
        goto free_key_pad;
    }

    /* hash i_key_pad and message start */
    ret = cipher_hash_init(hash_attr, hash_handle);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("hash i_key_pad and message start failed!\n");
        goto free_key_pad;
    }
    soft_id = hi_handle_get_chn_id(*hash_handle);
    hash_info = (hash_info_s *)&g_cipher_hash_data[soft_id];
    crypto_memcpy(hash_info->mac, sizeof(hash_info->mac), key_pad, hash_info->block_size);

    /* generate i_key_pad */
    for (i = 0; i < hash_info->block_size; i++)
        key_pad[i] ^= 0x36;

    /* hash i_key_pad update */
    ret = cipher_hash_update(*hash_handle, key_pad, hash_info->block_size);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("cipher hash update failed!\n");
        goto free_key_pad;
    }

free_key_pad:
    free(key_pad);
    key_pad = HI_NULL;
    return ret;
}

static hi_s32 cipher_hmac_update(hi_handle ci_hash_id, hi_u8 *input_data, hi_u32 input_data_len)
{
    return cipher_hash_update(ci_hash_id, input_data, input_data_len);
}

static hi_s32 cipher_hmac_o_key_pad(hi_cipher_hash_attr *hash_attr,
    hash_info_s *hash_info, hi_u8 *output_data, hi_u8 *hash_sum, hi_u8 *key_pad)
{
    hi_u32 i;
    hi_s32 ret;
    hi_handle hash_handle;
    hi_u32 sha_size;

    /* generate o_key_pad */
    for (i = 0; i < hash_info->block_size; i++)
        key_pad[i] ^= 0x5c;

    if (hash_attr->sha_type == HI_CIPHER_HASH_TYPE_HMAC_SHA224)
        sha_size = SHA224_RESULT_SIZE;
    else if (hash_attr->sha_type == HI_CIPHER_HASH_TYPE_HMAC_SHA384)
        sha_size = SHA384_RESULT_SIZE;
    else
        sha_size = hash_info->sha_len;

    /* hash o_key_pad + hash_sum start */
    ret = cipher_hash_init(hash_attr, &hash_handle) ||
          cipher_hash_update(hash_handle, key_pad, hash_info->block_size) ||
          cipher_hash_update(hash_handle, hash_sum, sha_size) ||
          cipher_hash_final(hash_handle, output_data);

    return ret;
}

static hi_s32 cipher_hmac_final(hi_handle ci_hash_id, hi_u8 *output_data)
{
    hi_s32 ret;
    hi_handle hash_handle;
    hi_cipher_hash_attr hash_attr;
    hi_u8 *hash_sum = HI_NULL;
    hi_u8 *key_pad = HI_NULL;
    hash_info_s *hash_info = HI_NULL;

    if (hash_check_handle(ci_hash_id) != HI_SUCCESS)
        return HI_ERR_CIPHER_INVALID_HANDLE;
    hash_handle = hi_handle_get_chn_id(ci_hash_id);
    hash_info = (hash_info_s *)&g_cipher_hash_data[hash_handle];

    key_pad = (hi_u8 *)memalign(ARCH_DMA_MINALIGN, HASH_MAX_BLOCK_SIZE);
    if (key_pad == HI_NULL) {
        hi_err_cipher("memalign for key_pad failed!\n");
        hash_info->is_used = HI_FALSE;
        return HI_FAILURE;
    }

    hash_sum = (hi_u8 *)memalign(ARCH_DMA_MINALIGN, HASH_RESULT_MAX_LEN);
    if (hash_sum == HI_NULL) {
        hi_err_cipher("memalign for key_pad failed!\n");
        hash_info->is_used = HI_FALSE;
        ret = HI_FAILURE;
        goto free_key_pad;
    }

    crypto_memset(key_pad, HASH_MAX_BLOCK_SIZE, 0, HASH_MAX_BLOCK_SIZE);
    crypto_memset(hash_sum, HASH_RESULT_MAX_LEN, 0, HASH_RESULT_MAX_LEN);
    crypto_memset(&hash_attr, sizeof(hash_attr), 0, sizeof(hi_cipher_hash_attr));
    hash_attr.sha_type = hash_info->sha_type;
    crypto_memcpy(key_pad, HASH_MAX_BLOCK_SIZE, hash_info->mac, hash_info->block_size);

    /* hash i_key_pad + message finished */
    ret = cipher_hash_final(ci_hash_id, hash_sum);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("Hash Final i_key_pad + message failure, ret=%d\n", ret);
        hash_info->is_used = HI_FALSE;
        goto free_hash_sum;
    }

    /* hash o_key_pad + message finished */
    ret = cipher_hmac_o_key_pad(&hash_attr, hash_info, output_data, hash_sum, key_pad);
    if (ret != HI_SUCCESS) {
        hi_err_cipher("Hash Final o_key_pad + message failure, ret=%d\n", ret);
        hash_info->is_used = HI_FALSE;
        goto free_hash_sum;
    }

free_hash_sum:
    free(hash_sum);
    hash_sum = HI_NULL;

free_key_pad:
    free(key_pad);
    key_pad = HI_NULL;
    return ret;
}

hi_s32 hi_mpi_cipher_hash_init(hi_cipher_hash_attr *hash_attr, hi_handle *hash_handle)
{
    hi_s32 ret;

    check_cipher_not_open_return();
    inlet_var_is_null_return(hash_attr);
    inlet_var_is_null_return(hash_handle);

    switch (hash_attr->sha_type) {
        case HI_CIPHER_HASH_TYPE_SHA1:
        case HI_CIPHER_HASH_TYPE_SHA224:
        case HI_CIPHER_HASH_TYPE_SHA256:
        case HI_CIPHER_HASH_TYPE_SHA384:
        case HI_CIPHER_HASH_TYPE_SHA512:
        case HI_CIPHER_HASH_TYPE_SM3:
            ret = cipher_hash_init(hash_attr, hash_handle);
            break;
        case HI_CIPHER_HASH_TYPE_HMAC_SHA1:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA224:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA256:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA384:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA512:
            ret = cipher_hmac_init(hash_attr, hash_handle);
            break;
        default:
            hi_err_cipher("Invalid sha type %d!\n", hash_attr->sha_type);
            return HI_FAILURE;
    }

    if (ret != HI_SUCCESS) {
        hi_err_cipher("hash init failed, hash type: %d\n", hash_attr->sha_type);
        return ret;
    }

    return ret;
}

hi_s32 hi_mpi_cipher_hash_update(hi_handle hash_handle, hi_u8 *input_data, hi_u32 input_data_len)
{
    hi_s32 ret;
    hi_u32 soft_id;
    hash_info_s *hash_info = HI_NULL;

    check_cipher_not_open_return();
    inlet_var_is_null_return(input_data);

    if (hash_check_handle(hash_handle) != HI_SUCCESS)
        return HI_ERR_CIPHER_INVALID_HANDLE;

    soft_id = hi_handle_get_chn_id(hash_handle);
    hash_info = (hash_info_s *)&g_cipher_hash_data[soft_id];

    switch (hash_info->sha_type) {
        case HI_CIPHER_HASH_TYPE_SHA1:
        case HI_CIPHER_HASH_TYPE_SHA224:
        case HI_CIPHER_HASH_TYPE_SHA256:
        case HI_CIPHER_HASH_TYPE_SHA384:
        case HI_CIPHER_HASH_TYPE_SHA512:
        case HI_CIPHER_HASH_TYPE_SM3:
            ret = cipher_hash_update(hash_handle, input_data, input_data_len);
            break;
        case HI_CIPHER_HASH_TYPE_HMAC_SHA1:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA224:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA256:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA384:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA512:
            ret = cipher_hmac_update(hash_handle, input_data, input_data_len);
            break;
        default:
            hi_err_cipher("Invalid hash type %d!\n", hash_info->sha_type);
            return HI_FAILURE;
    }

    if (ret != HI_SUCCESS) {
        hi_err_cipher("hash update failed, hash type: %d\n", hash_info->sha_type);
        return ret;
    }

    return ret;
}

hi_s32 hi_mpi_cipher_hash_final(hi_handle hash_handle, hi_u8 *output_hash)
{
    hi_s32 ret;
    hi_u32 soft_id;
    hash_info_s *hash_info = HI_NULL;

    check_cipher_not_open_return();
    inlet_var_is_null_return(output_hash);

    if (hash_check_handle(hash_handle) != HI_SUCCESS)
        return HI_ERR_CIPHER_INVALID_HANDLE;

    soft_id = hi_handle_get_chn_id(hash_handle);
    hash_info = (hash_info_s *)&g_cipher_hash_data[soft_id];

    switch (hash_info->sha_type) {
        case HI_CIPHER_HASH_TYPE_SHA1:
        case HI_CIPHER_HASH_TYPE_SHA224:
        case HI_CIPHER_HASH_TYPE_SHA256:
        case HI_CIPHER_HASH_TYPE_SHA384:
        case HI_CIPHER_HASH_TYPE_SHA512:
        case HI_CIPHER_HASH_TYPE_SM3:
            ret = cipher_hash_final(hash_handle, output_hash);
            break;
        case HI_CIPHER_HASH_TYPE_HMAC_SHA1:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA224:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA256:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA384:
        case HI_CIPHER_HASH_TYPE_HMAC_SHA512:
            ret = cipher_hmac_final(hash_handle, output_hash);
            break;
        default:
            hi_err_cipher("Invalid hash type %d!\n", hash_info->sha_type);
            return HI_FAILURE;
    }

    if (ret != HI_SUCCESS) {
        hi_err_cipher("hash final failed, hash type: %d\n", hash_info->sha_type);
        return ret;
    }

    return ret;
}
