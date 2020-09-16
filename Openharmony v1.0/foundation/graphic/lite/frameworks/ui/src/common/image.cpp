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

#include "common/image.h"
#include "common/image_decode_ability.h"
#include "draw/draw_image.h"
#include "graphic_log.h"
#include "imgdecode/cache_manager.h"
#include "jpeglib.h"
#include "png.h"
#include "securec.h"

namespace OHOS {
Image::Image() : imageInfo_(nullptr), path_(nullptr), srcType_(IMG_SRC_UNKNOWN), mallocFlag_(false) {}

Image::~Image()
{
    if (srcType_ == IMG_SRC_FILE) {
        CacheManager::GetInstance().Close(path_);
    }
    if (imageInfo_ != nullptr) {
        if (mallocFlag_) {
            UIFree(reinterpret_cast<void*>(const_cast<uint8_t*>(imageInfo_->data)));
            mallocFlag_ = false;
        }
        UIFree(reinterpret_cast<void*>(const_cast<ImageInfo*>(imageInfo_)));
        imageInfo_ = nullptr;
    }
    if (path_ != nullptr) {
        UIFree(reinterpret_cast<void*>(const_cast<char*>(path_)));
        path_ = nullptr;
    }
    srcType_ = IMG_SRC_UNKNOWN;
}

void Image::GetHeader(ImageHeader& header) const
{
    if (srcType_ == IMG_SRC_VARIABLE && imageInfo_ != nullptr) {
        header = imageInfo_->header;
    } else if (srcType_ == IMG_SRC_FILE && path_ != nullptr) {
        CacheManager::GetInstance().GetImageHeader(path_, header);
    }
}

bool Image::SetStandardSrc(const char* src)
{
    const char* ptr = strrchr(src, '.');
    if (ptr == nullptr) {
        srcType_ = IMG_SRC_UNKNOWN;
        return false;
    }

    if (strcmp(ptr, ".png") == 0 || strcmp(ptr, ".PNG") == 0) {
        return SetPNGSrc(src);
    } else if (strcmp(ptr, ".jpg") == 0 || strcmp(ptr, ".JPG") == 0 || strcmp(ptr, ".jpeg") == 0 ||
               strcmp(ptr, ".JPEG") == 0) {
        return SetJPEGSrc(src);
    }

    size_t strLen = strlen(src) + 1;
    char* imagePath = static_cast<char*>(UIMalloc(static_cast<uint32_t>(strLen)));
    if (imagePath == nullptr) {
        srcType_ = IMG_SRC_UNKNOWN;
        return false;
    }

    if (memcpy_s(imagePath, strLen, src, strLen) != EOK) {
        UIFree(reinterpret_cast<void*>(imagePath));
        imagePath = nullptr;
        srcType_ = IMG_SRC_UNKNOWN;
        return false;
    }
    path_ = imagePath;
    srcType_ = IMG_SRC_FILE;
    return true;
}

bool Image::SetLiteSrc(const char* src)
{
    const char* ptr = strrchr(src, '.');
    if (ptr == nullptr) {
        srcType_ = IMG_SRC_UNKNOWN;
        return false;
    }

    size_t strLen = strlen(src) + 1;
    char* imagePath = static_cast<char*>(UIMalloc(static_cast<uint32_t>(strLen)));
    if (imagePath == nullptr) {
        srcType_ = IMG_SRC_UNKNOWN;
        return false;
    }
    if (strcmp(ptr, ".png") == 0 || strcmp(ptr, ".PNG") == 0 || strcmp(ptr, ".jpg") == 0 || strcmp(ptr, ".JPG") == 0 ||
        strcmp(ptr, ".jpeg") == 0 || strcmp(ptr, ".JPEG") == 0) {
        const char* suffixName = "bin";
        if (memcpy_s(imagePath, strLen, src, strLen) != EOK) {
            UIFree(reinterpret_cast<void*>(imagePath));
            imagePath = nullptr;
            srcType_ = IMG_SRC_UNKNOWN;
            return false;
        }
        for (int16_t index = strLen - 2; index >= 0; index--) { // 2: Last but one letter
            if (*(imagePath + index) == '.') {
                imagePath[index + 1] = '\0';
                break;
            }
        }
        if (strcat_s(imagePath, strLen, suffixName) != EOK) {
            UIFree(reinterpret_cast<void*>(imagePath));
            imagePath = nullptr;
            srcType_ = IMG_SRC_UNKNOWN;
            return false;
        }
    } else {
        if (memcpy_s(imagePath, strLen, src, strLen) != EOK) {
            UIFree(reinterpret_cast<void*>(imagePath));
            imagePath = nullptr;
            srcType_ = IMG_SRC_UNKNOWN;
            return false;
        }
    }
    path_ = imagePath;
    srcType_ = IMG_SRC_FILE;
    return true;
}

bool Image::SetSrc(const char* src)
{
    if (path_ != nullptr) {
        UIFree(reinterpret_cast<void*>(const_cast<char*>(path_)));
        path_ = nullptr;
    }

    if (src != nullptr) {
        uint32_t imageType = ImageDecodeAbility::GetInstance().GetImageDecodeAbility();
        if (((imageType & IMG_SUPPORT_JPEG) == IMG_SUPPORT_JPEG) ||
            ((imageType & IMG_SUPPORT_PNG) == IMG_SUPPORT_PNG)) {
            return SetStandardSrc(src);
        } else {
            return SetLiteSrc(src);
        }
    } else {
        path_ = src;
        srcType_ = IMG_SRC_UNKNOWN;
    }
    return true;
}

bool Image::SetSrc(const ImageInfo* src)
{
    if (imageInfo_ != nullptr) {
        UIFree(reinterpret_cast<void*>(const_cast<ImageInfo*>(imageInfo_)));
        imageInfo_ = nullptr;
    }

    if (src != nullptr) {
        imageInfo_ = static_cast<ImageInfo*>(UIMalloc(static_cast<uint32_t>(sizeof(ImageInfo))));
        if (imageInfo_ == nullptr) {
            srcType_ = IMG_SRC_UNKNOWN;
            return false;
        }

        if (memcpy_s(const_cast<ImageInfo*>(imageInfo_), sizeof(ImageInfo), src, sizeof(ImageInfo)) != EOK) {
            srcType_ = IMG_SRC_UNKNOWN;
            return false;
        }

        srcType_ = IMG_SRC_VARIABLE;
    } else {
        imageInfo_ = src;
        srcType_ = IMG_SRC_UNKNOWN;
    }
    return true;
}

void Image::DrawImage(const Rect& coords, const Rect& mask, const Style& style, uint8_t opaScale) const
{
    if (srcType_ == IMG_SRC_VARIABLE) {
        DrawImage::DrawCommon(coords, mask, imageInfo_, style, opaScale);
    } else if (srcType_ == IMG_SRC_FILE) {
        DrawImage::DrawCommon(coords, mask, path_, style, opaScale);
    } else {
        GRAPHIC_LOGE("Image::DrawImage:: failed with error srctype!\n");
    }
}

bool Image::SetPNGSrc(const char* src)
{
    FILE* infile = nullptr;
    png_bytep* rowPointer = nullptr;
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (png == nullptr) {
        srcType_ = IMG_SRC_UNKNOWN;
        return false;
    }
    png_infop info = png_create_info_struct(png);
    if (info == nullptr) {
        srcType_ = IMG_SRC_UNKNOWN;
        return false;
    }
    if ((infile = fopen(src, "rb")) == nullptr) {
        GRAPHIC_LOGE("can't open %s\n", src);
        srcType_ = IMG_SRC_UNKNOWN;
        return false;
    }
    png_init_io(png, infile);
    png_read_info(png, info);

    uint8_t pixelByteSize = DrawUtils::GetPxSizeByColorMode(ARGB8888) >> 3; // 3: Shift right 3 bits
    uint16_t width = png_get_image_width(png, info);
    uint16_t height = png_get_image_height(png, info);
    uint32_t dataSize = height * width * pixelByteSize;

    if (png_get_valid(png, info, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png);
    }
    png_read_update_info(png, info);

    rowPointer = static_cast<png_bytep*>(UIMalloc(sizeof(png_bytep) * height));
    if (rowPointer == nullptr) {
        srcType_ = IMG_SRC_UNKNOWN;
        fclose(infile);
        return false;
    }
    for (uint16_t y = 0; y < height; y++) {
        rowPointer[y] = static_cast<png_byte*>(UIMalloc(png_get_rowbytes(png, info)));
        if (rowPointer[y] == nullptr) {
            for (uint16_t i = 0; i < y; i++) {
                UIFree(rowPointer[i]);
                rowPointer[i] = nullptr;
            }
            fclose(infile);
            UIFree(rowPointer);
            srcType_ = IMG_SRC_UNKNOWN;
            png_destroy_read_struct(&png, &info, nullptr);
            return false;
        }
    }
    png_read_image(png, rowPointer);
    fclose(infile);
    png_destroy_read_struct(&png, &info, nullptr);
    ImageInfo* newStr = static_cast<ImageInfo*>(UIMalloc(sizeof(ImageInfo)));
    if (newStr == nullptr) {
        for (uint16_t i = 0; i < height; i++) {
            UIFree(rowPointer[i]);
            rowPointer[i] = nullptr;
        }
        UIFree(rowPointer);
        srcType_ = IMG_SRC_UNKNOWN;
        return false;
    }
    uint8_t* srcData = static_cast<uint8_t*>(UIMalloc(dataSize));
    if (srcData == nullptr) {
        for (uint16_t i = 0; i < height; i++) {
            UIFree(rowPointer[i]);
            rowPointer[i] = nullptr;
        }
        UIFree(rowPointer);
        UIFree(newStr);
        srcType_ = IMG_SRC_UNKNOWN;
        return false;
    }
    uint32_t n = 0;
    for (uint16_t y = 0; y < height; y++) {
        png_bytep row = rowPointer[y];
        for (uint16_t x = 0; x < width * pixelByteSize; x += pixelByteSize) {
            srcData[n++] = row[x + 2]; // 2: B channel
            srcData[n++] = row[x + 1]; // 1: G channel
            srcData[n++] = row[x + 0]; // 0: R channel
            srcData[n++] = row[x + 3]; // 3: Alpha channel
        }
        UIFree(row);
        row = nullptr;
    }
    UIFree(rowPointer);

    newStr->header.width = width;
    newStr->header.height = height;
    newStr->header.colorMode = ARGB8888;
    newStr->dataSize = dataSize;
    newStr->data = srcData;

    if (imageInfo_ != nullptr) {
        if (mallocFlag_) {
            UIFree(reinterpret_cast<void*>(const_cast<uint8_t*>(imageInfo_->data)));
            mallocFlag_ = false;
        }
        UIFree(reinterpret_cast<void*>(const_cast<ImageInfo*>(imageInfo_)));
        imageInfo_ = nullptr;
    }
    imageInfo_ = newStr;
    mallocFlag_ = true;
    srcType_ = IMG_SRC_VARIABLE;
    return true;
}

bool Image::SetJPEGSrc(const char* src)
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE* infile = nullptr;
    JSAMPARRAY buffer;

