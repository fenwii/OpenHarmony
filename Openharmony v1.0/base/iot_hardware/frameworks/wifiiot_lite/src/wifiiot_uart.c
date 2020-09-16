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

#include "wifiiot_uart.h"
#include "hal_wifiiot_uart.h"
#include "hal_wifiiot_uart_ex.h"

unsigned int UartInit(WifiIotUartIdx id, const WifiIotUartAttribute *param, const WifiIotUartExtraAttr *extraAttr)
{
    return HalUartInit((HalWifiIotUartIdx) id, (const HalWifiIotUartAttribute *)param,
                       (const HalWifiIotUartExtraAttr *)extraAttr);
}

int UartRead(WifiIotUartIdx id, unsigned char *data, unsigned int dataLen)
{
    return HalUartRead((HalWifiIotUartIdx) id, data, dataLen);
}

int UartWrite(WifiIotUartIdx id, const unsigned char *data, unsigned int dataLen)
{
    return HalUartWrite((HalWifiIotUartIdx) id, data, dataLen);
}

unsigned int UartDeinit(WifiIotUartIdx id)
{
    return HalUartDeinit((HalWifiIotUartIdx)id);
}

unsigned int UartSetFlowCtrl(WifiIotUartIdx id, WifiIotFlowCtrl flowCtrl)
{
    return HalUartSetFlowCtrl((HalWifiIotUartIdx)id, (HalWifiIotFlowCtrl)flowCtrl);
}

unsigned int UartIsBufEmpty(WifiIotUartIdx id, unsigned char *empty)
{
    return HalUartIsBufEmpty((HalWifiIotUartIdx)id, empty);
}

int UartWriteImmediately(WifiIotUartIdx id, const unsigned char *data, unsigned int dataLen)
{
    return HalUartWriteImmediately((HalWifiIotUartIdx)id, data, dataLen);
}

unsigned int UartGetAttribute(WifiIotUartIdx id, WifiIotUartAttribute *attr, WifiIotUartExtraAttr *extraAttr)
{
    return HalUartGetAttribute((HalWifiIotUartIdx)id, (HalWifiIotUartAttribute *)attr,
                               (HalWifiIotUartExtraAttr *)extraAttr);
}

unsigned int UartIsBusy(WifiIotUartIdx id, unsigned char *busy)
{
    return HalUartIsBusy((HalWifiIotUartIdx)id, busy);
}

