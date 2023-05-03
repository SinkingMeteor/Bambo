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
	class BAMBO_API Renderer2D final : public Renderer
	{
	public:
		Renderer2D();
		void Render(const SPtr<Sprite> sprite, const RenderConfig& renderConfig);
	private:
		SPtr<VertexBufferObject> m_vbo;
		SPtr<VertexArrayObject> m_vao;
	};
}