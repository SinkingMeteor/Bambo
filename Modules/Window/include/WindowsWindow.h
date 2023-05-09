#pragma once
#include "pch.h"
#include "GraphicsContext.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "WindowEvents.h"

namespace Bambo
{
	class BAMBO_API WindowsWindow final : public Window
	{
		class WindowData
		{
		public:
			uint32 Width{ 1u };
			uint32 Height{ 1u };
			std::string Title{};
			EventCallback Callback{};
		};

	public:
		WindowsWindow(const WindowSettings& settings);
		virtual ~WindowsWindow();

		virtual void Initialize() override;
		virtual uint32 GetWidth() const override { return m_data.Width; }
		virtual uint32 GetHeight() const override { return m_data.Height; }
		virtual bool WindowShouldClose() const override { return glfwWindowShouldClose(m_window); }
		virtual void SetEventCallback(const EventCallback& callback) override { m_data.Callback = callback; }
		virtual void Update() override;
		virtual void* GetWindowPtr() override { return m_window; };
		virtual void CloseWindow() override;

	private:
		GLFWwindow* m_window;
		WindowData m_data;
		std::unique_ptr<GraphicsContext> m_context;
	};
}