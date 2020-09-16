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

#include "components/chart_component.h"
#include "ace_log.h"
#include "ace_mem_base.h"
#include "flex_layout.h"
#include "keys.h"
#include "ui_chart.h"
#include "ui_circle_progress.h"
#include "font/ui_font_header.h"

namespace OHOS {
namespace ACELite {
const char * const ChartComponent::DATA = "data";
const char * const ChartComponent::APPEND_SERIAL_INDEX = "serial";
const char * const ChartComponent::LINE = "line";
const char * const ChartComponent::BAR = "bar";
const char * const ChartComponent::FUNC_JS_API = "append";
const char * const ChartComponent::STROKE_COLOR = "strokeColor";
const char * const ChartComponent::STROKE_WIDTH = "strokeWidth";
const char * const ChartComponent::FILL_COLOR = "fillColor";
const char * const ChartComponent::GRADIENT = "gradient";
const char * const ChartComponent::LINE_STYLE = "lineStyle";
const char * const ChartComponent::SMOOTH = "smooth";
const char * const ChartComponent::HEAD_POINT = "headPoint";
const char * const ChartComponent::SHAPE = "shape";
const char * const ChartComponent::SIZE = "size";
const char * const ChartComponent::TOP_POINT = "topPoint";
const char * const ChartComponent::BOTTOM_POINT = "bottomPoint";
const char * const ChartComponent::X_AXIS = "xAxis";
const char * const ChartComponent::Y_AXIS = "yAxis";
const char * const ChartComponent::MIN = "min";
const char * const ChartComponent::MAX = "max";
const char * const ChartComponent::TYPE = "type";
const char * const ChartComponent::SERIES = "series";
const char * const ChartComponent::COLOR = "color";
const char * const ChartComponent::WIDTH = "width";
const char * const ChartComponent::LOOP = "loop";
const char * const ChartComponent::MARGIN = "margin";
const char * const ChartComponent::DISPLAY = "display";

ChartComponent::ChartComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager)
    : Component(options, children, styleManager),
      xAxis_(nullptr),
      yAxis_(nullptr),
      yMinValue_(0),
      yMaxValue_(0),
      xMinValue_(0),
      xMaxValue_(0),
      options_(options),
      chartView_(nullptr),
      serials_(nullptr),
      totalSerialsNum_(0),
      dataSetsRecord_(UNDEFINED),
      seriesOptions_(nullptr),
      chartType_(const_cast<char *>(LINE)),
      headPointStyle_(nullptr),
      topPointStyle_(nullptr),
      bottomPointStyle_(nullptr){}

bool ChartComponent::CreateNativeViews()
{
    jerry_value_t attrsPropValue = jerryx_get_property_str(options_, ATTR_ATTRS);
    jerry_value_t typeStrHandler = jerry_create_string(reinterpret_cast<const jerry_char_t *>(TYPE));
    jerry_value_t hasTypeProp = jerry_has_property(attrsPropValue, typeStrHandler);
    if (jerry_get_boolean_value(hasTypeProp)) {
        jerry_value_t typeValHandler = jerry_get_property(attrsPropValue, typeStrHandler);
        char *type = MallocStringOf(typeValHandler);
        jerry_release_value(typeValHandler);
        if ((type != nullptr) && !strcmp(type, BAR)) {
            chartView_ = new UIChartPillar();
            chartType_ = const_cast<char *>(BAR);
        }
        ACE_FREE(type);
    }
    ReleaseJerryValue(hasTypeProp, typeStrHandler, attrsPropValue, VA_ARG_END_FLAG);
    if (!strcmp(chartType_, LINE)) {
        chartView_ = new UIChartPolyline();
    }
    if (chartView_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create chart view error");
        return false;
    }
    if (!Init()) {
        return false;
    }
    return true;
}

bool ChartComponent::SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue)
{
    if ((chartView_ == nullptr) || !KeyParser::IsKeyValid(attrKeyId) || IS_UNDEFINED(attrValue)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "chart view has not been created");
        return false;
    }
    switch (attrKeyId) {
        case K_DATASETS: {
            dataSetsRecord_ = attrValue;
            break;
        }
        case K_OPATIONS: {
            SetOptions(attrValue);
            break;
        }
        default: {
            break;
        }
    }
    return false;
}

void ChartComponent::PostUpdate(uint16_t attrKeyId, bool updateResult)
{
    chartView_->ClearDataSerial();
    chartView_->Invalidate();
    ClearAllDataSerials();
    Reset();
    PostRender();
}

void ChartComponent::PostRender()
{
    uint8_t serialsCount = jerry_get_array_length(dataSetsRecord_);
    jerry_value_t data = jerry_create_string(reinterpret_cast<const jerry_char_t *>(DATA));
    UpdateData(dataSetsRecord_, data, serialsCount);
    jerry_release_value(data);
    chartView_->Invalidate();
}

