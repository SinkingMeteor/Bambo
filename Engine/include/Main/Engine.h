#pragma once
#include "engpch.h"
#include "Window.h"
#include "Time/Timer.h"
#include "WindowManager.h"
#include "AudioManager.h"
#include "RenderManager.h"

namespace Bambo
{
	class Engine final
	{
	public:
		Engine() = default;
		Engine(const Engine& engine) = delete;
		Engine& operator=(const Engine& engine) = delete;

		void Initialize();
		int Run();
	private:
		void Update(float deltaTime);
		void Render();
		void Dispose();
	};
}