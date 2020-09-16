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

#include <app_demo_spi.h>

hi_u8 g_spi_send_buf[BUF_LENGTH];
hi_u8 g_spi_rcv_buf[BUF_LENGTH];
hi_spi_idx g_spi_id = HI_SPI_ID_0;
hi_u32 g_transfer_lenth = 0;
hi_u32 g_test_loop = 0;
hi_u32 g_lb_loop = 0;
hi_u32 g_delay_us_spi = 0;
hi_spi_cfg_data_width g_data_width = HI_SPI_CFG_DATA_WIDTH_E_7BIT;

hi_void prepare_func(hi_void)
{
    test_spi_printf("prepare");
}

hi_void restore_func(hi_void)
{
    test_spi_printf("restore");
}

hi_void app_demo_spi_print_reg(hi_spi_idx spi_id)
{
    hi_u16 reg_val;
    hi_u32 reg_base;
    if (spi_id == HI_SPI_ID_0) {
        reg_base = HI_SSP0_REG_BASE;
    } else {
        reg_base = HI_SSP1_REG_BASE;
    }
    test_spi_printf("BASE_ADDR=%x", reg_base);
    reg_val = hi_reg_read_val16(reg_base + 0x00);
    test_spi_printf("REG_SPI_CR0=%x", reg_val);
    reg_val = hi_reg_read_val16(reg_base + 0x04);
    test_spi_printf("REG_SPI_CR1=%x", reg_val);
    reg_val = hi_reg_read_val16(reg_base + 0x0c);
    test_spi_printf("REG_SPI_SR=%x", reg_val);
    reg_val = hi_reg_read_val16(reg_base + 0x10);
    test_spi_printf("REG_SPI_CPSR=%x", reg_val);
    reg_val = hi_reg_read_val16(reg_base + 0x14);
    test_spi_printf("REG_SPI_IMSC=%x", reg_val);
    reg_val = hi_reg_read_val16(reg_base + 0x18);
    test_spi_printf("REG_SPI_RIS=%x", reg_val);
    reg_val = hi_reg_read_val16(reg_base + 0x1c);
    test_spi_printf("REG_SPI_MIS=%x", reg_val);
    reg_val = hi_reg_read_val16(reg_base + 0x24);
    test_spi_printf("REG_SPI_DMACR=%x", reg_val);
    reg_val = hi_reg_read_val16(reg_base + 0x28);
    test_spi_printf("REG_SPI_TXFIFOCR=%x", reg_val);
    reg_val = hi_reg_read_val16(reg_base + 0x2c);
    test_spi_printf("REG_SPI_RXFIFOCR=%x", reg_val);
}

hi_void app_demo_spi_print_test_para(const test_spi_para *spi_para)
{
    if (spi_para == HI_NULL) {
        test_spi_printf("spi para is null\n");
        return;
    }
    test_spi_printf("cpol:%d", spi_para->cfg_info.cpol);
    test_spi_printf("cpha:%d", spi_para->cfg_info.cpha);
    test_spi_printf("fram_mode:%d", spi_para->cfg_info.fram_mode);
    test_spi_printf("data_width:%d", spi_para->cfg_info.data_width);
    test_spi_printf("freq:%d", spi_para->cfg_info.freq);
    test_spi_printf("spi id:%d", spi_para->spi_id);
    test_spi_printf("loop:%d", spi_para->loop);
    test_spi_printf("length:%d", spi_para->length);
    test_spi_printf("irq:%d", spi_para->irq);
    test_spi_printf("slave:%d", spi_para->slave);
    test_spi_printf("lb:%d", spi_para->lb);
    test_spi_printf("dma en:%d", spi_para->dma_en);
    test_spi_printf("delay:%d", g_delay_us_spi);
}

hi_void print_err_send_buf_u8(const hi_u8 *buf, hi_u32 len)
{
    hi_u32 i;
    for (i = 0; i < len; i++) {
        test_spi_printf("%d", buf[i]);
    }
}

hi_void print_err_send_buf_u16(const hi_u16 *buf, hi_u32 len)
{
    hi_u32 i;
    for (i = 0; i < len; i++) {
        test_spi_printf("%d", buf[i]);
    }
}

hi_void print_err_rev_buf_u16(const hi_u16 *buf, const hi_u16 *cmp, hi_u32 len)
{
    hi_u32 i;
    for (i = 0; i < len; i++) {
        test_spi_printf("%d, %d", cmp[i], buf[i]);
    }
}
hi_void print_err_rev_buf_u8(const hi_u8 *buf, const hi_u8 *cmp, hi_u32 len)
{
    hi_u32 i;
    for (i = 0; i < len; i++) {
        test_spi_printf("%d, %d", cmp[i], buf[i]);
    }
}


hi_u32 app_demo_spi_init(hi_spi_idx id, const hi_spi_cfg_basic_info *spi_cfg_basic_info, hi_bool slave)
{
    hi_u32 ret;
    hi_spi_cfg_init_param init_param;
    init_param.is_slave = slave;
    ret = hi_spi_init(id, init_param, spi_cfg_basic_info);

    test_spi_printf("app_demo_spi_init ret=%x", ret);
    return ret;
}

