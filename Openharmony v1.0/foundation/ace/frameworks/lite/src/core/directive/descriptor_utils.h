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

#ifndef OHOS_ACELITE_DESCRIPTOR_UTILS_H
#define OHOS_ACELITE_DESCRIPTOR_UTILS_H

#include "component.h"
#include "non_copyable.h"
#include "wrapper/js.h"

namespace OHOS {
namespace ACELite {
class DescriptorUtils final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(DescriptorUtils);
    ~DescriptorUtils() {}
    static JSValue CreateIfDescriptor(JSValue getter, JSValue render);
    static JSValue CreateForDescriptor(JSValue getter, JSValue render);
    static JSValue CreateDescriptorWatcher(JSValue element, JSValue descriptor);
    static bool IsIfDescriptor(JSValue descriptor);
    static bool IsForDescriptor(JSValue descriptor);
    static bool IsIfDescriptorShown(JSValue descriptor);
    static JSValue RenderIfDescriptor(JSValue descriptor);
    static JSValue RenderForDescriptor(JSValue descriptor);
    static JSValue GetDescriptorRendered(JSValue descriptor);
    static void DelIfDescriptorRendered(JSValue descriptor);
    static void DelForDescriptorRendered(JSValue descriptor);
    static void ReleaseDescriptorOrElements(JSValue descriptorOrElements);
    static void ReleaseDescriptorOrElement(JSValue descriptorOrElement);
    static void ReleaseForDescriptor(JSValue descriptor);
    static void ReleaseIfDescriptor(JSValue descriptor);
    static void ReleaseElement(JSValue element);

    static const char * const DESCRIPTOR_ATTR_RENDERED;
    static const char * const DESCRIPTOR_ATTR_GETTER;
    static const char * const DESCRIPTOR_ATTR_RENDER;
    static const char * const WATCHER_OPTION_ELEMENT;
    static const char * const WATCHER_OPTION_DESCRIPTOR;

private:
    static JSValue CreateDescriptor(const char * const type, JSValue getter, JSValue render);
    static bool IsDescriptor(const char * const type, JSValue descriptor);
    static const char * const DESCRIPTOR_ATTR_IF;
    static const char * const DESCRIPTOR_ATTR_FOR;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_DESCRIPTOR_UTILS_H
