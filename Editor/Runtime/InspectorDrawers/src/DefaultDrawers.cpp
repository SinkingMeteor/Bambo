#include "DefaultDrawers.h"

namespace
{
	const std::string NONE_TEXTURE = "No texture";
}

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

		if (spriteComponent->GetTexture())
		{
			std::string idStr = std::to_string(spriteComponent->GetTexture()->GetAssetInstanceID());
			DrawReadonlyString(&idStr);
		}
		else
		{
			DrawReadonlyString(&NONE_TEXTURE);
		}
	}

	void DrawCameraComponent(Bambo::Component* component)
	{
		Bambo::CameraComponent* cameraComponent = Bambo::Cast<Bambo::CameraComponent>(component);

		ImGui::Text("CameraComponent");
	}

	void DrawTextComponent(Bambo::Component* component)
	{
		Bambo::TextComponent* textComponent = Bambo::Cast<Bambo::TextComponent>(component);
		ImGui::Text("Text Component");

		if (DrawFloat("Width", &textComponent->GetInternalText().GetAreaWidthRef(), 0))
		{
			textComponent->GetInternalText().SetRebuildFlag();
		}

		if (DrawFloat("Height", &textComponent->GetInternalText().GetAreaHeightRef()))
		{
			textComponent->GetInternalText().SetRebuildFlag();
		}

		if (DrawUInteger("Size", &textComponent->GetInternalText().GetTextSizeRef()))
		{
			textComponent->GetInternalText().SetRebuildFlag();
		}

		DrawInteger("Sorting order", &textComponent->GetSortingOrderRef());
	}

}