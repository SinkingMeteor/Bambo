#pragma once
#include "pch.h"

namespace Bambo
{

	template<typename T>
	struct Vector2
	{
		static_assert(std::is_arithmetic<T>::value);

	public:
		T X;
		T Y;

		Vector2() noexcept : Vector2(T(0.0f), T(0.0f)) {}
		Vector2(T valueX, T valueY) noexcept : X(valueX), Y(valueY) {}

		float Dot(const Vector2<T>& vector) const;
		float Magnitude() const;
		Vector2<T> GetNormalized() const;
	};

	template<typename T>
	inline float Vector2<T>::Dot(const Vector2<T>& vector) const
	{
		return X * vector.X + Y * vector.Y;
	}

	template<typename T>
	inline float Vector2<T>::Magnitude() const
	{
		float x = static_cast<float>(X);
		float y = static_cast<float>(Y);
		return std::sqrt(x * x + y * y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::GetNormalized() const
	{
		float length = this->Magnitude();
		if (length <= 0.0f)
		{
			return Vector2<T>{};
		}

		T x = static_cast<T>(X / length);
		T y = static_cast<T>(Y / length);
		return Vector2<T>{x, y};
	}

	template<typename T>
	Vector2<T> operator+(const Vector2<T>& lVector, const Vector2<T>& rVector)
	{
		return Vector2<T>(lVector.X + rVector.X, lVector.Y + rVector.Y);
	}

	template<typename T>
	Vector2<T> operator-(const Vector2<T>& lVector, const Vector2<T>& rVector)
	{
		return Vector2<T>(lVector.X - rVector.X, lVector.Y - rVector.Y);
	}

	using Vector2f = Vector2<float>;
	using Vector2i = Vector2<int>;

	template<typename T>
	struct Vector3
	{
	public:
		T X;
		T Y;
		T Z;

		Vector3() noexcept : Vector3(T(0.0f), T(0.0f), T(0.0f)) {}
		Vector3(T valueX, T valueY, T valueZ) : X(valueX), Y(valueY), Z(valueZ) {}

		float Dot(const Vector3<T>& vector) const;
		float Magnitude() const;
		Vector3<T> GetNormalized() const;
	};

	template<typename T>
	inline float Vector3<T>::Dot(const Vector3<T>& vector) const
	{
		return X * vector.X + Y * vector.Y + Z * vector.Z;
	}

	template<typename T>
	inline float Vector3<T>::Magnitude() const
	{
		float x = static_cast<float>(X);
		float y = static_cast<float>(Y);
		float z = static_cast<float>(Z);
		return std::sqrt(x * x + y * y + z * z);
	}

	template<typename T>
	Vector3<T> Vector3<T>::GetNormalized() const
	{
		float length = this->Magnitude();
		if (length <= 0.0f)
		{
			return Vector3<T>{};
		}

		T x = static_cast<T>(X / length);
		T y = static_cast<T>(Y / length);
		T z = static_cast<T>(Z / length);
		return Vector3<T>{x, y, z};
	}

	template<typename T>
	Vector3<T> operator+(const Vector3<T>& lVector, const Vector3<T>& rVector)
	{
		return Vector3<T>(lVector.X + rVector.X, lVector.Y + rVector.Y, lVector.Z + rVector.Z);
	}

	template<typename T>
	Vector3<T> operator-(const Vector3<T>& lVector, const Vector3<T>& rVector)
	{
		return Vector3<T>(lVector.X - rVector.X, lVector.Y - rVector.Y, lVector.Z - rVector.Z);
	}

	using Vector3f = Vector3<float>;
	using Vector3i = Vector3<int>;
}