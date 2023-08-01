#include "Graphics/VertexArrayObject.h"
#include "Graphics/RenderManager.h"
#include "Graphics/RenderAPI.h"
#include "Graphics/OpenGL/OpenGLVertexArrayObject.h"

namespace Bambo
{
	SPtr<VertexArrayObject> VertexArrayObject::CreateVertexArrayObject()
	{
		RenderAPI renderApi = RenderManager::Get()->GetCurrentRenderAPI();
		switch (renderApi)
		{
		case RenderAPI::OpenGL: return std::make_shared<OpenGLVertexArrayObject>();
		}
		BAMBO_ASSERT(false, "Unrecognized render api type")
		return nullptr;
	}

}