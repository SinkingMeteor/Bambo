#include "RenderManager.h"

DECLARE_LOG_CATEGORY_STATIC(LogRenderManager)

namespace Bambo
{
	RenderManager::RenderManager(Engine* engine):
		m_engine(engine),
		m_freeTypeHandle(),
		m_renderStatistics(),
		m_renderParameters(),
		m_renderApiType(RenderAPI::OpenGL),
		m_renderer()
	{}

	void RenderManager::Initialize(RenderAPI renderApi)
	{
		if (FT_Init_FreeType(&m_freeTypeHandle))
		{
			Logger::Get()->Log(LogRenderManager, Verbosity::Fatal, "Can't initialize freetype library");
			return;
		}

		m_renderApiType = renderApi;
		m_renderer = RendererImplementation::CreateRenderer(renderApi);
		m_renderer->Initialize();
	}

	void RenderManager::OnStartFrame()
	{
		m_renderStatistics.DrawCalls = 0;
		m_renderStatistics.SavedByBatching = 0;
	}

	void RenderManager::Dispose()
	{
		FT_Done_FreeType(m_freeTypeHandle);
	}
}