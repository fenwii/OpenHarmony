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

#ifndef OHOS_ACELITE_JS_APP_ENVIRONMENT_H
#define OHOS_ACELITE_JS_APP_ENVIRONMENT_H

#include "js_debugger_config.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
/**
 * @brief Environment of js app.
 */
class JsAppEnvironment final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(JsAppEnvironment);
    /**
     * @brief: get instance of js app Environment.
     *
     * @returns: js app environment instance
     */
    static JsAppEnvironment *GetInstance()
    {
        static JsAppEnvironment instance;
        return &instance;
    }

    /**
     * @brief: init js framework.
     */
    void InitJsFramework() const;
    /**
     * @brief: cleanup resources
     */
    void Cleanup();
    /*
     * @brief: this is called when preparing the environment for the application running, to decide
     * the snapshot mode or JS parsing mode.
     */
    void InitRuntimeMode();
    bool IsSnapshotMode() const
    {
        return snapshotMode_;
    }

private:
    void LoadAceBuiltInModules() const;
    JsAppEnvironment();
    ~JsAppEnvironment() {}
    void LoadFramework() const;
    // we use snapshot as default on device and JS parser as default on simulator
    bool snapshotMode_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_JS_APP_ENVIRONMENT_H
