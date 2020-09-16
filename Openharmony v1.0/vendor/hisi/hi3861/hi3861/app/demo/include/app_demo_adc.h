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

#ifndef __APP_DEMO_ADC_H__
#define __APP_DEMO_ADC_H__

#include <hi_types_base.h>

#define APP_DEMO_ADC
#ifdef APP_DEMO_ADC

#include <hi_adc.h>
#include <hi_stdlib.h>
#include <hi_early_debug.h>

#define ADC_TEST_LENGTH  128
#define VLT_MIN 100

hi_void app_demo_adc_test(hi_void);
#endif
#endif