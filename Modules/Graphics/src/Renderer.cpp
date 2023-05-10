#include "Renderer.h"
#include "RenderManager.h"
namespace Bambo
{
	Renderer::Renderer() :
		m_camera(),
		m_defaultShader()
	{}

	void Renderer::RenderInternal(const SPtr<VertexArrayObject> vao, uint32 vertexAmount)
	{
		RenderManager::Get()->GetRenderer().Draw(vao, vertexAmount);
	}
}