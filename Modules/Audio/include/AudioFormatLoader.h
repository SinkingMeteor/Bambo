#pragma once
#include "pch.h"
#include "Audio.h"
namespace Bambo
{
	struct RawAudioData
	{
		char* Data;
		ALsizei DataSize;
		ALsizei SampleRate;
		int Channels;
		int Bps;
	};

	class AudioFormatLoader
	{
	public:
		AudioFormatLoader() = default;
		AudioFormatLoader(const AudioFormatLoader&) = default;
		AudioFormatLoader& operator=(const AudioFormatLoader&) = default;
		virtual bool IsThatFormat(std::ifstream& dataStream) const = 0;
		virtual bool LoadAudio(std::ifstream& dataStream, RawAudioData& rawData) = 0;
		virtual ~AudioFormatLoader() {};
	};
}