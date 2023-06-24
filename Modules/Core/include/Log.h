#pragma once
#include "pch.h"
#include "Singleton.h"

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

	class BAMBO_API Logger final : public Singleton<Logger>
	{
	public:
		Logger();
		void SetOutput(const std::filesystem::path& outputPath);
		template<typename... Args>
		void Log(const char* logScope, Verbosity verbosity, const char* format, Args&&...args);
		template<typename... Args>
		void Log(const char* logScope, Verbosity verbosity, Args&&...args);
		void Log(const char* logScope, Verbosity verbosity, const char* text);
		void SetVerbosityLevel(Verbosity level) { m_verbosity = level; }
	private:
		Verbosity m_verbosity;
		std::ofstream m_outputFile;

		template<typename... Args>
		void LogToFile(const char* logScope, const char* text, const char* format);
		bool CheckVerbosity(Verbosity verbosity);
	};

	template<typename... Args>
	void Logger::Log(const char* logScope, Verbosity verbosity, const char* format, Args&&...args)
	{
		if (!CheckVerbosity(verbosity)) return;

		printf("[%s]: ", logScope);
		printf(format, std::forward<Args>(args)...);
		printf("\n");
	}

	template<typename... Args>
	void Logger::Log(const char* logScope, Verbosity verbosity, Args&&...args)
	{
		if (!CheckVerbosity(verbosity)) return;

		std::ostream tempStream{};

		tempStream << std::forward<Arg>(arg);
		((tempStream << std::forward<Args>(args)), ...);
		tempStream << std::endl;

		std::cout << tempStream;
		
		if (m_outputFile.is_open())
		{
			m_outputFile << tempStream;
		}
	}
}
