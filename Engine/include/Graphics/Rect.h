#pragma once
#include "pch.h"
#include "Graphics/CommonMath.h"

namespace Bambo 
{
	template <typename T>
	struct BAMBO_API Rect 
	{
	public:
		Rect() : Rect(0.0f, 0.0f, 0.0f, 0.0f) {}
		Rect(T left, T top, T width, T height);
		Rect(Vector2<T> leftTop, Vector2<T> size);
		bool Intersects2D(const Rect<T>& rect1, const Rect<T>& rect2);

		T Left;
		T Top;
		T Width;
		T Height;
	};

	template<typename T>
	Rect<T>::Rect(T left, T top, T width, T height) :
		Left(left),
		Top(top),
		Width(width),
		Height(height)
	{}

	template<typename T>
	Rect<T>::Rect(Vector2<T> leftTop, Vector2<T> size) :
		Left(leftTop.X),
		Top(leftTop.Y),
		Width(size.X),
		Height(size.Y)
	{}

	template<typename T>
	bool Rect<T>::Intersects2D(const Rect<T>& rect1, const Rect<T>& rect2)
	{
		Vector2<T> rect1Min = Vector2<T>{ rect1.Left, rect1.Top };
		Vector2<T> rect2Min = Vector2<T>{ rect2.Left, rect2.Top };
		Vector2<T> rect1Max = rect1Min + Vector2<T>{ rect1.Width, rect1.Height };
		Vector2<T> rect2Max = rect2Min + Vector2<T>{ rect2.Width, rect2.Height };

		return rect1Min.x <= rect2Max.x &&
			rect1Max.x >= rect2Min.x &&
			rect1Min.y <= rect2Max.y &&
			rect1Max.y >= rect2Min.y;
	}

	using RectInt = Rect<int>;
	using RectFloat = Rect<float>;
}