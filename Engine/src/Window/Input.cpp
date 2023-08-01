#include "Window/Input.h"

namespace Bambo 
{
	bool Input::IsKeyPressed(int keyCode)
	{

		GLFWwindow* window = static_cast<GLFWwindow*>(WindowManager::Get()->GetWindow().GetWindowPtr());

		int result = glfwGetKey(window, keyCode);
		return result == GLFW_PRESS || result == GLFW_REPEAT;
	}

	bool Input::IsKeyReleased(int keyCode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(WindowManager::Get()->GetWindow().GetWindowPtr());

		int result = glfwGetKey(window, keyCode);
		return result == GLFW_RELEASE;
	}

	bool Input::IsMouseButtonPressed(int mouseButton)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(WindowManager::Get()->GetWindow().GetWindowPtr());

		int result = glfwGetMouseButton(window, mouseButton);
		return result == GLFW_PRESS || result == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonReleased(int mouseButton)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(WindowManager::Get()->GetWindow().GetWindowPtr());

		int result = glfwGetMouseButton(window, mouseButton);
		return result == GLFW_RELEASE;

	}

	glm::vec2 Input::GetMousePosition()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(WindowManager::Get()->GetWindow().GetWindowPtr());

		double x = 0.0f;
		double y = 0.0f;

		glfwGetCursorPos(window, &x, &y);
		return glm::vec2{ static_cast<float>(x), static_cast<float>(y) };
	}
}
