#include "Input.h"

namespace Bambo 
{
	Input::Input(Window* window) :
		m_window(window)
	{
	}

	bool Input::IsKeyPressed(int keyCode) const 
	{
		if (!m_window) return false;

		int result = glfwGetKey(m_window->GetRawWindow(), keyCode);
		return result == GLFW_PRESS || result == GLFW_REPEAT;
	}

	bool Input::IsKeyReleased(int keyCode) const
	{
		if (!m_window) return false;

		int result = glfwGetKey(m_window->GetRawWindow(), keyCode);
		return result == GLFW_RELEASE;
	}

	bool Input::IsMouseButtonPressed(int mouseButton) const
	{
		if (!m_window) return false;

		int result = glfwGetMouseButton(m_window->GetRawWindow(), mouseButton);
		return result == GLFW_PRESS || result == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonReleased(int mouseButton) const
	{
		if (!m_window) return false;

		int result = glfwGetMouseButton(m_window->GetRawWindow(), mouseButton);
		return result == GLFW_RELEASE;

	}

	glm::vec2 Input::GetMousePosition() const 
	{
		if (!m_window) return glm::vec2{0.0f};

		double x = 0.0f;
		double y = 0.0f;

		glfwGetCursorPos(m_window->GetRawWindow(), &x, &y);
		return glm::vec2{ static_cast<float>(x), static_cast<float>(y) };
	}
}
