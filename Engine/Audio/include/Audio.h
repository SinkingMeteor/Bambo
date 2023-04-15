#pragma once
#include "pch.h"
#include "ALCheck.h"
#include "Utils.h"

namespace Bambo
{

	enum class AudioType
	{
		Sound = 1,
		Music = 4
	};

	class BAMBO_API Audio
	{
	public:
		Audio(char* data, ALsizei sampleRate, ALsizei dataSize, int channels, int bps);
		~Audio();
		Audio(const Audio& audio) = delete;
		Audio& operator=(const Audio& audio) = delete;
		ALuint GetFirstID() const;

		ALsizei GetSampleRate() const { return m_sampleRate; }
		ALsizei GetDataSize() const { return m_dataSize; }
		int GetChannels() const { return m_channels; }
		int GetBitsPerSample() const { return m_bps; }
		const char* GetRawData() const { return m_data; }

	private:
		ALuint m_buffer;

		char* m_data;
		ALsizei m_sampleRate;
		ALsizei m_dataSize;
		int m_channels;
		int m_bps;
	};

}