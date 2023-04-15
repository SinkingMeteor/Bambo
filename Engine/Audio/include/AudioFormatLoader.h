#pragma once
#include "pch.h"
#include "Audio.h"
namespace Bambo
{
	class AudioFormatLoader
	{
	public:
		AudioFormatLoader() = default;
		AudioFormatLoader(const AudioFormatLoader&) = default;
		AudioFormatLoader& operator=(const AudioFormatLoader&) = default;
		virtual bool IsThatFormat(std::ifstream& dataStream) const = 0;
		virtual std::shared_ptr<Audio> LoadAudio(std::ifstream& dataStream) = 0;
		virtual ~AudioFormatLoader() {};
	};
}