hi_void app_demo_spi_config_gpio(hi_spi_idx id)
{
    if (id == HI_SPI_ID_0) {
        hi_io_set_func(HI_IO_NAME_GPIO_5, HI_IO_FUNC_GPIO_5_SPI0_CSN);
        hi_io_set_func(HI_IO_NAME_GPIO_6, HI_IO_FUNC_GPIO_6_SPI0_CK);
        hi_io_set_func(HI_IO_NAME_GPIO_7, HI_IO_FUNC_GPIO_7_SPI0_RXD);
        hi_io_set_func(HI_IO_NAME_GPIO_8, HI_IO_FUNC_GPIO_8_SPI0_TXD);
        hi_io_set_driver_strength(HI_IO_NAME_GPIO_6, HI_IO_DRIVER_STRENGTH_2);
    } else {
        hi_io_set_func(HI_IO_NAME_GPIO_0, HI_IO_FUNC_GPIO_0_SPI1_CK);
        hi_io_set_func(HI_IO_NAME_GPIO_1, HI_IO_FUNC_GPIO_1_SPI1_RXD);
        hi_io_set_func(HI_IO_NAME_GPIO_2, HI_IO_FUNC_GPIO_2_SPI1_TXD);
        hi_io_set_func(HI_IO_NAME_GPIO_3, HI_IO_FUNC_GPIO_3_SPI1_CSN);
        hi_io_set_driver_strength(HI_IO_NAME_GPIO_0, HI_IO_DRIVER_STRENGTH_2);
    }
}

hi_u32 app_demo_spi_slave_send_8bits(hi_spi_idx spi_id)
{
    hi_u32 i;
    hi_u32 j;
    hi_u32 while_times = 0;
    hi_u32 ret;
    hi_u32 err_times = 0;
    if (g_transfer_lenth > BUF_LENGTH) {
        return HI_ERR_FAILURE;
    }
    i = 0;
    for (j = 0; j < g_transfer_lenth; j++) {
        g_spi_send_buf[j] = (hi_u8)i;
        i++;
    }
    do {
        ret = hi_spi_slave_write(spi_id, g_spi_send_buf, g_transfer_lenth, 10000);  /* time out 10000 ms */
        if (ret != HI_ERR_SUCCESS) {
            err_times += 1;
            break;
        }
        hi_watchdog_feed();
        while_times++;
    } while (while_times < g_test_loop || g_test_loop == 0);
    test_spi_printf("demo_spi_slave_send err_send: %d,while_times:%d, ret:%x", err_times, while_times, ret);
    return ret;
}

hi_u32 app_demo_spi_slave_send_16bits(hi_spi_idx spi_id)
{
    hi_u32 i;
    hi_u32 j;
    hi_u32 while_times = 0;
    hi_u32 ret = HI_ERR_SUCCESS;
    hi_u32 index;
    hi_u32 err_times = 0;
    hi_u32 send_len;
    do {
        i = 0;
        index = 0;
        while (index < g_transfer_lenth) {
            send_len = min(g_transfer_lenth - index, BUF_LENGTH_HALF);
            for (j = 0; j < send_len; j++) { /* loops 256 */
                *((hi_u16 *)g_spi_send_buf + j) = (hi_u16)i;
                i++;
            }
            ret = hi_spi_slave_write(spi_id, g_spi_send_buf, send_len * 2, 10000);  /* 2:doubule the length 10000:ms */
            if (ret != HI_ERR_SUCCESS) {
                err_times++;
                print_err_send_buf_u16((hi_u16 *)g_spi_send_buf, send_len);
                break;
            }
            hi_watchdog_feed();
            index += send_len; /* add 256 */
        }
        while_times++;
    } while (while_times < g_test_loop || g_test_loop == 0);
    test_spi_printf("demo_spi_slave_send err_send: %d,while_times:%d, ret:%x", err_times, while_times, ret);
    return ret;
}

hi_void *app_demo_spi_slave_send_task(hi_void *param)
{
    hi_spi_idx spi_id = *(hi_spi_idx*)param;
    hi_u32 ret;
    hi_u32 time_old;
    hi_u32 time_new;
    time_old = hi_get_milli_seconds();
    if (g_data_width < HI_SPI_CFG_DATA_WIDTH_E_9BIT) {
        ret = app_demo_spi_slave_send_8bits(spi_id);
    } else {
        ret = app_demo_spi_slave_send_16bits(spi_id);
    }
    if (ret != HI_ERR_SUCCESS) {
        printf("app_demo_spi_slave_send fail: %x\n", ret);
    }

    time_new = hi_get_milli_seconds();
    app_demo_spi_print_reg(spi_id);
    test_spi_printf("demo_spi_slave_send time_old: %d,time_new %d, delt:%d", time_old, time_new, time_new - time_old);
    ret = hi_spi_deinit(spi_id);
    if (ret != HI_ERR_SUCCESS) {
        printf("hi_spi_deinit fail: %x\n", ret);
    }
    return HI_NULL;
}

