#include "WindowsWindow.h"
namespace Bambo
{
	WindowsWindow::WindowsWindow(const WindowSettings& settings, RenderAPI renderApi) :
		m_window(nullptr),
		m_width(settings.Width),
		m_height(settings.Height),
		m_title(settings.Title),
		m_context(),
		m_renderApi(renderApi)
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
			Logger::Get()->Log("LogWindow", Verbosity::Fatal, "glfw initialization failed");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

		if (!m_window)
		{
			Logger::Get()->Log("LogWindow", Verbosity::Fatal, "glfw window creation failed");
			return;
		}

		glfwMakeContextCurrent(m_window);

		m_context = GraphicsContext::Create(m_renderApi, m_window);
		m_context->Initialize();

		glfwSetWindowUserPointer(m_window, this);
		glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int32 width, int32 height)
			{
				WindowsWindow* windowsWindow = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
				windowsWindow->SetNewWindowSize(static_cast<uint32>(width), static_cast<uint32>(height));
			});
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

	void WindowsWindow::SetNewWindowSize(uint32 width, uint32 height)
	{
		if (width == 0u || height == 0u) return;

		m_width = width;
		m_height = height;

		m_onWindowResized.Invoke(m_width, m_height);
	}
}