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

/**
 * @addtogroup Graphic
 * @{
 *
 * @brief Defines a lightweight graphics system that provides basic UI and container views,
 *        including buttons, images, labels, lists, animators, scroll views, swipe views, and layouts.
 *        This system also provides the Design for X (DFX) capability to implement features such as
 *        view rendering, animation, and input event distribution.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file ui_chart.h
 *
 * @brief Defines the attributes of the chart component and provides functions for adding and deleting
 *        data sets to display a chart.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_CHART_H
#define GRAPHIC_LITE_UI_CHART_H

#include "components/ui_axis.h"
#include "components/ui_label.h"
#include "components/ui_view_group.h"
#include "list.h"

namespace OHOS {
class UIChart;
/**
 * @brief Defines a data set and provides functions such as adding and deleting data points.
 *
 * @since 1.0
 * @version 1.0
 */
class UIChartDataSerial : public HeapBase {
public:
    /**
     * @brief A constructor used to create a <b>UIChartDataSerial</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIChartDataSerial();

    /**
     * @brief A destructor used to delete the <b>UIChartDataSerial</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIChartDataSerial()
    {
        if (pointArray_ != nullptr) {
            UIFree(pointArray_);
            pointArray_ = nullptr;
        }
    }

    /**
     * @brief Sets the maximum number of data points that can be stored in a data set.
     *
     * This function must be called before data is added, deleted, or modified. Otherwise, data operations will fail.
     *
     * @param maxCount Indicates the number of data points. The default value is <b>0</b>.
     *
     * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool SetMaxDataCount(uint16_t maxCount);

    /**
     * @brief Modifies the value of a data point in the data set.
     *
     * @param index Indicates the index of the data point to modify.
     * @param point Indicates the new value of the data point.
     *
     * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool ModifyPoint(uint16_t index, const Point& point);

    /**
     * @brief Obtains the coordinates in the chart for a data point in the data set.
     *
     * @param index Indicates the index of the data point to obtain.
     * @param point Indicates the obtained coordinates. If the data set is not added to the chart,
     *              the original value of the data point is printed.
     *
     * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool GetPoint(uint16_t index, Point& point);

    /**
     * @brief Adds data points.
     *
     * The new data points are appended to the last added data. \n
     * No more data points can be added if the maximum number is reached \n
     *
     * @param data  Indicates the pointer to the start address of the data point.
     * @param count Indicates the number of data points to add.
     * @return Returns <b>true</b> if the data points are added successfully; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool AddPoints(const Point* data, uint16_t count);

    /**
     * @brief Clears all data points.
     *
     * @since 1.0
     * @version 1.0
     */
    void ClearData();

    /**
     * @brief Obtains the number of data points available in the data set.
     *
     * @return Returns the number of data points.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetDataCount() const
    {
        return dataCount_;
    }

    /**
     * @brief Sets whether to smooth a polyline.
     *
     * This function applies only to line charts. After the smoothing, some data is discarded.
     * Therefore, the polyline does not pass through all data points. \n
     * If <b>smooth</b> is set to <b>true</b>, the filling color, top point, and bottom point of a line chart have
     * deviations. Therefore, you are advised not to use these functions at the same time. \n
     *
     * @param smooth Specifies whether to smooth a polyline. Value <b>true</b> means to smooth a polyline, and value
     *               <b>false</b> means not to smooth a polyline. The default value is <b>false</b>.
     * @since 1.0
     * @version 1.0
     */
    void EnableSmooth(bool smooth)
    {
        smooth_ = smooth;
    }

    /**
     * @brief Checks whether smoothing is performed on a polyline.
     *
     * @return Returns <b>true</b> if smooth processing is performed on the polyline; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsSmooth() const
    {
        return smooth_;
    }

    /**
     * @brief Enables the fill color of a line chart.
     *
     * This function applies only to line charts. By default, the area between the polyline and the x-axis is filled.
     * You can use {@link SetGradientBottom} to modify the filled region. \n
     *
     * @param enable Specifies whether to enable the fill color. Value <b>true</b> means to enable the fill color,
     *               and value <b>false</b> means to disable the fill color. The default value is <b>false</b>.
     * @since 1.0
     * @version 1.0
     */
    void EnableGradient(bool enable)
    {
        enableGradient_ = enable;
    }

