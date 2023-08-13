#include "World/Components/SpriteComponent.h"
#include "World/World.h"

namespace Bambo
{
	void SpriteComponent::Serialize(nlohmann::json& node)
	{
		node["name"] = "SpriteComponent";
		node["texturePath"] = Texture->GetTexturePath();
		node["textureID"] = Texture->GetAssetID();
		node["rectId"] = SpriteRectIndex;
	}

	void SpriteComponent::Deserialize(nlohmann::json& node)
	{
		BAMBO_ASSERT_S(m_owner)
		BAMBO_ASSERT_S(m_owner->IsValid())
		BAMBO_ASSERT_S(m_owner->GetWorld())

		World* world = m_owner->GetWorld();
		TextureProvider* textureProvider = world->GetTextureProvider();
		SpriteRectIndex = node["rectId"].get<uint32>();
		std::size_t assetId = node["textureID"].get<std::size_t>();
		std::string assetPath = node["texturePath"];

		Texture = textureProvider->Load(assetId, assetPath);
	}
}