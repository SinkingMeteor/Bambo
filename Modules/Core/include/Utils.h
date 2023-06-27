#pragma once
#include "pch.h"

namespace Bambo 
{
	constexpr const float ONE_DEGREE_IN_RADIANS = 0.0174532f;
	constexpr const float ONE_RADIAN_IN_DEGREES = 57.2957795f;

	inline std::size_t ToId(const std::string& text) 
	{
		return std::hash<std::string>{}(text);
	}

	inline float DegToRad(float degrees) 
	{
		return ONE_DEGREE_IN_RADIANS * degrees;
	}

	inline float RadToDeg(float radians) 
	{
		return ONE_RADIAN_IN_DEGREES * radians;
	}

	bool HasExtension(const std::string& targetString, const std::string& extension);
	bool IsHiddenFolder(const std::filesystem::path& path);
	bool IsLittleEndian();
	int ConvertToInt(char* buffer, std::size_t len);
}