#include "IndexBufferObject.h"
#include "RenderManager.h"
#include "OpenGL/OpenGLIndexBufferObject.h"
namespace Bambo
{
	SPtr<IndexBufferObject> IndexBufferObject::CreateIndexBuffer(RenderAPI renderApi, std::size_t size)
	{
		switch (renderApi)
		{
			case RenderAPI::OpenGL: return std::make_shared<OpenGLIndexBufferObject>(size);
		}
		BAMBO_ASSERT(false, "Unrecognized render api type")
		return nullptr;
	}
}