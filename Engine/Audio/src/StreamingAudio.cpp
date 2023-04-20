#include "StreamingAudio.h"

namespace Bambo
{
	StreamingAudio::StreamingAudio(char* data, ALsizei dataSize, ALsizei sampleRate, int channels, int bps) :
		m_buffers(std::make_unique<ALuint[]>(BUFFER_AMOUNT)),
		m_data(data),
		m_dataSize(dataSize),
		m_sampleRate(sampleRate),
		m_channels(channels),
		m_bps(bps)
	{
		ALenum format{};
		BAMBO_ASSERT(GetFormat(channels, bps, format), "Invalid format of audio")

		ALCheck(alGenBuffers(BUFFER_AMOUNT, m_buffers.get()));

		for (std::size_t i = 0; i < BUFFER_AMOUNT; ++i)
		{
			ALCheck(alBufferData(m_buffers.get()[i], format, &(m_data.get()[i * BUFFER_SIZE]), BUFFER_SIZE, m_sampleRate));
		}
	}

	StreamingAudio::~StreamingAudio()
	{
		ALCheck(alDeleteBuffers(BUFFER_AMOUNT, m_buffers.get()));
	}
}