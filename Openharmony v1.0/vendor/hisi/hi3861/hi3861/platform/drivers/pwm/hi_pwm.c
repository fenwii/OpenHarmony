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

#include <hi_stdlib.h>
#include <hi_sem.h>

#include "pwm_drv.h"

#define CLKEN1_PWM5     10
#define CLKEN1_PWM_BUS  6
#define CLKEN1_PWM      5
#define CLKEN1_PWM4     4
#define CLKEN1_PWM3     3
#define CLKEN1_PWM2     2
#define CLKEN1_PWM1     1
#define CLKEN1_PWM0     0
#define CLKEN1_PWM_ALL  ((1 << (CLKEN1_PWM0)) | (1 << (CLKEN1_PWM1)) | (1 << (CLKEN1_PWM2)) | (1 << (CLKEN1_PWM3)) | \
                        (1 << (CLKEN1_PWM4)) | (1 << (CLKEN1_PWM5)))

hi_u32 hi_pwm_init(hi_pwm_port port)
{
    hi_u32 ret;
    pwm_ctl *ctrl = HI_NULL;
    hi_u16 reg_val;

    if (pwm_check_port(port) != HI_ERR_SUCCESS) {
        return HI_ERR_PWM_INVALID_PARAMETER;
    }
    ctrl = pwm_get_ctl(port);
    if (ctrl->is_init == HI_FALSE) {
        hi_reg_read16(CLDO_CTL_CLKEN1_REG, reg_val);
        switch (port) {
            case HI_PWM_PORT_PWM0:
                ret = hi_sem_bcreate(&(ctrl->pwm_sem), HI_SEM_ONE);
                reg_val |= 1 << CLKEN1_PWM0;
                break;
            case HI_PWM_PORT_PWM1:
                ret = hi_sem_bcreate(&(ctrl->pwm_sem), HI_SEM_ONE);
                reg_val |= 1 << CLKEN1_PWM1;
                break;
            case HI_PWM_PORT_PWM2:
                ret = hi_sem_bcreate(&(ctrl->pwm_sem), HI_SEM_ONE);
                reg_val |= 1 << CLKEN1_PWM2;
                break;
            case HI_PWM_PORT_PWM3:
                ret = hi_sem_bcreate(&(ctrl->pwm_sem), HI_SEM_ONE);
                reg_val |= 1 << CLKEN1_PWM3;
                break;
            case HI_PWM_PORT_PWM4:
                ret = hi_sem_bcreate(&(ctrl->pwm_sem), HI_SEM_ONE);
                reg_val |= 1 << CLKEN1_PWM4;
                break;
            default:
                ret = hi_sem_bcreate(&(ctrl->pwm_sem), HI_SEM_ONE);
                reg_val |= 1 << CLKEN1_PWM5;
                break;
        }

        if (ret == HI_ERR_SUCCESS) {
            ctrl->is_init = HI_TRUE;
            reg_val |= (1 << CLKEN1_PWM_BUS) | (1 << CLKEN1_PWM);
            hi_reg_write16(CLDO_CTL_CLKEN1_REG, reg_val); /* enable pwmx clk bus */
        }
    } else {
        ret = HI_ERR_SUCCESS; /* HI_ERR_PWM_INITILIZATION_ALREADY return success */
    }
    return ret;
}

hi_void pwm_deinit_clken(hi_pwm_port port)
{
    hi_u16 reg_val;
    if (pwm_check_port(port) != HI_ERR_SUCCESS) {
        return;
    }
    hi_reg_read16(CLDO_CTL_CLKEN1_REG, reg_val);
    if (port == HI_PWM_PORT_PWM5) {
        reg_val &= ~(1 << CLKEN1_PWM5);
    } else {
        reg_val &= ~(1 << (hi_u16)port);
    }
    if ((reg_val & CLKEN1_PWM_ALL) == 0) { /* if all channels are free, then close pwm bus and clk_pwm */
        reg_val &= ~((1 << CLKEN1_PWM_BUS) | (1 << CLKEN1_PWM));
    }
    hi_reg_write16(CLDO_CTL_CLKEN1_REG, reg_val); /* disable pwmx clk bus */
}

