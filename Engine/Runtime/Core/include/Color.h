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
		static Color Yellow();
		static Color Red();
		static Color Green();
		static Color Blue();
		static Color Cyan();
		static Color Black();
		static Color Transparent();
	};

	struct BAMBO_API ByteColor final
	{
		ByteColor() : ByteColor(255u, 255u, 255u, 255u) {}
		ByteColor(uint8 r) : ByteColor(r, 255u, 255u, 255u) {}
		ByteColor(uint8 r, uint8 g) : ByteColor(r, g, 255u, 255u) {}
		ByteColor(uint8 r, uint8 g, uint8 b) : ByteColor(r, g, b, 255u) {}
		ByteColor(uint8 r, uint8 g, uint8 b, uint8 a) :
			Colors()
		{
			Colors[0] = r;
			Colors[1] = g;
			Colors[2] = b;
			Colors[3] = a;
		}

		uint8 Colors[4];

		static ByteColor White();
		static ByteColor Red();
		static ByteColor Green();
		static ByteColor Blue();
		static ByteColor Black();
		static ByteColor Transparent();
	};
}