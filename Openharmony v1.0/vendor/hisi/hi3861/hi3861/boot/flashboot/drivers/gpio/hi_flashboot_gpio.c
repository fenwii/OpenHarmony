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

#include "hi_flashboot_gpio.h"

#include <hi_types.h>
#include <hi3861_platform.h>

#define GPIO_SWPORT_DR            0x00
#define GPIO_SWPORT_DDR           0x04
#define GPIO_INTEN                0x30
#define GPIO_INTMASK              0x34
#define GPIO_INTTYPE_LEVEL        0x38
#define GPIO_INT_POLARITY         0x3c
#define GPIO_INTSTATUS            0x40
#define GPIO_RAWINTSTATUS         0x44
#define GPIO_PORT_EOI             0x4c
#define GPIO_EXT_PORT             0x50

hi_u32 hi_gpio_get_dir(hi_gpio_idx id, hi_gpio_dir *dir)
{
    if (id >= HI_GPIO_IDX_MAX || dir == HI_NULL) {
        return HI_ERR_GPIO_INVALID_PARAMETER;
    }

    hi_u16 reg_val = 0;
    // Obtains the input or output. The default value is 0.
    hi_reg_read16((HI_GPIO_REG_BASE + GPIO_SWPORT_DDR), reg_val);
    hi_io_dir_get(reg_val, (hi_u16) id, dir);

    return HI_ERR_SUCCESS;
}

hi_u32 hi_gpio_get_output_val(hi_gpio_idx id, hi_gpio_value* val)
{
    if ((id >= HI_GPIO_IDX_MAX) || (val == HI_NULL)) {
        return HI_ERR_GPIO_INVALID_PARAMETER;
    }

    hi_u16 reg_val = 0;

    hi_reg_read16((HI_GPIO_REG_BASE + GPIO_SWPORT_DR), reg_val);
    hi_io_val_get(reg_val, (hi_u16) id, val);

    return HI_ERR_SUCCESS;
}

hi_u32 hi_gpio_set_output_val(hi_gpio_idx id, hi_gpio_value val)
{
    if (id >= HI_GPIO_IDX_MAX || val > HI_GPIO_VALUE1) {
        return HI_ERR_GPIO_INVALID_PARAMETER;
    }

    hi_u16 reg_val = 0;

    hi_reg_read16((HI_GPIO_REG_BASE + GPIO_SWPORT_DR), reg_val);
    hi_io_val_set(val, (hi_u16) id, reg_val);
    hi_reg_write16((HI_GPIO_REG_BASE + GPIO_SWPORT_DR), reg_val);

    return HI_ERR_SUCCESS;
}

hi_u32 hi_gpio_get_input_val(hi_gpio_idx id, hi_gpio_value* val)
{
    if ((id >= HI_GPIO_IDX_MAX) || (val == HI_NULL)) {
        return HI_ERR_GPIO_INVALID_PARAMETER;
    }
    hi_u16 reg_val = 0;

    hi_reg_read16((HI_GPIO_REG_BASE + GPIO_EXT_PORT), reg_val);
    hi_io_val_get(reg_val, (hi_u16) id, val);

    return HI_ERR_SUCCESS;
}

hi_u32 hi_gpio_set_dir(hi_gpio_idx id, hi_gpio_dir dir)
{
    if (id >= HI_GPIO_IDX_MAX || dir > HI_GPIO_DIR_OUT) {
        return HI_ERR_GPIO_INVALID_PARAMETER;
    }
    hi_u16 dir_val = 0;

    hi_reg_read16((HI_GPIO_REG_BASE + GPIO_SWPORT_DDR), dir_val);
    hi_io_val_set(dir, (hi_u16) id, dir_val);
    hi_reg_write16((HI_GPIO_REG_BASE + GPIO_SWPORT_DDR), dir_val);

    return HI_ERR_SUCCESS;
}
