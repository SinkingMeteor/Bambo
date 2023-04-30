#pragma once
#include "engpch.h"
#include "Window.h"
#include "RenderTarget.h"
#include "Time/Timer.h"
#include "Managers/WindowManager.h"
#include "Managers/AudioManager.h"
#include "Managers/RenderManager.h"

namespace Bambo
{
	class Engine final
	{
	public:
		Engine();
		Engine(const Engine& engine) = delete;
		Engine& operator=(const Engine& engine) = delete;
		~Engine();

		void Initialize();
		int Run();
	private:
		void Update(float deltaTime);
		void Render();
		void Dispose();
	};
}