#include "Audio/AudioSource.h"

namespace Bambo
{
	AudioSource::AudioSource() :
		m_sourceId(0),
		m_pitch(1.0f),
		m_volume(1.0f),
		m_isLoop(false)
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

	bool AudioSource::IsPlaying() const
	{
		ALint state = AL_PLAYING;
		ALCheck(alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state));
		return state == AL_PLAYING;
	}

	AudioSource::~AudioSource()
	{
		ALCheck(alSourcei(m_sourceId, AL_BUFFER, 0));
		ALCheck(alDeleteSources(1, &m_sourceId));
	}
}