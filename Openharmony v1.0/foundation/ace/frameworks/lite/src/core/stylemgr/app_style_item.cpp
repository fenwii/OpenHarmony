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

#include "stylemgr/app_style_item.h"
#include "ace_log.h"
#include "keys.h"

namespace OHOS {
namespace ACELite {
uint8_t AppStyleItem::EstimatePseudoClassType(const char * const styleKey, uint16_t *keyLength)
{
    char *p = strchr(const_cast<char *>(styleKey), ':');
    if (p == nullptr) {
        return PSEUDO_CLASS_UNKNOWN;
    }

    uint8_t type = PSEUDO_CLASS_UNKNOWN;
    // :active meets
    if (!strcmp(p, PSEUDO_CLASS_TYPE_ACTIVE)) {
        type = PSEUDO_CLASS_ACTIVE;
    } else if (!strcmp(p, PSEUDO_CLASS_TYPE_CHECKED)) {
        type = PSEUDO_CLASS_CHECKED;
    }

    // drop :xxxx
    if (type != PSEUDO_CLASS_UNKNOWN) {
        *p = '\0';
        *keyLength = (uint16_t)(p - styleKey);
    }
    return type;
}

void AppStyleItem::SetStringValue(const char * const value)
{
    if (value == nullptr) {
        return;
    }
    size_t len = strlen(value);
    if (len >= UINT16_MAX) {
        return;
    }
    valueType_ = STYLE_PROP_VALUE_TYPE_STRING;
    styleValue_.string = static_cast<char *>(ace_malloc(sizeof(char) * (len + 1)));
    if (styleValue_.string == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create style item string failed.");
        return;
    }
    if (memcpy_s(styleValue_.string, len, value, len) != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "app_style set string value error");
        ace_free(styleValue_.string);
        styleValue_.string = nullptr;
        return;
    }
    *(styleValue_.string + len) = '\0';
}

bool AppStyleItem::UpdateNumValToStr()
{
    if (GetValueType() == STYLE_PROP_VALUE_TYPE_NUMBER) {
        int32_t numVal = GetNumValue();
        const uint8_t len = 11; // max size of int32_t
        char strVal[len] = { 0 };
        if (sprintf_s(strVal, len, "%d", numVal) < 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "style item tranform num to string fail");
            return false;
        }
        SetStringValue((const char *)strVal);
    }
    return true;
}

AppStyleItem *AppStyleItem::GenerateFromJSValue(jerry_value_t stylePropName, jerry_value_t stylePropValue)
{
    uint16_t strLen = 0;
    char *keyNameBuffer = MallocStringOf(stylePropName, &strLen);
    if (keyNameBuffer == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "convert style prop name to char failed, will be dropped");
        return nullptr;
    } else {
        if (strLen == 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "style prop name length is 0, will be dropped");
            ace_free(keyNameBuffer);
            keyNameBuffer = nullptr;
            return nullptr;
        }
    }
    uint8_t pseudoType_ = EstimatePseudoClassType(static_cast<char *>(keyNameBuffer), &strLen);
    AppStyleItem *styleItem =
        CreateStyleItem(KeyParser::ParseKeyId((const char *)keyNameBuffer, strLen), stylePropValue, pseudoType_);
    ace_free(keyNameBuffer);
    keyNameBuffer = nullptr;
    return styleItem;
}

AppStyleItem *AppStyleItem::CreateStyleItem(uint16_t keyId, const jerry_value_t stylePropValue, uint8_t pseudoClassType)
{
    AppStyleItem *newStyleItem = new AppStyleItem();
    if (newStyleItem == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "new styleItem error");
        return nullptr;
    }

    char *strValueBuffer = nullptr;

    newStyleItem->propNameId_ = keyId;
    newStyleItem->pseudoClassType_ = pseudoClassType;

    if (jerry_value_is_number(stylePropValue)) {
        if (keyId == K_OPACITY) {
            newStyleItem->SetFloatingValue(jerry_get_number_value(stylePropValue));
        } else {
            newStyleItem->SetNumValue((int32_t)(jerry_get_number_value(stylePropValue)));
        }
    } else if (jerry_value_is_boolean(stylePropValue)) {
        newStyleItem->SetBoolValue(jerry_get_boolean_value(stylePropValue));
    } else {
        strValueBuffer = MallocStringOf(stylePropValue);
        if (strValueBuffer == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "convert style value to char failed, will be dropped");
            delete newStyleItem;
            newStyleItem = nullptr;
            return nullptr;
        } else {
            newStyleItem->SetStringValue((const char *)strValueBuffer);
            ace_free(strValueBuffer);
            strValueBuffer = nullptr;
        }
    }

    return newStyleItem;
}

AppStyleItem *AppStyleItem::CopyFrom(const AppStyleItem *from)
{
    if (from == nullptr) {
        return nullptr;
    }

    AppStyleItem *styleItem = new AppStyleItem();
    if (styleItem == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "new styleItem error");
        return nullptr;
    }

    styleItem->propNameId_ = from->propNameId_;
    styleItem->pseudoClassType_ = from->pseudoClassType_;
    switch (from->GetValueType()) {
        case STYLE_PROP_VALUE_TYPE_STRING: {
            const char *strValue = from->GetStrValue();
            if (strValue != nullptr) {
                styleItem->SetStringValue(strValue);
            }
            break;
        }
        case STYLE_PROP_VALUE_TYPE_BOOL:
            styleItem->SetBoolValue(from->GetBoolValue());
            break;
        case STYLE_PROP_VALUE_TYPE_NUMBER:
            styleItem->SetNumValue(from->GetNumValue());
            break;
        case STYLE_PROP_VALUE_TYPE_FLOATING:
            styleItem->SetFloatingValue(from->GetFloatingValue());
            break;
        default:
            break;
    }

    return styleItem;
}
} // namespace ACELite
} // namespace OHOS
