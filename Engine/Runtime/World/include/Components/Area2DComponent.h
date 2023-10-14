#pragma once
#include "Essentials.h"
#include "Component.h"

namespace Bambo
{
	struct BAMBO_API Area2DComponent final : public Component
	{
		COMPONENT_BODY(Area2DComponent);

	public:
		float Width;
		float Height;

		Area2DComponent() = default;

		virtual void Serialize(nlohmann::json& node) override;
		virtual void Deserialize(nlohmann::json& node) override;

		virtual void OnRender(const glm::mat4& ownerGlobalMatrix) override;
	};
}