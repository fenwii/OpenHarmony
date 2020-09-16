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
 * @file ui_canvas.h
 *
 * @brief Defines the attributes of the canvas component and provides functions for drawing rectangles,
 *        circles, and others.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_CANVAS_H
#define GRAPHIC_LITE_UI_CANVAS_H

#include "common/image.h"
#include "components/ui_label.h"
#include "list.h"

namespace OHOS {
/**
 * @brief Defines the basic styles of graphs drawn on canvases.
 *
 * @since 1.0
 * @version 1.0
 */
class Paint : public HeapBase {
public:
    /**
     * @brief A constructor used to create a <b>Paint</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    Paint()
        : style_(PaintStyle::STROKE_FILL_STYLE), fillColor_(Color::Black()),
          strokeColor_(Color::White()), opacity_(OPA_OPAQUE), strokeWidth_(2) {}

    /**
     * @brief A destructor used to delete the <b>Paint</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~Paint() {}

    /**
     * @brief Enumerates paint styles of a closed graph. The styles are invalid for non-closed graphs.
     */
    enum PaintStyle {
        /** Stroke only */
        STROKE_STYLE = 1,
        /** Fill only */
        FILL_STYLE,
        /** Stroke and fill */
        STROKE_FILL_STYLE,
    };

    /**
     * @brief Sets the paint style of a closed graph.
     *
     * @param style Indicates the paint style. Stroke and fill are set by default. For details, see {@link PaintStyle}.
     * @see GetStyle
     * @since 1.0
     * @version 1.0
     */
    void SetStyle(PaintStyle style)
    {
        style_ = style;
    }

    /**
     * @brief Obtains the paint style of a closed graph.
     *
     * @return Returns the paint style. For details, see {@link PaintStyle}.
     * @see SetStyle
     * @since 1.0
     * @version 1.0
     */
    PaintStyle GetStyle() const
    {
        return style_;
    }

    /**
     * @brief Sets the width of a line or border.
     *
     * @param width Indicates the line width when a line is drawn or the border width when a closed graph is drawn.
     *        The width is extended to both sides.
     * @see GetStrokeWidth
     * @since 1.0
     * @version 1.0
     */
    void SetStrokeWidth(uint16_t width)
    {
        strokeWidth_ = width;
    }

    /**
     * @brief Obtains the width of a line or border.
     *
     * @return Returns the line width if a line is drawn or the border width if a closed graph is drawn.
     * @see SetStrokeWidth
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetStrokeWidth() const
    {
        return strokeWidth_;
    }

    /**
     * @brief Sets the color of a line or border.
     *
     * @param color Indicates the line color when a line is drawn or the border color when a closed graph is drawn.
     * @see GetStrokeColor
     * @since 1.0
     * @version 1.0
     */
    void SetStrokeColor(ColorType color)
    {
        strokeColor_ = color;
    }

    /**
     * @brief Obtains the color of a line or border.
     *
     * @return Returns the line color if a line is drawn or the border color if a closed graph is drawn.
     * @see SetStrokeWidth
     * @since 1.0
     * @version 1.0
     */
    ColorType GetStrokeColor() const
    {
        return strokeColor_;
    }

    /**
     * @brief Sets fill color.
     *
     * This function is valid only for closed graphs.
     *
     * @param color Indicates the fill color to set.
     * @see GetFillColor
     * @since 1.0
     * @version 1.0
     */
    void SetFillColor(ColorType color)
    {
        fillColor_ = color;
    }

    /**
     * @brief Obtains the fill color.
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
     * @brief Sets the opacity.
     *
     * The setting takes effect for the entire graph, including the border, line color, and fill color.
     *
     * @param opacity Indicates the opacity. The value range is [0, 255].
     * @see GetOpacity
     * @since 1.0
     * @version 1.0
     */
    void SetOpacity(uint8_t opacity)
    {
        opacity_ = opacity;
    }

    /**
     * @brief Obtains the opacity.
     *
     * @return Returns the opacity.
     * @see SetOpacity
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetOpacity() const
    {
        return opacity_;
    }

private:
    PaintStyle style_;
    ColorType fillColor_;
    ColorType strokeColor_;
    uint8_t opacity_;
    uint16_t strokeWidth_;
};

/**
 * @brief Defines a canvas, which is used to draw multiple types of 2D graphs.
 *
 * @since 1.0
 * @version 1.0
 */
class UICanvas : public UIView {
public:
    /**
     * @brief A constructor used to create a <b>UICanvas</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UICanvas() : startPoint_({ 0, 0 }) {}

    /**
     * @brief A destructor used to delete the <b>UICanvas</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UICanvas();

    /**
     * @brief Obtains the view type.
     *
     * @return Returns the view type. For details, see {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_CANVAS;
    }

    /**
     * @brief Clears the entire canvas.
     *
     * @since 1.0
     * @version 1.0
     */
    void Clear();

