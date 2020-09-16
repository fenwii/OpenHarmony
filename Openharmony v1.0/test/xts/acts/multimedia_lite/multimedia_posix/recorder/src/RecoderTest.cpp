/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "camera_config.h"
#include "camera_kit.h"
#include "camera_state_callback.h"
#include "event_handler.h"
#include "frame_config.h"
#include "frame_state_callback.h"
#include "fstream"
#include "iostream"
#include "recorder.h"
#include "surface.h"
#include "thread"
#include "unistd.h"
#include "gtest/gtest.h"
#include <climits>

#define FRAME_RATE_DEFAULT 30
using namespace std;
using namespace OHOS::Media;

using namespace testing::ext;

EventHandler *g_hdl = nullptr;

class RecoderTest : public testing::Test {
protected:
    static void SetUpTestCase(void)
    {
        g_hdl = new EventHandler;
    }
    static void TearDownTestCase(void)
    {
        if (g_hdl != nullptr) {
            delete g_hdl;
            g_hdl = NULL;
        }
    }
    virtual void SetUp() {}
    virtual void TearDown() {}
};

/*
This is recorder format struct
*/
typedef struct Format {
    VideoSourceType VideoSource;
    AudioSourceType AudioSource;
    int32_t AudioChannels;
    AudioCodecFormat AudioEncoder;
    int32_t AudioEncodingBitRate;
    int32_t AudioSampleRate;
    VideoCodecFormat VideoEncoder;
    int32_t VideoEncodingBitRate;
    int32_t VideoFrameRate;
    int32_t width;
    int32_t height;
    double CaptureRate;
} RecorderFormat;

