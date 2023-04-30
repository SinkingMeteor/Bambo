#include "ShaderImplementation.h"
#include "RenderManager.h"
namespace Bambo
{
	std::unique_ptr<ShaderImplementation> ShaderImplementation::CreateInternalShader()
	{
		RenderAPI renderApi = RenderManager::Get()->GetCurrentRenderAPI();
		switch (renderApi)
		{
		case Bambo::RenderAPI::OpenGL:
			break;
		}
		BAMBO_ASSERT(false, "Unrecognized render by while creating shader")
		return nullptr;
	}
}