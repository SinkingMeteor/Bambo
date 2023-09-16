#pragma once
#include "Essentials.h"
#include "Camera.h"
#include "SpriteRenderer.h"
#include "ShaderProvider.h"
#include "TextureProvider.h"
#include "IID.h"
#include "GameObject.h"
#include "Components/Components.h"
#include "WindowManager.h"
#include "Input.h"
#include "json.hpp"

namespace Bambo
{
	struct WorldParameters
	{
		std::filesystem::path WorldFilePath;
		std::filesystem::path AssetsFolderPath;
	};

	const std::string WORLD_FILE_EXTENSION_DOT = ".bworld";

	class BAMBO_API World
	{
	public:
		World(const WorldParameters& worldParameters);
		virtual ~World();

		virtual void Start();
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
		WorldParameters m_worldParameters;
		std::unordered_map<IID, UPtr<GameObject>> m_gameObjectMap;
		IID m_root;
		UPtr<SpriteRenderer> m_spriteRenderer;
		SPtr<ResourceCache> m_resourceCache;

		ShaderProvider m_shaderProvider;
		TextureProvider m_textureProvider;

		std::vector<glm::mat4> m_globalMatrices;

		GameObject* CreateGameObjectInternal(IID parent, IID id);
		void LoadWorld();

	};
}