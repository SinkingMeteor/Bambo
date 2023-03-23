#pragma once
#include "pch.h"

namespace Bambo 
{
	class BAMBO_API Timer final
	{
	public:
		Timer() noexcept;
		float Restart() noexcept;
		float PeekTime() noexcept;
	private:
		using clock = std::chrono::steady_clock;

		clock::time_point m_lastTime;
	};
}