void ChartComponent::ReleaseNativeViews()
{
    if (chartView_) {
        delete (chartView_);
        chartView_ = nullptr;
    }
    ClearAllDataSerials();
    if (seriesOptions_ != nullptr) {
        if (seriesOptions_->head) {
            delete(seriesOptions_->head);
            seriesOptions_->head = nullptr;
        }
        if (seriesOptions_->top) {
            delete(seriesOptions_->top);
            seriesOptions_->top = nullptr;
        }
        if (seriesOptions_->bottom) {
            delete(seriesOptions_->bottom);
            seriesOptions_->bottom = nullptr;
        }
        delete(seriesOptions_);
        seriesOptions_ = nullptr;
    }
    if (headPointStyle_ != nullptr) {
        delete(headPointStyle_);
        headPointStyle_ = nullptr;
    }
    if (topPointStyle_ != nullptr) {
        delete(topPointStyle_);
        topPointStyle_ = nullptr;
    }
    if (bottomPointStyle_ != nullptr) {
        delete(bottomPointStyle_);
        bottomPointStyle_ = nullptr;
    }
}

inline UIView *ChartComponent::GetComponentRootView() const
{
    return chartView_;
}

void ChartComponent::UpdateStrokeColorToSerial(jerry_value_t dataSet, UIChartDataSerial &dataserial)
{
    if (!strcmp(chartType_, BAR)) {
        HILOG_WARN(HILOG_MODULE_ACE, "bar not support stroke color set");
        return;
    }
    UpdateColorToSerial(dataSet, dataserial, true);
}

void ChartComponent::UpdateFillColorToSerial(jerry_value_t dataSet, UIChartDataSerial& dataserial)
{
    UpdateColorToSerial(dataSet, dataserial, false);
}

void ChartComponent::UpdateStrokeSmoothToSerial(UIChartDataSerial& dataserial)
{
    dataserial.EnableSmooth(seriesOptions_->smooth);
}

bool ChartComponent::UpdatePointToSerial(UIChartDataSerial* dataserial, PointType type)
{
    switch (type) {
        case PointType::HEAD: {
            if (headPointStyle_ == nullptr) {
                headPointStyle_ = new UIChartDataSerial::PointStyle();
                if (headPointStyle_ == nullptr) {
                    HILOG_ERROR(HILOG_MODULE_ACE, "malloc headPointStyle heap error");
                    return false;
                }
            }
            headPointStyle_->fillColor = GetRGBColor(seriesOptions_->head->fillColor);
            headPointStyle_->strokeColor = GetRGBColor(seriesOptions_->head->strokeColor);
            headPointStyle_->strokeWidth = 1;
            headPointStyle_->radius = seriesOptions_->head->size;
            headPointStyle_->strokeWidth = seriesOptions_->head->strokeWidth;
            dataserial->SetHeadPointStyle(*headPointStyle_);
            break;
        }
        case PointType::TOP: {
            if (topPointStyle_ == nullptr) {
                topPointStyle_ = new UIChartDataSerial::PointStyle();
                if (topPointStyle_ == nullptr) {
                    HILOG_ERROR(HILOG_MODULE_ACE, "malloc topPointStyle heap error");
                    return false;
                }
            }
            topPointStyle_->fillColor = GetRGBColor(seriesOptions_->top->fillColor);
            topPointStyle_->strokeColor = GetRGBColor(seriesOptions_->top->strokeColor);
            topPointStyle_->strokeWidth = 1;
            topPointStyle_->radius = seriesOptions_->top->size;
            topPointStyle_->strokeWidth = seriesOptions_->top->strokeWidth;
            dataserial->SetTopPointStyle(*topPointStyle_);
            break;
        }
        case PointType::BOTTOM: {
            if (bottomPointStyle_ == nullptr) {
                bottomPointStyle_ = new UIChartDataSerial::PointStyle();
                if (bottomPointStyle_ == nullptr) {
                    HILOG_ERROR(HILOG_MODULE_ACE, "malloc bottomPointStyle heap error");
                    return false;
                }
            }
            bottomPointStyle_->fillColor = GetRGBColor(seriesOptions_->bottom->fillColor);
            bottomPointStyle_->strokeColor = GetRGBColor(seriesOptions_->bottom->strokeColor);
            bottomPointStyle_->strokeWidth = 1;
            bottomPointStyle_->radius = seriesOptions_->bottom->size;
            bottomPointStyle_->strokeWidth = seriesOptions_->bottom->strokeWidth;
            dataserial->SetBottomPointStyle(*bottomPointStyle_);
            break;
        }
        default: {
            break;
        }
    }
    return true;
}

bool ChartComponent::UpdatePoints(UIChartDataSerial* dataserial)
{
    if (seriesOptions_->isTopSet) {
        if (UpdatePointToSerial(dataserial, PointType::TOP)) {
            dataserial->EnableTopPoint(true);
        } else {
            return false;
        }
    } else {
        dataserial->EnableTopPoint(false);
    }
    if (seriesOptions_->isHeadSet) {
        if (UpdatePointToSerial(dataserial, PointType::HEAD)) {
            dataserial->EnableHeadPoint(true);
        } else {
            return false;
        }
    } else {
        dataserial->EnableHeadPoint(false);
    }
    if (seriesOptions_->isBottomSet) {
        if (UpdatePointToSerial(dataserial, PointType::BOTTOM)) {
            dataserial->EnableBottomPoint(true);
        } else {
            return false;
        }
    } else {
        dataserial->EnableBottomPoint(false);
    }
    return true;
}

