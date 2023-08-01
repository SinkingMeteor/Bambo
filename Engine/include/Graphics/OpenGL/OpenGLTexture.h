#pragma once
#include "Core/Essentials.h"
#include "Graphics/OpenGL/OpenGLCheck.h"
#include "Graphics/TextureImplementation.h"
#include "Graphics/Rect.h"

namespace Bambo
{
	class BAMBO_API OpenGLTexture final : public TextureImplementation
	{
	public:
		OpenGLTexture();
		virtual ~OpenGLTexture();

		virtual void LoadFromFile(const std::string& file) override;
		virtual void Use() const override;
		virtual uint32 GetID() const override { return m_id; }
		virtual RectInt GetTextureRect() const override { return RectInt{ 0, 0, m_width, m_height }; }
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