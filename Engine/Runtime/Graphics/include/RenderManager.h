#pragma once
#include "pch.h"
#include "RenderAPI.h"
#include "RendererImplementation.h"
#include "freetype.h"

namespace Bambo
{
	class Engine;

	struct RenderStatistics
	{
		int32 DrawCalls;
		int32 SavedByBatching;
	};

	struct RenderParameters
	{
		bool DrawDebug{true};
	};

	class BAMBO_API RenderManager final
	{
	public:
		RenderManager(Engine* engine);
		void Initialize(RenderAPI renderApi);
		void Dispose();

		void OnStartFrame();
		RenderStatistics& GetRenderStatistics() { return m_renderStatistics; }
		RenderParameters& GetRenderParameters() { return m_renderParameters; }

		FT_Library* GetFontHandle() { return &m_freeTypeHandle; }
		RendererImplementation* GetRenderer() { return m_renderer.get(); }
		RenderAPI GetCurrentRenderAPI() const { return m_renderApiType; }
	private:
		Engine* m_engine;
		FT_Library m_freeTypeHandle;
		RenderStatistics m_renderStatistics;
		RenderParameters m_renderParameters;
		std::unique_ptr<RendererImplementation> m_renderer;
		RenderAPI m_renderApiType;
	};
}