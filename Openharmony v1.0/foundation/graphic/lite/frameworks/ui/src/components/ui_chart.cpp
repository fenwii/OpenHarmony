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

#include "components/ui_chart.h"
#include "common/typed_text.h"
#include "draw/draw_arc.h"
#include "draw/draw_line.h"
#include "geometry2d.h"
#include "securec.h"

namespace OHOS {
UIChart::~UIChart()
{
    if (mixData_ != nullptr) {
        UIFree(mixData_);
        mixData_ = nullptr;
    }
    ClearDataSerial();
    Remove(&xAxis_);
    Remove(&yAxis_);
    DeleteMeasureView();
}

void UIChart::SetHeight(int16_t height)
{
    if (GetHeight() == height) {
        return;
    }

    if (height > 0) {
        needRefresh_ = true;
        AddMeasureView();
    }

    UIViewGroup::SetHeight(height);
    xAxis_.SetHeight(height);
    xAxis_.UpdateAxis();
    yAxis_.SetHeight(height);
    yAxis_.UpdateAxis();
}

void UIChart::SetWidth(int16_t width)
{
    UIViewGroup::SetWidth(width);
    xAxis_.SetWidth(width);
    yAxis_.SetWidth(width);
    xAxis_.UpdateAxis();
    yAxis_.UpdateAxis();
}

void UIChart::OnDraw(const Rect& invalidatedArea)
{
    UIViewGroup::OnDraw(invalidatedArea);
    Rect rect = GetContentRect();
    if (rect.Intersect(rect, invalidatedArea)) {
        DrawDataSerials(rect);
    }
}

bool UIChart::AddDataSerial(UIChartDataSerial* dataSerial)
{
    if (dataSerial == nullptr) {
        return false;
    }

    ListNode<UIChartDataSerial*>* serialNode = list_.Head();
    while (serialNode != list_.End()) {
        if (serialNode->data_ == dataSerial) {
            return false;
        }
        serialNode = serialNode->next_;
    }
    list_.PushBack(dataSerial);
    dataSerial->BindToChart(this);
    return true;
}

bool UIChart::DeleteDataSerial(UIChartDataSerial* dataSerial)
{
    if ((dataSerial == nullptr) || (list_.IsEmpty())) {
        return false;
    }

    bool findSerial = false;
    ListNode<UIChartDataSerial*>* serialNode = list_.Head();
    while (serialNode != list_.End()) {
        if (serialNode->data_ == dataSerial) {
            dataSerial->BindToChart(nullptr);
            list_.Remove(serialNode);
            findSerial = true;
            break;
        }
        serialNode = serialNode->next_;
    }

    return findSerial;
}

void UIChart::ClearDataSerial()
{
    if (list_.IsEmpty()) {
        return;
    }

    ListNode<UIChartDataSerial*>* serialNode = list_.Head();
    while (serialNode != list_.End()) {
        serialNode->data_->BindToChart(nullptr);
        ListNode<UIChartDataSerial*>* tempNode = serialNode;
        serialNode = serialNode->next_;
        list_.Remove(tempNode);
    }
    list_.Clear();
}

UIChartDataSerial::UIChartDataSerial()
    : maxCount_(0), pointArray_(nullptr), serialColor_(Color::White()), fillColor_(Color::White()),
      dataCount_(0), peakPointIndex_(0), peakData_(0), valleyData_(0), valleyPointIndex_(0),
      lastPointIndex_(0), latestIndex_(0), hideIndex_(0), hideCount_(0), smooth_(false),
      enableGradient_(false), enableHeadPoint_(false), enableTopPoint_(false), enableBottomPoint_(false),
      chart_(nullptr), invalidateRect_(0, 0, 0, 0)
{
    PointStyle style;
    style.radius = DEFAULT_POINT_RADIUS;
    style.strokeWidth = 1;
    style.fillColor = Color::White();
    style.strokeColor = Color::White();
    topPointStyle_ = style;
    bottomPointStyle_ = style;
    headPointStyle_ = style;
}

bool UIChartDataSerial::SetMaxDataCount(uint16_t maxCount)
{
    if (maxCount > MAX_POINTS_COUNT) {
        maxCount = MAX_POINTS_COUNT;
    }

    if (maxCount == maxCount_) {
        return true;
    }

    if (pointArray_ != nullptr) {
        UIFree(pointArray_);
        pointArray_ = nullptr;
    }

    maxCount_ = maxCount;
    if (maxCount_ == 0) {
        return true;
    }

    pointArray_ = static_cast<Point*>(UIMalloc(sizeof(Point) * maxCount_));
    if (pointArray_ == nullptr) {
        maxCount_ = 0;
        return false;
    }
    return true;
}

bool UIChartDataSerial::ModifyPoint(uint16_t index, const Point& point)
{
    if ((index >= maxCount_) || (pointArray_ == nullptr)) {
        return false;
    }

    pointArray_[index].x = point.x;
    pointArray_[index].y = point.y;
    if (point.y > peakData_) {
        if (enableTopPoint_) {
            RefreshInvalidateRect(peakPointIndex_, topPointStyle_);
        }
        peakPointIndex_ = index;
        peakData_ = point.y;
    } else if (point.y < valleyData_) {
        if (enableBottomPoint_) {
            RefreshInvalidateRect(valleyPointIndex_, bottomPointStyle_);
        }
        valleyPointIndex_ = index;
        valleyData_ = point.y;
    } else if (index == peakPointIndex_ || index == valleyPointIndex_) {
        UpdatePeakAndValley(0, dataCount_);
    }

    latestIndex_ = index;
    uint16_t startIndex = (index == 0) ? index : (index - 1);
    RefreshInvalidateRect(startIndex, index + 1);
    return true;
}

bool UIChartDataSerial::GetPoint(uint16_t index, Point& point)
{
    if ((index >= dataCount_) || (pointArray_ == nullptr)) {
        return false;
    }
    point = pointArray_[index];
    if (chart_ != nullptr) {
        chart_->GetXAxis().TranslateToPixel(point.x);
        chart_->GetYAxis().TranslateToPixel(point.y);
    }
    return true;
}

void UIChartDataSerial::HidePoint(uint16_t index, uint16_t count)
{
    RefreshInvalidateRect(hideIndex_, hideIndex_ + hideCount_);
    hideIndex_ = index;
    hideCount_ = count;
    RefreshInvalidateRect(hideIndex_, hideIndex_ + hideCount_);
}

void UIChartDataSerial::RefreshInvalidateRect(uint16_t pointIndex, const PointStyle& style)
{
    Point point;
    if (GetPoint(pointIndex, point)) {
        uint16_t width = style.radius + style.strokeWidth;
        Rect refresh(point.x - width, 0, point.x + width, 0);
        if (invalidateRect_.GetLeft() == 0 && invalidateRect_.GetRight() == 0) {
            invalidateRect_ = refresh;
        } else {
            invalidateRect_.Join(invalidateRect_, refresh);
        }
    }
}

void UIChartDataSerial::RefreshInvalidateRect(uint16_t startIndex, uint16_t endIndex)
{
    Point start;
    GetPoint(startIndex, start);
    Point end;
    endIndex = (endIndex >= dataCount_) ? (dataCount_ - 1) : endIndex;
    GetPoint(endIndex, end);
    int16_t xMin = MATH_MIN(start.x, end.x);
    int16_t xMax = MATH_MAX(start.x, end.x);
    Rect refresh(xMin, 0, xMax, 0);
    if (invalidateRect_.GetLeft() == 0 && invalidateRect_.GetRight() == 0) {
        invalidateRect_ = refresh;
    } else {
        invalidateRect_.Join(invalidateRect_, refresh);
    }
}

bool UIChartDataSerial::UpdatePeakAndValley(uint16_t startPos, uint16_t endPos)
{
    if ((startPos >= endPos) || (endPos > dataCount_) || (pointArray_ == nullptr)) {
        return false;
    }

    if (startPos == 0) {
        peakData_ = pointArray_[startPos].y;
        valleyData_ = pointArray_[startPos].y;
    }

    for (uint16_t i = startPos; i < endPos; i++) {
        if (pointArray_[i].y > peakData_) {
            if (enableTopPoint_) {
                RefreshInvalidateRect(peakPointIndex_, topPointStyle_);
                RefreshInvalidateRect(i, topPointStyle_);
            }
            peakPointIndex_ = i;
            peakData_ = pointArray_[i].y;
        }

        if (pointArray_[i].y < valleyData_) {
            if (enableBottomPoint_) {
                RefreshInvalidateRect(valleyPointIndex_, bottomPointStyle_);
                RefreshInvalidateRect(i, bottomPointStyle_);
            }
            valleyPointIndex_ = i;
            valleyData_ = pointArray_[i].y;
        }
    }
    return true;
}

bool UIChartDataSerial::AddPoints(const Point* data, uint16_t count)
{
    if ((maxCount_ <= dataCount_) || (count == 0) || (pointArray_ == nullptr) || data == nullptr) {
        return false;
    }

    if (count > (maxCount_ - dataCount_)) {
        count = maxCount_ - dataCount_;
    }

    Point* current = pointArray_ + dataCount_;
    if (memcpy_s(current, (maxCount_ - dataCount_) * sizeof(Point), data, count * sizeof(Point)) != EOK) {
        return false;
    }
    uint16_t i = dataCount_;
    dataCount_ += count;
    UpdatePeakAndValley(i, dataCount_);
    latestIndex_ = dataCount_ - 1;
    uint16_t startIndex = (i == 0) ? i : (i - 1);
    RefreshInvalidateRect(startIndex, latestIndex_);
    return true;
}

void UIChartDataSerial::ClearData()
{
    RefreshInvalidateRect(0, dataCount_ - 1);
    if (pointArray_ != nullptr) {
        if (memset_s(pointArray_, maxCount_ * sizeof(Point), 0, maxCount_ * sizeof(Point)) != EOK) {
            return;
        }
    }
    dataCount_ = 0;
    valleyPointIndex_ = 0;
    peakPointIndex_ = 0;
    latestIndex_ = 0;
}

void UIChartDataSerial::DoDrawPoint(const Point& center, const PointStyle& style, const Rect& mask)
{
    Style drawStyle = StyleDefault::GetDefaultStyle();
    drawStyle.lineOpa_ = OPA_OPAQUE;
    drawStyle.lineColor_ = style.fillColor;

    ArcInfo arcinfo = {{0}};
    arcinfo.center = center;
    arcinfo.imgPos = Point{0, 0};
    arcinfo.radius = style.radius + style.strokeWidth;
    arcinfo.startAngle = 0;
    arcinfo.endAngle = CIRCLE_IN_DEGREE;

    if (style.fillColor.full == style.strokeColor.full) {
        drawStyle.lineWidth_ = style.radius + style.strokeWidth;
        DrawArc::GetInstance()->Draw(arcinfo, mask, drawStyle, OPA_OPAQUE, CapType::CAP_NONE);
    } else {
        drawStyle.lineWidth_ = style.radius;
        arcinfo.radius = style.radius;
        DrawArc::GetInstance()->Draw(arcinfo, mask, drawStyle, OPA_OPAQUE, CapType::CAP_NONE);

        drawStyle.lineWidth_ = style.strokeWidth;
        drawStyle.lineColor_ = style.strokeColor;
        arcinfo.radius = style.radius + style.strokeWidth;
        DrawArc::GetInstance()->Draw(arcinfo, mask, drawStyle, OPA_OPAQUE, CapType::CAP_NONE);
    }
}

void UIChartDataSerial::DrawPoint(const Rect& mask)
{
    Point center;
    if (enableTopPoint_) {
        if (GetPoint(peakPointIndex_, center)) {
            DoDrawPoint(center, topPointStyle_, mask);
        }
    }

    if (enableBottomPoint_) {
        if (GetPoint(valleyPointIndex_, center)) {
            DoDrawPoint(center, bottomPointStyle_, mask);
        }
    }

    if (enableHeadPoint_) {
        if (GetPoint(latestIndex_, center)) {
            DoDrawPoint(center, headPointStyle_, mask);
        }
    }
}

void UIChartDataSerial::Refresh()
{
    if (chart_ != nullptr) {
        Rect refresh = chart_->GetContentRect();
        refresh.SetLeft(invalidateRect_.GetLeft() - headPointStyle_.radius - headPointStyle_.strokeWidth);
        refresh.SetRight(invalidateRect_.GetRight() + headPointStyle_.radius + headPointStyle_.strokeWidth);
        invalidateRect_.SetLeft(0);
        invalidateRect_.SetRight(0);
        chart_->InvalidateRect(refresh);
    }
}

void UIChartPillar::RefreshChart()
{
    ListNode<UIChartDataSerial*>* iter = list_.Begin();
    Rect rect = GetContentRect();
    for (; iter != list_.End(); iter = iter->next_) {
        UIChartDataSerial* data = iter->data_;
        uint16_t dataCount = data->GetDataCount();
        if (dataCount <= 1) {
            break;
        }

        int16_t index = data->GetLastPointIndex();
        if (index >= dataCount) {
            break;
        }

        Point current;
        data->GetPoint(index, current);
        Point last;
        data->GetPoint(dataCount - 1, last);
        Rect refresh(current.x, rect.GetTop(), last.x, rect.GetBottom());
        InvalidateRect(refresh);
        data->SetLastPointIndex(dataCount - 1);
    }
}

void UIChartPillar::DrawDataSerials(const Rect& invalidatedArea)
{
    xAxis_.UpdateAxisPoints();
    yAxis_.UpdateAxisPoints();
    uint16_t minXStep = static_cast<uint16_t>(xAxis_.GetMarkInterval());
    Point xStart = xAxis_.GetStartPoint();
    uint16_t dataSerialCount = list_.Size();
    if (dataSerialCount == 0) {
        return;
    }
    uint16_t width = minXStep / dataSerialCount;
    uint8_t dataSerialIndex = 0;
    uint16_t barWidth = static_cast<uint16_t>(width - DEFAULT_MARK_PERCENTAGE * (width << 1));

    for (ListNode<UIChartDataSerial*>* iter = list_.Begin(); iter != list_.End(); iter = iter->next_) {
        UIChartDataSerial* data = iter->data_;
        uint16_t dataSerialWidth = width * dataSerialIndex;
        int16_t x = dataSerialWidth + (width >> 1);
        for (uint16_t index = 0; index < data->GetDataCount(); index++) {
            Point current;
            data->GetPoint(index, current);
            if (current.y == xStart.y) {
                continue;
            }
            current.x += x;
            xStart.x = current.x;
            DrawLine::Draw(current, xStart, invalidatedArea, barWidth, data->GetFillColor(), style_->lineOpa_);
        }
        dataSerialIndex++;
    }
}

void UIChartPolyline::RefreshChart()
{
    ListNode<UIChartDataSerial*>* iter = list_.Begin();
    for (; iter != list_.End(); iter = iter->next_) {
        UIChartDataSerial* data = iter->data_;
        uint16_t dataCount = data->GetDataCount();
        if (dataCount == 1) {
            break;
        }
        data->Refresh();
    }
}

void UIChartPolyline::ReMeasure()
{
    if (!needRefresh_) {
        return;
    }
    needRefresh_ = false;
    int16_t height = GetHeight();
    if (mixData_ != nullptr) {
        UIFree(mixData_);
        mixData_ = nullptr;
    }
    if (height <= 0) {
        return;
    }
    if (height > COORD_MAX) {
        height = COORD_MAX;
    }
    mixData_ = static_cast<uint8_t*>(UIMalloc(height));
    if (mixData_ == nullptr) {
        return;
    }
    int16_t opa = maxOpa_ - minOpa_;
    for (int16_t y = 0; y < height; y++) {
        mixData_[y] = static_cast<uint8_t>(y * opa / height + minOpa_);
    }
}

void UIChartPolyline::DrawDataSerials(const Rect& invalidatedArea)
{
    xAxis_.UpdateAxisPoints();
    yAxis_.UpdateAxisPoints();
    ListNode<UIChartDataSerial*>* iter = list_.Begin();
    for (; iter != list_.End(); iter = iter->next_) {
        UIChartDataSerial* data = iter->data_;
        uint16_t dataCount = data->GetDataCount();
        if (dataCount <= 1) {
            continue;
        }
        if (data->IsGradient()) {
            GradientColor(invalidatedArea, data);
        }
        if (data->GetHideCount() != 0) {
            uint16_t hideIndex = data->GetHideIndex();
            DrawPolyLine(0, hideIndex, invalidatedArea, data);
            DrawPolyLine(hideIndex + data->GetHideCount(), dataCount - 1, invalidatedArea, data);
        } else {
            DrawPolyLine(0, dataCount - 1, invalidatedArea, data);
        }

        data->DrawPoint(invalidatedArea);
    }
}

void UIChartPolyline::DrawSmoothPolyLine(uint16_t startIndex, uint16_t endIndex, const Rect& invalidatedArea,
    UIChartDataSerial* data)
{
    if (data == nullptr) {
        return;
    }
    Point start;
    Point end;
    ColorType color = data->GetLineColor();
    Style style = *style_;
    style.lineColor_ = color;

    uint16_t slope;
    data->GetPoint(startIndex, start);
    data->GetPoint(startIndex + 1, end);
    uint16_t preSlope = (start.x == end.x) ? QUARTER_IN_DEGREE : FastAtan2(end.x - start.x, end.y - start.y);
    Point current;
    for (uint16_t i = startIndex; i < endIndex; i++) {
        data->GetPoint(i + 1, current);
        slope = (current.x == start.x) ? QUARTER_IN_DEGREE : FastAtan2(current.x - start.x, current.y - start.y);
        if (MATH_ABS(slope - preSlope) < SMOOTH_SLOPE_ANGLE) {
            end = current;
            continue;
        }
        preSlope = (current.x == end.x) ? QUARTER_IN_DEGREE : FastAtan2(current.x - end.x, current.y - end.y);
        Rect rect;
        rect.SetLeft(MATH_MIN(start.x, end.x) - style_->lineWidth_);
        rect.SetRight(MATH_MAX(start.x, end.x) + style_->lineWidth_);
        rect.SetTop(MATH_MIN(start.y, end.y) - style_->lineWidth_);
        rect.SetBottom(MATH_MAX(start.y, end.y) + style_->lineWidth_);
        if (!invalidatedArea.IsIntersect(rect)) {
            start = end;
            end = current;
            continue;
        }

        DrawLine::Draw(start, end, invalidatedArea, style_->lineWidth_, color, style_->lineOpa_);
        ArcInfo arcinfo = {{0}};
        arcinfo.center = end;
        arcinfo.imgPos = Point{0, 0};
        arcinfo.radius = (style_->lineWidth_ + 1) >> 1;
        arcinfo.startAngle = 0;
        arcinfo.endAngle = CIRCLE_IN_DEGREE;

        DrawArc::GetInstance()->Draw(arcinfo, invalidatedArea, style, opaScale_, CapType::CAP_NONE);

        start = end;
        end = current;
    }
    DrawLine::Draw(start, end, invalidatedArea, style_->lineWidth_, color, style_->lineOpa_);
}

void UIChartPolyline::DrawPolyLine(uint16_t startIndex, uint16_t endIndex, const Rect& invalidatedArea,
    UIChartDataSerial* data)
{
    if (startIndex >= endIndex || data == nullptr) {
        return;
    }

    if (data->IsSmooth()) {
        DrawSmoothPolyLine(startIndex, endIndex, invalidatedArea, data);
    } else {
        Point start;
        Point end;
        ColorType color = data->GetLineColor();
        for (uint16_t i = startIndex; i < endIndex; i++) {
            data->GetPoint(i, start);
            data->GetPoint(i + 1, end);
            Rect rect;
            rect.SetLeft(MATH_MIN(start.x, end.x) - style_->lineWidth_);
            rect.SetRight(MATH_MAX(start.x, end.x) + style_->lineWidth_);
            rect.SetTop(MATH_MIN(start.y, end.y) - style_->lineWidth_);
            rect.SetBottom(MATH_MAX(start.y, end.y) + style_->lineWidth_);
            if (!invalidatedArea.IsIntersect(rect)) {
                continue;
            }

            DrawLine::Draw(start, end, invalidatedArea, style_->lineWidth_, color, style_->lineOpa_);
        }
    }
}

bool UIChartPolyline::GetLineCrossPoint(const Point& p1, const Point& p2, const Point& p3, const Point& p4,
    Point& cross)
{
    /* Rectangular ranges of line segments must intersect. */
    if (MATH_MIN(p1.x, p2.x) <= MATH_MAX(p3.x, p4.x) &&
        MATH_MIN(p3.x, p4.x) <= MATH_MAX(p1.x, p2.x) &&
        MATH_MIN(p1.y, p2.y) <= MATH_MAX(p3.y, p4.y) &&
        MATH_MIN(p3.y, p4.y) <= MATH_MAX(p1.y, p2.y)) {
        /* Check whether the lines are parallel. If the lines are collinear, there is no intersection point. */
        if ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y) != 0) {
            /*
             * (y1 - y2)x + (x2 - x1)y = x2y1 - x1y2  ->  ax + by = c
             * (y3 - y4)x + (x4 - x3)y = x4y3 - x3y4  ->  dx + ey = f
             */
            int64_t a = p1.y - p2.y;
            int64_t b = p2.x - p1.x;
            int64_t c = p2.x * p1.y - p1.x * p2.y;
            int64_t d = p3.y - p4.y;
            int64_t e = p4.x - p3.x;
            int64_t f = p4.x * p3.y - p3.x * p4.y;
            int64_t left = a * e - b * d;
            int64_t right = c * e - b * f;
            if (left == 0) {
                return false;
            }
            cross.x = static_cast<int16_t>(right / left);
            left = b * d - a * e;
            right = c * d - a * f;
            if (left == 0) {
                return false;
            }
            cross.y = static_cast<int16_t>(right / left);
            if (cross.x >= MATH_MIN(p1.x, p2.x) && cross.x <= MATH_MAX(p1.x, p2.x) &&
                cross.x >= MATH_MIN(p3.x, p4.x) && cross.x <= MATH_MAX(p3.x, p4.x)) {
                return true;
            }
        }
    }
    return false;
}

