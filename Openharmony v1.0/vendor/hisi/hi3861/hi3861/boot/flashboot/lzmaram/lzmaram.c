/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <lzmaram.h>
#include <hi_boot_err.h>
#include <hi_boot_rom.h>

#define LZMA_DIC_MIN   (1 << 12)
#define LZMA_BASE_SIZE 1846
#define LZMA_LIT_SIZE  768
#define IN_BUF_SIZE    0x1000
#define OUT_BUF_SIZE   0x1000

static hi_pbyte lzma_alloc(hi_pbyte unused, size_t size)
{
    hi_unref_param(unused);
    hi_pbyte addr = (hi_pbyte)boot_malloc(size);
    if (!addr) {
        boot_msg1("\n LZMA_Alloc fail= ", size);
    }
    return addr;
}

static void lzma_free(hi_pbyte unused, hi_pbyte address)
{
    hi_unref_param(unused);
    if (address == HI_NULL) {
        return;
    }

    boot_free(address);
}

/**
* @ingroup  LZMA
* @brief  : get file size and dictionary size before LZMA compressed
*
* @par :description:
*          get file size and dictionary size before LZMA compressed
*
* @attention: nothing
* @param  lzma_head                     [IN] type #hi_u8*-LZMA head
* @param  pulDecompressedDataLen        [OUT] type #unsigned int*, size before compressed
* @param  dic_size                      [OUT] type #unsigned int* , dictionary size
*
* @retval #HI_ERR_SUCCESS  success
* @retval # other value: fail, see hi_errno.h for details
* @par  dependency:
*
* @see : nothing
 */
unsigned int hi_lzma_get_uncompress_len(const hi_u8 lzma_head[13], hi_u32 head_size, /* head 13B */
                                        unsigned int *pul_decompressed_data_len, unsigned int *dic_size)
{
    unsigned int uncompressed_len;
    unsigned int uncompressed_len_high;

    if ((lzma_head == HI_NULL)
        || (pul_decompressed_data_len == HI_NULL)
        || head_size > 13) { /* head 13B */
        boot_msg1("[lzma get uncompress len]head size", head_size);
        return HI_ERR_LZMA_PARAM;
    }

    uncompressed_len = (unsigned int)lzma_head[5] |               /* index 5,  low 8bits */
                       ((unsigned int)lzma_head[6] << 8) |        /* index 6, bits 8-15 */
                       ((unsigned int)lzma_head[7] << 16) |       /* index 7, bits 16-23 */
                       ((unsigned int)lzma_head[8] << 24);        /* index 8, bits 24-32 */
    uncompressed_len_high = (unsigned int)lzma_head[9] |          /* index 9,  low 8bits */
                            ((unsigned int)lzma_head[10] << 8) |  /* index 10,  bits 8-15 */
                            ((unsigned int)lzma_head[11] << 16) | /* index 11,  bits 16-23 */
                            ((unsigned int)lzma_head[12] << 24);  /* index 12,  bits 24-32 */

    if ((uncompressed_len_high != 0)) {
        /* uncompressed file is too long, output buffer is not enough */
        boot_msg1("[lzma get uncompress len]high", uncompressed_len_high);
        return HI_ERR_LZMA_LEN;
    }

    *dic_size = (unsigned int)lzma_head[1] |         /* index 1,  low 8bits */
                ((unsigned int)lzma_head[2] << 8) |  /* index 2, bits 8-15 */
                ((unsigned int)lzma_head[3] << 16) | /* index 3, bits 16-23 */
                ((unsigned int)lzma_head[4] << 24);  /* index 4, bits 24-32 */

    if (*dic_size < LZMA_DIC_MIN) {
        *dic_size = LZMA_DIC_MIN;
    }

    *pul_decompressed_data_len = uncompressed_len;
    return HI_ERR_SUCCESS;
}

/**
* @ingroup  LZMA
* @brief : LZMA decompress for sections
*
* @par description:
*          LZMA decompress for sections
*
* @attention : nothing
* @param  lzma_head                     [IN] type #hi_u8*-LZMA head
* @param  compress_len                  [IN] type  #unsigned int, size after compressed
* @param  in_func                       [IN] type #LZMA_STREAM_FCT,  get content of compressed
* @param  out_func                      [IN] type #LZMA_STREAM_FCT, save the content after compressed
*
* @retval #HI_ERR_SUCCESS  success
* @retval # other value: fail, see hi_errno.h for details
* @par  dependency:
*
* @see : nothing
 */
