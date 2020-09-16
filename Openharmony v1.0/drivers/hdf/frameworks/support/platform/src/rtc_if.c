/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "hdf_base.h"
#include "hdf_log.h"
#include "devsvc_manager_clnt.h"
#include "osal_mem.h"
#include "rtc_base.h"
#include "rtc_core.h"
#include "rtc_if.h"

#define HDF_LOG_TAG rtc_if

static char *g_rtcServiceName = "HDF_PLATFORM_RTC";

struct DevHandle *RtcOpen()
{
    struct DevHandle *handle = NULL;
    struct RtcHost *host = NULL;

    host = (struct RtcHost *)DevSvcManagerClntGetService(g_rtcServiceName);
    if (host == NULL) {
        HDF_LOGE("rtc get service name failed");
        return NULL;
    }
    handle = OsalMemCalloc(sizeof(*handle));
    if (handle == NULL) {
        return NULL;
    }
    handle->object = host;
    return handle;
}

void RtcClose(struct DevHandle *handle)
{
    if (handle != NULL) {
        handle->object = NULL;
        OsalMemFree(handle);
    }
}

int32_t RtcReadTime(struct DevHandle *handle, struct RtcTime *time)
{
    struct RtcHost *host = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("RtcReadTime: handle is null");
        return HDF_ERR_INVALID_OBJECT;
    }
    host = (struct RtcHost *)handle->object;
    if (host->method == NULL || host->method->ReadTime == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->ReadTime(host, time);
}

int32_t RtcWriteTime(struct DevHandle *handle, const struct RtcTime *time)
{
    struct RtcHost *host = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("RtcWriteTime: handle is null");
        return HDF_ERR_INVALID_OBJECT;
    }

    if (RtcIsInvalid(time) == RTC_TRUE) {
        HDF_LOGE("RtcWriteTime: time invalid");
        return HDF_ERR_INVALID_PARAM;
    }

    host = (struct RtcHost *)handle->object;
    if (host->method == NULL || host->method->WriteTime == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->WriteTime(host, time);
}

int32_t RtcReadAlarm(struct DevHandle *handle, enum RtcAlarmIndex alarmIndex, struct RtcTime *time)
{
    struct RtcHost *host = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("RtcReadAlarm: handle is null");
        return HDF_ERR_INVALID_OBJECT;
    }

    host = (struct RtcHost *)handle->object;
    if (host->method == NULL || host->method->ReadAlarm == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->ReadAlarm(host, alarmIndex, time);
}

int32_t RtcWriteAlarm(struct DevHandle *handle, enum RtcAlarmIndex alarmIndex, const struct RtcTime *time)
{
    struct RtcHost *host = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("RtcWriteAlarm: handle is null");
        return HDF_ERR_INVALID_OBJECT;
    }

    if (RtcIsInvalid(time) == RTC_TRUE) {
        HDF_LOGE("RtcWriteAlarm: time invalid");
        return HDF_ERR_INVALID_PARAM;
    }

    host = (struct RtcHost *)handle->object;
    if (host->method == NULL || host->method->WriteAlarm == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->WriteAlarm(host, alarmIndex, time);
}

int32_t RtcRegisterAlarmCallback(struct DevHandle *handle, enum RtcAlarmIndex alarmIndex, RtcAlarmCallback cb)
{
    struct RtcHost *host = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("RtcRegisterAlarmCallback: handle is null");
        return HDF_ERR_INVALID_OBJECT;
    }
    host = (struct RtcHost *)handle->object;
    if (host->method == NULL || host->method->RegisterAlarmCallback == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->RegisterAlarmCallback(host, alarmIndex, cb);
}

int32_t RtcAlarmInterruptEnable(struct DevHandle *handle, enum RtcAlarmIndex alarmIndex, uint8_t enable)
{
    struct RtcHost *host = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("RtcAlarmInterruptEnable: handle is null");
        return HDF_ERR_INVALID_OBJECT;
    }
    host = (struct RtcHost *)handle->object;
    if (host->method == NULL || host->method->AlarmInterruptEnable == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->AlarmInterruptEnable(host, alarmIndex, enable);
}

int32_t RtcGetFreq(struct DevHandle *handle, uint32_t *freq)
{
    struct RtcHost *host = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("RtcGetFreq: handle is null");
        return HDF_ERR_INVALID_OBJECT;
    }
    host = (struct RtcHost *)handle->object;
    if (host->method == NULL || host->method->GetFreq == NULL) {
        HDF_LOGE("RtcGetFreq: pointer null");
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->GetFreq(host, freq);
}

int32_t RtcSetFreq(struct DevHandle *handle, uint32_t freq)
{
    struct RtcHost *host = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("RtcSetFreq: handle is null");
        return HDF_ERR_INVALID_OBJECT;
    }
    host = (struct RtcHost *)handle->object;
    if (host->method == NULL || host->method->SetFreq == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->SetFreq(host, freq);
}

int32_t RtcReset(struct DevHandle *handle)
{
    struct RtcHost *host = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("RtcReset: handle is null");
        return HDF_ERR_INVALID_OBJECT;
    }
    host = (struct RtcHost *)handle->object;
    if (host->method == NULL || host->method->Reset == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->Reset(host);
}

int32_t RtcReadReg(struct DevHandle *handle, uint8_t usrDefIndex, uint8_t *value)
{
    struct RtcHost *host = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("RtcReadReg: handle is null");
        return HDF_ERR_INVALID_OBJECT;
    }
    host = (struct RtcHost *)handle->object;
    if (host->method == NULL || host->method->ReadReg == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->ReadReg(host, usrDefIndex, value);
}

int32_t RtcWriteReg(struct DevHandle *handle, uint8_t usrDefIndex, uint8_t value)
{
    struct RtcHost *host = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("RtcReadReg: handle is null");
        return HDF_ERR_INVALID_OBJECT;
    }
    host = (struct RtcHost *)handle->object;
    if (host->method == NULL || host->method->WriteReg == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->WriteReg(host, usrDefIndex, value);
}
