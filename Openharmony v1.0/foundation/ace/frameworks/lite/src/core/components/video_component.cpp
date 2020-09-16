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
#include "video_component.h"
#include "ace_log.h"
#include "key_parser.h"
#include "keys.h"

#ifdef FEATURE_UPDATE_VIDEO_PROGRESS_ASYNC
#include <sys/prctl.h>
#include "ace_ability.h"
#endif // FEATURE_UPDATE_VIDEO_PROGRESS_ASYNC

namespace OHOS {
namespace ACELite {
const char * const VideoComponent::FUNC_START = "start";
const char * const VideoComponent::FUNC_PAUSE = "pause";
const char * const VideoComponent::FUNC_SET_CURRENT_TIME = "setCurrentTime";
const char * const VideoComponent::FUNC_SET_Volume = "setVolume";
List<Component *> VideoComponent::componentNodes_;

#ifdef FEATURE_UPDATE_VIDEO_PROGRESS_ASYNC
pthread_mutex_t VideoComponent::updateLock_ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t VideoComponent::updateCondition_ = PTHREAD_COND_INITIALIZER;
#endif // FEATURE_UPDATE_VIDEO_PROGRESS_ASYN

VideoComponent::VideoComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager)
    : Component(options, children, styleManager),
      videoSourceUrl_(nullptr),
      videoView_(nullptr),
      videoEventListener_(nullptr),
      videoSliderListener_(nullptr),
      videoPlayImageClickListener_(nullptr),
      autoPlay_(false),
      videoMuted_(false),
      isPlaying_(false),
      isReleasing_(false),
      isUpdatingHandlerQuited_(false)
{
    SetComponentName(K_VIDEO);
    RegisterNativeFunctions();
}

void VideoComponent::RegisterNativeFunctions()
{
    RegisterNamedFunction(FUNC_START, Start);
    RegisterNamedFunction(FUNC_PAUSE, Pause);
    RegisterNamedFunction(FUNC_SET_CURRENT_TIME, SetCurrentTime);
    RegisterNamedFunction(FUNC_SET_Volume, SetVolume);
}

void VideoComponent::UpdatePlayImageInfo(bool playFlag)
{
    PanelView* panelView = const_cast<PanelView *>(videoView_->GetPanelView());
    if (panelView == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "video panel get panelview is nullptr");
        return;
    }
    UIImageView *playImageView = const_cast<UIImageView *>(panelView->GetVideoPlayImage());
    if (playImageView == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "video panel get play image view is nullptr");
        return;
    }
    const ImageInfo* imageSrc = playFlag ? GetVideoPlayImageOffInfo() : GetVideoPlayImageOnInfo();
    playImageView->SetSrc(imageSrc);
    if (videoPlayImageClickListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "video panel get image click listener is nullptr");
        return;
    }
    videoPlayImageClickListener_->setVideoPlayImageClickStatus(playFlag);
}
JSValue VideoComponent::Start(const jerry_value_t func,
                              const jerry_value_t context,
                              const jerry_value_t args[],
                              const jerry_length_t argsNum)
{
    VideoView *nativeVideo = reinterpret_cast<VideoView *>(ComponentUtils::GetViewFromBindingObject(context));
    if (nativeVideo == nullptr) {
        return UNDEFINED;
    }
    VideoComponent *videoComponent
        = reinterpret_cast<VideoComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (videoComponent == nullptr) {
        return UNDEFINED;
    }
    if ((nativeVideo->Play()) != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "call VideoComponent::Start failed");
        return UNDEFINED;
    }
    videoComponent->UpdatePlayImageInfo(true);
    HILOG_DEBUG(HILOG_MODULE_ACE, "nativeVideo Start");
    return UNDEFINED;
}

JSValue VideoComponent::Pause(const jerry_value_t func,
                              const jerry_value_t context,
                              const jerry_value_t args[],
                              const jerry_length_t argsNum)
{
    VideoView *nativeVideo = reinterpret_cast<VideoView *>(ComponentUtils::GetViewFromBindingObject(context));
    if (nativeVideo == nullptr) {
        return UNDEFINED;
    }
    VideoComponent *videoComponent =
        reinterpret_cast<VideoComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (videoComponent == nullptr) {
        return UNDEFINED;
    }
    if ((nativeVideo->Pause()) != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "call VideoComponent::Pause failed");
        return UNDEFINED;
    }
    // update panel info
    videoComponent->UpdatePlayImageInfo(false);
    return UNDEFINED;
}

