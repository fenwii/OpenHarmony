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

#include "common/image.h"
#include "components/ui_canvas.h"
#include "draw/draw_arc.h"
#include "draw/draw_curve.h"
#include "draw/draw_image.h"
#include "draw/draw_line.h"
#include "draw/draw_rect.h"

namespace OHOS {
UICanvas::~UICanvas()
{
    void* param = nullptr;
    ListNode<DrawCmd>* curDraw = drawCmdList_.Begin();
    for (; curDraw != drawCmdList_.End(); curDraw = curDraw->next_) {
        param = curDraw->data_.param;
        curDraw->data_.DeleteParam(param);
        curDraw->data_.param = nullptr;
    }
    drawCmdList_.Clear();
}

void UICanvas::Clear()
{
    void* param = nullptr;
    ListNode<DrawCmd>* curDraw = drawCmdList_.Begin();
    for (; curDraw != drawCmdList_.End(); curDraw = curDraw->next_) {
        param = curDraw->data_.param;
        curDraw->data_.DeleteParam(param);
        curDraw->data_.param = nullptr;
    }
    drawCmdList_.Clear();
    Invalidate();
}

void UICanvas::DrawLine(const Point& endPoint, const Paint& paint)
{
    DrawLine(startPoint_, endPoint, paint);
}

void UICanvas::DrawLine(const Point& startPoint, const Point& endPoint, const Paint& paint)
{
    LineParam* lineParam = new LineParam;
    lineParam->start = startPoint;
    lineParam->end = endPoint;
    lineParam->paint = paint;

    DrawCmd cmd;
    cmd.param = lineParam;
    cmd.DeleteParam = DeleteLineParam;
    cmd.DrawGraphics = DoDrawLine;
    drawCmdList_.PushBack(cmd);

    Invalidate();
    SetStartPosition(endPoint);
}

void UICanvas::DrawCurve(const Point& control1, const Point& control2, const Point& endPoint, const Paint& paint)
{
    DrawCurve(startPoint_, control1, control2, endPoint, paint);
}

void UICanvas::DrawCurve(const Point& startPoint, const Point& control1, const Point& control2,
    const Point& endPoint, const Paint& paint)
{
    CurveParam* curveParam = new CurveParam;
    curveParam->start = startPoint;
    curveParam->control1 = control1;
    curveParam->control2 = control2;
    curveParam->end = endPoint;
    curveParam->paint = paint;

    if (paint.GetStrokeWidth() > MAX_CURVE_WIDTH) {
        curveParam->paint.SetStrokeWidth(MAX_CURVE_WIDTH);
    }

    DrawCmd cmd;
    cmd.param = curveParam;
    cmd.DeleteParam = DeleteCurveParam;
    cmd.DrawGraphics = DoDrawCurve;
    drawCmdList_.PushBack(cmd);

    Invalidate();
    SetStartPosition(endPoint);
}

void UICanvas::DrawRect(const Point& startPoint, int16_t height, int16_t width, const Paint& paint)
{
    if (static_cast<uint8_t>(paint.GetStyle()) & Paint::PaintStyle::STROKE_STYLE) {
        RectParam* rectParam = new RectParam;
        rectParam->start = startPoint;
        rectParam->height = height;
        rectParam->width = width;
        rectParam->paint = paint;

        DrawCmd cmd;
        cmd.param = rectParam;
        cmd.DeleteParam = DeleteRectParam;
        cmd.DrawGraphics = DoDrawRect;
        drawCmdList_.PushBack(cmd);
    }

    if (static_cast<uint8_t>(paint.GetStyle()) & Paint::PaintStyle::FILL_STYLE) {
        RectParam* rectParam = new RectParam;
        rectParam->start = startPoint;
        rectParam->height = height;
        rectParam->width = width;
        rectParam->paint = paint;

        DrawCmd cmd;
        cmd.param = rectParam;
        cmd.DeleteParam = DeleteRectParam;
        cmd.DrawGraphics = DoFillRect;
        drawCmdList_.PushBack(cmd);
    }

    Invalidate();
}

void UICanvas::DrawCircle(const Point& center, uint16_t radius, const Paint& paint)
{
    CircleParam* circleParam = new CircleParam;
    circleParam->center = center;
    circleParam->radius = radius;
    circleParam->paint = paint;

    DrawCmd cmd;
    cmd.param = circleParam;
    cmd.DeleteParam = DeleteCircleParam;
    cmd.DrawGraphics = DoDrawCircle;
    drawCmdList_.PushBack(cmd);

    Invalidate();
}

void UICanvas::DrawSector(const Point& center, uint16_t radius, int16_t startAngle, int16_t endAngle,
    const Paint& paint)
{
    if (static_cast<uint8_t>(paint.GetStyle()) & Paint::PaintStyle::FILL_STYLE) {
        Paint innerPaint = paint;
        innerPaint.SetStyle(Paint::PaintStyle::STROKE_STYLE);
        innerPaint.SetStrokeWidth(radius);
        innerPaint.SetStrokeColor(paint.GetFillColor());
        radius >>= 1;
        DrawArc(center, radius, startAngle, endAngle, innerPaint);
    }
}

void UICanvas::DrawArc(const Point& center, uint16_t radius, int16_t startAngle, int16_t endAngle, const Paint& paint)
{
    if (static_cast<uint8_t>(paint.GetStyle()) & Paint::PaintStyle::STROKE_STYLE) {
        ArcParam* arcParam = new ArcParam;
        arcParam->center = center;
        arcParam->radius = radius;

        int16_t start;
        int16_t end;
        if (startAngle > endAngle) {
            start = endAngle;
            end = startAngle;
        } else {
            start = startAngle;
            end = endAngle;
        }

        DrawArc::GetInstance()->GetDrawRange(start, end);
        arcParam->startAngle = start;
        arcParam->endAngle = end;
        arcParam->paint = paint;

        DrawCmd cmd;
        cmd.param = arcParam;
        cmd.DeleteParam = DeleteArcParam;
        cmd.DrawGraphics = DoDrawArc;
        drawCmdList_.PushBack(cmd);

        Invalidate();
    }
}

void UICanvas::DrawLabel(const Point& startPoint, const char* text, uint16_t maxWidth,
    const FontStyle& fontStyle, const Paint& paint)
{
    if (text == nullptr) {
        return;
    }
    if (static_cast<uint8_t>(paint.GetStyle()) & Paint::PaintStyle::FILL_STYLE) {
        UILabel *label = new UILabel();
        label->SetLineBreakMode(UILabel::LINE_BREAK_CLIP);
        label->SetPosition(startPoint.x, startPoint.y);
        label->SetWidth(maxWidth);
        label->SetHeight(GetHeight());
        label->SetText(text);
        label->SetFont(fontStyle.fontName, fontStyle.fontSize);
        label->SetAlign(fontStyle.align);
        label->SetDirect(fontStyle.direct);
        label->SetStyle(STYLE_LETTER_SPACE, fontStyle.letterSpace);
        label->SetStyle(STYLE_TEXT_COLOR, paint.GetFillColor().full);
        label->SetStyle(STYLE_TEXT_OPA, paint.GetOpacity());

        DrawCmd cmd;
        cmd.param = label;
        cmd.DeleteParam = DeleteLabel;
        cmd.DrawGraphics = DoDrawLabel;
        drawCmdList_.PushBack(cmd);

        Invalidate();
    }
}

void UICanvas::DrawImage(const Point& startPoint, const char* image, const Paint& paint)
{
    if (image == nullptr) {
        return;
    }

    ImageParam* imageParam = new ImageParam;
    imageParam->image = nullptr;
    imageParam->image = new Image();
    if (imageParam->image == nullptr) {
        return;
    }

    imageParam->image->SetSrc(image);
    ImageHeader header = { 0 };
    imageParam->image->GetHeader(header);
    imageParam->start = startPoint;
    imageParam->height = header.height;
    imageParam->width = header.width;

    imageParam->paint = paint;

    DrawCmd cmd;
    cmd.param = imageParam;
    cmd.DeleteParam = DeleteImageParam;
    cmd.DrawGraphics = DoDrawImage;
    drawCmdList_.PushBack(cmd);

    Invalidate();
}

void UICanvas::OnDraw(const Rect& invalidatedArea)
{
    Rect rect = GetRect();
    DrawRect::Draw(rect, invalidatedArea, *style_);
    void* param = nullptr;
    ListNode<DrawCmd>* curDraw = drawCmdList_.Begin();
    Rect coords = GetContentRect();
    Rect trunc = invalidatedArea;
    if (trunc.Intersect(trunc, coords)) {
        for (; curDraw != drawCmdList_.End(); curDraw = curDraw->next_) {
            param = curDraw->data_.param;
            curDraw->data_.DrawGraphics(param, rect, trunc, *style_);
        }
    }
}

void UICanvas::GetAbsolutePosition(Point& point, const Point& prePoint, const Rect& rect, const Style& style)
{
    point.x = prePoint.x + rect.GetLeft() + style.paddingLeft_ + style.borderWidth_;
    point.y = prePoint.y + rect.GetTop() + style.paddingTop_ + style.borderWidth_;
}

void UICanvas::DoDrawLine(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style)
{
    if (param == nullptr) {
        return;
    }
    LineParam* lineParam = static_cast<LineParam*>(param);
    Point start;
    Point end;
    GetAbsolutePosition(start, lineParam->start, rect, style);
    GetAbsolutePosition(end, lineParam->end, rect, style);

    DrawLine::Draw(start, end, invalidatedArea, lineParam->paint.GetStrokeWidth(),
        lineParam->paint.GetStrokeColor(), lineParam->paint.GetOpacity());
}

void UICanvas::DoDrawCurve(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style)
{
    if (param == nullptr) {
        return;
    }
    CurveParam* curveParam = static_cast<CurveParam*>(param);
    Point start;
    Point end;
    Point control1;
    Point control2;
    GetAbsolutePosition(start, curveParam->start, rect, style);
    GetAbsolutePosition(end, curveParam->end, rect, style);
    GetAbsolutePosition(control1, curveParam->control1, rect, style);
    GetAbsolutePosition(control2, curveParam->control2, rect, style);

    DrawCurve::DrawCubicBezier(start, control1, control2, end, invalidatedArea, curveParam->paint.GetStrokeWidth(),
        curveParam->paint.GetStrokeColor(), curveParam->paint.GetOpacity());
}

void UICanvas::DoDrawRect(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style)
{
    if (param == nullptr) {
        return;
    }
    RectParam* rectParam = static_cast<RectParam*>(param);
    Style drawStyle = StyleDefault::GetDefaultStyle();
    drawStyle.bgColor_ = rectParam->paint.GetStrokeColor();
    drawStyle.bgOpa_ = rectParam->paint.GetOpacity();
    drawStyle.borderRadius_ = 0;

    int16_t lineWidth = rectParam->paint.GetStrokeWidth();
    Point start;
    GetAbsolutePosition(start, rectParam->start, rect, style);

    int16_t x = start.x - lineWidth / 2; // 2: half
    int16_t y = start.y - lineWidth / 2; // 2: half
    Rect coords;
    if (rectParam->height <= lineWidth || rectParam->width <= lineWidth) {
        coords.SetPosition(x, y);
        coords.SetHeight(rectParam->height + lineWidth);
        coords.SetWidth(rectParam->width + lineWidth);
        DrawRect::Draw(coords, invalidatedArea, drawStyle);
        return;
    }

    coords.SetPosition(x, y);
    coords.SetHeight(lineWidth);
    coords.SetWidth(rectParam->width);
    DrawRect::Draw(coords, invalidatedArea, drawStyle);

    coords.SetPosition(x + rectParam->width, y);
    coords.SetHeight(rectParam->height);
    coords.SetWidth(lineWidth);
    DrawRect::Draw(coords, invalidatedArea, drawStyle);

    coords.SetPosition(x, y + lineWidth);
    coords.SetHeight(rectParam->height);
    coords.SetWidth(lineWidth);
    DrawRect::Draw(coords, invalidatedArea, drawStyle);

    coords.SetPosition(x + lineWidth, y + rectParam->height);
    coords.SetHeight(lineWidth);
    coords.SetWidth(rectParam->width);
    DrawRect::Draw(coords, invalidatedArea, drawStyle);
}

void UICanvas::DoFillRect(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style)
{
    if (param == nullptr) {
        return;
    }
    RectParam* rectParam = static_cast<RectParam*>(param);
    uint8_t enableStroke = static_cast<uint8_t>(rectParam->paint.GetStyle()) & Paint::PaintStyle::STROKE_STYLE;
    int16_t lineWidth = enableStroke ? rectParam->paint.GetStrokeWidth() : 0;
    if (rectParam->height <= lineWidth || rectParam->width <= lineWidth) {
        return;
    }
    Point start;
    GetAbsolutePosition(start, rectParam->start, rect, style);

    Rect coords;
    coords.SetPosition(start.x + (lineWidth + 1) / 2, start.y + (lineWidth + 1) / 2); // 2: half
    coords.SetHeight(rectParam->height - lineWidth);
    coords.SetWidth(rectParam->width - lineWidth);

    Style drawStyle = StyleDefault::GetDefaultStyle();
    drawStyle.bgColor_ = rectParam->paint.GetFillColor();
    drawStyle.bgOpa_ = rectParam->paint.GetOpacity();
    drawStyle.borderRadius_ = 0;
    DrawRect::Draw(coords, invalidatedArea, drawStyle);
}

void UICanvas::DoDrawCircle(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style)
{
    if (param == nullptr) {
        return;
    }
    CircleParam* circleParam = static_cast<CircleParam*>(param);

    Style drawStyle = StyleDefault::GetDefaultStyle();
    drawStyle.lineOpa_ = circleParam->paint.GetOpacity();

    ArcInfo arcInfo = {{0}};
    arcInfo.imgPos = Point{0, 0};
    arcInfo.startAngle = 0;
    arcInfo.endAngle = CIRCLE_IN_DEGREE;
    GetAbsolutePosition(arcInfo.center, circleParam->center, rect, style);
    uint8_t enableStroke = static_cast<uint8_t>(circleParam->paint.GetStyle()) & Paint::PaintStyle::STROKE_STYLE;
    uint16_t halfLineWidth = enableStroke ? (circleParam->paint.GetStrokeWidth() >> 1) : 0;
    if (static_cast<uint8_t>(circleParam->paint.GetStyle()) & Paint::PaintStyle::FILL_STYLE) {
        arcInfo.radius = circleParam->radius - halfLineWidth;
        drawStyle.lineWidth_ = arcInfo.radius;
        drawStyle.lineColor_ = circleParam->paint.GetFillColor();
        DrawArc::GetInstance()->Draw(arcInfo, invalidatedArea, drawStyle, OPA_OPAQUE, CapType::CAP_NONE);
    }

    if (enableStroke) {
        arcInfo.radius = circleParam->radius + halfLineWidth - 1;
        drawStyle.lineWidth_ = circleParam->paint.GetStrokeWidth();
        drawStyle.lineColor_ = circleParam->paint.GetStrokeColor();
        DrawArc::GetInstance()->Draw(arcInfo, invalidatedArea, drawStyle, OPA_OPAQUE, CapType::CAP_NONE);
    }
}

void UICanvas::DoDrawArc(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style)
{
    if (param == nullptr) {
        return;
    }
    ArcParam* arcParam = static_cast<ArcParam*>(param);

    ArcInfo arcInfo = {{0}};
    arcInfo.imgPos = Point{0, 0};
    arcInfo.startAngle = arcParam->startAngle;
    arcInfo.endAngle = arcParam->endAngle;
    Style drawStyle = StyleDefault::GetDefaultStyle();
    drawStyle.lineWidth_ = arcParam->paint.GetStrokeWidth();
    drawStyle.lineColor_ = arcParam->paint.GetStrokeColor();
    drawStyle.lineOpa_ = arcParam->paint.GetOpacity();
    arcInfo.radius = arcParam->radius + ((arcParam->paint.GetStrokeWidth() + 1) >> 1);

    GetAbsolutePosition(arcInfo.center, arcParam->center, rect, style);
    DrawArc::GetInstance()->Draw(arcInfo, invalidatedArea, drawStyle, OPA_OPAQUE, CapType::CAP_NONE);
}

void UICanvas::DoDrawImage(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style)
{
    if (param == nullptr) {
        return;
    }
    ImageParam* imageParam = static_cast<ImageParam*>(param);

    Point start;
    GetAbsolutePosition(start, imageParam->start, rect, style);

    Rect cordsTmp;
    cordsTmp.SetPosition(start.x, start.y);
    cordsTmp.SetHeight(imageParam->height);
    cordsTmp.SetWidth(imageParam->width);
    DrawImage::DrawCommon(cordsTmp, invalidatedArea, imageParam->image->GetPath(), style,
        imageParam->paint.GetOpacity());
}

void UICanvas::DoDrawLabel(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style)
{
    if (param == nullptr) {
        return;
    }
    UILabel* label = static_cast<UILabel*>(param);
    Point startPos = { label->GetX(), label->GetY() };
    Point start;
    GetAbsolutePosition(start, { startPos.x, startPos.y }, rect, style);
    label->SetPosition(start.x, start.y);
    label->OnDraw(invalidatedArea);
    label->SetPosition(startPos.x, startPos.y);
}
} // namespace OHOS