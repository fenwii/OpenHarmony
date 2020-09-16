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

#include <cmd_loop.h>
#include <crc.h>
#include <transfer.h>

#define CMD_RX_DELAY_MS     100 /* 100ms */
#define US_PER_MS           1000
#define CMD_FRAME_TIMEOUT   20000 /* 20s */
#define CMD_ABNORMAL_MAX    100
#define CHECKSUM_SIZE       2
#define ACK_LEN             0x0C

#define VER_CFG_BIN_LEN 8
#define UPDATE_VER_STATUS_NONE        0
#define UPDATE_VER_STATUS_BOOT        1
#define UPDATE_VER_STATUS_KERNEL      2
#define UPDATE_VER_STATUS_BOOT_KERNEL 3
#define KERELN_VER_MAX          48
#define KERNEL_VER_LEN          6
#define BOOT_VER_MAX            16
#define BOOT_VER_LEN            2
#define BIT_U8   8
#define SEC_BOOT_FLAG 0x42
#define WAIT_VER_UPDATE_TRY_CNT 1000
#define WAIT_VER_UPDATE_TRY_INTER_US 10000

#define NMI_BASE_ADDRESS    0x40010000
#define NMI_CTRL            0x0258
#define NMI_INT_MOD_DONE_EN_POS 0

volatile hi_u8 g_update_ver_status = UPDATE_VER_STATUS_NONE;
volatile hi_bool g_upg_update_ver_success = HI_FALSE;
hi_u8 g_upg_efuse_data_boot_ver[BOOT_VER_LEN] = {0};
hi_u8 g_upg_efuse_data_kernel_ver[KERNEL_VER_LEN] = {0};
void *g_nmi_stack_end = ((void *) &__nmi_stack_top);

typedef enum {
    CMD_RX_STATUS_WAIT_START_0,
    CMD_RX_STATUS_WAIT_START_1,
    CMD_RX_STATUS_WAIT_START_2,
    CMD_RX_STATUS_WAIT_START_3,
    CMD_RX_STATUS_WAIT_SIZE_0,
    CMD_RX_STATUS_WAIT_SIZE_1,
    CMD_RX_STATUS_WAIT_TYPE,
    CMD_RX_STATUS_WAIT_PAD,
    CMD_RX_STATUS_WAIT_DATA,
    CMD_RX_STATUS_WAIT_CS_0,
    CMD_RX_STATUS_WAIT_CS_1,
} cmd_rx_status;

typedef hi_u32(*cmd_func) (const uart_ctx *cmd_ctx);

typedef struct {
    hi_u8 cmd_type;
    cmd_func cmdfunc;
} loader_cmd;

uart_ctx *g_cmd_ctx = HI_NULL;

const loader_cmd g_loader_cmdtable[LOADER_CMD_MAX] = {
    { CMD_DL_IMAGE,         loader_download_image },
    { CMD_BURN_EFUSE,       loader_burn_efuse },
    { CMD_UL_DATA,          loader_upload_data },
    { CMD_READ_EFUSE,       loader_read_efuse },
    { CMD_FLASH_PROTECT,    loader_flash_protect },
    { CMD_RESET,            loader_reset },
    { CMD_FACTORY_IMAGE,    loader_download_image },
    { CMD_VERSION,          loader_burn_version},
};

hi_void loader_read_flash_protect_state(hi_void)
{
    hi_u32 reg = 0;
    hi_reg_write(SFC_REG_BASE_ADDRESS + SFC_REG_CMD_DATABUF1, 0);
    spif_wait_config_start();
    hi_reg_write(SFC_REG_BASE_ADDRESS + SFC_REG_CMD_INS, 0x05);
    hi_reg_write(SFC_REG_BASE_ADDRESS + SFC_REG_CMD_CONFIG, 0x183);
    spif_wait_config_start();
    hi_reg_read(SFC_REG_BASE_ADDRESS + SFC_REG_CMD_DATABUF1, reg);
    boot_msg1("S0 ~ S7   : ", reg);
    hi_reg_write(SFC_REG_BASE_ADDRESS + SFC_REG_CMD_DATABUF1, 0);
    spif_wait_config_start();
    hi_reg_write(SFC_REG_BASE_ADDRESS + SFC_REG_CMD_INS, 0x35);
    hi_reg_write(SFC_REG_BASE_ADDRESS + SFC_REG_CMD_CONFIG, 0x183);
    spif_wait_config_start();
    hi_reg_read(SFC_REG_BASE_ADDRESS + SFC_REG_CMD_DATABUF1, reg);
    boot_msg1("S8 ~ S15 : ", reg);
}

