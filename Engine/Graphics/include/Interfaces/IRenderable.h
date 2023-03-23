#pragma once
namespace Bambo
{
	struct RenderConfig;
	class RenderTarget;

	class IRenderable
	{
	public:
		virtual void Render(RenderTarget& renderTarget, const RenderConfig& config) = 0;
		virtual ~IRenderable() {}
	};
}