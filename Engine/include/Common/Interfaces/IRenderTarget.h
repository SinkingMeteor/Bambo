#pragma once
#include "pch.h"
#include "Graphics/Vertex.h"
#include "Graphics/RenderConfig.h"
#include "Graphics/RenderTarget.h"
namespace Bambo
{
	class IRenderTarget 
	{
	public:
		virtual RenderTarget& GetRenderTarget() = 0;
		virtual ~IRenderTarget() {}
	};
}