    /**
     * @brief Checks whether a polyline has a fill color.
     *
     * @return Returns <b>true</b> if there is a fill color; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsGradient() const
    {
        return enableGradient_;
    }

    /**
     * @brief Obtains the index of the top point in the data set.
     *
     * @return Returns the index of the top point. If there are multiple top points, the first one is returned.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetPeakIndex() const
    {
        return peakPointIndex_;
    }

    /**
     * @brief Obtains the index of the frontmost point (the latest added or modified data point in a data set).
     *
     * @return Returns the index of the frontmost point.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetLatestIndex() const
    {
        return latestIndex_;
    }

    /**
     * @brief Obtains the index of the bottom point in a data set.
     *
     * @return Returns the index of the bottom point. If there are multiple bottom points, the first one is returned.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetValleyIndex() const
    {
        return valleyPointIndex_;
    }

    /**
     * @brief Obtains the Y value of the top point in a data set.
     *
     * The Y value is the data added by users, not the pixel coordinate.
     *
     * @return Returns the Y value.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetPeakData() const
    {
        return peakData_;
    }

    /**
     * @brief Obtains the Y value of the bottom point in a data set.
     *
     * The Y value is the data added by users, not the pixel coordinate.
     *
     * @return Returns the Y value.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetValleyData() const
    {
        return valleyData_;
    }

    void SetLastPointIndex(uint16_t value)
    {
        lastPointIndex_ = value;
    }

    uint16_t GetLastPointIndex() const
    {
        return lastPointIndex_;
    }

    /**
     * @brief Obtains the polyline color of the data set in a line chart.
     *
     * @return Returns the polyline color of the data set.
     * @see SetLineColor
     * @since 1.0
     * @version 1.0
     */
    ColorType GetLineColor() const
    {
        return serialColor_;
    }

    /**
     * @brief Obtains the fill color of the data set.
     *
     * @return Returns the fill color.
     * @see SetFillColor
     * @since 1.0
     * @version 1.0
     */
    ColorType GetFillColor() const
    {
        return fillColor_;
    }

    /**
     * @brief Sets the fill color of the data set.
     *
     * For a line chart, <b>color</b> refers to the fill color between the line and the x-axis.
     * For a bar chart, <b>color</b> refers to the color of the bars.
     *
     * @param color Indicates the fill color to set.
     * @see GetFillColor
     * @since 1.0
     * @version 1.0
     */
    void SetFillColor(const ColorType& color)
    {
        fillColor_ = color;
    }

    /**
     * @brief Sets the polyline color of the data set in the line chart.
     *
     * This function applies only to line charts.
     *
     * @param color Indicates the polyline color to set.
     * @see GetLineColor
     * @since 1.0
     * @version 1.0
     */
    void SetLineColor(const ColorType& color)
    {
        serialColor_ = color;
    }

    void BindToChart(UIChart* chart)
    {
        chart_ = chart;
    }

    /**
     * @brief Hides some points in the data set.
     *
     * This function applies only to line charts. After the points are hidden, the line connected by the points
     * is not displayed. \n
     * The top and bottom points may appear in the hidden region. If this method is enabled,
     * you are not advised to enable the display of the top and bottom points.
     *
     * @param index Indicates the point from which the hide starts.
     * @param count Indicates the number of points to hide.
     * @since 1.0
     * @version 1.0
     */
    void HidePoint(uint16_t index, uint16_t count);

    /**
     * @brief Obtains the index from which the data set starts to hide.
     *
     * @return Returns the index.
     * @see HidePoint
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetHideIndex() const
    {
        return hideIndex_;
    }

    /**
     * @brief Obtains the number of hidden points in the data set.
     *
     * @return Returns the number of hidden points.
     * @see HidePoint
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetHideCount() const
    {
        return hideCount_;
    }

    /**
     * @brief Defines the style for the top, bottom, and frontmost points in a line chart.
     */
    struct PointStyle : public HeapBase {
        /** Fill color */
        ColorType fillColor;
        /** Border color */
        ColorType strokeColor;
        /** Inner radius */
        uint16_t radius;
        /** Border width, which extends outwards from the inner radius */
        uint16_t strokeWidth;
    };

