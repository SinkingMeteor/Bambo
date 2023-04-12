#include "Engine.h"

Engine::Engine() :
	m_window(std::make_shared<Bambo::WindowSettings>(Bambo::WindowSettings{ 1280u, 720u, "Hello Window!" })),
	m_input(&m_window),
	m_textureProvider(),
	m_shaderProvider(),
	m_audioProvider(),
	m_renderTarget(m_window.GetSettings()),
	m_testSprite(nullptr),
	m_camera(std::make_shared<Bambo::Camera>(glm::vec2{ 0.0f, 0.0f }, glm::vec2{ 640.0f, 360.0f })),
	m_audioDevice(std::make_shared<Bambo::AudioDevice>()),
	m_audioListener(m_audioDevice),
	m_audioSource()
{
	Initialize();
}

Engine::~Engine()
{
	if (m_audioSource.IsPlaying())
	{
		m_audioSource.Stop();
	}
}

void Engine::Initialize()
{
	int result = m_window.Initialize();

	m_renderTarget.Initialize();

	std::string projectPath = std::string{ BAMBO_RESOURCE_DIR };

	std::shared_ptr<Bambo::Texture2D> texture = m_textureProvider.Load(Bambo::ToId("TestTexture"), projectPath + "Textures/TestImage.png");
	m_shaderProvider.Load(Bambo::ToId("TestShader"), projectPath + "Shaders/VSpriteDefault.txt", projectPath + "Shaders/FSpriteDefault.txt");
	std::shared_ptr<Bambo::Audio> audio = m_audioProvider.Load(Bambo::ToId("TestAudio"), projectPath + "Audio/file_example.wav");

	m_testSprite = std::make_unique<Bambo::Sprite>(texture);
	m_audioSource.SetAudio(audio);
	m_audioSource.Play();
}

int Engine::Run()
{
	Bambo::Timer timer{};
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
	float speed = 50.0f;
	if (m_input.IsKeyPressed(GLFW_KEY_W))
	{
		m_camera->GetTransform().AddToPosition(glm::vec2(0.0f, -1.0f) * deltaTime * speed);
	}
	if (m_input.IsKeyPressed(GLFW_KEY_A))
	{
		m_camera->GetTransform().AddToPosition(glm::vec2(-1.0f, 0.0f) * deltaTime * speed);
	}
	if (m_input.IsKeyPressed(GLFW_KEY_S))
	{
		m_camera->GetTransform().AddToPosition(glm::vec2(0.0f, 1.0f) * deltaTime * speed);
	}
	if (m_input.IsKeyPressed(GLFW_KEY_D))
	{
		m_camera->GetTransform().AddToPosition(glm::vec2(1.0f, 0.0f) * deltaTime * speed);
	}
}

void Engine::Render() 
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Bambo::RenderConfig config{};
	config.Primitive = Bambo::PrimitiveType::TriangleStrip;
	config.Shader = m_shaderProvider.Get(Bambo::ToId("TestShader"));
	config.Camera = m_camera;
	m_testSprite->Render(m_renderTarget, config);

	glfwSwapBuffers(m_window.GetRawWindow());
	glfwPollEvents();
}
