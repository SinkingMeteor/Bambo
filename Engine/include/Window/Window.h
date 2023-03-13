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

		void Update(float deltaTime);
		int GetWidth() const { return m_windowSettings.Width; }
		int GetHeight() const { return m_windowSettings.Height; }

		void CloseWindow();
	private:
		WindowSettings m_windowSettings;
		GLFWwindow* m_glfwWindow;
	};
}