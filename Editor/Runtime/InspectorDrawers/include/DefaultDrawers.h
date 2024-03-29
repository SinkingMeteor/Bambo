#pragma once
#include "Components/Components.h"
#include "InspectorDrawer.h"
#include "PrimitiveDrawers.h"
#include "Transform.h"

namespace BamboEditor
{
	void DrawTransformComponent(Bambo::Transform* component);
	void DrawSpriteComponent(Bambo::Component* component);
	void DrawArea2DComponent(Bambo::Component* component);
	void DrawCameraComponent(Bambo::Component* component);
	void DrawTextComponent(Bambo::Component* component);
}