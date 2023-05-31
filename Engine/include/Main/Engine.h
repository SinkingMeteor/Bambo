#pragma once
#include "engpch.h"
#include "Window.h"
#include "EngineEvent.h"
#include "TimeManager.h"
#include "WindowManager.h"
#include "AudioManager.h"
#include "RenderManager.h"
#include "WindowEvents.h"
#include "World/World.h"
#include "GUI/GUIWorld.h"
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
	private:
		UPtr<GUIWorld> m_guiWorld;
		std::vector<UPtr<Module>> m_modules;

		void OnEvent(Event& event);
		bool OnWindowResize(WindowResizedEvent& windowEvent);
		void Dispose();
	};
}