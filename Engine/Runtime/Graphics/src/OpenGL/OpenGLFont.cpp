#include "OpenGL/OpenGLFont.h"
#include "freetype.h"
#include "RenderManager.h"

DECLARE_LOG_CATEGORY_STATIC(LogOpenGLFont)

namespace Bambo
{
	OpenGLFont::OpenGLFont() :
		FontImplementation(),
		m_pages(),
		m_fontFace()
	{}

	OpenGLFont::~OpenGLFont()
	{
		if (m_fontFace)
		{
			FT_Done_Face(std::move(m_fontFace));
		}
	}

	void OpenGLFont::LoadFromFile(const std::string& filePath)
	{
		FT_Library* ffHandle = RenderManager::Get()->GetFontHandle();

		if (FT_New_Face(*ffHandle, filePath.c_str(), 0, &m_fontFace))
		{
			Logger::Get()->Log(LogOpenGLFont, Verbosity::Error, "Can't load font by path %s", filePath.c_str());
			return;
		}

		Logger::Get()->Log(LogOpenGLFont, Verbosity::Info, "Num of available glyphs: %i", m_fontFace->num_glyphs);

		FT_Set_Pixel_Sizes(m_fontFace, 0, 48);
	}

	const Glyph& OpenGLFont::GetGlyph(uint32 glyphCode, uint32 charSize) const
	{

	}

	Glyph OpenGLFont::LoadGlyph(uint32 codePoint, uint32 characterSize)
	{
		return {};
	}

	Page& OpenGLFont::LoadPage(uint32 charSize)
	{
		return m_pages.try_emplace(charSize).first->second;
	}

}