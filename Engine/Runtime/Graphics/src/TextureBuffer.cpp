#include "TextureBuffer.h"

namespace Bambo
{
	DECLARE_LOG_CATEGORY_STATIC(LogTextureBuffer)

	TextureBuffer::TextureBuffer(TexChannelsAmount channels) :
		m_colors(),
		m_size(),
		m_channelsAmount(channels)
	{}

	void TextureBuffer::Create(const Vector2u& texSize, const ByteColor& fillColor)
	{
		if (texSize.X == 0 || texSize.Y == 0)
		{
			Logger::Get()->Log(LogTextureBuffer, Verbosity::Error, "Invalid size for texture buffer. X: %i, Y: %i", texSize.X, texSize.Y);
			return;
		}

		int32 channelsAmount = static_cast<int32>(m_channelsAmount);

		m_size = texSize;
		m_colors.resize(texSize.X * texSize.Y * 4);
		size_t arrSize = m_colors.size();

		for (int32 i = 0; i < arrSize; i += 4)
		{
			for (int32 j = 0; j < channelsAmount; ++j)
			{
				m_colors[i + j] = fillColor.Colors[j];
			}
		}
	}

	void TextureBuffer::SetColor(const ByteColor& targetColor, const Vector2u coordinates)
	{
		BAMBO_ASSERT_S(coordinates.X < m_size.X)
		BAMBO_ASSERT_S(coordinates.Y < m_size.Y)

		uint32 targetIndex = (coordinates.Y * m_size.X + coordinates.X) * 4u;
		int32 channelsAmount = static_cast<int32>(m_channelsAmount);

		for (int32 j = 0; j < channelsAmount; ++j)
		{
			m_colors[targetIndex + j] = targetColor.Colors[j];
		}
	}

	ByteColor TextureBuffer::GetColor(const Vector2u coordinates) const
	{
		BAMBO_ASSERT_S(coordinates.X < m_size.X)
		BAMBO_ASSERT_S(coordinates.Y < m_size.Y)

		uint32 targetIndex = (coordinates.Y * m_size.X + coordinates.X) * 4u;
		int32 channelsAmount = static_cast<int32>(m_channelsAmount);

		ByteColor color{};

		for (int32 j = 0; j < channelsAmount; ++j)
		{
			color.Colors[j] = m_colors[targetIndex + j];
		}

		return color;
	}
}