#pragma once
#include "pch.h"
#include "ALCheck.h"
#include "AudioUtils.h"

namespace Bambo
{
	class BAMBO_API StreamingAudio final
	{
	public:
		StreamingAudio(char* data, ALsizei dataSize, ALsizei sampleRate, int channels, int bps);
		StreamingAudio(const StreamingAudio&) = delete;
		StreamingAudio& operator=(const StreamingAudio&) = delete;
		~StreamingAudio();

		ALsizei GetSampleRate() const { return m_sampleRate; }
		ALsizei GetDataSize() const { return m_dataSize; }
		int GetChannels() const { return m_channels; }
		int GetBitsPerSample() const { return m_bps; }
		const char* GetRawData() const { return m_data.get(); }
	private:
		constexpr static std::size_t BUFFER_AMOUNT = 4;
		constexpr static std::size_t BUFFER_SIZE = 65536;

		std::unique_ptr<ALuint[]> m_buffers;
		std::unique_ptr<char[]> m_data;
		ALsizei m_dataSize;
		ALsizei m_sampleRate;
		int m_channels;
		int m_bps;
	};
}