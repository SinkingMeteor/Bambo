#pragma once
#include "Core.h"
#include "pch.h"
#include "Window/Window.h"
#include "Input/Input.h"
#include "Common/Time/Timer.h"
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
		void Update(float deltaTime);
		void Render();

		Window m_window;
		Input m_input;
	};
}