#pragma once
#include "Core.h"
#include "pch.h"
#include "Window/Window.h"

namespace Bambo
{
	class BAMBO_API Engine 
	{
	public:
		Engine();
		Engine(const Engine& engine) = delete;
		Engine& operator=(const Engine& engine) = delete;
		[[nodiscard]] int Run();
	private:
		void Initialize();

		Window m_window;
	};
}