void ChartComponent::UpdateGradientToSerial(jerry_value_t dataSet, UIChartDataSerial* dataserial)
{
    jerry_value_t jNeedGradient = jerry_create_string(reinterpret_cast<jerry_char_t *>(const_cast<char *>(GRADIENT)));
    jerry_value_t hasGradientProperty = jerry_has_property(dataSet, jNeedGradient);
    if (hasGradientProperty) {
        bool needGradient = jerry_get_boolean_value(jerry_get_property(dataSet, jNeedGradient));
        if (!strcmp(chartType_, LINE) && needGradient) {
            dataserial->EnableGradient(true);
        }
    }
    ReleaseJerryValue(hasGradientProperty, jNeedGradient, VA_ARG_END_FLAG);
}

bool ChartComponent::UpdateValuesToSerial(jerry_value_t dataSet, UIChartDataSerial* dataserial, uint16_t dataLen)
{
    bool isSetOk = true;
    jerry_value_t jData = jerry_create_string(reinterpret_cast<const jerry_char_t *>(DATA));
    jerry_value_t hasDataProp = jerry_has_property(dataSet, jData);
    if (hasDataProp) {
        jerry_value_t jDataValue = jerry_get_property(dataSet, jData);
        uint16_t len = 0;
        if (!strcmp(chartType_, BAR)) {
            len = jerry_get_array_length(jDataValue);
        } else {
            if ((xMaxValue_ >= (UINT16_MAX - 1)) || (dataLen < xMinValue_)) {
                HILOG_WARN(HILOG_MODULE_ACE, "customMaxCount or customMinValue is set out of boundary");
            }
            uint16_t customMaxCount = xMaxValue_ + 1; // the max data count speciafied by user
            uint16_t actualMaxCount = dataLen - xMinValue_; // the actual max data count setted in data array
            len = (customMaxCount < actualMaxCount) ? customMaxCount : actualMaxCount;
        }
        if (isSetOk) {
            Point* pointArray = (len > 0) ? (static_cast<Point *>(ace_malloc(sizeof(Point) * len))) : nullptr;
            if (pointArray == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "malloc point array memory heap failed");
                isSetOk = false;
            } else {
                for (int i = 0; i < len; i++) {
                    pointArray[i] = { 0, 0 };
                }
                uint16_t interval = 0;
                ParseDataValue(jDataValue, interval, pointArray, len);
                dataserial->AddPoints(pointArray, len);
                chartView_->AddDataSerial(dataserial);
                ace_free(pointArray);
                pointArray = nullptr;
            }
        }
        jerry_release_value(jDataValue);
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "data not set");
        isSetOk = false;
    }
    ReleaseJerryValue(hasDataProp, jData, VA_ARG_END_FLAG);
    // need to set after datas setted
    isSetOk = isSetOk ? UpdatePoints(dataserial) : false;
    return isSetOk;
}

bool ChartComponent::AppendValuesToSerial(jerry_value_t dataSet, UIChartDataSerial* dataserial, uint16_t dataLen)
{
    if (dataserial == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "dataserial is null");
        return false;
    }
    bool isSetOk = true;
    jerry_value_t jData = jerry_create_string(reinterpret_cast<const jerry_char_t *>("data"));
    jerry_value_t hasDataProp = jerry_has_property(dataSet, jData);
    if (hasDataProp) {
        jerry_value_t jDataValue = dataSet;
        uint16_t interval = dataserial->GetDataCount();
        Point* pointArray = (dataLen > 0) ? (static_cast<Point *>(ace_malloc(sizeof(Point) * dataLen))) : nullptr;
        if (pointArray == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "malloc point array memory heap failed!");
            isSetOk = false;
        } else {
            for (int i = 0; i < dataLen; i++) {
                pointArray[i] = { 0, 0 };
            }
            ParseDataValue(jDataValue, interval, pointArray, dataLen);
            AppendValues(*dataserial, pointArray, dataLen);
            chartView_->RefreshChart();
            ace_free(pointArray);
            pointArray = nullptr;
        }
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "data not set!");
        isSetOk = false;
    }
    ReleaseJerryValue(hasDataProp, jData, VA_ARG_END_FLAG);
    return isSetOk;
}

