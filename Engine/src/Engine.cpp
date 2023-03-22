#include "Engine.h"
namespace Bambo
{
	Engine::Engine() : 
		m_window(WindowSettings{640, 640, "Hello Window!"}),
		m_input(&m_window),
		m_textureProvider(),
		m_shaderProvider(),
		m_testSprite(nullptr),
		m_camera(std::make_shared<Camera>(glm::vec2{ 0.0f, 0.0f }, glm::vec2{ 640.0f, 640.0f}))
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
		if (m_input.IsKeyPressed(GLFW_KEY_W))
		{
			m_camera->GetTransform().AddToPosition(glm::vec2(0.0f, -1.0f));
		}
		if (m_input.IsKeyPressed(GLFW_KEY_A))
		{
			m_camera->GetTransform().AddToPosition(glm::vec2(-1.0f, 0.0f));
		}
		if (m_input.IsKeyPressed(GLFW_KEY_S))
		{
			m_camera->GetTransform().AddToPosition(glm::vec2(0.0f, 1.0f));
		}
		if (m_input.IsKeyPressed(GLFW_KEY_D))
		{
			m_camera->GetTransform().AddToPosition(glm::vec2(1.0f, 0.0f));
		}

		glm::vec2 pos = m_camera->GetTransform().GetPosition();
		Log("LogEngine", "Camera pos. X: %f, Y: %f", pos.x, pos.y);
		glm::vec2 center = m_camera->GetCameraCenter();
		Log("LogEngine", "Camera center. X: %f, Y: %f", center.x, center.y);

	}

	void Engine::Render() 
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		RenderConfig config{};
		config.Primitive = PrimitiveType::TriangleStrip;
		config.Shader = m_shaderProvider.Get(ToId("TestShader"));
		config.Camera = m_camera;
		m_testSprite->Render(m_window.GetRenderTarget(), config);

		glfwSwapBuffers(m_window.GetRawWindow());
		glfwPollEvents();
	}
}
