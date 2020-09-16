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
#include "components/ui_abstract_clock.h"
#include "components/ui_analog_clock.h"
#include "components/ui_image_view.h"

using namespace OHOS;
using namespace testing::ext;

class AnalogClockTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void) {}
    // TearDownTestCase: Testsuit teardown, run after last testcase
    static void TearDownTestCase(void) {}
    // Testcase setup
    virtual void SetUp() {}
    // Testcase teardown
    virtual void TearDown() {}
};

/**
* @tc.number     SUB_UIKIT_NDKAPI_ANALOGCLOCK_ANALOGCLOCK_SETTIME24HOUR_0100
* @tc.name       test analog clock set time 24 hour api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(AnalogClockTest, testAnalogClockSetTime24Hour, TestSize.Level0) {
    UIAnalogClock* clock = new UIAnalogClock();
    uint8_t currentHour = 14;
    uint8_t currentMinute = 40;
    uint8_t currentSecond = 30;
    clock->SetTime24Hour(currentHour, currentMinute, currentSecond);

    EXPECT_EQ(clock->GetCurrentHour(), currentHour);
    EXPECT_EQ(clock->GetCurrentMinute(), currentMinute);
    EXPECT_EQ(clock->GetCurrentSecond(), currentSecond);
    delete(clock);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_ANALOGCLOCK_ANALOGCLOCK_SETTIME12HOURAM_0100
* @tc.name       test analog clock set time 12 hour api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(AnalogClockTest, testAnalogClockSetTime12HourAM, TestSize.Level0) {
    UIAnalogClock* clock = new UIAnalogClock();
    uint8_t currentHour = 10;
    uint8_t currentMinute = 40;
    uint8_t currentSecond = 30;
    clock->SetTime12Hour(currentHour, currentMinute, currentSecond, true);

    EXPECT_EQ(clock->GetCurrentHour(), currentHour);
    EXPECT_EQ(clock->GetCurrentMinute(), currentMinute);
    EXPECT_EQ(clock->GetCurrentSecond(), currentSecond);
    delete(clock);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_ANALOGCLOCK_ANALOGCLOCK_SETTIME12HOURPM_0100
* @tc.name       test analog clock set time 12 hour api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(AnalogClockTest, testAnalogClockSetTime12HourPM, TestSize.Level0) {
    UIAnalogClock* clock = new UIAnalogClock();
    uint8_t currentHour = 10;
    uint8_t currentMinute = 40;
    uint8_t currentSecond = 30;
    clock->SetTime12Hour(currentHour, currentMinute, currentSecond, false);

    EXPECT_EQ(clock->GetCurrentHour(), currentHour + 12);
    EXPECT_EQ(clock->GetCurrentMinute(), currentMinute);
    EXPECT_EQ(clock->GetCurrentSecond(), currentSecond);
    delete(clock);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_ANALOGCLOCK_ANALOGCLOCK_SETWORKMODE_0100
* @tc.name       test analog clock set work mode api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(AnalogClockTest, testAnalogClockSetWorkMode, TestSize.Level0) {
    UIAbstractClock* clock = new UIAbstractClock();
    clock->SetWorkMode(UIAbstractClock::NORMAL);
    EXPECT_EQ(clock->GetWorkMode(), UIAbstractClock::NORMAL);
    clock->SetWorkMode(UIAbstractClock::ALWAYS_ON);
    EXPECT_EQ(clock->GetWorkMode(), UIAbstractClock::ALWAYS_ON);
    delete(clock);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_ANALOGCLOCK_ANALOGCLOCK_SETHANDIMAGE_0100
* @tc.name       test analog clock set hand image api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(AnalogClockTest, testAnalogClockSetHandImage, TestSize.Level0) {
    UIAnalogClock* clock = new UIAnalogClock();
    Point position = { 214, 3 };
    Point center = { 14, 223 };
    clock->SetHandLine(UIAnalogClock::HandType::SECOND_HAND, position, center, Color::White(), 1, 223, 255);
    EXPECT_EQ(clock->GetHandPosition(UIAnalogClock::HandType::SECOND_HAND).x, position.x);
    EXPECT_EQ(clock->GetHandPosition(UIAnalogClock::HandType::SECOND_HAND).y, position.y);
    EXPECT_EQ(clock->GetHandRotateCenter(UIAnalogClock::HandType::SECOND_HAND).x, center.x);
    EXPECT_EQ(clock->GetHandRotateCenter(UIAnalogClock::HandType::SECOND_HAND).y, center.y);
    delete(clock);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_ANALOGCLOCK_ANALOGCLOCK_SETHANDLINE_0100
* @tc.name       test analog clock set hand line api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(AnalogClockTest, testAnalogClockSetHandLine, TestSize.Level0) {
    UIAnalogClock* clock = new UIAnalogClock();
    Point position = { 214, 3 };
    Point center = { 14, 223 };
    UIImageView* image = new UIImageView();
    image->SetSrc("..\\config\\faces\\default\\B024_009.bin");
    clock->SetHandImage(UIAnalogClock::HandType::HOUR_HAND, *image, position, center);
    EXPECT_EQ(clock->GetHandPosition(UIAnalogClock::HandType::HOUR_HAND).x, position.x);
    EXPECT_EQ(clock->GetHandPosition(UIAnalogClock::HandType::HOUR_HAND).y, position.y);
    EXPECT_EQ(clock->GetHandRotateCenter(UIAnalogClock::HandType::HOUR_HAND).x, center.x);
    EXPECT_EQ(clock->GetHandRotateCenter(UIAnalogClock::HandType::HOUR_HAND).y, center.y);
    delete(clock);
    delete(image);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_ANALOGCLOCK_ANALOGCLOCK_SETINITTIME24HOUR_0100
* @tc.name       test analog clock set init time 24 hour api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(AnalogClockTest, testAnalogClockSetInitTime24Hour, TestSize.Level0) {
    uint8_t initHour = 6;
    uint8_t initMinute = 0;
    uint8_t initSecond = 0;
    UIAnalogClock* clock = new UIAnalogClock();
    clock->SetInitTime24Hour(initHour, initMinute, initSecond);
    EXPECT_EQ(clock->GetCurrentHour(), initHour);
    EXPECT_EQ(clock->GetCurrentMinute(), initMinute);
    EXPECT_EQ(clock->GetCurrentSecond(), initSecond);
    EXPECT_EQ(clock->GetHandInitAngle(UIAnalogClock::HandType::HOUR_HAND), 180);
    EXPECT_EQ(clock->GetHandCurrentAngle(UIAnalogClock::HandType::HOUR_HAND), 180);

    uint8_t currentHour = 9;
    uint8_t currentMinute = 0;
    uint8_t currentSecond = 0;
    clock->SetTime24Hour(currentHour, currentMinute, currentSecond);
    EXPECT_EQ(clock->GetHandInitAngle(UIAnalogClock::HandType::HOUR_HAND), 180);
    EXPECT_EQ(clock->GetHandCurrentAngle(UIAnalogClock::HandType::HOUR_HAND), 270);
    delete(clock);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_ANALOGCLOCK_ANALOGCLOCK_SETINITTIME12HOUR_0100
* @tc.name       test analog clock set init time 12 hour api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(AnalogClockTest, testAnalogClockSetInitTime12HourAM, TestSize.Level0) {
    uint8_t initHour = 6;
    uint8_t initMinute = 0;
    uint8_t initSecond = 0;
    UIAnalogClock* clock = new UIAnalogClock();
    clock->SetInitTime12Hour(initHour, initMinute, initSecond, true);
    EXPECT_EQ(clock->GetCurrentHour(), initHour);
    EXPECT_EQ(clock->GetCurrentMinute(), initMinute);
    EXPECT_EQ(clock->GetCurrentSecond(), initSecond);
    EXPECT_EQ(clock->GetHandInitAngle(UIAnalogClock::HandType::HOUR_HAND), 180);
    EXPECT_EQ(clock->GetHandCurrentAngle(UIAnalogClock::HandType::HOUR_HAND), 180);
    delete(clock);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_ANALOGCLOCK_ANALOGCLOCK_SETINITTIME12HOUR_0200
* @tc.name       test analog clock set init time 12 hour api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(AnalogClockTest, testAnalogClockSetInitTime12HourPM, TestSize.Level0) {
    uint8_t initHour = 6;
    uint8_t initMinute = 0;
    uint8_t initSecond = 0;
    UIAnalogClock* clock = new UIAnalogClock();
    clock->SetInitTime12Hour(initHour, initMinute, initSecond, false);
    EXPECT_EQ(clock->GetCurrentHour(), initHour + 12);
    EXPECT_EQ(clock->GetCurrentMinute(), initMinute);
    EXPECT_EQ(clock->GetCurrentSecond(), initSecond);
    EXPECT_EQ(clock->GetHandInitAngle(UIAnalogClock::HandType::HOUR_HAND), 180);
    EXPECT_EQ(clock->GetHandCurrentAngle(UIAnalogClock::HandType::HOUR_HAND), 180);
    delete(clock);
}