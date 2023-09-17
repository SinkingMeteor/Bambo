#pragma once
#include "Essentials.h"
#include "Window.h"
#include "Time/TimeManager.h"
#include "WindowManager.h"
#include "AudioManager.h"
#include "RenderManager.h"
#include "Resource/ResourceManager.h"
#include "Components/ComponentFactory.h"
#include "World.h"
#include "Module.h"
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

		void LoadConfigurationFile(WindowSettings& windowSettings);
		void OnWindowResize(uint32 width, uint32 height);
		void Dispose();
	};
}