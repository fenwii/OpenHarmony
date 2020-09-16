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

#ifndef GRAPHIC_LITE_ISURFACE_H
#define GRAPHIC_LITE_ISURFACE_H

#include "geometry2d.h"

namespace OHOS {
/**
 * @brief The ISurface class is an abstract definition of surface.
 *        Interface to a surface object, being a graphics context for rendering and state control,
 *        buffer operations, palette access.
 */
class ISurface {
public:
    ISurface() {}

    virtual ~ISurface() {}

    virtual void Lock(void** buf, void** phyMem, uint32_t* strideLen) = 0;

    /**
     * @brief Unlock the surface.
     */
    virtual void Unlock() = 0;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_ISURFACE_H