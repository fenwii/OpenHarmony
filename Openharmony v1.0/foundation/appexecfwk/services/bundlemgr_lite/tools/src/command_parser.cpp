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

#include "command_parser.h"

#include <climits>
#include <cstdint>
#include <getopt.h>
#include <pthread.h>
#include <semaphore.h>

#include "adapter.h"
#include "appexecfwk_errors.h"
#include "bundle_info.h"
#include "bundle_inner_interface.h"
#include "bundle_manager.h"
#include "convert_utils.h"
#include "iproxy_client.h"
#include "liteipc_adapter.h"
#include "samgr_lite.h"
#include "securec.h"

namespace OHOS {
namespace {
const int32_t MIN_ARGUMENT_NUMBER = 2;
const int32_t MAX_ARGUMENT_NUMBER = 4;
const int32_t MAX_LOG_LEN = 1024;
const int32_t MAX_DUMP_LIST_NUMBER = 3;
const uint32_t INITIAL_CBID = 1;

static sem_t g_sem;
static IClientProxy *g_bmsInnerClient = nullptr;

const std::string CMD_INSTALL = "install";
const std::string CMD_UNINSTALL = "uninstall";
const std::string CMD_DUMP = "dump";
const std::string CMD_ENABLE = "set";

const std::string INSTALL_HELP_MESSAGE = "Usage: install hap-path [options]\n"
                                   "Description:\n"
                                   "\t--help|-h                   help menu\n"
                                   "\t--happath|-p           location of the hap to install\n";
const std::string UNINSTALL_HELP_MESSAGE = "Usage: uninstall bundle-name [options]\n"
                                     "Description:\n"
                                     "\t--help|-h                   help menu\n"
                                     "\t--bundlename|-n           name of the bundle to uninstall\n";
const std::string DUMP_HELP_MESSAGE = "Usage: dump [options]\n"
                                      "Option Description:\n"
                                      "\t--help|-h                   help menu\n"
                                      "\t--list|-l                   app list\n"
                                      "\t--bundlename|-n           dump installed hap's info\n"
                                      "\t--metadatakey|-m           dump bundleNames match metaData key\n";
const std::string ENABLE_HELP_MESSAGE = "Usage: set [options]\n"
                                        "Option Description:\n"
                                        "\t--externalmode|-e status    enable externalmode\n"
                                        "\t--debugmode|-d  status      enable debugmode\n"
                                        "\t--signmode|-s  status      enable signmode\n";

const std::string HELP_MESSAGE = INSTALL_HELP_MESSAGE + UNINSTALL_HELP_MESSAGE + DUMP_HELP_MESSAGE +
    ENABLE_HELP_MESSAGE;
const std::string ERROR_COMMAND = "error command!\n";
const std::string ERROR_OPTION = "error option!\n";
const std::string ERROR_INSTALL_PATH = "invalid path!\n";
const std::string ERROR_EXTRA_PARAMETER = "extra parameter!\n";
const std::string ERROR_SEM_ERROR = "sem init failed!\n";
const std::string ERROR_DUMP_FAIL = "no bundle info!\n";
const std::string ERROR_DUMP_ERROR = "dump info error!\n";

const std::string SHORT_OPTIONS = "n:hlp:m:";
const struct option LONG_OPTIONS[] = {
    {"help", no_argument, nullptr, 'h'},
    {"list", no_argument, nullptr, 'l'},
    {"bundlename", required_argument, nullptr, 'n'},
    {"happath", required_argument, nullptr, 'p'},
    {"metadatakey", required_argument, nullptr, 'm'},
    {nullptr, 0, nullptr, 0}
};

#ifdef OHOS_DEBUG
const std::string ENABLE_SHORT_OPTIONS = "he:d:s:";
const struct option ENABLE_LONG_OPTIONS[] = {
    {"help", no_argument, nullptr, 'h'},
    {"externalmode", required_argument, nullptr, 'e'},
    {"debugmode", required_argument, nullptr, 'd'},
    {"signmode", required_argument, nullptr, 's'},
    {nullptr, 0, nullptr, 0}
};
#endif

IClientProxy *GetBmsInnerClient()
{
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(BMS_SERVICE, BMS_INNER_FEATURE);
    if (iUnknown == nullptr) {
        return nullptr;
    }
    IClientProxy *bmsClient = nullptr;
    int result = iUnknown->QueryInterface(iUnknown, CLIENT_PROXY_VER, reinterpret_cast<void **>(&bmsClient));
    if (result != 0) {
        return nullptr;
    }
    return bmsClient;
}
} // namespace

void CommandParser::HandleCommands(int32_t argc, char *argv[]) const
{
    if (argc < MIN_ARGUMENT_NUMBER) {
        printf("%s\n", HELP_MESSAGE.c_str());
        return;
    }
    g_bmsInnerClient = GetBmsInnerClient();
    std::string cmd = argv[1];
    if (cmd == CMD_INSTALL) {
        RunAsInstallCommand(argc, argv);
    } else if (cmd == CMD_UNINSTALL) {
        RunAsUninstallCommand(argc, argv);
    } else if (cmd == CMD_DUMP) {
        RunAsDumpCommand(argc, argv);
#ifdef OHOS_DEBUG
    } else if (cmd == CMD_ENABLE) {
        RunAsEnableCommand(argc, argv);
#endif
    } else {
        printf("%s\n", (ERROR_COMMAND + HELP_MESSAGE).c_str());
    }
}

static void ReceiveCallback(const uint8_t resultCode, const void *resultMessage)
{
    std::string strMessage = reinterpret_cast<const char *>(resultMessage);
    if (!strMessage.empty()) {
        printf("resultMessage is %s\n", strMessage.c_str());
    }
    sem_post(&g_sem);
}

static int32 BmToolDeathNotify(const IpcContext* context, void *ipcMsg, IpcIo *data, void *arg)
{
    FreeBuffer(nullptr, ipcMsg);
    printf("error message: %s\n", "Bundle Manager Service is dead");
    exit(-1);
}

void CommandParser::RunAsInstallCommand(int32_t argc, char *argv[]) const
{
    if (argc > MAX_ARGUMENT_NUMBER) {
        printf("%s\n", (ERROR_EXTRA_PARAMETER + INSTALL_HELP_MESSAGE).c_str());
        return;
    }

    int32_t option;
    char realPath[PATH_MAX + 1] = { 0 };
    uint32_t cbId = INITIAL_CBID;
    SvcIdentity sid = SAMGR_GetRemoteIdentity(BMS_SERVICE, BMS_INNER_FEATURE);
    while ((option = getopt_long_only(argc, argv, SHORT_OPTIONS.c_str(), LONG_OPTIONS, nullptr)) != -1) {
        switch (option) {
            case 'h':
                printf("%s\n", INSTALL_HELP_MESSAGE.c_str());
                break;
            case 'p':
                if (sem_init(&g_sem, 0, 0)) {
                    printf("error message: %s\n", ERROR_SEM_ERROR.c_str());
                    return;
                }
                if (optarg == nullptr || strlen(optarg) > PATH_MAX) {
                    printf("error message: %s\n", ERROR_INSTALL_PATH.c_str());
                    return;
                }
                if (realpath(optarg, realPath) == nullptr) {
                    printf("error message: %s\n", ERROR_INSTALL_PATH.c_str());
                    return;
                }
                if (RegisteDeathCallback(nullptr, sid, BmToolDeathNotify, nullptr, &cbId) != LITEIPC_OK) {
                    printf("error message: %s\n", "death callback is registered unsuccessfully");
                    return;
                }
                Install(realPath, nullptr, ReceiveCallback);
                sem_wait(&g_sem);
                break;
            default:
                printf("%s\n", (ERROR_OPTION + INSTALL_HELP_MESSAGE).c_str());
                break;
        }
    }
}

void CommandParser::RunAsUninstallCommand(int32_t argc, char *argv[]) const
{
    if (argc > MAX_ARGUMENT_NUMBER) {
        printf("%s\n", (ERROR_EXTRA_PARAMETER + UNINSTALL_HELP_MESSAGE).c_str());
        return;
    }

    int32_t option;
    uint32_t cbId = INITIAL_CBID;
    SvcIdentity sid = SAMGR_GetRemoteIdentity(BMS_SERVICE, BMS_INNER_FEATURE);
    while ((option = getopt_long_only(argc, argv, SHORT_OPTIONS.c_str(), LONG_OPTIONS, nullptr)) != -1) {
        switch (option) {
            case 'h':
                printf("%s\n", UNINSTALL_HELP_MESSAGE.c_str());
                break;
            case 'n':
                if (sem_init(&g_sem, 0, 0)) {
                    printf("error message: %s\n", ERROR_SEM_ERROR.c_str());
                    return;
                }
                if (RegisteDeathCallback(nullptr, sid, BmToolDeathNotify, nullptr, &cbId) != LITEIPC_OK) {
                    printf("error message: %s\n", "death callback is registered unsuccessfully");
                    return;
                }
                Uninstall(optarg, nullptr, ReceiveCallback);
                sem_wait(&g_sem);
                break;
            default:
                printf("%s\n", (ERROR_OPTION + UNINSTALL_HELP_MESSAGE).c_str());
                break;
        }
    }
}

void CommandParser::RunAsDumpCommand(int32_t argc, char *argv[]) const
{
    if (argc > MAX_ARGUMENT_NUMBER) {
        printf("%s\n", (ERROR_EXTRA_PARAMETER + DUMP_HELP_MESSAGE).c_str());
        return;
    }

    int32_t option = getopt_long_only(argc, argv, SHORT_OPTIONS.c_str(), LONG_OPTIONS, nullptr);
    switch (option) {
        case 'h':
            printf("%s\n", DUMP_HELP_MESSAGE.c_str());
            break;
        case 'n':
            GetInstallBundleInfo(optarg);
            break;
        case 'l':
            GetInstallBundleInfos(argc);
            break;
        case 'm':
            GetBundleInfosByMetaDataKey(optarg);
            break;
        default:
            printf("%s\n", (ERROR_OPTION + DUMP_HELP_MESSAGE).c_str());
            break;
    }
}

#ifdef OHOS_DEBUG
void CommandParser::RunAsEnableCommand(int32_t argc, char *argv[]) const
{
    if (argc > MAX_ARGUMENT_NUMBER) {
        printf("%s\n", (ERROR_EXTRA_PARAMETER + ENABLE_HELP_MESSAGE).c_str());
        return;
    }

    int32_t option = getopt_long_only(argc, argv, ENABLE_SHORT_OPTIONS.c_str(), ENABLE_LONG_OPTIONS, nullptr);
    switch (option) {
        case 'h':
            printf("%s\n", ENABLE_HELP_MESSAGE.c_str());
            break;
        case 'd':
            SetDebugMode(optarg, SET_SIGN_DEBUG_MODE);
            break;
        case 'e':
            SetDebugMode(optarg, SET_EXTERNAL_INSTALL_MODE);
            break;
        case 's':
            SetDebugMode(optarg, SET_SIGN_MODE);
            break;
        default:
            printf("%s\n", (ERROR_OPTION + ENABLE_HELP_MESSAGE).c_str());
            break;
    }
}
#endif

void CommandParser::GetInstallBundleInfo(const std::string &bundleName) const
{
    BundleInfo bundleInfo;
    if (memset_s(&bundleInfo, sizeof(BundleInfo), 0, sizeof(BundleInfo)) != EOK) {
        printf("error message: %s\n", ERROR_DUMP_ERROR.c_str());
        return;
    }
    if (GetBundleInfo(bundleName.c_str(), 1, &bundleInfo) != HOS_SUCCESS) {
        printf("error message: %s\n", ERROR_DUMP_FAIL.c_str());
        return;
    }

    cJSON *root = ConvertUtils::GetJsonBundleInfo(&bundleInfo);
    if (root == nullptr) {
        ClearBundleInfo(&bundleInfo);
        printf("error message: %s\n", ERROR_DUMP_ERROR.c_str());
        return;
    }

    char *str = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    ClearBundleInfo(&bundleInfo);
    if (str != nullptr) {
        InfoPrint(str);
        cJSON_free(str);
        str = nullptr;
    } else {
        printf("error message: %s\n", ERROR_DUMP_ERROR.c_str());
    }
}

void CommandParser::InfoPrint(const std::string &str) const
{
    int32_t len = str.size();
    if (len == 0) {
        return;
    }
    int32_t times = len / MAX_LOG_LEN;
    int32_t remains = len % MAX_LOG_LEN;
    for (int32_t i = 0; i < times; i++) {
        printf("%s", str.substr(i * MAX_LOG_LEN, MAX_LOG_LEN).c_str());
    }
    printf("%s\n", str.substr(times * MAX_LOG_LEN, remains).c_str());
}

void CommandParser::GetInstallBundleInfos(int32_t argc) const
{
    if (argc > MAX_DUMP_LIST_NUMBER) {
        printf("error message: %s\n", ERROR_OPTION.c_str());
        return;
    }

    BundleInfo *bundleInfo = nullptr;
    int32_t len = 0;
    if (GetBundleInfos(1, &bundleInfo, &len) != HOS_SUCCESS) {
        printf("error message: %s\n", ERROR_DUMP_FAIL.c_str());
        return;
    }

    cJSON *root = ConvertUtils::GetJsonBundleInfos(&bundleInfo, len);
    if (root == nullptr) {
        printf("error message: %s\n", ERROR_DUMP_ERROR.c_str());
        BundleInfoUtils::FreeBundleInfos(bundleInfo, len);
        return;
    }

    char *str = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    BundleInfoUtils::FreeBundleInfos(bundleInfo, len);
    if (str != nullptr) {
        InfoPrint(str);
        cJSON_free(str);
        str = nullptr;
    } else {
        printf("error message: %s\n", ERROR_DUMP_ERROR.c_str());
    }
}

void CommandParser::GetBundleInfosByMetaDataKey(const std::string &metaDataKey) const
{
    int32_t len = 0;
    BundleInfo *bundleInfos = nullptr;

    if (metaDataKey.empty()) {
        printf("query param is invalid!\n");
        return;
    }
    if (GetBundleInfosByMetaData(metaDataKey.c_str(), &bundleInfos, &len) != HOS_SUCCESS) {
        printf("error message: %s\n", ERROR_DUMP_FAIL.c_str());
        return;
    }

    printf("bundleNames match metaData key, len: %d\n", len);
    for (int32_t i = 0; i < len; ++i) {
        printf("bundleName: %s", bundleInfos[i].bundleName);
        if (i != len - 1) {
            printf("%s\n", "; ");
        } else {
            printf("%s\n", "\n");
        }
    }
    BundleInfoUtils::FreeBundleInfos(bundleInfos, len);
}

#ifdef OHOS_DEBUG
static int BmsToolNotify(IOwner owner, int code, IpcIo *reply)
{
    if ((reply == nullptr) || (owner == nullptr)) {
        printf("%s\n", "Bm tool Notify ipc is nullptr");
        return HOS_FAILURE;
    }
    switch (IpcIoPopUint8(reply)) {
        case SET_EXTERNAL_INSTALL_MODE:
        case SET_SIGN_DEBUG_MODE:
        case SET_SIGN_MODE: {
            uint8_t *ret = reinterpret_cast<uint8_t *>(owner);
            *ret = IpcIoPopUint8(reply);
            break;
        }
        default: {
            break;
        }
    }
    return ERR_OK;
}

uint8_t SetMode(int32_t mode, bool enable)
{
    if (g_bmsInnerClient == nullptr) {
        printf("%s\n", "Bm tool client is nullptr");
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    IpcIo ipcIo;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&ipcIo, data, IPC_IO_DATA_MAX, 0);
    IpcIoPushBool(&ipcIo, enable);
    if (!IpcIoAvailable(&ipcIo)) {
        printf("%s\n", "Bm tool ipc failed");
        return ERR_APPEXECFWK_SERIALIZATION_FAILED;
    }
    uint8_t setModeResult = 0;
    int32_t ret = g_bmsInnerClient->Invoke(g_bmsInnerClient, mode, &ipcIo, &setModeResult, BmsToolNotify);
    if (ret != ERR_OK) {
        printf("Bm tool invoke failed: %d\n", ret);
        return ERR_APPEXECFWK_INVOKE_ERROR;
    }
    return setModeResult;
}

void CommandParser::SetDebugMode(const std::string &enable, int32_t mode) const
{
    bool isEnable = false;
    if (enable == "enable") {
        isEnable = true;
    } else if (enable == "disable") {
        isEnable =  false;
    } else {
        printf("%s\n", "wrong param");
        return;
    }
    uint8_t ret = SetMode(mode, isEnable);
    if (ret == 0) {
        printf("%s\n", "success");
    } else {
        printf("%s\n", "fail");
    }
}
#endif
} // namespace OHOS
