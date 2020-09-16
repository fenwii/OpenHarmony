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

#include "hi_flashboot_io.h"

#include <hi_types.h>

#define GPIO_SWPORT_DR            0x00
#define GPIO_SWPORT_DDR           0x04
#define GPIO_EXT_PORT             0x50
#define IO_MUX_REG_BASE_ADDR      0x604  /* Base address for the I/O function multiplexing register */
#define IO_CTRL_REG_BASE_ADDR     0x904  /* Base address of the I/O control register, which is used to
                                            configure the drive capability and pull-up/pull-down */
#define IO_DRV_PULL_MASK          0x3
#define IO_DRV_STRENGTH_MASK      0x7
#define IO_DRV_PULL_START_BIT     8
#define IO_DRV_STRENGTH_START_BIT 4
#define OFFSET_10_B 10
#define OFFSET_2_B  2
#define IE_MSK      0x1

hi_u32 hi_io_get_func(hi_io_name id, hi_u8* val)
{
    if ((id >= HI_IO_NAME_MAX) || (val == HI_NULL)) {
        return HI_ERR_GPIO_INVALID_PARAMETER;
    }
    hi_u32 reg_addr;
    hi_u32 reg_val = 0;
    reg_addr = HI_IOCFG_REG_BASE + IO_MUX_REG_BASE_ADDR + ((hi_u32)id << 2); /* lift shift 2 bits */
    hi_reg_read(reg_addr, reg_val);
    *val = (hi_u8)reg_val;
    return HI_ERR_SUCCESS;
}

hi_u32 hi_io_get_pull(hi_io_name id, hi_io_pull* val)
{
    if ((id >= HI_IO_NAME_MAX) || (val == HI_NULL)) {
        return HI_ERR_GPIO_INVALID_PARAMETER;
    }
    hi_u32 reg_val = 0;
    hi_reg_read((HI_IOCFG_REG_BASE + IO_CTRL_REG_BASE_ADDR + ((hi_u32)id << 2)), reg_val); /* lift shift 2 bits */
    *val = (hi_io_pull) ((reg_val >> IO_DRV_PULL_START_BIT) & IO_DRV_PULL_MASK);

    return HI_ERR_SUCCESS;
}

hi_u32 hi_io_set_driver_strength(hi_io_name id, hi_io_driver_strength val)
{
    if ((id >= HI_IO_NAME_MAX) || (val >= HI_IO_DRIVER_STRENGTH_MAX)) {
        return HI_ERR_GPIO_INVALID_PARAMETER;
    }
    hi_u32 reg_val = 0;

    if (((id <= HI_IO_NAME_GPIO_11) || (id == HI_IO_NAME_GPIO_13) || (id == HI_IO_NAME_GPIO_14))
        && (val >= HI_IO_DRIVER_STRENGTH_4)) {
        return HI_ERR_GPIO_NOT_SUPPORT;
    }
    hi_reg_read((HI_IOCFG_REG_BASE + IO_CTRL_REG_BASE_ADDR + ((hi_u32)id << 2)), reg_val); /* lift shift 2 bits */
    reg_val &= ~(IO_DRV_STRENGTH_MASK << IO_DRV_STRENGTH_START_BIT);
    reg_val |= ((hi_u32) val & IO_DRV_STRENGTH_MASK) << IO_DRV_STRENGTH_START_BIT;
    hi_reg_write((HI_IOCFG_REG_BASE + IO_CTRL_REG_BASE_ADDR + ((hi_u32)id << 2)), reg_val); /* lift shift 2 bits */

    return HI_ERR_SUCCESS;
}

hi_u32 hi_io_get_driver_strength(hi_io_name id, hi_io_driver_strength* val)
{
    if ((id >= HI_IO_NAME_MAX) || (val == HI_NULL)) {
        return HI_ERR_GPIO_INVALID_PARAMETER;
    }
    hi_u32 reg_val = 0;

    hi_reg_read((HI_IOCFG_REG_BASE + IO_CTRL_REG_BASE_ADDR + ((hi_u32)id << 2)), reg_val); /* lift shift 2 bits */

    *val = (hi_io_driver_strength) ((reg_val >> IO_DRV_STRENGTH_START_BIT) & IO_DRV_STRENGTH_MASK);
    return HI_ERR_SUCCESS;
}

hi_u32 hi_io_set_input_enable(hi_io_name id, hi_bool state)
{
    hi_u32 reg_val;
    if (id >= HI_IO_NAME_MAX) {
        return HI_ERR_GPIO_INVALID_PARAMETER;
    }
    hi_reg_read((HI_IOCFG_REG_BASE + IO_CTRL_REG_BASE_ADDR + ((hi_u32)id << OFFSET_2_B)), reg_val);
    reg_val &= ~(IE_MSK << OFFSET_10_B);
    reg_val |= (state & IE_MSK) << OFFSET_10_B;
    hi_reg_write((HI_IOCFG_REG_BASE + IO_CTRL_REG_BASE_ADDR + ((hi_u32)id << OFFSET_2_B)), reg_val);
    return HI_ERR_SUCCESS;
}

hi_u32 hi_io_get_input_enable(hi_io_name id, hi_bool *state)
{
    hi_u32 reg_val;
    if ((id >= HI_IO_NAME_MAX) || (state == HI_NULL)) {
        return HI_ERR_GPIO_INVALID_PARAMETER;
    }
    hi_reg_read((HI_IOCFG_REG_BASE + IO_CTRL_REG_BASE_ADDR + ((hi_u32)id << OFFSET_2_B)), reg_val);
    *state = (reg_val >> OFFSET_10_B) & IE_MSK;
    return HI_ERR_SUCCESS;
}
