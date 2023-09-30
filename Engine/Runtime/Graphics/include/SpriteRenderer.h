#pragma once
#include "Essentials.h"
#include "Renderer.h"
#include "RendererImplementation.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "BufferLayout.h"
#include "RenderConfig.h"
#include "Texture2D.h"
#include "ShaderProvider.h"

namespace Bambo
{
	class SpriteComponent;
	class World;

	struct SpriteRenderRequest
	{
	public:
		SPtr<Texture2D> Texture;
		SPtr<Shader> Shader;
		RectInt Rect;
		glm::mat4 Model;
		int32 SortingOrder;
	};

	class BAMBO_API SpriteRenderer final : public Renderer
	{
	public:
		SpriteRenderer(SPtr<Shader> defaultShader);
		void EnqueueSpriteToRender(const SpriteRenderRequest& renderRequest);
		void Render(World* world);
	private:
		static constexpr uint32 SPRITE_VERTEX_COUNT = 4u;

		SPtr<VertexBufferObject> m_vbo;
		SPtr<VertexArrayObject> m_vao;
		std::array<QuadVertex, SPRITE_VERTEX_COUNT> m_renderVertices;
		std::vector<SpriteRenderRequest> m_sprites;

		void Render(SpriteRenderRequest& sprite, const glm::mat4& projViewMatrix);
	};
}