namespace OHOS {
void GenSurface1(RecorderFormat ft);
void TestSaveCapture(char *p, uint32_t size)
{
    cout << "Start saving picture" << endl;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm *ltm = localtime(&tv.tv_sec);
    ostringstream ss("Capture_");
    ss << "Capture" << ltm->tm_hour << "-" << ltm->tm_min << "-" << ltm->tm_sec << ".jpg";

    ofstream pic("/tmp/" + ss.str());
    cout << "write " << size << " bytes" << endl;
    pic.write(p, size);
    cout << "Saving picture end" << endl;
}

class TestFrameStateCallback : public FrameStateCallback {
    void OnFrameCompleted(Camera &camera, FrameConfig &frameConfig, FrameResult frameResult) override
    {
        if (frameConfig.GetFrameConfigType() != CAPTURE) {
            cout << "Test frame completed." << endl;
            return;
        }
        // write file;
        cout << "Try to read picture." << endl;
        auto surfaceList = frameConfig.GetSurfaceList();
        Surface *surface = nullptr;
        if (surfaceList->empty()) {
            delete &frameConfig;
            cout << "Receive empty frame config" << endl;
            return;
        }
        surface = surfaceList->front();
        SurfaceBuffer *buffer = surface->AcquireBuffer();
        if (buffer != nullptr) {
            TestSaveCapture(static_cast<char *>(buffer->GetVirAddr()), buffer->GetSize());
            surface->ReleaseBuffer(buffer);
        }

        delete surface;
        delete &frameConfig;
    }
};

class TestConsumer : public IBufferConsumerListener {
    void OnBufferAvailable() override
    {
        return;
    }
};

class TestPreviewCameraStateCallback : public CameraStateCallback {
public:
    TestPreviewCameraStateCallback() : camera_(nullptr), fsc_(nullptr), surface_(nullptr) {}
    ~TestPreviewCameraStateCallback()
    {
        if (surface_ != nullptr) {
            delete surface_;
        }
        if (fsc_ != nullptr) {
            delete fsc_;
        }
    }
    void GenSurface()
    {
        surface_ = Surface::CreateSurface();
        auto consumer = new TestConsumer;
        surface_->RegisterConsumerListener(*consumer);
    }
    void OnCreated(Camera &c) override
    {
        fsc_ = new TestFrameStateCallback;
        CameraConfig *cc = CameraConfig::CreateCameraConfig();
        cc->SetFrameStateCallback(fsc_, g_hdl);
        c.Configure(cc);
        GenSurface();
        surface_->SetUserData("region_position_x", "100");
        surface_->SetUserData("region_position_y", "100");
        surface_->SetUserData("region_width", "192");
        surface_->SetUserData("region_height", "108");
        surface_->SetQueueSize(2);
        surface_->SetWidthAndHeight(1920, 1080);
        camera_ = &c;
    }
    void OnCreateFailed(std::string cameraId, int32_t errorCode) override
    {
        printf("OnCreateFailed\n");
    }
    void OnReleased(Camera &c) override {}
    Surface *surface_;
    Camera *camera_;
    FrameStateCallback *fsc_;
};

class TestCameraStateCallback : public CameraStateCallback {
public:
    TestCameraStateCallback() : camera_(nullptr), fsc_(nullptr), surface_(nullptr)
    {
        recorder_ = new Recorder();
    }
    ~TestCameraStateCallback()
    {
        if (recorder_ != nullptr) {
            delete recorder_;
        }
        if (fsc_ != nullptr) {
            delete fsc_;
        }
    }
    void GenSurface(VideoEncodeParam *param)
    {
        std::cout << "recorder main " << std::endl;
        int ret = 0;
        int32_t sampleRate = 48000;
        int32_t channelCount = 1;
        AudioCodecFormat audioFormat = AAC_LC;
        AudioSourceType inputSource = AUDIO_MIC;
        int32_t audioEncodingBitRate = sampleRate;
        VideoSourceType source = VIDEO_SOURCE_SURFACE_ES;
        int32_t frameRate = 30;
        float fps = 30;
        int32_t rate = 4096;
        int32_t sourceId = 0;
        int32_t audioSourceId = 0;
        int32_t width = 1920;
        int32_t height = 1080;
        VideoCodecFormat encoder;
        if (param->enType == ENCODE_H265) {
            encoder = HEVC;
        } else {
            encoder = H264;
        }
        if (param->picSize == PIC_1080P) {
            width = 1920;
            height = 1080;
        } else {
            width = 1280;
            height = 720;
        }
        if ((ret = recorder_->SetVideoSource(source, sourceId)) != SUCCESS) {
            printf("SetVideoSource fialed :0x%x\n", ret);
        }
        if ((ret = recorder_->SetVideoEncoder(sourceId, encoder)) != SUCCESS) {
            printf("SetVideoEncoder fialed :0x%x\n", ret);
        }
        if ((ret = recorder_->SetVideoSize(sourceId, width, height)) != SUCCESS) {
            printf("SetVideoSize fialed :0x%x\n", ret);
        }
        if ((ret = recorder_->SetVideoFrameRate(sourceId, frameRate)) != SUCCESS) {
            printf("SetVideoFrameRate fialed :0x%x\n", ret);
        }
        if ((ret = recorder_->SetVideoEncodingBitRate(sourceId, rate)) != SUCCESS) {
            printf("SetVideoEncodingBitRate fialed :0x%x\n", ret);
        }
        if ((ret = recorder_->SetCaptureRate(sourceId, frameRate)) != SUCCESS) {
            printf("SetCaptureRate fialed :0x%x\n", ret);
        }
        if ((ret = recorder_->SetAudioSource(inputSource, audioSourceId)) != SUCCESS) {
            printf("SetAudioSource fialed :0x%x\n", ret);
        }
        if ((ret = recorder_->SetAudioEncoder(audioSourceId, audioFormat)) != SUCCESS) {
            printf("SetAudioEncoder fialed :0x%x\n", ret);
        }
        if ((ret = recorder_->SetAudioSampleRate(audioSourceId, sampleRate)) != SUCCESS) {
            printf("SetAudioSampleRate fialed :0x%x\n", ret);
        }
        if ((ret = recorder_->SetAudioChannels(audioSourceId, channelCount)) != SUCCESS) {
            printf("SetAudioChannels fialed :0x%x\n", ret);
        }
        if ((ret = recorder_->SetAudioEncodingBitRate(audioSourceId, audioEncodingBitRate)) != SUCCESS) {
            printf("SetAudioEncodingBitRate fialed :0x%x\n", ret);
        }
    }

