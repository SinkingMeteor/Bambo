#include "Window/Window.h"

namespace Bambo 
{
	Window::Window() :
		m_glfwWindow(nullptr)
	{

	}

	void Window::Initialize() 
	{
		if (glfwInit() == GLFW_FALSE) 
		{
			printf("glfw initialization failed");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_glfwWindow = glfwCreateWindow(640, 360, "Hello window", nullptr, nullptr);

		if (!m_glfwWindow) 
		{
			printf("glfw window creation failed");
			return;
		}

		glfwMakeContextCurrent(m_glfwWindow);
	}

	Window::~Window() 
	{
		if (m_glfwWindow) glfwDestroyWindow(m_glfwWindow);

		glfwTerminate();
	}
}