hi_u32 app_demo_spi_slave_receive_8bits(hi_spi_idx spi_id)
{
    hi_u8 cmp_buf[BUF_LENGTH];
    hi_u32 while_times = 0;
    hi_u32 i;
    hi_u32 j;
    hi_u32 ret;
    hi_u32 err_times = 0;
    i = 0;
    if (g_transfer_lenth > BUF_LENGTH) {
        return HI_ERR_FAILURE;
    }
    for (j = 0; j < g_transfer_lenth; j++) {
        cmp_buf[j] = (hi_u8)i;
        i++;
    }
    do {
        while_times++;
        memset_s(g_spi_rcv_buf, sizeof(g_spi_rcv_buf), 0x0, sizeof(g_spi_rcv_buf));
        ret = hi_spi_slave_read(spi_id, g_spi_rcv_buf, g_transfer_lenth, 10000); /* time out 10000 ms */
        if ((memcmp(g_spi_rcv_buf, cmp_buf, g_transfer_lenth) != 0) || (ret != HI_ERR_SUCCESS)) {
            err_times++;
            print_err_rev_buf_u8(g_spi_rcv_buf, cmp_buf, g_transfer_lenth);
            break;
        }
    } while (while_times < g_test_loop || g_test_loop == 0);
    test_spi_printf("demo_spi_rev err_rev: %d,while_times:%d, ret:%x", err_times, while_times, ret);
    return ret;
}

hi_u32 app_demo_spi_slave_receive_16bits(hi_spi_idx spi_id)
{
    hi_u8 cmp_buf[BUF_LENGTH];
    hi_u32 while_times = 0;
    hi_u32 i;
    hi_u32 j;
    hi_u32 k;
    hi_u32 ret = HI_ERR_SUCCESS;
    hi_u32 err_times = 0;
    hi_u32 rcv_len;
    do {
        k = 0;
        while_times++;
        i = 0;
        while (k < g_transfer_lenth) {
            rcv_len = min(g_transfer_lenth - k, BUF_LENGTH_HALF);
            for (j = 0; j < rcv_len; j++) {
                *((hi_u16 *)cmp_buf + j) = (hi_u16)i;
                i++;
            }
            memset_s(g_spi_rcv_buf, sizeof(g_spi_rcv_buf), 0x0, sizeof(g_spi_rcv_buf));
            ret = hi_spi_slave_read(spi_id, g_spi_rcv_buf, rcv_len * 2, 10000);  /* 2:doubule the length 10000:ms */
            if ((memcmp(g_spi_rcv_buf, cmp_buf, rcv_len) != 0) || (ret != HI_ERR_SUCCESS)) {
                err_times++;
                print_err_rev_buf_u16((hi_u16 *)g_spi_rcv_buf, (hi_u16 *)cmp_buf, rcv_len);
                break;
            }
            hi_watchdog_feed();
            k += rcv_len;
        }
    } while (while_times < g_test_loop || g_test_loop == 0);
    test_spi_printf("demo_spi_slave_rev err_rev: %d,while_times:%d, ret:%x", err_times, while_times, ret);
    return ret;
}

hi_void *app_demo_spi_slave_receive_task(hi_void *param)
{
    hi_spi_idx spi_id = *(hi_spi_idx*)param;
    hi_u32 ret;
    hi_u32 time_old;
    hi_u32 time_new;
    time_old = hi_get_milli_seconds();
    if (g_data_width < HI_SPI_CFG_DATA_WIDTH_E_9BIT) {
        ret = app_demo_spi_slave_receive_8bits(spi_id);
    } else {
        ret = app_demo_spi_slave_receive_16bits(spi_id);
    }
    if (ret != HI_ERR_SUCCESS) {
        printf("app_demo_spi_slave_receive fail: %x\n", ret);
    }

    time_new = hi_get_milli_seconds();
    test_spi_printf("time_old: %d,time_new %d, delt:%d", time_old, time_new, time_new - time_old);
    app_demo_spi_print_reg(spi_id);
    ret = hi_spi_deinit(spi_id);
    if (ret != HI_ERR_SUCCESS) {
        printf("hi_spi_deinit fail: %x\n", ret);
    }
    return HI_NULL;
}

hi_void *app_demo_spi_host_write_read_task(hi_void *param)
{
    hi_spi_idx spi_id = *(hi_spi_idx*)param;
    hi_u32 ret;
    hi_u32 i;
    hi_u8 send_buf[g_transfer_lenth];
    hi_u8 recv_buf[g_transfer_lenth + 1];
    hi_u32 while_times = 0;
    hi_u32 err_times = 0;
    hi_u32 time_old;
    hi_u32 time_new;
    for (i = 0; i < g_transfer_lenth; i++) {
        send_buf[i] = (hi_u8)i;
    }
    time_old = hi_get_milli_seconds();
    do {
        memset_s(recv_buf, sizeof(recv_buf), 0x0, sizeof(recv_buf));
        ret = hi_spi_host_writeread(spi_id, send_buf, recv_buf, g_transfer_lenth);
        if (memcmp(recv_buf, send_buf, g_transfer_lenth) != 0 || ret != HI_ERR_SUCCESS) {
            err_times++;
        }
        while_times++;
    } while (while_times < g_test_loop || g_test_loop == 0);
    time_new = hi_get_milli_seconds();
    test_spi_printf("while_times:%d ,err_times:%d", while_times, err_times);
    test_spi_printf("time_old: %d,time_new %d, delt:%d", time_old, time_new, time_new - time_old);
    app_demo_spi_print_reg(spi_id);
    return HI_NULL;
}

