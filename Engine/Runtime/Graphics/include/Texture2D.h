#pragma once
#include "pch.h"
#include "Resource/Resource.h"
#include "TextureImplementation.h"
namespace Bambo 
{
	class BAMBO_API Texture2D final : public Resource
	{
		friend class TextureLoader;

		RESOURCE_BODY(Texture2D, AssetType::Texture2D)

	public:
		Texture2D(const std::size_t assetId = 0);
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;

		void Use() const { m_textureImplementation->Use(); }
		RectInt GetTextureRect() const { return m_textureImplementation->GetTextureRect(); }
		const std::vector<RectInt>& GetTextureRects() const { return m_textureRects; }
		uint32 GetGraphicsID() const { return m_textureImplementation->GetID(); }
		const std::string& GetTexturePath() const { return m_textureImplementation->GetTexturePath(); }
	private:
		std::unique_ptr<TextureImplementation> m_textureImplementation;
		std::vector<RectInt> m_textureRects;

		void LoadFromFile(const std::filesystem::path& file);
	};
}