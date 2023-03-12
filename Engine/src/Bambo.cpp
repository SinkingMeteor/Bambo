#include "Bambo.h"
#include "GLFW/glfw3.h"
namespace Bambo
{
	Engine::Engine() : 
		m_window()
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