JSValue VideoComponent::SetCurrentTime(const jerry_value_t func,
                                       const jerry_value_t context,
                                       const jerry_value_t args[],
                                       const jerry_length_t argsNum)
{
    VideoView *nativeVideo = reinterpret_cast<VideoView *>(ComponentUtils::GetViewFromBindingObject(context));
    if (nativeVideo == nullptr || argsNum != 1) {
        return UNDEFINED;
    }
    int16_t currentTime = IntegerOf(args[0]);
    if (nativeVideo->SeekTo(currentTime * PanelView::MILLIONS_PER_SECOND) != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "call VideoComponent::SetCurrentTime failed");
        return UNDEFINED;
    }
    // update panel view slider info
    nativeVideo->UpdatePanelTimeText(true);
    return UNDEFINED;
}

JSValue VideoComponent::SetVolume(const jerry_value_t func,
                                  const jerry_value_t context,
                                  const jerry_value_t args[],
                                  const jerry_length_t argsNum)
{
    VideoView *nativeVideo = reinterpret_cast<VideoView *>(ComponentUtils::GetViewFromBindingObject(context));
    if (nativeVideo != nullptr && argsNum == 1) {
        int16_t volumeValue = IntegerOf(args[0]);
        if ((nativeVideo->SetVolume(volumeValue)) != 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "call VideoComponent::SetVolume failed");
            return UNDEFINED;
        }
    }
    return UNDEFINED;
}

bool VideoComponent::CreateNativeViews()
{
    videoView_ = new VideoView();
    if (videoView_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "VideoComponent: create VideoView object failed!");
        return false;
    }
    videoView_->SetPlayStateCallback(this);
    if (!videoView_->CreateVideoView()) {
        return false;
    }
    videoSliderListener_ = new VideoSliderEventListener(videoView_);
    if (videoSliderListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create videoSliderListener_ event failed");
        return false;
    }
    videoPlayImageClickListener_ = new VideoPlayImageOnClickListener(videoView_);
    if (videoPlayImageClickListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create video slider listener failed");
        return false;
    }
    videoEventListener_ = std::make_shared<VideoEventListener>(videoView_, videoPlayImageClickListener_);
    if (videoEventListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "VideoComponent: create videoEventListener_ failed!");
        return false;
    }
    if (!RegisterVideoEventListener()) {
        return false;
    }
    AddComponentNode(this);
    PrepareProgressUpdatingThread();
    return true;
}

void VideoComponent::ReleaseNativeViews()
{
    RemoveComponentNode(this);
    SetComponentReleasingFlag(true);
    // wait until the updating thread destroyed
    pthread_cond_signal(&updateCondition_);
    while (!isUpdatingHandlerQuited_) {
        const uint16_t waitThreadDestoryTime = 20000;
        usleep(waitThreadDestoryTime);
    }
    ACE_DELETE(videoView_);
    ACE_DELETE(videoSliderListener_);
    ACE_DELETE(videoPlayImageClickListener_);
    ACE_FREE(videoSourceUrl_);
    SetComponentReleasingFlag(false);
}
UIView *VideoComponent::GetComponentRootView() const
{
    return videoView_;
}

VideoView *VideoComponent::GetVideoView() const
{
    return videoView_;
}

bool VideoComponent::RegisterVideoEventListener()
{
    PanelView* videoPanelView = const_cast<PanelView *>(videoView_->GetPanelView());
    if (videoPanelView == nullptr) {
        return false;
    }

    UISlider *videoSlider = const_cast<UISlider *>(videoPanelView->GetVideoSlider());
    if (videoSlider == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create get video slider failed");
        return false;
    }
    videoSlider->SetSliderEventListener(videoSliderListener_);
    videoSlider->SetOnClickListener(videoSliderListener_);
    videoSlider->SetTouchable(true);
    videoSlider->SetDraggable(true);

    UIImageView *videoPlayImage = const_cast<UIImageView *>(videoPanelView->GetVideoPlayImage());
    if (videoPlayImage == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create get video play image failed");
        return false;
    }
    videoPlayImage->SetOnClickListener(videoPlayImageClickListener_);
    videoPlayImage->SetTouchable(true);

    UIImageView *videoMutedImage = const_cast<UIImageView *>(videoPanelView->GetVideoMutedImage());
    if (videoMutedImage == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create get video muted image failed");
        return false;
    }
    videoMutedImage->SetOnClickListener(videoPlayImageClickListener_);
    videoMutedImage->SetTouchable(true);

    Media::Player *videoPlayer = const_cast<Media::Player *>(videoView_->GetVideoPlayer());
    if (videoPlayer == nullptr) {
        return false;
    }
    videoPlayer->SetPlayerCallback(videoEventListener_);
    videoView_->SetPlayEventListener(videoEventListener_);
    return true;
}

