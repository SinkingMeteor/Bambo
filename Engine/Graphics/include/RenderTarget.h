#pragma once
#include "pch.h"
#include "Graphics.h"
#include "RenderConfig.h"
#include "Interfaces/IRenderable.h"
#include "Vertex.h"
namespace Bambo 
{
	struct RenderSettings
	{
	public:
		int Width;
		int Height;
	};

	class BAMBO_API RenderTarget 
	{
	public:
		RenderTarget(const RenderSettings& renderSettings);
		RenderTarget(const RenderTarget& v) = delete;
		RenderTarget& operator=(const RenderTarget& v) = delete;
		~RenderTarget();

		void Initialize();
		void Draw(const Vertex* vertices, int amount, const RenderConfig& config);
		void Draw(IRenderable& renderable, const RenderConfig& config);
	private:
		void ApplyViewport(const RenderConfig& config);

		const RenderSettings m_renderSettings;
		GLuint m_vao;
		GLuint m_vbo;
		uint m_bufferSize;
	};
}