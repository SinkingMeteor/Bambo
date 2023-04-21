#pragma once
#include "pch.h"
#include "AudioFormatLoader.h"
namespace Bambo
{
	class AudioWavLoader final : public AudioFormatLoader
	{
	public:
		AudioWavLoader() = default;
		virtual ~AudioWavLoader(){}
		virtual bool IsThatFormat(std::ifstream& dataStream) const override;
		virtual bool LoadAudio(std::ifstream& dataStream, RawAudioData& rawData) override;
	private:
		bool AudioWavLoader::ReadHeaderOfWav(std::ifstream& file, ALsizei& sampleRate, ALsizei& dataSize, int& channels, int& bps);
	};
}