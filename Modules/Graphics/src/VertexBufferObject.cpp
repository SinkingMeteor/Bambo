#include "VertexBufferObject.h"
#include "RenderManager.h"
#include "RenderAPI.h"
#include "OpenGL/OpenGLVertexBufferObject.h"

namespace Bambo
{
	SPtr<VertexBufferObject> VertexBufferObject::CreateVertexBufferObject(const void* data, uint32 size)
	{
		RenderAPI renderApi = RenderManager::Get()->GetCurrentRenderAPI();
		switch (renderApi)
		{
		case RenderAPI::OpenGL: return std::make_shared<OpenGLVertexBufferObject>(data, size);
		}
		BAMBO_ASSERT(false, "Unrecognized render api")
		return nullptr;
	}

	SPtr<VertexBufferObject> VertexBufferObject::CreateVertexBufferObject(uint32 size)
	{
		RenderAPI renderApi = RenderManager::Get()->GetCurrentRenderAPI();
		switch (renderApi)
		{
		case RenderAPI::OpenGL: return std::make_shared<OpenGLVertexBufferObject>(size);
		}
		BAMBO_ASSERT(false, "Unrecognized render api")
		return nullptr;
	}
}