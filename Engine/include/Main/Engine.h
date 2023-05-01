#pragma once
#include "engpch.h"
#include "Window.h"
#include "Time/Timer.h"
#include "WindowManager.h"
#include "AudioManager.h"
#include "RenderManager.h"
#include "TextureProvider.h"
#include "ShaderProvider.h"
#include "Camera.h"
#include "Sprite.h"
namespace Bambo
{
	class Engine final
	{
	public:
		Engine() = default;
		Engine(const Engine& engine) = delete;
		Engine& operator=(const Engine& engine) = delete;

		void Initialize();
		int Run();
	private:
		TextureProvider m_textureProvider;
		ShaderProvider m_shaderProvider;
		UPtr<Sprite> m_sprite;
		SPtr<Camera> m_camera;

		void Update(float deltaTime);
		void Render();
		void Dispose();
	};
}