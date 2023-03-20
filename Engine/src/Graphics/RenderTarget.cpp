#include "Graphics/RenderTarget.h"

namespace Bambo
{
	RenderTarget::RenderTarget() :
		m_vao(0),
		m_vbo(0),
		m_bufferSize(4)
	{
	}

	void RenderTarget::Initialize()
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_bufferSize, NULL, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(float)));
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(float)));
	}

	void RenderTarget::Draw(const Vertex* vertices, int amount, const RenderConfig& config)
	{
		if (m_bufferSize != amount) 
		{
			m_bufferSize = amount;
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * amount, vertices, GL_DYNAMIC_DRAW);
		}
		else
		{
			/*for (size_t i = 0; i < amount; ++i)
			{
				Vertex& vertex = m_vertices[i];
				vertex.Position = vertices[i].Position;
				vertex.TexCoord = vertices[i].TexCoord;
				vertex.Color = vertices[i].Color;
			}*/

			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * amount, vertices);
		}

		if (config.Shader) 
		{
			config.Shader->Use();
			config.Shader->SetMatrix4("model", config.ModelMatrix.GetInternalMatrix());
			config.Shader->SetMatrix4("projection", glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f));
		}

		if (config.Texture)
		{
			glActiveTexture(GL_TEXTURE0);
			config.Texture->Use();
		}

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glDrawArrays(static_cast<GLenum>(config.Primitive), 0, amount);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		Shader::StopUse();
		Texture2D::StopUse();
	}

	void RenderTarget::Draw(IRenderable& renderable, const RenderConfig& config)
	{
		renderable.Render(*this, config);
	}

	RenderTarget::~RenderTarget() 
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		if (m_vbo) glDeleteBuffers(1, &m_vbo);
		if (m_vao) glDeleteVertexArrays(1, &m_vao);
	}
}