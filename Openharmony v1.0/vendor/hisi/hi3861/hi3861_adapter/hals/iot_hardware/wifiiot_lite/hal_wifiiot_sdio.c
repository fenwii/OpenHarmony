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

#include "hal_wifiiot_sdio.h"

#include <unistd.h>

#include "hi_sdio_device.h"
#include "hal_wifiiot_errno.h"

#define HAL_SDIO_INIT_TIMEOUT 20
#define HAL_SDIO_INIT_SLEEPTIME 1

unsigned int HalSdioInit(void)
{
    int timeOut = HAL_SDIO_INIT_TIMEOUT;

    while (timeOut) {
        if (hi_sdio_host_clk_ready()) {
            return hi_sdio_init();
        }
        timeOut--;
        sleep(HAL_SDIO_INIT_SLEEPTIME);
    }
    return HAL_WIFI_IOT_FAILURE;
}

unsigned int HalSdioReinit(void)
{
    int timeOut = HAL_SDIO_INIT_TIMEOUT;

    while (timeOut) {
        if (hi_sdio_host_clk_ready()) {
            return hi_sdio_reinit();
        }
        timeOut--;
        sleep(HAL_SDIO_INIT_SLEEPTIME);
    }
    return HAL_WIFI_IOT_FAILURE;
}

void HalSdioSoftReset(void)
{
    hi_sdio_soft_reset();
}

unsigned int HalSdioRegisterCallback(const HalWifiIotSdioIntcallback *callbackFunc)
{
    return hi_sdio_register_callback((const hi_sdio_intcallback *)callbackFunc);
}

unsigned int HalSdioCompleteSend(unsigned char *admaTable, unsigned int admaIndex)
{
    return hi_sdio_complete_send(admaTable, admaIndex);
}

unsigned int HalSdioSetPadAdmatab(unsigned int padlen, unsigned char *admatable, unsigned int admaIndex)
{
    return hi_sdio_set_pad_admatab(padlen, admatable, admaIndex);
}

unsigned int HalSdioWriteExtinfo(HalWifiIotSdioExtendFunc *extFunc)
{
    return hi_sdio_write_extendinfo((hi_sdio_extendfunc *)extFunc);
}

void HalSdioSendData(unsigned int xferBytes)
{
    return hi_sdio_send_data(xferBytes);
}

unsigned int HalSdioSetAdmatable(unsigned char *admatable, unsigned int admaIndex,
                                 const unsigned int *dataAddr, unsigned int dataLen)
{
    return hi_sdio_set_admatable(admatable, admaIndex, dataAddr, dataLen);
}

unsigned int HalSdioSchedMsg(void)
{
    return hi_sdio_sched_msg();
}

unsigned int HalSdioSendSyncMsg(unsigned int msg)
{
    return hi_sdio_send_sync_msg(msg);
}

unsigned int HalSdioSendMsgAck(unsigned int msg)
{
    return hi_sdio_send_msg_ack(msg);
}

unsigned int HalSdioProcessMsg(unsigned int sendMsg, unsigned int clearMsg)
{
    return hi_sdio_process_message(sendMsg, clearMsg);
}

unsigned int HalSdioIsPendingMsg(unsigned int msg)
{
    return hi_sdio_is_pending_message(msg);
}

unsigned int HalSdioIsSendingMsg(unsigned int msg)
{
    return hi_sdio_is_sending_message(msg);
}

HalWifiIotSdioExtendFunc *HalSdioGetExtendInfo(void)
{
    return (HalWifiIotSdioExtendFunc *)hi_sdio_get_extend_info();
}

void HalSdioRegisterNotifyMessageCallback(HalNotifyHostMessageEvent msgEventCallback)
{
    return hi_sdio_register_notify_message_callback(msgEventCallback);
}

void HalSdioSetPowerdownWhenDeepSleep(unsigned char powerDown)
{
    return hi_sdio_set_powerdown_when_deep_sleep(powerDown);
}
