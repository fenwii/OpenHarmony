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

#include "ability_service.h"

#include <string.h>

#include "ability_list.h"
#include "ability_message_id.h"
#include "ability_record.h"
#include "ability_stack.h"
#include "appexecfwk_errors.h"

#include "cmsis_os.h"
#include "dmslite_msg_parser.h"
#include "js_app_host.h"
#include "los_task.h"
#include "los_task_pri.h"
#include "sys_status.h"
#include "utils.h"
#include "want.h"
extern "C" {
#include "pms.h"
#include "ui_sync.h"
}

using namespace OHOS::ACELite;

static void SetAppState(AppState appState);
constexpr char FORCESTOP_FLAG[] = "forcestop";
constexpr char SCREENOFF_FLAG[] = "screenoff";

namespace OHOS {
constexpr char LAUNCHER_BUNDLE_NAME[] = "com.huawei.launcher";
constexpr uint16_t LAUNCHER_TOKEN = 0;
constexpr int QUEUE_LENGTH = 32;
constexpr int SIZE_COEFFICIENT = 12;
constexpr int TASK_STACK_SIZE = 0x400 * SIZE_COEFFICIENT;
// name and token prefix
constexpr int ABILITY_INFO_HEADER = 16;
constexpr int ABILITY_TOKEN_LENGTH = 4;
constexpr int TERMINATE_TIMEOUT = 5000; // terminate timeout is 5 seconds
constexpr int LOS_PRIORITY_WIN = 8;

void AbilityService::ServiceMsgProcess(MC_MSG_S *msg)
{
    if (msg == nullptr) {
        HILOG_ERROR(HILOG_MODULE_AAFWK, "AbilityService::ServiceMsgProcess msg is null");
        return;
    }

    switch (msg->enId) {
        case AMS_SERVICE_INITED: {
            StartLauncher();
            break;
        }
        case AMS_START_ABILITY: {
            AbilitySvcInfo *info = static_cast<AbilitySvcInfo *>(msg->pMsgAllocBuf);
            if (info == nullptr) {
                break;
            }
            StartAbility(info);
            AdapterFree(info->bundleName);
            AdapterFree(info->path);
            AdapterFree(info->data);
            break;
        }
        case AMS_TERMINATE_ABILITY: {
            char *flag = static_cast<char *>(msg->pMsgAllocBuf);
            if (flag != nullptr) {
                if (strcmp(flag, FORCESTOP_FLAG) == 0) {
                    ForceStopAbility();
                } else if (strcmp(flag, SCREENOFF_FLAG) == 0) {
                    StopAbility();
                }
            } else {
                (void) TerminateAbility(msg->msgValue);
            }
            break;
        }
        case AMS_ONSTART: {
            OnStart(msg->msgValue);
            break;
        }
        case AMS_ONACTIVE: {
            OnActive(msg->msgValue);
            break;
        }
        case AMS_ONBACKGROUND: {
            OnBackground(msg->msgValue);
            break;
        }
        case AMS_ONDESTROY: {
            OnDestroy(msg->msgValue);
            break;
        }
        case AMS_BUTTON_EVENT: {
            if (msg->msgValue == 1) {
                HandleButtonEvent();
            }
            break;
        }
        case AMS_SENDMESSAGE: {
            FeatureAbilityDataInfo *dataInfo = static_cast<FeatureAbilityDataInfo *>(msg->pMsgAllocBuf);
            if (dataInfo == nullptr) {
                break;
            }
            (void) SendMsg(dataInfo);
            AdapterFree(dataInfo->bundleName);
            AdapterFree(dataInfo->message);
            AdapterFree(dataInfo->abilityName);
            AdapterFree(dataInfo->deviceID);
            break;
        }
        case AMS_REGISTER: {
            RegisterInfo *info = static_cast<RegisterInfo *>(msg->pMsgAllocBuf);
            if (info == nullptr) {
                break;
            }
            Register(info);
            AdapterFree(info->bundleName);
            break;
        }
        case AMS_UNREGISTER: {
            Unregister(static_cast<char *>(msg->pMsgAllocBuf));
            break;
        }
        case AMS_START_CHECK_RESPONSE: {
            CheckResponse(static_cast<char *>(msg->pMsgAllocBuf), (msg->msgValue == 0) ? false : true);
            break;
        }
        default: {
            break;
        }
    }
}

AbilityService::AbilityService()
{
    abilityList_ = new AbilityList();
    abilityStack_ = new AbilityStack();
    bundleRspTimer_ = {
        { "BundleRspTimer", 0, nullptr, 0 },
        (osTimerFunc_t)ForceStopAbilityProc,
        osTimerOnce,
        osTimerRousesIgnore,
        osTimerAlignIgnore
    };
}

AbilityService::~AbilityService()
{
    DeleteRecordInfo(LAUNCHER_TOKEN);
    delete abilityList_;
    delete abilityStack_;
}

void AbilityService::StartLauncher()
{
    auto record = new AbilityRecord();

    record->SetAppName(LAUNCHER_BUNDLE_NAME);
    abilityList_->Add(record);

    abilityStack_->PushAbility(record);
    record->SetState(SCHEDULE_ACTIVE);
    SetAppState(STATE_NATIVE_RUNNING);
}

void AbilityService::StartAbility(AbilitySvcInfo *info)
{
    if ((info == nullptr) || (info->bundleName == nullptr) || (strlen(info->bundleName) == 0)) {
        return;
    }

    auto topRecord = const_cast<AbilityRecord *>(abilityStack_->GetTopAbility());
    if ((topRecord == nullptr) || (topRecord->GetAppName() == nullptr)) {
        return;
    }
    uint16_t topToken = topRecord->GetToken();
    AbilityRecord *record = abilityList_->Get(info->bundleName);
    // application has been launched or running background
    if ((record != nullptr) && (record->IsAttached()) && (topToken != LAUNCHER_TOKEN)) {
        if (topRecord->GetState() == SCHEDULE_BACKGROUND) {
            if (strcmp(info->bundleName, topRecord->GetAppName()) == 0) {
                HILOG_INFO(HILOG_MODULE_AAFWK, "StartAbility Resume app when background.");
                TerminateAbility(LAUNCHER_TOKEN);
            }
            return;
        }
        if (strcmp(info->bundleName, LAUNCHER_BUNDLE_NAME) == 0) {
            HILOG_INFO(HILOG_MODULE_AAFWK, "Change Js app to background.");
            (void) SendMsgToJsAbility(BACKGROUND, topRecord);
        } else if (strcmp(info->bundleName, topRecord->GetAppName()) == 0) {
            HILOG_INFO(HILOG_MODULE_AAFWK, "Js app already started or starting.");
        } else {
            HILOG_WARN(HILOG_MODULE_AAFWK, "Other Js app already running, not allow start.");
            // application has not been launched and another application running foreground.
        }

        return;
    }

    BundleInfo bundleInfo = {};
    if (GetBundleInfo(info->bundleName, false, &bundleInfo) != ERR_OK) {
        HILOG_WARN(HILOG_MODULE_AAFWK, "Bundle not found, StartAbility failed.");
        return;
    }

    // application has not been launched and then to check priority and permission.
    PreCheckStartAbility(info->bundleName, info->path, info->data, info->dataLength);
}

int32_t AbilityService::TerminateAbility(uint16_t token)
{
    HILOG_INFO(HILOG_MODULE_AAFWK, "TerminateAbility [%u]", token);
    const AbilityRecord *record = abilityStack_->GetTopAbility();
    if (record == nullptr) {
        return -1;
    }
    uint16_t topToken =  record->GetToken();
    if (token == LAUNCHER_TOKEN) {
        if (record->GetState() == SCHEDULE_BACKGROUND) {
            HILOG_INFO(HILOG_MODULE_AAFWK, "Resume Js app [%u]", topToken);
            SetAppState(STATE_NATIVE_JUMP_JS);
            if (!SendMsgToLauncherAbility(nullptr, INVALID_EXIT, LAUNCHER_SCHEDULE_BACKGROUND)) {
                SetAppState(STATE_NATIVE_RUNNING);
                return -1;
            }
        }
        return 0;
    }

    if (token != topToken) {
        return -1;
    }
    StopBundleTimer();

    // Terminate ability when js starting
    if (GetAppState() == STATE_NATIVE_JUMP_JS) {
        HILOG_INFO(HILOG_MODULE_AAFWK, "Resume native again.");
        abilityStack_->PopAbility();
        DeleteRecordInfo(token);
        SetAppState(STATE_JS_JUMP_NATIVE);
        (void) SendMsgToLauncherAbility(nullptr, NORMAL_EXIT, LAUNCHER_SCHEDULE_ACTIVE);
        return 0;
    }

    SetAppState(STATE_JS_JUMP_NATIVE);
    if (!SendMsgToJsAbility(DESTORY, record)) {
        SetAppState(STATE_JS_RUNNING);
        return -1;
    }
    abilityStack_->PopAbility();
    return 0;
}

void AbilityService::AbortAbility(const char *bundleName)
{
    HILOG_INFO(HILOG_MODULE_AAFWK, "AbortAbility.");
    if (bundleName == nullptr) {
        return;
    }
    const AbilityRecord *topRecord = abilityStack_->GetTopAbility();
    if (topRecord == nullptr) {
        return;
    }
    uint16_t topToken = topRecord->GetToken();
    if ((topToken != LAUNCHER_TOKEN) && (strcmp(bundleName, topRecord->GetAppName()) == 0)) {
        (void) TerminateAbility(topToken);
    }
}

void AbilityService::StopAbility()
{
    const AbilityRecord *topRecord = abilityStack_->GetTopAbility();
    if (topRecord == nullptr) {
        return;
    }
    uint16_t topToken = topRecord->GetToken();
    if (topToken != LAUNCHER_TOKEN) {
        isLongTimeIdle_ = true;
        (void) TerminateAbility(topToken);
    }
}

void AbilityService::PreCheckStartAbility(
    const char *bundleName, const char *path, const void *data, uint16_t dataLength)
{
    if (path == nullptr) {
        return;
    }

    auto record = new AbilityRecord();
    record->SetToken(GenerateToken());
    record->SetAppName(bundleName);
    record->SetAppPath(path);
    record->SetAppData(data, dataLength);
    abilityList_->Add(record);

    if (!SendMsgToLauncherAbility(bundleName, INVALID_EXIT, AMS_START_CHECK_REQUEST)) {
        abilityList_->Erase(record->GetToken());
        delete record;
    }
}

void AbilityService::CheckResponse(const char *bundleName, bool isAllow)
{
    auto record = abilityList_->Get(bundleName);
    if (record == nullptr) {
        return;
    }

    if (!isAllow) {
        HILOG_INFO(HILOG_MODULE_AAFWK, "CheckResponse failed.");
        abilityList_->Erase(record->GetToken());
        delete record;
        return;
    }

    CreateAppTask(record);
}

void AbilityService::CreateAppTask(AbilityRecord *record)
{
    if ((record == nullptr) || (record->GetAppName() == nullptr)) {
        return;
    }

    HILOG_INFO(HILOG_MODULE_AAFWK, "CreateAppTask.");
    LOS_TaskLock();
    TSK_INIT_PARAM_S stTskInitParam;
    stTskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)(JsAppHost::JsAppTaskHandler);
    stTskInitParam.uwStackSize = TASK_STACK_SIZE;
    stTskInitParam.usTaskPrio = OS_TASK_PRIORITY_LOWEST - (UI_TASK_PRI - LOS_PRIORITY_WIN);
    stTskInitParam.pcName = "AppTask";
    stTskInitParam.uwResved = 0;
    auto jsAppHost = new JsAppHost();
    stTskInitParam.uwArg = reinterpret_cast<UINT32>((uintptr_t)jsAppHost);
    UINT32 appTaskId = 0;
    UINT32 res = LOS_TaskCreate(&appTaskId, &stTskInitParam);
    if (res != LOS_OK) {
        delete jsAppHost;
        LOS_TaskUnlock();
        return;
    }
    osMessageQueueId_t jsAppQueueId = osMessageQueueNew(QUEUE_LENGTH, sizeof(AbilityInnerMsg), nullptr);
    jsAppHost->SetMessageQueueId(jsAppQueueId);
    LOS_TaskUnlock();

