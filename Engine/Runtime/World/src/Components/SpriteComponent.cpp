#include "Components/SpriteComponent.h"
#include "World.h"
#include "BaseSerialization.h"

namespace Bambo
{
	SpriteComponent::SpriteComponent() :
		m_texture{},
		m_origin{0.5f},
		m_spriteRectIndex{0}
	{}

	void SpriteComponent::PostConstruct()
	{
		Component::PostConstruct();

		if (!m_owner) return;

		World* world = m_owner->GetWorld();
		if (!world) return;
		m_texture = world->GetTextureProvider()->Load(BamboPaths::EngineResourcesDir / BamboPaths::EngineDefaultSpritePath_A);
	}

	void SpriteComponent::OnRender(std::vector<glm::mat4>& globals, int32 ownerMatIndex)
	{
		if (!m_owner) return;

		World* world = m_owner->GetWorld();
		if (!world) return;

		SpriteRenderer* renderer = world->GetSpriteRenderer();

		if (!m_texture) return;

		SpriteRenderRequest request{};
		request.Texture = m_texture;

		int32 rectsAmount = m_texture->GetTextureRects().size();
		request.Rect = m_texture->GetTextureRects()[std::clamp(m_spriteRectIndex, 0, rectsAmount - 1)];
		request.Model = glm::translate(globals[ownerMatIndex], GetOriginOffset());
		request.SortingOrder = m_sortingOrder;

		renderer->EnqueueSpriteToRender(request);
	}

	void SpriteComponent::Serialize(nlohmann::json& node)
	{
		Serialization::Serialize("SpriteComponent", node["name"]);
		Serialization::Serialize(m_texture->GetAssetInstanceID(), node["textureID"]);
		Serialization::Serialize(m_spriteRectIndex, node["rectId"]);
		Serialization::Serialize(m_sortingOrder, node["sortingOrder"]);
		Serialization::Serialize(m_origin, node["origin"]);
	}

	void SpriteComponent::Deserialize(nlohmann::json& node)
	{
		BAMBO_ASSERT_S(m_owner)
		BAMBO_ASSERT_S(m_owner->IsValid())
		BAMBO_ASSERT_S(m_owner->GetWorld())

		m_spriteRectIndex = Serialization::Deserialize<int32>(node["rectId"]);
		m_sortingOrder = Serialization::Deserialize<int32>(node["sortingOrder"]);
		m_origin = Serialization::Deserialize<glm::vec3>(node["origin"]);

		World* world = m_owner->GetWorld();
		TextureProvider* textureProvider = world->GetTextureProvider();

		std::size_t assetId = Serialization::Deserialize<std::size_t>(node["textureID"]);
		m_texture = textureProvider->Load(assetId);
	}
}