void UIChartPolyline::FindCrossPoints(const ChartLine& line, const ChartLine& polyLine, CrossPointSet& cross)
{
    if (GetLineCrossPoint(line.start, line.end, polyLine.start, polyLine.end, cross.nextFirst)) {
        if (!cross.firstFind) {
            /* first corss must on the line like "/" */
            if (polyLine.start.y < polyLine.end.y) {
                cross.first = cross.nextFirst;
                cross.firstFind = true;
            }
        } else if (!cross.secondFind) {
            /* second corss can't be same with first cross. */
            if (cross.first.x != cross.nextFirst.x || cross.first.y != cross.nextFirst.y) {
                cross.second = cross.nextFirst;
                cross.secondFind = true;
            } else {
                /* second corss must on the line like "\", otherwise skip those crosss. */
                if (polyLine.start.y > polyLine.end.y) {
                    cross.firstFind = false;
                }
            }
        }
    }
}

void UIChartPolyline::DrawGradientColor(const Rect& invalidatedArea, UIChartDataSerial* data,
    const ChartLine& linePoints, const ChartLine& limitPoints, int16_t startY)
{
    if (data == nullptr) {
        return;
    }
    Rect currentRect = GetContentRect();
    CrossPointSet cross = { {0} };
    ChartLine polyLine = { {0} };
    uint16_t pointCount = data->GetDataCount() - 1;
    int16_t y = enableReverse_ ? (linePoints.start.y + startY) : (startY - linePoints.start.y);
    int16_t mixScale = !enableReverse_ ? (currentRect.GetBottom() - y) : (y - currentRect.GetTop());
    if (mixScale < 0 || mixScale >= currentRect.GetHeight()) {
        return;
    }
    bool onVerticalLine = enableReverse_ ? (y <= limitPoints.start.y) : (y >= limitPoints.start.y);
    if (onVerticalLine) {
        cross.first.x = limitPoints.start.x;
        cross.first.y = enableReverse_ ? (y - startY) : (startY - y);
        cross.firstFind = true;
    }

    Point start;
    Point end;
    for (uint16_t i = 0; i < pointCount; i++) {
        data->GetPoint(i, start);
        data->GetPoint(i + 1, end);
        if (start.y == end.y) {
            int16_t y = enableReverse_ ? (start.y + startY) : (startY - start.y);
            if (y == linePoints.start.y) {
                cross.firstFind = false;
                cross.secondFind = false;
            }
            continue;
        }
        start.y = enableReverse_ ? (start.y - startY) : (startY - start.y);
        end.y = enableReverse_ ? (end.y - startY) : (startY - end.y);
        polyLine.start = start;
        polyLine.end = end;
        FindCrossPoints(linePoints, polyLine, cross);
        if (cross.firstFind && cross.secondFind) {
            cross.first.y = enableReverse_ ? (cross.first.y + startY) : (startY - cross.first.y);
            cross.second.y = enableReverse_ ? (cross.second.y + startY) : (startY - cross.second.y);
            DrawLine::Draw(cross.first, cross.second, invalidatedArea, 1, data->GetFillColor(), mixData_[mixScale]);
            cross.firstFind = false;
            cross.secondFind = false;
        }
    }

    if (cross.firstFind && !cross.secondFind) {
        cross.second.x = limitPoints.end.x;
        cross.second.y = y;
        cross.first.y = y;
        DrawLine::Draw(cross.first, cross.second, invalidatedArea, 1, data->GetFillColor(), mixData_[mixScale]);
    }
}