    /**
     * @brief Sets the style of the frontmost point on a polyline.
     *
     * @param style Indicates the style to set. For details, see {@link PointStyle}.
     * @since 1.0
     * @version 1.0
     */
    void SetHeadPointStyle(const PointStyle& style)
    {
        headPointStyle_ = style;
    }

    /**
     * @brief Sets the style of the top point of a polyline.
     *
     * @param style Indicates the style to set. For details, see {@link PointStyle}.
     * @since 1.0
     * @version 1.0
     */
    void SetTopPointStyle(const PointStyle& style)
    {
        topPointStyle_ = style;
    }

    /**
     * @brief Sets the style of the bottom point of a polyline.
     *
     * @param style Indicates the style to set. For details, see {@link PointStyle}.
     * @since 1.0
     * @version 1.0
     */
    void SetBottomPointStyle(const PointStyle& style)
    {
        bottomPointStyle_ = style;
    }

    /**
     * @brief Obtains the style of the frontmost point on a polyline.
     *
     * @return Returns the style of the point. For details, see {@link PointStyle}.
     * @since 1.0
     * @version 1.0
     */
    const PointStyle& GetHeadPointStyle() const
    {
        return headPointStyle_;
    }

    /**
     * @brief Obtains the style of the top point of a polyline.
     *
     * @return Returns the style of the point. For details, see {@link PointStyle}.
     * @since 1.0
     * @version 1.0
     */
    const PointStyle& GetTopPointStyle() const
    {
        return topPointStyle_;
    }

    /**
     * @brief Obtains the style of the bottom point of a polyline.
     *
     * @return Returns the style of the point. For details, see {@link PointStyle}.
     * @since 1.0
     * @version 1.0
     */
    const PointStyle& GetBottomPointStyle() const
    {
        return bottomPointStyle_;
    }

    /**
     * @brief Enables the feature of drawing the frontmost point on a polyline.
     *
     * @param enable Specifies whether to draw the frontmost point. Value <b>true</b> means to draw the frontmost
     *               point, and value <b>false</b> means not to draw the frontmost point.
     * @since 1.0
     * @version 1.0
     */
    void EnableHeadPoint(bool enable)
    {
        enableHeadPoint_ = enable;
    }

    /**
     * @brief Enables the feature of drawing the top point of a polyline. If there are multiple top points,
     *        only the first one is drawn.
     *
     * @param enable Specifies whether to draw the top point. Value <b>true</b> means to draw the top point,
     *               and value <b>false</b> means not to draw the top point.
     * @since 1.0
     * @version 1.0
     */
    void EnableTopPoint(bool enable)
    {
        enableTopPoint_ = enable;
    }

    /**
     * @brief Enables the feature of drawing the bottom point of a polyline. If there are multiple bottom points,
     *        only the first one is drawn.
     *
     * @param enable Specifies whether to draw the bottom point. Value <b>true</b> means to draw the bottom point,
     *               and value <b>false</b> means not to draw the bottom point.
     * @since 1.0
     * @version 1.0
     */
    void EnableBottomPoint(bool enable)
    {
        enableBottomPoint_ = enable;
    }

    void DrawPoint(const Rect& mask);

    void Refresh();

protected:
    uint16_t maxCount_;
    Point* pointArray_;

private:
    constexpr static uint16_t DEFAULT_POINT_RADIUS = 5;
    constexpr static uint16_t MAX_POINTS_COUNT = 512;

    ColorType serialColor_;
    ColorType fillColor_;
    uint16_t dataCount_;
    uint16_t peakPointIndex_;
    int16_t peakData_;
    int16_t valleyData_;
    uint16_t valleyPointIndex_;
    uint16_t lastPointIndex_;
    uint16_t latestIndex_;
    uint16_t hideIndex_;
    uint16_t hideCount_;
    bool smooth_ : 1;
    bool enableGradient_ : 1;
    bool enableHeadPoint_ : 1;
    bool enableTopPoint_ : 1;
    bool enableBottomPoint_ : 1;
    PointStyle headPointStyle_;
    PointStyle topPointStyle_;
    PointStyle bottomPointStyle_;
    UIChart* chart_;
    Rect invalidateRect_;
    void RefreshInvalidateRect(uint16_t startIndex, uint16_t endIndex);
    void RefreshInvalidateRect(uint16_t pointIndex, const PointStyle& style);
    bool UpdatePeakAndValley(uint16_t startPos, uint16_t endPos);
    void DoDrawPoint(const Point& point, const PointStyle& style, const Rect& mask);
};

