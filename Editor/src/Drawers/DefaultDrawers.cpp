#include "Drawers/DefaultDrawers.h"

namespace BamboEditor
{
	void DrawTagComponent(Bambo::Component* component)
	{
		Bambo::TagComponent* tag = Bambo::Cast<Bambo::TagComponent>(component);
		ImGui::Text("TagComponent");
		DrawString("Tag", &tag->Tag);
	}

	void DrawTransformComponent(Bambo::Component* component)
	{
		Bambo::TransformComponent* transform = Bambo::Cast<Bambo::TransformComponent>(component);

		ImGui::Text("TransformComponent");
		DrawVector3("Position", &transform->Position);
		DrawVector3("Rotation", &transform->Rotation);
		DrawVector3("Scale", &transform->Scale);
	}

	void DrawSpriteComponent(Bambo::Component* component)
	{
		Bambo::SpriteComponent* spriteComponent = Bambo::Cast<Bambo::SpriteComponent>(component);

		ImGui::Text("SpriteComponent");
		DrawInteger("Rect index", &spriteComponent->SpriteRectIndex);
		DrawReadonlyString(&spriteComponent->Texture->GetTexturePath());
	}

	void DrawCameraComponent(Bambo::Component* component)
	{
		Bambo::CameraComponent* cameraComponent = Bambo::Cast<Bambo::CameraComponent>(component);

		ImGui::Text("CameraComponent");
	}
}