hi_u32 app_demo_spi_host_send_8bits(hi_spi_idx spi_id)
{
    hi_u32 i;
    hi_u32 j;
    hi_u32 while_times = 0;
    hi_u32 err_times = 0;
    hi_u32 ret;
    if (g_transfer_lenth > BUF_LENGTH) {
        return HI_ERR_FAILURE;
    }
    i = 0;
    for (j = 0; j < g_transfer_lenth; j++) {
        g_spi_send_buf[j] = (hi_u8)i;
        i++;
    }
    do {
        ret = hi_spi_host_write(spi_id, g_spi_send_buf, g_transfer_lenth);
        hi_udelay(g_delay_us_spi);
        if (ret != HI_ERR_SUCCESS) {
            err_times++;
            break;
        }
        while_times++;
    } while (while_times < g_test_loop || g_test_loop == 0);
    test_spi_printf("demo_spi_host_send err_send: %d,while_times:%d, ret:%x", err_times, while_times, ret);
    return ret;
}

hi_u32 app_demo_spi_host_send_16bits(hi_spi_idx spi_id)
{
    hi_u32 i;
    hi_u32 j;
    hi_u32 while_times = 0;
    hi_u32 ret = HI_ERR_SUCCESS;
    hi_u32 index;
    hi_u32 err_times = 0;
    hi_u32 send_len;
    do {
        i = 0;
        index = 0;
        while (index < g_transfer_lenth) {
            send_len = min(g_transfer_lenth - index, BUF_LENGTH_HALF);
            for (j = 0; j < send_len; j++) {
                *((hi_u16 *)g_spi_send_buf + j) = (hi_u16)i;
                i++;
            }
            ret = hi_spi_host_write(spi_id, g_spi_send_buf, send_len * 2);  /* 2:doubule the length */
            hi_udelay(g_delay_us_spi);
            if (ret != HI_ERR_SUCCESS) {
                err_times++;
                print_err_send_buf_u16((hi_u16 *)g_spi_send_buf, send_len);
            }
            hi_watchdog_feed();
            index += send_len;
        }
        while_times++;
    } while (while_times < g_test_loop || g_test_loop == 0);
    test_spi_printf("demo_spi_slave_send err_send: %d,while_times:%d, ret:%x", err_times, while_times, ret);
    return ret;
}
/*
 * spi host device write data task
 */
hi_void *app_demo_spi_host_write_task(hi_void *param)
{
    hi_spi_idx spi_id = *(hi_spi_idx*)param;
    hi_u32 ret;
    hi_u32 time_old;
    hi_u32 time_new;
    time_old = hi_get_milli_seconds();
    if (g_data_width < HI_SPI_CFG_DATA_WIDTH_E_9BIT) {
        ret = app_demo_spi_host_send_8bits(spi_id);
    } else {
        ret = app_demo_spi_host_send_16bits(spi_id);
    }
    if (ret != HI_ERR_SUCCESS) {
        printf("app_demo_spi_host_send fail: %x\n", ret);
    }
    time_new = hi_get_milli_seconds();
    test_spi_printf("time_old: %d,time_new %d, delt:%d", time_old, time_new, time_new - time_old);
    app_demo_spi_print_reg(spi_id);
    ret = hi_spi_deinit(spi_id);
    if (ret != HI_ERR_SUCCESS) {
        printf("hi_spi_deinit fail: %x\n", ret);
        return HI_NULL;
    }
    return HI_NULL;
}

hi_u32 app_demo_spi_host_receive_8bits(hi_spi_idx spi_id)
{
    hi_u8 cmp_buf[BUF_LENGTH];
    hi_u32 while_times = 0;
    hi_u32 i;
    hi_u32 j;
    hi_u32 err_times = 0;
    hi_u32 ret;
    i = 0;
    if (g_transfer_lenth > BUF_LENGTH) {
        return HI_ERR_FAILURE;
    }
    for (j = 0; j < g_transfer_lenth; j++) {
        cmp_buf[j] = (hi_u8)i;
        i++;
    }
    do {
        while_times++;
        if (memset_s(g_spi_rcv_buf, sizeof(g_spi_rcv_buf), 0x0, sizeof(g_spi_rcv_buf)) != EOK) {
            ret = HI_ERR_MEMSET_S;
            break;
        }
        ret = hi_spi_host_read(spi_id, g_spi_rcv_buf, g_transfer_lenth);
        hi_udelay(g_delay_us_spi);
        if (memcmp(g_spi_rcv_buf, cmp_buf, g_transfer_lenth) != 0) {
            err_times++;
            print_err_rev_buf_u8(g_spi_rcv_buf, cmp_buf, g_transfer_lenth);
            break;
        }
    } while (while_times < g_test_loop || g_test_loop == 0);
    test_spi_printf("demo_spi_host_rev err_rev: %d,while_times:%d, ret:%x", err_times, while_times, ret);
    return ret;
}

