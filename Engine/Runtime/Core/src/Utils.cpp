#include "Utils.h"

namespace Bambo
{
	DECLARE_LOG_CATEGORY_STATIC(UtilsLog)

	bool IsLittleEndian()
	{
		short int word = 0x0001;
		char* b = (char*)&word;

		if (b[0])
		{
			return true;
		}
		return false;
	}

	int ConvertToInt(char* buffer, std::size_t len)
	{
		std::int32_t a = 0;
		if (IsLittleEndian())
		{
			std::memcpy(&a, buffer, len);
		}
		else
		{
			for (std::size_t i = 0; i < len; ++i)
			{
				reinterpret_cast<char*>(&a)[3 - i] = buffer[i];
			}
		}
		return a;
	}


	bool MakeDirectory(const std::filesystem::path& path, const std::string& directoryName)
	{
		std::error_code err{};
		std::filesystem::path targetPath = path / directoryName;
		if (!std::filesystem::create_directories(targetPath, err))
		{
			if (std::filesystem::exists(targetPath))
			{

				return true; 
			}

			Logger::Get()->Log(UtilsLog, Verbosity::Error, ": FAILED to create [%s], err:%s\n", directoryName.c_str(), err.message().c_str());
			return false;
		}
		return true;
	}

	void GetAvalaibleDisks(std::vector<std::string>& disks)
	{
		DWORD dwSize = MAX_PATH;
		char szLogicalDrives[MAX_PATH] = { 0 };
		DWORD dwResult = GetLogicalDriveStringsA(dwSize, szLogicalDrives);

		if (dwResult > 0 && dwResult <= MAX_PATH)
		{
			char* szSingleDrive = szLogicalDrives;
			while (*szSingleDrive)
			{
				disks.push_back(szSingleDrive);
				szSingleDrive += strlen(szSingleDrive) + 1;
			}
		}
	}

	bool IsHiddenFolder(const std::filesystem::path& path)
	{
		DWORD attributes = GetFileAttributesA(path.string().c_str());
		return attributes & FILE_ATTRIBUTE_HIDDEN;
	}

	bool HasExtension(const std::string& targetString, const std::string& extension)
	{
		return targetString.substr(targetString.find_last_of(".") + 1) == extension;
	}

	constexpr static int SEED = 131;
	constexpr static std::size_t MAX_SIZE = SIZE_MAX;
	constexpr static std::size_t SIZE = MAX_SIZE / SEED;
	
	std::size_t HashString(const std::string_view& str)
	{
		std::size_t hash = 0;
		for (int i = 0; i < str.length(); ++i)
		{
			BAMBO_ASSERT_S(hash < MAX_SIZE / SEED)

			hash = (hash * SEED % SIZE) + str[i];
		}
		return hash % SIZE;
	}
}