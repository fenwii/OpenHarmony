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

#include "i2c.h"
#include <hi_sem.h>
#include <hi_i2c.h>
#include <hi_time.h>
#include <hi3861_platform_base.h>

#define I2C0_BASE HI_I2C0_REG_BASE
#define I2C1_BASE HI_I2C1_REG_BASE
#define CLKEN_I2C0 14
#define CLKEN_I2C1 15

hi_u32 g_i2c_drv_sem[2] = {0xffffffff, 0xffffffff}; // for 2 i2c

hi_u32 g_i2c_rcv_time_out_us = 4096;

typedef struct {
    hi_u32 baudrate;
    i2c_reset_func reset_bus_func;
    i2c_prepare_func prepare_func;
    i2c_restore_func restore_func;
    hi_u16 timeout_us;
    hi_u8 scl_h : 3;
    hi_u8 scl_l : 3;
    hi_bool init : 1;
    hi_bool pad : 1;
    hi_u8 err_times;
} hi_i2c_ctrl;

/* timeout_us unused */
hi_i2c_ctrl g_i2c_ctrl[I2C_NUM] = {
    { 0, HI_NULL, HI_NULL, HI_NULL, 3000, 1, 1, HI_FALSE, 0, 0 },
    { 0, HI_NULL, HI_NULL, HI_NULL, 3000, 1, 1, HI_FALSE, 0, 0 }
};

hi_void i2c_read(hi_i2c_idx id);
hi_void i2c_write(hi_i2c_idx id);

hi_u32 i2c_reset(hi_i2c_idx id)
{
    hi_u32 value;
    hi_u32 ret;

    hi_reg_read32(CRG_REG_SC_PERI_SRST_REG, value);
    value |= (1 << CRG_REG_I2C_SRST_REQ_OFFSET);
    hi_reg_write32(CRG_REG_SC_PERI_SRST_REG, value);
    value &= ~(1 << CRG_REG_I2C_SRST_REQ_OFFSET);
    hi_reg_write32(CRG_REG_SC_PERI_SRST_REG, value);

    ret = hi_i2c_deinit(id);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if (!g_i2c_ctrl[id].baudrate) {
        hi_i2c_init(id, g_i2c_ctrl[id].baudrate);
    } else {
        hi_i2c_init(id, I2C_RATE_DEFAULT);
    }
    return HI_ERR_SUCCESS;
}

static hi_u32 i2c_base(hi_i2c_idx id)
{
    if (id == HI_I2C_IDX_0) {
        return I2C0_BASE;
    }
    return I2C1_BASE;
}

static hi_u32 i2c_wait(hi_i2c_idx id)
{
    hi_u32 reg_val = 0;
    hi_u32 time_out = 0;

    hi_reg_read32((i2c_base(id) + I2C_SR), reg_val);
    while ((!(reg_val & I2C_INT_DONE)) && (time_out < g_i2c_ctrl[id].timeout_us)) {
        time_out++;
        hi_udelay(1);
        hi_reg_read32((i2c_base(id) + I2C_SR), reg_val);
    }

    if (time_out >= g_i2c_ctrl[id].timeout_us) {
        i2c_error("wait-timeout >= TIMEOUT error ! \n");
        return HI_ERR_I2C_TIMEOUT_WAIT;
    }

    /* ack error occur */
    if (I2C_ACK_INTR & reg_val) {
        return HI_ERR_I2C_WAIT_ACK_ERR;
    }

    hi_reg_read32((i2c_base(id) + I2C_ICR), reg_val);
    hi_reg_write32((i2c_base(id) + I2C_ICR), (reg_val | I2C_CLEAR_OVER));

    return HI_ERR_SUCCESS;
}

