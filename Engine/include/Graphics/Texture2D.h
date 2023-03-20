#pragma once
#include "pch.h"
#include "Graphics/Rect.h"
namespace Bambo 
{
	class BAMBO_API Texture2D 
	{
	public:
		Texture2D();
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;
		~Texture2D();
		void LoadFromFile(const std::string& file);
		void Use() const;
		static void StopUse();
		RectInt GetTextureRect() const { return RectInt{ 0, 0, m_width, m_height }; }
	private:
		uint m_id;

		int m_width;
		int m_height;

		uint m_internalFormat;
		uint m_imageFormat;

		uint m_wrapS;
		uint m_wrapT;
		uint m_filterMin;
		uint m_filterMax;
	};
}