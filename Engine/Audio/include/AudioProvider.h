#pragma once
#include "pch.h"
#include "Audio.h"
namespace Bambo
{
	struct BAMBO_API AudioLoader
	{
		using result_type = std::shared_ptr<Audio>;

		result_type operator()(const std::string& path) const
		{
			std::shared_ptr<Audio> audio = std::make_shared<Audio>();
			if(!audio->LoadFromFile(path)) return nullptr;
			return audio;
		}
	};

	using AudioProvider = ResourceProvider<Audio, AudioLoader>;
}