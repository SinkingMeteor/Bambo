#pragma once
#include "pch.h"
#include "TextureImplementation.h"
namespace Bambo 
{
	class BAMBO_API Texture2D final
	{
	public:
		Texture2D();
		
		void LoadFromFile(const std::string& file);
		void Use() const { m_textureImplementation->Use(); }
		RectInt GetTextureRect() const { return m_textureImplementation->GetTextureRect(); }
		const std::vector<RectInt>& GetTextureRects() const { return m_textureRects; }
	private:
		std::unique_ptr<TextureImplementation> m_textureImplementation;
		std::vector<RectInt> m_textureRects;
	};
}