static hi_void i2c_cfg_clk(hi_i2c_idx id, hi_u32 i2c_rate)
{
    hi_u32 reg_val = 0;
    hi_u32 reg_clk_val;

    /* save i2c system control */
    hi_reg_read32((i2c_base(id) + I2C_CTRL), reg_val);

    /* mask all i2c interrupt */
    hi_reg_write32((i2c_base(id) + I2C_CTRL), (reg_val & (~I2C_UNMASK_ALL)));
    reg_clk_val = (I2C_CLK / (i2c_rate * 2)) *  /* 2 */
        g_i2c_ctrl[id].scl_h / (g_i2c_ctrl[id].scl_l + g_i2c_ctrl[id].scl_h) - 1;
    hi_reg_write32((i2c_base(id) + I2C_SCL_H), reg_clk_val);
    reg_clk_val = (I2C_CLK / (i2c_rate * 2)) *  /* 2 */
        g_i2c_ctrl[id].scl_l / (g_i2c_ctrl[id].scl_l + g_i2c_ctrl[id].scl_h) - 1;
    hi_reg_write32((i2c_base(id) + I2C_SCL_L), reg_clk_val);

    /* resume i2c interrupt */
    hi_reg_write32((i2c_base(id) + I2C_CTRL), reg_val);
}

static hi_u32 i2c_start(hi_i2c_idx id)
{
    hi_u32 reg_val = 0;
    hi_u32 time_out = 0;

    /* clear interrupt */
    hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);

    /* start operation */
    hi_reg_write32((i2c_base(id) + I2C_COM), (I2C_START | I2C_WRITE));

    hi_reg_read32((i2c_base(id) + I2C_SR), reg_val);

    while (((reg_val & I2C_INT_DONE) != I2C_INT_DONE) && (time_out < g_i2c_ctrl[id].timeout_us)) {
        time_out++;
        hi_reg_read32((i2c_base(id) + I2C_SR), reg_val);
        hi_udelay(1);
    }

    hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_START_END);

    /* timeout handle */
    if (time_out >= g_i2c_ctrl[id].timeout_us) {
        i2c_error("timeout >= TIMEOUT error ! \n");
        return HI_ERR_I2C_TIMEOUT_START;
    }

    if (I2C_ACK_INTR & reg_val) { /* ack error occur */
        return HI_ERR_I2C_START_ACK_ERR;
    }

    hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_OVER);

    return HI_ERR_SUCCESS;
}

static hi_u32 i2c_stop(hi_i2c_idx id)
{
    hi_u32 reg_val = 0;
    hi_u32 time_out = 0;

    /* start stop operation */
    hi_reg_write32((i2c_base(id) + I2C_COM), I2C_STOP);
    hi_reg_read32((i2c_base(id) + I2C_SR), reg_val);

    while (((reg_val & I2C_INT_DONE) != I2C_INT_DONE) && (time_out < g_i2c_ctrl[id].timeout_us)) {
        hi_reg_read32((i2c_base(id) + I2C_SR), reg_val);
        hi_udelay(1);
        time_out++;
    }

    hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);

    if (time_out >= g_i2c_ctrl[id].timeout_us) {
        i2c_error("timeout >= TIMEOUT in i2c_stop error ! \n");
        return HI_ERR_I2C_TIMEOUT_STOP;
    }

    return HI_ERR_SUCCESS;
}

hi_void i2c_read(hi_i2c_idx id)
{
    hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
    hi_reg_write32((i2c_base(id) + I2C_COM), I2C_READ);
}

hi_void i2c_write(hi_i2c_idx id)
{
    /* clear interrupt */
    hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);

    /* write operation */
    hi_reg_write32((i2c_base(id) + I2C_COM), I2C_WRITE);
}

/*
 * sends a character over I2C bus routine.
 *
 * @param sendvalue: character to send
 * @return value:0--success; -1--error.
 *
 */
static hi_u32 i2c_send_byte(hi_i2c_idx id, hi_u8 send_val)
{
    hi_reg_write32((i2c_base(id) + I2C_TXR), send_val);
    i2c_write(id);

    return i2c_wait(id);
}

