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

#include "dfx/ui_screenshot.h"

#if ENABLE_DEBUG
#include "client/iwindows_manager.h"
#include "color.h"
#include "common/screen.h"
#include "draw/draw_utils.h"
#include "file.h"
#include "graphic_log.h"
#include "image_info.h"
#include "securec.h"

namespace OHOS {
union Color16Argb1555 {
    struct {
        uint16_t blue : 5;
        uint16_t green : 5;
        uint16_t red : 5;
        uint16_t alph : 1;
    };
    uint16_t full;
};

static uint32_t Argb1555ToArgb8888(Color16Argb1555* color)
{
    ColorType ret;
    ret.alpha = color->alph ? 0xFF : 0x00;
    ret.red = color->red << 3;
    ret.green = color->green << 3;
    ret.blue = color->blue << 3;
    return ret.full;
}

class UIScreenshotListener : public IWindowsManager::ScreenshotListener {
public:
    UIScreenshotListener() : filePath_(nullptr) {}

    virtual ~UIScreenshotListener()
    {
        if (filePath_ != nullptr) {
            UIFree(reinterpret_cast<void*>(filePath_));
            filePath_ = nullptr;
        }
    }

    void OnScreenshotEnd(uint8_t* virAddr, uint32_t size) override
    {
        if (virAddr == nullptr) {
            return;
        }
        ImageInfo image;
#if COLOR_DEPTH == 16
        image.header = { RGB565, Screen::GetInstance().GetWidth(), Screen::GetInstance().GetHeight()};
#elif COLOR_DEPTH == 32
        image.header = { RGB888, Screen::GetInstance().GetWidth(), Screen::GetInstance().GetHeight()};
#endif
        image.dataSize = image.header.width * image.header.height * DEFAULT_COLOR_SIZE;
        image.data = nullptr;

        FileUnlink(filePath_);
        int32_t fd = FileOpen(filePath_, O_RDWR | O_CREAT);
        UIFree(reinterpret_cast<void*>(filePath_));
        filePath_ = nullptr;
        if (fd < 0) {
            GRAPHIC_LOGE("UIScreenshotListener::OnScreenshotEnd open file failed Err!\n");
            return;
        }

        if (FileWrite(fd, &image.header, sizeof(ImageHeader)) != sizeof(ImageHeader)) {
            GRAPHIC_LOGE("UIScreenshotListener::OnScreenshotEnd write image header failed Err!\n");
            FileClose(fd);
            return;
        }

        uint32_t dataLength = size / 2; // 2: 2 bytes data is a pixel data.
        uint32_t circles = dataLength / MAX_MALLOC_SIZE;
        uint32_t* argb8888Addr = static_cast<uint32_t*>(UIMalloc(MAX_MALLOC_SIZE * sizeof(uint32_t)));
        if (argb8888Addr == nullptr) {
            GRAPHIC_LOGE("UIScreenshotListener::OnScreenshotEnd memory allocation failed Err!\n");
            FileClose(fd);
            return;
        }

        uint16_t* startAddr = reinterpret_cast<uint16_t*>(virAddr);
        for (uint32_t i = 0; i < circles; i++) {
            if (!WriteBlockToFile(fd, argb8888Addr, startAddr, MAX_MALLOC_SIZE)) {
                GRAPHIC_LOGE("UIScreenshotListener::OnScreenshotEnd write pixel data failed Err!\n");
                UIFree(reinterpret_cast<void*>(argb8888Addr));
                FileClose(fd);
                return;
            }
            startAddr += MAX_MALLOC_SIZE;
        }

        uint16_t remainder = dataLength % MAX_MALLOC_SIZE;
        if (remainder == 0) {
            UIFree(reinterpret_cast<void*>(argb8888Addr));
            FileClose(fd);
            return;
        }
        WriteBlockToFile(fd, argb8888Addr, startAddr, remainder);
        UIFree(reinterpret_cast<void*>(argb8888Addr));
        FileClose(fd);
    }

    void SetFilePath(char* path)
    {
        if (filePath_ != nullptr) {
            UIFree(reinterpret_cast<void*>(filePath_));
        }
        filePath_ = path;
    }

private:
    static constexpr uint8_t DEFAULT_COLOR_SIZE = 4;
    static constexpr uint16_t MAX_MALLOC_SIZE = 2048; // unit: 4 bytes
    char* filePath_;

    bool WriteBlockToFile(int32_t fd, uint32_t* buffer, uint16_t* startAddr, uint32_t size) const
    {
        if (fd < 0 || buffer == nullptr || startAddr == nullptr || size == 0) {
            return false;
        }

        uint16_t* temp = startAddr;
        uint32_t* argb8888Addr = buffer;
        for (uint32_t i = 0; i < size; i++) {
            argb8888Addr[i] = Argb1555ToArgb8888(reinterpret_cast<Color16Argb1555*>(temp));
            temp++;
        }

        uint32_t blockSize = size * sizeof(uint32_t);
        if (FileWrite(fd, argb8888Addr, blockSize) != blockSize) {
            GRAPHIC_LOGE("UIScreenshotListener::WriteBlockToFile wrong amount of written data Err!\n");
            return false;
        }
        return true;
    }
};

UIScreenshot::~UIScreenshot()
{
    if (screenshotListener_ != nullptr) {
        delete screenshotListener_;
        screenshotListener_ = nullptr;
    }
}

bool UIScreenshot::ScreenshotToFile(const char* path)
{
    if (screenshotListener_ == nullptr) {
        screenshotListener_ = new UIScreenshotListener();
        if (screenshotListener_ == nullptr) {
            GRAPHIC_LOGE("UIScreenshot::ScreenshotToFile register screenshot listener failed Err!\n");
            return false;
        }
        IWindowsManager::GetInstance()->SetScreenshotListener(screenshotListener_);
    }

    const char* srcPath = (path == nullptr) ? DEFAULT_SCREENSHOT_PATH : path;
    uint32_t pathLength = strlen(srcPath);
    char* destPath = static_cast<char*>(UIMalloc(pathLength + 1));
    if (destPath == nullptr) {
        return false;
    }

    if (memcpy_s(destPath, pathLength + 1, srcPath, pathLength) != EOK) {
        UIFree(reinterpret_cast<void*>(destPath));
        return false;
    }
    destPath[pathLength] = '\0';
    screenshotListener_->SetFilePath(destPath);
    IWindowsManager::GetInstance()->Screenshot();
    return true;
}
} // namespace OHOS
#endif // ENABLE_DEBUG