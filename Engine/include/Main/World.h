#pragma once
#include "engpch.h"
#include "Sprite.h"
#include "Camera.h"
#include "SpriteRenderer.h"
#include "ShaderProvider.h"
#include "TextureProvider.h"
namespace Bambo
{
	class BAMBO_API World final
	{
	public:
		World() = default;
		void Initialize();
		void Update(float deltaSeconds);
		void Render();
		void Dispose();
	private:
		SPtr<Sprite> m_sprite;
		SPtr<Camera> m_camera;
		UPtr<SpriteRenderer> m_spriteRenderer;
	};
}