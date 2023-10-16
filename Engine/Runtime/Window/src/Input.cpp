#include "Input.h"

namespace Bambo 
{
	bool Input::IsKeyPressed(InputKey keyCode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_windowManager->GetWindow()->GetWindowPtr());

		int result = glfwGetKey(window, static_cast<int>(keyCode));
		return result == GLFW_PRESS || result == GLFW_REPEAT;
	}

	bool Input::IsKeyReleased(InputKey keyCode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_windowManager->GetWindow()->GetWindowPtr());

		int result = glfwGetKey(window, static_cast<int>(keyCode));
		return result == GLFW_RELEASE;
	}

	bool Input::IsMouseButtonPressed(InputKey mouseButton)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_windowManager->GetWindow()->GetWindowPtr());

		int result = glfwGetMouseButton(window, static_cast<int>(mouseButton));
		return result == GLFW_PRESS || result == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonReleased(InputKey mouseButton)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_windowManager->GetWindow()->GetWindowPtr());

		int result = glfwGetMouseButton(window, static_cast<int>(mouseButton));
		return result == GLFW_RELEASE;

	}

	glm::vec2 Input::GetMousePosition()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_windowManager->GetWindow()->GetWindowPtr());

		double x = 0.0f;
		double y = 0.0f;

		glfwGetCursorPos(window, &x, &y);
		return glm::vec2{ static_cast<float>(x), static_cast<float>(y) };
	}
}