hi_u32 app_demo_spi_host_receive_16bits(hi_spi_idx spi_id)
{
    hi_u8 cmp_buf[BUF_LENGTH];
    hi_u32 while_times = 0;
    hi_u32 err_times = 0;
    hi_u32 i;
    hi_u32 j;
    hi_u32 k;
    hi_u32 ret = HI_ERR_SUCCESS;
    hi_u32 recv_len;
    do {
        k = 0;
        while_times++;
        i = 0;
        while (k < g_transfer_lenth) {
            recv_len = min(g_transfer_lenth - k, BUF_LENGTH_HALF);
            for (j = 0; j < recv_len; j++) {
                *((hi_u16 *)cmp_buf + j) = (hi_u16)i;
                i++;
            }
            memset_s(g_spi_rcv_buf, sizeof(g_spi_rcv_buf), 0x0, sizeof(g_spi_rcv_buf));
            ret = hi_spi_host_read(spi_id, g_spi_rcv_buf, recv_len * 2); /* 2:doubule the length */
            hi_udelay(g_delay_us_spi);
            if (memcmp(g_spi_rcv_buf, cmp_buf, recv_len * 2) != 0) {  /* 2:doubule the length */
                err_times++;
                print_err_rev_buf_u16((hi_u16 *)g_spi_rcv_buf, (hi_u16 *)cmp_buf, recv_len);
                break;
            }
            hi_watchdog_feed();
            k += recv_len;
        }
    } while (while_times < g_test_loop || g_test_loop == 0);
    test_spi_printf("demo_spi_host_rev err_rev: %d,while_times:%d, ret:%x", err_times, while_times, ret);
    return ret;
}

/*
 * spi host device read data task
 */
hi_void *app_demo_spi_host_read_task(hi_void *param)
{
    hi_spi_idx spi_id = *(hi_spi_idx*)param;
    printf("spi_id:%d\n", spi_id);
    hi_u32 ret;
    hi_u32 time_old;
    hi_u32 time_new;
    time_old = hi_get_milli_seconds();
    if (g_data_width < HI_SPI_CFG_DATA_WIDTH_E_9BIT) {
        ret = app_demo_spi_host_receive_8bits(spi_id);
    } else {
        ret = app_demo_spi_host_receive_16bits(spi_id);
    }
    if (ret != HI_ERR_SUCCESS) {
        printf("app_demo_spi_host_receive fail: %x\n", ret);
    }
    time_new = hi_get_milli_seconds();
    test_spi_printf("time_old: %d,time_new %d, delt:%d", time_old, time_new, time_new - time_old);
    app_demo_spi_print_reg(spi_id);
    ret = hi_spi_deinit(spi_id);
    if (ret != HI_ERR_SUCCESS) {
        printf("hi_spi_deinit fail: %x\n", ret);
    }
    return HI_NULL;
}

/*
 * host device write data and slave device read data
 */
hi_void app_demo_spi_test_cmd_mw_sr(const test_spi_para *spi_para)
{
    hi_u32 ret;
    hi_u32 taskid1;
    hi_task_attr attr;

    test_spi_printf("app_demo_spi_test_cmd_mw_sr Start");
    ret = app_demo_spi_init(spi_para->spi_id, &(spi_para->cfg_info), spi_para->slave);

    g_transfer_lenth = spi_para->length;
    g_spi_id = spi_para->spi_id;
    if (ret == HI_ERR_SUCCESS) {
        test_spi_printf("SPI init succ!");
    } else {
        test_spi_printf("SPI init fail! %x ", ret);
        return;
    }
    hi_spi_set_loop_back_mode(spi_para->spi_id, spi_para->lb);
    app_demo_spi_config_gpio(spi_para->spi_id);
    g_test_loop = spi_para->loop;
    g_data_width = (hi_spi_cfg_data_width)spi_para->cfg_info.data_width;
    hi_sleep(1000); /* 1000 */
    hi_spi_set_irq_mode(spi_para->spi_id, spi_para->irq);
    hi_spi_set_dma_mode(spi_para->spi_id, spi_para->dma_en);
    if (spi_para->slave == 0) {
        attr.task_prio = 5; /* priority 5 */
        attr.stack_size = 0x2000;
        attr.task_name = (hi_char *)"spi_host";
        ret = hi_task_create(&taskid1, &attr, app_demo_spi_host_write_task, (hi_void *)&spi_para->spi_id);
    } else {
        attr.task_prio = 5; /* priority 5 */
        attr.stack_size = 0x2000;
        attr.task_name = (hi_char *)"r_spi_slave";
        ret = hi_task_create(&taskid1, &attr, app_demo_spi_slave_receive_task, (hi_void *)&spi_para->spi_id);
    }
    test_spi_printf("SPI Test End!");
}

/*
 * host device read data and slave device write data
 */
hi_void app_demo_spi_test_cmd_mr_sw(const test_spi_para *spi_para)
{
    hi_u32 ret;
    hi_u32 taskid1;
    hi_task_attr attr;

    test_spi_printf("app_demo_spi_test_cmd_mr_sw Start");
    ret = app_demo_spi_init(spi_para->spi_id, &(spi_para->cfg_info), spi_para->slave);
    app_demo_spi_config_gpio(spi_para->spi_id);
    g_transfer_lenth = spi_para->length;
    g_spi_id = spi_para->spi_id;
    g_data_width = (hi_spi_cfg_data_width)spi_para->cfg_info.data_width;
    if (ret == HI_ERR_SUCCESS) {
        test_spi_printf("SPI init succ!");
    } else {
        test_spi_printf("SPI init fail! %x ", ret);
        return;
    }
    hi_spi_set_loop_back_mode(spi_para->spi_id, spi_para->lb);
    g_test_loop = spi_para->loop;
    hi_sleep(1000); /* 1000 */
    hi_spi_set_irq_mode(spi_para->spi_id, spi_para->irq);
    ret = hi_spi_set_dma_mode(spi_para->spi_id, spi_para->dma_en);
    printf("hi_spi_set_dma_mode :%x\n", ret);
    if (spi_para->slave == 0) {
        attr.task_prio = 25; /* priority 25 */
        attr.stack_size = 0x2000;
        attr.task_name = (hi_char *)"spi_host";
        ret = hi_task_create(&taskid1, &attr, app_demo_spi_host_read_task, (hi_void *)&spi_para->spi_id);
    } else {
        attr.task_prio = 25; /* priority 25 */
        attr.stack_size = 0x2000;
        attr.task_name = (hi_char *)"w_spi_slave";
        ret = hi_task_create(&taskid1, &attr, app_demo_spi_slave_send_task, (hi_void *)&spi_para->spi_id);
    }
    test_spi_printf("SPI Test End!");
}

