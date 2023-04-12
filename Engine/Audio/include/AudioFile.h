#pragma once
#include "pch.h"
#include "ALCheck.h"
#include "Utils.h"
namespace Bambo
{
	class AudioFile
	{
	public:
		AudioFile();
		AudioFile(const AudioFile&) = delete;
		AudioFile& operator=(const AudioFile&) = delete;
		~AudioFile();

		bool LoadWavFile(const std::string& fileName);
		ALsizei GetSampleRate() const { return m_sampleRate; }
		ALsizei GetDataSize() const { return m_dataSize; }
		int GetChannels() const { return m_channels; }
		int GetBitsPerSample() const { return m_bps; }
		const char* GetRawData() const { return m_data; }

	private:
		bool ReadHeaderOfWav(std::ifstream& inStream);
		int ConvertToInt(char* buffer, std::size_t len);

		ALsizei m_sampleRate;
		ALsizei m_dataSize;
		int m_channels;
		int m_bps;
		char* m_data;
	};
}