#pragma once
#include "pch.h"
#include "AL/al.h"
#include "AudioFile.h"
#include "Utils.h"
namespace Bambo
{
	class BAMBO_API Audio
	{
	public:
		Audio();
		~Audio();
		Audio(const Audio& audio) = delete;
		Audio& operator=(const Audio& audio) = delete;
		bool LoadFromFile(const std::string& filePath);

	private:
		ALuint m_id;
	};
}