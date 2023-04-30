#pragma once
#include "pch.h"
#include "TextureImplementation.h"
namespace Bambo 
{
	class BAMBO_API Texture2D final
	{
	public:
		Texture2D();
		
		void LoadFromFile(const std::string& file) { m_textureImplementation->LoadFromFile(file); }
		void Use() const { m_textureImplementation->Use(); }
		RectInt GetTextureRect() const { return m_textureImplementation->GetTextureRect(); }

	private:
		std::unique_ptr<TextureImplementation> m_textureImplementation;
	};
}