hi_u32 app_demo_spi_single_loopback(hi_spi_idx spi_id, hi_u8 data_width)
{
    hi_u32 ret;
    hi_u32 i;
    hi_u8 send_buf[512] = { 0 }; /* 512 */
    hi_u8 recv_buf[512] = { 0 }; /* 512 */
    hi_u32 test_length = 243; /* 243: test length */
    hi_u32 while_times = 0;
    do {
        if (data_width < HI_SPI_CFG_DATA_WIDTH_E_8BIT) {
            test_length = (0x1 << data_width) - 1;
        }
        while_times++;
        printf("while_times:%d \n", while_times);
        memset_s(recv_buf, sizeof(recv_buf), 0x0, sizeof(recv_buf));
        if (data_width >= HI_SPI_CFG_DATA_WIDTH_E_9BIT) {
            for (i = 0; i < 256; i++) { /* loop 256 times */
                *((hi_u16 *)send_buf + i) = (hi_u16)i;
            }
            ret = hi_spi_host_writeread(spi_id, (hi_pvoid)send_buf, (hi_pvoid)recv_buf, test_length * 2); /* 2 */
            if (ret != HI_ERR_SUCCESS) {
                return ret;
            }
            if (memcmp(recv_buf, send_buf, test_length * 2) != 0) { /* 2 double buf length */
                print_err_rev_buf_u16((hi_u16 *)send_buf, (hi_u16 *)recv_buf, test_length);
                return HI_ERR_FAILURE;
            }
            continue;
        }
        for (i = 0; i < 512; i++) { /* 512 */
            send_buf[i] = (hi_u8)i;
        }
        ret = hi_spi_host_writeread(spi_id, (hi_pvoid)send_buf, (hi_pvoid)recv_buf, test_length);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
        if (memcmp(recv_buf, send_buf, test_length) != 0) {
            for (i = 0; i < test_length; i++) {
                test_spi_printf("b[%d]i[%d]s[%d]r[%d]", data_width + 1, i, send_buf[i], recv_buf[i]);
            }
            return HI_ERR_FAILURE;
        }
    } while (while_times <= g_lb_loop);
    return ret;
}

hi_u32 app_demo_spi_para_test(hi_spi_cfg_basic_info *spi_para)
{
    hi_u32 ret;
    spi_para->data_width = 2; /* data width 2 */
    ret = hi_spi_set_basic_info(g_spi_id, spi_para);
    if (ret != HI_ERR_SPI_PARAMETER_WRONG) {
        return HI_ERR_FAILURE;
    }
    spi_para->data_width = HI_SPI_CFG_DATA_WIDTH_E_8BIT;
    spi_para->fram_mode = 3; /* data protocol 3 */
    ret = hi_spi_set_basic_info(g_spi_id, spi_para);
    if (ret != HI_ERR_SPI_PARAMETER_WRONG) {
        return HI_ERR_FAILURE;
    }
    spi_para->fram_mode = HI_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para->freq = 80000000; /* Clock rate 13 80000000 */
    ret = hi_spi_set_basic_info(g_spi_id, spi_para);
    if (ret != HI_ERR_SPI_PARAMETER_WRONG) {
        return HI_ERR_FAILURE;
    }
    spi_para->freq = 1000; /* Clock rate 256 1000 */
    ret = hi_spi_set_basic_info(g_spi_id, spi_para);
    if (ret != HI_ERR_SPI_PARAMETER_WRONG) {
        return HI_ERR_FAILURE;
    }
    spi_para->freq = 2000000; /* Clock rate 24 2000000 */
    return HI_ERR_SUCCESS;
}

