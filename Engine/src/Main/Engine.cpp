#include "Main/Engine.h"
#include "WindowSettings.h"

namespace
{
	const constexpr float DESIRED_DELTA_TIME = 1.0f / 60.0f;
}

namespace Bambo
{
	void Engine::Initialize()
	{
		WindowSettings settings{ 1280, 720, "Hello world!" };
		WindowManager::Get()->Initialize(settings);

		RenderManager::Get()->Initialize(RenderAPI::OpenGL);
		
		AudioManager::Get()->Initialize();
	}

	int Engine::Run()
	{
		Timer timer{};

		while (!WindowManager::Get()->WantsToClose())
		{
			float passedTime = timer.Restart();

			while (passedTime > DESIRED_DELTA_TIME)
			{
				passedTime -= DESIRED_DELTA_TIME;
				Update(DESIRED_DELTA_TIME);
			}
			Update(passedTime);
			Render();
			WindowManager::Get()->Update();
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
	}
}