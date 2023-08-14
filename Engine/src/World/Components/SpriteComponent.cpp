#include "World/Components/SpriteComponent.h"
#include "World/World.h"

namespace Bambo
{
	void SpriteComponent::Serialize(nlohmann::json& node)
	{
		node["name"] = "SpriteComponent";
		node["texturePath"] = m_texture->GetTexturePath();
		node["textureID"] = m_texture->GetAssetID();
		node["rectId"] = m_spriteRectIndex;
	}

	void SpriteComponent::Deserialize(nlohmann::json& node)
	{
		BAMBO_ASSERT_S(m_owner)
		BAMBO_ASSERT_S(m_owner->IsValid())
		BAMBO_ASSERT_S(m_owner->GetWorld())

		m_spriteRectIndex = node["rectId"].get<int32>();

		World* world = m_owner->GetWorld();
		TextureProvider* textureProvider = world->GetTextureProvider();
		std::size_t assetId = node["textureID"].get<std::size_t>();
		std::string assetPath = node["texturePath"];

		m_texture = textureProvider->Load(assetId, assetPath);
	}
}