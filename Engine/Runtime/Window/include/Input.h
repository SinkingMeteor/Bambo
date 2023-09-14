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
		static bool IsKeyPressed(int keyCode);
		static bool IsKeyReleased(int keyCode);
		static bool IsMouseButtonPressed(int mouseButton);
		static bool IsMouseButtonReleased(int mouseButton);
		static glm::vec2 GetMousePosition();
	};
}