hi_u32 loader_reset(const uart_ctx *cmd_ctx)
{
    hi_unref_param(cmd_ctx);
    boot_msg0("\nReset device...\n");
    loader_ack(ACK_SUCCESS);
    mdelay(5);  /* delay 5ms */
    global_reset();
    return HI_ERR_SUCCESS;
}

hi_u32 loader_flash_protect(const uart_ctx *cmd_ctx)
{
    hi_u32 ret;
    hi_u16 cmd_type = *(hi_u16 *)(&cmd_ctx->packet.payload[0]);
    boot_msg0("Flash protect state");
    loader_read_flash_protect_state();
    if (cmd_type == 1) {
        ret = flash_protect_set_protect(0, HI_FALSE);
        if (ret == HI_ERR_SUCCESS) {
            boot_msg0("\r\nUnlock Succ\r\n");
            loader_read_flash_protect_state();
        } else {
            boot_msg0("\r\nUnlock Fail\r\n");
        }
        return ret;
    } else if (cmd_type > 1) {
        boot_msg0("Unknow cmd type");
        return HI_ERR_FAILURE;
    }
    return HI_ERR_SUCCESS;
}

hi_u32 loader_download_image(const uart_ctx *cmd_ctx)
{
    hi_u8 chip_id[HI_FLASH_CHIP_ID_NUM] = { 0 };
    hi_u32 flash_size = 0;
    hi_u32 download_addr = *(hi_u32 *)(&cmd_ctx->packet.payload[0]);
    hi_u32 file_len = *(hi_u32 *)(&cmd_ctx->packet.payload[4]); /* offset 4 is file length */
    hi_u32 erase_size = *(hi_u32 *)(&cmd_ctx->packet.payload[8]); /* offset 8 is erase size */
    hi_u8 burn_efuse = cmd_ctx->packet.payload[12]; /* offset 12 is burn efuse flag */
    hi_u32 ret = spi_flash_read_chip_id(chip_id, HI_FLASH_CHIP_ID_NUM);
    if (ret == HI_ERR_SUCCESS) {
        flash_size = spi_flash_get_size((const hi_u8 *)chip_id);
    } else {
        boot_msg0("Get flash size fail");
        return HI_ERR_FAILURE;
    }

    if (file_len == 0 || erase_size == 0 || erase_size < file_len || (download_addr + file_len) > flash_size) {
        boot_msg0("Invalid params");
        serial_puts("download_addr ");
        serial_puthex(download_addr, 1);
        serial_puts(" file_len ");
        serial_puthex(file_len, 1);
        serial_puts(" erase_size ");
        serial_puthex(erase_size, 1);
        serial_puts("\r\n");
        return HI_ERR_FAILURE;
    }

#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
    hi_u64 efuse_lock_status = 0;
    ret = hi_efuse_get_lockstat(&efuse_lock_status);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }
    if ((efuse_lock_status & 0x10) == 0) {
        boot_msg0("Enable flash encryption: ");
        boot_msg0("Please write and lock efuse root key field first!");
        return HI_ERR_FAILURE;
    }
#endif

    if (cmd_ctx->packet.head.type == CMD_FACTORY_IMAGE) {
        return download_factory_image(download_addr, erase_size, flash_size, burn_efuse);
    }

    return download_image(download_addr, erase_size, flash_size, burn_efuse);
}


hi_bool tool_bit_test(const hi_u8 *data, hi_u16 pos, hi_u16 data_len)
{
    hi_u16 base = pos / BIT_U8;
    hi_u16 i = pos % BIT_U8;
    if (pos > (data_len * BIT_U8)) {
        return HI_FALSE;
    }
    return (hi_bool)bit_get(data[base], i);
}

hi_void tool_bit_set(hi_u8 *data, hi_u16 pos, hi_u8 val)
{
    hi_u16 base = pos / BIT_U8;
    hi_u16 i = pos % BIT_U8;
    bit_set(data[base], i, val);
}

