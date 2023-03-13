#include "Engine.h"

namespace Bambo
{
	Engine::Engine() : 
		m_window(WindowSettings{640, 360, "Hello Window!"}),
		m_input(&m_window)
	{
		Initialize();
	}

	void Engine::Initialize()
	{
		int result = m_window.Initialize();
		BAMBO_ASSERT(result != BAMBO_FALSE, "Window initialization failed");
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
