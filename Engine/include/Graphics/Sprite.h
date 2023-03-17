#pragma once
#include "pch.h"
#include "Common/Resource/TextureProvider.h"
#include "Graphics/Rect.h"
#include "Graphics/Vertex.h"

namespace Bambo 
{
	class Sprite 
	{
	public:
		Sprite();
		Sprite(std::shared_ptr<Texture2D> texture, const RectInt& rect);
		void SetRect(const RectInt& rect);
		void SetTexture(std::shared_ptr<Texture2D> texture);
	private:
		std::array<Vertex, 4> m_vertices;
		std::shared_ptr<Texture2D> m_texture;
		RectInt m_spriteRect;
	};
}