hi_u32 get_secure_boot_flag(hi_bool *secure_flag)
{
    hi_u8 data = 0;
    hi_u32 ret = hi_efuse_read(HI_EFUSE_SEC_BOOT_RW_ID, (hi_u8 *)(&data), (hi_u8)(sizeof(hi_u8)));
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("secure boot efuse read err:", ret);
        return ret;
    }

    if (data == SEC_BOOT_FLAG) {
        *secure_flag = HI_FALSE;
    } else {
        *secure_flag = HI_TRUE;
    }

    return HI_ERR_SUCCESS;
}


hi_u32 get_efuse_boot_ver(hi_u8 *ver)
{
    hi_u8 pos;
    hi_u8 efuse_data[BOOT_VER_LEN] = { 0 };
    hi_u32 ret = hi_efuse_read(HI_EFUSE_TEE_BOOT_VER_RW_ID, efuse_data, sizeof(efuse_data));
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    for (pos = 0; pos < BOOT_VER_MAX; pos++) {
        if (tool_bit_test(efuse_data, pos, BOOT_VER_LEN) == HI_FALSE) {
            break;
        }
    }
    if (pos >= BOOT_VER_MAX) {
        *ver = BOOT_VER_MAX;
    } else {
        *ver = pos;
    }
    return ret;
}

hi_u32 get_efuse_code_ver(hi_u8 *ver)
{
    hi_u8 pos;
    hi_u8 efuse_data[KERNEL_VER_LEN];
    hi_u32 ret;

    hi_u32 cs = (uintptr_t)efuse_data ^ KERNEL_VER_LEN ^ 0 ^ KERNEL_VER_LEN;
    (hi_void) memset_s(efuse_data, KERNEL_VER_LEN, 0, KERNEL_VER_LEN, cs);
    ret = hi_efuse_read(HI_EFUSE_TEE_KERNEL_VER_RW_ID, efuse_data, sizeof(efuse_data));
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    for (pos = 0; pos < KERELN_VER_MAX; pos++) {
        if (tool_bit_test(efuse_data, pos, KERNEL_VER_LEN) == HI_FALSE) {
            break;
        }
    }
    if (pos >= KERELN_VER_MAX) {
        *ver = KERELN_VER_MAX;
    } else {
        *ver = pos;
    }
    return ret;
}

hi_u32 start_and_wait_update_ver()
{
    /* init upg flag */
    g_upg_update_ver_success = HI_FALSE;

    /* trigger upg nmi */
    hi_reg_setbit(NMI_BASE_ADDRESS + NMI_CTRL, NMI_INT_MOD_DONE_EN_POS);

    /* wait nmi handle finish */
    hi_u32 try_cnt;
    for (try_cnt = 0; try_cnt < WAIT_VER_UPDATE_TRY_CNT; try_cnt++) {
        if (g_update_ver_status == UPDATE_VER_STATUS_NONE) {
            break;
        }
        udelay(WAIT_VER_UPDATE_TRY_INTER_US);   /* sleep 10ms */
    }

    if (g_upg_update_ver_success == HI_TRUE) {
        return HI_ERR_SUCCESS;
    } else if (try_cnt == WAIT_VER_UPDATE_TRY_CNT) {
        return HI_ERR_UPG_UPDATE_VER_TIMEOUT;
    } else {
        return HI_ERR_UPG_UPDATE_VER_FAIL;
    }
}

