#include "Sprite.h"

namespace Bambo
{
	Sprite::Sprite() :
		m_texture(nullptr),
		m_origin(0.5f, 0.5f, 0.5f),
		m_texRectIndex(0)
	{}

	RectInt Sprite::GetRect() const
	{
		if (!m_texture)
		{
			return RectInt{};
		}

		return m_texture->GetTextureRects()[m_texRectIndex];
	}

	glm::vec3 Sprite::GetOriginOffset() const
	{
		if (!m_texture) return glm::vec3{ 0.0f };

		RectInt texRect = m_texture->GetTextureRect();
		return glm::vec3{ -texRect.Width * m_origin.x, -texRect.Height * m_origin.y, 0.0f };
	}
}