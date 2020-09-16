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

#include "bundle_extractor.h"

#include "cJSON.h"

#include "appexecfwk_errors.h"
#include "bundle_common.h"
#include "bundle_util.h"
#include "extractor_util.h"
#include "log.h"

namespace OHOS {
uint8_t BundleExtractor::ExtractHapProfile(const std::string &hapFile, std::ostringstream &profileStream)
{
    ExtractorUtil extractorUtil(hapFile);
    if (!extractorUtil.Init()) {
        HILOG_ERROR(HILOG_MODULE_APP, "BundleExtractor ExtractHapProfile init fail");
        return ERR_APPEXECFWK_INSTALL_FAILED_EXTRACTOR_NOT_INIT;
    }

    if (!extractorUtil.ExtractFileByName(PROFILE_NAME, profileStream)) {
        HILOG_ERROR(HILOG_MODULE_APP, "it can not find json file!");
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PROFILE_ERROR;
    }
    return ERR_OK;
}
} // namespace OHOS
