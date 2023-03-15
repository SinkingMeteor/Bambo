#pragma once

namespace Bambo 
{
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
}