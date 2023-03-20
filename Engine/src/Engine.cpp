#include "Engine.h"
namespace Bambo
{
	Engine::Engine() : 
		m_window(WindowSettings{640, 640, "Hello Window!"}),
		m_input(&m_window),
		m_textureProvider(),
		m_shaderProvider(),
		m_testSprite(nullptr)
	{
		Initialize();
	}

	void Engine::Initialize()
	{
		int result = m_window.Initialize();
		BAMBO_ASSERT(result != BAMBO_FALSE, "Window initialization failed");

		std::shared_ptr<Texture2D> texture = m_textureProvider.Load(ToId("TestTexture"), "E:\\projects\\visualstudio\\Bambo\\Engine\\resources\\Textures\\TestImage.png");
		m_shaderProvider.Load(ToId("TestShader"), 
			"E:\\projects\\visualstudio\\Bambo\\Engine\\resources\\Shaders\\VSpriteDefault.txt",
			"E:\\projects\\visualstudio\\Bambo\\Engine\\resources\\Shaders\\FSpriteDefault.txt");
		m_testSprite = std::make_unique<Sprite>(texture);

	}

	int Engine::Run()
	{

		Timer timer{};
		const float deltaTime = 1.0f / 60.0f;

		while (!m_window.WindowShouldClose())
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

		return 0;
	}

	void Engine::Update(float deltaTime)
	{
	}

	void Engine::Render() 
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		RenderConfig config{};
		config.Primitive = PrimitiveType::TriangleStrip;
		config.Shader = m_shaderProvider.Get(ToId("TestShader"));
		m_testSprite->Render(m_window.GetRenderTarget(), config);

		glfwSwapBuffers(m_window.GetRawWindow());
		glfwPollEvents();
	}
}
