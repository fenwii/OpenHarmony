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
#include "acelite_config.h"
#ifdef FEATURE_COMPONENT_VIDEO

#include "video_view.h"
#include "video_state_callback.h"

namespace OHOS {
namespace ACELite {
pthread_mutex_t VideoView::rebuildPlayerlock_ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t VideoView::rebuildPlayerCondition_ = PTHREAD_COND_INITIALIZER;

VideoView::VideoView()
    : panelView_(nullptr),
      videoPlayer_(nullptr),
      surfaceView_(nullptr),
      playEventListener_(nullptr),
      playStateCallback_(nullptr),
      preparedSyncCallBackFunc_(UNDEFINED),
      startSyncCallBackFunc_(UNDEFINED),
      pauseSyncCallBackFunc_(UNDEFINED),
      timeUpdateSyncCallBackFunc_(UNDEFINED),
      videoSrc_(nullptr),
      mutedFlag_(false),
      autoPlayFlag_(false) {}

bool VideoView::CreateVideoView()
{
    videoPlayer_ = new Media::Player();
    surfaceView_ = new UISurfaceView();
    panelView_ = new PanelView();
    if (videoPlayer_ == nullptr || surfaceView_ == nullptr || panelView_ == nullptr || !(panelView_->InitView())) {
        return false;
    }
    Add(surfaceView_);
    Add(panelView_);
    SetLayoutDirection(LAYOUT_VER);
    SetMajorAxisAlign(OHOS::ALIGN_END);
    LayoutChildren();
    return true;
}
void VideoView::SetVideoView()
{
    SetSurfaceView();
    SetVideoPanel();
}

void VideoView::SetSurfaceView()
{
    if (surfaceView_ == nullptr) {
        HILOG_DEBUG(HILOG_MODULE_ACE, "native VideoView get surfaceView is nullptr");
        return;
    }
    surfaceView_->SetPosition(0, 0);
    surfaceView_->SetWidth(GetWidth());
    surfaceView_->SetHeight(GetHeight() - PanelView::DEFAULT_PANEL_HEIGHT);
}

void VideoView::PanelRefreshLayout()
{
    if (panelView_ == nullptr) {
        return;
    }
    panelView_->LayoutChildren();
    panelView_->Invalidate();
    LayoutChildren();
}

VideoView::~VideoView()
{
    if (!DestoryPlayer()) {
        HILOG_ERROR(HILOG_MODULE_ACE, "videoView destroy player failed");
    }
    ACE_DELETE(panelView_);
    ACE_DELETE(surfaceView_);
    jerry_release_value(preparedSyncCallBackFunc_);
    jerry_release_value(startSyncCallBackFunc_);
    jerry_release_value(pauseSyncCallBackFunc_);
    jerry_release_value(timeUpdateSyncCallBackFunc_);
    (void)pthread_mutex_destroy(&rebuildPlayerlock_);
    (void)pthread_cond_destroy(&rebuildPlayerCondition_);
}

const Media::Player *VideoView::GetVideoPlayer() const
{
    return videoPlayer_;
}

/* player info */
int32_t VideoView::Prepare()
{
    if ((videoPlayer_ != nullptr) && (surfaceView_ != nullptr) && (videoPlayer_->Prepare() == 0)) {
        Surface *surface = surfaceView_->GetSurface();
        if (surface == nullptr) {
            HILOG_DEBUG(HILOG_MODULE_ACE, "surfaceView get surface failed");
            return -1;
        }
        videoPlayer_->SetVideoSurface(surface);
        /* call js prepare sync callback function */
        if (jerry_value_is_function(preparedSyncCallBackFunc_)) {
            CallJSFunctionAutoRelease(preparedSyncCallBackFunc_, UNDEFINED, nullptr, 0);
        }
        HILOG_DEBUG(HILOG_MODULE_ACE, "native VideoView prepare");
        return 0;
    }
    return -1;
}
int32_t VideoView::Play()
{
    if ((videoPlayer_ != nullptr) && (videoPlayer_->Play() == 0)) {
        /* call js start play sync callback function */
        if (jerry_value_is_function(startSyncCallBackFunc_)) {
            CallJSFunctionAutoRelease(startSyncCallBackFunc_, UNDEFINED, nullptr, 0);
        }
        UpdatePlayState(VideoPlayState::STATE_PLAYING);
        HILOG_DEBUG(HILOG_MODULE_ACE, "native VideoView play");
        return 0;
    }
    return -1;
}
int32_t VideoView::Pause()
{
    if ((videoPlayer_ != nullptr) && (videoPlayer_->Pause() == 0)) {
        /* call js pause play sync callback function */
        if (jerry_value_is_function(pauseSyncCallBackFunc_)) {
            CallJSFunctionAutoRelease(pauseSyncCallBackFunc_, UNDEFINED, nullptr, 0);
        }
        UpdatePlayState(VideoPlayState::STATE_PAUSED);
        HILOG_DEBUG(HILOG_MODULE_ACE, "native VideoView Pause");
        return 0;
    }
    return -1;
}
int32_t VideoView::Stop()
{
    if ((videoPlayer_ != nullptr) && (videoPlayer_->Stop() == 0)) {
        HILOG_DEBUG(HILOG_MODULE_ACE, "native VideoView Stop");
        UpdatePlayState(VideoPlayState::STATE_STOPPED);
        return 0;
    }
    return -1;
}

bool VideoView::WaitRebuildPlayerFinish()
{
    int retCode = pthread_mutex_lock(&rebuildPlayerlock_);
    if (retCode != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "WaitRebuildPlayerFinish mutex lock failed: %d", retCode);
        return false;
    }
    PrepareRebuildPlayerThread();
    (void)pthread_cond_wait(&rebuildPlayerCondition_, &rebuildPlayerlock_);
    retCode = pthread_mutex_unlock(&rebuildPlayerlock_);
    if (retCode != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "WaitRebuildPlayerFinish mutex unlock failed: %d", retCode);
        return false;
    }
    return true;
}
void VideoView::PrepareRebuildPlayerThread()
{
    pthread_t threadId;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int retCode = pthread_create(&threadId, &attr, VideoView::RebuildPlayerHandler, this);
    if (retCode != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "fork play complete thread failed, %{public}d", retCode);
        return;
    }
}

