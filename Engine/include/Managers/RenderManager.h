#pragma once
#include "engpch.h"
#include "Managers/Singleton.h"
#include "RenderTarget.h"
#include "WindowManager.h"

namespace Bambo
{
	class RenderManager : public Singleton<RenderManager>
	{
	public:
		void Initialize();
		void Dispose();
		void ClearCanvas();
	private:
		RenderTarget* m_renderTarget;
	};
}