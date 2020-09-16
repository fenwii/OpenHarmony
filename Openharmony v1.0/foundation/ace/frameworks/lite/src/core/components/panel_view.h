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
#ifndef OHOS_ACELITE_PANEL_VIEW_H
#define OHOS_ACELITE_PANEL_VIEW_H

#include "acelite_config.h"
#ifdef FEATURE_COMPONENT_VIDEO

#include "ace_log.h"
#include "flex_layout.h"
#include "js_fwk_common.h"
#include "memory_heap.h"
#include "non_copyable.h"
#include "ui_font.h"
#include "ui_image_view.h"
#include "ui_label.h"
#include "ui_slider.h"
#include "ui_text_language.h"
#include "video_panel_image_res.h"

namespace OHOS {
namespace ACELite {
class PanelView : public FlexLayout, public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(PanelView);
    PanelView();
    ~PanelView();

    const UILabel* GetCurTimeText() const;

    const UILabel* GetVideoTotalTimeText() const;

    const UISlider* GetVideoSlider() const;

    const UIImageView* GetVideoPlayImage() const;

    const UIImageView* GetVideoMutedImage() const;

    bool InitView();

    void SetVideoSlider();

    void SetTextInPanel(UILabel* label);

    void SetImageInPanel(UIImageView* image, int16_t imageWidth, int16_t imageHeight, const ImageInfo* imageSrc);

    static const char * const DEFAULT_PLAY_TIME;
    static const uint16_t DEFAULT_VOLUME_VALUE;
    static const uint16_t DEFAULT_PANEL_HEIGHT;
    static const uint8_t SECONDS_PER_MINUTE;
    static const uint16_t MILLIONS_PER_SECOND;
    static const uint16_t SECONDS_PER_HOUR;
    static const uint8_t MAX_HOURS;
    static const uint16_t THOUSAND_MILLISECOND;
    static const int64_t MAX_SHOW_TIME;
    static const uint16_t UPDATE_CYCLE;
    static const uint32_t UPDATE_CYCLE_MICRO_SECONDS;
private:
    UILabel* curTimeLabel_;
    UIImageView* playImage_;
    UISlider* videoSlider_;
    UILabel* totalTimeLabel_;
    UIImageView* mutedImage_;
};
} // namespace ACELite
} // namespace OHOS

#endif // FEATURE_COMPONENT_VIDEO
#endif // OHOS_ACELITE_PANEL_VIEW_H