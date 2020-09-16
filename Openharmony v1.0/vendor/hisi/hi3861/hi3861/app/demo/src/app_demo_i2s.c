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

#include "app_demo_i2s.h"

#ifndef I2S_TEST_DEBUG
#define i2s_print(ftm...) do {printf(ftm);} while (0);
#else
#define i2s_print(ftm...)
#endif

audio_map g_audio_map[2] = {  /* 2 flash fields */
    {0x001A1000, 100 * 1024}, /* audio file size: 100 * 1024(100K) */
    {0x001CE000, 204800},     /* recod size: 200K */
};

hi_u32 g_audio_event;
hi_u32 g_audio_task_id;
test_audio_attr g_audio_test;
hi_u8 g_record_data[AUDIO_RECORD_BUF_SIZE] = {0};

hi_void es8311_codec_init(const hi_codec_attribute *codec_attr)
{
    if (codec_attr == HI_NULL) {
        return;
    }
    hi_u32 ret;

    ret = hi_i2c_init(HI_I2C_IDX_1, 100000);  /* 100000: i2s bit rate */
    if (ret != HI_ERR_SUCCESS) {
        i2s_print("==ERROR== hi_i2c_init, err = %X\n", ret);
        return;
    }

    ret = hi_codec_init(codec_attr);
    if (ret != HI_ERR_SUCCESS) {
        i2s_print("==ERROR== Failed to init codec!! err = %X\n", ret);
    } else {
        i2s_print("init codec success!\n");
    }
}

hi_void audio_play(hi_u32 map_index)
{
    hi_u32 ret;
    hi_u32 play_addr = g_audio_map[map_index].flash_start_addr;
    hi_u32 total_play_len = g_audio_map[map_index].data_len;
    hi_u32 time_out = HI_SYS_WAIT_FOREVER;

    /* apply memory */
    g_audio_test.play_buf = (hi_u8 *) hi_malloc(HI_MOD_ID_DRV, AUDIO_PLAY_BUF_SIZE);
    if (g_audio_test.play_buf == HI_NULL) {
        hi_i2s_deinit();
        i2s_print("==ERROR== play buf malloc fail!!!\n");
        return;
    }
    memset_s(g_audio_test.play_buf, AUDIO_PLAY_BUF_SIZE, 0, AUDIO_PLAY_BUF_SIZE);

    while (total_play_len > 0) {
        hi_u32 send_len = hi_min(total_play_len, AUDIO_PLAY_BUF_SIZE);
        ret = hi_flash_read(play_addr, send_len, g_audio_test.play_buf);
        if (ret != HI_ERR_SUCCESS) {
            i2s_print("==ERROR== hi_flash_read fail, err = %X\n", ret);
        }

        ret = hi_i2s_write(g_audio_test.play_buf, send_len, time_out);
        if (ret != HI_ERR_SUCCESS) {
            i2s_print("hi_i2s_write fail, err = %X\n", ret);
        }

        play_addr += send_len;
        total_play_len -= send_len;
    }

    i2s_print("Play over....\n");

    hi_free(HI_MOD_ID_DRV, g_audio_test.play_buf);
}

hi_void audio_record_func(hi_u32 map_index)
{
    hi_u32 ret;
    hi_u32 record_addr = g_audio_map[map_index].flash_start_addr;
    hi_u32 total_record_len = g_audio_map[map_index].data_len;
    hi_u32 time_out = HI_SYS_WAIT_FOREVER;

    ret = hi_flash_erase(record_addr, total_record_len);
    if (ret != HI_ERR_SUCCESS) {
        i2s_print("Failed to erase flash, err = %X\n", ret);
        return;
    }

    while (total_record_len > 0) {
        hi_u32 len = hi_min(AUDIO_RECORD_BUF_SIZE, total_record_len);
        ret = hi_i2s_read(g_audio_test.record_buf, len, time_out);
        if (ret != HI_ERR_SUCCESS) {
            i2s_print("Failed to hi_i2s_read, err = %X\n", ret);
            return;
        }

        if (memcpy_s(g_record_data, sizeof(g_record_data), g_audio_test.record_buf, len) != EOK) {
            return;
        }
        hi_event_send(g_audio_event, AUDIO_RECORD_FINISH_BIT);

        record_addr += len;
        total_record_len -= len;
    }

    hi_event_send(g_audio_event, ALL_AUDIO_RECORD_FINISH_BIT);
}

