#include "Graphics/TextureImplementation.h"
#include "Graphics/OpenGL/OpenGLTexture.h"
#include "Graphics/RenderManager.h"
#include "Graphics/RenderAPI.h"
namespace Bambo
{
	std::unique_ptr<TextureImplementation> TextureImplementation::CreateTexture()
	{
		RenderAPI renderApi = RenderManager::Get()->GetCurrentRenderAPI();
		switch (renderApi)
		{
			case RenderAPI::OpenGL: return std::make_unique<OpenGLTexture>();
		}
		BAMBO_ASSERT(false, "Unknown render api")
		return nullptr;
	}
}