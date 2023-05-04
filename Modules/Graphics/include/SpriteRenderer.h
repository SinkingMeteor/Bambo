#pragma once
#include "pch.h"
#include "Renderer.h"
#include "RendererImplementation.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "BufferLayout.h"
#include "Sprite.h"
#include "RenderConfig.h"
namespace Bambo
{
	class BAMBO_API SpriteRenderer final : public Renderer
	{
	public:
		SpriteRenderer();
		void Render(const SPtr<Sprite> sprite, const RenderConfig& renderConfig);
	private:
		static constexpr uint32 SPRITE_VERTEX_COUNT = 4;

		SPtr<VertexBufferObject> m_vbo;
		SPtr<VertexArrayObject> m_vao;
		std::array<QuadVertex, SPRITE_VERTEX_COUNT> m_renderVertices;
	};
}