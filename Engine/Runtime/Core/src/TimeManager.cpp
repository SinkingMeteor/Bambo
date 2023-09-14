#include "Time/TimeManager.h"

namespace Bambo
{
	float TimeManager::MakeTick()
	{
		m_lastDeltaTime = m_mainTimer.Restart();
		m_totalTimePassed += m_lastDeltaTime;
		return m_lastDeltaTime;
	}
}