    record->SetTaskId(appTaskId);
    record->SetMessageQueueId(jsAppQueueId);
    record->SetJsAppHost(jsAppHost);

    LoadPermissions(record->GetAppName(), appTaskId);

    SetAppState(STATE_NATIVE_JUMP_JS);
    if (!SendMsgToJsAbility(START_ABILITY, record)) {
        SetAppState(STATE_NATIVE_RUNNING);
        DeleteRecordInfo(record->GetToken());
    }
}

uint16_t AbilityService::GenerateToken()
{
    static uint16_t token = LAUNCHER_TOKEN;
    if (token == UINT16_MAX - 1) {
        token = LAUNCHER_TOKEN;
    }
    return ++token;
}

void AbilityService::DeleteRecordInfo(uint16_t token)
{
    AbilityRecord *record = abilityList_->Get(token);
    if (record == nullptr) {
        return;
    }
    if (token != LAUNCHER_TOKEN) {
        UINT32 taskId = record->GetTaskId();
        UnLoadPermissions(taskId);
        LOS_TaskDelete(taskId);
        osMessageQueueId_t jsAppQueueId = record->GetMessageQueueId();
        osMessageQueueDelete(jsAppQueueId);
        auto jsAppHost = const_cast<JsAppHost *>(record->GetJsAppHost());
        delete jsAppHost;
        // free all JS native memory after exiting it
        CleanTaskMem(taskId);
    }
    abilityList_->Erase(token);
    delete record;
}

