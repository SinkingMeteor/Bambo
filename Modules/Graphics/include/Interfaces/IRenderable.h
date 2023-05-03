#pragma once
namespace Bambo
{
	struct RenderConfig;
	class RendererImplementation;

	class IRenderable
	{
	public:
		virtual void Render(RendererImplementation& renderer, RenderConfig config) = 0;
		virtual ~IRenderable() {}
	};
}