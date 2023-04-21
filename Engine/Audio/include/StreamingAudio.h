#pragma once
#include "pch.h"
#include "ALCheck.h"
#include "AudioUtils.h"

namespace Bambo
{
	class BAMBO_API StreamingAudio final
	{
	public:
		constexpr static std::size_t BUFFER_SIZE = 65536;

		StreamingAudio(char* data, ALsizei dataSize, ALsizei sampleRate, int channels, int bps);
		StreamingAudio(const StreamingAudio&) = delete;
		StreamingAudio& operator=(const StreamingAudio&) = delete;
		~StreamingAudio();

		ALsizei GetSampleRate() const { return m_sampleRate; }
		ALsizei GetDataSize() const { return m_dataSize; }
		const char* GetRawData(std::size_t offset, std::size_t& sizeWasRead) const;
		std::size_t GetBuffersAmount() const { return m_currentBufferAmount; }
		ALuint* GetBufferAtIndex(int index);
		ALenum GetFormat() const { return m_format; }
		bool IsUsing() const { return m_isUsing; }
		void SetIsUsing(bool isUsing) { m_isUsing = isUsing; }
		void Reset();
	private:
		constexpr static std::size_t DEFAULT_BUFFER_AMOUNT = 4;

		std::unique_ptr<ALuint[]> m_buffers;
		std::unique_ptr<char[]> m_data;
		ALsizei m_dataSize;
		ALsizei m_sampleRate;
		ALenum m_format;
		std::size_t m_currentBufferAmount;
		bool m_isUsing;
	};
}