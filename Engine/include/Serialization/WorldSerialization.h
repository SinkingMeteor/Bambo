#pragma once
#include "engpch.h"
#include "World/World.h"
namespace Bambo
{
	namespace Serialization
	{
		void BAMBO_API Serialize(World& world, nlohmann::json& node);
		void BAMBO_API Deserialize(World& world, nlohmann::json& node);
	}
}