bool VideoComponent::RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue)
{
    if (videoEventListener_ == nullptr || videoView_ == nullptr || videoSliderListener_ == nullptr) {
        return false;
    }
    switch (eventTypeId) {
        case K_ERROR:
            HILOG_DEBUG(HILOG_MODULE_ACE, "VideoComponent: RegisterListener && bind ERROR callback function");
            videoEventListener_->SetOnErrorFuncName(funcValue);
            break;
        case K_PREPARED:
            HILOG_DEBUG(HILOG_MODULE_ACE, "VideoComponent: RegisterListener && bind PREPARED callback function");
            videoView_->SetPrepareSyncCBFunc(funcValue);
            break;
        case K_START:
            HILOG_DEBUG(HILOG_MODULE_ACE, "VideoComponent: RegisterListener && bind START callback function");
            videoView_->SetStartSyncCBFunc(funcValue);
            break;
        case K_PAUSE:
            HILOG_DEBUG(HILOG_MODULE_ACE, "VideoComponent: RegisterListener && bind PAUSE callback function");
            videoView_->SetPauseSyncCBFunc(funcValue);
            break;
        case K_FINISH:
            HILOG_DEBUG(HILOG_MODULE_ACE, "VideoComponent: RegisterListener && bind FINISH callback function");
            videoEventListener_->SetOnPlayCompleteFuncName(funcValue);
            break;
        case K_SEEKING:
            HILOG_DEBUG(HILOG_MODULE_ACE, "VideoComponent: RegisterListener && bind SEEKING callback function");
            videoSliderListener_->SetOnPlaySeekingFuncName(funcValue);
            break;
        case K_SEEKED:
            HILOG_DEBUG(HILOG_MODULE_ACE, "VideoComponent: RegisterListener && bind SEEKED callback function");
            videoEventListener_->SetOnPlaySeekedFuncName(funcValue);
            break;
        case K_TIME_UPDATE:
            HILOG_DEBUG(HILOG_MODULE_ACE, "VideoComponent: RegisterListener && bind TIME_UPDATE callback function");
            videoView_->SetTimeUpdateSyncCBFunc(funcValue);
            break;
        default:
            return false;
    }
    return true;
}

bool VideoComponent::SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue)
{
    switch (attrKeyId) {
        case K_MUTED: {
            SetMuted(attrValue);
            break;
        }
        case K_SRC: {
            SetVideoSource(attrValue);
            break;
        }
        case K_AUTOPLAY: {
            SetVideoAutoPlay(attrValue);
            break;
        }
        case K_CONTROLS: {
            SetVideoControls(attrValue);
            break;
        }
        default: {
            return false;
        }
    }
    return true;
}

void VideoComponent::SetMuted(jerry_value_t attrValue)
{
    videoMuted_ = BoolOf(attrValue);
    if (videoView_ != nullptr) {
        videoView_->setMuted(videoMuted_);
    }
}

void VideoComponent::SetVideoSource(jerry_value_t attrValue)
{
    ACE_FREE(videoSourceUrl_);
    videoSourceUrl_ = MallocStringOf(attrValue);
    if (videoView_ != nullptr) {
        videoView_->SetVideoSrc(videoSourceUrl_);
    }
}

void VideoComponent::SetVideoAutoPlay(jerry_value_t attrValue)
{
    autoPlay_ = BoolOf(attrValue);
    if (videoView_ != nullptr) {
        videoView_->SetAutoPlayFlag(autoPlay_);
    }
}

void VideoComponent::SetVideoControls(jerry_value_t attrValue)
{
    if ((videoView_ != nullptr) && !BoolOf(attrValue)) {
        videoView_->HideVideoPanel();
    }
}

