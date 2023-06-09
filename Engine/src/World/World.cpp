#include "World/World.h"

namespace
{
	const char* WORLD_NAME_KEY = "WorldName";
	const char* WORLD_CONTENT_KEY = "Content";
}

DECLARE_LOG_CATEGORY_STATIC(WorldLog)

namespace Bambo
{
	World::World(const std::filesystem::path& worldFilePath) :
		m_worldFilePath(worldFilePath),
		m_entityManager(),
		m_entityMap(),
		m_rootEntityId(),
		m_spriteRenderer()
	{
		Initialize();
		LoadWorld();
	}

	World::~World()
	{
		Dispose();
	}

	void World::Initialize()
	{
		CreateRoot();
		m_spriteRenderer = std::make_unique<SpriteRenderer>();
	}

	void World::Render()
	{
		m_entityManager.each([this](CameraComponent& camera, TransformComponent& transform)
		{
			glm::mat4 projViewMatrix = camera.Camera.GetProjectionMatrix() * glm::inverse(transform.GetTransform());
			m_entityManager.each([this, &projViewMatrix](SpriteComponent& sprite, TransformComponent& transform)
			{
				m_spriteRenderer->Render(sprite.Texture, sprite.Texture->GetTextureRects()[sprite.SpriteRectIndex], transform.GetTransform(), projViewMatrix);
			});
		});

	}

	Entity& World::CreateEntity()
	{
		IID id{};
		std::string nameId = "Entity_";
		nameId += std::to_string(id);
		return CreateEntity(m_rootEntityId, nameId.c_str(), id);
	}

	Entity& World::CreateEntity(const char* name)
	{
		return CreateEntity(m_rootEntityId, name, IID{});
	}

	Entity& World::CreateEntity(IID parentId)
	{
		IID id{};
		std::string nameId = "Entity_";
		nameId += std::to_string(id);
		return CreateEntity(parentId, nameId.c_str(), id);
	}

	Entity& World::CreateEntity(IID parentId, const char* name)
	{
		return CreateEntity(parentId, name, IID{});
	}

	Entity& World::CreateEntity(IID parentId, const char* name, IID selfId)
	{
		BAMBO_ASSERT_S(m_entityMap.find(selfId) == m_entityMap.end())
		BAMBO_ASSERT_S(m_entityMap.find(parentId) != m_entityMap.end())

		Entity& parentEntity = m_entityMap[parentId];
		flecs::entity ent = m_entityManager.entity(name);
		ent.child_of(parentEntity.GetInternalEntity());

		ent.set<IDComponent>(IDComponent{ selfId });
		ent.set<TagComponent>(TagComponent{ name });
		ent.add<TransformComponent>();
		m_entityMap[selfId] = Entity{ ent };
		return m_entityMap[selfId];
	}
	
	Entity& World::GetEntityByID(IID id)
	{
		BAMBO_ASSERT_S(m_entityMap.find(id) != m_entityMap.end())
		BAMBO_ASSERT_S(!m_entityMap[id].IsDestroyed())
		return m_entityMap[id];
	}

	void World::DestroyEntity(IID id)
	{
		BAMBO_ASSERT_S(m_entityMap.find(id) != m_entityMap.end())
		Entity& ent = m_entityMap[id];
		ent.GetInternalEntity().destruct();
		m_entityMap.erase(id);
	}

	void World::DestroyEntity(Entity& entity)
	{
		IDComponent* id = entity.GetComponent<IDComponent>();
		BAMBO_ASSERT_S(m_entityMap.find(id->ID) != m_entityMap.end())
		m_entityMap.erase(id->ID);
		entity.GetInternalEntity().destruct();
	}

	void World::CreateRoot()
	{
		flecs::entity root = m_entityManager.entity("Root");
		root.set<IDComponent>(IDComponent{ m_rootEntityId });
		root.set<TagComponent>(TagComponent{ "Root" });
		root.add<TransformComponent>();
		m_entityMap[m_rootEntityId] = Entity{ root };
	}

	void World::CreateNewWorldFile(const std::filesystem::path& assetPath) 
	{
		std::ofstream outProject{ assetPath };

		BAMBO_ASSERT_S(!outProject.fail())

		nlohmann::json rootConfig{};
		rootConfig[WORLD_NAME_KEY] = assetPath.filename().replace_extension().string();
		outProject << std::setw(4) << rootConfig;


		outProject.close();
	}

	void World::LoadWorld() 
	{
		std::ifstream worldFileStream{ m_worldFilePath };
		BAMBO_ASSERT_S(!worldFileStream.fail())
		
		nlohmann::json worldConfigFile{};
		worldFileStream >> worldConfigFile;

		worldFileStream.close();

		BAMBO_ASSERT_S(!worldConfigFile.is_null())
		BAMBO_ASSERT_S(!worldConfigFile[WORLD_NAME_KEY].is_null())

		if (worldConfigFile[WORLD_CONTENT_KEY].is_null())
			return;

		m_entityManager.reset();

		std::string worldString = worldConfigFile[WORLD_CONTENT_KEY].get<std::string>();
		flecs::string_view worldStringView{ worldString.c_str() };

		m_entityManager.from_json(worldStringView);
	}
	
	void World::SaveWorld() 
	{
		std::ofstream worldFileStream{ m_worldFilePath };
		BAMBO_ASSERT_S(!worldFileStream.fail())
		
		nlohmann::json worldConfigFile{};

		flecs::string jsonedWorld = m_entityManager.to_json();
		//@TODO: STORE NAME ??
		worldConfigFile[WORLD_NAME_KEY] = "Hello world";
		worldConfigFile[WORLD_CONTENT_KEY] = jsonedWorld.c_str();

		worldFileStream << std::setw(4) << worldConfigFile;
		worldFileStream.close();
	}

	void World::Dispose()
	{
		m_entityManager.reset();
	}
}