/*
 * receives a character from I2C bus routine.
 *
 * @return value:character received
 *
 */
static hi_u32 i2c_receive_byte(hi_i2c_idx id, hi_u8 *p_data)
{
    hi_u32 ret;
    hi_u32 reg_val = 0;
    hi_u32 time_out = 0;

    if (p_data == HI_NULL) {
        i2c_error("null point.\n");
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    i2c_read(id);

    hi_reg_read32((i2c_base(id) + I2C_SR), reg_val);
    while ((!(reg_val & I2C_INT_DONE)) && (time_out < g_i2c_ctrl[id].timeout_us)) {
        time_out++;
        hi_udelay(1);
        hi_reg_read32((i2c_base(id) + I2C_SR), reg_val);
    }

    if (time_out >= g_i2c_ctrl[id].timeout_us) {
        i2c_error("receive data error\n");
        return HI_ERR_I2C_TIMEOUT_RCV_BYTE;
    }

    hi_reg_read32((i2c_base(id) + I2C_RXR), reg_val);
    *p_data = (hi_u8)(reg_val);
    ret = i2c_wait(id);
    if (ret != HI_ERR_SUCCESS) {
        i2c_error("read wait timeout.\n");
    }

    hi_reg_write32((i2c_base(id) + I2C_ICR), (I2C_RECEIVE_INTR | I2C_INT_DONE));

    return ret;
}

/*
 * writes address of device to I2C bus routine.
 *
 * @param address: address of device
 *
 */
static hi_void i2c_set_addr(hi_i2c_idx id, hi_u16 addr)
{
    hi_reg_write32((i2c_base(id) + I2C_TXR), addr);
}

static hi_bool i2c_is_10bit_addr(hi_u16 uc_addr)
{
    if ((uc_addr & 0xF000) == 0xF000) {
        return HI_TRUE;
    }
    return HI_FALSE;
}

static hi_u32 i2c_10bit_send_addressing(hi_i2c_idx id, hi_u16 device_addr)
{
    hi_u32 ret;
    /* 10bit: */
    /* Send 5 bits signaling 10 bit addressing(1111 0)
      followed by the first two bits of the I2C address
      and then the standard read/write bit. */
    hi_u8 addr = device_addr >> 8;  /* 8 */

    i2c_set_addr(id, addr & WRITE_OPERATION);  /* R/W -> W(0) */
    ret = i2c_start(id);
    if (ret != HI_ERR_SUCCESS) {
        hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
        /* for testing */
        i2c_error("10bit SEND first addressing failed!");
        return ret;
    }

    addr = (hi_u8)device_addr;
    i2c_set_addr(id, addr);  /* second addressing */
    ret = i2c_start(id);
    if (ret != HI_ERR_SUCCESS) {
        hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
        /* for testing */
        i2c_error("10bit SEND second addressing failed!");
        return ret;
    }
    return HI_ERR_SUCCESS;
}

static hi_u32 i2c_10bit_receive_addressing(hi_i2c_idx id, hi_u16 device_addr)
{
    hi_u32 ret;
    /* 10bit: */
    /* send the complete 10-bit address (two bytes) as for writing at first */
    /* first addressing R/W->W(0) */
    hi_u8 addr = device_addr >> 8;  /* 8 */

    i2c_set_addr(id, addr & WRITE_OPERATION);   /* R/W -> W(0) */
    ret = i2c_start(id);
    if (ret != HI_ERR_SUCCESS) {
        hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
        /* for testing */
        i2c_error("10bit RECEIVE first addressing failed");
        return ret;
    }

    /* second addressing */
    addr = (hi_u8)device_addr;

    i2c_set_addr(id, addr);
    ret = i2c_start(id);
    if (ret != HI_ERR_SUCCESS) {
        hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
        /* for testing */
        i2c_error("10bit RECEIVE second addressing failed");
        return ret;
    }

    /* a repeated start is sent followed by the first address byte
       with read/write bit set to high to signal reading */
    /* third addressing R/W->R(1) */
    addr = device_addr >> 8;    /* 8 */

    i2c_set_addr(id, addr | READ_OPERATION);
    ret = i2c_start(id);
    if (ret != HI_ERR_SUCCESS) {
        hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
        /* for testing */
        i2c_error("10bit RECEIVE after SR addressing failed");
        return ret;
    }
    return HI_ERR_SUCCESS;
}

static hi_u32 i2c_receive_last_byte(hi_i2c_idx id, hi_u8 *p_data)
{
    hi_u32 reg_val = 0;
    hi_u32 ret;
    hi_u32 time_out = 0;

    hi_reg_write32((i2c_base(id) + I2C_COM), (I2C_READ | (~I2C_SEND_ACK)));
    hi_reg_read32((i2c_base(id) + I2C_SR), reg_val);
    while ((!(reg_val & I2C_INT_DONE)) && (time_out < g_i2c_rcv_time_out_us)) {
        time_out++;
        hi_udelay(1);
        hi_reg_read32((i2c_base(id) + I2C_SR), reg_val);
    }

    if (time_out >= g_i2c_rcv_time_out_us) {
        i2c_error("receive data error\n");
        hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
        return HI_ERR_I2C_TIMEOUT_RCV_BYTE_PROC;
    }

    hi_reg_read32((i2c_base(id) + I2C_RXR), reg_val);
    if (p_data != HI_NULL) {
        *p_data = (hi_u8)reg_val;
    }
    ret = i2c_wait(id);
    if (ret != HI_ERR_SUCCESS) {
        i2c_error("Receive data with no ack error!..\n");
        hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
        return ret;
    }

    return HI_ERR_SUCCESS;
}

static hi_u32 i2c_receive_byte_proc(hi_i2c_idx id, const hi_i2c_data *i2c_data)
{
    hi_u32 ret;
    hi_u32 i;

    for (i = 0; i < (i2c_data->receive_len); i++) {
        if (i == (i2c_data->receive_len - 1)) {
            ret = i2c_receive_last_byte(id, i2c_data->receive_buf + i);
            if (ret != HI_ERR_SUCCESS) {
                return ret;
            }
        } else {
            ret = i2c_receive_byte(id, i2c_data->receive_buf + i);
            if (ret != HI_ERR_SUCCESS) {
                i2c_error("i2c_receive_byte error ! \n");
                hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
                return ret;
            }
        }
    }

    hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_OVER);

    ret = i2c_stop(id);
    if (ret != HI_ERR_SUCCESS) {
        hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
        return ret;
    }

    return HI_ERR_SUCCESS;
}