void AbilityService::OnStart(uint16_t token)
{
    HILOG_INFO(HILOG_MODULE_AAFWK, "OnStart [%u]", token);
    if (token == LAUNCHER_TOKEN) {
        return;
    }
    AbilityRecord *record = abilityList_->Get(token);
    if (record == nullptr) {
        return;
    }
    StopBundleTimer();
    const AbilityRecord *topRecord = abilityStack_->GetTopAbility();
    if (topRecord == nullptr) {
        return;
    }

    if (topRecord->GetToken() != LAUNCHER_TOKEN) {
        return;
    }
    record->SetState(SCHEDULE_INACTIVE);
    abilityStack_->PushAbility(record);
    SetAppState(STATE_NATIVE_JUMP_JS);
    if (!SendMsgToLauncherAbility(record->GetAppName(), INVALID_EXIT, LAUNCHER_SCHEDULE_BACKGROUND)) {
        HILOG_INFO(HILOG_MODULE_AAFWK, "OnStart Fail to hide launcher");
        /* Fail to hide Launcher */
        DeleteRecordInfo(token);
        abilityStack_->PopAbility();
        SetAppState(STATE_NATIVE_RUNNING);
    }
}

void AbilityService::OnActive(uint16_t token)
{
    HILOG_INFO(HILOG_MODULE_AAFWK, "OnActive [%u]", token);
    auto topRecord = const_cast<AbilityRecord *>(abilityStack_->GetTopAbility());
    if (topRecord == nullptr) {
        return;
    }
    if (token != LAUNCHER_TOKEN) {
        topRecord->SetState(SCHEDULE_ACTIVE);
        SetAppState(STATE_JS_RUNNING);
        InnerSendMsg(topRecord);
        StopBundleTimer();
        return;
    }
    SetAppState(STATE_NATIVE_RUNNING);
    if (topRecord->GetToken() != LAUNCHER_TOKEN) {
        HILOG_INFO(HILOG_MODULE_AAFWK, "OnActive Fail to hide launcher");
        if (topRecord->GetState() != SCHEDULE_BACKGROUND) {
            /* Fail to hide Launcher */
            abilityStack_->PopAbility();
            DeleteRecordInfo(topRecord->GetToken());
        }
    }
}

