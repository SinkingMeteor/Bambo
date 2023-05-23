#pragma once
#include "engpch.h"
#include "Camera.h"
#include "SpriteRenderer.h"
#include "ShaderProvider.h"
#include "TextureProvider.h"
#include "IID.h"
#include "Entity.h"
#include "Components.h"
#include "WindowManager.h"
#include "Input.h"

namespace Bambo
{
	class BAMBO_API World final
	{
	public:
		World() = default;
		void Initialize();
		void Update(float deltaSeconds);
		void OnGUI();
		void Render();
		void Dispose();

		Entity& CreateEntity(const char* name);
		Entity& CreateEntity(const char* name, IID id);
		Entity& GetEntityByID(IID id);
		void DestroyEntity(Entity& entity);
		void DestroyEntity(IID id);

		EntityManager& GetEntityManager() { return m_entityManager; }
	private:
		EntityManager m_entityManager;
		std::unordered_map<IID, Entity> m_entityMap;
		UPtr<SpriteRenderer> m_spriteRenderer;
	};
}