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

	class BAMBO_API SpriteRenderer final : public Renderer
	{
	public:
		SpriteRenderer(SPtr<Shader> defaultShader);
		virtual void BeginRender() override;
		virtual void EndRender() override;
		void EnqueueSprite(SpriteComponent* component);
	private:
		static constexpr uint32 SPRITE_VERTEX_COUNT = 4;

		SPtr<VertexBufferObject> m_vbo;
		SPtr<VertexArrayObject> m_vao;
		std::array<QuadVertex, SPRITE_VERTEX_COUNT> m_renderVertices;
		std::vector<SpriteComponent*> m_sprites;

		void Render(const SPtr<Texture2D> texture, const RectInt& spriteRect, const glm::mat4& transform, const glm::mat4& projViewMatrix);
	};
}