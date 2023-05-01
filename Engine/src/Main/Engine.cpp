#include "Main/Engine.h"
#include "WindowSettings.h"
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

		RenderManager::Get()->Initialize(RenderAPI::OpenGL);
		RenderManager::Get()->GetRenderer().SetClearColor(Color{ 0.3f, 0.3f, 0.3f, 1.0f });
		RenderManager::Get()->GetRenderer().SetViewport({ 0u , 0u }, { settings.Width, settings.Height });
		
		AudioManager::Get()->Initialize();

		m_shaderProvider.Load(ToId("TestShader"), BamboPaths::BamboResourcesDir + "Shaders/VSpriteDefault.txt", BamboPaths::BamboResourcesDir + "Shaders/FSpriteDefault.txt");
		SPtr<Texture2D> texture = m_textureProvider.Load(ToId("TestTexture"), BamboPaths::BamboResourcesDir + "Textures/TestImage.png");
		m_sprite = std::make_unique<Sprite>(texture);
		m_camera = std::make_shared<Camera>();
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
		RenderManager::Get()->GetRenderer().Clear();

		RenderConfig config{};
		config.Shader = m_shaderProvider.Get(ToId("TestShader"));
		config.Camera = m_camera;

		m_sprite->Render(RenderManager::Get()->GetRenderer(), config);
	}
}