static hi_u32 i2c_restart_receive_data(hi_i2c_idx id, hi_u8 device_addr, const hi_i2c_data *i2c_data)
{
    hi_u32 i;
    hi_u32 ret;

    hi_reg_write32((i2c_base(id) + I2C_CTRL),
                   (I2C_IP_ENABLE | I2C_UNMASK_ALL | I2C_UNMASK_ACK | I2C_UNMASK_ARBITRATE | I2C_UNMASK_OVER));

    hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);

    /* write device addr */
    if (i2c_is_10bit_addr(device_addr) == HI_TRUE) {
        ret = i2c_10bit_send_addressing(id, device_addr);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    } else {
        /* 7bit addressing */
        i2c_set_addr(id, device_addr & WRITE_OPERATION);
        ret = i2c_start(id);
        if (ret != HI_ERR_SUCCESS) {
            i2c_error("start error when write address.\n");
            hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
            return ret;
        }
    }

    /* write register addr */
    for (i = 0; i < (i2c_data->send_len); i++) {
        ret = i2c_send_byte(id, *(i2c_data->send_buf + i));
        if (ret != HI_ERR_SUCCESS) {
            i2c_error("no ack.\n");
            hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
            return ret;
        }
    }

    /* read device addr */
    if (i2c_is_10bit_addr(device_addr) == HI_TRUE) {
        ret = i2c_10bit_receive_addressing(id, device_addr);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    } else {
        /* 7bit addressing */
        i2c_set_addr(id, device_addr | READ_OPERATION);
        ret = i2c_start(id);
        if (ret != HI_ERR_SUCCESS) {
            i2c_error("start error when write address.\n");
            hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
            return ret;
        }
    }

    /* read data */
    ret = i2c_receive_byte_proc(id, i2c_data);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    return HI_ERR_SUCCESS;
}