void *VideoView::RebuildPlayerHandler(void *arg)
{
    VideoView *videoView = (VideoView *)arg;
    HILOG_DEBUG(HILOG_MODULE_ACE, "rebuild player handler");
    prctl(PR_SET_NAME, "VideoPlayerRebuildHandler");
    if (!videoView->ResetPlayer()) {
        HILOG_ERROR(HILOG_MODULE_ACE, "videoView reset player failed");
    }
    return nullptr;
}

bool VideoView::ResetPlayer()
{
    (void)pthread_mutex_lock(&rebuildPlayerlock_);
    if (!DestoryPlayer()) {
        HILOG_ERROR(HILOG_MODULE_ACE, "videoView destroy player failed");
    }
    if (!CreatePlayer()) {
        HILOG_ERROR(HILOG_MODULE_ACE, "videoView create player failed");
    }
    (void)pthread_mutex_unlock(&rebuildPlayerlock_);
    int retCode = pthread_cond_signal(&rebuildPlayerCondition_);
    if (retCode != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "mutex unlock failed: %d", retCode);
        return false;
    }
    return true;
}

bool VideoView::DestoryPlayer()
{
    if (videoPlayer_ == nullptr) {
        return false;
    }
    if (videoPlayer_->IsPlaying() && videoPlayer_->Stop() != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "DestoryPlayer fail to stop videoplayer");
    }
    if (videoPlayer_->Reset() != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "DestoryPlayer fail to reset videoplayer");
    }
    if (videoPlayer_->Release() != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "DestoryPlayer fail to release videoplayer");
    }
    delete videoPlayer_;
    videoPlayer_ = nullptr;
    HILOG_DEBUG(HILOG_MODULE_ACE, "delete player");
    return true;
}