hi_u32 check_boot_kernel_ver(hi_u8 boot_ver, hi_u8 kernel_ver, hi_u8 *current_boot_ver, hi_u8 *current_kernel_ver)
{
    hi_u32 ret;

    ret = get_efuse_boot_ver(current_boot_ver);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("get boot ver ret:", ret);
        return ret;
    }

    ret = get_efuse_code_ver(current_kernel_ver);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("get kernel ver ret:", ret);
        return ret;
    }

    if (boot_ver < *current_boot_ver) {
        boot_msg2("current boot ver >boot ver:", *current_boot_ver, boot_ver);
        return HI_ERR_UPG_LOW_KERNEL_VER;
    }

    if (kernel_ver < *current_kernel_ver) {
        boot_msg2("current kernel ver > kernel ver:", *current_kernel_ver, kernel_ver);
        return HI_ERR_UPG_LOW_KERNEL_VER;
    }

    if (boot_ver > BOOT_VER_MAX || kernel_ver > KERELN_VER_MAX) {
        boot_msg2("invalid boot ver, kernel ver:", boot_ver, kernel_ver);
        return HI_ERR_UPG_FULL_KERNEL_VER;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 set_efuse_boot_kernel_ver(hi_u8 boot_ver, hi_u8 kernel_ver)
{
    hi_u32 ret;
    hi_u8 pos;
    hi_u8 current_boot_ver = 0;
    hi_u8 current_kernel_ver = 0;
    hi_bool flag = HI_FALSE;

    ret = get_secure_boot_flag(&flag);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if (flag == HI_FALSE) {
        boot_msg0("not secure boot.");
        return HI_ERR_SUCCESS;
    }

    ret = check_boot_kernel_ver(boot_ver, kernel_ver, &current_boot_ver, &current_kernel_ver);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    hi_bool update_boot_ver = HI_FALSE;
    hi_bool update_kernel_ver = HI_FALSE;
    if (boot_ver != current_boot_ver) {
        hi_u32 cs = (uintptr_t)g_upg_efuse_data_boot_ver ^ BOOT_VER_LEN ^ 0 ^ BOOT_VER_LEN;
        (hi_void) memset_s(g_upg_efuse_data_boot_ver, BOOT_VER_LEN, 0, BOOT_VER_LEN, cs);
        for (pos = current_boot_ver; pos < boot_ver; pos++) {
            tool_bit_set(g_upg_efuse_data_boot_ver, pos, SRV_BIT_HIGH);
        }
        update_boot_ver = HI_TRUE;
    }

    if (kernel_ver != current_kernel_ver) {
        hi_u32 cs = (uintptr_t)g_upg_efuse_data_kernel_ver ^ KERNEL_VER_LEN ^ 0 ^ KERNEL_VER_LEN;
        (hi_void) memset_s(g_upg_efuse_data_kernel_ver, KERNEL_VER_LEN, 0, KERNEL_VER_LEN, cs);
        for (pos = current_kernel_ver; pos < kernel_ver; pos++) {
            tool_bit_set(g_upg_efuse_data_kernel_ver, pos, SRV_BIT_HIGH);
        }
        update_kernel_ver = HI_TRUE;
    }

    if (update_boot_ver == HI_FALSE && update_kernel_ver == HI_FALSE) {
        boot_msg0("same ver with efuse");
        return HI_ERR_SUCCESS;
    } else if (update_boot_ver == HI_TRUE && update_kernel_ver == HI_TRUE) {
        g_update_ver_status =  UPDATE_VER_STATUS_BOOT_KERNEL;
    } else if (update_boot_ver == HI_TRUE) {
        g_update_ver_status =  UPDATE_VER_STATUS_BOOT;
    } else {
        g_update_ver_status =  UPDATE_VER_STATUS_KERNEL;
    }

    ret = start_and_wait_update_ver();

    return ret;
}

hi_void nmi_update_ver(hi_void)
{
    if (g_update_ver_status == UPDATE_VER_STATUS_NONE) {
        return;
    }

    hi_u32 ret;

    if (g_update_ver_status == UPDATE_VER_STATUS_BOOT || g_update_ver_status == UPDATE_VER_STATUS_BOOT_KERNEL) {
        ret = hi_efuse_write(HI_EFUSE_TEE_BOOT_VER_RW_ID, g_upg_efuse_data_boot_ver);
        if (ret != HI_ERR_SUCCESS) {
            boot_msg1("update boot ver fail, ret:", ret);
            g_upg_update_ver_success = HI_FALSE;
            g_update_ver_status = UPDATE_VER_STATUS_NONE;
            return;
        }
    }

    if (g_update_ver_status == UPDATE_VER_STATUS_KERNEL || g_update_ver_status == UPDATE_VER_STATUS_BOOT_KERNEL) {
        ret = hi_efuse_write(HI_EFUSE_TEE_KERNEL_VER_RW_ID, g_upg_efuse_data_kernel_ver);
        if (ret != HI_ERR_SUCCESS) {
            boot_msg1("update kernel ver fail, ret:", ret);
            g_upg_update_ver_success = HI_FALSE;
            g_update_ver_status = UPDATE_VER_STATUS_NONE;
            return;
        }
    }

    g_upg_update_ver_success = HI_TRUE;
    g_update_ver_status = UPDATE_VER_STATUS_NONE;

    return;
}

hi_u32 loader_burn_version(const uart_ctx *cmd_ctx)
{
    hi_u32 ret;
    hi_u32 file_len = *(hi_u32 *)(&cmd_ctx->packet.payload[0]);
    if (file_len != VER_CFG_BIN_LEN) {
        boot_msg1("Ver length error : ", file_len);
        return HI_ERR_FAILURE;
    }
    hi_u8 *buf = boot_malloc(file_len);
    if (buf == HI_NULL) {
        boot_msg0("Malloc buffer error");
        return HI_ERR_FAILURE;
    }

    ret = loady_version_file((uintptr_t)buf);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("Loady ver file failed:", ret);
        return ret;
    }

    hi_u32 boot_ver = *(hi_u32 *)buf;
    hi_u32 kernel_ver = *(hi_u32 *)(buf + 4); /* 4: 4 byte as a word(little ending). */

    boot_msg1("boot ver:", boot_ver);
    boot_msg1("kernel_ver:", kernel_ver);

    ret = set_efuse_boot_kernel_ver(boot_ver, kernel_ver);

    return ret;
}

