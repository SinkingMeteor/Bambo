#include "DrawDebugHelpers.h"
#include "RenderManager.h"
#include "DebugLineRenderer.h"

namespace Bambo
{
	void DrawDebugLine(World* world, const Vector3f& from, const Vector3f& to, const Color& color)
	{
		LineRenderRequest drawRequest{};
		drawRequest.FromPos = from;
		drawRequest.ToPos = to;
		drawRequest.LineColor = color;

		world->GetDebugLineRenderer()->EnqueueLineToRender(drawRequest);
	}
}