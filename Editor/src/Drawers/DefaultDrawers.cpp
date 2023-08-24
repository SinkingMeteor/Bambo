#include "Drawers/DefaultDrawers.h"

namespace BamboEditor
{
	void DrawTransformComponent(Bambo::Transform* transform)
	{
		ImGui::Text("Transform:");
		DrawVector3("Position", &transform->GetPositionRef());
		DrawVector3("Rotation", &transform->GetRotationRef());
		DrawVector3("Scale", &transform->GetScaleRef());
		transform->SetNeedUpdate();
	}

	void DrawSpriteComponent(Bambo::Component* component)
	{
		Bambo::SpriteComponent* spriteComponent = Bambo::Cast<Bambo::SpriteComponent>(component);

		ImGui::Text("SpriteComponent");
		DrawInteger("Rect index", &spriteComponent->GetRectIndexRef());
		DrawInteger("Sorting order", &spriteComponent->GetSortingOrderRef());
		DrawVector3("Origin", &spriteComponent->GetOriginRef());
		DrawReadonlyString(&spriteComponent->GetTexture()->GetTexturePath());
	}

	void DrawCameraComponent(Bambo::Component* component)
	{
		Bambo::CameraComponent* cameraComponent = Bambo::Cast<Bambo::CameraComponent>(component);

		ImGui::Text("CameraComponent");
	}
}