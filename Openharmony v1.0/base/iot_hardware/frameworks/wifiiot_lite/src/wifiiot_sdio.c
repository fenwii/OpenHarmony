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

#include "wifiiot_sdio.h"
#include "wifiiot_errno.h"
#include "hal_wifiiot_sdio.h"

unsigned int SdioInit(void)
{
    return HalSdioInit();
}

unsigned int SdioReinit(void)
{
    return HalSdioReinit();
}

void SdioSoftReset(void)
{
    HalSdioSoftReset();
}

unsigned int SdioRegisterCallback(const WifiIotSdioIntcallback *callbackFunc)
{
    return HalSdioRegisterCallback((const HalWifiIotSdioIntcallback *)callbackFunc);
}

unsigned int SdioCompleteSend(unsigned char *admaTable, unsigned int admaIndex)
{
    return HalSdioCompleteSend(admaTable, admaIndex);
}

unsigned int SdioSetPadAdmatab(unsigned int padlen, unsigned char *admatable, unsigned int admaIndex)
{
    return HalSdioSetPadAdmatab(padlen, admatable, admaIndex);
}

unsigned int SdioWriteExtinfo(WifiIotSdioExtendFunc *extFunc)
{
    return HalSdioWriteExtinfo((HalWifiIotSdioExtendFunc *)extFunc);
}

void SdioSendData(unsigned int xferBytes)
{
    return HalSdioSendData(xferBytes);
}

unsigned int SdioSetAdmatable(unsigned char *admatable, unsigned int admaIndex,
                              const unsigned int *dataAddr, unsigned int dataLen)
{
    return HalSdioSetAdmatable(admatable, admaIndex, dataAddr, dataLen);
}

unsigned int SdioSchedMsg(void)
{
    return HalSdioSchedMsg();
}

unsigned int SdioSendSyncMsg(unsigned int msg)
{
    return HalSdioSendSyncMsg(msg);
}

unsigned int SdioSendMsgAck(unsigned int msg)
{
    return HalSdioSendMsgAck(msg);
}

unsigned int SdioProcessMsg(unsigned int sendMsg, unsigned int clearMsg)
{
    return HalSdioProcessMsg(sendMsg, clearMsg);
}

unsigned int SdioIsPendingMsg(unsigned int msg)
{
    return HalSdioIsPendingMsg(msg);
}

unsigned int SdioIsSendingMsg(unsigned int msg)
{
    return HalSdioIsSendingMsg(msg);
}

WifiIotSdioExtendFunc *SdioGetExtendInfo(void)
{
    return (WifiIotSdioExtendFunc *)HalSdioGetExtendInfo();
}

void SdioRegisterNotifyMessageCallback(NotifyHostMessageEvent msgEventCallback)
{
    return HalSdioRegisterNotifyMessageCallback((HalNotifyHostMessageEvent)msgEventCallback);
}

void SdioSetPowerdownWhenDeepSleep(unsigned char powerDown)
{
    return HalSdioSetPowerdownWhenDeepSleep(powerDown);
}
