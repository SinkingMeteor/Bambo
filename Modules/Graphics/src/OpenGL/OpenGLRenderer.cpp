#include "OpenGL/OpenGLRenderer.h"

namespace Bambo
{
	OpenGLRenderer::OpenGLRenderer() :
		Renderer(),
		m_vbo(VertexBufferObject::CreateVertexBufferObject(4 * sizeof(Vertex))),
		m_vao(VertexArrayObject::CreateVertexArrayObject())
	{
		m_vbo->SetLayout(std::make_shared<BufferLayout>(std::initializer_list{ ShaderDataType::Float2, ShaderDataType::Float2, ShaderDataType::Float4 }));
		m_vao->AddVertexBufferObject(m_vbo);
	}

	OpenGLRenderer::~OpenGLRenderer()
	{
	}

	void OpenGLRenderer::Initialize()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRenderer::SetViewport(const Vector2u & origin, const Vector2u & size)
	{
		glViewport(origin.X, origin.Y, size.X, size.Y);
	}

	void OpenGLRenderer::Draw(const Vertex * vertices, int amount, const RenderConfig & config)
	{
		if (!config.Camera) return;

		m_vbo->SetData(vertices, amount * sizeof(Vertex));

		if (config.Shader)
		{
			config.Shader->Use();
			config.Shader->SetMatrix4("model", config.ModelMatrix.GetInternalMatrix());
			config.Shader->SetMatrix4("projView", config.Camera->GetProjViewMatrix());
		}

		if (config.Texture)
		{
			glActiveTexture(GL_TEXTURE0);
			config.Texture->Use();
		}

		m_vao->Bind();
		glDrawArrays(static_cast<GLenum>(config.Primitive), 0, amount);
		m_vao->Unbind();

		glUseProgram(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLRenderer::SetClearColor(const Color & color)
	{
		glClearColor(color.R, color.G, color.B, color.A);
	}

	void OpenGLRenderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}