#pragma once
#include "Essentials.h"
namespace Bambo
{
	enum class TexChannelsAmount
	{
		R = 1,
		RGB = 3,
		RGBA = 4
	};

	class BAMBO_API TextureBuffer final
	{
	public:
		TextureBuffer(TexChannelsAmount channels);
		TextureBuffer(const TextureBuffer&) = delete;
		TextureBuffer& operator=(const TextureBuffer&) = delete;

		void Create(const Vector2u& texSize, const ByteColor& fillColor);
		Vector2u GetSize() const { return m_size; }
		TexChannelsAmount GetChannelsAmounts() const { return m_channelsAmount; }
		void SetColor(const ByteColor& targetColor, const Vector2u coordinates);
		ByteColor GetColor(const Vector2u coordinates) const;
		const uint8* GetData() const { return m_colors.data(); }
	private:
		std::vector<uint8> m_colors;
		Vector2u m_size;
		TexChannelsAmount m_channelsAmount;
	};
}