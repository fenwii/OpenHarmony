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

#include "ability_thread.h"

#include <ability.h>
#include <ability_kit_command.h>
#include <ability_service_interface.h>
#include <ability_state.h>
#include <climits>
#include <cstring>
#ifdef ABILITY_WINDOW_SUPPORT
#include <common/graphic_startup.h>
#include <common/task_manager.h>
#include <common/screen_device_proxy.h>
#include <font/ui_font_header.h>
#include <sys/prctl.h>
#endif
#include <dlfcn.h>
#include <kvstore_env.h>

#include "ability_env.h"
#include "ability_env_impl.h"
#include "ability_info.h"
#include "ability_loader.h"
#include "ability_service_interface.h"
#include "adapter.h"
#include "element_name_utils.h"
#include "liteipc_adapter.h"
#include "log.h"

namespace OHOS {
namespace {
constexpr static char PATH_SEPARATOR[] = "/";
constexpr static char LIB_PREFIX[] = "/lib";
constexpr static char LIB_SUFFIX[] = ".so";
constexpr static char ACE_LIB_PATH[] = "/usr/lib/libace_lite.so";
constexpr static char ACE_ABILITY_NAME[] = "AceAbility";
#ifdef ABILITY_WINDOW_SUPPORT
constexpr static char FONT_PATH[] = "/storage/data/";
constexpr static char FONT_NAME[] = "SourceHanSansSC-Regular.otf";
constexpr static int UI_TASK_HANDLER_PERIOD = 10 * 1000; // UI task sleep period is 10ms
constexpr static char UI_TASK_THREAD_NAME[] = "UITaskPost";
static uint32_t g_fontPsramBaseAddr[MIN_FONT_PSRAM_LENGTH / 4];
#endif
}
bool AbilityThread::isAppRunning_ = true;
bool AbilityThread::isNativeApp_ = true;
bool AbilityThread::isDisplayInited_ = false;

AbilityThread::~AbilityThread()
{
    AdapterFree(identity_);
    delete abilityScheduler_;
    abilityScheduler_ = nullptr;
    delete eventHandler_;
    eventHandler_ = nullptr;
}

void AbilityThread::ThreadMain(uint64_t token)
{
    HILOG_INFO(HILOG_MODULE_APP, "AbilityThread::ThreadMain enter");

    AbilityThread abilityThread;
    abilityThread.AttachBundle(token);

    HILOG_INFO(HILOG_MODULE_APP, "AbilityThread::ThreadMain start loop");
    abilityThread.Run();
}

#ifdef ABILITY_WINDOW_SUPPORT
void *AbilityThread::UITaskPost(void *arg)
{
    prctl(PR_SET_NAME, UI_TASK_THREAD_NAME);

    auto handler = static_cast<AbilityEventHandler *>(arg);
    if (handler == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "EventHandler is nullptr, fail to start loop");
        return nullptr;
    }

    int ret = pthread_detach(pthread_self());
    if (ret != 0) {
        HILOG_WARN(HILOG_MODULE_APP, "UITaskPost detach failed: %{public}d", ret);
    }

    HILOG_INFO(HILOG_MODULE_APP, "start UITaskPost loop");
    while (isAppRunning_) {
        handler->PostTask([] {
            TaskManager::GetInstance()->TaskHandler();
        });
        usleep(UI_TASK_HANDLER_PERIOD);
    }
    return nullptr;
}

void AbilityThread::InitUITaskEnv()
{
    if (isDisplayInited_) {
        return;
    }

    HILOG_INFO(HILOG_MODULE_APP, "Hal and UI init");
    GraphicStartUp::Init();
    GraphicStartUp::InitFontEngine(reinterpret_cast<uintptr_t>(g_fontPsramBaseAddr), MIN_FONT_PSRAM_LENGTH,
        const_cast<char *>(FONT_PATH), const_cast<char *>(FONT_NAME));
    auto screenDevice = new ScreenDevice();
    ScreenDeviceProxy::GetInstance()->SetDevice(screenDevice);

    HILOG_INFO(HILOG_MODULE_APP, "Create UITaskPost thread");
    pthread_t tid;
    int ret = pthread_create(&tid, nullptr, AbilityThread::UITaskPost, eventHandler_);
    if (ret != 0) {
        HILOG_ERROR(HILOG_MODULE_APP, "create UI post thread error, %{public}d", ret);
        exit(-1);
    }
    isDisplayInited_ = true;
}
#endif

