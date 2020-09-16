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

#include <transfer.h>
#include <cmd_loop.h>
#include <crc.h>

#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
#include <load_crypto.h>
#endif

#define FLASHBOOT_MAX_SIZE       0x8000
#define DEFAULT_KERNEL_BURN_ADDR 0xD000

upload_context *g_upload_ctx = HI_NULL;

hi_u32 loader_serial_ymodem(hi_u32 offset, hi_u32 erased_size, hi_u32 min, hi_u32 max)
{
    hi_u32 size = 0;
    uintptr_t store_addr = offset;
    hi_u32 file_length, remain, read_len, ret, cs;

    ret = loader_ymodem_open();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    file_length = ymodem_get_length();
    if (file_length <= min || file_length > max) {
        boot_msg1("file length err : ", file_length);
        return HI_ERR_FAILURE;
    }

    if (erased_size && (erased_size < file_length)) {
        boot_msg0("file_size > erase_size");
        return HI_ERR_FAILURE;
    }

    remain = file_length;

    while (remain > 0) {
        hi_u32 read_size = (hi_u32)hi_min(remain, SZ_1KB);
        read_len = ymodem_read(g_ymodem_buf, read_size, ((uintptr_t)g_ymodem_buf) ^ read_size);
        if (read_len == 0 || remain < read_len) {
            return HI_ERR_FAILURE;
        }

        if (erased_size == 0) {
            cs = (uintptr_t)(hi_void *)store_addr ^ (hi_u32)remain ^ (uintptr_t)g_ymodem_buf ^ (hi_u32)read_len;
            if (memcpy_s((hi_void *)store_addr, (hi_u32)remain, g_ymodem_buf, read_len, cs) != EOK) {
                return HI_ERR_FAILURE;
            }
        } else {
            ret = g_flash_cmd_funcs.write(store_addr, read_len, (hi_u8 *)g_ymodem_buf, HI_FALSE);
            if (ret != HI_ERR_SUCCESS) {
                boot_msg1("flash write fail", ret);
                return HI_ERR_FAILURE;
            }
        }
        remain -= read_len;
        size += read_len;
        store_addr += (hi_u32)read_len;
    }
    cs = ((uintptr_t)g_ymodem_buf) ^ SZ_1KB;
    (hi_void) ymodem_read(g_ymodem_buf, SZ_1KB, cs);

    ymodem_close();
    if ((hi_u32)size == file_length) {
        boot_msg1("total size:", (hi_u32)size);
        return HI_ERR_SUCCESS;
    }

    return HI_ERR_FAILURE;
}

hi_u32 loady_file(uintptr_t ram_addr)
{
    hi_u32 ret;

    if (load_malloc_init() != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE; /* failure */
    }

    loader_ack(ACK_SUCCESS);
    ret = loader_serial_ymodem(ram_addr, 0, sizeof(efuse_config_header), EFUSE_CFG_MAX_LEN);

    load_malloc_deinit();

    return ret;
}

hi_u32 loady_version_file(uintptr_t ram_addr)
{
    hi_u32 ret;

    if (load_malloc_init() != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    loader_ack(ACK_SUCCESS);

    ret = loader_serial_ymodem(ram_addr, 0, 0x7, 0x8);

    load_malloc_deinit();

    return ret;
}

hi_u32 download_to_flash(hi_u32 flash_offset, hi_u32 erase_size, hi_u32 flash_size)
{
    hi_u32 ret;

    ret = g_flash_cmd_funcs.init();
    if (ret != HI_ERR_FLASH_RE_INIT && ret != HI_ERR_SUCCESS &&
        ret != HI_ERR_FLASH_QUAD_MODE_COMPARE_REG) {
        boot_msg1("probe ", ret);
        return HI_ERR_FAILURE;
    }

    if (load_malloc_init() != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;  /* failure */
    }

    if (erase_size == 0) {
        boot_msg0("len error");
        load_malloc_deinit();
        return HI_ERR_FAILURE;
    }

    boot_msg2("erase flash ", flash_offset, erase_size);

    ret = g_flash_cmd_funcs.erase(flash_offset, erase_size);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("erase faild ret=", (hi_u32)ret);
        load_malloc_deinit();
        return HI_ERR_FAILURE;
    }

    boot_msg0("Ready for download");

    loader_ack(ACK_SUCCESS);
    ret = loader_serial_ymodem(flash_offset, erase_size, 0, flash_size);
    load_malloc_deinit();
    return ret;
}

