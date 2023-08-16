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

	class BAMBO_API World
	{
	public:
		World(const std::filesystem::path& worldFilePath);
		virtual ~World();

		virtual void Update(float deltaSeconds);
		virtual void OnGUI() {};
		virtual void Render();

		SpriteRenderer* GetRenderer() { return m_spriteRenderer.get(); }
		GameObject* CreateGameObject(IID parent = IID{}, IID id = IID{});
		GameObject* GetGameObject(IID id);
		GameObject* GetRoot() { return GetGameObject(m_root); }
		void CreateRoot(IID id);
		void DestroyGameObject(GameObject* gameObject);
		void DestroyGameObject(IID id);
		TextureProvider* GetTextureProvider() { return &m_textureProvider; }
		void SaveWorld();
		void Reset();

		static void CreateNewWorldFile(const std::filesystem::path& assetPath);

		bool IsValidGameObject(IID id);

	private:
		std::filesystem::path m_worldFilePath;
		std::unordered_map<IID, UPtr<GameObject>> m_gameObjectMap;
		IID m_root;
		UPtr<SpriteRenderer> m_spriteRenderer;
		ShaderProvider m_shaderProvider;
		TextureProvider m_textureProvider;

		GameObject* CreateGameObjectInternal(IID parent, IID id);
		void LoadWorld();

	};
}