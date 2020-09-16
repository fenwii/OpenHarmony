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
 * @file graphic_math.h
 *
 * @brief Defines mathematical operation functions and types, including trigonometric functions, two-dimensional
 *        vectors, three-dimensional vectors, and matrices.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_GRAPHIC_MATH_H
#define GRAPHIC_LITE_GRAPHIC_MATH_H

#include "heap_base.h"
#include <cstdint>

namespace OHOS {
/**
 * @brief Larger of a and b.
 */
#define MATH_MAX(a, b) ((a) > (b) ? (a) : (b))
/**
 * @brief Smaller of a and b.
 */
#define MATH_MIN(a, b) ((a) < (b) ? (a) : (b))
/**
 * @brief Absolute value of x.
 */
#define MATH_ABS(x) ((x) > 0 ? (x) : (-(x)))
/**
 * @brief Difference between a and b.
 */
#define MATH_MINUS(a, b) ((a) < (b) ? ((b) - (a)) : ((a) - (b)))

/** A quarter of a rotation: 90 degrees */
static constexpr uint16_t QUARTER_IN_DEGREE = 90;
/** A half of a rotation: 180 degrees */
static constexpr uint16_t SEMICIRCLE_IN_DEGREE = 180;
/** Three fourths of a rotation: 270 degrees */
static constexpr uint16_t THREE_QUARTER_IN_DEGREE = 270;
/** A full rotation: 360 degrees */
static constexpr uint16_t CIRCLE_IN_DEGREE = 360;
/** Pi value */
static constexpr double UI_PI = 3.14159265358979;
static constexpr float ATAN2_P3 = -0.3258775;
static constexpr float ATAN2_P5 = 0.1556117;
static constexpr float ATAN2_P7 = -0.0443360;
static constexpr float RADIAN_TO_ANGLE = 57.295779513;

float Sin(int16_t angle);
uint16_t FastAtan2(int16_t x, int16_t y);
uint32_t Sqrt(uint32_t num);

/**
 * @brief Defines the two-dimensional vector, and provides basic mathematical operations such as vector assignment,
 *        scalar product, cross product, addition, and subtraction.
 *
 * @since 1.0
 * @version 1.0
 */
template<typename T>
class Vector2 : public HeapBase {
public:
    /**
     * @brief A constructor used to create a <b>Vector2</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    Vector2() : x_(0), y_(0) {}

    /**
     * @brief A constructor used to create a <b>Vector2</b> instance based on the X and Y coordinates.
     * @param x Indicates the X coordinate.
     * @param y Indicates the Y coordinate.
     * @since 1.0
     * @version 1.0
     */
    Vector2(T x, T y)
    {
        x_ = x;
        y_ = y;
    }

    /**
     * @brief A destructor used to delete the <b>Vector2</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    ~Vector2() {}

    /**
     * @brief Calculates the scalar product of the two-dimensional vector and another two-dimensional vector.
     * @param other Indicates the two-dimensional vector to be used for calculation.
     * @return Returns the scalar product.
     * @since 1.0
     * @version 1.0
     */
    T Dot(const Vector2<T>& other) const
    {
        T sum = x_ * other.x_;
        sum += y_ * other.y_;
        return sum;
    }

    /**
     * @brief Calculates the cross product of the two-dimensional vector and another two-dimensional vector.
     * @param other Indicates the two-dimensional vector to be used for calculation.
     * @return Returns the cross product.
     * @since 1.0
     * @version 1.0
     */
    T Cross(const Vector2<T>& other) const
    {
        return x_ * other.y_ - y_ * other.x_;
    }

    Vector2 operator-() const
    {
        return Vector2(-x_, -y_);
    }

    Vector2 operator-(const Vector2<T>& other) const
    {
        return Vector2(x_ - other.x_, y_ - other.y_);
    }

    Vector2 operator+(const Vector2<T>& other) const
    {
        return Vector2(x_ + other.x_, y_ + other.y_);
    }

    Vector2 operator*(T scale) const
    {
        return Vector2(x_ * scale, y_ * scale);
    }

    bool operator==(const Vector2& other) const
    {
        return (x_ == other.x_) && (y_ == other.y_);
    }

