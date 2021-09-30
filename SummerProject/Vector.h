#pragma once

#include <cmath>
#include <limits>

// (1)2Dベクトルクラスの宣言
class Vector2 {
public:
    // x成分,y成分
    double x, y;
    // コンストラクタ
    Vector2(double inX = 0.0, double inY = 0.0)
        :x{ inX }
        , y{ inY } {
    }
    //// (2-1)ベクトルの加算 a + b ※外部関数
    //friend Vector2 operator+(const Vector2& a, const Vector2& b) {
    //    return { a.x + b.x, a.y + b.y };
    //}
    //// (2-2.)ベクトルの減算 a - b ※外部関数
    //friend Vector2 operator-(const Vector2& a, const Vector2& b) {
    //    return { a.x - b.x, a.y - b.y };
    //}
    //// (3-1)ベクトルのスカラー倍 v * scalar ※外部関数
    //friend Vector2 operator*(const Vector2& v, float scalar) {
    //    return { v.x * scalar, v.y * scalar };
    //}
    //// (3-2)ベクトルのスカラー倍 scalar * v ※外部関数
    //friend Vector2 operator*(float scalar, const Vector2& v) {
    //    return { v.x * scalar, v.y * scalar };
    //}
    //// (6-4)ベクトル加算代入
    //Vector2& operator+=(const Vector2& right) {
    //    x += right.x;
    //    y += right.y;
    //    return *this;
    //}
    //// ベクトル減算代入
    //Vector2& operator-=(const Vector2& right) {
    //    x -= right.x;
    //    y -= right.y;
    //    return *this;
    //}
    //// ベクトルのスカラ乗算代入
    //Vector2& operator*=(float scalar) {
    //    x *= scalar;
    //    y *= scalar;
    //    return *this;
    //}
    //// (3-3)ベクトルの大きさ
    //float Length() const {
    //    return std::sqrt(x * x + y * y);
    //}
    //// (3-4.)ベクトルの正規化
    //void Normalize() {
    //    auto length = Length();
    //    // 誤差未満ならゼロとみなす。
    //    if (std::abs(length) < std::numeric_limits<double>::epsilon()) {
    //        x = 0.0;
    //        y = 0.0;
    //    }
    //    else {
    //        x /= length;
    //        y /= length;
    //    }
    //}

    // ベクトルの加算 a + b ※外部関数
    friend Vector2 operator+(const Vector2& a, const Vector2& b)
    {
        return { a.x + b.x, a.y + b.y };
    }
    // ベクトルの減算 a - b ※外部関数
    friend Vector2 operator-(const Vector2& a, const Vector2& b)
    {
        return { a.x - b.x, a.y - b.y };
    }
    // ベクトルのスカラー倍 v * scalar ※外部関数
    friend Vector2 operator*(const Vector2& v, double scalar)
    {
        return { v.x * scalar, v.y * scalar };
    }
    // ベクトルのスカラー倍 scalar * v ※外部関数
    friend Vector2 operator*(double scalar, const Vector2& v)
    {
        return { v.x * scalar, v.y * scalar };
    }
    // ベクトル加算代入
    Vector2& operator+=(const Vector2& right)
    {
        x += right.x;
        y += right.y;
        return *this;
    }
    // ベクトル減算代入
    Vector2& operator-=(const Vector2& right)
    {
        x -= right.x;
        y -= right.y;
        return *this;
    }
    // ベクトルのスカラ乗算代入
    Vector2& operator*=(double scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    // ベクトルの大きさ
    double Length() const
    {
        return std::sqrt(x * x + y * y);
    }
    // ベクトルの正規化
    void Normalize()
    {
        auto length = Length();
            // 誤差未満ならゼロとみなす。
            if (std::abs(length) < std::numeric_limits<double>::epsilon()) {
                x = 0.0;
                y = 0.0;
            }
            else {
                x /= length;
                y /= length;
            }
    }

    static Vector2 Normalize(const Vector2& vec)
    {
        auto temp = vec;
        temp.Normalize();
        return temp;
    }
};