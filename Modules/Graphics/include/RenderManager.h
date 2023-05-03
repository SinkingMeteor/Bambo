#pragma once
#include "pch.h"
#include "Singleton.h"
#include "RenderAPI.h"
#include "RendererImplementation.h"
namespace Bambo
{
	class BAMBO_API RenderManager : public Singleton<RenderManager>
	{
	public:
		RenderManager();
		void Initialize(RenderAPI renderApi);
		void Dispose();
		RendererImplementation& GetRenderer() { return *m_renderer; }
		RenderAPI GetCurrentRenderAPI() const { return m_renderApiType; }
	protected:
	private:
		std::unique_ptr<RendererImplementation> m_renderer;
		RenderAPI m_renderApiType;
	};
}