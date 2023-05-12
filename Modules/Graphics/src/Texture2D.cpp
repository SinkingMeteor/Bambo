#include "Texture2D.h"

namespace Bambo 
{
	Texture2D::Texture2D() :
		m_textureImplementation(),
		m_textureRects()
	{
		m_textureImplementation = TextureImplementation::CreateTexture();
		m_textureRects.push_back(GetTextureRect());
	}

	Texture2D::Texture2D(std::vector<RectInt>&& textureRects) :
		m_textureImplementation(),
		m_textureRects(std::move(textureRects))
	{}

}