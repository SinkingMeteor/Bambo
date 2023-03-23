#include "RenderTarget.h"

namespace Bambo
{
	RenderTarget::RenderTarget(const RenderSettings& renderSettings) :
		m_renderSettings(renderSettings),
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

	void RenderTarget::ApplyViewport(const RenderConfig& config)
	{
		const float viewportWidth = m_renderSettings.Width;
		const float viewportHeight = m_renderSettings.Height;

		glViewport(0, 0, viewportWidth, viewportHeight);
	}

	void RenderTarget::Draw(const Vertex* vertices, int amount, const RenderConfig& config)
	{
		if (!config.Camera) return;

		ApplyViewport(config);

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
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		if (m_vbo) glDeleteBuffers(1, &m_vbo);
		if (m_vao) glDeleteVertexArrays(1, &m_vao);
	}
}