void AbilityThread::StartAbilityCallback(const Want &want)
{
    if ((want.sid == nullptr) || (want.element == nullptr)) {
        return;
    }
    HILOG_INFO(HILOG_MODULE_APP, "start ability callback");
    IpcIo io;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&io, data, IPC_IO_DATA_MAX, 0);
    if (!SerializeElement(&io, want.element)) {
        return;
    }
    IpcIoPushInt32(&io, EC_SUCCESS);
    if (Transact(nullptr, *(want.sid), SCHEDULER_APP_INIT, &io, nullptr, LITEIPC_FLAG_ONEWAY, nullptr) != LITEIPC_OK) {
        HILOG_ERROR(HILOG_MODULE_APP, "start ability callback failed, ipc error");
    }
}

void AbilityThread::PerformAppInit(const AppInfo &appInfo)
{
    HILOG_INFO(HILOG_MODULE_APP, "Start app init");
    if ((appInfo.bundleName.empty()) || (appInfo.srcPath.empty())) {
        HILOG_ERROR(HILOG_MODULE_APP, "appInfo is null");
        return;
    }
    if (!appInfo.isNativeApp && (appInfo.moduleNames.size() != 1)) {
        HILOG_ERROR(HILOG_MODULE_APP, "only native app support multi hap");
        return;
    }
    AbilityEnvImpl::GetInstance().SetAppInfo(appInfo);
    AbilityThread::isNativeApp_ = appInfo.isNativeApp;

    for (const auto &module : appInfo.moduleNames) {
        std::string modulePath;
        if (appInfo.isNativeApp) {
            modulePath = appInfo.srcPath + PATH_SEPARATOR + module + LIB_PREFIX + module + LIB_SUFFIX;
            if (modulePath.size() > PATH_MAX) {
                continue;
            }
            char realPath[PATH_MAX + 1] = { 0 };
            if (realpath(modulePath.c_str(), realPath) == nullptr) {
                continue;
            }
            modulePath = realPath;
        } else {
            modulePath = ACE_LIB_PATH;
        }
        void *handle = dlopen(modulePath.c_str(), RTLD_NOW | RTLD_GLOBAL);
        if (handle == nullptr) {
            HILOG_ERROR(HILOG_MODULE_APP, "Fail to dlopen %{public}s, [%{public}s]", modulePath.c_str(), dlerror());
            exit(-1);
        }
        handle_.emplace_front(handle);
    }

    int ret = UtilsSetEnv(GetDataPath());
    HILOG_INFO(HILOG_MODULE_APP, "Set env ret: %{public}d, App init end", ret);
}

void AbilityThread::PerformAppExit()
{
    HILOG_INFO(HILOG_MODULE_APP, "perform app exit");
    eventHandler_->PostTask([] {
        AbilityThread::isAppRunning_ = false;
    });
    for (auto handle : handle_) {
        dlclose(handle);
    }
    eventHandler_->PostQuit();
    handle_.clear();
}

void AbilityThread::PerformTransactAbilityState(const Want &want, int state, uint64_t token, int abilityType)
{
    HILOG_INFO(HILOG_MODULE_APP, "perform transact ability state to [%{public}d]", state);
    Ability *ability = nullptr;
    auto iter = abilities_.find(token);
    if ((iter == abilities_.end()) || (iter->second == nullptr)) {
        if (want.element == nullptr) {
            HILOG_ERROR(HILOG_MODULE_APP, "element name is null, fail to load ability");
            AbilityMsClient::GetInstance().SchedulerLifecycleDone(token, STATE_INITIAL);
            return;
        }
        auto abilityName = isNativeApp_ ? want.element->abilityName : ACE_ABILITY_NAME;
        ability = AbilityLoader::GetInstance().GetAbilityByName(abilityName);
        if (ability == nullptr) {
            HILOG_ERROR(HILOG_MODULE_APP, "fail to load ability: %{public}s", abilityName);
            AbilityMsClient::GetInstance().SchedulerLifecycleDone(token, STATE_INITIAL);
            return;
        }
        HILOG_INFO(HILOG_MODULE_APP, "Create ability success [%{public}s]", want.element->abilityName);

        // Only page ability need to init display
#ifdef ABILITY_WINDOW_SUPPORT
        if (abilityType == PAGE) {
            InitUITaskEnv();
        }
#endif
        ability->Init(token, abilityType, AbilityThread::isNativeApp_);
        abilities_[token] = ability;
    } else {
        ability = iter->second;
    }

    if (ability->GetState() != state) {
        HandleLifecycleTransaction(*ability, want, state);
    }

    HILOG_INFO(HILOG_MODULE_APP, "perform transact ability state done [%{public}d]", ability->GetState());
    AbilityMsClient::GetInstance().SchedulerLifecycleDone(token, ability->GetState());
    if (ability->GetState() == STATE_ACTIVE) {
        StartAbilityCallback(want);
    }

    if (ability->GetState() == STATE_INITIAL) {
        abilities_.erase(token);
        delete ability;
    }
}

