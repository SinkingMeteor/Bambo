#include "Audio.h"

namespace Bambo
{
	Audio::Audio(char* data, ALsizei dataSize, ALsizei sampleRate, int channels, int bps) :
		m_buffer(AL_NONE),
		m_data(data),
		m_dataSize(dataSize),
		m_sampleRate(sampleRate),
		m_channels(channels),
		m_bps(bps)
	{
		ALenum format{};
		BAMBO_ASSERT(GetFormat(channels, bps, format), "Invalid format of audio")

		ALCheck(alGenBuffers(1, &m_buffer));
		ALCheck(alBufferData(m_buffer, format, m_data.get(), dataSize, sampleRate));
	}

	Audio::~Audio()
	{
		ALCheck(alDeleteBuffers(1, &m_buffer));
	}

	ALuint Audio::GetFirstID() const
	{
		return m_buffer;
	}
}