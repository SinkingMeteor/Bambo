#include "SpriteRenderer.h"

namespace Bambo
{
	SpriteRenderer::SpriteRenderer() :
		Renderer(),
		m_vbo(VertexBufferObject::CreateVertexBufferObject(4 * sizeof(QuadVertex))),
		m_vao(VertexArrayObject::CreateVertexArrayObject()),
		m_basePositions(),
		m_renderVertices()
	{
		m_vbo->SetLayout(std::make_shared<BufferLayout>(std::initializer_list{ ShaderDataType::Float3, ShaderDataType::Float2, ShaderDataType::Float4 }));
		m_vao->AddVertexBufferObject(m_vbo);

		m_basePositions[0] = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };
		m_basePositions[1] = glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f };
		m_basePositions[2] = glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f };
		m_basePositions[3] = glm::vec4{ 1.0f, 1.0f, 0.0f, 1.0f };

		m_renderVertices[0] = QuadVertex{};
		m_renderVertices[1] = QuadVertex{};
		m_renderVertices[2] = QuadVertex{};
		m_renderVertices[3] = QuadVertex{};
	}

	void SpriteRenderer::Render(const SPtr<Sprite> sprite, const RenderConfig& renderConfig)
	{
		if (m_camera.expired()) return;

		RectFloat localBounds = sprite->GetLocalBounds();

		//@TODO: Can be deleted ?
		m_renderVertices[0].Position = glm::vec3{ 0.0f, 0.0f, 0.0f };
		m_renderVertices[1].Position = glm::vec3{ 0.0f, localBounds.Height, 0.0f };
		m_renderVertices[2].Position = glm::vec3{ localBounds.Width, 0.0f, 0.0f };
		m_renderVertices[3].Position = glm::vec3{ localBounds.Width, localBounds.Height, 0.0f };

		RectInt spriteRect = sprite->m_spriteRect;
		RectInt texRect = sprite->m_texture->GetTextureRect();
		float texWidth = static_cast<float>(texRect.Width);
		float texHeight = static_cast<float>(texRect.Height);

		float left = static_cast<float>(spriteRect.Left) / texWidth;
		float right = (left + static_cast<float>(spriteRect.Width)) / texWidth;
		float top = static_cast<float>(spriteRect.Top) / texHeight;
		float bottom = (top + static_cast<float>(spriteRect.Height)) / texHeight;

		m_renderVertices[0].TexCoord = glm::vec2(left, top);
		m_renderVertices[1].TexCoord = glm::vec2(left, bottom);
		m_renderVertices[2].TexCoord = glm::vec2(right, top);
		m_renderVertices[3].TexCoord = glm::vec2(right, bottom);

		m_vbo->SetData(m_renderVertices.data(), SPRITE_VERTEX_COUNT * sizeof(QuadVertex));

		renderConfig.Shader->Use();
		glm::mat4 modelMatrix = renderConfig.WorldMatrix * sprite->GetTransform().GetMatrix();
		renderConfig.Shader->SetMatrix4("model", modelMatrix);
		renderConfig.Shader->SetMatrix4("projView", m_camera.lock()->GetProjViewMatrix());

		if (sprite->m_texture)
		{
			sprite->m_texture->Use();
		}

		RenderInternal(m_vao, SPRITE_VERTEX_COUNT);
	}
}