#include "Log.h"

namespace Bambo
{
	Logger::Logger() :
		m_verbosity(Verbosity::Info),
		m_outputFile()
	{

	}

	void Logger::SetOutput(const std::filesystem::path& outputPath)
	{
		if (outputPath.empty())
		{
			Log("LoggerLog", Verbosity::Error, "You are trying to set empty path to logger");
			return;
		}

		if (m_outputFile.is_open())
		{
			m_outputFile.close();
		}

		m_outputFile.open(outputPath, std::ios::out);
		if (m_outputFile.fail())
		{
			Log("LoggerLog", Verbosity::Error, "Can't open or create file for logger");
			return;
		}
	}

	void Logger::Log(const char* logScope, Verbosity verbosity, const char* text)
	{
		if (!CheckVerbosity(verbosity)) return;

		printf("[%s]: %s\n", logScope, text);
	}

	bool Logger::CheckVerbosity(Verbosity verbosity)
	{
		int currentVerbosityLevel = static_cast<int>(m_verbosity);
		int expectedVerbosityLevel = static_cast<int>(verbosity);

		return currentVerbosityLevel >= expectedVerbosityLevel;
	}

}