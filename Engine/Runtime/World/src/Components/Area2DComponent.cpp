#include "Components/Area2DComponent.h"
#include "World.h"
#include "BaseSerialization.h"
#include "DrawDebugHelpers.h"

namespace Bambo
{
	void Area2DComponent::OnRender(std::vector<glm::mat4>& globals, int32 ownerMatIndex)
	{
		if (!m_owner) return;

		World* world = m_owner->GetWorld();
		if (!world) return;

		glm::mat4 objectPos = globals[ownerMatIndex];

#ifdef WITH_EDITOR

		glm::vec4 selfWorldPos = glm::translate(globals[ownerMatIndex], GetOriginOffset()) * glm::vec4{ 1.0f };

		RectFloat rect{ m_rect };
		rect.Left = selfWorldPos.x;
		rect.Top = selfWorldPos.y;

		DrawDebugRect(world, rect, Color::Green());
#endif
	}

	void Area2DComponent::Serialize(nlohmann::json& node)
	{
		Serialization::Serialize(GetName(), node["name"]);
		Serialization::Serialize(m_origin, node["origin"]);
		Serialization::Serialize(m_rect, node["rect"]);
	}

	void Area2DComponent::Deserialize(nlohmann::json& node)
	{
		BAMBO_ASSERT_S(m_owner)
		BAMBO_ASSERT_S(m_owner->IsValid())
		BAMBO_ASSERT_S(m_owner->GetWorld())

		m_rect = Serialization::Deserialize<RectFloat>(node["rect"]);
		m_origin = Serialization::Deserialize<glm::vec3>(node["origin"]);
	}
}