unsigned int hi_lzma_decompress(const hi_u8 lzma_head[13], hi_u32 head_size,  /* head 13B */
    unsigned int compress_len, lzma_stream_fct in_func, lzma_stream_fct out_func)
{
    unsigned int ret;
    unsigned int lzma_stat = 0;
    unsigned int uncompress_len = 0;
    unsigned int dic_size = 0;
    i_sz_alloc alloc = { 0 };
    lzma_stream in_stream;
    lzma_stream out_stream;
    in_stream.func = in_func;
    in_stream.offset = 13; /* offset 13 */
    out_stream.func = out_func;
    out_stream.offset = 0;

    alloc.alloc = lzma_alloc;
    alloc.free = lzma_free;

    ret = hi_lzma_get_uncompress_len(lzma_head, head_size, &uncompress_len, &dic_size);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("[hi lzma decompress]get uncompress len:", ret);
    }
    ret = LzmaDecode2(lzma_head, 5, &lzma_stat, &alloc, &in_stream, /* size 5 */
                      &out_stream, compress_len - 13, uncompress_len);            /* length subtract 13 */
    if (ret != 0) {
        boot_msg1("[hi lzma decompress]decode ret:", ret);
    }

    return (ret ? (HI_ERR_LZMA_DECODE + ret) : HI_ERR_SUCCESS);
}

/**
* @ingroup  LZMA
* @brief  LZMA RAM usage detect
*
* @par description:
*           LZMA RAM usage detect, detect for whether the current RAM is enough for LZMA uncompress
*
* @attention : nothing
* @param  lzma_head                     [IN] type #hi_u8*, LZMA head
*
* @retval #HI_ERR_SUCCESS  success
* @retval # other value: fail, see hi_errno.h for details
* @par  dependency:
*
* @see : nothing
 */
unsigned int hi_lzma_mem_detect(const hi_u8 lzma_head[13], hi_u32 head_size) /* head 13B */
{
    unsigned int ret;
    unsigned int compress_len = 0;
    unsigned int dic_size = 0;
    unsigned char d;
    unsigned int lc, lp;
    unsigned int malloc_size[5] = { /* size 5*4 */
        0,
    };
    unsigned char *addr[5] = { /* addr 5B */
        HI_NULL,
    };
    unsigned int array_size = sizeof(addr) / sizeof(addr[0]);
    unsigned int i;

    ret = hi_lzma_get_uncompress_len(lzma_head, head_size, &compress_len, &dic_size);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    d = lzma_head[0];
    if (d >= (9 * 5 * 5)) { /* less than 9*5*5 */
        boot_msg1("[hi_lzma_mem_detect]d", d);
        return HI_ERR_FAILURE;
    }

    lc = d % 9; /* remain of devide 9 */
    d /= 9;     /* counts of 9 */
    lp = d % 5; /* remain of devide 5 */

    malloc_size[0] = (((unsigned int)LZMA_BASE_SIZE + (LZMA_LIT_SIZE << (lc + lp))) * 2); /* shifts (lc+lp)*2 */
    malloc_size[1] = IN_BUF_SIZE;                                                         /* index 1 */
    malloc_size[2] = OUT_BUF_SIZE;                                                        /* index 2 */
    malloc_size[3] = dic_size;                                                            /* index 3 */
    malloc_size[4] = 0x400;                                /* for security ,index 4:0x400 */
    boot_msg2("[hi_lzma_mem_detect]malloc_size[0-3]", malloc_size[0], dic_size);

    for (i = 0; i < array_size; i++) {
        addr[i] = boot_malloc(malloc_size[i]);

        if (addr[i] == HI_NULL) {
            ret = HI_ERR_FAILURE;
            break;
        }
    }

    for (i = 0; i < array_size; i++) {
        if (addr[array_size - i - 1] != HI_NULL) {
            boot_free(addr[array_size - i - 1]);
        }
    }

    return ret;
}