    Vector2& operator=(const Vector2& other)
    {
        x_ = other.x_;
        y_ = other.y_;
        return *this;
    }

    Vector2& operator+=(const Vector2& other)
    {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }

    Vector2& operator-=(const Vector2& other)
    {
        x_ -= other.x_;
        y_ -= other.y_;
        return *this;
    }

    T x_;
    T y_;
};

/**
 * @brief Defines the 3-dimensional vector, and provides basic operators such as [] and ==.
 *
 * @since 1.0
 * @version 1.0
 */
template<typename T>
class Vector3 : public HeapBase {
public:
    union {
        struct {
            T x_;
            T y_;
            T z_;
        };
        T data_[3]; // 3: size for x,y,z
    };

    /**
     * @brief A constructor used to create a <b>Vector3</b> instance.
     * @since 1.0
     * @version 1.0
     */
    Vector3() : x_(0), y_(0), z_(1) {}

    /**
     * @brief Defines a <b>Vector3</b> instance and initializes the values of <b>x</b>, <b>y</b>, and <b>z</b>.
     * @param x Indicates the X coordinate.
     * @param y Indicates the Y coordinate.
     * @param z Indicates the Z coordinate.
     * @since 1.0
     * @version 1.0
     */
    Vector3(T x, T y, T z)
    {
        data_[0] = x;
        data_[1] = y;
        data_[2] = z; // 2: index of z
    }

    /**
     * @brief A destructor used to delete the <b>Vector3</b> instance.
     * @since 1.0
     * @version 1.0
     */
    ~Vector3() {}

    T operator[](uint8_t index) const
    {
        return data_[index];
    }

    T& operator[](uint8_t index)
    {
        return data_[index];
    }

    bool operator==(const Vector3& other) const
    {
        return (x_ == other.x_) && (y_ == other.y_) && (z_ == other.z_);
    }
};

/**
 * @brief Defines a 3 x 3 matrix.
 *
 * @since 1.0
 * @version 1.0
 */
template<typename T>
class Matrix3 : public HeapBase {
public:
    /**
     * @brief Defines a <b>Matrix3</b> instance and initializes the 3 x 3 matrix data.
     *
     * @since 1.0
     * @version 1.0
     */
    Matrix3();

    /**
     * @brief Defines a <b>Matrix3</b> instance and initializes the 3 x 3 matrix data.
     *
     * @param m00 Indicates the element in row 1 and column 1 of the matrix.
     * @param m01 Indicates the element in row 1 and column 2 of the matrix.
     * @param m02 Indicates the element in row 1 and column 3 of the matrix.
     * @param m10 Indicates the element in row 2 and column 1 of the matrix.
     * @param m11 Indicates the element in row 2 and column 2 of the matrix.
     * @param m12 Indicates the element in row 2 and column 3 of the matrix.
     * @param m20 Indicates the element in row 3 and column 1 of the matrix.
     * @param m21 Indicates the element in row 3 and column 2 of the matrix.
     * @param m22 Indicates the element in row 3 and column 3 of the matrix.
     * @since 1.0
     * @version 1.0
     */
    Matrix3(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22);

    /**
     * @brief A destructor used to delete the <b>Matrix3</b> instance.
     * @since 1.0
     * @version 1.0
     */
    ~Matrix3() {}

    /**
     * @brief Obtains the 3 x 3 matrix data.
     * @return Returns the 3 x 3 matrix data.
     * @since 1.0
     * @version 1.0
     */
    const T* GetData() const
    {
        return data_;
    }

    /**
     * @brief Obtains the determinant of the matrix.
     * @return Returns the determinant.
     * @since 1.0
     * @version 1.0
     */
    T Determinant() const;

    /**
     * @brief Obtains the inverse matrix.
     * @return Returns the inverse matrix.
     * @since 1.0
     * @version 1.0
     */
    Matrix3 Inverse() const;

