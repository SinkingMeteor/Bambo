#pragma once
#include "pch.h"
#include "Renderer.h"
#include "Graphics.h"
#include "BufferLayout.h"
namespace Bambo
{
	class BAMBO_API OpenGLRenderer final : public Renderer
	{
	public:
		OpenGLRenderer();
		virtual ~OpenGLRenderer();
		virtual void Initialize() override;
		virtual void SetViewport(const Vector2u& origin, const Vector2u& size) override;
		virtual void Draw(const Vertex* vertices, int amount, const RenderConfig& config) override;
		virtual void SetClearColor(const Color& color) override;
		virtual void Clear() override;
	private:
		GLuint m_vao;
		GLuint m_vbo;
		uint32 m_bufferSize;
		BufferLayout m_layout;
	};
}