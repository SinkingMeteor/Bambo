#include "Audio.h"

namespace
{
	constexpr std::size_t BUFFER_MAX_SIZE = 65536;
}

namespace Bambo
{
	Audio::Audio(char* data, ALsizei sampleRate, ALsizei dataSize, int channels, int bps) :
		m_buffer(0),
		m_data(data),
		m_sampleRate(sampleRate),
		m_dataSize(dataSize),
		m_channels(channels),
		m_bps(bps)
	{
		ALenum format{};

		if (m_channels == 1 && m_bps == 8)
			format = AL_FORMAT_MONO8;
		else if (m_channels == 1 && m_bps == 16)
			format = AL_FORMAT_MONO16;
		else if (m_channels == 2 && m_bps == 8)
			format = AL_FORMAT_STEREO8;
		else if (m_channels == 2 && m_bps == 16)
			format = AL_FORMAT_STEREO16;

		ALCheck(alGenBuffers(1, &m_buffer));
		ALCheck(alBufferData(m_buffer, format, m_data, dataSize, sampleRate));
	}

	Audio::~Audio()
	{
		ALCheck(alDeleteBuffers(1, &m_buffer));

		if (m_data != nullptr)
		{
			delete[] m_data;
		}
	}

	ALuint Audio::GetFirstID() const
	{
		return m_buffer;
	}
}