hi_u32 download_image(hi_u32 addr, hi_u32 erase_size, hi_u32 flash_size, hi_u8 burn_efuse)
{
    hi_u32 ret;
    hi_unref_param(burn_efuse);

    ret = download_to_flash(addr, erase_size, flash_size);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
    if (((addr == DEFAULT_KERNEL_BURN_ADDR) && (erase_size > FLASHBOOT_MAX_SIZE)) ||
        ((addr == 0) && (erase_size > FLASHBOOT_MAX_SIZE))) {
        ret = crypto_check_encrypt();
        if (ret != HI_ERR_SUCCESS) {
            boot_put_errno(HI_PRINT_ERRNO_CRYPTO_FW_ENCRYPT_ERR);
            return ret;
        }
    }
#endif

    return HI_ERR_SUCCESS;
}

hi_u32 download_factory_image(hi_u32 addr, hi_u32 erase_size, hi_u32 flash_size, hi_u8 burn_efuse)
{
    hi_u32 ret;
    hi_unref_param(burn_efuse);

    ret = download_to_flash(addr, erase_size, flash_size);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
        ret = crypto_encrypt_factory_image(addr);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
#endif

    return HI_ERR_SUCCESS;
}

hi_u32 upload_malloc_init(hi_void)
{
    if (g_upload_ctx == HI_NULL) {
        g_upload_ctx = (upload_context *)boot_malloc(sizeof(upload_context));
    }

    if (g_upload_ctx == HI_NULL) {
        return HI_ERR_FAILURE;
    }

    hi_u32 check_sum = (uintptr_t)g_upload_ctx ^ (hi_u32)sizeof(upload_context) ^ 0 ^ (hi_u32)sizeof(upload_context);
    (hi_void) memset_s(g_upload_ctx, sizeof(upload_context), 0, sizeof(upload_context), check_sum);

    return HI_ERR_SUCCESS;
}
hi_u32 upload_malloc_deinit(hi_void)
{
    hi_u32 ret;
    ret = boot_free(g_upload_ctx);
    if (ret == HI_ERR_SUCCESS) {
        g_upload_ctx = HI_NULL;
    }

    return ret;
}

hi_void upload_send_file_info(hi_void)
{
    upload_context *ctx = g_upload_ctx;
    hi_u8 name_length = UPLOAD_FILE_NAME_LEN;
    hi_u8 *data = HI_NULL;
    hi_s32 temp_length = (hi_s32)ctx->file_length;
    hi_s32 count = 0;
    hi_u8 temp_char;
    hi_u16 crc;
    hi_s32 i;
    hi_u32 check_sum;

    if (ctx->retry > 0) {
        serial_put_buf((const char *)ctx->buffer, SOH_MSG_TOTAL_LEN);
        return;
    }

    hi_u32 check_sum_val = (uintptr_t)(ctx->buffer) ^ (hi_u32)sizeof(ctx->buffer) ^ 0 ^ (hi_u32)sizeof(ctx->buffer);
    (hi_void) memset_s(ctx->buffer, sizeof(ctx->buffer), 0, sizeof(ctx->buffer), check_sum_val);
    ctx->buffer[0] = MODEM_SOH;
    ctx->buffer[1] = ctx->seq;
    ctx->buffer[2] = (hi_u8)~ctx->buffer[1]; /* buffer[2] is buffer[1] invert val */

    check_sum = (uintptr_t)(ctx->buffer + MSG_START_LEN) ^ SOH_MSG_LEN ^ (uintptr_t)(ctx->file_name) ^
        (hi_u32)name_length;
    if (memcpy_s(ctx->buffer + MSG_START_LEN, SOH_MSG_LEN, ctx->file_name, name_length, check_sum) != EOK) {
        return;
    }

    data = ctx->buffer + MSG_START_LEN + name_length;

    while (temp_length > 0) {
        data[count++] = (hi_u8)((hi_u8)'0' + (temp_length % DECIMAL));
        temp_length /= DECIMAL;
    }

    /* 64 bytes, enough for storing 32-bit decimal digits
       CNcomment:64字节足够存放32位10进制数 */
    for (i = 0; i < count / 2; i++) { /* count should be divided by 2 */
        temp_char = data[i];
        data[i] = data[count - i - 1];
        data[count - i - 1] = temp_char;
    }

    check_sum = 0 ^ (uintptr_t)(ctx->buffer + MSG_START_LEN) ^ SOH_MSG_LEN;
    crc = crc16_ccitt(0, ctx->buffer + MSG_START_LEN, SOH_MSG_LEN, check_sum);
    ctx->buffer[131] = (hi_u8)(crc >> 8); /* buffer[131] is crc high 8 bit */
    ctx->buffer[132] = (hi_u8)crc; /* buffer[132] is crc low 8 bit */

    serial_put_buf((const char *)ctx->buffer, SOH_MSG_TOTAL_LEN);

    ctx->status = UPLOAD_WAIT_INIT_ACK;
}