void boot_nmi_handler(void)
{
    hi_u32 *sp_val = 0;

    /* clear NMI interrupt */
    hi_reg_write(NMI_BASE_ADDRESS + NMI_CTRL, 0x0);
    __asm__ __volatile__("fence":::"memory");

    nmi_update_ver();

    /* NOTICE: Start Clear NMI Stack, All User nmi service MUST BE DONE at this moment!!! */
    __asm__ volatile ("mv %0, sp" : "=r"(sp_val));
    while (sp_val != (hi_u32 *)(&__nmi_stack_bottom)) {
        *sp_val = 0;
        sp_val--;
    }
}

hi_u32 loader_burn_efuse(const uart_ctx *cmd_ctx)
{
    hi_u32 ret;
    hi_u32 file_len = *(hi_u32 *)(&cmd_ctx->packet.payload[0]);
    if (file_len <= EFUSE_CFG_MIN_LEN || file_len > EFUSE_CFG_MAX_LEN) {
        boot_msg1("File length error : ", file_len);
        return HI_ERR_FAILURE;
    }

    hi_u8 *buf = boot_malloc(file_len);
    if (buf == HI_NULL) {
        boot_msg0("Malloc buffer error");
        return HI_ERR_FAILURE;
    }

    ret = loady_file((uintptr_t)buf);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("Loady efuse file failed:", ret);
        return ret;
    }

    ret = efuse_burn((uintptr_t)buf, file_len);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    /* 复位efuse模块，使得efuse立即生效，应用于在烧写过程中依赖huks根秘钥的场景 */
    /* reset efuse for validate immediately */
    hi_reg_clrbit16(CLDO_CTL_SOFT_RESET2_REG, EFUSE_RST_BIT);
    udelay(0x3);
    hi_reg_setbit16(CLDO_CTL_SOFT_RESET2_REG, EFUSE_RST_BIT);

    return HI_ERR_SUCCESS;
}

