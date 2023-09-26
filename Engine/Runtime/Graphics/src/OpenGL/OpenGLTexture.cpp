#include "OpenGL/OpenGLTexture.h"

namespace
{
	void GetTexFormats(Bambo::TexChannelsAmount channelsAmount, uint32& internalFormat, uint32& imageFormat)
	{
		switch (channelsAmount)
		{
		case Bambo::TexChannelsAmount::R: imageFormat = GL_RED; internalFormat = GL_RED; break;
		case Bambo::TexChannelsAmount::RGB: imageFormat = GL_RGB; internalFormat = GL_RGB8; break;
		case Bambo::TexChannelsAmount::RGBA: imageFormat = GL_RGBA; internalFormat = GL_RGBA8; break;
		}
	}
}

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

	void OpenGLTexture::LoadFromBuffer(const TextureBuffer& buffer)
	{
		Vector2u size = buffer.GetSize();
		m_width = static_cast<int32>(size.X);
		m_height = static_cast<int32>(size.Y);

		const uint8* data = buffer.GetData();

		TexChannelsAmount channelsAmount = buffer.GetChannelsAmounts();
		GetTexFormats(channelsAmount, m_internalFormat, m_imageFormat);

		OpenGLCheck(glBindTexture(GL_TEXTURE_2D, m_id));

		if (channelsAmount == TexChannelsAmount::R)
		{
			OpenGLCheck(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
		}

		OpenGLCheck(glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_imageFormat, GL_UNSIGNED_BYTE, data));
		OpenGLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS));
		OpenGLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT));
		OpenGLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin));
		OpenGLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax));

		OpenGLCheck(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void OpenGLTexture::Use() const
	{
		OpenGLCheck(glBindTexture(GL_TEXTURE_2D, m_id));
	}

	void OpenGLTexture::AddSubTex(const RectUInt& rect, const TextureBuffer& buffer)
	{
		uint32 internalFormat = 0u;
		uint32 imageFormat = 0u;

		TexChannelsAmount channelsAmount = buffer.GetChannelsAmounts();
		GetTexFormats(channelsAmount, internalFormat, imageFormat);

		Use();

		OpenGLCheck(glTexSubImage2D(GL_TEXTURE_2D, 0, rect.Left, rect.Top, rect.Width, rect.Height, imageFormat, GL_UNSIGNED_BYTE, buffer.GetData()));
	}

	void OpenGLTexture::AddSubTex(const RectUInt& rect, const uint8* data, TexChannelsAmount channels)
	{
		uint32 internalFormat = 0u;
		uint32 imageFormat = 0u;

		GetTexFormats(channels, internalFormat, imageFormat);

		Use();

		OpenGLCheck(glTexSubImage2D(GL_TEXTURE_2D, 0, rect.Left, rect.Top, rect.Width, rect.Height, imageFormat, GL_UNSIGNED_BYTE, data));
	}

}