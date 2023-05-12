#include "World/World.h"

namespace Bambo
{
	void World::Initialize()
	{
		SPtr<Shader> defaultSpriteShader = ShaderProvider::Get()->Load(ToId("TestShader"), BamboPaths::BamboResourcesDir + "Shaders/VSpriteDefault.txt", BamboPaths::BamboResourcesDir + "Shaders/FSpriteDefault.txt");
		SPtr<Texture2D> texture = TextureProvider::Get()->Load(ToId("TestTexture"), BamboPaths::BamboResourcesDir + "Textures/TestImage.png");
		m_sprite = std::make_shared<Sprite>(texture);
		m_camera = std::make_shared<Camera>();

		m_spriteRenderer = std::make_unique<SpriteRenderer>();
		m_spriteRenderer->Initialize();
		m_spriteRenderer->SetCamera(m_camera);
		m_spriteRenderer->SetDefaultShader(defaultSpriteShader);
	}

	void World::Update(float deltaSeconds)
	{

	}

	void World::Render()
	{
		RenderConfig config{};
		m_spriteRenderer->Render(m_sprite, config);
	}

	Entity World::CreateEntity()
	{
		return CreateEntity(IID{});
	}
	
	Entity World::CreateEntity(IID id)
	{
		flecs::entity ent = m_entityManager.entity();
		m_entityMap[id] = Entity{ent};
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
		//ID
	}



	void World::Dispose()
	{

	}
}