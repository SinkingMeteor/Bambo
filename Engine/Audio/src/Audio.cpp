#include "Audio.h"

namespace Bambo
{
	Audio::Audio() : 
		m_id(0)
	{
		ALCheck(alGenBuffers(1, &m_id));
	}

	Audio::~Audio()
	{
		ALCheck(alDeleteBuffers(1, &m_id));
	}

	bool Audio::LoadFromFile(const std::string& filePath)
	{
		std::shared_ptr<AudioFile> audioFile = std::make_shared<AudioFile>();
		if (!audioFile->LoadWavFile(filePath)) return false;

		int bitsPerSample = audioFile->GetBitsPerSample();
		int channels = audioFile->GetChannels();
		ALsizei sampleRate = static_cast<ALsizei>(audioFile->GetSampleRate());
		ALenum format{};

		if (channels == 1 && bitsPerSample == 8)
			format = AL_FORMAT_MONO8;
		else if (channels == 1 && bitsPerSample == 16)
			format = AL_FORMAT_MONO16;
		else if (channels == 2 && bitsPerSample == 8)
			format = AL_FORMAT_STEREO8;
		else if (channels == 2 && bitsPerSample == 16)
			format = AL_FORMAT_STEREO16;
		else
		{
			Log("AudioLog", "ERROR: unrecognised wave format: %i channels, %i bps", channels, bitsPerSample);
			return false;
		}

		ALCheck(alBufferData(m_id, format, audioFile->GetRawData(), audioFile->GetDataSize(), sampleRate));

		return true;
	}
}