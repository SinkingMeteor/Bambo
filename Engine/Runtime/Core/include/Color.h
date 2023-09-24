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

		static Color White();
		static Color Red();
		static Color Green();
		static Color Blue();
		static Color Black();
		static Color Transparent();
	};

	struct BAMBO_API ByteColor final
	{
		ByteColor() : ByteColor(255, 255, 255, 255) {}
		ByteColor(uint8 r, uint8 g, uint8 b, uint8 a) :
			R(r),
			G(g),
			B(b),
			A(a)
		{}


		uint8 R{};
		uint8 G{};
		uint8 B{};
		uint8 A{};

		static ByteColor White();
		static ByteColor Red();
		static ByteColor Green();
		static ByteColor Blue();
		static ByteColor Black();
		static ByteColor Transparent();
	};
}