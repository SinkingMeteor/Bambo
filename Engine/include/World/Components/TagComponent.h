#pragma once
#include "engpch.h"

namespace Bambo
{
	class BAMBO_API TagComponent final : public Component
	{
	public:
		std::string Tag;

		TagComponent() = default;
		TagComponent(const std::string& tag) : Tag(tag) {}

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