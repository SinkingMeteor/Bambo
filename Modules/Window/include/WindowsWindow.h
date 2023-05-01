#pragma once
#include "pch.h"
#include "GraphicsContext.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "WindowSettings.h"

namespace Bambo
{
	class BAMBO_API WindowsWindow final : public Window
	{
	public:
		WindowsWindow(const WindowSettings& settings);
		virtual ~WindowsWindow();

		virtual void Initialize() override;
		virtual uint32 GetWidth() const override { return m_settings.Width; }
		virtual uint32 GetHeight() const override { return m_settings.Height; }
		virtual bool WindowShouldClose() const override { return glfwWindowShouldClose(m_window); }
		virtual void Update() override;
		virtual void* GetWindowPtr() override { return m_window; };
		virtual void CloseWindow() override;

	private:
		GLFWwindow* m_window;
		WindowSettings m_settings;
		std::unique_ptr<GraphicsContext> m_context;
	};
}