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
		WindowSettings settings{ 1280u, 720u, "Bambo Engine" };
		WindowManager::Get()->Initialize(settings);

		WindowManager::Get()->GetWindow().OnWindowResized().Bind(*this, &Engine::OnWindowResize);

		RenderManager::Get()->Initialize(RenderAPI::OpenGL);
		RenderManager::Get()->GetRenderer().SetClearColor(Color{ 0.3f, 0.3f, 0.3f, 1.0f });
		RenderManager::Get()->GetRenderer().SetViewport({ 0u , 0u }, { settings.Width, settings.Height });

		m_guiWorld = std::make_unique<GUIWorld>();
		m_guiWorld->Initialize();
		
		AudioManager::Get()->Initialize();
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

			m_guiWorld->StartFrame();
			for (size_t i = 0; i < m_modules.size(); ++i)
			{
				m_modules[i]->OnGUI();
			}
			m_guiWorld->EndFrame();

			WindowManager::Get()->Update();
		}

		Dispose();

		return 0;
	}


	void Engine::OnWindowResize(uint32 width, uint32 height)
	{
		RendererImplementation& renderer = RenderManager::Get()->GetRenderer();
		Window& window = WindowManager::Get()->GetWindow();
		renderer.SetViewport(Vector2u{ 0u, 0u }, Vector2u{ window.GetWidth(), window.GetHeight() });
	}

	void Engine::Dispose()
	{
		for (size_t i = 0; i < m_modules.size(); ++i)
		{
			m_modules[i]->OnDetach();
		}

		AudioManager::Get()->Dispose();
		m_guiWorld->Dispose();
		RenderManager::Get()->Dispose();
		WindowManager::Get()->Dispose();
	}
}