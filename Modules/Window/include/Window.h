#pragma once
#include "pch.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Utils.h"
#include "WindowSettings.h"
namespace Bambo 
{
	class BAMBO_API Window
	{
	public:
		Window(std::shared_ptr<WindowSettings> initialSettings);
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		~Window();

		[[nodiscard]] int Initialize();
		bool WindowShouldClose() const { return glfwWindowShouldClose(m_glfwWindow); }

		std::shared_ptr<WindowSettings> GetSettings() { return m_windowSettings; }
		int GetWidth() const { return m_windowSettings->Width; }
		int GetHeight() const { return m_windowSettings->Height; }
		GLFWwindow* GetRawWindow() const { return m_glfwWindow; }
		void SetViewportSize(int width, int height);
		void CloseWindow();


	private:
		std::shared_ptr<WindowSettings> m_windowSettings;
		GLFWwindow* m_glfwWindow;
	};
}