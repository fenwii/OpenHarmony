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

#include "wifiiot_flash.h"
#include "hal_wifiiot_flash.h"

unsigned int FlashRead(const unsigned int flashOffset, const unsigned int size, unsigned char *ramData)
{
    return HalFlashRead(flashOffset, size, ramData);
}

unsigned int FlashWrite(const unsigned int flashOffset, unsigned int size,
                        const unsigned char *ramData, unsigned char doErase)
{
    return HalFlashWrite(flashOffset, size, ramData, doErase);
}

unsigned int FlashErase(const unsigned int flashOffset, const unsigned int size)
{
    return HalFlashErase(flashOffset, size);
}

unsigned int FlashInit(void)
{
    return HalFlashInit();
}

unsigned int FlashDeinit(void)
{
    return HalFlashDeinit();
}

unsigned int FlashIoctl(unsigned short cmd, char *data)
{
    return HalFlashIoctl(cmd, data);
}

