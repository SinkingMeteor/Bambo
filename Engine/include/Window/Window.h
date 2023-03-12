#pragma once
#include "pch.h"
#include "Core.h"
namespace Bambo 
{
	class BAMBO_API Window 
	{
	public:
		Window();
		void Initialize();
		~Window();
	private:
		GLFWwindow* m_glfwWindow;
	};
}