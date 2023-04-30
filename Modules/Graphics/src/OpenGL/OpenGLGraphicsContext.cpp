#include "OpenGLGraphicsContext.h"

namespace Bambo
{
	OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* window) :
		m_window()
	{}


	void OpenGLGraphicsContext::Initialize()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Logger::Log("LogWindow", Verbosity::Fatal, "failed to initialize GLAD");
			return;
		}
	}
	void OpenGLGraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}