bool VideoView::CreatePlayer()
{
    videoPlayer_ = new Media::Player();
    if (videoPlayer_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "fail to create videoplayer");
        return false;
    }
    videoPlayer_->SetPlayerCallback(playEventListener_);
    const float volumeValue = mutedFlag_ ? 0 : PanelView::DEFAULT_VOLUME_VALUE;
    SetVolume(volumeValue);
    if (SetSource(videoSrc_) != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "video view SetSource failed");
        return false;
    }
    if (Prepare() != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "video view prepare failed");
        return false;
    }
    HILOG_DEBUG(HILOG_MODULE_ACE, "reCreate player success");
    return true;
}

void VideoView::UpdatePlayState(VideoPlayState newState)
{
    if (playStateCallback_ != nullptr) {
        playStateCallback_->OnPlayStateChanged(newState);
    }
}

int32_t VideoView::SeekTo(int64_t currentTime)
{
    if ((videoPlayer_ != nullptr) &&
        videoPlayer_->Rewind(currentTime, Media::PlayerSeekMode::PLAYER_SEEK_CLOSEST_SYNC) == 0) {
        HILOG_DEBUG(HILOG_MODULE_ACE, "native VideoView SeekTo %{public}lld", currentTime);
        return 0;
    }
    return -1;
}

int32_t VideoView::SetVolume(float volumeValue)
{
    if ((videoPlayer_ != nullptr) && videoPlayer_->SetVolume(volumeValue, volumeValue) == 0) {
        HILOG_DEBUG(HILOG_MODULE_ACE, "native VideoView setVolume %{public}f", volumeValue);
        return 0;
    }
    return -1;
}

int32_t VideoView::GetCurrentPosition(int64_t &currentPosition)
{
    if ((videoPlayer_ != nullptr) && videoPlayer_->GetCurrentTime(currentPosition) == 0) {
        HILOG_DEBUG(HILOG_MODULE_ACE, "native VideoView GetCurrentTime %{public}lld", currentPosition);
        return 0;
    }
    return -1;
}

/* get video total time */
int32_t VideoView::GetDuration(int64_t &duration)
{
    if ((videoPlayer_ != nullptr) && videoPlayer_->GetDuration(duration) == 0) {
        HILOG_DEBUG(HILOG_MODULE_ACE, "native VideoView GetDuration %{public}lld", duration);
        return 0;
    }
    return -1;
}

int32_t VideoView::SetSource(const char * const videoSourceUrl)
{
    if ((videoPlayer_ == nullptr) || (videoSourceUrl == nullptr)) {
        HILOG_DEBUG(HILOG_MODULE_ACE, "native VideoView videoSourceUrl is nullptr");
        return -1;
    }
    std::string uri(videoSourceUrl);
    std::map<std::string, std::string> header;
    Media::Source source(uri, header);
    if (videoPlayer_->SetSource(source) == 0) {
        HILOG_DEBUG(HILOG_MODULE_ACE, "native VideoView set source success, %{public}s", videoSourceUrl);
        return 0;
    }
    return -1;
}

/* pannel info */
bool VideoView::HideVideoPanel()
{
    if (panelView_ == nullptr) {
        return false;
    }
    UILabel* curPlayTime = const_cast<UILabel *>(panelView_->GetCurTimeText());
    if (curPlayTime != nullptr) {
        curPlayTime->SetVisible(false);
    }
    UIImageView* playImage = const_cast<UIImageView *>(panelView_->GetVideoPlayImage());
    if (playImage != nullptr) {
        playImage->SetVisible(false);
    }
    UISlider* slider = const_cast<UISlider *>(panelView_->GetVideoSlider());
    if (slider != nullptr) {
        slider->SetVisible(false);
    }
    UILabel* totalTimeLabel = const_cast<UILabel *>(panelView_->GetVideoTotalTimeText());
    if (totalTimeLabel != nullptr) {
        totalTimeLabel->SetVisible(false);
    }
    UIImageView* mutedImage = const_cast<UIImageView *>(panelView_->GetVideoMutedImage());
    if (mutedImage != nullptr) {
        mutedImage->SetVisible(false);
    }

    panelView_->SetVisible(false);
    PanelRefreshLayout();
    HILOG_DEBUG(HILOG_MODULE_ACE, "native VideoView hide control panel");
    return true;
}

