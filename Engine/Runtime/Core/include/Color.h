#pragma once

namespace Bambo
{
	struct BAMBO_API Color final
	{
		Color() : Color(1.0f, 1.0f, 1.0f, 1.0f) {}
		Color(float r, float g, float b, float a) :
			R(r),
			G(g),
			B(b),
			A(a)
		{}


		float R{};
		float G{};
		float B{};
		float A{};

	};
}