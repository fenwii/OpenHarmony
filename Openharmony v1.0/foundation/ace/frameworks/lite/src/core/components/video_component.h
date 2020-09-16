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
#ifndef OHOS_ACELITE_VIDEO_COMPONENT_H
#define OHOS_ACELITE_VIDEO_COMPONENT_H

#include "acelite_config.h"
#ifdef FEATURE_COMPONENT_VIDEO
#ifdef FEATURE_UPDATE_VIDEO_PROGRESS_ASYNC
#include <pthread.h>
#include <unistd.h>
#endif // FEATURE_UPDATE_VIDEO_PROGRESS_ASYNC
#include "component.h"
#include "list.h"
#include "panel_view.h"
#include "video_state_callback.h"
#include "video_view.h"

namespace OHOS {
namespace ACELite {
class VideoPlayImageOnClickListener final : public UIView::OnClickListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(VideoPlayImageOnClickListener);
    explicit VideoPlayImageOnClickListener(VideoView *aceVideo)
        : video_(aceVideo),
          videoPlayImageClick_(false),
          videoMutedImageClick_(false) {}
    ~VideoPlayImageOnClickListener() {}
    bool OnClick(UIView &view, const ClickEvent &event) override
    {
        if (video_ == nullptr) {
            return false;
        }
        UIImageView *image = reinterpret_cast<UIImageView *>(&view);
        if (image == nullptr) {
            return false;
        }
        PanelView* panelView = const_cast<PanelView *>(video_->GetPanelView());
        if (panelView == nullptr) {
            return false;
        }
        UIImageView* playImage = const_cast<UIImageView *>(panelView->GetVideoPlayImage());
        if (playImage != nullptr && playImage == image) {
            if (SetPlayImageInfo(playImage) == false) {
                HILOG_ERROR(HILOG_MODULE_ACE, "set play image info failed.");
                return false;
            }
        }

        UIImageView* mutedImage = const_cast<UIImageView *>(panelView->GetVideoMutedImage());
        if (mutedImage != nullptr && mutedImage == image) {
            if (SetMutedImageInfo(mutedImage) == false) {
                HILOG_ERROR(HILOG_MODULE_ACE, "set muted image info failed.");
                return false;
            }
        }
        video_->PanelRefreshLayout();
        return true;
    }

    bool SetPlayImageInfo(UIImageView* playImage)
    {
        if (video_ == nullptr || playImage == nullptr) {
            return false;
        }
        if (videoPlayImageClick_) {
            if ((video_->Pause()) == 0) {
                playImage->SetSrc(GetVideoPlayImageOnInfo());
                videoPlayImageClick_ = false;
                return true;
            }
        } else {
            if ((video_->Play()) == 0) {
                playImage->SetSrc(GetVideoPlayImageOffInfo());
                videoPlayImageClick_ = true;
                return true;
            }
        }
        return false;
    }

    bool SetMutedImageInfo(UIImageView* mutedImage)
    {
        if (video_ == nullptr || mutedImage == nullptr) {
            return false;
        }
        if (videoMutedImageClick_) {
            if (video_->SetVolume(PanelView::DEFAULT_VOLUME_VALUE) == 0) {
                mutedImage->SetSrc(GetVideoMutedImageOnInfo());
                videoMutedImageClick_ = false;
                return true;
            }
        } else {
            if (video_->SetVolume(0) == 0) {
                mutedImage->SetSrc(GetVideoMutedImageOffInfo());
                video_->setMuted(true);
                videoMutedImageClick_ = true;
                return true;
            }
        }
        return false;
    }

    bool setVideoPlayImageClickStatus(bool status)
    {
        videoPlayImageClick_ = status;
        return true;
    }

    bool setVideoMutedImageClickStatus(bool status)
    {
        videoMutedImageClick_ = status;
        return true;
    }

private:
    VideoView* video_;
    bool videoPlayImageClick_;
    bool videoMutedImageClick_;
};

class VideoSliderEventListener final: public UISlider::UISliderEventListener, public UISlider::OnClickListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(VideoSliderEventListener);
    explicit VideoSliderEventListener(VideoView *aceVideo)
        : video_(aceVideo), playSeekingFunc_(UNDEFINED), progressValue_(0) {}
    ~VideoSliderEventListener()
    {
        ReleaseJerryValue(playSeekingFunc_, VA_ARG_END_FLAG);
    }

