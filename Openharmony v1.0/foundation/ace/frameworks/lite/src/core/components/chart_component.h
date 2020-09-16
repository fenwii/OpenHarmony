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

#ifndef OHOS_ACELITE_CHART_COMPONENT_H
#define OHOS_ACELITE_CHART_COMPONENT_H

#include "component.h"
#include "non_copyable.h"
#include "ui_chart.h"
#include "ui_label.h"

namespace OHOS {
namespace ACELite {
struct DataSerials : public MemoryHeap {
    UIChartDataSerial *dataSerial;
    DataSerials *next;
    ACE_DISALLOW_COPY_AND_MOVE(DataSerials);
    DataSerials() : dataSerial(nullptr), next(nullptr) {}
};

enum class PointType { HEAD, TOP, BOTTOM };

struct PointOptions : public MemoryHeap {
    uint8_t size;
    uint8_t strokeWidth;
    uint32_t strokeColor;
    uint32_t fillColor;
    ACE_DISALLOW_COPY_AND_MOVE(PointOptions);
    PointOptions() : size(POINT_SIZE), strokeWidth(1), strokeColor(0xFF0000), fillColor(0xFF0000) {}
};

struct SeriesOptions : public MemoryHeap {
    uint8_t width;
    uint8_t margin;
    PointOptions *head;
    PointOptions *top;
    PointOptions *bottom;
    bool smooth;
    bool isHeadSet;
    bool isTopSet;
    bool isBottomSet;
    bool isLoopSet;
    ACE_DISALLOW_COPY_AND_MOVE(SeriesOptions);
    SeriesOptions() : width(1), margin(1), head(nullptr), top(nullptr), bottom(nullptr), smooth(false),
        isHeadSet(false), isTopSet(false), isBottomSet(false), isLoopSet(false){};
};

class ChartComponent final : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ChartComponent);
    ChartComponent() = delete;
    ChartComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager);
    ~ChartComponent() {}
    virtual bool CreateNativeViews() override;
    virtual bool SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue) override;
    virtual void PostUpdate(uint16_t attrKeyId, bool updateResult) override;
    virtual void PostRender() override;
    virtual void ReleaseNativeViews() override;

protected:
    virtual UIView *GetComponentRootView() const override;

private:
    bool Init();
    void UpdateData(jerry_value_t dataSets, jerry_value_t keyName, uint8_t serialsCount);
    bool UpdataDataInOrder(jerry_value_t dataSet, UIChartDataSerial &dataserial, uint16_t dataLen);
    void AppendData(jerry_value_t dataSet, DataSerials *dataSerialNode);
    void UpdateColorToSerial(jerry_value_t dataSet, UIChartDataSerial &dataserial, bool isStrokeColor);
    void UpdateStrokeColorToSerial(jerry_value_t dataSet, UIChartDataSerial &dataserial);
    void UpdateFillColorToSerial(jerry_value_t dataSet, UIChartDataSerial &dataserial);
    void UpdateStrokeSmoothToSerial(UIChartDataSerial &dataserial);
    bool UpdatePointToSerial(UIChartDataSerial *dataserial, PointType type);
    bool UpdatePoints(UIChartDataSerial *dataserial);
    void UpdateGradientToSerial(jerry_value_t dataSet, UIChartDataSerial *dataserial);
    bool UpdateValuesToSerial(jerry_value_t dataSet, UIChartDataSerial *dataserial, uint16_t dataLen);
    bool AppendValuesToSerial(jerry_value_t dataSet, UIChartDataSerial *dataserial, uint16_t dataLen);
    void AppendValues(UIChartDataSerial &dataserial, Point *pointArray, uint16_t dataLen);
    bool ParseDataValue(jerry_value_t dataValue, uint16_t interval, Point *pointArray, uint16_t arrayLen);
    bool SetOptions(jerry_value_t options);
    bool SetOptionsAxis(jerry_value_t options, bool isXAxis);
    bool SetOptionsAxisDataRange(jerry_value_t options, bool isXAxis);
    bool SetOptionsAxisDataRange(uint16_t minValue, uint16_t maxValue, uint8_t defaultMinValue,
        uint8_t defaultMaxValue, bool isXaxis);
    void SetOptionsAxisTick(jerry_value_t options, bool isXAxis);
    bool SetOptionsAxisDisplay(jerry_value_t options, bool isXAxis);
    void SetOptionsAxisColor(jerry_value_t options, bool isXAxis);
    /**
     * @brief record series options in seriesOptions_
     *
     * @param [in] options.
     */
    void RecordOptionsSeries(jerry_value_t options);
    void RecordOptionsSeriesLineStyle(jerry_value_t jSeriesVal);
    void RecordOptionsSeriesPoint(jerry_value_t jSeriesVal, PointType type);
    void RecordOptionsSeriesLoop(jerry_value_t jSeriesVal);
    void Reset();
    /**
     * @brief record DataSerials into linked list
     *
     * @param [in] serial.
     */
    void AddDataSerial(DataSerials *serial);
    void ClearDataSerialsNode(DataSerials *serial);
    void ClearAllDataSerials();
    uint16_t GetSizeVal(jerry_value_t obj, const char * const styleName, uint16_t defaultValue);
    uint32_t GetColor(jerry_value_t obj, const char * const styleName, uint32_t defaultValue);
    bool GetDisplayStatus(jerry_value_t obj);
    static jerry_value_t AppendDatas(const jerry_value_t func, const jerry_value_t context,
        const jerry_value_t *args, const jerry_length_t argsNum);
    static ChartComponent *GetChartComponent(jerry_value_t nativeElement);
    static const DataSerials *GetDataSerial(ChartComponent *chartComponent, uint8_t index);

    UIXAxis *xAxis_;
    UIYAxis *yAxis_;
    size_t yMinValue_;
    size_t yMaxValue_;
    uint16_t xMinValue_;
    uint16_t xMaxValue_;
    jerry_value_t options_;
    UIChart *chartView_;
    DataSerials *serials_;
    uint8_t totalSerialsNum_;
    jerry_value_t dataSetsRecord_;
    SeriesOptions *seriesOptions_;
    char *chartType_;
    UIChartDataSerial::PointStyle *headPointStyle_;
    UIChartDataSerial::PointStyle *topPointStyle_;
    UIChartDataSerial::PointStyle *bottomPointStyle_;
    static const char * const DATA;
    static const char * const APPEND_SERIAL_INDEX;
    static const char * const LINE;
    static const char * const BAR;
    static const char * const FUNC_JS_API;
    static const char * const STROKE_COLOR;
    static const char * const STROKE_WIDTH;
    static const char * const FILL_COLOR;
    static const char * const GRADIENT;
    static const char * const LINE_STYLE;
    static const char * const SMOOTH;
    static const char * const HEAD_POINT;
    static const char * const SHAPE;
    static const char * const SIZE;
    static const char * const TOP_POINT;
    static const char * const BOTTOM_POINT;
    static const char * const X_AXIS;
    static const char * const Y_AXIS;
    static const char * const MIN;
    static const char * const MAX;
    static const char * const TYPE;
    static const char * const SERIES;
    static const char * const COLOR;
    static const char * const WIDTH;
    static const char * const LOOP;
    static const char * const MARGIN;
    static const char * const DISPLAY;
};
} // namespace ACELite
} // namespace OHOS

#endif // !OHOS_ACELITE_CHART_COMPONENT_H
