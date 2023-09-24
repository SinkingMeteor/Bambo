#pragma once
#include "Essentials.h"
#include "OpenGL/OpenGLCheck.h"
#include "FontImplementation.h"
#include "freetype.h"

namespace Bambo
{
	class BAMBO_API OpenGLFont final : public FontImplementation
	{
	public:
		OpenGLFont();
		virtual ~OpenGLFont();
		virtual void LoadFromFile(const std::string& filePath) override;
		virtual const Glyph& GetGlyph(uint32 glyphCode, uint32 charSize) const;

	private:
		std::unordered_map<uint32, Page> m_pages;
		FT_Face m_fontFace;

		Glyph LoadGlyph(uint32 codePoint, uint32 characterSize);
		Page& LoadPage(uint32 charSize);
	};
}