#include "Bambo.h"
#include "GLFW/glfw3.h"
namespace Bambo
{
	Engine::Engine() : 
		m_window(WindowSettings{640, 360, "Hello Window!"})
	{
		Initialize();
	}

	void Engine::Initialize()
	{
		m_window.Initialize();
	}

	int Engine::Run()
	{
		return 0;
	}
}
