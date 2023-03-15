#pragma once
#include "pch.h"

namespace Bambo 
{
	class Texture2D 
	{
	public:
		Texture2D();
		~Texture2D();
		void LoadFromFile(const char* file);
		void SetFormat(uint format);
		void Use() const;

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