void AbilityThread::PerformConnectAbility(const Want &want, uint64_t token)
{
    auto iter = abilities_.find(token);
    if (iter == abilities_.end() || iter->second == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "app has been stopped");
        return;
    }
    const SvcIdentity *sid = iter->second->OnConnect(want);
    AbilityMsClient::GetInstance().ScheduleAms(nullptr, token, sid, CONNECT_ABILITY_DONE);
}

void AbilityThread::PerformDisconnectAbility(const Want &want, uint64_t token)
{
    auto iter = abilities_.find(token);
    if (iter == abilities_.end() || iter->second == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "app has been stopped");
        return;
    }
    iter->second->OnDisconnect(want);
    AbilityMsClient::GetInstance().ScheduleAms(nullptr, token, nullptr, DISCONNECT_ABILITY_DONE);
}

void AbilityThread::PerformDumpAbility(const Want &want, uint64_t token)
{
    auto iter = abilities_.find(token);
    if (iter == abilities_.end() || iter->second == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "app has been stopped");
        return;
    }
    if (want.sid == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "SvcIdentity is null, dump failed");
        return;
    }
    std::string extra("");
    if (want.data != nullptr) {
        auto str = static_cast<char *>(want.data);
        if (want.dataLength == strlen(str) + 1) {
            extra = str;
        }
    }
    iter->second->Dump(extra);
    std::string dumpInfo = iter->second->GetDumpInfo();
    IpcIo io;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&io, data, IPC_IO_DATA_MAX, 1);
    BuffPtr dataBuff = {
            .buffSz = dumpInfo.length() + 1, // include \0
            .buff = const_cast<char *>(dumpInfo.c_str()),
    };
    IpcIoPushDataBuff(&io, &dataBuff);
    if (Transact(nullptr, *(want.sid), SCHEDULER_DUMP_ABILITY, &io, nullptr, LITEIPC_FLAG_ONEWAY, nullptr) != LITEIPC_OK) {
        HILOG_ERROR(HILOG_MODULE_APP, "dump ability failed, ipc error");
    }
}

void AbilityThread::HandleLifecycleTransaction(Ability &ability, const Want &want, int state)
{
    // Switch INITIAL state to INACTIVE state
    if (ability.GetState() == STATE_INITIAL) {
        ability.OnStart(want);
    }

    // Switch ACTIVE state to INACTIVE state
    if (ability.GetState() == STATE_ACTIVE) {
        ability.OnInactive();
    }

    switch (state) {
        case STATE_INITIAL: {
            if (ability.GetState() == STATE_INACTIVE) {
                ability.OnBackground();
            }
            ability.OnStop();
            break;
        }
        case STATE_INACTIVE: {
            // Not support transact from BACKGROUND to INACTIVE state
            break;
        }
        case STATE_ACTIVE: {
            ability.OnActive(want);
            break;
        }
        case STATE_BACKGROUND: {
            if (ability.GetState() == STATE_INACTIVE) {
                ability.OnBackground();
            }
            break;
        }
        default: {
            HILOG_ERROR(HILOG_MODULE_APP, "Unknown target state: %{public}d", state);
            break;
        }
    }
}

void AbilityThread::AttachBundle(uint64_t token)
{
    eventHandler_ = new AbilityEventHandler();
    abilityScheduler_ = new AbilityScheduler(*eventHandler_, *this);
    if (!AbilityMsClient::GetInstance().Initialize()) {
        HILOG_ERROR(HILOG_MODULE_APP, "ams feature is null");
        return;
    }

    identity_ = static_cast<SvcIdentity *>(AdapterMalloc(sizeof(SvcIdentity)));
    if (identity_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "ams identity is null");
        return;
    }
    int32_t ret = RegisteIpcCallback(AbilityScheduler::AmsCallback, 0, IPC_WAIT_FOREVER, identity_, abilityScheduler_);
    if (ret != 0) {
        HILOG_ERROR(HILOG_MODULE_APP, "RegisterIpcCallback failed");
        AdapterFree(identity_);
        return;
    }

    AbilityMsClient::GetInstance().ScheduleAms(nullptr, token, identity_, ATTACH_BUNDLE);
}

void AbilityThread::Run()
{
    eventHandler_->Run();
}
} //  namespace OHOS