void ChartComponent::AppendValues(UIChartDataSerial& dataserial, Point* pointArray, uint16_t dataLen)
{
    if (!(seriesOptions_->isLoopSet)) {
        dataserial.AddPoints(pointArray, dataLen);
        return;
    }
    // the index of the latest updated point (include add or modify)
    uint16_t latestIndex = dataserial.GetLatestIndex();
    // the length that will become after adding new data
    uint16_t expectedDatasLen = latestIndex + dataLen + 1;
    if ((dataLen == UINT16_MAX) || (UINT16_MAX - latestIndex) < (dataLen + 1)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "dataLen out of boundary");
        return;
    }
    // the amount of data already in the current data series
    uint16_t existingDataLen = dataserial.GetDataCount();
    if (expectedDatasLen > (xMaxValue_ + 1)) {
        if (latestIndex < existingDataLen - 1) {
            // means need to modify the value between lastestIndex and existingDataLen
            for (uint16_t i = 0; i < xMaxValue_ - latestIndex; i++) {
                if (i >= dataLen) {
                    HILOG_ERROR(HILOG_MODULE_ACE, "append data error1");
                    return;
                }
                pointArray[i].x = i + latestIndex + 1;
                dataserial.ModifyPoint(i + latestIndex + 1, pointArray[i]);
                dataserial.HidePoint(i + latestIndex + 1, seriesOptions_->margin);
            }
        } else { // means need to add new data to the series
            dataserial.AddPoints(pointArray, xMaxValue_ - latestIndex);
        }
        // Get the data set beyond the screen, and replace the existing data in the sequence one by one
        // from the beginning
        for (uint16_t i = 0; i < (expectedDatasLen - (xMaxValue_ + 1)); i++) {
            if (((xMaxValue_ - latestIndex) + i) >= dataLen) {
                HILOG_ERROR(HILOG_MODULE_ACE, "append data error2");
                return;
            }
            pointArray[(xMaxValue_ - latestIndex) + i].x = i;
            dataserial.ModifyPoint(i, pointArray[(xMaxValue_ - latestIndex) + i]);
            dataserial.HidePoint(i + latestIndex + 1, seriesOptions_->margin);
        }
    } else { // after adding data, the length will not exceed the maximum value of the x axis
        if (latestIndex < existingDataLen - 1) {
            // means need to modify the value between lastestIndex and dataLen
            for (uint16_t i = 0; i < dataLen; i++) {
                pointArray[i].x = latestIndex + 1 + i;
                dataserial.ModifyPoint(latestIndex + 1 + i, pointArray[i]);
                dataserial.HidePoint(i + latestIndex + 1, seriesOptions_->margin);
            }
        } else { // means need to add new data to the series
            dataserial.AddPoints(pointArray, dataLen);
        }
    }
}

bool ChartComponent::ParseDataValue(jerry_value_t dataValue, uint16_t interval, Point* pointArray, uint16_t arrayLen)
{
    for (size_t index = 0; index < arrayLen; index++) {
        // interval == 0 means update series, otherwise means append data to series
        jerry_value_t data = (interval == 0) ? jerry_get_property_by_index(dataValue, (index + xMinValue_)) :
            jerry_get_property_by_index(dataValue, index);
        if (!jerry_value_is_number(data)) {
            jerry_release_value(data);
            HILOG_ERROR(HILOG_MODULE_ACE, "chart data is not a number");
            return false;
        }
        size_t dataValue = static_cast<size_t>(jerry_get_number_value(data));
        pointArray[index].x = (index + interval);
        if (dataValue < yMinValue_) {
            HILOG_WARN(HILOG_MODULE_ACE, "the value %d is less than min value, and will use minValue instead",
                dataValue);
            pointArray[index].y = yMinValue_;
        } else if (dataValue > yMaxValue_) {
            HILOG_WARN(HILOG_MODULE_ACE, "the value %d is larger than max value, and will use maxValue instead",
                dataValue);
            pointArray[index].y = yMaxValue_;
        } else {
            pointArray[index].y = dataValue;
        }
        jerry_release_value(data);
    }
    return true;
}

jerry_value_t ChartComponent::AppendDatas(const jerry_value_t func,
    const jerry_value_t context,
    const jerry_value_t *args,
    const jerry_length_t argsNum)
{
    uint8_t functionParamsNum = 1; // js append function just recieve 1 number params
    if (argsNum != functionParamsNum) {
        HILOG_ERROR(HILOG_MODULE_ACE, "append function params error");
    } else {
        if (jerry_value_is_undefined(args[0])) {
            HILOG_ERROR(HILOG_MODULE_ACE, "append function params error");
            return UNDEFINED;
        }
        jerry_value_t jAppendDataObj = args[0];
        uint8_t serialIndex = JerryGetIntegerProperty(jAppendDataObj, APPEND_SERIAL_INDEX);
        jerry_value_t jDatas = jerryx_get_property_str(jAppendDataObj, DATA);
        ChartComponent* chartComponent = ChartComponent::GetChartComponent(context);
        if (chartComponent != nullptr) {
            DataSerials* tarSerial = const_cast<DataSerials *>(GetDataSerial(chartComponent, serialIndex));
            if (tarSerial != nullptr) {
                chartComponent->AppendData(jDatas, tarSerial);
            }
        }
        jerry_release_value(jDatas);
    }
    return UNDEFINED;
}

bool ChartComponent::SetOptions(jerry_value_t options)
{
    if (!SetOptionsAxis(options, true)) {
        return false;
    }
    if (!SetOptionsAxis(options, false)) {
        return false;
    }
    RecordOptionsSeries(options);
    return true;
}

