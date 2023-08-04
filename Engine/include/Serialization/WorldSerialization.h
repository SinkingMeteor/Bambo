#pragma once
#include "Core/Essentials.h"
#include "World/World.h"
namespace Bambo
{
	namespace Serialization
	{
		BAMBO_API void Serialize(World& world, nlohmann::json& node) {}
		BAMBO_API void Deserialize(World& world, nlohmann::json& node) {}
	}
}