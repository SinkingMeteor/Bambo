#include "Graphics/Sprite.h"

namespace Bambo 
{
	Sprite::Sprite() :
		m_vertices(),
		m_texture(nullptr),
		m_spriteRect(0, 0, 0, 0)
	{}

	Sprite::Sprite(std::shared_ptr<Texture2D> texture, const RectInt& rect):
		m_vertices(),
		m_texture(texture),
		m_spriteRect(rect)
	{
	}

	void Sprite::SetRect(const RectInt& rect) 
	{
		m_spriteRect = rect;
	}

	void Sprite::SetTexture(std::shared_ptr<Texture2D> texture) 
	{
		m_texture = texture;
	}

}