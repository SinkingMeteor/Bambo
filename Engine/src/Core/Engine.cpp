#include "Core/Engine.h"

namespace
{
	const constexpr float DESIRED_DELTA_TIME = 1.0f / 60.0f;
}

namespace Bambo
{
	void Engine::Initialize()
	{
		SingletonManager* singletonManager = SingletonManager::Get();

		Logger* logger = singletonManager->Register<Logger>();
		BAMBO_ASSERT_S(logger)
		TimeManager* timeManager = singletonManager->Register<TimeManager>();
		BAMBO_ASSERT_S(timeManager)

		WindowSettings settings{ 1280u, 720u, "Bambo Engine" };

		WindowManager* windowManager = singletonManager->Register<WindowManager>();
		RenderManager* renderManager = singletonManager->Register<RenderManager>();

		BAMBO_ASSERT_S(windowManager)
		BAMBO_ASSERT_S(renderManager)

		windowManager->Initialize(settings);
		windowManager->GetWindow().OnWindowResized().Bind(*this, &Engine::OnWindowResize);

		renderManager->Initialize(RenderAPI::OpenGL);
		renderManager->GetRenderer()->SetClearColor(Color{ 0.3f, 0.3f, 0.3f, 1.0f });
		renderManager->GetRenderer()->SetViewport({ 0u , 0u }, { settings.Width, settings.Height });

		AudioManager* audioManager = singletonManager->Register<AudioManager>();
		BAMBO_ASSERT_S(audioManager)
		audioManager->Initialize();
	}

	Window* Engine::GetWindow()
	{
		return &WindowManager::Get()->GetWindow();
	}

	void Engine::AddModule(UPtr<Module> module)
	{
		module->OnAttach();
		m_modules.emplace_back(std::move(module));
	}

	void Engine::RemoveModule(int32 moduleName)
	{
		using It = std::vector<UPtr<Module>>::iterator;

		It it = std::remove_if(m_modules.begin(), m_modules.end(), [&moduleName](const UPtr<Module>& module) { return module->GetModuleName() == moduleName; });
		m_modules.erase(it, m_modules.end());
	}

	int Engine::Run()
	{

		while (!WindowManager::Get()->WantsToClose())
		{
			float passedTime = TimeManager::Get()->MakeTick();

			while (passedTime > DESIRED_DELTA_TIME)
			{
				passedTime -= DESIRED_DELTA_TIME;

				for (size_t i = 0; i < m_modules.size(); ++i)
				{
					m_modules[i]->OnUpdate(DESIRED_DELTA_TIME);
				}
			}

			for (size_t i = 0; i < m_modules.size(); ++i)
			{
				m_modules[i]->OnUpdate(DESIRED_DELTA_TIME);
			}

			for (size_t i = 0; i < m_modules.size(); ++i)
			{
				m_modules[i]->OnRender();
			}

			for (size_t i = 0; i < m_modules.size(); ++i)
			{
				m_modules[i]->OnGUIStart();
			}

			for (size_t i = 0; i < m_modules.size(); ++i)
			{
				m_modules[i]->OnGUI();
			}

			for (size_t i = 0; i < m_modules.size(); ++i)
			{
				m_modules[i]->OnGUIEnd();
			}

			WindowManager::Get()->Update();
		}

		Dispose();

		return 0;
	}


	void Engine::OnWindowResize(uint32 width, uint32 height)
	{
		RendererImplementation* renderer = RenderManager::Get()->GetRenderer();
		Window& window = WindowManager::Get()->GetWindow();
		renderer->SetViewport(Vector2u{ 0u, 0u }, Vector2u{ window.GetWidth(), window.GetHeight() });
	}

	void Engine::Dispose()
	{
		for (size_t i = 0; i < m_modules.size(); ++i)
		{
			m_modules[i]->OnDetach();
		}

		AudioManager::Get()->Dispose();
		RenderManager::Get()->Dispose();
		WindowManager::Get()->Dispose();
	}
}