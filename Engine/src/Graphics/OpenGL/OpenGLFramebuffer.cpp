#include "Graphics/OpenGL/OpenGLFramebuffer.h"

namespace
{
	GLenum GetInternalFormatByTextureType(Bambo::FramebufferTextureType textureType)
	{
		BAMBO_ASSERT_S(textureType != Bambo::FramebufferTextureType::None);

		switch (textureType)
		{
		case Bambo::FramebufferTextureType::Color: return GL_RGBA8;
		case Bambo::FramebufferTextureType::Depth: return GL_DEPTH24_STENCIL8;
		}
	}

	GLenum GetFormatByTextureType(Bambo::FramebufferTextureType textureType)
	{
		BAMBO_ASSERT_S(textureType != Bambo::FramebufferTextureType::None);

		switch (textureType)
		{
		case Bambo::FramebufferTextureType::Color: return GL_RGBA;
		case Bambo::FramebufferTextureType::Depth: return GL_UNSIGNED_INT_24_8;
		}
	}

	GLenum GetAttachmentType(const std::vector<Bambo::FramebufferTextureType>& textureTypes, std::size_t index)
	{
		if (textureTypes[index] == Bambo::FramebufferTextureType::Depth) return GL_DEPTH_STENCIL_ATTACHMENT;

		uint32 colorTexNum = 0;
		for (size_t i = 0; i < index; ++i)
		{
			if (textureTypes[i] == Bambo::FramebufferTextureType::Color)
			{
				++colorTexNum;
			}
		}
		return GL_COLOR_ATTACHMENT0 + colorTexNum;
	}
}

namespace Bambo
{

	OpenGLFramebuffer::OpenGLFramebuffer(const std::vector<FramebufferTextureType>& textureTypes, uint32 textureWidth, uint32 textureHeight) :
		Framebuffer(),
		m_ID(0),
		m_textureWidth(textureWidth),
		m_textureHeight(textureHeight),
		m_textureTypes(textureTypes),
		m_textures()
	{
		CreateNewFramebuffer();
	}

	void OpenGLFramebuffer::CreateNewFramebuffer()
	{
		if (m_ID != 0)
		{
			OpenGLCheck(glDeleteFramebuffers(1, &m_ID));
			OpenGLCheck(glDeleteTextures(m_textures.size(), m_textures.data()));
			m_textures.clear();
		}

		OpenGLCheck(glGenFramebuffers(1, &m_ID));

		if (m_textureTypes.size() == 0)
		{
			OpenGLCheck(glDrawBuffer(GL_NONE));
			return;
		}

		Bind();

		m_textures.resize(m_textureTypes.size());
		OpenGLCheck(glGenTextures(m_textures.size(), m_textures.data()));

		for (size_t i = 0; i < m_textures.size(); ++i)
		{
			OpenGLCheck(glBindTexture(GL_TEXTURE_2D, m_textures[i]));
			AttachTexture(m_textures[i],
				GetInternalFormatByTextureType(m_textureTypes[i]),
				GetAttachmentType(m_textureTypes, i),
				GetFormatByTextureType(m_textureTypes[i]));
		}

		OpenGLCheck(glBindTexture(GL_TEXTURE_2D, 0));

		BAMBO_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		Unbind();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		OpenGLCheck(glDeleteFramebuffers(1, &m_ID));
		OpenGLCheck(glDeleteTextures(m_textures.size(), m_textures.data()));
	}

	void OpenGLFramebuffer::Bind()
	{
		OpenGLCheck(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
	}

	void OpenGLFramebuffer::Unbind()
	{
		OpenGLCheck(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void OpenGLFramebuffer::Resize(uint32 width, uint32 height)
	{
		BAMBO_ASSERT_S(width != 0 && height != 0)

		m_textureWidth = width;
		m_textureHeight = height;
		CreateNewFramebuffer();
	}

	int32 OpenGLFramebuffer::ReadPixel(uint32 attachmentIndex, int32 x, int32 y)
	{
		OpenGLCheck(glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex));
		int32 pixelData;
		OpenGLCheck(glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData));
		return pixelData;

	}

	void OpenGLFramebuffer::AttachTexture(uint32 id, GLenum internalFormat, GLenum attachmentType, GLenum format)
	{
		OpenGLCheck(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_textureWidth, m_textureHeight, 0, format, GL_UNSIGNED_BYTE, nullptr));
		OpenGLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		OpenGLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		OpenGLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
		OpenGLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		OpenGLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		OpenGLCheck(glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, id, 0));
	}
}