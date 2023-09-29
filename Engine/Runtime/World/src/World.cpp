#include "World.h"
#include "WorldSerialization.h"
#include "DrawDebugHelpers.h"
namespace
{
	const char* WORLD_NAME_KEY = "name";
	const char* WORLD_CONTENT_KEY = "content";
	const char* ID_COUNTER = "idcounter";
}

DECLARE_LOG_CATEGORY_STATIC(WorldLog)

namespace Bambo
{
	World::World(const WorldParameters& worldParameters) :
		m_worldParameters(worldParameters),
		m_gameObjectMap(),
		m_root(),
		m_spriteRenderer(),
		m_debugLineRenderer(),
		m_cameraManager(),
		m_shaderProvider(),
		m_textureProvider(),
		m_fontProvider(),
		m_globalMatrices()
	{
		SPtr<Shader> defaultSpriteShader = m_shaderProvider.Load(BamboPaths::EngineResourcesDir / "Shaders/SpriteDefault.shader");
		m_spriteRenderer = std::make_unique<SpriteRenderer>(defaultSpriteShader);
		SPtr<Shader> defaultLineShader = m_shaderProvider.Load(BamboPaths::EngineResourcesDir / BamboPaths::EngineDefaultShaderPath_A);
		m_debugLineRenderer = std::make_unique<DebugLineRenderer>(defaultLineShader);

		CreateRoot(IID::GenerateNew());
		LoadWorld();

		SPtr<Font> font = m_fontProvider.Load(BamboPaths::EngineResourcesDir / "Fonts/arial.ttf");
		SpriteComponent* sprite = CreateGameObject()->AddComponent<SpriteComponent>();
		sprite->SetTexture(font->GetPage(16u)->FontTexture);
	}

	World::~World()
	{
		Reset();
	}

	void World::Start()
	{
		auto it = m_gameObjectMap.begin();
		auto end = m_gameObjectMap.end();
		for (; it != end; ++it)
		{
			it->second->Start();
		}
	}

	void World::Update(float deltaSeconds)
	{
		GameObject* root = GetGameObject(m_root);
		std::vector<IID>& children = root->GetChildren();
		for (size_t i = 0; i < children.size(); ++i)
		{
			GameObject* child = GetGameObject(children[i]);
			child->Tick(deltaSeconds);
		}
	}

	void World::Render()
	{
		GameObject* root = GetGameObject(m_root);
		
		DrawDebugLine(this, { 0.0f, 0.0f, 0.0f }, { 100.0f, 100.0f, 0.0f }, Color::Green());
		DrawDebugRect(this, {-50.0f, 50.0f, 200.0f, 200.0f}, Color::Red());

		SPtr<Font> font = m_fontProvider.Load(BamboPaths::EngineResourcesDir / "Fonts/arial.ttf");
		Page* page = font->GetPage(16u);
		BAMBO_ASSERT_S(page)

		for (auto& pair : page->Glyphs)
		{
			RectUInt rect = pair.second.TextureRect;

			float left = static_cast<float>(rect.Left);
			float top = static_cast<float>(rect.Top);
			float width = static_cast<float>(rect.Width);
			float height = static_cast<float>(rect.Height);

			DrawDebugRect(this, RectFloat{left - 64.0f, -top + 64.0f, width, height}, Color::White());
		}


		m_globalMatrices.push_back(root->GetTransform()->GetMatrix());
		std::vector<IID>& children = root->GetChildren();
		for (size_t i = 0; i < children.size(); ++i)
		{
			GameObject* child = GetGameObject(children[i]);
			child->OnRender(m_globalMatrices, 0);
		}

		m_spriteRenderer->Render(this, m_globalMatrices);
		m_debugLineRenderer->Render(this);

		m_globalMatrices.clear();
	}

	GameObject* World::CreateGameObject(IID parent, IID id)
	{
		if (!parent.IsValid())
		{
			parent = m_root;
		}

		if (!id.IsValid())
		{
			id = IID::GenerateNew();
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

		gameObject->SetParent(IID{});
		std::vector<IID>& children = gameObject->GetChildren();
	
		for (size_t i = 0; i < children.size(); ++i)
		{
			DestroyGameObject(children[i]);
		}

		gameObject->End();

		IID id = gameObject->GetID();
		m_gameObjectMap.erase(id);
	}

	void World::DestroyGameObject(IID id)
	{
		DestroyGameObject(GetGameObject(id));
	}

	bool World::IsValidGameObject(IID id)
	{
		GameObject* go = GetGameObject(id);
		if (!go) return false;

		return go->IsValid();
	}

	void World::CreateRoot(IID id)
	{
		if (m_root.IsValid())
		{
			DestroyGameObject(m_root);
		}

		m_root = CreateGameObjectInternal(IID{}, id)->GetID();
	}

	GameObject* World::CreateGameObjectInternal(IID parentId, IID id)
	{
		UPtr<GameObject> newGameObject = std::make_unique<GameObject>(this, id);

		GameObject* rawPtr = newGameObject.get();
		newGameObject->SetParent(parentId);

		m_gameObjectMap[id] = std::move(newGameObject);
		return rawPtr;
	}


	void World::LoadWorld() 
	{
		std::ifstream worldFileStream{ m_worldParameters.WorldFilePath };

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

		IID::SetGlobalCounter(worldConfigFile[ID_COUNTER].get<uint64>());

		if (worldConfigFile[WORLD_CONTENT_KEY].is_null())
			return;

		Serialization::Deserialize(*this, worldConfigFile[WORLD_CONTENT_KEY]);
	}
	
	void World::SaveWorld() 
	{
		std::ofstream worldFileStream{ m_worldParameters.WorldFilePath };
		BAMBO_ASSERT_S(!worldFileStream.fail())
		
		nlohmann::json worldConfigFile{};

		worldConfigFile[WORLD_NAME_KEY] = m_worldParameters.WorldFilePath.filename().replace_extension().string();
		worldConfigFile[ID_COUNTER] = IID::GetGlobalCounter();
		Serialization::Serialize(*this, worldConfigFile[WORLD_CONTENT_KEY]);

		worldFileStream << std::setw(4) << worldConfigFile;
		worldFileStream.close();
	}

	void World::Reset()
	{
		DestroyGameObject(m_root);
	}
}