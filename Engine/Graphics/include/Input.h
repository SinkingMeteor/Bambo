#pragma once
#include "pch.h"
#include "glm.hpp"
#include "Window.h"

namespace Bambo 
{
	class BAMBO_API Input final
	{
	public:
		Input(Window* window);
		bool IsKeyPressed(int keyCode) const;
		bool IsKeyReleased(int keyCode) const;
		bool IsMouseButtonPressed(int mouseButton) const;
		bool IsMouseButtonReleased(int mouseButton) const;
		glm::vec2 GetMousePosition() const;
	private:
		Window* m_window;
	};
}