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

#include "ActsMediaCameraTest.h"
#include "camera_config.h"
#include "camera_device_callback.h"
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

using namespace std;
using namespace OHOS::Media;
using namespace testing::ext;

const int FRAME_RATE_DEFAULT = 30;
EventHandler *g_hdl = nullptr;

// SetUpTestCase：测试套预置动作，在第一个TestCase之前执行
void ActsMediaCameraTest::SetUpTestCase(void)
{
    g_hdl = new EventHandler;
    cout << "SetUpTestCase" << endl;
}
// TearDownTestCase：测试套清理动作，在最后一个TestCase之后执行
void ActsMediaCameraTest::TearDownTestCase(void)
{
    if (g_hdl != nullptr) {
        delete g_hdl;
        g_hdl = NULL;
    }
    cout << "TearDownTestCase" << endl;
}
// 用例的预置动作 初始化回调Flag为 FLAG0
void ActsMediaCameraTest::SetUp(void)
{
    // CameraDeviceCallBack
    CameraFlag::g_onCameraAvailableFlag = FLAG0;
    CameraFlag::g_onCameraUnavailableFlag = FLAG0;
    CameraFlag::g_onCameraAccessPrioritiesChangedFlag = FLAG0;
    CameraFlag::g_onTorchModeAvailableFlag = FLAG0;
    CameraFlag::g_onTorchModeUnavailableFlag = FLAG0;

    // CameraStateCallback
    CameraFlag::g_onCreatedFlag = FLAG0;
    CameraFlag::g_onCreateFailedFlag = FLAG0;
    CameraFlag::g_onReleasedFlag = FLAG0;

    // FrameStateCallback
    CameraFlag::g_onCaptureTriggerAbortedFlag = FLAG0;
    CameraFlag::g_onCaptureTriggerCompletedFlag = FLAG0;
    CameraFlag::g_onCaptureTriggerStartedFlag = FLAG0;
    CameraFlag::g_onFrameCompletedFlag = FLAG0;
    CameraFlag::g_onFrameErrorFlag = FLAG0;
    CameraFlag::g_onFrameProgressedFlag = FLAG0;
    CameraFlag::g_onFrameStartedFlag = FLAG0;
    cout << "SetUp" << endl;
}

// 用例的清理动作
void ActsMediaCameraTest::TearDown(void)
{
    cout << "TearDown.." << endl;
}

namespace OHOS::Media {
// 设置保存拍照
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
// 实现framestate callback
class TestFrameStateCallback : public FrameStateCallback {
    void OnFrameCompleted(Camera &camera, FrameConfig &frameConfig, FrameResult frameResult) override
    {
        if (frameConfig.GetFrameConfigType() != CAPTURE) {
            cout << "Test frame completed." << endl;
            return;
        }
        // 写入文件
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

// 实现IBufferConsumerListener回调
class TestConsumer : public IBufferConsumerListener {
    void OnBufferAvailable() override
    {
        return;
    }
};

// 实现CameraStateCallback,进行预览相关操作
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
    // 创建surface并注册
    void GenSurface()
    {
        surface_ = Surface::CreateSurface();
        auto consumer = new TestConsumer;
        surface_->RegisterConsumerListener(*consumer);
    }
    // 相机创建成功，设置surface相关参数
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
    // 相机创建失败
    void OnCreateFailed(std::string cameraId, int32_t errorCode) override
    {
        CameraFlag::g_onCreateFailedFlag = FLAG1;
        printf("OnCreateFailed\n");
    }
    // 相机释放
    void OnReleased(Camera &c) override
    {
        CameraFlag::g_onReleasedFlag = FLAG1;
        printf("OnReleased\n");
    }
    Surface *surface_;
    Camera *camera_;
    FrameStateCallback *fsc_;
};

// 实现CameraStateCallback,进行录像相关操作
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

