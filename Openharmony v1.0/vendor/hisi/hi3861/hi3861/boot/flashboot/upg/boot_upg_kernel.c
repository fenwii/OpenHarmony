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

#include "boot_upg_kernel.h"
#include "boot_upg_tool.h"

#if defined(CONFIG_FLASH_ENCRYPT_SUPPORT)
#include <crypto.h>
#endif

hi_u32 boot_upg_lzma_detect(hi_u32 addr_write, hi_u32 *uncompress_size, const hi_upg_section_head *section_head)
{
    hi_u8 lzma_head[13] = { 0 }; /* head 13B */
    hi_u32 dic_size = 0;

    /* get LZMA head. get uncompressed size */
    hi_u32 ret = hi_flash_read(addr_write + section_head->section0_offset, 13, lzma_head); /* 13 Bytes:head length */
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    ret = hi_lzma_get_uncompress_len(lzma_head, sizeof(lzma_head), uncompress_size, &dic_size);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("get uncompress len:", ret);
        return ret;
    }

    /* RAM usage detect for  LAMA uncompressing.
        * Avoid can't uncompress after erasing file, it'll cause unable to start */
    ret = hi_lzma_mem_detect(lzma_head, sizeof(lzma_head));
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("mem detect:", ret);
    } else {
        if ((*uncompress_size) == 0) {
            ret = HI_ERR_UPG_FILE_LEN_ZERO;
            boot_msg0("uncompress size.");
        }
    }
    return ret;
}

hi_u32 boot_upg_lzma_verify(hi_u32 addr_write, hi_u32 *uncompress_size, const hi_upg_section_head *section_head,
                            const hi_upg_file_head *file_head)
{
    hi_u32 ret = boot_upg_lzma_detect(addr_write, uncompress_size, section_head);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg2("detect1 writeaddr-uncompress_size:", addr_write, *uncompress_size);
        return ret;
    }

    ret = hi_cipher_init();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    ret = boot_upg_check_before_decompress(addr_write, section_head, file_head);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("check before decompress:", ret);
    }
    (hi_void)hi_cipher_deinit();
    return ret;
}

hi_u32 boot_upg_kernel_process(hi_u32 addr_start, hi_u32 addr_write)
{
    hi_u32 uncompress_size;
    hi_upg_section_head section_head = { 0 };
    hi_u32 ret = hi_flash_read(addr_write + sizeof(hi_upg_head), sizeof(hi_upg_section_head), (hi_u8 *)(&section_head));
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    if (section_head.section0_compress == HI_FALSE) {
        boot_msg0("Not support uncompressed file.");
        return HI_ERR_UPG_PARAMETER;
    }
    hi_upg_file_head *file_head = boot_malloc(sizeof(hi_upg_file_head));
    if (file_head == HI_NULL) {
        return HI_ERR_UPG_MALLOC_FAIL;
    }

#if defined(CONFIG_FLASH_ENCRYPT_SUPPORT)
    ret = boot_decrypt_upg_file(addr_write, &section_head);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("decrypt upg file fail:", ret);
        goto end;
    }
#endif

    ret = boot_upg_lzma_verify(addr_write, &uncompress_size, &section_head, file_head);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("lzma verify fail:", ret);
        goto end;
    }

    ret = boot_upg_lzma_detect(addr_write, &uncompress_size, &section_head);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("detect2:", ret);
        goto end;
    }

    /* make 4K allignment for kernal and NV before compression. Erasing target space */
    hi_u32 erase_size = uncompress_size;
    erase_size = align_length(erase_size, ALIGNTYPE_4K);
    ret = hi_flash_erase(addr_start, erase_size);
    boot_msg4("info start-erasesize-write-uncompresssize:", addr_start, erase_size, addr_write, uncompress_size);
    /* uncompress kernel and nv file to target space */
    ret = boot_upg_copy_flash_2_flash(addr_write + section_head.section0_offset, section_head.section0_len,
                                      addr_start, uncompress_size, section_head.section0_compress);
    if (ret == HI_ERR_SUCCESS) {
        boot_msg0("[bootupg kernel process]decompress success.");
    }
end:
    boot_upg_mem_free(file_head);
#if defined(CONFIG_FLASH_ENCRYPT_SUPPORT)
    boot_decrypt_free_memory();
#endif
    return ret;
}