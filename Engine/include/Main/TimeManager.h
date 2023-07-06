#pragma once
#include "engpch.h"
#include "Singleton.h"
#include "Time/Timer.h"
namespace Bambo
{
	class BAMBO_API TimeManager final : public Singleton<TimeManager>
	{
	public:
		TimeManager() :
			m_mainTimer(),
			m_lastDeltaTime(0.0f),
			m_totalTimePassed(0.0f) {}
		float MakeTick();
		float GetLastDeltaTime() const { return m_lastDeltaTime; }
	private:
		Timer m_mainTimer;
		float m_lastDeltaTime;
		float m_totalTimePassed;
	};
}