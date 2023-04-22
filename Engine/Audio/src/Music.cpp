#include "Music.h"

namespace Bambo
{
	Music::Music() :
		AudioSource(),
		m_currentAudio(),
		m_cursor(0)
	{}

	void Music::Play()
	{
		if (!m_currentAudio)
		{
			Log("LogMusic", "[WARNING]: Current audio is nullptr");
			return;
		}

		Stop();

		ALCheck(alSourcePlay(m_sourceId));
	}

	void Music::Stop()
	{
		if (!IsPlaying()) return;

		ALCheck(alSourceStop(m_sourceId));
	}

	void Music::SetAudio(std::shared_ptr<StreamingAudio> streamingAudio)
	{
		BAMBO_ASSERT(streamingAudio, "You're trying to set invalid streaming audio")
		BAMBO_ASSERT(!streamingAudio->IsUsing(), "This streaming audio is already used by another music object")

		if (m_currentAudio.get() != nullptr)
		{
			if (IsPlaying())
				Stop();

			ALCheck(alSourceUnqueueBuffers(m_sourceId, m_currentAudio->GetBuffersAmount(), m_currentAudio->GetBufferAtIndex(0)));
			m_currentAudio->SetIsUsing(false);
			m_currentAudio->Reset();
		}

		m_currentAudio = streamingAudio;

		m_cursor = m_currentAudio->GetBuffersAmount() * StreamingAudio::BUFFER_SIZE;
		ALCheck(alSourceQueueBuffers(m_sourceId, m_currentAudio->GetBuffersAmount(), m_currentAudio->GetBufferAtIndex(0)));
	}

	void Music::Update()
	{
		if (!m_currentAudio) return;

		ALint buffersProcessed = 0;
		ALCheck(alGetSourcei(m_sourceId, AL_BUFFERS_PROCESSED, &buffersProcessed));

		if (buffersProcessed <= 0) return;

		while (buffersProcessed--)
		{
			ALuint buffer;
			ALCheck(alSourceUnqueueBuffers(m_sourceId, 1, &buffer));

			std::size_t newChunkSize{};
			const char* data = m_currentAudio->GetRawData(m_cursor, newChunkSize);


			if (!data)
			{
				m_cursor = 0;

				if (!m_isLoop)
				{
					Stop();
					return;
				}
				else
				{
					data = m_currentAudio->GetRawData(m_cursor, newChunkSize);
				}
			}

			m_cursor += newChunkSize;

			ALCheck(alBufferData(buffer, m_currentAudio->GetFormat(), data, newChunkSize, m_currentAudio->GetSampleRate()));
			ALCheck(alSourceQueueBuffers(m_sourceId, 1, &buffer));
		}
	}
}