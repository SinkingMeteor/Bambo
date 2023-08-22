#pragma once
#include "Core/Essentials.h"
#include "Graphics/Renderer.h"
#include "Graphics/RendererImplementation.h"
#include "Graphics/VertexArrayObject.h"
#include "Graphics/VertexBufferObject.h"
#include "Graphics/BufferLayout.h"
#include "Graphics/RenderConfig.h"
#include "Graphics/Texture2D.h"
#include "Graphics/ShaderProvider.h"

namespace Bambo
{
	class SpriteComponent;

	struct SpriteRenderRequest
	{
	public:
		SPtr<Texture2D> Texture;
		int32 RectIndex;
		int32 GlobalPosIndex;
	};

	class BAMBO_API SpriteRenderer final : public Renderer
	{
	public:
		SpriteRenderer(SPtr<Shader> defaultShader);
		void EnqueueSpriteToRender(const SpriteRenderRequest& renderRequest);
		virtual void Render(std::vector<glm::mat4>& globalTransforms) override;
	private:
		static constexpr uint32 SPRITE_VERTEX_COUNT = 4;

		SPtr<VertexBufferObject> m_vbo;
		SPtr<VertexArrayObject> m_vao;
		std::array<QuadVertex, SPRITE_VERTEX_COUNT> m_renderVertices;
		std::vector<SpriteRenderRequest> m_sprites;

		void Render(const SPtr<Texture2D> texture, const RectInt& spriteRect, const glm::mat4& transform, const glm::mat4& projViewMatrix);
	};
}