    if ((infile = fopen(src, "rb")) == nullptr) {
        GRAPHIC_LOGE("can't open %s\n", src);
        srcType_ = IMG_SRC_UNKNOWN;
        return false;
    }
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    uint8_t pixelByteSize = DrawUtils::GetPxSizeByColorMode(ARGB8888) >> 3; // 3: Shift right 3 bits
    uint16_t width = cinfo.output_width;
    uint16_t height = cinfo.output_height;
    uint32_t dataSize = width * height * pixelByteSize;
    uint16_t rowStride = cinfo.output_width * pixelByteSize;
    buffer = (*cinfo.mem->alloc_sarray)(reinterpret_cast<j_common_ptr>(&cinfo), JPOOL_IMAGE, rowStride,
                                        1); // 1: one-row-high array
    ImageInfo* newStr = static_cast<ImageInfo*>(UIMalloc(sizeof(ImageInfo)));
    if (newStr == nullptr) {
        fclose(infile);
        srcType_ = IMG_SRC_UNKNOWN;
        return false;
    }
    uint8_t* srcData = static_cast<uint8_t*>(UIMalloc(dataSize));
    if (srcData == nullptr) {
        fclose(infile);
        UIFree(newStr);
        srcType_ = IMG_SRC_UNKNOWN;
        return false;
    }
    uint32_t n = 0;
    while (cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo, buffer, 1);       // 1: read one line each time
        for (uint16_t x = 0; x < width * 3; x += 3) { // 3: color components per pixel
            srcData[n++] = buffer[0][x + 2];          // 2: B channel
            srcData[n++] = buffer[0][x + 1];          // 1: G channel
            srcData[n++] = buffer[0][x + 0];          // 0: R channel
            srcData[n++] = 255;                       // 255: set alpha channel
        }
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);

    newStr->header.width = width;
    newStr->header.height = height;
    newStr->header.colorMode = ARGB8888;
    newStr->dataSize = dataSize;
    newStr->data = srcData;

    if (imageInfo_ != nullptr) {
        if (mallocFlag_) {
            UIFree(reinterpret_cast<void*>(const_cast<uint8_t*>(imageInfo_->data)));
            mallocFlag_ = false;
        }
        UIFree(reinterpret_cast<void*>(const_cast<ImageInfo*>(imageInfo_)));
        imageInfo_ = nullptr;
    }
    imageInfo_ = newStr;
    mallocFlag_ = true;
    srcType_ = IMG_SRC_VARIABLE;
    return true;
}
} // namespace OHOS