#include "OpenGL/OpenGLRenderer.h"
namespace Bambo
{
	void OpenGLRenderer::Initialize()
	{
		OpenGLCheck(glEnable(GL_DEPTH_TEST));
		OpenGLCheck(glEnable(GL_BLEND));
		OpenGLCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	void OpenGLRenderer::SetViewport(const Vector2u & origin, const Vector2u & size)
	{
		OpenGLCheck(glViewport(origin.X, origin.Y, size.X, size.Y));
	}

	void OpenGLRenderer::Draw(const SPtr<VertexArrayObject> vao, uint32 vertexAmount)
	{
		vao->Bind();
		OpenGLCheck(glDrawArrays(static_cast<GLenum>(GL_TRIANGLE_STRIP), 0, vertexAmount));
		vao->Unbind();
	}

	void OpenGLRenderer::SetClearColor(const Color & color)
	{
		OpenGLCheck(glClearColor(color.R, color.G, color.B, color.A));
	}

	void OpenGLRenderer::Clear()
	{
		OpenGLCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}
}