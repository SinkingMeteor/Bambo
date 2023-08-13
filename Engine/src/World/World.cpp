#include "World/World.h"
#include "Serialization/WorldSerialization.h"
namespace
{
	const char* WORLD_NAME_KEY = "name";
	const char* WORLD_CONTENT_KEY = "content";
}

DECLARE_LOG_CATEGORY_STATIC(WorldLog)

namespace Bambo
{
	World::World(const std::filesystem::path& worldFilePath) :
		m_worldFilePath(worldFilePath),
		m_gameObjectMap(),
		m_root(),
		m_spriteRenderer(),
		m_shaderProvider(),
		m_textureProvider()
	{
		SPtr<Shader> defaultShader = m_shaderProvider.Load(ToId("DefaultShader"), BamboPaths::BamboResourcesDir + "Shaders/VSpriteDefault.txt", BamboPaths::BamboResourcesDir + "Shaders/FSpriteDefault.txt");
		m_spriteRenderer = std::make_unique<SpriteRenderer>(defaultShader);
		CreateRoot(IID{});
		LoadWorld();
	}

	World::~World()
	{
		Reset();
	}

	void World::Render()
	{
	}

	GameObject* World::CreateGameObject(GameObject* parent, IID id)
	{
		if (!parent)
		{
			parent = m_root;
		}
		return CreateGameObjectInternal(parent, id);
	}

	GameObject* World::GetGameObject(IID id)
	{
		auto it = m_gameObjectMap.find(id);
		if (it == m_gameObjectMap.end()) return nullptr;
		return it->second.get();
	}

	void World::DestroyGameObject(GameObject* gameObject)
	{
		if (!gameObject) return;

		BAMBO_ASSERT_S(gameObject->IsValid())

		IID id = gameObject->GetID();
		m_gameObjectMap.erase(id);
		gameObject = nullptr;
	}

	void World::DestroyGameObject(IID id)
	{
		DestroyGameObject(GetGameObject(id));
	}

	void World::CreateRoot(IID id)
	{
		if (m_root && m_root->IsValid())
		{
			DestroyGameObject(m_root);
		}

		m_root = CreateGameObjectInternal(nullptr, id);
	}

	GameObject* World::CreateGameObjectInternal(GameObject* parent, IID id)
	{
		IID newId = id;
		UPtr<GameObject> newGameObject = std::make_unique<GameObject>(this, newId);

		GameObject* rawPtr = newGameObject.get();

		if (!parent)
		{
			newGameObject->SetParent(nullptr);
		}
		else
		{
			newGameObject->SetParent(parent);
		}

		newGameObject->AddComponent<TagComponent>()->Tag = "GameObject";
		newGameObject->AddComponent<TransformComponent>();

		m_gameObjectMap[newId] = std::move(newGameObject);
		return rawPtr;
	}


	void World::LoadWorld() 
	{
		std::ifstream worldFileStream{ m_worldFilePath };

		if (worldFileStream.fail())
		{
			worldFileStream.close();
			return;
		}
		
		nlohmann::json worldConfigFile{};
		worldFileStream >> worldConfigFile;

		worldFileStream.close();

		BAMBO_ASSERT_S(!worldConfigFile.is_null())
		BAMBO_ASSERT_S(!worldConfigFile[WORLD_NAME_KEY].is_null())

		if (worldConfigFile[WORLD_CONTENT_KEY].is_null())
			return;

		Serialization::Deserialize(*this, worldConfigFile[WORLD_CONTENT_KEY]);
	}
	
	void World::SaveWorld() 
	{
		std::ofstream worldFileStream{ m_worldFilePath };
		BAMBO_ASSERT_S(!worldFileStream.fail())
		
		nlohmann::json worldConfigFile{};

		worldConfigFile[WORLD_NAME_KEY] = m_worldFilePath.filename().replace_extension().string();
		Serialization::Serialize(*this, worldConfigFile[WORLD_CONTENT_KEY]);

		worldFileStream << std::setw(4) << worldConfigFile;
		worldFileStream.close();
	}

	void World::Reset()
	{
		// Remove ???
		for (auto& pair : m_gameObjectMap)
		{
			pair.second.release();
		}

		m_gameObjectMap.clear();
	}
}