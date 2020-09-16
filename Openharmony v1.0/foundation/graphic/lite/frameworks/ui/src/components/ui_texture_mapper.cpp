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

#include "components/ui_texture_mapper.h"

namespace OHOS {
void UITextureMapper::TextureMapperAnimatorCallback::Callback(UIView* view)
{
    if (view == nullptr) {
        return;
    }
    UITextureMapper* mapper = static_cast<UITextureMapper*>(view);
    mapper->Callback();
}

void UITextureMapper::TextureMapperAnimatorCallback::OnStop(UIView& view)
{
    UITextureMapper& mapper = static_cast<UITextureMapper&>(view);
    if (mapper.listener_ != nullptr) {
        mapper.listener_->OnAnimatorStop(view);
    }
}

UITextureMapper::UITextureMapper()
    : animator_(&animatorCallback_, this, 0, false),
      listener_(nullptr),
      pivot_(0, 0),
      rotateCur_(0),
      rotateStart_(0),
      rotateEnd_(0),
      scaleCur_(SCALE_CONVERTION),
      scaleStart_(SCALE_CONVERTION),
      scaleEnd_(SCALE_CONVERTION),
      delayTime_(0),
      easingFunc_(EasingEquation::LinearEaseNone)
{
    AnimatorManager::GetInstance()->Add(&animator_);
}

UITextureMapper::~UITextureMapper()
{
    AnimatorManager::GetInstance()->Remove(&animator_);
}

void UITextureMapper::Start()
{
    rotateStart_ = rotateCur_;
    scaleStart_ = scaleCur_;
    animator_.Start();
}

void UITextureMapper::Cancel()
{
    animator_.Stop();
}

void UITextureMapper::Reset()
{
    Invalidate();
    GetTransformMap().SetPolygon(Polygon());
    Invalidate();
}

void UITextureMapper::Callback()
{
    uint16_t curTime = animator_.GetRunTime();
    if (curTime < delayTime_) {
        return;
    } else {
        Rect viewRect = GetOrigRect();
        TransformMap transMap(viewRect);
        uint16_t actualTime = curTime - delayTime_;
        uint16_t durationTime = animator_.GetTime();

        if (scaleStart_ != scaleEnd_) {
            scaleCur_ = easingFunc_(scaleStart_, scaleEnd_, actualTime, durationTime);
        }
        float scale = static_cast<float>(scaleCur_) / SCALE_CONVERTION;
        transMap.Scale(Vector2<float>(scale, scale), pivot_);

        if (rotateStart_ != rotateEnd_) {
            rotateCur_ = easingFunc_(rotateStart_, rotateEnd_, actualTime, durationTime);
        }
        transMap.Rotate(rotateCur_, pivot_);

        SetTransformMap(transMap);
    }
}
}