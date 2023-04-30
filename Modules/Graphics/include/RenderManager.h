#pragma once
#include "pch.h"
#include "Singleton.h"
#include "RenderTarget.h"
#include "RenderAPI.h"
namespace Bambo
{
	class BAMBO_API RenderManager : public Singleton<RenderManager>
	{
	public:
		RenderManager();
		void Initialize(RenderAPI renderApi);
		void Dispose();
		void ClearCanvas();
		RenderAPI GetCurrentRenderAPI() const { return m_renderApiType; }
	protected:
	private:
		std::unique_ptr<RenderTarget> m_renderTarget;
		RenderAPI m_renderApiType;
	};
}