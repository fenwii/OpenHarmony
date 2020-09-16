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

#include "directive/descriptor_utils.h"
#include "ace_log.h"
#include "directive/directive_watcher_callback.h"
#include "wrapper/js.h"

namespace OHOS {
namespace ACELite {
const char * const DescriptorUtils::DESCRIPTOR_ATTR_GETTER = "getter";
const char * const DescriptorUtils::DESCRIPTOR_ATTR_RENDER = "render";
const char * const DescriptorUtils::DESCRIPTOR_ATTR_IF = "if";
const char * const DescriptorUtils::DESCRIPTOR_ATTR_FOR = "for";
const char * const DescriptorUtils::DESCRIPTOR_ATTR_RENDERED = "rendered";
const char * const DescriptorUtils::WATCHER_OPTION_ELEMENT = "element";
const char * const DescriptorUtils::WATCHER_OPTION_DESCRIPTOR = "descriptor";

JSValue DescriptorUtils::CreateIfDescriptor(JSValue getter, JSValue render)
{
    return CreateDescriptor(DESCRIPTOR_ATTR_IF, getter, render);
}

JSValue DescriptorUtils::CreateForDescriptor(JSValue getter, JSValue render)
{
    return CreateDescriptor(DESCRIPTOR_ATTR_FOR, getter, render);
}

JSValue DescriptorUtils::CreateDescriptorWatcher(JSValue element, JSValue descriptor)
{
    JSValue getter = JSObject::Get(descriptor, DESCRIPTOR_ATTR_GETTER);
    JSValue options = JSObject::Create();
    JSObject::Set(options, WATCHER_OPTION_ELEMENT, element);
    JSObject::Set(options, WATCHER_OPTION_DESCRIPTOR, descriptor);

    JSValue watcher = CreateWatcher(getter, DirectiveWatcherCallback::Handler, options);
    JSRelease(options);
    JSRelease(getter);

    return watcher;
}

bool DescriptorUtils::IsIfDescriptor(JSValue descriptor)
{
    return IsDescriptor(DESCRIPTOR_ATTR_IF, descriptor);
}

bool DescriptorUtils::IsForDescriptor(JSValue descriptor)
{
    return IsDescriptor(DESCRIPTOR_ATTR_FOR, descriptor);
}

bool DescriptorUtils::IsIfDescriptorShown(JSValue descriptor)
{
    JSValue getter = JSObject::Get(descriptor, DESCRIPTOR_ATTR_GETTER);
    JSValue condition = CallWithRootAbilitySlice(getter);
    bool isShown = JSBoolean::Value(condition);
    JSRelease(condition);
    JSRelease(getter);
    return isShown;
}

JSValue DescriptorUtils::RenderIfDescriptor(JSValue descriptor)
{
    JSValue render = JSObject::Get(descriptor, DESCRIPTOR_ATTR_RENDER);
    JSValue rendered = CallWithRootAbilitySlice(render);
    JSRelease(render);
    JSObject::Set(descriptor, DESCRIPTOR_ATTR_RENDERED, rendered);
    return rendered;
}

JSValue DescriptorUtils::RenderForDescriptor(JSValue descriptor)
{
    JSValue getter = JSObject::Get(descriptor, DESCRIPTOR_ATTR_GETTER);

    JSValue array = CallWithRootAbilitySlice(getter);
    JSRelease(getter);

    if (JSUndefined::Is(array)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to RenderForDescriptor because the result value is undefined.");
        return JSUndefined::Create();
    }

    JSValue render = JSObject::Get(descriptor, DESCRIPTOR_ATTR_RENDER);

    JSValue rendered = JSArray::Map(array, render);
    JSRelease(render);
    JSRelease(array);
    JSObject::Set(descriptor, DESCRIPTOR_ATTR_RENDERED, rendered);
    return rendered;
}

JSValue DescriptorUtils::GetDescriptorRendered(JSValue descriptor)
{
    return JSObject::Get(descriptor, DESCRIPTOR_ATTR_RENDERED);
}

void DescriptorUtils::DelIfDescriptorRendered(JSValue descriptor)
{
    JSValue descriptorOrElement = GetDescriptorRendered(descriptor);
    if (!JSUndefined::Is(descriptorOrElement)) {
        JSObject::Del(descriptor, DESCRIPTOR_ATTR_RENDERED);
        // the rendered property need to be released
        // and ReleaseDescriptorOrElement function will release it.
        ReleaseDescriptorOrElement(descriptorOrElement);
    }
    // decrease the count of reference increased by jerry_get_property
    JSRelease(descriptorOrElement);
}

void DescriptorUtils::DelForDescriptorRendered(JSValue descriptor)
{
    JSValue descriptorOrElements = GetDescriptorRendered(descriptor);
    if (!JSUndefined::Is(descriptorOrElements)) {
        JSObject::Del(descriptor, DESCRIPTOR_ATTR_RENDERED);
        ReleaseDescriptorOrElements(descriptorOrElements);
        // the rendered property need to be released
        // but ReleaseDescriptorOrElements function only release its element.
        JSRelease(descriptorOrElements);
    }
    // decrease the count of reference increased by jerry_get_property
    JSRelease(descriptorOrElements);
}

void DescriptorUtils::ReleaseDescriptorOrElements(JSValue descriptorOrElements)
{
    uint16_t size = JSArray::Length(descriptorOrElements);
    for (uint16_t idx = 0; idx < size; ++idx) {
        JSValue descriptorOrElement = JSArray::Get(descriptorOrElements, idx);
        // Don't release descriptorOrElement after ReleaseDescriptorOrElement function
        // because ReleaseDescriptorOrElement will release descriptorOrElement
        ReleaseDescriptorOrElement(descriptorOrElement);
    }
}

void DescriptorUtils::ReleaseDescriptorOrElement(JSValue descriptorOrElement)
{
    if (IsForDescriptor(descriptorOrElement)) {
        ReleaseForDescriptor(descriptorOrElement);
    } else if (IsIfDescriptor(descriptorOrElement)) {
        ReleaseIfDescriptor(descriptorOrElement);
    } else {
        ReleaseElement(descriptorOrElement);
    }
}

void DescriptorUtils::ReleaseForDescriptor(JSValue descriptor)
{
    if (JSUndefined::Is(descriptor)) {
        return;
    }
    DelForDescriptorRendered(descriptor);
    JSRelease(descriptor);
}

void DescriptorUtils::ReleaseIfDescriptor(JSValue descriptor)
{
    if (JSUndefined::Is(descriptor)) {
        return;
    }
    DelIfDescriptorRendered(descriptor);
    JSRelease(descriptor);
}

void DescriptorUtils::ReleaseElement(JSValue element)
{
    if (JSUndefined::Is(element)) {
        return;
    }

    Component *component = nullptr;
    bool isBinded = JSObject::GetNativePointer(element, reinterpret_cast<void **>(&component));
    if (!isBinded || (component == nullptr)) {
        return;
    }

    bool isSuccess = JSObject::DelNativePointer(element);
    if (!isSuccess) {
        HILOG_WARN(HILOG_MODULE_ACE, "delete native view pointer from native element failed.");
    }

    if (component->GetComponentName() != K_LIST) {
        JSValue descriptors = component->GetDescriptors();
        if (!JSUndefined::Is(descriptors)) {
            ReleaseDescriptorOrElements(descriptors);
        }
    }

    component->Release();
    delete component;
    component = nullptr;
}

JSValue DescriptorUtils::CreateDescriptor(const char * const type, JSValue getter, JSValue render)
{
    if ((type == nullptr) || (strlen(type) == 0)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to create descriptor because the type argument is null or empty.");
        return UNDEFINED;
    }

    if (!JSFunction::Is(getter)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to create descriptor because the getter argument is not a function.");
        return UNDEFINED;
    }

    if (!JSFunction::Is(render)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to create descriptor because the render argument is not a function.");
        return UNDEFINED;
    }

    JSValue descriptor = JSObject::Create();
    JSValue value = JSBoolean::Create(true);
    JSObject::Set(descriptor, type, value);
    JSRelease(value);

    JSObject::Set(descriptor, DESCRIPTOR_ATTR_GETTER, getter);
    JSObject::Set(descriptor, DESCRIPTOR_ATTR_RENDER, render);

    return descriptor;
}

bool DescriptorUtils::IsDescriptor(const char * const type, JSValue descriptor)
{
    if (JSUndefined::Is(descriptor)) {
        return false;
    }

    JSValue value = JSObject::Get(descriptor, type);
    bool result = JSBoolean::Value(value);
    JSRelease(value);
    return result;
}
} // namespace ACELite
} // namespace OHOS