void AbilityService::OnBackground(uint16_t token)
{
    HILOG_INFO(HILOG_MODULE_AAFWK, "OnBackground [%u]", token);
    auto topRecord = const_cast<AbilityRecord *>(abilityStack_->GetTopAbility());
    if (topRecord == nullptr) {
        return;
    }
    if (token != LAUNCHER_TOKEN) {
        StopBundleTimer();
        topRecord->SetState(SCHEDULE_BACKGROUND);
        SetAppState(STATE_JS_JUMP_NATIVE);
        if (!SendMsgToLauncherAbility(nullptr, ENTER_BACKGROUND, LAUNCHER_SCHEDULE_ACTIVE)) {
            SetAppState(STATE_JS_RUNNING);
        }
        return;
    }
    if (topRecord->GetToken() != LAUNCHER_TOKEN) {
        (void) SendMsgToJsAbility(ACTIVE, topRecord);
    } else {
        HILOG_WARN(HILOG_MODULE_AAFWK, "Js app exit, should start native again.");
        (void) SendMsgToLauncherAbility(nullptr, NORMAL_EXIT, LAUNCHER_SCHEDULE_ACTIVE);
    }
}

void AbilityService::OnDestroy(uint16_t token)
{
    HILOG_INFO(HILOG_MODULE_AAFWK, "OnDestroy [%u]", token);
    if (token == LAUNCHER_TOKEN) {
        return;
    }
    StopBundleTimer();
    DeleteRecordInfo(token);
    const AbilityRecord *topRecord = abilityStack_->GetTopAbility();
    if (topRecord == nullptr) {
        return;
    }
    uint16_t topToken = topRecord->GetToken();
    if (topToken == LAUNCHER_TOKEN) {
        AbilityExitReason reason = isBackPressed_ ? POWER_KEY_EXIT :
            (isLongTimeIdle_ ? LONG_TIME_IDLE_EXIT : NORMAL_EXIT);
        SetAppState(STATE_JS_JUMP_NATIVE);
        (void) SendMsgToLauncherAbility(nullptr, reason, LAUNCHER_SCHEDULE_ACTIVE);
    }
    isBackPressed_ = false;
    isLongTimeIdle_ = false;
}

void AbilityService::ForceStopAbilityProc(void *arg)
{
    GetInstance().ForceStopAbility();
}

void AbilityService::StartBundleTimer(void *arg)
{
    if (bundleRspTimerID_ == nullptr) {
        bundleRspTimerID_ = TimerCreate(&bundleRspTimer_, arg);
        if (bundleRspTimerID_ == nullptr) {
            return;
        }
    }

    osStatus_t result = osTimerStart(bundleRspTimerID_, TERMINATE_TIMEOUT);
    if (result != osOK) {
        return;
    }
}

void AbilityService::StopBundleTimer()
{
    if (bundleRspTimerID_ != nullptr) {
        (void)osTimerDelete(bundleRspTimerID_);
        bundleRspTimerID_ = nullptr;
    }
}

