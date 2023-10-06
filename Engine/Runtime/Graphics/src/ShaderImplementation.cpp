#include "ShaderImplementation.h"
#include "RenderManager.h"
#include "OpenGL/OpenGLShader.h"
namespace Bambo
{
	std::unique_ptr<ShaderImplementation> ShaderImplementation::CreateInternalShader(RenderAPI renderApi)
	{
		switch (renderApi)
		{
			case Bambo::RenderAPI::OpenGL: return std::make_unique<OpenGLShader>();
		}
		BAMBO_ASSERT(false, "Unrecognized render by while creating shader")
		return nullptr;
	}
}