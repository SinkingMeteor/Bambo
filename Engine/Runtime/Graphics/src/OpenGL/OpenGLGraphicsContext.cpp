#include "Essentials.h"
#include "OpenGL/OpenGLGraphicsContext.h"

namespace Bambo
{
	OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* window) :
		m_window(window)
	{}


	void OpenGLGraphicsContext::Initialize()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Logger::Get()->Log("LogWindow", Verbosity::Fatal, "failed to initialize GLAD");
			return;
		}
	}
	void OpenGLGraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}