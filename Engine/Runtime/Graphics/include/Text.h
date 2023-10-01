#pragma once
#include "Essentials.h"
#include "Font.h"

namespace Bambo
{
	struct GlyphRenderData
	{
		SPtr<Texture2D> Texture;
		Vector3f GlyphWorldPos;
		RectInt GlyphTexRect;
	};

	class BAMBO_API Text
	{
	public:
		Text();
		SPtr<Font> GetFont() const { return m_font; }
		const std::u32string GetText() const { return m_displayText; }
		uint32 GetTextSize() const { return m_charSize; }
		uint32& GetTextSizeRef() { return m_charSize; }

		RectFloat GetAreaRect() const { return m_textAreaRect; }
		float& GetAreaWidthRef() { return m_textAreaRect.Width; }
		float& GetAreaHeightRef() { return m_textAreaRect.Height; }

		void SetFont(SPtr<Font> font);
		void SetSize(uint32 charSize);
		void SetText(const std::u32string& displayText);
		const std::vector<GlyphRenderData>& GetTextData();

		void SetRebuildFlag() { m_needToRebuild = true; }
	private:
		RectFloat m_textAreaRect;
		SPtr<Font> m_font;
		std::u32string m_displayText;
		uint32 m_charSize;

		std::vector<GlyphRenderData> m_glyphs;
		bool m_needToRebuild;

		void Rebuild();
	};
}