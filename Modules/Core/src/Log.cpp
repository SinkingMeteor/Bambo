#include "Log.h"

namespace Bambo
{
	void Logger::Log(const char* logScope, Verbosity verbosity, const char* text)
	{
		int currentVerbosityLevel = static_cast<int>(m_verbosity);
		int expectedVerbosityLevel = static_cast<int>(verbosity);

		if (currentVerbosityLevel < expectedVerbosityLevel) return;

		printf("[%s]: %s\n", logScope, text);
	}

	Verbosity Logger::m_verbosity{ Verbosity::Info };

}