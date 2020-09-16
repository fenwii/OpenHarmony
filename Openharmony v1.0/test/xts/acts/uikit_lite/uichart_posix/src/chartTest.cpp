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
#include "components/ui_axis.h"
#include "components/ui_chart.h"
#include "components/ui_view_group.h"

using namespace OHOS;
using namespace testing::ext;

class ChartTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_ADDPOINTS_0100
* @tc.name       test chart add points api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartAddPoints, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);
    bool ret = data->AddPoints(nullptr, 0);
    EXPECT_EQ(ret, false);

    Point pointArray[5] = { {0, 2478}, {1, 2600}, {2, 3000}, {3, 3200}, {4, 3500} };
    ret = data->AddPoints(pointArray, 5);
    EXPECT_EQ(ret, true);

    ret = data->AddPoints(pointArray, 1);
    EXPECT_EQ(ret, false);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_GETPOINT_0100
* @tc.name       test chart get point api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartGetPoint, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);

    Point pointArray[5] = { {0, 2478}, {1, 2600}, {2, 3000}, {3, 3200}, {4, 3500} };
    bool ret = data->AddPoints(pointArray, 5);
    EXPECT_EQ(ret, true);

    Point point;
    ret = data->GetPoint(1, point);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(point.x, 1);
    EXPECT_EQ(point.y, 2600);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_MODIFYPOINT_0100
* @tc.name       test chart modify point api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartModifyPoint, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);

    Point pointArray[5] = { {0, 2478}, {1, 2600}, {2, 3000}, {3, 3200}, {4, 3500} };
    bool ret = data->AddPoints(pointArray, 5);
    EXPECT_EQ(ret, true);

    Point point = { 1, 200 };
    ret = data->ModifyPoint(6, point);
    EXPECT_EQ(ret, false);

    ret = data->ModifyPoint(1, point);
    EXPECT_EQ(ret, true);

    Point point1;
    ret = data->GetPoint(1, point1);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(point1.x, 1);
    EXPECT_EQ(point1.y, 200);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_HIDEPOINTS_0100
* @tc.name       test chart hide points api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartHidePoints, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);
    uint16_t index = 3;
    uint16_t count = 5;
    data->HidePoint(index, count);
    EXPECT_EQ(data->GetHideIndex(), index);
    EXPECT_EQ(data->GetHideCount(), count);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_CLEARDATA_0100
* @tc.name       test chart clear data api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartClearData, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);

    Point pointArray[5] = { {0, 2478}, {1, 2600}, {2, 3000}, {3, 3200}, {4, 3500} };
    bool ret = data->AddPoints(pointArray, 5);
    EXPECT_EQ(ret, true);

    data->ClearData();

    Point point;
    ret = data->GetPoint(1, point);
    EXPECT_EQ(ret, false);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_GETDATACOUNT_0100
* @tc.name       test chart get data count api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartGetDataCount, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);

    Point pointArray[5] = { {0, 2478}, {1, 2600}, {2, 3000}, {3, 3200}, {4, 3500} };
    bool ret = data->AddPoints(pointArray, 5);
    EXPECT_EQ(ret, true);

    uint16_t count = data->GetDataCount();
    EXPECT_EQ(count, 5);

    data->ClearData();
    count = data->GetDataCount();
    EXPECT_EQ(count, 0);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_ENABLESMOOTH_0100
* @tc.name       test chart enable smooth api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartEnableSmooth, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);

    data->EnableSmooth(true);

    bool ret = data->IsSmooth();
    EXPECT_EQ(ret, true);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_GETPEAKINDEX_0100
* @tc.name       test chart get peak index api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartGetPeakIndex, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);

    Point pointArray[5] = { {0, 2478}, {1, 2600}, {2, 3000}, {3, 200}, {4, 1654} };
    bool ret = data->AddPoints(pointArray, 5);
    EXPECT_EQ(ret, true);

    uint16_t index = data->GetPeakIndex();
    EXPECT_EQ(index, 2);

    int16_t value = data->GetPeakData();
    EXPECT_EQ(value, 3000);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_GETVALLEYINDEX_0100
* @tc.name       test chart get valley index api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartGetValleyIndex, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);

    Point pointArray[5] = { {0, 2478}, {1, 2600}, {2, 3000}, {3, 200}, {4, 1654} };
    bool ret = data->AddPoints(pointArray, 5);
    EXPECT_EQ(ret, true);

    uint16_t index = data->GetValleyIndex();
    EXPECT_EQ(index, 3);

    int16_t value = data->GetValleyData();
    EXPECT_EQ(value, 200);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_GETLATESTINDEX_0100
* @tc.name       test chart get latest index api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartGetLatestIndex, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);

    Point pointArray[5] = { {0, 2478}, {1, 2600}, {2, 3000}, {3, 200}, {4, 1654} };
    bool ret = data->AddPoints(pointArray, 5);
    EXPECT_EQ(ret, true);

    uint16_t index = data->GetLatestIndex();
    EXPECT_EQ(index, 4);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_SETLASTPOINTINDEX_0100
* @tc.name       test chart set last point index api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartSetLastPointIndex, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);
    Point pointArray[5] = { {0, 2478}, {1, 2600}, {2, 3000}, {3, 200}, {4, 1654} };
    bool ret = data->AddPoints(pointArray, 5);
    EXPECT_EQ(ret, true);

    uint16_t index = data->GetLastPointIndex();
    EXPECT_EQ(index, 0);

    data->SetLastPointIndex(4);
    EXPECT_EQ(data->GetLastPointIndex(), 4);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_SETLINECOLOR_0100
