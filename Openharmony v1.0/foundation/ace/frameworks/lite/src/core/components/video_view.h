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
#ifndef OHOS_ACELITE_VIDEO_VIEW_H
#define OHOS_ACELITE_VIDEO_VIEW_H

#include "acelite_config.h"
#ifdef FEATURE_COMPONENT_VIDEO
#include <pthread.h>
#include <sys/prctl.h>
#include <unistd.h>
#include "ace_log.h"
#include "flex_layout.h"
#include "js_fwk_common.h"
#include "js_app_context.h"
#include "panel_view.h"
#include "player.h"
#include "ui_font.h"
#include "ui_image_view.h"
#include "ui_label.h"
#include "ui_slider.h"
#include "ui_surface_view.h"
#include "ui_text_language.h"
#include "ui_view.h"
#include "ui_view_group.h"
#include "video_state_callback.h"

namespace OHOS {
namespace ACELite {
class VideoView : public FlexLayout, public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(VideoView);
    VideoView();
    ~VideoView();
    bool CreateVideoView();
    void SetVideoView();
    void PanelRefreshLayout();

    /* player info */
    int32_t Prepare();

    int32_t Play();

    int32_t Pause();

    int32_t Stop();

    int32_t SeekTo(int64_t currentTime);

    int32_t SetVolume(float volumeValue);

    int32_t GetCurrentPosition(int64_t &currentPosition);

    int32_t GetDuration(int64_t &duration);

    int32_t SetSource(const char * const videoSourceUrl);

    const Media::Player* GetPlayer() const
    {
        return videoPlayer_;
    }

    /* video pannel info */
    const PanelView* GetPanelView() const
    {
        return panelView_;
    }

    const bool GetMuted() const
    {
        return mutedFlag_;
    }

    void setMuted(bool muted)
    {
        mutedFlag_ = muted;
    }

    void SetVideoSrc(char* src)
    {
        videoSrc_ = src;
    }

    const bool GetAutoPlayFlag() const
    {
        return autoPlayFlag_;
    }

    void SetAutoPlayFlag(bool autoPlayFlag)
    {
        autoPlayFlag_ = autoPlayFlag;
    }

    void UpdateMutedStatus();

    bool HideVideoPanel();

    const Media::Player* GetVideoPlayer() const;

    void UpdatePanelProgress();

    void SetPlayStateCallback(VideoStateCallback *callback)
    {
        playStateCallback_ = callback;
    }

    void UpdatePlayState(VideoPlayState newState);

    bool WaitRebuildPlayerFinish();

    void PrepareRebuildPlayerThread();

    /* set video event sync call back functions */
    void SetPlayEventListener(const std::shared_ptr<Media::PlayerCallback> &cb)
    {
        playEventListener_ = cb;
    }

    const std::shared_ptr<Media::PlayerCallback> GetPlayEventListener() const
    {
        return playEventListener_;
    }

    const jerry_value_t GetPrepareSyncCBFunc() const
    {
        return preparedSyncCallBackFunc_;
    }

    const jerry_value_t GetStartSyncCBFunc() const
    {
        return startSyncCallBackFunc_;
    }

    const jerry_value_t GetPauseSyncCBFunc() const
    {
        return pauseSyncCallBackFunc_;
    }

    const jerry_value_t GetTimeUpdateSyncCBFunc() const
    {
        return timeUpdateSyncCallBackFunc_;
    }

    void SetPrepareSyncCBFunc(jerry_value_t& callBackFunc)
    {
        preparedSyncCallBackFunc_ = jerry_acquire_value(callBackFunc);
    }
    void SetStartSyncCBFunc(jerry_value_t& callBackFunc)
    {
        startSyncCallBackFunc_ = jerry_acquire_value(callBackFunc);
    }
    void SetPauseSyncCBFunc(jerry_value_t& callBackFunc)
    {
        pauseSyncCallBackFunc_ = jerry_acquire_value(callBackFunc);
    }
    void SetTimeUpdateSyncCBFunc(jerry_value_t& callBackFunc)
    {
        timeUpdateSyncCallBackFunc_ = jerry_acquire_value(callBackFunc);
    }

    void FormatTime(uint32_t inSeconds, char* outBuffer, uint8_t bufferLength);
    void UpdatePanelTimeText(bool currentTime = true);
    void SetCurrentPlayTimeText(int16_t progress);
    void CallJSFunctionWithOnePara(const jerry_value_t &callBackFunc, const int64_t inputValue);
private:
    void SetVideoPanel();
    void SetSurfaceView();
    bool ResetPlayer();
    bool DestoryPlayer();
    bool CreatePlayer();
    static void *RebuildPlayerHandler(void *arg);
    static pthread_mutex_t rebuildPlayerlock_;
    static pthread_cond_t rebuildPlayerCondition_;

    PanelView* panelView_;
    Media::Player* videoPlayer_;
    UISurfaceView* surfaceView_;
    std::shared_ptr<Media::PlayerCallback> playEventListener_;
    VideoStateCallback* playStateCallback_;
    jerry_value_t preparedSyncCallBackFunc_;
    jerry_value_t startSyncCallBackFunc_;
    jerry_value_t pauseSyncCallBackFunc_;
    jerry_value_t timeUpdateSyncCallBackFunc_;
    char* videoSrc_;
    bool mutedFlag_;
    bool autoPlayFlag_;
};
} // namespace ACELite
} // namespace OHOS

#endif // FEATURE_COMPONENT_VIDEO
#endif // OHOS_ACELITE_VIDEO_VIEW_H
