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

#ifndef __APP_DEMO_I2C_H__
#define __APP_DEMO_I2C_H__

#include <hi_types_base.h>
#include <hi_i2c.h>
#include <hi_early_debug.h>
#include <hi_stdlib.h>

#define I2C_REG_ARRAY_LEN 64
#define ES8311_DEV_ADDR 0x30          /* 11000 0 */
#define ES8311_REG_ADDR 0x10
#define I2C_SEND_LEN_2  2
#define I2C_RECV_LEN_1  1

hi_void i2c_demo_send_data_init(hi_void);
hi_u32 i2c_demo_write(hi_i2c_idx id, hi_u16 device_addr, hi_u32 send_len);
hi_u32 i2c_demo_writeread(hi_i2c_idx id, hi_u16 device_addr, hi_u32 recv_len);
hi_void i2c_demo(hi_i2c_idx id);
hi_void app_demo_custom_i2c(hi_void);

#endif