    void OnChange(int16_t progress) override
    {
        if (video_ == nullptr) {
            return;
        }
        progressValue_ = progress;
        Media::Player* videoPlayer = const_cast<Media::Player *>(video_->GetPlayer());
        if (videoPlayer != nullptr && videoPlayer->IsPlaying()) {
            // when slider changing && videoPlayer is playing, notify UpdateProgressHandler stop update
            video_->UpdatePlayState(VideoPlayState::STATE_STOPPED);
        }
        video_->SetCurrentPlayTimeText(progress);
        // call js registered on seeking function
        if (!jerry_value_is_function(playSeekingFunc_)) {
            return;
        }
        video_->CallJSFunctionWithOnePara(playSeekingFunc_, progress);
    }

    bool OnClick(UIView& view, const ClickEvent& event) override
    {
        if (SetPlayPositionInfo(progressValue_)) {
            HILOG_DEBUG(HILOG_MODULE_ACE, "slider onClick video to %{public}d", progressValue_);
            return true;
        }
        return false;
    }
    void OnRelease(int16_t progress) override
    {
        if (SetPlayPositionInfo(progress)) {
            HILOG_DEBUG(HILOG_MODULE_ACE, "slider release video to %{public}d", progress);
        }
    }

    bool SetPlayPositionInfo(int16_t progressValue)
    {
        if (video_ == nullptr) {
            return false;
        }
        int64_t playPosition = progressValue * PanelView::MILLIONS_PER_SECOND;
        if (video_->SeekTo(playPosition) == 0) {
            video_->SetCurrentPlayTimeText(progressValue);
            Media::Player* videoPlayer = const_cast<Media::Player *>(video_->GetPlayer());
            if (videoPlayer != nullptr && videoPlayer->IsPlaying()) {
                // when slider clicked && videoPlayer is playing, notify UpdateProgressHandler start update
                video_->UpdatePlayState(VideoPlayState::STATE_PLAYING);
            }
        }
        return true;
    }

    void SetOnPlaySeekingFuncName(jerry_value_t bindFunc)
    {
        playSeekingFunc_ = jerry_acquire_value(bindFunc);
    }
private:
    VideoView* video_;
    jerry_value_t playSeekingFunc_;
    int16_t progressValue_;
};

class VideoEventListener final: public OHOS::Media::PlayerCallback {
public:
    ACE_DISALLOW_COPY_AND_MOVE(VideoEventListener);
    VideoEventListener(VideoView *aceVideo, VideoPlayImageOnClickListener *imageClickListener)
        : playErrorFunc_(UNDEFINED),
          playCompleteFunc_(UNDEFINED),
          playSeekedFunc_(UNDEFINED),
          video_(aceVideo),
          playImageListener_(imageClickListener) {}

    ~VideoEventListener()
    {
        ReleaseJerryValue(playErrorFunc_, playCompleteFunc_, playSeekedFunc_, VA_ARG_END_FLAG);
    }
    void OnError(int32_t errorType, int32_t errorCode) override
    {
        if (video_ == nullptr) {
            return;
        }
        video_->UpdatePlayState(VideoPlayState::STATE_STOPPED);
        if (jerry_value_is_function(playErrorFunc_)) {
            CallJSFunctionAutoRelease(playErrorFunc_, UNDEFINED, nullptr, 0);
        }
        HILOG_DEBUG(HILOG_MODULE_ACE, "video play errorType = %{public}d, errCode= %{public}d", errorType, errorCode);
    }

    void OnPlaybackComplete() override
    {
        if (video_ == nullptr) {
            return;
        }
        video_->UpdatePlayState(VideoPlayState::STATE_STOPPED);
        video_->PrepareRebuildPlayerThread();
        // call js complete function
        if (jerry_value_is_function(playCompleteFunc_)) {
            CallJSFunctionAutoRelease(playCompleteFunc_, UNDEFINED, nullptr, 0);
        }
        // update play image when video play complete
        PanelView* panelView = const_cast<PanelView *>(video_->GetPanelView());
        if (panelView == nullptr) {
            return;
        }
        UIImageView* playImage = const_cast<UIImageView *>(panelView->GetVideoPlayImage());
        if (playImage == nullptr || playImageListener_ == nullptr) {
            return;
        }
        playImage->SetSrc(GetVideoPlayImageOnInfo());
        playImageListener_->setVideoPlayImageClickStatus(false);
        video_->PanelRefreshLayout();
        HILOG_DEBUG(HILOG_MODULE_ACE, "video play complete.");
    }

    void OnInfo(int type, int extra) override
    {
        HILOG_DEBUG(HILOG_MODULE_ACE, "video play on Info. type= %{public}d, extra= %{public}d", type, extra);
    }

    void OnVideoSizeChanged(int width, int height) override
    {
        HILOG_DEBUG(HILOG_MODULE_ACE, "Video Size Changed. width= %{public}d, height= %{public}d", width, height);
    }

