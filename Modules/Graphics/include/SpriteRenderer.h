#pragma once
#include "pch.h"
#include "Graphics.h"
#include "Renderer.h"
#include "RendererImplementation.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "BufferLayout.h"
#include "RenderConfig.h"
#include "Texture2D.h"

namespace Bambo
{
	class BAMBO_API SpriteRenderer final : public Renderer
	{
	public:
		SpriteRenderer();
		void Render(const SPtr<Texture2D> texture, const RectInt& spriteRect, const glm::mat4& transform, const glm::mat4& projViewMatrix);
	private:
		static constexpr uint32 SPRITE_VERTEX_COUNT = 4;

		SPtr<VertexBufferObject> m_vbo;
		SPtr<VertexArrayObject> m_vao;
		std::array<QuadVertex, SPRITE_VERTEX_COUNT> m_renderVertices;
	};
}