#pragma once
#include "Essentials.h"
#include "GraphicsContext.h"
namespace Bambo
{
	class BAMBO_API OpenGLGraphicsContext final : public GraphicsContext
	{
	public:
		OpenGLGraphicsContext(GLFWwindow* window);
		virtual void Initialize() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_window;
	};
}