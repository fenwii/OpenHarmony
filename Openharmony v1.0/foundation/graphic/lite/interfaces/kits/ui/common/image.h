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

/**
 * @addtogroup Graphic
 * @{
 *
 * @brief Defines a lightweight graphics system that provides basic UI and container views,
 *        including buttons, images, labels, lists, animators, scroll views, swipe views, and layouts.
 *        This system also provides the Design for X (DFX) capability to implement features such as
 *        view rendering, animation, and input event distribution.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file image.h
 *
 * @brief Declares basic image attributes, including the image type and path.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_IMAGE_H
#define GRAPHIC_LITE_IMAGE_H

#include "heap_base.h"
#include "geometry2d.h"
#include "image_info.h"
#include "style.h"

namespace OHOS {
/**
 * @brief Represents basic image attributes, including the image type and path.
 *
 * @since 1.0
 * @version 1.0
 */
class Image : public HeapBase {
public:
    /**
     * @brief A constructor used to create an <b>Image</b> instance. You can use this constructor when a component
     * requires a map.
     *
     * @since 1.0
     * @version 1.0
     */
    Image();

    /**
     * @brief A destructor used to delete the <b>Image</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~Image();

    /**
     * @brief Obtains the image information in an array.
     *
     * @return Returns the pointer to the image information.
     * @since 1.0
     * @version 1.0
     */
    const ImageInfo* GetImageInfo() const
    {
        return imageInfo_;
    }

    /**
     * @brief Obtains the image path in binary.
     *
     * @return Returns the pointer to the image path.
     * @since 1.0
     * @version 1.0
     */
    const char* GetPath() const
    {
        return path_;
    }

    /**
     * @brief Obtains the basic image information, including the image format, width, and height.
     *
     * @param header Indicates the basic image information.
     * @since 1.0
     * @version 1.0
     */
    void GetHeader(ImageHeader& header) const;

    /**
     * @brief Obtains the image type.
     *
     * @return Returns <b>IMG_SRC_VARIABLE</b> for image information in an array; returns <b>IMG_SRC_FILE</b> for an
     * image path in binary.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetSrcType() const
    {
        return srcType_;
    }

    /**
     * @brief Sets the image path.
     *
     * @param src Indicates the pointer to image path in the format of <b>..\\xxx\\xxx\\xxx.bin</b>.
     * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> if the operation fails.
     * @since 1.0
     * @version 1.0
     */
    bool SetSrc(const char* src);

    /**
     * @brief Sets the image information.
     *
     * @param src Indicates the pointer to the image information.
     * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> if the operation fails.
     * @since 1.0
     * @version 1.0
     */
    bool SetSrc(const ImageInfo* src);

    void DrawImage(const Rect& coords, const Rect& mask, const Style& style, uint8_t opaScale) const;

protected:
    const ImageInfo* imageInfo_;
    const char* path_;

private:
    uint8_t srcType_;
    bool mallocFlag_;
    bool SetLiteSrc(const char* src);
    bool SetStandardSrc(const char* src);
    bool SetPNGSrc(const char* src);
    bool SetJPEGSrc(const char* src);
};
}
#endif // GRAPHIC_LITE_IMAGE_H
