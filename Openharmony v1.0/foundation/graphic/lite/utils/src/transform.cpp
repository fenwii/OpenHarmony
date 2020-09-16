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

#include "transform.h"
#include "graphic_math.h"
namespace OHOS {
constexpr uint8_t VERTEX_NUM_MIN = 3;

TransformMap::TransformMap() :  rect_ { 0, 0, 0, 0 }, polygon_(Rect(0, 0, 0, 0)), pivot_ { 0, 0 }
{
    /* 256 : scale is 1 and converted by using 'FloatToLong' is 256 */
    scale_ = Matrix3<int64_t>::Scale(Vector2<int64_t>(256, 256), Vector2<int64_t>(0, 0));
    rotate_ = Matrix3<int64_t>::Rotate(0, Vector2<int64_t>(0, 0));
    translate_ = Matrix3<int64_t>::Translate(Vector2<int64_t>(0, 0));
}

TransformMap::TransformMap(const Rect& rect) : pivot_{ 0, 0 }
{
    /* 256 : scale is 1 and converted by using 'FloatToLong' is 256 */
    scale_ = Matrix3<int64_t>::Scale(Vector2<int64_t>(256, 256), Vector2<int64_t>(0, 0));
    rotate_ = Matrix3<int64_t>::Rotate(0, Vector2<int64_t>(0, 0));
    translate_ = Matrix3<int64_t>::Translate(Vector2<int64_t>(0, 0));
    rect_ = rect;
    polygon_ = rect;
}

bool TransformMap::GetClockWise() const
{
    int16_t count = 0;
    int32_t c;

    uint8_t vertexNum = polygon_.GetVertexNum();
    if (vertexNum < VERTEX_NUM_MIN) {
        return false;
    }

    uint8_t i = 0;
    uint8_t j;
    uint8_t k;
    for (; i < vertexNum; i++) {
        j = (i + 1) % vertexNum;  // 1: the next vertex
        k = (i + 2) % vertexNum;  // 2: the after next vertex
        c = (static_cast<int32_t>(polygon_[j].x_ - polygon_[i].x_) *
            (polygon_[k].y_ - polygon_[j].y_)) -
            (static_cast<int32_t>(polygon_[j].y_ - polygon_[i].y_) *
            (polygon_[k].x_ - polygon_[j].x_));
        if (c < 0) {
            count--;
        } else if (c > 0) {
            count++;
        }
    }
    if (count > 0) {
        return true;
    }
    return false;
}

void TransformMap::Scale(const Vector2<float> scale, const Vector2<int16_t>& pivot)
{
    pivot_ = { pivot.x_, pivot.y_ };
    Vector2<int64_t> intScale;
    if (scale.x_ == 0 || scale.y_ == 0) {
        return;
    }
    intScale.x_ = FloatToInt64(1.0f / scale.x_);  // int64_t = float * 2^8
    intScale.y_ = FloatToInt64(1.0f / scale.y_);

    Vector2<int64_t> offset(rect_.GetX(), rect_.GetY());
    Vector2<int64_t> relativeOrigPivot(pivot.x_ + offset.x_, pivot.y_ + offset.y_);
    scale_ = Matrix3<int64_t>::Scale(intScale, relativeOrigPivot);
    translate_ = Matrix3<int64_t>::Translate(-offset);

    Vector2<int64_t> intInvScale;
    intInvScale.x_ = FloatToInt64(scale.x_);
    intInvScale.y_ = FloatToInt64(scale.y_);

    Matrix3<int64_t> invScale = Matrix3<int64_t>::Scale(intInvScale, relativeOrigPivot);
    uint8_t vertexNum = polygon_.GetVertexNum();
    Vector3<int64_t> imgPoint3;
    for (uint8_t i = 0; i < vertexNum; i++) {
        Vector3<int64_t> point(polygon_[i].x_, polygon_[i].y_, 1);
        imgPoint3 = invScale * point;
        // 128 : to correct the data due to the loss of right shift. 8: result of the Scale should right shift 8 bit
        polygon_[i].x_ = (imgPoint3.x_ + 128) >> 8;
        // 128 : to correct the data due to the loss of right shift. 8: result of the Scale should right shift 8 bit
        polygon_[i].y_ = (imgPoint3.y_ + 128) >> 8;
    }
}

void TransformMap::Rotate(int16_t angle, const Vector2<int16_t>& pivot)
{
    pivot_ = { pivot.x_, pivot.y_ };
    Vector2<int16_t> offset = Vector2<int16_t>(rect_.GetX(), rect_.GetY());
    Vector2<int16_t> relativeOrigPivot = pivot + offset;
    uint8_t vertexNum = polygon_.GetVertexNum();
    for (uint8_t i = 0; i < vertexNum; i++) {
        OHOS::Rotate(Vector2<int16_t>(polygon_[i].x_, polygon_[i].y_), angle, relativeOrigPivot, polygon_[i]);
    }

    rotate_ = Matrix3<int64_t>::Rotate(-angle, Vector2<int64_t>(relativeOrigPivot.x_, relativeOrigPivot.y_));
    translate_ = Matrix3<int64_t>::Translate(-Vector2<int64_t>(offset.x_, offset.y_));
}

void Rotate(const Vector2<int16_t>& point, int16_t angle, const Vector2<int16_t>& pivot, Vector2<int16_t>& out)
{
    float sinma = Sin(angle);
    float cosma = Sin(angle + 90); // 90: cos

    int16_t xt = point.x_ - pivot.x_;
    int16_t yt = point.y_ - pivot.y_;

    /* 0.5: round up */
    float temp = cosma * xt - sinma * yt;
    out.x_ = static_cast<int16_t>((temp > 0) ? (temp + 0.5f) : (temp - 0.5f)) + pivot.x_;
    temp = sinma * xt + cosma * yt;
    out.y_ = static_cast<int16_t>((temp > 0) ? (temp + 0.5f) : (temp - 0.5f)) + pivot.y_;
}

void Rotate(const Line& origLine, int16_t angle, const Vector2<int16_t>& pivot, Line& out)
{
    Vector2<int16_t> pt1 = origLine[0];
    Vector2<int16_t> pt2 = origLine[1];

    Rotate(pt1, angle, pivot, out[1]); // 1: the first point of line
    Rotate(pt2, angle, pivot, out[2]); // 2: the second point of line
}

void Rotate(const Rect& origRect, int16_t angle, const Vector2<int16_t>& pivot, Polygon& out)
{
    Vector2<int16_t> pt1 = { origRect.GetLeft(), origRect.GetTop() };
    Vector2<int16_t> pt2 = { origRect.GetRight(), origRect.GetTop() };
    Vector2<int16_t> pt3 = { origRect.GetRight(), origRect.GetBottom() };
    Vector2<int16_t> pt4 = { origRect.GetLeft(), origRect.GetBottom() };

    Rotate(pt1, angle, pivot, out[1]); // 1: the first point
    Rotate(pt2, angle, pivot, out[2]); // 2: the second point
    Rotate(pt3, angle, pivot, out[3]); // 3: the third point
    Rotate(pt4, angle, pivot, out[4]); // 4: the fourth point

    out.SetVertexNum(4);  // 4: number of vertex
}
}