* @tc.name       test chart set line color api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartSetLineColor, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);
    ColorType color = Color::Red();
    data->SetLineColor(color);
    EXPECT_EQ(data->GetLineColor().full, color.full);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_SETFILLCOLOR_0100
* @tc.name       test chart set fill color api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartSetFillColor, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);
    ColorType color = Color::Red();
    data->SetFillColor(color);
    EXPECT_EQ(data->GetFillColor().full, color.full);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_SETHEADPOINTSTYLE_0100
* @tc.name       test chart set head point style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartSetHeadPointStyle, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);

    UIChartDataSerial::PointStyle pointStyle;
    pointStyle.fillColor = Color::Red();
    pointStyle.radius = 5;
    pointStyle.strokeColor = Color::White();
    pointStyle.strokeWidth = 10;

    data->SetHeadPointStyle(pointStyle);

    UIChartDataSerial::PointStyle pointStyle1 = data->GetHeadPointStyle();

    EXPECT_EQ(pointStyle1.fillColor.full, pointStyle.fillColor.full);
    EXPECT_EQ(pointStyle1.strokeColor.full, pointStyle.strokeColor.full);
    EXPECT_EQ(pointStyle1.strokeWidth, pointStyle.strokeWidth);
    EXPECT_EQ(pointStyle1.radius, pointStyle.radius);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_SETTOPPOINTSTYLE_0100
* @tc.name       test chart set top point style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartSetTopPointStyle, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);
    UIChartDataSerial::PointStyle pointStyle;
    pointStyle.fillColor = Color::Red();
    pointStyle.radius = 5;
    pointStyle.strokeColor = Color::White();
    pointStyle.strokeWidth = 10;
    data->SetTopPointStyle(pointStyle);
    UIChartDataSerial::PointStyle pointStyle1 = data->GetTopPointStyle();
    EXPECT_EQ(pointStyle1.fillColor.full, pointStyle.fillColor.full);
    EXPECT_EQ(pointStyle1.strokeColor.full, pointStyle.strokeColor.full);
    EXPECT_EQ(pointStyle1.strokeWidth, pointStyle.strokeWidth);
    EXPECT_EQ(pointStyle1.radius, pointStyle.radius);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_SETBOTTOMPOINTSTYLE_0100
* @tc.name       test chart set bottmo point style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartSetBottomPointStyle, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);
    UIChartDataSerial::PointStyle pointStyle;
    pointStyle.fillColor = Color::Red();
    pointStyle.radius = 5;
    pointStyle.strokeColor = Color::White();
    pointStyle.strokeWidth = 10;
    data->SetBottomPointStyle(pointStyle);
    UIChartDataSerial::PointStyle pointStyle1 = data->GetBottomPointStyle();
    EXPECT_EQ(pointStyle1.fillColor.full, pointStyle.fillColor.full);
    EXPECT_EQ(pointStyle1.strokeColor.full, pointStyle.strokeColor.full);
    EXPECT_EQ(pointStyle1.strokeWidth, pointStyle.strokeWidth);
    EXPECT_EQ(pointStyle1.radius, pointStyle.radius);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_ADDDATASERIAL_0100
* @tc.name       test chart add data serial style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartAddDataSerial, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);
    UIChartPillar* chart = new UIChartPillar();
    bool ret = chart->AddDataSerial(nullptr);
    EXPECT_EQ(ret, false);
    ret= chart->AddDataSerial(data);
    EXPECT_EQ(ret, true);
    ret = chart->AddDataSerial(data);
    EXPECT_EQ(ret, false);
    delete(chart);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_DELETEDATASERIAL_0100
* @tc.name       test chart delete data serial style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartDeleteDataSerial, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);
    UIChartPillar* chart = new UIChartPillar();
    bool ret = chart->DeleteDataSerial(nullptr);
    EXPECT_EQ(ret, false);
    ret = chart->DeleteDataSerial(data);
    EXPECT_EQ(ret, false);
    ret = chart->AddDataSerial(data);
    EXPECT_EQ(ret, true);
    ret = chart->DeleteDataSerial(data);
    EXPECT_EQ(ret, true);
    delete(chart);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_CLEARDATASERIAL_0100
* @tc.name       test chart clear data serial style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartClearDataSerial, TestSize.Level0) {
    UIChartDataSerial* data = new UIChartDataSerial();
    data->SetMaxDataCount(5);
    UIChartPillar* chart = new UIChartPillar();
    bool ret = chart->AddDataSerial(data);
    EXPECT_EQ(ret, true);
    chart->ClearDataSerial();
    ret = chart->DeleteDataSerial(data);
    EXPECT_EQ(ret, false);
    delete(chart);
    delete(data);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_SETHEIGHT_0100
* @tc.name       test chart height style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartSetHeight, TestSize.Level0) {
    UIChartPillar* chart = new UIChartPillar();
    chart->SetHeight(50);
    EXPECT_EQ(chart->GetHeight(), 50);
    delete(chart);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CHART_CHART_SETWIDTH_0100
* @tc.name       test chart width style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ChartTest, testChartSetWidth, TestSize.Level0) {
    UIChartPillar* chart = new UIChartPillar();
    chart->SetWidth(50);
    EXPECT_EQ(chart->GetWidth(), 50);
    delete(chart);
}