hi_void upload_send_null_info(hi_void)
{
    upload_context *ctx = g_upload_ctx;
    hi_u16 crc;

    hi_u32 check_sum_val = (uintptr_t)(ctx->buffer) ^ (hi_u32)sizeof(ctx->buffer) ^ 0 ^ SOH_MSG_LEN;
    (hi_void) memset_s(ctx->buffer, sizeof(ctx->buffer), 0, SOH_MSG_LEN, check_sum_val);
    ctx->buffer[0] = MODEM_SOH;
    ctx->buffer[1] = 0;
    ctx->buffer[2] = 0xFF;  /* buffer[2] is buffer[1] invert val */
    hi_u32 check_sum = 0 ^ (uintptr_t)(ctx->buffer + MSG_START_LEN) ^ SOH_MSG_LEN;
    crc = crc16_ccitt(0, ctx->buffer + MSG_START_LEN, SOH_MSG_LEN, check_sum);
    ctx->buffer[131] = (hi_u8)(crc >> 8); /* buffer[131] is crc high 8 bit */
    ctx->buffer[132] = (hi_u8)crc; /* buffer[132] is crc low 8 bit */
    serial_put_buf((const char *)ctx->buffer, SOH_MSG_TOTAL_LEN);

    ctx->status = UPLOAD_WAIT_ZERO_ACK;
}

hi_void upload_send_data(hi_void)
{
    upload_context *ctx = g_upload_ctx;
    hi_u32 remain = ctx->file_length - ctx->offset;
    hi_u16 crc;

    if (ctx->retry > 0) {
        if (ctx->buffer[0] == MODEM_SOH) {
            serial_put_buf((const char *)ctx->buffer, SOH_MSG_TOTAL_LEN);
        } else {
            serial_put_buf((const char *)ctx->buffer, UPLOAD_BUFF_LEN);
        }

        return;
    }

    ctx->status = UPLOAD_WAIT_FINAL_ACK;
    hi_u32 check_sum = (uintptr_t)(ctx->buffer) ^ (hi_u32)sizeof(ctx->buffer) ^ MODEM_EOF ^ (hi_u32)sizeof(ctx->buffer);
    (hi_void) memset_s(ctx->buffer, sizeof(ctx->buffer), MODEM_EOF, sizeof(ctx->buffer), check_sum);

    ctx->buffer[0] = MODEM_STX;
    ctx->buffer[1] = ++ctx->seq;
    ctx->buffer[2] = (hi_u8)~ctx->buffer[1];  /* buffer[2] is buffer[1] invert val */

    if (remain <= SOH_MSG_LEN) {
        ctx->buffer[0] = MODEM_SOH;
        if (memcpy_s (ctx->buffer + MSG_START_LEN, SOH_MSG_LEN,
            (const hi_void *)(uintptr_t)(ctx->file_addr + ctx->offset), remain, (uintptr_t)(ctx->buffer + MSG_START_LEN)
            ^ SOH_MSG_LEN ^ (uintptr_t)(const hi_void *)(uintptr_t)(ctx->file_addr + ctx->offset) ^ remain) != EOK) {
            return;
        }
        check_sum = 0 ^ (uintptr_t)(ctx->buffer + MSG_START_LEN) ^ SOH_MSG_LEN;
        crc = crc16_ccitt(0, ctx->buffer + MSG_START_LEN, SOH_MSG_LEN, check_sum);
        ctx->buffer[131] = (hi_u8)(crc >> 8); /* buffer[131] is crc high 8 bit */
        ctx->buffer[132] = (hi_u8)crc; /* buffer[132] is crc low 8 bit */
        serial_put_buf((const char *)ctx->buffer, SOH_MSG_TOTAL_LEN);
    } else {
        if (remain > UPLOAD_DATA_SIZE) {
            remain = UPLOAD_DATA_SIZE;
            ctx->status = UPLOAD_WAIT_INTER_ACK;
        }
        check_sum = (uintptr_t)(ctx->buffer + MSG_START_LEN) ^ UPLOAD_DATA_SIZE ^
            (uintptr_t)(const hi_void *)(uintptr_t)(ctx->file_addr + ctx->offset) ^ remain;
        if (memcpy_s(ctx->buffer + MSG_START_LEN, UPLOAD_DATA_SIZE,
            (const hi_void *)(uintptr_t)(ctx->file_addr + ctx->offset), remain, check_sum) != EOK) {
            return;
        }
        check_sum = 0 ^ (uintptr_t)(ctx->buffer + MSG_START_LEN) ^ UPLOAD_DATA_SIZE;
        crc = crc16_ccitt(0, ctx->buffer + MSG_START_LEN, UPLOAD_DATA_SIZE, check_sum);
        ctx->buffer[1027] = (hi_u8)(crc >> 8); /* buffer[1027] is crc high 8 bit */
        ctx->buffer[1028] = (hi_u8)crc; /* buffer[1028] is crc low 8 bit */
        serial_put_buf((const char *)ctx->buffer, UPLOAD_BUFF_LEN);
    }

    ctx->offset += remain;
}

