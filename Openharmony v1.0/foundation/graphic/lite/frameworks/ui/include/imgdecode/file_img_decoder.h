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

#ifndef GRAPHIC_LITE_FILE_IMG_DECODER_H
#define GRAPHIC_LITE_FILE_IMG_DECODER_H

#include "draw/draw_image.h"
#include "draw/draw_utils.h"

namespace OHOS {
constexpr uint8_t BYTE_TO_BIT_SHIFT = 3;
constexpr uint8_t ONE_BIT_LEN_IN_BIT = 1;
constexpr uint8_t TWO_BIT_LEN_IN_BIT = 2;
constexpr uint8_t FOUR_BIT_LEN_IN_BIT = 4;
constexpr uint8_t BYTE_LEN_IN_BIT = 8;

enum class RetCode {
    OK,
    FAIL,
};

class FileImgDecoder : public HeapBase {
public:
    static FileImgDecoder& GetInstance()
    {
        static FileImgDecoder instance;
        return instance;
    }

    struct ImgResDsc {
        FileImgDecoder* decoder;
        const char* path;
        ImageInfo imgInfo;
        uint32_t timeToOpen;
        int32_t fd;
        ImageSrcType srcType;
        bool inCache_;
    };

    RetCode Open(ImgResDsc& dsc);

    RetCode Close(ImgResDsc& dsc);

    RetCode GetHeader(ImgResDsc& dsc);

    RetCode ReadLine(ImgResDsc& dsc, const Point& start, int16_t len, uint8_t* buf);

    RetCode ReadToCache(ImgResDsc& dsc);

private:
    FileImgDecoder() {};
    ~FileImgDecoder() {};

    bool IsImgValidMode(uint8_t colorMode)
    {
        if (colorMode == RGB565 || colorMode == RGB888 || colorMode == ARGB8888) {
            return true;
        } else {
            return false;
        }
    }
    RetCode ReadLineTrueColor(ImgResDsc& dsc, const Point& start, int16_t len, uint8_t* buf);

    FileImgDecoder(const FileImgDecoder&) = delete;
    FileImgDecoder& operator=(const FileImgDecoder&) = delete;
    FileImgDecoder(FileImgDecoder&&) = delete;
    FileImgDecoder& operator=(FileImgDecoder&&) = delete;
};
}
#endif