#pragma once

namespace nc
{
	const float Pi = 3.14159265359f;		// 180 degree
	const float TwoPi = 6.28318530718f;		// 360 degree
	const float HalfPi = 1.57079632679f;	// 90 degree
	const float QuarterPi = 0.78539816339f;	// 45 degree

	inline float RadToDeg(float radians)
	{
		return radians * 180.0f / Pi; // == 57.295
	}
	
	inline float DegToRad(float degrees)
	{
		return degrees * Pi / 180.0f; // == 0.01745
	}

	template<typename T>
	inline T Clamp(T v, T min, T max)
	{
		if (v < min) return min;
		if (v > max) return max;
		return v;
	}
	
	template<typename T>
	T Wrap(T v, T min, T max)
	{
		if (v < min) return max;
		if (v > max) return min;
		return v;
	}
	
	template<typename T>
	T Lerp(T a, T b, float t)
	{
		t = Clamp(t, 0.0f, 1.0f);

		return a + ((b - a) * t);
	}
}