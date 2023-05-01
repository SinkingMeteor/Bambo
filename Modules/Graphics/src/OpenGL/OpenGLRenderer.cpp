#include "OpenGL/OpenGLRenderer.h"

namespace Bambo
{
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Matrix3f:     return GL_FLOAT;
		case ShaderDataType::Matrix4f:     return GL_FLOAT;
		case ShaderDataType::Integer:      return GL_INT;
		case ShaderDataType::Integer2:     return GL_INT;
		case ShaderDataType::Integer3:     return GL_INT;
		case ShaderDataType::Integer4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		BAMBO_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	static void ApplyLayout(const Bambo::BufferLayout& layout)
	{
		size_t counter = 0;
		for (Bambo::CLayoutIter it = layout.Begin(); it != layout.End(); ++it)
		{
			glEnableVertexAttribArray(counter);
			ShaderDataType type = it->GetType();
			glVertexAttribPointer(counter, GetComponentCount(type), ShaderDataTypeToOpenGLType(type), GL_FALSE, layout.GetStride(), (void*)it->GetOffset());
			++counter;
		}
	}

	OpenGLRenderer::OpenGLRenderer() :
		Renderer(),
		m_vao(0),
		m_vbo(0),
		m_bufferSize(4),
		m_layout{ ShaderDataType::Float2, ShaderDataType::Float2, ShaderDataType::Float4 }
	{}

	OpenGLRenderer::~OpenGLRenderer()
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		if (m_vbo) glDeleteBuffers(1, &m_vbo);
		if (m_vao) glDeleteVertexArrays(1, &m_vao);
	}

	void OpenGLRenderer::Initialize()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_bufferSize, NULL, GL_DYNAMIC_DRAW);

		ApplyLayout(m_layout);
	}

	void OpenGLRenderer::SetViewport(const Vector2u & origin, const Vector2u & size)
	{
		glViewport(origin.X, origin.Y, size.X, size.Y);
	}

	void OpenGLRenderer::Draw(const Vertex * vertices, int amount, const RenderConfig & config)
	{
		if (!config.Camera) return;

		if (m_bufferSize != amount)
		{
			m_bufferSize = amount;
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * amount, vertices, GL_DYNAMIC_DRAW);
		}
		else
		{
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * amount, vertices);
		}

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

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glDrawArrays(static_cast<GLenum>(config.Primitive), 0, amount);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

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