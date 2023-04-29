#include "Main/Engine.h"
#include "WindowSettings.h"
namespace Bambo
{
	Engine::Engine(const InitialSettings& settings)
	{
	}

	Engine::~Engine()
	{
	}

	void Engine::Initialize()
	{
		WindowSettings settings{ 1280, 720, "Hello world!" };
		WindowManager::Get()->Initialize(settings);
		RenderManager::Get()->Initialize();
		AudioManager::Get()->Initialize();
	}

	int Engine::Run()
	{
		Timer timer{};
		const float deltaTime = 1.0f / 60.0f;

		while (!WindowManager::Get()->WantsToClose())
		{
			float passedTime = timer.Restart();

			while (passedTime > deltaTime)
			{
				passedTime -= deltaTime;
				Update(deltaTime);
			}
			Update(passedTime);
			Render();
		}

		Dispose();

		return 0;
	}

	void Engine::Update(float deltaTime)
	{
	}

	void Engine::Dispose()
	{
		AudioManager::Get()->Dispose();
		RenderManager::Get()->Dispose();
		WindowManager::Get()->Dispose();
	}


	void Engine::Render()
	{
		RenderManager::Get()->ClearCanvas();

		WindowManager::Get()->EndFrame();
	}
}