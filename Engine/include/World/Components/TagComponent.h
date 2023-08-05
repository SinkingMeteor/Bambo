#pragma once
#include "Core/Essentials.h"

namespace Bambo
{
	class BAMBO_API TagComponent final : public Component
	{
		COMPONENT_BODY(TagComponent)

	public:
		std::string Tag;

		TagComponent() = default;

		virtual void Serialize(nlohmann::json& node) override
		{
			node["name"] = "TagComponent";
			node["tag"] = Tag;
		}

		virtual void Deserialize(nlohmann::json& node) override
		{
			BAMBO_ASSERT_S(!node["tag"].is_null())

				Tag = node["tag"];
		}
	};
}