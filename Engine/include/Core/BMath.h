#pragma once
#include "pch.h"
#include "Vectors.h"

namespace Bambo
{
	namespace BMath
	{
		constexpr const float DEG2RAD = 0.0174532f;
		constexpr const float RAD2DEG = 57.2957795f;
		constexpr const float TAU = 6.28318530717959f;
		constexpr const float PI = 3.14159265359f;
		constexpr const float DEFAULT_TOLERANCE = 0.0000001f;

		bool IsNearlyEqual(float v1, float v2, float tolerance = DEFAULT_TOLERANCE)
		{
			return std::abs(v1 - v2) < tolerance;
		}

		template<typename T>
		bool IsNearlyEqual(const Vector3<T>& vec1, const Vector3<T>& vec2, float tolerance = DEFAULT_TOLERANCE)
		{
			return vec1.X == vec2.X && vec1.Y == vec2.Y && vec1.Z == vec2.Z;
		}

		bool IsNearlyEqual(const Vector3f& vec1, const Vector3f& vec2, float tolerance = DEFAULT_TOLERANCE)
		{
			return IsNearlyEqual(vec1.X, vec2.X, tolerance) && IsNearlyEqual(vec1.Y, vec2.Y, tolerance) && IsNearlyEqual(vec1.Z, vec2.Z, tolerance);
		}

		template<typename T>
		bool IsNearlyEqual(const Vector2<T>& vec1, const Vector2<T>& vec2, float tolerance = DEFAULT_TOLERANCE)
		{
			return vec1.X == vec2.X && vec1.Y == vec2.Y;
		}

		bool IsNearlyEqual(const Vector2f& vec1, const Vector2f& vec2, float tolerance = DEFAULT_TOLERANCE)
		{
			return IsNearlyEqual(vec1.X, vec2.X, tolerance) && IsNearlyEqual(vec1.Y, vec2.Y, tolerance);
		}

		template<typename T>
		Vector2<T> ToVec2(const Vector3<T>& vec)
		{
			return Vector2<T>{ vec.X, vec.Y };
		}

		template<typename T>
		float Clamp(T from, T to, T value)
		{
			return std::clamp(from, to, value);
		}

		float Clamp01(float value)
		{
			return Clamp(0.0f, 1.0f, value);
		}

		float DegToRad(float degrees)
		{
			return DEG2RAD * degrees;
		}

		float RadToDeg(float radians)
		{
			return RAD2DEG * radians;
		}

		float Lerp(float a, float b, float t)
		{
			return (1.0f - t) * a + t * b;
		}

		float InverseLerp(float a, float b, float t)
		{
			BAMBO_ASSERT_S(!IsNearlyEqual(a, b))

			return (t - a) / (b - a);
		}

		float InverseLerpClamped(float a, float b, float t)
		{
			return Clamp01((t - a) / (b - a));
		}

		float Remap(float iMin, float iMax, float oMin, float oMax, float value)
		{
			return Lerp(oMin, oMax, InverseLerp(iMin, iMax, value));
		}

		void Sum(int& counter, float& total, float num)
		{
			++counter;
			total += num;
		}

		template<typename... Args>
		void Sum(int& counter, float& total, float num, Args... args)
		{
			++counter;
			total += num;
			Sum(counter, total, args...);
		}

		template<typename... Args>
		float Average(Args... args)
		{
			float total = 0.0f;
			int32 counter = 0;
			Sum(counter, total, args...);
			return total / counter;
		}

	}
}
