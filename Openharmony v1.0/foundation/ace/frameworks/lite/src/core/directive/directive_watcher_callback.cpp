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

#include "directive/directive_watcher_callback.h"

namespace OHOS {
namespace ACELite {
const int DirectiveWatcherCallback::CALLBACK_ARGS_LENGTH = 3;
const int DirectiveWatcherCallback::ARG_IDX_OPTIONS = 2;

JSValue DirectiveWatcherCallback::Handler(const JSValue func,
                                          const JSValue context,
                                          const JSValue args[],
                                          const JSSize argsSize)
{
    if (argsSize != CALLBACK_ARGS_LENGTH) {
        return JSUndefined::Create();
    }

    JSValue options = args[ARG_IDX_OPTIONS];

    JSValue parentElement = JSObject::Get(options, DescriptorUtils::WATCHER_OPTION_ELEMENT);
    JSValue descriptor = JSObject::Get(options, DescriptorUtils::WATCHER_OPTION_DESCRIPTOR);

    Component *component = ComponentUtils::GetComponentFromBindingObject(parentElement);
    if (component) {
        component->HandleChildrenChange(descriptor);
    }
    JSRelease(descriptor);
    JSRelease(parentElement);
    return JSUndefined::Create();
}
} // namespace ACELite
} // namespace OHOS