hi_void app_demo_spi_test_case_part1(hi_spi_cfg_basic_info *spi_para, hi_u8 test_case)
{
    switch (test_case) {
        case TEST_CASE_POL0_PHA0:
            spi_para->cpol = HI_SPI_CFG_CLOCK_CPOL_0;
            spi_para->cpha = HI_SPI_CFG_CLOCK_CPHA_0;
            break;
        case TEST_CASE_POL0_PHA1:
            spi_para->cpol = HI_SPI_CFG_CLOCK_CPOL_0;
            spi_para->cpha = HI_SPI_CFG_CLOCK_CPHA_1;
            break;
        case TEST_CASE_POL1_PHA0:
            spi_para->cpol = HI_SPI_CFG_CLOCK_CPOL_1;
            spi_para->cpha = HI_SPI_CFG_CLOCK_CPHA_0;
            break;
        case TEST_CASE_POL1_PHA1:
            spi_para->cpol = HI_SPI_CFG_CLOCK_CPOL_1;
            spi_para->cpha = HI_SPI_CFG_CLOCK_CPHA_1;
            break;
        case TEST_CASE_MOTOROLA:
            spi_para->fram_mode = HI_SPI_CFG_FRAM_MODE_MOTOROLA;
            break;
        case TEST_CASE_TI:
            spi_para->fram_mode = HI_SPI_CFG_FRAM_MODE_TI;
            break;
        /* Microware does not support self-loopback tests. Two devices must be connected for tests. */
        case TEST_CASE_BIT4:
            spi_para->data_width = HI_SPI_CFG_DATA_WIDTH_E_4BIT;
            break;
        case TEST_CASE_BIT7:
            spi_para->data_width = HI_SPI_CFG_DATA_WIDTH_E_7BIT;
            break;
        case TEST_CASE_BIT8:
            spi_para->data_width = HI_SPI_CFG_DATA_WIDTH_E_8BIT;
            break;
        case TEST_CASE_BIT9:
            spi_para->data_width = HI_SPI_CFG_DATA_WIDTH_E_9BIT;
            break;
        case TEST_CASE_BIT15:
            spi_para->data_width = HI_SPI_CFG_DATA_WIDTH_E_15BIT;
            break;
        case TEST_CASE_BIT16:
            spi_para->data_width = HI_SPI_CFG_DATA_WIDTH_E_16BIT;
            break;
        default:
            break;
    }
}

hi_u32 app_demo_spi_test_case_part2(hi_spi_cfg_basic_info *spi_para, hi_u8 test_case, hi_u8 *flag)
{
    switch (test_case) {
        case TEST_CASE_CLK_MIN:
            spi_para->freq = 20000000; /* Clock rate 4 20000000 */
            break;
        case TEST_CASE_CLK_16:
            spi_para->freq = 5000000; /* Clock rate 16 5000000 */
            break;
        case TEST_CASE_CLK_50:
            spi_para->freq = 1600000; /* Clock rate 50 1600000 */
            break;
        case TEST_CASE_CLK_100:
            spi_para->freq = 800000; /* Clock rate 100 800000 */
            break;
        case TEST_CASE_CLK_200:
            spi_para->freq = 400000; /* Clock rate 200 400000 */
            break;
        case TEST_CASE_PARAMETER_WRONG:
            *flag = 1;
            return app_demo_spi_para_test(spi_para);
        default:
            break;
    }
    return HI_ERR_SUCCESS;
}

hi_u32 app_demo_spi_test_case(hi_u8 test_case)
{
    hi_u32 ret;
    hi_u8 flag = 0;
    hi_spi_cfg_basic_info spi_para = {
        .data_width = HI_SPI_CFG_DATA_WIDTH_E_8BIT,
        .fram_mode = HI_SPI_CFG_FRAM_MODE_MOTOROLA,
        .cpol = HI_SPI_CFG_CLOCK_CPOL_0,
        .cpha = HI_SPI_CFG_CLOCK_CPHA_0,
        .endian = HI_SPI_CFG_ENDIAN_LITTLE,
        .pad = 0,
        .freq = 2000000, /* Clock rate 24 2000000 */
    };
    app_demo_spi_test_case_part1(&spi_para, test_case);
    ret = app_demo_spi_test_case_part2(&spi_para, test_case, &flag);
    if (flag) {
        return ret;
    }
    ret = hi_spi_set_basic_info(g_spi_id, &spi_para);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    return app_demo_spi_single_loopback(g_spi_id, spi_para.data_width);
}

/*
 * Test SPI unit parameters and loop back mode
 */
hi_void app_demo_spi_test(hi_spi_idx spi_id, hi_u32 irq_en, hi_u32 test_case, hi_u32 loop)
{
    test_spi_printf("SPI%d TEST START", spi_id);
    hi_spi_cfg_basic_info spi_cfg_basic_info;
    spi_cfg_basic_info.cpha = 1;
    spi_cfg_basic_info.cpol = 1;
    spi_cfg_basic_info.data_width = HI_SPI_CFG_DATA_WIDTH_E_7BIT;
    spi_cfg_basic_info.endian = 0;
    spi_cfg_basic_info.fram_mode = 0;
    spi_cfg_basic_info.freq = 2000000; /* set frequency 2000000 */
    app_demo_spi_init(spi_id, &spi_cfg_basic_info, HI_FALSE);
    hi_spi_set_loop_back_mode(spi_id, HI_TRUE);
    hi_spi_set_irq_mode(spi_id, (hi_bool)irq_en);
    g_spi_id = spi_id;
    g_lb_loop = loop;
    if (test_case == TEST_CASE_ALL) {
        /* The last three test case need connect Peripherals */
        for (int i = TEST_CASE_POL0_PHA0; i < TEST_CASE_SLAVE; i++) {
            hi_u32 ret = app_demo_spi_test_case((hi_u8)i);
            test_spi_printf("===spi[%d]====TEST_CASE %d %s!=====", spi_id, i,
                            ret == HI_ERR_SUCCESS ? "SUCCESS!" : "FAILURE!");
        }
    } else {
        if (test_case >= TEST_CASE_MAX) {
            test_spi_printf("INVALID TEST CASE!");
            return;
        }
        hi_u32 ret = app_demo_spi_test_case((hi_u8)test_case);
        test_spi_printf("===spi[%d]====TEST_CASE %d %s!=====", spi_id, test_case,
                        ret == HI_ERR_SUCCESS ? "SUCCESS!" : "FAILURE!");
    }
    app_demo_spi_print_reg(g_spi_id);
    test_spi_printf("SPI%d TEST END", spi_id);
}

