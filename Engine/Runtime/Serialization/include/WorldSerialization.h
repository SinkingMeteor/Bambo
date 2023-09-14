#pragma once
#include "Essentials.h"
#include "World.h"
namespace Bambo
{
	namespace Serialization
	{
		BAMBO_API void Serialize(World& world, nlohmann::json& node);
		BAMBO_API void Deserialize(World& world, nlohmann::json& node);
	}
}