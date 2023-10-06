#pragma once
#include "pch.h"
#include "RenderAPI.h"
#include "RendererImplementation.h"
#include "freetype.h"

namespace Bambo
{
	class BAMBO_API RenderManager final : public ISingleton
	{
		SINGLETON_BODY(RenderManager, 'RNDR')
	public:
		RenderManager();
		void Initialize(RenderAPI renderApi);
		void Dispose();

		FT_Library* GetFontHandle() { return &m_freeTypeHandle; }
		RendererImplementation* GetRenderer() { return m_renderer.get(); }
		RenderAPI GetCurrentRenderAPI() const { return m_renderApiType; }
	private:
		FT_Library m_freeTypeHandle;
		
		std::unique_ptr<RendererImplementation> m_renderer;
		RenderAPI m_renderApiType;
	};
}