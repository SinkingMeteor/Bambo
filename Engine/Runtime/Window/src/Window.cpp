#include "Window.h"
#include "WindowsWindow.h"

namespace Bambo
{
	std::unique_ptr<Window> Window::CreateBamboWindow(const WindowSettings& settings, OSType osType, RenderAPI renderApi)
	{
		switch (osType)
		{
			case OSType::Windows: return std::make_unique<WindowsWindow>(settings, renderApi);
		}

		BAMBO_ASSERT(false, "Unknown os type.");
		return nullptr;
	}
}