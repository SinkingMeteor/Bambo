#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Components/SpriteComponent.h"
#include "World.h"

namespace Bambo
{
	DECLARE_LOG_CATEGORY_STATIC(SpriteRendererLog)

	SpriteRenderer::SpriteRenderer(SPtr<Shader> defaultShader) :
		Renderer(),
		m_vbo(VertexBufferObject::CreateVertexBufferObject(SPRITE_VERTEX_COUNT * sizeof(QuadVertex))),
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
		m_renderVertices[4] = QuadVertex{};
		m_renderVertices[5] = QuadVertex{};
	}

	void SpriteRenderer::EnqueueSpriteToRender(const SpriteRenderRequest& renderRequest)
	{
		m_sprites.push_back(renderRequest);
	}

	void SpriteRenderer::Render(World* world)
	{
		const glm::mat4& projViewMat = world->GetCameraManager()->GetProjViewMatrix();
		std::sort(m_sprites.begin(), m_sprites.end(), [](SpriteRenderRequest& r1, SpriteRenderRequest& r2) { return r1.SortingOrder < r2.SortingOrder; });

		int32 drawCallCounter = 0;
		for (size_t i = 0; i < m_sprites.size(); ++i, ++drawCallCounter)
		{
			SpriteRenderRequest& initSprite = m_sprites[i];
			SPtr<Shader> currentShader = m_sprites[i].Shader;

			if (!currentShader)
			{
				currentShader = m_defaultShader.lock();
			}

			currentShader->Use();
			currentShader->SetMatrix4("projView", projViewMat);

			if (initSprite.Texture)
			{
				initSprite.Texture->Use();
			}

			std::vector<QuadVertex> verticesToDraw{};

			while (i < m_sprites.size() && initSprite.Texture == m_sprites[i].Texture && initSprite.Shader == m_sprites[i].Shader)
			{
				SpriteRenderRequest sprite = m_sprites[i];

				float width = static_cast<float>(std::abs(sprite.Rect.Width));
				float height = static_cast<float>(std::abs(sprite.Rect.Height));

				m_renderVertices[0].Position = sprite.Model * glm::vec4{ 0.0f, height, 0.0f, 1.0f };
				m_renderVertices[1].Position = sprite.Model * glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };
				m_renderVertices[2].Position = sprite.Model * glm::vec4{ width, height, 0.0f, 1.0f };
				m_renderVertices[4].Position = sprite.Model * glm::vec4{ width, 0.0f, 0.0f, 1.0f };

				RectInt texRect = sprite.Texture->GetTextureRect();
				float texWidth = static_cast<float>(texRect.Width);
				float texHeight = static_cast<float>(texRect.Height);

				float left = static_cast<float>(sprite.Rect.Left) / texWidth;
				float top = static_cast<float>(sprite.Rect.Top) / texHeight;

				float right = (static_cast<float>(sprite.Rect.Left) + static_cast<float>(sprite.Rect.Width)) / texWidth;
				float bottom = (static_cast<float>(sprite.Rect.Top) + static_cast<float>(sprite.Rect.Height)) / texHeight;

				m_renderVertices[0].TexCoord = glm::vec2(left, top);
				m_renderVertices[1].TexCoord = glm::vec2(left, bottom);
				m_renderVertices[2].TexCoord = glm::vec2(right, top);
				m_renderVertices[4].TexCoord = glm::vec2(right, bottom);

				m_renderVertices[3] = m_renderVertices[1];
				m_renderVertices[5] = m_renderVertices[2];

				verticesToDraw.push_back(m_renderVertices[0]);
				verticesToDraw.push_back(m_renderVertices[1]);
				verticesToDraw.push_back(m_renderVertices[2]);
				verticesToDraw.push_back(m_renderVertices[3]);
				verticesToDraw.push_back(m_renderVertices[4]);
				verticesToDraw.push_back(m_renderVertices[5]);

				++i;
			}

			m_vbo->SetData(verticesToDraw.data(), verticesToDraw.size() * sizeof(QuadVertex));

			RenderInternal(m_vao, verticesToDraw.size(), RenderPrimitive::Triangle);
		}
		
		Logger::Get()->Log(SpriteRendererLog, Verbosity::Info, "Draw calls: %i", drawCallCounter);
		m_sprites.clear();
	}
}