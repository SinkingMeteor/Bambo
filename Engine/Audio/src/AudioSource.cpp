#include "AudioSource.h"

namespace Bambo
{
	AudioSource::AudioSource() :
		m_sourceId(0),
		m_pitch(1.0f),
		m_volume(1.0f),
		m_isLoop(false),
		m_currentAudio(nullptr)
	{
		ALCheck(alGenSources(1, &m_sourceId));
		SetPitch(m_pitch);
		SetVolume(m_volume);
		SetLoop(m_isLoop);
	}

	void AudioSource::SetPitch(float value01)
	{
		m_pitch = std::clamp(value01, 0.0f, 1.0f);
		ALCheck(alSourcef(m_sourceId, AL_PITCH, m_pitch));
	}

	void AudioSource::SetVolume(float value01)
	{
		m_volume = std::clamp(value01, 0.0f, 1.0f);
		ALCheck(alSourcef(m_sourceId, AL_GAIN, m_volume));
	}

	void AudioSource::SetLoop(bool isActive)
	{
		m_isLoop = isActive;
		ALCheck(alSourcei(m_sourceId, AL_LOOPING, m_isLoop));
	}

	void AudioSource::SetPosiiton(const glm::vec2& newPosition)
	{
		ALCheck(alSource3f(m_sourceId, AL_POSITION, newPosition.x, newPosition.y, 0.0f));
	}

	void AudioSource::SetAudio(std::shared_ptr<Audio> audioResource) 
	{
		if (!audioResource) return;
	
		m_currentAudio = audioResource;
		ALCheck(alSourcei(m_sourceId, AL_BUFFER, m_currentAudio->GetFirstID()));
	}

	bool AudioSource::IsPlaying() const
	{
		ALint state = AL_PLAYING;
		ALCheck(alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state));
		return state == AL_PLAYING;
	}

	void AudioSource::Play()
	{
		if (!m_currentAudio)
		{
			Log("AudioSourceLog", "There is no sound to play.");
			return;
		}

		Stop();

		ALCheck(alSourcePlay(m_sourceId));
	}

	void AudioSource::Stop()
	{
		if (!IsPlaying()) return;

		ALCheck(alSourceStop(m_sourceId));
	}

	AudioSource::~AudioSource()
	{
		ALCheck(alSourcei(m_sourceId, AL_BUFFER, 0));
		ALCheck(alDeleteSources(1, &m_sourceId));
	}
}