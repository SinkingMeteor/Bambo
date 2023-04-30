#include "WindowsWindow.h"

namespace Bambo
{
	WindowsWindow::WindowsWindow(const WindowSettings& settings) :
		m_window(nullptr),
		m_settings(settings),
		m_context()
	{}

	WindowsWindow::~WindowsWindow()
	{
		if (m_window) glfwDestroyWindow(m_window);

		glfwTerminate();
	}

	void WindowsWindow::Initialize()
	{
		if (glfwInit() == GLFW_FALSE)
		{
			Logger::Log("LogWindow", Verbosity::Fatal, "glfw initialization failed");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(m_settings.Width, m_settings.Height, m_settings.Title.c_str(), nullptr, nullptr);

		if (!m_window)
		{
			Logger::Log("LogWindow", Verbosity::Fatal, "glfw window creation failed");
			return;
		}

		glfwMakeContextCurrent(m_window);

		m_context = GraphicsContext::Create(m_window);
		m_context->Initialize();

		glfwSetWindowUserPointer(m_window, this);
		glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				Window* gameWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
				//@TODO: Make events
				//gameWindow->SetViewportSize(width, height);
			});


		return;
	}


	void WindowsWindow::Update()
	{
		m_context->SwapBuffers();
		glfwPollEvents();
	}

	void WindowsWindow::CloseWindow()
	{
		if (!m_window) return;

		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
}