hi_u32 hi_pwm_deinit(hi_pwm_port port)
{
    hi_u32 ret;
    pwm_ctl *ctrl = HI_NULL;

    if (pwm_check_port(port) != HI_ERR_SUCCESS) {
        return HI_ERR_PWM_INVALID_PARAMETER;
    }
    ctrl = pwm_get_ctl(port);
    if (ctrl->is_init == HI_TRUE) {
        ret = hi_sem_delete(ctrl->pwm_sem);
        if (ret == HI_ERR_SUCCESS) {
            (hi_void)memset_s(ctrl, sizeof(pwm_ctl), 0, sizeof(pwm_ctl));
            pwm_deinit_clken(port);
        }
    } else {
        ret = HI_ERR_SUCCESS;
    }
    return ret;
}

hi_u32 hi_pwm_set_clock(hi_pwm_clk_source clk_type)
{
    if (clk_type >= PWM_CLK_MAX) {
        return HI_ERR_PWM_INVALID_PARAMETER;
    }

    if (clk_type == PWM_CLK_160M) {
        hi_reg_clrbit(CLDO_CTL_CLK_SEL_REG, 0);
    } else {
        hi_reg_setbit(CLDO_CTL_CLK_SEL_REG, 0);
    }

    return HI_ERR_SUCCESS;
}

static hi_void pwm_set_enable(hi_pwm_port port, hi_bool flag)
{
    if (flag == HI_TRUE) {
        /* enable */
        hi_reg_setbit(pwm_en_reg(pwm_base_addr(port)), 0);
    } else {
        /* disable */
        hi_reg_clrbit(pwm_en_reg(pwm_base_addr(port)), 0);
    }
}

static hi_void pwm_set_freq(hi_pwm_port port, hi_u16 freq)
{
    hi_reg_setbits(pwm_freq_reg(pwm_base_addr(port)), 0, 16, freq);  /* base_addr 16 */
}

static hi_void pwm_set_duty(hi_pwm_port port, hi_u16 duty)
{
    hi_reg_setbits(pwm_duty_reg(pwm_base_addr(port)), 0, 16, duty);  /* base_addr 16 */
}

static hi_void pwm_take_effect(hi_pwm_port port)
{
    hi_reg_setbit(pwm_start_reg(pwm_base_addr(port)), 0);
}

hi_u32 hi_pwm_start(hi_pwm_port port, hi_u16 duty, hi_u16 freq)
{
    hi_u32 ret;

    if ((pwm_check_port(port) != HI_ERR_SUCCESS) || (duty == 0) || (freq == 0)
        || (duty > freq)) {
        return HI_ERR_PWM_INVALID_PARAMETER;
    }
    if (pwm_is_init(port) == HI_FALSE) {
        return HI_ERR_PWM_NO_INIT;
    }
    ret = pwm_lock(port);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    pwm_set_enable(port, HI_TRUE);
    pwm_set_freq(port, freq);
    pwm_set_duty(port, duty);
    pwm_take_effect(port);
    return pwm_unlock(port);
}

hi_u32 hi_pwm_stop(hi_pwm_port port)
{
    hi_u32 ret;

    if (pwm_check_port(port) != HI_ERR_SUCCESS) {
        return HI_ERR_PWM_INVALID_PARAMETER;
    }
    if (pwm_is_init(port) == HI_FALSE) {
        return HI_ERR_PWM_NO_INIT;
    }

    ret = pwm_lock(port);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    pwm_set_enable(port, HI_FALSE);
    pwm_take_effect(port);
    return pwm_unlock(port);
}

hi_u32 pwm_check_port(hi_pwm_port port)
{
    if (port >= HI_PWM_PORT_MAX) {
        return HI_ERR_PWM_INVALID_PARAMETER;
    }
    return HI_ERR_SUCCESS;
}
