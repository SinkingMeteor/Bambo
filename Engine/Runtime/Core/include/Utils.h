#pragma once
#include "pch.h"
#include "Log.h"

namespace Bambo 
{
	BAMBO_API std::size_t HashString(const std::string_view& str);

	BAMBO_API inline std::size_t ToId(const std::string& text) 
	{
		return HashString(text);
	}

	BAMBO_API bool HasExtension(const std::string& targetString, const std::string& extension);
	BAMBO_API bool IsHiddenFolder(const std::filesystem::path& path);
	BAMBO_API bool IsLittleEndian();
	BAMBO_API void GetAvalaibleDisks(std::vector<std::string>& disks);
	BAMBO_API int ConvertToInt(char* buffer, std::size_t len);
	BAMBO_API bool MakeDirectory(const std::filesystem::path& path, const std::string& directoryName);
}