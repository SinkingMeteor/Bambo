#include "Time/Timer.h"
#include "Utils.h"
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
		float deltaTimeMilli = std::chrono::duration_cast<std::chrono::microseconds>(m_lastTime - oldTime).count();
		float deltaTimeSeconds = deltaTimeMilli / 1'000'000.0f;
		return deltaTimeSeconds;
	}
}

