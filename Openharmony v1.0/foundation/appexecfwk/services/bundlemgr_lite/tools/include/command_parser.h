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

#ifndef FOUNDATION_APPEXECFWK_TOOLS_BM_INCLUDE_COMMAND_PARSER_H
#define FOUNDATION_APPEXECFWK_TOOLS_BM_INCLUDE_COMMAND_PARSER_H

#include "bundle_info_utils.h"

#include <stdint.h>
#include <string>

namespace OHOS {
class CommandParser {
public:
    CommandParser() = default;
    ~CommandParser() = default;

    void HandleCommands(int32_t argc, char *argv[]) const;
private:
    void RunAsInstallCommand(int32_t argc, char *argv[]) const;
    void RunAsUninstallCommand(int32_t argc, char *argv[]) const;
    void RunAsDumpCommand(int32_t argc, char *argv[]) const;
    void GetInstallBundleInfo(const std::string &bundleName) const;
    void GetInstallBundleInfos(int32_t argc) const;
    void GetBundleInfosByMetaDataKey(const std::string &metaDataKey) const;
    void InfoPrint(const std::string &str) const;
#ifdef OHOS_DEBUG
    void RunAsEnableCommand(int32_t argc, char *argv[]) const;
    void SetDebugMode(const std::string &enable, int32_t mode) const;
#endif
};
} // namespace OHOS
#endif // FOUNDATION_APPEXECFWK_TOOLS_BM_INCLUDE_COMMAND_PARSER_H
