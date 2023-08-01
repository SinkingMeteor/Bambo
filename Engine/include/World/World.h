#pragma once
#include "Core/Essentials.h"
#include "Graphics/Camera.h"
#include "Graphics/SpriteRenderer.h"
#include "Graphics/ShaderProvider.h"
#include "Graphics/TextureProvider.h"
#include "Core/IID.h"
#include "Entity.h"
#include "World/Components/Components.h"
#include "Window/WindowManager.h"
#include "Window/Input.h"
#include "json.hpp"

namespace Bambo
{
	const std::string WORLD_FILE_EXTENSION_DOT = ".bworld";

	class BAMBO_API World final
	{
		friend Entity;
	public:
		World(const std::filesystem::path& worldFilePath);
		~World();

		virtual void Update(float deltaSeconds) {};
		virtual void OnGUI() {};
		virtual void Render();

		Entity& CreateEntity();
		Entity& CreateEntity(IID parentId);
		Entity& CreateEntity(const char* name);
		Entity& CreateEntity(IID parentId, const char* name);
		Entity& CreateEntity(IID parentId, const char* name, IID selfId);
		Entity& GetEntityByID(IID id);

		Entity& GetRoot() { return m_entityMap[m_rootEntityId]; }
		void DestroyEntity(Entity& entity);
		void DestroyEntity(IID id);

		EntityManager& GetEntityManager() { return m_entityManager; }

		static void CreateNewWorldFile(const std::filesystem::path& assetPath);
		void SaveWorld();
		void Reset();

	private:
		std::filesystem::path m_worldFilePath;
		EntityManager m_entityManager;
		std::unordered_map<IID, Entity> m_entityMap;
		IID m_rootEntityId;
		UPtr<SpriteRenderer> m_spriteRenderer;
		ShaderProvider m_shaderProvider;

		void CreateRoot();
		void LoadWorld();
		void ChangeID(Entity& entity, IID oldID, IID newID);
	};
}