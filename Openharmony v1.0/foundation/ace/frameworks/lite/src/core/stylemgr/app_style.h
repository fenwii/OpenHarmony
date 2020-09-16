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
#ifndef OHOS_ACELITE_APP_STYLE_H
#define OHOS_ACELITE_APP_STYLE_H

#include "non_copyable.h"
#include "stylemgr/app_style_item.h"
#if ENABLED(SECURE_C_FUNCTION)
#include "securec.h"
#endif // ENABLED(SECURE_C_FUNCTION)

namespace OHOS {
namespace ACELite {
class AppStyle final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(AppStyle);
    AppStyle() : firstStyleItem_(nullptr), lastStyleItem_(nullptr), pre_(nullptr), next_(nullptr), styleName_(nullptr)
    {
    }

    ~AppStyle()
    {
        Reset();
    }

    const char* GetStyleName()
    {
        return styleName_;
    }

    const AppStyleItem* GetFirst() const
    {
        return firstStyleItem_;
    }

    void SetPre(AppStyle* preStyle)
    {
        if (preStyle == nullptr) {
            return;
        }

        pre_ = preStyle;
    }

    AppStyle* GetPre()
    {
        return pre_;
    }

    void SetNext(AppStyle* nextStyle)
    {
        if (nextStyle == nullptr) {
            return;
        }
        next_ = nextStyle;
    }

    const AppStyle* GetNext()
    {
        return next_;
    }

    void Reset();
    void AddStyleItem(AppStyleItem* newStyleItem);
    const AppStyleItem* GetStyleItemByName(const char * const stylePropName) const;
    const AppStyleItem* GetStyleItemByNameId(uint16_t stylePropNameId) const;
    static AppStyle* GenerateFromJS(jerry_value_t styleKey, jerry_value_t styleValue, bool isKeyFrames);

private:
    void SetStyleName(const char * const name, size_t nameLen);
    static void AddItemsInLoop(jerry_value_t object, AppStyle& newStyle);
    static void AddKeyFramesItemsInLoop(jerry_value_t objFrom, jerry_value_t objTo, AppStyle& newStyle);
    static jerry_value_t AddKeyFramesTransformValue(jerry_value_t propValueFrom,
                                                    jerry_value_t propValueTo,
                                                    bool& isItemNeedToAdd,
                                                    jerry_value_t& propKeyFrom);
    static jerry_value_t ConcatJerryString(jerry_value_t strA, jerry_value_t strB);
    static bool MergeAnimationString(char* dest, uint16_t destSz, const char * const src1, const char * const src2);
    const AppStyleItem* firstStyleItem_;
    AppStyleItem* lastStyleItem_;
    AppStyle* pre_;
    AppStyle* next_;
    char *styleName_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_APP_STYLE_H
