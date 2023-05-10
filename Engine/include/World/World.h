#pragma once
#include "engpch.h"
#include "Sprite.h"
#include "Camera.h"
#include "SpriteRenderer.h"
#include "ShaderProvider.h"
#include "TextureProvider.h"
#include "Entity.h"
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
		EntityManager& GetEntityManager() { return m_entityManager; }
	private:
		EntityManager m_entityManager;
		SPtr<Sprite> m_sprite;
		SPtr<Camera> m_camera;
		UPtr<SpriteRenderer> m_spriteRenderer;
	};
}