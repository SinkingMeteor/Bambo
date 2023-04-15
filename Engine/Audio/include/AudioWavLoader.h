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
		virtual std::shared_ptr<Audio> LoadAudio(std::ifstream& dataStream) override;
	private:
		bool AudioWavLoader::ReadHeaderOfWav(std::ifstream& file, ALsizei& sampleRate, ALsizei& dataSize, int& channels, int& bps);
	};
}