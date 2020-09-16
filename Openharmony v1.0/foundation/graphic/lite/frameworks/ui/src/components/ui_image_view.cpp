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

#include "components/ui_image_view.h"
#include "common/image.h"
#include "common/typed_text.h"
#include "draw/draw_image.h"
#include "draw/draw_label.h"
#include "draw/draw_rect.h"
#include "image_info.h"
#include "imgdecode/cache_manager.h"
#include "mem_api.h"

namespace OHOS {
UIImageView::UIImageView()
    : imageWidth_(0), imageHeight_(0),
      autoEnable_(true), needRefresh_(false), colorFormat_(UNKNOW),
      blurLevel_(BlurLevel::LEVEL0), algorithm_(TransformAlgorithm::BILINEAR), reserve_(0)
{
    style_ = &(StyleDefault::GetBackgroundTransparentStyle());
}

UIImageView::~UIImageView()
{
    DeleteMeasureView();
}

bool UIImageView::OnPreDraw(const Rect& invalidatedArea)
{
    bool cover = false;
    if ((image_.GetSrcType() == IMG_SRC_UNKNOWN)) {
        return false;
    }

    if ((colorFormat_ == RGB565 || colorFormat_ == RGB888)) {
        cover = GetRect().IsContains(invalidatedArea);
    }

    return cover;
}

void UIImageView::OnDraw(const Rect& invalidatedArea)
{
    DrawRect::Draw(GetRect(), invalidatedArea, *style_);
    if ((imageHeight_ == 0) || (imageWidth_ == 0)) {
        return;
    }

    Rect viewRect = GetContentRect();
    Rect trunc(invalidatedArea);
    if (trunc.Intersect(trunc, viewRect)) {
        uint8_t srcType = image_.GetSrcType();
        if ((srcType == IMG_SRC_FILE) || (srcType == IMG_SRC_VARIABLE)) {
            Rect cordsTmp;
            cordsTmp.SetTop(viewRect.GetY());
            cordsTmp.SetBottom(viewRect.GetY() + imageHeight_ - 1);

            if ((transMap_ == nullptr) || transMap_->IsInvalid()) {
                while (cordsTmp.GetTop() <= viewRect.GetBottom()) {
                    cordsTmp.SetLeft(viewRect.GetX());
                    cordsTmp.SetRight(viewRect.GetX() + imageWidth_ - 1);
                    while (cordsTmp.GetLeft() <= viewRect.GetRight()) {
                        image_.DrawImage(cordsTmp, trunc, *style_, opaScale_);
                        cordsTmp.SetLeft(cordsTmp.GetLeft() + imageWidth_);
                        cordsTmp.SetRight(cordsTmp.GetRight() + imageWidth_);
                    }
                    cordsTmp.SetTop(cordsTmp.GetTop() + imageHeight_);
                    cordsTmp.SetBottom(cordsTmp.GetBottom() + imageHeight_);
                }
            } else if ((transMap_ != nullptr) && !transMap_->IsInvalid()) {
                ImageInfo imgInfo;
                if (srcType == IMG_SRC_FILE) {
                    CacheEntry entry;
                    RetCode ret = CacheManager::GetInstance().Open(GetPath(), *style_, entry);
                    if (ret != RetCode::OK) {
                        return;
                    }
                    imgInfo = entry.GetImageInfo();
                } else {
                    imgInfo = *(GetImageInfo());
                }
                uint8_t pxSize = DrawUtils::GetPxSizeByColorMode(imgInfo.header.colorMode);
                TransformDataInfo imageTranDataInfo = {
                    imgInfo.header, imgInfo.data, pxSize,
                    static_cast<BlurLevel>(blurLevel_), static_cast<TransformAlgorithm>(algorithm_)
                };

                Rect origRect = GetOrigRect();
                int16_t deltaX = origRect.GetX() - transMap_->GetTransMapRect().GetX();
                int16_t deltaY = origRect.GetY() - transMap_->GetTransMapRect().GetY();
                DrawUtils::GetInstance()->DrawTransform(invalidatedArea, Point{ deltaX, deltaY }, Color::Black(),
                    *transMap_, imageTranDataInfo);
            }
        }
    }
}

void UIImageView::SetSrc(const char* src)
{
    bool updated = image_.SetSrc(src);
    if (updated == false) {
        return;
    }
    needRefresh_ = true;
    if (autoEnable_) {
        ReMeasure();
    } else {
        AddMeasureView();
    }
    Invalidate();
}

void UIImageView::ReMeasure()
{
    if (!needRefresh_) {
        return;
    }
    needRefresh_ = false;

    ImageHeader header = {0};
    image_.GetHeader(header);

    imageWidth_ = header.width;
    imageHeight_ = header.height;
    colorFormat_ = header.colorMode;

    if (autoEnable_) {
        Resize(imageWidth_, imageHeight_);
        Invalidate();
    }
}

void UIImageView::SetSrc(const ImageInfo* src)
{
    bool updated = image_.SetSrc(src);
    if (updated == false) {
        return;
    }
    needRefresh_ = true;
    if (autoEnable_) {
        ReMeasure();
    } else {
        AddMeasureView();
    }
    Invalidate();
}
}