void ChartComponent::UpdateData(jerry_value_t dataSets, jerry_value_t keyName, uint8_t serialsCount)
{
    if (serials_ != nullptr) {
        chartView_->ClearDataSerial();
        ClearAllDataSerials(); // clear all data serials
    }
    bool isSetOk = false;
    for (uint8_t index = 0; index < serialsCount; index++) { // every data set
        jerry_value_t dataSet = jerry_get_property_by_index(dataSets, index);
        // check data is set correctlly, if the data is not set correctly, need not to set other attribute left
        jerry_value_t dataValue = jerry_get_property(dataSet, keyName);
        if ((!jerry_value_is_undefined(dataValue)) && jerry_value_is_array(dataValue)) {
            uint16_t dataLen = jerry_get_array_length(dataValue);
            // add to serial linked list, delete all before next update or component finish
            DataSerials* dataSerialNode = new DataSerials();
            if (dataSerialNode == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "new dataSerialNode memory heap fail");
                ReleaseJerryValue(dataValue, dataSet, VA_ARG_END_FLAG);
                break;
            }
            AddDataSerial(dataSerialNode);
            // create dataserial
            uint16_t dataCount = 0;
            if (!strcmp(chartType_, BAR)) {
                jerry_value_t jData = jerry_create_string(reinterpret_cast<const jerry_char_t *>(DATA));
                jerry_value_t jDataValue = jerry_get_property(dataSet, jData);
                dataCount = jerry_get_array_length(jDataValue);
                ReleaseJerryValue(jDataValue, jData, VA_ARG_END_FLAG);
            } else {
                dataCount = xMaxValue_ + 1;
            }
            UIChartDataSerial* dataserial = new UIChartDataSerial();
            if (dataserial == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "new UIChartDataSerial memory heap fail");
                ReleaseJerryValue(dataValue, dataSet, VA_ARG_END_FLAG);
                break;
            }
            dataserial->SetMaxDataCount(dataCount);
            dataSerialNode->dataSerial = dataserial;
            isSetOk = UpdataDataInOrder(dataSet, *dataserial, dataLen);
        } else {
            HILOG_ERROR(HILOG_MODULE_ACE, "chart data is not defined or is not array");
        }
        ReleaseJerryValue(dataValue, dataSet, VA_ARG_END_FLAG);
        if (!isSetOk) {
            break;
        }
    }
}

bool ChartComponent::UpdataDataInOrder(jerry_value_t dataSet, UIChartDataSerial& dataserial, uint16_t dataLen)
{
    UpdateStrokeColorToSerial(dataSet, dataserial);
    UpdateFillColorToSerial(dataSet, dataserial);
    UpdateGradientToSerial(dataSet, &dataserial);
    UpdateStrokeSmoothToSerial(dataserial);
    bool isSetOk = UpdateValuesToSerial(dataSet, &dataserial, dataLen);
    return isSetOk;
}

void ChartComponent::AppendData(jerry_value_t dataSet, DataSerials* dataSerialNode)
{
    if (dataSerialNode == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "data serial is null");
        return;
    }
    if (!strcmp(chartType_, BAR)) {
        HILOG_WARN(HILOG_MODULE_ACE, "bar not support append data");
        return;
    }
    uint16_t dataLen = jerry_get_array_length(dataSet);
    AppendValuesToSerial(dataSet, dataSerialNode->dataSerial, dataLen);
}

void ChartComponent::UpdateColorToSerial(jerry_value_t dataSet, UIChartDataSerial& dataserial, bool isStrokeColor)
{
    bool isColorSet = false;
    const char* styleName = isStrokeColor ? STROKE_COLOR : FILL_COLOR;
    if (jerryx_has_property_str(dataSet, styleName)) {
        isColorSet = true;
    } else {
        // Compatible with old versions (chart1.0)
        styleName = COMMON_STYLE_BACKGROUND_COLOR;
        if (jerryx_has_property_str(dataSet, styleName)) {
            isColorSet = true;
        }
    }
    uint32_t defaultColorVal = 0xFF6384; // pink
    uint32_t colorVal = defaultColorVal;
    if (isColorSet) {
        colorVal = GetColor(dataSet, const_cast<char *>(styleName), defaultColorVal);
    }
    ColorType bgColor = GetRGBColor(colorVal);
    if (isStrokeColor) {
        dataserial.SetLineColor(bgColor);
    } else {
        dataserial.SetFillColor(bgColor);
    }
}

bool ChartComponent::SetOptionsAxis(jerry_value_t attrValue, bool isXAxis)
{
    bool isSetOk = false;
    jerry_value_t jAxisName;
    if (isXAxis) {
        jAxisName = jerry_create_string(reinterpret_cast<const jerry_char_t *>(X_AXIS));
    } else {
        jAxisName = jerry_create_string(reinterpret_cast<const jerry_char_t *>(Y_AXIS));
    }
    jerry_value_t hasXAxisProp = jerry_has_property(attrValue, jAxisName);
    if (!jerry_get_boolean_value(hasXAxisProp)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "xAxis and yAxis param must set");
    } else {
        jerry_value_t axisValue = jerry_get_property(attrValue, jAxisName);
        isSetOk = SetOptionsAxisDataRange(axisValue, isXAxis);
        if (isSetOk) {
            SetOptionsAxisTick(axisValue, isXAxis);
            isSetOk = SetOptionsAxisDisplay(axisValue, isXAxis);
        }
        if (isSetOk) {
            SetOptionsAxisColor(axisValue, isXAxis);
        }
        jerry_release_value(axisValue);
    }
    ReleaseJerryValue(jAxisName, hasXAxisProp, VA_ARG_END_FLAG);
    return isSetOk;
}