static hi_u32 i2c_send_data(hi_i2c_idx id, hi_u16 device_addr, const hi_i2c_data *i2c_data)
{
    hi_u32 i;
    hi_u32 ret;

    hi_reg_write32((i2c_base(id) + I2C_CTRL),
                   (I2C_IP_ENABLE | I2C_UNMASK_ALL | I2C_UNMASK_ACK | I2C_UNMASK_ARBITRATE | I2C_UNMASK_OVER));

    /* clear all i2c interrupt */
    hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);

    i2c_set_addr(id, device_addr & WRITE_OPERATION);

    if (i2c_is_10bit_addr(device_addr) == HI_TRUE) {
        ret = i2c_10bit_send_addressing(id, device_addr);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    } else {
        /* 7bit addressing */
        i2c_set_addr(id, device_addr & WRITE_OPERATION);
        ret = i2c_start(id);
        if (ret != HI_ERR_SUCCESS) {
            hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
            return ret;
        }
    }

    for (i = 0; i < (i2c_data->send_len); i++) {
        ret = i2c_send_byte(id, *(i2c_data->send_buf + i));
        if (ret != HI_ERR_SUCCESS) {
            i2c_error("i2csendbyte() error ! \n");
            hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
            return ret;
        }
    }

    ret = i2c_stop(id);
    if (ret != HI_ERR_SUCCESS) {
        hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
        return ret;
    }

    return HI_ERR_SUCCESS;
}

static hi_u32 i2c_receive_data(hi_i2c_idx id, hi_u16 device_addr, const hi_i2c_data *i2c_data)
{
    hi_u32 ret;

    hi_reg_write32((i2c_base(id) + I2C_CTRL),
                   (I2C_IP_ENABLE | I2C_UNMASK_ALL | I2C_UNMASK_ACK | I2C_UNMASK_ARBITRATE | I2C_UNMASK_OVER));

    /* clear all i2c interrupt */
    hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);

    if (i2c_is_10bit_addr(device_addr) == HI_TRUE) {
        ret = i2c_10bit_receive_addressing(id, device_addr);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    } else {
        /* 7bit addressing */
        i2c_set_addr(id, device_addr | READ_OPERATION);
        ret = i2c_start(id);
        if (ret != HI_ERR_SUCCESS) {
            i2c_error("start error when write address.\n");
            hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);
            return ret;
        }
        ret = i2c_receive_byte_proc(id, i2c_data);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    }

    return HI_ERR_SUCCESS;
}

