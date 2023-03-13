#pragma once
#include "pch.h"
#include "Core.h"
namespace Bambo 
{
	struct WindowSettings 
	{
	public:
		int Width;
		int Height;
		std::string Title;
	};

	class BAMBO_API Window 
	{
	public:
		Window(const WindowSettings& settings);
		~Window();

		void Initialize();
		bool WindowShouldClose() const { return glfwWindowShouldClose(m_glfwWindow); }

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