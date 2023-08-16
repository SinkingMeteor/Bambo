#include "World/Components/SpriteComponent.h"
#include "World/World.h"
#include "Serialization/MathSerialization.h"
namespace Bambo
{
	SpriteComponent::SpriteComponent() :
		m_texture{},
		m_origin{0.5f},
		m_spriteRectIndex{0}
	{}

	void SpriteComponent::PostConstruct()
	{
		if (!m_owner) return;

		World* world = m_owner->GetWorld();
		if (!world) return;
		m_texture = world->GetTextureProvider()->Load(ToId("Square"), BamboPaths::BamboResourcesDir + "Textures/Square.png");
	}

	void SpriteComponent::Tick(float deltaSeconds)
	{
		if (!m_owner) return;

		World* world = m_owner->GetWorld();
		if (!world) return;

		world->GetRenderer()->EnqueueSprite(this);
	}

	void SpriteComponent::Serialize(nlohmann::json& node)
	{
		node["name"] = "SpriteComponent";
		node["texturePath"] = m_texture->GetTexturePath();
		node["textureID"] = m_texture->GetAssetID();
		node["rectId"] = m_spriteRectIndex;
		Serialization::Serialize(m_origin, node["origin"]);
	}

	void SpriteComponent::Deserialize(nlohmann::json& node)
	{
		BAMBO_ASSERT_S(m_owner)
		BAMBO_ASSERT_S(m_owner->IsValid())
		BAMBO_ASSERT_S(m_owner->GetWorld())

		m_spriteRectIndex = node["rectId"].get<int32>();
		Serialization::Deserialize(m_origin, node["origin"]);

		World* world = m_owner->GetWorld();
		TextureProvider* textureProvider = world->GetTextureProvider();
		std::size_t assetId = node["textureID"].get<std::size_t>();
		std::string assetPath = node["texturePath"];

		m_texture = textureProvider->Load(assetId, assetPath);
	}
}