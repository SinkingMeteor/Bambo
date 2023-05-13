#include "Texture2D.h"

namespace Bambo 
{
	Texture2D::Texture2D() :
		m_textureImplementation(),
		m_textureRects()
	{
		m_textureImplementation = TextureImplementation::CreateTexture();
	}

	void Texture2D::LoadFromFile(const std::string& filePath)
	{
		m_textureRects.clear();
		m_textureImplementation->LoadFromFile(filePath);
		//@TODO: Loading meta files
		m_textureRects.push_back(GetTextureRect());
	}

}