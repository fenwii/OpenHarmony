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

#ifndef GRAPHIC_LITE_IMAGEDECODE_ABILITY_H
#define GRAPHIC_LITE_IMAGEDECODE_ABILITY_H
#include "heap_base.h"

namespace OHOS {
enum {
    IMG_SUPPORT_UNKNOW = 0x0,
    IMG_SUPPORT_BITMAP = 0x01,
    IMG_SUPPORT_JPEG = 0x02,
    IMG_SUPPORT_PNG = 0x04,
};
class ImageDecodeAbility : public HeapBase {
public:
    static ImageDecodeAbility& GetInstance()
    {
        static ImageDecodeAbility instance;
        return instance;
    }

    void SetImageDecodeAbility(uint32_t imageType)
    {
        imageType_ = imageType;
    }

    uint32_t GetImageDecodeAbility()
    {
        return imageType_;
    }

private:
    ImageDecodeAbility()
    {
#ifdef VERSION_STANDARD
        imageType_ = IMG_SUPPORT_BITMAP | IMG_SUPPORT_JPEG | IMG_SUPPORT_PNG;
#else
        imageType_ = IMG_SUPPORT_BITMAP;
#endif
    }
    ~ImageDecodeAbility() {}

    uint32_t imageType_;

    ImageDecodeAbility(const ImageDecodeAbility&) = delete;
    ImageDecodeAbility& operator=(const ImageDecodeAbility&) = delete;
    ImageDecodeAbility(ImageDecodeAbility&&) = delete;
    ImageDecodeAbility& operator=(ImageDecodeAbility&&) = delete;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_IMAGEDECODE_ABILITY_H