void VideoView::SetVideoPanel()
{
    if (panelView_ == nullptr) {
        HILOG_DEBUG(HILOG_MODULE_ACE, "native VideoView get panel view is nullptr");
        return;
    }
    const int16_t panelViewWidth = GetWidth();
    const int16_t panelViewHeight = PanelView::DEFAULT_PANEL_HEIGHT;
    const int16_t imageWidth = 48;
    const int16_t imageHeight = 48;
    /* set panelView layout children from left to right in one row */
    (reinterpret_cast<FlexLayout *>(panelView_))->SetLayoutDirection(LAYOUT_HOR);
    SetMajorAxisAlign(OHOS::ALIGN_CENTER);
    panelView_->SetWidth(panelViewWidth);
    panelView_->SetHeight(panelViewHeight);
    /* set video current play time label in video panel */

    UILabel* curTimeLabel = const_cast<UILabel *>(panelView_->GetCurTimeText());
    if (curTimeLabel != nullptr) {
        panelView_->SetTextInPanel(curTimeLabel);
    }
    UIImageView* playImage = const_cast<UIImageView *>(panelView_->GetVideoPlayImage());
    if (playImage != nullptr) {
        panelView_->SetImageInPanel(playImage, imageWidth, imageHeight, GetVideoPlayImageOnInfo());
    }
    /* set video total time label in video panel */
    UILabel* totalTimeLabel = const_cast<UILabel *>(panelView_->GetVideoTotalTimeText());
    if (totalTimeLabel != nullptr) {
        panelView_->SetTextInPanel(totalTimeLabel);
    }
    /* set muted image in video panel */
    UIImageView* mutedImage = const_cast<UIImageView *>(panelView_->GetVideoMutedImage());
    if (mutedImage != nullptr) {
        panelView_->SetImageInPanel(mutedImage, imageWidth, imageHeight, GetVideoMutedImageOffInfo());
    }
    /* video slider set last in video panel, because slider width depend others */
    panelView_->SetVideoSlider();
}

void VideoView::UpdatePanelProgress()
{
    // update current play postion time
    UpdatePanelTimeText(true);
}

void VideoView::SetCurrentPlayTimeText(int16_t inSeconds)
{
    if (panelView_ == nullptr || inSeconds <= 0 || inSeconds >= (PanelView::MAX_HOURS * PanelView::SECONDS_PER_HOUR)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "input duration inSeconds time exception");
        return;
    }
    UILabel *curTimeLabel = const_cast<UILabel *>(panelView_->GetCurTimeText());
    if (curTimeLabel == nullptr) {
        return;
    }
    const uint8_t timeStrLength = 16;
    char timeStr[timeStrLength] = {0};
    FormatTime(inSeconds, timeStr, timeStrLength);
    curTimeLabel->SetText(timeStr);
    curTimeLabel->Invalidate();
}

