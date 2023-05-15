#include "Time/Timer.h"
#include "Utils.h"

namespace
{
	constexpr float MICRO = 1'000'000.0f;
}

namespace Bambo
{
	Timer::Timer() noexcept
	{
		m_lastTime = Clock::now();
	}

	float Timer::Restart() noexcept
	{
		const Clock::time_point oldTime = m_lastTime;
		m_lastTime = Clock::now();
		Duration deltaTimeMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(m_lastTime - oldTime);
		float deltaTimeSeconds = deltaTimeMicroseconds.count() / MICRO;
		return deltaTimeSeconds;
	}
}

