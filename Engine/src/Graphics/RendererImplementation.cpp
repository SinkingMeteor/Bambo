#include "Graphics/RendererImplementation.h"
#include "Graphics/OpenGL/OpenGLRenderer.h"
#include "Graphics/RenderManager.h"
namespace Bambo
{
	std::unique_ptr<RendererImplementation> RendererImplementation::CreateRenderer()
	{
		RenderAPI renderApi = RenderManager::Get()->GetCurrentRenderAPI();
		switch (renderApi)
		{
			case RenderAPI::OpenGL: return std::make_unique<OpenGLRenderer>();
		}
		BAMBO_ASSERT(false, "Unrecognized render api while creating renderer")
		return nullptr;
	}

}