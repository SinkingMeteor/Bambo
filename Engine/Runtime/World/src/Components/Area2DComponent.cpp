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

		glm::vec4 selfWorldPos = glm::translate(globals[ownerMatIndex], glm::vec3{ 1.0f }) * glm::vec4{ 1.0f };
		RectFloat rect{ selfWorldPos.x, selfWorldPos.y, Width, Height };

		DrawDebugRect(world, rect, Color::Green());
#endif
	}

	void Area2DComponent::Serialize(nlohmann::json& node)
	{
		Serialization::Serialize(GetName(), node["name"]);
		Serialization::Serialize(Width, node["width"]);
		Serialization::Serialize(Height, node["height"]);
	}

	void Area2DComponent::Deserialize(nlohmann::json& node)
	{
		BAMBO_ASSERT_S(m_owner)
		BAMBO_ASSERT_S(m_owner->IsValid())
		BAMBO_ASSERT_S(m_owner->GetWorld())

		Width = Serialization::Deserialize<float>(node["width"]);
		Height = Serialization::Deserialize<float>(node["height"]);
	}
}