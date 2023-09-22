#include "FontImplementation.h"
#include "RenderManager.h"
#include "OpenGL/OpenGLFont.h"
namespace Bambo
{
	UPtr<FontImplementation> FontImplementation::CreateBamboFont()
	{
		RenderAPI renderApi = RenderManager::Get()->GetCurrentRenderAPI();
		switch (renderApi)
		{
		case RenderAPI::OpenGL: return std::make_unique<OpenGLFont>();
		}
		BAMBO_ASSERT(false, "Unrecognized render api while creating renderer")
			return nullptr;
	}
}