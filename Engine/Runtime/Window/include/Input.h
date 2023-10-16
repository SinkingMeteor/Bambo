#pragma once
#include "pch.h"
#include "glm.hpp"
#include "GLFW/glfw3.h"
#include "InputKey.h"
#include "WindowManager.h"
namespace Bambo 
{
	class BAMBO_API Input 
	{
	public:
		Input(WindowManager* windowManager) : m_windowManager(windowManager) {}
		bool IsKeyPressed(InputKey keyCode);
		bool IsKeyReleased(InputKey keyCode);
		bool IsMouseButtonPressed(InputKey mouseButton);
		bool IsMouseButtonReleased(InputKey mouseButton);
		glm::vec2 GetMousePosition();
	private:
		WindowManager* m_windowManager;
	};
}