void AbilityService::ForceStopAbility()
{
    StopBundleTimer();

    const AbilityRecord *topRecord = abilityStack_->GetTopAbility();
    if (topRecord == nullptr) {
        return;
    }
    uint16_t token = topRecord->GetToken();
    if (token == LAUNCHER_TOKEN) {
        return;
    }
    HILOG_INFO(HILOG_MODULE_AAFWK, "ForceStopAbility [%u]", token);
    abilityStack_->PopAbility();

    UINT32 taskId = topRecord->GetTaskId();
    LOS_TaskSuspend(taskId);
    auto jsAppHost = const_cast<JsAppHost *>(topRecord->GetJsAppHost());
    if (jsAppHost != nullptr) {
        jsAppHost->ForceDestroy();
    }
    DeleteRecordInfo(token);

    topRecord = abilityStack_->GetTopAbility();
    if (topRecord == nullptr) {
        return;
    }
    uint16_t topToken = topRecord->GetToken();
    if (topToken == LAUNCHER_TOKEN) {
        SetAppState(STATE_JS_JUMP_NATIVE);
        AbilityExitReason reason = isBackPressed_ ? POWER_KEY_EXIT : FORCE_STOP_EXIT;
        (void) SendMsgToLauncherAbility(nullptr, reason, LAUNCHER_SCHEDULE_ACTIVE);
    }

    isBackPressed_ = false;
    isLongTimeIdle_ = false;
    bundleRspTimerID_ = nullptr;
}

void AbilityService::HandleButtonEvent()
{
    HILOG_INFO(HILOG_MODULE_AAFWK, "HandleButtonEvent");
    const AbilityRecord *topRecord = abilityStack_->GetTopAbility();
    if ((topRecord == nullptr) || (topRecord->GetToken() == LAUNCHER_TOKEN) ||
        (topRecord->GetState() == SCHEDULE_BACKGROUND)) {
        return;
    }

    // js app is not on foreground
    if (!IsScreenOn()) {
        if (IsScreenOning()) {
            SetScreenOn();
        }
        return;
    }
    isBackPressed_ = true;
    HILOG_INFO(HILOG_MODULE_AAFWK, "Trigger js BACKPRESSED");
    (void) SendMsgToJsAbility(BACKPRESSED, topRecord);
}

bool AbilityService::SendMsgToLauncherAbility(const char* bundleName, AbilityExitReason reason, unsigned int id)
{
    char *innerBundleName = nullptr;
    if (bundleName != nullptr) {
        innerBundleName = reinterpret_cast<char *>(SvrMalloc(strlen(bundleName) + 1));
        if (innerBundleName == nullptr) {
            return false;
        }
        if (strncpy_s(innerBundleName, strlen(bundleName) + 1, bundleName, strlen(bundleName)) != EOK) {
            SvrFree(innerBundleName);
            return false;
        }
    }
    if (AdapterSend((MC_MSG_ID_E) id, reason, innerBundleName) != MC_TRUE) {
        SvrFree(innerBundleName);
        return false;
    }
    return true;
}

bool AbilityService::SendMsgToJsAbility(AbilityMsgId msgId, const AbilityRecord *record)
{
    if (record == nullptr) {
        return false;
    }
    AbilityInnerMsg innerMsg;
    innerMsg.msgId = msgId;
    innerMsg.bundleName = record->GetAppName();
    innerMsg.token = record->GetToken();
    innerMsg.path = record->GetAppPath();
    innerMsg.data = const_cast<void *>(record->GetAppData());
    innerMsg.dataLength = record->GetDataLength();
    osMessageQueueId_t appQueueId = record->GetMessageQueueId();
    osStatus_t uwRet = osMessageQueuePut(appQueueId, reinterpret_cast<void *>(&innerMsg), 0, 0);
    if (uwRet != osOK) {
        return false;
    }
    if (!bundleRspTimerID_) {
        StartBundleTimer(reinterpret_cast<void *>((uintptr_t)record->GetToken()));
    }
    return true;
}

uint8_t AbilityService::DumpAbilityInfo(char **abilities)
{
    AbilityRecord *records = nullptr;
    int size = abilityStack_->GetAllAbilities(&records);
    if (size == 0) {
        if (records != nullptr) {
            delete [] records;
        }
        return -1;
    }

    int strLength = 1;
    for (int i = 0; i < size; i++) {
        if (records[i].GetAppName() == nullptr) {
            delete [] records;
            return -1;
        }
        strLength += strlen(records[i].GetAppName()) + ABILITY_TOKEN_LENGTH + ABILITY_INFO_HEADER;
    }

    *abilities = reinterpret_cast<char *>(AdapterMalloc(strLength));
    if (*abilities == nullptr) {
        if (records != nullptr) {
            delete [] records;
        }
        return -1;
    }

    (*abilities)[0] = '\0';
    for (int i = 0; i < size; i++) {
        int res = sprintf_s((*abilities) + strlen(*abilities), strLength - strlen(*abilities),
                            "appName:%s,token:%x;", records[i].GetAppName(), records[i].GetToken());
        if (res < 0) {
            AdapterFree(*abilities);
            delete [] records;
            return -1;
        }
    }

    if (records != nullptr) {
        delete [] records;
    }
    return 0;
}