void UIChartPolyline::CalcVerticalInfo(int16_t top, int16_t bottom, int16_t start, int16_t end,
    int16_t& y, int16_t& yHeight)
{
    if (top < start && bottom > start) {
        y = start;
        yHeight = top;
    } else if (bottom <= start && top >= end) {
        y = bottom;
        yHeight = top;
    } else if (top < end && bottom > end) {
        y = bottom;
        yHeight = end;
    }
}

void UIChartPolyline::GradientColor(const Rect& invalidatedArea, UIChartDataSerial* data)
{
    if (data == nullptr) {
        return;
    }
    int16_t bottom = invalidatedArea.GetBottom();
    int16_t top = invalidatedArea.GetTop();
    Point yStart = yAxis_.GetStartPoint();
    yStart.y = enableReverse_ ? (yStart.y + gradientBottom_) : (yStart.y - gradientBottom_);
    int16_t topY = enableReverse_ ? data->GetValleyData() : data->GetPeakData();
    int16_t bottomY = enableReverse_ ? data->GetPeakData() : data->GetValleyData();
    yAxis_.TranslateToPixel(topY);
    yAxis_.TranslateToPixel(bottomY);
    int16_t valleyY = enableReverse_ ? topY : bottomY;
    int16_t startY = enableReverse_ ? topY : yStart.y;
    int16_t endY = enableReverse_ ? yStart.y : topY;
    if (bottom < endY || top > startY) {
        return;
    }

    int16_t y = 0;
    int16_t yHeight = 0;
    CalcVerticalInfo(top, bottom, startY, endY, y, yHeight);

    ChartLine limitPoints = { {0} };
    data->GetPoint(0, limitPoints.start);
    data->GetPoint(data->GetDataCount() - 1, limitPoints.end);
    ChartLine linePoints = { {0} };
    linePoints.start.x = limitPoints.start.x;
    linePoints.end.x = limitPoints.end.x;
    Rect currentRect = GetContentRect();
    while (y >= yHeight) {
        linePoints.start.y = enableReverse_ ? (y - endY) : (startY - y);
        linePoints.end.y = linePoints.start.y;
        if (y <= valleyY) {
            int16_t baseY = enableReverse_ ? endY : startY;
            DrawGradientColor(invalidatedArea, data, linePoints, limitPoints, baseY);
        } else {
            int16_t mixScale = enableReverse_ ? (linePoints.start.y + endY - currentRect.GetTop()) :
                (currentRect.GetBottom() - (startY - linePoints.start.y));
            if (mixScale < 0 || mixScale >= currentRect.GetHeight()) {
                continue;
            }
            Point start = {limitPoints.start.x, y};
            Point end = {limitPoints.end.x, y};
            DrawLine::Draw(start, end, invalidatedArea, 1, data->GetFillColor(), mixData_[mixScale]);
        }
        y--;
    }
}
}