#pragma once
#include "pch.h"
#include "OpenGLCheck.h"
#include "RendererImplementation.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

namespace Bambo
{
	class BAMBO_API OpenGLRenderer final : public RendererImplementation
	{
	public:
		OpenGLRenderer();
		virtual ~OpenGLRenderer();
		virtual void Initialize() override;
		virtual void SetViewport(const Vector2u& origin, const Vector2u& size) override;
		virtual void Draw(const void* vertices, int verticesAmount, const RenderConfig& config) override;
		virtual void SetClearColor(const Color& color) override;
		virtual void Clear() override;
	private:
		SPtr<VertexBufferObject> m_vbo;
		SPtr<VertexArrayObject> m_vao;
		BufferLayout m_layout;
	};
}