#pragma once
#include "pch.h"
#include "glm.hpp"
#include "GLFW/glfw3.h"
#include "WindowManager.h"
namespace Bambo 
{
	class BAMBO_API Input 
	{
	public:
		Input(WindowManager* windowManager) : m_windowManager(windowManager) {}
		bool IsKeyPressed(int keyCode);
		bool IsKeyReleased(int keyCode);
		bool IsMouseButtonPressed(int mouseButton);
		bool IsMouseButtonReleased(int mouseButton);
		glm::vec2 GetMousePosition();
	private:
		WindowManager* m_windowManager;
	};
}