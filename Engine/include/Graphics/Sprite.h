#pragma once
#include "pch.h"
#include "Common/Resource/TextureProvider.h"
#include "Graphics/Rect.h"
#include "Graphics/Vertex.h"
#include "Common/Interfaces/ITransformable.h"
#include "Common/Interfaces/IRenderable.h"
#include "Common/Interfaces/IRenderTarget.h"
#include "Graphics/RenderConfig.h"
namespace Bambo 
{
	class Sprite final : public ITransformable, public IRenderable
	{
	public:
		Sprite(std::shared_ptr<Texture2D> texture);
		Sprite(std::shared_ptr<Texture2D> texture, const RectInt& rect);
		void SetRect(const RectInt& rect);
		void SetTexture(std::shared_ptr<Texture2D> texture);
		RectFloat GetLocalBounds() const;

		virtual Transform& GetTransform() override { return m_transform; }
		virtual void Render(IRenderTarget& renderTarget, const RenderConfig& config) override;



	private:
		void UpdatePosition();
		void UpdateTexCoords();

		std::array<Vertex, 4> m_vertices;
		std::shared_ptr<Texture2D> m_texture;
		RectInt m_spriteRect;

		Transform m_transform;
	};
}