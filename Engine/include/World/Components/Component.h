#pragma once
#include "engpch.h"

namespace Bambo
{
	class Component
	{
	public:
		virtual ~Component() = default;
		virtual void Serialize(nlohmann::json& node) = 0;
		virtual void Deserialize(nlohmann::json& node) = 0;
	};
}