    int32_t GenSurface1(RecorderFormat ft)
    {
        VideoSourceType source = ft.VideoSource;
        AudioSourceType inputSource = ft.AudioSource;
        int32_t channelCount = ft.AudioChannels;
        AudioCodecFormat audioFormat = ft.AudioEncoder;
        int32_t audioEncodingBitRate = ft.AudioEncodingBitRate;
        int32_t sampleRate = ft.AudioSampleRate;
        VideoCodecFormat encoder = ft.VideoEncoder;
        int32_t rate = ft.VideoEncodingBitRate;
        int32_t frameRate = ft.VideoFrameRate;
        int32_t width = ft.width;
        int32_t height = ft.height;
        double fps = ft.CaptureRate;
        int32_t sourceId = 0;
        int32_t audioSourceId = 0;
        int32_t ret = 0;
        if ((ret = recorder_->SetVideoSource(source, sourceId)) != SUCCESS) {
            printf("SetVideoSource fialed :0x%x\n", ret);
            return ret;
        }
        surface_ = recorder_->GetSurface(sourceId).get();
        surface_->SetWidthAndHeight(width, height);

        printf("SetVideoSource SUCCESS\n");
        if ((ret = recorder_->SetVideoEncoder(sourceId, encoder)) != SUCCESS) {
            printf("SetVideoEncoder fialed :0x%x\n", ret);
            return ret;
        }
        printf("SetVideoSource SUCCESS\n");
        if ((ret = recorder_->SetVideoSize(sourceId, width, height)) != SUCCESS) {
            printf("SetVideoSize fialed :0x%x\n", ret);
            return ret;
        }
        printf("SetVideoSize SUCCESS\n");
        if ((ret = recorder_->SetVideoFrameRate(sourceId, frameRate)) != SUCCESS) {
            printf("SetVideoFrameRate fialed :0x%x\n", ret);
            return ret;
        }
        printf("SetVideoFrameRate SUCCESS\n");
        if ((ret = recorder_->SetVideoEncodingBitRate(sourceId, rate)) != SUCCESS) {
            printf("SetVideoEncodingBitRate fialed :0x%x\n", ret);
            return ret;
        }
        printf("SetVideoEncodingBitRate SUCCESS\n");
        if ((ret = recorder_->SetCaptureRate(sourceId, fps)) != SUCCESS) {
            printf("SetCaptureRate fialed :0x%x\n", ret);
            return ret;
        }
        if ((ret = recorder_->SetAudioSource(inputSource, audioSourceId)) != SUCCESS) {
            printf("SetAudioSource fialed :0x%x\n", ret);
            return ret;
        }
        printf("SetAudioSource SUCCESS\n");
        if ((ret = recorder_->SetAudioEncoder(audioSourceId, audioFormat)) != SUCCESS) {
            printf("SetAudioEncoder fialed :0x%x\n", ret);
            return ret;
        }
        printf("SetAudioEncoder SUCCESS\n");
        if ((ret = recorder_->SetAudioSampleRate(audioSourceId, sampleRate)) != SUCCESS) {
            printf("SetAudioSampleRate fialed :0x%x\n", ret);
            return ret;
        }
        printf("SetAudioSampleRate SUCCESS\n");
        if ((ret = recorder_->SetAudioChannels(audioSourceId, channelCount)) != SUCCESS) {
            printf("SetAudioChannels fialed :0x%x\n", ret);
            return ret;
        }
        printf("SetAudioChannels SUCCESS\n");
        if ((ret = recorder_->SetAudioEncodingBitRate(audioSourceId, audioEncodingBitRate)) != SUCCESS) {
            printf("SetAudioEncodingBitRate fialed :0x%x\n", ret);
            return ret;
        }
        printf("SetAudioEncodingBitRate SUCCESS\n");
        if ((ret = recorder_->Prepare()) != SUCCESS) {
            printf("Prepare fialed :0x%x\n", ret);
            return ret;
        }
        printf("Prepare SUCCESS\n");

        return SUCCESS;
    }
    void OnCreated(Camera &c) override
    {
        fsc_ = new TestFrameStateCallback;
        CameraConfig *cc = CameraConfig::CreateCameraConfig();
        cc->SetFrameStateCallback(fsc_, g_hdl);
        c.Configure(cc);
        camera_ = &c;
    }
    void OnCreateFailed(std::string cameraId, int32_t errorCode) override
    {
        printf("OnCreateFailed\n");
    }
    void OnReleased(Camera &c) override {}
    Surface *surface_;
    Recorder *recorder_;
    Camera *camera_;
    FrameStateCallback *fsc_;
};
} // namespace OHOS

