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

#include <app_demo_i2c.h>

/* Es8311 initialization array */
hi_u8 g_es8311_reg_array[I2C_REG_ARRAY_LEN] = {
    0x1F, 0x00, 0x00, 0x10, 0x10, 0x00, 0x03, 0x00, /* 0x00 ~ 0x0f */
    0xff, 0x00, 0x00, 0x00, 0x20, 0xfc, 0x6a, 0x00,
    0x13, 0x7c, 0x02, 0x40, 0x10, 0x00, 0x04, 0x00, /* 0x10 ~ 0x1f */
    0x00, 0x00, 0x00, 0x0b, 0x4b, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x20 ~ 0x2f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, /* 0x30 ~ 0x3f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

hi_u8 g_send_data[I2C_REG_ARRAY_LEN] = { 0 };

hi_void i2c_demo_send_data_init(hi_void)
{
    hi_u8 i;

    hi_u8 reg_addr = ES8311_REG_ADDR;

    g_send_data[0] = reg_addr;
    g_send_data[1] = g_es8311_reg_array[reg_addr];

    reg_addr++;
    g_send_data[2] = reg_addr;                       /* size 2 */
    g_send_data[3] = g_es8311_reg_array[reg_addr];   /* size 3 */

    for (i = 0; i < I2C_SEND_LEN_2; i++) {
        printf("----- data init:  send_buf[%d] = 0x%x! -----*\r\n", i, g_send_data[i]);
    }

    printf("\n");
}

hi_u32 i2c_demo_write(hi_i2c_idx id, hi_u16 device_addr, hi_u32 send_len)
{
    hi_u32 status;
    hi_i2c_data es8311_i2c_data = { 0 };

    es8311_i2c_data.send_buf = g_send_data;
    es8311_i2c_data.send_len = send_len;
    status = hi_i2c_write(id, device_addr, &es8311_i2c_data);
    if (status != HI_ERR_SUCCESS) {
        printf("===== Error: I2C write status = 0x%x! =====\r\n", status);
        return status;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 i2c_demo_writeread(hi_i2c_idx id, hi_u16 device_addr, hi_u32 recv_len)
{
    hi_u8 i;
    hi_u32 status;
    hi_u8 recv_data[I2C_REG_ARRAY_LEN] = { 0 };
    hi_i2c_data es8311_i2c_data = { 0 };

    printf("----- reg addr[0] = 0x%x! -----\r\n", g_send_data[0]);

    /* Request memory space */
    memset_s(recv_data, I2C_REG_ARRAY_LEN, 0x0, sizeof(recv_data));
    memset_s(&es8311_i2c_data, sizeof(hi_i2c_data), 0x0, sizeof(hi_i2c_data));

    es8311_i2c_data.send_buf = g_send_data;
    es8311_i2c_data.send_len = 1;
    es8311_i2c_data.receive_buf = recv_data;
    es8311_i2c_data.receive_len = recv_len;
    status = hi_i2c_writeread(id, device_addr, &es8311_i2c_data);
    if (status != HI_ERR_SUCCESS) {
        printf("===== Error: I2C read status = 0x%x! =====\r\n", status);
        return status;
    }

    for (i = 0; i < recv_len; i++) {
        printf("----- revData[%d] = 0x%x! -----\r\n", i, recv_data[i]);
    }

    return HI_ERR_SUCCESS;
}

hi_void i2c_demo(hi_i2c_idx id)
{
    hi_u32 ret;

    printf("----- I2C Start -----\r\n");

    i2c_demo_send_data_init();
    hi_i2c_init(id, 100000); /* baudrate: 100000 */

    ret = i2c_demo_write(id, ES8311_DEV_ADDR, I2C_SEND_LEN_2);
    printf("----- (ES8311)i2c_demo_write %d : %s! -----\r\n\n", __LINE__,
        ret == HI_ERR_SUCCESS ? "SUCCESS!" : "FAILURE!");

    ret = i2c_demo_writeread(id, ES8311_DEV_ADDR, I2C_RECV_LEN_1);
    printf("----- (ES8311)i2c_demo_writeread %d : %s! -----\r\n\n", __LINE__,
        ret == HI_ERR_SUCCESS ? "SUCCESS!" : "FAILURE!");

    hi_i2c_deinit(id);

    printf("I2C Test End!\r\n");
}

hi_void app_demo_custom_i2c(hi_void)
{
    /* Default use I2C 0 */
    i2c_demo(HI_I2C_IDX_0);
}

