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

#include "dfx_module.h"
#include "ace_log.h"
#include "ui_dump_dom_tree.h"
#ifdef FEATURE_ACELITE_MC_DFX_MODULE
#include "ui_snapshot.h"
#elif defined(FEATURE_ACELITE_LITE_DFX_MODULE)
#include "ability_env.h"
#include "ace_mem_base.h"
#include "js_fwk_common.h"
#include "ui_screenshot.h"
#endif

namespace OHOS {
namespace ACELite {
const char * const DfxModule::DOM_TREE_PATH = "dump_dom_tree.json";

const char * const DfxModule::SCREEN_SNAP_PATH = "screensnap.bin";

bool DfxModule::PreCheck(uint8_t argsNum)
{
    if (argsNum > 1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Dfx Module args num(%d) is invalid, at most one parameter", argsNum);
        return false;
    }
    return true;
}

char *DfxModule::GetDomViewId(const JSIValue *args)
{
    if (args == nullptr) {
        return nullptr;
    }
    return JSI::ValueToString(args[0]);
}

bool DfxModule::IsEventInjectorRegistered(EventDataType type)
{
    if ((EventInjector::GetInstance() == nullptr) || (!EventInjector::GetInstance()->IsEventInjectorRegistered(type) &&
        !EventInjector::GetInstance()->RegisterEventInjector(type))) {
        HILOG_ERROR(HILOG_MODULE_ACE, "register event error");
        return false;
    }
    return true;
}

#ifdef FEATURE_ACELITE_DFX_MODULE
JSIValue DfxModule::Screenshot(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
#ifdef FEATURE_ACELITE_MC_DFX_MODULE
    JSIValue retVal = JSI::CreateBoolean(true);
    if (!UISnapShot::ScreenshotToFile()) {
        HILOG_ERROR(HILOG_MODULE_ACE, "screenshot failed");
        JSI::ReleaseValue(retVal);
        retVal = JSI::CreateBoolean(false);
    }
    return retVal;
#elif defined(FEATURE_ACELITE_LITE_DFX_MODULE)
    JSIValue retVal = JSI::CreateBoolean(true);
    const char * const dataPath = GetDataPath();
    char *path = RelocateResourceFilePath(dataPath, SCREEN_SNAP_PATH);
    // uikit will deal with if path is null
    if ((UIScreenshot::GetInstance() == nullptr) || (!UIScreenshot::GetInstance()->ScreenshotToFile(path))) {
        HILOG_ERROR(HILOG_MODULE_ACE, "screenshot failed");
        JSI::ReleaseValue(retVal);
        retVal = JSI::CreateBoolean(false);
    }
    if (path != nullptr) {
        ace_free(path);
    }
    return retVal;
#endif
}
#endif

JSIValue DfxModule::DumpDomTree(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue retVal = JSI::CreateBoolean(false);
    if (!PreCheck(argsNum)) {
        return retVal;
    }

    char *viewId = GetDomViewId(args);
#ifdef FEATURE_ACELITE_LITE_DFX_MODULE
    const char * const dataPath = GetDataPath();
    char *path = RelocateResourceFilePath(dataPath, DOM_TREE_PATH);
    // uikit will deal with if path and viewid is null
    if ((UIDumpDomTree::GetInstance() != nullptr) && (UIDumpDomTree::GetInstance()->DumpDomTree(viewId, path))) {
#else
    if ((UIDumpDomTree::GetInstance() != nullptr) && (UIDumpDomTree::GetInstance()->DumpDomTree(viewId))) {
#endif
        JSI::ReleaseValue(retVal);
        retVal = JSI::CreateBoolean(true);
    }

#ifdef FEATURE_ACELITE_LITE_DFX_MODULE
    if (path != nullptr) {
        ace_free(path);
    }
#endif
    JSI::ReleaseString(viewId);
    return retVal;
}

JSIValue DfxModule::DumpDomNode(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    if (!PreCheck(argsNum) || (UIDumpDomTree::GetInstance() == nullptr)) {
        return JSI::CreateUndefined();
    }

    char *viewId = GetDomViewId(args);
    char *msg = UIDumpDomTree::GetInstance()->DumpDomNode(viewId);
    if (msg == nullptr) {
        JSI::ReleaseString(viewId);
        return JSI::CreateUndefined();
    }
    JSIValue retVal = JSI::CreateString(msg);
    free(msg); // use heap memory, use free() instead of ace_free()
    JSI::ReleaseString(viewId);
    return retVal;
}

JSIValue DfxModule::InjectPointEvent(const JSIValue *args, EventDataType type)
{
    JSIValue retVal = JSI::CreateBoolean(true);
    const uint8_t index = 2;
    const uint32_t maxLen = 40;
    // over 40 are ignored, ignore from beginning of the array
    uint32_t len = JSI::GetArrayLength(args[0]);
    uint32_t arrIndex = 0;
    uint32_t realLen = (len > maxLen) ? maxLen : len;
    DeviceData *data = (realLen > 0) ? static_cast<DeviceData *>(ace_malloc(sizeof(DeviceData) * realLen)) : nullptr;
    if (len > maxLen) {
        arrIndex = len - maxLen;
    }
    if (data == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create device data failed");
        JSI::ReleaseValue(retVal);
        return JSI::CreateBoolean(false);
    }

    for (uint16_t i = 0; arrIndex < len; i++, arrIndex++) {
        JSIValue point = JSI::GetPropertyByIndex(args[0], arrIndex);
        if (JSI::ValueIsUndefined(point)) {
            HILOG_ERROR(HILOG_MODULE_ACE, "point is error");
            ace_free(data);
            JSI::ReleaseValue(retVal);
            return JSI::CreateBoolean(false);
        }
        JSIValue point_x = JSI::GetPropertyByIndex(point, 0);
        JSIValue point_y = JSI::GetPropertyByIndex(point, 1);
        JSIValue state = JSI::GetPropertyByIndex(point, index);
        data[i].point = {
            static_cast<int16_t>(JSI::ValueToNumber(point_x)),
            static_cast<int16_t>(JSI::ValueToNumber(point_y))
        };
        data[i].state = static_cast<uint16_t>(JSI::ValueToNumber(state));
        JSI::ReleaseValueList(point_x, point_y, state, point);
    }

    // simulate point event
    if ((EventInjector::GetInstance() != nullptr) &&
        (EventInjector::GetInstance()->SetInjectEvent(data, realLen, type))) {
        ace_free(data);
        return retVal;
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "simulator point event error");
        ace_free(data);
        JSI::ReleaseValue(retVal);
        return JSI::CreateBoolean(false);
    }
}

JSIValue DfxModule::InjectEvent(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    // pre check
    const uint8_t num = 2;
    if (argsNum != num) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Dfx Module args num(%d) is invalid, only one parameter", argsNum);
        return JSI::CreateBoolean(false);
    }

    // dispatch register event
    char *eventType = JSI::ValueToString(args[1]);
    if (eventType == nullptr) {
        return JSI::CreateBoolean(false);
    }
    if (!strcmp(eventType, "point")) {
        JSI::ReleaseString(eventType);
        EventDataType type = EventDataType::POINT_TYPE;
        if (!IsEventInjectorRegistered(type)) {
            return JSI::CreateBoolean(false);
        }
        return InjectPointEvent(args, type);
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "only support point event");
    }

    JSI::ReleaseString(eventType);
    return JSI::CreateBoolean(false);
}

void DfxModule::OnDestroy()
{
    // iterator remove all registered event
    if (EventInjector::GetInstance() != nullptr) {
        EventInjector::GetInstance()->UnregisterEventInjector(EventDataType::POINT_TYPE);
        EventInjector::GetInstance()->UnregisterEventInjector(EventDataType::OTHERS);
    }
}
} // namespace ACELite
} // namespace OHOS
