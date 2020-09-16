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
#include "components/root_view.h"
#include "components/ui_digital_clock.h"
#include "components/ui_view_group.h"
#include "font/ui_font.h"

using namespace OHOS;
using namespace testing::ext;

class DigitalClockTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_DIGITALCLOCK_DIGITALCLOCK_DISPLAYMODE_0100
* @tc.name       test digital clock display mode api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(DigitalClockTest, testDigitalClockDisplayMode, TestSize.Level0) {
    UIDigitalClock *clock = new UIDigitalClock();
    clock->SetDisplayMode(UIDigitalClock::DisplayMode::DISPLAY_12_HOUR_NO_SECONDS);
    EXPECT_EQ(clock->GetDisplayMode(), UIDigitalClock::DisplayMode::DISPLAY_12_HOUR_NO_SECONDS);
    clock->SetDisplayMode(UIDigitalClock::DisplayMode::DISPLAY_24_HOUR_NO_SECONDS);
    EXPECT_EQ(clock->GetDisplayMode(), UIDigitalClock::DisplayMode::DISPLAY_24_HOUR_NO_SECONDS);
    clock->SetDisplayMode(UIDigitalClock::DisplayMode::DISPLAY_12_HOUR);
    EXPECT_EQ(clock->GetDisplayMode(), UIDigitalClock::DisplayMode::DISPLAY_12_HOUR);
    clock->SetDisplayMode(UIDigitalClock::DisplayMode::DISPLAY_24_HOUR);
    EXPECT_EQ(clock->GetDisplayMode(), UIDigitalClock::DisplayMode::DISPLAY_24_HOUR);
    delete(clock);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_DIGITALCLOCK_DIGITALCLOCK_OPACITY_0100
* @tc.name       test digital clock set opacity api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(DigitalClockTest, testDigitalClockSetOpacity, TestSize.Level0) {
    uint8_t opacity = 255;
    UIDigitalClock *clock = new UIDigitalClock();
    clock->SetOpacity(opacity);
    EXPECT_EQ(clock->GetOpacity(), opacity);
    delete(clock);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_DIGITALCLOCK_DIGITALCLOCK_SETTIME24HOUR_0100
* @tc.name       test digital clock set time 24 hour api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(DigitalClockTest, testDigitalClockSetTime24Hour, TestSize.Level0) {
    UIDigitalClock *clock = new UIDigitalClock();
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
* @tc.number     SUB_UIKIT_NDKAPI_DIGITALCLOCK_DIGITALCLOCK_SETTIME12HOURAM_0100
* @tc.name       test digital clock set time 12 hour api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(DigitalClockTest, testDigitalClockSetTime12HourAM, TestSize.Level0) {
    UIDigitalClock *clock = new UIDigitalClock();
    uint8_t currentHour = 14;
    uint8_t currentMinute = 40;
    uint8_t currentSecond = 30;
    clock->SetTime12Hour(currentHour, currentMinute, currentSecond, true);
    EXPECT_EQ(clock->GetCurrentHour(), currentHour-12);
    EXPECT_EQ(clock->GetCurrentMinute(), currentMinute);
    EXPECT_EQ(clock->GetCurrentSecond(), currentSecond);
    delete(clock);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_DIGITALCLOCK_DIGITALCLOCK_SETTIME12HOURPM_0100
* @tc.name       test digital clock set time 12 hour api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(DigitalClockTest, testDigitalClockSetTime12HourPM, TestSize.Level0) {
    UIDigitalClock *clock = new UIDigitalClock();
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
* @tc.number     SUB_UIKIT_NDKAPI_DIGITALCLOCK_DIGITALCLOCK_SETFONTID_0200
* @tc.name       test digital clock set font id api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(DigitalClockTest, testDigitalClockSetFontId, TestSize.Level0) {
    UIDigitalClock *clock = new UIDigitalClock();
    uint8_t fontId = 0;
    clock->SetFontId(fontId);
    EXPECT_EQ(clock->GetStyle(STYLE_TEXT_FONT), 0);
    delete(clock);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_DIGITALCLOCK_DIGITALCLOCK_SETWORKMODE_0200
* @tc.name       test digital clock set work mode api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(DigitalClockTest, testDigitalClockSetWorkMode, TestSize.Level0) {
    UIDigitalClock *clock = new UIDigitalClock();

    clock->SetWorkMode(UIAbstractClock::ALWAYS_ON);
    EXPECT_EQ(clock->GetWorkMode(), UIAbstractClock::ALWAYS_ON);
    delete(clock);
}
