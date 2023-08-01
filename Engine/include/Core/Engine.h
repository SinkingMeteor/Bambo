#pragma once
#include "Core/Essentials.h"
#include "Window/Window.h"
#include "Core/Time/TimeManager.h"
#include "Window/WindowManager.h"
#include "Audio/AudioManager.h"
#include "Graphics/RenderManager.h"
#include "World/World.h"
#include "Core/Module.h"
namespace Bambo
{
	class BAMBO_API Engine final
	{
	public:
		Engine() = default;
		Engine(const Engine& engine) = delete;
		Engine& operator=(const Engine& engine) = delete;

		void Initialize();
		int Run();
		void AddModule(UPtr<Module> module);
		void RemoveModule(int32 moduleName);
		Window* GetWindow();
	private:
		std::vector<UPtr<Module>> m_modules;

		void OnWindowResize(uint32 width, uint32 height);
		void Dispose();
	};
}