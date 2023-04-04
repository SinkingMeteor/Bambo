#include "AudioDevice.h"

namespace Bambo
{
	AudioDevice::AudioDevice()
	{
		m_device = alcOpenDevice(nullptr);

		if (!m_device)
		{
			Log("Audio device log", "ERROR: %s", "Can't create an openAL device");
			return;
		}

		m_context = alcCreateContext(m_device, nullptr);
	
		if (!m_context)
		{
			Log("Audio device log", "ERROR: %s", "Can't create an openAL context");
			return;
		}

		if (!alcMakeContextCurrent(m_context))
		{
			Log("Audio device log", "ERROR: %s", "Can't set current openAL context");
			return;
		}
	}

	AudioDevice::~AudioDevice()
	{
		alcMakeContextCurrent(nullptr);
		if (m_context) alcDestroyContext(m_context);
		if (m_device) alcCloseDevice(m_device);
	}
}