/*
 * The host device sets the SPI unit and read data
 */
hi_void app_demo_spi_cmd_host_read(hi_spi_idx spi_id, hi_u32 length, hi_u32 loop)
{
    test_spi_para spi_para;
    spi_para.spi_id = spi_id;
    spi_para.irq = HI_FALSE;
    spi_para.length = length;
    spi_para.loop = loop;
    spi_para.cfg_info.data_width = HI_SPI_CFG_DATA_WIDTH_E_8BIT;
    spi_para.cfg_info.cpha = HI_SPI_CFG_CLOCK_CPHA_0;
    spi_para.cfg_info.cpol = HI_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cfg_info.fram_mode = HI_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.cfg_info.endian = HI_SPI_CFG_ENDIAN_LITTLE;
    spi_para.slave = HI_FALSE;
    spi_para.lb = HI_FALSE;
    spi_para.dma_en = HI_FALSE;
    g_delay_us_spi = 200; /* 200us */
    spi_para.cfg_info.freq = 8000000; /* defaul freq 8000000 Hz */
    app_demo_spi_print_test_para(&spi_para);
    app_demo_spi_test_cmd_mr_sw(&spi_para);
}

/*
 * The slave device sets the SPI unit and write data
 */
hi_void app_demo_spi_cmd_slave_write(hi_spi_idx spi_id, hi_u32 length, hi_u32 loop)
{
    test_spi_para spi_para;
    spi_para.spi_id = spi_id;
    spi_para.irq = HI_FALSE;
    spi_para.length = length;
    spi_para.loop = loop;
    spi_para.cfg_info.data_width = HI_SPI_CFG_DATA_WIDTH_E_8BIT;
    spi_para.cfg_info.cpha = HI_SPI_CFG_CLOCK_CPHA_0;
    spi_para.cfg_info.cpol = HI_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cfg_info.fram_mode = HI_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.cfg_info.endian = HI_SPI_CFG_ENDIAN_LITTLE;
    spi_para.slave = HI_TRUE;
    spi_para.lb = HI_FALSE;
    spi_para.dma_en = HI_TRUE;
    g_delay_us_spi = 0;
    spi_para.cfg_info.freq = 8000000; /* defaul freq 8000000 Hz */
    app_demo_spi_print_test_para(&spi_para);
    app_demo_spi_test_cmd_mr_sw(&spi_para);
}

/*
 * The host device sets the SPI unit and write data
 */
hi_void app_demo_spi_cmd_host_write(hi_spi_idx spi_id, hi_u32 length, hi_u32 loop)
{
    test_spi_para spi_para;
    spi_para.spi_id = spi_id;
    spi_para.irq = HI_FALSE;
    spi_para.length = length;
    spi_para.loop = loop;
    spi_para.cfg_info.data_width = HI_SPI_CFG_DATA_WIDTH_E_8BIT;
    spi_para.cfg_info.cpha = HI_SPI_CFG_CLOCK_CPHA_0;
    spi_para.cfg_info.cpol = HI_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cfg_info.fram_mode = HI_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.cfg_info.endian = HI_SPI_CFG_ENDIAN_LITTLE;
    spi_para.slave = HI_FALSE;
    spi_para.lb = HI_FALSE;
    spi_para.dma_en = HI_FALSE;
    g_delay_us_spi = 100;  /* 100 us */
    spi_para.cfg_info.freq = 8000000; /* defaul freq 8000000 Hz */
    app_demo_spi_print_test_para(&spi_para);
    app_demo_spi_test_cmd_mw_sr(&spi_para);
}

/*
 * The slave device sets the SPI unit and read data
 */
hi_void app_demo_spi_cmd_slave_read(hi_spi_idx spi_id, hi_u32 length, hi_u32 loop)
{
    test_spi_para spi_para;
    spi_para.spi_id = spi_id;
    spi_para.irq = HI_FALSE;
    spi_para.length = length;
    spi_para.loop = loop;
    spi_para.cfg_info.data_width = HI_SPI_CFG_DATA_WIDTH_E_8BIT;
    spi_para.cfg_info.cpha = HI_SPI_CFG_CLOCK_CPHA_0;
    spi_para.cfg_info.cpol = HI_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cfg_info.fram_mode = HI_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.cfg_info.endian = HI_SPI_CFG_ENDIAN_LITTLE;
    spi_para.slave = HI_TRUE;
    spi_para.lb = HI_FALSE;
    spi_para.dma_en = HI_TRUE;
    g_delay_us_spi = 0;
    spi_para.cfg_info.freq = 8000000; /* defaul freq 8000000 Hz */
    app_demo_spi_print_test_para(&spi_para);
    app_demo_spi_test_cmd_mw_sr(&spi_para);
}