    /**
     * @brief Sets the coordinates of the start point for drawing a line. For example, if <b>startPoint</b> is
     *        set to {50, 50}, the line is drawn from this set of coordinates on the canvas.
     *
     * @param startPoint Indicates the coordinates of the start point.
     * @see GetStartPosition
     * @since 1.0
     * @version 1.0
     */
    void SetStartPosition(const Point& startPoint)
    {
        startPoint_ = startPoint;
    }

    /**
     * @brief Obtains the coordinates of the start point of a line.
     *
     * @return Returns the coordinates of the start point.
     * @see SetStartPosition
     * @since 1.0
     * @version 1.0
     */
    const Point& GetStartPosition() const
    {
        return startPoint_;
    }

    /**
     * @brief Draws a straight line.
     *
     * If {@link SetStartPosition} is not used to set the coordinates of the start point of the line, the drawing
     * starts from the end point of the last line.
     *
     * @param endPoint Indicates the end point of the straight line.
     * @param paint    Indicates the straight line style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawLine(const Point& endPoint, const Paint& paint);

    /**
     * @brief Draws a straight line from the coordinates of the start point.
     *
     * @param startPoint Indicates the coordinates of the start point.
     * @param endPoint   Indicates the coordinates of the end point.
     * @param paint      Indicates the straight line style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawLine(const Point& startPoint, const Point& endPoint, const Paint& paint);

    /**
     * @brief Draws a cubic Bezier curve.
     *
     * If {@link SetStartPosition} is not used to set the coordinates of the start point of the curve,
     * the drawing starts from the end point of the last line.
     * Currently, the opacity cannot be set, and the maximum line width is <b>3</b>.
     *
     * @param control1 Indicates the coordinates of the first control point of the cubic Bezier curve.
     * @param control2 Indicates the coordinates of the second control point of the cubic Bezier curve.
     * @param endPoint Indicates the coordinates of the end point of the cubic Bezier curve.
     * @param paint    Indicates the curve style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawCurve(const Point& control1, const Point& control2, const Point& endPoint, const Paint& paint);

    /**
     * @brief Draws a cubic Bezier curve from the start point coordinates.
     *
     * Currently, the opacity cannot be set, and the maximum line width is <b>3</b>.
     *
     * @param startPoint Indicates the coordinates of the start point of the cubic Bezier curve.
     * @param control1   Indicates the coordinates of the first control point of the cubic Bezier curve.
     * @param control2   Indicates the coordinates of the second control point of the cubic Bezier curve.
     * @param endPoint   Indicates the coordinates of the end point of the cubic Bezier curve.
     * @param paint      Indicates the curve style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawCurve(const Point& startPoint, const Point& control1, const Point& control2,
        const Point& endPoint, const Paint& paint);

    /**
     * @brief Draws a rectangle.
     *
     * @param startPoint Indicates the coordinates of the point at the upper left corner of the rectangle.
     * @param height     Indicates the height of the rectangle.
     * @param width      Indicates the width of the rectangle.
     * @param paint      Indicates the rectangle style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawRect(const Point& startPoint, int16_t height, int16_t width, const Paint& paint);

    /**
     * @brief Draws a circle.
     *
     * @param center Indicates the coordinates of the circle center.
     * @param radius Indicates the radius of the circle.
     * @param paint  Indicates the circle style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawCircle(const Point& center, uint16_t radius, const Paint& paint);

    /**
     * @brief Draws a sector.
     *
     * When the start angle is smaller than the end angle, the sector is drawn clockwise.
     * Otherwise, the sector is drawn counterclockwise.
     *
     * @param center     Indicates the coordinates of the sector's center.
     * @param radius     Indicates the radius of the sector.
     * @param startAngle Indicates the start angle of the sector. Value <b>0</b> indicates the 12-o'clock direction,
     *                   and <b>90</b> indicates the 3-o'clock direction.
     * @param endAngle   Indicates the end angle of the sector. Value <b>0</b> indicates the 12-o'clock direction,
     *                   and <b>90</b> indicates the 3-o'clock direction.
     * @param paint      Indicates the sector style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawSector(const Point& center, uint16_t radius, int16_t startAngle, int16_t endAngle, const Paint& paint);

    /**
     * @brief Draws an arc.
     *
     * Only stroke is supported. \n
     * When the start angle is smaller than the end angle, the sector is drawn clockwise.
     * Otherwise, the sector is drawn counterclockwise. \n
     *
     * @param center     Indicates the coordinates of the arc's center.
     * @param radius     Indicates the radius of the arc.
     * @param startAngle Indicates the start angle of the arc. Value <b>0</b> indicates the 12-o'clock direction,
     *                   and <b>90</b> indicates the 3-o'clock direction.
     * @param endAngle   Indicates the end angle of the arc. Value <b>0</b> indicates the 12-o'clock direction,
     *                   and <b>90</b> indicates the 3-o'clock direction.
     * @param paint      Indicates the arc style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawArc(const Point& center, uint16_t radius, int16_t startAngle, int16_t endAngle, const Paint& paint);

    /**
     * @brief Draws an image.
     *
     * @param startPoint Indicates the coordinates of the start point.
     * @param image      Indicates the pointer to the image source.
     * @param paint      Indicates the image style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawImage(const Point& startPoint, const char* image, const Paint& paint);

    /**
     * @brief Defines the font style.
     */
    struct FontStyle {
        /** Text direction. For details, see {@link UITextLanguageDirect}. */
        UITextLanguageDirect direct;
        /** Text alignment mode. For details, see {@link UITextLanguageAlignment}. */
        UITextLanguageAlignment align;
        /** Font size */
        uint8_t fontSize;
        /** Letter-spacing */
        int16_t letterSpace;
        /** Font name */
        const char* fontName;
    };

