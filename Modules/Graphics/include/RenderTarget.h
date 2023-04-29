#pragma once
#include "pch.h"
#include "Graphics.h"
#include "RenderConfig.h"
#include "Interfaces/IRenderable.h"
#include "Vectors.h"
#include "Vertex.h"
namespace Bambo 
{
	class BAMBO_API RenderTarget final
	{
	public:
		RenderTarget();
		RenderTarget(const RenderTarget& v) = delete;
		RenderTarget& operator=(const RenderTarget& v) = delete;
		~RenderTarget();

		void Initialize();
		void Draw(const Vertex* vertices, int amount, const RenderConfig& config);
		void Draw(IRenderable& renderable, const RenderConfig& config);
		void SetWindowSize(int windowWidth, int windowHeight) { m_windowSize = Vector2i{ windowWidth, windowHeight }; }
	private:
		Vector2i m_windowSize;
		GLuint m_vao;
		GLuint m_vbo;
		uint m_bufferSize;

		void ApplyViewport(const RenderConfig& config);

	};
}