#include "WindowManager.h"

namespace Bambo
{
	void WindowManager::Initialize(const WindowSettings& windowSettings, RenderAPI renderApi)
	{
		m_window = Window::CreateBamboWindow(windowSettings, OSType::Windows, renderApi);
		m_window->Initialize();
	}

	void WindowManager::Dispose()
	{
		m_window->CloseWindow();
	}
}