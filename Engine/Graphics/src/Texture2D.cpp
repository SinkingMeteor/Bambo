#include "Texture2D.h"

namespace Bambo 
{
	Texture2D::Texture2D():
		m_id(0),
		m_width(0),
		m_height(0),
		m_internalFormat(GL_SRGB),
		m_imageFormat(GL_SRGB),
		m_wrapS(GL_REPEAT),
		m_wrapT(GL_REPEAT),
		m_filterMin(GL_NEAREST),
		m_filterMax(GL_NEAREST)
	{
		glGenTextures(1, &m_id);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_id);
	}

	void Texture2D::LoadFromFile(const std::string& file)
	{
		int channels{};
		uchar* data = stbi_load(file.c_str(), &m_width, &m_height, &channels, 0);
		BAMBO_ASSERT(data, "Failed to load image");

		if (channels == 4) {
			m_internalFormat = GL_RGBA8;
			m_imageFormat = GL_RGBA;
		}
		else
		{
			m_internalFormat = GL_RGB8;
			m_imageFormat = GL_RGB;
		}

		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_imageFormat, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);
	}

	void Texture2D::Use() const 
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture2D::StopUse()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}