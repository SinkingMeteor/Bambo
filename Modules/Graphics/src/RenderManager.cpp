#include "RenderManager.h"

namespace Bambo
{
	RenderManager::RenderManager():
		m_renderApiType{RenderAPI::OpenGL},
		m_renderTarget{}
	{}


	void RenderManager::Initialize(RenderAPI renderApi)
	{
		m_renderApiType = renderApi;
		m_renderTarget = std::make_unique<RenderTarget>();
		m_renderTarget->Initialize();
	}

	void RenderManager::Dispose()
	{
	}

	void RenderManager::ClearCanvas()
	{
		m_renderTarget->ClearCanvas();
	}

}