bool ChartComponent::SetOptionsAxisDataRange(jerry_value_t xAxisValue, bool isXAxis)
{
    bool isSetOk = true;
    uint8_t defaultMinValue = 0;
    uint8_t defaultMaxValue = 100;
    jerry_value_t jMinValue = jerryx_get_property_str(xAxisValue, MIN);
    jerry_value_t jMaxValue = jerryx_get_property_str(xAxisValue, MAX);
    uint16_t minValue = jerry_get_number_value(jMinValue);
    uint16_t maxValue = jerry_get_number_value(jMaxValue);
    if (maxValue == 0) {
        if (!jerryx_has_property_str(xAxisValue, "max")) {
            HILOG_WARN(HILOG_MODULE_ACE,
                "max value is not defined, and will use default value %d instead", defaultMaxValue);
            maxValue = defaultMaxValue;
        }
    }
    if (isXAxis) {
        if (!strcmp(chartType_, BAR)) {
            xAxis_->SetDataRange(0, 0);
        } else {
            isSetOk = SetOptionsAxisDataRange(minValue, maxValue, defaultMinValue, defaultMaxValue, true);
        }
    } else {
        isSetOk = SetOptionsAxisDataRange(minValue, maxValue, defaultMinValue, defaultMaxValue, false);
    }
    ReleaseJerryValue(jMinValue, jMaxValue, VA_ARG_END_FLAG);
    return isSetOk;
}

bool ChartComponent::SetOptionsAxisDataRange(uint16_t minValue, uint16_t maxValue, uint8_t defaultMinValue,
    uint8_t defaultMaxValue, bool isXaxis)
{
    bool isSetOk = true;
    uint8_t supportMinValue = 0;
    uint16_t supportedMaxValue = 65535;
    const char * const xOrY = isXaxis ?  "x" : "y";
    if ((minValue < supportMinValue) || (minValue > supportedMaxValue)) {
        HILOG_WARN(HILOG_MODULE_ACE,
            "%s min value: %d is not between %d ~ %d, and will use default value %d instead",
            xOrY, minValue, supportMinValue, supportedMaxValue, defaultMinValue);
        minValue = defaultMinValue;
    }
    if ((maxValue < supportMinValue) || (maxValue > supportedMaxValue)) {
        HILOG_WARN(HILOG_MODULE_ACE,
            "%s max value: %d is not between %d ~ %d, and will use default value %d instead",
            xOrY, maxValue, supportMinValue, supportedMaxValue, defaultMaxValue);
        maxValue = defaultMaxValue;
    }
    if (minValue <= maxValue) {
        if (isXaxis) {
            xAxis_->SetDataRange(0, maxValue - minValue);
            xMaxValue_ = maxValue - minValue;
            xMinValue_ = minValue;
        } else {
            yAxis_->SetDataRange(minValue, maxValue);
            yMinValue_ = minValue;
            yMaxValue_ = maxValue;
        }
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "%s min value is larger than max value", xOrY);
        isSetOk = false;
    }
    return isSetOk;
}

void ChartComponent::SetOptionsAxisTick(jerry_value_t xAxisValue, bool isXAxis)
{
    jerry_value_t jAxisTickValue = jerryx_get_property_str(xAxisValue, "axisTick");
    int16_t axisTickValue = jerry_get_number_value(jAxisTickValue);
    const int8_t minTickValue = 1;
    const int8_t maxTickValue = 20;
    if ((axisTickValue < minTickValue) || (axisTickValue > maxTickValue)) {
        int16_t defaultValue = 10; // default value, means total number of ticks
        axisTickValue = defaultValue;
    }
    jerry_release_value(jAxisTickValue);
    if (isXAxis) {
        xAxis_->SetMarkNum(axisTickValue);
    } else {
        yAxis_->SetMarkNum(axisTickValue);
    }
}

bool ChartComponent::SetOptionsAxisDisplay(jerry_value_t xAxisValue, bool isXAxis)
{
    bool displayValue = false; // default value, means not show axis
    jerry_value_t jDisplayValue = jerryx_get_property_str(xAxisValue, DISPLAY);
    displayValue = jerry_get_boolean_value(jDisplayValue);
    if (isXAxis) {
        xAxis_->SetVisible(displayValue);
    } else {
        yAxis_->SetVisible(displayValue);
    }
    return true;
}

void ChartComponent::SetOptionsAxisColor(jerry_value_t xAxisValue, bool isXAxis)
{
    const char * const styleName = COLOR;
    uint32_t color = 0xc0c0c0; // default color
    if (jerryx_has_property_str(xAxisValue, styleName)) {
        uint16_t len = 0;
        char* styleValue = JerryMallocStringProperty(xAxisValue, styleName, len);
        uint8_t alpha = 0;
        (void)ParseColor(styleValue, color, alpha);
        ACE_FREE(styleValue);
    }
    ColorType axisColor = GetRGBColor(color);
    if (isXAxis) {
        xAxis_->SetLineColor(axisColor);
    } else {
        yAxis_->SetLineColor(axisColor);
    }
}

