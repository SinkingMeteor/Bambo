#include "Serialization/WorldSerialization.h"

namespace Bambo
{
	namespace Serialization
	{
		void Serialize(World& world, nlohmann::json& node)
		{
			world.GetRoot()->Serialize(node);
		}

		void Deserialize(World& world, nlohmann::json& node)
		{
			world.Reset();
			IID id = node["id"].get<uint64_t>();
			world.CreateRoot(id);
			world.GetRoot()->Deserialize(node);
		}
	}
}