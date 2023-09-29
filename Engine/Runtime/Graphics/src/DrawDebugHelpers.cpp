#include "DrawDebugHelpers.h"
#include "RenderManager.h"
#include "DebugLineRenderer.h"

namespace Bambo
{
	void DrawDebugLine(World* world, const Vector3f& from, const Vector3f& to, const Color& color, float thickness)
	{
		LineRenderRequest drawRequest{};
		drawRequest.FromPos = from;
		drawRequest.ToPos = to;
		drawRequest.LineColor = color;
		drawRequest.Thickness = thickness;

		world->GetDebugLineRenderer()->EnqueueLineToRender(drawRequest);
	}

	void DrawDebugRect(World* world, const RectFloat& rect, const Color& color, float thickness)
	{
		DebugLineRenderer* lineRenderer = world->GetDebugLineRenderer();

		Vector3f leftTop{ rect.Left, rect.Top, 0.0f };
		Vector3f rightBottom{ rect.Left + rect.Width, rect.Top - rect.Height, 0.0f };

		lineRenderer->EnqueueLineToRender(LineRenderRequest{ leftTop, leftTop + Vector3f{rect.Width, 0.0f, 0.0f}, color, thickness });
		lineRenderer->EnqueueLineToRender(LineRenderRequest{ leftTop, leftTop - Vector3f{0.0f, rect.Height, 0.0f}, color, thickness });
		lineRenderer->EnqueueLineToRender(LineRenderRequest{ rightBottom, rightBottom - Vector3f{rect.Width, 0.0f, 0.0f}, color, thickness });
		lineRenderer->EnqueueLineToRender(LineRenderRequest{ rightBottom, rightBottom + Vector3f{0.0f, rect.Height, 0.0f}, color, thickness });
	}

}