void AbilityService::InnerSendMsg(AbilityRecord *record)
{
    if ((record == nullptr) || (record->GetAppName() == nullptr) || (record->GetAppData() == nullptr)) {
        return;
    }

    auto dataInfo = reinterpret_cast<FeatureAbilityDataInfo *>(AdapterMalloc(sizeof(FeatureAbilityDataInfo)));
    if (dataInfo == nullptr) {
        return;
    }
    dataInfo->bundleName = Utils::Strdup(record->GetAppName());
    dataInfo->message = Utils::Memdup(record->GetAppData(), record->GetDataLength());
    dataInfo->messageLength = record->GetDataLength();
    dataInfo->abilityName = nullptr;
    dataInfo->deviceID = nullptr;
    if ((dataInfo->bundleName != nullptr) && (dataInfo->message != nullptr)) {
        record->TriggerSuccessCallback(reinterpret_cast<void *>(dataInfo));
    }
    AdapterFree(dataInfo->bundleName);
    AdapterFree(dataInfo->message);
    AdapterFree(dataInfo);
    // Clear app data, avoid repeated send message once app register
    record->SetAppData(nullptr, 0);
}

void AbilityService::Register(RegisterInfo *info)
{
    HILOG_INFO(HILOG_MODULE_AAFWK, "Register message");
    if ((info == nullptr) || (info->bundleName == nullptr) || (info->success == nullptr) || (info->fail == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_AAFWK, "Register error argument");
        return;
    }
    AbilityRecord *record = abilityList_->Get(info->bundleName);
    if (record == nullptr) {
        return;
    }
    DMSLiteRegestToFileTrans(info->bundleName);
    record->SetRegiterState(true);
    record->SetSuccessCallback(info->success);
    record->SetFailCallback(info->fail);

    InnerSendMsg(record);
}

void AbilityService::Unregister(const char *bundleName)
{
    HILOG_INFO(HILOG_MODULE_AAFWK, "Unregister send message");
    if (bundleName == nullptr) {
        return;
    }
    AbilityRecord *record = abilityList_->Get(bundleName);
    if (record == nullptr) {
        return;
    }
    record->SetSuccessCallback(nullptr);
    record->SetFailCallback(nullptr);
    record->SetRegiterState(false);
}

int AbilityService::SendMsg(FeatureAbilityDataInfo *dataInfo)
{
    if ((dataInfo == nullptr) || (dataInfo->bundleName == nullptr) || (dataInfo->message == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_AAFWK, "SendMsg error argument");
        return -1;
    }
    auto topRecord = const_cast<AbilityRecord *>(abilityStack_->GetTopAbility());
    if ((topRecord == nullptr) || (topRecord->GetAppName() == nullptr)) {
        return -1;
    }
    uint16_t topToken = topRecord->GetToken();
    // js app has been launched
    if (topToken != LAUNCHER_TOKEN) {
        if (strcmp(dataInfo->bundleName, topRecord->GetAppName()) == 0) {
            HILOG_INFO(HILOG_MODULE_AAFWK, "SendMsg already running");
            if (!topRecord->GetRegiterState()) {
                return -1;
            }
            if (topRecord->GetState() == SCHEDULE_BACKGROUND) {
                topRecord->SetAppData(dataInfo->message, dataInfo->messageLength);
                return TerminateAbility(LAUNCHER_TOKEN);
            }
            topRecord->TriggerSuccessCallback((reinterpret_cast<void *>(dataInfo)));
            return 0;
        }

        HILOG_WARN(HILOG_MODULE_AAFWK, "SendMsg other app running, ignore this message");
        return -1;
    }
    // js app is not launched
    AbilityRecord *record = abilityList_->Get(dataInfo->bundleName);
    if (record != nullptr) {
        record->SetAppData(dataInfo->message, dataInfo->messageLength);
        return 0;
    }
    Want want = {};
    ElementName elementName = {};
    SetElementBundleName(&elementName, dataInfo->bundleName);
    SetWantElement(&want, elementName);
    AbilityInfo abilityInfo = {};
    QueryAbilityInfo(want, &abilityInfo);
    ClearElement(&elementName);
    ClearWant(&want);
    if ((abilityInfo.bundleName == nullptr) || (strlen(abilityInfo.bundleName) == 0) ||
        (abilityInfo.srcPath == nullptr) || (strlen(abilityInfo.srcPath) == 0)) {
        ClearAbilityInfo(&abilityInfo);
        return -1;
    }

    AbilitySvcInfo info = {
        .bundleName = abilityInfo.bundleName,
        .path = abilityInfo.srcPath,
        .data = dataInfo->message,
        .dataLength = (uint16_t) dataInfo->messageLength
    };

    StartAbility(&info);
    ClearAbilityInfo(&abilityInfo);
    return 0;
}

