#pragma once
namespace Bambo
{
	struct RenderConfig;
	class Renderer;

	class IRenderable
	{
	public:
		virtual void Render(Renderer& renderer, const RenderConfig& config) = 0;
		virtual ~IRenderable() {}
	};
}