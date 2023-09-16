#include "Components/SpriteComponent.h"
#include "World.h"
#include "MathSerialization.h"
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
		m_texture = world->GetTextureProvider()->Load(BamboPaths::BamboResourcesDir + "Textures/Square.png");
	}

	void SpriteComponent::OnRender(std::vector<glm::mat4>& globals, int32 ownerMatIndex)
	{
		if (!m_owner) return;

		World* world = m_owner->GetWorld();
		if (!world) return;

		SpriteRenderer* renderer = world->GetRenderer();

		globals[ownerMatIndex] = glm::translate(globals[ownerMatIndex], GetOriginOffset());

		SpriteRenderRequest request{};
		request.Texture = m_texture;

		int32 rectsAmount = m_texture->GetTextureRects().size();
		m_spriteRectIndex = std::clamp(m_spriteRectIndex, 0, rectsAmount - 1);
		request.RectIndex = m_spriteRectIndex;
		request.GlobalPosIndex = ownerMatIndex;
		request.SortingOrder = m_sortingOrder;

		renderer->EnqueueSpriteToRender(request);
	}

	void SpriteComponent::Serialize(nlohmann::json& node)
	{
		node["name"] = "SpriteComponent";
		node["textureID"] = m_texture->GetAssetInstanceID();
		node["rectId"] = m_spriteRectIndex;
		node["sortingOrder"] = m_sortingOrder;
		Serialization::Serialize(m_origin, node["origin"]);
	}

	void SpriteComponent::Deserialize(nlohmann::json& node)
	{
		BAMBO_ASSERT_S(m_owner)
		BAMBO_ASSERT_S(m_owner->IsValid())
		BAMBO_ASSERT_S(m_owner->GetWorld())

		m_spriteRectIndex = node["rectId"].get<int32>();
		nlohmann::json& sortingOrderNode = node["sortingOrder"];
		if (!sortingOrderNode.is_null())
		{
			m_sortingOrder = sortingOrderNode.get<int32>();
		}
		Serialization::Deserialize(m_origin, node["origin"]);

		World* world = m_owner->GetWorld();
		TextureProvider* textureProvider = world->GetTextureProvider();
		std::size_t assetId = node["textureID"].get<std::size_t>();

		m_texture = textureProvider->Load(assetId);
	}
}