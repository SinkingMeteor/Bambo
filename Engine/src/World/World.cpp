#include "World/World.h"

namespace Bambo
{
	void World::Initialize()
	{
		SPtr<Shader> defaultSpriteShader = ShaderProvider::Get()->Load(ToId("TestShader"), BamboPaths::BamboResourcesDir + "Shaders/VSpriteDefault.txt", BamboPaths::BamboResourcesDir + "Shaders/FSpriteDefault.txt");

		m_spriteRenderer = std::make_unique<SpriteRenderer>();
		m_spriteRenderer->Initialize();
		m_spriteRenderer->SetDefaultShader(defaultSpriteShader);
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

	Entity& World::CreateEntity(const char* name)
	{
		return CreateEntity(name, IID{});
	}
	
	Entity& World::CreateEntity(const char* name, IID id)
	{
		BAMBO_ASSERT_S(m_entityMap.find(id) == m_entityMap.end())
		flecs::entity ent = m_entityManager.entity(name);
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
		IDComponent* id = entity.GetComponent<IDComponent>();
		BAMBO_ASSERT_S(m_entityMap.find(id->ID) != m_entityMap.end())
		m_entityMap.erase(id->ID);
		entity.GetInternalEntity().destruct();
	}

	void World::Dispose()
	{
		m_entityManager.reset();
	}
}