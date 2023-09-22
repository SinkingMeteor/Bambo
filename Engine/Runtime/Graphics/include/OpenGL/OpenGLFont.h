#pragma once
#include "Essentials.h"
#include "OpenGL/OpenGLCheck.h"
#include "FontImplementation.h"
#include "freetype.h"

namespace Bambo
{
	struct OpenGLCharacter
	{
		Vector2i Size{};
		Vector2i Bearing{};
		GLuint TextureID{};
		GLuint Advance{};
	};

	class BAMBO_API OpenGLFont final : public FontImplementation
	{
	public:
		OpenGLFont();
		virtual void LoadFromFile(const std::string& filePath) override;
	private:
		std::unordered_map<GLchar, OpenGLCharacter> m_characters;
		FT_Face m_fontFace;
	};
}