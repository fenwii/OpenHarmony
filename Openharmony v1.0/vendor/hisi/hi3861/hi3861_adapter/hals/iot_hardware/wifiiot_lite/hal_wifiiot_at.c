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
#include "hal_wifiiot_at.h"

#include <stdio.h>

#include "hi_at.h"

#include "hal_wifiiot_errno.h"

unsigned int HalAtRegisterCmd(const HalAtCmdTbl *cmdTbl, unsigned short cmdNum)
{
    return hi_at_register_cmd((at_cmd_func *)cmdTbl, cmdNum);
}

void HalAtSysCmdRegister(void)
{
    hi_at_sys_cmd_register();
}

int HalAtPrintf(const char *buf, int len)
{
    (void)len;
    return hi_at_printf("%s", buf);
}

unsigned int HalAtInit(void)
{
    return hi_at_init();
}

void HalAtCheckUartBusy(unsigned char enable)
{
    hi_at_set_check_uart_busy(enable);
}

