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

#ifndef __I2C_H_
#define __I2C_H_

#include <hi3861_platform_base.h>

#define I2C_CLK              CONFIG_WDT_CLOCK
#define I2C_NUM              2

#define I2C_FIFO_LINE_MIN    1
#define I2C_FIFO_LINE_MAX    32
#define I2C_FIFO_INIT_COUNT  1
#define I2C_FIFO_INIT_VALUE  0x1fff
#define I2C_INIT_VALUE       0x1ff
#define READ_OPERATION       (1<<0)
#define WRITE_OPERATION      (~READ_OPERATION)

#define I2C_CTRL             0x000
#define I2C_COM              0x004
#define I2C_ICR              0x008
#define I2C_SR               0x00C
#define I2C_SCL_H            0x010
#define I2C_SCL_L            0x014
#define I2C_TXR              0x018
#define I2C_RXR              0x01C
#define I2C_FIFOSTATUS       0x020
#define I2C_TXCOUNT          0x024
#define I2C_RXCOUNT          0x028
#define I2C_RXTIDE           0x02C
#define I2C_TXTIDE           0x030

/* I2C_CTRL */
#define I2C_UNMASK_FIFO_EMPTY       (1<<12)
#define I2C_FIFO_ENABLE             (1<<11)
#define I2C_UNMASK_FIFO_SEND_OF     (1<<10)
#define I2C_UNMASK_FIFO_RECEIVE_OF  (1<<9)
#define I2C_IP_ENABLE        (1<<8)
#define I2C_UNMASK_ALL       (1<<7)
#define I2C_UNMASK_START     (1<<6)
#define I2C_UNMASK_END       (1<<5)
#define I2C_UNMASK_SEND      (1<<4)
#define I2C_UNMASK_RECEIVE   (1<<3)
#define I2C_UNMASK_ACK       (1<<2)
#define I2C_UNMASK_ARBITRATE (1<<1)
#define I2C_UNMASK_OVER      (1<<0)

/* I2C_COM */
#define I2C_SEND_ACK         (~(1<<4))
#define I2C_START            (1<<3)
#define I2C_READ             (1<<2)
#define I2C_WRITE            (1<<1)
#define I2C_STOP             (1<<0)

/* I2C_ICR */
#define I2C_CLEAR_FIFO_EMPTY      (1<<9)
#define I2C_CLEAR_FIFO_SEND_OF    (1<<8)
#define I2C_CLEAR_FIFO_RECEIVE_OF (1<<7)
#define I2C_CLEAR_START      (1<<6)
#define I2C_CLEAR_END        (1<<5)
#define I2C_CLEAR_SEND       (1<<4)
#define I2C_CLEAR_RECEIVE    (1<<3)
#define I2C_CLEAR_ACK        (1<<2)
#define I2C_CLEAR_ARBITRATE  (1<<1)
#define I2C_CLEAR_OVER       (1<<0)
#define I2C_CLEAR_ALL        (I2C_CLEAR_FIFO_EMPTY | \
                              I2C_CLEAR_FIFO_SEND_OF | I2C_CLEAR_FIFO_RECEIVE_OF | \
                              I2C_CLEAR_START | I2C_CLEAR_END | \
                              I2C_CLEAR_SEND | I2C_CLEAR_RECEIVE | \
                              I2C_CLEAR_ACK | I2C_CLEAR_ARBITRATE | \
                              I2C_CLEAR_OVER)

/* I2C_SR */
#define I2C_FIFO_EMPTY       (1<<10)
#define I2C_FIFO_SEND_OF     (1<<9)
#define I2C_FIFO_RECEIVE_OF  (1<<8)
#define I2C_BUSY             (1<<7)
#define I2C_START_INTR       (1<<6)
#define I2C_END_INTR         (1<<5)
#define I2C_SEND_INTR        (1<<4)
#define I2C_RECEIVE_INTR     (1<<3)
#define I2C_ACK_INTR         (1<<2)
#define I2C_ARBITRATE_INTR   (1<<1)
#define I2C_INT_DONE         (1<<0)

#define I2C_START_END        (I2C_START_INTR | I2C_INT_DONE)
#define I2C_STOP_END         (I2C_END_INTR | I2C_INT_DONE)

#define I2C_START_EMPTY      (I2C_START_INTR | I2C_FIFO_EMPTY)
#define I2C_STOP_EMPTY       (I2C_END_INTR | I2C_FIFO_EMPTY)

/* I2C_FIFOSTATUS */
#define I2C_RECVFIFO_EMPTY   (1<<3)
#define I2C_RECVFIFO_FULL    (1<<2)
#define I2C_SENDFIFO_EMPTY   (1<<1)
#define I2C_SENDFIFO_FULL    (1<<0)


#define I2C_SC_SCPERCTRL0    0x1c
#define I2C_SC_SCPERCTRL2    0x34

#define i2c_error(_fmt, arg...)

#endif

