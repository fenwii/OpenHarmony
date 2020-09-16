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
 *
 * Description: pwm driver implementatioin.
 */

#ifndef __PWM_DRV_H__
#define __PWM_DRV_H__

#include <hi3861_platform.h>
#include <hi_pwm.h>

#define PWM_BASE_ADDR_STEP 0x100
#define pwm_base_addr(pwm_num) (HI_PWM_REG_BASE + (pwm_num) * PWM_BASE_ADDR_STEP)

#define pwm_en_reg(base_addr)    ((base_addr)+ 0x0)
#define pwm_start_reg(base_addr) ((base_addr) + 0x4)
#define pwm_freq_reg(base_addr)  ((base_addr) + 0x8)
#define pwm_duty_reg(base_addr)  ((base_addr) + 0xC)

typedef struct {
    hi_bool is_init;
    hi_u8 reserved[3]; /* 3bytes reserved */
    hi_u32 pwm_sem;
}pwm_ctl;

typedef struct {
    pwm_ctl pwm[HI_PWM_PORT_MAX];
}pwm_ctx;

hi_u32 pwm_check_port(hi_pwm_port port);
hi_bool pwm_is_init(hi_pwm_port port);
hi_u32 pwm_lock(hi_pwm_port port);
hi_u32 pwm_unlock(hi_pwm_port port);
pwm_ctl *pwm_get_ctl(hi_pwm_port port);


#endif

