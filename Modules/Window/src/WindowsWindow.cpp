#include "WindowsWindow.h"

namespace Bambo
{
	WindowsWindow::WindowsWindow(const WindowSettings& settings) :
		m_window(nullptr),
		m_data(),
		m_context()
	{
		m_data.Width = settings.Width; 
		m_data.Height = settings.Height; 
		m_data.Title = settings.Title;
	}

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

		m_window = glfwCreateWindow(m_data.Width, m_data.Height, m_data.Title.c_str(), nullptr, nullptr);

		if (!m_window)
		{
			Logger::Log("LogWindow", Verbosity::Fatal, "glfw window creation failed");
			return;
		}

		glfwMakeContextCurrent(m_window);

		m_context = GraphicsContext::Create(m_window);
		m_context->Initialize();

		glfwSetWindowUserPointer(m_window, &m_data);
		glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int32 width, int32 height)
			{
				WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				windowData->Width = static_cast<uint32>(width);
				windowData->Height = static_cast<uint32>(height);

				WindowResizedEvent windowEvent{ windowData->Width, windowData->Height };
				windowData->Callback(windowEvent);
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
		glfwSetWindowShouldClose(m_window, true);
	}
}