bool VideoComponent::ApplyPrivateStyle(const AppStyleItem *style)
{
    return false;
}

bool VideoComponent::SetPanelView()
{
    if (videoView_ == nullptr || videoPlayImageClickListener_ == nullptr) {
        return false;
    }
    PanelView *panelView = const_cast<PanelView *>(videoView_->GetPanelView());
    if (panelView == nullptr) {
        return false;
    }
    /* set video total time and slider range */
    int64_t totalPlayTime = 0;
    if (videoView_->GetDuration(totalPlayTime) == 0) {
        UISlider *slider = const_cast<UISlider *>(panelView->GetVideoSlider());
        if (slider == nullptr || totalPlayTime < 0 || totalPlayTime >= PanelView::MAX_SHOW_TIME) {
            return false;
        }
        slider->SetRange(totalPlayTime / PanelView::MILLIONS_PER_SECOND, 0);
    }

    /* set panel info when autoPlay */
    UIImageView *playImageView = const_cast<UIImageView *>(panelView->GetVideoPlayImage());
    if (playImageView == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "video panel get play image view is nullptr");
        return false;
    }
    // set total video time to total label
    videoView_->UpdatePanelTimeText(false);
    if (autoPlay_) {
        if ((videoView_->Play()) == 0) {
            playImageView->SetSrc(GetVideoPlayImageOffInfo());
            videoPlayImageClickListener_->setVideoPlayImageClickStatus(true);
        } else {
            HILOG_ERROR(HILOG_MODULE_ACE, "video play failed");
            return false;
        }
    } else {
        playImageView->SetSrc(GetVideoPlayImageOnInfo());
        videoPlayImageClickListener_->setVideoPlayImageClickStatus(false);
    }
    /* set video volume & panel muted image */
    videoView_->UpdateMutedStatus();
    videoPlayImageClickListener_->setVideoMutedImageClickStatus(videoMuted_);
    videoView_->PanelRefreshLayout();
    return true;
}

void VideoComponent::PostRender()
{
    if (videoView_ == nullptr) {
        return;
    }
    videoView_->SetVideoView();
    if (videoView_->SetSource(videoSourceUrl_) != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PostRender video view SetSource failed");
        return;
    }
    if (videoView_->Prepare() != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PostRender video view prepare failed");
        return;
    }
    if (SetPanelView() == false) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PostRender set panel view failed");
        return;
    }
}

void VideoComponent::PostUpdate(uint16_t attrKeyId, bool updateResult)
{
    if ((videoView_ == nullptr) || !updateResult) {
        HILOG_ERROR(HILOG_MODULE_ACE, "video component post update check args failed");
        return;
    }
    videoView_->WaitRebuildPlayerFinish();
    videoView_->SetVideoView();
    if (SetPanelView() == false) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PostUpdate set panel view failed");
        return;
    }
}
void VideoComponent::SetComponentReleasingFlag(bool releasing)
{
    isReleasing_ = releasing;
}

#ifdef FEATURE_UPDATE_VIDEO_PROGRESS_ASYNC
void VideoComponent::PrepareProgressUpdatingThread()
{
    int ret = pthread_mutex_init(&updateLock_, nullptr);
    if (ret != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "mutex init failed, %{public}d", ret);
        return;
    }
    ret = pthread_cond_init(&updateCondition_, nullptr);
    if (ret != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "condition init failed, %{public}d", ret);
        (void)pthread_mutex_destroy(&updateLock_);
        return;
    }
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    ret = pthread_create(&tid, &attr, VideoComponent::UpdateProgressHandler, this);
    if (ret != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create video progress updating thread error, %{public}d", ret);
        (void)pthread_mutex_destroy(&updateLock_);
        (void)pthread_cond_destroy(&updateCondition_);
        return;
    }
}

void VideoComponent::UpdateProgress()
{
    if (isReleasing_ || !(isPlaying_)) {
        return;
    }
    if (videoView_ != nullptr) {
        videoView_->UpdatePanelProgress();
    }
}

void VideoComponent::SetVideoPlayingFlag(bool playing)
{
    isPlaying_ = playing;
}

bool VideoComponent::IsVideoPlaying() const
{
    return isPlaying_;
}