void ChartComponent::RecordOptionsSeries(jerry_value_t options)
{
    if (!jerryx_has_property_str(options, SERIES)) {
        return;
    } else {
        jerry_value_t jSeriesVal = jerryx_get_property_str(options, SERIES);
        RecordOptionsSeriesLineStyle(jSeriesVal);
        RecordOptionsSeriesPoint(jSeriesVal, PointType::HEAD);
        RecordOptionsSeriesPoint(jSeriesVal, PointType::TOP);
        RecordOptionsSeriesPoint(jSeriesVal, PointType::BOTTOM);
        RecordOptionsSeriesLoop(jSeriesVal);
        jerry_release_value(jSeriesVal);
    }
}

void ChartComponent::RecordOptionsSeriesLineStyle(jerry_value_t jSeriesVal)
{
    char* styleName = const_cast<char *>(LINE_STYLE);
    if (!jerryx_has_property_str(jSeriesVal, styleName)) {
        return;
    } else {
        jerry_value_t jLineStyleVal = jerryx_get_property_str(jSeriesVal, styleName);
        styleName = const_cast<char *>(WIDTH);
        uint16_t widthVal = GetSizeVal(jLineStyleVal, styleName, 1);
        chartView_->SetStyle(STYLE_LINE_WIDTH, widthVal); // chart width set can affect all the series
        seriesOptions_->width = widthVal;
        styleName = const_cast<char *>(SMOOTH);
        if (jerryx_has_property_str(jLineStyleVal, styleName)) {
            jerry_value_t jSmoothVal = jerryx_get_property_str(jLineStyleVal, styleName);
            seriesOptions_->smooth = jerry_get_boolean_value(jSmoothVal);
            jerry_release_value(jSmoothVal);
        }
        jerry_release_value(jLineStyleVal);
    }
}

void ChartComponent::RecordOptionsSeriesPoint(jerry_value_t jSeriesVal, PointType type)
{
    char* styleName = nullptr;
    switch (type) {
        case PointType::HEAD: {
            styleName = const_cast<char *>(HEAD_POINT);
            break;
        }
        case PointType::TOP: {
            styleName = const_cast<char *>(TOP_POINT);
            break;
        }
        case PointType::BOTTOM: {
            styleName = const_cast<char *>(BOTTOM_POINT);
            break;
        }
        default: {
            break;
        }
    }
    if ((styleName == nullptr) || !jerryx_has_property_str(jSeriesVal, styleName)) {
        return;
    }
    jerry_value_t jPointStyleVal = jerryx_get_property_str(jSeriesVal, styleName);
    styleName = const_cast<char *>(SIZE);
    uint8_t defaultValue = 4;
    uint8_t size = GetSizeVal(jPointStyleVal, styleName, defaultValue);
    uint32_t defalutColorVal = 0xff0000;
    styleName = const_cast<char *>(STROKE_COLOR);
    uint32_t strokeColor = GetColor(jPointStyleVal, styleName, defalutColorVal);
    defaultValue = 1;
    styleName = const_cast<char *>(STROKE_WIDTH);
    uint8_t strokeWidth = GetSizeVal(jPointStyleVal, styleName, defaultValue);
    styleName = const_cast<char *>(FILL_COLOR);
    uint32_t fillColor = GetColor(jPointStyleVal, styleName, defalutColorVal);
    bool isDisplay = GetDisplayStatus(jPointStyleVal);

    jerry_release_value(jPointStyleVal);
    switch (type) {
        case PointType::HEAD: {
            seriesOptions_->isHeadSet = isDisplay;
            seriesOptions_->head->size = size;
            seriesOptions_->head->strokeColor = strokeColor;
            seriesOptions_->head->fillColor = fillColor;
            seriesOptions_->head->strokeWidth = strokeWidth;
            break;
        }
        case PointType::TOP: {
            seriesOptions_->isTopSet = isDisplay;
            seriesOptions_->top->size = size;
            seriesOptions_->top->strokeColor = strokeColor;
            seriesOptions_->top->fillColor = fillColor;
            seriesOptions_->top->strokeWidth = strokeWidth;
            break;
        }
        case PointType::BOTTOM: {
            seriesOptions_->isBottomSet = isDisplay;
            seriesOptions_->bottom->size = size;
            seriesOptions_->bottom->strokeColor = strokeColor;
            seriesOptions_->bottom->fillColor = fillColor;
            seriesOptions_->bottom->strokeWidth = strokeWidth;
            break;
        }
        default: {
            break;
        }
    }
}

void ChartComponent::RecordOptionsSeriesLoop(jerry_value_t jSeriesVal)
{
    char* styleName = const_cast<char *>(LOOP);
    if (!jerryx_has_property_str(jSeriesVal, styleName)) {
        return;
    }

    jerry_value_t jLoopStyleVal = jerryx_get_property_str(jSeriesVal, styleName);
    seriesOptions_->isLoopSet = GetDisplayStatus(jLoopStyleVal);

    styleName = const_cast<char *>(MARGIN);
    if (!jerryx_has_property_str(jLoopStyleVal, styleName)) {
        seriesOptions_->margin = 1;
    } else {
        int16_t marginVal = JerryGetIntegerProperty(jLoopStyleVal, styleName);
        seriesOptions_->margin = marginVal;
    }
    jerry_release_value(jLoopStyleVal);
}

