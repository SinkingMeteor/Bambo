#include "Renderer.h"
#include "OpenGL/OpenGLRenderer.h"
namespace Bambo
{
	std::unique_ptr<Renderer> Renderer::CreateRenderer(RenderAPI renderApi)
	{
		switch (renderApi)
		{
			case RenderAPI::OpenGL: return std::make_unique<OpenGLRenderer>();
		}
		BAMBO_ASSERT(false, "Unrecognized render api while creating renderer")
		return nullptr;
	}

}