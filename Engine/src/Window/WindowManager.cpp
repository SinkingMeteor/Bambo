#include "Window/WindowManager.h"

namespace Bambo
{
	void WindowManager::Initialize(const WindowSettings& windowSettings)
	{
		m_window = Window::CreateBamboWindow(windowSettings, OSType::Windows);
		m_window->Initialize();
	}

	void WindowManager::Dispose()
	{
		m_window->CloseWindow();
	}
}