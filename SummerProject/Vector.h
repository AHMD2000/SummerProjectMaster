#pragma once

#include <cmath>
#include <limits>

// (1)2D�x�N�g���N���X�̐錾
class Vector2 {
public:
    // x����,y����
    double x, y;
    // �R���X�g���N�^
    Vector2(double inX = 0.0, double inY = 0.0)
        :x{ inX }
        , y{ inY } {
    }
    //// (2-1)�x�N�g���̉��Z a + b ���O���֐�
    //friend Vector2 operator+(const Vector2& a, const Vector2& b) {
    //    return { a.x + b.x, a.y + b.y };
    //}
    //// (2-2.)�x�N�g���̌��Z a - b ���O���֐�
    //friend Vector2 operator-(const Vector2& a, const Vector2& b) {
    //    return { a.x - b.x, a.y - b.y };
    //}
    //// (3-1)�x�N�g���̃X�J���[�{ v * scalar ���O���֐�
    //friend Vector2 operator*(const Vector2& v, float scalar) {
    //    return { v.x * scalar, v.y * scalar };
    //}
    //// (3-2)�x�N�g���̃X�J���[�{ scalar * v ���O���֐�
    //friend Vector2 operator*(float scalar, const Vector2& v) {
    //    return { v.x * scalar, v.y * scalar };
    //}
    //// (6-4)�x�N�g�����Z���
    //Vector2& operator+=(const Vector2& right) {
    //    x += right.x;
    //    y += right.y;
    //    return *this;
    //}
    //// �x�N�g�����Z���
    //Vector2& operator-=(const Vector2& right) {
    //    x -= right.x;
    //    y -= right.y;
    //    return *this;
    //}
    //// �x�N�g���̃X�J����Z���
    //Vector2& operator*=(float scalar) {
    //    x *= scalar;
    //    y *= scalar;
    //    return *this;
    //}
    //// (3-3)�x�N�g���̑傫��
    //float Length() const {
    //    return std::sqrt(x * x + y * y);
    //}
    //// (3-4.)�x�N�g���̐��K��
    //void Normalize() {
    //    auto length = Length();
    //    // �덷�����Ȃ�[���Ƃ݂Ȃ��B
    //    if (std::abs(length) < std::numeric_limits<double>::epsilon()) {
    //        x = 0.0;
    //        y = 0.0;
    //    }
    //    else {
    //        x /= length;
    //        y /= length;
    //    }
    //}

    // �x�N�g���̉��Z a + b ���O���֐�
    friend Vector2 operator+(const Vector2& a, const Vector2& b)
    {
        return { a.x + b.x, a.y + b.y };
    }
    // �x�N�g���̌��Z a - b ���O���֐�
    friend Vector2 operator-(const Vector2& a, const Vector2& b)
    {
        return { a.x - b.x, a.y - b.y };
    }
    // �x�N�g���̃X�J���[�{ v * scalar ���O���֐�
    friend Vector2 operator*(const Vector2& v, double scalar)
    {
        return { v.x * scalar, v.y * scalar };
    }
    // �x�N�g���̃X�J���[�{ scalar * v ���O���֐�
    friend Vector2 operator*(double scalar, const Vector2& v)
    {
        return { v.x * scalar, v.y * scalar };
    }
    // �x�N�g�����Z���
    Vector2& operator+=(const Vector2& right)
    {
        x += right.x;
        y += right.y;
        return *this;
    }
    // �x�N�g�����Z���
    Vector2& operator-=(const Vector2& right)
    {
        x -= right.x;
        y -= right.y;
        return *this;
    }
    // �x�N�g���̃X�J����Z���
    Vector2& operator*=(double scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    // �x�N�g���̑傫��
    double Length() const
    {
        return std::sqrt(x * x + y * y);
    }
    // �x�N�g���̐��K��
    void Normalize()
    {
        auto length = Length();
            // �덷�����Ȃ�[���Ƃ݂Ȃ��B
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