#include "StreamingAudio.h"

namespace Bambo
{
	StreamingAudio::StreamingAudio(char* data, ALsizei dataSize, ALsizei sampleRate, int channels, int bps) :
		m_buffers(nullptr),
		m_data(data),
		m_dataSize(dataSize),
		m_sampleRate(sampleRate),
		m_format(AL_INVALID_ENUM),
		m_currentBufferAmount(DEFAULT_BUFFER_AMOUNT),
		m_isUsing(false)
	{
		BAMBO_ASSERT(CalculateAudioFormat(channels, bps, m_format), "Invalid format of audio")

		if (dataSize < DEFAULT_BUFFER_AMOUNT * BUFFER_SIZE)
		{
			m_currentBufferAmount = dataSize % BUFFER_SIZE;
		}

		m_buffers = std::make_unique<ALuint[]>(m_currentBufferAmount);

		ALCheck(alGenBuffers(m_currentBufferAmount, m_buffers.get()));

		for (std::size_t i = 0; i < m_currentBufferAmount; ++i)
		{
			ALCheck(alBufferData(m_buffers.get()[i], m_format, &(m_data.get()[i * BUFFER_SIZE]), BUFFER_SIZE, m_sampleRate));
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

	const char* StreamingAudio::GetRawData(std::size_t offset, std::size_t& sizeWasRead) const
	{
		sizeWasRead = 0;
		if (offset > m_dataSize) return nullptr;

		std::size_t dataLeft = m_dataSize - offset;

		if (dataLeft >= BUFFER_SIZE)
		{
			sizeWasRead = BUFFER_SIZE;
		}
		else
		{
			sizeWasRead = dataLeft;
		}

		return m_data.get() + offset;
	}


	void StreamingAudio::Reset()
	{
		for (std::size_t i = 0; i < m_currentBufferAmount; ++i)
		{
			ALCheck(alBufferData(m_buffers.get()[i], m_format, &(m_data.get()[i * BUFFER_SIZE]), BUFFER_SIZE, m_sampleRate));
		}
	}

}