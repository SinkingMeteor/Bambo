#pragma once
#include "pch.h"
#include "GraphicsContext.h"
#include "GLFW/glfw3.h"
#include "Window.h"

namespace Bambo
{
	class BAMBO_API WindowsWindow final : public Window
	{
	public:
		WindowsWindow(const WindowSettings& settings);
		virtual ~WindowsWindow();

		virtual void Initialize() override;
		virtual uint32 GetWidth() const override { return m_width; }
		virtual uint32 GetHeight() const override { return m_height; }
		virtual bool WindowShouldClose() const override { return glfwWindowShouldClose(m_window); }
		virtual void Update() override;
		virtual void* GetWindowPtr() override { return m_window; };
		virtual void CloseWindow() override;

		//Don't call. Only for internal use.
		void SetNewWindowSize(uint32 width, uint32 height);
	private:
		GLFWwindow* m_window;
		uint32 m_width{ 1u };
		uint32 m_height{ 1u };
		std::string m_title{};
		std::unique_ptr<GraphicsContext> m_context;
	};
}