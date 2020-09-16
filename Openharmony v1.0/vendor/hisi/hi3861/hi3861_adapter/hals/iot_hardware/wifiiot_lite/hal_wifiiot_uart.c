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

#include "hal_wifiiot_uart.h"

#include <stdio.h>

#include "hi_uart.h"

unsigned int HalUartInit(HalWifiIotUartIdx id, const HalWifiIotUartAttribute *param,
                         const HalWifiIotUartExtraAttr *extraAttr)
{
    return hi_uart_init((hi_uart_idx)id, (const hi_uart_attribute *)param, (const hi_uart_extra_attr *)extraAttr);
}

int HalUartRead(HalWifiIotUartIdx id, unsigned char *data, unsigned int dataLen)
{
    return hi_uart_read((hi_uart_idx)id, data, dataLen);
}

int HalUartWrite(HalWifiIotUartIdx id, const unsigned char *data, unsigned int dataLen)
{
    return hi_uart_write((hi_uart_idx)id, data, dataLen);
}

unsigned int HalUartDeinit(HalWifiIotUartIdx id)
{
    return hi_uart_deinit((hi_uart_idx)id);
}

unsigned int HalUartSetFlowCtrl(HalWifiIotUartIdx id, HalWifiIotFlowCtrl flowCtrl)
{
    return hi_uart_set_flow_ctrl((hi_uart_idx)id, (hi_flow_ctrl)flowCtrl);
}

unsigned int HalUartIsBufEmpty(HalWifiIotUartIdx id, unsigned char *empty)
{
    return hi_uart_is_buf_empty((hi_uart_idx)id, (hi_bool *)empty);
}

int HalUartWriteImmediately(HalWifiIotUartIdx id, const unsigned char *data, unsigned int dataLen)
{
    return hi_uart_write_immediately((hi_uart_idx)id, data, dataLen);
}

unsigned int HalUartGetAttribute(HalWifiIotUartIdx id, HalWifiIotUartAttribute *attr,
                                 HalWifiIotUartExtraAttr *extraAttr)
{
    return hi_uart_get_attribute((hi_uart_idx)id, (hi_uart_attribute *)attr, (hi_uart_extra_attr *)extraAttr);
}

unsigned int HalUartIsBusy(HalWifiIotUartIdx id, unsigned char *busy)
{
    return hi_uart_is_busy((hi_uart_idx)id, (hi_bool *)busy);
}

