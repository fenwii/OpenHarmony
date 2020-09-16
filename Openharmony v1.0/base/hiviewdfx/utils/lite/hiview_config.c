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

#include "hos_types.h"
#include "hos_init.h"
#include "hiview_log.h"
#include "hiview_config.h"

HiviewConfig g_hiviewConfig = {
    .outputOption = OUTPUT_OPTION_FLOW,
    .level = HILOG_LV_DEBUG,
    .logSwitch = HIVIEW_FEATURE_ON,
    .dumpSwitch = HIVIEW_FEATURE_OFF,
    .eventSwitch = HIVIEW_FEATURE_OFF,
};

static void HiviewConfigInit(void)
{
    g_hiviewConfig.hiviewInited = FALSE;
    g_hiviewConfig.logOutputModule = 0xFFFFFFFFFFFFFFFF;
    g_hiviewConfig.writeFailureCount = 0;
}
CORE_INIT_PRI(HiviewConfigInit, 0);

boolean SetLogLevel(uint8 level)
{
    if (level >= HILOG_LV_DEBUG && level < HILOG_MODULE_MAX) {
        g_hiviewConfig.level = level;
        return TRUE;
    }
    return FALSE;
}

void SwitchLog(uint8 flag)
{
    (flag == HIVIEW_FEATURE_ON) ? (g_hiviewConfig.logSwitch = HIVIEW_FEATURE_ON) :
    (g_hiviewConfig.logSwitch = HIVIEW_FEATURE_OFF);
}

void SwitchEvent(uint8 flag)
{
    (flag == HIVIEW_FEATURE_ON) ? (g_hiviewConfig.eventSwitch = HIVIEW_FEATURE_ON) :
    (g_hiviewConfig.eventSwitch = HIVIEW_FEATURE_OFF);
}

void SwitchDump(uint8 flag)
{
    (flag == HIVIEW_FEATURE_ON) ? (g_hiviewConfig.dumpSwitch = HIVIEW_FEATURE_ON) :
    (g_hiviewConfig.dumpSwitch = HIVIEW_FEATURE_OFF);
}

boolean OpenLogOutputModule(uint8 mod)
{
    if (mod < HILOG_MODULE_MAX) {
        g_hiviewConfig.logOutputModule |= (1 << mod);
        return TRUE;
    }
    return FALSE;
}

boolean CloseLogOutputModule(uint8 mod)
{
    if (mod < HILOG_MODULE_MAX) {
        g_hiviewConfig.logOutputModule &= (~(1 << mod));
        return TRUE;
    }
    return FALSE;
}

boolean SetLogOutputModule(uint8 mod)
{
    if (mod < HILOG_MODULE_MAX) {
        g_hiviewConfig.logOutputModule &= (1 << mod);
        return TRUE;
    } else if (mod == HILOG_MODULE_MAX) {
        g_hiviewConfig.logOutputModule = 0xFFFFFFFFFFFFFFFF;
        return TRUE;
    } else {
        return FALSE;
    }
}