int32_t AbilityService::RegisterReceiver(const char *bundleName, SuccessCallback success, FailCallback fail)
{
    if ((bundleName == nullptr) || (success == nullptr) || (fail == nullptr)) {
        return -1;
    }
    RegisterInfo *info = reinterpret_cast<RegisterInfo *>(SvrMalloc(sizeof(RegisterInfo)));
    if (info == nullptr) {
        return -1;
    }
    info->bundleName = Utils::Strdup(bundleName);
    if (info->bundleName == nullptr) {
        SvrFree(info);
        return -1;
    }
    info->success = success;
    info->fail = fail;
    if (AdapterSend((MC_MSG_ID_E) AMS_REGISTER, 0, reinterpret_cast<void *>(info)) != MC_TRUE) {
        AdapterFree(info->bundleName);
        SvrFree(info);
        return -1;
    }
    return 0;
}

int32_t AbilityService::UnregisterReceiver(const char *bundleName)
{
    if ((bundleName == nullptr) || (abilityList_->Get(bundleName) == nullptr)) {
        return -1;
    }

    char *innerBundleName = reinterpret_cast<char *>(SvrMalloc(strlen(bundleName) + 1));
    if (innerBundleName == nullptr) {
        return -1;
    }
    if (strncpy_s(innerBundleName, strlen(bundleName) + 1, bundleName, strlen(bundleName)) != EOK) {
        SvrFree(innerBundleName);
        return -1;
    }

    if (AdapterSend((MC_MSG_ID_E) AMS_UNREGISTER, 0, reinterpret_cast<void *>(innerBundleName)) != MC_TRUE) {
        SvrFree(innerBundleName);
        return -1;
    }
    return 0;
}

int32_t AbilityService::SendMsgToPeerApp(bool isLocalMsg, const char *callingPkgName, const char *calledPkgName,
                                         const uint8_t *msgBody, uint32_t length)
{
    return DMSLiteSendP2PMsg((isLocalMsg ? MC_TRUE : MC_FALSE), callingPkgName, calledPkgName, msgBody, length);
}

AbilityState AbilityService::GetJsState(const char *bundleName) const
{
    auto topRecord = abilityStack_->GetTopAbility();
    if ((topRecord == nullptr) || (topRecord->GetToken() == LAUNCHER_TOKEN) ||
        (topRecord->GetAppName() == nullptr) ||
        ((bundleName != nullptr) && (strcmp(topRecord->GetAppName(), bundleName) != 0))) {
        return SCHEDULE_STOP;
    }

    return topRecord->GetState();
}
} // namespace OHOS

