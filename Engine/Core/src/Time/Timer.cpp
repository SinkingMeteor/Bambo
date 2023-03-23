#include "Time/Timer.h"

namespace Bambo
{
	Timer::Timer() noexcept
	{
		m_lastTime = clock::now();
	}

	float Timer::Restart() noexcept
	{
		const clock::time_point oldTime = m_lastTime;
		m_lastTime = clock::now();
		clock::duration timePassed = m_lastTime - oldTime;
		return std::chrono::duration_cast<std::chrono::seconds>(timePassed).count();
	}

	float Timer::PeekTime() noexcept
	{
		return std::chrono::duration_cast<std::chrono::seconds>(clock::now() - m_lastTime).count();
	}
}

