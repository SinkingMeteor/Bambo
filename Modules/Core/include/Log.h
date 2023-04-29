#pragma once
#include "pch.h"

namespace Bambo
{
	enum class Verbosity
	{
		Fatal = 0,
		Error,
		Warning,
		Info,
		Default,
		Verbose
	};

	class BAMBO_API Logger
	{
	public:
		template<typename... Args>
		static void Log(const char* logScope, Verbosity verbosity, const char* format, Args&&...args);
		static void Log(const char* logScope, Verbosity verbosity, const char* text);
		static void SetVerbosityLevel(Verbosity level) { m_verbosity = level; }
	private:
		static Verbosity m_verbosity;
	};

	template<typename... Args>
	void Logger::Log(const char* logScope, Verbosity verbosity, const char* format, Args&&...args)
	{
		int currentVerbosityLevel = static_cast<int>(m_verbosity);
		int expectedVerbosityLevel = static_cast<int>(verbosity);

		if (currentVerbosityLevel < expectedVerbosityLevel) return;

		printf("[%s]: ", logScope);
		printf(format, std::forward<Args>(args)...);
		printf("\n");
	}

}