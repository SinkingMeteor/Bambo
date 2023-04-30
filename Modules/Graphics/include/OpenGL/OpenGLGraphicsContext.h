#pragma once
#include "pch.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GraphicsContext.h"
#include "Log.h"

namespace Bambo
{
	class BAMBO_API OpenGLGraphicsContext : public GraphicsContext
	{
	public:
		OpenGLGraphicsContext(GLFWwindow* window);
		virtual void Initialize() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_window;
	};
}