#include "Engine.h"

namespace Bambo
{
	Engine::Engine(const InitialSettings& settings) :
		m_window(std::make_shared<WindowSettings>(WindowSettings{ settings.WindowWidth, settings.WindowHeight, settings.WindowName })),
		m_renderTarget(m_window.GetSettings())
	{
	}

	Engine::~Engine()
	{
	}

	bool Engine::Initialize()
	{
		int result = m_window.Initialize();
		m_renderTarget.Initialize();

		return result;
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

		glfwSwapBuffers(m_window.GetRawWindow());
		glfwPollEvents();
	}
}