hi_u32 loader_read_efuse(const uart_ctx *cmd_ctx)
{
    hi_u32 ret;
    hi_u16 start_bit = *(hi_u16 *)(&cmd_ctx->packet.payload[0]);
    hi_u16 size = *(hi_u16 *)(&cmd_ctx->packet.payload[2]); /* offset 2 is read size */
    boot_msg0("Efuse read");
    serial_puts("Start bit: ");
    serial_puthex(start_bit, 1);
    serial_puts(" len(bits)=");
    serial_puthex(size, 1);
    serial_puts("\r\n");
    if ((start_bit >= EFUSE_BIT_NUM) || ((start_bit + size) > EFUSE_BIT_NUM) || size > EFUSE_READ_MAX_BITS) {
        boot_msg0("Params err");
        return HI_ERR_FAILURE;
    }

    ret = efuse_read(start_bit, size);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 loader_upload_data(const uart_ctx *cmd_ctx)
{
    hi_u8 chip_id[HI_FLASH_CHIP_ID_NUM] = {0};
    hi_u32 flash_size = 0;
    hi_u32 file_len = *(hi_u32 *)(&cmd_ctx->packet.payload[0]);
    hi_u32 upload_addr = *(hi_u32 *)(&cmd_ctx->packet.payload[4]);  /* offset 4 is read addr */
    boot_msg2("Upload addr, length :", upload_addr, file_len);

    hi_u32 ret = spi_flash_read_chip_id(chip_id, HI_FLASH_CHIP_ID_NUM);
    if (ret == HI_ERR_SUCCESS) {
        flash_size = spi_flash_get_size((const hi_u8 *)chip_id);
    } else {
        boot_msg0("Get flash size fail");
        return HI_ERR_FAILURE;
    }

    if (file_len == 0 || file_len > flash_size) {
        boot_msg0("Upload length error");
        return HI_ERR_FAILURE;
    }

    if ((upload_addr & 0x3) != 0) {
        boot_msg0("Upload addr error");
        return HI_ERR_FAILURE;
    }

    if ((upload_addr + file_len) > flash_size) {
        boot_msg0("Upload addr exceeds flash capacity");
        return HI_ERR_FAILURE;
    }

    return upload_data(upload_addr, file_len);
}

hi_u32 loader_frame_head_rx(uart_ctx *ctx)
{
    hi_u8 ch;
    hi_bool reset_flag = HI_FALSE;
    hi_u16 rcv = 0;

    packet_data_head *head = &ctx->packet.head;
    hi_u8 *payload = (hi_u8 *)head;

    while (rcv <= CMD_ABNORMAL_MAX) {
        hi_u32 ret = serial_getc_timeout(CMD_FRAME_TIMEOUT * US_PER_MS, &ch);
        if (ret != HI_ERR_SUCCESS) {
            continue;
        }

        rcv++;
        if (reset_flag == HI_TRUE) {
            reset_flag = HI_FALSE;
            head->start_flag = 0;
            ctx->status = CMD_RX_STATUS_WAIT_START_0;
        }
        if (ctx->status <= CMD_RX_STATUS_WAIT_START_3) {
            hi_u32 start_flag = UART_PACKET_START_FLAG;
            hi_u8 *start_byte = (hi_u8 *)&start_flag;
            if (ch == start_byte[ctx->status]) {
                payload[ctx->status] = ch;
                ctx->status++;
                continue;
            } else if (ch == 0xEF) {
                payload[CMD_RX_STATUS_WAIT_START_0] = ch;
                ctx->status = CMD_RX_STATUS_WAIT_START_1;
                continue;
            }
            reset_flag = HI_TRUE;
            continue;
        } else {
            payload[ctx->status] = ch;
            if (ctx->status >= CMD_RX_STATUS_WAIT_START_1 && (head->packet_size > UART_PACKET_PAYLOAD_MAX)) {
                reset_flag = HI_TRUE;
                continue;
            }
            ctx->status++;
            if (ctx->status >= CMD_RX_STATUS_WAIT_DATA) {
                return HI_ERR_SUCCESS;
            }
        }
    }
    return HI_ERR_FAILURE;
}

hi_u32 loader_frame_data_rx(uart_ctx *ctx)
{
    hi_u8 ch;
    hi_u32 ret;
    ctx->received = 0;

    packet_data_head *head = &ctx->packet.head;
    hi_u8 *payload = ctx->packet.payload;

    while (ctx->received < (head->packet_size - sizeof(packet_data_head))) {
        ret = serial_getc_timeout(CMD_RX_DELAY_MS * US_PER_MS, &ch);
        if (ret == HI_ERR_SUCCESS) {
            payload[ctx->received++] = ch;
            continue;
        }
        return HI_ERR_FAILURE;
    }
    ctx->packet.check_sum = (payload[head->packet_size - 9] << 8) | payload[head->packet_size - 10]; /* 8,9,10: sub */
    payload[head->packet_size - 9] = 0;  /* 9: sub 9 */
    payload[head->packet_size - 10] = 0; /* 10: sub 10 */

    if (ctx->received == (head->packet_size - sizeof(packet_data_head))) {
        return HI_ERR_SUCCESS;
    }

    return HI_ERR_FAILURE;
}

hi_void loader_ack(hi_u8 err_code)
{
    uart_ctx *ctx = g_cmd_ctx;
    packet_data_head *head = &ctx->packet.head;

    head->start_flag = UART_PACKET_START_FLAG;
    head->type = CMD_ACK;
    head->pad = (hi_u8)(~(CMD_ACK));
    head->packet_size = ACK_LEN;
    ctx->packet.payload[0] = err_code;
    ctx->packet.payload[1] = ~err_code;
    hi_u32 cs = 0 ^ (uintptr_t)(hi_u8 *)&(ctx->packet) ^ (head->packet_size - CHECKSUM_SIZE);
    ctx->packet.check_sum = crc16_ccitt(0, (hi_u8 *)&(ctx->packet), head->packet_size - CHECKSUM_SIZE, cs);

    serial_put_buf ((const char *)&(ctx->packet), (int)(head->packet_size - CHECKSUM_SIZE));
    serial_put_buf ((const char *)&(ctx->packet.check_sum), CHECKSUM_SIZE);
}

hi_u32 loader_read_frame(uart_ctx *ctx)
{
    packet_data_info *packet = &ctx->packet;
    packet_data_head *head = &packet->head;
    hi_u32 ret;
    hi_u32 cs;

    /* Reset receiving status.CNcomment:复位接收状态 */
    ctx->status = CMD_RX_STATUS_WAIT_START_0;
    ctx->received = 0;
    cs = (uintptr_t)packet ^ (hi_u32)sizeof(packet_data_info) ^ 0 ^ (hi_u32)sizeof(packet_data_info);
    if (memset_s(packet, sizeof(packet_data_info), 0, sizeof(packet_data_info), cs) != EOK) {
        return HI_ERR_FAILURE;
    }

    ret = loader_frame_head_rx(ctx);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    ret = loader_frame_data_rx(ctx);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    cs = 0 ^ (uintptr_t)(hi_u8 *)packet ^ (head->packet_size - CHECKSUM_SIZE);
    cs = crc16_ccitt(0, (hi_u8 *)packet, head->packet_size - CHECKSUM_SIZE, cs);
    if (cs == packet->check_sum) {
        return HI_ERR_SUCCESS;
    }

    return HI_ERR_FAILURE;
}

hi_u32 loader_exe_cmd(uart_ctx *ctx)
{
    hi_u32 i;

    packet_data_info *packet = &ctx->packet;
    packet_data_head *head = &packet->head;
    for (i = 0; i < LOADER_CMD_MAX; i++) {
        if (head->type == g_loader_cmdtable[i].cmd_type) {
            if (g_loader_cmdtable[i].cmdfunc != HI_NULL) {
                return g_loader_cmdtable[i].cmdfunc(ctx);
            }
        }
    }

    if (i == LOADER_CMD_MAX) {
        boot_msg1("Unsupport CMD:", head->type);
    }

    return HI_ERR_FAILURE;
}

uart_ctx *cmd_loop_init(hi_void)
{
    if (g_cmd_ctx == HI_NULL) {
        g_cmd_ctx = (uart_ctx *)boot_malloc(sizeof(uart_ctx));
    }

    if (g_cmd_ctx != HI_NULL) {
        volatile hi_u32 check_sum = (uintptr_t)g_cmd_ctx ^ (hi_u32)sizeof(uart_ctx) ^ 0 ^ (hi_u32)sizeof(uart_ctx);
        (hi_void) memset_s(g_cmd_ctx, sizeof(uart_ctx), 0, sizeof(uart_ctx), check_sum);
        return g_cmd_ctx;
    }
    return HI_NULL;
}

hi_u32 cmd_loop_deinit(hi_void)
{
    hi_u32 ret = boot_free(g_cmd_ctx);
    if (ret == HI_ERR_SUCCESS) {
        g_cmd_ctx = HI_NULL;
    }

    return ret;
}

hi_void cmd_loop(uart_ctx *ctx)
{
    hi_u32 ret;
    for (;;) {
        ret = loader_read_frame(ctx);
        if (ret != HI_ERR_SUCCESS) {
            boot_msg0("\nGet CMD fail");
            loader_ack(ACK_FAILURE);
            continue;
        }

        ret = loader_exe_cmd(ctx);
        if (ret != HI_ERR_SUCCESS) {
            loader_ack(ACK_FAILURE);
            boot_msg0("\nExecution Failure : ");
            boot_msg0("============================================\n");
            continue;
        }

        loader_ack(ACK_SUCCESS);
        boot_msg0("\nExecution Successful");
        boot_msg0("============================================\n");
    }
}

