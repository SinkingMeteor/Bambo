#pragma once
#include "pch.h"
#include "Graphics/RenderTarget.h"
#include "Graphics/Camera.h"
#include "Window/WindowSettings.h"

namespace Bambo 
{
	class BAMBO_API Window
	{
	public:
		Window(const WindowSettings& initialSettings);
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		~Window();

		[[nodiscard]] int Initialize();
		bool WindowShouldClose() const { return glfwWindowShouldClose(m_glfwWindow); }

		const WindowSettings* GetCurrentSettings() const { return &m_windowSettings; }
		int GetWidth() const { return m_windowSettings.Width; }
		int GetHeight() const { return m_windowSettings.Height; }
		GLFWwindow* GetRawWindow() const { return m_glfwWindow; }
		void SetViewportSize(int width, int height);
		void CloseWindow();


	private:
		WindowSettings m_windowSettings;
		GLFWwindow* m_glfwWindow;
	};
}