hi_s32 upload_modem_c_step(hi_u8 status)
{
    switch (status) {
        case UPLOAD_WAIT_START_C:
            upload_send_file_info();
            return 1;
        case UPLOAD_WAIT_TRANS_C:
            upload_send_data();
            return 1;
        case UPLOAD_WAIT_EOT_C:
            upload_send_null_info();
            return 1;
        default:
            return 0;
    }
}

hi_s32 upload_modem_ack_step(hi_u8 *status, hi_u32 *timeout)
{
    switch (*status) {
        case UPLOAD_WAIT_INIT_ACK:
            *timeout = UPLOAD_WAIT_DEFAULT_TIME;
            *status = UPLOAD_WAIT_TRANS_C;
            return 1;
        case UPLOAD_WAIT_INTER_ACK:
            upload_send_data();
            return 1;
        case UPLOAD_WAIT_FINAL_ACK:
            serial_putc(MODEM_EOT);
            *status = UPLOAD_WAIT_EOT_C;
            return 1;
        default:
            return 0;
    }
}

hi_s32 upload_modem_nak_step(hi_u8 *status, hi_u32 *timeout)
{
    switch (*status) {
        case UPLOAD_WAIT_INIT_ACK:
            *timeout = UPLOAD_WAIT_START_C_TIME;
            upload_send_file_info();
            return 1;
        case UPLOAD_WAIT_INTER_ACK:
        case UPLOAD_WAIT_FINAL_ACK:
            upload_send_data();
            return 1;
        case UPLOAD_WAIT_EOT_C:
            serial_putc(MODEM_EOT);
            *status = UPLOAD_WAIT_EOT_C;
            return 1;
        case UPLOAD_WAIT_ZERO_ACK:
            upload_send_null_info();
            return 1;
        default:
            return 0;
    }
}

hi_u32 upload_serial_ymodem(hi_void)
{
    upload_context *ctx = g_upload_ctx;
    hi_u8 ch;
    hi_u32 timeout = UPLOAD_WAIT_START_C_TIME;

    for (;;) {
        hi_u32 ret = serial_getc_timeout(timeout, &ch);
        if (ret != HI_ERR_SUCCESS) {
            continue;
        }

        switch (ch) {
            case MODEM_C:
                ctx->can_cnt = 0;
                ctx->retry = 0;
                if (upload_modem_c_step(ctx->status) == 1) {
                    continue;
                }
                break;

            case MODEM_ACK:
                ctx->can_cnt = 0;
                ctx->retry = 0;
                if (ctx->status == UPLOAD_WAIT_ZERO_ACK) {
                    mdelay(WAIT_ZERO_ACK_DELAY);
                    return HI_ERR_SUCCESS;
                }
                if (upload_modem_ack_step(&ctx->status, &timeout) == 1) {
                    continue;
                }
                break;

            case MODEM_NAK:
                ctx->can_cnt = 0;

                if (++ctx->retry == RETRY_COUNT) {
                    return HI_ERR_FAILURE;
                }
                if (upload_modem_nak_step(&ctx->status, &timeout) == 1) {
                    continue;
                }
                break;

            case MODEM_CAN:
                ctx->retry = 0;

                if (++ctx->can_cnt == CAN_COUNT) {
                    return HI_ERR_FAILURE;
                }

                continue;
                /* fall-through */
            default:
                continue;
        }
    }
}

hi_u32 upload_data(hi_u32 addr, hi_u32 length)
{
    if (upload_malloc_init() != HI_ERR_SUCCESS) {
        boot_msg0("upload init fail.");
        return HI_ERR_FAILURE;
    }

    g_upload_ctx->file_addr = addr + FLASH_ADDR_OFFSET;
    g_upload_ctx->file_length = length;
    g_upload_ctx->file_name = UPLOAD_FILE_NAME;
    g_upload_ctx->status = UPLOAD_WAIT_START_C;

    loader_ack(ACK_SUCCESS);

    if (upload_serial_ymodem() == HI_ERR_SUCCESS) {
        upload_malloc_deinit();
        return HI_ERR_SUCCESS;
    }
    upload_malloc_deinit();
    return HI_ERR_FAILURE;
}
