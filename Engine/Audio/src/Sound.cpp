#include "Sound.h"

namespace Bambo
{
	Sound::Sound() : 
		AudioSource(),
		m_currentAudio(nullptr)
	{}

	void Sound::Play()
	{
		if (!m_currentAudio)
		{
			Log("AudioSourceLog", "There is no sound to play.");
			return;
		}

		Stop();

		ALCheck(alSourcePlay(m_sourceId));
	}

	void Sound::Stop()
	{
		if (!IsPlaying()) return;

		ALCheck(alSourceStop(m_sourceId));
	}

	void Sound::SetAudio(std::shared_ptr<Audio> audioResource)
	{
		if (!audioResource) return;

		m_currentAudio = audioResource;
		ALCheck(alSourcei(m_sourceId, AL_BUFFER, m_currentAudio->GetFirstID()));
	}

}