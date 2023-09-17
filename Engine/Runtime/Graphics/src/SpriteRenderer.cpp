#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Components/SpriteComponent.h"

namespace Bambo
{
	SpriteRenderer::SpriteRenderer(SPtr<Shader> defaultShader) :
		Renderer(),
		m_vbo(VertexBufferObject::CreateVertexBufferObject(4 * sizeof(QuadVertex))),
		m_vao(VertexArrayObject::CreateVertexArrayObject()),
		m_renderVertices(),
		m_sprites()
	{
		m_defaultShader = defaultShader;

		BAMBO_ASSERT(!m_defaultShader.expired() && m_defaultShader.lock(), "Default shader wasn't loaded")

		m_vbo->SetLayout(std::make_shared<BufferLayout>(std::initializer_list{ ShaderDataType::Float3, ShaderDataType::Float2, ShaderDataType::Float4 }));
		m_vao->AddVertexBufferObject(m_vbo);

		m_renderVertices[0] = QuadVertex{};
		m_renderVertices[1] = QuadVertex{};
		m_renderVertices[2] = QuadVertex{};
		m_renderVertices[3] = QuadVertex{};
	}

	void SpriteRenderer::EnqueueSpriteToRender(const SpriteRenderRequest& renderRequest)
	{
		m_sprites.push_back(renderRequest);
	}

	void SpriteRenderer::Render(std::vector<glm::mat4>& globalTransforms)
	{
		std::sort(m_sprites.begin(), m_sprites.end(), [](SpriteRenderRequest& r1, SpriteRenderRequest& r2) { return r1.SortingOrder < r2.SortingOrder; });

		for (size_t i = 0; i < m_sprites.size(); ++i)
		{
			const RectInt& rect = m_sprites[i].Texture->GetTextureRects()[m_sprites[i].RectIndex];
			Render(m_sprites[i].Texture, rect, globalTransforms[m_sprites[i].GlobalPosIndex], m_projViewMatrix);
		}

		m_sprites.clear();
	}

	void SpriteRenderer::Render(const SPtr<Texture2D> texture, const RectInt& spriteRect, const glm::mat4& transform, const glm::mat4& projViewMatrix)
	{
		SPtr<Shader> currentShader{m_defaultShader.lock()};

		float width = static_cast<float>(std::abs(spriteRect.Width));
		float height = static_cast<float>(std::abs(spriteRect.Height));

		RectFloat localBounds(Vector2f{ 0.f, 0.f }, Vector2f{ width, height });

		m_renderVertices[0].Position = glm::vec3{ 0.0f, 0.0f, 0.0f };
		m_renderVertices[1].Position = glm::vec3{ 0.0f, localBounds.Height, 0.0f };
		m_renderVertices[2].Position = glm::vec3{ localBounds.Width, 0.0f, 0.0f };
		m_renderVertices[3].Position = glm::vec3{ localBounds.Width, localBounds.Height, 0.0f };

		RectInt texRect = texture->GetTextureRect();
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

		currentShader->Use();
		currentShader->SetMatrix4("model", transform);
		currentShader->SetMatrix4("projView", projViewMatrix);

		if (texture)
		{
			texture->Use();
		}

		RenderInternal(m_vao, SPRITE_VERTEX_COUNT);
	}
}