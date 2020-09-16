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

#include <efuse_opt.h>
#include <efuse.h>
#include <hi_cipher.h>

hi_u32 efuse_read(hi_u16 start_bit, hi_u16 size)
{
    hi_u8 count;
    hi_u32 print_val;
    hi_u8 line_cnt = U32_PER_LINE;
    hi_u8 data[EFUSE_MAX_INDEX_SIZE] = { 0 };
    hi_void *tmp_data = HI_NULL;
    hi_u32 ret = efuse_bits_read(start_bit, size, data, EFUSE_MAX_INDEX_SIZE);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if (size < SIZE_32_BITS) {
        *(volatile hi_u32 *)data &= ((1 << size) - 1);
        size = SIZE_32_BITS;
    } else if (size > SIZE_32_BITS && size < SIZE_64_BITS) {
        *(volatile hi_u32 *)(data + WORD_WIDTH) &= ((1 << (size - SIZE_32_BITS)) - 1);
        size = SIZE_64_BITS;
    }

    count = size >> SHIFT_5_BITS;
    if (count < U32_PER_LINE) {
        line_cnt = count;
    }

    tmp_data = (hi_void *)data;
    while (count) {
        boot_puthex(start_bit, 1);
        serial_putc(':');
        if (count < line_cnt) {
            line_cnt = count;
        }
        /* Copy from memory into linebuf and print hex values */
        for (hi_u8 i = 0; i < line_cnt; i++) {
            print_val = *(volatile unsigned int *)tmp_data;
            boot_puthex(print_val, 1);
            tmp_data = (unsigned char *)tmp_data + WORD_WIDTH;
        }
        serial_putc('\n');

        /* update references */
        start_bit += line_cnt * WORD_WIDTH * BITS_PER_BYTE;
        count -= line_cnt;
    }
    return HI_ERR_SUCCESS;
}

hi_u32 efuse_cfg_verify(uintptr_t file_addr, hi_u32 file_len)
{
    hi_u32 ret;
    hi_u8 hash[SHA_256_LENGTH] = {0};
    efuse_config_header *header = (efuse_config_header *)file_addr;

    if (header->file_size != file_len) {
        return HI_ERR_FAILURE;
    }

    ret = hi_cipher_init();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = hi_cipher_hash_sha256((uintptr_t)&(header->stru_ver), header->file_size - SHA_256_LENGTH, hash,
        SHA_256_LENGTH);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = hi_cipher_deinit();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if (memcmp(header->hash, hash, SHA_256_LENGTH) != EOK) {
        return HI_ERR_FAILURE;
    }

    if (header->number > (HI_EFUSE_IDX_MAX + HI_EFUSE_LOCK_MAX)) {
        return HI_ERR_FAILURE;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 efuse_burn(uintptr_t file_addr, hi_u32 file_len)
{
    hi_u32 ret = efuse_cfg_verify(file_addr, file_len);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg0("Efuse config file invalid");
        return HI_ERR_FAILURE;
    }

    efuse_config_header *header = (efuse_config_header *)file_addr;
    efuse_config_item *item = (efuse_config_item *)(file_addr + header->stru_size);
    for (hi_u8 i = 0; i < header->number; i++) {
        if (item == HI_NULL) {
            return HI_ERR_FAILURE;
        }
        ret = efuse_bits_write(item->start_bit, item->bit_width, item->value);
        if (ret != HI_ERR_SUCCESS) {
            boot_msg1("efuse write error, index:", i);
            serial_puts("Start bit: ");
            serial_puthex(item->start_bit, 1);
            serial_puts(" len(bits)=");
            serial_puthex(item->bit_width, 1);
            serial_puts("\n");
        }

        item = (efuse_config_item *)((uintptr_t)item + item->stru_size + item->value_len);
    }
    return HI_ERR_SUCCESS;
}

