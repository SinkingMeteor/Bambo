#include "Text.h"

namespace Bambo
{
	Text::Text() :
		m_textAreaRect(0.0f, 0.0f, 300.0f, 150.0f),
		m_font(),
		m_displayText(),
		m_charSize(16u),
		m_glyphs(),
		m_needToRebuild(true)
	{}

	void Text::SetFont(SPtr<Font> font)
	{
		if (m_font == font) return;

		m_font = font;
		m_needToRebuild = true;
	}

	void Text::SetSize(uint32 charSize)
	{
		if (m_charSize = charSize) return;

		m_charSize = charSize;
		m_needToRebuild = true;
	}


	void Text::SetText(const std::u32string& displayText)
	{
		m_displayText = displayText;
		m_needToRebuild = true;
	}

	void Text::SetText(const std::string& utf8Text)
	{
		m_displayText = ToUtf32(utf8Text);
		m_needToRebuild = true;
	}

	const std::vector<GlyphRenderData>& Text::GetTextData()
	{
		if (m_needToRebuild)
		{
			Rebuild();
		}
		return m_glyphs;
	}

	void Text::Rebuild()
	{
		BAMBO_ASSERT_S(m_font)

		m_needToRebuild = false;
		m_glyphs.clear();

		Page* page = m_font->GetPage(m_charSize);
		BAMBO_ASSERT_S(page)

		SPtr<Texture2D> tex = page->FontTexture;

		std::size_t textSize = m_displayText.size();
		float xPos = 0.0f;
		float yPos = -page->RowHeight;

		for (size_t i = 0; i < textSize; ++i)
		{
			auto it = page->Glyphs.find(m_displayText[i]);
			if (it == page->Glyphs.end())
			{
				it = page->Glyphs.begin();
			}

			GlyphRenderData renderData{};
			renderData.Texture = tex;

			Glyph& glyph = it->second;

			//@TODO: добавить rect всему тексту
			renderData.GlyphWorldPos = {xPos + glyph.Bearing.X, yPos - glyph.Bearing.Y, 0.0f};
			xPos += glyph.Advance.X;
			if (xPos > m_textAreaRect.Width)
			{
				xPos = 0.0f;
				yPos -= page->RowHeight;
			}

			RectInt glyphTexRect{};
 			glyphTexRect.Left = static_cast<int32>(glyph.TextureRect.Left);
			glyphTexRect.Top = static_cast<int32>(glyph.TextureRect.Top);
			glyphTexRect.Width = static_cast<int32>(glyph.TextureRect.Width);
			glyphTexRect.Height = static_cast<int32>(glyph.TextureRect.Height);
			renderData.GlyphTexRect = glyphTexRect;

			m_glyphs.push_back(renderData);
		}
	}

}