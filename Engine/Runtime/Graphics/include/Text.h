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

	class BAMBO_API Text final
	{
	public:
		Text();
		SPtr<Font> GetFont() const { return m_font; }
		std::u32string* GetText32Ptr() { return &m_displayText; }
		std::u32string GetText32() const { return m_displayText; }
		std::string GetText8() const { return ToUtf8(m_displayText); }
		uint32 GetTextSize() const { return m_charSize; }
		uint32& GetTextSizeRef() { return m_charSize; }

		RectFloat GetAreaRect() const { return m_textAreaRect; }
		float& GetAreaWidthRef() { return m_textAreaRect.Width; }
		float& GetAreaHeightRef() { return m_textAreaRect.Height; }

		void SetFont(SPtr<Font> font);
		void SetSize(uint32 charSize);
		void SetText(const std::u32string& displayText);
		void SetText(const std::string& utf8Text);
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