    /**
     * @brief Obtains a rotation matrix. After a matrix is rotated, its data is shifted leftwards by 15 bits. Therefore,
     *        the result data needs to be shifted rightwards by 15 bits.
     * @param angle Indicates the angle to rotate.
     * @param pivot Indicates the rotation pivot.
     * @return Returns the matrix after rotation.
     * @since 1.0
     * @version 1.0
     */
    static Matrix3 Rotate(T angle, const Vector2<T>& pivot);

    /**
     * @brief Obtains the scaling matrix. After a matrix is scaled, its data is shifted leftwards by 8 bits. Therefore,
     *        the result data needs to be shifted rightwards by 8 bits.
     * @param scale Indicates the scaling factors of the x-axis and y-axis.
     * @param fixed Indicates the fixed scaling point.
     * @return Returns the matrix after scaling.
     * @since 1.0
     * @version 1.0
     */
    static Matrix3 Scale(const Vector2<T>& scale, const Vector2<T>& fixed);

    /**
     * @brief Obtains a matrix translation.
     * @param trans Indicates the distances to translate along the x-axis and y-axis.
     * @return Returns the matrix after translation.
     * @since 1.0
     * @version 1.0
     */
    static Matrix3<T> Translate(const Vector2<T>& trans);

    Matrix3 operator*(const Matrix3& other) const;

    Vector3<T> operator*(const Vector3<T>& other) const;

    T* operator[](uint8_t col)
    {
        return &data_[col * 3]; // 3: size of point
    }

    Matrix3& operator=(const Matrix3& other)
    {
        // 9: data_ value number
        data_[0] = other.data_[0];
        data_[1] = other.data_[1];
        data_[2] = other.data_[2];
        data_[3] = other.data_[3];
        data_[4] = other.data_[4];
        data_[5] = other.data_[5];
        data_[6] = other.data_[6];
        data_[7] = other.data_[7];
        data_[8] = other.data_[8];
        return *this;
    }

