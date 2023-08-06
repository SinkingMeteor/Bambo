#pragma once
#include "World/Components/Components.h"
#include "Drawers/InspectorDrawer.h"
#include "Drawers/PrimitiveDrawers.h"

namespace BamboEditor
{
	void DrawTagComponent(Bambo::Component* component);
	void DrawTransformComponent(Bambo::Component* component);
	void DrawSpriteComponent(Bambo::Component* component);
	void DrawCameraComponent(Bambo::Component* component);
}