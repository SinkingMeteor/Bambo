#pragma once
#include "Core/Essentials.h"
#include "Graphics/Camera.h"
#include "Graphics/SpriteRenderer.h"
#include "Graphics/ShaderProvider.h"
#include "Graphics/TextureProvider.h"
#include "Core/IID.h"
#include "GameObject.h"
#include "World/Components/Components.h"
#include "Window/WindowManager.h"
#include "Window/Input.h"
#include "json.hpp"

namespace Bambo
{
	const std::string WORLD_FILE_EXTENSION_DOT = ".bworld";

	class BAMBO_API World final
	{
	public:
		World(const std::filesystem::path& worldFilePath);
		~World();

		virtual void Update(float deltaSeconds) {};
		virtual void OnGUI() {};
		virtual void Render();

		GameObject* CreateGameObject(GameObject* parent = nullptr, IID id = IID{});
		void CreateRoot(IID id);
		GameObject* GetGameObject(IID id);
		GameObject* GetRoot() { return m_root; }
		void DestroyGameObject(GameObject* gameObject);
		void DestroyGameObject(IID id);

		static void CreateNewWorldFile(const std::filesystem::path& assetPath);
		void SaveWorld();
		void Reset();

		bool IsValidGameObject(IID id) 
		{
			GameObject* go = GetGameObject(id);
			if (!go) return false;

			return go->IsValid();
		}

	private:
		std::filesystem::path m_worldFilePath;
		std::unordered_map<IID, UPtr<GameObject>> m_gameObjectMap;
		GameObject* m_root;
		UPtr<SpriteRenderer> m_spriteRenderer;
		ShaderProvider m_shaderProvider;

		GameObject* CreateGameObjectInternal(GameObject* parent, IID id);
		void LoadWorld();

	};
}