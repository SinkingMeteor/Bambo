#pragma once
#include "pch.h"
#include "Graphics/RenderTarget.h"
#include "Common/Interfaces/IRenderTarget.h"
namespace Bambo 
{
	struct WindowSettings 
	{
	public:
		int Width;
		int Height;
		std::string Title;
	};

	class BAMBO_API Window : public IRenderTarget
	{
	public:
		Window(const WindowSettings& settings);
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		~Window();

		[[nodiscard]] int Initialize();
		bool WindowShouldClose() const { return glfwWindowShouldClose(m_glfwWindow); }

		int GetWidth() const { return m_windowSettings.Width; }
		int GetHeight() const { return m_windowSettings.Height; }
		GLFWwindow* GetRawWindow() const { return m_glfwWindow; }
		void SetViewportSize(int width, int height);
		void CloseWindow();

		virtual RenderTarget& GetRenderTarget() override { return m_renderTarget; }

	private:
		WindowSettings m_windowSettings;
		GLFWwindow* m_glfwWindow;
		RenderTarget m_renderTarget;
	};
}