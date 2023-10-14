#pragma once
#include "Essentials.h"
#include "Camera.h"
#include "SpriteRenderer.h"
#include "DebugLineRenderer.h"
#include "ShaderProvider.h"
#include "WorldCameraManager.h"
#include "TextureProvider.h"
#include "FontProvider.h"
#include "IID.h"
#include "GameObject.h"
#include "Components/Components.h"
#include "WindowManager.h"
#include "Input.h"
#include "json.hpp"

namespace Bambo
{
	struct WorldContext
	{
		Engine* Engine;
		std::filesystem::path WorldFilePath;
		std::filesystem::path AssetsFolderPath;
	};

	const std::string WORLD_FILE_EXTENSION_DOT = ".bworld";

	class BAMBO_API World
	{
	public:
		World(const WorldContext& worldParameters);
		virtual ~World();

		virtual void Start();
		virtual void Update(float deltaSeconds);
		virtual void OnGUI() {};
		virtual void Render();

		DebugLineRenderer* GetDebugLineRenderer() { return m_debugLineRenderer.get(); }
		SpriteRenderer* GetSpriteRenderer() { return m_spriteRenderer.get(); }
		WorldCameraManager* GetCameraManager() { return &m_cameraManager; }
		WorldContext* GetWorldContext() { return &m_worldParameters; }

		GameObject* CreateGameObject(IID parent = IID{}, IID id = IID{});
		GameObject* GetGameObject(IID id);
		GameObject* GetRoot() { return GetGameObject(m_root); }
		void CreateRoot(IID id);
		void DestroyGameObject(GameObject* gameObject);
		void DestroyGameObject(IID id);
		TextureProvider* GetTextureProvider() { return &m_textureProvider; }
		ShaderProvider* GetShaderProvider() { return &m_shaderProvider; }
		FontProvider* GetFontProvider() { return &m_fontProvider; }

		void SaveWorld();
		void Reset();

		static void CreateNewWorldFile(const std::filesystem::path& assetPath);

		bool IsValidGameObject(IID id);

	private:
		WorldContext m_worldParameters;
		std::unordered_map<IID, UPtr<GameObject>> m_gameObjectMap;
		IID m_root;

		UPtr<SpriteRenderer> m_spriteRenderer;
		UPtr<DebugLineRenderer> m_debugLineRenderer;
		WorldCameraManager m_cameraManager;

		ShaderProvider m_shaderProvider;
		TextureProvider m_textureProvider;
		FontProvider m_fontProvider;

		GameObject* CreateGameObjectInternal(IID parent, IID id);
		void LoadWorld();

	};
}