extern "C" {
static AppState g_appState = STATE_NATIVE_RUNNING;

void ABILITY_ServiceTaskInit(void)
{
    (void) AdapterSend((MC_MSG_ID_E) AMS_SERVICE_INITED, 0, nullptr);
}

void ABILITY_ServiceMsgProcess(MC_MSG_S *msg)
{
    OHOS::AbilityService::GetInstance().ServiceMsgProcess(msg);
}

int StartAbility(Want want)
{
    if (want.element == nullptr) {
        return -1;
    }
    char *bundleName = want.element->bundleName;
    if (bundleName == nullptr) {
        return -1;
    }

    OHOS::AbilitySvcInfo *info =
        reinterpret_cast<OHOS::AbilitySvcInfo *>(SvrMalloc(sizeof(OHOS::AbilitySvcInfo)));
    if (info == nullptr) {
        return -1;
    }

    if (strcmp(bundleName, OHOS::LAUNCHER_BUNDLE_NAME) == 0) {
        info->bundleName = OHOS::Utils::Strdup(bundleName);
        info->path = nullptr;
    } else {
        AbilityInfo abilityInfo = { nullptr, nullptr };
        QueryAbilityInfo(want, &abilityInfo);
        if ((abilityInfo.bundleName == nullptr) || (strlen(abilityInfo.bundleName) == 0) ||
            (abilityInfo.srcPath == nullptr) || (strlen(abilityInfo.srcPath) == 0)) {
            ClearAbilityInfo(&abilityInfo);
            SvrFree(info);
            return -1;
        }
        info->bundleName = OHOS::Utils::Strdup(abilityInfo.bundleName);
        info->path = OHOS::Utils::Strdup(abilityInfo.srcPath);
        ClearAbilityInfo(&abilityInfo);
    }

    info->data = OHOS::Utils::Memdup(want.data, want.dataLength);
    info->dataLength = want.dataLength;

    if (AdapterSend((MC_MSG_ID_E) AMS_START_ABILITY, 0, reinterpret_cast<void *>(info)) != MC_TRUE) {
        AdapterFree(info->bundleName);
        AdapterFree(info->data);
        AdapterFree(info->path);
        SvrFree(info);
        return -1;
    }
    return 0;
}

int TerminateAbility(uint16_t token)
{
    if (AdapterSend((MC_MSG_ID_E) AMS_TERMINATE_ABILITY, token, nullptr) != MC_TRUE) {
        return -1;
    }
    return 0;
}

void StopAbility()
{
    char *flag = reinterpret_cast<char *>(SvrMalloc(sizeof(SCREENOFF_FLAG)));
    if (flag == nullptr) {
        return;
    }
    if (strncpy_s(flag, sizeof(SCREENOFF_FLAG), SCREENOFF_FLAG, strlen(SCREENOFF_FLAG)) != EOK) {
        SvrFree(flag);
        return;
    }
    if (AdapterSend((MC_MSG_ID_E) AMS_TERMINATE_ABILITY, 0, reinterpret_cast<void *>(flag)) != MC_TRUE) {
        SvrFree(flag);
    }
}

int ForceStopAbility()
{
    char *flag = reinterpret_cast<char *>(SvrMalloc(sizeof(FORCESTOP_FLAG)));
    if (flag == nullptr) {
        return -1;
    }
    if (strncpy_s(flag, sizeof(FORCESTOP_FLAG), FORCESTOP_FLAG, strlen(FORCESTOP_FLAG)) != EOK) {
        SvrFree(flag);
        return -1;
    }
    if (AdapterSend((MC_MSG_ID_E) AMS_TERMINATE_ABILITY, 0, reinterpret_cast<void *>(flag)) != MC_TRUE) {
        SvrFree(flag);
        return -1;
    }
    return 0;
}

uint8_t DumpAbilityInfo(char **abilities)
{
    return OHOS::AbilityService::GetInstance().DumpAbilityInfo(abilities);
}

int AbilityTransactionDone(uint16_t token, int state)
{
    int ret = 0;
    switch (state) {
        case SCHEDULE_INITED:
            break;
        case SCHEDULE_INACTIVE:
            break;
        case SCHEDULE_ACTIVE:
            if (AdapterSend((MC_MSG_ID_E) AMS_ONACTIVE, token, nullptr) != MC_TRUE) {
                ret = -1;
            } else {
                ret = 0;
            }
            break;
        case SCHEDULE_STOP:
            break;
        case SCHEDULE_BACKGROUND:
            if (AdapterSend((MC_MSG_ID_E) AMS_ONBACKGROUND, token, nullptr) != MC_TRUE) {
                ret = -1;
            } else {
                ret = 0;
            }
            break;
        default:
            break;
    }
    return ret;
}

int SendMsg(const char *bundleName, const void *data, uint16_t dataLength)
{
    if ((bundleName == nullptr) || (data == nullptr)) {
        return -1;
    }
    OHOS::FeatureAbilityDataInfo *dataInfo =
        reinterpret_cast<OHOS::FeatureAbilityDataInfo *>(
            SvrMalloc(sizeof(OHOS::FeatureAbilityDataInfo)));
    if (dataInfo == nullptr) {
        return -1;
    }
    dataInfo->bundleName = OHOS::Utils::Strdup(bundleName);
    dataInfo->message = OHOS::Utils::Memdup(data, dataLength);
    dataInfo->messageLength = dataLength;
    dataInfo->abilityName = nullptr;
    dataInfo->deviceID = nullptr;
    if (AdapterSend((MC_MSG_ID_E) AMS_SENDMESSAGE, 0, reinterpret_cast<void *>(dataInfo)) != MC_TRUE) {
        AdapterFree(dataInfo->bundleName);
        AdapterFree(dataInfo->message);
        SvrFree(dataInfo);
        return -1;
    }
    return 0;
}

MC_VOID AbilityCheckResponse(const MC_CHAR *bundleName, bool isAllowed)
{
    if (bundleName == nullptr) {
        return;
    }
    char *innerBundleName = reinterpret_cast<char *>(SvrMalloc(strlen(bundleName) + 1));
    if (innerBundleName == nullptr ||
        strncpy_s(innerBundleName, strlen(bundleName) + 1, bundleName, strlen(bundleName)) != EOK) {
        SvrFree(innerBundleName);
        return;
    }

    if (AdapterSend((MC_MSG_ID_E) AMS_START_CHECK_RESPONSE, isAllowed ? 1 : 0, innerBundleName) != MC_TRUE) {
        SvrFree(innerBundleName);
        return;
    }
}

AbilityState GetJsState(const char *bundleName)
{
    return OHOS::AbilityService::GetInstance().GetJsState(bundleName);
}

static void SetAppState(AppState appState)
{
    HILOG_INFO(HILOG_MODULE_AAFWK, "SetAppState [%d]", (int) appState);
    g_appState = appState;
}

AppState GetAppState()
{
    return g_appState;
}
}
