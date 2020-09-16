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

#include "gtest/gtest.h"
#include <climits>
#include "components/ui_image_animator.h"

using namespace OHOS;
using namespace testing::ext;

class ImageAnimatorTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void) {}
    // TearDownTestCase: Testsuit teardown, run after last testcase
    static void TearDownTestCase(void) {}
    // Testcase setup
    virtual void SetUp() {}
    // Testcase teardown
    virtual void TearDown() {}
    ImageAnimatorInfo imageAnimatorInfoData[4] = {
        { "..\\config\\images\\A021_001.bin", {50, 50},  116, 116 },
        { "..\\config\\images\\A021_002.bin", {50, 50},  116, 116 },
        { "..\\config\\images\\A021_003.bin", {50, 50},  116, 116 },
        { "..\\config\\images\\A021_004.bin", {50, 50},  116, 116 },
    };
};

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGEANIMATOR_IMAGEANIMATOR_TIMEOFUPDATE_0100
* @tc.name       test image animator time of update api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageAnimatorTest, testImageAnimatorTimeOfUpdate, TestSize.Level0) {
    UIImageAnimatorView* imageAnimator = new UIImageAnimatorView();
    uint16_t time = 300;
    imageAnimator->SetTimeOfUpdate(time);

    EXPECT_EQ(imageAnimator->GetTimeOfUpdate(), time);
    delete(imageAnimator);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGEANIMATOR_IMAGEANIMATOR_IMAGEANIMATORSRC_0100
* @tc.name       test image animator image animator src api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageAnimatorTest, testImageAnimatorImageAnimatorSrc, TestSize.Level0) {
    UIImageAnimatorView* imageAnimator = new UIImageAnimatorView();
    uint8_t imageNum = 4;
    imageAnimator->SetImageAnimatorSrc(reinterpret_cast<const char*>(&imageAnimatorInfoData[0]), imageNum);

    EXPECT_EQ(imageAnimator->GetImageAnimatorImageNum(), imageNum);
    delete(imageAnimator);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGEANIMATOR_IMAGEANIMATOR_IMAGEANIMATORSRC_0200
* @tc.name       test image animator image animator src api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageAnimatorTest, testImageAnimatorImageAnimatorSrc2, TestSize.Level0) {
    UIImageAnimatorView* imageAnimator = new UIImageAnimatorView();
    ImageAnimatorInfo* info = &imageAnimatorInfoData[0];
    imageAnimator->SetImageAnimatorSrc(reinterpret_cast<const char*>(&imageAnimatorInfoData[0]), 4);
    EXPECT_EQ(imageAnimator->GetImageAnimatorSrc(), info);
    delete(imageAnimator);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGEANIMATOR_IMAGEANIMATOR_SIZEFIXED_0200
* @tc.name       test image animator size fixed api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageAnimatorTest, testImageAnimatorSzieFixed, TestSize.Level0) {
    UIImageAnimatorView* imageAnimator = new UIImageAnimatorView();
    bool fixed = true;
    imageAnimator->SetSizeFixed(fixed);

    EXPECT_EQ(imageAnimator->IsSizeFixed(), fixed);
    delete(imageAnimator);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGEANIMATOR_IMAGEANIMATOR_REPEAT_0200
* @tc.name       test image animator repeat api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageAnimatorTest, testImageAnimatorRepeat, TestSize.Level0) {
    UIImageAnimatorView* imageAnimator = new UIImageAnimatorView();
    bool repeat = true;
    imageAnimator->SetRepeat(repeat);

    EXPECT_EQ(imageAnimator->IsRepeat(), repeat);
    delete(imageAnimator);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGEANIMATOR_IMAGEANIMATOR_REVERSE_0200
* @tc.name       test image animator reverse api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageAnimatorTest, testImageAnimatorReverse, TestSize.Level0) {
    UIImageAnimatorView* imageAnimator = new UIImageAnimatorView();
    bool reverse = true;
    imageAnimator->SetReverse(reverse);

    EXPECT_EQ(imageAnimator->IsReverse(), reverse);
    delete(imageAnimator);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGEANIMATOR_IMAGEANIMATOR_STATE_0200
* @tc.name       test image animator state api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageAnimatorTest, testImageAnimatorState, TestSize.Level0) {
    UIImageAnimatorView* imageAnimator = new UIImageAnimatorView();
    uint8_t state = Animator::STOP;
    EXPECT_EQ(imageAnimator->GetState(), state);
    delete(imageAnimator);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGEANIMATOR_IMAGEANIMATOR_START_0200
* @tc.name       test image animator start api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageAnimatorTest, testImageAnimatorStart, TestSize.Level0) {
    UIImageAnimatorView* imageAnimator = new UIImageAnimatorView();
    imageAnimator->Start();
    EXPECT_EQ(imageAnimator->GetState(), Animator::START);
    delete(imageAnimator);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGEANIMATOR_IMAGEANIMATOR_STOP_0200
* @tc.name       test image animator stop api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageAnimatorTest, testImageAnimatorStop, TestSize.Level0) {
    UIImageAnimatorView* imageAnimator = new UIImageAnimatorView();
    imageAnimator->Stop(true);
    EXPECT_EQ(imageAnimator->GetState(), Animator::STOP);
    delete(imageAnimator);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGEANIMATOR_IMAGEANIMATOR_PAUSE_0200
* @tc.name       test image animator pause api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageAnimatorTest, testImageAnimatorPause, TestSize.Level0) {
    UIImageAnimatorView* imageAnimator = new UIImageAnimatorView();
    imageAnimator->Pause();
    EXPECT_EQ(imageAnimator->GetState(), Animator::PAUSE);
    delete(imageAnimator);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGEANIMATOR_IMAGEANIMATOR_RESUME_0200
* @tc.name       test image animator resume api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageAnimatorTest, testImageAnimatorResume, TestSize.Level0) {
    UIImageAnimatorView* imageAnimator = new UIImageAnimatorView();
    imageAnimator->Resume();
    EXPECT_EQ(imageAnimator->GetState(), Animator::START);
    delete(imageAnimator);
}