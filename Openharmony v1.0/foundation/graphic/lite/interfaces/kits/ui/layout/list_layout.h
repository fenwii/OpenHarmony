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

#ifndef GRAPHIC_LITE_LIST_LAYOUT_H
#define GRAPHIC_LITE_LIST_LAYOUT_H

#include "flex_layout.h"

namespace OHOS {
class ListLayout : public FlexLayout {
public:
    /** @brief Default constructor */
    ListLayout(const uint8_t direction = VERTICAL);

    /**
     * @brief Destructor
     */
    virtual ~ListLayout() {}

    /**
     * @brief set list direction, HORIZONTAL list view will recount X position, VERTICAL recount Y.
     *
     * @param [in] direction the direction, @see HORIZONTAL, VERTICAL.
     */
    void SetDirection(uint8_t direction);

    /**
     * @brief get list direction.
     *
     * @param [in] null.
     */
    uint8_t GetDirection()
    {
        return listDirection_;
    }

    static constexpr uint8_t HORIZONTAL = 0;
    static constexpr uint8_t VERTICAL = 1;
protected:
    void SetLayoutDirect(uint8_t direction);
    void OnChildChanged() override;
    uint8_t listDirection_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_LIST_LAYOUT_H
