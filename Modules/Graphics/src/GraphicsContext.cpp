#include "OpenGL/OpenGLGraphicsContext.h"
#include "GraphicsContext.h"

namespace Bambo
{
	std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* windowPtr, RenderAPI apiType)
	{
		switch (apiType)
		{
		case RenderAPI::OpenGL:  return std::make_unique<OpenGLGraphicsContext>(static_cast<GLFWwindow*>(windowPtr));
		}

		BAMBO_ASSERT(false, "Unknown RenderAPI.");
		return nullptr;
	}

}