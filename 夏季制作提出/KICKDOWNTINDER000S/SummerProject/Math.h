#pragma once

#include <cmath>
#include <limits>

namespace Math {
	// �~����
	constexpr double Pi = 3.1415926535f;
	constexpr double TwoPi = Pi * 2.0f;
	constexpr double PiOver2 = Pi / 2.0f;

	// �x������Ǔx(���W�A��)�ɕϊ�
	inline double ToRadians(double degrees)
	{
		return degrees * Pi / 180.0f;
	}
	// �Ǔx����x��(�f�B�O���[)�ɕϊ�
	inline double ToDegrees(double radians)
	{
		return radians * 180.0f / Pi;
	}
	// ��̒l�̑傫���l���擾
	template <typename T>
	T Max(const T& a, const T& b)
	{
		return (a < b ? b : a);
	}
	// ��̒l�̏������l���擾
	template <typename T>
	T Min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}
	// ��̒l�̊ԂŃN�����v����
	template <typename T>
	T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, value));
	}
}