using namespace OHOS;
using namespace std;
FrameConfig *TestCreatCaptureFrameConfig()
{
    FrameConfig *fc = new FrameConfig(CAPTURE);
    Surface *surface = Surface::CreateSurface();
    surface->SetWidthAndHeight(1920, 1080);
    fc->AddSurface(surface);
    return fc;
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_03400
 * @tc.name      : test recoder setting parms
 * @tc.desc      : test recoder setting parms avaliable
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(RecoderTest, Test_Recorder_0010, TestSize.Level0)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestCameraStateCallback *stateCallback = new TestCameraStateCallback();
    EventHandler *handler = new EventHandler();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, handler);
    RecorderFormat fmt = { VIDEO_SOURCE_SURFACE_ES, AUDIO_MIC, 1, AAC_LC, 16000, 24000, H264, 1, 1, 900, 600, 30.0 };
    int32_t ret = stateCallback->GenSurface1(fmt);
    EXPECT_EQ(SUCCESS, ret);
    std::string cameraId = "camera001";
    cameraKit->CreateCamera(cameraId, stateCallback, handler);
    VideoEncodeParam param;
    param.enGopMode = VENCODE_GOPMODE_NORMALP;
    param.enType = ENCODE_H265;
    param.enRcMode = VENCODE_RC_CBR;
    param.picSize = PIC_1080P;
    FrameConfig *fc = new FrameConfig(RECORD);
    fc->AddSurface(stateCallback->surface_);
    fc->SetFrameFps(25);
    fc->SetVencParam(&param);
    ret = stateCallback->recorder_->Start();
    EXPECT_EQ(SUCCESS, ret);
    stateCallback->camera_->StartLoopingCapture(*fc);
    sleep(5);
    int32_t ret2 = stateCallback->recorder_->Pause();
    EXPECT_EQ(SUCCESS, ret2);
    sleep(2);
    int32_t ret3 = stateCallback->recorder_->Stop(true);
    EXPECT_EQ(SUCCESS, ret3);
    stateCallback->camera_->StopLoopingCapture();
    stateCallback->recorder_->Release();
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_03300
 * @tc.name      : test recoder setting parms
 * @tc.desc      : test recoder setting parms avaliable
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(RecoderTest, Test_Recorder_0020, TestSize.Level0)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestCameraStateCallback *stateCallback = new TestCameraStateCallback();
    EventHandler *handler = new EventHandler();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, handler);
    RecorderFormat fmt = { VIDEO_SOURCE_SURFACE_ES, AUDIO_MIC, 1, AAC_LC, 16000, 24000, H264, 1, 1, 800, 600, 30.0 };
    int32_t ret = stateCallback->GenSurface1(fmt);
    EXPECT_EQ(SUCCESS, ret);
    std::string cameraId = "camera001";
    cameraKit->CreateCamera(cameraId, stateCallback, handler);
    VideoEncodeParam param;
    param.enGopMode = VENCODE_GOPMODE_NORMALP;
    param.enType = ENCODE_H265;
    param.enRcMode = VENCODE_RC_CBR;
    param.picSize = PIC_1080P;
    FrameConfig *fc = new FrameConfig(RECORD);
    fc->AddSurface(stateCallback->surface_);
    fc->SetFrameFps(25);
    fc->SetVencParam(&param);
    ret = stateCallback->recorder_->Start();
    EXPECT_EQ(SUCCESS, ret);
    stateCallback->camera_->StartLoopingCapture(*fc);
    sleep(5);
    int32_t ret2 = stateCallback->recorder_->Pause();
    EXPECT_EQ(SUCCESS, ret2);
    sleep(2);
    int32_t ret3 = stateCallback->recorder_->Stop(true);
    EXPECT_EQ(SUCCESS, ret3);
    stateCallback->camera_->StopLoopingCapture();
    stateCallback->recorder_->Release();
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_03200
 * @tc.name      : test recoder setting parms
 * @tc.desc      : test recoder setting parms avaliable
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(RecoderTest, Test_Recorder_0030, TestSize.Level0)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestCameraStateCallback *stateCallback = new TestCameraStateCallback();
    EventHandler *handler = new EventHandler();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, handler);
    RecorderFormat fmt = { VIDEO_SOURCE_SURFACE_ES, AUDIO_MIC, 1, AAC_LC, 16000, 24000, H264, 1, 1, 1920, 1080, 30.0 };
    int32_t ret = stateCallback->GenSurface1(fmt);
    EXPECT_EQ(SUCCESS, ret);
    std::string cameraId = "camera001";
    cameraKit->CreateCamera(cameraId, stateCallback, handler);
    VideoEncodeParam param;
    param.enGopMode = VENCODE_GOPMODE_NORMALP;
    param.enType = ENCODE_H265;
    param.enRcMode = VENCODE_RC_CBR;
    param.picSize = PIC_1080P;
    FrameConfig *fc = new FrameConfig(RECORD);
    fc->AddSurface(stateCallback->surface_);
    fc->SetFrameFps(25);
    fc->SetVencParam(&param);
    ret = stateCallback->recorder_->Start();
    EXPECT_EQ(SUCCESS, ret);
    stateCallback->camera_->StartLoopingCapture(*fc);
    sleep(5);
    int32_t ret2 = stateCallback->recorder_->Pause();
    EXPECT_EQ(SUCCESS, ret2);
    sleep(2);
    int32_t ret3 = stateCallback->recorder_->Stop(true);
    EXPECT_EQ(SUCCESS, ret3);
    stateCallback->camera_->StopLoopingCapture();
    stateCallback->recorder_->Release();
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_03100
 * @tc.name      : test recoder setting parms
 * @tc.desc      : test recoder setting parms avaliable
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(RecoderTest, Test_Recorder_0040, TestSize.Level0)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestCameraStateCallback *stateCallback = new TestCameraStateCallback();
    EventHandler *handler = new EventHandler();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, handler);
    RecorderFormat fmt = { VIDEO_SOURCE_SURFACE_ES, AUDIO_MIC, 1, AAC_LC, 16000, 24000, HEVC, 1, 1, 1920, 1080, 30.0 };
    int32_t ret = stateCallback->GenSurface1(fmt);
    EXPECT_EQ(SUCCESS, ret);
    std::string cameraId = "camera001";
    cameraKit->CreateCamera(cameraId, stateCallback, handler);
    VideoEncodeParam param;
    param.enGopMode = VENCODE_GOPMODE_NORMALP;
    param.enType = ENCODE_H265;
    param.enRcMode = VENCODE_RC_CBR;
    param.picSize = PIC_1080P;
    FrameConfig *fc = new FrameConfig(RECORD);
    fc->AddSurface(stateCallback->surface_);
    fc->SetFrameFps(25);
    fc->SetVencParam(&param);
    ret = stateCallback->recorder_->Start();
    EXPECT_EQ(SUCCESS, ret);
    stateCallback->camera_->StartLoopingCapture(*fc);
    sleep(5);
    int32_t ret2 = stateCallback->recorder_->Pause();
    EXPECT_EQ(SUCCESS, ret2);
    sleep(2);
    int32_t ret3 = stateCallback->recorder_->Stop(true);
    EXPECT_EQ(SUCCESS, ret3);
    stateCallback->camera_->StopLoopingCapture();
    stateCallback->recorder_->Release();
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_03000
 * @tc.name      : test recoder setting parms
 * @tc.desc      : test recoder setting parms avaliable
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(RecoderTest, Test_Recorder_0050, TestSize.Level0)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestCameraStateCallback *stateCallback = new TestCameraStateCallback();
    EventHandler *handler = new EventHandler();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, handler);
    RecorderFormat fmt = { VIDEO_SOURCE_SURFACE_ES, AUDIO_MIC, 1, AAC_LC, 16000, 24000, HEVC, 1, 1, 1920, 1080, 30.0 };
    int32_t ret = stateCallback->GenSurface1(fmt);
    EXPECT_EQ(SUCCESS, ret);
    std::string cameraId = "camera001";
    cameraKit->CreateCamera(cameraId, stateCallback, handler);
    VideoEncodeParam param;
    param.enGopMode = VENCODE_GOPMODE_NORMALP;
    param.enType = ENCODE_H265;
    param.enRcMode = VENCODE_RC_CBR;
    param.picSize = PIC_1080P;
    FrameConfig *fc = new FrameConfig(RECORD);
    fc->AddSurface(stateCallback->surface_);
    fc->SetFrameFps(25);
    fc->SetVencParam(&param);
    ret = stateCallback->recorder_->Start();
    EXPECT_EQ(SUCCESS, ret);
    stateCallback->camera_->StartLoopingCapture(*fc);
    sleep(5);
    int32_t ret2 = stateCallback->recorder_->Pause();
    EXPECT_EQ(SUCCESS, ret2);
    sleep(2);
    int32_t ret3 = stateCallback->recorder_->Stop(true);
    EXPECT_EQ(SUCCESS, ret3);
    stateCallback->camera_->StopLoopingCapture();
    stateCallback->recorder_->Release();
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_00100
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetVideoSource01, TestSize.Level0)
{
    cout << "Test_SetVideoSource01 starting..." << endl;
    Recorder *recorder = new Recorder();
    int32_t sourceId = 0;
    int ret = recorder->SetVideoSource(VIDEO_SOURCE_SURFACE_ES, sourceId);
    EXPECT_EQ(SUCCESS, ret);
    cout << "Test_SetVideoSource01 ending..." << endl;
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_00200
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetVideoSource02, TestSize.Level0)
{
    cout << "Test_SetVideoSource02 starting..." << endl;
    Recorder *recorder = new Recorder();
    int32_t sourceId = 0;
    int ret = recorder->SetVideoSource(VIDEO_SOURCE_SURFACE_YUV, sourceId);
    EXPECT_EQ(SUCCESS, ret);
    cout << "Test_SetVideoSource02 ending..." << endl;
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_00300
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetVideoEncoder01, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t sourceId = 0;
    int ret = recorder->SetVideoSource(VIDEO_SOURCE_SURFACE_ES, sourceId);
    EXPECT_EQ(SUCCESS, ret);
    ret = recorder->SetVideoEncoder(sourceId, HEVC);
    EXPECT_EQ(SUCCESS, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_00400
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetVideoEncoder02, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t sourceId = 10000;
    int ret = recorder->SetVideoEncoder(sourceId, HEVC);
    EXPECT_EQ(ERR_INVALID_PARAM, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_00500
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetVideoSize01, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t sourceId = 0;
    int32_t width = 1920;
    int32_t height = 1080;
    int ret = recorder->SetVideoSource(VIDEO_SOURCE_SURFACE_ES, sourceId);
    EXPECT_EQ(SUCCESS, ret);
    ret = recorder->SetVideoSize(sourceId, width, height);
    EXPECT_EQ(SUCCESS, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_00600
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetVideoSize02, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t sourceId = 0;
    int32_t width = -1920;
    int32_t height = -1080;
    int ret = recorder->SetVideoSource(VIDEO_SOURCE_SURFACE_ES, sourceId);
    EXPECT_EQ(SUCCESS, ret);
    ret = recorder->SetVideoSize(sourceId, width, height);
    EXPECT_EQ(ERR_INVALID_PARAM, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_00700
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetVideoSize03, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t sourceId = 10000;
    int32_t width = 1920;
    int32_t height = 1080;
    int ret = recorder->SetVideoSize(sourceId, width, height);
    EXPECT_EQ(ERR_INVALID_PARAM, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_00800
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetVideoFrameRate01, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t sourceId = 0;
    int32_t frameRate = 30;
    int ret = recorder->SetVideoSource(VIDEO_SOURCE_SURFACE_ES, sourceId);
    EXPECT_EQ(SUCCESS, ret);
    ret = recorder->SetVideoFrameRate(sourceId, frameRate);
    EXPECT_EQ(SUCCESS, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_00900
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetVideoFrameRate02, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t sourceId = 10000;
    int32_t frameRate = 30;
    int ret = recorder->SetVideoFrameRate(sourceId, frameRate);
    EXPECT_EQ(ERR_INVALID_PARAM, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_01000
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetVideoEncodingBitRate01, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t sourceId = 0;
    int32_t rate = 4096;
    int ret = recorder->SetVideoSource(VIDEO_SOURCE_SURFACE_ES, sourceId);
    EXPECT_EQ(SUCCESS, ret);
    ret = recorder->SetVideoEncodingBitRate(sourceId, rate);
    EXPECT_EQ(SUCCESS, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_01100
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetVideoEncodingBitRate02, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t sourceId = 10000;
    int32_t rate = 4096;
    int ret = recorder->SetVideoEncodingBitRate(sourceId, rate);
    EXPECT_EQ(ERR_INVALID_PARAM, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_01200
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetCaptureRate01, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t sourceId = 0;
    double fps = 30.0;
    int ret = recorder->SetVideoSource(VIDEO_SOURCE_SURFACE_ES, sourceId);
    EXPECT_EQ(SUCCESS, ret);
    ret = recorder->SetCaptureRate(sourceId, fps);
    EXPECT_EQ(SUCCESS, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_01300
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetCaptureRate02, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t sourceId = 10000;
    double fps = 30.0;
    int ret = recorder->SetCaptureRate(sourceId, fps);
    EXPECT_EQ(ERR_INVALID_PARAM, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_01400
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetAudioSource01, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t audioSourceId = 0;
    int ret = recorder->SetAudioSource(AUDIO_MIC, audioSourceId);
    EXPECT_EQ(SUCCESS, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_01500
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetAudioSource02, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t audioSourceId = 0;
    int ret = recorder->SetAudioSource(AUDIO_SOURCE_INVALID, audioSourceId);
    EXPECT_EQ(ERR_INVALID_PARAM, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_01600
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetAudioEncoder01, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t audioSourceId = 0;
    int ret = recorder->SetAudioSource(AUDIO_MIC, audioSourceId);
    EXPECT_EQ(SUCCESS, ret);
    ret = recorder->SetAudioEncoder(audioSourceId, AAC_LC);
    EXPECT_EQ(SUCCESS, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_01700
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetAudioEncoder02, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t audioSourceId = 0;
    int ret = recorder->SetAudioSource(AUDIO_MIC, audioSourceId);
    EXPECT_EQ(SUCCESS, ret);
    ret = recorder->SetAudioEncoder(audioSourceId, AUDIO_DEFAULT);
    EXPECT_EQ(ERR_INVALID_PARAM, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_01800
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetAudioEncoder03, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t audioSourceId = 10000;
    int ret = recorder->SetAudioEncoder(audioSourceId, AAC_LC);
    EXPECT_EQ(ERR_INVALID_PARAM, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_01900
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetAudioSampleRate01, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t audioSourceId = 0;
    int32_t sampleRate = 48000;
    int ret = recorder->SetAudioSource(AUDIO_MIC, audioSourceId);
    EXPECT_EQ(SUCCESS, ret);
    ret = recorder->SetAudioSampleRate(audioSourceId, sampleRate);
    EXPECT_EQ(SUCCESS, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_02000
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetAudioSamplingRate02, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t audioSourceId = 10000;
    int32_t sampleRate = 48000;
    int ret = recorder->SetAudioSampleRate(audioSourceId, sampleRate);
    EXPECT_EQ(ERR_INVALID_PARAM, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_02100
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetAudioChannels01, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t audioSourceId = 0;
    int32_t channelCount = 1;
    int ret = recorder->SetAudioSource(AUDIO_MIC, audioSourceId);
    EXPECT_EQ(SUCCESS, ret);
    ret = recorder->SetAudioChannels(audioSourceId, channelCount);
    EXPECT_EQ(SUCCESS, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_02200
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetAudioChannels02, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t audioSourceId = 100000;
    int32_t channelCount = 1;
    int ret = recorder->SetAudioChannels(audioSourceId, channelCount);
    EXPECT_EQ(ERR_INVALID_PARAM, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_02300
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetAudioChannels03, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t audioSourceId = 0;
    int32_t channelCount = 1;
    int ret = recorder->SetAudioChannels(audioSourceId, channelCount);
    EXPECT_EQ(ERR_INVALID_PARAM, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_02400
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetAudioEncodingBitRate01, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t audioSourceId = 0;
    int32_t audioEncodingBitRate = 48000;
    int ret = recorder->SetAudioSource(AUDIO_MIC, audioSourceId);
    EXPECT_EQ(SUCCESS, ret);
    ret = recorder->SetAudioEncodingBitRate(audioSourceId, audioEncodingBitRate);
    EXPECT_EQ(SUCCESS, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_02500
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_SetAudioEncodingBitRate02, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t audioSourceId = 10000;
    int32_t audioEncodingBitRate = 48000;
    int ret = recorder->SetAudioEncodingBitRate(audioSourceId, audioEncodingBitRate);
    EXPECT_EQ(ERR_INVALID_PARAM, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_02600
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_Prepare01, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t sourceId = 0;
    int32_t audioSourceId = 0;
    int ret = recorder->SetVideoSource(VIDEO_SOURCE_SURFACE_ES, sourceId);
    EXPECT_EQ(SUCCESS, ret);
    ret = recorder->SetAudioSource(AUDIO_MIC, audioSourceId);
    EXPECT_EQ(SUCCESS, ret);
    ret = recorder->SetAudioSource(AUDIO_MIC, audioSourceId);
    EXPECT_EQ(SUCCESS, ret);
    ret = recorder->Prepare();
    EXPECT_EQ(ERR_INVALID_PARAM, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_02700
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_GetSurface01, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t sourceId = 0;
    int ret = recorder->SetVideoSource(VIDEO_SOURCE_SURFACE_ES, sourceId);
    EXPECT_EQ(SUCCESS, ret);
    Surface *surface = recorder->GetSurface(sourceId).get();
    ret = (int32_t)(surface == nullptr);
    EXPECT_EQ(SUCCESS, ret);
}

/* *
 * @tc.number    : SUB_MEDIA_REC_PARAM_02800
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(RecoderTest, Test_GetSurface02, TestSize.Level0)
{
    Recorder *recorder = new Recorder();
    int32_t sourceId = 10000;
    Surface *surface = recorder->GetSurface(sourceId).get();
    EXPECT_EQ(nullptr, surface);
}