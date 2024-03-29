#include "VertexBufferObject.h"
#include "RenderManager.h"
#include "RenderAPI.h"
#include "OpenGL/OpenGLVertexBufferObject.h"

namespace Bambo
{
	SPtr<VertexBufferObject> VertexBufferObject::CreateVertexBufferObject(RenderAPI renderApi, const void* data, uint32 byteSize)
	{
		switch (renderApi)
		{
		case RenderAPI::OpenGL: return std::make_shared<OpenGLVertexBufferObject>(data, byteSize);
		}
		BAMBO_ASSERT(false, "Unrecognized render api")
		return nullptr;
	}

	SPtr<VertexBufferObject> VertexBufferObject::CreateVertexBufferObject(RenderAPI renderApi, uint32 byteSize)
	{
		switch (renderApi)
		{
		case RenderAPI::OpenGL: return std::make_shared<OpenGLVertexBufferObject>(byteSize);
		}
		BAMBO_ASSERT(false, "Unrecognized render api")
		return nullptr;
	}
}