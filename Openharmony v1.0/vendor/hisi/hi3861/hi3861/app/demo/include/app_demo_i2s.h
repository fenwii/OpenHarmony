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
#include <hi_errno.h>
#include <hi_mem.h>
#include <hi_event.h>
#include <hi_time.h>
#include <hi_task.h>
#include <hi_early_debug.h>
#include <hi_config.h>
#include <hi_stdlib.h>
#include <hi_i2s.h>
#include <hi_i2c.h>
#include <hi_flash.h>
#include <es8311_codec.h>
#define I2S_TEST_TASK_STAK_SIZE     2048
#define I2S_TEST_TASK_PRIORITY      28
#define AUDIO_PLAY_BUF_SIZE         4096
#define AUDIO_RECORD_BUF_SIZE       3072
#define AUDIO_RECORD_FINISH_BIT     (1 << 0)
#define ALL_AUDIO_RECORD_FINISH_BIT (1 << 1)

#define AUDIO_PLAY_FIEL_MODE         0
#define AUDIO_RECORD_AND_PLAY_MODE   1

typedef struct {
    hi_u32 flash_start_addr;
    hi_u32 data_len;
} audio_map;

typedef struct {
    hi_u8 *play_buf;
    hi_u8 *record_buf;
} test_audio_attr;

hi_void i2s_demo(hi_void);
#endif
