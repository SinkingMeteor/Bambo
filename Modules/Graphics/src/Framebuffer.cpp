#include "Framebuffer.h"

#include "OpenGL/OpenGLFramebuffer.h"
#include "RenderManager.h"
#include "RenderAPI.h"

namespace Bambo
{
	SPtr<Framebuffer> Framebuffer::Create(const std::vector<FramebufferTextureType>& textureTypes, uint32 textureWidth, uint32 textureHeight)
	{
		RenderAPI renderApi = RenderManager::Get()->GetCurrentRenderAPI();
		switch (renderApi)
		{
		case RenderAPI::OpenGL: return std::make_unique<OpenGLFramebuffer>(textureTypes, textureWidth, textureHeight);
		}
		BAMBO_ASSERT(false, "Unrecognized render api while creating renderer")
			return nullptr;
	}
}