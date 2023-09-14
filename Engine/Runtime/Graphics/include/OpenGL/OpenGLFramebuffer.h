#pragma once
#include "Essentials.h"
#include "Framebuffer.h"
#include "OpenGL/OpenGLCheck.h"

namespace Bambo
{
	class OpenGLFramebuffer final : public Framebuffer
	{
	public:
		OpenGLFramebuffer() = delete;
		OpenGLFramebuffer(const std::vector<FramebufferTextureType>& textureTypes, uint32 textureWidth, uint32 textureHeight);
		virtual ~OpenGLFramebuffer();
		OpenGLFramebuffer(const OpenGLFramebuffer&) = delete;
		OpenGLFramebuffer& operator=(const OpenGLFramebuffer&) = delete;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32 GetCurrentTextureWidth() const override { return m_textureWidth; }
		virtual uint32 GetCurrentTextureHeight() const override { return m_textureHeight; }
		virtual uint32 GetTextureID(uint32 index = 0) const override { BAMBO_ASSERT_S(index < m_textures.size()); return m_textures[index]; }


		virtual void Resize(uint32 width, uint32 height) override;
		virtual int32 ReadPixel(uint32 attachmentIndex, int32 x, int32 y) override;
	private:
		uint32 m_ID = 0;
		uint32 m_textureWidth;
		uint32 m_textureHeight;
		std::vector<FramebufferTextureType> m_textureTypes;
		std::vector<uint32> m_textures;

		void CreateNewFramebuffer();
		void OpenGLFramebuffer::AttachTexture(uint32 id, GLenum internalFormat, GLenum attachmentType, GLenum format);
	};
}