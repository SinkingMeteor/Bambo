#pragma once

#include "pch.h"
#include "engpch.h"
#include "Window.h"
#include "RenderTarget.h"
#include "Time/Timer.h"

namespace Bambo
{
	class BAMBO_API InitialSettings
	{
	public:
		int WindowWidth{ 640 };
		int WindowHeight{ 360 };
		std::string WindowName{"Engine"};
	};

	class BAMBO_API Engine final
	{
	public:
		Engine(const InitialSettings& settings);
		Engine(const Engine& engine) = delete;
		Engine& operator=(const Engine& engine) = delete;
		~Engine();

		bool Initialize();
		int Run();
	private:
		Window m_window;
		RenderTarget m_renderTarget;

		void Update(float deltaTime);
		void Render();
	};
}