#pragma once
#include "engpch.h"
#include "Window.h"
#include "EngineEvent.h"
#include "Time/Timer.h"
#include "WindowManager.h"
#include "AudioManager.h"
#include "RenderManager.h"
#include "TextureProvider.h"
#include "ShaderProvider.h"
#include "SpriteRenderer.h"
#include "WindowEvents.h"
#include "Camera.h"
#include "World/World.h"
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
	private:
		UPtr<World> m_world;

		void LoadWorld();
		void OnEvent(Event& event);
		bool OnWindowResize(WindowResizedEvent& windowEvent);
		void Update(float deltaTime);
		void Render();
		void Dispose();
	};
}