#include "FontImplementation.h"
#include "RenderManager.h"
#include "OpenGL/OpenGLFont.h"
namespace Bambo
{
	Page::Page()
	{

	}


	UPtr<FontImplementation> FontImplementation::CreateBamboFont()
	{
		RenderAPI renderApi = RenderManager::Get()->GetCurrentRenderAPI();
		switch (renderApi)
		{
		case RenderAPI::OpenGL: return std::make_unique<OpenGLFont>();
		}
		BAMBO_ASSERT(false, "Unrecognized render api while creating font")
			return nullptr;
	}
}