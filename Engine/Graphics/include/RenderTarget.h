#pragma once
#include "pch.h"
#include "Graphics.h"
#include "RenderConfig.h"
#include "Interfaces/IRenderable.h"
#include "Vertex.h"
#include "WindowSettings.h"
namespace Bambo 
{
	class BAMBO_API RenderTarget final
	{
	public:
		RenderTarget(std::shared_ptr<WindowSettings> windowSettings);
		RenderTarget(const RenderTarget& v) = delete;
		RenderTarget& operator=(const RenderTarget& v) = delete;
		~RenderTarget();

		void Initialize();
		void Draw(const Vertex* vertices, int amount, const RenderConfig& config);
		void Draw(IRenderable& renderable, const RenderConfig& config);
	private:
		std::shared_ptr<WindowSettings> m_windowSettings;
		GLuint m_vao;
		GLuint m_vbo;
		uint m_bufferSize;

		void ApplyViewport(const RenderConfig& config);

	};
}