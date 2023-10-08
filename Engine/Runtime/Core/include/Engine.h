#pragma once
#include "Essentials.h"
#include "Module.h"

#include "WindowManager.h"
#include "AudioManager.h"
#include "RenderManager.h"
#include "Resource/ResourceManager.h"
#include "Time/TimeManager.h"
#include "Components/ComponentFactory.h"

namespace Bambo
{
	class BAMBO_API Engine final
	{
	public:
		Engine();
		Engine(const Engine& engine) = delete;
		Engine& operator=(const Engine& engine) = delete;

		void Initialize();
		int Run();
		void AddModule(UPtr<Module> module);
		void RemoveModule(int32 moduleName);

		AudioManager* GetAudioManager() { return &m_audioManager; }
		RenderManager* GetRenderManager() { return &m_renderManager; }
		WindowManager* GetWindowManager() { return &m_windowManager; }
		ResourceManager* GetResourceManager() { return &m_resourceManager; }
		TimeManager* GetTimeManager() { return &m_timeManager; }
		ComponentFactory* GetComponentFactory() { return &m_componentFactory; }

	private:
		std::vector<UPtr<Module>> m_modules;
		AudioManager m_audioManager;
		RenderManager m_renderManager;
		WindowManager m_windowManager;
		ResourceManager m_resourceManager;
		TimeManager m_timeManager;
		ComponentFactory m_componentFactory;

		void LoadConfigurationFile(WindowSettings& windowSettings);
		void OnWindowResize(uint32 width, uint32 height);
		void Dispose();
	};
}