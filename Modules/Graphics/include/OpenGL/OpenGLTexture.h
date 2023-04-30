#pragma once
#include "pch.h"
#include "Graphics.h"
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
		virtual void Use() const override;
		virtual RectInt GetTextureRect() const override { return RectInt{ 0, 0, m_width, m_height }; }
	private:
		uint m_id;

		int m_width;
		int m_height;

		uint m_internalFormat;
		uint m_imageFormat;

		uint m_wrapS;
		uint m_wrapT;
		uint m_filterMin;
		uint m_filterMax;
	};
}