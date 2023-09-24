#include "TextureBuffer.h"

namespace Bambo
{
	DECLARE_LOG_CATEGORY_STATIC(LogTextureBuffer)

	TextureBuffer::TextureBuffer() :
		m_colors(),
		m_size()
	{}

	void TextureBuffer::Create(const Vector2u& texSize, const ByteColor& fillColor)
	{
		if (texSize.X == 0 || texSize.Y == 0)
		{
			Logger::Get()->Log(LogTextureBuffer, Verbosity::Error, "Invalid size for texture buffer. X: %i, Y: %i", texSize.X, texSize.Y);
			return;
		}

		m_size = texSize;
		m_colors.resize(texSize.X * texSize.Y * 4);
		size_t arrSize = m_colors.size();

		for (int i = 0; i < arrSize; i += 4)
		{
			m_colors[i] = fillColor.R;
			m_colors[i + 1] = fillColor.G;
			m_colors[i + 2] = fillColor.B;
			m_colors[i + 3] = fillColor.A;
		}
	}

	void TextureBuffer::SetColor(const ByteColor& targetColor, const Vector2u coordinates)
	{
		BAMBO_ASSERT_S(coordinates.X < m_size.X)
		BAMBO_ASSERT_S(coordinates.Y < m_size.Y)

		uint32 targetIndex = (coordinates.Y * m_size.X + coordinates.X) * 4u;
		m_colors[targetIndex] = targetColor.R;
		m_colors[targetIndex + 1] = targetColor.G;
		m_colors[targetIndex + 2] = targetColor.B;
		m_colors[targetIndex + 3] = targetColor.A;
	}

	ByteColor TextureBuffer::GetColor(const Vector2u coordinates) const
	{
		BAMBO_ASSERT_S(coordinates.X < m_size.X)
		BAMBO_ASSERT_S(coordinates.Y < m_size.Y)

		uint32 targetIndex = (coordinates.Y * m_size.X + coordinates.X) * 4u;
		uint8 r = m_colors[targetIndex];
		uint8 g = m_colors[targetIndex + 1];
		uint8 b = m_colors[targetIndex + 2];
		uint8 a = m_colors[targetIndex + 3];
		return { r, g, b, a };
	}
}