void VideoView::UpdatePanelTimeText(bool currentTime)
{
    if (panelView_ == nullptr) {
        return;
    }
    UILabel *timeLabel = currentTime ?
        const_cast<UILabel *>(panelView_->GetCurTimeText()) :
        const_cast<UILabel *>(panelView_->GetVideoTotalTimeText());
    if (timeLabel == nullptr) {
        return;
    }

    int64_t duration = 0;
    if (currentTime) {
        if (GetCurrentPosition(duration) != 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "UpdatePanelTimeText GetCurrentPosition failed");
            return;
        }
    } else {
        if (GetDuration(duration) != 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "UpdatePanelTimeText GetDuration failed");
            return;
        }
    }
    if (duration < 0 || duration >= PanelView::MAX_SHOW_TIME) {
        HILOG_ERROR(HILOG_MODULE_ACE, "input duration exception");
        duration = 0;
    }
    const uint8_t timeStrLength = 16;
    char timeStr[timeStrLength] = {0};
    FormatTime((duration / PanelView::MILLIONS_PER_SECOND), timeStr, timeStrLength);
    HILOG_DEBUG(HILOG_MODULE_ACE, "--- set time =%{public}s -----", timeStr);
    timeLabel->SetText(timeStr);
    timeLabel->Invalidate();
    // update video slider status when play changed
    UISlider* videoSlider = const_cast<UISlider *>(panelView_->GetVideoSlider());
    if (videoSlider != nullptr && currentTime) {
        videoSlider->SetValue(duration / PanelView::MILLIONS_PER_SECOND);
        videoSlider->Invalidate();
        // call js timeupdate callback function
        if (!jerry_value_is_function(timeUpdateSyncCallBackFunc_)) {
            return;
        }
        CallJSFunctionWithOnePara(timeUpdateSyncCallBackFunc_, duration / PanelView::MILLIONS_PER_SECOND);
    }
}

void VideoView::UpdateMutedStatus()
{
    if (panelView_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "video view get mpanelView_ is nullptr");
        return;
    }
    UIImageView *mutedImageView = const_cast<UIImageView *>(panelView_->GetVideoMutedImage());
    if (mutedImageView == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "video view get muted image view is nullptr");
        return;
    }
    float volumeValue = mutedFlag_ ? 0 : PanelView::DEFAULT_VOLUME_VALUE;
    const ImageInfo* mutedImageSrc = mutedFlag_ ? GetVideoMutedImageOffInfo() : GetVideoMutedImageOnInfo();
    if (SetVolume(volumeValue) != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "video set volume failed");
        return;
    }
    mutedImageView->SetSrc(mutedImageSrc);
}

void VideoView::FormatTime(uint32_t inSeconds, char *outBuffer, uint8_t bufferLength)
{
    if (inSeconds >= (PanelView::MAX_HOURS * PanelView::SECONDS_PER_HOUR)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "input duration time exception");
        return;
    }
    const uint8_t minBufferLength = 6;  // xx:xx
    const uint8_t minBufferLength2 = 9; // xx:xx:xx
    if (outBuffer == nullptr) {
        return;
    }
    uint8_t hours = inSeconds / PanelView::SECONDS_PER_HOUR;
    uint32_t remainSeconds = inSeconds % PanelView::SECONDS_PER_HOUR;
    uint8_t minutes = remainSeconds / PanelView::SECONDS_PER_MINUTE;
    uint8_t seconds = remainSeconds % PanelView::SECONDS_PER_MINUTE;
    if (hours >= PanelView::MAX_HOURS) {
        HILOG_ERROR(HILOG_MODULE_ACE, "input video length more than the max length");
        return;
    }
    if (hours == 0) {
        if (sprintf_s(outBuffer, bufferLength, "%02d:%02d", minutes, seconds) < 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "xx:xx transfer error");
            return;
        }
        outBuffer[minBufferLength - 1] = '\0';
    } else {
        if (sprintf_s(outBuffer, bufferLength, "%02d:%02d:%02d", hours, minutes, seconds) < 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "xx:xx:xx transfer error");
            return;
        }
        outBuffer[minBufferLength2 - 1] = '\0';
    }
}

void VideoView::CallJSFunctionWithOnePara(const jerry_value_t &callBackFunc, const int64_t inputValue)
{
    if (!jerry_value_is_function(callBackFunc)) {
        return;
    }
    jerry_value_t value = jerry_create_number(inputValue);
    jerry_value_t args[1];
    args[0] = jerry_create_object();
    const char attrName[] = "currenttime";
    jerry_value_t result = jerryx_set_property_str(args[0], attrName, value);
    if (!jerry_value_is_error(result)) {
        CallJSFunctionAutoRelease(callBackFunc, jerry_create_undefined(), args, 1);
    }
    ReleaseJerryValue(result, args[0], value, VA_ARG_END_FLAG);
}
} // namespace ACELite
} // namespace OHOS

#endif // FEATURE_COMPONENT_VIDEO
