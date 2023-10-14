#include "DefaultDrawers.h"
#include "AssetReferenceWidget.h"
#include "GameObject.h"
#include "World.h"
#include "Utils.h"

namespace
{
	const std::string NONE_TEXTURE = "No texture";
	std::string tmpText{};
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

		DrawInteger("Rect index", &spriteComponent->GetRectIndexRef());
		DrawInteger("Sorting order", &spriteComponent->GetSortingOrderRef());
		DrawVector3("Origin", &spriteComponent->GetOriginRef());

		Bambo::World* world = spriteComponent->GetOwner()->GetWorld();
		Bambo::ResourceManager* resourceManager = world->GetWorldContext()->Engine->GetResourceManager();
		AssetReferenceWidget texReference{ resourceManager, Bambo::AssetType::Texture2D };

		if (spriteComponent->GetTexture())
		{
			texReference.SetAssetID(spriteComponent->GetTexture()->GetAssetInstanceID());
		}

		ImGui::Text("Texture");
		ImGui::SameLine();

		std::size_t cachedTex = texReference.GetAssetID();
		texReference.Draw();

		if (cachedTex != texReference.GetAssetID())
		{
			Bambo::TextureProvider* textureProvider = component->GetOwner()->GetWorld()->GetTextureProvider();
			spriteComponent->SetTexture(textureProvider->Load(texReference.GetAssetID()));
		}
	}

	void DrawArea2DComponent(Bambo::Component* component)
	{
		Bambo::Area2DComponent* areaComponent = Bambo::Cast<Bambo::Area2DComponent>(component);
		DrawFloat("Width", &areaComponent->Width);
		DrawFloat("Height", &areaComponent->Height);
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

		if (DrawU32String("Content", textComponent->GetInternalText().GetText32Ptr()))
		{
			textComponent->GetInternalText().SetRebuildFlag();
		}

		DrawInteger("Sorting order", &textComponent->GetSortingOrderRef());
	}

}