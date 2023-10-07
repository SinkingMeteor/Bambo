#include "Font.h"
#include "Engine.h"

DECLARE_LOG_CATEGORY_STATIC(LogFont)

namespace
{
	constexpr uint32 DEFAULT_GLYPH_PADDING = 1u;
	constexpr uint32 DEFAULT_GLYPH_SIZE = 16u;
	constexpr uint32 DEFAULT_UTF_START_INDEX = 32u;
	constexpr uint32 DEFAULT_UTF_END_INDEX = 128u;
	constexpr uint32 MAX_SUPPORTED_SIZE = 4096u;

	const std::vector<uint32> TEX_SIZES = { 2u, 4u, 8u, 16u, 32u, 64u, 128u, 256u, 512u, 1024u, 2048u, 4096u };
	const std::vector<uint32> DEFAULT_GLYPH_RANGES =
	{
		0x0020u, 0x00FFu, // Basic Latin + Latin Supplement
		0x0400u, 0x052Fu, // Cyrillic + Cyrillic Supplement
		0x2DE0u, 0x2DFFu, // Cyrillic Extended-A
		0xA640u, 0xA69Fu // Cyrillic Extended-B
	};
}

namespace Bambo
{
	Font::Font(Engine* engine, std::size_t instanceID) :
		Resource(instanceID, engine),
		m_pages(),
		m_fontFace()
	{
	}

	Font::~Font()
	{
		if (m_fontFace)
		{
			FT_Done_Face(std::move(m_fontFace));
		}
	}

	void Font::LoadFromFile(const std::string& fontFile)
	{
		BAMBO_ASSERT_S(m_engine)
		FT_Library* ffHandle = m_engine->GetRenderManager()->GetFontHandle();

		if (FT_New_Face(*ffHandle, fontFile.c_str(), 0, &m_fontFace))
		{
			Logger::Get()->Log(LogFont, Verbosity::Error, "Can't load font by path %s", fontFile.c_str());
			return;
		}

		LoadPage(DEFAULT_GLYPH_SIZE);
	}

	Page* Font::GetPage(uint32 charSize)
	{
		auto it = m_pages.find(charSize);
		if (it == m_pages.end())
		{
			if (!LoadPage(charSize)) return nullptr;
		}

		return &(m_pages[charSize]);
	}

	bool Font::LoadPage(uint32 charSize)
	{
		if (HasPage(charSize)) return true;
		if (!SetCurrentSize(charSize)) return false;

		Page page{};

		uint32 texWidth = DEFAULT_GLYPH_PADDING;
		uint32 texHeight = 0u;
		uint32 maxGlyphHeight = 0u;

		for (uint32 j = 0; j < DEFAULT_GLYPH_RANGES.size(); j += 2)
		{
			for (uint32 i = DEFAULT_GLYPH_RANGES[j]; i < DEFAULT_GLYPH_RANGES[j + 1]; ++i)
			{
				if (FT_Load_Char(m_fontFace, i, FT_LOAD_RENDER))
				{
					Logger::Get()->Log(LogFont, Verbosity::Warning, "Can't load glyph with code %u", i);
					continue;
				}

				Glyph glyph{};

				FT_Vector advanceVec = m_fontFace->glyph->advance;

				glyph.Advance.X = advanceVec.x >> 6;
				glyph.Advance.Y = advanceVec.y >> 6;

				glyph.TextureRect.Width = m_fontFace->glyph->bitmap.width;
				glyph.TextureRect.Height = m_fontFace->glyph->bitmap.rows;

				texWidth += glyph.TextureRect.Width + DEFAULT_GLYPH_PADDING * 2u;

				maxGlyphHeight = std::max(maxGlyphHeight, glyph.TextureRect.Height);

				glyph.Bearing.X = m_fontFace->glyph->metrics.horiBearingX >> 6;
				glyph.Bearing.Y = glyph.TextureRect.Height - (m_fontFace->glyph->metrics.horiBearingY >> 6);

				

				page.Glyphs[i] = glyph;

			}
		}

		BAMBO_ASSERT_S(texWidth != 0u)

		uint32 totalMapSquare = texWidth * maxGlyphHeight;
		page.RowHeight = maxGlyphHeight;

		if (totalMapSquare > MAX_SUPPORTED_SIZE * MAX_SUPPORTED_SIZE)
		{
			Logger::Get()->Log(LogFont, Verbosity::Error, "Can't load font with size %u. Target texture size is unsupported.", charSize);
			return false;
		}

		for (uint32 i = 0; i < TEX_SIZES.size(); ++i)
		{
			uint32 targetTexSquare = TEX_SIZES[i] * TEX_SIZES[i];
			if (targetTexSquare >= totalMapSquare)
			{
				texWidth = TEX_SIZES[i];
				texHeight = TEX_SIZES[i];
				break;
			}
		}
			
		page.FontTexture = std::make_shared<Texture2D>(m_engine);

		{
			TextureBuffer globalTexBuffer{TexChannelsAmount::R};
			globalTexBuffer.Create({ texWidth, texHeight }, ByteColor::Transparent());
			page.FontTexture->LoadFromBuffer(globalTexBuffer);
		}

		Vector2i offset{ 0, 0 };

		offset.X += DEFAULT_GLYPH_PADDING;
		offset.Y += DEFAULT_GLYPH_PADDING;

		for (uint32 j = 0; j < DEFAULT_GLYPH_RANGES.size(); j += 2)
		{
			for (uint32 i = DEFAULT_GLYPH_RANGES[j]; i < DEFAULT_GLYPH_RANGES[j + 1]; ++i)
			{
				if (FT_Load_Char(m_fontFace, i, FT_LOAD_RENDER)) continue;
				BAMBO_ASSERT_S(page.Glyphs.find(i) != page.Glyphs.end())

				if (!m_fontFace->glyph->bitmap.buffer) continue;

				Glyph& glyph = page.Glyphs[i];

				int32 leftSpace = static_cast<int32>(texWidth) - offset.X;
				if (leftSpace < static_cast<int32>(glyph.TextureRect.Width))
				{
					offset.Y += maxGlyphHeight;
					offset.Y += DEFAULT_GLYPH_PADDING;
					offset.X = DEFAULT_GLYPH_PADDING;
				}

				glyph.TextureRect.Left = offset.X;
				glyph.TextureRect.Top = offset.Y;

				page.FontTexture->AddSubTex(glyph.TextureRect, m_fontFace->glyph->bitmap.buffer, TexChannelsAmount::R);

				offset.X += DEFAULT_GLYPH_PADDING;
				offset.X += glyph.TextureRect.Width;
			}
		}

		m_pages[charSize] = std::move(page);
		return true;
	}

	bool Font::SetCurrentSize(uint32 charNewSize)
	{
		const uint16 currentSize = m_fontFace->size->metrics.x_ppem;

		if (currentSize == charNewSize) return true;

		return !FT_Set_Pixel_Sizes(m_fontFace, 0u, charNewSize);
	}

	bool Font::HasPage(uint32 charSize) const
	{
		return m_pages.find(charSize) != m_pages.end();
	}
}