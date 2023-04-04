#include "Audio.h"

namespace Bambo
{
	Audio::Audio() : 
		m_id(0)
	{
		alGenBuffers(1, &m_id);
	}

	Audio::~Audio()
	{
		alDeleteBuffers(1, &m_id);
	}

	bool Audio::LoadFromFile(const std::string& filePath)
	{
		std::shared_ptr<AudioFile<double>> audioFile = std::make_shared<AudioFile<double>>();
		if (!audioFile->load(filePath)) return false;

		int bitsPerSample = audioFile->getBitDepth();
		int channels = audioFile->getNumChannels();
		ALsizei sampleRate = static_cast<ALsizei>(audioFile->getSampleRate());
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

		alBufferData(m_id, format, audioFile->samples.data(), audioFile->samples.size(), sampleRate);

		return true;
	}
}