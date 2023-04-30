#include "OpenGL/OpenGLGraphicsContext.h"
#include "GraphicsContext.h"
#include "RenderManager.h"
namespace Bambo
{
	std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* windowPtr)
	{
		RenderAPI apiType = RenderManager::Get()->GetCurrentRenderAPI();
		switch (apiType)
		{
		case RenderAPI::OpenGL:  return std::make_unique<OpenGLGraphicsContext>(static_cast<GLFWwindow*>(windowPtr));
		}

		BAMBO_ASSERT(false, "Unknown RenderAPI.");
		return nullptr;
	}

}