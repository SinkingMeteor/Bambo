#include "Serialization/WorldSerialization.h"

namespace Bambo
{
	namespace Serialization
	{
		template<typename T>
		void SerializeComponent(nlohmann::json& node, flecs::entity& entity, ecs_id_t id)
		{
			node["components"].push_back({});
			((T*)entity.get_mut(id))->Serialize(node["components"].back());
		}

		void SerializeEntity(flecs::entity& entity, World& world, nlohmann::json& node)
		{
			EntityManager& entityManager = world.GetEntityManager();

			const ecs_type_t* type = ecs_get_type(entityManager, entity);
			
			for (int32 i = 0; i < type->count; i++) 
			{
				if (type->array[i] == entityManager.id<IDComponent>())
					SerializeComponent<IDComponent>(node, entity, type->array[i]);
				else if (type->array[i] == entityManager.id<TransformComponent>())
					SerializeComponent<TransformComponent>(node, entity, type->array[i]);
				else if (type->array[i] == entityManager.id<SpriteComponent>())
					SerializeComponent<SpriteComponent>(node, entity, type->array[i]);
				else if (type->array[i] == entityManager.id<TagComponent>())
					SerializeComponent<TagComponent>(node, entity, type->array[i]);
				else if (type->array[i] == entityManager.id<CameraComponent>())
					SerializeComponent<CameraComponent>(node, entity, type->array[i]);
			}

			ecs_iter_t it = ecs_children(entityManager, entity);

			while (ecs_children_next(&it))
			{
				for (int i = 0; i < it.count; ++i)
				{
					ecs_entity_t child = it.entities[i];
					flecs::entity childEntity = entityManager.entity(child);

					node["children"].push_back({});
					SerializeEntity(childEntity, world, node["children"].back());
				}
			}
		}

		void Serialize(World& world, nlohmann::json& node)
		{
			SerializeEntity(world.GetRoot().GetInternalEntity(), world, node);
		}

		void DeserializeEntity(Entity& entity, World& world, nlohmann::json& node)
		{
			nlohmann::json& componentsNode = node["components"];
			for (size_t i = 0; i < componentsNode.size(); ++i)
			{
				nlohmann::json& compNode = componentsNode.at(i);
				if (compNode["name"] == "TransformComponent")
					entity.GetComponent<TransformComponent>()->Deserialize(compNode);
				else if (compNode["name"] == "TagComponent")
					entity.GetComponent<TagComponent>()->Deserialize(compNode);
				else if (compNode["name"] == "IDComponent")
					entity.SetID(compNode["id"].get<uint64>());
				else if (compNode["name"] == "CameraComponent")
					entity.AddComponent<CameraComponent>()->Deserialize(compNode);
				else if (compNode["name"] == "SpriteComponent")
					entity.AddComponent<SpriteComponent>()->Deserialize(compNode);
			}

			nlohmann::json& childrenNode = node["children"];
			if (childrenNode.is_null() || childrenNode.size() == 0) return;

			for (size_t i = 0; i < childrenNode.size(); ++i)
			{
				Entity& childEntity = world.CreateEntity(entity.GetID());
				BAMBO_ASSERT_S(childEntity.IsValid())
				DeserializeEntity(childEntity, world, childrenNode.at(i));
			}
		}

		void Deserialize(World& world, nlohmann::json& node)
		{
			world.Reset();
			DeserializeEntity(world.GetRoot(), world, node);
		}
	}
}