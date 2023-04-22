#pragma once
#include "pch.h"
#include "AudioFormatLoader.h"
#include "AudioWavLoader.h"
#include "StreamingAudio.h"

namespace Bambo
{
	struct BAMBO_API StreamingAudioLoader
	{
		using result_type = std::shared_ptr<StreamingAudio>;

	public:
		StreamingAudioLoader() :
			m_loaders()
		{
			m_loaders.emplace_back(std::make_shared<AudioWavLoader>());
		}

		result_type operator()(const std::string& path) const
		{
			std::ifstream inStream{ path, std::ios::binary };
			if (!inStream.is_open())
			{
				Logger::Log("LogAudioFile", Verbosity::Error, "Can't open file by path: %s", path.c_str());
				return nullptr;
			}

			for (size_t i = 0; i < m_loaders.size(); ++i)
			{
				inStream.clear();
				inStream.seekg(0, std::ios::beg);

				if (m_loaders[i]->IsThatFormat(inStream))
				{
					inStream.clear();
					inStream.seekg(0, std::ios::beg);

					RawAudioData rawData{};
					if (!m_loaders[i]->LoadAudio(inStream, rawData))
					{
						return nullptr;
					}
					return std::make_shared<StreamingAudio>(rawData.Data, rawData.DataSize, rawData.SampleRate, rawData.Channels, rawData.Bps);
				}
			}

			return nullptr;
		}

	private:
		std::vector<std::shared_ptr<AudioFormatLoader>> m_loaders;
	};

	using StreamingAudioProvider = ResourceProvider<StreamingAudio, StreamingAudioLoader>;
}