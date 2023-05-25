#include "OpenGLTexture.h"

namespace Bambo
{
	OpenGLTexture::OpenGLTexture() :
		TextureImplementation(),
		m_id(0u),
		m_width(0u),
		m_height(0u),
		m_internalFormat(GL_SRGB),
		m_imageFormat(GL_SRGB),
		m_wrapS(GL_REPEAT),
		m_wrapT(GL_REPEAT),
		m_filterMin(GL_NEAREST),
		m_filterMax(GL_NEAREST)
	{
		OpenGLCheck(glGenTextures(1, &m_id));
	}

	OpenGLTexture::~OpenGLTexture()
	{
		OpenGLCheck(glDeleteTextures(1, &m_id));
	}

	void OpenGLTexture::LoadFromFile(const std::string& file)
	{
		int channels{};
		stbi_uc* data = stbi_load(file.c_str(), &m_width, &m_height, &channels, 0);
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

		OpenGLCheck(glBindTexture(GL_TEXTURE_2D, m_id));
		OpenGLCheck(glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_imageFormat, GL_UNSIGNED_BYTE, data));
		OpenGLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS));
		OpenGLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT));
		OpenGLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin));
		OpenGLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax));

		OpenGLCheck(glBindTexture(GL_TEXTURE_2D, 0));

		stbi_image_free(data);
	}

	void OpenGLTexture::Use() const
	{
		OpenGLCheck(glBindTexture(GL_TEXTURE_2D, m_id));
	}
}