static hi_u32 i2c_read_param_check(hi_i2c_idx id, const hi_i2c_data *i2c_data)
{
    if (id > HI_I2C_IDX_1 || id < HI_I2C_IDX_0) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (id >= I2C_NUM) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (i2c_data == HI_NULL) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (i2c_data->receive_buf == HI_NULL) {
        i2c_error("null point.\n");
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (i2c_data->receive_len == 0) {
        i2c_error("invalid receive_len. \n");
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    return HI_ERR_SUCCESS;
}

static hi_u32 i2c_writeread_param_check(hi_i2c_idx id, const hi_i2c_data *i2c_data)
{
    if (id > HI_I2C_IDX_1 || id < HI_I2C_IDX_0) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (id >= I2C_NUM) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (i2c_data == HI_NULL) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if ((i2c_data->send_buf == HI_NULL) || (i2c_data->receive_buf == HI_NULL)) {
        i2c_error("null point.\n");
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (i2c_data->receive_len == 0 || i2c_data->send_len == 0) {
        i2c_error("invalid receive_len or send_len. \n");
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    return HI_ERR_SUCCESS;
}

static hi_u32 i2c_read_data(hi_i2c_idx id, hi_u16 device_addr, const hi_i2c_data *i2c_data)
{
    hi_u32 ret;

    if (g_i2c_ctrl[id].prepare_func) {
        g_i2c_ctrl[id].prepare_func();
    }

    ret = i2c_receive_data(id, device_addr, i2c_data);
    if (ret) {
        if (g_i2c_ctrl[id].reset_bus_func) {
            g_i2c_ctrl[id].reset_bus_func();
        }
    }

    if (g_i2c_ctrl[id].restore_func) {
        g_i2c_ctrl[id].restore_func();
    }

    return ret;
}

static hi_void i2c_writeread_data(hi_i2c_idx id, hi_u16 device_addr, const hi_i2c_data *i2c_data)
{
    hi_u32 ret;

    if (g_i2c_ctrl[id].prepare_func) {
        g_i2c_ctrl[id].prepare_func();
    }

    ret = i2c_restart_receive_data(id, device_addr, i2c_data);
    if (ret) {
        if (g_i2c_ctrl[id].reset_bus_func) {
            g_i2c_ctrl[id].reset_bus_func();
        }
    }
    if (g_i2c_ctrl[id].restore_func) {
        g_i2c_ctrl[id].restore_func();
    }
}

hi_u32 hi_i2c_writeread(hi_i2c_idx id, hi_u16 device_addr, const hi_i2c_data *i2c_data)
{
    hi_u32 ret;

    ret = i2c_writeread_param_check(id, i2c_data);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (g_i2c_ctrl[id].init == HI_FALSE) {
        return HI_ERR_I2C_NOT_INIT;
    }

    i2c_writeread_data(id, device_addr, i2c_data);

    ret = hi_sem_wait(g_i2c_drv_sem[id], HI_SYS_WAIT_FOREVER);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_I2C_WAIT_SEM_FAIL;
    }

    hi_sem_signal(g_i2c_drv_sem[id]);
    return ret;
}

hi_u32 hi_i2c_write(hi_i2c_idx id, hi_u16 device_addr, const hi_i2c_data *i2c_data)
{
    hi_u32 ret;

    if (id > HI_I2C_IDX_1 || id < HI_I2C_IDX_0) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (id >= I2C_NUM) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (g_i2c_ctrl[id].init == HI_FALSE) {
        return HI_ERR_I2C_NOT_INIT;
    }

    if (i2c_data == HI_NULL) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (i2c_data->send_buf == HI_NULL) {
        i2c_error("null point.\n");
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (i2c_data->send_len == 0) {
        i2c_error("invalid send_len. \n");
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    ret = hi_sem_wait(g_i2c_drv_sem[id], HI_SYS_WAIT_FOREVER);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_I2C_WAIT_SEM_FAIL;
    }

    if (g_i2c_ctrl[id].prepare_func) {
        g_i2c_ctrl[id].prepare_func();
    }

    ret = i2c_send_data(id, device_addr, i2c_data);
    if (ret) {
        if (g_i2c_ctrl[id].reset_bus_func) {
            g_i2c_ctrl[id].reset_bus_func();
        }
    }

    if (g_i2c_ctrl[id].restore_func) {
        g_i2c_ctrl[id].restore_func();
    }

    hi_sem_signal(g_i2c_drv_sem[id]);

    return ret;
}

hi_u32 hi_i2c_read(hi_i2c_idx id, hi_u16 device_addr, const hi_i2c_data *i2c_data)
{
    hi_u32 ret, sem_ret;

    ret = i2c_read_param_check(id, i2c_data);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if (g_i2c_ctrl[id].init == HI_FALSE) {
        return HI_ERR_I2C_NOT_INIT;
    }

    ret = hi_sem_wait(g_i2c_drv_sem[id], HI_SYS_WAIT_FOREVER);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_I2C_WAIT_SEM_FAIL;
    }

    ret = i2c_read_data(id, device_addr, i2c_data);

    sem_ret = hi_sem_signal(g_i2c_drv_sem[id]);
    if (sem_ret != HI_ERR_SUCCESS) {
        return sem_ret;
    }

    return ret;
}

hi_u32 hi_i2c_init(hi_i2c_idx id, hi_u32 baudrate)
{
    hi_u32 ret;

    if (baudrate == 0 || id > HI_I2C_IDX_1 || id < HI_I2C_IDX_0) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (id >= I2C_NUM) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (g_i2c_ctrl[id].init == HI_FALSE) {
        hi_u16 reg_val;
        hi_reg_read16(CLDO_CTL_CLKEN_REG, reg_val);
        reg_val |= (id == HI_I2C_IDX_0) ? (1 << CLKEN_I2C0) : (1 << CLKEN_I2C1);
        hi_reg_write16(CLDO_CTL_CLKEN_REG, reg_val); /* enable i2cx clk bus */
        hi_reg_write32((i2c_base(id) + I2C_CTRL), (~(I2C_IP_ENABLE)));

        g_i2c_ctrl[id].baudrate = baudrate;

        i2c_cfg_clk(id, baudrate);

        hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);

        ret = hi_sem_bcreate(&g_i2c_drv_sem[id], HI_TRUE);
        if (ret) {
            return ret;
        }
        g_i2c_ctrl[id].init = HI_TRUE;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 hi_i2c_deinit(hi_i2c_idx id)
{
    hi_u32 ret;

    if (id > HI_I2C_IDX_1 || id < HI_I2C_IDX_0) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (id >= I2C_NUM) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (g_i2c_ctrl[id].init == HI_TRUE) {
        ret = hi_sem_delete(g_i2c_drv_sem[id]);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
        g_i2c_ctrl[id].init = HI_FALSE;
        hi_u16 reg_val;
        hi_reg_read16(CLDO_CTL_CLKEN_REG, reg_val);
        reg_val &= (id == HI_I2C_IDX_0) ? ~(1 << CLKEN_I2C0) : ~(1 << CLKEN_I2C1);
        hi_reg_write16(CLDO_CTL_CLKEN_REG, reg_val); /* disable i2cx clk bus */
    }

    return HI_ERR_SUCCESS;
}

hi_u32 hi_i2c_set_baudrate(hi_i2c_idx id, hi_u32 baudrate)
{
    /* baudrate range */
    if (id > HI_I2C_IDX_1 || id < HI_I2C_IDX_0 || baudrate == 0) {
        return HI_ERR_I2C_INVALID_PARAMETER;
    }

    if (g_i2c_ctrl[id].init == HI_FALSE) {
        return HI_ERR_I2C_NOT_INIT;
    }

    hi_reg_write32((i2c_base(id) + I2C_CTRL), (~(I2C_IP_ENABLE)));

    g_i2c_ctrl[id].baudrate = baudrate;

    i2c_cfg_clk(id, baudrate);

    hi_reg_write32((i2c_base(id) + I2C_ICR), I2C_CLEAR_ALL);

    return HI_ERR_SUCCESS;
}

hi_void hi_i2c_register_reset_bus_func(hi_i2c_idx id, hi_i2c_func pfn)
{
    if (id > HI_I2C_IDX_1 || id < HI_I2C_IDX_0) {
        return;
    }
    g_i2c_ctrl[id].reset_bus_func = pfn.reset_func;
    g_i2c_ctrl[id].prepare_func = pfn.prepare_func;
    g_i2c_ctrl[id].restore_func = pfn.restore_func;
}

