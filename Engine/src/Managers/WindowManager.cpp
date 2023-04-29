#include "Managers/WindowManager.h"

namespace Bambo
{
	void WindowManager::Initialize(const WindowSettings& windowSettings)
	{
		m_window = new Window(windowSettings);
		m_window->Initialize();
	}

	void WindowManager::Dispose()
	{
		delete m_window;
	}

	void WindowManager::EndFrame()
	{
		glfwSwapBuffers(m_window->GetRawWindow());
		glfwPollEvents();
	}
}