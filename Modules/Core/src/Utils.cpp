#include "Utils.h"

namespace Bambo
{
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
}