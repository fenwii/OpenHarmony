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

#include "localization_module.h"
#include "ace_event_error_code.h"
#ifdef FEATURE_LOCALIZATION_MODULE
#include "ace_log.h"
#if (defined(_WIN32) || defined(_WIN64))
#include <windows.h>
#else
#include "securec.h"
#endif
#include "file.h"
#include "js_fwk_common.h"
#include <stdlib.h>

namespace OHOS {
namespace ACELite {
void LocalizationModule::Init()
{
    jerry_value_t globalContext = jerry_get_global_object();
    const char * const name = "ViewModel";
    jerry_value_t propertyName = jerry_create_string(reinterpret_cast<const jerry_char_t *>(name));
    if (JerryHasProperty(globalContext, propertyName)) {
        // get the prototype of AbilitySlice
        jerry_value_t currentApp = jerry_get_property(globalContext, propertyName);
        jerry_value_t protoType = jerryx_get_property_str(currentApp, "prototype");
        // register $t to the prototype of abilitySlice
        jerry_value_t functionHandle = jerry_create_external_function(Translate);
        const char * const propName = "$t";
        JerrySetNamedProperty(protoType, propName, functionHandle);
        // register $tc to the prototype of abilitySlice
#ifdef LOCALIZATION_PLURAL
        jerry_value_t pluralHandle = jerry_create_external_function(TranslatePlural);
        const char * const pluralFuncName = "$tc";
        JerrySetNamedProperty(protoType, pluralFuncName, pluralHandle);
        jerry_release_value(pluralHandle);
#endif // LOCALIZATION_PLURAL
        ReleaseJerryValue(functionHandle, protoType, currentApp, VA_ARG_END_FLAG);
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "app is not create.");
    }
    ReleaseJerryValue(propertyName, globalContext, VA_ARG_END_FLAG);
}

void LocalizationModule::Clear()
{
    if (parser_ != nullptr) {
        delete parser_;
        parser_ = nullptr;
    }
    if (currentList_ != nullptr) {
        cJSON_Delete(currentList_);
        currentList_ = nullptr;
    }
}

#ifdef LOCALIZATION_PLURAL
jerry_value_t LocalizationModule::GetValueByKey(const jerry_value_t *args, const jerry_length_t argsNum, bool isPlural)
#else
jerry_value_t LocalizationModule::GetValueByKey(const jerry_value_t *args, const jerry_length_t argsNum)
#endif
{
    if (argsNum == 0) {
        return UNDEFINED;
    }
    char *result = nullptr;
    LocalizationModule *localization = GetInstance();
    char *param = MallocStringOf(args[0]);
    if (param == nullptr) {
        return UNDEFINED;
    }
    cJSON *currentItem = localization->GetJSONByKey(param);
    if (currentItem == nullptr) {
        jerry_value_t paramProp = jerry_create_string(reinterpret_cast<jerry_char_t *>(param));
        ace_free(param);
        param = nullptr;
        return paramProp;
    }
    jerry_value_t arg = UNDEFINED;
    if (argsNum > 1) {
        arg = args[1];
    }
    if (currentItem->type == cJSON_String) {
#ifdef LOCALIZATION_PLURAL
        result = localization->parser_->FillPlaceholder(currentItem->valuestring, arg, argsNum, isPlural);
#else
        result = localization->parser_->FillPlaceholder(currentItem->valuestring, arg, argsNum);
#endif // LOCALIZATION_PLURAL
    } else if (currentItem->type == cJSON_Object || (currentItem->type == cJSON_Array)) {
        char* format = cJSON_Print(currentItem);
#ifdef LOCALIZATION_PLURAL
        result = localization->parser_->FillPlaceholder(format, arg, argsNum, isPlural);
#else
        result = localization->parser_->FillPlaceholder(format, arg, argsNum);
#endif // LOCALIZATION_PLURAL
        if (format != nullptr) {
            cJSON_free(format);
            format = nullptr;
        }
    }
    if (result != nullptr) {
        ace_free(param);
        param = nullptr;
    } else {
        // if currentItem is invalid, return the whole key.e.g.the currrentItem is nullptr
        result = param;
    }
    jerry_value_t resultProp = jerry_create_string(reinterpret_cast<jerry_char_t *>(result));
    ACE_FREE(result);
    cJSON_Delete(localization->currentList_);
    localization->currentList_ = nullptr;
    return resultProp;
}

cJSON *LocalizationModule::GetJSONByKey(const char *key)
{
    char delemeter = '.';
    if (parser_ == nullptr) {
        parser_ = new CJSONParser();
        if (parser_ == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "create json parser failed");
            return nullptr;
        }
        if (!parser_->Init()) {
            ACE_ERROR_CODE_PRINT(EXCE_ACE_LOCALIZATION_FAILED, EXCE_ACE_LOCALIZATION_SYSTEM_LANGUAGE_NOT_INITIALIZED);
            Clear(); // parser init failed, release the resource of this module
            return nullptr;
        }
    }

    cJSON *curJsonItem = nullptr;
    CJSONParser::ListNode *keySplited = nullptr;
    // split the key by '.'
    uint8_t keyCount = parser_->Split(key, delemeter, keySplited);
    uint8_t curKeyIndex = 0;
    // get the json object which defined the key
    do {
        if (curJsonItem == nullptr) {
            curKeyIndex = 0;
            // read the next json file and assign it to currentList_
            if (!parser_->ChangeJsonFile(currentList_)) {
                break;
            }
            curJsonItem = currentList_;
        }
        // get the current splited key
        char *message = CJSONParser::GetNode(keySplited, keyCount - curKeyIndex);
        curJsonItem = cJSON_GetObjectItem(curJsonItem, message);
        curKeyIndex++;
    } while (!(curKeyIndex == keyCount && (curJsonItem != nullptr)));
    CJSONParser::ClearNode(keySplited);
    // reset the index of read file
    parser_->ResetIndex();
    return curJsonItem;
}
} // namespace ACELite
} // namespace OHOS
#endif // LOCALIZATION_MODULE