    void OnCreated(Camera &c) override
    {
        CameraFlag::g_onCreatedFlag = FLAG1;
        printf("OnCreated\n");
        fsc_ = new TestFrameStateCallback;
        CameraConfig *cc = CameraConfig::CreateCameraConfig();
        cc->SetFrameStateCallback(fsc_, g_hdl);
        c.Configure(cc);
        camera_ = &c;
    }
    // 相机创建失败
    void OnCreateFailed(std::string cameraId, int32_t errorCode) override
    {
        CameraFlag::g_onCreateFailedFlag = FLAG1;
        printf("OnCreateFailed\n");
    }
    // 相机释放
    void OnReleased(Camera &c) override
    {
        CameraFlag::g_onReleasedFlag = FLAG1;
        printf("OnReleased\n");
    }

    Surface *surface_;
    Recorder *recorder_;
    Camera *camera_;
    FrameStateCallback *fsc_;
};
} // namespace OHOS::Media

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
 * @tc.number    : SUB_MEDIA_CAMERA_DEV_00100
 * @tc.name      : get cameraKit instance
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(ActsMediaCameraTest, TestCreatCamerakit, TestSize.Level1)
{
    CameraKit *cameraKit = new CameraKit();
    EXPECT_NE(nullptr, cameraKit);
    delete cameraKit;
}

