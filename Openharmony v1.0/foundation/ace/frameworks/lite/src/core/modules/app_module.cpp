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

#include "app_module.h"
#include "ace_log.h"
#include "js_app_context.h"

namespace OHOS {
namespace ACELite {
const char * const AppModule::FILE_MANIFEST = "manifest.json";
const char * const AppModule::KEY_APP_NAME = "appName";
const char * const AppModule::KEY_VERSION_NAME = "versionName";
const char * const AppModule::KEY_VERSION_CODE = "versionCode";

JSIValue AppModule::GetInfo(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue result = JSI::CreateUndefined();

    cJSON *manifest = ReadManifest();
    if (manifest == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Fail to get the content of manifest.");
        return result;
    }

    cJSON *appName = cJSON_GetObjectItem(manifest, KEY_APP_NAME);
    cJSON *versionName = cJSON_GetObjectItem(manifest, KEY_VERSION_NAME);
    cJSON *versionCode = cJSON_GetObjectItem(manifest, KEY_VERSION_CODE);

    result = JSI::CreateObject();
    if (appName != nullptr) {
        JSI::SetStringProperty(result, KEY_APP_NAME, appName->valuestring);
    }
    if (versionName != nullptr) {
        JSI::SetStringProperty(result, KEY_VERSION_NAME, versionName->valuestring);
    }
    if (versionCode != nullptr) {
        JSI::SetNumberProperty(result, KEY_VERSION_CODE, versionCode->valuedouble);
    }
    cJSON_Delete(manifest);
    manifest = nullptr;
    return result;
}

cJSON *AppModule::ReadManifest()
{
    char *appPath = const_cast<char *>(JsAppContext::GetInstance()->GetCurrentAbilityPath());
    if ((appPath == nullptr) || !strlen(appPath)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Fail to get app information because the app path is null or empty.");
        return nullptr;
    }

    char *manifestPath = RelocateJSSourceFilePath(appPath, FILE_MANIFEST);
    if (manifestPath == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Fail to get app information because the manifest.json path is null.");
        return nullptr;
    }
    if (!strlen(manifestPath)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Fail to get app information because the manifest.json path is empty.");
        ace_free(manifestPath);
        manifestPath = nullptr;
        return nullptr;
    }

    uint32_t fileSize = 0;
    char *manifestContent = ReadFile(manifestPath, &fileSize, false);

    ace_free(manifestPath);
    manifestPath = nullptr;

    if (manifestContent == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Fail to get app information because the manifest.json context is null.");
        return nullptr;
    }
    if (fileSize == 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Fail to get app information because the manifest.json context is empty.");
        ace_free(manifestContent);
        manifestContent = nullptr;
        return nullptr;
    }

    cJSON *manifest = cJSON_Parse(manifestContent);

    ace_free(manifestContent);
    manifestContent = nullptr;

    return manifest;
}

JSIValue AppModule::Terminate(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    UNUSED(thisVal);
    UNUSED(args);
    UNUSED(argsNum);
    JsAppContext::GetInstance()->TerminateAbility();
    return JSI::CreateUndefined();
}
} // namespace ACELite
} // namespace OHOS
