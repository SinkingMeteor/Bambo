#pragma once
#include "pch.h"
#include "Graphics.h"
#include "TextureProvider.h"
#include "Rect.h"
#include "Vertex.h"
#include "Interfaces/ITransformable.h"
#include "Interfaces/IRenderable.h"
#include "RenderConfig.h"
#include "RendererImplementation.h"

namespace Bambo 
{
	class BAMBO_API Sprite final : public ITransformable
	{
	public:
		Sprite(std::shared_ptr<Texture2D> texture);
		Sprite(std::shared_ptr<Texture2D> texture, const RectInt& rect);
		void SetRect(const RectInt& rect);
		void SetTexture(std::shared_ptr<Texture2D> texture);
		RectFloat GetLocalBounds() const;
		virtual Transform& GetTransform() override { return m_transform; }
		void SetPivot(const glm::vec2& relativePivot);
	private:
		std::shared_ptr<Texture2D> m_texture;
		RectInt m_spriteRect;
		Transform m_transform;

		void UpdatePosition();
		void UpdateTexCoords();

		friend class SpriteRenderer;
	};
}