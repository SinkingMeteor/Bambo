#pragma once
#include "pch.h"

namespace Bambo 
{
	inline std::size_t ToId(const std::string& text) 
	{
		return std::hash<std::string>{}(text);
	}

	bool HasExtension(const std::string& targetString, const std::string& extension);
	bool IsHiddenFolder(const std::filesystem::path& path);
	bool IsLittleEndian();
	int ConvertToInt(char* buffer, std::size_t len);
}