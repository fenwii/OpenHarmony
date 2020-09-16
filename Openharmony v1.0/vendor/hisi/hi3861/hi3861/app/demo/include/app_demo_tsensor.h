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

#ifndef __APP_DEMO_I2S_H__
#define __APP_DEMO_I2S_H__

#include <hi_types_base.h>
#include <hi_early_debug.h>
#include <hi_task.h>
#include <hi_systick.h>
#include <hi_time.h>
#include <hi_tsensor.h>
#include <app_demo_tsensor.h>

#define TEMPERRATURE_OUT_THRESHOLD_LOW    (-30)
#define TEMPERRATURE_OUT_THRESHOLD_HIGH   100
#define TEMPERRATURE_OVER_THRESHOLD       115
#define TEMPERRATURE_POWER_DOWN_THRESHOLD 125
#define TSENSOR_CALIBRATE_CODE            0x07
#define TSENSOR_CALIBRATE_CODE_LOAD_EFUSE 0
#define TSENSOR_CALIBRATE_CODE_LOAD_REG   1
#define TSENSOR_PERIOD_VALUE              500
#define TSENSOR_TEST_INTERVAL             1000
#define TSENSOR_TEST_LOOP                 10
#define TSENSOR_GET_TEMPERRATURE_INTERVAL (TSENSOR_PERIOD_VALUE * 31.25 + 192 * 16)

static hi_void tensor_collect_finish_irq(hi_s16 irq_temperature);
static hi_void tensor_outtemp_irq(hi_s16 irq_temperature);
static hi_void tensor_overtemp_irq(hi_s16 irq_temperature);
static hi_void read_temprature_none_irq_single(hi_void);
hi_void tsensor_demo(hi_void);
#endif
