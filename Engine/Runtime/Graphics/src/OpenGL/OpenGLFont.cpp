#include "OpenGL/OpenGLFont.h"
#include "freetype.h"
#include "RenderManager.h"

DECLARE_LOG_CATEGORY_STATIC(LogOpenGLFont)

namespace Bambo
{
	OpenGLFont::OpenGLFont() :
		FontImplementation(),
		m_characters(),
		m_fontFace()
	{}

	void OpenGLFont::LoadFromFile(const std::string& filePath)
	{
		FT_Library* ffHandle = RenderManager::Get()->GetFontHandle();
		FT_Face fontFace{};

		if (FT_New_Face(*ffHandle, filePath.c_str(), 0, &fontFace))
		{
			Logger::Get()->Log(LogOpenGLFont, Verbosity::Error, "Can't load font by path %s", filePath.c_str());
			return;
		}

		FT_Set_Pixel_Sizes(fontFace, 0, 48);
	}
}