hi_void *record_n_play_task(hi_void *param)
{
    hi_u32 ret;
    hi_u32 event_bit = 0;
    hi_u32 record_addr = g_audio_map[AUDIO_RECORD_AND_PLAY_MODE].flash_start_addr;
    hi_u32 total_record_len = g_audio_map[AUDIO_RECORD_AND_PLAY_MODE].data_len;
    hi_u32 len;
    hi_unref_param(param);

    while (1) {
        hi_event_wait(g_audio_event, AUDIO_RECORD_FINISH_BIT | ALL_AUDIO_RECORD_FINISH_BIT, &event_bit,
            HI_SYS_WAIT_FOREVER, HI_EVENT_WAITMODE_OR | HI_EVENT_WAITMODE_CLR);
        if (event_bit & ALL_AUDIO_RECORD_FINISH_BIT) {
            break;
        }
        len = hi_min(AUDIO_RECORD_BUF_SIZE, total_record_len);

        ret = hi_flash_write(record_addr, len, g_record_data, HI_FALSE);
        if (ret != HI_ERR_SUCCESS) {
            i2s_print("==ERROR== hi_flash_write, err = %X\n", ret);
        }
        record_addr += len;
        total_record_len -= len;
    }

    i2s_print("Record success!...\n");
    hi_udelay(1000000); /* 1000000: delay 1s */

    audio_play(AUDIO_RECORD_AND_PLAY_MODE);
    i2s_print("Play record audio success!...\n");

    return HI_NULL;
}


hi_void audio_record_play(hi_u32 map_index)
{
    hi_u32 ret;

    hi_task_attr attr = {0};
    attr.stack_size = I2S_TEST_TASK_STAK_SIZE;
    attr.task_prio = I2S_TEST_TASK_PRIORITY;
    attr.task_name = (hi_char*)"audio_record";
    ret = hi_task_create(&g_audio_task_id, &attr, record_n_play_task, 0);
    if (ret != HI_ERR_SUCCESS) {
        i2s_print("Falied to create record task, err = %X\n", ret);
    }

    /* apply memory */
    g_audio_test.record_buf = (hi_u8 *) hi_malloc(HI_MOD_ID_DRV, AUDIO_RECORD_BUF_SIZE);
    if (g_audio_test.record_buf == HI_NULL) {
        hi_i2s_deinit();
        i2s_print("==ERROR== record buf malloc fail!!!\n");
        return;
    }
    memset_s(g_audio_test.record_buf, AUDIO_RECORD_BUF_SIZE, 0, AUDIO_RECORD_BUF_SIZE);

    i2s_print("==start record== please say somerthing~~\n");
    audio_record_func(map_index);
}

/*
 * i2s_demo: a simple demo implement paly audio file and record audio then play them back function.
 * -note: If it is in play mode, user need to burn the audio file to the specified location of flash in advance.
 *        max size of audio file: 100K bytes
 *        burn command:           burn 1A1000 19000
 */
hi_void i2s_demo(hi_void)
{
    hi_u32 ret;

    ret = hi_flash_init();
    if (ret == HI_ERR_FLASH_RE_INIT) {
        i2s_print("Flash has already been initialized!\n");
    } else if (ret != HI_ERR_SUCCESS) {
        i2s_print("Falied to init flash, err = %X\n", ret);
    }

    /* create I2S record event */
    ret = hi_event_create(&g_audio_event);
    if (ret != HI_ERR_SUCCESS) {
        i2s_print("Failed to init g_audio_event! err = %X\n", ret);
        return;
    }

    hi_codec_attribute codec_cfg = {
        .sample_rate = HI_CODEC_SAMPLE_RATE_8K,
        .resolution = HI_CODEC_RESOLUTION_16BIT,
    };
    hi_i2s_attribute i2s_cfg = {
        .sample_rate = HI_I2S_SAMPLE_RATE_8K,
        .resolution = HI_I2S_RESOLUTION_16BIT,
    };

    es8311_codec_init(&codec_cfg);

    ret = hi_i2s_init(&i2s_cfg);
    if (ret != HI_ERR_SUCCESS) {
        i2s_print("Failed to init i2s!\n");
        return;
    }

    i2s_print("I2s init success!\n");

    /* paly audio file */
    audio_play(AUDIO_PLAY_FIEL_MODE);

    hi_udelay(5000000); /* 5000000: delay 5s */

    /* record audio then play them back */
    audio_record_play(AUDIO_RECORD_AND_PLAY_MODE);
}

