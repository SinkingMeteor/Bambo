#pragma once
#include "Essentials.h"
namespace Bambo
{
	class BAMBO_API TextureBuffer final
	{
	public:
		TextureBuffer();
		TextureBuffer(const TextureBuffer&) = delete;
		TextureBuffer& operator=(const TextureBuffer&) = delete;

		void Create(const Vector2u& texSize, const ByteColor& fillColor);
		Vector2u GetSize() const { return m_size; }
		void SetColor(const ByteColor& targetColor, const Vector2u coordinates);
		ByteColor GetColor(const Vector2u coordinates) const;
		const uint8* GetData() const { return m_colors.data(); }
	private:
		std::vector<uint8> m_colors;
		Vector2u m_size;
	};
}