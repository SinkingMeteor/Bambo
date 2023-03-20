#pragma once
#include "pch.h"
#include "Graphics/RenderConfig.h"
#include "Common/Interfaces/IRenderable.h"
#include "Graphics/Vertex.h"
namespace Bambo 
{
	class BAMBO_API RenderTarget 
	{
	public:
		RenderTarget();
		RenderTarget(const RenderTarget& v) = delete;
		RenderTarget& operator=(const RenderTarget& v) = delete;
		~RenderTarget();

		void Initialize();
		void Draw(const Vertex* vertices, int amount, const RenderConfig& config);
		void Draw(IRenderable& renderable, const RenderConfig& config);
	private:
		GLuint m_vao;
		GLuint m_vbo;
		uint m_bufferSize;
	};
}