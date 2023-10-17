#include "Components/SpriteComponent.h"
#include "World.h"
#include "BaseSerialization.h"

namespace Bambo
{
	SpriteComponent::SpriteComponent() :
		m_sprite(),
		m_sortingOrder(0)
	{}

	void SpriteComponent::PostConstruct()
	{
		Component::PostConstruct();

		if (!m_owner) return;

		World* world = m_owner->GetWorld();
		if (!world) return;
		m_sprite.SetTexture(world->GetTextureProvider()->Load(BamboPaths::EngineResourcesDir / BamboPaths::EngineDefaultSpritePath_A));
	}

	void SpriteComponent::OnRender(const glm::mat4& ownerGlobalMatrix)
	{
		if (!m_owner) return;

		World* world = m_owner->GetWorld();
		if (!world) return;

		SpriteRenderer* renderer = world->GetSpriteRenderer();

		if (!m_sprite.GetTexture()) return;

		SpriteRenderRequest request{};
		request.Texture = m_sprite.GetTexture();

		int32 rectsAmount = request.Texture->GetTextureRects().size();
		request.Rect = request.Texture->GetTextureRects()[std::clamp(m_sprite.GetRectIndex(), 0, rectsAmount - 1)];
		request.Model = glm::translate(ownerGlobalMatrix, m_sprite.GetOriginOffset());
		request.SortingOrder = m_sortingOrder;

		renderer->EnqueueSpriteToRender(request);
	}

	void SpriteComponent::Serialize(nlohmann::json& node)
	{
		Serialization::Serialize("SpriteComponent", node["name"]);
		Serialization::Serialize(m_sprite.GetTexture()->GetAssetInstanceID(), node["textureID"]);
		Serialization::Serialize(m_sprite.GetRectIndex(), node["rectId"]);
		Serialization::Serialize(m_sortingOrder, node["sortingOrder"]);
		Serialization::Serialize(m_sprite.GetOrigin(), node["origin"]);
	}

	void SpriteComponent::Deserialize(nlohmann::json& node)
	{
		BAMBO_ASSERT_S(m_owner)
		BAMBO_ASSERT_S(m_owner->IsValid())
		BAMBO_ASSERT_S(m_owner->GetWorld())

		m_sprite.SetRectIndex(Serialization::Deserialize<int32>(node["rectId"]));
		m_sortingOrder = Serialization::Deserialize<int32>(node["sortingOrder"]);
		m_sprite.SetOrigin(Serialization::Deserialize<glm::vec3>(node["origin"]));

		World* world = m_owner->GetWorld();
		TextureProvider* textureProvider = world->GetTextureProvider();

		std::size_t assetId = Serialization::Deserialize<std::size_t>(node["textureID"]);
		m_sprite.SetTexture(textureProvider->Load(assetId));
	}
}