inline void ChartComponent::Reset()
{
    totalSerialsNum_ = 0;
}

void ChartComponent::AddDataSerial(DataSerials *serial)
{
    if (serial == nullptr) {
        return;
    }
    if (serials_) {
        serial->next = serials_;
        totalSerialsNum_++;
    } else {
        totalSerialsNum_ = 1;
    }
    serials_ = serial;
}

ChartComponent* ChartComponent::GetChartComponent(jerry_value_t nativeElement)
{
    ChartComponent* chartComponent =
        reinterpret_cast<ChartComponent *>(ComponentUtils::GetComponentFromBindingObject(nativeElement));
    if (chartComponent == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "get binded component fail");
    }
    return chartComponent;
}

const DataSerials* ChartComponent::GetDataSerial(ChartComponent* chartComponent, uint8_t index)
{
    if (chartComponent == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "chartComponent is null");
        return nullptr;
    }
    uint8_t targetSerial = index + 1;
    if (targetSerial > chartComponent->totalSerialsNum_) {
        HILOG_ERROR(HILOG_MODULE_ACE, "data serial index should not larger than total serials num - 1");
        return nullptr;
    }
    targetSerial = chartComponent->totalSerialsNum_ - targetSerial + 1; // serials_ is added reversed before
    DataSerials* serial = chartComponent->serials_;
    while (targetSerial > 1) {
        serial = serial->next;
        targetSerial--;
    }
    return serial;
}

void ChartComponent::ClearDataSerialsNode(DataSerials* serial)
{
    if (serial == nullptr) {
        return;
    } else {
        if (serial->next) {
            ClearDataSerialsNode(serial->next);
        }
        if (serial->dataSerial) {
            delete (serial->dataSerial);
            serial->dataSerial = nullptr;
        }
        delete (serial);
        serial = nullptr;
    }
}

void ChartComponent::ClearAllDataSerials()
{
    ClearDataSerialsNode(serials_);
    serials_ = nullptr;
}

uint16_t ChartComponent::GetSizeVal(jerry_value_t obj, const char * const styleName, uint16_t defaultValue)
{
    if (jerryx_has_property_str(obj, styleName)) {
        uint16_t len = 0;
        char* sizeVal = JerryMallocStringProperty(obj, styleName, len);
        if (sizeVal == nullptr) {
            HILOG_WARN(HILOG_MODULE_ACE, "Get Style String value failed, return default value!");
            return defaultValue;
        }
        uint16_t size = strtol(sizeVal, nullptr, DEC);
        ace_free(sizeVal);
        sizeVal = nullptr;
        return size;
    }
    return defaultValue;
}

uint32_t ChartComponent::GetColor(jerry_value_t obj, const char * const styleName, uint32_t defaultValue)
{
    uint8_t alpha = 0;
    uint32_t color = defaultValue;
    uint16_t len = 0;
    char* styleValue = JerryMallocStringProperty(obj, styleName, len);
    if (!ParseColor(styleValue, color, alpha)) {
        HILOG_WARN(HILOG_MODULE_ACE, "color format error");
    }
    ACE_FREE(styleValue);
    return color;
}

bool ChartComponent::GetDisplayStatus(jerry_value_t obj)
{
    if (!jerryx_has_property_str(obj, DISPLAY)) {
        return true;
    } else {
        jerry_value_t jDisplayValue = jerryx_get_property_str(obj, DISPLAY);
        return jerry_get_boolean_value(jDisplayValue);
    }
}

bool ChartComponent::Init()
{
    seriesOptions_ = new SeriesOptions();
    if (seriesOptions_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "malloc seriesOptions heap error");
        return false;
    }
    seriesOptions_->head = new PointOptions();
    if (seriesOptions_->head == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "malloc PointOptions head heap error");
        return false;
    }
    seriesOptions_->top = new PointOptions();
    if (seriesOptions_->top == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "malloc PointOptions top heap error");
        return false;
    }
    seriesOptions_->bottom = new PointOptions();
    if (seriesOptions_->bottom == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "malloc PointOptions bottom heap error");
        return false;
    }

    xAxis_ = &(chartView_->GetXAxis());
    yAxis_ = &(chartView_->GetYAxis());
    if ((xAxis_ == nullptr) || (yAxis_ == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "get axis error");
        return false;
    }
    const int8_t originPosition = 0;
    chartView_->SetPosition(originPosition, originPosition);
    chartView_->SetStyle(StyleDefault::GetBrightStyle());
    chartView_->SetStyle(STYLE_BACKGROUND_OPA, 0);
    chartView_->SetStyle(STYLE_BORDER_OPA, 0);
    chartView_->SetStyle(STYLE_BORDER_WIDTH, 0);
    chartView_->SetStyle(STYLE_PADDING_LEFT, 0);
    RegisterNamedFunction(FUNC_JS_API, AppendDatas);
    return true;
}
} // namespace ACELite
} // namespace OHOS
