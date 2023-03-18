#pragma once
namespace Bambo
{
	struct RenderConfig;
	class IRenderTarget;

	class IRenderable
	{
	public:
		virtual void Render(IRenderTarget& renderTarget, const RenderConfig& config) = 0;
		virtual ~IRenderable() {}
	};
}