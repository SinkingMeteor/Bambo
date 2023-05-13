#include "World/World.h"

namespace Bambo
{
	void World::Initialize()
	{
		SPtr<Shader> defaultSpriteShader = ShaderProvider::Get()->Load(ToId("TestShader"), BamboPaths::BamboResourcesDir + "Shaders/VSpriteDefault.txt", BamboPaths::BamboResourcesDir + "Shaders/FSpriteDefault.txt");
		SPtr<Texture2D> texture = TextureProvider::Get()->Load(ToId("TestTexture"), BamboPaths::BamboResourcesDir + "Textures/TestImage.png");

		m_spriteRenderer = std::make_unique<SpriteRenderer>();
		m_spriteRenderer->Initialize();
		m_spriteRenderer->SetDefaultShader(defaultSpriteShader);

		Entity& camera = CreateEntity();
		camera.AddComponent<CameraComponent>(CameraComponent{ {640.0f, 360.0f} });

		Entity& sprite = CreateEntity();
		sprite.AddComponent<SpriteComponent>(SpriteComponent{ texture });
	}

	void World::Update(float deltaSeconds)
	{

	}

	void World::Render()
	{
		m_entityManager.each([this](CameraComponent& camera, TransformComponent& transform)
		{
			glm::mat4 projViewMatrix = camera.GetProjectionMatrix() * camera.GetViewMatrix(transform.GetTransform());
			m_entityManager.each([this, &projViewMatrix](SpriteComponent& sprite, TransformComponent& transform)
			{
				m_spriteRenderer->Render(sprite.Texture, sprite.Texture->GetTextureRects()[sprite.SpriteRectIndex], transform.GetTransform(), projViewMatrix);
			});
		});

	}

	Entity& World::CreateEntity()
	{
		return CreateEntity(IID{});
	}
	
	Entity& World::CreateEntity(IID id)
	{
		BAMBO_ASSERT_S(m_entityMap.find(id) == m_entityMap.end())
		flecs::entity ent = m_entityManager.entity();
		ent.set<IDComponent>(IDComponent{ id });
		ent.add<TransformComponent>();
		m_entityMap[id] = Entity{ ent };
		return m_entityMap[id];
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