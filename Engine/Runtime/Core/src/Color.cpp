#include "Color.h"

namespace Bambo
{
	Color Color::White()
	{
		static Color color{ 1.0f, 1.0f, 1.0f, 1.0f };
		return color;
	}

	Color Color::Yellow()
	{
		static Color color{ 1.0f, 1.0f, 0.0f, 1.0f };
		return color;
	}

	Color Color::Red()
	{
		static Color color{ 1.0f, 0.0f, 0.0f, 1.0f };
		return color;
	}

	Color Color::Green()
	{
		static Color color{ 0.0f, 1.0f, 0.0f, 1.0f };
		return color;
	}

	Color Color::Blue()
	{
		static Color color{ 0.0f, 0.0f, 1.0f, 1.0f };
		return color;
	}

	Color Color::Black()
	{
		static Color color{ 0.0f, 0.0f, 0.0f, 1.0f };
		return color;
	}

	Color Color::Transparent()
	{
		static Color color{ 0.0f, 0.0f, 0.0f, 0.0f };
		return color;
	}

	ByteColor ByteColor::White()
	{
		static ByteColor color{ 255u, 255u, 255u, 255u };
		return color;
	}

	ByteColor ByteColor::Red()
	{
		static ByteColor color{ 255u, 0u, 0u, 255u };
		return color;
	}

	ByteColor ByteColor::Green()
	{
		static ByteColor color{ 0u, 255u, 0u, 255u };
		return color;
	}

	ByteColor ByteColor::Blue()
	{
		static ByteColor color{ 0u, 0u, 255u, 255u };
		return color;
	}

	ByteColor ByteColor::Black()
	{
		static ByteColor color{ 0u, 0u, 0u, 255u };
		return color;
	}

	ByteColor ByteColor::Transparent()
	{
		static ByteColor color{ 0u, 0u, 0u, 0u };
		return color;
	}
}