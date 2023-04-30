#include "Time/Timer.h"
#include "Utils.h"

namespace
{
	constexpr float MILLI = 1'000.0f;
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
		Duration deltaTimeMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(m_lastTime - oldTime);
		float deltaTimeSeconds = deltaTimeMilliseconds.count() / MILLI;
		return deltaTimeSeconds;
	}
}

