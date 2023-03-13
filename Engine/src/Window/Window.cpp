#include "Window/Window.h"

namespace Bambo 
{
	Window::Window(const WindowSettings& settings) :
		m_windowSettings(settings),
		m_glfwWindow(nullptr)
	{

	}

	int Window::Initialize() 
	{
		if (glfwInit() == GLFW_FALSE) 
		{
			printf("glfw initialization failed");
			return BAMBO_FALSE;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_glfwWindow = glfwCreateWindow(m_windowSettings.Width, m_windowSettings.Height, m_windowSettings.Title.c_str(), nullptr, nullptr);

		if (!m_glfwWindow) 
		{
			printf("glfw window creation failed");
			return BAMBO_FALSE;
		}

		glfwMakeContextCurrent(m_glfwWindow);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			printf("failed to initialize GLAD");
			return BAMBO_FALSE;
		}

		glfwSetWindowUserPointer(m_glfwWindow, this);
		glfwSetFramebufferSizeCallback(m_glfwWindow, [](GLFWwindow* window, int width, int height) 
		{
			Window* gameWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			gameWindow->SetViewportSize(width, height);
		});

		return BAMBO_TRUE;
	}

	void Window::SetViewportSize(int width, int height)
	{
		m_windowSettings.Width = width;
		m_windowSettings.Height = height;

		glViewport(0, 0, width, height);
	}

	void Window::CloseWindow()
	{
		if (!m_glfwWindow) return;

		glfwDestroyWindow(m_glfwWindow);
		m_glfwWindow = nullptr;
	}

	Window::~Window() 
	{
		if (m_glfwWindow) glfwDestroyWindow(m_glfwWindow);

		glfwTerminate();
	}
}