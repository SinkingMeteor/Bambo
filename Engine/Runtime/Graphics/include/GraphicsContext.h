#pragma once
#include "pch.h"
#include "GLFW/glfw3.h"
#include "RenderAPI.h"

namespace Bambo
{
	class BAMBO_API GraphicsContext
	{
	public:
		virtual ~GraphicsContext() {};

		virtual void Initialize() = 0;
		virtual void SwapBuffers() = 0;

		static std::unique_ptr<GraphicsContext> Create(RenderAPI renderApi, void* windowPtr);
	};
}