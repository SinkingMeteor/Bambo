#include "Main/Engine.h"
#include "Utils.h"

namespace
{
	const constexpr float DESIRED_DELTA_TIME = 1.0f / 60.0f;
}

namespace Bambo
{
	void Engine::Initialize()
	{
		WindowSettings settings{ 1280u, 720u, "Hello world!" };
		WindowManager::Get()->Initialize(settings);
		WindowManager::Get()->GetWindow().SetEventCallback(BAMBO_BIND_EVENT_FN(Engine::OnEvent));

		RenderManager::Get()->Initialize(RenderAPI::OpenGL);
		RenderManager::Get()->GetRenderer().SetClearColor(Color{ 0.3f, 0.3f, 0.3f, 1.0f });
		RenderManager::Get()->GetRenderer().SetViewport({ 0u , 0u }, { settings.Width, settings.Height });
		
		AudioManager::Get()->Initialize();

		LoadWorld();
	}

	void Engine::LoadWorld()
	{
		if (m_world)
		{
			m_world->Dispose();
		}
		m_world = std::make_unique<World>();
		m_world->Initialize();
	}

	void Engine::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizedEvent>(BAMBO_BIND_EVENT_FN(Engine::OnWindowResize));
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
		if (m_world)
		{
			m_world->Update(deltaTime);
		}
	}

	bool Engine::OnWindowResize(WindowResizedEvent& windowEvent)
	{
		RendererImplementation& renderer = RenderManager::Get()->GetRenderer();
		renderer.SetViewport(Vector2u{ 0u, 0u }, Vector2u{ windowEvent.GetWidth(), windowEvent.GetHeight() });
		return true;
	}


	void Engine::Dispose()
	{
		AudioManager::Get()->Dispose();
		RenderManager::Get()->Dispose();
		WindowManager::Get()->Dispose();
	}


	void Engine::Render()
	{
		RenderManager::Get()->GetRenderer().Clear();
		if (m_world)
		{
			m_world->Render();
		}
	}
}