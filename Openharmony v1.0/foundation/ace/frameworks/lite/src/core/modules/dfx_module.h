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

#ifndef OHOS_ACELITE_DFX_MODULE_H
#define OHOS_ACELITE_DFX_MODULE_H

#include "acelite_config.h"
#include "event_injector.h"
#include "jsi.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
class DfxModule final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(DfxModule);
#ifdef FEATURE_ACELITE_DFX_MODULE
    static JSIValue Screenshot(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
#endif
    static JSIValue InjectEvent(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static JSIValue DumpDomNode(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static JSIValue DumpDomTree(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static void OnDestroy();

private:
    static const char * const DOM_TREE_PATH;
    static const char * const SCREEN_SNAP_PATH;

    DfxModule() {}
    ~DfxModule() {}

    static char *GetDomViewId(const JSIValue *args);
    static bool PreCheck(uint8_t argsNum);
    static JSIValue InjectPointEvent(const JSIValue *args, EventDataType type);
    static bool IsEventInjectorRegistered(EventDataType type);
};

void InitDfxModule(JSIValue exports)
{
#ifdef FEATURE_ACELITE_DFX_MODULE
    JSI::SetModuleAPI(exports, "screenshotToFile", DfxModule::Screenshot);
#endif // FEATURE_ACELITE_DFX_MODULE
    JSI::SetModuleAPI(exports, "injectEvent", DfxModule::InjectEvent);
    JSI::SetModuleAPI(exports, "dumpDomNode", DfxModule::DumpDomNode);
    JSI::SetModuleAPI(exports, "dumpDomTree", DfxModule::DumpDomTree);
    JSI::SetOnDestroy(exports, DfxModule::OnDestroy);
}
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_DFX_MODULE_H