    void OnRewindToComplete() override
    {
        if (video_ == nullptr) {
            return;
        }
        PanelView* panelView = const_cast<PanelView *>(video_->GetPanelView());
        if (panelView == nullptr) {
            return;
        }
        const UISlider* slider = panelView->GetVideoSlider();
        if (slider == nullptr) {
            return;
        }
        int16_t sliderValue = slider->GetValue();
        if (!jerry_value_is_function(playSeekedFunc_)) {
            return;
        }
        video_->CallJSFunctionWithOnePara(playSeekedFunc_, sliderValue);
        HILOG_DEBUG(HILOG_MODULE_ACE, "video seek to play complete.");
    }

    void SetOnErrorFuncName(jerry_value_t bindFunc)
    {
        playErrorFunc_ = jerry_acquire_value(bindFunc);
    }

    void SetOnPlayCompleteFuncName(jerry_value_t bindFunc)
    {
        playCompleteFunc_ = jerry_acquire_value(bindFunc);
    }

    void SetOnPlaySeekedFuncName(jerry_value_t bindFunc)
    {
        playSeekedFunc_ = jerry_acquire_value(bindFunc);
    }

private:
    jerry_value_t playErrorFunc_;
    jerry_value_t playCompleteFunc_;
    jerry_value_t playSeekedFunc_;
    VideoView* video_;
    VideoPlayImageOnClickListener* playImageListener_;
};

class VideoComponent : public Component, public VideoStateCallback {
public:
    ACE_DISALLOW_COPY_AND_MOVE(VideoComponent);
    VideoComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager);
    ~VideoComponent() override {}
    void OnPlayStateChanged(VideoPlayState newState) override;

protected:
    bool CreateNativeViews() override;
    void ReleaseNativeViews() override;
    UIView *GetComponentRootView() const override;
    bool SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue) override;
    bool ApplyPrivateStyle(const AppStyleItem* style) override;
    void PostRender() override;
    void PostUpdate(uint16_t attrKeyId, bool updateResult) override;
    bool RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue) override;

    static List<Component *> componentNodes_;

private:
    VideoView *GetVideoView() const;
    bool SetPanelView();
    void SetMuted(jerry_value_t attrValue);
    void SetVideoSource(jerry_value_t attrValue);
    void SetVideoAutoPlay(jerry_value_t attrValue);
    void SetVideoControls(jerry_value_t attrValue);
    void RegisterNativeFunctions();
    bool RegisterVideoEventListener();
    void PrepareProgressUpdatingThread();
    void UpdatePlayImageInfo(bool playFlag);
    void UpdateProgress();
    void SetVideoPlayingFlag(bool playing);
    void SetComponentReleasingFlag(bool releasing);
    bool IsComponentReleasing() const;
    bool IsVideoPlaying() const;
    void NotifyUpdatingThreadDestroy();
    static void AddComponentNode(Component *component);
    static void RemoveComponentNode(const Component *component);
    static bool ContainComponentNode(Component *component);
    static void VideoStateCallback(VideoPlayState state);
    static void *UpdateProgressHandler(void *arg);

    static JSValue Start(const jerry_value_t func,
                         const jerry_value_t context,
                         const jerry_value_t args[],
                         const jerry_length_t argsNum);
    static JSValue Pause(const jerry_value_t func,
                         const jerry_value_t context,
                         const jerry_value_t args[],
                         const jerry_length_t argsNum);
    static JSValue SetCurrentTime(const jerry_value_t func,
                                  const jerry_value_t context,
                                  const jerry_value_t args[],
                                  const jerry_length_t argsNum);

    static JSValue SetVolume(const jerry_value_t func,
                             const jerry_value_t context,
                             const jerry_value_t args[],
                             const jerry_length_t argsNum);

    static const char * const FUNC_START;
    static const char * const FUNC_PAUSE;
    static const char * const FUNC_SET_CURRENT_TIME;
    static const char * const FUNC_SET_Volume;

    char* videoSourceUrl_;
    VideoView* videoView_;
    std::shared_ptr<VideoEventListener> videoEventListener_;
    VideoSliderEventListener* videoSliderListener_;
    VideoPlayImageOnClickListener* videoPlayImageClickListener_;
    bool autoPlay_;
    bool videoMuted_;
    bool isPlaying_;
    bool isReleasing_;
    bool isUpdatingHandlerQuited_;
#ifdef FEATURE_UPDATE_VIDEO_PROGRESS_ASYNC
    static pthread_mutex_t updateLock_;
    static pthread_cond_t updateCondition_;
#endif // FEATURE_UPDATE_VIDEO_PROGRESS_ASYNC
};
} // namespace ACELite
} // namespace OHOS
#endif // FEATURE_COMPONENT_VIDEO
#endif // OHOS_ACELITE_VIDEO_COMPONENT_H
