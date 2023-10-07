#pragma once
#include "Essentials.h"
#include "Resource/Resource.h"
#include "Texture2D.h"
#include "freetype.h"

namespace Bambo
{
	class RenderManager;
	class Engine;

	struct Glyph
	{
	public:
		RectUInt TextureRect{};
		Vector2i Bearing{};
		Vector2i Advance{};
	};

	struct Page
	{
	public:
		std::unordered_map<uint32, Glyph> Glyphs{};
		SPtr<Texture2D> FontTexture{};
		float RowHeight;
	};


	class BAMBO_API Font final : public Resource
	{
		RESOURCE_BODY(Font, AssetType::Font)
	public:
		Font(Engine* engine, std::size_t instanceID);
		virtual ~Font();
		void LoadFromFile(const std::string& fontFile);
		Page* GetPage(uint32 charSize);

	private:
		std::unordered_map<uint32, Page> m_pages;
		FT_Face m_fontFace;

		bool LoadPage(uint32 charSize);
		bool HasPage(uint32 charSize) const;

		bool SetCurrentSize(uint32 charNewSize);
	};
}