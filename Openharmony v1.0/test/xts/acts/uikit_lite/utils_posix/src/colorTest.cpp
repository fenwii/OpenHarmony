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
#include "utils/color.h"

using namespace OHOS;
using namespace testing::ext;

class ColorTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_GETCOLORFROMRGB_0100
* @tc.name       test color get color from rgb api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorGetFromRGB, TestSize.Level0) {
    EXPECT_EQ(Color::GetColorFromRGB(0, 0, 0).red, 0);
    EXPECT_EQ(Color::GetColorFromRGB(0, 0, 0).green, 0);
    EXPECT_EQ(Color::GetColorFromRGB(0, 0, 0).blue, 0);
    EXPECT_EQ(Color::GetColorFromRGB(0, 0, 0).alpha, 0xFF);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_GETCOLORFROMRGBA_0100
* @tc.name       test color get color from rgba api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorGetFromRGBA, TestSize.Level0) {
    EXPECT_EQ(Color::GetColorFromRGBA(0, 0, 0, 0).red, 0);
    EXPECT_EQ(Color::GetColorFromRGBA(0, 0, 0, 0).green, 0);
    EXPECT_EQ(Color::GetColorFromRGBA(0, 0, 0, 0).blue, 0);
    EXPECT_EQ(Color::GetColorFromRGBA(0, 0, 0, 0).alpha, 0);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_TO32_0100
* @tc.name       test color to 32 api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorTo32Test1, TestSize.Level0) {
    ColorType color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;
    color.alpha = 0;
    uint32_t color32 = 0;
    EXPECT_EQ(Color::ColorTo32(color), color32);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_TO32_0200
* @tc.name       test color to 32 api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorTo32Test2, TestSize.Level0) {
    Color16 color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;
    EXPECT_EQ(Color::ColorTo32(color, 0), 0);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_TO16_0200
* @tc.name       test color to 16 api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorTo16, TestSize.Level0) {
    Color32 color32;
    color32.red = 0;
    color32.green = 0;
    color32.blue = 0;
    EXPECT_EQ(Color::ColorTo16(color32), 0);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_WHITE_0200
* @tc.name       test color white api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorWhite, TestSize.Level0) {
    ColorType white = Color::White();
    EXPECT_EQ(white.red, 0xFF);
    EXPECT_EQ(white.green, 0xFF);
    EXPECT_EQ(white.blue, 0xFF);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_SILVER_0200
* @tc.name       test color silver api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorSilver, TestSize.Level0) {
    ColorType silver = Color::Silver();
    EXPECT_EQ(silver.red, 0xC0);
    EXPECT_EQ(silver.green, 0xC0);
    EXPECT_EQ(silver.blue, 0xC0);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_GRAY_0200
* @tc.name       test color gray api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorGray, TestSize.Level0) {
    ColorType gray = Color::Gray();
    EXPECT_EQ(gray.red, 0x80);
    EXPECT_EQ(gray.green, 0x80);
    EXPECT_EQ(gray.blue, 0x80);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_BLACK_0200
* @tc.name       test color black api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorBlack, TestSize.Level0) {
    ColorType black = Color::Black();
    EXPECT_EQ(black.red, 0x00);
    EXPECT_EQ(black.green, 0x00);
    EXPECT_EQ(black.blue, 0x00);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_RED_0200
* @tc.name       test color red api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorRed, TestSize.Level0) {
    ColorType red = Color::Red();
    EXPECT_EQ(red.red, 0xFF);
    EXPECT_EQ(red.green, 0x00);
    EXPECT_EQ(red.blue, 0x00);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_MAROON_0200
* @tc.name       test color maroon api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorMaroon, TestSize.Level0) {
    ColorType maroon = Color::Maroon();
    EXPECT_EQ(maroon.red, 0x80);
    EXPECT_EQ(maroon.green, 0x00);
    EXPECT_EQ(maroon.blue, 0x00);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_YELLOW_0200
* @tc.name       test color yellow api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorYellow, TestSize.Level0) {
    ColorType yellow = Color::Yellow();
    EXPECT_EQ(yellow.red, 0xFF);
    EXPECT_EQ(yellow.green, 0xFF);
    EXPECT_EQ(yellow.blue, 0x00);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_OLIVE_0200
* @tc.name       test color olive api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorOlive, TestSize.Level0) {
    ColorType olive = Color::Olive();
    EXPECT_EQ(olive.red, 0x80);
    EXPECT_EQ(olive.green, 0x80);
    EXPECT_EQ(olive.blue, 0x00);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_LIME_0200
* @tc.name       test color lime api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorLime, TestSize.Level0) {
    ColorType lime = Color::Lime();
    EXPECT_EQ(lime.red, 0x00);
    EXPECT_EQ(lime.green, 0xFF);
    EXPECT_EQ(lime.blue, 0x00);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_GREEN_0200
* @tc.name       test color green api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorGreen, TestSize.Level0) {
    ColorType green = Color::Green();
    EXPECT_EQ(green.red, 0x00);
    EXPECT_EQ(green.green, 0xFF);
    EXPECT_EQ(green.blue, 0x00);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_CYAN_0200
* @tc.name       test color cyan api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorCyan, TestSize.Level0) {
    ColorType cyan = Color::Cyan();
    EXPECT_EQ(cyan.red, 0x00);
    EXPECT_EQ(cyan.green, 0xFF);
    EXPECT_EQ(cyan.blue, 0xFF);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_AQUA_0200
* @tc.name       test color aqua api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorAqua, TestSize.Level0) {
    ColorType aqua = Color::Aqua();
    EXPECT_EQ(aqua.red, 0x00);
    EXPECT_EQ(aqua.green, 0xFF);
    EXPECT_EQ(aqua.blue, 0xFF);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_TEAL_0200
* @tc.name       test color teal api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorTeal, TestSize.Level0) {
    ColorType teal = Color::Teal();
    EXPECT_EQ(teal.red, 0x00);
    EXPECT_EQ(teal.green, 0x80);
    EXPECT_EQ(teal.blue, 0x80);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_BLUE_0200
* @tc.name       test color blue api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorBlue, TestSize.Level0) {
    ColorType blue = Color::Blue();
    EXPECT_EQ(blue.red, 0x00);
    EXPECT_EQ(blue.green, 0x00);
    EXPECT_EQ(blue.blue, 0xFF);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_NAVY_0200
* @tc.name       test color navy api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorNavy, TestSize.Level0) {
    ColorType navy = Color::Navy();
    EXPECT_EQ(navy.red, 0x00);
    EXPECT_EQ(navy.green, 0x00);
    EXPECT_EQ(navy.blue, 0x80);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_MAGENTA_0200
* @tc.name       test color magenta api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorMagenta, TestSize.Level0) {
    ColorType magenta = Color::Magenta();
    EXPECT_EQ(magenta.red, 0xFF);
    EXPECT_EQ(magenta.green, 0x00);
    EXPECT_EQ(magenta.blue, 0xFF);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_PURPLE_0200
* @tc.name       test color purple api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorPurple, TestSize.Level0) {
    ColorType purple = Color::Purple();
    EXPECT_EQ(purple.red, 0x80);
    EXPECT_EQ(purple.green, 0x00);
    EXPECT_EQ(purple.blue, 0x80);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_COLOR_COLOR_Orange_0200
* @tc.name       test color orange api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ColorTest, testColorOrange, TestSize.Level0) {
    ColorType orange = Color::Orange();
    EXPECT_EQ(orange.red, 0xFF);
    EXPECT_EQ(orange.green, 0xA5);
    EXPECT_EQ(orange.blue, 0x00);
}