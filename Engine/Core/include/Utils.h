#pragma once
#include "pch.h"

namespace Bambo 
{
	constexpr const float ONE_DEGREE_IN_RADIANS = 0.0174532f;
	constexpr const float ONE_RADIAN_IN_DEGREES = 57.2957795f;

	template<typename... Args>
	static void Log(const char* logScope, const char* format, Args&&...args)
	{
		printf("[%s]: ", logScope);
		printf(format, std::forward<Args>(args)...);
		printf("\n");
	}

	static void Log(const char* logScope, const char* text)
	{
		printf("[%s]: %s\n", logScope, text);
	}

	static std::size_t ToId(const std::string& text) 
	{
		return std::hash<std::string>{}(text);
	}

	static float DegToRad(float degrees) 
	{
		return ONE_DEGREE_IN_RADIANS * degrees;
	}

	static float RadToDeg(float radians) 
	{
		return ONE_RADIAN_IN_DEGREES * radians;
	}

	static bool IsLittleEndian()
	{
		short int word = 0x0001;
		char* b = (char*)&word;

		if (b[0])
		{
			return true;
		}
		return false;

	}
}