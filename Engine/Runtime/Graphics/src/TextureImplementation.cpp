#include "TextureImplementation.h"
#include "OpenGL/OpenGLTexture.h"
#include "RenderManager.h"
#include "RenderAPI.h"
namespace Bambo
{
	std::unique_ptr<TextureImplementation> TextureImplementation::CreateTexture(RenderAPI renderApi)
	{
		switch (renderApi)
		{
			case RenderAPI::OpenGL: return std::make_unique<OpenGLTexture>();
		}

		BAMBO_ASSERT(false, "Unknown render api")
		return nullptr;
	}
}