    /**
     * @brief Draws text.
     *
     * Only fill is supported. \n
     * If the text length exceeds the value of <b>maxWidth</b>, the text will be truncated. \n
     *
     * @param startPoint Indicates the coordinates of the start point.
     * @param text       Indicates the pointer to the text content.
     * @param maxWidth   Indicates the maximum width of the text that can be displayed. If the maximum width is
     *                   exceeded, the text is truncated.
     * @param fontStyle  Indicates the text layout and font style. For details, see {@link FontStyle}.
     * @param paint      Indicates the text style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawLabel(const Point& startPoint, const char* text, uint16_t maxWidth, const FontStyle& fontStyle,
        const Paint& paint);

    virtual void OnDraw(const Rect& invalidatedArea) override;

protected:
    Point startPoint_;

private:
    constexpr static uint8_t MAX_CURVE_WIDTH = 3;

    struct LineParam : public HeapBase {
        Point start;
        Point end;
        Paint paint;
    };

    struct CurveParam : public HeapBase {
        Point start;
        Point control1;
        Point control2;
        Point end;
        Paint paint;
    };

    struct RectParam : public HeapBase {
        Point start;
        int16_t height;
        int16_t width;
        Paint paint;
    };

    struct CircleParam : public HeapBase {
        Point center;
        uint16_t radius;
        Paint paint;
    };

    struct ArcParam : public HeapBase {
        Point center;
        uint16_t radius;
        int16_t startAngle;
        int16_t endAngle;
        Paint paint;
    };

    struct ImageParam : public HeapBase {
        Point start;
        uint16_t height;
        uint16_t width;
        Image* image;
        Paint paint;
    };

    struct DrawCmd : public HeapBase {
        void* param;
        void(*DrawGraphics)(void*, const Rect&, const Rect&, const Style&);
        void(*DeleteParam)(void *);
    };

    List<DrawCmd> drawCmdList_;

    static void DeleteLineParam(void* param)
    {
        LineParam* lineParam = static_cast<LineParam*>(param);
        delete lineParam;
    }

    static void DeleteCurveParam(void* param)
    {
        CurveParam* curveParam = static_cast<CurveParam*>(param);
        delete curveParam;
    }

    static void DeleteRectParam(void* param)
    {
        RectParam* rectParam = static_cast<RectParam*>(param);
        delete rectParam;
    }

    static void DeleteCircleParam(void* param)
    {
        CircleParam* circleParam = static_cast<CircleParam*>(param);
        delete circleParam;
    }

    static void DeleteArcParam(void* param)
    {
        ArcParam* arcParam = static_cast<ArcParam*>(param);
        delete arcParam;
    }

    static void DeleteImageParam(void* param)
    {
        ImageParam* imageParam = static_cast<ImageParam*>(param);
        if (imageParam->image != nullptr) {
            delete imageParam->image;
        }
        delete imageParam;
    }

    static void DeleteLabel(void* param)
    {
        UILabel* label = static_cast<UILabel*>(param);
        delete label;
    }

    static void DoDrawLine(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style);
    static void DoDrawCurve(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style);
    static void DoDrawRect(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style);
    static void DoFillRect(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style);
    static void DoDrawCircle(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style);
    static void DoDrawArc(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style);
    static void DoDrawImage(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style);
    static void DoDrawLabel(void* param, const Rect& rect, const Rect& invalidatedArea, const Style& style);
    static void GetAbsolutePosition(Point& point, const Point& prePoint, const Rect& rect, const Style& style);
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_CANVAS_H