bool VideoComponent::IsComponentReleasing() const
{
    return isReleasing_;
}

void VideoComponent::NotifyUpdatingThreadDestroy()
{
    (void)pthread_cond_destroy(&updateCondition_);
    (void)pthread_mutex_destroy(&updateLock_);
    isUpdatingHandlerQuited_ = true;
}

void VideoComponent::AddComponentNode(Component *component)
{
    if (component == nullptr) {
        return;
    }
    componentNodes_.PushBack(component);
}

void VideoComponent::RemoveComponentNode(const Component *component)
{
    if (component == nullptr) {
        return;
    }
    ListNode<Component *> *node = componentNodes_.Begin();
    while (node != componentNodes_.End()) {
        if (node->data_ == component) {
            componentNodes_.Remove(node);
            break;
        }
        node = node->next_;
    }
}

bool VideoComponent::ContainComponentNode(Component *component)
{
    if (component == nullptr) {
        return false;
    }
    ListNode<Component *> *node = componentNodes_.Begin();
    while (node != componentNodes_.End()) {
        if (node->data_ == component) {
            return true;
        }
        node = node->next_;
    }
    return false;
}

void VideoComponent::OnPlayStateChanged(VideoPlayState newState)
{
    HILOG_INFO(HILOG_MODULE_ACE, "OnPlayStateChanged called newState[%{public}d]", newState);
    int ret = pthread_mutex_lock(&updateLock_);
    if (ret != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "mutex lock failed when playing state changed, %{public}d", ret);
        return;
    }
    switch (newState) {
        case VideoPlayState::STATE_PLAYING:
            SetVideoPlayingFlag(true);
            ret = pthread_cond_signal(&updateCondition_);
            if (ret != 0) {
                HILOG_ERROR(HILOG_MODULE_ACE, "condition signal failed when playing state changed, %{public}d", ret);
            }
            break;
        default:
            SetVideoPlayingFlag(false);
            break;
    }
    ret = pthread_mutex_unlock(&updateLock_);
    if (ret != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "mutex unlock failed when playing state changed, %{public}d", ret);
    }
}

/* seperated thread to trigger all update progress request */
void *VideoComponent::UpdateProgressHandler(void *arg)
{
    prctl(PR_SET_NAME, "UpdateProgressHandler");
    auto videoComponent = static_cast<VideoComponent *>(arg);
    if (videoComponent == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "videoComponent is nullptr, fail to start loop");
        return nullptr;
    }

    HILOG_INFO(HILOG_MODULE_ACE, "start video progress updating loop");
    while (!(videoComponent->IsComponentReleasing())) {
        if (videoComponent->IsVideoPlaying()) {
            auto task = [videoComponent]() {
                // critical case that the video component has been released but the task is already in queue
                if (!ContainComponentNode(videoComponent)) {
                    return;
                }
                videoComponent->UpdateProgress();
            };
            HILOG_DEBUG(HILOG_MODULE_ACE, "video update progress");
            AceAbility::PostUITask(task);
            usleep(PanelView::UPDATE_CYCLE_MICRO_SECONDS); // request to update for every 250ms
        } else {
            // if the video is paused no need to post task
            int ret = pthread_mutex_lock(&updateLock_);
            if (ret != 0) {
                HILOG_ERROR(HILOG_MODULE_ACE, "mutex lock failed when updating progress, %{public}d", ret);
                break;
            }
            HILOG_INFO(HILOG_MODULE_ACE, "--- video panel update thread wating ----");
            ret = pthread_cond_wait(&updateCondition_, &updateLock_);
            if (ret != 0) {
                HILOG_ERROR(HILOG_MODULE_ACE, "condition wait failed when updating progress, %{public}d", ret);
                (void)pthread_mutex_unlock(&updateLock_);
                break;
            }
            ret = pthread_mutex_unlock(&updateLock_);
            if (ret != 0) {
                HILOG_ERROR(HILOG_MODULE_ACE, "mutex unlock failed when updating progress, %{public}d", ret);
                break;
            }
        }
    }
    videoComponent->NotifyUpdatingThreadDestroy();
    return nullptr;
}
#endif // FEATURE_UPDATE_VIDEO_PROGRESS_ASYNC
} // namespace ACELite
} // namespace OHOS

#endif // FEATURE_COMPONENT_VIDEO