/**
 * @brief Defines the chart class and provides functions such as adding and deleting data sets to display a chart.
 *
 * @since 1.0
 * @version 1.0
 */
class UIChart : public UIViewGroup {
public:
    /**
     * @brief A constructor used to create a <b>UIChart</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIChart() : enableReverse_(false), needRefresh_(false), mixData_(nullptr)
    {
        Add(&xAxis_);
        Add(&yAxis_);
        SetStyle(STYLE_LINE_WIDTH, 1);
        SetStyle(STYLE_BACKGROUND_COLOR, Color::Black().full);
    }

    /**
     * @brief A destructor used to delete the <b>UIChart</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIChart();

    /**
     * @brief Obtains the view type.
     *
     * @return Returns the view type. For details, see {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_CHART;
    }

    /**
     * @brief Sets the height for this component.
     *
     * @param height Indicates the height to set.
     * @since 1.0
     * @version 1.0
     */
    void SetHeight(int16_t height) override;

    /**
     * @brief Sets the width for this component.
     *
     * @param width Indicates the width to set.
     * @since 1.0
     * @version 1.0
     */
    void SetWidth(int16_t width) override;

    bool OnPreDraw(const Rect& invalidatedArea) override
    {
        return false;
    }

    void OnDraw(const Rect& invalidatedArea) override;

    /**
     * @brief Adds a data set.
     *
     * @param dataSerial Indicates the pointer to the data set class. For details, see {@link UIChartDataSerial}.
     * @return Returns <b>true</b> if the data set is added successfully; returns <b>false</b> otherwise.
     * @see DeleteDataSerial
     * @since 1.0
     * @version 1.0
     */
    virtual bool AddDataSerial(UIChartDataSerial* dataSerial);

    /**
     * @brief Deletes a data set.
     *
     * @param dataSerial Indicates the pointer to the data set class. For details, see {@link UIChartDataSerial}.
     * @return Returns <b>true</b> if the data set is deleted successfully; returns <b>false</b> otherwise.
     * @see AddDataSerial
     * @since 1.0
     * @version 1.0
     */
    virtual bool DeleteDataSerial(UIChartDataSerial* dataSerial);

    /**
     * @brief Clears all data sets.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void ClearDataSerial();

    /**
     * @brief Refreshes a chart and redraws the dirty region.
     *
     * Only the parts that need to be redrawn are refreshed, for example, new data points.
     * This function provides better performance than {@link Invalidate}.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void RefreshChart() = 0;

    /**
     * @brief Obtains the x-axis instance.
     *
     * @return Returns the x-axis instance.
     * @since 1.0
     * @version 1.0
     */
    UIXAxis& GetXAxis()
    {
        return xAxis_;
    }

    /**
     * @brief Obtains the y-axis instance.
     *
     * @return Returns the y-axis instance.
     * @since 1.0
     * @version 1.0
     */
    UIYAxis& GetYAxis()
    {
        return yAxis_;
    }

    /**
     * @brief Enables chart reverse.
     *
     * After the chart is reversed, the x-axis aligns with the top of the chart. The pixel position corresponding
     * to the data point remains unchanged. Complementary filling is performed on the chart
     * (only the part that is not filled previously will be filled).
     *
     * @param enable Specifies whether to enable chart reverse. Value <b>true</b> means to enable chart reverse,
     *               and value <b>false</b> means not to enable chart reverse. The default value is <b>false</b>.
     * @since 1.0
     * @version 1.0
     */
    void EnableReverse(bool enable)
    {
        if (enableReverse_ != enable) {
            enableReverse_ = enable;
            xAxis_.EnableReverse(enable);
            yAxis_.EnableReverse(enable);
        }
    }

protected:
    List<UIChartDataSerial*> list_;
    UIXAxis xAxis_;
    UIYAxis yAxis_;
    bool enableReverse_;
    bool needRefresh_;
    uint8_t* mixData_;
    virtual void DrawDataSerials(const Rect& invalidatedArea) = 0;
};

