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
#include "wifiiot_at.h"

#include <securec.h>
#include <stdarg.h>
#include "hal_wifiiot_at.h"
#include "wifiiot_errno.h"

#define AT_BUFF_LEN 512

unsigned int AtRegisterCmd(const AtCmdTbl *cmdTbl, unsigned short cmdNum)
{
    return HalAtRegisterCmd((HalAtCmdTbl *)cmdTbl, cmdNum);
}

void AtSysCmdRegister(void)
{
    HalAtSysCmdRegister();
}

int AtPrintf(const char *fmt, ...)
{
    va_list arg;
    int ret;
    char buf[AT_BUFF_LEN] = {0};

    if (memset_s(&arg, sizeof(va_list), 0, sizeof(va_list)) != EOK) {
        return WIFI_IOT_FAILURE;
    }
    va_start(arg, fmt);
    ret = vsprintf_s(buf, sizeof(buf), fmt, arg);
    va_end(arg);
    if (ret < 0) {
        return WIFI_IOT_FAILURE;
    }

    return HalAtPrintf(buf, strlen(buf));
}

unsigned int AtInit(void)
{
    return HalAtInit();
}

void AtCheckUartBusy(unsigned char enable)
{
    HalAtCheckUartBusy(enable);
}