/* *
 * @tc.number    : SUB_MEDIA_CAMERA_DEV_00200
 * @tc.name      : get cameraKit device callback
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(ActsMediaCameraTest, TestCamera002, TestSize.Level1)
{
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    EXPECT_NE(nullptr, deviceCallback);
    delete deviceCallback;
}

/* *
 * @tc.number    : SUB_MEDIA_CAMERA_DEV_00300
 * @tc.name      : get cameraKit state callback
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(ActsMediaCameraTest, TestCamera003, TestSize.Level1)
{
    CameraStateCallback *stateCallback = new CameraStateCallback();
    EXPECT_NE(nullptr, stateCallback);
    delete stateCallback;
}

/* *
 * @tc.number    : SUB_MEDIA_CAMERA_DEV_00400
 * @tc.name      : get cameraKit Envent Handle
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(ActsMediaCameraTest, TestCamera004, TestSize.Level1)
{
    EXPECT_NE(nullptr, g_hdl);
}

/* *
 * @tc.number    : SUB_MEDIA_CAMERA_DEV_00500
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(ActsMediaCameraTest, Test_Camera005, TestSize.Level1)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestCameraStateCallback *stateCallback = new TestCameraStateCallback();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, g_hdl);
    EXPECT_EQ(FLAG1, CameraFlag::g_onCameraAvailableFlag);
    delete cameraKit;
    delete deviceCallback;
    delete stateCallback;
}

/* *
 * @tc.number    : SUB_MEDIA_CAMERA_DEV_00600
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(ActsMediaCameraTest, Test_Camera006, TestSize.Level1)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestCameraStateCallback *stateCallback = new TestCameraStateCallback();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, g_hdl);
    EXPECT_EQ(FLAG1, CameraFlag::g_onCameraAvailableFlag);
    cameraKit->UnregisterCameraDeviceCallback(deviceCallback);
    EXPECT_EQ(FLAG1, CameraFlag::g_onCameraUnavailableFlag);
    delete cameraKit;
    delete deviceCallback;
    delete stateCallback;
}

/* *
 * @tc.number    : SUB_MEDIA_CAMERA_DEV_00700
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(ActsMediaCameraTest, Test_Camera007, TestSize.Level1)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestCameraStateCallback *stateCallback = new TestCameraStateCallback();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, g_hdl);
    std::string cameraId = "camera001";
    cameraKit->CreateCamera(cameraId, stateCallback, g_hdl);
    while (stateCallback->camera_ == nullptr) {
        sleep(1);
    }
    EXPECT_EQ(FLAG1, CameraFlag::g_onCreatedFlag);
    EXPECT_TRUE(stateCallback->camera_);
    EXPECT_TRUE(stateCallback->surface_);
    stateCallback->recorder_->Release();
    sleep(2);
    delete cameraKit;
    delete deviceCallback;
    delete stateCallback;
}

/* *
 * @tc.number    : SUB_MEDIA_CAMERA_DEV_00800
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(ActsMediaCameraTest, Test_Camera008, TestSize.Level0)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestCameraStateCallback *stateCallback = new TestCameraStateCallback();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, g_hdl);
    FrameConfig *fc = new FrameConfig(RECORD); // TODO: NEED TO FREE
    std::string cameraId = "camera001";
    fc->AddSurface(stateCallback->surface_);
    const CameraAbility *cameraAbility = cameraKit->GetCameraAbility(cameraId);
    EXPECT_EQ(1920, cameraAbility->imageSize[0].u32Width);
    EXPECT_EQ(1080, cameraAbility->imageSize[0].u32Height);
    delete fc;
    delete cameraKit;
    delete deviceCallback;
    delete stateCallback;
}

/* *
 * @tc.number    : SUB_MEDIA_CAMERA_DEV_00900
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(ActsMediaCameraTest, Test_Camera009, TestSize.Level0)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestCameraStateCallback *stateCallback = new TestCameraStateCallback();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, g_hdl);
    std::string cameraId = "camera001";
    cameraKit->CreateCamera(cameraId, stateCallback, g_hdl);
    FrameConfig *fc = new FrameConfig(RECORD);
    VideoEncodeParam param;
    param.enGopMode = VENCODE_GOPMODE_NORMALP;
    param.enType = ENCODE_H265;
    param.enRcMode = VENCODE_RC_CBR;
    param.picSize = PIC_1080P;
    param.u32Profile = 0;
    stateCallback->GenSurface(&param);
    stateCallback->recorder_->Prepare();
    stateCallback->surface_ = stateCallback->recorder_->GetSurface(0).get();
    stateCallback->surface_->SetWidthAndHeight(1920, 1080);
    stateCallback->surface_->SetQueueSize(3);
    stateCallback->surface_->SetSize(512 * 1024);
    fc->AddSurface(stateCallback->surface_);
    fc->SetFrameFps(FRAME_RATE_DEFAULT);
    fc->SetVencParam(&param);
    int32_t ret = stateCallback->recorder_->Start();
    stateCallback->camera_->StartLoopingCapture(*fc);
    sleep(5);
    stateCallback->recorder_->Stop(false);
    stateCallback->camera_->StopLoopingCapture();
    stateCallback->recorder_->Release();
    delete fc;
    delete stateCallback;
    delete cameraKit;
    delete deviceCallback;
    sleep(10);
}

/* *
 * @tc.number    : SUB_MEDIA_CAMERA_DEV_01000
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(ActsMediaCameraTest, Test_Camera010, TestSize.Level0)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestCameraStateCallback *stateCallback = new TestCameraStateCallback();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, g_hdl);
    std::string cameraId = "camera001";
    cameraKit->CreateCamera(cameraId, stateCallback, g_hdl);
    while (stateCallback->camera_ == nullptr) {
        sleep(1);
    }
    VideoEncodeParam param;
    param.enGopMode = VENCODE_GOPMODE_NORMALP;
    param.enType = ENCODE_H264;
    param.enRcMode = VENCODE_RC_CBR;
    param.picSize = PIC_1080P;
    param.u32Profile = 0;
    FrameConfig *fc = new FrameConfig(RECORD);
    stateCallback->GenSurface(&param);
    stateCallback->recorder_->Prepare();
    stateCallback->surface_ = stateCallback->recorder_->GetSurface(0).get();
    stateCallback->surface_->SetWidthAndHeight(1920, 1080);
    stateCallback->surface_->SetQueueSize(3);
    stateCallback->surface_->SetSize(512 * 1024);
    fc->AddSurface(stateCallback->surface_);
    fc->SetFrameFps(FRAME_RATE_DEFAULT);
    fc->SetVencParam(&param);
    int32_t ret = stateCallback->recorder_->Start();
    stateCallback->camera_->StartLoopingCapture(*fc);
    sleep(5);
    stateCallback->recorder_->Stop(false);
    stateCallback->camera_->StopLoopingCapture();
    stateCallback->recorder_->Release();
    delete fc;
    delete stateCallback;
    delete cameraKit;
    delete deviceCallback;
}

/* *
 * @tc.number    : SUB_MEDIA_CAMERA_DEV_01100
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(ActsMediaCameraTest, Test_Camera011, TestSize.Level0)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestCameraStateCallback *stateCallback = new TestCameraStateCallback();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, g_hdl);
    std::string cameraId = "camera001";
    cameraKit->CreateCamera(cameraId, stateCallback, g_hdl);
    while (stateCallback->camera_ == NULL) {
        sleep(1);
    }
    FrameConfig *fc = new FrameConfig(RECORD);
    VideoEncodeParam param;
    param.enGopMode = VENCODE_GOPMODE_NORMALP;
    param.enType = ENCODE_H265;
    param.enRcMode = VENCODE_RC_CBR;
    param.picSize = PIC_720P;
    param.u32Profile = 0;
    stateCallback->GenSurface(&param);
    stateCallback->recorder_->Prepare();
    stateCallback->surface_ = stateCallback->recorder_->GetSurface(0).get();
    stateCallback->surface_->SetWidthAndHeight(1280, 720);
    stateCallback->surface_->SetQueueSize(3);
    stateCallback->surface_->SetSize(1024 * 1024);
    fc->AddSurface(stateCallback->surface_);
    fc->SetFrameFps(FRAME_RATE_DEFAULT);
    fc->SetVencParam(&param);
    int32_t ret = stateCallback->recorder_->Start();
    EXPECT_EQ(SUCCESS, ret);
    stateCallback->camera_->StartLoopingCapture(*fc);
    sleep(5);
    stateCallback->recorder_->Stop(false);
    stateCallback->camera_->StopLoopingCapture();
    stateCallback->recorder_->Release();
    delete fc;
    delete cameraKit;
    delete deviceCallback;
    delete stateCallback;
}

/* *
 * @tc.number    : SUB_MEDIA_CAMERA_DEV_01200
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(ActsMediaCameraTest, Test_Camera012, TestSize.Level0)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestCameraStateCallback *stateCallback = new TestCameraStateCallback();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, g_hdl);
    std::string cameraId = "camera001";
    cameraKit->CreateCamera(cameraId, stateCallback, g_hdl);
    VideoEncodeParam param;
    param.enGopMode = VENCODE_GOPMODE_NORMALP;
    param.enType = ENCODE_H264;
    param.enRcMode = VENCODE_RC_CBR;
    param.picSize = PIC_1080P;
    param.u32Profile = 0;
    auto fc1080 = TestCreatCaptureFrameConfig();
    fc1080->SetVencParam(&param);
    stateCallback->camera_->CaptureFrame(*fc1080);
    delete cameraKit;
    delete deviceCallback;
    delete stateCallback;
}

/* *
 * @tc.number    : SUB_MEDIA_CAMERA_DEV_01300
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(ActsMediaCameraTest, Test_Camera013, TestSize.Level0)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestCameraStateCallback *stateCallback = new TestCameraStateCallback();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, g_hdl);
    std::string cameraId = "camera001";
    cameraKit->CreateCamera(cameraId, stateCallback, g_hdl);
    VideoEncodeParam param;
    param.enGopMode = VENCODE_GOPMODE_NORMALP;
    param.enType = ENCODE_H264;
    param.enRcMode = VENCODE_RC_CBR;
    param.picSize = PIC_720P;
    param.u32Profile = 0;
    auto fc720 = TestCreatCaptureFrameConfig();
    fc720->SetVencParam(&param);
    stateCallback->camera_->CaptureFrame(*fc720);
    delete cameraKit;
    delete deviceCallback;
    delete stateCallback;
}

/* *
 * @tc.number    : SUB_MEDIA_CAMERA_PREVIEW_00100
 * @tc.name      : get cameraKit instance ptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(ActsMediaCameraTest, Test_Preview001, TestSize.Level0)
{
    CameraKit *cameraKit = new CameraKit();
    CameraDeviceCallback *deviceCallback = new CameraDeviceCallback();
    TestPreviewCameraStateCallback *stateCallback = new TestPreviewCameraStateCallback();
    cameraKit->RegisterCameraDeviceCallback(deviceCallback, g_hdl);
    std::string cameraId = "camera001";
    cameraKit->CreateCamera(cameraId, stateCallback, g_hdl);
    FrameConfig *fc = new FrameConfig(FrameConfigType::PREVIEW);
    fc->AddSurface(stateCallback->surface_);
    stateCallback->camera_->StartLoopingCapture(*fc);
    printf("start preview---");
    sleep(15);
    stateCallback->camera_->StopLoopingCapture();
    delete fc;
    delete cameraKit;
    delete deviceCallback;
    delete stateCallback;
}