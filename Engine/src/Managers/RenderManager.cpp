#include "Managers/RenderManager.h"

namespace Bambo
{
	void RenderManager::Initialize() 
	{
	}

	void RenderManager::Dispose()
	{
	}

	void RenderManager::ClearCanvas()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

}