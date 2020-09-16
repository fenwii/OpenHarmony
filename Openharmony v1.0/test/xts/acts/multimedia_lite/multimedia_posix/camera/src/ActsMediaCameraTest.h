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

#ifndef CAMERA_DEMO_TEST_H
#define CAMERA_DEMO_TEST_H

#include "gtest/gtest.h"

namespace OHOS::Media {
/* 定义函数回调FLAG取值常量 */
enum TestCallBackFlag {
    FLAG0 = 0,
    FLAG1 = 1,
};

/* 预定义测试数据：VideoSize */
enum TestVideoSize {
    WIDTH = 1920,
    HEIGHT = 1080,
};

class ActsMediaCameraTest : public testing::Test {
public:
    // SetUpTestCase：测试套预置动作，在第一个TestCase之前执行
    static void SetUpTestCase(void);
    // TearDownTestCase：测试套清理动作，在最后一个TestCase之后执行
    static void TearDownTestCase(void);
    // 用例的预置动作
    void SetUp(void);
    // 用例的清理动作
    void TearDown(void);
    // 定义两个常量 正常cameraID 和 异常 cameraID
    static const std::string NORMALID;
    static const std::string ABNORMALID;
};

const std::string ActsMediaCameraTest::NORMALID = "0";
const std::string ActsMediaCameraTest::ABNORMALID = "STRING0";

class CameraFlag {
public:
    // CameraDeviceCallBack Flag
    static int32_t g_onCameraAvailableFlag;
    static int32_t g_onCameraUnavailableFlag;
    static int32_t g_onCameraAccessPrioritiesChangedFlag;
    static int32_t g_onTorchModeAvailableFlag;
    static int32_t g_onTorchModeUnavailableFlag;
    // CameraStateCallback
    static int32_t g_onCreatedFlag;
    static int32_t g_onCreateFailedFlag;
    static int32_t g_onReleasedFlag;
    // FrameStateCallback
    static int32_t g_onCaptureTriggerAbortedFlag;
    static int32_t g_onCaptureTriggerCompletedFlag;
    static int32_t g_onCaptureTriggerStartedFlag;
    static int32_t g_onFrameCompletedFlag;
    static int32_t g_onFrameErrorFlag;
    static int32_t g_onFrameProgressedFlag;
    static int32_t g_onFrameStartedFlag;
};
// CameraDeviceCallBack
int32_t CameraFlag::g_onCameraAvailableFlag = FLAG0;
int32_t CameraFlag::g_onCameraUnavailableFlag = FLAG0;
int32_t CameraFlag::g_onCameraAccessPrioritiesChangedFlag = FLAG0;
int32_t CameraFlag::g_onTorchModeAvailableFlag = FLAG0;
int32_t CameraFlag::g_onTorchModeUnavailableFlag = FLAG0;
// CameraStateCallback
int32_t CameraFlag::g_onCreatedFlag = FLAG0;
int32_t CameraFlag::g_onCreateFailedFlag = FLAG0;
int32_t CameraFlag::g_onReleasedFlag = FLAG0;
// FrameStateCallback
int32_t CameraFlag::g_onCaptureTriggerAbortedFlag = FLAG0;
int32_t CameraFlag::g_onCaptureTriggerCompletedFlag = FLAG0;
int32_t CameraFlag::g_onCaptureTriggerStartedFlag = FLAG0;
int32_t CameraFlag::g_onFrameCompletedFlag = FLAG0;
int32_t CameraFlag::g_onFrameErrorFlag = FLAG0;
int32_t CameraFlag::g_onFrameProgressedFlag = FLAG0;
int32_t CameraFlag::g_onFrameStartedFlag = FLAG0;
} // namespace OHOS::Media
#endif // CAMERA_DEMO_TEST_H