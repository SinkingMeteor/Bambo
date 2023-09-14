#pragma once
#include "Components/Components.h"
#include "Drawers/InspectorDrawer.h"
#include "Drawers/PrimitiveDrawers.h"
#include "Transform.h"

namespace BamboEditor
{
	void DrawTransformComponent(Bambo::Transform* component);
	void DrawSpriteComponent(Bambo::Component* component);
	void DrawCameraComponent(Bambo::Component* component);
}