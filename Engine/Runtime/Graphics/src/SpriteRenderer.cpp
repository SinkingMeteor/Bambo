#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Components/SpriteComponent.h"
#include "RenderManager.h"
#include "World.h"
#include "Engine.h"

namespace Bambo
{
	DECLARE_LOG_CATEGORY_STATIC(SpriteRendererLog)

	SpriteRenderer::SpriteRenderer(World* world, SPtr<Shader> defaultShader) :
		Renderer(),
		m_vbo(),
		m_vao(),
		m_ibo(),
		m_renderVertices(),
		m_sprites(),
		m_cachedVertices(),
		m_cachedIndices()
	{
		Engine* engine = world->GetWorldContext()->Engine;
		RenderAPI renderApi = engine->GetRenderManager()->GetCurrentRenderAPI();

		m_vbo = VertexBufferObject::CreateVertexBufferObject(renderApi, SPRITE_VERTEX_COUNT * sizeof(QuadVertex));
		m_vao = VertexArrayObject::CreateVertexArrayObject(renderApi);
		m_ibo = IndexBufferObject::CreateIndexBuffer(renderApi, INDEX_VERTEX_COUNT * sizeof(uint32));

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

	void SpriteRenderer::Render(World* world)
	{
		Engine* engine = world->GetWorldContext()->Engine;
		BAMBO_ASSERT_S(engine);
		RendererImplementation* renderer = engine->GetRenderManager()->GetRenderer();
		BAMBO_ASSERT_S(renderer);

		std::sort(m_sprites.begin(), m_sprites.end(), [](SpriteRenderRequest& r1, SpriteRenderRequest& r2) { return r1.SortingOrder < r2.SortingOrder; });

		const glm::mat4& projectionMatrix = world->GetCameraManager()->GetProjectionMatrix();
		const glm::mat4& viewMatrix = world->GetCameraManager()->GetViewMatrix();

		int32 drawCallCounter = 0;
		int32 savedByBatching = 0;

		for (size_t i = 0; i < m_sprites.size(); ++drawCallCounter)
		{
			SpriteRenderRequest& initSprite = m_sprites[i];
			SPtr<Shader> currentShader = m_sprites[i].Shader;

			if (!currentShader)
			{
				currentShader = m_defaultShader.lock();
			}

			currentShader->Use();
			currentShader->SetMatrix4("ViewMatrix", viewMatrix);
			currentShader->SetMatrix4("ProjectionMatrix", projectionMatrix);

			if (initSprite.Texture)
			{
				initSprite.Texture->Use();
			}

			while (i < m_sprites.size() && initSprite.Texture == m_sprites[i].Texture && initSprite.Shader == m_sprites[i].Shader)
			{
				SpriteRenderRequest sprite = m_sprites[i];

				float width = static_cast<float>(std::abs(sprite.Rect.Width));
				float height = static_cast<float>(std::abs(sprite.Rect.Height));

				m_renderVertices[0].Position = sprite.Model * glm::vec4{ 0.0f, height, 0.0f, 1.0f };
				m_renderVertices[1].Position = sprite.Model * glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };
				m_renderVertices[2].Position = sprite.Model * glm::vec4{ width, height, 0.0f, 1.0f };
				m_renderVertices[3].Position = sprite.Model * glm::vec4{ width, 0.0f, 0.0f, 1.0f };

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
				m_renderVertices[3].TexCoord = glm::vec2(right, bottom);

				std::size_t verticesSize = m_cachedVertices.size();

				m_cachedIndices.push_back(verticesSize + 0);
				m_cachedIndices.push_back(verticesSize + 1);
				m_cachedIndices.push_back(verticesSize + 2);
				m_cachedIndices.push_back(verticesSize + 2);
				m_cachedIndices.push_back(verticesSize + 1);
				m_cachedIndices.push_back(verticesSize + 3);

				m_cachedVertices.push_back(m_renderVertices[0]);
				m_cachedVertices.push_back(m_renderVertices[1]);
				m_cachedVertices.push_back(m_renderVertices[2]);
				m_cachedVertices.push_back(m_renderVertices[3]);

				++i;
				++savedByBatching;
			}

			m_vbo->SetData(m_cachedVertices.data(), m_cachedVertices.size() * sizeof(QuadVertex));
			m_ibo->SetIndices(m_cachedIndices.data(), m_cachedIndices.size());

			renderer->DrawIndexed(m_vao, m_ibo, m_cachedIndices.size(), RenderPrimitive::Triangle);

			m_cachedVertices.clear();
			m_cachedIndices.clear();
			--savedByBatching;
		}
		
		RenderStatistics& renderStatistics = engine->GetRenderManager()->GetRenderStatistics();
		renderStatistics.DrawCalls += drawCallCounter;
		renderStatistics.SavedByBatching += savedByBatching;

		m_sprites.clear();
	}
}