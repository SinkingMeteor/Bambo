#pragma once
#include "Essentials.h"
#include "OpenGL/OpenGLCheck.h"
#include "TextureImplementation.h"
#include "Rect.h"

namespace Bambo
{
	class BAMBO_API OpenGLTexture final : public TextureImplementation
	{
	public:
		OpenGLTexture();
		virtual ~OpenGLTexture();

		virtual void LoadFromFile(const std::string& file) override;
		virtual void LoadFromBuffer(const TextureBuffer& buffer) override;

		virtual void AddSubTex(const RectUInt& rect, const TextureBuffer& buffer) override;
		virtual void AddSubTex(const RectUInt& rect, const uint8* data, TexChannelsAmount channels) override;

		virtual void Use() const override;
		virtual uint32 GetID() const override { return m_id; }
		virtual RectInt GetTextureRect() const override { return RectInt{ 0, m_height, m_width, m_height }; }
		virtual int32 GetTextureWidth() override { return m_width; }
		virtual int32 GetTextureHeight() override { return m_height; }
	private:
		uint32 m_id;

		int32 m_width;
		int32 m_height;

		uint32 m_internalFormat;
		uint32 m_imageFormat;

		uint32 m_wrapS;
		uint32 m_wrapT;
		uint32 m_filterMin;
		uint32 m_filterMax;
	};
}