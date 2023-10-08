#include "Engine.h"

#include "Window.h"
#include "Components/Components.h"
#include "Resource/ResourceManager.h"

namespace
{
	const constexpr float DESIRED_DELTA_TIME = 1.0f / 60.0f;
	const uint32 DEFAULT_WIDHT = 1280u;
	const uint32 DEFAULT_HEIGHT = 720u;
	const std::string DEFAULT_TITLE = "Bambo Engine";

	const std::string WINDOW_TITLE_PARAMETER = "windowTitle";
	const std::string WINDOW_WIDTH_PARAMETER = "windowWidth";
	const std::string WINDOW_HEIGHT_PARAMETER = "windowHeight";
}

namespace Bambo
{
	Engine::Engine() :
		m_modules(),
		m_audioManager(),
		m_renderManager(this),
		m_windowManager(),
		m_resourceManager(),
		m_timeManager(),
		m_componentFactory()
	{}

	void Engine::Initialize()
	{
		SingletonManager* singletonManager = SingletonManager::Get();

		Logger* logger = singletonManager->Register<Logger>();
		BAMBO_ASSERT_S(logger)

		m_resourceManager.ScanFiles(BamboPaths::EngineResourcesDir);

		m_componentFactory.Register(CameraComponent::GetTypeID(), []() { return std::make_unique<CameraComponent>(); });
		m_componentFactory.Register(SpriteComponent::GetTypeID(), []() { return std::make_unique<SpriteComponent>(); });
		m_componentFactory.Register(TextComponent::GetTypeID(), []() { return std::make_unique<TextComponent>(); });

		WindowSettings settings{ DEFAULT_WIDHT, DEFAULT_HEIGHT, DEFAULT_TITLE };
		LoadConfigurationFile(settings);

		m_windowManager.Initialize(settings, RenderAPI::OpenGL);
		m_windowManager.GetWindow()->OnWindowResized().Bind(*this, &Engine::OnWindowResize);

		m_renderManager.Initialize(RenderAPI::OpenGL);
		m_renderManager.GetRenderer()->SetClearColor(Color{ 0.3f, 0.3f, 0.3f, 1.0f });
		m_renderManager.GetRenderer()->SetViewport({ 0u , 0u }, { settings.Width, settings.Height });

		m_audioManager.Initialize();
	}

	void Engine::AddModule(UPtr<Module> module)
	{
		module->OnAttach(this);
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
		while (!m_windowManager.WantsToClose())
		{
			float passedTime = m_timeManager.MakeTick();

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

			m_renderManager.OnStartFrame();

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

			m_windowManager.Update();
		}

		Dispose();

		return 0;
	}

	void Engine::LoadConfigurationFile(WindowSettings& windowSettings)
	{
		if (!std::filesystem::exists(BamboPaths::EngineConfigPath))	return;

		std::ifstream stream{ BamboPaths::EngineConfigPath };
		BAMBO_ASSERT_S(!stream.fail());

		nlohmann::json configRoot{};
		stream >> configRoot;

		stream.close();

		if (!configRoot[WINDOW_TITLE_PARAMETER].is_null())
		{
			windowSettings.Title = configRoot[WINDOW_TITLE_PARAMETER];
		}

		if (!configRoot[WINDOW_WIDTH_PARAMETER].is_null())
		{
			windowSettings.Width = configRoot[WINDOW_WIDTH_PARAMETER].get<uint32>();
		}

		if (!configRoot[WINDOW_HEIGHT_PARAMETER].is_null())
		{
			windowSettings.Height = configRoot[WINDOW_HEIGHT_PARAMETER].get<uint32>();
		}

	}

	void Engine::OnWindowResize(uint32 width, uint32 height)
	{
		RendererImplementation* renderer = m_renderManager.GetRenderer();
		Window* window = m_windowManager.GetWindow();

		renderer->SetViewport(Vector2u{ 0u, 0u }, Vector2u{ window->GetWidth(), window->GetHeight() });
	}

	void Engine::Dispose()
	{
		for (size_t i = 0; i < m_modules.size(); ++i)
		{
			m_modules[i]->OnDetach();
		}

		m_audioManager.Dispose();
		m_renderManager.Dispose();
		m_windowManager.Dispose();
	}
}