#include "RenderManager.h"

namespace Bambo
{
	RenderManager::RenderManager():
		m_renderApiType{RenderAPI::OpenGL},
		m_renderer{}
	{}


	void RenderManager::Initialize(RenderAPI renderApi)
	{
		m_renderApiType = renderApi;
		m_renderer = RendererImplementation::CreateRenderer();
		m_renderer->Initialize();
		m_renderer->SetClearColor(Color{ 1.0f, 0.0f, 1.0f, 1.0f });
	}

	void RenderManager::Dispose()
	{
	}
}