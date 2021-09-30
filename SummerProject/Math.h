#pragma once

#include <cmath>
#include <limits>

namespace Math {
	// 円周率
	constexpr double Pi = 3.1415926535f;
	constexpr double TwoPi = Pi * 2.0f;
	constexpr double PiOver2 = Pi / 2.0f;

	// 度数から孤度(ラジアン)に変換
	inline double ToRadians(double degrees)
	{
		return degrees * Pi / 180.0f;
	}
	// 孤度から度数(ディグリー)に変換
	inline double ToDegrees(double radians)
	{
		return radians * 180.0f / Pi;
	}
	// 二つの値の大きい値を取得
	template <typename T>
	T Max(const T& a, const T& b)
	{
		return (a < b ? b : a);
	}
	// 二つの値の小さい値を取得
	template <typename T>
	T Min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}
	// 二つの値の間でクランプする
	template <typename T>
	T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, value));
	}
}