    bool operator==(const Matrix3& other) const;

protected:
    T data_[9]; // 9: 3 point with x,y,z
};

template<typename T>
Matrix3<T>::Matrix3()
{
    data_[1] = 0;
    data_[2] = 0;
    data_[3] = 0;
    data_[5] = 0;
    data_[6] = 0;
    data_[7] = 0;
    data_[0] = 1;
    data_[4] = 1;
    data_[8] = 1;
}

template<typename T>
Matrix3<T>::Matrix3(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22)
{
    data_[0] = m00;
    data_[1] = m01;
    data_[2] = m02;

    data_[3] = m10;
    data_[4] = m11;
    data_[5] = m12;

    data_[6] = m20;
    data_[7] = m21;
    data_[8] = m22;
}

template<typename T>
Matrix3<T> Matrix3<T>::operator*(const Matrix3<T>& other) const
{
    Matrix3<T> rMulti;
    T* rData = rMulti.data_;
    const T* oData = other.data_;

    rData[0] = data_[0] * oData[0] + data_[3] * oData[1] + data_[6] * oData[2];
    rData[3] = data_[0] * oData[3] + data_[3] * oData[4] + data_[6] * oData[5];
    rData[6] = data_[0] * oData[6] + data_[3] * oData[7] + data_[6] * oData[8];

    rData[1] = data_[1] * oData[0] + data_[4] * oData[1] + data_[7] * oData[2];
    rData[4] = data_[1] * oData[3] + data_[4] * oData[4] + data_[7] * oData[5];
    rData[7] = data_[1] * oData[6] + data_[4] * oData[7] + data_[7] * oData[8];

    rData[2] = data_[2] * oData[0] + data_[5] * oData[1] + data_[8] * oData[2];
    rData[5] = data_[2] * oData[3] + data_[5] * oData[4] + data_[8] * oData[5];
    rData[8] = data_[2] * oData[6] + data_[5] * oData[7] + data_[8] * oData[8];
    return rMulti;
}

template<typename T>
Vector3<T> Matrix3<T>::operator*(const Vector3<T>& other) const
{
    Vector3<T> rMulti;
    T* rData = rMulti.data_;
    const T* oData = other.data_;
    rData[0] = data_[0] * oData[0] + data_[3] * oData[1] + data_[6] * oData[2];
    rData[1] = data_[1] * oData[0] + data_[4] * oData[1] + data_[7] * oData[2];
    rData[2] = data_[2] * oData[0] + data_[5] * oData[1] + data_[8] * oData[2];
    return rMulti;
}

template<typename T>
T Matrix3<T>::Determinant() const
{
    T x = data_[0] * ((data_[4] * data_[8]) - (data_[5] * data_[7]));
    T y = data_[1] * ((data_[3] * data_[8]) - (data_[5] * data_[6]));
    T z = data_[2] * ((data_[3] * data_[7]) - (data_[4] * data_[6]));
    return (x - y) + z;
}

template<typename T>
Matrix3<T> Matrix3<T>::Inverse() const
{
    T det = this->Determinant();
    if (det == 0) {
        return Matrix3<T>(*this);
    }

    T invDet = 1.0f / det;
    const T* data = this->data_;

    T iX = invDet * (data[4] * data[8] - data[5] * data[7]);
    T iY = invDet * (data[2] * data[7] - data[1] * data[8]);
    T iZ = invDet * (data[1] * data[5] - data[2] * data[4]);
    T jX = invDet * (data[5] * data[6] - data[3] * data[8]);
    T jY = invDet * (data[0] * data[8] - data[2] * data[6]);
    T jZ = invDet * (data[2] * data[3] - data[0] * data[5]);
    T kX = invDet * (data[3] * data[7] - data[4] * data[6]);
    T kY = invDet * (data[1] * data[6] - data[0] * data[7]);
    T kZ = invDet * (data[0] * data[4] - data[1] * data[3]);

    return Matrix3<T>(iX, iY, iZ, jX, jY, jZ, kX, kY, kZ);
}

template<typename T>
bool Matrix3<T>::operator==(const Matrix3& other) const
{
    const T* oData = other.data_;

    return (data_[0] == oData[0]) && (data_[1] == oData[1]) && (data_[2] == oData[2]) && (data_[3] == oData[3]) &&
           (data_[4] == oData[4]) && (data_[5] == oData[5]) && (data_[6] == oData[6]) && (data_[7] == oData[7]) &&
           (data_[8] == oData[8]);
}

template<typename T>
Matrix3<T> Matrix3<T>::Rotate(T angle, const Vector2<T>& pivot)
{
    T s = static_cast<T>(Sin(angle) * 32768); /* 32768: 2^15 */
    T c = static_cast<T>(Sin(angle + 90) * 32768); /* 90: cos */

    Matrix3<T> rotateMat3;
    T* rData = rotateMat3.data_;
    rData[0] = c;
    rData[1] = s;

    rData[3] = -s;
    rData[4] = c;

    rData[6] = pivot.x_ * (32768 - c) + pivot.y_ * s;
    rData[7] = pivot.y_ * (32768 - c) - pivot.x_ * s;

    rData[8] = 32768;

    return rotateMat3;
}

template<typename T>
Matrix3<T> Matrix3<T>::Scale(const Vector2<T>& scale, const Vector2<T>& fixed)
{
    Matrix3<T> scaleMat3;
    T* rData = scaleMat3.data_;
    rData[0] = scale.x_;

    rData[4] = scale.y_;

    // 256: 2^8
    rData[6] = fixed.x_ * (256 - scale.x_);
    rData[7] = fixed.y_ * (256 - scale.y_);

    rData[8] = 256;

    return scaleMat3;
}

template<typename T>
Matrix3<T> Matrix3<T>::Translate(const Vector2<T>& trans)
{
    Matrix3 transMat3;
    T* rData = transMat3.data_;

    rData[6] = trans.x_;
    rData[7] = trans.y_;

    return transMat3;
}

inline int64_t FloatToInt64(float f)
{
    if (f > 127.0) { // 127.0: 2^7
        return 0x7FFF;
    }

    if (f < -127.0) { // 127.0: 2^7
        return -0x7FFF;
    }

    // 256.0: 2^8 left move 8 bit. 0.5: round up
    return static_cast<int64_t>(f * 256.0 + ((f < 0) ? -0.5 : 0.5));
}
} // namespace OHOS
#endif // GRAPHIC_LITE_GRAPHIC_MATH_H
