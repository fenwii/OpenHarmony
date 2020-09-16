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
 * Description   : drivers for cipher adapt
 */

#include "cipher_adapt.h"

hi_s32 cipher_mmz_alloc_remap(hi_char *name, cipher_mmz_buf_t *cipher_mmz)
{
    if (cipher_mmz->mmz_size == 0) {
        hi_err_cipher("Error: length of malloc is invalid!\n");
        return HI_FAILURE;
    }

    cipher_mmz->start_phy_addr = (hi_size_t)(uintptr_t)memalign(ARCH_DMA_MINALIGN, cipher_mmz->mmz_size);

    if (cipher_mmz->start_phy_addr == 0) {
        hi_err_cipher("Error: Get phyaddr for cipher input failed!\n");
        return HI_FAILURE;
    }
    cipher_mmz->start_vir_addr = (hi_u8 *)(uintptr_t)cipher_mmz->start_phy_addr;

    return HI_SUCCESS;
}

hi_void cipher_mmz_release_unmap(cipher_mmz_buf_t *cipher_mmz)
{
    if (cipher_mmz->start_phy_addr > 0) {
        free(cipher_mmz->start_vir_addr);
        cipher_mmz->start_phy_addr = 0;
        cipher_mmz->start_vir_addr = NULL;
    }
}

hi_s32 cipher_mmz_map(cipher_mmz_buf_t *cipher_mmz)
{
    cipher_mmz->start_vir_addr = (hi_u8 *)(uintptr_t)cipher_mmz->start_phy_addr;

    return HI_SUCCESS;
}

hi_void cipher_mmz_unmap(cipher_mmz_buf_t *cipher_mmz)
{

}

hi_s32 cipher_waitdone_callback(hi_void *param)
{
    hi_bool *done = HI_NULL;

    done = param;

    return  *done != HI_FALSE;
}

/************************* SYSTEM API ************************/
hi_void *crypto_memcpy(hi_void *dst, unsigned dstlen, const hi_void *src, unsigned len)
{
    if ((dst == NULL) || (src == NULL) || (dstlen < len)) {
        hi_err_cipher("Error: cipher call %s with invalid parameter.\n", __FUNCTION__);
        return NULL;
    }

    return memcpy(dst, src, len);
}

hi_void *crypto_memset(hi_void *dst, unsigned int dlen, unsigned val, unsigned int len)
{
    if ((dst == NULL) || (dlen < len)) {
        hi_err_cipher("Error: cipher call %s with invalid parameter.\n", __FUNCTION__);
        return NULL;
    }

    return memset(dst, val, len);
}

int crypto_memcmp(const hi_void *a, const hi_void *b, unsigned int len)
{
    if ((a == NULL) || (b == NULL)) {
        hi_err_cipher("Error: cipher call %s with invalid parameter, point is null.\n", __FUNCTION__);
        return HI_FAILURE;
    }

    if (a == b) {
        hi_err_cipher("Error: cipher call %s with invalid parameter, comparing with the same address.\n", __FUNCTION__);
        return HI_FAILURE;
    }

    return memcmp(a, b, len);
}

void hex2str(char buf[2], hi_u8 val) /* 2 buf size */
{
    hi_u8 high, low;

    high = (val >> 4) & 0x0F; /* 4 */
    low = val & 0x0F;

    if (high <= 9) /* 9 */
        buf[0] = high + '0';
    else
        buf[0] = (high - 0x0A) + 'A';

    if (low <= 9) /* 9 */
        buf[1] = low + '0';
    else
        buf[1] = (low - 0x0A) + 'A';
}

void print_data(const char *name, hi_u8 *data, hi_u32 size)
{
    hi_u32 i;

    if (name != HI_NULL)
        HI_PRINT("[%s]:\n", name);

    for (i = 0; i < size; i++) {
        if (i % 16 == 0 && i != 0) /* 16 align */
            HI_PRINT("\n");
        HI_PRINT("%02X ", data[i]);
    }
    HI_PRINT("\n");
}
