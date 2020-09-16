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

#include "mem_api.h"
#include "file.h"
#include "imgdecode/file_img_decoder.h"

namespace OHOS {
RetCode FileImgDecoder::Open(ImgResDsc& dsc)
{
#ifdef _WIN32
    int32_t fd = FileOpen(dsc.path, _O_BINARY);
#else
    int32_t fd = FileOpen(dsc.path, O_RDONLY);
#endif
    if (fd == FILE_RET_FAIL) {
        return RetCode::FAIL;
    }
    dsc.fd = fd;

    dsc.imgInfo.data = nullptr;
    dsc.inCache_ = false;
    uint8_t colorMode = dsc.imgInfo.header.colorMode;
    if (IsImgValidMode(colorMode)) {
        dsc.imgInfo.data = nullptr;
        return RetCode::OK;
    } else {
        return RetCode::FAIL;
    }
}

RetCode FileImgDecoder::Close(ImgResDsc& dsc)
{
    if (dsc.imgInfo.data != nullptr) {
        ImageCacheFree(dsc.imgInfo);
        dsc.imgInfo.data = nullptr;
    }
    if (dsc.fd && dsc.fd != FILE_RET_FAIL) {
        FileClose(dsc.fd);
        dsc.fd = FILE_RET_FAIL;
    }

    return RetCode::OK;
}

RetCode FileImgDecoder::GetHeader(ImgResDsc& dsc)
{
    int32_t fd;
    int32_t readCount;
#ifdef _WIN32
    fd = FileOpen(dsc.path, _O_BINARY);
#else
    fd = FileOpen(dsc.path, O_RDONLY);
#endif
    if (fd == FILE_RET_FAIL) {
        return RetCode::FAIL;
    }

    dsc.fd = fd;
    readCount = FileRead(fd, &dsc.imgInfo.header, sizeof(ImageHeader));
    FileClose(fd);
    dsc.fd = FILE_RET_FAIL;
    if (readCount != sizeof(ImageHeader)) {
        dsc.imgInfo.header.width = 0;
        dsc.imgInfo.header.height = 0;
        dsc.imgInfo.header.colorMode = UNKNOW;
        return RetCode::FAIL;
    }

    return RetCode::OK;
}

RetCode FileImgDecoder::ReadLine(ImgResDsc& dsc, const Point& start, int16_t len, uint8_t* buf)
{
    if (IsImgValidMode(dsc.imgInfo.header.colorMode)) {
        return ReadLineTrueColor(dsc, start, len, buf);
    }
    return RetCode::FAIL;
}

RetCode FileImgDecoder::ReadToCache(ImgResDsc& dsc)
{
    FileStatInfo info;
    if (dsc.inCache_ == false) {
        FileSeek(dsc.fd, 0, FILE_SEEK_SET);
        int32_t readCount = FileRead(dsc.fd, &dsc.imgInfo.header, sizeof(ImageHeader));
        if (readCount < 0) {
            return RetCode::FAIL;
        }

        uint8_t ret = FileFdStat(dsc.fd, &info);
        if (ret != FILE_RET_OK) {
            return RetCode::FAIL;
        }
        uint32_t pxCount = info.size - readCount;
        if (dsc.imgInfo.data != nullptr) {
            ImageCacheFree(dsc.imgInfo);
        }

        dsc.imgInfo.dataSize = pxCount;
        dsc.imgInfo.data = reinterpret_cast<uint8_t*>(ImageCacheMalloc(dsc.imgInfo));
        if (dsc.imgInfo.data == nullptr) {
            return RetCode::OK;
        }

        uint8_t* tmp = const_cast<uint8_t*>(dsc.imgInfo.data);
        readCount = FileRead(dsc.fd, reinterpret_cast<void*>(tmp), pxCount);
        if (readCount != pxCount) {
            dsc.imgInfo.data = nullptr;
            dsc.imgInfo.dataSize = 0;
            ImageCacheFree(dsc.imgInfo);
            FileSeek(dsc.fd, 0, FILE_SEEK_SET);
            FileClose(dsc.fd);
            dsc.fd = FILE_RET_FAIL;
            return RetCode::OK;
        }
        dsc.inCache_ = true;
        FileSeek(dsc.fd, 0, FILE_SEEK_SET);
        FileClose(dsc.fd);
        dsc.fd = FILE_RET_FAIL;
    }

    return RetCode::OK;
}

RetCode FileImgDecoder::ReadLineTrueColor(ImgResDsc& dsc, const Point& start, int16_t len, uint8_t* buf)
{
    uint8_t pxSizeInBit = DrawUtils::GetPxSizeByImageInfo(dsc.imgInfo);
    off_t res;

    uint32_t pos = ((start.y * dsc.imgInfo.header.width + start.x) * pxSizeInBit) >> BYTE_TO_BIT_SHIFT;
    pos += sizeof(ImageHeader); /* Skip the header */
    res = FileSeek(dsc.fd, pos, FILE_SEEK_SET);
    if (res == FILE_RET_FAIL) {
        return RetCode::FAIL;
    }
    uint32_t btr = len * (pxSizeInBit >> BYTE_TO_BIT_SHIFT);
    int32_t br = FileRead(dsc.fd, buf, btr);
    if (br == FILE_RET_FAIL || btr != br) {
        return RetCode::FAIL;
    }

    return RetCode::OK;
}
} // namespace OHOS
