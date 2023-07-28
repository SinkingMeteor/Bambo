#pragma once
#include "engpch.h"
#include "IID.h"

namespace Bambo
{
	class BAMBO_API IDComponent final : public Component
	{
	public:
		IID ID;

		IDComponent() = default;
		IDComponent(IID id) : ID(id) {}
		IDComponent(const IDComponent& id) = default;

		virtual void Serialize(nlohmann::json& node) override
		{
			node["name"] = "IDComponent";
			node["id"] = static_cast<uint64>(ID);
		}

		virtual void Deserialize(nlohmann::json& node) override
		{
			ID = node["id"].get<uint64>();
		}
	};
}