/**
 * @brief Provides special functions for implementing a bar chart.
 *
 * @since 1.0
 * @version 1.0
 */
class UIChartPillar : public UIChart {
public:
    /**
     * @brief A constructor used to create a <b>UIChartPillar</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIChartPillar() {}

    /**
     * @brief A destructor used to delete the <b>UIChartPillar</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIChartPillar() {}

    /**
     * @brief Refreshes a bar chart and redraws the dirty region.
     *
     * Only the parts that need to be redrawn are refreshed, for example, new data points.
     * This function provides better performance than {@link Invalidate}.
     *
     * @since 1.0
     * @version 1.0
     */
    void RefreshChart() override;

protected:
    void DrawDataSerials(const Rect& invalidatedArea) override;

private:
    static constexpr float DEFAULT_MARK_PERCENTAGE = 0.1f;
};

/**
 * @brief Provides special functions for implementing a polyline.
 *
 * @since 1.0
 * @version 1.0
 */
class UIChartPolyline : public UIChart {
public:
    /**
     * @brief A constructor used to create a <b>UIChartPolyline</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIChartPolyline() : minOpa_(OPA_TRANSPARENT), maxOpa_(OPA_OPAQUE), gradientBottom_(0) {}

    /**
     * @brief A destructor used to delete the <b>UIChartPolyline</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIChartPolyline() {}

    /**
     * @brief Refreshes a line chart and redraws the dirty region.
     *
     * Only the parts that need to be redrawn are refreshed, for example, new data points.
     * This function provides better performance than {@link Invalidate}.
     *
     * @since 1.0
     * @version 1.0
     */
    void RefreshChart() override;

    /**
     * @brief Sets the opacity range of the fill color gradient.
     *
     * This function sets the opacity range between the top point and bottom point of the line chart.
     * The opacity of each horizontal line is calculated based on the ratio.
     *
     * @param minOpa Indicates the opacity closest to the x-axis.
     * @param maxOpa Indicates the opacity farthest away from the x-axis.
     * @since 1.0
     * @version 1.0
     */
    void SetGradientOpacity(uint8_t minOpa, uint8_t maxOpa)
    {
        minOpa_ = minOpa;
        maxOpa_ = maxOpa;
        needRefresh_ = true;
        AddMeasureView();
    }

    /**
     * @brief Sets the distance between the bottom edge of the fill color range and the x-axis.
     *
     * This function fills in the area between the polyline and bottom of the line chart. For a chart that is not
     * reversed, if the bottom is above the polyline, there is no filling. For a reversed chart,
     * if the bottom is below the polyline, there is no filling.
     *
     * @param bottom Indicates the bottom of the filling range. The value is the distance to the x-axis.
     * @since 1.0
     * @version 1.0
     */
    void SetGradientBottom(uint16_t bottom)
    {
        gradientBottom_ = bottom;
    }

protected:
    void DrawDataSerials(const Rect& invalidatedArea) override;

private:
    struct ChartLine {
        Point start;
        Point end;
    };

    struct CrossPointSet {
        Point first;
        Point second;
        Point nextFirst;
        bool firstFind;
        bool secondFind;
    };

    constexpr static uint8_t SMOOTH_SLOPE_ANGLE = 3;
    uint8_t minOpa_;
    uint8_t maxOpa_;
    uint16_t gradientBottom_;

    void GradientColor(const Rect& invalidatedArea, UIChartDataSerial* data);
    void DrawGradientColor(const Rect& invalidatedArea, UIChartDataSerial* data,
        const ChartLine& linePoints, const ChartLine& limitPoints, int16_t startY);
    void DrawSmoothPolyLine(uint16_t startIndex, uint16_t endIndex, const Rect& invalidatedArea,
        UIChartDataSerial* data);
    void DrawPolyLine(uint16_t startIndex, uint16_t endIndex, const Rect& invalidatedArea, UIChartDataSerial* data);
    bool GetLineCrossPoint(const Point& p1, const Point& p2, const Point& p3, const Point& p4, Point& cross);
    void FindCrossPoints(const ChartLine& line, const ChartLine& polyLine, CrossPointSet& cross);
    void ReMeasure() override;
    void CalcVerticalInfo(int16_t top, int16_t bottom, int16_t start, int16_t end, int16_t& y, int16_t& yHeight);
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_CHART_H
