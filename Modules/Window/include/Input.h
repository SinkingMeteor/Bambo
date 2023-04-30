#pragma once
#include "pch.h"
#include "glm.hpp"
#include "GLFW/glfw3.h"

namespace Bambo 
{
	class BAMBO_API Input 
	{
	public:
		Input(GLFWwindow* window);
		bool IsKeyPressed(int keyCode) const;
		bool IsKeyReleased(int keyCode) const;
		bool IsMouseButtonPressed(int mouseButton) const;
		bool IsMouseButtonReleased(int mouseButton) const;
		glm::vec2 GetMousePosition() const;
	private:
		GLFWwindow* m_window;
	};
}