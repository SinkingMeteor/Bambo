#pragma once
#include "Essentials.h"
#include "World.h"
namespace Bambo
{
	void DrawDebugLine(World* world, const Vector3f& from, const Vector3f& to, const Color& color, float thickness = 1.0f);

	void DrawDebugRect(World* world, const RectFloat& rect, const Color& color, float thickness = 1.0f);
}