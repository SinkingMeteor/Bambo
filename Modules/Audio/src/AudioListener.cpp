#include "AudioListener.h"

namespace Bambo
{
	//@TODO: Dublicate all setters and getters in audio device
	AudioListener::AudioListener(std::shared_ptr<AudioDevice> device) :
		m_device(device)
	{
		BAMBO_ASSERT(m_device, "Audio device is null");

		SetPosition(glm::vec2{ 0.0f, 0.0f });
		SetOrientation(glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f, -1.0f });
		SetVolume(1.0f);
	}

	void AudioListener::SetPosition(const glm::vec2& position)
	{
		BAMBO_ASSERT(m_device, "Audio device is null");

		ALCheck(alListener3f(AL_POSITION, position.x, position.y, 0.0f));
	}

	void AudioListener::SetOrientation(const glm::vec3& upVector, const glm::vec3& direction)
	{
		BAMBO_ASSERT(m_device, "Audio device is null");

		float orientation[] = { direction.x, direction.y, direction.z, upVector.x, upVector.y, upVector.z };
		ALCheck(alListenerfv(AL_ORIENTATION, orientation));
	}

	void AudioListener::SetVolume(float value01)
	{
		BAMBO_ASSERT(m_device, "Audio device is null");

		ALCheck(alListenerf(AL_GAIN, value01));
	}

	glm::vec2 AudioListener::GetPosition() const
	{
		BAMBO_ASSERT(m_device, "Audio device is null");

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		ALCheck(alGetListener3f(AL_POSITION, &x, &y, &z));
		return glm::vec2{ x, y };
	}

}