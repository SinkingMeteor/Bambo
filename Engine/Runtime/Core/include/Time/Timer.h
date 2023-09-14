#pragma once
#include "pch.h"

namespace Bambo 
{
	class BAMBO_API Timer final
	{
	public:
		Timer() noexcept;
		float Restart() noexcept;
	private:
		using Clock = std::chrono::high_resolution_clock;
		using Duration = std::chrono::duration<float, std::micro>;

		Clock::time_point m_lastTime;
	};
}