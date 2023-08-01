#pragma once
#include "Core/Essentials.h"
#include "Audio/ALCheck.h"
#include "Audio/AudioUtils.h"

namespace Bambo
{
	class BAMBO_API Audio final
	{
	public:
		Audio(char* data, ALsizei dataSize, ALsizei sampleRate, int channels, int bps);
		~Audio();
		Audio(const Audio& audio) = delete;
		Audio& operator=(const Audio& audio) = delete;
		ALuint GetFirstID() const;

		ALsizei GetSampleRate() const { return m_sampleRate; }
		ALsizei GetDataSize() const { return m_dataSize; }
		int GetChannels() const { return m_channels; }
		int GetBitsPerSample() const { return m_bps; }
		const char* GetRawData() const { return m_data.get(); }

	private:
		ALuint m_buffer;

		std::unique_ptr<char[]> m_data;
		ALsizei m_dataSize;
		ALsizei m_sampleRate;
		int m_channels;
		int m_bps;
	};

}