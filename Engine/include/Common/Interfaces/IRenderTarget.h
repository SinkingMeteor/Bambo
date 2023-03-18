#pragma once
#include "pch.h"
#include "Graphics/Vertex.h"
#include "Graphics/RenderConfig.h"

namespace Bambo
{
	class IRenderable;

	class IRenderTarget 
	{
	public:
		virtual void Draw(const Vertex* vertices, int amount, const RenderConfig& config) = 0;
		virtual void Draw(IRenderable& renderable, const RenderConfig& config) = 0;
		virtual ~IRenderTarget() {}
	};
}