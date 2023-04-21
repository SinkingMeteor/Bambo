#include "StreamingAudio.h"

namespace Bambo
{
	StreamingAudio::StreamingAudio(char* data, ALsizei dataSize, ALsizei sampleRate, int channels, int bps) :
		m_buffers(nullptr),
		m_data(data),
		m_dataSize(dataSize),
		m_sampleRate(sampleRate),
		m_channels(channels),
		m_bps(bps),
		m_currentBufferAmount(DEFAULT_BUFFER_AMOUNT)
	{
		ALenum format{};
		BAMBO_ASSERT(GetFormat(channels, bps, format), "Invalid format of audio")

		if (dataSize < DEFAULT_BUFFER_AMOUNT * BUFFER_SIZE)
		{
			m_currentBufferAmount = dataSize % BUFFER_SIZE;
		}

		ALCheck(alGenBuffers(m_currentBufferAmount, m_buffers.get()));

		for (std::size_t i = 0; i < m_currentBufferAmount; ++i)
		{
			ALCheck(alBufferData(m_buffers.get()[i], format, &(m_data.get()[i * BUFFER_SIZE]), BUFFER_SIZE, m_sampleRate));
		}
	}

	StreamingAudio::~StreamingAudio()
	{
		ALCheck(alDeleteBuffers(m_currentBufferAmount, m_buffers.get()));
	}

	ALuint* StreamingAudio::GetBufferAtIndex(int index)
	{
		BAMBO_ASSERT(index >= 0 && index < m_currentBufferAmount, "Out of range of streaming audio buffer array")
		return &m_buffers.get()[index];
	}


}