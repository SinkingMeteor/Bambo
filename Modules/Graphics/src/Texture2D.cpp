#include "Texture2D.h"

namespace Bambo 
{
	Texture2D::Texture2D() :
		m_textureImplementation()
	{
		m_textureImplementation = TextureImplementation::CreateTexture();
	}
}