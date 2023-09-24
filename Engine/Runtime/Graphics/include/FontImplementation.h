#pragma once
#include "Essentials.h"
#include "RenderAPI.h"
#include "Texture2D.h"

namespace Bambo
{
	struct Glyph
	{
	public:
		RectInt TextureRect{};
		RectFloat Bounds{};
		float Advance{};
	};

	struct Row
	{
	public:
		uint32 Width{};
		uint32 TopPos{};
		uint32 Height{};
	};

	struct Page
	{
	public:
		std::unordered_map<uint32, Glyph> Glyphs{};
		std::vector<Row> Rows{};
		Texture2D FontTexture{};
		uint32 NextRowPosY{ 3 };

		Page();
	};

	class BAMBO_API FontImplementation
	{
	public:
		FontImplementation() = default;
		FontImplementation(const FontImplementation&) = delete;
		FontImplementation& operator=(const FontImplementation&) = delete;
		virtual ~FontImplementation() {}

		virtual void LoadFromFile(const std::string& filePath);
		virtual const Glyph& GetGlyph(uint32 glyphCode, uint32 charSize) const = 0;

		static UPtr<FontImplementation> CreateBamboFont();
	};
}