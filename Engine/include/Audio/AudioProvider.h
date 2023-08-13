#pragma once
#include "pch.h"
#include "AudioFormatLoader.h"
#include "AudioWavLoader.h"
#include "Audio.h"
namespace Bambo
{
	struct BAMBO_API AudioLoader
	{
		using result_type = std::shared_ptr<Audio>;

	public:
		AudioLoader() :
			m_loaders()
		{
			m_loaders.emplace_back(std::make_shared<AudioWavLoader>());
		}

		result_type operator()(const std::size_t id, const std::string& path) const
		{
			std::ifstream inStream{ path, std::ios::binary };
			if (!inStream.is_open())
			{
				Log("LogAudioFile", "Can't open file by path: %s", path.c_str());
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
					return std::make_shared<Audio>(id, rawData.Data, rawData.DataSize, rawData.SampleRate, rawData.Channels, rawData.Bps);
				}
			}

			return nullptr;
		}

	private:
		std::vector<std::shared_ptr<AudioFormatLoader>> m_loaders;
	};

	using AudioProvider = ResourceProvider<Audio, AudioLoader>;
}