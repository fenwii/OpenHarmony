/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
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

#include <stdio.h>
#include "hal_wifiiot_flash.h"
#include "hi_flash.h"

unsigned int HalFlashRead(const unsigned int flashOffset, const unsigned int size, unsigned char *ramData)
{
    return hi_flash_read(flashOffset, size, ramData);
}

unsigned int HalFlashWrite(const unsigned int flashOffset, unsigned int size,
                           const unsigned char *ramData, unsigned char doErase)
{
    return hi_flash_write(flashOffset, size, ramData, doErase);
}

unsigned int HalFlashErase(const unsigned int flashOffset, const unsigned int size)
{
    return hi_flash_erase(flashOffset, size);
}

unsigned int HalFlashInit(void)
{
    return hi_flash_init();
}

unsigned int HalFlashDeinit(void)
{
    return hi_flash_deinit();
}

unsigned int HalFlashIoctl(unsigned short cmd, char *data)
{
    return hi_flash_ioctl(cmd, data);
}

